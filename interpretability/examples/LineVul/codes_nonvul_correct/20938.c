// commit message qemu@26e92f6552 (target=0, prob=0.013804741, correct=True): Realview/EB procid hacks
/*0   */ static uint32_t arm_sysctl_read(void *opaque, target_phys_addr_t offset)           // (0) 0.05078
/*2   */ {                                                                                  // (34) 0.001953
/*4   */     arm_sysctl_state *s = (arm_sysctl_state *)opaque;                              // (2) 0.04492
/*8   */     switch (offset) {                                                              // (33) 0.01563
/*10  */     case 0x00: /* ID */                                                            // (28) 0.02148
/*12  */         return s->sys_id;                                                          // (5) 0.02734
/*14  */     case 0x04: /* SW */                                                            // (29) 0.02148
/*16  */         /* General purpose hardware switches.                                      // (14) 0.02539
/*18  */            We don't have a useful way of exposing these to the user.  */           // (1) 0.05078
/*20  */         return 0;                                                                  // (30) 0.01953
/*22  */     case 0x08: /* LED */                                                           // (27) 0.02148
/*24  */         return s->leds;                                                            // (15) 0.02539
/*26  */     case 0x20: /* LOCK */                                                          // (26) 0.02344
/*28  */         return s->lockval;                                                         // (17) 0.02539
/*30  */     case 0x0c: /* OSC0 */                                                          // (6) 0.02734
/*32  */     case 0x10: /* OSC1 */                                                          // (18) 0.02539
/*34  */     case 0x14: /* OSC2 */                                                          // (19) 0.02539
/*36  */     case 0x18: /* OSC3 */                                                          // (20) 0.02539
/*38  */     case 0x1c: /* OSC4 */                                                          // (7) 0.02734
/*40  */     case 0x24: /* 100HZ */                                                         // (21) 0.02539
/*42  */         /* ??? Implement these.  */                                                // (8) 0.02734
/*44  */         return 0;                                                                  // (31) 0.01953
/*46  */     case 0x28: /* CFGDATA1 */                                                      // (9) 0.02734
/*48  */         return s->cfgdata1;                                                        // (10) 0.02734
/*50  */     case 0x2c: /* CFGDATA2 */                                                      // (3) 0.0293
/*52  */         return s->cfgdata2;                                                        // (11) 0.02734
/*54  */     case 0x30: /* FLAGS */                                                         // (22) 0.02539
/*56  */         return s->flags;                                                           // (24) 0.02344
/*58  */     case 0x38: /* NVFLAGS */                                                       // (23) 0.02539
/*60  */         return s->nvflags;                                                         // (16) 0.02539
/*62  */     case 0x40: /* RESETCTL */                                                      // (4) 0.02734
/*64  */         return s->resetlevel;                                                      // (12) 0.02539
/*66  */     case 0x44: /* PCICTL */                                                        // (13) 0.02539
/*68  */         return 1;                                                                  // (32) 0.01953
/*70  */     case 0x48: /* MCI */                                                           // (25) 0.02344
/*72  */         return 0;                                                                  // 0.0
/*74  */     case 0x4c: /* FLASH */                                                         // 0.0
/*76  */         return 0;                                                                  // 0.0
/*78  */     case 0x50: /* CLCD */                                                          // 0.0
/*80  */         return 0x1000;                                                             // 0.0
/*82  */     case 0x54: /* CLCDSER */                                                       // 0.0
/*84  */         return 0;                                                                  // 0.0
/*86  */     case 0x58: /* BOOTCS */                                                        // 0.0
/*88  */         return 0;                                                                  // 0.0
/*90  */     case 0x5c: /* 24MHz */                                                         // 0.0
/*92  */         return muldiv64(qemu_get_clock(vm_clock), 24000000, get_ticks_per_sec());  // 0.0
/*94  */     case 0x60: /* MISC */                                                          // 0.0
/*96  */         return 0;                                                                  // 0.0
/*98  */     case 0x84: /* PROCID0 */                                                       // 0.0
/*100 */         /* ??? Don't know what the proper value for the core tile ID is.  */       // 0.0
/*102 */         return 0x02000000;                                                         // 0.0
/*104 */     case 0x88: /* PROCID1 */                                                       // 0.0
/*106 */         return 0xff000000;                                                         // 0.0
/*108 */     case 0x64: /* DMAPSR0 */                                                       // 0.0
/*110 */     case 0x68: /* DMAPSR1 */                                                       // 0.0
/*112 */     case 0x6c: /* DMAPSR2 */                                                       // 0.0
/*114 */     case 0x70: /* IOSEL */                                                         // 0.0
/*116 */     case 0x74: /* PLDCTL */                                                        // 0.0
/*118 */     case 0x80: /* BUSID */                                                         // 0.0
/*120 */     case 0x8c: /* OSCRESET0 */                                                     // 0.0
/*122 */     case 0x90: /* OSCRESET1 */                                                     // 0.0
/*124 */     case 0x94: /* OSCRESET2 */                                                     // 0.0
/*126 */     case 0x98: /* OSCRESET3 */                                                     // 0.0
/*128 */     case 0x9c: /* OSCRESET4 */                                                     // 0.0
/*130 */     case 0xc0: /* SYS_TEST_OSC0 */                                                 // 0.0
/*132 */     case 0xc4: /* SYS_TEST_OSC1 */                                                 // 0.0
/*134 */     case 0xc8: /* SYS_TEST_OSC2 */                                                 // 0.0
/*136 */     case 0xcc: /* SYS_TEST_OSC3 */                                                 // 0.0
/*138 */     case 0xd0: /* SYS_TEST_OSC4 */                                                 // 0.0
/*140 */         return 0;                                                                  // 0.0
/*142 */     default:                                                                       // 0.0
/*144 */         printf ("arm_sysctl_read: Bad register offset 0x%x\n", (int)offset);       // 0.0
/*146 */         return 0;                                                                  // 0.0
/*148 */     }                                                                              // 0.0
/*150 */ }                                                                                  // 0.0
