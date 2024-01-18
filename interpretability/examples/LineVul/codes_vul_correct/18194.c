// commit message qemu@6baebed769 (target=1, prob=0.656647, correct=True): vnc: cleanup surface handling, fix screen corruption bug. (Gerd Hoffmann)
/*0  */ static int find_dirty_height(VncState *vs, int y, int last_x, int x)  // (3) 0.1256
/*2  */ {                                                                     // (10) 0.005025
/*4  */     int h;                                                            // (7) 0.03015
/*8  */     for (h = 1; h < (vs->serverds.height - y); h++) {                 // (4) 0.1206
/*10 */         int tmp_x;                                                    // (6) 0.0603
/*12 */         if (!vnc_get_bit(vs->dirty_row[y + h], last_x))               // (1) 0.1508
/*14 */             break;                                                    // (5) 0.06533
/*16 */         for (tmp_x = last_x; tmp_x < x; tmp_x++)                      // (2) 0.1357
/*18 */             vnc_clear_bit(vs->dirty_row[y + h], tmp_x);               // (0) 0.1608
/*20 */     }                                                                 // (9) 0.0201
/*24 */     return h;                                                         // (8) 0.03015
/*26 */ }                                                                     // (11) 0.005025
