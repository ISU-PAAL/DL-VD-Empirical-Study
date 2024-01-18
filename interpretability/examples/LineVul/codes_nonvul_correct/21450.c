// commit message qemu@f61eddcb2b (target=0, prob=0.15767178, correct=True): vl.c: Replace fprintf(stderr) with error_report()
/*0  */ static int bt_hci_parse(const char *str)                                         // (10) 0.04688
/*2  */ {                                                                                // (20) 0.003125
/*4  */     struct HCIInfo *hci;                                                         // (13) 0.03438
/*6  */     bdaddr_t bdaddr;                                                             // (12) 0.0375
/*10 */     if (nb_hcis >= MAX_NICS) {                                                   // (4) 0.05313
/*12 */         fprintf(stderr, "qemu: Too many bluetooth HCIs (max %i).\n", MAX_NICS);  // (0) 0.1188
/*14 */         return -1;                                                               // (14) 0.03438
/*16 */     }                                                                            // (18) 0.0125
/*20 */     hci = hci_init(str);                                                         // (11) 0.04063
/*22 */     if (!hci)                                                                    // (16) 0.025
/*24 */         return -1;                                                               // (15) 0.03438
/*28 */     bdaddr.b[0] = 0x52;                                                          // (5) 0.05
/*30 */     bdaddr.b[1] = 0x54;                                                          // (6) 0.05
/*32 */     bdaddr.b[2] = 0x00;                                                          // (7) 0.05
/*34 */     bdaddr.b[3] = 0x12;                                                          // (8) 0.05
/*36 */     bdaddr.b[4] = 0x34;                                                          // (9) 0.05
/*38 */     bdaddr.b[5] = 0x56 + nb_hcis;                                                // (1) 0.07188
/*40 */     hci->bdaddr_set(hci, bdaddr.b);                                              // (2) 0.0625
/*44 */     hci_table[nb_hcis++] = hci;                                                  // (3) 0.05938
/*48 */     return 0;                                                                    // (17) 0.01875
/*50 */ }                                                                                // (19) 0.003125
