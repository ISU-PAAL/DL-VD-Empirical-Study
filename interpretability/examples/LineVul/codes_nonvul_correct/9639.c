// commit message qemu@bc210eb163 (target=0, prob=0.1316279, correct=True): pixman: fix vnc tight png/jpeg support
/*0  */ void qemu_pixman_linebuf_fill(pixman_image_t *linebuf, pixman_image_t *fb,  // (1) 0.2273
/*2  */                               int width, int y)                             // (2) 0.2273
/*4  */ {                                                                           // (4) 0.006494
/*6  */     pixman_image_composite(PIXMAN_OP_SRC, fb, NULL, linebuf,                // (3) 0.1948
/*8  */                            0, y, 0, 0, 0, 0, width, 1);                     // (0) 0.2727
/*10 */ }                                                                           // (5) 0.006494
