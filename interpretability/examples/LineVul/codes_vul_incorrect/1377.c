// commit message FFmpeg@46e3883519 (target=1, prob=0.4014721, correct=False): avcodec/opusdec: check alignment, misalignment could lead to crashes with avx
/*0   */ static int opus_decode_frame(OpusStreamContext *s, const uint8_t *data, int size)                   // (5) 0.05469
/*2   */ {                                                                                                   // (20) 0.001954
/*4   */     int samples    = s->packet.frame_duration;                                                      // (9) 0.03516
/*6   */     int redundancy = 0;                                                                             // (18) 0.01562
/*8   */     int redundancy_size, redundancy_pos;                                                            // (13) 0.02344
/*10  */     int ret, i, consumed;                                                                           // (14) 0.01953
/*12  */     int delayed_samples = s->delayed_samples;                                                       // (11) 0.0332
/*16  */     ret = opus_rc_init(&s->rc, data, size);                                                         // (8) 0.03906
/*18  */     if (ret < 0)                                                                                    // (17) 0.01758
/*20  */         return ret;                                                                                 // (15) 0.01953
/*24  */     /* decode the silk frame */                                                                     // (16) 0.01758
/*26  */     if (s->packet.mode == OPUS_MODE_SILK || s->packet.mode == OPUS_MODE_HYBRID) {                   // (3) 0.07422
/*28  */         if (!swr_is_initialized(s->swr)) {                                                          // (7) 0.04297
/*30  */             ret = opus_init_resample(s);                                                            // (6) 0.04492
/*32  */             if (ret < 0)                                                                            // (12) 0.0332
/*34  */                 return ret;                                                                         // (10) 0.03516
/*36  */         }                                                                                           // (19) 0.01562
/*40  */         samples = ff_silk_decode_superframe(s->silk, &s->rc, s->silk_output,                        // (4) 0.07227
/*42  */                                             FFMIN(s->packet.bandwidth, OPUS_BANDWIDTH_WIDEBAND),    // (0) 0.1328
/*44  */                                             s->packet.stereo + 1,                                   // (2) 0.1035
/*46  */                                             silk_frame_duration_ms[s->packet.config]);              // (1) 0.1133
/*48  */         if (samples < 0) {                                                                          // 0.0
/*50  */             av_log(s->avctx, AV_LOG_ERROR, "Error decoding a SILK frame.\n");                       // 0.0
/*52  */             return samples;                                                                         // 0.0
/*54  */         }                                                                                           // 0.0
/*56  */         samples = swr_convert(s->swr,                                                               // 0.0
/*58  */                               (uint8_t**)s->out, s->packet.frame_duration,                          // 0.0
/*60  */                               (const uint8_t**)s->silk_output, samples);                            // 0.0
/*62  */         if (samples < 0) {                                                                          // 0.0
/*64  */             av_log(s->avctx, AV_LOG_ERROR, "Error resampling SILK data.\n");                        // 0.0
/*66  */             return samples;                                                                         // 0.0
/*68  */         }                                                                                           // 0.0
/*71  */         s->delayed_samples += s->packet.frame_duration - samples;                                   // 0.0
/*73  */     } else                                                                                          // 0.0
/*75  */         ff_silk_flush(s->silk);                                                                     // 0.0
/*79  */     // decode redundancy information                                                                // 0.0
/*81  */     consumed = opus_rc_tell(&s->rc);                                                                // 0.0
/*83  */     if (s->packet.mode == OPUS_MODE_HYBRID && consumed + 37 <= size * 8)                            // 0.0
/*85  */         redundancy = opus_rc_p2model(&s->rc, 12);                                                   // 0.0
/*87  */     else if (s->packet.mode == OPUS_MODE_SILK && consumed + 17 <= size * 8)                         // 0.0
/*89  */         redundancy = 1;                                                                             // 0.0
/*93  */     if (redundancy) {                                                                               // 0.0
/*95  */         redundancy_pos = opus_rc_p2model(&s->rc, 1);                                                // 0.0
/*99  */         if (s->packet.mode == OPUS_MODE_HYBRID)                                                     // 0.0
/*101 */             redundancy_size = opus_rc_unimodel(&s->rc, 256) + 2;                                    // 0.0
/*103 */         else                                                                                        // 0.0
/*105 */             redundancy_size = size - (consumed + 7) / 8;                                            // 0.0
/*107 */         size -= redundancy_size;                                                                    // 0.0
/*109 */         if (size < 0) {                                                                             // 0.0
/*111 */             av_log(s->avctx, AV_LOG_ERROR, "Invalid redundancy frame size.\n");                     // 0.0
/*113 */             return AVERROR_INVALIDDATA;                                                             // 0.0
/*115 */         }                                                                                           // 0.0
/*119 */         if (redundancy_pos) {                                                                       // 0.0
/*121 */             ret = opus_decode_redundancy(s, data + size, redundancy_size);                          // 0.0
/*123 */             if (ret < 0)                                                                            // 0.0
/*125 */                 return ret;                                                                         // 0.0
/*127 */             ff_celt_flush(s->celt);                                                                 // 0.0
/*129 */         }                                                                                           // 0.0
/*131 */     }                                                                                               // 0.0
/*135 */     /* decode the CELT frame */                                                                     // 0.0
/*137 */     if (s->packet.mode == OPUS_MODE_CELT || s->packet.mode == OPUS_MODE_HYBRID) {                   // 0.0
/*139 */         float *out_tmp[2] = { s->out[0], s->out[1] };                                               // 0.0
/*141 */         float **dst = (s->packet.mode == OPUS_MODE_CELT) ?                                          // 0.0
/*143 */                       out_tmp : s->celt_output;                                                     // 0.0
/*145 */         int celt_output_samples = samples;                                                          // 0.0
/*147 */         int delay_samples = av_audio_fifo_size(s->celt_delay);                                      // 0.0
/*151 */         if (delay_samples) {                                                                        // 0.0
/*153 */             if (s->packet.mode == OPUS_MODE_HYBRID) {                                               // 0.0
/*155 */                 av_audio_fifo_read(s->celt_delay, (void**)s->celt_output, delay_samples);           // 0.0
/*159 */                 for (i = 0; i < s->output_channels; i++) {                                          // 0.0
/*161 */                     s->fdsp->vector_fmac_scalar(out_tmp[i], s->celt_output[i], 1.0,                 // 0.0
/*163 */                                                 delay_samples);                                     // 0.0
/*165 */                     out_tmp[i] += delay_samples;                                                    // 0.0
/*167 */                 }                                                                                   // 0.0
/*169 */                 celt_output_samples -= delay_samples;                                               // 0.0
/*171 */             } else {                                                                                // 0.0
/*173 */                 av_log(s->avctx, AV_LOG_WARNING,                                                    // 0.0
/*175 */                        "Spurious CELT delay samples present.\n");                                   // 0.0
/*177 */                 av_audio_fifo_drain(s->celt_delay, delay_samples);                                  // 0.0
/*179 */                 if (s->avctx->err_recognition & AV_EF_EXPLODE)                                      // 0.0
/*181 */                     return AVERROR_BUG;                                                             // 0.0
/*183 */             }                                                                                       // 0.0
/*185 */         }                                                                                           // 0.0
/*189 */         opus_raw_init(&s->rc, data + size, size);                                                   // 0.0
/*193 */         ret = ff_celt_decode_frame(s->celt, &s->rc, dst,                                            // 0.0
/*195 */                                    s->packet.stereo + 1,                                            // 0.0
/*197 */                                    s->packet.frame_duration,                                        // 0.0
/*199 */                                    (s->packet.mode == OPUS_MODE_HYBRID) ? 17 : 0,                   // 0.0
/*201 */                                    celt_band_end[s->packet.bandwidth]);                             // 0.0
/*203 */         if (ret < 0)                                                                                // 0.0
/*205 */             return ret;                                                                             // 0.0
/*209 */         if (s->packet.mode == OPUS_MODE_HYBRID) {                                                   // 0.0
/*211 */             int celt_delay = s->packet.frame_duration - celt_output_samples;                        // 0.0
/*213 */             void *delaybuf[2] = { s->celt_output[0] + celt_output_samples,                          // 0.0
/*215 */                                   s->celt_output[1] + celt_output_samples };                        // 0.0
/*219 */             for (i = 0; i < s->output_channels; i++) {                                              // 0.0
/*221 */                 s->fdsp->vector_fmac_scalar(out_tmp[i],                                             // 0.0
/*223 */                                             s->celt_output[i], 1.0,                                 // 0.0
/*225 */                                             celt_output_samples);                                   // 0.0
/*227 */             }                                                                                       // 0.0
/*231 */             ret = av_audio_fifo_write(s->celt_delay, delaybuf, celt_delay);                         // 0.0
/*233 */             if (ret < 0)                                                                            // 0.0
/*235 */                 return ret;                                                                         // 0.0
/*237 */         }                                                                                           // 0.0
/*239 */     } else                                                                                          // 0.0
/*241 */         ff_celt_flush(s->celt);                                                                     // 0.0
/*245 */     if (s->redundancy_idx) {                                                                        // 0.0
/*247 */         for (i = 0; i < s->output_channels; i++)                                                    // 0.0
/*249 */             opus_fade(s->out[i], s->out[i],                                                         // 0.0
/*251 */                       s->redundancy_output[i] + 120 + s->redundancy_idx,                            // 0.0
/*253 */                       ff_celt_window2 + s->redundancy_idx, 120 - s->redundancy_idx);                // 0.0
/*255 */         s->redundancy_idx = 0;                                                                      // 0.0
/*257 */     }                                                                                               // 0.0
/*259 */     if (redundancy) {                                                                               // 0.0
/*261 */         if (!redundancy_pos) {                                                                      // 0.0
/*263 */             ff_celt_flush(s->celt);                                                                 // 0.0
/*265 */             ret = opus_decode_redundancy(s, data + size, redundancy_size);                          // 0.0
/*267 */             if (ret < 0)                                                                            // 0.0
/*269 */                 return ret;                                                                         // 0.0
/*273 */             for (i = 0; i < s->output_channels; i++) {                                              // 0.0
/*275 */                 opus_fade(s->out[i] + samples - 120 + delayed_samples,                              // 0.0
/*277 */                           s->out[i] + samples - 120 + delayed_samples,                              // 0.0
/*279 */                           s->redundancy_output[i] + 120,                                            // 0.0
/*281 */                           ff_celt_window2, 120 - delayed_samples);                                  // 0.0
/*283 */                 if (delayed_samples)                                                                // 0.0
/*285 */                     s->redundancy_idx = 120 - delayed_samples;                                      // 0.0
/*287 */             }                                                                                       // 0.0
/*289 */         } else {                                                                                    // 0.0
/*291 */             for (i = 0; i < s->output_channels; i++) {                                              // 0.0
/*293 */                 memcpy(s->out[i] + delayed_samples, s->redundancy_output[i], 120 * sizeof(float));  // 0.0
/*295 */                 opus_fade(s->out[i] + 120 + delayed_samples,                                        // 0.0
/*297 */                           s->redundancy_output[i] + 120,                                            // 0.0
/*299 */                           s->out[i] + 120 + delayed_samples,                                        // 0.0
/*301 */                           ff_celt_window2, 120);                                                    // 0.0
/*303 */             }                                                                                       // 0.0
/*305 */         }                                                                                           // 0.0
/*307 */     }                                                                                               // 0.0
/*311 */     return samples;                                                                                 // 0.0
/*313 */ }                                                                                                   // 0.0
