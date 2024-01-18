// commit message qemu@a2d4e44b48 (target=1, prob=0.34612292, correct=False): Fix PCI config space overflow, by Herbert Xu.
/*0   */ void pci_default_write_config(PCIDevice *d,                                     // (11) 0.03323
/*2   */                               uint32_t address, uint32_t val, int len)          // (0) 0.08584
/*4   */ {                                                                               // (26) 0.00196
/*6   */     int can_write, i;                                                           // (20) 0.0197
/*8   */     uint32_t end, addr;                                                         // (19) 0.0215
/*12  */     if (len == 4 && ((address >= 0x10 && address < 0x10 + 4 * 6) ||             // (3) 0.05463
/*14  */                      (address >= 0x30 && address < 0x34))) {                    // (1) 0.06632
/*16  */         PCIIORegion *r;                                                         // (16) 0.02926
/*18  */         int reg;                                                                // (21) 0.01951
/*22  */         if ( address >= 0x30 ) {                                                // (15) 0.03121
/*24  */             reg = PCI_ROM_SLOT;                                                 // (7) 0.03901
/*26  */         }else{                                                                  // (22) 0.01951
/*28  */             reg = (address - 0x10) >> 2;                                        // (5) 0.04486
/*30  */         }                                                                       // (25) 0.0156
/*32  */         r = &d->io_regions[reg];                                                // (9) 0.03706
/*34  */         if (r->size == 0)                                                       // (17) 0.02926
/*36  */             goto default_config;                                                // (14) 0.03122
/*38  */         /* compute the stored value */                                          // (18) 0.02536
/*40  */         if (reg == PCI_ROM_SLOT) {                                              // (8) 0.03706
/*42  */             /* keep ROM enable bit */                                           // (12) 0.03317
/*44  */             val &= (~(r->size - 1)) | 1;                                        // (4) 0.04877
/*46  */         } else {                                                                // (23) 0.01951
/*48  */             val &= ~(r->size - 1);                                              // (6) 0.04292
/*50  */             val |= r->type;                                                     // (10) 0.03511
/*52  */         }                                                                       // (24) 0.01561
/*54  */         *(uint32_t *)(d->config + address) = cpu_to_le32(val);                  // (2) 0.06129
/*56  */         pci_update_mappings(d);                                                 // (13) 0.03123
/*58  */         return;                                                                 // 0.0
/*60  */     }                                                                           // 0.0
/*62  */  default_config:                                                                // 0.0
/*64  */     /* not efficient, but simple */                                             // 0.0
/*66  */     addr = address;                                                             // 0.0
/*68  */     for(i = 0; i < len; i++) {                                                  // 0.0
/*70  */         /* default read/write accesses */                                       // 0.0
/*72  */         switch(d->config[0x0e]) {                                               // 0.0
/*74  */         case 0x00:                                                              // 0.0
/*76  */         case 0x80:                                                              // 0.0
/*78  */             switch(addr) {                                                      // 0.0
/*80  */             case 0x00:                                                          // 0.0
/*82  */             case 0x01:                                                          // 0.0
/*84  */             case 0x02:                                                          // 0.0
/*86  */             case 0x03:                                                          // 0.0
/*88  */             case 0x08:                                                          // 0.0
/*90  */             case 0x09:                                                          // 0.0
/*92  */             case 0x0a:                                                          // 0.0
/*94  */             case 0x0b:                                                          // 0.0
/*96  */             case 0x0e:                                                          // 0.0
/*98  */             case 0x10 ... 0x27: /* base */                                      // 0.0
/*100 */             case 0x30 ... 0x33: /* rom */                                       // 0.0
/*102 */             case 0x3d:                                                          // 0.0
/*104 */                 can_write = 0;                                                  // 0.0
/*106 */                 break;                                                          // 0.0
/*108 */             default:                                                            // 0.0
/*110 */                 can_write = 1;                                                  // 0.0
/*112 */                 break;                                                          // 0.0
/*114 */             }                                                                   // 0.0
/*116 */             break;                                                              // 0.0
/*118 */         default:                                                                // 0.0
/*120 */         case 0x01:                                                              // 0.0
/*122 */             switch(addr) {                                                      // 0.0
/*124 */             case 0x00:                                                          // 0.0
/*126 */             case 0x01:                                                          // 0.0
/*128 */             case 0x02:                                                          // 0.0
/*130 */             case 0x03:                                                          // 0.0
/*132 */             case 0x08:                                                          // 0.0
/*134 */             case 0x09:                                                          // 0.0
/*136 */             case 0x0a:                                                          // 0.0
/*138 */             case 0x0b:                                                          // 0.0
/*140 */             case 0x0e:                                                          // 0.0
/*142 */             case 0x38 ... 0x3b: /* rom */                                       // 0.0
/*144 */             case 0x3d:                                                          // 0.0
/*146 */                 can_write = 0;                                                  // 0.0
/*148 */                 break;                                                          // 0.0
/*150 */             default:                                                            // 0.0
/*152 */                 can_write = 1;                                                  // 0.0
/*154 */                 break;                                                          // 0.0
/*156 */             }                                                                   // 0.0
/*158 */             break;                                                              // 0.0
/*160 */         }                                                                       // 0.0
/*162 */         if (can_write) {                                                        // 0.0
/*164 */             d->config[addr] = val;                                              // 0.0
/*166 */         }                                                                       // 0.0
/*168 */         addr++;                                                                 // 0.0
/*170 */         val >>= 8;                                                              // 0.0
/*172 */     }                                                                           // 0.0
/*176 */     end = address + len;                                                        // 0.0
/*178 */     if (end > PCI_COMMAND && address < (PCI_COMMAND + 2)) {                     // 0.0
/*180 */         /* if the command register is modified, we must modify the mappings */  // 0.0
/*182 */         pci_update_mappings(d);                                                 // 0.0
/*184 */     }                                                                           // 0.0
/*186 */ }                                                                               // 0.0
