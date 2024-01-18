// commit message FFmpeg@2df0c32ea1 (target=0, prob=0.72541636, correct=False): lavc: use a separate field for exporting audio encoder padding
/*0   */ static av_cold int g722_encode_init(AVCodecContext * avctx)                       // (6) 0.04297
/*2   */ {                                                                                 // (24) 0.001953
/*4   */     G722Context *c = avctx->priv_data;                                            // (11) 0.0332
/*6   */     int ret;                                                                      // (21) 0.01172
/*10  */     if (avctx->channels != 1) {                                                   // (15) 0.02734
/*12  */         av_log(avctx, AV_LOG_ERROR, "Only mono tracks are allowed.\n");           // (4) 0.05859
/*14  */         return AVERROR_INVALIDDATA;                                               // (12) 0.0332
/*16  */     }                                                                             // (23) 0.007812
/*20  */     c->band[0].scale_factor = 8;                                                  // (13) 0.0293
/*22  */     c->band[1].scale_factor = 2;                                                  // (14) 0.0293
/*24  */     c->prev_samples_pos = 22;                                                     // (16) 0.02734
/*28  */     if (avctx->trellis) {                                                         // (17) 0.02539
/*30  */         int frontier = 1 << avctx->trellis;                                       // (9) 0.03711
/*32  */         int max_paths = frontier * FREEZE_INTERVAL;                               // (7) 0.04102
/*34  */         int i;                                                                    // (19) 0.01953
/*36  */         for (i = 0; i < 2; i++) {                                                 // (8) 0.03906
/*38  */             c->paths[i] = av_mallocz(max_paths * sizeof(**c->paths));             // (3) 0.07422
/*40  */             c->node_buf[i] = av_mallocz(2 * frontier * sizeof(**c->node_buf));    // (2) 0.07617
/*42  */             c->nodep_buf[i] = av_mallocz(2 * frontier * sizeof(**c->nodep_buf));  // (0) 0.08398
/*44  */             if (!c->paths[i] || !c->node_buf[i] || !c->nodep_buf[i]) {            // (1) 0.08398
/*46  */                 ret = AVERROR(ENOMEM);                                            // (5) 0.04883
/*48  */                 goto error;                                                       // (10) 0.03516
/*50  */             }                                                                     // (18) 0.02344
/*52  */         }                                                                         // (20) 0.01562
/*54  */     }                                                                             // (22) 0.007812
/*58  */     if (avctx->frame_size) {                                                      // 0.0
/*60  */         /* validate frame size */                                                 // 0.0
/*62  */         if (avctx->frame_size & 1 || avctx->frame_size > MAX_FRAME_SIZE) {        // 0.0
/*64  */             int new_frame_size;                                                   // 0.0
/*68  */             if (avctx->frame_size == 1)                                           // 0.0
/*70  */                 new_frame_size = 2;                                               // 0.0
/*72  */             else if (avctx->frame_size > MAX_FRAME_SIZE)                          // 0.0
/*74  */                 new_frame_size = MAX_FRAME_SIZE;                                  // 0.0
/*76  */             else                                                                  // 0.0
/*78  */                 new_frame_size = avctx->frame_size - 1;                           // 0.0
/*82  */             av_log(avctx, AV_LOG_WARNING, "Requested frame size is not "          // 0.0
/*84  */                    "allowed. Using %d instead of %d\n", new_frame_size,           // 0.0
/*86  */                    avctx->frame_size);                                            // 0.0
/*88  */             avctx->frame_size = new_frame_size;                                   // 0.0
/*90  */         }                                                                         // 0.0
/*92  */     } else {                                                                      // 0.0
/*94  */         /* This is arbitrary. We use 320 because it's 20ms @ 16kHz, which is      // 0.0
/*96  */            a common packet size for VoIP applications */                          // 0.0
/*98  */         avctx->frame_size = 320;                                                  // 0.0
/*100 */     }                                                                             // 0.0
/*102 */     avctx->delay = 22;                                                            // 0.0
/*106 */     if (avctx->trellis) {                                                         // 0.0
/*108 */         /* validate trellis */                                                    // 0.0
/*110 */         if (avctx->trellis < MIN_TRELLIS || avctx->trellis > MAX_TRELLIS) {       // 0.0
/*112 */             int new_trellis = av_clip(avctx->trellis, MIN_TRELLIS, MAX_TRELLIS);  // 0.0
/*114 */             av_log(avctx, AV_LOG_WARNING, "Requested trellis value is not "       // 0.0
/*116 */                    "allowed. Using %d instead of %d\n", new_trellis,              // 0.0
/*118 */                    avctx->trellis);                                               // 0.0
/*120 */             avctx->trellis = new_trellis;                                         // 0.0
/*122 */         }                                                                         // 0.0
/*124 */     }                                                                             // 0.0
/*128 */     return 0;                                                                     // 0.0
/*130 */ error:                                                                            // 0.0
/*132 */     g722_encode_close(avctx);                                                     // 0.0
/*134 */     return ret;                                                                   // 0.0
/*136 */ }                                                                                 // 0.0
