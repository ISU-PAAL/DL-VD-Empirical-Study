// commit message qemu@a8170e5e97 (target=0, prob=0.0048956145, correct=True): Rename target_phys_addr_t to hwaddr
/*0 */ void cpu_physical_memory_rw(target_phys_addr_t addr, uint8_t *buf,             // (2) 0.2577
/*2 */                             int len, int is_write)                             // (0) 0.3608
/*4 */ {                                                                              // (3) 0.01031
/*6 */     return address_space_rw(&address_space_memory, addr, buf, len, is_write);  // (1) 0.268
/*8 */ }                                                                              // (4) 0.01031
