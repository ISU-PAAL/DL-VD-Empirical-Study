// commit message FFmpeg@74b1bf632f (target=1, prob=0.25412875, correct=False): mp3: Make the extrasize explicit
/*0   */ static int mp_decode_frame(MPADecodeContext *s, OUT_INT **samples,                             // (4) 0.04684
/*2   */                            const uint8_t *buf, int buf_size)                                   // (0) 0.07602
/*4   */ {                                                                                              // (27) 0.002537
/*6   */     int i, nb_frames, ch, ret;                                                                 // (15) 0.02958
/*8   */     OUT_INT *samples_ptr;                                                                      // (17) 0.0234
/*12  */     init_get_bits(&s->gb, buf + HEADER_SIZE, (buf_size - HEADER_SIZE) * 8);                    // (1) 0.06431
/*16  */     /* skip error protection field */                                                          // (20) 0.01754
/*18  */     if (s->error_protection)                                                                   // (18) 0.02143
/*20  */         skip_bits(&s->gb, 16);                                                                 // (13) 0.03312
/*24  */     switch(s->layer) {                                                                         // (19) 0.01948
/*26  */     case 1:                                                                                    // (24) 0.01175
/*28  */         s->avctx->frame_size = 384;                                                            // (11) 0.03507
/*30  */         nb_frames = mp_decode_layer1(s);                                                       // (5) 0.04286
/*32  */         break;                                                                                 // (22) 0.01753
/*34  */     case 2:                                                                                    // (25) 0.01169
/*36  */         s->avctx->frame_size = 1152;                                                           // (9) 0.03701
/*38  */         nb_frames = mp_decode_layer2(s);                                                       // (6) 0.04286
/*40  */         break;                                                                                 // (21) 0.01753
/*42  */     case 3:                                                                                    // (23) 0.01179
/*44  */         s->avctx->frame_size = s->lsf ? 576 : 1152;                                            // (2) 0.0526
/*46  */     default:                                                                                   // (26) 0.00974
/*48  */         nb_frames = mp_decode_layer3(s);                                                       // (7) 0.04286
/*52  */         if (nb_frames < 0)                                                                     // (16) 0.02922
/*54  */             return nb_frames;                                                                  // (14) 0.03312
/*58  */         s->last_buf_size=0;                                                                    // (12) 0.03312
/*60  */         if (s->in_gb.buffer) {                                                                 // (10) 0.03508
/*62  */             align_get_bits(&s->gb);                                                            // (8) 0.04093
/*64  */             i = get_bits_left(&s->gb)>>3;                                                      // (3) 0.05066
/*66  */             if (i >= 0 && i <= BACKSTEP_SIZE) {                                                // 0.0
/*68  */                 memmove(s->last_buf, s->gb.buffer + (get_bits_count(&s->gb)>>3), i);           // 0.0
/*70  */                 s->last_buf_size=i;                                                            // 0.0
/*72  */             } else                                                                             // 0.0
/*74  */                 av_log(s->avctx, AV_LOG_ERROR, "invalid old backstep %d\n", i);                // 0.0
/*76  */             s->gb           = s->in_gb;                                                        // 0.0
/*78  */             s->in_gb.buffer = NULL;                                                            // 0.0
/*80  */         }                                                                                      // 0.0
/*84  */         align_get_bits(&s->gb);                                                                // 0.0
/*86  */         assert((get_bits_count(&s->gb) & 7) == 0);                                             // 0.0
/*88  */         i = get_bits_left(&s->gb) >> 3;                                                        // 0.0
/*92  */         if (i < 0 || i > BACKSTEP_SIZE || nb_frames < 0) {                                     // 0.0
/*94  */             if (i < 0)                                                                         // 0.0
/*96  */                 av_log(s->avctx, AV_LOG_ERROR, "invalid new backstep %d\n", i);                // 0.0
/*98  */             i = FFMIN(BACKSTEP_SIZE, buf_size - HEADER_SIZE);                                  // 0.0
/*100 */         }                                                                                      // 0.0
/*102 */         assert(i <= buf_size - HEADER_SIZE && i >= 0);                                         // 0.0
/*104 */         memcpy(s->last_buf + s->last_buf_size, s->gb.buffer + buf_size - HEADER_SIZE - i, i);  // 0.0
/*106 */         s->last_buf_size += i;                                                                 // 0.0
/*108 */     }                                                                                          // 0.0
/*112 */     /* get output buffer */                                                                    // 0.0
/*114 */     if (!samples) {                                                                            // 0.0
/*116 */         av_assert0(s->frame != NULL);                                                          // 0.0
/*118 */         s->frame->nb_samples = s->avctx->frame_size;                                           // 0.0
/*120 */         if ((ret = ff_get_buffer(s->avctx, s->frame, 0)) < 0) {                                // 0.0
/*122 */             av_log(s->avctx, AV_LOG_ERROR, "get_buffer() failed\n");                           // 0.0
/*124 */             return ret;                                                                        // 0.0
/*126 */         }                                                                                      // 0.0
/*128 */         samples = (OUT_INT **)s->frame->extended_data;                                         // 0.0
/*130 */     }                                                                                          // 0.0
/*134 */     /* apply the synthesis filter */                                                           // 0.0
/*136 */     for (ch = 0; ch < s->nb_channels; ch++) {                                                  // 0.0
/*138 */         int sample_stride;                                                                     // 0.0
/*140 */         if (s->avctx->sample_fmt == OUT_FMT_P) {                                               // 0.0
/*142 */             samples_ptr   = samples[ch];                                                       // 0.0
/*144 */             sample_stride = 1;                                                                 // 0.0
/*146 */         } else {                                                                               // 0.0
/*148 */             samples_ptr   = samples[0] + ch;                                                   // 0.0
/*150 */             sample_stride = s->nb_channels;                                                    // 0.0
/*152 */         }                                                                                      // 0.0
/*154 */         for (i = 0; i < nb_frames; i++) {                                                      // 0.0
/*156 */             RENAME(ff_mpa_synth_filter)(&s->mpadsp, s->synth_buf[ch],                          // 0.0
/*158 */                                         &(s->synth_buf_offset[ch]),                            // 0.0
/*160 */                                         RENAME(ff_mpa_synth_window),                           // 0.0
/*162 */                                         &s->dither_state, samples_ptr,                         // 0.0
/*164 */                                         sample_stride, s->sb_samples[ch][i]);                  // 0.0
/*166 */             samples_ptr += 32 * sample_stride;                                                 // 0.0
/*168 */         }                                                                                      // 0.0
/*170 */     }                                                                                          // 0.0
/*174 */     return nb_frames * 32 * sizeof(OUT_INT) * s->nb_channels;                                  // 0.0
/*176 */ }                                                                                              // 0.0
