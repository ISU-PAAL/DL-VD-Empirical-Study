// commit message qemu@b0457b6920 (target=0, prob=0.013440415, correct=True): Fix/remove bogus ram size checks.
/*0  */ static void pxa2xx_descriptor_load(struct pxa2xx_lcdc_s *s)              // (9) 0.05273
/*2  */ {                                                                        // (20) 0.001953
/*4  */     struct pxa_frame_descriptor_s desc;                                  // (14) 0.03125
/*6  */     target_phys_addr_t descptr;                                          // (15) 0.02539
/*8  */     int i;                                                               // (19) 0.01172
/*12 */     for (i = 0; i < PXA_LCDDMA_CHANS; i ++) {                            // (11) 0.05078
/*14 */         s->dma_ch[i].source = 0;                                         // (12) 0.03906
/*18 */         if (!s->dma_ch[i].up)                                            // (13) 0.03906
/*20 */             continue;                                                    // (16) 0.02539
/*24 */         if (s->dma_ch[i].branch & FBR_BRA) {                             // (8) 0.05469
/*26 */             descptr = s->dma_ch[i].branch & FBR_SRCADDR;                 // (1) 0.06641
/*28 */             if (s->dma_ch[i].branch & FBR_BINT)                          // (2) 0.06055
/*30 */                 pxa2xx_dma_bs_set(s, i);                                 // (3) 0.06055
/*32 */             s->dma_ch[i].branch &= ~FBR_BRA;                             // (4) 0.06055
/*34 */         } else                                                           // (18) 0.01758
/*36 */             descptr = s->dma_ch[i].descriptor;                           // (10) 0.05273
/*40 */         if (!(descptr >= PXA2XX_SDRAM_BASE && descptr +                  // (6) 0.05664
/*42 */                     sizeof(desc) <= PXA2XX_SDRAM_BASE + phys_ram_size))  // (0) 0.08398
/*44 */             continue;                                                    // (17) 0.02539
/*48 */         cpu_physical_memory_read(descptr, (void *)&desc, sizeof(desc));  // (7) 0.05469
/*50 */         s->dma_ch[i].descriptor = tswap32(desc.fdaddr);                  // (5) 0.05859
/*52 */         s->dma_ch[i].source = tswap32(desc.fsaddr);                      // 0.0
/*54 */         s->dma_ch[i].id = tswap32(desc.fidr);                            // 0.0
/*56 */         s->dma_ch[i].command = tswap32(desc.ldcmd);                      // 0.0
/*58 */     }                                                                    // 0.0
/*60 */ }                                                                        // 0.0
