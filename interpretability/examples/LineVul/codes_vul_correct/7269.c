// commit message qemu@821303f59b (target=1, prob=0.9991129, correct=True): Implement assorted pSeries hcalls and RTAS methods
/*0  */ target_ulong spapr_rtas_call(sPAPREnvironment *spapr,                            // (4) 0.08276
/*1  */                              uint32_t token, uint32_t nargs, target_ulong args,  // (0) 0.1621
/*2  */                              uint32_t nret, target_ulong rets)                   // (1) 0.1448
/*3  */ {                                                                                // (11) 0.003448
/*4  */     if ((token >= TOKEN_BASE)                                                    // (9) 0.04483
/*5  */         && ((token - TOKEN_BASE) < TOKEN_MAX)) {                                 // (5) 0.08276
/*6  */         struct rtas_call *call = rtas_table + (token - TOKEN_BASE);              // (3) 0.1069
/*7  */         if (call->fn) {                                                          // (8) 0.04828
/*8  */             call->fn(spapr, token, nargs, args, nret, rets);                     // (2) 0.1103
/*9  */     hcall_dprintf("Unknown RTAS token 0x%x\n", token);                           // (6) 0.07586
/*10 */     rtas_st(rets, 0, -3);                                                        // (7) 0.05517
/*11 */     return H_PARAMETER;                                                          // (10) 0.03793
