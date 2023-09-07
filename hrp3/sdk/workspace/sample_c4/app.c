/**
 ******************************************************************************
 ** ファイル名 : app.c
 **
 ** 概要 : 二輪差動型ライントレースロボットのTOPPERS/HRP3用Cサンプルプログラム
 **
 ** 注記 : sample_c4 (sample_c3にBluetooth通信リモートスタート機能を追加)
 ******************************************************************************
 **/

#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "ev3api.h"
#include "app.h"
#include "etroboc_ext.h"
#include "common.h"
#include "matrix.h"
#include "extern.h"
#include "color.h"

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

#define REFLECT_LOG_SIZE 255

extern LIST_ORDER_t list_order;

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
    center_motor    = EV3_PORT_D;

static int      bt_cmd = 0;     /* Bluetoothコマンド 1:リモートスタート */
int flag_turn;

int color_reflect;

//course種類 1-左コース 2-右コース
int course_type=1;

//serach_mode =0 :通常走行モード
int serach_mode=0;

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
    int read_color;
    int detected_flag = 0;    /* 線検知フラグ */

    int order_pattern = 0;
    int order_red_pos = 0;

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
    ev3_motor_config(center_motor, LARGE_MOTOR);

    //テールモーター固定
    ev3_motor_stop(center_motor,true);
    
    //マトリクス攻略命令リスト初期化
    init_matrix_order();

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
        fprintf(bt, "Bluetooth Remote Start: Ready.\n");
        fprintf(bt, "send '1' to start\n");
    }

    /* スタート待機 */
    while(1)
    {
        //tail_control(TAIL_ANGLE_STAND_UP); /* 完全停止用角度に制御 */

        if (bt_cmd == 1) {
            break; /* リモートスタート */
        } else if (bt_cmd == 2) {
            /* 光取得用のデバッグ処理 */
            rgb_raw_t dbg_raw;
            ev3_color_sensor_get_rgb_raw(color_sensor, &dbg_raw);
            LOG_D_DEBUG("R:%u, G:%u, B:%u\n", dbg_raw.r, dbg_raw.g, dbg_raw.b);
            LOG_D_DEBUG("Reflect:%d\n", ev3_color_sensor_get_reflect(color_sensor));
            bt_cmd = 0;
        }

        if (ev3_touch_sensor_is_pressed(touch_sensor) == 1)
        {
            break; /* タッチセンサが押された */
        }

        if (ev3_button_is_pressed(LEFT_BUTTON) ){
            LOG_D_DEBUG("LEFT  BUTTON is pushed\n");
        }

        if (ev3_button_is_pressed(RIGHT_BUTTON) ){
            LOG_D_DEBUG("RIGHT BUTTON is pushed\n");
        }
        if (ev3_button_is_pressed(UP_BUTTON) ){
            LOG_D_DEBUG("UP    BUTTON is pushed\n");
        }
        if (ev3_button_is_pressed(DOWN_BUTTON) ){
            LOG_D_DEBUG("DOWN  BUTTON is pushed\n");
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

    //コースパターンを設定する
    while (1) {
        if (ev3_button_is_pressed(UP_BUTTON)) {
            //パターン1
            order_pattern = 0;
            break;
        } else if (ev3_button_is_pressed(DOWN_BUTTON)) {
            //パターン2
            order_pattern = 1;
            break;
        } else if (ev3_button_is_pressed(LEFT_BUTTON)) {
            //パターン3
            order_pattern = 2;
            break;
        } else if (ev3_button_is_pressed(RIGHT_BUTTON)) {
            //パターン4
            order_pattern = 3;
            break;
        } else if (ev3_button_is_pressed(ENTER_BUTTON)) {
            //パターン5
            order_pattern = 4;
            break;
        }
    }

    LOG_D_DEBUG("selected pattern %d\n", order_pattern + 1);

    //赤ブロックの位置を設定する
    //ダミーデータを設定されても確認しないので注意
    while(1) {
        if (ev3_button_is_pressed(UP_BUTTON)) {
            //パターン1
            order_red_pos = MATRIX_COLOR_RED;
            break;
        } else if (ev3_button_is_pressed(DOWN_BUTTON)) {
            //パターン2
            order_red_pos = MATRIX_COLOR_BLUE;
            break;
        } else if (ev3_button_is_pressed(LEFT_BUTTON)) {
            //パターン3
            order_red_pos = MATRIX_COLOR_YELLOW;
            break;
        } else if (ev3_button_is_pressed(RIGHT_BUTTON)) {
            //パターン4
            order_red_pos = MATRIX_COLOR_GREEN;
            break;
        }
    }

    char debug_color_msg[MATRIX_COLOR_MAX][10] = {
        "赤", "青", "黄", "緑"
    };
    LOG_D_DEBUG("selected red block %s\n", debug_color_msg[order_red_pos]);

    /* ライントレース */
#if 0
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
#endif

    /* コンフィグ 初期設定 */
   float Kp = 2.80;
   float Kd = 0.3;
   float P;
   float D;
   rgb_raw_t main_rgb;
   float sensor = 0;
   float sensor_dt = 0;
   float curb = 0.0;
   float sensor_diff = (LIGHT_WHITE + LIGHT_BLACK)/2;
   float sensor_reflect = 0;
   
   float weight;
   int blue_count = 0;
   int is_blue = 0;
   int wait_flame = 120;

   int count = 0;
    while(1)
    {
        if (ev3_button_is_pressed(BACK_BUTTON)) break;

        if (isfound_red() == COLOR_CODE_RED){
            //赤色を検出したのでライントレースを終了する
            LOG_D_DEBUG("red discoverd.\n");
            break;
        }

        forward = 30; /* 前進命令 */
        ev3_color_sensor_get_rgb_raw(color_sensor,&main_rgb);

        sensor_reflect = ev3_color_sensor_get_reflect(color_sensor);
        if(sensor_reflect > LIGHT_WHITE){
            sensor_reflect = LIGHT_WHITE;
        }

        sensor_dt = sensor_diff - sensor_reflect;
        sensor_diff = sensor_reflect;

        sensor = ev3_color_sensor_get_reflect(color_sensor);

        //青かどうかの判定
        if(4 * main_rgb.r < main_rgb.b && 2 * main_rgb.g < main_rgb.b && main_rgb.b > THRE_B_OF_BLUE * 3/4 && is_blue == 0){
            is_blue = 1;
            LOG_D_DEBUG("isBlue");
        }
        
        if(!((4 * main_rgb.r < main_rgb.b && 2 * main_rgb.g < main_rgb.b && main_rgb.b > THRE_B_OF_BLUE * 3/4 && is_blue)
        || (main_rgb.r > 158
        || main_rgb.g > 229
        || main_rgb.b > 353))
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
        curb = Kp * P - Kd * D;
        if(course_type == 1) {
            turn = -curb;
        } else {
            turn = curb;
        }

        if(blue_count == 3){
            LOG_D_DEBUG("直進");
            turn *= -1;
        }

        if(blue_count == 4 && count < wait_flame){
            LOG_D_DEBUG("直進");
            turn *= 1;
            count++;
        }

        if(blue_count >= 4 && count >= wait_flame){
            turn *= -1;
        }

        ev3_motor_steer(
            left_motor,
            right_motor,
            forward,
            turn
        );

#if 0
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
#endif

        tslp_tsk(1 * 1000U); /* 4msec周期起動 */
    }

    //ライントレース完了

    LOG_D_DEBUG("linetrace completed.\n");

    ev3_motor_stop(left_motor, false);
    ev3_motor_stop(right_motor, false);
    tslp_tsk(100 * 1000U); /* 100msec 停止*/

    //マトリクスに向かって移動する
    move_to_matrix_start_pos(course_type);
    tslp_tsk(1000 * 1000U); /* 1000msec 停止*/

    //誤作動を防ぐため、一定距離進
    ev3_motor_rotate(right_motor, 100, 30, false);
    ev3_motor_rotate(left_motor , 100, 30, true);
    tslp_tsk(100 * 1000U); /* 1000msec 停止*/

    ev3_motor_set_power(left_motor, 10);
    ev3_motor_set_power(right_motor, 10);

    while (1) {
        read_color = ret_color_code();
        if (read_color == COLOR_CODE_BLACK) {
            LOG_D_DEBUG("arrived matrix1.\n");
            //到着した
            break;
        }

        tslp_tsk(4 * 1000U); /* 4msec 停止*/
    }

    tslp_tsk(100 * 1000U); /* 1000msec 停止*/

    //角度をただす
    //車軸-センサー間分(5cm)前進
    ev3_motor_rotate(right_motor, 40, 30, false);
    ev3_motor_rotate(left_motor , 40, 30, true);

    while(1){
        if (course_type == 1) {
            ev3_motor_rotate(left_motor , 10, 20, false);
            ev3_motor_rotate(right_motor , -10, 20, true);
        } else {
        ev3_motor_rotate(left_motor , -10, 20, false);
        ev3_motor_rotate(right_motor , 10, 20, true);
        }

        read_color = ret_color_code();
        if (read_color == COLOR_CODE_BLACK) {
            LOG_D_DEBUG("arrived matrix2.\n");
            //到着した
            break;
        }

        tslp_tsk(4 * 1000U); /* 4msec 停止*/
    }

    //マトリクス攻略
    while(0)
    {
        matrix_move_sequence(list_order.left_matrix_order[0][MATRIX_COLOR_RED]);
        tslp_tsk(2 * 1000000U); /* 0.4msec周期起動 */

    }

    if (_bt_enabled)
    {
        ter_tsk(BT_TASK);
        fclose(bt);
    }

    ev3_motor_set_power(left_motor, 0);
    ev3_motor_set_power(right_motor, 0);

    ext_tsk();
}

//*****************************************************************************
// 関数名 : matrix_move_sequence
// 引数 :   マトリクス行動ルートを格納した配列, 配列サイズ
// 返り値 : 
// 概要 :　
//*****************************************************************************
void matrix_move_sequence(MATRIX_ORDER_t order) {
    int i = 0;
    
    for(i = 0; i < ORDER_NUM_MAX; i++){
        switch (order.move_on_matrix_order[i]){
        case move_forward:
            LOG_D_DEBUG("matrix_move_sequence %d- move_forward\n",i);
            trace_node();
            break;
        case turn_right:
            LOG_D_DEBUG("matrix_move_sequence %d- turn_right\n",i);
            turn_90_degree(1);
            break;
        case turn_left:
            LOG_D_DEBUG("matrix_move_sequence %d- turn_left \n",i);
            turn_90_degree(2);
            break;

        case push_blue_block:
            LOG_D_DEBUG("matrix_move_sequence %d- push_blue_block\n",i);
            do_push_blue_block();
            break;

        case get_red_block:
            LOG_D_DEBUG("matrix_move_sequence %d- get_red_block\n",i);
            break;

        default:
            break;
        }
    }
}

//*****************************************************************************
// 関数名 : do_push_blue_block
// 引数 :   
// 返り値 : 
// 概要 :　
//*****************************************************************************
void do_push_blue_block(void) {

    int rotate_degree=180;

    ev3_motor_rotate(center_motor, 50 , 50, true);

    ev3_motor_rotate(right_motor, rotate_degree , 50, false);
    ev3_motor_rotate(left_motor , rotate_degree,  50, true);

    tslp_tsk(2 * 1000000U); /* 0.2sec停止 */

    ev3_motor_rotate(right_motor, -rotate_degree , 50, false);
    ev3_motor_rotate(left_motor , -rotate_degree,  50, true);

    ev3_motor_rotate(center_motor, -50 , 50, true);

}

int isfound_red(void) {
    rgb_raw_t read_rgb;
    ev3_color_sensor_get_rgb_raw(color_sensor, &read_rgb);

    if ((read_rgb.r >= THRE_R_OF_RED) && (read_rgb.r > 1.5 * read_rgb.b) && (read_rgb.r > 1.5 * read_rgb.g)) {
        return COLOR_CODE_RED;
    }

    return 0;
}

//*****************************************************************************
// 関数名 : ret_color_code
// 引数 :   L
// 返り値 : COLOR_CODEの整数
// 概要 :　
//*****************************************************************************
int ret_color_code(void) {
    
    int ret;
    rgb_raw_t read_rgb;
    ev3_color_sensor_get_rgb_raw(color_sensor, &read_rgb);

    if(read_rgb.r>THRE_R_OF_WHITE && read_rgb.g>THRE_G_OF_WHITE && read_rgb.b>THRE_B_OF_WHITE){
        //白の時
        ret= COLOR_CODE_WHITE;
        //LOG_D_DEBUG("WHITE  r= %u g= %u b=%u \n",read_rgb.r, read_rgb.g, read_rgb.b);

    }else if(read_rgb.r<THRE_R_OF_BLUE && read_rgb.g<THRE_G_OF_BLUE && read_rgb.b>THRE_B_OF_BLUE){
        //青の時
        ret= COLOR_CODE_BLUE;
        //LOG_D_DEBUG("BLUE   r= %u g= %u b=%u \n",read_rgb.r, read_rgb.g, read_rgb.b);

    }else if(read_rgb.r>THRE_R_OF_YELLOW && read_rgb.g>THRE_G_OF_YELLOW && read_rgb.b<THRE_B_OF_YELLOW){
        //黄の時
        ret= COLOR_CODE_YELLOW;
        ///LOG_D_DEBUG("YELLOW r= %u g= %u b=%u \n",read_rgb.r, read_rgb.g, read_rgb.b);

    }else if(read_rgb.r>THRE_R_OF_RED && read_rgb.g<THRE_G_OF_RED && read_rgb.b<THRE_B_OF_RED){
        //赤の時
        ret= COLOR_CODE_RED;
        //LOG_D_DEBUG("RED    r= %u g= %u b=%u \n",read_rgb.r, read_rgb.g, read_rgb.b);

    }else if(read_rgb.r<THRE_R_OF_GREEN && read_rgb.g>THRE_G_OF_GREEN && read_rgb.b<THRE_B_OF_GREEN){
        //緑の時
        ret= COLOR_CODE_GREEN;
        //LOG_D_DEBUG("GREEN  r= %u g= %u b=%u \n",read_rgb.r, read_rgb.g, read_rgb.b);

    }else if(read_rgb.r < THRE_R_OF_BLACK && read_rgb.g < THRE_G_OF_BLACK && read_rgb.b < THRE_B_OF_BLACK){
        ret = COLOR_CODE_BLACK;
    } else {
        //不明の時
        ret= COLOR_CODE_UNKNOWN;
        //LOG_D_DEBUG("UNKNOWN r= %u g= %u b=%u \n",read_rgb.r, read_rgb.g, read_rgb.b);

    }
    return ret;


}
//*****************************************************************************
// 関数名 :move_to_matrix_start_pos
// 引数   :   1-左コース 2-右コース
// 返り値 : なし
// 概要   :　ライントレース最終部分の赤読み取り時に実行される
//           
//*****************************************************************************
void move_to_matrix_start_pos(int course_flag) {

    if(course_type==1){

        turn_70_degree(1);


    }else if(course_type==2){

        turn_70_degree(2);


    }


}


//*****************************************************************************
// 関数名 : motor_set_two_motor
// 引数 :   LeftMotorPower   :左モーターパワー
//          RightMotorPower  :右モーターパワー
// 返り値 : なし
// 概要 :　
//*****************************************************************************
void motor_set_two_motor(int LeftMotorPower, int RightMotorPower) {

    ev3_motor_set_power(EV3_PORT_C, LeftMotorPower);
    ev3_motor_set_power(EV3_PORT_B, RightMotorPower);

    
}

//*****************************************************************************
// 関数名 : turn_90_degree
// 引数 :   1-右旋回　2-左旋回
// 返り値 : 
// 概要 :　
//*****************************************************************************
void turn_90_degree(int flag_turn) {

    //車体　90度分旋回時　回転角度
    const int rotate_degree=125;

    if(flag_turn==1){
        //右旋回
        ev3_motor_rotate(right_motor, rotate_degree , 20, false);
        ev3_motor_rotate(left_motor , -rotate_degree, 20, true);

    }else if(flag_turn==2){
        //左旋回
        ev3_motor_rotate(left_motor , rotate_degree , 20, false);
        ev3_motor_rotate(right_motor , -rotate_degree, 20, true);

    }
    
}

//*****************************************************************************
// 関数名 : turn_70_degree
// 引数 :   1-右旋回　2-左旋回
// 返り値 : 
// 概要 :　
//*****************************************************************************
void turn_70_degree(int flag_turn) {

    //車体　70度分旋回時　回転角度
    const int rotate_degree=87;

    if(flag_turn==1){
        //右旋回
        ev3_motor_rotate(right_motor, rotate_degree , 20, false);
        ev3_motor_rotate(left_motor , -rotate_degree, 20, true);

    }else if(flag_turn==2){
        //左旋回
        ev3_motor_rotate(left_motor , rotate_degree , 20, false);
        ev3_motor_rotate(right_motor , -rotate_degree, 20, true);

    }
    
}
//*****************************************************************************
// 関数名 : trace_node
// 引数 : 
// 返り値 : 
// 概要 :　
//*****************************************************************************
void trace_node(void) {

    int read_color;

    //15cm前進するときに必要な回転角
    const int degree_to_move_node=172;
    
    //センサ-車軸間文全身に必要な回転角
    const int degree_to_move_wheel_offset=57;
    int tog=0;
    int motor_degree=20;
    int motor_power=20;


    //ブロックサークル間距離　移動
    ev3_motor_rotate(right_motor, degree_to_move_node , 20, false);
    ev3_motor_rotate(left_motor , degree_to_move_node , 20, true);

    while(1){

        if (ev3_color_sensor_get_reflect(color_sensor) >= (LIGHT_WHITE + LIGHT_BLACK)/2){
            //白部分の上の時
            if(tog==0){
                ev3_motor_rotate(left_motor , motor_degree+10, motor_power, false);
                ev3_motor_rotate(right_motor, motor_degree, motor_power, true);
                tog=1;


            }else if(tog==1){
                ev3_motor_rotate(left_motor, motor_degree, motor_power, false);
                ev3_motor_rotate(right_motor, motor_degree+10, motor_power, true);
                tog=0;
            }

            LOG_D_DEBUG("trace_node [white]\n");

        }else{
            ev3_motor_rotate(left_motor, motor_degree, motor_power, true);
            ev3_motor_rotate(right_motor, motor_degree, motor_power, true);

            LOG_D_DEBUG("trace_node [black]\n");
        }
        read_color=ret_color_code();

        //色(赤、青、黄、緑)検出時
        if(read_color==COLOR_CODE_BLUE    ||read_color==COLOR_CODE_YELLOW 
            || read_color==COLOR_CODE_RED || read_color==COLOR_CODE_GREEN){

            //車軸-センサー間分(5cm)前進
            ev3_motor_rotate(right_motor, degree_to_move_wheel_offset , 30, false);
            ev3_motor_rotate(left_motor , degree_to_move_wheel_offset , 30, true);
            

            LOG_D_DEBUG("** COLOR FIND BREAK \n");
            break;
        }
    }


}

void init_matrix_order(void) {
    memset(&list_order, 0x00, sizeof(LIST_ORDER_t));
    memcpy(&list_order.left_matrix_order, &left_list_order, sizeof(MATRIX_ORDER_t));
    memcpy(&list_order.right_matrix_order, &right_list_order, sizeof(MATRIX_ORDER_t));
}

//*****************************************************************************
// 関数名 : motor_stop
// 引数 :   
// 返り値 : なし
// 概要 :　車体を停止する
//*****************************************************************************
void motor_stop() {
    ev3_motor_stop(EV3_PORT_B,true);
    ev3_motor_stop(EV3_PORT_C,true);
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
            case '2':
                bt_cmd = 2;
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
static void _syslog(int level, char* text) {
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
static void _log(char *text) {
    _syslog(LOG_NOTICE, text);
}