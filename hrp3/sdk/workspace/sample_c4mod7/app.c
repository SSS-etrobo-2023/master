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
    right_motor     = EV3_PORT_B;
    centar_motor     = EV3_PORT_D;
    

static int      bt_cmd = 0;     /* Bluetoothコマンド 1:リモートスタート */
//static FILE     *bt = NULL;     /* Bluetoothファイルハンドル */
int flag_turn;

int color_reflect;

//turn_mode =1:右旋回モード
//          =0:左旋回モード
int turn_mode=0;

#define REFLECT_LOG_SIZE 255



//serach_mode =0 :通常走行モード
//
int serach_mode=0;

//反射データを記録するための配列
uint8_t reflect_log[REFLECT_LOG_SIZE];
//記録位置のポインタ
int reflect_ptr=0;

/* 下記のマクロは個体/環境に合わせて変更する必要があります */
/* sample_c1マクロ */
#define LIGHT_WHITE  23         /* 白色の光センサ値 */
#define LIGHT_BLACK  0          /* 黒色の光センサ値 */
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

#define MOTOR_POWER_STRONG 40
#define MOTOR_POWER_WEAK 20

/*コースのタイプ　
1  :右回り
-1 :左回り
*/
#define COURSE_TYPE 1

#define CROSSED_LINE 1

/* 関数プロトタイプ宣言 */
static int sonar_alert(void);
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

    int black_detect_count=0;


    //配列初期化
    for(int i=0;i<REFLECT_LOG_SIZE;i++){
        reflect_log[i]=0;


    }

    //線検知フラグ
    int detected_flag =0;
    /* LCD画面表示 */
    ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);

    _log("HackEV sample_c4");
    if (_LEFT)  _log("Left course:");
    else        _log("Right course:");

    /* センサー入力ポートの設定 */
    ev3_sensor_config(sonar_sensor, ULTRASONIC_SENSOR);
    ev3_sensor_config(color_sensor, COLOR_SENSOR);
    ev3_color_sensor_get_reflect(color_sensor); /* 反射率モード */
    ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
    /* モーター出力ポートの設定 */
    ev3_motor_config(left_motor, LARGE_MOTOR);
    ev3_motor_config(right_motor, LARGE_MOTOR);
    ev3_motor_config(centar_motor, LARGE_MOTOR);

    //テールモーター固定
    ev3_motor_stop(centar_motor,true);

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

    if (_bt_enabled)
    {
        fprintf(bt, "Bluetooth Remote Start: Ready.\n", EV3_SERIAL_BT);
        fprintf(bt, "send '1' to start\n", EV3_SERIAL_BT);
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

    /* 走行モーターエンコーダーリセット */
    ev3_motor_reset_counts(left_motor);
    ev3_motor_reset_counts(right_motor);

    ev3_led_set_color(LED_GREEN); /* スタート通知 */

    /**
    * Main loop
    */
    while(1)
    {
        if (ev3_button_is_pressed(BACK_BUTTON)) break;

        
        //if (sonar_alert() == 1) /* 障害物検知 */
        //{
        //    forward = turn = 0; /* 障害物を検知したら停止 */
        //}
        if(0){

        }
        else
        {
            forward = 30; /* 前進命令 */

            color_reflect = ev3_color_sensor_get_reflect(color_sensor);
            //LOG_D_DEBUG("color reflect= %d\n", color_reflect);

            //配列にデータを保存
            reflect_log[reflect_ptr]=color_reflect;
            LOG_D_DEBUG("**reflect_log[%d]= %d\n", reflect_ptr, reflect_log[reflect_ptr]);

            reflect_ptr++;

            if(reflect_ptr >= REFLECT_LOG_SIZE){
                reflect_ptr=0;

            }

            //ラインを測定
            //ev3_color_sensor_get_reflectの値は白いほど大きく、黒いほど0に近い
            if (ev3_color_sensor_get_reflect(color_sensor) >= (LIGHT_WHITE + LIGHT_BLACK)/2)
            {
                //白部分の上の時
                ev3_led_set_color(LED_GREEN);

                LOG_D_DEBUG("Line detected\n");
                
                if(black_detect_count>300||black_detect_count==0){
                    black_detect_count=0;
                    turn_mode=1;
                }

            }
            else
            {
                //黒部分の上の時
                ev3_led_set_color(LED_ORANGE);
                LOG_D_DEBUG("Line is not detected\n");
                turn_mode=0;
                

            }
        }


        

        if(turn_mode==1){
            motor_ser_two_motor(20,30);

        }else if(turn_mode==0){

            motor_ser_two_motor(40,10);
            black_detect_count++;

        }
        
        tslp_tsk(4 * 1000U); /* 4msec周期起動 */


    }


    if (_bt_enabled)
    {
        ter_tsk(BT_TASK);
        fclose(bt);
    }


    ext_tsk();
}
//*****************************************************************************
// 関数名 : motor_set_two_motor
// 引数 :   LeftMotorPower   :左モーターパワー
//          RightMotorPower  :右モーターパワー
// 返り値 : なし
// 概要 :　
//*****************************************************************************
void motor_set_two_motor(int LeftMotorPower, int RightMotorPower){

    ev3_motor_set_power(EV3_PORT_C, LeftMotorPower);
    ev3_motor_set_power(EV3_PORT_B, RightMotorPower);

    
}

//*****************************************************************************
// 関数名 : motor_steer_by_ratio
// 引数 :   steerRatio モーター回転比率　(50~ -50)
//          power      モーターパワー(0 ~100)
// 返り値 : なし
// 概要 :　
//*****************************************************************************
void motor_ser_two_motor(int LeftMotorPower, int RightMotorPower){

    ev3_motor_set_power(EV3_PORT_C, LeftMotorPower);
    ev3_motor_set_power(EV3_PORT_B, RightMotorPower);

    
}

//*****************************************************************************
// 関数名 : trace_cource_by_cource_type
// 引数 :   cource_type :1  :右回り  -1 :左回り
//          detected :1　線検知　0 :検知なし
// 返り値 : なし
// 概要 :　
//*****************************************************************************
void trace_cource_by_cource_type(int cource_type, int detected){

    //右回りコース
    if(cource_type==1){
        
        if(detected==1){

            motor_steer_by_ratio(-20,20);

        }else{
            motor_steer_by_ratio(20,20);


        }


    }
    else if(cource_type== -1){  //左回りコース

        if(detected==1){

            motor_steer_by_ratio(-20,20);

        }else{
            motor_steer_by_ratio(20,20);


        }


    }




}

//*****************************************************************************
// 関数名 : motor_stop
// 引数 :   
// 返り値 : なし
// 概要 :　車体を停止する
//*****************************************************************************
void motor_stop(){
    ev3_motor_stop(EV3_PORT_B,true);
    ev3_motor_stop(EV3_PORT_C,true);

}
//*****************************************************************************
// 関数名 : motor_inertia
// 引数 :   
// 返り値 : なし
// 概要 :　慣性走行する
//*****************************************************************************
void motor_inertia(){

    ev3_motor_stop(EV3_PORT_B,false);
    ev3_motor_stop(EV3_PORT_C,false);

}


//*****************************************************************************
// 関数名 : motor_steer
// 引数 :   flagturn(1- 右旋回, -1- 左旋回) motor_power=モーターパワー(-100~100)
// 返り値 : なし
// 概要 :　
//*****************************************************************************
void motor_steer(int flag_turn, int motor_power){
    if(flag_turn==1){
            //左モーターを動かす
            ev3_motor_set_power(EV3_PORT_C,motor_power);
            ev3_motor_stop(EV3_PORT_B,true);
            LOG_D_DEBUG("Left turn\r\n");
            

        }else if(flag_turn==-1){
            //右モーターを動かす
            ev3_motor_set_power(EV3_PORT_B,motor_power);
            ev3_motor_stop(EV3_PORT_C,true);
            LOG_D_DEBUG("Right turn\r\n");
            
        }
}

//*****************************************************************************
// 関数名 : motor_steer_by_degree
// 引数 :   motor_number=モーターナンバー(左モーター:1 右モーター: -1)　
//          motor_degree=回転角(°)
//          motor_power=モーターパワー(-100~100)
// 返り値 : なし
// 概要 :　
//*****************************************************************************
void motor_steer_by_degree(int flag_turn, int motor_degree, int motor_power){
    if(flag_turn==1){
            //左モーターを動かす
            ev3_motor_rotate(EV3_PORT_B, motor_degree, motor_power, true);
            ev3_motor_stop(EV3_PORT_B,false);
            //LOG_D_DEBUG("Left turn\r\n");
            

        }else if(flag_turn==-1){
            //右モーターを動かす
            ev3_motor_rotate(EV3_PORT_C, motor_degree, motor_power, true);
            ev3_motor_stop(EV3_PORT_C,false);
            //LOG_D_DEBUG("Left turn\r\n");
            
        }
}

//*****************************************************************************
// 関数名 : motor_steer_by_ratio
// 引数 :   steerRatio モーター回転比率　(50~ -50)
//          power      モーターパワー(0 ~100)
// 返り値 : なし
// 概要 :　
//*****************************************************************************
void motor_steer_by_ratio(int steerRatio, int power){

    int const_steer_ratio=30;

    ev3_motor_set_power(EV3_PORT_C, (int)(const_steer_ratio+ steerRatio*power/100));
    ev3_motor_set_power(EV3_PORT_B, (int)(const_steer_ratio- steerRatio*power/100));
    LOG_D_DEBUG("C POWER= %d\n", (int)(const_steer_ratio+ steerRatio*power/100));
    LOG_D_DEBUG("B POWER= %d\n", (int)(const_steer_ratio- steerRatio*power/100));


    
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