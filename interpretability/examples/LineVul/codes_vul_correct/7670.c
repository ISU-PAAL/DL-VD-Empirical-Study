// commit message FFmpeg@221402c1c8 (target=1, prob=0.9991002, correct=True): pcx: check that the packet is large enough before reading the header
/*0   */ static int pcx_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,   // (1) 0.06461
/*1   */                             AVPacket *avpkt)                                     // (0) 0.06775
/*2   */ {                                                                                // (25) 0.00193
/*3   */     const uint8_t *buf = avpkt->data;                                            // (15) 0.03295
/*4   */     int buf_size       = avpkt->size;                                            // (11) 0.03869
/*5   */     AVFrame *const p   = data;                                                   // (17) 0.0276
/*6   */     int compressed, xmin, ymin, xmax, ymax;                                      // (13) 0.03471
/*7   */     unsigned int w, h, bits_per_pixel, bytes_per_line, nplanes, stride, y, x,    // (3) 0.05894
/*8   */                  bytes_per_scanline;                                             // (5) 0.04413
/*9   */     uint8_t *ptr;                                                                // (22) 0.01951
/*10  */     const uint8_t *buf_end = buf + buf_size;                                     // (12) 0.03648
/*11  */     const uint8_t *bufstart = buf;                                               // (18) 0.0269
/*12  */     uint8_t *scanline;                                                           // (21) 0.02111
/*13  */     int ret = -1;                                                                // (24) 0.01726
/*14  */     if (buf[0] != 0x0a || buf[1] > 5) {                                          // (6) 0.04413
/*15  */         av_log(avctx, AV_LOG_ERROR, "this is not PCX encoded data\n");           // (2) 0.05954
/*16  */     compressed = buf[2];                                                         // (23) 0.01734
/*17  */     xmin       = AV_RL16(buf + 4);                                               // (10) 0.04028
/*18  */     ymin       = AV_RL16(buf + 6);                                               // (9) 0.04028
/*19  */     xmax       = AV_RL16(buf + 8);                                               // (8) 0.04029
/*20  */     ymax       = AV_RL16(buf + 10);                                              // (7) 0.0403
/*21  */     if (xmax < xmin || ymax < ymin) {                                            // (14) 0.03453
/*22  */         av_log(avctx, AV_LOG_ERROR, "invalid image dimensions\n");               // (4) 0.05377
/*23  */     w = xmax - xmin + 1;                                                         // (20) 0.02493
/*24  */     h = ymax - ymin + 1;                                                         // (19) 0.02494
/*25  */     bits_per_pixel     = buf[3];                                                 // (16) 0.03284
/*26  */     bytes_per_line     = AV_RL16(buf + 66);                                      // 0.0
/*27  */     nplanes            = buf[65];                                                // 0.0
/*28  */     bytes_per_scanline = nplanes * bytes_per_line;                               // 0.0
/*29  */     if (bytes_per_scanline < (w * bits_per_pixel * nplanes + 7) / 8 ||           // 0.0
/*30  */         (!compressed && bytes_per_scanline > buf_size / h)) {                    // 0.0
/*31  */         av_log(avctx, AV_LOG_ERROR, "PCX data is corrupted\n");                  // 0.0
/*32  */     switch ((nplanes << 8) + bits_per_pixel) {                                   // 0.0
/*33  */     case 0x0308:                                                                 // 0.0
/*34  */         avctx->pix_fmt = AV_PIX_FMT_RGB24;                                       // 0.0
/*35  */         break;                                                                   // 0.0
/*36  */     case 0x0108:                                                                 // 0.0
/*37  */     case 0x0104:                                                                 // 0.0
/*38  */     case 0x0102:                                                                 // 0.0
/*39  */     case 0x0101:                                                                 // 0.0
/*40  */     case 0x0401:                                                                 // 0.0
/*41  */     case 0x0301:                                                                 // 0.0
/*42  */     case 0x0201:                                                                 // 0.0
/*43  */         avctx->pix_fmt = AV_PIX_FMT_PAL8;                                        // 0.0
/*44  */         break;                                                                   // 0.0
/*45  */     default:                                                                     // 0.0
/*46  */         av_log(avctx, AV_LOG_ERROR, "invalid PCX file\n");                       // 0.0
/*47  */     buf += 128;                                                                  // 0.0
/*48  */     if ((ret = ff_set_dimensions(avctx, w, h)) < 0)                              // 0.0
/*49  */         return ret;                                                              // 0.0
/*50  */     if ((ret = ff_get_buffer(avctx, p, 0)) < 0) {                                // 0.0
/*51  */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                    // 0.0
/*52  */         return ret;                                                              // 0.0
/*53  */     p->pict_type = AV_PICTURE_TYPE_I;                                            // 0.0
/*54  */     ptr    = p->data[0];                                                         // 0.0
/*55  */     stride = p->linesize[0];                                                     // 0.0
/*56  */     scanline = av_malloc(bytes_per_scanline + AV_INPUT_BUFFER_PADDING_SIZE);     // 0.0
/*57  */     if (!scanline)                                                               // 0.0
/*58  */         return AVERROR(ENOMEM);                                                  // 0.0
/*59  */     if (nplanes == 3 && bits_per_pixel == 8) {                                   // 0.0
/*60  */         for (y = 0; y < h; y++) {                                                // 0.0
/*61  */             buf = pcx_rle_decode(buf, buf_end,                                   // 0.0
/*62  */                                  scanline, bytes_per_scanline, compressed);      // 0.0
/*63  */             for (x = 0; x < w; x++) {                                            // 0.0
/*64  */                 ptr[3 * x]     = scanline[x];                                    // 0.0
/*65  */                 ptr[3 * x + 1] = scanline[x + bytes_per_line];                   // 0.0
/*66  */                 ptr[3 * x + 2] = scanline[x + (bytes_per_line << 1)];            // 0.0
/*67  */             ptr += stride;                                                       // 0.0
/*68  */     } else if (nplanes == 1 && bits_per_pixel == 8) {                            // 0.0
/*69  */         const uint8_t *palstart = bufstart + buf_size - 769;                     // 0.0
/*70  */         if (buf_size < 769) {                                                    // 0.0
/*71  */             av_log(avctx, AV_LOG_ERROR, "File is too short\n");                  // 0.0
/*72  */             ret = avctx->err_recognition & AV_EF_EXPLODE ?                       // 0.0
/*73  */                   AVERROR_INVALIDDATA : buf_size;                                // 0.0
/*74  */             goto end;                                                            // 0.0
/*75  */         for (y = 0; y < h; y++, ptr += stride) {                                 // 0.0
/*76  */             buf = pcx_rle_decode(buf, buf_end,                                   // 0.0
/*77  */                                  scanline, bytes_per_scanline, compressed);      // 0.0
/*78  */             memcpy(ptr, scanline, w);                                            // 0.0
/*79  */         if (buf != palstart) {                                                   // 0.0
/*80  */             av_log(avctx, AV_LOG_WARNING, "image data possibly corrupted\n");    // 0.0
/*81  */             buf = palstart;                                                      // 0.0
/*82  */         if (*buf++ != 12) {                                                      // 0.0
/*83  */             av_log(avctx, AV_LOG_ERROR, "expected palette after image data\n");  // 0.0
/*84  */             ret = avctx->err_recognition & AV_EF_EXPLODE ?                       // 0.0
/*85  */                   AVERROR_INVALIDDATA : buf_size;                                // 0.0
/*86  */             goto end;                                                            // 0.0
/*87  */     } else if (nplanes == 1) {   /* all packed formats, max. 16 colors */        // 0.0
/*88  */         GetBitContext s;                                                         // 0.0
/*89  */         for (y = 0; y < h; y++) {                                                // 0.0
/*90  */             init_get_bits(&s, scanline, bytes_per_scanline << 3);                // 0.0
/*91  */             buf = pcx_rle_decode(buf, buf_end,                                   // 0.0
/*92  */                                  scanline, bytes_per_scanline, compressed);      // 0.0
/*93  */             for (x = 0; x < w; x++)                                              // 0.0
/*94  */                 ptr[x] = get_bits(&s, bits_per_pixel);                           // 0.0
/*95  */             ptr += stride;                                                       // 0.0
/*96  */     } else {    /* planar, 4, 8 or 16 colors */                                  // 0.0
/*97  */         int i;                                                                   // 0.0
/*98  */         for (y = 0; y < h; y++) {                                                // 0.0
/*99  */             buf = pcx_rle_decode(buf, buf_end,                                   // 0.0
/*100 */                                  scanline, bytes_per_scanline, compressed);      // 0.0
/*101 */             for (x = 0; x < w; x++) {                                            // 0.0
/*102 */                 int m = 0x80 >> (x & 7), v = 0;                                  // 0.0
/*103 */                 for (i = nplanes - 1; i >= 0; i--) {                             // 0.0
/*104 */                     v <<= 1;                                                     // 0.0
/*105 */                     v  += !!(scanline[i * bytes_per_line + (x >> 3)] & m);       // 0.0
/*106 */                 ptr[x] = v;                                                      // 0.0
/*107 */             ptr += stride;                                                       // 0.0
/*108 */     if (nplanes == 1 && bits_per_pixel == 8) {                                   // 0.0
/*109 */         pcx_palette(&buf, (uint32_t *)p->data[1], 256);                          // 0.0
/*110 */     } else if (bits_per_pixel < 8) {                                             // 0.0
/*111 */         const uint8_t *palette = bufstart + 16;                                  // 0.0
/*112 */         pcx_palette(&palette, (uint32_t *)p->data[1], 16);                       // 0.0
/*113 */     *got_frame = 1;                                                              // 0.0
/*114 */     ret = buf - bufstart;                                                        // 0.0
/*115 */ end:                                                                             // 0.0
/*116 */     av_free(scanline);                                                           // 0.0
/*117 */     return ret;                                                                  // 0.0
