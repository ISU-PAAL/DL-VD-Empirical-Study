// commit message qemu@f3172a0e2e (target=0, prob=0.029538218, correct=True): milkymist-sysctl: fix timers
/*0   */ static void sysctl_write(void *opaque, target_phys_addr_t addr, uint32_t value)  // (9) 0.05273
/*2   */ {                                                                                // (24) 0.001953
/*4   */     MilkymistSysctlState *s = opaque;                                            // (16) 0.02539
/*8   */     trace_milkymist_sysctl_memory_write(addr, value);                            // (11) 0.03906
/*12  */     addr >>= 2;                                                                  // (21) 0.01562
/*14  */     switch (addr) {                                                              // (20) 0.01562
/*16  */     case R_GPIO_OUT:                                                             // (18) 0.02148
/*18  */     case R_GPIO_INTEN:                                                           // (17) 0.02344
/*20  */     case R_TIMER0_COUNTER:                                                       // (13) 0.0293
/*22  */         if (value > s->regs[R_TIMER0_COUNTER]) {                                 // (6) 0.05469
/*24  */             value = s->regs[R_TIMER0_COUNTER];                                   // (4) 0.05664
/*26  */             error_report("milkymist_sysctl: timer0: trying to write a "          // (0) 0.05859
/*28  */                     "value greater than the limit. Clipping.");                  // (1) 0.05859
/*30  */         }                                                                        // (22) 0.01562
/*32  */         /* milkymist timer counts up */                                          // (12) 0.0293
/*34  */         value = s->regs[R_TIMER0_COUNTER] - value;                               // (7) 0.05469
/*36  */         ptimer_set_count(s->ptimer0, value);                                     // (10) 0.04297
/*38  */         break;                                                                   // (19) 0.01758
/*40  */     case R_TIMER1_COUNTER:                                                       // (15) 0.0293
/*42  */         if (value > s->regs[R_TIMER1_COUNTER]) {                                 // (8) 0.05469
/*44  */             value = s->regs[R_TIMER1_COUNTER];                                   // (5) 0.05664
/*46  */             error_report("milkymist_sysctl: timer1: trying to write a "          // (2) 0.05859
/*48  */                     "value greater than the limit. Clipping.");                  // (3) 0.05859
/*50  */         }                                                                        // (23) 0.01562
/*52  */         /* milkymist timer counts up */                                          // (14) 0.0293
/*54  */         value = s->regs[R_TIMER1_COUNTER] - value;                               // 0.0
/*56  */         ptimer_set_count(s->ptimer1, value);                                     // 0.0
/*58  */         break;                                                                   // 0.0
/*60  */     case R_TIMER0_COMPARE:                                                       // 0.0
/*62  */         ptimer_set_limit(s->ptimer0, value, 0);                                  // 0.0
/*64  */         s->regs[addr] = value;                                                   // 0.0
/*66  */         break;                                                                   // 0.0
/*68  */     case R_TIMER1_COMPARE:                                                       // 0.0
/*70  */         ptimer_set_limit(s->ptimer1, value, 0);                                  // 0.0
/*72  */         s->regs[addr] = value;                                                   // 0.0
/*74  */         break;                                                                   // 0.0
/*76  */     case R_TIMER0_CONTROL:                                                       // 0.0
/*78  */         s->regs[addr] = value;                                                   // 0.0
/*80  */         if (s->regs[R_TIMER0_CONTROL] & CTRL_ENABLE) {                           // 0.0
/*82  */             trace_milkymist_sysctl_start_timer1();                               // 0.0
/*84  */             ptimer_run(s->ptimer0, 0);                                           // 0.0
/*86  */         } else {                                                                 // 0.0
/*88  */             trace_milkymist_sysctl_stop_timer1();                                // 0.0
/*90  */             ptimer_stop(s->ptimer0);                                             // 0.0
/*92  */         }                                                                        // 0.0
/*94  */         break;                                                                   // 0.0
/*96  */     case R_TIMER1_CONTROL:                                                       // 0.0
/*98  */         s->regs[addr] = value;                                                   // 0.0
/*100 */         if (s->regs[R_TIMER1_CONTROL] & CTRL_ENABLE) {                           // 0.0
/*102 */             trace_milkymist_sysctl_start_timer1();                               // 0.0
/*104 */             ptimer_run(s->ptimer1, 0);                                           // 0.0
/*106 */         } else {                                                                 // 0.0
/*108 */             trace_milkymist_sysctl_stop_timer1();                                // 0.0
/*110 */             ptimer_stop(s->ptimer1);                                             // 0.0
/*112 */         }                                                                        // 0.0
/*114 */         break;                                                                   // 0.0
/*116 */     case R_ICAP:                                                                 // 0.0
/*118 */         sysctl_icap_write(s, value);                                             // 0.0
/*120 */         break;                                                                   // 0.0
/*122 */     case R_SYSTEM_ID:                                                            // 0.0
/*124 */         qemu_system_reset_request();                                             // 0.0
/*126 */         break;                                                                   // 0.0
/*130 */     case R_GPIO_IN:                                                              // 0.0
/*132 */     case R_CAPABILITIES:                                                         // 0.0
/*134 */         error_report("milkymist_sysctl: write to read-only register 0x"          // 0.0
/*136 */                 TARGET_FMT_plx, addr << 2);                                      // 0.0
/*138 */         break;                                                                   // 0.0
/*142 */     default:                                                                     // 0.0
/*144 */         error_report("milkymist_sysctl: write access to unkown register 0x"      // 0.0
/*146 */                 TARGET_FMT_plx, addr << 2);                                      // 0.0
/*148 */         break;                                                                   // 0.0
/*150 */     }                                                                            // 0.0
/*152 */ }                                                                                // 0.0
