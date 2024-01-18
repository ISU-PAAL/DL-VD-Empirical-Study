// commit message FFmpeg@8c5cd1c9d3 (target=1, prob=0.6869444, correct=True): avcodec/webp: Fix signedness in prefix_code check
/*0   */ static int decode_entropy_coded_image(WebPContext *s, enum ImageRole role,     // (7) 0.04297
/*2   */                                       int w, int h)                            // (0) 0.08398
/*4   */ {                                                                              // (26) 0.001953
/*6   */     ImageContext *img;                                                         // (23) 0.01563
/*8   */     HuffReader *hg;                                                            // (20) 0.01758
/*10  */     int i, j, ret, x, y, width;                                                // (13) 0.03125
/*14  */     img       = &s->image[role];                                               // (11) 0.03516
/*16  */     img->role = role;                                                          // (21) 0.01758
/*20  */     if (!img->frame) {                                                         // (18) 0.01953
/*22  */         img->frame = av_frame_alloc();                                         // (12) 0.0332
/*24  */         if (!img->frame)                                                       // (15) 0.02539
/*26  */             return AVERROR(ENOMEM);                                            // (9) 0.03906
/*28  */     }                                                                          // (25) 0.007812
/*32  */     img->frame->format = AV_PIX_FMT_ARGB;                                      // (8) 0.03906
/*34  */     img->frame->width  = w;                                                    // (16) 0.02344
/*36  */     img->frame->height = h;                                                    // (17) 0.02148
/*40  */     if (role == IMAGE_ROLE_ARGB && !img->is_alpha_primary) {                   // (4) 0.05078
/*42  */         ThreadFrame pt = { .f = img->frame };                                  // (10) 0.03711
/*44  */         ret = ff_thread_get_buffer(s->avctx, &pt, 0);                          // (3) 0.05273
/*46  */     } else                                                                     // (24) 0.009766
/*48  */         ret = av_frame_get_buffer(img->frame, 1);                              // (6) 0.04492
/*50  */     if (ret < 0)                                                               // (22) 0.01758
/*52  */         return ret;                                                            // (19) 0.01953
/*56  */     if (get_bits1(&s->gb)) {                                                   // (14) 0.0293
/*58  */         img->color_cache_bits = get_bits(&s->gb, 4);                           // (5) 0.04883
/*60  */         if (img->color_cache_bits < 1 || img->color_cache_bits > 11) {         // (2) 0.05859
/*62  */             av_log(s->avctx, AV_LOG_ERROR, "invalid color cache bits: %d\n",   // (1) 0.07422
/*64  */                    img->color_cache_bits);                                     // 0.0
/*66  */             return AVERROR_INVALIDDATA;                                        // 0.0
/*68  */         }                                                                      // 0.0
/*70  */         img->color_cache = av_mallocz_array(1 << img->color_cache_bits,        // 0.0
/*72  */                                             sizeof(*img->color_cache));        // 0.0
/*74  */         if (!img->color_cache)                                                 // 0.0
/*76  */             return AVERROR(ENOMEM);                                            // 0.0
/*78  */     } else {                                                                   // 0.0
/*80  */         img->color_cache_bits = 0;                                             // 0.0
/*82  */     }                                                                          // 0.0
/*86  */     img->nb_huffman_groups = 1;                                                // 0.0
/*88  */     if (role == IMAGE_ROLE_ARGB && get_bits1(&s->gb)) {                        // 0.0
/*90  */         ret = decode_entropy_image(s);                                         // 0.0
/*92  */         if (ret < 0)                                                           // 0.0
/*94  */             return ret;                                                        // 0.0
/*96  */         img->nb_huffman_groups = s->nb_huffman_groups;                         // 0.0
/*98  */     }                                                                          // 0.0
/*100 */     img->huffman_groups = av_mallocz_array(img->nb_huffman_groups *            // 0.0
/*102 */                                            HUFFMAN_CODES_PER_META_CODE,        // 0.0
/*104 */                                            sizeof(*img->huffman_groups));      // 0.0
/*106 */     if (!img->huffman_groups)                                                  // 0.0
/*108 */         return AVERROR(ENOMEM);                                                // 0.0
/*112 */     for (i = 0; i < img->nb_huffman_groups; i++) {                             // 0.0
/*114 */         hg = &img->huffman_groups[i * HUFFMAN_CODES_PER_META_CODE];            // 0.0
/*116 */         for (j = 0; j < HUFFMAN_CODES_PER_META_CODE; j++) {                    // 0.0
/*118 */             int alphabet_size = alphabet_sizes[j];                             // 0.0
/*120 */             if (!j && img->color_cache_bits > 0)                               // 0.0
/*122 */                 alphabet_size += 1 << img->color_cache_bits;                   // 0.0
/*126 */             if (get_bits1(&s->gb)) {                                           // 0.0
/*128 */                 read_huffman_code_simple(s, &hg[j]);                           // 0.0
/*130 */             } else {                                                           // 0.0
/*132 */                 ret = read_huffman_code_normal(s, &hg[j], alphabet_size);      // 0.0
/*134 */                 if (ret < 0)                                                   // 0.0
/*136 */                     return ret;                                                // 0.0
/*138 */             }                                                                  // 0.0
/*140 */         }                                                                      // 0.0
/*142 */     }                                                                          // 0.0
/*146 */     width = img->frame->width;                                                 // 0.0
/*148 */     if (role == IMAGE_ROLE_ARGB && s->reduced_width > 0)                       // 0.0
/*150 */         width = s->reduced_width;                                              // 0.0
/*154 */     x = 0; y = 0;                                                              // 0.0
/*156 */     while (y < img->frame->height) {                                           // 0.0
/*158 */         int v;                                                                 // 0.0
/*162 */         hg = get_huffman_group(s, img, x, y);                                  // 0.0
/*164 */         v = huff_reader_get_symbol(&hg[HUFF_IDX_GREEN], &s->gb);               // 0.0
/*166 */         if (v < NUM_LITERAL_CODES) {                                           // 0.0
/*168 */             /* literal pixel values */                                         // 0.0
/*170 */             uint8_t *p = GET_PIXEL(img->frame, x, y);                          // 0.0
/*172 */             p[2] = v;                                                          // 0.0
/*174 */             p[1] = huff_reader_get_symbol(&hg[HUFF_IDX_RED],   &s->gb);        // 0.0
/*176 */             p[3] = huff_reader_get_symbol(&hg[HUFF_IDX_BLUE],  &s->gb);        // 0.0
/*178 */             p[0] = huff_reader_get_symbol(&hg[HUFF_IDX_ALPHA], &s->gb);        // 0.0
/*180 */             if (img->color_cache_bits)                                         // 0.0
/*182 */                 color_cache_put(img, AV_RB32(p));                              // 0.0
/*184 */             x++;                                                               // 0.0
/*186 */             if (x == width) {                                                  // 0.0
/*188 */                 x = 0;                                                         // 0.0
/*190 */                 y++;                                                           // 0.0
/*192 */             }                                                                  // 0.0
/*194 */         } else if (v < NUM_LITERAL_CODES + NUM_LENGTH_CODES) {                 // 0.0
/*196 */             /* LZ77 backwards mapping */                                       // 0.0
/*198 */             int prefix_code, length, distance, ref_x, ref_y;                   // 0.0
/*202 */             /* parse length and distance */                                    // 0.0
/*204 */             prefix_code = v - NUM_LITERAL_CODES;                               // 0.0
/*206 */             if (prefix_code < 4) {                                             // 0.0
/*208 */                 length = prefix_code + 1;                                      // 0.0
/*210 */             } else {                                                           // 0.0
/*212 */                 int extra_bits = (prefix_code - 2) >> 1;                       // 0.0
/*214 */                 int offset     = 2 + (prefix_code & 1) << extra_bits;          // 0.0
/*216 */                 length = offset + get_bits(&s->gb, extra_bits) + 1;            // 0.0
/*218 */             }                                                                  // 0.0
/*220 */             prefix_code = huff_reader_get_symbol(&hg[HUFF_IDX_DIST], &s->gb);  // 0.0
/*222 */             if (prefix_code > 39) {                                            // 0.0
/*224 */                 av_log(s->avctx, AV_LOG_ERROR,                                 // 0.0
/*226 */                        "distance prefix code too large: %d\n", prefix_code);   // 0.0
/*228 */                 return AVERROR_INVALIDDATA;                                    // 0.0
/*230 */             }                                                                  // 0.0
/*232 */             if (prefix_code < 4) {                                             // 0.0
/*234 */                 distance = prefix_code + 1;                                    // 0.0
/*236 */             } else {                                                           // 0.0
/*238 */                 int extra_bits = prefix_code - 2 >> 1;                         // 0.0
/*240 */                 int offset     = 2 + (prefix_code & 1) << extra_bits;          // 0.0
/*242 */                 distance = offset + get_bits(&s->gb, extra_bits) + 1;          // 0.0
/*244 */             }                                                                  // 0.0
/*248 */             /* find reference location */                                      // 0.0
/*250 */             if (distance <= NUM_SHORT_DISTANCES) {                             // 0.0
/*252 */                 int xi = lz77_distance_offsets[distance - 1][0];               // 0.0
/*254 */                 int yi = lz77_distance_offsets[distance - 1][1];               // 0.0
/*256 */                 distance = FFMAX(1, xi + yi * width);                          // 0.0
/*258 */             } else {                                                           // 0.0
/*260 */                 distance -= NUM_SHORT_DISTANCES;                               // 0.0
/*262 */             }                                                                  // 0.0
/*264 */             ref_x = x;                                                         // 0.0
/*266 */             ref_y = y;                                                         // 0.0
/*268 */             if (distance <= x) {                                               // 0.0
/*270 */                 ref_x -= distance;                                             // 0.0
/*272 */                 distance = 0;                                                  // 0.0
/*274 */             } else {                                                           // 0.0
/*276 */                 ref_x = 0;                                                     // 0.0
/*278 */                 distance -= x;                                                 // 0.0
/*280 */             }                                                                  // 0.0
/*282 */             while (distance >= width) {                                        // 0.0
/*284 */                 ref_y--;                                                       // 0.0
/*286 */                 distance -= width;                                             // 0.0
/*288 */             }                                                                  // 0.0
/*290 */             if (distance > 0) {                                                // 0.0
/*292 */                 ref_x = width - distance;                                      // 0.0
/*294 */                 ref_y--;                                                       // 0.0
/*296 */             }                                                                  // 0.0
/*298 */             ref_x = FFMAX(0, ref_x);                                           // 0.0
/*300 */             ref_y = FFMAX(0, ref_y);                                           // 0.0
/*304 */             /* copy pixels                                                     // 0.0
/*306 */              * source and dest regions can overlap and wrap lines, so just     // 0.0
/*308 */              * copy per-pixel */                                               // 0.0
/*310 */             for (i = 0; i < length; i++) {                                     // 0.0
/*312 */                 uint8_t *p_ref = GET_PIXEL(img->frame, ref_x, ref_y);          // 0.0
/*314 */                 uint8_t *p     = GET_PIXEL(img->frame,     x,     y);          // 0.0
/*318 */                 AV_COPY32(p, p_ref);                                           // 0.0
/*320 */                 if (img->color_cache_bits)                                     // 0.0
/*322 */                     color_cache_put(img, AV_RB32(p));                          // 0.0
/*324 */                 x++;                                                           // 0.0
/*326 */                 ref_x++;                                                       // 0.0
/*328 */                 if (x == width) {                                              // 0.0
/*330 */                     x = 0;                                                     // 0.0
/*332 */                     y++;                                                       // 0.0
/*334 */                 }                                                              // 0.0
/*336 */                 if (ref_x == width) {                                          // 0.0
/*338 */                     ref_x = 0;                                                 // 0.0
/*340 */                     ref_y++;                                                   // 0.0
/*342 */                 }                                                              // 0.0
/*344 */                 if (y == img->frame->height || ref_y == img->frame->height)    // 0.0
/*346 */                     break;                                                     // 0.0
/*348 */             }                                                                  // 0.0
/*350 */         } else {                                                               // 0.0
/*352 */             /* read from color cache */                                        // 0.0
/*354 */             uint8_t *p = GET_PIXEL(img->frame, x, y);                          // 0.0
/*356 */             int cache_idx = v - (NUM_LITERAL_CODES + NUM_LENGTH_CODES);        // 0.0
/*360 */             if (!img->color_cache_bits) {                                      // 0.0
/*362 */                 av_log(s->avctx, AV_LOG_ERROR, "color cache not found\n");     // 0.0
/*364 */                 return AVERROR_INVALIDDATA;                                    // 0.0
/*366 */             }                                                                  // 0.0
/*368 */             if (cache_idx >= 1 << img->color_cache_bits) {                     // 0.0
/*370 */                 av_log(s->avctx, AV_LOG_ERROR,                                 // 0.0
/*372 */                        "color cache index out-of-bounds\n");                   // 0.0
/*374 */                 return AVERROR_INVALIDDATA;                                    // 0.0
/*376 */             }                                                                  // 0.0
/*378 */             AV_WB32(p, img->color_cache[cache_idx]);                           // 0.0
/*380 */             x++;                                                               // 0.0
/*382 */             if (x == width) {                                                  // 0.0
/*384 */                 x = 0;                                                         // 0.0
/*386 */                 y++;                                                           // 0.0
/*388 */             }                                                                  // 0.0
/*390 */         }                                                                      // 0.0
/*392 */     }                                                                          // 0.0
/*396 */     return 0;                                                                  // 0.0
/*398 */ }                                                                              // 0.0
