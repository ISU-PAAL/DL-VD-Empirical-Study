// commit message qemu@d4cd450288 (target=0, prob=0.123409845, correct=True): xen-pt: fix Negative array index read
/*0  */ static XenPTBarFlag xen_pt_bar_reg_parse(XenPCIPassthroughState *s,             // (6) 0.05078
/*2  */                                          XenPTRegInfo *reg)                     // (0) 0.09375
/*4  */ {                                                                               // (25) 0.001953
/*6  */     PCIDevice *d = &s->dev;                                                     // (12) 0.0293
/*8  */     XenPTRegion *region = NULL;                                                 // (15) 0.02539
/*10 */     PCIIORegion *r;                                                             // (17) 0.02148
/*12 */     int index = 0;                                                              // (21) 0.01562
/*16 */     /* check 64bit BAR */                                                       // (19) 0.01758
/*18 */     index = xen_pt_bar_offset_to_index(reg->offset);                            // (9) 0.04102
/*20 */     if ((0 < index) && (index < PCI_ROM_SLOT)) {                                // (10) 0.04102
/*22 */         int type = s->real_device.io_regions[index - 1].type;                   // (5) 0.05273
/*26 */         if ((type & XEN_HOST_PCI_REGION_TYPE_MEM)                               // (4) 0.05469
/*28 */             && (type & XEN_HOST_PCI_REGION_TYPE_MEM_64)) {                      // (1) 0.06836
/*30 */             region = &s->bases[index - 1];                                      // (7) 0.04492
/*32 */             if (region->bar_flag != XEN_PT_BAR_FLAG_UPPER) {                    // (2) 0.06445
/*34 */                 return XEN_PT_BAR_FLAG_UPPER;                                   // (3) 0.05664
/*36 */             }                                                                   // (16) 0.02344
/*38 */         }                                                                       // (22) 0.01562
/*40 */     }                                                                           // (23) 0.007812
/*44 */     /* check unused BAR */                                                      // (20) 0.01563
/*46 */     r = &d->io_regions[index];                                                  // (13) 0.0293
/*48 */     if (!xen_pt_get_bar_size(r)) {                                              // (11) 0.03711
/*50 */         return XEN_PT_BAR_FLAG_UNUSED;                                          // (8) 0.04297
/*52 */     }                                                                           // (24) 0.007812
/*56 */     /* for ExpROM BAR */                                                        // (18) 0.01758
/*58 */     if (index == PCI_ROM_SLOT) {                                                // (14) 0.0293
/*60 */         return XEN_PT_BAR_FLAG_MEM;                                             // 0.0
/*62 */     }                                                                           // 0.0
/*66 */     /* check BAR I/O indicator */                                               // 0.0
/*68 */     if (s->real_device.io_regions[index].type & XEN_HOST_PCI_REGION_TYPE_IO) {  // 0.0
/*70 */         return XEN_PT_BAR_FLAG_IO;                                              // 0.0
/*72 */     } else {                                                                    // 0.0
/*74 */         return XEN_PT_BAR_FLAG_MEM;                                             // 0.0
/*76 */     }                                                                           // 0.0
/*78 */ }                                                                               // 0.0
