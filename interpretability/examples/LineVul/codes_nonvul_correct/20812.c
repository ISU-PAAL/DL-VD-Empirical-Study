// commit message qemu@a8170e5e97 (target=0, prob=0.0067370464, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static void bw_conf1_write(void *opaque, target_phys_addr_t addr,  // (1) 0.2424
/*2  */                            uint64_t val, unsigned size)            // (0) 0.3535
/*4  */ {                                                                  // (4) 0.0101
/*6  */     PCIBus *b = opaque;                                            // (3) 0.1111
/*8  */     pci_data_write(b, addr, val, size);                            // (2) 0.1717
/*10 */ }                                                                  // (5) 0.0101
