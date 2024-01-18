// commit message qemu@a8170e5e97 (target=0, prob=0.013333676, correct=True): Rename target_phys_addr_t to hwaddr
/*0 */ void isa_mmio_setup(MemoryRegion *mr, target_phys_addr_t size)         // (1) 0.3594
/*2 */ {                                                                      // (2) 0.01563
/*4 */     memory_region_init_io(mr, &isa_mmio_ops, NULL, "isa-mmio", size);  // (0) 0.4844
/*6 */ }                                                                      // (3) 0.01562
