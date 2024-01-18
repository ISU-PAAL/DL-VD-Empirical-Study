// commit message qemu@198a0039c5 (target=1, prob=0.21261396, correct=False): vnc: rework VncState release workflow.
/*0  */ static void vnc_dpy_copy(DisplayState *ds, int src_x, int src_y, int dst_x, int dst_y, int w, int h)  // (0) 0.1822
/*2  */ {                                                                                                     // (10) 0.004444
/*4  */     VncDisplay *vd = ds->opaque;                                                                      // (4) 0.06667
/*6  */     VncState *vs = vd->clients;                                                                       // (5) 0.06667
/*8  */     while (vs != NULL) {                                                                              // (8) 0.04444
/*10 */         if (vnc_has_feature(vs, VNC_FEATURE_COPYRECT))                                                // (3) 0.1289
/*12 */             vnc_copy(vs, src_x, src_y, dst_x, dst_y, w, h);                                           // (1) 0.1689
/*14 */         else /* TODO */                                                                               // (7) 0.05333
/*16 */             vnc_update(vs, dst_x, dst_y, w, h);                                                       // (2) 0.1333
/*18 */         vs = vs->next;                                                                                // (6) 0.05778
/*20 */     }                                                                                                 // (9) 0.01778
/*22 */ }                                                                                                     // (11) 0.004444
