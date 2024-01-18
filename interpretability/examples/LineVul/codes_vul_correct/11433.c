// commit message FFmpeg@8ce803db51 (target=1, prob=0.50169444, correct=True): Make x11grab cursor drawing suck less This new version: 1.  Works on 24-bit and 32-bit input, not just 32-bit. 2.  Doesn't try to run on 16-bit or 8-bit, instead of outright crashing. 3.  Does proper alpha-blending, so cursor shadows look correct. 4.  Doesn't swap R and B.
/*0  */ paint_mouse_pointer(XImage *image, struct x11_grab *s)                                                  // (8) 0.03906
/*2  */ {                                                                                                       // (22) 0.001954
/*4  */     int x_off = s->x_off;                                                                               // (12) 0.02734
/*6  */     int y_off = s->y_off;                                                                               // (14) 0.02734
/*8  */     int width = s->width;                                                                               // (19) 0.01953
/*10 */     int height = s->height;                                                                             // (18) 0.01953
/*12 */     Display *dpy = s->dpy;                                                                              // (15) 0.02539
/*14 */     XFixesCursorImage *xcim;                                                                            // (16) 0.02539
/*16 */     int x, y;                                                                                           // (20) 0.01563
/*18 */     int line, column;                                                                                   // (21) 0.01562
/*20 */     int to_line, to_column;                                                                             // (17) 0.02344
/*22 */     int image_addr, xcim_addr;                                                                          // (13) 0.02734
/*26 */     xcim = XFixesGetCursorImage(dpy);                                                                   // (9) 0.03516
/*30 */     x = xcim->x - xcim->xhot;                                                                           // (11) 0.03516
/*32 */     y = xcim->y - xcim->yhot;                                                                           // (10) 0.03516
/*36 */     to_line = FFMIN((y + xcim->height), (height + y_off));                                              // (7) 0.04883
/*38 */     to_column = FFMIN((x + xcim->width), (width + x_off));                                              // (6) 0.04883
/*42 */     for (line = FFMAX(y, y_off); line < to_line; line++) {                                              // (5) 0.04883
/*44 */         for (column = FFMAX(x, x_off); column < to_column; column++) {                                  // (4) 0.05664
/*46 */             xcim_addr = (line - y) * xcim->width + column - x;                                          // (3) 0.06445
/*50 */             if ((unsigned char)(xcim->pixels[xcim_addr] >> 24) != 0) { // skip fully transparent pixel  // (1) 0.07617
/*52 */                 image_addr = ((line - y_off) * width + column - x_off) * 4;                             // (2) 0.07422
/*56 */                 image->data[image_addr] = (unsigned char)(xcim->pixels[xcim_addr] >> 0);                // (0) 0.08203
/*58 */                 image->data[image_addr+1] = (unsigned char)(xcim->pixels[xcim_addr] >> 8);              // 0.0
/*60 */                 image->data[image_addr+2] = (unsigned char)(xcim->pixels[xcim_addr] >> 16);             // 0.0
/*62 */             }                                                                                           // 0.0
/*64 */         }                                                                                               // 0.0
/*66 */     }                                                                                                   // 0.0
/*70 */     XFree(xcim);                                                                                        // 0.0
/*72 */     xcim = NULL;                                                                                        // 0.0
/*74 */ }                                                                                                       // 0.0
