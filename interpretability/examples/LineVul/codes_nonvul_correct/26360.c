// commit message FFmpeg@01e4537f66 (target=0, prob=0.10166384, correct=True): ffprobe: rework/fix flat writer
/*0  */ static void flat_print_key_prefix(WriterContext *wctx)                     // (6) 0.07767
/*2  */ {                                                                          // (9) 0.004854
/*4  */     FlatContext *flat = wctx->priv;                                        // (7) 0.06311
/*6  */     const struct section *parent_section = wctx->section[wctx->level-1];   // (2) 0.1117
/*10 */     printf("%s", flat->section_header[wctx->level].str);                   // (4) 0.1019
/*14 */     if (parent_section->flags & SECTION_FLAG_IS_ARRAY) {                   // (5) 0.1019
/*16 */         int n = parent_section->id == SECTION_ID_PACKETS_AND_FRAMES ?      // (1) 0.1408
/*18 */             wctx->nb_section_packet_frame : wctx->nb_item[wctx->level-1];  // (0) 0.1796
/*20 */         printf("%d%s", n, flat->sep_str);                                  // (3) 0.1117
/*22 */     }                                                                      // (8) 0.01942
/*24 */ }                                                                          // (10) 0.004854
