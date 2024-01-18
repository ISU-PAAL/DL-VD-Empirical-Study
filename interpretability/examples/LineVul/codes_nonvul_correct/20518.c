// commit message qemu@4083733db5 (target=0, prob=0.20997253, correct=True): ui/curses: Fix color attribute of monitor for curses
/*0   */ static void console_handle_escape(QemuConsole *s)                  // (17) 0.0293
/*2   */ {                                                                  // (25) 0.001953
/*4   */     int i;                                                         // (24) 0.01172
/*8   */     for (i=0; i<s->nb_esc_params; i++) {                           // (7) 0.04297
/*10  */         switch (s->esc_params[i]) {                                // (9) 0.03516
/*12  */             case 0: /* reset all console attributes to default */  // (8) 0.04297
/*14  */                 s->t_attrib = s->t_attrib_default;                 // (0) 0.06055
/*16  */                 break;                                             // (10) 0.0332
/*18  */             case 1:                                                // (18) 0.02734
/*20  */                 s->t_attrib.bold = 1;                              // (5) 0.05078
/*22  */                 break;                                             // (11) 0.0332
/*24  */             case 4:                                                // (19) 0.02734
/*26  */                 s->t_attrib.uline = 1;                             // (1) 0.05273
/*28  */                 break;                                             // (12) 0.0332
/*30  */             case 5:                                                // (20) 0.02734
/*32  */                 s->t_attrib.blink = 1;                             // (2) 0.05273
/*34  */                 break;                                             // (13) 0.0332
/*36  */             case 7:                                                // (21) 0.02734
/*38  */                 s->t_attrib.invers = 1;                            // (3) 0.05273
/*40  */                 break;                                             // (14) 0.0332
/*42  */             case 8:                                                // (22) 0.02734
/*44  */                 s->t_attrib.unvisible = 1;                         // (4) 0.05273
/*46  */                 break;                                             // (15) 0.0332
/*48  */             case 22:                                               // (23) 0.02734
/*50  */                 s->t_attrib.bold = 0;                              // (6) 0.05078
/*52  */                 break;                                             // (16) 0.0332
/*54  */             case 24:                                               // 0.0
/*56  */                 s->t_attrib.uline = 0;                             // 0.0
/*58  */                 break;                                             // 0.0
/*60  */             case 25:                                               // 0.0
/*62  */                 s->t_attrib.blink = 0;                             // 0.0
/*64  */                 break;                                             // 0.0
/*66  */             case 27:                                               // 0.0
/*68  */                 s->t_attrib.invers = 0;                            // 0.0
/*70  */                 break;                                             // 0.0
/*72  */             case 28:                                               // 0.0
/*74  */                 s->t_attrib.unvisible = 0;                         // 0.0
/*76  */                 break;                                             // 0.0
/*78  */             /* set foreground color */                             // 0.0
/*80  */             case 30:                                               // 0.0
/*82  */                 s->t_attrib.fgcol=COLOR_BLACK;                     // 0.0
/*84  */                 break;                                             // 0.0
/*86  */             case 31:                                               // 0.0
/*88  */                 s->t_attrib.fgcol=COLOR_RED;                       // 0.0
/*90  */                 break;                                             // 0.0
/*92  */             case 32:                                               // 0.0
/*94  */                 s->t_attrib.fgcol=COLOR_GREEN;                     // 0.0
/*96  */                 break;                                             // 0.0
/*98  */             case 33:                                               // 0.0
/*100 */                 s->t_attrib.fgcol=COLOR_YELLOW;                    // 0.0
/*102 */                 break;                                             // 0.0
/*104 */             case 34:                                               // 0.0
/*106 */                 s->t_attrib.fgcol=COLOR_BLUE;                      // 0.0
/*108 */                 break;                                             // 0.0
/*110 */             case 35:                                               // 0.0
/*112 */                 s->t_attrib.fgcol=COLOR_MAGENTA;                   // 0.0
/*114 */                 break;                                             // 0.0
/*116 */             case 36:                                               // 0.0
/*118 */                 s->t_attrib.fgcol=COLOR_CYAN;                      // 0.0
/*120 */                 break;                                             // 0.0
/*122 */             case 37:                                               // 0.0
/*124 */                 s->t_attrib.fgcol=COLOR_WHITE;                     // 0.0
/*126 */                 break;                                             // 0.0
/*128 */             /* set background color */                             // 0.0
/*130 */             case 40:                                               // 0.0
/*132 */                 s->t_attrib.bgcol=COLOR_BLACK;                     // 0.0
/*134 */                 break;                                             // 0.0
/*136 */             case 41:                                               // 0.0
/*138 */                 s->t_attrib.bgcol=COLOR_RED;                       // 0.0
/*140 */                 break;                                             // 0.0
/*142 */             case 42:                                               // 0.0
/*144 */                 s->t_attrib.bgcol=COLOR_GREEN;                     // 0.0
/*146 */                 break;                                             // 0.0
/*148 */             case 43:                                               // 0.0
/*150 */                 s->t_attrib.bgcol=COLOR_YELLOW;                    // 0.0
/*152 */                 break;                                             // 0.0
/*154 */             case 44:                                               // 0.0
/*156 */                 s->t_attrib.bgcol=COLOR_BLUE;                      // 0.0
/*158 */                 break;                                             // 0.0
/*160 */             case 45:                                               // 0.0
/*162 */                 s->t_attrib.bgcol=COLOR_MAGENTA;                   // 0.0
/*164 */                 break;                                             // 0.0
/*166 */             case 46:                                               // 0.0
/*168 */                 s->t_attrib.bgcol=COLOR_CYAN;                      // 0.0
/*170 */                 break;                                             // 0.0
/*172 */             case 47:                                               // 0.0
/*174 */                 s->t_attrib.bgcol=COLOR_WHITE;                     // 0.0
/*176 */                 break;                                             // 0.0
/*178 */         }                                                          // 0.0
/*180 */     }                                                              // 0.0
/*182 */ }                                                                  // 0.0
