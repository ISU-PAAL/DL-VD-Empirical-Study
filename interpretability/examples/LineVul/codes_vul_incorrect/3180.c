// commit message qemu@0857a06ef7 (target=1, prob=0.4379253, correct=False): target-xtensa: don't generate dead code to access invalid SRs
/*0  */ static void gen_check_sr(DisasContext *dc, uint32_t sr, unsigned access)    // (7) 0.05386
/*2  */ {                                                                           // (19) 0.002342
/*4  */     if (!xtensa_option_bits_enabled(dc->config, sregnames[sr].opt_bits)) {  // (2) 0.07026
/*6  */         if (sregnames[sr].name) {                                           // (13) 0.04215
/*8  */             qemu_log("SR %s is not configured\n", sregnames[sr].name);      // (0) 0.07963
/*10 */         } else {                                                            // (15) 0.02342
/*12 */             qemu_log("SR %d is not implemented\n", sr);                     // (3) 0.06557
/*14 */         }                                                                   // (16) 0.01874
/*16 */         gen_exception_cause(dc, ILLEGAL_INSTRUCTION_CAUSE);                 // (4) 0.06557
/*18 */     } else if (!(sregnames[sr].access & access)) {                          // (12) 0.0445
/*20 */         static const char * const access_text[] = {                         // (14) 0.04215
/*22 */             [SR_R] = "rsr",                                                 // (8) 0.04918
/*24 */             [SR_W] = "wsr",                                                 // (9) 0.04918
/*26 */             [SR_X] = "xsr",                                                 // (10) 0.04918
/*28 */         };                                                                  // (17) 0.01874
/*30 */         assert(access < ARRAY_SIZE(access_text) && access_text[access]);    // (6) 0.06323
/*32 */         qemu_log("SR %s is not available for %s\n", sregnames[sr].name,     // (1) 0.07728
/*34 */                 access_text[access]);                                       // (11) 0.04918
/*36 */         gen_exception_cause(dc, ILLEGAL_INSTRUCTION_CAUSE);                 // (5) 0.06557
/*38 */     }                                                                       // (18) 0.009368
/*40 */ }                                                                           // (20) 0.002342
