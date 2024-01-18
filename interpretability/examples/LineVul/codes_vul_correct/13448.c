// commit message qemu@b5e751b51f (target=1, prob=0.7002113, correct=True): spice: init dcl before registering qxl interface
/*0  */ static void qemu_spice_display_init_one(QemuConsole *con)     // (3) 0.1028
/*2  */ {                                                             // (10) 0.004673
/*4  */     SimpleSpiceDisplay *ssd = g_new0(SimpleSpiceDisplay, 1);  // (1) 0.1075
/*8  */     qemu_spice_display_init_common(ssd);                      // (5) 0.08879
/*12 */     ssd->qxl.base.sif = &dpy_interface.base;                  // (2) 0.1075
/*14 */     qemu_spice_add_display_interface(&ssd->qxl, con);         // (0) 0.1168
/*16 */     assert(ssd->worker);                                      // (9) 0.04673
/*20 */     qemu_spice_create_host_memslot(ssd);                      // (4) 0.09813
/*24 */     ssd->dcl.ops = &display_listener_ops;                     // (6) 0.08879
/*26 */     ssd->dcl.con = con;                                       // (8) 0.06075
/*28 */     register_displaychangelistener(&ssd->dcl);                // (7) 0.07944
/*30 */ }                                                             // (11) 0.004673
