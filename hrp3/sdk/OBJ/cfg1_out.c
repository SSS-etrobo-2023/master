/* cfg1_out.c */
#define TOPPERS_CFG1_OUT
#include "kernel/kernel_int.h"
#line 1 "../common/ev3api/ev3api.cfg"
#include "api.cfg.h"
#line 3 "../workspace/sample_c4/app.cfg"
#include "app.h"

#ifdef INT64_MAX
  typedef int64_t signed_t;
  typedef uint64_t unsigned_t;
#else
  typedef int32_t signed_t;
  typedef uint32_t unsigned_t;
#endif

#include "target_cfg1_out.h"

const uint32_t TOPPERS_magic_number = 0x12345678;
const uint32_t TOPPERS_sizeof_signed_t = sizeof(signed_t);
const uint32_t TOPPERS_sizeof_intptr_t = sizeof(intptr_t);
const uint32_t TOPPERS_sizeof_char_ptr_t = sizeof(char *);

const unsigned_t TOPPERS_cfg_CHAR_BIT = (unsigned_t)(CHAR_BIT);
const signed_t TOPPERS_cfg_SCHAR_MAX = (signed_t)(SCHAR_MAX);
const signed_t TOPPERS_cfg_SCHAR_MIN = (signed_t)(SCHAR_MIN);
const unsigned_t TOPPERS_cfg_UCHAR_MAX = (unsigned_t)(UCHAR_MAX);
const signed_t TOPPERS_cfg_CHAR_MAX = (signed_t)(CHAR_MAX);
const signed_t TOPPERS_cfg_CHAR_MIN = (signed_t)(CHAR_MIN);
const signed_t TOPPERS_cfg_SHRT_MAX = (signed_t)(SHRT_MAX);
const signed_t TOPPERS_cfg_SHRT_MIN = (signed_t)(SHRT_MIN);
const unsigned_t TOPPERS_cfg_USHRT_MAX = (unsigned_t)(USHRT_MAX);
const signed_t TOPPERS_cfg_INT_MAX = (signed_t)(INT_MAX);
const signed_t TOPPERS_cfg_INT_MIN = (signed_t)(INT_MIN);
const unsigned_t TOPPERS_cfg_UINT_MAX = (unsigned_t)(UINT_MAX);
const signed_t TOPPERS_cfg_LONG_MAX = (signed_t)(LONG_MAX);
const signed_t TOPPERS_cfg_LONG_MIN = (signed_t)(LONG_MIN);
const unsigned_t TOPPERS_cfg_ULONG_MAX = (unsigned_t)(ULONG_MAX);
#if defined(SIL_ENDIAN_BIG)
const signed_t TOPPERS_cfg_SIL_ENDIAN_BIG = (signed_t)(true);
#endif
#if defined(SIL_ENDIAN_LITTLE)
const signed_t TOPPERS_cfg_SIL_ENDIAN_LITTLE = (signed_t)(true);
#endif
const unsigned_t TOPPERS_cfg_TA_NULL = (unsigned_t)(TA_NULL);
const unsigned_t TOPPERS_cfg_TA_TPRI = (unsigned_t)(TA_TPRI);
const unsigned_t TOPPERS_cfg_TA_CEILING = (unsigned_t)(TA_CEILING);
const signed_t TOPPERS_cfg_TMIN_TPRI = (signed_t)(TMIN_TPRI);
const signed_t TOPPERS_cfg_TMAX_TPRI = (signed_t)(TMAX_TPRI);
const signed_t TOPPERS_cfg_TMIN_DPRI = (signed_t)(TMIN_DPRI);
const signed_t TOPPERS_cfg_TMAX_DPRI = (signed_t)(TMAX_DPRI);
const unsigned_t TOPPERS_cfg_TNFY_HANDLER = (unsigned_t)(TNFY_HANDLER);
const unsigned_t TOPPERS_cfg_TNFY_SETVAR = (unsigned_t)(TNFY_SETVAR);
const unsigned_t TOPPERS_cfg_TNFY_INCVAR = (unsigned_t)(TNFY_INCVAR);
const unsigned_t TOPPERS_cfg_TNFY_ACTTSK = (unsigned_t)(TNFY_ACTTSK);
const unsigned_t TOPPERS_cfg_TNFY_WUPTSK = (unsigned_t)(TNFY_WUPTSK);
const unsigned_t TOPPERS_cfg_TNFY_SIGSEM = (unsigned_t)(TNFY_SIGSEM);
const unsigned_t TOPPERS_cfg_TNFY_SETFLG = (unsigned_t)(TNFY_SETFLG);
const unsigned_t TOPPERS_cfg_TNFY_SNDDTQ = (unsigned_t)(TNFY_SNDDTQ);
const unsigned_t TOPPERS_cfg_TENFY_SETVAR = (unsigned_t)(TENFY_SETVAR);
const unsigned_t TOPPERS_cfg_TENFY_INCVAR = (unsigned_t)(TENFY_INCVAR);
const unsigned_t TOPPERS_cfg_TENFY_ACTTSK = (unsigned_t)(TENFY_ACTTSK);
const unsigned_t TOPPERS_cfg_TENFY_WUPTSK = (unsigned_t)(TENFY_WUPTSK);
const unsigned_t TOPPERS_cfg_TENFY_SIGSEM = (unsigned_t)(TENFY_SIGSEM);
const unsigned_t TOPPERS_cfg_TENFY_SETFLG = (unsigned_t)(TENFY_SETFLG);
const unsigned_t TOPPERS_cfg_TENFY_SNDDTQ = (unsigned_t)(TENFY_SNDDTQ);

#define TDOM_APP 1

#line 4 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_static_api_1 = 1;
#define APP_INIT_TASK	(<>)
#line 4 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_1 = (unsigned_t)(TA_ACT);
#line 4 "../common/ev3api/ev3api.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_1 = (signed_t)(TPRI_APP_INIT_TASK);
#line 4 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_1 = (unsigned_t)(STACK_SIZE);

#line 7 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_static_api_2 = 2;
#line 7 "../common/ev3api/ev3api.cfg"
const char * TOPPERS_cfg_valueof_modname_2 = (char *)("ev3api.o");

#line 8 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_static_api_3 = 3;
#line 8 "../common/ev3api/ev3api.cfg"
const char * TOPPERS_cfg_valueof_modname_3 = (char *)("ev3api_battery.o");

#line 9 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_static_api_4 = 4;
#line 9 "../common/ev3api/ev3api.cfg"
const char * TOPPERS_cfg_valueof_modname_4 = (char *)("ev3api_brick.o");

#line 10 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_static_api_5 = 5;
#line 10 "../common/ev3api/ev3api.cfg"
const char * TOPPERS_cfg_valueof_modname_5 = (char *)("ev3api_fs.o");

#line 11 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_static_api_6 = 6;
#line 11 "../common/ev3api/ev3api.cfg"
const char * TOPPERS_cfg_valueof_modname_6 = (char *)("ev3api_newlib.o");

#line 12 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_static_api_7 = 7;
#line 12 "../common/ev3api/ev3api.cfg"
const char * TOPPERS_cfg_valueof_modname_7 = (char *)("ev3api_lcd.o");

#line 13 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_static_api_8 = 8;
#line 13 "../common/ev3api/ev3api.cfg"
const char * TOPPERS_cfg_valueof_modname_8 = (char *)("ev3api_motor.o");

#line 14 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_static_api_9 = 9;
#line 14 "../common/ev3api/ev3api.cfg"
const char * TOPPERS_cfg_valueof_modname_9 = (char *)("ev3api_sensor.o");

#line 15 "../common/ev3api/ev3api.cfg"
const unsigned_t TOPPERS_cfg_static_api_10 = 10;
#line 15 "../common/ev3api/ev3api.cfg"
const char * TOPPERS_cfg_valueof_modname_10 = (char *)("ev3api_speaker.o");

#line 3 "../common/app_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_11 = 11;
#line 3 "../common/app_common.cfg"
const char * TOPPERS_cfg_valueof_modname_11 = (char *)("log_output.o");

#line 4 "../common/app_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_12 = 12;
#line 4 "../common/app_common.cfg"
const char * TOPPERS_cfg_valueof_modname_12 = (char *)("vasyslog.o");

#line 5 "../common/app_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_13 = 13;
#line 5 "../common/app_common.cfg"
const char * TOPPERS_cfg_valueof_modname_13 = (char *)("t_perror.o");

#line 6 "../common/app_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_14 = 14;
#line 6 "../common/app_common.cfg"
const char * TOPPERS_cfg_valueof_modname_14 = (char *)("strerror.o");

#line 7 "../common/app_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_15 = 15;
#line 7 "../common/app_common.cfg"
const char * TOPPERS_cfg_valueof_modname_15 = (char *)("libc.a");

#line 6 "../workspace/sample_c4/app.cfg"
const unsigned_t TOPPERS_cfg_static_api_16 = 16;
#define MAIN_TASK	(<>)
#line 6 "../workspace/sample_c4/app.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_16 = (unsigned_t)(TA_ACT);
#line 6 "../workspace/sample_c4/app.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_16 = (signed_t)(TMIN_APP_TPRI + 1);
#line 6 "../workspace/sample_c4/app.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_16 = (unsigned_t)(STACK_SIZE);

#line 7 "../workspace/sample_c4/app.cfg"
const unsigned_t TOPPERS_cfg_static_api_17 = 17;
#define BT_TASK	(<>)
#line 7 "../workspace/sample_c4/app.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_17 = (unsigned_t)(TA_NULL);
#line 7 "../workspace/sample_c4/app.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_17 = (signed_t)(TMIN_APP_TPRI + 2);
#line 7 "../workspace/sample_c4/app.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_17 = (unsigned_t)(STACK_SIZE);

#line 10 "../workspace/sample_c4/app.cfg"
const unsigned_t TOPPERS_cfg_static_api_18 = 18;
#line 10 "../workspace/sample_c4/app.cfg"
const char * TOPPERS_cfg_valueof_modname_18 = (char *)("app.o");

