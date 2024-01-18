// commit message qemu@5d79b80b33 (target=0, prob=0.58159965, correct=False): pflash_cfi01: Drop unused 'bypass' field
/*0   */ static void pflash_write(pflash_t *pfl, hwaddr offset,                                  // (7) 0.03906
/*2   */                          uint32_t value, int width, int be)                             // (2) 0.07031
/*4   */ {                                                                                       // (25) 0.001953
/*6   */     uint8_t *p;                                                                         // (20) 0.01953
/*8   */     uint8_t cmd;                                                                        // (21) 0.01758
/*12  */     cmd = value;                                                                        // (22) 0.01367
/*16  */     DPRINTF("%s: writing offset " TARGET_FMT_plx " value %08x width %d wcycle 0x%x\n",  // (0) 0.07422
/*18  */             __func__, offset, value, width, pfl->wcycle);                               // (4) 0.05273
/*22  */     if (!pfl->wcycle) {                                                                 // (16) 0.02344
/*24  */         /* Set the device in I/O access mode */                                         // (8) 0.03516
/*26  */         memory_region_rom_device_set_readable(&pfl->mem, false);                        // (5) 0.05078
/*28  */     }                                                                                   // (24) 0.007812
/*32  */     switch (pfl->wcycle) {                                                              // (17) 0.02344
/*34  */     case 0:                                                                             // (23) 0.01172
/*36  */         /* read mode */                                                                 // (19) 0.02148
/*38  */         switch (cmd) {                                                                  // (18) 0.02344
/*40  */         case 0x00: /* ??? */                                                            // (14) 0.0293
/*42  */             goto reset_flash;                                                           // (12) 0.03125
/*44  */         case 0x10: /* Single Byte Program */                                            // (10) 0.0332
/*46  */         case 0x40: /* Single Byte Program */                                            // (11) 0.0332
/*48  */             DPRINTF("%s: Single Byte Program\n", __func__);                             // (3) 0.05469
/*50  */             break;                                                                      // (15) 0.02539
/*52  */         case 0x20: /* Block erase */                                                    // (13) 0.03125
/*54  */             p = pfl->storage;                                                           // (9) 0.03516
/*56  */             offset &= ~(pfl->sector_len - 1);                                           // (6) 0.04883
/*60  */             DPRINTF("%s: block erase at " TARGET_FMT_plx " bytes %x\n",                 // (1) 0.07227
/*62  */                     __func__, offset, (unsigned)pfl->sector_len);                       // 0.0
/*66  */             if (!pfl->ro) {                                                             // 0.0
/*68  */                 memset(p + offset, 0xff, pfl->sector_len);                              // 0.0
/*70  */                 pflash_update(pfl, offset, pfl->sector_len);                            // 0.0
/*72  */             } else {                                                                    // 0.0
/*74  */                 pfl->status |= 0x20; /* Block erase error */                            // 0.0
/*76  */             }                                                                           // 0.0
/*78  */             pfl->status |= 0x80; /* Ready! */                                           // 0.0
/*80  */             break;                                                                      // 0.0
/*82  */         case 0x50: /* Clear status bits */                                              // 0.0
/*84  */             DPRINTF("%s: Clear status bits\n", __func__);                               // 0.0
/*86  */             pfl->status = 0x0;                                                          // 0.0
/*88  */             goto reset_flash;                                                           // 0.0
/*90  */         case 0x60: /* Block (un)lock */                                                 // 0.0
/*92  */             DPRINTF("%s: Block unlock\n", __func__);                                    // 0.0
/*94  */             break;                                                                      // 0.0
/*96  */         case 0x70: /* Status Register */                                                // 0.0
/*98  */             DPRINTF("%s: Read status register\n", __func__);                            // 0.0
/*100 */             pfl->cmd = cmd;                                                             // 0.0
/*102 */             return;                                                                     // 0.0
/*104 */         case 0x90: /* Read Device ID */                                                 // 0.0
/*106 */             DPRINTF("%s: Read Device information\n", __func__);                         // 0.0
/*108 */             pfl->cmd = cmd;                                                             // 0.0
/*110 */             return;                                                                     // 0.0
/*112 */         case 0x98: /* CFI query */                                                      // 0.0
/*114 */             DPRINTF("%s: CFI query\n", __func__);                                       // 0.0
/*116 */             break;                                                                      // 0.0
/*118 */         case 0xe8: /* Write to buffer */                                                // 0.0
/*120 */             DPRINTF("%s: Write to buffer\n", __func__);                                 // 0.0
/*122 */             pfl->status |= 0x80; /* Ready! */                                           // 0.0
/*124 */             break;                                                                      // 0.0
/*126 */         case 0xf0: /* Probe for AMD flash */                                            // 0.0
/*128 */             DPRINTF("%s: Probe for AMD flash\n", __func__);                             // 0.0
/*130 */             goto reset_flash;                                                           // 0.0
/*132 */         case 0xff: /* Read array mode */                                                // 0.0
/*134 */             DPRINTF("%s: Read array mode\n", __func__);                                 // 0.0
/*136 */             goto reset_flash;                                                           // 0.0
/*138 */         default:                                                                        // 0.0
/*140 */             goto error_flash;                                                           // 0.0
/*142 */         }                                                                               // 0.0
/*144 */         pfl->wcycle++;                                                                  // 0.0
/*146 */         pfl->cmd = cmd;                                                                 // 0.0
/*148 */         break;                                                                          // 0.0
/*150 */     case 1:                                                                             // 0.0
/*152 */         switch (pfl->cmd) {                                                             // 0.0
/*154 */         case 0x10: /* Single Byte Program */                                            // 0.0
/*156 */         case 0x40: /* Single Byte Program */                                            // 0.0
/*158 */             DPRINTF("%s: Single Byte Program\n", __func__);                             // 0.0
/*160 */             if (!pfl->ro) {                                                             // 0.0
/*162 */                 pflash_data_write(pfl, offset, value, width, be);                       // 0.0
/*164 */                 pflash_update(pfl, offset, width);                                      // 0.0
/*166 */             } else {                                                                    // 0.0
/*168 */                 pfl->status |= 0x10; /* Programming error */                            // 0.0
/*170 */             }                                                                           // 0.0
/*172 */             pfl->status |= 0x80; /* Ready! */                                           // 0.0
/*174 */             pfl->wcycle = 0;                                                            // 0.0
/*176 */         break;                                                                          // 0.0
/*178 */         case 0x20: /* Block erase */                                                    // 0.0
/*180 */         case 0x28:                                                                      // 0.0
/*182 */             if (cmd == 0xd0) { /* confirm */                                            // 0.0
/*184 */                 pfl->wcycle = 0;                                                        // 0.0
/*186 */                 pfl->status |= 0x80;                                                    // 0.0
/*188 */             } else if (cmd == 0xff) { /* read array mode */                             // 0.0
/*190 */                 goto reset_flash;                                                       // 0.0
/*192 */             } else                                                                      // 0.0
/*194 */                 goto error_flash;                                                       // 0.0
/*198 */             break;                                                                      // 0.0
/*200 */         case 0xe8:                                                                      // 0.0
/*202 */             DPRINTF("%s: block write of %x bytes\n", __func__, value);                  // 0.0
/*204 */             pfl->counter = value;                                                       // 0.0
/*206 */             pfl->wcycle++;                                                              // 0.0
/*208 */             break;                                                                      // 0.0
/*210 */         case 0x60:                                                                      // 0.0
/*212 */             if (cmd == 0xd0) {                                                          // 0.0
/*214 */                 pfl->wcycle = 0;                                                        // 0.0
/*216 */                 pfl->status |= 0x80;                                                    // 0.0
/*218 */             } else if (cmd == 0x01) {                                                   // 0.0
/*220 */                 pfl->wcycle = 0;                                                        // 0.0
/*222 */                 pfl->status |= 0x80;                                                    // 0.0
/*224 */             } else if (cmd == 0xff) {                                                   // 0.0
/*226 */                 goto reset_flash;                                                       // 0.0
/*228 */             } else {                                                                    // 0.0
/*230 */                 DPRINTF("%s: Unknown (un)locking command\n", __func__);                 // 0.0
/*232 */                 goto reset_flash;                                                       // 0.0
/*234 */             }                                                                           // 0.0
/*236 */             break;                                                                      // 0.0
/*238 */         case 0x98:                                                                      // 0.0
/*240 */             if (cmd == 0xff) {                                                          // 0.0
/*242 */                 goto reset_flash;                                                       // 0.0
/*244 */             } else {                                                                    // 0.0
/*246 */                 DPRINTF("%s: leaving query mode\n", __func__);                          // 0.0
/*248 */             }                                                                           // 0.0
/*250 */             break;                                                                      // 0.0
/*252 */         default:                                                                        // 0.0
/*254 */             goto error_flash;                                                           // 0.0
/*256 */         }                                                                               // 0.0
/*258 */         break;                                                                          // 0.0
/*260 */     case 2:                                                                             // 0.0
/*262 */         switch (pfl->cmd) {                                                             // 0.0
/*264 */         case 0xe8: /* Block write */                                                    // 0.0
/*266 */             if (!pfl->ro) {                                                             // 0.0
/*268 */                 pflash_data_write(pfl, offset, value, width, be);                       // 0.0
/*270 */             } else {                                                                    // 0.0
/*272 */                 pfl->status |= 0x10; /* Programming error */                            // 0.0
/*274 */             }                                                                           // 0.0
/*278 */             pfl->status |= 0x80;                                                        // 0.0
/*282 */             if (!pfl->counter) {                                                        // 0.0
/*284 */                 hwaddr mask = pfl->writeblock_size - 1;                                 // 0.0
/*286 */                 mask = ~mask;                                                           // 0.0
/*290 */                 DPRINTF("%s: block write finished\n", __func__);                        // 0.0
/*292 */                 pfl->wcycle++;                                                          // 0.0
/*294 */                 if (!pfl->ro) {                                                         // 0.0
/*296 */                     /* Flush the entire write buffer onto backing storage.  */          // 0.0
/*298 */                     pflash_update(pfl, offset & mask, pfl->writeblock_size);            // 0.0
/*300 */                 } else {                                                                // 0.0
/*302 */                     pfl->status |= 0x10; /* Programming error */                        // 0.0
/*304 */                 }                                                                       // 0.0
/*306 */             }                                                                           // 0.0
/*310 */             pfl->counter--;                                                             // 0.0
/*312 */             break;                                                                      // 0.0
/*314 */         default:                                                                        // 0.0
/*316 */             goto error_flash;                                                           // 0.0
/*318 */         }                                                                               // 0.0
/*320 */         break;                                                                          // 0.0
/*322 */     case 3: /* Confirm mode */                                                          // 0.0
/*324 */         switch (pfl->cmd) {                                                             // 0.0
/*326 */         case 0xe8: /* Block write */                                                    // 0.0
/*328 */             if (cmd == 0xd0) {                                                          // 0.0
/*330 */                 pfl->wcycle = 0;                                                        // 0.0
/*332 */                 pfl->status |= 0x80;                                                    // 0.0
/*334 */             } else {                                                                    // 0.0
/*336 */                 DPRINTF("%s: unknown command for \"write block\"\n", __func__);         // 0.0
/*338 */                 PFLASH_BUG("Write block confirm");                                      // 0.0
/*340 */                 goto reset_flash;                                                       // 0.0
/*342 */             }                                                                           // 0.0
/*344 */             break;                                                                      // 0.0
/*346 */         default:                                                                        // 0.0
/*348 */             goto error_flash;                                                           // 0.0
/*350 */         }                                                                               // 0.0
/*352 */         break;                                                                          // 0.0
/*354 */     default:                                                                            // 0.0
/*356 */         /* Should never happen */                                                       // 0.0
/*358 */         DPRINTF("%s: invalid write state\n",  __func__);                                // 0.0
/*360 */         goto reset_flash;                                                               // 0.0
/*362 */     }                                                                                   // 0.0
/*364 */     return;                                                                             // 0.0
/*368 */  error_flash:                                                                           // 0.0
/*370 */     qemu_log_mask(LOG_UNIMP, "%s: Unimplemented flash cmd sequence "                    // 0.0
/*372 */                   "(offset " TARGET_FMT_plx ", wcycle 0x%x cmd 0x%x value 0x%x)"        // 0.0
/*374 */                   "\n", __func__, offset, pfl->wcycle, pfl->cmd, value);                // 0.0
/*378 */  reset_flash:                                                                           // 0.0
/*380 */     memory_region_rom_device_set_readable(&pfl->mem, true);                             // 0.0
/*384 */     pfl->bypass = 0;                                                                    // 0.0
/*386 */     pfl->wcycle = 0;                                                                    // 0.0
/*388 */     pfl->cmd = 0;                                                                       // 0.0
/*390 */ }                                                                                       // 0.0
