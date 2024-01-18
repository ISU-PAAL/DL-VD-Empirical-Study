// commit message FFmpeg@5257743aee (target=1, prob=0.43416008, correct=False): ws_snd1: Fix wrong samples count and crash.
/*0   */ static int ws_snd_decode_frame(AVCodecContext *avctx, void *data,                 // (5) 0.04883
/*2   */                                int *got_frame_ptr, AVPacket *avpkt)               // (0) 0.08984
/*4   */ {                                                                                 // (29) 0.001953
/*6   */     WSSndContext *s = avctx->priv_data;                                           // (7) 0.0332
/*8   */     const uint8_t *buf = avpkt->data;                                             // (9) 0.0332
/*10  */     int buf_size       = avpkt->size;                                             // (6) 0.03906
/*14  */     int in_size, out_size, ret;                                                   // (15) 0.02734
/*16  */     int sample = 128;                                                             // (24) 0.01562
/*18  */     uint8_t *samples;                                                             // (18) 0.02148
/*20  */     uint8_t *samples_end;                                                         // (16) 0.02539
/*24  */     if (!buf_size)                                                                // (22) 0.01758
/*26  */         return 0;                                                                 // (21) 0.01953
/*30  */     if (buf_size < 4) {                                                           // (17) 0.02344
/*32  */         av_log(avctx, AV_LOG_ERROR, "packet is too small\n");                     // (2) 0.05664
/*34  */         return AVERROR(EINVAL);                                                   // (13) 0.03125
/*36  */     }                                                                             // (28) 0.007812
/*40  */     out_size = AV_RL16(&buf[0]);                                                  // (12) 0.03125
/*42  */     in_size  = AV_RL16(&buf[2]);                                                  // (8) 0.0332
/*44  */     buf += 4;                                                                     // (25) 0.01367
/*48  */     if (in_size > buf_size) {                                                     // (14) 0.02734
/*50  */         av_log(avctx, AV_LOG_ERROR, "Frame data is larger than input buffer\n");  // (1) 0.06055
/*52  */         return -1;                                                                // (19) 0.02148
/*54  */     }                                                                             // (26) 0.007812
/*58  */     /* get output buffer */                                                       // (23) 0.01562
/*60  */     s->frame.nb_samples = out_size;                                               // (11) 0.03125
/*62  */     if ((ret = avctx->get_buffer(avctx, &s->frame)) < 0) {                        // (4) 0.05078
/*64  */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                     // (3) 0.05664
/*66  */         return ret;                                                               // (20) 0.01953
/*68  */     }                                                                             // (27) 0.007812
/*70  */     samples     = s->frame.data[0];                                               // (10) 0.0332
/*72  */     samples_end = samples + out_size;                                             // 0.0
/*76  */     if (in_size == out_size) {                                                    // 0.0
/*78  */         memcpy(samples, buf, out_size);                                           // 0.0
/*80  */         *got_frame_ptr   = 1;                                                     // 0.0
/*82  */         *(AVFrame *)data = s->frame;                                              // 0.0
/*84  */         return buf_size;                                                          // 0.0
/*86  */     }                                                                             // 0.0
/*90  */     while (samples < samples_end && buf - avpkt->data < buf_size) {               // 0.0
/*92  */         int code, smp, size;                                                      // 0.0
/*94  */         uint8_t count;                                                            // 0.0
/*96  */         code  = *buf >> 6;                                                        // 0.0
/*98  */         count = *buf & 0x3F;                                                      // 0.0
/*100 */         buf++;                                                                    // 0.0
/*104 */         /* make sure we don't write past the output buffer */                     // 0.0
/*106 */         switch (code) {                                                           // 0.0
/*108 */         case 0:  smp = 4;                              break;                     // 0.0
/*110 */         case 1:  smp = 2;                              break;                     // 0.0
/*112 */         case 2:  smp = (count & 0x20) ? 1 : count + 1; break;                     // 0.0
/*114 */         default: smp = count + 1;                      break;                     // 0.0
/*116 */         }                                                                         // 0.0
/*118 */         if (samples_end - samples < smp)                                          // 0.0
/*120 */             break;                                                                // 0.0
/*124 */         /* make sure we don't read past the input buffer */                       // 0.0
/*126 */         size = ((code == 2 && (count & 0x20)) || code == 3) ? 0 : count + 1;      // 0.0
/*128 */         if ((buf - avpkt->data) + size > buf_size)                                // 0.0
/*130 */             break;                                                                // 0.0
/*134 */         switch (code) {                                                           // 0.0
/*136 */         case 0: /* ADPCM 2-bit */                                                 // 0.0
/*138 */             for (count++; count > 0; count--) {                                   // 0.0
/*140 */                 code = *buf++;                                                    // 0.0
/*142 */                 sample += ( code       & 0x3) - 2;                                // 0.0
/*144 */                 sample = av_clip_uint8(sample);                                   // 0.0
/*146 */                 *samples++ = sample;                                              // 0.0
/*148 */                 sample += ((code >> 2) & 0x3) - 2;                                // 0.0
/*150 */                 sample = av_clip_uint8(sample);                                   // 0.0
/*152 */                 *samples++ = sample;                                              // 0.0
/*154 */                 sample += ((code >> 4) & 0x3) - 2;                                // 0.0
/*156 */                 sample = av_clip_uint8(sample);                                   // 0.0
/*158 */                 *samples++ = sample;                                              // 0.0
/*160 */                 sample +=  (code >> 6)        - 2;                                // 0.0
/*162 */                 sample = av_clip_uint8(sample);                                   // 0.0
/*164 */                 *samples++ = sample;                                              // 0.0
/*166 */             }                                                                     // 0.0
/*168 */             break;                                                                // 0.0
/*170 */         case 1: /* ADPCM 4-bit */                                                 // 0.0
/*172 */             for (count++; count > 0; count--) {                                   // 0.0
/*174 */                 code = *buf++;                                                    // 0.0
/*176 */                 sample += ws_adpcm_4bit[code & 0xF];                              // 0.0
/*178 */                 sample = av_clip_uint8(sample);                                   // 0.0
/*180 */                 *samples++ = sample;                                              // 0.0
/*182 */                 sample += ws_adpcm_4bit[code >> 4];                               // 0.0
/*184 */                 sample = av_clip_uint8(sample);                                   // 0.0
/*186 */                 *samples++ = sample;                                              // 0.0
/*188 */             }                                                                     // 0.0
/*190 */             break;                                                                // 0.0
/*192 */         case 2: /* no compression */                                              // 0.0
/*194 */             if (count & 0x20) { /* big delta */                                   // 0.0
/*196 */                 int8_t t;                                                         // 0.0
/*198 */                 t = count;                                                        // 0.0
/*200 */                 t <<= 3;                                                          // 0.0
/*202 */                 sample += t >> 3;                                                 // 0.0
/*204 */                 sample = av_clip_uint8(sample);                                   // 0.0
/*206 */                 *samples++ = sample;                                              // 0.0
/*208 */             } else { /* copy */                                                   // 0.0
/*210 */                 memcpy(samples, buf, smp);                                        // 0.0
/*212 */                 samples += smp;                                                   // 0.0
/*214 */                 buf     += smp;                                                   // 0.0
/*216 */                 sample = buf[-1];                                                 // 0.0
/*218 */             }                                                                     // 0.0
/*220 */             break;                                                                // 0.0
/*222 */         default: /* run */                                                        // 0.0
/*224 */             memset(samples, sample, smp);                                         // 0.0
/*226 */             samples += smp;                                                       // 0.0
/*228 */         }                                                                         // 0.0
/*230 */     }                                                                             // 0.0
/*234 */     s->frame.nb_samples = samples - s->frame.data[0];                             // 0.0
/*236 */     *got_frame_ptr   = 1;                                                         // 0.0
/*238 */     *(AVFrame *)data = s->frame;                                                  // 0.0
/*242 */     return buf_size;                                                              // 0.0
/*244 */ }                                                                                 // 0.0
