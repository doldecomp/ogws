#ifndef MSL_STDARG_H
#define MSL_STDARG_H
#include <RevoSDK/TRK/__va_list.h>
#include <RevoSDK/TRK/__va_arg.h>

#define va_start(ARG,VA_LIST) ((void)ARG,__builtin_va_info(&VA_LIST))
#define va_end(VA_LIST) ((void)VA_LIST)
#define va_arg(VA_LIST,ARG_TYPE) (*(ARG_TYPE*))__va_arg(VA_LIST,_var_arg_typeof(ARG_TYPE))

#endif