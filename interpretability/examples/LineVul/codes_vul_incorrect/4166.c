// commit message qemu@4508d81a78 (target=1, prob=0.09222043, correct=False): ppc405_uc: fix a buffer overflow
/*0  */ ram_addr_t ppc405_set_bootinfo (CPUState *env, ppc4xx_bd_info_t *bd,  // (2) 0.0625
/*2  */                                 uint32_t flags)                       // (0) 0.07227
/*4  */ {                                                                     // (21) 0.001953
/*6  */     ram_addr_t bdloc;                                                 // (18) 0.02344
/*8  */     int i, n;                                                         // (19) 0.01562
/*12 */     /* We put the bd structure at the top of memory */                // (16) 0.03125
/*14 */     if (bd->bi_memsize >= 0x01000000UL)                               // (15) 0.03711
/*16 */         bdloc = 0x01000000UL - sizeof(struct ppc4xx_bd_info_t);       // (4) 0.06055
/*18 */     else                                                              // (20) 0.007812
/*20 */         bdloc = bd->bi_memsize - sizeof(struct ppc4xx_bd_info_t);     // (1) 0.06641
/*22 */     stl_phys(bdloc + 0x00, bd->bi_memstart);                          // (11) 0.04492
/*24 */     stl_phys(bdloc + 0x04, bd->bi_memsize);                           // (5) 0.04688
/*26 */     stl_phys(bdloc + 0x08, bd->bi_flashstart);                        // (12) 0.04492
/*28 */     stl_phys(bdloc + 0x0C, bd->bi_flashsize);                         // (6) 0.04688
/*30 */     stl_phys(bdloc + 0x10, bd->bi_flashoffset);                       // (13) 0.04492
/*32 */     stl_phys(bdloc + 0x14, bd->bi_sramstart);                         // (7) 0.04688
/*34 */     stl_phys(bdloc + 0x18, bd->bi_sramsize);                          // (8) 0.04688
/*36 */     stl_phys(bdloc + 0x1C, bd->bi_bootflags);                         // (9) 0.04688
/*38 */     stl_phys(bdloc + 0x20, bd->bi_ipaddr);                            // (14) 0.04492
/*40 */     for (i = 0; i < 6; i++)                                           // (17) 0.0293
/*42 */         stb_phys(bdloc + 0x24 + i, bd->bi_enetaddr[i]);               // (3) 0.0625
/*44 */     stw_phys(bdloc + 0x2A, bd->bi_ethspeed);                          // (10) 0.04688
/*46 */     stl_phys(bdloc + 0x2C, bd->bi_intfreq);                           // 0.0
/*48 */     stl_phys(bdloc + 0x30, bd->bi_busfreq);                           // 0.0
/*50 */     stl_phys(bdloc + 0x34, bd->bi_baudrate);                          // 0.0
/*52 */     for (i = 0; i < 4; i++)                                           // 0.0
/*54 */         stb_phys(bdloc + 0x38 + i, bd->bi_s_version[i]);              // 0.0
/*56 */     for (i = 0; i < 32; i++)                                          // 0.0
/*58 */         stb_phys(bdloc + 0x3C + i, bd->bi_s_version[i]);              // 0.0
/*60 */     stl_phys(bdloc + 0x5C, bd->bi_plb_busfreq);                       // 0.0
/*62 */     stl_phys(bdloc + 0x60, bd->bi_pci_busfreq);                       // 0.0
/*64 */     for (i = 0; i < 6; i++)                                           // 0.0
/*66 */         stb_phys(bdloc + 0x64 + i, bd->bi_pci_enetaddr[i]);           // 0.0
/*68 */     n = 0x6A;                                                         // 0.0
/*70 */     if (flags & 0x00000001) {                                         // 0.0
/*72 */         for (i = 0; i < 6; i++)                                       // 0.0
/*74 */             stb_phys(bdloc + n++, bd->bi_pci_enetaddr2[i]);           // 0.0
/*76 */     }                                                                 // 0.0
/*78 */     stl_phys(bdloc + n, bd->bi_opbfreq);                              // 0.0
/*80 */     n += 4;                                                           // 0.0
/*82 */     for (i = 0; i < 2; i++) {                                         // 0.0
/*84 */         stl_phys(bdloc + n, bd->bi_iic_fast[i]);                      // 0.0
/*86 */         n += 4;                                                       // 0.0
/*88 */     }                                                                 // 0.0
/*92 */     return bdloc;                                                     // 0.0
/*94 */ }                                                                     // 0.0
