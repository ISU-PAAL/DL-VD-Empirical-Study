// commit message FFmpeg@89325417e7 (target=1, prob=0.99894434, correct=True): avcodec/jpeg2000dec: Check tile offsets
/*0   */ static int get_siz(Jpeg2000DecoderContext *s)                                                             // (15) 0.03126
/*1   */ {                                                                                                         // (19) 0.001953
/*2   */     int i;                                                                                                // (18) 0.01172
/*3   */     int ncomponents;                                                                                      // (17) 0.01563
/*4   */     uint32_t log2_chroma_wh = 0;                                                                          // (14) 0.03321
/*5   */     const enum AVPixelFormat *possible_fmts = NULL;                                                       // (13) 0.03519
/*6   */     int possible_fmts_nb = 0;                                                                             // (16) 0.02539
/*7   */     if (bytestream2_get_bytes_left(&s->g) < 36) {                                                         // (11) 0.04687
/*8   */         av_log(s->avctx, AV_LOG_ERROR, "Insufficient space for SIZ\n");                                   // (2) 0.06251
/*9   */     s->avctx->profile = bytestream2_get_be16u(&s->g); // Rsiz                                             // (10) 0.05468
/*10  */     s->width          = bytestream2_get_be32u(&s->g); // Width                                            // (1) 0.06445
/*11  */     s->height         = bytestream2_get_be32u(&s->g); // Height                                           // (5) 0.06249
/*12  */     s->image_offset_x = bytestream2_get_be32u(&s->g); // X0Siz                                            // (8) 0.06054
/*13  */     s->image_offset_y = bytestream2_get_be32u(&s->g); // Y0Siz                                            // (7) 0.06054
/*14  */     s->tile_width     = bytestream2_get_be32u(&s->g); // XTSiz                                            // (4) 0.06249
/*15  */     s->tile_height    = bytestream2_get_be32u(&s->g); // YTSiz                                            // (9) 0.06054
/*16  */     s->tile_offset_x  = bytestream2_get_be32u(&s->g); // XT0Siz                                           // (3) 0.06249
/*17  */     s->tile_offset_y  = bytestream2_get_be32u(&s->g); // YT0Siz                                           // (0) 0.06445
/*18  */     ncomponents       = bytestream2_get_be16u(&s->g); // CSiz                                             // (6) 0.06054
/*19  */     if (s->image_offset_x || s->image_offset_y) {                                                         // (12) 0.04296
/*20  */         avpriv_request_sample(s->avctx, "Support for image offsets");                                     // 0.0
/*21  */         return AVERROR_PATCHWELCOME;                                                                      // 0.0
/*22  */     if (av_image_check_size(s->width, s->height, 0, s->avctx)) {                                          // 0.0
/*23  */         avpriv_request_sample(s->avctx, "Large Dimensions");                                              // 0.0
/*24  */         return AVERROR_PATCHWELCOME;                                                                      // 0.0
/*25  */     if (ncomponents <= 0) {                                                                               // 0.0
/*26  */         av_log(s->avctx, AV_LOG_ERROR, "Invalid number of components: %d\n",                              // 0.0
/*27  */     if (ncomponents > 4) {                                                                                // 0.0
/*28  */         avpriv_request_sample(s->avctx, "Support for %d components",                                      // 0.0
/*29  */                               ncomponents);                                                               // 0.0
/*30  */         return AVERROR_PATCHWELCOME;                                                                      // 0.0
/*31  */     s->ncomponents = ncomponents;                                                                         // 0.0
/*32  */     if (s->tile_width <= 0 || s->tile_height <= 0) {                                                      // 0.0
/*33  */         av_log(s->avctx, AV_LOG_ERROR, "Invalid tile dimension %dx%d.\n",                                 // 0.0
/*34  */                s->tile_width, s->tile_height);                                                            // 0.0
/*35  */     if (bytestream2_get_bytes_left(&s->g) < 3 * s->ncomponents) {                                         // 0.0
/*36  */         av_log(s->avctx, AV_LOG_ERROR, "Insufficient space for %d components in SIZ\n", s->ncomponents);  // 0.0
/*37  */     for (i = 0; i < s->ncomponents; i++) { // Ssiz_i XRsiz_i, YRsiz_i                                     // 0.0
/*38  */         uint8_t x    = bytestream2_get_byteu(&s->g);                                                      // 0.0
/*39  */         s->cbps[i]   = (x & 0x7f) + 1;                                                                    // 0.0
/*40  */         s->precision = FFMAX(s->cbps[i], s->precision);                                                   // 0.0
/*41  */         s->sgnd[i]   = !!(x & 0x80);                                                                      // 0.0
/*42  */         s->cdx[i]    = bytestream2_get_byteu(&s->g);                                                      // 0.0
/*43  */         s->cdy[i]    = bytestream2_get_byteu(&s->g);                                                      // 0.0
/*44  */         if (   !s->cdx[i] || s->cdx[i] == 3 || s->cdx[i] > 4                                              // 0.0
/*45  */             || !s->cdy[i] || s->cdy[i] == 3 || s->cdy[i] > 4) {                                           // 0.0
/*46  */             av_log(s->avctx, AV_LOG_ERROR, "Invalid sample separation %d/%d\n", s->cdx[i], s->cdy[i]);    // 0.0
/*47  */         log2_chroma_wh |= s->cdy[i] >> 1 << i * 4 | s->cdx[i] >> 1 << i * 4 + 2;                          // 0.0
/*48  */     s->numXtiles = ff_jpeg2000_ceildiv(s->width  - s->tile_offset_x, s->tile_width);                      // 0.0
/*49  */     s->numYtiles = ff_jpeg2000_ceildiv(s->height - s->tile_offset_y, s->tile_height);                     // 0.0
/*50  */     if (s->numXtiles * (uint64_t)s->numYtiles > INT_MAX/sizeof(*s->tile)) {                               // 0.0
/*51  */         s->numXtiles = s->numYtiles = 0;                                                                  // 0.0
/*52  */         return AVERROR(EINVAL);                                                                           // 0.0
/*53  */     s->tile = av_mallocz_array(s->numXtiles * s->numYtiles, sizeof(*s->tile));                            // 0.0
/*54  */     if (!s->tile) {                                                                                       // 0.0
/*55  */         s->numXtiles = s->numYtiles = 0;                                                                  // 0.0
/*56  */         return AVERROR(ENOMEM);                                                                           // 0.0
/*57  */     for (i = 0; i < s->numXtiles * s->numYtiles; i++) {                                                   // 0.0
/*58  */         Jpeg2000Tile *tile = s->tile + i;                                                                 // 0.0
/*59  */         tile->comp = av_mallocz(s->ncomponents * sizeof(*tile->comp));                                    // 0.0
/*60  */         if (!tile->comp)                                                                                  // 0.0
/*61  */             return AVERROR(ENOMEM);                                                                       // 0.0
/*62  */     /* compute image size with reduction factor */                                                        // 0.0
/*63  */     s->avctx->width  = ff_jpeg2000_ceildivpow2(s->width  - s->image_offset_x,                             // 0.0
/*64  */                                                s->reduction_factor);                                      // 0.0
/*65  */     s->avctx->height = ff_jpeg2000_ceildivpow2(s->height - s->image_offset_y,                             // 0.0
/*66  */                                                s->reduction_factor);                                      // 0.0
/*67  */     if (s->avctx->profile == FF_PROFILE_JPEG2000_DCINEMA_2K ||                                            // 0.0
/*68  */         s->avctx->profile == FF_PROFILE_JPEG2000_DCINEMA_4K) {                                            // 0.0
/*69  */         possible_fmts = xyz_pix_fmts;                                                                     // 0.0
/*70  */         possible_fmts_nb = FF_ARRAY_ELEMS(xyz_pix_fmts);                                                  // 0.0
/*71  */     } else {                                                                                              // 0.0
/*72  */         switch (s->colour_space) {                                                                        // 0.0
/*73  */         case 16:                                                                                          // 0.0
/*74  */             possible_fmts = rgb_pix_fmts;                                                                 // 0.0
/*75  */             possible_fmts_nb = FF_ARRAY_ELEMS(rgb_pix_fmts);                                              // 0.0
/*76  */             break;                                                                                        // 0.0
/*77  */         case 17:                                                                                          // 0.0
/*78  */             possible_fmts = gray_pix_fmts;                                                                // 0.0
/*79  */             possible_fmts_nb = FF_ARRAY_ELEMS(gray_pix_fmts);                                             // 0.0
/*80  */             break;                                                                                        // 0.0
/*81  */         case 18:                                                                                          // 0.0
/*82  */             possible_fmts = yuv_pix_fmts;                                                                 // 0.0
/*83  */             possible_fmts_nb = FF_ARRAY_ELEMS(yuv_pix_fmts);                                              // 0.0
/*84  */             break;                                                                                        // 0.0
/*85  */         default:                                                                                          // 0.0
/*86  */             possible_fmts = all_pix_fmts;                                                                 // 0.0
/*87  */             possible_fmts_nb = FF_ARRAY_ELEMS(all_pix_fmts);                                              // 0.0
/*88  */             break;                                                                                        // 0.0
/*89  */     for (i = 0; i < possible_fmts_nb; ++i) {                                                              // 0.0
/*90  */         if (pix_fmt_match(possible_fmts[i], ncomponents, s->precision, log2_chroma_wh, s->pal8)) {        // 0.0
/*91  */             s->avctx->pix_fmt = possible_fmts[i];                                                         // 0.0
/*92  */             break;                                                                                        // 0.0
/*93  */     if (i == possible_fmts_nb) {                                                                          // 0.0
/*94  */         if (ncomponents == 4 &&                                                                           // 0.0
/*95  */             s->cdy[0] == 1 && s->cdx[0] == 1 &&                                                           // 0.0
/*96  */             s->cdy[1] == 1 && s->cdx[1] == 1 &&                                                           // 0.0
/*97  */             s->cdy[2] == s->cdy[3] && s->cdx[2] == s->cdx[3]) {                                           // 0.0
/*98  */             if (s->precision == 8 && s->cdy[2] == 2 && s->cdx[2] == 2 && !s->pal8) {                      // 0.0
/*99  */                 s->avctx->pix_fmt = AV_PIX_FMT_YUVA420P;                                                  // 0.0
/*100 */                 s->cdef[0] = 0;                                                                           // 0.0
/*101 */                 s->cdef[1] = 1;                                                                           // 0.0
/*102 */                 s->cdef[2] = 2;                                                                           // 0.0
/*103 */                 s->cdef[3] = 3;                                                                           // 0.0
/*104 */                 i = 0;                                                                                    // 0.0
/*105 */     if (i == possible_fmts_nb) {                                                                          // 0.0
/*106 */         av_log(s->avctx, AV_LOG_ERROR,                                                                    // 0.0
/*107 */                "Unknown pix_fmt, profile: %d, colour_space: %d, "                                         // 0.0
/*108 */                "components: %d, precision: %d\n"                                                          // 0.0
/*109 */                "cdx[0]: %d, cdy[0]: %d\n"                                                                 // 0.0
/*110 */                "cdx[1]: %d, cdy[1]: %d\n"                                                                 // 0.0
/*111 */                "cdx[2]: %d, cdy[2]: %d\n"                                                                 // 0.0
/*112 */                "cdx[3]: %d, cdy[3]: %d\n",                                                                // 0.0
/*113 */                s->avctx->profile, s->colour_space, ncomponents, s->precision,                             // 0.0
/*114 */                s->cdx[0],                                                                                 // 0.0
/*115 */                s->cdy[0],                                                                                 // 0.0
/*116 */                ncomponents > 1 ? s->cdx[1] : 0,                                                           // 0.0
/*117 */                ncomponents > 1 ? s->cdy[1] : 0,                                                           // 0.0
/*118 */                ncomponents > 2 ? s->cdx[2] : 0,                                                           // 0.0
/*119 */                ncomponents > 2 ? s->cdy[2] : 0,                                                           // 0.0
/*120 */                ncomponents > 3 ? s->cdx[3] : 0,                                                           // 0.0
/*121 */                ncomponents > 3 ? s->cdy[3] : 0);                                                          // 0.0
/*122 */         return AVERROR_PATCHWELCOME;                                                                      // 0.0
/*123 */     s->avctx->bits_per_raw_sample = s->precision;                                                         // 0.0
/*124 */     return 0;                                                                                             // 0.0
