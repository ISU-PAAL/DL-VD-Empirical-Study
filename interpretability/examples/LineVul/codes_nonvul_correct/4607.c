// commit message qemu@32bafa8fdd (target=0, prob=0.015130786, correct=True): qapi: Don't special-case simple union wrappers
/*0  */ static CharDriverState *qemu_chr_open_null(const char *id,           // (3) 0.07023
/*2  */                                            ChardevBackend *backend,  // (0) 0.1706
/*4  */                                            ChardevReturn *ret,       // (1) 0.1639
/*6  */                                            Error **errp)             // (2) 0.1572
/*8  */ {                                                                    // (13) 0.003344
/*10 */     CharDriverState *chr;                                            // (8) 0.03344
/*12 */     ChardevCommon *common = backend->u.null;                         // (6) 0.05351
/*16 */     chr = qemu_chr_alloc(common, errp);                              // (4) 0.06689
/*18 */     if (!chr) {                                                      // (10) 0.0301
/*20 */         return NULL;                                                 // (9) 0.03344
/*22 */     }                                                                // (12) 0.01338
/*24 */     chr->chr_write = null_chr_write;                                 // (5) 0.0602
/*26 */     chr->explicit_be_open = true;                                    // (7) 0.05017
/*28 */     return chr;                                                      // (11) 0.02341
/*30 */ }                                                                    // (14) 0.003344
