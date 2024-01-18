// commit message qemu@568c73a478 (target=0, prob=0.11210962, correct=True): input: Convert to new qapi union layout
/*0  */ static void qemu_chr_parse_vc(QemuOpts *opts, ChardevBackend *backend,  // (1) 0.07635
/*2  */                               Error **errp)                             // (0) 0.08374
/*4  */ {                                                                       // (24) 0.002463
/*6  */     int val;                                                            // (19) 0.01478
/*10 */     backend->vc = g_new0(ChardevVC, 1);                                 // (6) 0.0468
/*14 */     val = qemu_opt_get_number(opts, "width", 0);                        // (3) 0.05665
/*16 */     if (val != 0) {                                                     // (15) 0.02463
/*18 */         backend->vc->has_width = true;                                  // (8) 0.04187
/*20 */         backend->vc->width = val;                                       // (12) 0.03695
/*22 */     }                                                                   // (20) 0.009852
/*26 */     val = qemu_opt_get_number(opts, "height", 0);                       // (4) 0.05665
/*28 */     if (val != 0) {                                                     // (16) 0.02463
/*30 */         backend->vc->has_height = true;                                 // (9) 0.04187
/*32 */         backend->vc->height = val;                                      // (13) 0.03695
/*34 */     }                                                                   // (21) 0.009852
/*38 */     val = qemu_opt_get_number(opts, "cols", 0);                         // (2) 0.05911
/*40 */     if (val != 0) {                                                     // (17) 0.02463
/*42 */         backend->vc->has_cols = true;                                   // (7) 0.04433
/*44 */         backend->vc->cols = val;                                        // (11) 0.03941
/*46 */     }                                                                   // (22) 0.009852
/*50 */     val = qemu_opt_get_number(opts, "rows", 0);                         // (5) 0.05665
/*52 */     if (val != 0) {                                                     // (18) 0.02463
/*54 */         backend->vc->has_rows = true;                                   // (10) 0.04187
/*56 */         backend->vc->rows = val;                                        // (14) 0.03695
/*58 */     }                                                                   // (23) 0.009852
/*60 */ }                                                                       // (25) 0.002463
