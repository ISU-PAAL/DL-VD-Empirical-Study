// commit message qemu@bdd81addf4 (target=1, prob=0.8889663, correct=True): vfio: Use g_new() & friends where that makes obvious sense
/*0  */ static void vfio_vga_probe_nvidia_3d0_quirk(VFIOPCIDevice *vdev)                 // (7) 0.06445
/*2  */ {                                                                                // (18) 0.001953
/*4  */     VFIOQuirk *quirk;                                                            // (13) 0.02344
/*6  */     VFIONvidia3d0Quirk *data;                                                    // (12) 0.0293
/*10 */     if (!vfio_pci_is(vdev, PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID) ||                  // (6) 0.06641
/*12 */         !vdev->bars[1].region.size) {                                            // (10) 0.03906
/*14 */         return;                                                                  // (16) 0.01758
/*16 */     }                                                                            // (17) 0.007812
/*20 */     quirk = g_malloc0(sizeof(*quirk));                                           // (11) 0.03516
/*22 */     quirk->data = data = g_malloc0(sizeof(*data));                               // (9) 0.04102
/*24 */     quirk->mem = g_malloc0(sizeof(MemoryRegion) * 2);                            // (8) 0.04492
/*26 */     quirk->nr_mem = 2;                                                           // (14) 0.02344
/*28 */     data->vdev = vdev;                                                           // (15) 0.02148
/*32 */     memory_region_init_io(&quirk->mem[0], OBJECT(vdev), &vfio_nvidia_3d4_quirk,  // (3) 0.07617
/*34 */                           data, "vfio-nvidia-3d4-quirk", 2);                     // (1) 0.08594
/*36 */     memory_region_add_subregion(&vdev->vga.region[QEMU_PCI_VGA_IO_HI].mem,       // (5) 0.07031
/*38 */                                 0x14 /* 0x3c0 + 0x14 */, &quirk->mem[0]);        // (0) 0.1055
/*42 */     memory_region_init_io(&quirk->mem[1], OBJECT(vdev), &vfio_nvidia_3d0_quirk,  // (4) 0.07617
/*44 */                           data, "vfio-nvidia-3d0-quirk", 2);                     // (2) 0.08594
/*46 */     memory_region_add_subregion(&vdev->vga.region[QEMU_PCI_VGA_IO_HI].mem,       // 0.0
/*48 */                                 0x10 /* 0x3c0 + 0x10 */, &quirk->mem[1]);        // 0.0
/*52 */     QLIST_INSERT_HEAD(&vdev->vga.region[QEMU_PCI_VGA_IO_HI].quirks,              // 0.0
/*54 */                       quirk, next);                                              // 0.0
/*58 */     trace_vfio_quirk_nvidia_3d0_probe(vdev->vbasedev.name);                      // 0.0
/*60 */ }                                                                                // 0.0
