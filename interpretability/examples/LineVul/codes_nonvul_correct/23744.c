// commit message qemu@b6ce27a593 (target=0, prob=0.14024837, correct=True): virtio-pci: fill VirtIOPCIRegions early.
/*0  */ static void virtio_pci_modern_region_map(VirtIOPCIProxy *proxy,       // (5) 0.07516
/*2  */                                          VirtIOPCIRegion *region,     // (1) 0.1634
/*4  */                                          struct virtio_pci_cap *cap)  // (0) 0.1667
/*6  */ {                                                                     // (10) 0.003268
/*8  */     memory_region_add_subregion(&proxy->modern_bar,                   // (7) 0.05882
/*10 */                                 region->offset,                       // (3) 0.1144
/*12 */                                 &region->mr);                         // (2) 0.1176
/*16 */     cap->cfg_type = region->type;                                     // (9) 0.04248
/*18 */     cap->offset = cpu_to_le32(region->offset);                        // (8) 0.05882
/*20 */     cap->length = cpu_to_le32(memory_region_size(&region->mr));       // (4) 0.07843
/*22 */     virtio_pci_add_mem_cap(proxy, cap);                               // (6) 0.06209
/*24 */ }                                                                     // (11) 0.003268
