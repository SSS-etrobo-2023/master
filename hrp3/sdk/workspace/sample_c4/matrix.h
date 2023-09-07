#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>

#define PATTERN_MAX 5
#define ORDER_NUM_MAX 25

enum matrix_color_code {
    MATRIX_COLOR_RED = 0,
    MATRIX_COLOR_BLUE,
    MATRIX_COLOR_YELLOW,
    MATRIX_COLOR_GREEN,
    MATRIX_COLOR_MAX
};

/*
マトリクス上動作命令
move_forward     :マトリクスのノードをトレースする
turn_right       :90°右旋回する
turn_left        :90°左旋回する
push_blue_block  :青ブロックを押し出す
get_red_block    :赤ブロックを保持する
*/
enum matrix_move_order {
    dummy = 0,
    move_forward,
    turn_right,
    turn_left,
    push_blue_block,
    get_red_block,
    move_on_white_zone,
    move_to_goal
};

typedef struct {
    uint8_t move_on_matrix_order[ORDER_NUM_MAX];
    uint8_t move_to_goal_order[ORDER_NUM_MAX];
} MATRIX_ORDER_t;

typedef struct {
    MATRIX_ORDER_t left_matrix_order[PATTERN_MAX][MATRIX_COLOR_MAX]; 
    MATRIX_ORDER_t right_matrix_order[PATTERN_MAX][MATRIX_COLOR_MAX]; 
} LIST_ORDER_t;

LIST_ORDER_t list_order;

// マトリクス命令リスト 初期値
const MATRIX_ORDER_t left_list_order[PATTERN_MAX][MATRIX_COLOR_MAX] = {
    /* パターン1 */
    {
        /* 赤ブロックが赤の位置 */
        {
            { 
                move_forward, turn_right, move_forward, push_blue_block, turn_left,
                move_forward, move_forward, turn_left, move_forward, move_forward,
                push_blue_block, turn_left, move_forward, turn_left, move_forward,
                turn_right, move_forward, move_forward, turn_right, move_forward,
                get_red_block,
            },

            {
                turn_right, move_forward, move_forward, move_forward, move_on_white_zone,
                turn_left, move_to_goal
            }
        },

        /* 赤ブロックが青の位置 */
        {
            {
                turn_left, move_forward, push_blue_block, turn_right, move_forward,
                move_forward, move_forward, push_blue_block, turn_right, move_forward,
                turn_right, move_forward, move_forward, turn_left, move_forward,
                get_red_block
            },

            {
                turn_left, move_forward, move_forward, move_on_white_zone, turn_left,
                move_to_goal
            }
        },

        /* 赤ブロックが黄の位置 */
        {
            {
                turn_left, move_forward, push_blue_block, turn_right, move_forward,
                turn_right, move_forward, move_forward, push_blue_block, turn_left,
                move_forward, turn_left, move_forward, move_forward, turn_right,
                move_forward, get_red_block
            },

            {
                move_on_white_zone, turn_left, move_to_goal
            }
        },

        /* 赤ブロックが緑の位置 */
        {
            { dummy },
            { dummy }
        },
    },

    /* パターン2 */
    {
        /* 赤ブロックが赤の位置 */
        {
            {
                turn_right, move_forward, move_forward, push_blue_block, turn_left,
                move_forward, move_forward, move_forward, push_blue_block, turn_left,
                move_forward, turn_left, move_forward, move_forward, turn_right,
                move_forward, get_red_block
            },

            {
                turn_right, move_forward, move_forward, move_on_white_zone, turn_left,
                move_to_goal
            }
        },

        /* 赤ブロックが青の位置 */
        {
            {
                move_forward, push_blue_block, turn_right, move_forward, turn_left,
                move_forward, move_forward, turn_right, move_forward, push_blue_block,
                turn_right, move_forward, turn_right, move_forward, turn_left,
                move_forward, move_forward, turn_left, move_forward, get_red_block
            },

            {
                turn_left, move_forward, move_forward, move_forward, move_on_white_zone,
                turn_left, move_to_goal
            }
        },

        /* 赤ブロックが黄の位置 */
        {
            { dummy },
            { dummy }
        },

        /* 赤ブロックが緑の位置 */
        {
            {
                move_forward, push_blue_block, turn_right, move_forward, turn_right,
                move_forward, turn_left, move_forward, push_blue_block, turn_left,
                move_forward, move_forward, move_forward, get_red_block
            },

            {
                move_on_white_zone, turn_left, move_to_goal
            }
        },
    },

    /* パターン3 */
    {
        /* 赤ブロックが赤の位置 */
        {
            {
                move_forward, move_forward, push_blue_block, turn_right, move_forward,
                turn_right, move_forward, push_blue_block, turn_right, move_forward,
                turn_left, move_forward, turn_right, move_forward, get_red_block
            },

            {
                move_forward, move_forward, move_forward, turn_right, move_forward,
                turn_left, move_on_white_zone, turn_left, move_to_goal
            }
        },

        /* 赤ブロックが青の位置 */
        {
            {
                turn_left, move_forward, push_blue_block, turn_right, move_forward,
                move_forward, turn_right, move_forward, push_blue_block, turn_right,
                move_forward, turn_left, move_forward, get_red_block
            },

            {
                turn_left, move_forward, move_forward, move_on_white_zone, turn_left,
                move_to_goal
            }
        },

        /* 赤ブロックが黄の位置 */
        {
            {
                turn_left, move_forward, push_blue_block, turn_right, move_forward,
                turn_right, move_forward, move_forward, push_blue_block, turn_left,
                move_forward, turn_left, move_forward, get_red_block
            },

            {
                turn_right, move_forward, move_on_white_zone, move_to_goal
            }
        },

         /* 赤ブロックが緑の位置 */
        {
            { dummy },
            { dummy }
        },
    },

    /* パターン4 */
    {
        /* 赤ブロックが赤の位置 */
        {
            { dummy },
            { dummy }
        },

        /* 赤ブロックが青の位置 */
        {
            {
                turn_left, move_forward, turn_right, move_forward, move_forward,
                push_blue_block, turn_right, move_forward, turn_left, move_forward,
                turn_right, move_forward, move_forward, push_blue_block, turn_right,
                move_forward, move_forward, turn_right, move_forward, get_red_block
            },

            {
                turn_right, move_forward, move_forward, move_on_white_zone, turn_left,
                move_to_goal
            }
        },

        /* 赤ブロックが黄の位置 */
        {
            {
                move_forward, turn_right, move_forward, push_blue_block, turn_left,
                move_forward, turn_right, move_forward, turn_left, move_forward,
                push_blue_block, turn_left, move_forward, move_forward, turn_left,
                move_forward, turn_right, move_forward, get_red_block
            },

            {
                turn_right, move_forward, turn_right, move_forward, turn_left,
                move_on_white_zone, turn_left, move_to_goal
            }
        },

        /* 赤ブロックが緑の位置 */
        {
            {
                move_forward, turn_right, move_forward, push_blue_block, turn_left,
                move_forward, turn_left, move_forward, move_forward, push_blue_block,
                turn_right, move_forward, turn_right, move_forward,
                move_forward, move_forward, get_red_block
            },

            {
                turn_left, move_on_white_zone, turn_left, move_to_goal
            }
        },
    },

    /* パターン5 */
    {
        /* 赤ブロックが赤の位置 */
        {
            {
                move_forward, move_forward, turn_right, move_forward, push_blue_block,
                turn_right, move_forward, turn_left, move_forward, push_blue_block,
                turn_right, move_forward, turn_right, move_forward, move_forward,
                move_forward, get_red_block
            },

            {
                move_forward, move_forward, move_forward, turn_right, move_forward,
                turn_left, move_on_white_zone, turn_left, move_to_goal
            }
        },

        /* 赤ブロックが青の位置 */
        {
            {
                turn_left, move_forward, push_blue_block, turn_right, move_forward,
                move_forward, turn_right, move_forward, move_forward, push_blue_block,
                turn_right, move_forward, turn_left, move_forward, get_red_block
            },

            {
                turn_left, move_forward, move_forward, move_on_white_zone, turn_left,
                move_to_goal
            }
        },

        /* 赤ブロックが黄の位置 */
        {
            { dummy },
            { dummy }
        },

        /* 赤ブロックが緑の位置 */
        {
            {
                turn_left, move_forward, push_blue_block, turn_right, move_forward,
                turn_right, move_forward, move_forward, move_forward, push_blue_block,
                turn_left, move_forward, turn_left, move_forward, get_red_block
            },

            {
                turn_right, move_forward, move_on_white_zone, turn_left, move_to_goal
            }
        },
    },
};

const MATRIX_ORDER_t right_list_order[PATTERN_MAX][MATRIX_COLOR_MAX] = {
    /* パターン1 */
    {
        /* 赤ブロックが赤の位置 */
        {
            {
                turn_right, move_forward, get_red_block
            },

            {
                turn_left, move_forward, move_forward, turn_left, move_forward,
                turn_right, move_forward, move_on_white_zone, turn_right, move_to_goal
            }
        },

        /* 赤ブロックが青の位置 */
        {
            {
                turn_left, move_forward, turn_right, move_forward, get_red_block
            },

            {
                move_forward, move_forward, move_on_white_zone, turn_right, move_to_goal
            }
        },

        /* 赤ブロックが黄の位置 */
        {
            {
                move_forward, move_forward, turn_right, move_forward, turn_left,
                move_forward, get_red_block
            },

            {
                turn_left, move_forward, turn_right, move_on_white_zone, turn_right,
                move_to_goal
            }
        },

        /* 赤ブロックが緑の位置 */
        {
            { dummy },
            { dummy }
        },
    },

    /* パターン2 */
    {
        /* 赤ブロックが赤の位置 */
        {
            {
                move_forward, get_red_block
            },

            {
                move_forward, move_forward, move_on_white_zone, turn_right, move_to_goal
            }
        },

        /* 赤ブロックが青の位置 */
        {
            {
                turn_left, move_forward, move_forward, get_red_block
            },

            {
                turn_right, move_forward, move_forward,  move_forward, move_on_white_zone,
                turn_right, move_to_goal
            }
        },

        /* 赤ブロックが黄の位置 */
        {
            { dummy },
            { dummy }
        },

        /* 赤ブロックが緑の位置 */
        {
            {
                turn_left, move_forward, turn_right, move_forward, move_forward,
                turn_left, move_forward, turn_right, move_forward, get_red_block
            },

            {
                move_on_white_zone, turn_right, move_to_goal
            }
        },
    },

    /* パターン3 */
    {
        /* 赤ブロックが赤の位置 */
        {
            {
                turn_right, move_forward, get_red_block
            },

            {
                turn_left, move_forward, move_forward, move_forward, turn_left,
                move_forward, turn_right, move_on_white_zone, turn_right, move_to_goal
            }
        },

        /* 赤ブロックが青の位置 */
        {
            {
                turn_left, move_forward, turn_right,  move_forward, get_red_block
            },

            {
                move_forward, move_forward, move_on_white_zone, turn_right, move_to_goal
            }
        },

        /* 赤ブロックが黄の位置 */
        {
            {
                move_forward, move_forward, get_red_block
            },

            {
                move_forward, move_on_white_zone, turn_right, move_to_goal
            }
        },

        /* 赤ブロックが緑の位置 */
        {
            { dummy },
            { dummy }
        },
    },

    /* パターン4 */
    {
        /* 赤ブロックが赤の位置 */
        {
            { dummy },
            { dummy }
        },

        /* 赤ブロックが青の位置 */
        {
            {
                turn_left, move_forward, turn_right, move_forward, get_red_block
            },

            {
                move_forward, move_forward, move_on_white_zone, turn_right, move_to_goal
            }
        },

        /* 赤ブロックが黄の位置 */
        {
            {
                turn_right, move_forward, turn_left, move_forward, move_forward,
                get_red_block
            },

            {
                move_forward, turn_left, move_forward, turn_right, move_on_white_zone,
                turn_right, move_to_goal
            }
        },

        /* 赤ブロックが緑の位置 */
        {
            {
                move_forward, move_forward, turn_left, move_forward, move_forward,
                turn_right, move_forward, get_red_block
            },

            {
                move_on_white_zone, turn_right, move_to_goal
            }
        },
    },

    /* パターン5 */
    {
        /* 赤ブロックが赤の位置 */
        {
            {
                turn_right, move_forward, get_red_block
            },

            {
                turn_left, move_forward, move_forward, move_forward, turn_left,
                move_forward, turn_right, move_on_white_zone, turn_right, move_to_goal
            }
        },

        /* 赤ブロックが青の位置 */
        {
            {
                turn_left, move_forward, move_forward, turn_right, move_forward,
                get_red_block
            },

            {
                move_forward, move_forward, move_on_white_zone, turn_right, move_to_goal
            }
        },

        /* 赤ブロックが黄の位置 */
        {
            { /* 命令を羅列する */},
            { /* 命令を羅列する */}
        },

        /* 赤ブロックが緑の位置 */
        {
            {
                turn_left, move_forward, turn_right, move_forward, move_forward,
                get_red_block
            },

            {
                move_forward, move_on_white_zone, turn_right, move_to_goal
            }
        },
    },
};

#endif