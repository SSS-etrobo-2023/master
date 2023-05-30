/* Generated automatically by the program `genflags'
   from the machine description file `md'.  */

#ifndef GCC_INSN_FLAGS_H
#define GCC_INSN_FLAGS_H

#define HAVE_sign23byte_load (TARGET_V850E2V3_UP)
#define HAVE_unsign23byte_load (TARGET_V850E2V3_UP)
#define HAVE_sign23hword_load (TARGET_V850E2V3_UP)
#define HAVE_unsign23hword_load (TARGET_V850E2V3_UP)
#define HAVE_23word_load (TARGET_V850E2V3_UP)
#define HAVE_23byte_store (TARGET_V850E2V3_UP)
#define HAVE_23hword_store (TARGET_V850E2V3_UP)
#define HAVE_23word_store (TARGET_V850E2V3_UP)
#define HAVE_cmpsi_insn 1
#define HAVE_cstoresf4 (TARGET_USE_FPU)
#define HAVE_cstoredf4 (TARGET_USE_FPU)
#define HAVE_addsi3 1
#define HAVE_subsi3 1
#define HAVE_negsi2 1
#define HAVE_mulhisi3_internal2 1
#define HAVE_mulsi3 ((TARGET_V850E_UP))
#define HAVE_divmodsi4 (TARGET_V850E_UP)
#define HAVE_udivmodsi4 (TARGET_V850E_UP)
#define HAVE_divmodhi4 (TARGET_V850E_UP)
#define HAVE_udivmodhi4 (TARGET_V850E_UP)
#define HAVE_andsi3 1
#define HAVE_iorsi3 1
#define HAVE_xorsi3 1
#define HAVE_one_cmplsi2 1
#define HAVE_insv (TARGET_V850E3V5_UP)
#define HAVE_setf_insn 1
#define HAVE_set_z_insn (TARGET_V850E2V3_UP)
#define HAVE_set_nz_insn (TARGET_V850E2V3_UP)
#define HAVE_movsicc_normal_cc ((TARGET_V850E_UP))
#define HAVE_movsicc_reversed_cc ((TARGET_V850E_UP))
#define HAVE_rotlsi3_a (TARGET_V850E3V5_UP && (INTVAL (operands[2]) + INTVAL (operands[3]) == 32))
#define HAVE_rotlsi3_b (TARGET_V850E3V5_UP && (INTVAL (operands[2]) + INTVAL (operands[3]) == 32))
#define HAVE_rotlsi3_v850e3v5 (TARGET_V850E3V5_UP)
#define HAVE_fix_loop_counter (TARGET_V850E3V5_UP && TARGET_LOOP)
#define HAVE_doloop_end_internal_loop (TARGET_V850E3V5_UP && TARGET_LOOP)
#define HAVE_branch_z_normal (TARGET_V850E2V3_UP)
#define HAVE_branch_nz_normal (TARGET_V850E2V3_UP)
#define HAVE_jump 1
#define HAVE_indirect_jump 1
#define HAVE_tablejump 1
#define HAVE_switch ((TARGET_V850E_UP))
#define HAVE_call_internal_short (! TARGET_LONG_CALLS)
#define HAVE_call_internal_long (TARGET_LONG_CALLS)
#define HAVE_call_value_internal_short (! TARGET_LONG_CALLS)
#define HAVE_call_value_internal_long (TARGET_LONG_CALLS)
#define HAVE_nop 1
#define HAVE_ashlsi3 1
#define HAVE_ashlsi3_v850e2 (TARGET_V850E2_UP)
#define HAVE_lshrsi3 1
#define HAVE_lshrsi3_v850e2 (TARGET_V850E2_UP)
#define HAVE_ashrsi3 1
#define HAVE_ashrsi3_v850e2 (TARGET_V850E2_UP)
#define HAVE_ffssi2 (TARGET_V850E2_UP)
#define HAVE_return_simple (reload_completed)
#define HAVE_return_internal 1
#define HAVE_addsf3 (TARGET_USE_FPU)
#define HAVE_adddf3 (TARGET_USE_FPU)
#define HAVE_subsf3 (TARGET_USE_FPU)
#define HAVE_subdf3 (TARGET_USE_FPU)
#define HAVE_mulsf3 (TARGET_USE_FPU)
#define HAVE_muldf3 (TARGET_USE_FPU)
#define HAVE_divsf3 (TARGET_USE_FPU)
#define HAVE_divdf3 (TARGET_USE_FPU)
#define HAVE_minsf3 (TARGET_USE_FPU)
#define HAVE_mindf3 (TARGET_USE_FPU)
#define HAVE_maxsf3 (TARGET_USE_FPU)
#define HAVE_maxdf3 (TARGET_USE_FPU)
#define HAVE_abssf2 (TARGET_USE_FPU)
#define HAVE_absdf2 (TARGET_USE_FPU)
#define HAVE_negsf2 (TARGET_USE_FPU)
#define HAVE_negdf2 (TARGET_USE_FPU)
#define HAVE_sqrtsf2 (TARGET_USE_FPU)
#define HAVE_sqrtdf2 (TARGET_USE_FPU)
#define HAVE_fix_truncsfsi2 (TARGET_USE_FPU)
#define HAVE_fixuns_truncsfsi2 (TARGET_USE_FPU)
#define HAVE_fix_truncdfsi2 (TARGET_USE_FPU)
#define HAVE_fixuns_truncdfsi2 (TARGET_USE_FPU)
#define HAVE_fix_truncsfdi2 (TARGET_USE_FPU)
#define HAVE_fixuns_truncsfdi2 (TARGET_USE_FPU)
#define HAVE_fix_truncdfdi2 (TARGET_USE_FPU)
#define HAVE_fixuns_truncdfdi2 (TARGET_USE_FPU)
#define HAVE_floatsisf2 (TARGET_USE_FPU)
#define HAVE_unsfloatsisf2 (TARGET_USE_FPU)
#define HAVE_floatsidf2 (TARGET_USE_FPU)
#define HAVE_unsfloatsidf2 (TARGET_USE_FPU)
#define HAVE_floatdisf2 (TARGET_USE_FPU)
#define HAVE_unsfloatdisf2 (TARGET_USE_FPU)
#define HAVE_floatdidf2 (TARGET_USE_FPU)
#define HAVE_unsfloatdidf2 (TARGET_USE_FPU)
#define HAVE_extendsfdf2 (TARGET_USE_FPU)
#define HAVE_truncdfsf2 (TARGET_USE_FPU)
#define HAVE_recipsf2 (TARGET_USE_FPU)
#define HAVE_recipdf2 (TARGET_USE_FPU)
#define HAVE_rsqrtsf2 (TARGET_USE_FPU)
#define HAVE_rsqrtdf2 (TARGET_USE_FPU)
#define HAVE_fmasf4 (TARGET_USE_FPU)
#define HAVE_fmssf4 (TARGET_USE_FPU)
#define HAVE_fnmasf4 (TARGET_USE_FPU)
#define HAVE_fnmssf4 (TARGET_USE_FPU)
#define HAVE_cmpsf_le_insn (TARGET_USE_FPU)
#define HAVE_cmpsf_lt_insn (TARGET_USE_FPU)
#define HAVE_cmpsf_ge_insn (TARGET_USE_FPU)
#define HAVE_cmpsf_gt_insn (TARGET_USE_FPU)
#define HAVE_cmpsf_eq_insn (TARGET_USE_FPU)
#define HAVE_cmpdf_le_insn (TARGET_USE_FPU)
#define HAVE_cmpdf_lt_insn (TARGET_USE_FPU)
#define HAVE_cmpdf_ge_insn (TARGET_USE_FPU)
#define HAVE_cmpdf_gt_insn (TARGET_USE_FPU)
#define HAVE_cmpdf_eq_insn (TARGET_USE_FPU)
#define HAVE_trfsr (TARGET_USE_FPU \
   && GET_MODE(operands[0]) == GET_MODE(operands[1]) \
   && GET_CODE(operands[0]) == REG && REGNO (operands[0]) == CC_REGNUM \
   && GET_CODE(operands[1]) == REG && REGNO (operands[1]) == FCC_REGNUM \
   && (GET_MODE(operands[0]) == CC_FPU_LEmode \
       || GET_MODE(operands[0]) == CC_FPU_GEmode \
       || GET_MODE(operands[0]) == CC_FPU_LTmode \
       || GET_MODE(operands[0]) == CC_FPU_GTmode \
       || GET_MODE(operands[0]) == CC_FPU_EQmode \
       || GET_MODE(operands[0]) == CC_FPU_NEmode))
#define HAVE_movsfcc_z_insn (TARGET_USE_FPU)
#define HAVE_movsfcc_nz_insn (TARGET_USE_FPU)
#define HAVE_movdfcc_z_insn (TARGET_USE_FPU)
#define HAVE_movdfcc_nz_insn (TARGET_USE_FPU)
#define HAVE_movedfcc_z_zero (TARGET_USE_FPU)
#define HAVE_movedfcc_nz_zero (TARGET_USE_FPU)
#define HAVE_callt_save_interrupt ((TARGET_V850E_UP) && !TARGET_DISABLE_CALLT)
#define HAVE_callt_return_interrupt ((TARGET_V850E_UP) && !TARGET_DISABLE_CALLT)
#define HAVE_save_interrupt 1
#define HAVE_return_interrupt 1
#define HAVE_callt_save_all_interrupt ((TARGET_V850E_UP) && !TARGET_DISABLE_CALLT)
#define HAVE_save_all_interrupt 1
#define HAVE__save_all_interrupt (TARGET_V850 && ! TARGET_LONG_CALLS)
#define HAVE_callt_restore_all_interrupt ((TARGET_V850E_UP) && !TARGET_DISABLE_CALLT)
#define HAVE_restore_all_interrupt 1
#define HAVE__restore_all_interrupt (TARGET_V850 && ! TARGET_LONG_CALLS)
#define HAVE_movdi (TARGET_V850E3V5_UP)
#define HAVE_movqi 1
#define HAVE_movhi 1
#define HAVE_movsi 1
#define HAVE_cbranchsi4 1
#define HAVE_cstoresi4 1
#define HAVE_cmpsi 1
#define HAVE_cbranchsf4 (TARGET_USE_FPU)
#define HAVE_cbranchdf4 (TARGET_USE_FPU)
#define HAVE_cmpsf (TARGET_USE_FPU)
#define HAVE_cmpdf (TARGET_USE_FPU)
#define HAVE_mulhisi3 1
#define HAVE_movsicc ((TARGET_V850E_UP))
#define HAVE_rotlhi3 ((TARGET_V850E_UP))
#define HAVE_rotlsi3 ((TARGET_V850E_UP))
#define HAVE_doloop_begin (TARGET_V850E3V5_UP && TARGET_LOOP)
#define HAVE_doloop_end (TARGET_V850E3V5_UP && TARGET_LOOP)
#define HAVE_casesi 1
#define HAVE_call 1
#define HAVE_call_value 1
#define HAVE_zero_extendhisi2 1
#define HAVE_zero_extendqisi2 1
#define HAVE_extendhisi2 1
#define HAVE_extendqisi2 1
#define HAVE_prologue 1
#define HAVE_epilogue 1
extern rtx        gen_sign23byte_load             (rtx, rtx, rtx);
extern rtx        gen_unsign23byte_load           (rtx, rtx, rtx);
extern rtx        gen_sign23hword_load            (rtx, rtx, rtx);
extern rtx        gen_unsign23hword_load          (rtx, rtx, rtx);
extern rtx        gen_23word_load                 (rtx, rtx, rtx);
extern rtx        gen_23byte_store                (rtx, rtx, rtx);
extern rtx        gen_23hword_store               (rtx, rtx, rtx);
extern rtx        gen_23word_store                (rtx, rtx, rtx);
extern rtx        gen_cmpsi_insn                  (rtx, rtx);
extern rtx        gen_cstoresf4                   (rtx, rtx, rtx, rtx);
extern rtx        gen_cstoredf4                   (rtx, rtx, rtx, rtx);
extern rtx        gen_addsi3                      (rtx, rtx, rtx);
extern rtx        gen_subsi3                      (rtx, rtx, rtx);
extern rtx        gen_negsi2                      (rtx, rtx);
extern rtx        gen_mulhisi3_internal2          (rtx, rtx, rtx);
extern rtx        gen_mulsi3                      (rtx, rtx, rtx);
extern rtx        gen_divmodsi4                   (rtx, rtx, rtx, rtx);
extern rtx        gen_udivmodsi4                  (rtx, rtx, rtx, rtx);
extern rtx        gen_divmodhi4                   (rtx, rtx, rtx, rtx);
extern rtx        gen_udivmodhi4                  (rtx, rtx, rtx, rtx);
extern rtx        gen_andsi3                      (rtx, rtx, rtx);
extern rtx        gen_iorsi3                      (rtx, rtx, rtx);
extern rtx        gen_xorsi3                      (rtx, rtx, rtx);
extern rtx        gen_one_cmplsi2                 (rtx, rtx);
extern rtx        gen_insv                        (rtx, rtx, rtx, rtx);
extern rtx        gen_setf_insn                   (rtx, rtx);
extern rtx        gen_set_z_insn                  (rtx, rtx);
extern rtx        gen_set_nz_insn                 (rtx, rtx);
extern rtx        gen_movsicc_normal_cc           (rtx, rtx, rtx, rtx);
extern rtx        gen_movsicc_reversed_cc         (rtx, rtx, rtx, rtx);
extern rtx        gen_rotlsi3_a                   (rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_rotlsi3_b                   (rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_rotlsi3_v850e3v5            (rtx, rtx, rtx);
extern rtx        gen_fix_loop_counter            (rtx);
extern rtx        gen_doloop_end_internal_loop    (rtx, rtx);
extern rtx        gen_branch_z_normal             (rtx, rtx);
extern rtx        gen_branch_nz_normal            (rtx, rtx);
extern rtx        gen_jump                        (rtx);
extern rtx        gen_indirect_jump               (rtx);
extern rtx        gen_tablejump                   (rtx, rtx);
extern rtx        gen_switch                      (rtx, rtx);
extern rtx        gen_call_internal_short         (rtx, rtx);
extern rtx        gen_call_internal_long          (rtx, rtx);
extern rtx        gen_call_value_internal_short   (rtx, rtx, rtx);
extern rtx        gen_call_value_internal_long    (rtx, rtx, rtx);
extern rtx        gen_nop                         (void);
extern rtx        gen_ashlsi3                     (rtx, rtx, rtx);
extern rtx        gen_ashlsi3_v850e2              (rtx, rtx, rtx);
extern rtx        gen_lshrsi3                     (rtx, rtx, rtx);
extern rtx        gen_lshrsi3_v850e2              (rtx, rtx, rtx);
extern rtx        gen_ashrsi3                     (rtx, rtx, rtx);
extern rtx        gen_ashrsi3_v850e2              (rtx, rtx, rtx);
extern rtx        gen_ffssi2                      (rtx, rtx);
extern rtx        gen_return_simple               (void);
extern rtx        gen_return_internal             (void);
extern rtx        gen_addsf3                      (rtx, rtx, rtx);
extern rtx        gen_adddf3                      (rtx, rtx, rtx);
extern rtx        gen_subsf3                      (rtx, rtx, rtx);
extern rtx        gen_subdf3                      (rtx, rtx, rtx);
extern rtx        gen_mulsf3                      (rtx, rtx, rtx);
extern rtx        gen_muldf3                      (rtx, rtx, rtx);
extern rtx        gen_divsf3                      (rtx, rtx, rtx);
extern rtx        gen_divdf3                      (rtx, rtx, rtx);
extern rtx        gen_minsf3                      (rtx, rtx, rtx);
extern rtx        gen_mindf3                      (rtx, rtx, rtx);
extern rtx        gen_maxsf3                      (rtx, rtx, rtx);
extern rtx        gen_maxdf3                      (rtx, rtx, rtx);
extern rtx        gen_abssf2                      (rtx, rtx);
extern rtx        gen_absdf2                      (rtx, rtx);
extern rtx        gen_negsf2                      (rtx, rtx);
extern rtx        gen_negdf2                      (rtx, rtx);
extern rtx        gen_sqrtsf2                     (rtx, rtx);
extern rtx        gen_sqrtdf2                     (rtx, rtx);
extern rtx        gen_fix_truncsfsi2              (rtx, rtx);
extern rtx        gen_fixuns_truncsfsi2           (rtx, rtx);
extern rtx        gen_fix_truncdfsi2              (rtx, rtx);
extern rtx        gen_fixuns_truncdfsi2           (rtx, rtx);
extern rtx        gen_fix_truncsfdi2              (rtx, rtx);
extern rtx        gen_fixuns_truncsfdi2           (rtx, rtx);
extern rtx        gen_fix_truncdfdi2              (rtx, rtx);
extern rtx        gen_fixuns_truncdfdi2           (rtx, rtx);
extern rtx        gen_floatsisf2                  (rtx, rtx);
extern rtx        gen_unsfloatsisf2               (rtx, rtx);
extern rtx        gen_floatsidf2                  (rtx, rtx);
extern rtx        gen_unsfloatsidf2               (rtx, rtx);
extern rtx        gen_floatdisf2                  (rtx, rtx);
extern rtx        gen_unsfloatdisf2               (rtx, rtx);
extern rtx        gen_floatdidf2                  (rtx, rtx);
extern rtx        gen_unsfloatdidf2               (rtx, rtx);
extern rtx        gen_extendsfdf2                 (rtx, rtx);
extern rtx        gen_truncdfsf2                  (rtx, rtx);
extern rtx        gen_recipsf2                    (rtx, rtx, rtx);
extern rtx        gen_recipdf2                    (rtx, rtx, rtx);
extern rtx        gen_rsqrtsf2                    (rtx, rtx, rtx);
extern rtx        gen_rsqrtdf2                    (rtx, rtx, rtx);
extern rtx        gen_fmasf4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_fmssf4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_fnmasf4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_fnmssf4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_cmpsf_le_insn               (rtx, rtx);
extern rtx        gen_cmpsf_lt_insn               (rtx, rtx);
extern rtx        gen_cmpsf_ge_insn               (rtx, rtx);
extern rtx        gen_cmpsf_gt_insn               (rtx, rtx);
extern rtx        gen_cmpsf_eq_insn               (rtx, rtx);
extern rtx        gen_cmpdf_le_insn               (rtx, rtx);
extern rtx        gen_cmpdf_lt_insn               (rtx, rtx);
extern rtx        gen_cmpdf_ge_insn               (rtx, rtx);
extern rtx        gen_cmpdf_gt_insn               (rtx, rtx);
extern rtx        gen_cmpdf_eq_insn               (rtx, rtx);
extern rtx        gen_trfsr                       (rtx, rtx);
extern rtx        gen_movsfcc_z_insn              (rtx, rtx, rtx, rtx);
extern rtx        gen_movsfcc_nz_insn             (rtx, rtx, rtx, rtx);
extern rtx        gen_movdfcc_z_insn              (rtx, rtx, rtx, rtx);
extern rtx        gen_movdfcc_nz_insn             (rtx, rtx, rtx, rtx);
extern rtx        gen_movedfcc_z_zero             (rtx, rtx, rtx, rtx);
extern rtx        gen_movedfcc_nz_zero            (rtx, rtx, rtx, rtx);
extern rtx        gen_callt_save_interrupt        (void);
extern rtx        gen_callt_return_interrupt      (void);
extern rtx        gen_save_interrupt              (void);
extern rtx        gen_return_interrupt            (void);
extern rtx        gen_callt_save_all_interrupt    (void);
extern rtx        gen_save_all_interrupt          (void);
extern rtx        gen__save_all_interrupt         (void);
extern rtx        gen_callt_restore_all_interrupt (void);
extern rtx        gen_restore_all_interrupt       (void);
extern rtx        gen__restore_all_interrupt      (void);
extern rtx        gen_movdi                       (rtx, rtx);
extern rtx        gen_movqi                       (rtx, rtx);
extern rtx        gen_movhi                       (rtx, rtx);
extern rtx        gen_movsi                       (rtx, rtx);
extern rtx        gen_cbranchsi4                  (rtx, rtx, rtx, rtx);
extern rtx        gen_cstoresi4                   (rtx, rtx, rtx, rtx);
extern rtx        gen_cmpsi                       (rtx, rtx);
extern rtx        gen_cbranchsf4                  (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchdf4                  (rtx, rtx, rtx, rtx);
extern rtx        gen_cmpsf                       (rtx, rtx);
extern rtx        gen_cmpdf                       (rtx, rtx);
extern rtx        gen_mulhisi3                    (rtx, rtx, rtx);
extern rtx        gen_movsicc                     (rtx, rtx, rtx, rtx);
extern rtx        gen_rotlhi3                     (rtx, rtx, rtx);
extern rtx        gen_rotlsi3                     (rtx, rtx, rtx);
extern rtx        gen_doloop_begin                (rtx, rtx);
extern rtx        gen_doloop_end                  (rtx, rtx);
extern rtx        gen_casesi                      (rtx, rtx, rtx, rtx, rtx);
#define GEN_CALL(A, B, C, D) gen_call ((A), (B))
extern rtx        gen_call                        (rtx, rtx);
#define GEN_CALL_VALUE(A, B, C, D, E) gen_call_value ((A), (B), (C))
extern rtx        gen_call_value                  (rtx, rtx, rtx);
extern rtx        gen_zero_extendhisi2            (rtx, rtx);
extern rtx        gen_zero_extendqisi2            (rtx, rtx);
extern rtx        gen_extendhisi2                 (rtx, rtx);
extern rtx        gen_extendqisi2                 (rtx, rtx);
extern rtx        gen_prologue                    (void);
extern rtx        gen_epilogue                    (void);

#endif /* GCC_INSN_FLAGS_H */
