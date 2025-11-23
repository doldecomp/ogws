#ifndef MSL_CTYPE_H
#define MSL_CTYPE_H
#include <types.h>
#include <locale.h>
#ifdef __cplusplus
extern "C" {
#endif


#define ctype_alpha 0x0001
#define ctype_blank 0x0002
#define ctype_cntrl 0x0004
#define ctype_digit 0x0008
#define ctype_graph 0x0010
#define ctype_lower 0x0020
#define ctype_print 0x0040
#define ctype_punct 0x0080
#define ctype_space 0x0100
#define ctype_upper 0x0200
#define ctype_xdigit 0x0400

#define ctype_alnum (ctype_alpha | ctype_digit)

static inline int isalnum(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_alnum);
}

static inline int isalpha(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_alpha);
}

static inline int isblank(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_blank);
}

static inline int iscntrl(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_cntrl);
}

static inline int isdigit(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_digit);
}

static inline int isgraph(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_graph);
}

static inline int islower(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_lower);
}

static inline int isprint(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_print);
}

static inline int ispunct(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_punct);
}

static inline int isspace(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_space);
}

static inline int isupper(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_upper);
}

static inline int isxdigit(int c) {
    return (c < 0 || c >= 256)
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] &
                       ctype_xdigit);
}

static inline int tolower(int c) {
    return (c < 0 || c >= 256)
               ? c
               : (int)(&_current_locale)->ctype_cmpt_ptr->lower_map_ptr[c];
}

static inline int toupper(int c) {
    return (c < 0 || c >= 256)
               ? c
               : (int)(&_current_locale)->ctype_cmpt_ptr->upper_map_ptr[c];
}

#ifdef __cplusplus
}
#endif
#endif
