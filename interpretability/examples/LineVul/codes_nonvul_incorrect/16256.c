// commit message FFmpeg@6221e2478c (target=0, prob=0.58715636, correct=False): parseutils: fix parsing of invalid alpha values
/*0   */ int av_parse_color(uint8_t *rgba_color, const char *color_string, int slen,                             // (3) 0.05469
/*2   */                    void *log_ctx)                                                                       // (4) 0.04687
/*4   */ {                                                                                                       // (25) 0.001953
/*6   */     char *tail, color_string2[128];                                                                     // (15) 0.02734
/*8   */     const ColorEntry *entry;                                                                            // (24) 0.01758
/*10  */     int len, hex_offset = 0;                                                                            // (21) 0.02344
/*14  */     if (color_string[0] == '#') {                                                                       // (14) 0.03125
/*16  */         hex_offset = 1;                                                                                 // (17) 0.02539
/*18  */     } else if (!strncmp(color_string, "0x", 2))                                                         // (7) 0.04102
/*20  */         hex_offset = 2;                                                                                 // (20) 0.02539
/*24  */     if (slen < 0)                                                                                       // (23) 0.01953
/*26  */         slen = strlen(color_string);                                                                    // (13) 0.0332
/*28  */     av_strlcpy(color_string2, color_string + hex_offset,                                                // (5) 0.04297
/*30  */                FFMIN(slen-hex_offset+1, sizeof(color_string2)));                                        // (2) 0.06641
/*32  */     if ((tail = strchr(color_string2, ALPHA_SEP)))                                                      // (6) 0.04297
/*34  */         *tail++ = 0;                                                                                    // (16) 0.02539
/*36  */     len = strlen(color_string2);                                                                        // (18) 0.02539
/*38  */     rgba_color[3] = 255;                                                                                // (19) 0.02539
/*42  */     if (!av_strcasecmp(color_string2, "random") || !av_strcasecmp(color_string2, "bikeshed")) {         // (1) 0.07422
/*44  */         int rgba = av_get_random_seed();                                                                // (11) 0.03711
/*46  */         rgba_color[0] = rgba >> 24;                                                                     // (9) 0.03906
/*48  */         rgba_color[1] = rgba >> 16;                                                                     // (10) 0.03906
/*50  */         rgba_color[2] = rgba >> 8;                                                                      // (8) 0.03906
/*52  */         rgba_color[3] = rgba;                                                                           // (12) 0.03516
/*54  */     } else if (hex_offset ||                                                                            // (22) 0.02148
/*56  */                strspn(color_string2, "0123456789ABCDEFabcdef") == len) {                                // (0) 0.07422
/*58  */         char *tail;                                                                                     // 0.0
/*60  */         unsigned int rgba = strtoul(color_string2, &tail, 16);                                          // 0.0
/*64  */         if (*tail || (len != 6 && len != 8)) {                                                          // 0.0
/*66  */             av_log(log_ctx, AV_LOG_ERROR, "Invalid 0xRRGGBB[AA] color string: '%s'\n", color_string2);  // 0.0
/*68  */             return AVERROR(EINVAL);                                                                     // 0.0
/*70  */         }                                                                                               // 0.0
/*72  */         if (len == 8) {                                                                                 // 0.0
/*74  */             rgba_color[3] = rgba;                                                                       // 0.0
/*76  */             rgba >>= 8;                                                                                 // 0.0
/*78  */         }                                                                                               // 0.0
/*80  */         rgba_color[0] = rgba >> 16;                                                                     // 0.0
/*82  */         rgba_color[1] = rgba >> 8;                                                                      // 0.0
/*84  */         rgba_color[2] = rgba;                                                                           // 0.0
/*86  */     } else {                                                                                            // 0.0
/*88  */         entry = bsearch(color_string2,                                                                  // 0.0
/*90  */                         color_table,                                                                    // 0.0
/*92  */                         FF_ARRAY_ELEMS(color_table),                                                    // 0.0
/*94  */                         sizeof(ColorEntry),                                                             // 0.0
/*96  */                         color_table_compare);                                                           // 0.0
/*98  */         if (!entry) {                                                                                   // 0.0
/*100 */             av_log(log_ctx, AV_LOG_ERROR, "Cannot find color '%s'\n", color_string2);                   // 0.0
/*102 */             return AVERROR(EINVAL);                                                                     // 0.0
/*104 */         }                                                                                               // 0.0
/*106 */         memcpy(rgba_color, entry->rgb_color, 3);                                                        // 0.0
/*108 */     }                                                                                                   // 0.0
/*112 */     if (tail) {                                                                                         // 0.0
/*114 */         unsigned long int alpha;                                                                        // 0.0
/*116 */         const char *alpha_string = tail;                                                                // 0.0
/*118 */         if (!strncmp(alpha_string, "0x", 2)) {                                                          // 0.0
/*120 */             alpha = strtoul(alpha_string, &tail, 16);                                                   // 0.0
/*122 */         } else {                                                                                        // 0.0
/*124 */             alpha = 255 * strtod(alpha_string, &tail);                                                  // 0.0
/*126 */         }                                                                                               // 0.0
/*130 */         if (tail == alpha_string || *tail || alpha > 255) {                                             // 0.0
/*132 */             av_log(log_ctx, AV_LOG_ERROR, "Invalid alpha value specifier '%s' in '%s'\n",               // 0.0
/*134 */                    alpha_string, color_string);                                                         // 0.0
/*136 */             return AVERROR(EINVAL);                                                                     // 0.0
/*138 */         }                                                                                               // 0.0
/*140 */         rgba_color[3] = alpha;                                                                          // 0.0
/*142 */     }                                                                                                   // 0.0
/*146 */     return 0;                                                                                           // 0.0
/*148 */ }                                                                                                       // 0.0
