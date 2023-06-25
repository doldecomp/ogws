#####################################################################
# NOTE: This is a modified version of decompctx.py.                 #
# Originally written by the PrimeDecomp team:                       #
# https://github.com/PrimeDecomp/prime/blob/main/tools/decompctx.py #
#####################################################################

from sys import platform, argv
from subprocess import Popen, PIPE
from os import walk, path
from os.path import join, exists, relpath, dirname, abspath, realpath
from re import compile

INCLUDE_DIR = "include/"
SRC_DIR = "src/"
STL_INCLUDE_DIR = "include/msl"
RVL_INCLUDE_DIR = "include/revolution"
TYPES_H_PATH = f"{RVL_INCLUDE_DIR}/types.h"
SCRIPT_DIR = dirname(realpath(__file__))
ROOT_DIR = abspath(join(SCRIPT_DIR, ".."))
SRC_DIR = join(ROOT_DIR, "src")

INCLUDE_PATTERN = compile(r'^#include\s*[<"](.+?)[>"]$')
GUARD_PATTERN = compile(r"^#ifndef\s+(.*)$")
GUARD_IFDEF_PATTERN = compile(r"^#ifdef\s+(.*)$")
GUARD_ELSE_PATTERN = compile(r"^#else\s*$")
GUARD_END_PATTERN = compile(r"^#endif\s*$")

DEFINES = set()


def main():
    if len(argv) < 2:
        print("[FATAL] Please supply a source file name.")
        exit(0)

    src_file = resolve_src_name(argv[1])

    print()
    print("[INFO] Generating context...")

    # Generate context file
    with open("ctx.c", "w+") as f:
        print(import_c_file(src_file), file=f)
    print("[INFO] Context written to ./ctx.c!")

    # Copy to clipboard if on Windows
    try:
        with open("ctx.c", "r") as f:
            copy_to_clip("".join(f.readlines()))
    except OSError:
        # Not a big deal really
        pass


def copy_to_clip(text: str):
    if platform == "win32":
        Popen(['CLIP'], stdin=PIPE).communicate(text.encode())
        print("[INFO] Copied to clipboard!")


def resolve_src_name(src_file) -> str:
    # Is the source file an absolute path?
    try:
        with open(src_file, "r") as tmp:
            return src_file
    # Relative path to some directory, try to find that directory
    except OSError:
        print(
            f"[INFO] Source file ({src_file}) appears to be a relative path.")
        print("[INFO] Attempting to resolve to an absolute path...")

        # Convert any path separators in the source file to what is expected
        src_file = src_file.replace("/", path.sep)
        src_file = src_file.replace("\\", path.sep)

        for _root, _dirs, _files in walk(SRC_DIR):
            for file in _files:
                p = join(_root, file)
                # Case sensitive check
                found = p.endswith(src_file)
                # Case insensitive check (on Windows)
                if platform == "win32":
                    found = found or p.lower().endswith(src_file.lower())

                if found:
                    print(
                        f"[INFO] I think you are referring to this file: {p}")
                    return p
        print("[FATAL] Sorry, but I don't know what file you want.")
        exit()


def import_h_file(in_file, r_path) -> str:
    # Only non-STL relative include should be types.h
    if in_file == "revolution/types.h" or in_file == "types.h" and exists(TYPES_H_PATH):
        return import_h_file_as_c(TYPES_H_PATH)

    # Try root directory
    rel_path = join(ROOT_DIR, r_path, in_file)
    if exists(rel_path):
        return import_h_file_as_c(rel_path)

    # Try root include directory
    inc_path = join(INCLUDE_DIR, in_file)
    if exists(inc_path):
        return import_h_file_as_c(inc_path)

    # Try root include directory
    inc_path = join(STL_INCLUDE_DIR, in_file)
    if exists(inc_path):
        return import_h_file_as_c(inc_path)

    print(f"Failed to locate header: {in_file}")
    return ""


def import_h_file_as_c(in_file) -> str:
    in_file = relpath(in_file, ROOT_DIR)
    out_text = ""

    with open(in_file) as file:
        for idx, line in enumerate(file):
            # Header guard
            guard_match = GUARD_PATTERN.match(line.strip())
            if guard_match:
                # At the beginning of the file = actually a header guard
                if idx == 0:
                    if guard_match[1] in DEFINES:
                        break
                    DEFINES.add(guard_match[1])

            # Sub-include
            include_match = INCLUDE_PATTERN.match(line.strip())
            if include_match:
                out_text += f'/* "{in_file}" line {idx} "{include_match[1]}" */\n'
                out_text += import_h_file(include_match[1], dirname(in_file))
                out_text += f'/* end "{include_match[1]}" */\n'
            # File text
            else:
                out_text += line

    return out_text


def import_c_file(in_file) -> str:
    in_file = relpath(in_file, ROOT_DIR)
    out_text = ""

    with open(in_file) as file:
        for idx, line in enumerate(file):
            # Sub-include
            include_match = INCLUDE_PATTERN.match(line.strip())
            if include_match:
                out_text += f'/* "{in_file}" line {idx} "{include_match[1]}" */\n'
                out_text += import_h_file(include_match[1], dirname(in_file))
                out_text += f'/* end "{include_match[1]}" */\n'

    return out_text


main()
