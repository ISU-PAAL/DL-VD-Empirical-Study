// commit message qemu@3a51dee658 (target=0, prob=0.19403517, correct=True): disabled signal hacks for softmmu version (qemu should be much more portable now...)
/*0  */ static void ide_identify(IDEState *s)                  // (24) 0.02344
/*2  */ {                                                      // (29) 0.001953
/*4  */     uint16_t *p;                                       // (26) 0.01953
/*6  */     unsigned int oldsize;                              // (27) 0.01563
/*10 */     memset(s->io_buffer, 0, 512);                      // (10) 0.03125
/*12 */     p = (uint16_t *)s->io_buffer;                      // (9) 0.0332
/*14 */     stw(p + 0, 0x0040);                                // (18) 0.0293
/*16 */     stw(p + 1, s->cylinders);                          // (12) 0.03125
/*18 */     stw(p + 3, s->heads);                              // (21) 0.02734
/*20 */     stw(p + 4, 512 * s->sectors); /* sectors */        // (3) 0.03906
/*22 */     stw(p + 5, 512); /* sector size */                 // (15) 0.03125
/*24 */     stw(p + 6, s->sectors);                            // (16) 0.03125
/*26 */     stw(p + 20, 3); /* buffer type */                  // (13) 0.03125
/*28 */     stw(p + 21, 512); /* cache size in sectors */      // (8) 0.03516
/*30 */     stw(p + 22, 4); /* ecc bytes */                    // (11) 0.03125
/*32 */     padstr((uint8_t *)(p + 27), "QEMU HARDDISK", 40);  // (0) 0.05273
/*34 */ #if MAX_MULT_SECTORS > 1                               // (14) 0.03125
/*36 */     stw(p + 47, MAX_MULT_SECTORS);                     // (7) 0.03711
/*38 */ #endif                                                 // (28) 0.003906
/*40 */     stw(p + 48, 1); /* dword I/O */                    // (6) 0.03711
/*42 */     stw(p + 49, 1 << 9); /* LBA supported, no DMA */   // (1) 0.04492
/*44 */     stw(p + 51, 0x200); /* PIO transfer cycle */       // (4) 0.03906
/*46 */     stw(p + 52, 0x200); /* DMA transfer cycle */       // (5) 0.03906
/*48 */     stw(p + 54, s->cylinders);                         // (17) 0.0293
/*50 */     stw(p + 55, s->heads);                             // (22) 0.02734
/*52 */     stw(p + 56, s->sectors);                           // (19) 0.0293
/*54 */     oldsize = s->cylinders * s->heads * s->sectors;    // (2) 0.03906
/*56 */     stw(p + 57, oldsize);                              // (23) 0.02539
/*58 */     stw(p + 58, oldsize >> 16);                        // (20) 0.0293
/*60 */     if (s->mult_sectors)                               // (25) 0.02344
/*62 */         stw(p + 59, 0x100 | s->mult_sectors);          // 0.0
/*64 */     stw(p + 60, s->nb_sectors);                        // 0.0
/*66 */     stw(p + 61, s->nb_sectors >> 16);                  // 0.0
/*68 */     stw(p + 80, (1 << 1) | (1 << 2));                  // 0.0
/*70 */     stw(p + 82, (1 << 14));                            // 0.0
/*72 */     stw(p + 83, (1 << 14));                            // 0.0
/*74 */     stw(p + 84, (1 << 14));                            // 0.0
/*76 */     stw(p + 85, (1 << 14));                            // 0.0
/*78 */     stw(p + 86, 0);                                    // 0.0
/*80 */     stw(p + 87, (1 << 14));                            // 0.0
/*82 */ }                                                      // 0.0
