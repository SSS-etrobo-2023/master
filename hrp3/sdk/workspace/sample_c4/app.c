/**
 ******************************************************************************
 ** ファイル名 : app.c
 **
 ** 概要 : 二輪差動型ライントレースロボットのTOPPERS/HRP3用Cサンプルプログラム
 **
 ** 注記 : sample_c4 (sample_c3にBluetooth通信リモートスタート機能を追加)
 ******************************************************************************
 **/

#include "ev3api.h"
#include "app.h"
#include "etroboc_ext.h"

#include "common.h"
#include <math.h>

#if defined(BUILD_MODULE)
    #include "module_cfg.h"
#else
    #include "kernel_cfg.h"
#endif

#define DEBUG

#if defined(DEBUG)
    #define _debug(x) (x)
#else
    #define _debug(x)
#endif

#if defined(MAKE_BT_DISABLE)
    static const int _bt_enabled = 0;
#else
    static const int _bt_enabled = 1;
#endif

/**
 * シミュレータかどうかの定数を定義します
 */
#if defined(MAKE_SIM)
    static const int _SIM = 1;
#elif defined(MAKE_EV3)
    static const int _SIM = 0;
#else
    static const int _SIM = 0;
#endif

/**
 * 左コース/右コース向けの設定を定義します
 * デフォルトは左コース(ラインの右エッジをトレース)です
 */
#if defined(MAKE_RIGHT)
    static const int _LEFT = 0;
    #define _EDGE -1
#else
    static const int _LEFT = 1;
    #define _EDGE 1
#endif

/**
 * センサー、モーターの接続を定義します
 */
static const sensor_port_t
    touch_sensor    = EV3_PORT_1,
    color_sensor    = EV3_PORT_2,
    sonar_sensor    = EV3_PORT_3,
    gyro_sensor     = EV3_PORT_4;

static const motor_port_t
    left_motor      = EV3_PORT_C,
    right_motor     = EV3_PORT_B,
    center_motor    = EV3_PORT_A;

static int      bt_cmd = 0;     /* Bluetoothコマンド 1:リモートスタート */
#if 0
static FILE     *bt = NULL;     /* Bluetoothファイルハンドル */
#endif

/* 下記のマクロは個体/環境に合わせて変更する必要があります */
/* sample_c1マクロ */
int LIGHT_WHITE = 42;         /* 白色の光センサ値 */
int LIGHT_BLACK = 2;        /* 黒色の光センサ値 */
/* sample_c2マクロ */
#define SONAR_ALERT_DISTANCE 30 /* 超音波センサによる障害物検知距離[cm] */
/* sample_c4マクロ */
//#define DEVICE_NAME     "ET0"  /* Bluetooth名 sdcard:\ev3rt\etc\rc.conf.ini LocalNameで設定 */
//#define PASS_KEY        "1234" /* パスキー    sdcard:\ev3rt\etc\rc.conf.ini PinCodeで設定 */
#define CMD_START         '1'    /* リモートスタートコマンド */

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

/* 関数プロトタイプ宣言 */
static int sonar_alert(void);//voidは引数なし
static void _syslog(int level, char* text);
static void _log(char* text);
//static void tail_control(signed int angle);
//static void backlash_cancel(signed char lpwm, signed char rpwm, int32_t *lenc, int32_t *renc);

/* メインタスク */
void main_task(intptr_t unused)
{
    signed char forward;      /* 前後進命令 */
    signed char turn;         /* 旋回命令 */
    //signed char pwm_L, pwm_R; /* 左右モーターPWM出力 */

    /* LCD画面表示 */
    ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);

    _log("HackEV sample_c4");
    if (_LEFT)  _log("Left course:");
    else        _log("Right course:");

    /* センサー入力ポートの設定 */
    ev3_sensor_config(sonar_sensor, ULTRASONIC_SENSOR);//第一引数→センサポート番号　第二引数→センサタイプ
    ev3_sensor_config(color_sensor, COLOR_SENSOR);
    ev3_color_sensor_get_reflect(color_sensor); /* 反射率モード */
    ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
    /* モーター出力ポートの設定 */
    ev3_motor_config(left_motor, LARGE_MOTOR);
    ev3_motor_config(right_motor, LARGE_MOTOR);
    ev3_motor_config(center_motor,LARGE_MOTOR);

    if (_bt_enabled)
    {
        /* Open Bluetooth file */
        bt = ev3_serial_open_file(EV3_SERIAL_BT);
        assert(bt != NULL);

        /* Bluetooth通信タスクの起動 */
        act_tsk(BT_TASK);
    }

    ev3_led_set_color(LED_ORANGE); /* 初期化完了通知 */

    _log("Go to the start, ready?");
    if (_SIM)   _log("Hit SPACE bar to start");
    else        _log("Tap Touch Sensor to start");
    LOG_D_DEBUG("initalize complete. ret=%d\n", 1333);
    //ログ出力
    if (_bt_enabled)
    {
        fprintf(bt, "Bluetooth Remote Start: Ready.\n", EV3_SERIAL_BT);
        fprintf(bt, "send '1' to start\n", EV3_SERIAL_BT);
        LOG_D_DEBUG("initalize complete. ret=%d\n", 1);
    }
    
    /* スタート待機 */
    while(1)
    {
        //tail_control(TAIL_ANGLE_STAND_UP); /* 完全停止用角度に制御 */

        if (bt_cmd == 1)
        {
            break; /* リモートスタート */
        }

        if (ev3_touch_sensor_is_pressed(touch_sensor) == 1)
        {
            break; /* タッチセンサが押された */
        }

        tslp_tsk(10 * 1000U); /* 10msecウェイト */
    }
    //モーターストップ
    ev3_motor_stop(EV3_PORT_A,true);

    /* 走行モーターエンコーダーリセット */
    ev3_motor_reset_counts(left_motor);
    ev3_motor_reset_counts(right_motor);

    ev3_led_set_color(LED_GREEN); /* スタート通知 */
    
    tslp_tsk(1000 * 1000U); /* 10msecウェイト */

    //白色取得
    rgb_raw_t white_rgb; 
    tslp_tsk(1000 * 1000U); /* 10msecウェイト */
    while(1)
    {
        //モーターストップからの2回目のタッチ
        if(ev3_touch_sensor_is_pressed(touch_sensor) == 1){
            ev3_color_sensor_get_rgb_raw(color_sensor, &white_rgb);
            LIGHT_WHITE = ev3_color_sensor_get_reflect(color_sensor);
            LOG_D_DEBUG("whitereflect = %d\n",LIGHT_WHITE);
            LOG_D_DEBUG("whitecolor's rgb =%u,%u,%u\n", white_rgb.r,white_rgb.g,white_rgb.b);
            break;
        }
    }
    //黒色取得
    rgb_raw_t black_rgb; 
    tslp_tsk(1000 * 1000U); /* 10msecウェイト */
    while(1)
    {
        //モーターストップからの3回目のタッチ
        if(ev3_touch_sensor_is_pressed(touch_sensor) == 1){
            ev3_color_sensor_get_rgb_raw(color_sensor,&black_rgb);
            LIGHT_BLACK = ev3_color_sensor_get_reflect(color_sensor);
            LOG_D_DEBUG("blackreflect = %d\n",LIGHT_BLACK);
            LOG_D_DEBUG("blackcolor's rgb =%u,%u,%u\n", black_rgb.r,black_rgb.g,black_rgb.b);
            break;
        }
    }
    //青色取得
    rgb_raw_t blue_rgb; 
    tslp_tsk(1000 * 1000U); /* 10msecウェイト */
    while(1)
    {
        //モーターストップからの4回目のタッチ
        if(ev3_touch_sensor_is_pressed(touch_sensor) == 1){
            ev3_color_sensor_get_rgb_raw(color_sensor,&blue_rgb);
            LOG_D_DEBUG("bluecolor's rgb =%u,%u,%u\n", blue_rgb.r,blue_rgb.g,blue_rgb.b);
            break;
        }
    }
    tslp_tsk(1000 * 1000U); /* 10msecウェイト */
    while(1)
    {
        //モーターストップからの5回目のタッチ
        if(ev3_touch_sensor_is_pressed(touch_sensor) == 1){
            break;
        }
    }
    /**
    * Main loop
    */
   float Kp = 2.8;
   float Kd = 0;
   float P;
   float D;
   rgb_raw_t main_rgb;
   float sensor = 0;
   float sensor_dt = 0;
   float curb = 0.0;
   float sensor_diff = (LIGHT_WHITE + LIGHT_BLACK)/2;
   
   float weight;
   int blue_count = 0;
   int is_blue = 0;

   int count = 0;
    while(1)
    {
        if (ev3_button_is_pressed(BACK_BUTTON)) break;

        if (sonar_alert() == 1) /* 障害物検知 */
        {
            forward = turn = 0; /* 障害物を検知したら停止 */
        }
        else
        {
            forward = 25; /* 前進命令 */
            ev3_color_sensor_get_rgb_raw(color_sensor,&main_rgb);

            sensor_dt = sensor_diff -ev3_color_sensor_get_reflect(color_sensor);
            sensor_diff = ev3_color_sensor_get_reflect(color_sensor);

            sensor = ev3_color_sensor_get_reflect(color_sensor);

            //青かどうかの判定
            if(4 * main_rgb.r < main_rgb.b && 2 * main_rgb.g < main_rgb.b && main_rgb.b > blue_rgb.b * 3/4 && is_blue == 0){
                is_blue = 1;
                LOG_D_DEBUG("isBlue");
            }
            if(!((4 * main_rgb.r < main_rgb.b && 2 * main_rgb.g < main_rgb.b && main_rgb.b > blue_rgb.b * 3/4 && is_blue)
            || (main_rgb.r > white_rgb.r/2
            || main_rgb.g > white_rgb.g/2
            || main_rgb.b > white_rgb.b/2))
            && is_blue == 1){
                is_blue = 0;
                blue_count++;
                LOG_D_DEBUG("isNOTBlue");
            }

            //P制御
            if(sensor > LIGHT_WHITE){
                sensor = LIGHT_WHITE;
            }
            P = ((float)(LIGHT_WHITE + LIGHT_BLACK)/2 - sensor);
            //D制御
            D = (sensor_dt);
            //曲がり角度の決定
            curb = Kp * P * (fabsf(P) / ((LIGHT_WHITE + LIGHT_BLACK)/2)) - Kd * D;
            turn = -curb;

            if(blue_count == 3
            ){
                LOG_D_DEBUG("直進");
                turn *= -1;
            }
            if(blue_count == 4 && count < 80
            ){
                LOG_D_DEBUG("直進");
                turn *= 1;
                count++;
            }
            if(blue_count >= 4 && count >= 80){
                turn *= -1;
            }
        }

        /* 左右モータでロボットのステアリング操作を行う */
        if(turn >= 0){
            ev3_motor_set_power(
                left_motor,
                (int)(forward + turn / 4)
            );
            ev3_motor_set_power(
                right_motor,
                (int)(forward - turn * 2 / 3)
            );
        }else{
            ev3_motor_set_power(
                left_motor,
                (int)(forward + turn * 2 / 3)
            );
            ev3_motor_set_power(
                right_motor,
                (int)(forward - turn / 4)
            );
        }
        
        LOG_D_DEBUG("forward = %d",forward);
        LOG_D_DEBUG("turn = %d",turn);
        LOG_D_DEBUG("Kp = %f",Kp * ((float)(LIGHT_WHITE + LIGHT_BLACK)/2 - sensor));
        LOG_D_DEBUG("Kd = %f",- Kd * (sensor_dt));
        LOG_D_DEBUG("test");

        tslp_tsk(4 * 1000U); /* 4msec周期起動 */
    }
   
    ev3_motor_stop(left_motor, false);
    ev3_motor_stop(right_motor, false);

    if (_bt_enabled)
    {
        ter_tsk(BT_TASK);
        fclose(bt);
    }

    ext_tsk();
}

//*****************************************************************************
// 関数名 : sonar_alert
// 引数 : 無し
// 返り値 : 1(障害物あり)/0(障害物無し)
// 概要 : 超音波センサによる障害物検知
//*****************************************************************************
static int sonar_alert(void)
{
    static unsigned int counter = 0;
    static int alert = 0;

    signed int distance;

    if (++counter == 40/4) /* 約40msec周期毎に障害物検知  */
    {
        /*
         * 超音波センサによる距離測定周期は、超音波の減衰特性に依存します。
         * NXTの場合は、40msec周期程度が経験上の最短測定周期です。
         * EV3の場合は、要確認
         */
        distance = ev3_ultrasonic_sensor_get_distance(sonar_sensor);
        if ((distance <= SONAR_ALERT_DISTANCE) && (distance >= 0))
        {
            alert = 1; /* 障害物を検知 */
        }
        else
        {
            alert = 0; /* 障害物無し */
        }
        counter = 0;
    }

    return alert;
}

//*****************************************************************************
// 関数名 : bt_task
// 引数 : unused
// 返り値 : なし
// 概要 : Bluetooth通信によるリモートスタート。 Tera Termなどのターミナルソフトから、
//       ASCIIコードで1を送信すると、リモートスタートする。
//*****************************************************************************
void bt_task(intptr_t unused)
{
    while(1)
    {
        if (_bt_enabled)
        {
            uint8_t c = fgetc(bt); /* 受信 */
            switch(c)
            {
            case '1':
                bt_cmd = 1;
                break;
            default:
                break;
            }
            fputc(c, bt); /* エコーバック */
        }
    }
}

//*****************************************************************************
// 関数名 : _syslog
// 引数 :   int   level - SYSLOGレベル
//          char* text  - 出力文字列
// 返り値 : なし
// 概要 : SYSLOGレベルlebelのログメッセージtextを出力します。
//        SYSLOGレベルはRFC3164のレベル名をそのまま（ERRだけはERROR）
//        `LOG_WARNING`の様に定数で指定できます。
//*****************************************************************************
static void _syslog(int level, char* text){
    static int _log_line = 0;
    if (_SIM)
    {
        syslog(level, text);
    }
    else
    {
        ev3_lcd_draw_string(text, 0, CALIB_FONT_HEIGHT*_log_line++);
    }
}

//*****************************************************************************
// 関数名 : _log
// 引数 :   char* text  - 出力文字列
// 返り値 : なし
// 概要 : SYSLOGレベルNOTICEのログメッセージtextを出力します。
//*****************************************************************************
static void _log(char *text){
    _syslog(LOG_NOTICE, text);
}
