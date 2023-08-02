#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include "app.h"

#define LOG_LEVEL 2 /* 1:ERROR, 2:DEBUG */

#ifndef MAKE_BT_DISABLE
#define LOG_D_DEBUG(format, ...)\
    if(LOG_LEVEL >= 2){\
	fprintf(bt, "%s:L%-5d\n[DEBUG]: \r\n", __FILE__, __LINE__);\
	fprintf(bt, format, ##__VA_ARGS__);\
    }

#define LOG_D_ERROR(format, ...)\
    if(LOG_LEVEL >= 1){\
	fprintf(bt, "%s:L%-5d\n[ERROR]: ", __FILE__, __LINE__);\
	fprintf(bt, format, ##__VA_ARGS__);\
    }
#else
#define LOG_D_DEBUG(format, ...)\
    if(LOG_LEVEL >= 2){\
	printf("%s:L%-5d\n[DEBUG]: ", __FILE__, __LINE__);\
	printf(format, ##__VA_ARGS__);\
    }

#define LOG_D_ERROR(format, ...)\
    if(LOG_LEVEL >= 1){\
	fprintf("%s:L%-5d\n[ERROR]: ", __FILE__, __LINE__);\
	fprintf(format, ##__VA_ARGS__);\
    }
#endif

FILE *bt = NULL;

#endif