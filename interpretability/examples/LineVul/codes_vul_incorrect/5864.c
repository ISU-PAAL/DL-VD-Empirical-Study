// commit message FFmpeg@e3052ce7b1 (target=1, prob=0.36388597, correct=False): Revert r10892, it's wrong and no longer needed to prevent crashes
/*0  */ static int get_num(ByteIOContext *pb, int *len)  // (2) 0.03188
/*2  */ {                                                // (8) 0.004226
/*4  */     int n, n1;                                   // (6) 0.007406
/*8  */     n = get_be16(pb);                            // (3) 0.01214
/*10 */     (*len)-=2;                                   // (1) 0.04322
/*12 */ //    n &= 0x7FFF;                               // (0) 0.4688
/*14 */     if (n >= 0x4000) {                           // (4) 0.01202
/*16 */         return n - 0x4000;                       // (11) 0.003223
/*18 */     } else {                                     // (12) 0.002695
/*20 */         n1 = get_be16(pb);                       // (9) 0.004072
/*22 */         (*len)-=2;                               // (7) 0.004493
/*24 */         return (n << 16) | n1;                   // (5) 0.009243
/*26 */     }                                            // (13) 0.001973
/*28 */ }                                                // (10) 0.00326
