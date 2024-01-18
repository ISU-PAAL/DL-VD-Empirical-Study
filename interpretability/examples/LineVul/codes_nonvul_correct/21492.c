// commit message qemu@6cded3a43a (target=0, prob=0.40613893, correct=True): eepro100: Fix PXE boot
/*0  */ static void nic_selective_reset(EEPRO100State * s)                                 // (14) 0.03756
/*2  */ {                                                                                  // (19) 0.002347
/*4  */     size_t i;                                                                      // (17) 0.01878
/*6  */     uint16_t *eeprom_contents = eeprom93xx_data(s->eeprom);                        // (2) 0.06808
/*8  */     //~ eeprom93xx_reset(s->eeprom);                                               // (10) 0.0446
/*10 */     memcpy(eeprom_contents, s->conf.macaddr.a, 6);                                 // (4) 0.05869
/*12 */     eeprom_contents[0xa] = 0x4000;                                                 // (12) 0.04225
/*14 */     if (s->device == i82557B || s->device == i82557C)                              // (7) 0.05399
/*16 */         eeprom_contents[5] = 0x0100;                                               // (9) 0.0493
/*18 */     uint16_t sum = 0;                                                              // (16) 0.02582
/*20 */     for (i = 0; i < EEPROM_SIZE - 1; i++) {                                        // (8) 0.05164
/*22 */         sum += eeprom_contents[i];                                                 // (13) 0.04225
/*24 */     }                                                                              // (18) 0.00939
/*26 */     eeprom_contents[EEPROM_SIZE - 1] = 0xbaba - sum;                               // (5) 0.05869
/*28 */     TRACE(EEPROM, logout("checksum=0x%04x\n", eeprom_contents[EEPROM_SIZE - 1]));  // (0) 0.0939
/*32 */     memset(s->mem, 0, sizeof(s->mem));                                             // (11) 0.04225
/*34 */     uint32_t val = BIT(21);                                                        // (15) 0.03052
/*36 */     memcpy(&s->mem[SCBCtrlMDI], &val, sizeof(val));                                // (6) 0.05634
/*40 */     assert(sizeof(s->mdimem) == sizeof(eepro100_mdi_default));                     // (3) 0.06338
/*42 */     memcpy(&s->mdimem[0], &eepro100_mdi_default[0], sizeof(s->mdimem));            // (1) 0.08451
/*44 */ }                                                                                  // (20) 0.002347
