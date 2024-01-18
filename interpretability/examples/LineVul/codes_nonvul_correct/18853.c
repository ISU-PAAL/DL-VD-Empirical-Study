// commit message qemu@a8170e5e97 (target=0, prob=0.0046554594, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint64_t cmd646_cmd_read(void *opaque, target_phys_addr_t addr,  // (1) 0.1699
/*2  */                                 unsigned size)                          // (0) 0.2222
/*4  */ {                                                                       // (7) 0.006536
/*6  */     CMD646BAR *cmd646bar = opaque;                                      // (4) 0.09804
/*10 */     if (addr != 2 || size != 1) {                                       // (5) 0.0915
/*12 */         return ((uint64_t)1 << (size * 8)) - 1;                         // (2) 0.1569
/*14 */     }                                                                   // (6) 0.02614
/*16 */     return ide_status_read(cmd646bar->bus, addr + 2);                   // (3) 0.1307
/*18 */ }                                                                       // (8) 0.006536
