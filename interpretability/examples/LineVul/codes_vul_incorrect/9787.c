// commit message qemu@e853ea1cc6 (target=1, prob=0.11902336, correct=False): qga: fix uninitialized value warning for win32
/*0  */ GIOStatus ga_channel_write_all(GAChannel *c, const char *buf, size_t size)  // (0) 0.1215
/*2  */ {                                                                           // (13) 0.004673
/*4  */     GIOStatus status = G_IO_STATUS_NORMAL;                                  // (4) 0.08411
/*6  */     size_t count;                                                           // (9) 0.03738
/*10 */     while (size) {                                                          // (8) 0.03738
/*12 */         status = ga_channel_write(c, buf, size, &count);                    // (1) 0.1121
/*14 */         if (status == G_IO_STATUS_NORMAL) {                                 // (3) 0.1028
/*16 */             size -= count;                                                  // (5) 0.07009
/*18 */             buf += count;                                                   // (6) 0.07009
/*20 */         } else if (status != G_IO_STATUS_AGAIN) {                           // (2) 0.1121
/*22 */             break;                                                          // (7) 0.06075
/*24 */         }                                                                   // (10) 0.03738
/*26 */     }                                                                       // (12) 0.01869
/*30 */     return status;                                                          // (11) 0.02804
/*32 */ }                                                                           // (14) 0.004673
