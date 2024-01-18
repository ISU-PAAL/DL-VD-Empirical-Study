// commit message FFmpeg@69d0a2922f (target=0, prob=0.4480349, correct=True): sonic: cleanup/simplify num_taps check
/*0   */ static av_cold int sonic_encode_init(AVCodecContext *avctx)                                                    // (6) 0.03907
/*2   */ {                                                                                                              // (34) 0.001958
/*4   */     SonicContext *s = avctx->priv_data;                                                                        // (14) 0.0293
/*6   */     PutBitContext pb;                                                                                          // (21) 0.01758
/*8   */     int i, version = 0;                                                                                        // (20) 0.01955
/*12  */     if (avctx->channels > MAX_CHANNELS)                                                                        // (8) 0.0332
/*14  */     {                                                                                                          // (28) 0.007812
/*16  */         av_log(avctx, AV_LOG_ERROR, "Only mono and stereo streams are supported by now\n");                    // (0) 0.06445
/*18  */         return AVERROR(EINVAL); /* only stereo or mono for now */                                              // (5) 0.04687
/*20  */     }                                                                                                          // (29) 0.007812
/*24  */     if (avctx->channels == 2)                                                                                  // (19) 0.02539
/*26  */         s->decorrelation = MID_SIDE;                                                                           // (7) 0.03515
/*28  */     else                                                                                                       // (31) 0.007812
/*30  */         s->decorrelation = 3;                                                                                  // (17) 0.0293
/*34  */     if (avctx->codec->id == AV_CODEC_ID_SONIC_LS)                                                              // (3) 0.05078
/*36  */     {                                                                                                          // (33) 0.007812
/*38  */         s->lossless = 1;                                                                                       // (18) 0.02734
/*40  */         s->num_taps = 32;                                                                                      // (13) 0.03125
/*42  */         s->downsampling = 1;                                                                                   // (16) 0.0293
/*44  */         s->quantization = 0.0;                                                                                 // (11) 0.03125
/*46  */     }                                                                                                          // (25) 0.007812
/*48  */     else                                                                                                       // (27) 0.007812
/*50  */     {                                                                                                          // (32) 0.007812
/*52  */         s->num_taps = 128;                                                                                     // (12) 0.03125
/*54  */         s->downsampling = 2;                                                                                   // (15) 0.0293
/*56  */         s->quantization = 1.0;                                                                                 // (10) 0.03125
/*58  */     }                                                                                                          // (26) 0.007812
/*62  */     // max tap 2048                                                                                            // (22) 0.01367
/*64  */     if ((s->num_taps < 32) || (s->num_taps > 1024) ||                                                          // (4) 0.05078
/*66  */         ((s->num_taps>>5)<<5 != s->num_taps))                                                                  // (2) 0.05273
/*68  */     {                                                                                                          // (30) 0.007812
/*70  */         av_log(avctx, AV_LOG_ERROR, "Invalid number of taps\n");                                               // (1) 0.05468
/*72  */         return AVERROR_INVALIDDATA;                                                                            // (9) 0.0332
/*74  */     }                                                                                                          // (24) 0.007812
/*78  */     // generate taps                                                                                           // (23) 0.01172
/*80  */     s->tap_quant = av_calloc(s->num_taps, sizeof(*s->tap_quant));                                              // 0.0
/*82  */     for (i = 0; i < s->num_taps; i++)                                                                          // 0.0
/*84  */         s->tap_quant[i] = ff_sqrt(i+1);                                                                        // 0.0
/*88  */     s->channels = avctx->channels;                                                                             // 0.0
/*90  */     s->samplerate = avctx->sample_rate;                                                                        // 0.0
/*94  */     s->block_align = 2048LL*s->samplerate/(44100*s->downsampling);                                             // 0.0
/*96  */     s->frame_size = s->channels*s->block_align*s->downsampling;                                                // 0.0
/*100 */     s->tail_size = s->num_taps*s->channels;                                                                    // 0.0
/*102 */     s->tail = av_calloc(s->tail_size, sizeof(*s->tail));                                                       // 0.0
/*104 */     if (!s->tail)                                                                                              // 0.0
/*106 */         return AVERROR(ENOMEM);                                                                                // 0.0
/*110 */     s->predictor_k = av_calloc(s->num_taps, sizeof(*s->predictor_k) );                                         // 0.0
/*112 */     if (!s->predictor_k)                                                                                       // 0.0
/*114 */         return AVERROR(ENOMEM);                                                                                // 0.0
/*118 */     for (i = 0; i < s->channels; i++)                                                                          // 0.0
/*120 */     {                                                                                                          // 0.0
/*122 */         s->coded_samples[i] = av_calloc(s->block_align, sizeof(**s->coded_samples));                           // 0.0
/*124 */         if (!s->coded_samples[i])                                                                              // 0.0
/*126 */             return AVERROR(ENOMEM);                                                                            // 0.0
/*128 */     }                                                                                                          // 0.0
/*132 */     s->int_samples = av_calloc(s->frame_size, sizeof(*s->int_samples));                                        // 0.0
/*136 */     s->window_size = ((2*s->tail_size)+s->frame_size);                                                         // 0.0
/*138 */     s->window = av_calloc(s->window_size, sizeof(*s->window));                                                 // 0.0
/*140 */     if (!s->window)                                                                                            // 0.0
/*142 */         return AVERROR(ENOMEM);                                                                                // 0.0
/*146 */     avctx->extradata = av_mallocz(16);                                                                         // 0.0
/*148 */     if (!avctx->extradata)                                                                                     // 0.0
/*150 */         return AVERROR(ENOMEM);                                                                                // 0.0
/*152 */     init_put_bits(&pb, avctx->extradata, 16*8);                                                                // 0.0
/*156 */     put_bits(&pb, 2, version); // version                                                                      // 0.0
/*158 */     if (version == 1)                                                                                          // 0.0
/*160 */     {                                                                                                          // 0.0
/*162 */         put_bits(&pb, 2, s->channels);                                                                         // 0.0
/*164 */         put_bits(&pb, 4, code_samplerate(s->samplerate));                                                      // 0.0
/*166 */     }                                                                                                          // 0.0
/*168 */     put_bits(&pb, 1, s->lossless);                                                                             // 0.0
/*170 */     if (!s->lossless)                                                                                          // 0.0
/*172 */         put_bits(&pb, 3, SAMPLE_SHIFT); // XXX FIXME: sample precision                                         // 0.0
/*174 */     put_bits(&pb, 2, s->decorrelation);                                                                        // 0.0
/*176 */     put_bits(&pb, 2, s->downsampling);                                                                         // 0.0
/*178 */     put_bits(&pb, 5, (s->num_taps >> 5)-1); // 32..1024                                                        // 0.0
/*180 */     put_bits(&pb, 1, 0); // XXX FIXME: no custom tap quant table                                               // 0.0
/*184 */     flush_put_bits(&pb);                                                                                       // 0.0
/*186 */     avctx->extradata_size = put_bits_count(&pb)/8;                                                             // 0.0
/*190 */     av_log(avctx, AV_LOG_INFO, "Sonic: ver: %d ls: %d dr: %d taps: %d block: %d frame: %d downsamp: %d\n",     // 0.0
/*192 */         version, s->lossless, s->decorrelation, s->num_taps, s->block_align, s->frame_size, s->downsampling);  // 0.0
/*196 */     avctx->frame_size = s->block_align*s->downsampling;                                                        // 0.0
/*200 */     return 0;                                                                                                  // 0.0
/*202 */ }                                                                                                              // 0.0
