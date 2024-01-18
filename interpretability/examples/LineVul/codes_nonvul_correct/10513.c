// commit message FFmpeg@ccb76ad91f (target=0, prob=0.46050918, correct=True): cook: check decouple values.
/*0  */ static void decouple_info(COOKContext *q, COOKSubpacket *p, int *decouple_tab)           // (2) 0.09929
/*2  */ {                                                                                        // (14) 0.003546
/*4  */     int i;                                                                               // (12) 0.02128
/*6  */     int vlc    = get_bits1(&q->gb);                                                      // (5) 0.06738
/*8  */     int start  = cplband[p->js_subband_start];                                           // (3) 0.07092
/*10 */     int end    = cplband[p->subbands - 1];                                               // (4) 0.07092
/*12 */     int length = end - start + 1;                                                        // (8) 0.04255
/*16 */     if (start > end)                                                                     // (9) 0.03191
/*18 */         return;                                                                          // (10) 0.03191
/*22 */     if (vlc)                                                                             // (11) 0.02837
/*24 */         for (i = 0; i < length; i++)                                                     // (6) 0.06738
/*26 */             decouple_tab[start + i] = get_vlc2(&q->gb, p->ccpl.table, p->ccpl.bits, 2);  // (0) 0.1667
/*28 */     else                                                                                 // (13) 0.01418
/*30 */         for (i = 0; i < length; i++)                                                     // (7) 0.06738
/*32 */             decouple_tab[start + i] = get_bits(&q->gb, p->js_vlc_bits);                  // (1) 0.1348
/*34 */ }                                                                                        // (15) 0.003546
