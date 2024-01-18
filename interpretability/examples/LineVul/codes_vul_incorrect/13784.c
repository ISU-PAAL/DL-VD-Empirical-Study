// commit message qemu@192cf55cc0 (target=1, prob=0.17231065, correct=False): ahci: avoid #ifdef DEBUG_AHCI bitrot
/*0  */ static void debug_print_fis(uint8_t *fis, int cmd_len)  // (2) 0.1176
/*2  */ {                                                       // (12) 0.005348
/*4  */ #ifdef DEBUG_AHCI                                       // (7) 0.04278
/*6  */     int i;                                              // (9) 0.03209
/*10 */     fprintf(stderr, "fis:");                            // (5) 0.08021
/*12 */     for (i = 0; i < cmd_len; i++) {                     // (3) 0.09626
/*14 */         if ((i & 0xf) == 0) {                           // (4) 0.09626
/*16 */             fprintf(stderr, "\n%02x:",i);               // (0) 0.1444
/*18 */         }                                               // (8) 0.04278
/*20 */         fprintf(stderr, "%02x ",fis[i]);                // (1) 0.123
/*22 */     }                                                   // (10) 0.02139
/*24 */     fprintf(stderr, "\n");                              // (6) 0.06952
/*26 */ #endif                                                  // (11) 0.0107
/*28 */ }                                                       // (13) 0.005348
