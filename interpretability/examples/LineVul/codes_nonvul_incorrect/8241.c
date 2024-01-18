// commit message FFmpeg@801c39e1e3 (target=0, prob=0.5398506, correct=False): dcadec: Use correct channel count in stereo downmix check
/*0   */ static int dca_decode_frame(AVCodecContext *avctx, void *data,                                      // (2) 0.04412
/*2   */                             int *got_frame_ptr, AVPacket *avpkt)                                    // (6) 0.01109
/*4   */ {                                                                                                   // (17) 0.004747
/*6   */     AVFrame *frame     = data;                                                                      // (5) 0.01448
/*8   */     const uint8_t *buf = avpkt->data;                                                               // (12) 0.005986
/*10  */     int buf_size = avpkt->size;                                                                     // (15) 0.005452
/*14  */     int lfe_samples;                                                                                // (22) 0.002731
/*16  */     int num_core_channels = 0;                                                                      // (21) 0.003266
/*18  */     int i, ret;                                                                                     // (23) 0.00262
/*20  */     float  **samples_flt;                                                                           // (19) 0.004305
/*22  */     DCAContext *s = avctx->priv_data;                                                               // (10) 0.007197
/*24  */     int channels, full_channels;                                                                    // (18) 0.004322
/*26  */     int core_ss_end;                                                                                // (14) 0.005816
/*32  */     s->xch_present = 0;                                                                             // (13) 0.005852
/*36  */     s->dca_buffer_size = ff_dca_convert_bitstream(buf, buf_size, s->dca_buffer,                     // (11) 0.00639
/*38  */                                                   DCA_MAX_FRAME_SIZE + DCA_MAX_EXSS_HEADER_SIZE);   // (8) 0.009565
/*40  */     if (s->dca_buffer_size == AVERROR_INVALIDDATA) {                                                // (16) 0.004857
/*42  */         av_log(avctx, AV_LOG_ERROR, "Not a valid DCA frame\n");                                     // (7) 0.009887
/*44  */         return AVERROR_INVALIDDATA;                                                                 // (20) 0.003375
/*46  */     }                                                                                               // (24) 0.001012
/*50  */     init_get_bits(&s->gb, s->dca_buffer, s->dca_buffer_size * 8);                                   // (9) 0.008886
/*52  */     if ((ret = dca_parse_frame_header(s)) < 0) {                                                    // (1) 0.08443
/*54  */         //seems like the frame is corrupt, try with the next one                                    // (0) 0.5953
/*56  */         return ret;                                                                                 // (4) 0.01617
/*58  */     }                                                                                               // (3) 0.02077
/*60  */     //set AVCodec values with parsed data                                                           // 0.0
/*62  */     avctx->sample_rate = s->sample_rate;                                                            // 0.0
/*64  */     avctx->bit_rate    = s->bit_rate;                                                               // 0.0
/*68  */     s->profile = FF_PROFILE_DTS;                                                                    // 0.0
/*72  */     for (i = 0; i < (s->sample_blocks / 8); i++) {                                                  // 0.0
/*74  */         if ((ret = dca_decode_block(s, 0, i))) {                                                    // 0.0
/*76  */             av_log(avctx, AV_LOG_ERROR, "error decoding block\n");                                  // 0.0
/*78  */             return ret;                                                                             // 0.0
/*80  */         }                                                                                           // 0.0
/*82  */     }                                                                                               // 0.0
/*86  */     /* record number of core channels incase less than max channels are requested */                // 0.0
/*88  */     num_core_channels = s->prim_channels;                                                           // 0.0
/*92  */     if (s->ext_coding)                                                                              // 0.0
/*94  */         s->core_ext_mask = dca_ext_audio_descr_mask[s->ext_descr];                                  // 0.0
/*96  */     else                                                                                            // 0.0
/*98  */         s->core_ext_mask = 0;                                                                       // 0.0
/*102 */     core_ss_end = FFMIN(s->frame_size, s->dca_buffer_size) * 8;                                     // 0.0
/*106 */     /* only scan for extensions if ext_descr was unknown or indicated a                             // 0.0
/*108 */      * supported XCh extension */                                                                   // 0.0
/*110 */     if (s->core_ext_mask < 0 || s->core_ext_mask & DCA_EXT_XCH) {                                   // 0.0
/*114 */         /* if ext_descr was unknown, clear s->core_ext_mask so that the                             // 0.0
/*116 */          * extensions scan can fill it up */                                                        // 0.0
/*118 */         s->core_ext_mask = FFMAX(s->core_ext_mask, 0);                                              // 0.0
/*122 */         /* extensions start at 32-bit boundaries into bitstream */                                  // 0.0
/*124 */         skip_bits_long(&s->gb, (-get_bits_count(&s->gb)) & 31);                                     // 0.0
/*128 */         while (core_ss_end - get_bits_count(&s->gb) >= 32) {                                        // 0.0
/*130 */             uint32_t bits = get_bits_long(&s->gb, 32);                                              // 0.0
/*134 */             switch (bits) {                                                                         // 0.0
/*136 */             case 0x5a5a5a5a: {                                                                      // 0.0
/*138 */                 int ext_amode, xch_fsize;                                                           // 0.0
/*142 */                 s->xch_base_channel = s->prim_channels;                                             // 0.0
/*146 */                 /* validate sync word using XCHFSIZE field */                                       // 0.0
/*148 */                 xch_fsize = show_bits(&s->gb, 10);                                                  // 0.0
/*150 */                 if ((s->frame_size != (get_bits_count(&s->gb) >> 3) - 4 + xch_fsize) &&             // 0.0
/*152 */                     (s->frame_size != (get_bits_count(&s->gb) >> 3) - 4 + xch_fsize + 1))           // 0.0
/*154 */                     continue;                                                                       // 0.0
/*158 */                 /* skip length-to-end-of-frame field for the moment */                              // 0.0
/*160 */                 skip_bits(&s->gb, 10);                                                              // 0.0
/*164 */                 s->core_ext_mask |= DCA_EXT_XCH;                                                    // 0.0
/*168 */                 /* extension amode(number of channels in extension) should be 1 */                  // 0.0
/*170 */                 /* AFAIK XCh is not used for more channels */                                       // 0.0
/*172 */                 if ((ext_amode = get_bits(&s->gb, 4)) != 1) {                                       // 0.0
/*174 */                     av_log(avctx, AV_LOG_ERROR, "XCh extension amode %d not"                        // 0.0
/*176 */                            " supported!\n", ext_amode);                                             // 0.0
/*178 */                     continue;                                                                       // 0.0
/*180 */                 }                                                                                   // 0.0
/*184 */                 /* much like core primary audio coding header */                                    // 0.0
/*186 */                 dca_parse_audio_coding_header(s, s->xch_base_channel);                              // 0.0
/*190 */                 for (i = 0; i < (s->sample_blocks / 8); i++)                                        // 0.0
/*192 */                     if ((ret = dca_decode_block(s, s->xch_base_channel, i))) {                      // 0.0
/*194 */                         av_log(avctx, AV_LOG_ERROR, "error decoding XCh extension\n");              // 0.0
/*196 */                         continue;                                                                   // 0.0
/*198 */                     }                                                                               // 0.0
/*202 */                 s->xch_present = 1;                                                                 // 0.0
/*204 */                 break;                                                                              // 0.0
/*206 */             }                                                                                       // 0.0
/*208 */             case 0x47004a03:                                                                        // 0.0
/*210 */                 /* XXCh: extended channels */                                                       // 0.0
/*212 */                 /* usually found either in core or HD part in DTS-HD HRA streams,                   // 0.0
/*214 */                  * but not in DTS-ES which contains XCh extensions instead */                       // 0.0
/*216 */                 s->core_ext_mask |= DCA_EXT_XXCH;                                                   // 0.0
/*218 */                 break;                                                                              // 0.0
/*222 */             case 0x1d95f262: {                                                                      // 0.0
/*224 */                 int fsize96 = show_bits(&s->gb, 12) + 1;                                            // 0.0
/*226 */                 if (s->frame_size != (get_bits_count(&s->gb) >> 3) - 4 + fsize96)                   // 0.0
/*228 */                     continue;                                                                       // 0.0
/*232 */                 av_log(avctx, AV_LOG_DEBUG, "X96 extension found at %d bits\n",                     // 0.0
/*234 */                        get_bits_count(&s->gb));                                                     // 0.0
/*236 */                 skip_bits(&s->gb, 12);                                                              // 0.0
/*238 */                 av_log(avctx, AV_LOG_DEBUG, "FSIZE96 = %d bytes\n", fsize96);                       // 0.0
/*240 */                 av_log(avctx, AV_LOG_DEBUG, "REVNO = %d\n", get_bits(&s->gb, 4));                   // 0.0
/*244 */                 s->core_ext_mask |= DCA_EXT_X96;                                                    // 0.0
/*246 */                 break;                                                                              // 0.0
/*248 */             }                                                                                       // 0.0
/*250 */             }                                                                                       // 0.0
/*254 */             skip_bits_long(&s->gb, (-get_bits_count(&s->gb)) & 31);                                 // 0.0
/*256 */         }                                                                                           // 0.0
/*258 */     } else {                                                                                        // 0.0
/*260 */         /* no supported extensions, skip the rest of the core substream */                          // 0.0
/*262 */         skip_bits_long(&s->gb, core_ss_end - get_bits_count(&s->gb));                               // 0.0
/*264 */     }                                                                                               // 0.0
/*268 */     if (s->core_ext_mask & DCA_EXT_X96)                                                             // 0.0
/*270 */         s->profile = FF_PROFILE_DTS_96_24;                                                          // 0.0
/*272 */     else if (s->core_ext_mask & (DCA_EXT_XCH | DCA_EXT_XXCH))                                       // 0.0
/*274 */         s->profile = FF_PROFILE_DTS_ES;                                                             // 0.0
/*278 */     /* check for ExSS (HD part) */                                                                  // 0.0
/*280 */     if (s->dca_buffer_size - s->frame_size > 32 &&                                                  // 0.0
/*282 */         get_bits_long(&s->gb, 32) == DCA_HD_MARKER)                                                 // 0.0
/*284 */         dca_exss_parse_header(s);                                                                   // 0.0
/*288 */     avctx->profile = s->profile;                                                                    // 0.0
/*292 */     full_channels = channels = s->prim_channels + !!s->lfe;                                         // 0.0
/*296 */     if (s->amode < 16) {                                                                            // 0.0
/*298 */         avctx->channel_layout = dca_core_channel_layout[s->amode];                                  // 0.0
/*302 */         if (s->prim_channels + !!s->lfe > 2 &&                                                      // 0.0
/*304 */             avctx->request_channel_layout == AV_CH_LAYOUT_STEREO) {                                 // 0.0
/*306 */             /*                                                                                      // 0.0
/*308 */              * Neither the core's auxiliary data nor our default tables contain                     // 0.0
/*310 */              * downmix coefficients for the additional channel coded in the XCh                     // 0.0
/*312 */              * extension, so when we're doing a Stereo downmix, don't decode it.                    // 0.0
/*314 */              */                                                                                     // 0.0
/*316 */             s->xch_disable = 1;                                                                     // 0.0
/*318 */         }                                                                                           // 0.0
/*322 */ #if FF_API_REQUEST_CHANNELS                                                                         // 0.0
/*324 */ FF_DISABLE_DEPRECATION_WARNINGS                                                                     // 0.0
/*326 */         if (s->xch_present && !s->xch_disable &&                                                    // 0.0
/*328 */             (!avctx->request_channels ||                                                            // 0.0
/*330 */              avctx->request_channels > num_core_channels + !!s->lfe)) {                             // 0.0
/*332 */ FF_ENABLE_DEPRECATION_WARNINGS                                                                      // 0.0
/*334 */ #else                                                                                               // 0.0
/*336 */         if (s->xch_present && !s->xch_disable) {                                                    // 0.0
/*338 */ #endif                                                                                              // 0.0
/*340 */             avctx->channel_layout |= AV_CH_BACK_CENTER;                                             // 0.0
/*342 */             if (s->lfe) {                                                                           // 0.0
/*344 */                 avctx->channel_layout |= AV_CH_LOW_FREQUENCY;                                       // 0.0
/*346 */                 s->channel_order_tab = dca_channel_reorder_lfe_xch[s->amode];                       // 0.0
/*348 */             } else {                                                                                // 0.0
/*350 */                 s->channel_order_tab = dca_channel_reorder_nolfe_xch[s->amode];                     // 0.0
/*352 */             }                                                                                       // 0.0
/*354 */         } else {                                                                                    // 0.0
/*356 */             channels = num_core_channels + !!s->lfe;                                                // 0.0
/*358 */             s->xch_present = 0; /* disable further xch processing */                                // 0.0
/*360 */             if (s->lfe) {                                                                           // 0.0
/*362 */                 avctx->channel_layout |= AV_CH_LOW_FREQUENCY;                                       // 0.0
/*364 */                 s->channel_order_tab = dca_channel_reorder_lfe[s->amode];                           // 0.0
/*366 */             } else                                                                                  // 0.0
/*368 */                 s->channel_order_tab = dca_channel_reorder_nolfe[s->amode];                         // 0.0
/*370 */         }                                                                                           // 0.0
/*374 */         if (channels > !!s->lfe &&                                                                  // 0.0
/*376 */             s->channel_order_tab[channels - 1 - !!s->lfe] < 0)                                      // 0.0
/*378 */             return AVERROR_INVALIDDATA;                                                             // 0.0
/*382 */         if (s->prim_channels + !!s->lfe > 2 &&                                                      // 0.0
/*384 */             avctx->request_channel_layout == AV_CH_LAYOUT_STEREO) {                                 // 0.0
/*386 */             channels = 2;                                                                           // 0.0
/*388 */             s->output = s->prim_channels == 2 ? s->amode : DCA_STEREO;                              // 0.0
/*390 */             avctx->channel_layout = AV_CH_LAYOUT_STEREO;                                            // 0.0
/*394 */             /* Stereo downmix coefficients                                                          // 0.0
/*396 */              *                                                                                      // 0.0
/*398 */              * The decoder can only downmix to 2-channel, so we need to ensure                      // 0.0
/*400 */              * embedded downmix coefficients are actually targeting 2-channel.                      // 0.0
/*402 */              */                                                                                     // 0.0
/*404 */             if (s->core_downmix && (s->core_downmix_amode == DCA_STEREO ||                          // 0.0
/*406 */                                     s->core_downmix_amode == DCA_STEREO_TOTAL)) {                   // 0.0
/*408 */                 int sign, code;                                                                     // 0.0
/*410 */                 for (i = 0; i < s->prim_channels + !!s->lfe; i++) {                                 // 0.0
/*412 */                     sign = s->core_downmix_codes[i][0] & 0x100 ? 1 : -1;                            // 0.0
/*414 */                     code = s->core_downmix_codes[i][0] & 0x0FF;                                     // 0.0
/*416 */                     s->downmix_coef[i][0] = (!code ? 0.0f :                                         // 0.0
/*418 */                                              sign * dca_dmixtable[code - 1]);                       // 0.0
/*420 */                     sign = s->core_downmix_codes[i][1] & 0x100 ? 1 : -1;                            // 0.0
/*422 */                     code = s->core_downmix_codes[i][1] & 0x0FF;                                     // 0.0
/*424 */                     s->downmix_coef[i][1] = (!code ? 0.0f :                                         // 0.0
/*426 */                                              sign * dca_dmixtable[code - 1]);                       // 0.0
/*428 */                 }                                                                                   // 0.0
/*430 */                 s->output = s->core_downmix_amode;                                                  // 0.0
/*432 */             } else {                                                                                // 0.0
/*434 */                 int am = s->amode & DCA_CHANNEL_MASK;                                               // 0.0
/*436 */                 if (am >= FF_ARRAY_ELEMS(dca_default_coeffs)) {                                     // 0.0
/*438 */                     av_log(s->avctx, AV_LOG_ERROR,                                                  // 0.0
/*440 */                            "Invalid channel mode %d\n", am);                                        // 0.0
/*442 */                     return AVERROR_INVALIDDATA;                                                     // 0.0
/*444 */                 }                                                                                   // 0.0
/*446 */                 if (s->prim_channels + !!s->lfe >                                                   // 0.0
/*448 */                     FF_ARRAY_ELEMS(dca_default_coeffs[0])) {                                        // 0.0
/*450 */                     avpriv_request_sample(s->avctx, "Downmixing %d channels",                       // 0.0
/*452 */                                           s->prim_channels + !!s->lfe);                             // 0.0
/*454 */                     return AVERROR_PATCHWELCOME;                                                    // 0.0
/*456 */                 }                                                                                   // 0.0
/*458 */                 for (i = 0; i < s->prim_channels + !!s->lfe; i++) {                                 // 0.0
/*460 */                     s->downmix_coef[i][0] = dca_default_coeffs[am][i][0];                           // 0.0
/*462 */                     s->downmix_coef[i][1] = dca_default_coeffs[am][i][1];                           // 0.0
/*464 */                 }                                                                                   // 0.0
/*466 */             }                                                                                       // 0.0
/*468 */             av_dlog(s->avctx, "Stereo downmix coeffs:\n");                                          // 0.0
/*470 */             for (i = 0; i < s->prim_channels + !!s->lfe; i++) {                                     // 0.0
/*472 */                 av_dlog(s->avctx, "L, input channel %d = %f\n", i,                                  // 0.0
/*474 */                         s->downmix_coef[i][0]);                                                     // 0.0
/*476 */                 av_dlog(s->avctx, "R, input channel %d = %f\n", i,                                  // 0.0
/*478 */                         s->downmix_coef[i][1]);                                                     // 0.0
/*480 */             }                                                                                       // 0.0
/*482 */             av_dlog(s->avctx, "\n");                                                                // 0.0
/*484 */         }                                                                                           // 0.0
/*486 */     } else {                                                                                        // 0.0
/*488 */         av_log(avctx, AV_LOG_ERROR, "Non standard configuration %d !\n", s->amode);                 // 0.0
/*490 */         return AVERROR_INVALIDDATA;                                                                 // 0.0
/*492 */     }                                                                                               // 0.0
/*494 */     avctx->channels = channels;                                                                     // 0.0
/*498 */     /* get output buffer */                                                                         // 0.0
/*500 */     frame->nb_samples = 256 * (s->sample_blocks / 8);                                               // 0.0
/*502 */     if ((ret = ff_get_buffer(avctx, frame, 0)) < 0) {                                               // 0.0
/*504 */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                                       // 0.0
/*506 */         return ret;                                                                                 // 0.0
/*508 */     }                                                                                               // 0.0
/*510 */     samples_flt = (float **)frame->extended_data;                                                   // 0.0
/*514 */     /* allocate buffer for extra channels if downmixing */                                          // 0.0
/*516 */     if (avctx->channels < full_channels) {                                                          // 0.0
/*518 */         ret = av_samples_get_buffer_size(NULL, full_channels - channels,                            // 0.0
/*520 */                                          frame->nb_samples,                                         // 0.0
/*522 */                                          avctx->sample_fmt, 0);                                     // 0.0
/*524 */         if (ret < 0)                                                                                // 0.0
/*526 */             return ret;                                                                             // 0.0
/*530 */         av_fast_malloc(&s->extra_channels_buffer,                                                   // 0.0
/*532 */                        &s->extra_channels_buffer_size, ret);                                        // 0.0
/*534 */         if (!s->extra_channels_buffer)                                                              // 0.0
/*536 */             return AVERROR(ENOMEM);                                                                 // 0.0
/*540 */         ret = av_samples_fill_arrays((uint8_t **)s->extra_channels, NULL,                           // 0.0
/*542 */                                      s->extra_channels_buffer,                                      // 0.0
/*544 */                                      full_channels - channels,                                      // 0.0
/*546 */                                      frame->nb_samples, avctx->sample_fmt, 0);                      // 0.0
/*548 */         if (ret < 0)                                                                                // 0.0
/*550 */             return ret;                                                                             // 0.0
/*552 */     }                                                                                               // 0.0
/*556 */     /* filter to get final output */                                                                // 0.0
/*558 */     for (i = 0; i < (s->sample_blocks / 8); i++) {                                                  // 0.0
/*560 */         int ch;                                                                                     // 0.0
/*564 */         for (ch = 0; ch < channels; ch++)                                                           // 0.0
/*566 */             s->samples_chanptr[ch] = samples_flt[ch] + i * 256;                                     // 0.0
/*568 */         for (; ch < full_channels; ch++)                                                            // 0.0
/*570 */             s->samples_chanptr[ch] = s->extra_channels[ch - channels] + i * 256;                    // 0.0
/*574 */         dca_filter_channels(s, i);                                                                  // 0.0
/*578 */         /* If this was marked as a DTS-ES stream we need to subtract back- */                       // 0.0
/*580 */         /* channel from SL & SR to remove matrixed back-channel signal */                           // 0.0
/*582 */         if ((s->source_pcm_res & 1) && s->xch_present) {                                            // 0.0
/*584 */             float *back_chan = s->samples_chanptr[s->channel_order_tab[s->xch_base_channel]];       // 0.0
/*586 */             float *lt_chan   = s->samples_chanptr[s->channel_order_tab[s->xch_base_channel - 2]];   // 0.0
/*588 */             float *rt_chan   = s->samples_chanptr[s->channel_order_tab[s->xch_base_channel - 1]];   // 0.0
/*590 */             s->fdsp.vector_fmac_scalar(lt_chan, back_chan, -M_SQRT1_2, 256);                        // 0.0
/*592 */             s->fdsp.vector_fmac_scalar(rt_chan, back_chan, -M_SQRT1_2, 256);                        // 0.0
/*594 */         }                                                                                           // 0.0
/*596 */     }                                                                                               // 0.0
/*600 */     /* update lfe history */                                                                        // 0.0
/*602 */     lfe_samples = 2 * s->lfe * (s->sample_blocks / 8);                                              // 0.0
/*604 */     for (i = 0; i < 2 * s->lfe * 4; i++)                                                            // 0.0
/*606 */         s->lfe_data[i] = s->lfe_data[i + lfe_samples];                                              // 0.0
/*610 */     /* AVMatrixEncoding                                                                             // 0.0
/*612 */      *                                                                                              // 0.0
/*614 */      * DCA_STEREO_TOTAL (Lt/Rt) is equivalent to Dolby Surround */                                  // 0.0
/*616 */     ret = ff_side_data_update_matrix_encoding(frame,                                                // 0.0
/*618 */                                               (s->output & ~DCA_LFE) == DCA_STEREO_TOTAL ?          // 0.0
/*620 */                                               AV_MATRIX_ENCODING_DOLBY : AV_MATRIX_ENCODING_NONE);  // 0.0
/*622 */     if (ret < 0)                                                                                    // 0.0
/*624 */         return ret;                                                                                 // 0.0
/*628 */     *got_frame_ptr = 1;                                                                             // 0.0
/*632 */     return buf_size;                                                                                // 0.0
/*634 */ }                                                                                                   // 0.0
