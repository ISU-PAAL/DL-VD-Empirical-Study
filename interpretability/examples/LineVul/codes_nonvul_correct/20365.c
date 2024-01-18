// commit message qemu@424ad8388f (target=0, prob=0.028970234, correct=True): target-alpha: Fix interrupt mask for cpu1
/*0   */ static void cchip_write(void *opaque, hwaddr addr,                          // (11) 0.0332
/*2   */                         uint64_t val, unsigned size)                        // (3) 0.0625
/*4   */ {                                                                           // (26) 0.001953
/*6   */     TyphoonState *s = opaque;                                               // (16) 0.01953
/*8   */     uint64_t oldval, newval;                                                // (14) 0.02539
/*12  */     switch (addr) {                                                         // (22) 0.01563
/*14  */     case 0x0000:                                                            // (23) 0.01562
/*16  */         /* CSC: Cchip System Configuration Register.  */                    // (9) 0.03711
/*18  */         /* All sorts of data here; nothing relevant RW.  */                 // (8) 0.03906
/*20  */         break;                                                              // (18) 0.01758
/*24  */     case 0x0040:                                                            // (19) 0.01758
/*26  */         /* MTR: Memory Timing Register.  */                                 // (10) 0.03516
/*28  */         /* All sorts of stuff related to real DRAM.  */                     // (7) 0.03906
/*30  */         break;                                                              // (20) 0.01758
/*34  */     case 0x0080:                                                            // (21) 0.01758
/*36  */         /* MISC: Miscellaneous Register.  */                                // (13) 0.03125
/*38  */         newval = oldval = s->cchip.misc;                                    // (6) 0.03906
/*40  */         newval &= ~(val & 0x10000ff0);     /* W1C fields */                 // (4) 0.06055
/*42  */         if (val & 0x100000) {                                               // (12) 0.0332
/*44  */             newval &= ~0xff0000ull;        /* ACL clears ABT and ABW */     // (1) 0.07227
/*46  */         } else {                                                            // (17) 0.01953
/*48  */             newval |= val & 0x00f00000;    /* ABT field is W1S */           // (2) 0.06836
/*50  */             if ((newval & 0xf0000) == 0) {                                  // (5) 0.04688
/*52  */                 newval |= val & 0xf0000;   /* ABW field is W1S iff zero */  // (0) 0.07617
/*54  */             }                                                               // (15) 0.02344
/*56  */         }                                                                   // (24) 0.01562
/*58  */         newval |= (val & 0xf000) >> 4;     /* IPREQ field sets IPINTR.  */  // 0.0
/*62  */         newval &= ~0xf0000000000ull;       /* WO and RW fields */           // 0.0
/*64  */         newval |= val & 0xf0000000000ull;                                   // 0.0
/*66  */         s->cchip.misc = newval;                                             // 0.0
/*70  */         /* Pass on changes to IPI and ITI state.  */                        // 0.0
/*72  */         if ((newval ^ oldval) & 0xff0) {                                    // 0.0
/*74  */             int i;                                                          // 0.0
/*76  */             for (i = 0; i < 4; ++i) {                                       // 0.0
/*78  */                 AlphaCPU *cpu = s->cchip.cpu[i];                            // 0.0
/*80  */                 if (cpu != NULL) {                                          // 0.0
/*82  */                     CPUState *cs = CPU(cpu);                                // 0.0
/*84  */                     /* IPI can be either cleared or set by the write.  */   // 0.0
/*86  */                     if (newval & (1 << (i + 8))) {                          // 0.0
/*88  */                         cpu_interrupt(cs, CPU_INTERRUPT_SMP);               // 0.0
/*90  */                     } else {                                                // 0.0
/*92  */                         cpu_reset_interrupt(cs, CPU_INTERRUPT_SMP);         // 0.0
/*94  */                     }                                                       // 0.0
/*98  */                     /* ITI can only be cleared by the write.  */            // 0.0
/*100 */                     if ((newval & (1 << (i + 4))) == 0) {                   // 0.0
/*102 */                         cpu_reset_interrupt(cs, CPU_INTERRUPT_TIMER);       // 0.0
/*104 */                     }                                                       // 0.0
/*106 */                 }                                                           // 0.0
/*108 */             }                                                               // 0.0
/*110 */         }                                                                   // 0.0
/*112 */         break;                                                              // 0.0
/*116 */     case 0x00c0:                                                            // 0.0
/*118 */         /* MPD: Memory Presence Detect Register.  */                        // 0.0
/*120 */         break;                                                              // 0.0
/*124 */     case 0x0100: /* AAR0 */                                                 // 0.0
/*126 */     case 0x0140: /* AAR1 */                                                 // 0.0
/*128 */     case 0x0180: /* AAR2 */                                                 // 0.0
/*130 */     case 0x01c0: /* AAR3 */                                                 // 0.0
/*132 */         /* AAR: Array Address Register.  */                                 // 0.0
/*134 */         /* All sorts of information about DRAM.  */                         // 0.0
/*136 */         break;                                                              // 0.0
/*140 */     case 0x0200: /* DIM0 */                                                 // 0.0
/*142 */         /* DIM: Device Interrupt Mask Register, CPU0.  */                   // 0.0
/*144 */         s->cchip.dim[0] = val;                                              // 0.0
/*146 */         cpu_irq_change(s->cchip.cpu[0], val & s->cchip.drir);               // 0.0
/*148 */         break;                                                              // 0.0
/*150 */     case 0x0240: /* DIM1 */                                                 // 0.0
/*152 */         /* DIM: Device Interrupt Mask Register, CPU1.  */                   // 0.0
/*154 */         s->cchip.dim[0] = val;                                              // 0.0
/*156 */         cpu_irq_change(s->cchip.cpu[1], val & s->cchip.drir);               // 0.0
/*158 */         break;                                                              // 0.0
/*162 */     case 0x0280: /* DIR0 (RO) */                                            // 0.0
/*164 */     case 0x02c0: /* DIR1 (RO) */                                            // 0.0
/*166 */     case 0x0300: /* DRIR (RO) */                                            // 0.0
/*168 */         break;                                                              // 0.0
/*172 */     case 0x0340:                                                            // 0.0
/*174 */         /* PRBEN: Probe Enable Register.  */                                // 0.0
/*176 */         break;                                                              // 0.0
/*180 */     case 0x0380: /* IIC0 */                                                 // 0.0
/*182 */         s->cchip.iic[0] = val & 0xffffff;                                   // 0.0
/*184 */         break;                                                              // 0.0
/*186 */     case 0x03c0: /* IIC1 */                                                 // 0.0
/*188 */         s->cchip.iic[1] = val & 0xffffff;                                   // 0.0
/*190 */         break;                                                              // 0.0
/*194 */     case 0x0400: /* MPR0 */                                                 // 0.0
/*196 */     case 0x0440: /* MPR1 */                                                 // 0.0
/*198 */     case 0x0480: /* MPR2 */                                                 // 0.0
/*200 */     case 0x04c0: /* MPR3 */                                                 // 0.0
/*202 */         /* MPR: Memory Programming Register.  */                            // 0.0
/*204 */         break;                                                              // 0.0
/*208 */     case 0x0580:                                                            // 0.0
/*210 */         /* TTR: TIGbus Timing Register.  */                                 // 0.0
/*212 */         /* All sorts of stuff related to interrupt delivery timings.  */    // 0.0
/*214 */         break;                                                              // 0.0
/*216 */     case 0x05c0:                                                            // 0.0
/*218 */         /* TDR: TIGbug Device Timing Register.  */                          // 0.0
/*220 */         break;                                                              // 0.0
/*224 */     case 0x0600:                                                            // 0.0
/*226 */         /* DIM2: Device Interrupt Mask Register, CPU2.  */                  // 0.0
/*228 */         s->cchip.dim[2] = val;                                              // 0.0
/*230 */         cpu_irq_change(s->cchip.cpu[2], val & s->cchip.drir);               // 0.0
/*232 */         break;                                                              // 0.0
/*234 */     case 0x0640:                                                            // 0.0
/*236 */         /* DIM3: Device Interrupt Mask Register, CPU3.  */                  // 0.0
/*238 */         s->cchip.dim[3] = val;                                              // 0.0
/*240 */         cpu_irq_change(s->cchip.cpu[3], val & s->cchip.drir);               // 0.0
/*242 */         break;                                                              // 0.0
/*246 */     case 0x0680: /* DIR2 (RO) */                                            // 0.0
/*248 */     case 0x06c0: /* DIR3 (RO) */                                            // 0.0
/*250 */         break;                                                              // 0.0
/*254 */     case 0x0700: /* IIC2 */                                                 // 0.0
/*256 */         s->cchip.iic[2] = val & 0xffffff;                                   // 0.0
/*258 */         break;                                                              // 0.0
/*260 */     case 0x0740: /* IIC3 */                                                 // 0.0
/*262 */         s->cchip.iic[3] = val & 0xffffff;                                   // 0.0
/*264 */         break;                                                              // 0.0
/*268 */     case 0x0780:                                                            // 0.0
/*270 */         /* PWR: Power Management Control.   */                              // 0.0
/*272 */         break;                                                              // 0.0
/*274 */                                                                             // (25) 0.007812
/*276 */     case 0x0c00: /* CMONCTLA */                                             // 0.0
/*278 */     case 0x0c40: /* CMONCTLB */                                             // 0.0
/*280 */     case 0x0c80: /* CMONCNT01 */                                            // 0.0
/*282 */     case 0x0cc0: /* CMONCNT23 */                                            // 0.0
/*284 */         break;                                                              // 0.0
/*288 */     default:                                                                // 0.0
/*290 */         cpu_unassigned_access(current_cpu, addr, true, false, 0, size);     // 0.0
/*292 */         return;                                                             // 0.0
/*294 */     }                                                                       // 0.0
/*296 */ }                                                                           // 0.0
