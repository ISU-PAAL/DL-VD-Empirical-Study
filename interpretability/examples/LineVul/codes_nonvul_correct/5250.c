// commit message qemu@a8170e5e97 (target=0, prob=0.003838873, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ uint32_t omap_badwidth_read8(void *opaque, target_phys_addr_t addr)  // (0) 0.3
/*2  */ {                                                                    // (5) 0.01111
/*4  */     uint8_t ret;                                                     // (3) 0.1
/*8  */     OMAP_8B_REG(addr);                                               // (2) 0.1444
/*10 */     cpu_physical_memory_read(addr, (void *) &ret, 1);                // (1) 0.2333
/*12 */     return ret;                                                      // (4) 0.06667
/*14 */ }                                                                    // (6) 0.01111
