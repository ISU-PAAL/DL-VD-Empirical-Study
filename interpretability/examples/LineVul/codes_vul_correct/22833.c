// commit message FFmpeg@a66c6e28b5 (target=1, prob=0.9835735, correct=True): avcodec/rv34: Fix runtime error: signed integer overflow: 36880 * 66288 cannot be represented in type 'int'
/*0  */ static AVRational update_sar(int old_w, int old_h, AVRational sar, int new_w, int new_h)  // (4) 0.04616
/*2  */ {                                                                                         // (2) 0.06062
/*4  */     // attempt to keep aspect during typical resolution switches                          // (0) 0.5856
/*6  */     if (!sar.num)                                                                         // (1) 0.08148
/*8  */         sar = (AVRational){1, 1};                                                         // (5) 0.04275
/*12 */     sar = av_mul_q(sar, (AVRational){new_h * old_w, new_w * old_h});                      // (3) 0.04718
/*14 */     return sar;                                                                           // (6) 0.007793
/*16 */ }                                                                                         // (7) 0.0008602
