// commit message qemu@5e755519ac (target=0, prob=0.008789971, correct=True): Don't check the FPU state for each FPU instruction, use hflags to handle this per-tb.
/*0  */ void op_cp1_registers(void)                                      // (2) 0.1196
/*2  */ {                                                                // (5) 0.01087
/*4  */     if (!(env->CP0_Status & (1 << CP0St_FR)) && (PARAM1 & 1)) {  // (0) 0.337
/*6  */         CALL_FROM_TB1(do_raise_exception, EXCP_RI);              // (1) 0.2935
/*8  */     }                                                            // (4) 0.04348
/*10 */     RETURN();                                                    // (3) 0.06522
/*12 */ }                                                                // (6) 0.01087
