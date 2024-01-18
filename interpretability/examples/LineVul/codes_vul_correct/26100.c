// commit message FFmpeg@ac4b32df71 (target=1, prob=0.8780467, correct=True): On2 VP7 decoder
/*0  */ int check_tm_pred4x4_mode(int mode, int mb_x, int mb_y)  // (1) 0.2389
/*2  */ {                                                        // (6) 0.00885
/*4  */     if (!mb_x) {                                         // (3) 0.0885
/*6  */         return mb_y ? VERT_VP8_PRED : DC_129_PRED;       // (0) 0.2566
/*8  */     } else {                                             // (4) 0.0531
/*10 */         return mb_y ? mode : HOR_VP8_PRED;               // (2) 0.2035
/*12 */     }                                                    // (5) 0.0354
/*14 */ }                                                        // (7) 0.00885
