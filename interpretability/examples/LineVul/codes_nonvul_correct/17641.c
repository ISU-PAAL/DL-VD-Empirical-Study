// commit message qemu@733f0b02c8 (target=0, prob=0.014426832, correct=True): qemu: address todo comment in exec.c
/*0 */ void stw_phys(target_phys_addr_t addr, uint32_t val)          // (1) 0.2877
/*2 */ {                                                             // (4) 0.0137
/*4 */     uint16_t v = tswap16(val);                                // (2) 0.2192
/*6 */     cpu_physical_memory_write(addr, (const uint8_t *)&v, 2);  // (0) 0.3425
/*8 */ }                                                             // (3) 0.0137
