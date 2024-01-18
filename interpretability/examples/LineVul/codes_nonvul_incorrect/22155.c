// commit message qemu@5829b09720 (target=0, prob=0.64504445, correct=False): vmsvga: more cursor checks
/*0   */ static void vmsvga_fifo_run(struct vmsvga_state_s *s)                            // (5) 0.04688
/*2   */ {                                                                                // (26) 0.001953
/*4   */     uint32_t cmd, colour;                                                        // (22) 0.02148
/*6   */     int args, len;                                                               // (25) 0.01562
/*8   */     int x, y, dx, dy, width, height;                                             // (16) 0.03125
/*10  */     struct vmsvga_cursor_definition_s cursor;                                    // (13) 0.03321
/*12  */     uint32_t cmd_start;                                                          // (23) 0.02148
/*16  */     len = vmsvga_fifo_length(s);                                                 // (14) 0.0332
/*18  */     while (len > 0) {                                                            // (24) 0.01953
/*20  */         /* May need to go back to the start of the command if incomplete */      // (7) 0.04297
/*22  */         cmd_start = s->cmd->stop;                                                // (15) 0.0332
/*26  */         switch (cmd = vmsvga_fifo_read(s)) {                                     // (6) 0.04687
/*28  */         case SVGA_CMD_UPDATE:                                                    // (17) 0.03125
/*30  */         case SVGA_CMD_UPDATE_VERBOSE:                                            // (8) 0.03906
/*32  */             len -= 5;                                                            // (18) 0.0293
/*34  */             if (len < 0) {                                                       // (11) 0.03516
/*36  */                 goto rewind;                                                     // (10) 0.03711
/*38  */             }                                                                    // (21) 0.02344
/*42  */             x = vmsvga_fifo_read(s);                                             // (2) 0.04883
/*44  */             y = vmsvga_fifo_read(s);                                             // (1) 0.04883
/*46  */             width = vmsvga_fifo_read(s);                                         // (4) 0.04883
/*48  */             height = vmsvga_fifo_read(s);                                        // (3) 0.04883
/*50  */             vmsvga_update_rect_delayed(s, x, y, width, height);                  // (0) 0.06445
/*52  */             break;                                                               // (20) 0.02539
/*56  */         case SVGA_CMD_RECT_FILL:                                                 // (9) 0.03711
/*58  */             len -= 6;                                                            // (19) 0.0293
/*60  */             if (len < 0) {                                                       // (12) 0.03516
/*62  */                 goto rewind;                                                     // 0.0
/*64  */             }                                                                    // 0.0
/*68  */             colour = vmsvga_fifo_read(s);                                        // 0.0
/*70  */             x = vmsvga_fifo_read(s);                                             // 0.0
/*72  */             y = vmsvga_fifo_read(s);                                             // 0.0
/*74  */             width = vmsvga_fifo_read(s);                                         // 0.0
/*76  */             height = vmsvga_fifo_read(s);                                        // 0.0
/*78  */ #ifdef HW_FILL_ACCEL                                                             // 0.0
/*80  */             if (vmsvga_fill_rect(s, colour, x, y, width, height) == 0) {         // 0.0
/*82  */                 break;                                                           // 0.0
/*84  */             }                                                                    // 0.0
/*86  */ #endif                                                                           // 0.0
/*88  */             args = 0;                                                            // 0.0
/*90  */             goto badcmd;                                                         // 0.0
/*94  */         case SVGA_CMD_RECT_COPY:                                                 // 0.0
/*96  */             len -= 7;                                                            // 0.0
/*98  */             if (len < 0) {                                                       // 0.0
/*100 */                 goto rewind;                                                     // 0.0
/*102 */             }                                                                    // 0.0
/*106 */             x = vmsvga_fifo_read(s);                                             // 0.0
/*108 */             y = vmsvga_fifo_read(s);                                             // 0.0
/*110 */             dx = vmsvga_fifo_read(s);                                            // 0.0
/*112 */             dy = vmsvga_fifo_read(s);                                            // 0.0
/*114 */             width = vmsvga_fifo_read(s);                                         // 0.0
/*116 */             height = vmsvga_fifo_read(s);                                        // 0.0
/*118 */ #ifdef HW_RECT_ACCEL                                                             // 0.0
/*120 */             if (vmsvga_copy_rect(s, x, y, dx, dy, width, height) == 0) {         // 0.0
/*122 */                 break;                                                           // 0.0
/*124 */             }                                                                    // 0.0
/*126 */ #endif                                                                           // 0.0
/*128 */             args = 0;                                                            // 0.0
/*130 */             goto badcmd;                                                         // 0.0
/*134 */         case SVGA_CMD_DEFINE_CURSOR:                                             // 0.0
/*136 */             len -= 8;                                                            // 0.0
/*138 */             if (len < 0) {                                                       // 0.0
/*140 */                 goto rewind;                                                     // 0.0
/*142 */             }                                                                    // 0.0
/*146 */             cursor.id = vmsvga_fifo_read(s);                                     // 0.0
/*148 */             cursor.hot_x = vmsvga_fifo_read(s);                                  // 0.0
/*150 */             cursor.hot_y = vmsvga_fifo_read(s);                                  // 0.0
/*152 */             cursor.width = x = vmsvga_fifo_read(s);                              // 0.0
/*154 */             cursor.height = y = vmsvga_fifo_read(s);                             // 0.0
/*156 */             vmsvga_fifo_read(s);                                                 // 0.0
/*158 */             cursor.bpp = vmsvga_fifo_read(s);                                    // 0.0
/*162 */             args = SVGA_BITMAP_SIZE(x, y) + SVGA_PIXMAP_SIZE(x, y, cursor.bpp);  // 0.0
/*164 */             if (SVGA_BITMAP_SIZE(x, y) > sizeof cursor.mask ||                   // 0.0
/*166 */                 SVGA_PIXMAP_SIZE(x, y, cursor.bpp) > sizeof cursor.image) {      // 0.0
/*168 */                     goto badcmd;                                                 // 0.0
/*170 */             }                                                                    // 0.0
/*174 */             len -= args;                                                         // 0.0
/*176 */             if (len < 0) {                                                       // 0.0
/*178 */                 goto rewind;                                                     // 0.0
/*180 */             }                                                                    // 0.0
/*184 */             for (args = 0; args < SVGA_BITMAP_SIZE(x, y); args++) {              // 0.0
/*186 */                 cursor.mask[args] = vmsvga_fifo_read_raw(s);                     // 0.0
/*188 */             }                                                                    // 0.0
/*190 */             for (args = 0; args < SVGA_PIXMAP_SIZE(x, y, cursor.bpp); args++) {  // 0.0
/*192 */                 cursor.image[args] = vmsvga_fifo_read_raw(s);                    // 0.0
/*194 */             }                                                                    // 0.0
/*196 */ #ifdef HW_MOUSE_ACCEL                                                            // 0.0
/*198 */             vmsvga_cursor_define(s, &cursor);                                    // 0.0
/*200 */             break;                                                               // 0.0
/*202 */ #else                                                                            // 0.0
/*204 */             args = 0;                                                            // 0.0
/*206 */             goto badcmd;                                                         // 0.0
/*208 */ #endif                                                                           // 0.0
/*212 */         /*                                                                       // 0.0
/*214 */          * Other commands that we at least know the number of arguments          // 0.0
/*216 */          * for so we can avoid FIFO desync if driver uses them illegally.        // 0.0
/*218 */          */                                                                      // 0.0
/*220 */         case SVGA_CMD_DEFINE_ALPHA_CURSOR:                                       // 0.0
/*222 */             len -= 6;                                                            // 0.0
/*224 */             if (len < 0) {                                                       // 0.0
/*226 */                 goto rewind;                                                     // 0.0
/*228 */             }                                                                    // 0.0
/*230 */             vmsvga_fifo_read(s);                                                 // 0.0
/*232 */             vmsvga_fifo_read(s);                                                 // 0.0
/*234 */             vmsvga_fifo_read(s);                                                 // 0.0
/*236 */             x = vmsvga_fifo_read(s);                                             // 0.0
/*238 */             y = vmsvga_fifo_read(s);                                             // 0.0
/*240 */             args = x * y;                                                        // 0.0
/*242 */             goto badcmd;                                                         // 0.0
/*244 */         case SVGA_CMD_RECT_ROP_FILL:                                             // 0.0
/*246 */             args = 6;                                                            // 0.0
/*248 */             goto badcmd;                                                         // 0.0
/*250 */         case SVGA_CMD_RECT_ROP_COPY:                                             // 0.0
/*252 */             args = 7;                                                            // 0.0
/*254 */             goto badcmd;                                                         // 0.0
/*256 */         case SVGA_CMD_DRAW_GLYPH_CLIPPED:                                        // 0.0
/*258 */             len -= 4;                                                            // 0.0
/*260 */             if (len < 0) {                                                       // 0.0
/*262 */                 goto rewind;                                                     // 0.0
/*264 */             }                                                                    // 0.0
/*266 */             vmsvga_fifo_read(s);                                                 // 0.0
/*268 */             vmsvga_fifo_read(s);                                                 // 0.0
/*270 */             args = 7 + (vmsvga_fifo_read(s) >> 2);                               // 0.0
/*272 */             goto badcmd;                                                         // 0.0
/*274 */         case SVGA_CMD_SURFACE_ALPHA_BLEND:                                       // 0.0
/*276 */             args = 12;                                                           // 0.0
/*278 */             goto badcmd;                                                         // 0.0
/*282 */         /*                                                                       // 0.0
/*284 */          * Other commands that are not listed as depending on any                // 0.0
/*286 */          * CAPABILITIES bits, but are not described in the README either.        // 0.0
/*288 */          */                                                                      // 0.0
/*290 */         case SVGA_CMD_SURFACE_FILL:                                              // 0.0
/*292 */         case SVGA_CMD_SURFACE_COPY:                                              // 0.0
/*294 */         case SVGA_CMD_FRONT_ROP_FILL:                                            // 0.0
/*296 */         case SVGA_CMD_FENCE:                                                     // 0.0
/*298 */         case SVGA_CMD_INVALID_CMD:                                               // 0.0
/*300 */             break; /* Nop */                                                     // 0.0
/*304 */         default:                                                                 // 0.0
/*306 */             args = 0;                                                            // 0.0
/*308 */         badcmd:                                                                  // 0.0
/*310 */             len -= args;                                                         // 0.0
/*312 */             if (len < 0) {                                                       // 0.0
/*314 */                 goto rewind;                                                     // 0.0
/*316 */             }                                                                    // 0.0
/*318 */             while (args--) {                                                     // 0.0
/*320 */                 vmsvga_fifo_read(s);                                             // 0.0
/*322 */             }                                                                    // 0.0
/*324 */             printf("%s: Unknown command 0x%02x in SVGA command FIFO\n",          // 0.0
/*326 */                    __func__, cmd);                                               // 0.0
/*328 */             break;                                                               // 0.0
/*332 */         rewind:                                                                  // 0.0
/*334 */             s->cmd->stop = cmd_start;                                            // 0.0
/*336 */             break;                                                               // 0.0
/*338 */         }                                                                        // 0.0
/*340 */     }                                                                            // 0.0
/*344 */     s->syncing = 0;                                                              // 0.0
/*346 */ }                                                                                // 0.0
