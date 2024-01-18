// commit message FFmpeg@5e53486545 (target=0, prob=0.40115428, correct=True): typo fix: inited --> initialized
/*0  */ static int decode_init_mp3on4(AVCodecContext * avctx)                              // (11) 0.03711
/*2  */ {                                                                                  // (27) 0.001953
/*4  */     MP3On4DecodeContext *s = avctx->priv_data;                                     // (8) 0.03906
/*6  */     int i;                                                                         // (23) 0.01172
/*10 */     if ((avctx->extradata_size < 2) || (avctx->extradata == NULL)) {               // (4) 0.05469
/*12 */         av_log(avctx, AV_LOG_ERROR, "Codec extradata missing or too short.\n");    // (0) 0.06445
/*14 */         return -1;                                                                 // (21) 0.02148
/*16 */     }                                                                              // (25) 0.007812
/*20 */     s->chan_cfg = (((unsigned char *)avctx->extradata)[1] >> 3) & 0x0f;            // (1) 0.0625
/*22 */     s->frames = mp3Frames[s->chan_cfg];                                            // (14) 0.0332
/*24 */     if(!s->frames) {                                                               // (19) 0.02148
/*26 */         av_log(avctx, AV_LOG_ERROR, "Invalid channel config number.\n");           // (2) 0.05664
/*28 */         return -1;                                                                 // (20) 0.02148
/*30 */     }                                                                              // (26) 0.007812
/*32 */     avctx->channels = mp3Channels[s->chan_cfg];                                    // (9) 0.03906
/*36 */     /* Init the first mp3 decoder in standard way, so that all tables get builded  // (7) 0.04297
/*38 */      * We replace avctx->priv_data with the context of the first decoder so that   // (6) 0.04492
/*40 */      * decode_init() does not have to be changed.                                  // (15) 0.03125
/*42 */      * Other decoders will be inited here copying data from the first context      // (10) 0.03906
/*44 */      */                                                                            // (24) 0.009766
/*46 */     // Allocate zeroed memory for the first decoder context                        // (16) 0.0293
/*48 */     s->mp3decctx[0] = av_mallocz(sizeof(MPADecodeContext));                        // (3) 0.05469
/*50 */     // Put decoder context in place to make init_decode() happy                    // (13) 0.03516
/*52 */     avctx->priv_data = s->mp3decctx[0];                                            // (12) 0.03711
/*54 */     decode_init(avctx);                                                            // (22) 0.01953
/*56 */     // Restore mp3on4 context pointer                                              // (18) 0.02148
/*58 */     avctx->priv_data = s;                                                          // (17) 0.02344
/*60 */     s->mp3decctx[0]->adu_mode = 1; // Set adu mode                                 // (5) 0.04883
/*64 */     /* Create a separate codec/context for each frame (first is already ok).       // 0.0
/*66 */      * Each frame is 1 or 2 channels - up to 5 frames allowed                      // 0.0
/*68 */      */                                                                            // 0.0
/*70 */     for (i = 1; i < s->frames; i++) {                                              // 0.0
/*72 */         s->mp3decctx[i] = av_mallocz(sizeof(MPADecodeContext));                    // 0.0
/*74 */         s->mp3decctx[i]->compute_antialias = s->mp3decctx[0]->compute_antialias;   // 0.0
/*76 */         s->mp3decctx[i]->adu_mode = 1;                                             // 0.0
/*78 */         s->mp3decctx[i]->avctx = avctx;                                            // 0.0
/*80 */     }                                                                              // 0.0
/*84 */     return 0;                                                                      // 0.0
/*86 */ }                                                                                  // 0.0
