// commit message qemu@33577b47c6 (target=0, prob=0.3662415, correct=True): replay: character devices
/*0  */ CharDriverState *qemu_chr_new(const char *label, const char *filename, void (*init)(struct CharDriverState *s))  // (0) 0.1037
/*2  */ {                                                                                                                // (20) 0.003049
/*4  */     const char *p;                                                                                               // (13) 0.02439
/*6  */     CharDriverState *chr;                                                                                        // (10) 0.03049
/*8  */     QemuOpts *opts;                                                                                              // (9) 0.03659
/*10 */     Error *err = NULL;                                                                                           // (12) 0.02744
/*14 */     if (strstart(filename, "chardev:", &p)) {                                                                    // (6) 0.05793
/*16 */         return qemu_chr_find(p);                                                                                 // (7) 0.05793
/*18 */     }                                                                                                            // (17) 0.0122
/*22 */     opts = qemu_chr_parse_compat(label, filename);                                                               // (5) 0.06707
/*24 */     if (!opts)                                                                                                   // (14) 0.02439
/*26 */         return NULL;                                                                                             // (11) 0.03049
/*30 */     chr = qemu_chr_new_from_opts(opts, init, &err);                                                              // (2) 0.08537
/*32 */     if (err) {                                                                                                   // (15) 0.02439
/*34 */         error_report_err(err);                                                                                   // (8) 0.04573
/*36 */     }                                                                                                            // (18) 0.0122
/*38 */     if (chr && qemu_opt_get_bool(opts, "mux", 0)) {                                                              // (1) 0.08537
/*40 */         qemu_chr_fe_claim_no_fail(chr);                                                                          // (3) 0.07622
/*42 */         monitor_init(chr, MONITOR_USE_READLINE);                                                                 // (4) 0.07012
/*44 */     }                                                                                                            // (19) 0.0122
/*46 */     return chr;                                                                                                  // (16) 0.02134
/*48 */ }                                                                                                                // (21) 0.003049
