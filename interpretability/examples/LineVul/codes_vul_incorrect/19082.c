// commit message qemu@8be487d8f1 (target=1, prob=0.040760424, correct=False): sdhci: convert the DPRINT() calls into trace events
/*0  */ sdhci_buff_access_is_sequential(SDHCIState *s, unsigned byte_num)      // (0) 0.2
/*2  */ {                                                                      // (7) 0.008
/*4  */     if ((s->data_count & 0x3) != byte_num) {                           // (2) 0.168
/*6  */         ERRPRINT("Non-sequential access to Buffer Data Port register"  // (1) 0.184
/*8  */                 "is prohibited\n");                                    // (3) 0.168
/*10 */         return false;                                                  // (4) 0.08
/*12 */     }                                                                  // (6) 0.032
/*14 */     return true;                                                       // (5) 0.048
/*16 */ }                                                                      // (8) 0.008
