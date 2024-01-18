// commit message FFmpeg@c83002a4f8 (target=1, prob=0.66131806, correct=True): lavc/ass_split: check for NULL pointer in ff_ass_split_override_codes().
/*0   */ int ff_ass_split_override_codes(const ASSCodesCallbacks *callbacks, void *priv,                                               // (6) 0.05078
/*2   */                                 const char *buf)                                                                              // (1) 0.07031
/*4   */ {                                                                                                                             // (22) 0.001953
/*6   */     const char *text = NULL;                                                                                                  // (18) 0.01953
/*8   */     char new_line[2];                                                                                                         // (19) 0.01953
/*10  */     int text_len = 0;                                                                                                         // (17) 0.01953
/*14  */     while (*buf) {                                                                                                            // (20) 0.01562
/*16  */         if (text && callbacks->text &&                                                                                        // (13) 0.03125
/*18  */             (sscanf(buf, "\\%1[nN]", new_line) == 1 ||                                                                        // (3) 0.06641
/*20  */              !strncmp(buf, "{\\", 2))) {                                                                                      // (7) 0.04883
/*22  */             callbacks->text(priv, text, text_len);                                                                            // (9) 0.04687
/*24  */             text = NULL;                                                                                                      // (15) 0.0293
/*26  */         }                                                                                                                     // (21) 0.01562
/*28  */         if (sscanf(buf, "\\%1[nN]", new_line) == 1) {                                                                         // (5) 0.0625
/*30  */             if (callbacks->new_line)                                                                                          // (11) 0.03906
/*32  */                 callbacks->new_line(priv, new_line[0] == 'N');                                                                // (2) 0.06641
/*34  */             buf += 2;                                                                                                         // (14) 0.0293
/*36  */         } else if (!strncmp(buf, "{\\", 2)) {                                                                                 // (10) 0.04492
/*38  */             buf++;                                                                                                            // (16) 0.02539
/*40  */             while (*buf == '\\') {                                                                                            // (12) 0.03711
/*42  */                 char style[2], c[2], sep[2], c_num[2] = "0", tmp[128] = {0};                                                  // (0) 0.08984
/*44  */                 unsigned int color = 0xFFFFFFFF;                                                                              // (8) 0.04688
/*46  */                 int len, size = -1, an = -1, alpha = -1;                                                                      // (4) 0.06445
/*48  */                 int x1, y1, x2, y2, t1 = -1, t2 = -1;                                                                         // 0.0
/*50  */                 if (sscanf(buf, "\\%1[bisu]%1[01\\}]%n", style, c, &len) > 1) {                                               // 0.0
/*52  */                     int close = c[0] == '0' ? 1 : c[0] == '1' ? 0 : -1;                                                       // 0.0
/*54  */                     len += close != -1;                                                                                       // 0.0
/*56  */                     if (callbacks->style)                                                                                     // 0.0
/*58  */                         callbacks->style(priv, style[0], close);                                                              // 0.0
/*60  */                 } else if (sscanf(buf, "\\c%1[\\}]%n", sep, &len) > 0 ||                                                      // 0.0
/*62  */                            sscanf(buf, "\\c&H%X&%1[\\}]%n", &color, sep, &len) > 1 ||                                         // 0.0
/*64  */                            sscanf(buf, "\\%1[1234]c%1[\\}]%n", c_num, sep, &len) > 1 ||                                       // 0.0
/*66  */                            sscanf(buf, "\\%1[1234]c&H%X&%1[\\}]%n", c_num, &color, sep, &len) > 2) {                          // 0.0
/*68  */                     if (callbacks->color)                                                                                     // 0.0
/*70  */                         callbacks->color(priv, color, c_num[0] - '0');                                                        // 0.0
/*72  */                 } else if (sscanf(buf, "\\alpha%1[\\}]%n", sep, &len) > 0 ||                                                  // 0.0
/*74  */                            sscanf(buf, "\\alpha&H%2X&%1[\\}]%n", &alpha, sep, &len) > 1 ||                                    // 0.0
/*76  */                            sscanf(buf, "\\%1[1234]a%1[\\}]%n", c_num, sep, &len) > 1 ||                                       // 0.0
/*78  */                            sscanf(buf, "\\%1[1234]a&H%2X&%1[\\}]%n", c_num, &alpha, sep, &len) > 2) {                         // 0.0
/*80  */                     if (callbacks->alpha)                                                                                     // 0.0
/*82  */                         callbacks->alpha(priv, alpha, c_num[0] - '0');                                                        // 0.0
/*84  */                 } else if (sscanf(buf, "\\fn%1[\\}]%n", sep, &len) > 0 ||                                                     // 0.0
/*86  */                            sscanf(buf, "\\fn%127[^\\}]%1[\\}]%n", tmp, sep, &len) > 1) {                                      // 0.0
/*88  */                     if (callbacks->font_name)                                                                                 // 0.0
/*90  */                         callbacks->font_name(priv, tmp[0] ? tmp : NULL);                                                      // 0.0
/*92  */                 } else if (sscanf(buf, "\\fs%1[\\}]%n", sep, &len) > 0 ||                                                     // 0.0
/*94  */                            sscanf(buf, "\\fs%u%1[\\}]%n", &size, sep, &len) > 1) {                                            // 0.0
/*96  */                     if (callbacks->font_size)                                                                                 // 0.0
/*98  */                         callbacks->font_size(priv, size);                                                                     // 0.0
/*100 */                 } else if (sscanf(buf, "\\a%1[\\}]%n", sep, &len) > 0 ||                                                      // 0.0
/*102 */                            sscanf(buf, "\\a%2u%1[\\}]%n", &an, sep, &len) > 1 ||                                              // 0.0
/*104 */                            sscanf(buf, "\\an%1[\\}]%n", sep, &len) > 0 ||                                                     // 0.0
/*106 */                            sscanf(buf, "\\an%1u%1[\\}]%n", &an, sep, &len) > 1) {                                             // 0.0
/*108 */                     if (an != -1 && buf[2] != 'n')                                                                            // 0.0
/*110 */                         an = (an&3) + (an&4 ? 6 : an&8 ? 3 : 0);                                                              // 0.0
/*112 */                     if (callbacks->alignment)                                                                                 // 0.0
/*114 */                         callbacks->alignment(priv, an);                                                                       // 0.0
/*116 */                 } else if (sscanf(buf, "\\r%1[\\}]%n", sep, &len) > 0 ||                                                      // 0.0
/*118 */                            sscanf(buf, "\\r%127[^\\}]%1[\\}]%n", tmp, sep, &len) > 1) {                                       // 0.0
/*120 */                     if (callbacks->cancel_overrides)                                                                          // 0.0
/*122 */                         callbacks->cancel_overrides(priv, tmp);                                                               // 0.0
/*124 */                 } else if (sscanf(buf, "\\move(%d,%d,%d,%d)%1[\\}]%n", &x1, &y1, &x2, &y2, sep, &len) > 4 ||                  // 0.0
/*126 */                            sscanf(buf, "\\move(%d,%d,%d,%d,%d,%d)%1[\\}]%n", &x1, &y1, &x2, &y2, &t1, &t2, sep, &len) > 6) {  // 0.0
/*128 */                     if (callbacks->move)                                                                                      // 0.0
/*130 */                         callbacks->move(priv, x1, y1, x2, y2, t1, t2);                                                        // 0.0
/*132 */                 } else if (sscanf(buf, "\\pos(%d,%d)%1[\\}]%n", &x1, &y1, sep, &len) > 2) {                                   // 0.0
/*134 */                     if (callbacks->move)                                                                                      // 0.0
/*136 */                         callbacks->move(priv, x1, y1, x1, y1, -1, -1);                                                        // 0.0
/*138 */                 } else if (sscanf(buf, "\\org(%d,%d)%1[\\}]%n", &x1, &y1, sep, &len) > 2) {                                   // 0.0
/*140 */                     if (callbacks->origin)                                                                                    // 0.0
/*142 */                         callbacks->origin(priv, x1, y1);                                                                      // 0.0
/*144 */                 } else {                                                                                                      // 0.0
/*146 */                     len = strcspn(buf+1, "\\}") + 2;  /* skip unknown code */                                                 // 0.0
/*148 */                 }                                                                                                             // 0.0
/*150 */                 buf += len - 1;                                                                                               // 0.0
/*152 */             }                                                                                                                 // 0.0
/*154 */             if (*buf++ != '}')                                                                                                // 0.0
/*156 */                 return AVERROR_INVALIDDATA;                                                                                   // 0.0
/*158 */         } else {                                                                                                              // 0.0
/*160 */             if (!text) {                                                                                                      // 0.0
/*162 */                 text = buf;                                                                                                   // 0.0
/*164 */                 text_len = 1;                                                                                                 // 0.0
/*166 */             } else                                                                                                            // 0.0
/*168 */                 text_len++;                                                                                                   // 0.0
/*170 */             buf++;                                                                                                            // 0.0
/*172 */         }                                                                                                                     // 0.0
/*174 */     }                                                                                                                         // 0.0
/*176 */     if (text && callbacks->text)                                                                                              // 0.0
/*178 */         callbacks->text(priv, text, text_len);                                                                                // 0.0
/*180 */     if (callbacks->end)                                                                                                       // 0.0
/*182 */         callbacks->end(priv);                                                                                                 // 0.0
/*184 */     return 0;                                                                                                                 // 0.0
/*186 */ }                                                                                                                             // 0.0
