#ifndef __EXTERN_H__
#define __EXTERN_H__

#include "matrix.h"

extern void matrix_move_sequence(MATRIX_ORDER_t order);
extern void do_push_blue_block(void);
extern int isfound_red(void);
extern int ret_color_code(void);
extern void move_to_matrix_start_pos(int course_flag);
extern void motor_set_two_motor(int LeftMotorPower, int RightMotorPower);
extern void turn_90_degree(int flag_turn);
extern void turn_70_degree(int flag_turn);
extern void trace_node(void);
extern void motor_stop(void);
extern void init_matrix_order(void);

#endif