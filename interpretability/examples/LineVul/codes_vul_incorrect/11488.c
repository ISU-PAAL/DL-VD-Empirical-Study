// commit message FFmpeg@a1a32fdb0e (target=1, prob=0.35117164, correct=False): avcodec/movtextdec: Make tx3g_ptr unsigned
/*0   */ static int mov_text_tx3g(AVCodecContext *avctx, MovTextContext *m)  // (3) 0.04688
/*2   */ {                                                                   // (30) 0.001953
/*4   */     char *tx3g_ptr = avctx->extradata;                              // (7) 0.03516
/*6   */     int i, box_size, font_length;                                   // (16) 0.02734
/*8   */     int8_t v_align, h_align;                                        // (11) 0.0293
/*10  */     int style_fontID;                                               // (25) 0.01758
/*12  */     StyleBox s_default;                                             // (26) 0.01758
/*16  */     m->count_f = 0;                                                 // (23) 0.02148
/*18  */     m->ftab_entries = 0;                                            // (19) 0.02539
/*20  */     box_size = BOX_SIZE_INITIAL; /* Size till ftab_entries */       // (4) 0.04687
/*22  */     if (avctx->extradata_size < box_size)                           // (8) 0.03516
/*24  */         return -1;                                                  // (24) 0.02148
/*28  */     // Display Flags                                                // (27) 0.01172
/*30  */     tx3g_ptr += 4;                                                  // (22) 0.02148
/*32  */     // Alignment                                                    // (28) 0.01172
/*34  */     h_align = *tx3g_ptr++;                                          // (18) 0.02734
/*36  */     v_align = *tx3g_ptr++;                                          // (17) 0.02734
/*38  */     if (h_align == 0) {                                             // (20) 0.02344
/*40  */         if (v_align == 0)                                           // (14) 0.0293
/*42  */             m->d.alignment = TOP_LEFT;                              // (5) 0.04492
/*44  */         if (v_align == 1)                                           // (13) 0.0293
/*46  */             m->d.alignment = MIDDLE_LEFT;                           // (0) 0.04883
/*48  */         if (v_align == -1)                                          // (9) 0.03125
/*50  */             m->d.alignment = BOTTOM_LEFT;                           // (2) 0.04883
/*52  */     }                                                               // (29) 0.007812
/*54  */     if (h_align == 1) {                                             // (21) 0.02344
/*56  */         if (v_align == 0)                                           // (12) 0.0293
/*58  */             m->d.alignment = TOP_CENTER;                            // (6) 0.04492
/*60  */         if (v_align == 1)                                           // (15) 0.0293
/*62  */             m->d.alignment = MIDDLE_CENTER;                         // (1) 0.04883
/*64  */         if (v_align == -1)                                          // (10) 0.03125
/*66  */             m->d.alignment = BOTTOM_CENTER;                         // 0.0
/*68  */     }                                                               // 0.0
/*70  */     if (h_align == -1) {                                            // 0.0
/*72  */         if (v_align == 0)                                           // 0.0
/*74  */             m->d.alignment = TOP_RIGHT;                             // 0.0
/*76  */         if (v_align == 1)                                           // 0.0
/*78  */             m->d.alignment = MIDDLE_RIGHT;                          // 0.0
/*80  */         if (v_align == -1)                                          // 0.0
/*82  */             m->d.alignment = BOTTOM_RIGHT;                          // 0.0
/*84  */     }                                                               // 0.0
/*86  */     // Background Color                                             // 0.0
/*88  */     m->d.back_color = AV_RB24(tx3g_ptr);                            // 0.0
/*90  */     tx3g_ptr += 4;                                                  // 0.0
/*92  */     // BoxRecord                                                    // 0.0
/*94  */     tx3g_ptr += 8;                                                  // 0.0
/*96  */     // StyleRecord                                                  // 0.0
/*98  */     tx3g_ptr += 4;                                                  // 0.0
/*100 */     // fontID                                                       // 0.0
/*102 */     style_fontID = AV_RB16(tx3g_ptr);                               // 0.0
/*104 */     tx3g_ptr += 2;                                                  // 0.0
/*106 */     // face-style-flags                                             // 0.0
/*108 */     s_default.style_flag = *tx3g_ptr++;                             // 0.0
/*110 */     m->d.bold = s_default.style_flag & STYLE_FLAG_BOLD;             // 0.0
/*112 */     m->d.italic = s_default.style_flag & STYLE_FLAG_ITALIC;         // 0.0
/*114 */     m->d.underline = s_default.style_flag & STYLE_FLAG_UNDERLINE;   // 0.0
/*116 */     // fontsize                                                     // 0.0
/*118 */     m->d.fontsize = *tx3g_ptr++;                                    // 0.0
/*120 */     // Primary color                                                // 0.0
/*122 */     m->d.color = AV_RB24(tx3g_ptr);                                 // 0.0
/*124 */     tx3g_ptr += 4;                                                  // 0.0
/*126 */     // FontRecord                                                   // 0.0
/*128 */     // FontRecord Size                                              // 0.0
/*130 */     tx3g_ptr += 4;                                                  // 0.0
/*132 */     // ftab                                                         // 0.0
/*134 */     tx3g_ptr += 4;                                                  // 0.0
/*138 */     m->ftab_entries = AV_RB16(tx3g_ptr);                            // 0.0
/*140 */     tx3g_ptr += 2;                                                  // 0.0
/*144 */     for (i = 0; i < m->ftab_entries; i++) {                         // 0.0
/*148 */         box_size += 3;                                              // 0.0
/*150 */         if (avctx->extradata_size < box_size) {                     // 0.0
/*152 */             mov_text_cleanup_ftab(m);                               // 0.0
/*154 */             m->ftab_entries = 0;                                    // 0.0
/*156 */             return -1;                                              // 0.0
/*158 */         }                                                           // 0.0
/*160 */         m->ftab_temp = av_malloc(sizeof(*m->ftab_temp));            // 0.0
/*162 */         if (!m->ftab_temp) {                                        // 0.0
/*164 */             mov_text_cleanup_ftab(m);                               // 0.0
/*166 */             return AVERROR(ENOMEM);                                 // 0.0
/*168 */         }                                                           // 0.0
/*170 */         m->ftab_temp->fontID = AV_RB16(tx3g_ptr);                   // 0.0
/*172 */         tx3g_ptr += 2;                                              // 0.0
/*174 */         font_length = *tx3g_ptr++;                                  // 0.0
/*178 */         box_size = box_size + font_length;                          // 0.0
/*180 */         if (avctx->extradata_size < box_size) {                     // 0.0
/*182 */             mov_text_cleanup_ftab(m);                               // 0.0
/*184 */             m->ftab_entries = 0;                                    // 0.0
/*186 */             return -1;                                              // 0.0
/*188 */         }                                                           // 0.0
/*190 */         m->ftab_temp->font = av_malloc(font_length + 1);            // 0.0
/*192 */         if (!m->ftab_temp->font) {                                  // 0.0
/*194 */             mov_text_cleanup_ftab(m);                               // 0.0
/*196 */             return AVERROR(ENOMEM);                                 // 0.0
/*198 */         }                                                           // 0.0
/*200 */         memcpy(m->ftab_temp->font, tx3g_ptr, font_length);          // 0.0
/*202 */         m->ftab_temp->font[font_length] = '\0';                     // 0.0
/*204 */         av_dynarray_add(&m->ftab, &m->count_f, m->ftab_temp);       // 0.0
/*206 */         if (!m->ftab) {                                             // 0.0
/*208 */             mov_text_cleanup_ftab(m);                               // 0.0
/*210 */             return AVERROR(ENOMEM);                                 // 0.0
/*212 */         }                                                           // 0.0
/*214 */         tx3g_ptr = tx3g_ptr + font_length;                          // 0.0
/*216 */     }                                                               // 0.0
/*218 */     for (i = 0; i < m->ftab_entries; i++) {                         // 0.0
/*220 */         if (style_fontID == m->ftab[i]->fontID)                     // 0.0
/*222 */             m->d.font = m->ftab[i]->font;                           // 0.0
/*224 */     }                                                               // 0.0
/*226 */     return 0;                                                       // 0.0
/*228 */ }                                                                   // 0.0
