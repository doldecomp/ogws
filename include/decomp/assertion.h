/**
 * Non-intrusive assertion macros for matching decomp
 *
 * References:
 * https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
 * http://jhnet.co.uk/articles/cpp_magic
 */

#ifndef DECOMP_ASSERTION_H
#define DECOMP_ASSERTION_H

// clang-format off
//
// >> Description <<
//
// The DECOMP_ASSERT provides a way for matching builds to force arbitrary line numbers,
// without needing intrusive changes, such as "_LINE" variations of every assertion macro.
//
// If a specific line number is desired, use the LINE(no) macro to force it.
// This macro must be the first argument of the assertion to be recognized.
//
// Additionally, the LINES(...) macro provided in this header allows for a single assertion
// to take different line numbers based on the build configuration.
//
// In nonmatching builds, the LINE family of macros is ignored for accuracy.
// DECOMP_ASSERT will instead provide the true source location.
//
// Due to this macro's implementation, unwanted macro expansion may occur.
// To preserve an expression
//
// >> Parameters <<
//
// The 'assert_impl' parameter is the name of the assertion implementation.
// It must be a function-like macro that accepts at least the following parameters: (file, line).
//   - file:     The name of the source file where the macro was expanded.
//
//   - line:     The location in the source file where the macro was expanded.
//               The LINE/LINES macros are provided to override this value.
//
//   - ...:      Any variadic arguments provided at the DECOMP_ASSERT invocation.
//
// The 'lines_impl' parameter is the name of the line tuple evaluator.
// It must be a function-like macro that accepts multiple line numbers.
// It is responsible for picking the correct line number, often based on the build configuration.
//
// For code where this feature should be disabled, specify LINES_DUMMY.
// Doing so will cause LINES(...) to produce a syntax error.
//
// >> Example <<
//
//     // keep DECOMP_ASSERT on the same line to stay accurate in non-matching builds!
//     #define MY_ASSERT(...) DECOMP_ASSERT(MY_ASSERT_IMPL, MY_LINES, __VA_ARGS__)
//
//     #define MY_ASSERT_IMPL(file, line, expr)
//         if (!expr) { Panic("Assertion failed: %s", #expr); }
//
//     // choose Rev 1 line number for this build
//     #define MY_LINES(rev0, rev1) rev1
//
//     MY_ASSERT(LINE(123), num > 0) expands to:
//         MY_ASSERT_IMPL("code.cpp", 123, "num > 0", num > 0)
//
// clang-format on

/******************************************************************************
 *
 * Public macros
 *
 ******************************************************************************/

/**
 * @brief Performs a runtime assertion
 */
// clang-format off
// The formatting looks weird, but we need to get the correct source location!
#define DECOMP_ASSERT(assert_impl, lines_impl, ...) AA_FWD(assert_impl, AA_EVAL_ARGS(__LINE__, lines_impl, __VA_ARGS__, AA_DUMMY))
// clang-format on

/**
 * @brief Forces a specific source line number in an assertion
 * @note This macro must come first in the DECOMP_ASSERT argument list.
 */
#define LINE(no) (AA_LINE, no)

/**
 * @brief Forces a specific source line number tuple in an assertion
 * @note This macro must come first in the DECOMP_ASSERT argument list.
 * @note You will need to define the appropriate *_LINES handler macro.
 */
#define LINES(no1, ...) (AA_LINES, (no1, __VA_ARGS__))

/**
 * @brief Dummy macro available for when line number tuples are not supported
 */
#define LINES_DUMMY(...) ~

/******************************************************************************
 *
 * Utility macros
 *
 ******************************************************************************/

/**
 * @brief Stringitizes a token
 * @details Macro expansion is often required, so the argument is forwarded.
 */
#define AA_STR(x) AA_STR_IMPL(x)
#define AA_STR_IMPL(x) #x

/**
 * @brief Concatenates two tokens
 * @details Macro expansion is often required, so the arguments are forwarded.
 */
#define AA_CAT(first, second) AA_CAT_IMPL(first, second)
#define AA_CAT_IMPL(first, second) first##second

/**
 * @brief Invokes the specified macro after an expansion pass
 */
#define AA_FWD(macro, tuple) macro tuple

/**
 * @brief Grabs the specified variadic argument
 * @note Dummy arguments make sure the argument list is always large enough.
 */
#define AA_1ST_IMPL(first, ...) first
#define AA_1ST(...) AA_1ST_IMPL(__VA_ARGS__, ~)
#define AA_2ND_IMPL(first, second, ...) second
#define AA_2ND(...) AA_2ND_IMPL(__VA_ARGS__, ~, ~)

/**
 * @brief Pattern matching primitives
 * @details AA_BOOL can be used to evaluate boolean logic, where TRUE cases
 * should expand to two tokens (AA_PROBE()).
 *
 * @note The '~' token is chosen specifically to help catch usage errors.
 */
#define AA_PROBE(...) ~, 1,
#define AA_BOOL(...) AA_2ND(__VA_ARGS__, 0, )
#define AA_TRUE 1
#define AA_FALSE 0

/**
 * @brief Tests whether the input argument is surrounded by parentheses
 * @details An argument beginning with parentheses will invoke AA_PROBE.
 */
#define AA_IS_IN_PARENS(x) AA_BOOL(AA_PROBE x)

/**
 * @brief Performs boolean logic
 * @note Assumes the 'expr' argument expands to either 0 or 1.
 */
#define AA_IF(expr, if_true, if_false) AA_CAT(AA_IF_, expr)(if_true, if_false)
#define AA_IF_0(if_true, if_false) if_false
#define AA_IF_1(if_true, if_false) if_true

/**
 * @brief Dummy parameter to signal the end of the variadic argument list
 * @details Keeps the syntax valid when AA_EVAL_ARGS receives only a single
 * argument in __VA_ARGS__.
 */
#define AA_DUMMY ~

/**
 * @brief Removes the last element from a variadic argument list
 * @note Assumes the list's size is <= 10.
 */
// clang-format off
#define AA_DROP_LAST(...)                                                      \
    AA_DROP_LAST_SELECT(                                                       \
        __VA_ARGS__,                                                           \
        AA_DROP_LAST_10,                                                       \
        AA_DROP_LAST_9,                                                        \
        AA_DROP_LAST_8,                                                        \
        AA_DROP_LAST_7,                                                        \
        AA_DROP_LAST_6,                                                        \
        AA_DROP_LAST_5,                                                        \
        AA_DROP_LAST_4,                                                        \
        AA_DROP_LAST_3,                                                        \
        AA_DROP_LAST_2,                                                        \
        AA_DUMMY,                                                              \
        AA_DUMMY                                                               \
    )(__VA_ARGS__)

// Variadic arguments will shift the AA_DROP_LAST* macros
#define AA_DROP_LAST_SELECT(for1, for2, for3, for4, for5, for6, for7, for8, for9, for10, selected, ...) selected
#define AA_DROP_LAST_10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) p1, p2, p3, p4, p5, p6, p7, p8, p9
#define AA_DROP_LAST_9(p1, p2, p3, p4, p5, p6, p7, p8, p9)       p1, p2, p3, p4, p5, p6, p7, p8
#define AA_DROP_LAST_8(p1, p2, p3, p4, p5, p6, p7, p8)           p1, p2, p3, p4, p5, p6, p7
#define AA_DROP_LAST_7(p1, p2, p3, p4, p5, p6, p7)               p1, p2, p3, p4, p5, p6
#define AA_DROP_LAST_6(p1, p2, p3, p4, p5, p6)                   p1, p2, p3, p4, p5
#define AA_DROP_LAST_5(p1, p2, p3, p4, p5)                       p1, p2, p3, p4
#define AA_DROP_LAST_4(p1, p2, p3, p4)                           p1, p2, p3
#define AA_DROP_LAST_3(p1, p2, p3)                               p1, p2
#define AA_DROP_LAST_2(p1, p2)                                   p1
// clang-format on

/******************************************************************************
 *
 * Assertion implementation details
 *
 ******************************************************************************/

/**
 * @brief Evaluates the specified tuple of assertion arguments
 *
 * This macro evaluates to: (file, line, params...).
 * The assertion parameters preserve their original order.
 *
 * If the first argument is not LINE/LINES, this macro uses __LINE__.
 * Otherwise, this macro uses the hardcoded line number.
 */
// clang-format off
#define AA_EVAL_ARGS(real_line, lines_impl, first, ...)                           \
    AA_IF(                                                                                 \
        /* Test for a valid LINE tag. */                                                   \
        AA_IS_TAG(first),                                                                  \
                                                                                           \
        /* Valid tag, extract the hardcoded line number. */                                \
        (__FILE__, AA_EVAL_TAG(lines_macro, real_line, first), AA_DROP_LAST(__VA_ARGS__)), \
                                                                                           \
        /* Not a tag, use the real source location. */                                     \
        (__FILE__, real_line, AA_DROP_LAST(first, __VA_ARGS__))                            \
    )
// clang-format on

/**
 * @brief Checks if a tag name is valid
 */
// clang-format off
#define AA_IS_TAG(x) \
    AA_IF(                                                                         \
        /* Input must be in parentheses to possibly be a tuple. */                 \
        AA_IS_IN_PARENS(x),                                                        \
                                                                                   \
        /* Pattern match on the tag name. */                                       \
        AA_BOOL(AA_CAT(AA_IS_TAG_, AA_1ST x)),                                     \
                                                                                   \
        /* Can't be a tag if it's not even in parentheses. */                      \
        AA_FALSE                                                                   \
    )

#define AA_IS_TAG_AA_LINE  AA_PROBE()
#define AA_IS_TAG_AA_LINES AA_PROBE()
// clang-format on

/**
 * Avoid hardcoded line numbers in nonmatching builds
 */
// clang-format off
#if defined(NONMATCHING)
#define AA_EVAL_TAG(lines_impl, real_line, tuple) real_line
#else
#define AA_EVAL_TAG(lines_impl, real_line, tuple) AA_CAT(AA_EVAL_TAG_, AA_1ST tuple)(lines_impl, tuple)
#define AA_EVAL_TAG_AA_LINE(lines_impl, tuple)    AA_2ND tuple
#define AA_EVAL_TAG_AA_LINES(lines_impl, tuple)   AA_FWD(lines_impl, AA_2ND tuple)
#endif
// clang-format on

#endif
