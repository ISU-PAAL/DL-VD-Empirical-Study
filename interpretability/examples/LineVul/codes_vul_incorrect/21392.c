// commit message qemu@bdd4df332a (target=1, prob=0.48224735, correct=False): spice: fix initialization order
/*0  */ void qemu_spice_display_init(DisplayState *ds)              // (6) 0.09189
/*2  */ {                                                           // (9) 0.005405
/*4  */     assert(sdpy.ds == NULL);                                // (7) 0.06486
/*6  */     qemu_spice_display_init_common(&sdpy, ds);              // (2) 0.1189
/*8  */     register_displaychangelistener(ds, &display_listener);  // (4) 0.1027
/*12 */     sdpy.qxl.base.sif = &dpy_interface.base;                // (0) 0.1243
/*14 */     qemu_spice_add_interface(&sdpy.qxl.base);               // (1) 0.1243
/*16 */     assert(sdpy.worker);                                    // (8) 0.05405
/*20 */     qemu_spice_create_host_memslot(&sdpy);                  // (3) 0.1135
/*22 */     qemu_spice_create_host_primary(&sdpy);                  // (5) 0.1027
/*24 */ }                                                           // (10) 0.005405
