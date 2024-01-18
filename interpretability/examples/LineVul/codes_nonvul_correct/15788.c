// commit message qemu@35c648078a (target=0, prob=0.013605456, correct=True): mips_malta: generate SMBUS EEPROM data
/*0  */ static uint8_t eeprom24c0x_read(void)                       // (2) 0.165
/*2  */ {                                                           // (4) 0.009709
/*4  */     logout("%u: scl = %u, sda = %u, data = 0x%02x\n",       // (1) 0.301
/*6  */         eeprom.tick, eeprom.scl, eeprom.sda, eeprom.data);  // (0) 0.3107
/*8  */     return eeprom.sda;                                      // (3) 0.1068
/*10 */ }                                                           // (5) 0.009709
