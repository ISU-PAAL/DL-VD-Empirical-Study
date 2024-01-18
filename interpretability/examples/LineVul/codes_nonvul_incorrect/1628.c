// commit message FFmpeg@89f464e9c2 (target=0, prob=0.6593491, correct=False): avcodec/tiff: Check subsample & rps values more completely
/*0   */ static int decode_frame(AVCodecContext *avctx,                                                            // (14) 0.02745
/*2   */                         void *data, int *got_frame, AVPacket *avpkt)                                      // (0) 0.07999
/*4   */ {                                                                                                         // (29) 0.001954
/*6   */     TiffContext *const s = avctx->priv_data;                                                              // (13) 0.03123
/*8   */     AVFrame *const p = data;                                                                              // (21) 0.02146
/*10  */     ThreadFrame frame = { .f = data };                                                                    // (15) 0.02538
/*12  */     unsigned off;                                                                                         // (27) 0.0117
/*14  */     int le, ret, plane, planes;                                                                           // (16) 0.0237
/*16  */     int i, j, entries, stride;                                                                            // (17) 0.02341
/*18  */     unsigned soff, ssize;                                                                                 // (22) 0.01951
/*20  */     uint8_t *dst;                                                                                         // (20) 0.02147
/*22  */     GetByteContext stripsizes;                                                                            // (25) 0.01757
/*24  */     GetByteContext stripdata;                                                                             // (24) 0.01757
/*28  */     bytestream2_init(&s->gb, avpkt->data, avpkt->size);                                                   // (4) 0.05081
/*32  */     // parse image header                                                                                 // (26) 0.01368
/*34  */     if ((ret = ff_tdecode_header(&s->gb, &le, &off))) {                                                   // (5) 0.05073
/*36  */         av_log(avctx, AV_LOG_ERROR, "Invalid TIFF header\n");                                             // (2) 0.05462
/*38  */         return ret;                                                                                       // (23) 0.01951
/*40  */     } else if (off >= UINT_MAX - 14 || avpkt->size < off + 14) {                                          // (3) 0.05267
/*42  */         av_log(avctx, AV_LOG_ERROR, "IFD offset is greater than image size\n");                           // (1) 0.06242
/*44  */         return AVERROR_INVALIDDATA;                                                                       // (12) 0.03316
/*46  */     }                                                                                                     // (28) 0.007803
/*48  */     s->le          = le;                                                                                  // (10) 0.03511
/*50  */     // TIFF_BPP is not a required tag and defaults to 1                                                   // (9) 0.03514
/*52  */     s->bppcount    = s->bpp = 1;                                                                          // (8) 0.03706
/*54  */     s->photometric = TIFF_PHOTOMETRIC_NONE;                                                               // (6) 0.03907
/*56  */     s->compr       = TIFF_RAW;                                                                            // (7) 0.03708
/*58  */     s->fill_order  = 0;                                                                                   // (18) 0.02341
/*60  */     free_geotags(s);                                                                                      // (19) 0.02155
/*64  */     // Reset these offsets so we can tell if they were set this frame                                     // (11) 0.03342
/*66  */     s->stripsizesoff = s->strippos = 0;                                                                   // 0.0
/*68  */     /* parse image file directory */                                                                      // 0.0
/*70  */     bytestream2_seek(&s->gb, off, SEEK_SET);                                                              // 0.0
/*72  */     entries = ff_tget_short(&s->gb, le);                                                                  // 0.0
/*74  */     if (bytestream2_get_bytes_left(&s->gb) < entries * 12)                                                // 0.0
/*76  */         return AVERROR_INVALIDDATA;                                                                       // 0.0
/*78  */     for (i = 0; i < entries; i++) {                                                                       // 0.0
/*80  */         if ((ret = tiff_decode_tag(s, p)) < 0)                                                            // 0.0
/*82  */             return ret;                                                                                   // 0.0
/*84  */     }                                                                                                     // 0.0
/*88  */     for (i = 0; i<s->geotag_count; i++) {                                                                 // 0.0
/*90  */         const char *keyname = get_geokey_name(s->geotags[i].key);                                         // 0.0
/*92  */         if (!keyname) {                                                                                   // 0.0
/*94  */             av_log(avctx, AV_LOG_WARNING, "Unknown or unsupported GeoTIFF key %d\n", s->geotags[i].key);  // 0.0
/*96  */             continue;                                                                                     // 0.0
/*98  */         }                                                                                                 // 0.0
/*100 */         if (get_geokey_type(s->geotags[i].key) != s->geotags[i].type) {                                   // 0.0
/*102 */             av_log(avctx, AV_LOG_WARNING, "Type of GeoTIFF key %d is wrong\n", s->geotags[i].key);        // 0.0
/*104 */             continue;                                                                                     // 0.0
/*106 */         }                                                                                                 // 0.0
/*108 */         ret = av_dict_set(avpriv_frame_get_metadatap(p), keyname, s->geotags[i].val, 0);                  // 0.0
/*110 */         if (ret<0) {                                                                                      // 0.0
/*112 */             av_log(avctx, AV_LOG_ERROR, "Writing metadata with key '%s' failed\n", keyname);              // 0.0
/*114 */             return ret;                                                                                   // 0.0
/*116 */         }                                                                                                 // 0.0
/*118 */     }                                                                                                     // 0.0
/*122 */     if (!s->strippos && !s->stripoff) {                                                                   // 0.0
/*124 */         av_log(avctx, AV_LOG_ERROR, "Image data is missing\n");                                           // 0.0
/*126 */         return AVERROR_INVALIDDATA;                                                                       // 0.0
/*128 */     }                                                                                                     // 0.0
/*130 */     /* now we have the data and may start decoding */                                                     // 0.0
/*132 */     if ((ret = init_image(s, &frame)) < 0)                                                                // 0.0
/*134 */         return ret;                                                                                       // 0.0
/*138 */     if (s->strips == 1 && !s->stripsize) {                                                                // 0.0
/*140 */         av_log(avctx, AV_LOG_WARNING, "Image data size missing\n");                                       // 0.0
/*142 */         s->stripsize = avpkt->size - s->stripoff;                                                         // 0.0
/*144 */     }                                                                                                     // 0.0
/*148 */     if (s->stripsizesoff) {                                                                               // 0.0
/*150 */         if (s->stripsizesoff >= (unsigned)avpkt->size)                                                    // 0.0
/*152 */             return AVERROR_INVALIDDATA;                                                                   // 0.0
/*154 */         bytestream2_init(&stripsizes, avpkt->data + s->stripsizesoff,                                     // 0.0
/*156 */                          avpkt->size - s->stripsizesoff);                                                 // 0.0
/*158 */     }                                                                                                     // 0.0
/*160 */     if (s->strippos) {                                                                                    // 0.0
/*162 */         if (s->strippos >= (unsigned)avpkt->size)                                                         // 0.0
/*164 */             return AVERROR_INVALIDDATA;                                                                   // 0.0
/*166 */         bytestream2_init(&stripdata, avpkt->data + s->strippos,                                           // 0.0
/*168 */                          avpkt->size - s->strippos);                                                      // 0.0
/*170 */     }                                                                                                     // 0.0
/*174 */     if (s->rps <= 0) {                                                                                    // 0.0
/*176 */         av_log(avctx, AV_LOG_ERROR, "rps %d invalid\n", s->rps);                                          // 0.0
/*178 */         return AVERROR_INVALIDDATA;                                                                       // 0.0
/*180 */     }                                                                                                     // 0.0
/*184 */     planes = s->planar ? s->bppcount : 1;                                                                 // 0.0
/*186 */     for (plane = 0; plane < planes; plane++) {                                                            // 0.0
/*188 */         stride = p->linesize[plane];                                                                      // 0.0
/*190 */         dst = p->data[plane];                                                                             // 0.0
/*192 */         for (i = 0; i < s->height; i += s->rps) {                                                         // 0.0
/*194 */             if (s->stripsizesoff)                                                                         // 0.0
/*196 */                 ssize = ff_tget(&stripsizes, s->sstype, le);                                              // 0.0
/*198 */             else                                                                                          // 0.0
/*200 */                 ssize = s->stripsize;                                                                     // 0.0
/*204 */             if (s->strippos)                                                                              // 0.0
/*206 */                 soff = ff_tget(&stripdata, s->sot, le);                                                   // 0.0
/*208 */             else                                                                                          // 0.0
/*210 */                 soff = s->stripoff;                                                                       // 0.0
/*214 */             if (soff > avpkt->size || ssize > avpkt->size - soff) {                                       // 0.0
/*216 */                 av_log(avctx, AV_LOG_ERROR, "Invalid strip size/offset\n");                               // 0.0
/*218 */                 return AVERROR_INVALIDDATA;                                                               // 0.0
/*220 */             }                                                                                             // 0.0
/*222 */             if ((ret = tiff_unpack_strip(s, p, dst, stride, avpkt->data + soff, ssize, i,                 // 0.0
/*224 */                                          FFMIN(s->rps, s->height - i))) < 0) {                            // 0.0
/*226 */                 if (avctx->err_recognition & AV_EF_EXPLODE)                                               // 0.0
/*228 */                     return ret;                                                                           // 0.0
/*230 */                 break;                                                                                    // 0.0
/*232 */             }                                                                                             // 0.0
/*234 */             dst += s->rps * stride;                                                                       // 0.0
/*236 */         }                                                                                                 // 0.0
/*238 */         if (s->predictor == 2) {                                                                          // 0.0
/*240 */             if (s->photometric == TIFF_PHOTOMETRIC_YCBCR) {                                               // 0.0
/*242 */                 av_log(s->avctx, AV_LOG_ERROR, "predictor == 2 with YUV is unsupported");                 // 0.0
/*244 */                 return AVERROR_PATCHWELCOME;                                                              // 0.0
/*246 */             }                                                                                             // 0.0
/*248 */             dst   = p->data[plane];                                                                       // 0.0
/*250 */             soff  = s->bpp >> 3;                                                                          // 0.0
/*252 */             if (s->planar)                                                                                // 0.0
/*254 */                 soff  = FFMAX(soff / s->bppcount, 1);                                                     // 0.0
/*256 */             ssize = s->width * soff;                                                                      // 0.0
/*258 */             if (s->avctx->pix_fmt == AV_PIX_FMT_RGB48LE ||                                                // 0.0
/*260 */                 s->avctx->pix_fmt == AV_PIX_FMT_RGBA64LE ||                                               // 0.0
/*262 */                 s->avctx->pix_fmt == AV_PIX_FMT_GRAY16LE ||                                               // 0.0
/*264 */                 s->avctx->pix_fmt == AV_PIX_FMT_YA16LE ||                                                 // 0.0
/*266 */                 s->avctx->pix_fmt == AV_PIX_FMT_GBRP16LE ||                                               // 0.0
/*268 */                 s->avctx->pix_fmt == AV_PIX_FMT_GBRAP16LE) {                                              // 0.0
/*270 */                 for (i = 0; i < s->height; i++) {                                                         // 0.0
/*272 */                     for (j = soff; j < ssize; j += 2)                                                     // 0.0
/*274 */                         AV_WL16(dst + j, AV_RL16(dst + j) + AV_RL16(dst + j - soff));                     // 0.0
/*276 */                     dst += stride;                                                                        // 0.0
/*278 */                 }                                                                                         // 0.0
/*280 */             } else if (s->avctx->pix_fmt == AV_PIX_FMT_RGB48BE ||                                         // 0.0
/*282 */                        s->avctx->pix_fmt == AV_PIX_FMT_RGBA64BE ||                                        // 0.0
/*284 */                        s->avctx->pix_fmt == AV_PIX_FMT_GRAY16BE ||                                        // 0.0
/*286 */                        s->avctx->pix_fmt == AV_PIX_FMT_YA16BE ||                                          // 0.0
/*288 */                        s->avctx->pix_fmt == AV_PIX_FMT_GBRP16BE ||                                        // 0.0
/*290 */                        s->avctx->pix_fmt == AV_PIX_FMT_GBRAP16BE) {                                       // 0.0
/*292 */                 for (i = 0; i < s->height; i++) {                                                         // 0.0
/*294 */                     for (j = soff; j < ssize; j += 2)                                                     // 0.0
/*296 */                         AV_WB16(dst + j, AV_RB16(dst + j) + AV_RB16(dst + j - soff));                     // 0.0
/*298 */                     dst += stride;                                                                        // 0.0
/*300 */                 }                                                                                         // 0.0
/*302 */             } else {                                                                                      // 0.0
/*304 */                 for (i = 0; i < s->height; i++) {                                                         // 0.0
/*306 */                     for (j = soff; j < ssize; j++)                                                        // 0.0
/*308 */                         dst[j] += dst[j - soff];                                                          // 0.0
/*310 */                     dst += stride;                                                                        // 0.0
/*312 */                 }                                                                                         // 0.0
/*314 */             }                                                                                             // 0.0
/*316 */         }                                                                                                 // 0.0
/*320 */         if (s->photometric == TIFF_PHOTOMETRIC_WHITE_IS_ZERO) {                                           // 0.0
/*322 */             dst = p->data[plane];                                                                         // 0.0
/*324 */             for (i = 0; i < s->height; i++) {                                                             // 0.0
/*326 */                 for (j = 0; j < stride; j++)                                                              // 0.0
/*328 */                     dst[j] = (s->avctx->pix_fmt == AV_PIX_FMT_PAL8 ? (1<<s->bpp) - 1 : 255) - dst[j];     // 0.0
/*330 */                 dst += stride;                                                                            // 0.0
/*332 */             }                                                                                             // 0.0
/*334 */         }                                                                                                 // 0.0
/*336 */     }                                                                                                     // 0.0
/*340 */     if (s->planar && s->bppcount > 2) {                                                                   // 0.0
/*342 */         FFSWAP(uint8_t*, p->data[0],     p->data[2]);                                                     // 0.0
/*344 */         FFSWAP(int,      p->linesize[0], p->linesize[2]);                                                 // 0.0
/*346 */         FFSWAP(uint8_t*, p->data[0],     p->data[1]);                                                     // 0.0
/*348 */         FFSWAP(int,      p->linesize[0], p->linesize[1]);                                                 // 0.0
/*350 */     }                                                                                                     // 0.0
/*354 */     *got_frame = 1;                                                                                       // 0.0
/*358 */     return avpkt->size;                                                                                   // 0.0
/*360 */ }                                                                                                         // 0.0
