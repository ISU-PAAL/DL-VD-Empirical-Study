// commit message qemu@e774a278d8 (target=0, prob=0.15841115, correct=True): -win2k-hack performance+DMA support (Leonardo E. Reiter)
/*0  */ static void ide_sector_write(IDEState *s)                                   // (19) 0.02539
/*2  */ {                                                                           // (31) 0.001953
/*4  */     int64_t sector_num;                                                     // (22) 0.02148
/*6  */     int ret, n, n1;                                                         // (21) 0.02148
/*10 */     s->status = READY_STAT | SEEK_STAT;                                     // (12) 0.0332
/*12 */     sector_num = ide_get_sector(s);                                         // (14) 0.0293
/*14 */ #if defined(DEBUG_IDE)                                                      // (26) 0.01563
/*16 */     printf("write sector=%Ld\n", sector_num);                               // (9) 0.03516
/*18 */ #endif                                                                      // (30) 0.003906
/*20 */     n = s->nsector;                                                         // (23) 0.01953
/*22 */     if (n > s->req_nb_sectors)                                              // (13) 0.03125
/*24 */         n = s->req_nb_sectors;                                              // (10) 0.03516
/*26 */     ret = bdrv_write(s->bs, sector_num, s->io_buffer, n);                   // (1) 0.05273
/*28 */     s->nsector -= n;                                                        // (24) 0.01953
/*30 */     if (s->nsector == 0) {                                                  // (20) 0.02539
/*32 */         /* no more sector to write */                                       // (17) 0.02734
/*34 */         ide_transfer_stop(s);                                               // (15) 0.0293
/*36 */     } else {                                                                // (27) 0.01172
/*38 */         n1 = s->nsector;                                                    // (16) 0.0293
/*40 */         if (n1 > s->req_nb_sectors)                                         // (7) 0.04102
/*42 */             n1 = s->req_nb_sectors;                                         // (4) 0.04492
/*44 */         ide_transfer_start(s, s->io_buffer, 512 * n1, ide_sector_write);    // (0) 0.0625
/*46 */     }                                                                       // (29) 0.007813
/*48 */     ide_set_sector(s, sector_num + n);                                      // (11) 0.0332
/*50 */                                                                             // (28) 0.007813
/*52 */ #ifdef TARGET_I386                                                          // (25) 0.01563
/*54 */     if (win2k_install_hack) {                                               // (18) 0.02734
/*56 */         /* It seems there is a bug in the Windows 2000 installer HDD        // (8) 0.03906
/*58 */            IDE driver which fills the disk with empty logs when the         // (5) 0.04102
/*60 */            IDE write IRQ comes too early. This hack tries to correct        // (3) 0.04492
/*62 */            that at the expense of slower write performances. Use this       // (6) 0.04102
/*64 */            option _only_ to install Windows 2000. You must disable it       // (2) 0.04492
/*66 */            for normal use. */                                               // 0.0
/*68 */         qemu_mod_timer(s->sector_write_timer,                               // 0.0
/*70 */                        qemu_get_clock(vm_clock) + (ticks_per_sec / 1000));  // 0.0
/*72 */     } else                                                                  // 0.0
/*74 */ #endif                                                                      // 0.0
/*76 */     {                                                                       // 0.0
/*78 */         ide_set_irq(s);                                                     // 0.0
/*80 */     }                                                                       // 0.0
/*82 */ }                                                                           // 0.0
