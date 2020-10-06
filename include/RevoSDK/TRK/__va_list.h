#ifndef REVOSDK_TRK___VA_LIST
#define REVOSDK_TRK___VA_LIST

typedef struct __va_list_struct {
	char gpr;
	char fpr;
	char * input_arg_area;
	char * reg_save_area;
} va_list[1];

#endif