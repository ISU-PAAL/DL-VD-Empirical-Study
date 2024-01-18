// commit message qemu@7b899f4dd5 (target=0, prob=0.7593883, correct=False): qtest: Avoid passing raw strings through hmp()
/*0  */ static void test_info_commands(void)                                       // (16) 0.02989
/*2  */ {                                                                          // (23) 0.002717
/*4  */     char *resp, *info, *info_buf, *endp;                                   // (4) 0.05163
/*8  */     info_buf = info = hmp("help info");                                    // (8) 0.04076
/*12 */     while (*info) {                                                        // (19) 0.02174
/*14 */         /* Extract the info command, ignore parameters and description */  // (5) 0.04891
/*16 */         g_assert(strncmp(info, "info ", 5) == 0);                          // (1) 0.06793
/*18 */         endp = strchr(&info[5], ' ');                                      // (3) 0.05707
/*20 */         g_assert(endp != NULL);                                            // (6) 0.04348
/*22 */         *endp = '\0';                                                      // (9) 0.04076
/*24 */         /* Now run the info command */                                     // (10) 0.03804
/*26 */         if (verbose) {                                                     // (12) 0.03533
/*28 */             fprintf(stderr, "\t%s\n", info);                               // (0) 0.07337
/*30 */         }                                                                  // (20) 0.02174
/*32 */         resp = hmp(info);                                                  // (11) 0.03804
/*34 */         g_free(resp);                                                      // (13) 0.03533
/*36 */         /* And move forward to the next line */                            // (7) 0.04348
/*38 */         info = strchr(endp + 1, '\n');                                     // (2) 0.05978
/*40 */         if (!info) {                                                       // (15) 0.03261
/*42 */             break;                                                         // (14) 0.03533
/*44 */         }                                                                  // (21) 0.02174
/*46 */         info += 1;                                                         // (17) 0.02989
/*48 */     }                                                                      // (22) 0.01087
/*52 */     g_free(info_buf);                                                      // (18) 0.02989
/*54 */ }                                                                          // (24) 0.002717
