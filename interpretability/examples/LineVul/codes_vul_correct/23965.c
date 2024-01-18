// commit message qemu@bdd81addf4 (target=1, prob=0.7446391, correct=True): vfio: Use g_new() & friends where that makes obvious sense
/*0  */ static void vfio_probe_nvidia_bar0_quirk(VFIOPCIDevice *vdev, int nr)         // (5) 0.06445
/*2  */ {                                                                             // (20) 0.001953
/*4  */     VFIOQuirk *quirk;                                                         // (13) 0.02344
/*6  */     VFIOConfigMirrorQuirk *mirror;                                            // (12) 0.0293
/*10 */     if (!vfio_pci_is(vdev, PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID) ||               // (4) 0.06641
/*12 */         !vfio_is_vga(vdev) || nr != 0) {                                      // (6) 0.05273
/*14 */         return;                                                               // (18) 0.01758
/*16 */     }                                                                         // (19) 0.007812
/*20 */     quirk = g_malloc0(sizeof(*quirk));                                        // (11) 0.03516
/*22 */     mirror = quirk->data = g_malloc0(sizeof(*mirror));                        // (9) 0.04297
/*24 */     mirror->mem = quirk->mem = g_malloc0(sizeof(MemoryRegion));               // (8) 0.04688
/*26 */     quirk->nr_mem = 1;                                                        // (14) 0.02344
/*28 */     mirror->vdev = vdev;                                                      // (16) 0.02148
/*30 */     mirror->offset = 0x88000;                                                 // (15) 0.02344
/*32 */     mirror->bar = nr;                                                         // (17) 0.01953
/*36 */     memory_region_init_io(mirror->mem, OBJECT(vdev),                          // (10) 0.04297
/*38 */                           &vfio_nvidia_mirror_quirk, mirror,                  // (2) 0.08008
/*40 */                           "vfio-nvidia-bar0-88000-mirror-quirk",              // (1) 0.08789
/*42 */                           PCIE_CONFIG_SPACE_SIZE);                            // (3) 0.07031
/*44 */     memory_region_add_subregion_overlap(&vdev->bars[nr].region.mem,           // (7) 0.05078
/*46 */                                         mirror->offset, mirror->mem, 1);      // (0) 0.0957
/*50 */     QLIST_INSERT_HEAD(&vdev->bars[nr].quirks, quirk, next);                   // 0.0
/*54 */     /* The 0x1800 offset mirror only seems to get used by legacy VGA */       // 0.0
/*56 */     if (vdev->has_vga) {                                                      // 0.0
/*58 */         quirk = g_malloc0(sizeof(*quirk));                                    // 0.0
/*60 */         mirror = quirk->data = g_malloc0(sizeof(*mirror));                    // 0.0
/*62 */         mirror->mem = quirk->mem = g_malloc0(sizeof(MemoryRegion));           // 0.0
/*64 */         quirk->nr_mem = 1;                                                    // 0.0
/*66 */         mirror->vdev = vdev;                                                  // 0.0
/*68 */         mirror->offset = 0x1800;                                              // 0.0
/*70 */         mirror->bar = nr;                                                     // 0.0
/*74 */         memory_region_init_io(mirror->mem, OBJECT(vdev),                      // 0.0
/*76 */                               &vfio_nvidia_mirror_quirk, mirror,              // 0.0
/*78 */                               "vfio-nvidia-bar0-1800-mirror-quirk",           // 0.0
/*80 */                               PCI_CONFIG_SPACE_SIZE);                         // 0.0
/*82 */         memory_region_add_subregion_overlap(&vdev->bars[nr].region.mem,       // 0.0
/*84 */                                             mirror->offset, mirror->mem, 1);  // 0.0
/*88 */         QLIST_INSERT_HEAD(&vdev->bars[nr].quirks, quirk, next);               // 0.0
/*90 */     }                                                                         // 0.0
/*94 */     trace_vfio_quirk_nvidia_bar0_probe(vdev->vbasedev.name);                  // 0.0
/*96 */ }                                                                             // 0.0
