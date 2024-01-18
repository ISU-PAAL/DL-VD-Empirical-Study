// commit message FFmpeg@381e195b46 (target=0, prob=0.5350354, correct=False): pcmdec: move DVD PCM bits_per_coded_sample check near to the code that sets the sample size.
/*0   */ static int pcm_decode_frame(AVCodecContext *avctx,                                                 // (11) 0.03517
/*2   */                             void *data, int *data_size,                                            // (0) 0.07226
/*4   */                             AVPacket *avpkt)                                                       // (1) 0.06836
/*6   */ {                                                                                                  // (24) 0.001956
/*8   */     const uint8_t *buf = avpkt->data;                                                              // (13) 0.0332
/*10  */     int buf_size = avpkt->size;                                                                    // (15) 0.02734
/*12  */     PCMDecode *s = avctx->priv_data;                                                               // (12) 0.0332
/*14  */     int sample_size, c, n, i;                                                                      // (16) 0.02734
/*16  */     uint8_t *samples;                                                                              // (17) 0.02148
/*18  */     const uint8_t *src, *src8, *src2[MAX_CHANNELS];                                                // (8) 0.04883
/*20  */     int32_t *dst_int32_t;                                                                          // (14) 0.03125
/*24  */     samples = data;                                                                                // (21) 0.01367
/*26  */     src = buf;                                                                                     // (20) 0.01367
/*30  */     if (avctx->sample_fmt!=avctx->codec->sample_fmts[0]) {                                         // (4) 0.05469
/*32  */         av_log(avctx, AV_LOG_ERROR, "invalid sample_fmt\n");                                       // (3) 0.05859
/*34  */         return -1;                                                                                 // (19) 0.02148
/*36  */     }                                                                                              // (23) 0.007812
/*40  */     if(avctx->channels <= 0 || avctx->channels > MAX_CHANNELS){                                    // (7) 0.04883
/*42  */         av_log(avctx, AV_LOG_ERROR, "PCM channels out of bounds\n");                               // (2) 0.05859
/*44  */         return -1;                                                                                 // (18) 0.02148
/*46  */     }                                                                                              // (22) 0.007813
/*50  */     sample_size = av_get_bits_per_sample(avctx->codec_id)/8;                                       // (6) 0.05273
/*54  */     /* av_get_bits_per_sample returns 0 for CODEC_ID_PCM_DVD */                                    // (5) 0.05273
/*56  */     if (CODEC_ID_PCM_DVD == avctx->codec_id)                                                       // (9) 0.04687
/*58  */         /* 2 samples are interleaved per block in PCM_DVD */                                       // (10) 0.04297
/*60  */         sample_size = avctx->bits_per_coded_sample * 2 / 8;                                        // 0.0
/*62  */     else if (avctx->codec_id == CODEC_ID_PCM_LXF)                                                  // 0.0
/*64  */         /* we process 40-bit blocks per channel for LXF */                                         // 0.0
/*66  */         sample_size = 5;                                                                           // 0.0
/*70  */     if (sample_size == 0) {                                                                        // 0.0
/*72  */         av_log(avctx, AV_LOG_ERROR, "Invalid sample_size\n");                                      // 0.0
/*74  */         return AVERROR(EINVAL);                                                                    // 0.0
/*76  */     }                                                                                              // 0.0
/*80  */     n = avctx->channels * sample_size;                                                             // 0.0
/*84  */     if(n && buf_size % n){                                                                         // 0.0
/*86  */         if (buf_size < n) {                                                                        // 0.0
/*88  */             av_log(avctx, AV_LOG_ERROR, "invalid PCM packet\n");                                   // 0.0
/*90  */             return -1;                                                                             // 0.0
/*92  */         }else                                                                                      // 0.0
/*94  */             buf_size -= buf_size % n;                                                              // 0.0
/*96  */     }                                                                                              // 0.0
/*100 */     buf_size= FFMIN(buf_size, *data_size/2);                                                       // 0.0
/*104 */     n = buf_size/sample_size;                                                                      // 0.0
/*108 */     switch(avctx->codec->id) {                                                                     // 0.0
/*110 */     case CODEC_ID_PCM_U32LE:                                                                       // 0.0
/*112 */         DECODE(32, le32, src, samples, n, 0, 0x80000000)                                           // 0.0
/*114 */         break;                                                                                     // 0.0
/*116 */     case CODEC_ID_PCM_U32BE:                                                                       // 0.0
/*118 */         DECODE(32, be32, src, samples, n, 0, 0x80000000)                                           // 0.0
/*120 */         break;                                                                                     // 0.0
/*122 */     case CODEC_ID_PCM_S24LE:                                                                       // 0.0
/*124 */         DECODE(32, le24, src, samples, n, 8, 0)                                                    // 0.0
/*126 */         break;                                                                                     // 0.0
/*128 */     case CODEC_ID_PCM_S24BE:                                                                       // 0.0
/*130 */         DECODE(32, be24, src, samples, n, 8, 0)                                                    // 0.0
/*132 */         break;                                                                                     // 0.0
/*134 */     case CODEC_ID_PCM_U24LE:                                                                       // 0.0
/*136 */         DECODE(32, le24, src, samples, n, 8, 0x800000)                                             // 0.0
/*138 */         break;                                                                                     // 0.0
/*140 */     case CODEC_ID_PCM_U24BE:                                                                       // 0.0
/*142 */         DECODE(32, be24, src, samples, n, 8, 0x800000)                                             // 0.0
/*144 */         break;                                                                                     // 0.0
/*146 */     case CODEC_ID_PCM_S24DAUD:                                                                     // 0.0
/*148 */         for(;n>0;n--) {                                                                            // 0.0
/*150 */           uint32_t v = bytestream_get_be24(&src);                                                  // 0.0
/*152 */           v >>= 4; // sync flags are here                                                          // 0.0
/*154 */           AV_WN16A(samples, av_reverse[(v >> 8) & 0xff] +                                          // 0.0
/*156 */                            (av_reverse[v & 0xff] << 8));                                           // 0.0
/*158 */           samples += 2;                                                                            // 0.0
/*160 */         }                                                                                          // 0.0
/*162 */         break;                                                                                     // 0.0
/*164 */     case CODEC_ID_PCM_S16LE_PLANAR:                                                                // 0.0
/*166 */         n /= avctx->channels;                                                                      // 0.0
/*168 */         for(c=0;c<avctx->channels;c++)                                                             // 0.0
/*170 */             src2[c] = &src[c*n*2];                                                                 // 0.0
/*172 */         for(;n>0;n--)                                                                              // 0.0
/*174 */             for(c=0;c<avctx->channels;c++) {                                                       // 0.0
/*176 */                 AV_WN16A(samples, bytestream_get_le16(&src2[c]));                                  // 0.0
/*178 */                 samples += 2;                                                                      // 0.0
/*180 */             }                                                                                      // 0.0
/*182 */         src = src2[avctx->channels-1];                                                             // 0.0
/*184 */         break;                                                                                     // 0.0
/*186 */     case CODEC_ID_PCM_U16LE:                                                                       // 0.0
/*188 */         DECODE(16, le16, src, samples, n, 0, 0x8000)                                               // 0.0
/*190 */         break;                                                                                     // 0.0
/*192 */     case CODEC_ID_PCM_U16BE:                                                                       // 0.0
/*194 */         DECODE(16, be16, src, samples, n, 0, 0x8000)                                               // 0.0
/*196 */         break;                                                                                     // 0.0
/*198 */     case CODEC_ID_PCM_S8:                                                                          // 0.0
/*200 */         for(;n>0;n--) {                                                                            // 0.0
/*202 */             *samples++ = *src++ + 128;                                                             // 0.0
/*204 */         }                                                                                          // 0.0
/*206 */         break;                                                                                     // 0.0
/*208 */ #if HAVE_BIGENDIAN                                                                                 // 0.0
/*210 */     case CODEC_ID_PCM_F64LE:                                                                       // 0.0
/*212 */         DECODE(64, le64, src, samples, n, 0, 0)                                                    // 0.0
/*214 */         break;                                                                                     // 0.0
/*216 */     case CODEC_ID_PCM_S32LE:                                                                       // 0.0
/*218 */     case CODEC_ID_PCM_F32LE:                                                                       // 0.0
/*220 */         DECODE(32, le32, src, samples, n, 0, 0)                                                    // 0.0
/*222 */         break;                                                                                     // 0.0
/*224 */     case CODEC_ID_PCM_S16LE:                                                                       // 0.0
/*226 */         DECODE(16, le16, src, samples, n, 0, 0)                                                    // 0.0
/*228 */         break;                                                                                     // 0.0
/*230 */     case CODEC_ID_PCM_F64BE:                                                                       // 0.0
/*232 */     case CODEC_ID_PCM_F32BE:                                                                       // 0.0
/*234 */     case CODEC_ID_PCM_S32BE:                                                                       // 0.0
/*236 */     case CODEC_ID_PCM_S16BE:                                                                       // 0.0
/*238 */ #else                                                                                              // 0.0
/*240 */     case CODEC_ID_PCM_F64BE:                                                                       // 0.0
/*242 */         DECODE(64, be64, src, samples, n, 0, 0)                                                    // 0.0
/*244 */         break;                                                                                     // 0.0
/*246 */     case CODEC_ID_PCM_F32BE:                                                                       // 0.0
/*248 */     case CODEC_ID_PCM_S32BE:                                                                       // 0.0
/*250 */         DECODE(32, be32, src, samples, n, 0, 0)                                                    // 0.0
/*252 */         break;                                                                                     // 0.0
/*254 */     case CODEC_ID_PCM_S16BE:                                                                       // 0.0
/*256 */         DECODE(16, be16, src, samples, n, 0, 0)                                                    // 0.0
/*258 */         break;                                                                                     // 0.0
/*260 */     case CODEC_ID_PCM_F64LE:                                                                       // 0.0
/*262 */     case CODEC_ID_PCM_F32LE:                                                                       // 0.0
/*264 */     case CODEC_ID_PCM_S32LE:                                                                       // 0.0
/*266 */     case CODEC_ID_PCM_S16LE:                                                                       // 0.0
/*268 */ #endif /* HAVE_BIGENDIAN */                                                                        // 0.0
/*270 */     case CODEC_ID_PCM_U8:                                                                          // 0.0
/*272 */         memcpy(samples, src, n*sample_size);                                                       // 0.0
/*274 */         src += n*sample_size;                                                                      // 0.0
/*276 */         samples += n * sample_size;                                                                // 0.0
/*278 */         break;                                                                                     // 0.0
/*280 */     case CODEC_ID_PCM_ZORK:                                                                        // 0.0
/*282 */         for(;n>0;n--) {                                                                            // 0.0
/*284 */             int x= *src++;                                                                         // 0.0
/*286 */             if(x&128) x-= 128;                                                                     // 0.0
/*288 */             else      x = -x;                                                                      // 0.0
/*290 */             AV_WN16A(samples, x << 8);                                                             // 0.0
/*292 */             samples += 2;                                                                          // 0.0
/*294 */         }                                                                                          // 0.0
/*296 */         break;                                                                                     // 0.0
/*298 */     case CODEC_ID_PCM_ALAW:                                                                        // 0.0
/*300 */     case CODEC_ID_PCM_MULAW:                                                                       // 0.0
/*302 */         for(;n>0;n--) {                                                                            // 0.0
/*304 */             AV_WN16A(samples, s->table[*src++]);                                                   // 0.0
/*306 */             samples += 2;                                                                          // 0.0
/*308 */         }                                                                                          // 0.0
/*310 */         break;                                                                                     // 0.0
/*312 */     case CODEC_ID_PCM_DVD:                                                                         // 0.0
/*314 */         dst_int32_t = data;                                                                        // 0.0
/*316 */         n /= avctx->channels;                                                                      // 0.0
/*318 */         switch (avctx->bits_per_coded_sample) {                                                    // 0.0
/*320 */         case 20:                                                                                   // 0.0
/*322 */             while (n--) {                                                                          // 0.0
/*324 */                 c = avctx->channels;                                                               // 0.0
/*326 */                 src8 = src + 4*c;                                                                  // 0.0
/*328 */                 while (c--) {                                                                      // 0.0
/*330 */                     *dst_int32_t++ = (bytestream_get_be16(&src) << 16) + ((*src8   &0xf0) << 8);   // 0.0
/*332 */                     *dst_int32_t++ = (bytestream_get_be16(&src) << 16) + ((*src8++ &0x0f) << 12);  // 0.0
/*334 */                 }                                                                                  // 0.0
/*336 */                 src = src8;                                                                        // 0.0
/*338 */             }                                                                                      // 0.0
/*340 */             break;                                                                                 // 0.0
/*342 */         case 24:                                                                                   // 0.0
/*344 */             while (n--) {                                                                          // 0.0
/*346 */                 c = avctx->channels;                                                               // 0.0
/*348 */                 src8 = src + 4*c;                                                                  // 0.0
/*350 */                 while (c--) {                                                                      // 0.0
/*352 */                     *dst_int32_t++ = (bytestream_get_be16(&src) << 16) + ((*src8++) << 8);         // 0.0
/*354 */                     *dst_int32_t++ = (bytestream_get_be16(&src) << 16) + ((*src8++) << 8);         // 0.0
/*356 */                 }                                                                                  // 0.0
/*358 */                 src = src8;                                                                        // 0.0
/*360 */             }                                                                                      // 0.0
/*362 */             break;                                                                                 // 0.0
/*364 */         default:                                                                                   // 0.0
/*366 */             av_log(avctx, AV_LOG_ERROR, "PCM DVD unsupported sample depth\n");                     // 0.0
/*368 */             return -1;                                                                             // 0.0
/*370 */         }                                                                                          // 0.0
/*372 */         samples = (uint8_t *) dst_int32_t;                                                         // 0.0
/*374 */         break;                                                                                     // 0.0
/*376 */     case CODEC_ID_PCM_LXF:                                                                         // 0.0
/*378 */         dst_int32_t = data;                                                                        // 0.0
/*380 */         n /= avctx->channels;                                                                      // 0.0
/*382 */         //unpack and de-planerize                                                                  // 0.0
/*384 */         for (i = 0; i < n; i++) {                                                                  // 0.0
/*386 */             for (c = 0, src8 = src + i*5; c < avctx->channels; c++, src8 += n*5) {                 // 0.0
/*388 */                 //extract low 20 bits and expand to 32 bits                                        // 0.0
/*390 */                 *dst_int32_t++ = (src8[2] << 28) | (src8[1] << 20) | (src8[0] << 12) |             // 0.0
/*392 */                                  ((src8[2] & 0xF) << 8) | src8[1];                                 // 0.0
/*394 */             }                                                                                      // 0.0
/*398 */             for (c = 0, src8 = src + i*5; c < avctx->channels; c++, src8 += n*5) {                 // 0.0
/*400 */                 //extract high 20 bits and expand to 32 bits                                       // 0.0
/*402 */                 *dst_int32_t++ = (src8[4] << 24) | (src8[3] << 16) |                               // 0.0
/*404 */                                  ((src8[2] & 0xF0) << 8) | (src8[4] << 4) | (src8[3] >> 4);        // 0.0
/*406 */             }                                                                                      // 0.0
/*408 */         }                                                                                          // 0.0
/*410 */         src += n * avctx->channels * 5;                                                            // 0.0
/*412 */         samples = (uint8_t *) dst_int32_t;                                                         // 0.0
/*414 */         break;                                                                                     // 0.0
/*416 */     default:                                                                                       // 0.0
/*418 */         return -1;                                                                                 // 0.0
/*420 */     }                                                                                              // 0.0
/*422 */     *data_size = samples - (uint8_t *)data;                                                        // 0.0
/*424 */     return src - buf;                                                                              // 0.0
/*426 */ }                                                                                                  // 0.0
