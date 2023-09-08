#ifndef __COLOR_H__
#define __COLOR_H__

#define LIGHT_WHITE 70   /* 白色の光センサ値 */
#define LIGHT_BLACK 2    /* 黒色の光センサ値 */

/* 色彩センサ　閾値 */
/* 青 */
#define THRE_B_OF_BLUE 100
#define THRE_G_OF_BLUE 60
#define THRE_R_OF_BLUE 15

/* 赤 */
#define THRE_B_OF_RED 75
#define THRE_G_OF_RED 75
#define THRE_R_OF_RED 90

/* 緑 */
#define THRE_B_OF_GREEN 30
#define THRE_G_OF_GREEN 90
#define THRE_R_OF_GREEN 60

/* 黄 */
#define THRE_B_OF_YELLOW 150
#define THRE_G_OF_YELLOW 150
#define THRE_R_OF_YELLOW 60

/* 黒 */
#define THRE_B_OF_BLACK 25
#define THRE_G_OF_BLACK 25
#define THRE_R_OF_BLACK 25

/* 白 */
#define THRE_B_OF_WHITE 100
#define THRE_G_OF_WHITE 100
#define THRE_R_OF_WHITE 100

/* カラーコード定義 */
#define COLOR_CODE_RED    1
#define COLOR_CODE_BLUE   2
#define COLOR_CODE_GREEN  3
#define COLOR_CODE_YELLOW 4
#define COLOR_CODE_BLACK  5
#define COLOR_CODE_WHITE  6
#define COLOR_CODE_UNKNOWN  -1

#endif