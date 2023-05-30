/* Generated automatically by the program 'build/genpreds'
   from the machine description file '../../gcc/config/v850/v850.md'.  */

#ifndef GCC_TM_PREDS_H
#define GCC_TM_PREDS_H

#ifdef HAVE_MACHINE_MODES
extern int general_operand (rtx, enum machine_mode);
extern int address_operand (rtx, enum machine_mode);
extern int register_operand (rtx, enum machine_mode);
extern int pmode_register_operand (rtx, enum machine_mode);
extern int scratch_operand (rtx, enum machine_mode);
extern int immediate_operand (rtx, enum machine_mode);
extern int const_int_operand (rtx, enum machine_mode);
extern int const_double_operand (rtx, enum machine_mode);
extern int nonimmediate_operand (rtx, enum machine_mode);
extern int nonmemory_operand (rtx, enum machine_mode);
extern int push_operand (rtx, enum machine_mode);
extern int pop_operand (rtx, enum machine_mode);
extern int memory_operand (rtx, enum machine_mode);
extern int indirect_operand (rtx, enum machine_mode);
extern int ordered_comparison_operator (rtx, enum machine_mode);
extern int comparison_operator (rtx, enum machine_mode);
extern int reg_or_0_operand (rtx, enum machine_mode);
extern int reg_or_int5_operand (rtx, enum machine_mode);
extern int reg_or_int9_operand (rtx, enum machine_mode);
extern int reg_or_const_operand (rtx, enum machine_mode);
extern int even_reg_operand (rtx, enum machine_mode);
extern int call_address_operand (rtx, enum machine_mode);
extern int movsi_source_operand (rtx, enum machine_mode);
extern int disp23_operand (rtx, enum machine_mode);
extern int special_symbolref_operand (rtx, enum machine_mode);
extern int power_of_two_operand (rtx, enum machine_mode);
extern int pattern_is_ok_for_prologue (rtx, enum machine_mode);
extern int pattern_is_ok_for_epilogue (rtx, enum machine_mode);
extern int register_is_ok_for_epilogue (rtx, enum machine_mode);
extern int pattern_is_ok_for_dispose (rtx, enum machine_mode);
extern int pattern_is_ok_for_prepare (rtx, enum machine_mode);
extern int not_power_of_two_operand (rtx, enum machine_mode);
extern int const_float_1_operand (rtx, enum machine_mode);
extern int const_float_0_operand (rtx, enum machine_mode);
extern int label_ref_operand (rtx, enum machine_mode);
extern int e3v5_shift_operand (rtx, enum machine_mode);
extern int ior_operator (rtx, enum machine_mode);
extern int v850_float_z_comparison_operator (rtx, enum machine_mode);
extern int v850_float_nz_comparison_operator (rtx, enum machine_mode);
#endif /* HAVE_MACHINE_MODES */

#define CONSTRAINT_NUM_DEFINED_P 1
enum constraint_num
{
  CONSTRAINT__UNKNOWN = 0,
  CONSTRAINT_e,
  CONSTRAINT_I,
  CONSTRAINT_J,
  CONSTRAINT_K,
  CONSTRAINT_L,
  CONSTRAINT_M,
  CONSTRAINT_N,
  CONSTRAINT_O,
  CONSTRAINT_P,
  CONSTRAINT_G,
  CONSTRAINT_H,
  CONSTRAINT_Q,
  CONSTRAINT_R,
  CONSTRAINT_S,
  CONSTRAINT_T,
  CONSTRAINT_U,
  CONSTRAINT_W,
  CONSTRAINT__LIMIT
};

extern enum constraint_num lookup_constraint (const char *);
extern bool constraint_satisfied_p (rtx, enum constraint_num);

#define CONSTRAINT_LEN(c_,s_) 1

extern enum reg_class regclass_for_constraint (enum constraint_num);
#define REG_CLASS_FROM_CONSTRAINT(c_,s_) \
    regclass_for_constraint (lookup_constraint (s_))
#define REG_CLASS_FOR_CONSTRAINT(x_) \
    regclass_for_constraint (x_)

extern bool insn_const_int_ok_for_constraint (HOST_WIDE_INT, enum constraint_num);
#define CONST_OK_FOR_CONSTRAINT_P(v_,c_,s_) \
    insn_const_int_ok_for_constraint (v_, lookup_constraint (s_))

#define CONST_DOUBLE_OK_FOR_CONSTRAINT_P(v_,c_,s_) \
    constraint_satisfied_p (v_, lookup_constraint (s_))

#define EXTRA_CONSTRAINT_STR(v_,c_,s_) \
    constraint_satisfied_p (v_, lookup_constraint (s_))

extern bool insn_extra_memory_constraint (enum constraint_num);
#define EXTRA_MEMORY_CONSTRAINT(c_,s_) insn_extra_memory_constraint (lookup_constraint (s_))

#define EXTRA_ADDRESS_CONSTRAINT(c_,s_) false

#endif /* tm-preds.h */
