// commit message FFmpeg@29d46d7bce (target=1, prob=0.377946, correct=False): ffprobe: fix potential NULL pointer dereference
/*0  */ static void json_print_section_header(WriterContext *wctx)                                   // (13) 0.03125
/*2  */ {                                                                                            // (24) 0.001956
/*4  */     JSONContext *json = wctx->priv;                                                          // (17) 0.02539
/*6  */     AVBPrint buf;                                                                            // (22) 0.01562
/*8  */     const struct section *section = wctx->section[wctx->level];                              // (12) 0.03711
/*10 */     const struct section *parent_section = wctx->level ?                                     // (14) 0.03125
/*12 */         wctx->section[wctx->level-1] : NULL;                                                 // (9) 0.04297
/*16 */     if (wctx->level && wctx->nb_item[wctx->level-1])                                         // (7) 0.04687
/*18 */         printf(",\n");                                                                       // (18) 0.02539
/*22 */     if (section->flags & SECTION_FLAG_IS_WRAPPER) {                                          // (11) 0.03906
/*24 */         printf("{\n");                                                                       // (19) 0.02344
/*26 */         json->indent_level++;                                                                // (15) 0.02734
/*28 */     } else {                                                                                 // (23) 0.01172
/*30 */         av_bprint_init(&buf, 1, AV_BPRINT_SIZE_UNLIMITED);                                   // (2) 0.06055
/*32 */         json_escape_str(&buf, section->name, wctx);                                          // (10) 0.04297
/*34 */         JSON_INDENT();                                                                       // (20) 0.02344
/*38 */         json->indent_level++;                                                                // (16) 0.02734
/*40 */         if (section->flags & SECTION_FLAG_IS_ARRAY) {                                        // (8) 0.04492
/*42 */             printf("\"%s\": [\n", buf.str);                                                  // (6) 0.04883
/*44 */         } else if (!(parent_section->flags & SECTION_FLAG_IS_ARRAY)) {                       // (3) 0.05469
/*46 */             printf("\"%s\": {%s", buf.str, json->item_start_end);                            // (1) 0.06445
/*48 */         } else {                                                                             // (21) 0.01953
/*50 */             printf("{%s", json->item_start_end);                                             // (5) 0.04883
/*54 */             /* this is required so the parser can distinguish between packets and frames */  // (4) 0.04883
/*56 */             if (parent_section->id == SECTION_ID_PACKETS_AND_FRAMES) {                       // (0) 0.06445
/*58 */                 if (!json->compact)                                                          // 0.0
/*60 */                     JSON_INDENT();                                                           // 0.0
/*62 */                 printf("\"type\": \"%s\"%s", section->name, json->item_sep);                 // 0.0
/*64 */             }                                                                                // 0.0
/*66 */         }                                                                                    // 0.0
/*68 */         av_bprint_finalize(&buf, NULL);                                                      // 0.0
/*70 */     }                                                                                        // 0.0
/*72 */ }                                                                                            // 0.0
