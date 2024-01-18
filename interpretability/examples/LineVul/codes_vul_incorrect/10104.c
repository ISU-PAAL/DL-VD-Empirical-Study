// commit message qemu@bbade20633 (target=1, prob=0.014716578, correct=False): pseries: Add more parameter validation in RTAS time of day functions
/*0  */ static void rtas_get_time_of_day(PowerPCCPU *cpu, sPAPREnvironment *spapr,  // (3) 0.07176
/*2  */                                  uint32_t token, uint32_t nargs,            // (1) 0.1009
/*4  */                                  target_ulong args,                         // (2) 0.0852
/*6  */                                  uint32_t nret, target_ulong rets)          // (0) 0.1031
/*8  */ {                                                                           // (18) 0.002242
/*10 */     struct tm tm;                                                           // (15) 0.02018
/*14 */     if (nret != 8) {                                                        // (14) 0.02466
/*16 */         rtas_st(rets, 0, RTAS_OUT_PARAM_ERROR);                             // (4) 0.06053
/*18 */         return;                                                             // (16) 0.02018
/*20 */     }                                                                       // (17) 0.008968
/*24 */     qemu_get_timedate(&tm, spapr->rtc_offset);                              // (6) 0.05381
/*28 */     rtas_st(rets, 0, RTAS_OUT_SUCCESS);                                     // (9) 0.04932
/*30 */     rtas_st(rets, 1, tm.tm_year + 1900);                                    // (8) 0.04932
/*32 */     rtas_st(rets, 2, tm.tm_mon + 1);                                        // (7) 0.04933
/*34 */     rtas_st(rets, 3, tm.tm_mday);                                           // (10) 0.04708
/*36 */     rtas_st(rets, 4, tm.tm_hour);                                           // (11) 0.04484
/*38 */     rtas_st(rets, 5, tm.tm_min);                                            // (13) 0.04484
/*40 */     rtas_st(rets, 6, tm.tm_sec);                                            // (12) 0.04484
/*42 */     rtas_st(rets, 7, 0); /* we don't do nanoseconds */                      // (5) 0.05605
/*44 */ }                                                                           // (19) 0.002242
