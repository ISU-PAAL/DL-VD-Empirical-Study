// commit message qemu@5e755519ac (target=0, prob=0.0064262026, correct=True): Don't check the FPU state for each FPU instruction, use hflags to handle this per-tb.
/*0  */ void op_cp1_64bitmode(void)                          // (2) 0.1412
/*2  */ {                                                    // (5) 0.01176
/*4  */     if (!(env->CP0_Status & (1 << CP0St_FR))) {      // (1) 0.2706
/*6  */         CALL_FROM_TB1(do_raise_exception, EXCP_RI);  // (0) 0.3176
/*8  */     }                                                // (4) 0.04706
/*10 */     RETURN();                                        // (3) 0.07059
/*12 */ }                                                    // (6) 0.01176
