// commit message qemu@a8170e5e97 (target=0, prob=0.0048108874, correct=True): Rename target_phys_addr_t to hwaddr
/*0 */ void stq_be_phys(target_phys_addr_t addr, uint64_t val)  // (0) 0.3485
/*2 */ {                                                        // (4) 0.01515
/*4 */     val = cpu_to_be64(val);                              // (2) 0.2121
/*6 */     cpu_physical_memory_write(addr, &val, 8);            // (1) 0.2727
/*8 */ }                                                        // (3) 0.01515
