// commit message FFmpeg@5674d4b0a3 (target=0, prob=0.4640127, correct=True): mpc8: check output buffer size before decoding
/*0   */ static int mpc8_decode_frame(AVCodecContext * avctx,                                                                                                                // (5) 0.03711
/*2   */                             void *data, int *data_size,                                                                                                             // (1) 0.07227
/*4   */                             AVPacket *avpkt)                                                                                                                        // (2) 0.06836
/*6   */ {                                                                                                                                                                   // (29) 0.001953
/*8   */     const uint8_t *buf = avpkt->data;                                                                                                                               // (11) 0.0332
/*10  */     int buf_size = avpkt->size;                                                                                                                                     // (16) 0.02734
/*12  */     MPCContext *c = avctx->priv_data;                                                                                                                               // (14) 0.03125
/*14  */     GetBitContext gb2, *gb = &gb2;                                                                                                                                  // (12) 0.0332
/*16  */     int i, j, k, ch, cnt, res, t;                                                                                                                                   // (6) 0.03711
/*18  */     Band *bands = c->bands;                                                                                                                                         // (18) 0.02148
/*20  */     int off;                                                                                                                                                        // (25) 0.01172
/*22  */     int maxband, keyframe;                                                                                                                                          // (19) 0.01953
/*24  */     int last[2];                                                                                                                                                    // (22) 0.01562
/*28  */     keyframe = c->cur_frame == 0;                                                                                                                                   // (15) 0.02734
/*32  */     if(keyframe){                                                                                                                                                   // (21) 0.01563
/*34  */         memset(c->Q, 0, sizeof(c->Q));                                                                                                                              // (4) 0.04297
/*36  */         c->last_bits_used = 0;                                                                                                                                      // (13) 0.0332
/*38  */     }                                                                                                                                                               // (28) 0.007812
/*40  */     init_get_bits(gb, buf, buf_size * 8);                                                                                                                           // (7) 0.03711
/*42  */     skip_bits(gb, c->last_bits_used & 7);                                                                                                                           // (8) 0.03711
/*46  */     if(keyframe)                                                                                                                                                    // (23) 0.01562
/*48  */         maxband = mpc8_get_mod_golomb(gb, c->maxbands + 1);                                                                                                         // (3) 0.06055
/*50  */     else{                                                                                                                                                           // (26) 0.009766
/*52  */         maxband = c->last_max_band + get_vlc2(gb, band_vlc.table, MPC8_BANDS_BITS, 2);                                                                              // (0) 0.08984
/*54  */         if(maxband > 32) maxband -= 33;                                                                                                                             // (9) 0.03711
/*56  */     }                                                                                                                                                               // (27) 0.007812
/*58  */     c->last_max_band = maxband;                                                                                                                                     // (17) 0.02734
/*62  */     /* read subband indexes */                                                                                                                                      // (20) 0.01758
/*64  */     if(maxband){                                                                                                                                                    // (24) 0.01562
/*66  */         last[0] = last[1] = 0;                                                                                                                                      // (10) 0.03711
/*68  */         for(i = maxband - 1; i >= 0; i--){                                                                                                                          // 0.0
/*70  */             for(ch = 0; ch < 2; ch++){                                                                                                                              // 0.0
/*72  */                 last[ch] = get_vlc2(gb, res_vlc[last[ch] > 2].table, MPC8_RES_BITS, 2) + last[ch];                                                                  // 0.0
/*74  */                 if(last[ch] > 15) last[ch] -= 17;                                                                                                                   // 0.0
/*76  */                 bands[i].res[ch] = last[ch];                                                                                                                        // 0.0
/*78  */             }                                                                                                                                                       // 0.0
/*80  */         }                                                                                                                                                           // 0.0
/*82  */         if(c->MSS){                                                                                                                                                 // 0.0
/*84  */             int mask;                                                                                                                                               // 0.0
/*88  */             cnt = 0;                                                                                                                                                // 0.0
/*90  */             for(i = 0; i < maxband; i++)                                                                                                                            // 0.0
/*92  */                 if(bands[i].res[0] || bands[i].res[1])                                                                                                              // 0.0
/*94  */                     cnt++;                                                                                                                                          // 0.0
/*96  */             t = mpc8_get_mod_golomb(gb, cnt);                                                                                                                       // 0.0
/*98  */             mask = mpc8_get_mask(gb, cnt, t);                                                                                                                       // 0.0
/*100 */             for(i = maxband - 1; i >= 0; i--)                                                                                                                       // 0.0
/*102 */                 if(bands[i].res[0] || bands[i].res[1]){                                                                                                             // 0.0
/*104 */                     bands[i].msf = mask & 1;                                                                                                                        // 0.0
/*106 */                     mask >>= 1;                                                                                                                                     // 0.0
/*108 */                 }                                                                                                                                                   // 0.0
/*110 */         }                                                                                                                                                           // 0.0
/*112 */     }                                                                                                                                                               // 0.0
/*114 */     for(i = maxband; i < c->maxbands; i++)                                                                                                                          // 0.0
/*116 */         bands[i].res[0] = bands[i].res[1] = 0;                                                                                                                      // 0.0
/*120 */     if(keyframe){                                                                                                                                                   // 0.0
/*122 */         for(i = 0; i < 32; i++)                                                                                                                                     // 0.0
/*124 */             c->oldDSCF[0][i] = c->oldDSCF[1][i] = 1;                                                                                                                // 0.0
/*126 */     }                                                                                                                                                               // 0.0
/*130 */     for(i = 0; i < maxband; i++){                                                                                                                                   // 0.0
/*132 */         if(bands[i].res[0] || bands[i].res[1]){                                                                                                                     // 0.0
/*134 */             cnt = !!bands[i].res[0] + !!bands[i].res[1] - 1;                                                                                                        // 0.0
/*136 */             if(cnt >= 0){                                                                                                                                           // 0.0
/*138 */                 t = get_vlc2(gb, scfi_vlc[cnt].table, scfi_vlc[cnt].bits, 1);                                                                                       // 0.0
/*140 */                 if(bands[i].res[0]) bands[i].scfi[0] = t >> (2 * cnt);                                                                                              // 0.0
/*142 */                 if(bands[i].res[1]) bands[i].scfi[1] = t & 3;                                                                                                       // 0.0
/*144 */             }                                                                                                                                                       // 0.0
/*146 */         }                                                                                                                                                           // 0.0
/*148 */     }                                                                                                                                                               // 0.0
/*152 */     for(i = 0; i < maxband; i++){                                                                                                                                   // 0.0
/*154 */         for(ch = 0; ch < 2; ch++){                                                                                                                                  // 0.0
/*156 */             if(!bands[i].res[ch]) continue;                                                                                                                         // 0.0
/*160 */             if(c->oldDSCF[ch][i]){                                                                                                                                  // 0.0
/*162 */                 bands[i].scf_idx[ch][0] = get_bits(gb, 7) - 6;                                                                                                      // 0.0
/*164 */                 c->oldDSCF[ch][i] = 0;                                                                                                                              // 0.0
/*166 */             }else{                                                                                                                                                  // 0.0
/*168 */                 t = get_vlc2(gb, dscf_vlc[1].table, MPC8_DSCF1_BITS, 2);                                                                                            // 0.0
/*170 */                 if(t == 64)                                                                                                                                         // 0.0
/*172 */                     t += get_bits(gb, 6);                                                                                                                           // 0.0
/*174 */                 bands[i].scf_idx[ch][0] = ((bands[i].scf_idx[ch][2] + t - 25) & 0x7F) - 6;                                                                          // 0.0
/*176 */             }                                                                                                                                                       // 0.0
/*178 */             for(j = 0; j < 2; j++){                                                                                                                                 // 0.0
/*180 */                 if((bands[i].scfi[ch] << j) & 2)                                                                                                                    // 0.0
/*182 */                     bands[i].scf_idx[ch][j + 1] = bands[i].scf_idx[ch][j];                                                                                          // 0.0
/*184 */                 else{                                                                                                                                               // 0.0
/*186 */                     t = get_vlc2(gb, dscf_vlc[0].table, MPC8_DSCF0_BITS, 2);                                                                                        // 0.0
/*188 */                     if(t == 31)                                                                                                                                     // 0.0
/*190 */                         t = 64 + get_bits(gb, 6);                                                                                                                   // 0.0
/*192 */                     bands[i].scf_idx[ch][j + 1] = ((bands[i].scf_idx[ch][j] + t - 25) & 0x7F) - 6;                                                                  // 0.0
/*194 */                 }                                                                                                                                                   // 0.0
/*196 */             }                                                                                                                                                       // 0.0
/*198 */         }                                                                                                                                                           // 0.0
/*200 */     }                                                                                                                                                               // 0.0
/*204 */     for(i = 0, off = 0; i < maxband; i++, off += SAMPLES_PER_BAND){                                                                                                 // 0.0
/*206 */         for(ch = 0; ch < 2; ch++){                                                                                                                                  // 0.0
/*208 */             res = bands[i].res[ch];                                                                                                                                 // 0.0
/*210 */             switch(res){                                                                                                                                            // 0.0
/*212 */             case -1:                                                                                                                                                // 0.0
/*214 */                 for(j = 0; j < SAMPLES_PER_BAND; j++)                                                                                                               // 0.0
/*216 */                     c->Q[ch][off + j] = (av_lfg_get(&c->rnd) & 0x3FC) - 510;                                                                                        // 0.0
/*218 */                 break;                                                                                                                                              // 0.0
/*220 */             case 0:                                                                                                                                                 // 0.0
/*222 */                 break;                                                                                                                                              // 0.0
/*224 */             case 1:                                                                                                                                                 // 0.0
/*226 */                 for(j = 0; j < SAMPLES_PER_BAND; j += SAMPLES_PER_BAND / 2){                                                                                        // 0.0
/*228 */                     cnt = get_vlc2(gb, q1_vlc.table, MPC8_Q1_BITS, 2);                                                                                              // 0.0
/*230 */                     t = mpc8_get_mask(gb, 18, cnt);                                                                                                                 // 0.0
/*232 */                     for(k = 0; k < SAMPLES_PER_BAND / 2; k++, t <<= 1)                                                                                              // 0.0
/*234 */                         c->Q[ch][off + j + k] = (t & 0x20000) ? (get_bits1(gb) << 1) - 1 : 0;                                                                       // 0.0
/*236 */                 }                                                                                                                                                   // 0.0
/*238 */                 break;                                                                                                                                              // 0.0
/*240 */             case 2:                                                                                                                                                 // 0.0
/*242 */                 cnt = 6;//2*mpc8_thres[res]                                                                                                                         // 0.0
/*244 */                 for(j = 0; j < SAMPLES_PER_BAND; j += 3){                                                                                                           // 0.0
/*246 */                     t = get_vlc2(gb, q2_vlc[cnt > 3].table, MPC8_Q2_BITS, 2);                                                                                       // 0.0
/*248 */                     c->Q[ch][off + j + 0] = mpc8_idx50[t];                                                                                                          // 0.0
/*250 */                     c->Q[ch][off + j + 1] = mpc8_idx51[t];                                                                                                          // 0.0
/*252 */                     c->Q[ch][off + j + 2] = mpc8_idx52[t];                                                                                                          // 0.0
/*254 */                     cnt = (cnt >> 1) + mpc8_huffq2[t];                                                                                                              // 0.0
/*256 */                 }                                                                                                                                                   // 0.0
/*258 */                 break;                                                                                                                                              // 0.0
/*260 */             case 3:                                                                                                                                                 // 0.0
/*262 */             case 4:                                                                                                                                                 // 0.0
/*264 */                 for(j = 0; j < SAMPLES_PER_BAND; j += 2){                                                                                                           // 0.0
/*266 */                     t = get_vlc2(gb, q3_vlc[res - 3].table, MPC8_Q3_BITS, 2) + q3_offsets[res - 3];                                                                 // 0.0
/*268 */                     c->Q[ch][off + j + 1] = t >> 4;                                                                                                                 // 0.0
/*270 */                     c->Q[ch][off + j + 0] = (t & 8) ? (t & 0xF) - 16 : (t & 0xF);                                                                                   // 0.0
/*272 */                 }                                                                                                                                                   // 0.0
/*274 */                 break;                                                                                                                                              // 0.0
/*276 */             case 5:                                                                                                                                                 // 0.0
/*278 */             case 6:                                                                                                                                                 // 0.0
/*280 */             case 7:                                                                                                                                                 // 0.0
/*282 */             case 8:                                                                                                                                                 // 0.0
/*284 */                 cnt = 2 * mpc8_thres[res];                                                                                                                          // 0.0
/*286 */                 for(j = 0; j < SAMPLES_PER_BAND; j++){                                                                                                              // 0.0
/*288 */                     t = get_vlc2(gb, quant_vlc[res - 5][cnt > mpc8_thres[res]].table, quant_vlc[res - 5][cnt > mpc8_thres[res]].bits, 2) + quant_offsets[res - 5];  // 0.0
/*290 */                     c->Q[ch][off + j] = t;                                                                                                                          // 0.0
/*292 */                     cnt = (cnt >> 1) + FFABS(c->Q[ch][off + j]);                                                                                                    // 0.0
/*294 */                 }                                                                                                                                                   // 0.0
/*296 */                 break;                                                                                                                                              // 0.0
/*298 */             default:                                                                                                                                                // 0.0
/*300 */                 for(j = 0; j < SAMPLES_PER_BAND; j++){                                                                                                              // 0.0
/*302 */                     c->Q[ch][off + j] = get_vlc2(gb, q9up_vlc.table, MPC8_Q9UP_BITS, 2);                                                                            // 0.0
/*304 */                     if(res != 9){                                                                                                                                   // 0.0
/*306 */                         c->Q[ch][off + j] <<= res - 9;                                                                                                              // 0.0
/*308 */                         c->Q[ch][off + j] |= get_bits(gb, res - 9);                                                                                                 // 0.0
/*310 */                     }                                                                                                                                               // 0.0
/*312 */                     c->Q[ch][off + j] -= (1 << (res - 2)) - 1;                                                                                                      // 0.0
/*314 */                 }                                                                                                                                                   // 0.0
/*316 */             }                                                                                                                                                       // 0.0
/*318 */         }                                                                                                                                                           // 0.0
/*320 */     }                                                                                                                                                               // 0.0
/*324 */     ff_mpc_dequantize_and_synth(c, maxband, data, avctx->channels);                                                                                                 // 0.0
/*328 */     c->cur_frame++;                                                                                                                                                 // 0.0
/*332 */     c->last_bits_used = get_bits_count(gb);                                                                                                                         // 0.0
/*334 */     if(c->cur_frame >= c->frames)                                                                                                                                   // 0.0
/*336 */         c->cur_frame = 0;                                                                                                                                           // 0.0
/*338 */     *data_size =  MPC_FRAME_SIZE * 2 * avctx->channels;                                                                                                             // 0.0
/*342 */     return c->cur_frame ? c->last_bits_used >> 3 : buf_size;                                                                                                        // 0.0
/*344 */ }                                                                                                                                                                   // 0.0
