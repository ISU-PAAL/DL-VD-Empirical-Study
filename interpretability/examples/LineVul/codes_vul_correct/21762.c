// commit message FFmpeg@fbfbd97be2 (target=1, prob=0.76045966, correct=True): avcodec/xpmdec: there are XPM files with dos line endings
/*0   */ static int xpm_decode_frame(AVCodecContext *avctx, void *data,                                    // (9) 0.04297
/*2   */                             int *got_frame, AVPacket *avpkt)                                      // (0) 0.08008
/*4   */ {                                                                                                 // (25) 0.001954
/*6   */     XPMDecContext *x = avctx->priv_data;                                                          // (11) 0.0332
/*8   */     AVFrame *p=data;                                                                              // (18) 0.01953
/*10  */     const uint8_t *end, *ptr = avpkt->data;                                                       // (10) 0.03906
/*12  */     int ncolors, cpp, ret, i, j;                                                                  // (13) 0.0332
/*14  */     int64_t size;                                                                                 // (22) 0.01758
/*16  */     uint32_t *dst;                                                                                // (17) 0.02148
/*20  */     avctx->pix_fmt = AV_PIX_FMT_BGRA;                                                             // (7) 0.04492
/*24  */     end = avpkt->data + avpkt->size;                                                              // (12) 0.0332
/*26  */     while (memcmp(ptr, "/* XPM */\n", 10) && ptr < end - 10)                                      // (3) 0.05273
/*28  */         ptr++;                                                                                    // (21) 0.01758
/*32  */     if (ptr >= end) {                                                                             // (20) 0.01953
/*34  */         av_log(avctx, AV_LOG_ERROR, "missing signature\n");                                       // (5) 0.05078
/*36  */         return AVERROR_INVALIDDATA;                                                               // (16) 0.0332
/*38  */     }                                                                                             // (23) 0.007812
/*42  */     ptr += mod_strcspn(ptr, "\"");                                                                // (14) 0.0332
/*44  */     if (sscanf(ptr, "\"%u %u %u %u\",",                                                           // (6) 0.04687
/*46  */                &avctx->width, &avctx->height, &ncolors, &cpp) != 4) {                             // (1) 0.07422
/*48  */         av_log(avctx, AV_LOG_ERROR, "missing image parameters\n");                                // (4) 0.05273
/*50  */         return AVERROR_INVALIDDATA;                                                               // (15) 0.0332
/*52  */     }                                                                                             // (24) 0.007812
/*56  */     if ((ret = ff_set_dimensions(avctx, avctx->width, avctx->height)) < 0)                        // (2) 0.05859
/*58  */         return ret;                                                                               // (19) 0.01953
/*62  */     if ((ret = ff_get_buffer(avctx, p, 0)) < 0)                                                   // (8) 0.04492
/*64  */         return ret;                                                                               // 0.0
/*68  */     if (cpp <= 0 || cpp >= 5) {                                                                   // 0.0
/*70  */         av_log(avctx, AV_LOG_ERROR, "unsupported/invalid number of chars per pixel: %d\n", cpp);  // 0.0
/*72  */         return AVERROR_INVALIDDATA;                                                               // 0.0
/*74  */     }                                                                                             // 0.0
/*78  */     size = 1;                                                                                     // 0.0
/*80  */     for (i = 0; i < cpp; i++)                                                                     // 0.0
/*82  */         size *= 94;                                                                               // 0.0
/*86  */     if (ncolors <= 0 || ncolors > size) {                                                         // 0.0
/*88  */         av_log(avctx, AV_LOG_ERROR, "invalid number of colors: %d\n", ncolors);                   // 0.0
/*90  */         return AVERROR_INVALIDDATA;                                                               // 0.0
/*92  */     }                                                                                             // 0.0
/*96  */     size *= 4;                                                                                    // 0.0
/*100 */     av_fast_padded_malloc(&x->pixels, &x->pixels_size, size);                                     // 0.0
/*102 */     if (!x->pixels)                                                                               // 0.0
/*104 */         return AVERROR(ENOMEM);                                                                   // 0.0
/*108 */     ptr += mod_strcspn(ptr, ",") + 1;                                                             // 0.0
/*110 */     for (i = 0; i < ncolors; i++) {                                                               // 0.0
/*112 */         const uint8_t *index;                                                                     // 0.0
/*114 */         int len;                                                                                  // 0.0
/*118 */         ptr += mod_strcspn(ptr, "\"") + 1;                                                        // 0.0
/*120 */         if (ptr + cpp > end)                                                                      // 0.0
/*122 */             return AVERROR_INVALIDDATA;                                                           // 0.0
/*124 */         index = ptr;                                                                              // 0.0
/*126 */         ptr += cpp;                                                                               // 0.0
/*130 */         ptr = strstr(ptr, "c ");                                                                  // 0.0
/*132 */         if (ptr) {                                                                                // 0.0
/*134 */             ptr += 2;                                                                             // 0.0
/*136 */         } else {                                                                                  // 0.0
/*138 */             return AVERROR_INVALIDDATA;                                                           // 0.0
/*140 */         }                                                                                         // 0.0
/*144 */         len = strcspn(ptr, "\" ");                                                                // 0.0
/*148 */         if ((ret = ascii2index(index, cpp)) < 0)                                                  // 0.0
/*150 */             return ret;                                                                           // 0.0
/*154 */         x->pixels[ret] = color_string_to_rgba(ptr, len);                                          // 0.0
/*156 */         ptr += mod_strcspn(ptr, ",") + 1;                                                         // 0.0
/*158 */     }                                                                                             // 0.0
/*162 */     for (i = 0; i < avctx->height; i++) {                                                         // 0.0
/*164 */         dst = (uint32_t *)(p->data[0] + i * p->linesize[0]);                                      // 0.0
/*166 */         ptr += mod_strcspn(ptr, "\"") + 1;                                                        // 0.0
/*170 */         for (j = 0; j < avctx->width; j++) {                                                      // 0.0
/*172 */             if (ptr + cpp > end)                                                                  // 0.0
/*174 */                 return AVERROR_INVALIDDATA;                                                       // 0.0
/*178 */             if ((ret = ascii2index(ptr, cpp)) < 0)                                                // 0.0
/*180 */                 return ret;                                                                       // 0.0
/*184 */             *dst++ = x->pixels[ret];                                                              // 0.0
/*186 */             ptr += cpp;                                                                           // 0.0
/*188 */         }                                                                                         // 0.0
/*190 */         ptr += mod_strcspn(ptr, ",") + 1;                                                         // 0.0
/*192 */     }                                                                                             // 0.0
/*196 */     p->key_frame = 1;                                                                             // 0.0
/*198 */     p->pict_type = AV_PICTURE_TYPE_I;                                                             // 0.0
/*202 */     *got_frame = 1;                                                                               // 0.0
/*206 */     return avpkt->size;                                                                           // 0.0
/*208 */ }                                                                                                 // 0.0
