#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include "app.h"

/* 1:ERROR, 2:DEBUG, 3:TEST */
#define LOG_LEVEL 3

#define RIGHT 1
#define LEFT  2

#ifndef MAKE_BT_DISABLE
#define LOG_D_TEST(format, ...)\
    if(LOG_LEVEL >= 3){\
	fprintf(bt, "%s:L%-5d\n[TEST ]: ", __FILE__, __LINE__);\
	fprintf(bt, format, ##__VA_ARGS__);\
    }

#define LOG_D_DEBUG(format, ...)\
    if(LOG_LEVEL >= 2){\
	fprintf(bt, "%s:L%-5d\n[DEBUG]: ", __FILE__, __LINE__);\
	fprintf(bt, format, ##__VA_ARGS__);\
    }

#define LOG_D_ERROR(format, ...)\
    if(LOG_LEVEL >= 1){\
	fprintf(bt, "%s:L%-5d\n[ERROR]: ", __FILE__, __LINE__);\
	fprintf(bt, format, ##__VA_ARGS__);\
    }
#else
#define LOG_D_TEST(format, ...)
#define LOG_D_DEBUG(format, ...)
#define LOG_D_ERROR(format, ...)
#endif

FILE *bt = NULL;

#endif
