// commit message qemu@d0d7708ba2 (target=0, prob=0.061938208, correct=True): qemu-char: add logfile facility to all chardev backends
/*0  */ static CharDriverState *qemu_chr_open_pipe(const char *id,           // (4) 0.05263
/*2  */                                            ChardevBackend *backend,  // (0) 0.1278
/*4  */                                            ChardevReturn *ret,       // (1) 0.1228
/*6  */                                            Error **errp)             // (2) 0.1178
/*8  */ {                                                                    // (19) 0.002506
/*10 */     ChardevHostdev *opts = backend->u.pipe;                          // (5) 0.04511
/*12 */     const char *filename = opts->device;                             // (11) 0.03258
/*14 */     CharDriverState *chr;                                            // (14) 0.02506
/*16 */     WinCharState *s;                                                 // (16) 0.02256
/*20 */     chr = qemu_chr_alloc();                                          // (9) 0.03759
/*22 */     s = g_new0(WinCharState, 1);                                     // (8) 0.0401
/*24 */     chr->opaque = s;                                                 // (13) 0.02757
/*26 */     chr->chr_write = win_chr_write;                                  // (6) 0.04511
/*28 */     chr->chr_close = win_chr_close;                                  // (7) 0.04511
/*32 */     if (win_chr_pipe_init(chr, filename, errp) < 0) {                // (3) 0.06516
/*34 */         g_free(s);                                                   // (12) 0.03258
/*36 */         g_free(chr);                                                 // (10) 0.03509
/*38 */         return NULL;                                                 // (15) 0.02506
/*40 */     }                                                                // (18) 0.01003
/*42 */     return chr;                                                      // (17) 0.01754
/*44 */ }                                                                    // (20) 0.002506
