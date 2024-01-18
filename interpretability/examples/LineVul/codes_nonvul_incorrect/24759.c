// commit message qemu@210b580b10 (target=0, prob=0.66461706, correct=False): spapr-rtas: add CPU argument to RTAS calls
/*0  */ target_ulong spapr_rtas_call(sPAPREnvironment *spapr,                            // (5) 0.05117
/*2  */                              uint32_t token, uint32_t nargs, target_ulong args,  // (0) 0.1002
/*4  */                              uint32_t nret, target_ulong rets)                   // (1) 0.08955
/*6  */ {                                                                                // (22) 0.002132
/*8  */     if ((token >= TOKEN_BASE)                                                    // (15) 0.02772
/*10 */         && ((token - TOKEN_BASE) < TOKEN_MAX)) {                                 // (6) 0.05117
/*12 */         struct rtas_call *call = rtas_table + (token - TOKEN_BASE);              // (4) 0.0661
/*16 */         if (call->fn) {                                                          // (13) 0.02985
/*18 */             call->fn(spapr, token, nargs, args, nret, rets);                     // (3) 0.06823
/*20 */             return H_SUCCESS;                                                    // (11) 0.03838
/*22 */         }                                                                        // (19) 0.01706
/*24 */     }                                                                            // (20) 0.008529
/*28 */     /* HACK: Some Linux early debug code uses RTAS display-character,            // (9) 0.04051
/*30 */      * but assumes the token value is 0xa (which it is on some real              // (8) 0.04264
/*32 */      * machines) without looking it up in the device tree.  This                 // (10) 0.03838
/*34 */      * special case makes this work */                                           // (16) 0.02345
/*36 */     if (token == 0xa) {                                                          // (17) 0.02345
/*38 */         rtas_display_character(spapr, 0xa, nargs, args, nret, rets);             // (2) 0.07036
/*40 */         return H_SUCCESS;                                                        // (14) 0.02985
/*42 */     }                                                                            // (21) 0.008529
/*46 */     hcall_dprintf("Unknown RTAS token 0x%x\n", token);                           // (7) 0.04691
/*48 */     rtas_st(rets, 0, -3);                                                        // (12) 0.03412
/*50 */     return H_PARAMETER;                                                          // (18) 0.02345
/*52 */ }                                                                                // (23) 0.002132
