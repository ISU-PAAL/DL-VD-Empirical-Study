// commit message FFmpeg@d7eabd5042 (target=0, prob=0.4977071, correct=True): mpc: pad mpc_CC/SCF[] tables to allow for negative indices.
/*0   */ static int mpc7_decode_frame(AVCodecContext * avctx, void *data,                                           // (5) 0.045
/*2   */                              int *got_frame_ptr, AVPacket *avpkt)                                          // (0) 0.08584
/*4   */ {                                                                                                          // (28) 0.001974
/*6   */     const uint8_t *buf = avpkt->data;                                                                      // (8) 0.03317
/*8   */     int buf_size;                                                                                          // (25) 0.01561
/*10  */     MPCContext *c = avctx->priv_data;                                                                      // (10) 0.03126
/*12  */     GetBitContext gb;                                                                                      // (22) 0.01756
/*14  */     int i, ch;                                                                                             // (23) 0.01561
/*16  */     int mb = -1;                                                                                           // (20) 0.01951
/*18  */     Band *bands = c->bands;                                                                                // (18) 0.02148
/*20  */     int off, ret, last_frame, skip;                                                                        // (14) 0.0279
/*22  */     int bits_used, bits_avail;                                                                             // (15) 0.02538
/*26  */     memset(bands, 0, sizeof(*bands) * (c->maxbands + 1));                                                  // (6) 0.04488
/*30  */     buf_size = avpkt->size & ~3;                                                                           // (12) 0.03121
/*32  */     if (buf_size <= 0) {                                                                                   // (17) 0.02341
/*34  */         av_log(avctx, AV_LOG_ERROR, "packet size is too small (%i bytes)\n",                               // (1) 0.06438
/*36  */                avpkt->size);                                                                               // (7) 0.03901
/*38  */         return AVERROR_INVALIDDATA;                                                                        // (9) 0.03316
/*40  */     }                                                                                                      // (26) 0.007804
/*42  */     if (buf_size != avpkt->size) {                                                                         // (11) 0.03121
/*44  */         av_log(avctx, AV_LOG_WARNING, "packet size is not a multiple of 4. "                               // (2) 0.06243
/*46  */                "extra bytes at the end will be skipped.\n");                                               // (4) 0.05267
/*48  */     }                                                                                                      // (27) 0.007803
/*52  */     skip       = buf[0];                                                                                   // (13) 0.02929
/*54  */     last_frame = buf[1];                                                                                   // (19) 0.02147
/*56  */     buf       += 4;                                                                                        // (16) 0.02536
/*58  */     buf_size  -= 4;                                                                                        // (21) 0.01951
/*62  */     /* get output buffer */                                                                                // (24) 0.01561
/*64  */     c->frame.nb_samples = last_frame ? c->lastframelen : MPC_FRAME_SIZE;                                   // (3) 0.06053
/*66  */     if ((ret = avctx->get_buffer(avctx, &c->frame)) < 0) {                                                 // 0.0
/*68  */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                                              // 0.0
/*70  */         return ret;                                                                                        // 0.0
/*72  */     }                                                                                                      // 0.0
/*76  */     av_fast_padded_malloc(&c->bits, &c->buf_size, buf_size);                                               // 0.0
/*78  */     if (!c->bits)                                                                                          // 0.0
/*80  */         return AVERROR(ENOMEM);                                                                            // 0.0
/*82  */     c->dsp.bswap_buf((uint32_t *)c->bits, (const uint32_t *)buf, buf_size >> 2);                           // 0.0
/*84  */     init_get_bits(&gb, c->bits, buf_size * 8);                                                             // 0.0
/*86  */     skip_bits_long(&gb, skip);                                                                             // 0.0
/*90  */     /* read subband indexes */                                                                             // 0.0
/*92  */     for(i = 0; i <= c->maxbands; i++){                                                                     // 0.0
/*94  */         for(ch = 0; ch < 2; ch++){                                                                         // 0.0
/*96  */             int t = 4;                                                                                     // 0.0
/*98  */             if(i) t = get_vlc2(&gb, hdr_vlc.table, MPC7_HDR_BITS, 1) - 5;                                  // 0.0
/*100 */             if(t == 4) bands[i].res[ch] = get_bits(&gb, 4);                                                // 0.0
/*102 */             else bands[i].res[ch] = bands[i-1].res[ch] + t;                                                // 0.0
/*104 */         }                                                                                                  // 0.0
/*108 */         if(bands[i].res[0] || bands[i].res[1]){                                                            // 0.0
/*110 */             mb = i;                                                                                        // 0.0
/*112 */             if(c->MSS) bands[i].msf = get_bits1(&gb);                                                      // 0.0
/*114 */         }                                                                                                  // 0.0
/*116 */     }                                                                                                      // 0.0
/*118 */     /* get scale indexes coding method */                                                                  // 0.0
/*120 */     for(i = 0; i <= mb; i++)                                                                               // 0.0
/*122 */         for(ch = 0; ch < 2; ch++)                                                                          // 0.0
/*124 */             if(bands[i].res[ch]) bands[i].scfi[ch] = get_vlc2(&gb, scfi_vlc.table, MPC7_SCFI_BITS, 1);     // 0.0
/*126 */     /* get scale indexes */                                                                                // 0.0
/*128 */     for(i = 0; i <= mb; i++){                                                                              // 0.0
/*130 */         for(ch = 0; ch < 2; ch++){                                                                         // 0.0
/*132 */             if(bands[i].res[ch]){                                                                          // 0.0
/*134 */                 bands[i].scf_idx[ch][2] = c->oldDSCF[ch][i];                                               // 0.0
/*136 */                 bands[i].scf_idx[ch][0] = get_scale_idx(&gb, bands[i].scf_idx[ch][2]);                     // 0.0
/*138 */                 switch(bands[i].scfi[ch]){                                                                 // 0.0
/*140 */                 case 0:                                                                                    // 0.0
/*142 */                     bands[i].scf_idx[ch][1] = get_scale_idx(&gb, bands[i].scf_idx[ch][0]);                 // 0.0
/*144 */                     bands[i].scf_idx[ch][2] = get_scale_idx(&gb, bands[i].scf_idx[ch][1]);                 // 0.0
/*146 */                     break;                                                                                 // 0.0
/*148 */                 case 1:                                                                                    // 0.0
/*150 */                     bands[i].scf_idx[ch][1] = get_scale_idx(&gb, bands[i].scf_idx[ch][0]);                 // 0.0
/*152 */                     bands[i].scf_idx[ch][2] = bands[i].scf_idx[ch][1];                                     // 0.0
/*154 */                     break;                                                                                 // 0.0
/*156 */                 case 2:                                                                                    // 0.0
/*158 */                     bands[i].scf_idx[ch][1] = bands[i].scf_idx[ch][0];                                     // 0.0
/*160 */                     bands[i].scf_idx[ch][2] = get_scale_idx(&gb, bands[i].scf_idx[ch][1]);                 // 0.0
/*162 */                     break;                                                                                 // 0.0
/*164 */                 case 3:                                                                                    // 0.0
/*166 */                     bands[i].scf_idx[ch][2] = bands[i].scf_idx[ch][1] = bands[i].scf_idx[ch][0];           // 0.0
/*168 */                     break;                                                                                 // 0.0
/*170 */                 }                                                                                          // 0.0
/*172 */                 c->oldDSCF[ch][i] = bands[i].scf_idx[ch][2];                                               // 0.0
/*174 */             }                                                                                              // 0.0
/*176 */         }                                                                                                  // 0.0
/*178 */     }                                                                                                      // 0.0
/*180 */     /* get quantizers */                                                                                   // 0.0
/*182 */     memset(c->Q, 0, sizeof(c->Q));                                                                         // 0.0
/*184 */     off = 0;                                                                                               // 0.0
/*186 */     for(i = 0; i < BANDS; i++, off += SAMPLES_PER_BAND)                                                    // 0.0
/*188 */         for(ch = 0; ch < 2; ch++)                                                                          // 0.0
/*190 */             idx_to_quant(c, &gb, bands[i].res[ch], c->Q[ch] + off);                                        // 0.0
/*194 */     ff_mpc_dequantize_and_synth(c, mb, c->frame.data[0], 2);                                               // 0.0
/*198 */     bits_used = get_bits_count(&gb);                                                                       // 0.0
/*200 */     bits_avail = buf_size * 8;                                                                             // 0.0
/*202 */     if (!last_frame && ((bits_avail < bits_used) || (bits_used + 32 <= bits_avail))) {                     // 0.0
/*204 */         av_log(avctx, AV_LOG_ERROR, "Error decoding frame: used %i of %i bits\n", bits_used, bits_avail);  // 0.0
/*206 */         return -1;                                                                                         // 0.0
/*208 */     }                                                                                                      // 0.0
/*210 */     if(c->frames_to_skip){                                                                                 // 0.0
/*212 */         c->frames_to_skip--;                                                                               // 0.0
/*214 */         *got_frame_ptr = 0;                                                                                // 0.0
/*216 */         return avpkt->size;                                                                                // 0.0
/*218 */     }                                                                                                      // 0.0
/*222 */     *got_frame_ptr   = 1;                                                                                  // 0.0
/*224 */     *(AVFrame *)data = c->frame;                                                                           // 0.0
/*228 */     return avpkt->size;                                                                                    // 0.0
/*230 */ }                                                                                                          // 0.0
