// commit message FFmpeg@f1e173049e (target=0, prob=0.102550216, correct=True): avcodec/jpeg2000: Remove CBLK limit
/*0   */ static void encode_clnpass(Jpeg2000T1Context *t1, int width, int height, int bandno, int *nmsedec, int bpno)           // (4) 0.07813
/*2   */ {                                                                                                                      // (14) 0.001953
/*4   */     int y0, x, y, mask = 1 << (bpno + NMSEDEC_FRACBITS);                                                               // (7) 0.05664
/*6   */     for (y0 = 0; y0 < height; y0 += 4)                                                                                 // (9) 0.03906
/*8   */         for (x = 0; x < width; x++){                                                                                   // (10) 0.03906
/*10  */             if (y0 + 3 < height && !(                                                                                  // (8) 0.04297
/*12  */             (t1->flags[y0+1][x+1] & (JPEG2000_T1_SIG_NB | JPEG2000_T1_VIS | JPEG2000_T1_SIG)) ||                       // (1) 0.1133
/*14  */             (t1->flags[y0+2][x+1] & (JPEG2000_T1_SIG_NB | JPEG2000_T1_VIS | JPEG2000_T1_SIG)) ||                       // (0) 0.1133
/*16  */             (t1->flags[y0+3][x+1] & (JPEG2000_T1_SIG_NB | JPEG2000_T1_VIS | JPEG2000_T1_SIG)) ||                       // (2) 0.1133
/*18  */             (t1->flags[y0+4][x+1] & (JPEG2000_T1_SIG_NB | JPEG2000_T1_VIS | JPEG2000_T1_SIG))))                        // (3) 0.1113
/*20  */             {                                                                                                          // (13) 0.02344
/*22  */                 // aggregation mode                                                                                    // (12) 0.03516
/*24  */                 int rlen;                                                                                              // (11) 0.03711
/*26  */                 for (rlen = 0; rlen < 4; rlen++)                                                                       // (6) 0.05859
/*28  */                     if (t1->data[y0+rlen][x] & mask)                                                                   // (5) 0.07227
/*30  */                         break;                                                                                         // 0.0
/*32  */                 ff_mqc_encode(&t1->mqc, t1->mqc.cx_states + MQC_CX_RL, rlen != 4);                                     // 0.0
/*34  */                 if (rlen == 4)                                                                                         // 0.0
/*36  */                     continue;                                                                                          // 0.0
/*38  */                 ff_mqc_encode(&t1->mqc, t1->mqc.cx_states + MQC_CX_UNI, rlen >> 1);                                    // 0.0
/*40  */                 ff_mqc_encode(&t1->mqc, t1->mqc.cx_states + MQC_CX_UNI, rlen & 1);                                     // 0.0
/*42  */                 for (y = y0 + rlen; y < y0 + 4; y++){                                                                  // 0.0
/*44  */                     if (!(t1->flags[y+1][x+1] & (JPEG2000_T1_SIG | JPEG2000_T1_VIS))){                                 // 0.0
/*46  */                         int ctxno = ff_jpeg2000_getsigctxno(t1->flags[y+1][x+1], bandno);                              // 0.0
/*48  */                         if (y > y0 + rlen)                                                                             // 0.0
/*50  */                             ff_mqc_encode(&t1->mqc, t1->mqc.cx_states + ctxno, t1->data[y][x] & mask ? 1:0);           // 0.0
/*52  */                         if (t1->data[y][x] & mask){ // newly significant                                               // 0.0
/*54  */                             int xorbit;                                                                                // 0.0
/*56  */                             int ctxno = ff_jpeg2000_getsgnctxno(t1->flags[y+1][x+1], &xorbit);                         // 0.0
/*58  */                             *nmsedec += getnmsedec_sig(t1->data[y][x], bpno + NMSEDEC_FRACBITS);                       // 0.0
/*60  */                             ff_mqc_encode(&t1->mqc, t1->mqc.cx_states + ctxno, (t1->flags[y+1][x+1] >> 15) ^ xorbit);  // 0.0
/*62  */                             ff_jpeg2000_set_significance(t1, x, y, t1->flags[y+1][x+1] >> 15);                         // 0.0
/*64  */                         }                                                                                              // 0.0
/*66  */                     }                                                                                                  // 0.0
/*68  */                     t1->flags[y+1][x+1] &= ~JPEG2000_T1_VIS;                                                           // 0.0
/*70  */                 }                                                                                                      // 0.0
/*72  */             } else{                                                                                                    // 0.0
/*74  */                 for (y = y0; y < y0 + 4 && y < height; y++){                                                           // 0.0
/*76  */                     if (!(t1->flags[y+1][x+1] & (JPEG2000_T1_SIG | JPEG2000_T1_VIS))){                                 // 0.0
/*78  */                         int ctxno = ff_jpeg2000_getsigctxno(t1->flags[y+1][x+1], bandno);                              // 0.0
/*80  */                         ff_mqc_encode(&t1->mqc, t1->mqc.cx_states + ctxno, t1->data[y][x] & mask ? 1:0);               // 0.0
/*82  */                         if (t1->data[y][x] & mask){ // newly significant                                               // 0.0
/*84  */                             int xorbit;                                                                                // 0.0
/*86  */                             int ctxno = ff_jpeg2000_getsgnctxno(t1->flags[y+1][x+1], &xorbit);                         // 0.0
/*88  */                             *nmsedec += getnmsedec_sig(t1->data[y][x], bpno + NMSEDEC_FRACBITS);                       // 0.0
/*90  */                             ff_mqc_encode(&t1->mqc, t1->mqc.cx_states + ctxno, (t1->flags[y+1][x+1] >> 15) ^ xorbit);  // 0.0
/*92  */                             ff_jpeg2000_set_significance(t1, x, y, t1->flags[y+1][x+1] >> 15);                         // 0.0
/*94  */                         }                                                                                              // 0.0
/*96  */                     }                                                                                                  // 0.0
/*98  */                     t1->flags[y+1][x+1] &= ~JPEG2000_T1_VIS;                                                           // 0.0
/*100 */                 }                                                                                                      // 0.0
/*102 */             }                                                                                                          // 0.0
/*104 */         }                                                                                                              // 0.0
/*106 */ }                                                                                                                      // 0.0
