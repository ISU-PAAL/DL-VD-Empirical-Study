// commit message qemu@0d7937974c (target=0, prob=0.30060074, correct=True): vmware_vga: Coding style cleanup
/*0  */ static inline void vmsvga_update_rect_delayed(struct vmsvga_state_s *s,    // (1) 0.1617
/*2  */                 int x, int y, int w, int h)                                // (2) 0.1617
/*4  */ {                                                                          // (8) 0.005988
/*6  */     struct vmsvga_rect_s *rect = &s->redraw_fifo[s->redraw_fifo_last ++];  // (0) 0.2096
/*8  */     s->redraw_fifo_last &= REDRAW_FIFO_LEN - 1;                            // (3) 0.1557
/*10 */     rect->x = x;                                                           // (4) 0.05389
/*12 */     rect->y = y;                                                           // (5) 0.05389
/*14 */     rect->w = w;                                                           // (6) 0.05389
/*16 */     rect->h = h;                                                           // (7) 0.05389
/*18 */ }                                                                          // (9) 0.005988
