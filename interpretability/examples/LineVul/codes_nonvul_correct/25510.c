// commit message qemu@6fedcaa1c5 (target=0, prob=0.094010055, correct=True): eeprom93xx: fix coding style
/*0  */ uint16_t eeprom93xx_read(eeprom_t *eeprom)                // (1) 0.2366
/*2  */ {                                                         // (4) 0.01075
/*4  */     /* Return status of pin DO (0 or 1). */               // (2) 0.1613
/*6  */     logout("CS=%u DO=%u\n", eeprom->eecs, eeprom->eedo);  // (0) 0.3441
/*8  */     return (eeprom->eedo);                                // (3) 0.129
/*10 */ }                                                         // (5) 0.01075
