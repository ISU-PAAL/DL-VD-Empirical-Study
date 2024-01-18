// commit message qemu@6750e795b1 (target=0, prob=0.36042526, correct=True): qemu-img: Suppress unhelpful extra errors in convert, resize
/*0  */ static int add_old_style_options(const char *fmt, QemuOpts *opts,            // (7) 0.06313
/*2  */                                  const char *base_filename,                  // (1) 0.09848
/*4  */                                  const char *base_fmt)                       // (0) 0.101
/*6  */ {                                                                            // (18) 0.002525
/*8  */     if (base_filename) {                                                     // (12) 0.02525
/*10 */         if (qemu_opt_set(opts, BLOCK_OPT_BACKING_FILE, base_filename)) {     // (3) 0.09091
/*12 */             error_report("Backing file not supported for file format '%s'",  // (5) 0.07071
/*14 */                          fmt);                                               // (6) 0.06566
/*16 */             return -1;                                                       // (9) 0.03788
/*18 */         }                                                                    // (13) 0.0202
/*20 */     }                                                                        // (16) 0.0101
/*22 */     if (base_fmt) {                                                          // (11) 0.02778
/*24 */         if (qemu_opt_set(opts, BLOCK_OPT_BACKING_FMT, base_fmt)) {           // (2) 0.09596
/*26 */             error_report("Backing file format not supported for file "       // (8) 0.06061
/*28 */                          "format '%s'", fmt);                                // (4) 0.08333
/*30 */             return -1;                                                       // (10) 0.03788
/*32 */         }                                                                    // (14) 0.0202
/*34 */     }                                                                        // (17) 0.0101
/*36 */     return 0;                                                                // (15) 0.01515
/*38 */ }                                                                            // (19) 0.002525
