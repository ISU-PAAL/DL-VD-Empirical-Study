// commit message qemu@6fedcaa1c5 (target=0, prob=0.19631082, correct=True): eeprom93xx: fix coding style
/*0   */ void eeprom93xx_write(eeprom_t *eeprom, int eecs, int eesk, int eedi)                  // (0) 0.06445
/*2   */ {                                                                                      // (23) 0.001953
/*4   */     uint8_t tick = eeprom->tick;                                                       // (16) 0.0293
/*6   */     uint8_t eedo = eeprom->eedo;                                                       // (13) 0.0332
/*8   */     uint16_t address = eeprom->address;                                                // (17) 0.0293
/*10  */     uint8_t command = eeprom->command;                                                 // (18) 0.0293
/*14  */     logout("CS=%u SK=%u DI=%u DO=%u, tick = %u\n",                                     // (3) 0.05859
/*16  */            eecs, eesk, eedi, eedo, tick);                                              // (5) 0.05078
/*20  */     if (! eeprom->eecs && eecs) {                                                      // (12) 0.03516
/*22  */         /* Start chip select cycle. */                                                 // (19) 0.02734
/*24  */         logout("Cycle start, waiting for 1st start bit (0)\n");                        // (6) 0.04883
/*26  */         tick = 0;                                                                      // (22) 0.02148
/*28  */         command = 0x0;                                                                 // (20) 0.02539
/*30  */         address = 0x0;                                                                 // (21) 0.02539
/*32  */     } else if (eeprom->eecs && ! eecs) {                                               // (8) 0.04102
/*34  */         /* End chip select cycle. This triggers write / erase. */                      // (10) 0.03906
/*36  */         if (eeprom->writable) {                                                        // (14) 0.0332
/*38  */             uint8_t subcommand = address >> (eeprom->addrbits - 2);                    // (4) 0.05859
/*40  */             if (command == 0 && subcommand == 2) {                                     // (7) 0.04492
/*42  */                 /* Erase all. */                                                       // (9) 0.04102
/*44  */                 for (address = 0; address < eeprom->size; address++) {                 // (2) 0.0625
/*46  */                     eeprom->contents[address] = 0xffff;                                // (1) 0.06445
/*48  */                 }                                                                      // (15) 0.03125
/*50  */             } else if (command == 3) {                                                 // (11) 0.03906
/*52  */                 /* Erase word. */                                                      // 0.0
/*54  */                 eeprom->contents[address] = 0xffff;                                    // 0.0
/*56  */             } else if (tick >= 2 + 2 + eeprom->addrbits + 16) {                        // 0.0
/*58  */                 if (command == 1) {                                                    // 0.0
/*60  */                     /* Write word. */                                                  // 0.0
/*62  */                     eeprom->contents[address] &= eeprom->data;                         // 0.0
/*64  */                 } else if (command == 0 && subcommand == 1) {                          // 0.0
/*66  */                     /* Write all. */                                                   // 0.0
/*68  */                     for (address = 0; address < eeprom->size; address++) {             // 0.0
/*70  */                         eeprom->contents[address] &= eeprom->data;                     // 0.0
/*72  */                     }                                                                  // 0.0
/*74  */                 }                                                                      // 0.0
/*76  */             }                                                                          // 0.0
/*78  */         }                                                                              // 0.0
/*80  */         /* Output DO is tristate, read results in 1. */                                // 0.0
/*82  */         eedo = 1;                                                                      // 0.0
/*84  */     } else if (eecs && ! eeprom->eesk && eesk) {                                       // 0.0
/*86  */         /* Raising edge of clock shifts data in. */                                    // 0.0
/*88  */         if (tick == 0) {                                                               // 0.0
/*90  */             /* Wait for 1st start bit. */                                              // 0.0
/*92  */             if (eedi == 0) {                                                           // 0.0
/*94  */                 logout("Got correct 1st start bit, waiting for 2nd start bit (1)\n");  // 0.0
/*96  */                 tick++;                                                                // 0.0
/*98  */             } else {                                                                   // 0.0
/*100 */                 logout("wrong 1st start bit (is 1, should be 0)\n");                   // 0.0
/*102 */                 tick = 2;                                                              // 0.0
/*104 */                 //~ assert(!"wrong start bit");                                        // 0.0
/*106 */             }                                                                          // 0.0
/*108 */         } else if (tick == 1) {                                                        // 0.0
/*110 */             /* Wait for 2nd start bit. */                                              // 0.0
/*112 */             if (eedi != 0) {                                                           // 0.0
/*114 */                 logout("Got correct 2nd start bit, getting command + address\n");      // 0.0
/*116 */                 tick++;                                                                // 0.0
/*118 */             } else {                                                                   // 0.0
/*120 */                 logout("1st start bit is longer than needed\n");                       // 0.0
/*122 */             }                                                                          // 0.0
/*124 */         } else if (tick < 2 + 2) {                                                     // 0.0
/*126 */             /* Got 2 start bits, transfer 2 opcode bits. */                            // 0.0
/*128 */             tick++;                                                                    // 0.0
/*130 */             command <<= 1;                                                             // 0.0
/*132 */             if (eedi) {                                                                // 0.0
/*134 */                 command += 1;                                                          // 0.0
/*136 */             }                                                                          // 0.0
/*138 */         } else if (tick < 2 + 2 + eeprom->addrbits) {                                  // 0.0
/*140 */             /* Got 2 start bits and 2 opcode bits, transfer all address bits. */       // 0.0
/*142 */             tick++;                                                                    // 0.0
/*144 */             address = ((address << 1) | eedi);                                         // 0.0
/*146 */             if (tick == 2 + 2 + eeprom->addrbits) {                                    // 0.0
/*148 */                 logout("%s command, address = 0x%02x (value 0x%04x)\n",                // 0.0
/*150 */                        opstring[command], address, eeprom->contents[address]);         // 0.0
/*152 */                 if (command == 2) {                                                    // 0.0
/*154 */                     eedo = 0;                                                          // 0.0
/*156 */                 }                                                                      // 0.0
/*158 */                 address = address % eeprom->size;                                      // 0.0
/*160 */                 if (command == 0) {                                                    // 0.0
/*162 */                     /* Command code in upper 2 bits of address. */                     // 0.0
/*164 */                     switch (address >> (eeprom->addrbits - 2)) {                       // 0.0
/*166 */                         case 0:                                                        // 0.0
/*168 */                             logout("write disable command\n");                         // 0.0
/*170 */                             eeprom->writable = 0;                                      // 0.0
/*172 */                             break;                                                     // 0.0
/*174 */                         case 1:                                                        // 0.0
/*176 */                             logout("write all command\n");                             // 0.0
/*178 */                             break;                                                     // 0.0
/*180 */                         case 2:                                                        // 0.0
/*182 */                             logout("erase all command\n");                             // 0.0
/*184 */                             break;                                                     // 0.0
/*186 */                         case 3:                                                        // 0.0
/*188 */                             logout("write enable command\n");                          // 0.0
/*190 */                             eeprom->writable = 1;                                      // 0.0
/*192 */                             break;                                                     // 0.0
/*194 */                     }                                                                  // 0.0
/*196 */                 } else {                                                               // 0.0
/*198 */                     /* Read, write or erase word. */                                   // 0.0
/*200 */                     eeprom->data = eeprom->contents[address];                          // 0.0
/*202 */                 }                                                                      // 0.0
/*204 */             }                                                                          // 0.0
/*206 */         } else if (tick < 2 + 2 + eeprom->addrbits + 16) {                             // 0.0
/*208 */             /* Transfer 16 data bits. */                                               // 0.0
/*210 */             tick++;                                                                    // 0.0
/*212 */             if (command == 2) {                                                        // 0.0
/*214 */                 /* Read word. */                                                       // 0.0
/*216 */                 eedo = ((eeprom->data & 0x8000) != 0);                                 // 0.0
/*218 */             }                                                                          // 0.0
/*220 */             eeprom->data <<= 1;                                                        // 0.0
/*222 */             eeprom->data += eedi;                                                      // 0.0
/*224 */         } else {                                                                       // 0.0
/*226 */             logout("additional unneeded tick, not processed\n");                       // 0.0
/*228 */         }                                                                              // 0.0
/*230 */     }                                                                                  // 0.0
/*232 */     /* Save status of EEPROM. */                                                       // 0.0
/*234 */     eeprom->tick = tick;                                                               // 0.0
/*236 */     eeprom->eecs = eecs;                                                               // 0.0
/*238 */     eeprom->eesk = eesk;                                                               // 0.0
/*240 */     eeprom->eedo = eedo;                                                               // 0.0
/*242 */     eeprom->address = address;                                                         // 0.0
/*244 */     eeprom->command = command;                                                         // 0.0
/*246 */ }                                                                                      // 0.0
