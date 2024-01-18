// commit message qemu@2d528d45ec (target=1, prob=0.13198245, correct=False): qemu-char: Use g_new() & friends where that makes obvious sense
/*0  */ static CharDriverState *qemu_chr_open_pipe(ChardevHostdev *opts)  // (0) 0.1073
/*2  */ {                                                                 // (15) 0.004292
/*4  */     const char *filename = opts->device;                          // (7) 0.05579
/*6  */     CharDriverState *chr;                                         // (10) 0.04292
/*8  */     WinCharState *s;                                              // (12) 0.03863
/*12 */     chr = qemu_chr_alloc();                                       // (5) 0.06438
/*14 */     s = g_malloc0(sizeof(WinCharState));                          // (2) 0.07725
/*16 */     chr->opaque = s;                                              // (9) 0.04721
/*18 */     chr->chr_write = win_chr_write;                               // (3) 0.07725
/*20 */     chr->chr_close = win_chr_close;                               // (4) 0.07725
/*24 */     if (win_chr_pipe_init(chr, filename) < 0) {                   // (1) 0.09871
/*26 */         g_free(s);                                                // (8) 0.05579
/*28 */         g_free(chr);                                              // (6) 0.06009
/*30 */         return NULL;                                              // (11) 0.04292
/*32 */     }                                                             // (14) 0.01717
/*34 */     return chr;                                                   // (13) 0.03004
/*36 */ }                                                                 // (16) 0.004292
