// commit message qemu@a8170e5e97 (target=0, prob=0.006214775, correct=True): Rename target_phys_addr_t to hwaddr
/*0 */ void address_space_write(AddressSpace *as, target_phys_addr_t addr,  // (2) 0.2283
/*2 */                          const uint8_t *buf, int len)                // (0) 0.3804
/*4 */ {                                                                    // (3) 0.01087
/*6 */     address_space_rw(as, addr, (uint8_t *)buf, len, true);           // (1) 0.2717
/*8 */ }                                                                    // (4) 0.01087
