// commit message FFmpeg@e5dd4ae728 (target=1, prob=0.68678665, correct=True): assdec: avoid a possible NULL dereference.
/*0  */ static int ass_decode_frame(AVCodecContext *avctx, void *data, int *got_sub_ptr,  // (2) 0.1003
/*2  */                             AVPacket *avpkt)                                      // (1) 0.1211
/*4  */ {                                                                                 // (15) 0.00346
/*6  */     const char *ptr = avpkt->data;                                                // (6) 0.04844
/*8  */     int len, size = avpkt->size;                                                  // (7) 0.04844
/*12 */     while (size > 0) {                                                            // (12) 0.0346
/*14 */         ASSDialog *dialog = ff_ass_split_dialog(avctx->priv_data, ptr, 0, NULL);  // (0) 0.1211
/*16 */         int duration = dialog->end - dialog->start;                               // (4) 0.06228
/*18 */         len = ff_ass_add_rect(data, ptr, 0, duration, 1);                         // (3) 0.09343
/*20 */         if (len < 0)                                                              // (9) 0.04498
/*22 */             return len;                                                           // (8) 0.04844
/*24 */         ptr  += len;                                                              // (10) 0.04152
/*26 */         size -= len;                                                              // (11) 0.03806
/*28 */     }                                                                             // (14) 0.01384
/*32 */     *got_sub_ptr = avpkt->size > 0;                                               // (5) 0.06228
/*34 */     return avpkt->size;                                                           // (13) 0.0346
/*36 */ }                                                                                 // (16) 0.00346
