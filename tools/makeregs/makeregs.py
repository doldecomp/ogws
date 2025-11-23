from sys import argv
from argparse import ArgumentParser
from json import loads


class Field:
    def __init__(self, res):
        self.name = get_req(res, "name")
        self.desc = res.get("desc")  # Description is optional
        self.start = get_req(res, "start")
        self.end = get_req(res, "end")

        # Sanity check on bounds
        if not isinstance(self.start, int) or not isinstance(self.end, int):
            raise Exception(
                f"[FATAL] Bitfield {self.name} has non-integral bounds: [{self.start}, {self.end}]")

        assert self.start <= self.end, "Bitfield has inverted bounds"

        # +1 for inclusive
        self.size = self.end - self.start + 1


class Register:
    def __init__(self, res):
        self.name = get_req(res, "name")
        self.id = res.get("id", "-1")

        # Sanity check on id
        try:
            self.id = int(self.id, base=0)
        except ValueError:
            raise Exception(
                f"[FATAL] Register {self.name} has invalid ID: {self.id}")

        # "fields" tag is optional, omit if currently empty/todo
        self.fields = [Field(f) for f in res.get("fields", [])]


def get_req(res, name):
    if name not in res:
        raise Exception(f"[FATAL] {res.__name__} missing key {name}")
    return res[name]


def enum_case(name):
    new_name = ""

    for c in name:
        if c.isalpha():
            new_name += c.upper()
        elif c.isnumeric():
            new_name += c
        else:
            new_name += "_"

    return new_name


def load_regs_json(args):
    # When not specified, output path is derived from the input path
    if args.output == None:
        args.output = args.input.replace(".json", ".h")
        print(f"[INFO] Output file path not specified, using {args.output}")

    # Read JSON file
    try:
        with open(args.input, "r") as f:
            res = loads(f.read())
    except OSError:
        print(f"[FATAL] Could not open JSON file for reading: {args.input}")
        return

    # Register info
    write_regs_header(args, res, [
                      Register(r) for r in get_req(res, "regs")])


def write_regs_header(args, res, regs):
    # Main context
    module = get_req(res, "module")
    name = get_req(res, "name")
    long_name = get_req(res, "long_name")

    # Output stream
    try:
        with open(args.output, "w+") as f:
            # Open header guard
            f.write(
                f"#ifndef RVL_SDK_{module.upper()}_HARDWARE_{name.upper()}_H\n")
            f.write(
                f"#define RVL_SDK_{module.upper()}_HARDWARE_{name.upper()}_H\n")

            # Main RVL types header
            f.write("#include <types.h>\n")
            f.write("\n")

            # Include dependencies
            for dep in res.get("deps", []):
                if dep != "types.h":
                    f.write(f"#include <{dep}>\n")
            f.write("\n")

            # C++ guard
            f.write("#ifdef __cplusplus\n")
            f.write("extern \"C\" {\n")
            f.write("#endif\n")

            f.write("\n")
            f.write("// clang-format off\n")
            f.write("\n")

            # Begin comment
            f.write(
                "/******************************************************************************\n")
            f.write(" *\n")
            f.write(" *\n")
            f.write(f" * {module} {long_name} ({name})\n")
            f.write(" *\n")
            f.write(" *\n")
            f.write(
                " *****************************************************************************/\n")

            f.write("\n")

            # Register enum comment
            f.write("/**\n")
            f.write(f" * {name} registers\n")
            f.write(" */\n")

            # Register enum
            enum_prefix = f"{module.upper()}_{name.upper()}_REG_"
            f.write("typedef enum {\n")
            for reg in regs:
                # Not "real" register (some are used as generic structure definitions)
                if reg.id == -1:
                    continue

                f.write(
                    f"    {enum_case(enum_prefix + reg.name)} = 0x{hex(reg.id)[2:].upper()},\n")
            f.write(f"}} {module.upper()}_{name.upper()}_REG;\n")

            f.write("\n")

            # Register field macros
            for reg in regs:
                # No fields defined for the register
                if len(reg.fields) == 0:
                    continue

                cased_reg = enum_case(reg.name)

                f.write(
                    "/******************************************************************************\n")

                if reg.id != -1:
                    f.write(
                        f" * {name} register 0x{hex(reg.id)[2:].upper()} - {reg.name}\n")
                else:
                    f.write(
                        f" * {name} structure - {reg.name}\n")

                f.write(
                    " *****************************************************************************/\n")

                for field in reg.fields:
                    cased_field = enum_case(field.name)

                    # Field comment
                    f.write(
                        f"// {cased_field} [{field.start}:{field.end}] ({field.size})")
                    if field.desc != None:
                        f.write(f" - {field.desc}")
                    f.write("\n")

                    macro_prefix = f"{module.upper()}_{name.upper()}"

                    # Begin/End/Size macros for manual use
                    f.write(
                        f"        /* start bit  */ #define {macro_prefix}_{cased_reg}_{cased_field}_B {field.start}\n")
                    f.write(
                        f"        /* end bit    */ #define {macro_prefix}_{cased_reg}_{cased_field}_E {field.end}\n")
                    f.write(
                        f"        /* bit size   */ #define {macro_prefix}_{cased_reg}_{cased_field}_SZ {field.size}\n")

                    f.write("\n")

                    # Mask macros for manual use
                    f.write(
                        f"        /* raw mask   */ #define {macro_prefix}_{cased_reg}_{cased_field}_MASK (((1 << {field.size}) - 1) << (31 - {field.end}))\n")
                    f.write(
                        f"        /* local mask */ #define {macro_prefix}_{cased_reg}_{cased_field}_LMASK ((1 << {field.size}) - 1)\n")

                    # Left-right shift macro for manual use
                    f.write(
                        f"        /* bit shift  */ #define {macro_prefix}_{cased_reg}_{cased_field}_SHIFT {31 - field.end}\n")

                    f.write("\n")

                    # Fast (intrinsic) GET macro
                    f.write(
                        f"        /* get value  */ #define {macro_prefix}_GET_{cased_reg}_{cased_field}(reg) ")
                    f.write(
                        f"GX_BITGET((reg), {field.start}, {field.size})\n")

                    # Fast (intrinsic) SET macro
                    f.write(
                        f"        /* set value  */ #define {macro_prefix}_SET_{cased_reg}_{cased_field}(reg, x) ")
                    f.write(
                        f"((reg) = GX_BITSET((reg), {field.start}, {field.size}, x))\n")

                    f.write("\n")

                f.write("\n")
            f.write("\n")

            f.write("// clang-format on\n")
            f.write("\n")

            # Close C++ guard
            f.write("#ifdef __cplusplus\n")
            f.write("}\n")
            f.write("#endif\n")

            # Close header guard
            f.write("#endif")
    except OSError:
        print(f"[FATAL] Failed to open header file for writing: {args.output}")
        return


def main():
    parser = ArgumentParser()
    parser.add_argument("input", nargs="?", type=str,
                        help="JSON file containing register information")
    parser.add_argument("output", nargs="?", type=str,
                        help="C header file output path (optional)")
    args = parser.parse_args(argv[1:])

    load_regs_json(args)


main()
