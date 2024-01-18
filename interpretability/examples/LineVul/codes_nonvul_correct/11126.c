// commit message qemu@a8170e5e97 (target=0, prob=0.005253232, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint32_t pci_apb_ioreadl (void *opaque, target_phys_addr_t addr)  // (0) 0.358
/*2  */ {                                                                        // (4) 0.01235
/*4  */     uint32_t val;                                                        // (2) 0.1111
/*8  */     val = bswap32(cpu_inl(addr & IOPORTS_MASK));                         // (1) 0.2963
/*10 */     return val;                                                          // (3) 0.07407
/*12 */ }                                                                        // (5) 0.01235
