// commit message qemu@e3da9921eb (target=0, prob=0.4363428, correct=True): armv7m_nvic: fix CPUID Base Register
/*0   */ static uint32_t nvic_readl(nvic_state *s, uint32_t offset)                       // (5) 0.04688
/*2   */ {                                                                                // (25) 0.001953
/*4   */     ARMCPU *cpu;                                                                 // (20) 0.01758
/*6   */     uint32_t val;                                                                // (21) 0.01758
/*8   */     int irq;                                                                     // (24) 0.01367
/*12  */     switch (offset) {                                                            // (22) 0.01563
/*14  */     case 4: /* Interrupt Control Type.  */                                       // (18) 0.02734
/*16  */         return (s->num_irq / 32) - 1;                                            // (9) 0.04102
/*18  */     case 0x10: /* SysTick Control and Status.  */                                // (10) 0.03711
/*20  */         val = s->systick.control;                                                // (16) 0.03125
/*22  */         s->systick.control &= ~SYSTICK_COUNTFLAG;                                // (6) 0.04688
/*24  */         return val;                                                              // (19) 0.01953
/*26  */     case 0x14: /* SysTick Reload Value.  */                                      // (12) 0.03516
/*28  */         return s->systick.reload;                                                // (17) 0.03125
/*30  */     case 0x18: /* SysTick Current Value.  */                                     // (11) 0.03516
/*32  */         {                                                                        // (23) 0.01562
/*34  */             int64_t t;                                                           // (15) 0.0332
/*36  */             if ((s->systick.control & SYSTICK_ENABLE) == 0)                      // (3) 0.05859
/*38  */                 return 0;                                                        // (13) 0.03516
/*40  */             t = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);                           // (1) 0.06641
/*42  */             if (t >= s->systick.tick)                                            // (8) 0.04297
/*44  */                 return 0;                                                        // (14) 0.03516
/*46  */             val = ((s->systick.tick - (t + 1)) / systick_scale(s)) + 1;          // (0) 0.07227
/*48  */             /* The interrupt in triggered when the timer reaches zero.           // (7) 0.04297
/*50  */                However the counter is not reloaded until the next clock          // (4) 0.04883
/*52  */                tick.  This is a hack to return zero during the first tick.  */   // (2) 0.06055
/*54  */             if (val > s->systick.reload)                                         // 0.0
/*56  */                 val = 0;                                                         // 0.0
/*58  */             return val;                                                          // 0.0
/*60  */         }                                                                        // 0.0
/*62  */     case 0x1c: /* SysTick Calibration Value.  */                                 // 0.0
/*64  */         return 10000;                                                            // 0.0
/*66  */     case 0xd00: /* CPUID Base.  */                                               // 0.0
/*68  */         cpu = ARM_CPU(current_cpu);                                              // 0.0
/*70  */         return cpu->env.cp15.c0_cpuid;                                           // 0.0
/*72  */     case 0xd04: /* Interrupt Control State.  */                                  // 0.0
/*74  */         /* VECTACTIVE */                                                         // 0.0
/*76  */         val = s->gic.running_irq[0];                                             // 0.0
/*78  */         if (val == 1023) {                                                       // 0.0
/*80  */             val = 0;                                                             // 0.0
/*82  */         } else if (val >= 32) {                                                  // 0.0
/*84  */             val -= 16;                                                           // 0.0
/*86  */         }                                                                        // 0.0
/*88  */         /* RETTOBASE */                                                          // 0.0
/*90  */         if (s->gic.running_irq[0] == 1023                                        // 0.0
/*92  */                 || s->gic.last_active[s->gic.running_irq[0]][0] == 1023) {       // 0.0
/*94  */             val |= (1 << 11);                                                    // 0.0
/*96  */         }                                                                        // 0.0
/*98  */         /* VECTPENDING */                                                        // 0.0
/*100 */         if (s->gic.current_pending[0] != 1023)                                   // 0.0
/*102 */             val |= (s->gic.current_pending[0] << 12);                            // 0.0
/*104 */         /* ISRPENDING */                                                         // 0.0
/*106 */         for (irq = 32; irq < s->num_irq; irq++) {                                // 0.0
/*108 */             if (s->gic.irq_state[irq].pending) {                                 // 0.0
/*110 */                 val |= (1 << 22);                                                // 0.0
/*112 */                 break;                                                           // 0.0
/*114 */             }                                                                    // 0.0
/*116 */         }                                                                        // 0.0
/*118 */         /* PENDSTSET */                                                          // 0.0
/*120 */         if (s->gic.irq_state[ARMV7M_EXCP_SYSTICK].pending)                       // 0.0
/*122 */             val |= (1 << 26);                                                    // 0.0
/*124 */         /* PENDSVSET */                                                          // 0.0
/*126 */         if (s->gic.irq_state[ARMV7M_EXCP_PENDSV].pending)                        // 0.0
/*128 */             val |= (1 << 28);                                                    // 0.0
/*130 */         /* NMIPENDSET */                                                         // 0.0
/*132 */         if (s->gic.irq_state[ARMV7M_EXCP_NMI].pending)                           // 0.0
/*134 */             val |= (1 << 31);                                                    // 0.0
/*136 */         return val;                                                              // 0.0
/*138 */     case 0xd08: /* Vector Table Offset.  */                                      // 0.0
/*140 */         cpu = ARM_CPU(current_cpu);                                              // 0.0
/*142 */         return cpu->env.v7m.vecbase;                                             // 0.0
/*144 */     case 0xd0c: /* Application Interrupt/Reset Control.  */                      // 0.0
/*146 */         return 0xfa05000;                                                        // 0.0
/*148 */     case 0xd10: /* System Control.  */                                           // 0.0
/*150 */         /* TODO: Implement SLEEPONEXIT.  */                                      // 0.0
/*152 */         return 0;                                                                // 0.0
/*154 */     case 0xd14: /* Configuration Control.  */                                    // 0.0
/*156 */         /* TODO: Implement Configuration Control bits.  */                       // 0.0
/*158 */         return 0;                                                                // 0.0
/*160 */     case 0xd24: /* System Handler Status.  */                                    // 0.0
/*162 */         val = 0;                                                                 // 0.0
/*164 */         if (s->gic.irq_state[ARMV7M_EXCP_MEM].active) val |= (1 << 0);           // 0.0
/*166 */         if (s->gic.irq_state[ARMV7M_EXCP_BUS].active) val |= (1 << 1);           // 0.0
/*168 */         if (s->gic.irq_state[ARMV7M_EXCP_USAGE].active) val |= (1 << 3);         // 0.0
/*170 */         if (s->gic.irq_state[ARMV7M_EXCP_SVC].active) val |= (1 << 7);           // 0.0
/*172 */         if (s->gic.irq_state[ARMV7M_EXCP_DEBUG].active) val |= (1 << 8);         // 0.0
/*174 */         if (s->gic.irq_state[ARMV7M_EXCP_PENDSV].active) val |= (1 << 10);       // 0.0
/*176 */         if (s->gic.irq_state[ARMV7M_EXCP_SYSTICK].active) val |= (1 << 11);      // 0.0
/*178 */         if (s->gic.irq_state[ARMV7M_EXCP_USAGE].pending) val |= (1 << 12);       // 0.0
/*180 */         if (s->gic.irq_state[ARMV7M_EXCP_MEM].pending) val |= (1 << 13);         // 0.0
/*182 */         if (s->gic.irq_state[ARMV7M_EXCP_BUS].pending) val |= (1 << 14);         // 0.0
/*184 */         if (s->gic.irq_state[ARMV7M_EXCP_SVC].pending) val |= (1 << 15);         // 0.0
/*186 */         if (s->gic.irq_state[ARMV7M_EXCP_MEM].enabled) val |= (1 << 16);         // 0.0
/*188 */         if (s->gic.irq_state[ARMV7M_EXCP_BUS].enabled) val |= (1 << 17);         // 0.0
/*190 */         if (s->gic.irq_state[ARMV7M_EXCP_USAGE].enabled) val |= (1 << 18);       // 0.0
/*192 */         return val;                                                              // 0.0
/*194 */     case 0xd28: /* Configurable Fault Status.  */                                // 0.0
/*196 */         /* TODO: Implement Fault Status.  */                                     // 0.0
/*198 */         qemu_log_mask(LOG_UNIMP, "Configurable Fault Status unimplemented\n");   // 0.0
/*200 */         return 0;                                                                // 0.0
/*202 */     case 0xd2c: /* Hard Fault Status.  */                                        // 0.0
/*204 */     case 0xd30: /* Debug Fault Status.  */                                       // 0.0
/*206 */     case 0xd34: /* Mem Manage Address.  */                                       // 0.0
/*208 */     case 0xd38: /* Bus Fault Address.  */                                        // 0.0
/*210 */     case 0xd3c: /* Aux Fault Status.  */                                         // 0.0
/*212 */         /* TODO: Implement fault status registers.  */                           // 0.0
/*214 */         qemu_log_mask(LOG_UNIMP, "Fault status registers unimplemented\n");      // 0.0
/*216 */         return 0;                                                                // 0.0
/*218 */     case 0xd40: /* PFR0.  */                                                     // 0.0
/*220 */         return 0x00000030;                                                       // 0.0
/*222 */     case 0xd44: /* PRF1.  */                                                     // 0.0
/*224 */         return 0x00000200;                                                       // 0.0
/*226 */     case 0xd48: /* DFR0.  */                                                     // 0.0
/*228 */         return 0x00100000;                                                       // 0.0
/*230 */     case 0xd4c: /* AFR0.  */                                                     // 0.0
/*232 */         return 0x00000000;                                                       // 0.0
/*234 */     case 0xd50: /* MMFR0.  */                                                    // 0.0
/*236 */         return 0x00000030;                                                       // 0.0
/*238 */     case 0xd54: /* MMFR1.  */                                                    // 0.0
/*240 */         return 0x00000000;                                                       // 0.0
/*242 */     case 0xd58: /* MMFR2.  */                                                    // 0.0
/*244 */         return 0x00000000;                                                       // 0.0
/*246 */     case 0xd5c: /* MMFR3.  */                                                    // 0.0
/*248 */         return 0x00000000;                                                       // 0.0
/*250 */     case 0xd60: /* ISAR0.  */                                                    // 0.0
/*252 */         return 0x01141110;                                                       // 0.0
/*254 */     case 0xd64: /* ISAR1.  */                                                    // 0.0
/*256 */         return 0x02111000;                                                       // 0.0
/*258 */     case 0xd68: /* ISAR2.  */                                                    // 0.0
/*260 */         return 0x21112231;                                                       // 0.0
/*262 */     case 0xd6c: /* ISAR3.  */                                                    // 0.0
/*264 */         return 0x01111110;                                                       // 0.0
/*266 */     case 0xd70: /* ISAR4.  */                                                    // 0.0
/*268 */         return 0x01310102;                                                       // 0.0
/*270 */     /* TODO: Implement debug registers.  */                                      // 0.0
/*272 */     default:                                                                     // 0.0
/*274 */         qemu_log_mask(LOG_GUEST_ERROR, "NVIC: Bad read offset 0x%x\n", offset);  // 0.0
/*276 */         return 0;                                                                // 0.0
/*278 */     }                                                                            // 0.0
/*280 */ }                                                                                // 0.0
