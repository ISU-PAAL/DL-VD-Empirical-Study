// commit message qemu@a8170e5e97 (target=0, prob=0.006173955, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint32_t pmac_ide_readb (void *opaque,target_phys_addr_t addr)  // (0) 0.1222
/*2  */ {                                                                      // (18) 0.004525
/*4  */     uint8_t retval;                                                    // (6) 0.04525
/*6  */     MACIOIDEState *d = opaque;                                         // (5) 0.0543
/*10 */     addr = (addr & 0xFFF) >> 4;                                        // (3) 0.0724
/*12 */     switch (addr) {                                                    // (11) 0.0362
/*14 */     case 1 ... 7:                                                      // (10) 0.0362
/*16 */         retval = ide_ioport_read(&d->bus, addr);                       // (1) 0.1041
/*18 */         break;                                                         // (8) 0.04072
/*20 */     case 8:                                                            // (13) 0.02715
/*22 */     case 22:                                                           // (14) 0.02715
/*24 */         retval = ide_status_read(&d->bus, 0);                          // (2) 0.09955
/*26 */         break;                                                         // (9) 0.04072
/*28 */     default:                                                           // (15) 0.02262
/*30 */         retval = 0xFF;                                                 // (4) 0.06335
/*32 */         break;                                                         // (7) 0.04072
/*34 */     }                                                                  // (16) 0.0181
/*36 */     return retval;                                                     // (12) 0.03167
/*38 */ }                                                                      // (17) 0.004525
