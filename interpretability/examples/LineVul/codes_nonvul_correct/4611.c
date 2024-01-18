// commit message qemu@27e0c9a1bb (target=0, prob=0.38630944, correct=True): ide: Add "model=s" qdev option
/*0   */ static void ide_atapi_identify(IDEState *s)                                       // (17) 0.0293
/*2   */ {                                                                                 // (24) 0.001953
/*4   */     uint16_t *p;                                                                  // (20) 0.01953
/*8   */     if (s->identify_set) {                                                        // (18) 0.02539
/*10  */ 	memcpy(s->io_buffer, s->identify_data, sizeof(s->identify_data));                // (3) 0.05273
/*12  */ 	return;                                                                          // (22) 0.005859
/*14  */     }                                                                             // (21) 0.007813
/*18  */     memset(s->io_buffer, 0, 512);                                                 // (16) 0.03125
/*20  */     p = (uint16_t *)s->io_buffer;                                                 // (15) 0.0332
/*22  */     /* Removable CDROM, 50us response, 12 byte packets */                         // (14) 0.0332
/*24  */     put_le16(p + 0, (2 << 14) | (5 << 8) | (1 << 7) | (2 << 5) | (0 << 0));       // (0) 0.08008
/*26  */     padstr((char *)(p + 10), s->drive_serial_str, 20); /* serial number */        // (4) 0.05273
/*28  */     put_le16(p + 20, 3); /* buffer type */                                        // (12) 0.03516
/*30  */     put_le16(p + 21, 512); /* cache size in sectors */                            // (11) 0.03906
/*32  */     put_le16(p + 22, 4); /* ecc bytes */                                          // (13) 0.03516
/*34  */     padstr((char *)(p + 23), s->version, 8); /* firmware version */               // (9) 0.04492
/*36  */     padstr((char *)(p + 27), "QEMU DVD-ROM", 40); /* model */                     // (6) 0.05078
/*38  */     put_le16(p + 48, 1); /* dword I/O (XXX: should not be set on CDROM) */        // (1) 0.0625
/*40  */ #ifdef USE_DMA_CDROM                                                              // (19) 0.02148
/*42  */     put_le16(p + 49, 1 << 9 | 1 << 8); /* DMA and LBA supported */                // (2) 0.05469
/*44  */     put_le16(p + 53, 7); /* words 64-70, 54-58, 88 valid */                       // (5) 0.05273
/*46  */     put_le16(p + 62, 7);  /* single word dma0-2 supported */                      // (7) 0.04883
/*48  */     put_le16(p + 63, 7);  /* mdma0-2 supported */                                 // (10) 0.04492
/*50  */ #else                                                                             // (23) 0.003906
/*52  */     put_le16(p + 49, 1 << 9); /* LBA supported, no DMA */                         // (8) 0.04883
/*54  */     put_le16(p + 53, 3); /* words 64-70, 54-58 valid */                           // 0.0
/*56  */     put_le16(p + 63, 0x103); /* DMA modes XXX: may be incorrect */                // 0.0
/*58  */ #endif                                                                            // 0.0
/*60  */     put_le16(p + 64, 3); /* pio3-4 supported */                                   // 0.0
/*62  */     put_le16(p + 65, 0xb4); /* minimum DMA multiword tx cycle time */             // 0.0
/*64  */     put_le16(p + 66, 0xb4); /* recommended DMA multiword tx cycle time */         // 0.0
/*66  */     put_le16(p + 67, 0x12c); /* minimum PIO cycle time without flow control */    // 0.0
/*68  */     put_le16(p + 68, 0xb4); /* minimum PIO cycle time with IORDY flow control */  // 0.0
/*72  */     put_le16(p + 71, 30); /* in ns */                                             // 0.0
/*74  */     put_le16(p + 72, 30); /* in ns */                                             // 0.0
/*78  */     if (s->ncq_queues) {                                                          // 0.0
/*80  */         put_le16(p + 75, s->ncq_queues - 1);                                      // 0.0
/*82  */         /* NCQ supported */                                                       // 0.0
/*84  */         put_le16(p + 76, (1 << 8));                                               // 0.0
/*86  */     }                                                                             // 0.0
/*90  */     put_le16(p + 80, 0x1e); /* support up to ATA/ATAPI-4 */                       // 0.0
/*92  */ #ifdef USE_DMA_CDROM                                                              // 0.0
/*94  */     put_le16(p + 88, 0x3f | (1 << 13)); /* udma5 set and supported */             // 0.0
/*96  */ #endif                                                                            // 0.0
/*98  */     memcpy(s->identify_data, p, sizeof(s->identify_data));                        // 0.0
/*100 */     s->identify_set = 1;                                                          // 0.0
/*102 */ }                                                                                 // 0.0
