// commit message FFmpeg@5b29af624f (target=0, prob=0.5625374, correct=False): aacenc: Replace loop counters in aac_encode_frame() with more descriptive 'ch' and 'w'.
/*0   */ static int aac_encode_frame(AVCodecContext *avctx,                                                     // (11) 0.03515
/*2   */                             uint8_t *frame, int buf_size, void *data)                                  // (0) 0.08396
/*4   */ {                                                                                                      // (22) 0.001953
/*6   */     AACEncContext *s = avctx->priv_data;                                                               // (14) 0.03127
/*8   */     int16_t *samples = s->samples, *samples2, *la;                                                     // (9) 0.04687
/*10  */     ChannelElement *cpe;                                                                               // (20) 0.01773
/*12  */     int i, j, chans, tag, start_ch;                                                                    // (12) 0.0332
/*14  */     const uint8_t *chan_map = aac_chan_configs[avctx->channels-1];                                     // (5) 0.05663
/*16  */     int chan_el_counter[4];                                                                            // (16) 0.02538
/*18  */     FFPsyWindowInfo windows[AAC_MAX_CHANNELS];                                                         // (10) 0.0371
/*22  */     if (s->last_frame)                                                                                 // (17) 0.02148
/*24  */         return 0;                                                                                      // (18) 0.01953
/*26  */     if (data) {                                                                                        // (21) 0.01562
/*28  */         if (!s->psypp) {                                                                               // (15) 0.02929
/*30  */             memcpy(s->samples + 1024 * avctx->channels, data,                                          // (3) 0.05858
/*32  */                    1024 * avctx->channels * sizeof(s->samples[0]));                                    // (2) 0.07029
/*34  */         } else {                                                                                       // (19) 0.01953
/*36  */             start_ch = 0;                                                                              // (13) 0.03319
/*38  */             samples2 = s->samples + 1024 * avctx->channels;                                            // (7) 0.05272
/*40  */             for (i = 0; i < chan_map[0]; i++) {                                                        // (6) 0.05663
/*42  */                 tag = chan_map[i+1];                                                                   // (8) 0.05077
/*44  */                 chans = tag == TYPE_CPE ? 2 : 1;                                                       // (4) 0.05665
/*46  */                 ff_psy_preprocess(s->psypp, (uint16_t*)data + start_ch,                                // (1) 0.07616
/*48  */                                   samples2 + start_ch, start_ch, chans);                               // 0.0
/*50  */                 start_ch += chans;                                                                     // 0.0
/*52  */             }                                                                                          // 0.0
/*54  */         }                                                                                              // 0.0
/*56  */     }                                                                                                  // 0.0
/*58  */     if (!avctx->frame_number) {                                                                        // 0.0
/*60  */         memcpy(s->samples, s->samples + 1024 * avctx->channels,                                        // 0.0
/*62  */                1024 * avctx->channels * sizeof(s->samples[0]));                                        // 0.0
/*64  */         return 0;                                                                                      // 0.0
/*66  */     }                                                                                                  // 0.0
/*70  */     start_ch = 0;                                                                                      // 0.0
/*72  */     for (i = 0; i < chan_map[0]; i++) {                                                                // 0.0
/*74  */         FFPsyWindowInfo* wi = windows + start_ch;                                                      // 0.0
/*76  */         tag      = chan_map[i+1];                                                                      // 0.0
/*78  */         chans    = tag == TYPE_CPE ? 2 : 1;                                                            // 0.0
/*80  */         cpe      = &s->cpe[i];                                                                         // 0.0
/*82  */         for (j = 0; j < chans; j++) {                                                                  // 0.0
/*84  */             IndividualChannelStream *ics = &cpe->ch[j].ics;                                            // 0.0
/*86  */             int k;                                                                                     // 0.0
/*88  */             int cur_channel = start_ch + j;                                                            // 0.0
/*90  */             samples2 = samples + cur_channel;                                                          // 0.0
/*92  */             la       = samples2 + (448+64) * avctx->channels;                                          // 0.0
/*94  */             if (!data)                                                                                 // 0.0
/*96  */                 la = NULL;                                                                             // 0.0
/*98  */             if (tag == TYPE_LFE) {                                                                     // 0.0
/*100 */                 wi[j].window_type[0] = ONLY_LONG_SEQUENCE;                                             // 0.0
/*102 */                 wi[j].window_shape   = 0;                                                              // 0.0
/*104 */                 wi[j].num_windows    = 1;                                                              // 0.0
/*106 */                 wi[j].grouping[0]    = 1;                                                              // 0.0
/*108 */             } else {                                                                                   // 0.0
/*110 */                 wi[j] = ff_psy_suggest_window(&s->psy, samples2, la, cur_channel,                      // 0.0
/*112 */                                               ics->window_sequence[0]);                                // 0.0
/*114 */             }                                                                                          // 0.0
/*116 */             ics->window_sequence[1] = ics->window_sequence[0];                                         // 0.0
/*118 */             ics->window_sequence[0] = wi[j].window_type[0];                                            // 0.0
/*120 */             ics->use_kb_window[1]   = ics->use_kb_window[0];                                           // 0.0
/*122 */             ics->use_kb_window[0]   = wi[j].window_shape;                                              // 0.0
/*124 */             ics->num_windows        = wi[j].num_windows;                                               // 0.0
/*126 */             ics->swb_sizes          = s->psy.bands    [ics->num_windows == 8];                         // 0.0
/*128 */             ics->num_swb            = tag == TYPE_LFE ? 12 : s->psy.num_bands[ics->num_windows == 8];  // 0.0
/*130 */             for (k = 0; k < ics->num_windows; k++)                                                     // 0.0
/*132 */                 ics->group_len[k] = wi[j].grouping[k];                                                 // 0.0
/*136 */             apply_window_and_mdct(avctx, s, &cpe->ch[j], samples2);                                    // 0.0
/*138 */         }                                                                                              // 0.0
/*140 */         start_ch += chans;                                                                             // 0.0
/*142 */     }                                                                                                  // 0.0
/*144 */     do {                                                                                               // 0.0
/*146 */         int frame_bits;                                                                                // 0.0
/*148 */         init_put_bits(&s->pb, frame, buf_size*8);                                                      // 0.0
/*150 */         if ((avctx->frame_number & 0xFF)==1 && !(avctx->flags & CODEC_FLAG_BITEXACT))                  // 0.0
/*152 */             put_bitstream_info(avctx, s, LIBAVCODEC_IDENT);                                            // 0.0
/*154 */         start_ch = 0;                                                                                  // 0.0
/*156 */         memset(chan_el_counter, 0, sizeof(chan_el_counter));                                           // 0.0
/*158 */         for (i = 0; i < chan_map[0]; i++) {                                                            // 0.0
/*160 */             FFPsyWindowInfo* wi = windows + start_ch;                                                  // 0.0
/*162 */             tag      = chan_map[i+1];                                                                  // 0.0
/*164 */             chans    = tag == TYPE_CPE ? 2 : 1;                                                        // 0.0
/*166 */             cpe      = &s->cpe[i];                                                                     // 0.0
/*168 */             put_bits(&s->pb, 3, tag);                                                                  // 0.0
/*170 */             put_bits(&s->pb, 4, chan_el_counter[tag]++);                                               // 0.0
/*172 */             for (j = 0; j < chans; j++) {                                                              // 0.0
/*174 */                 s->cur_channel = start_ch + j;                                                         // 0.0
/*176 */                 ff_psy_set_band_info(&s->psy, s->cur_channel, cpe->ch[j].coeffs, &wi[j]);              // 0.0
/*178 */                 s->coder->search_for_quantizers(avctx, s, &cpe->ch[j], s->lambda);                     // 0.0
/*180 */             }                                                                                          // 0.0
/*182 */             cpe->common_window = 0;                                                                    // 0.0
/*184 */             if (chans > 1                                                                              // 0.0
/*186 */                 && wi[0].window_type[0] == wi[1].window_type[0]                                        // 0.0
/*188 */                 && wi[0].window_shape   == wi[1].window_shape) {                                       // 0.0
/*192 */                 cpe->common_window = 1;                                                                // 0.0
/*194 */                 for (j = 0; j < wi[0].num_windows; j++) {                                              // 0.0
/*196 */                     if (wi[0].grouping[j] != wi[1].grouping[j]) {                                      // 0.0
/*198 */                         cpe->common_window = 0;                                                        // 0.0
/*200 */                         break;                                                                         // 0.0
/*202 */                     }                                                                                  // 0.0
/*204 */                 }                                                                                      // 0.0
/*206 */             }                                                                                          // 0.0
/*208 */             s->cur_channel = start_ch;                                                                 // 0.0
/*210 */             if (cpe->common_window && s->coder->search_for_ms)                                         // 0.0
/*212 */                 s->coder->search_for_ms(s, cpe, s->lambda);                                            // 0.0
/*214 */             adjust_frame_information(s, cpe, chans);                                                   // 0.0
/*216 */             if (chans == 2) {                                                                          // 0.0
/*218 */                 put_bits(&s->pb, 1, cpe->common_window);                                               // 0.0
/*220 */                 if (cpe->common_window) {                                                              // 0.0
/*222 */                     put_ics_info(s, &cpe->ch[0].ics);                                                  // 0.0
/*224 */                     encode_ms_info(&s->pb, cpe);                                                       // 0.0
/*226 */                 }                                                                                      // 0.0
/*228 */             }                                                                                          // 0.0
/*230 */             for (j = 0; j < chans; j++) {                                                              // 0.0
/*232 */                 s->cur_channel = start_ch + j;                                                         // 0.0
/*234 */                 encode_individual_channel(avctx, s, &cpe->ch[j], cpe->common_window);                  // 0.0
/*236 */             }                                                                                          // 0.0
/*238 */             start_ch += chans;                                                                         // 0.0
/*240 */         }                                                                                              // 0.0
/*244 */         frame_bits = put_bits_count(&s->pb);                                                           // 0.0
/*246 */         if (frame_bits <= 6144 * avctx->channels - 3) {                                                // 0.0
/*248 */             s->psy.bitres.bits = frame_bits / avctx->channels;                                         // 0.0
/*250 */             break;                                                                                     // 0.0
/*252 */         }                                                                                              // 0.0
/*256 */         s->lambda *= avctx->bit_rate * 1024.0f / avctx->sample_rate / frame_bits;                      // 0.0
/*260 */     } while (1);                                                                                       // 0.0
/*264 */     put_bits(&s->pb, 3, TYPE_END);                                                                     // 0.0
/*266 */     flush_put_bits(&s->pb);                                                                            // 0.0
/*268 */     avctx->frame_bits = put_bits_count(&s->pb);                                                        // 0.0
/*272 */     // rate control stuff                                                                              // 0.0
/*274 */     if (!(avctx->flags & CODEC_FLAG_QSCALE)) {                                                         // 0.0
/*276 */         float ratio = avctx->bit_rate * 1024.0f / avctx->sample_rate / avctx->frame_bits;              // 0.0
/*278 */         s->lambda *= ratio;                                                                            // 0.0
/*280 */         s->lambda = FFMIN(s->lambda, 65536.f);                                                         // 0.0
/*282 */     }                                                                                                  // 0.0
/*286 */     if (!data)                                                                                         // 0.0
/*288 */         s->last_frame = 1;                                                                             // 0.0
/*290 */     memcpy(s->samples, s->samples + 1024 * avctx->channels,                                            // 0.0
/*292 */            1024 * avctx->channels * sizeof(s->samples[0]));                                            // 0.0
/*294 */     return put_bits_count(&s->pb)>>3;                                                                  // 0.0
/*296 */ }                                                                                                      // 0.0
