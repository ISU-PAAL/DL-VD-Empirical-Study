// commit message qemu@9307c4c1d9 (target=0, prob=0.067126095, correct=True): improved monitor: type check, expression evaluator, memory dump, disassembly
/*0  */ static void do_log(int argc, const char **argv)  // (3) 0.07805
/*2  */ {                                                // (16) 0.004878
/*4  */     int mask;                                    // (12) 0.02927
/*6  */                                                  // (14) 0.01951
/*8  */     if (argc != 2)                               // (8) 0.04878
/*10 */         goto help;                               // (9) 0.04878
/*12 */     if (!strcmp(argv[1], "none")) {              // (2) 0.08293
/*14 */         mask = 0;                                // (6) 0.05366
/*16 */     } else {                                     // (13) 0.02927
/*18 */         mask = cpu_str_to_log_mask(argv[1]);     // (0) 0.1171
/*20 */         if (!mask) {                             // (5) 0.05854
/*22 */         help:                                    // (10) 0.0439
/*24 */             help_cmd(argv[0]);                   // (1) 0.09756
/*26 */             return;                              // (4) 0.06341
/*28 */         }                                        // (11) 0.03902
/*30 */     }                                            // (15) 0.01951
/*32 */     cpu_set_log(mask);                           // (7) 0.05366
/*34 */ }                                                // (17) 0.004878
