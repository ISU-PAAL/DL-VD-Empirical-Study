// commit message qemu@a8170e5e97 (target=0, prob=0.024427913, correct=True): Rename target_phys_addr_t to hwaddr
/*0   */ static uint64_t hpet_ram_read(void *opaque, target_phys_addr_t addr,          // (4) 0.05078
/*2   */                               unsigned size)                                  // (0) 0.0625
/*4   */ {                                                                             // (25) 0.001953
/*6   */     HPETState *s = opaque;                                                    // (22) 0.02148
/*8   */     uint64_t cur_tick, index;                                                 // (20) 0.02539
/*12  */     DPRINTF("qemu: Enter hpet_ram_readl at %" PRIx64 "\n", addr);             // (1) 0.06055
/*14  */     index = addr;                                                             // (24) 0.01367
/*16  */     /*address range of all TN regs*/                                          // (21) 0.02344
/*18  */     if (index >= 0x100 && index <= 0x3ff) {                                   // (10) 0.03711
/*20  */         uint8_t timer_id = (addr - 0x100) / 0x20;                             // (2) 0.05273
/*22  */         HPETTimer *timer = &s->timer[timer_id];                               // (5) 0.04297
/*26  */         if (timer_id > s->num_timers) {                                       // (7) 0.04102
/*28  */             DPRINTF("qemu: timer id out of range\n");                         // (3) 0.05273
/*30  */             return 0;                                                         // (19) 0.02734
/*32  */         }                                                                     // (23) 0.01562
/*36  */         switch ((addr - 0x100) % 0x20) {                                      // (8) 0.04102
/*38  */         case HPET_TN_CFG:                                                     // (16) 0.03125
/*40  */             return timer->config;                                             // (17) 0.03125
/*42  */         case HPET_TN_CFG + 4: // Interrupt capabilities                       // (6) 0.04297
/*44  */             return timer->config >> 32;                                       // (11) 0.03516
/*46  */         case HPET_TN_CMP: // comparator register                              // (9) 0.03906
/*48  */             return timer->cmp;                                                // (18) 0.03125
/*50  */         case HPET_TN_CMP + 4:                                                 // (12) 0.03516
/*52  */             return timer->cmp >> 32;                                          // (13) 0.03516
/*54  */         case HPET_TN_ROUTE:                                                   // (14) 0.0332
/*56  */             return timer->fsb;                                                // (15) 0.0332
/*58  */         case HPET_TN_ROUTE + 4:                                               // 0.0
/*60  */             return timer->fsb >> 32;                                          // 0.0
/*62  */         default:                                                              // 0.0
/*64  */             DPRINTF("qemu: invalid hpet_ram_readl\n");                        // 0.0
/*66  */             break;                                                            // 0.0
/*68  */         }                                                                     // 0.0
/*70  */     } else {                                                                  // 0.0
/*72  */         switch (index) {                                                      // 0.0
/*74  */         case HPET_ID:                                                         // 0.0
/*76  */             return s->capability;                                             // 0.0
/*78  */         case HPET_PERIOD:                                                     // 0.0
/*80  */             return s->capability >> 32;                                       // 0.0
/*82  */         case HPET_CFG:                                                        // 0.0
/*84  */             return s->config;                                                 // 0.0
/*86  */         case HPET_CFG + 4:                                                    // 0.0
/*88  */             DPRINTF("qemu: invalid HPET_CFG + 4 hpet_ram_readl\n");           // 0.0
/*90  */             return 0;                                                         // 0.0
/*92  */         case HPET_COUNTER:                                                    // 0.0
/*94  */             if (hpet_enabled(s)) {                                            // 0.0
/*96  */                 cur_tick = hpet_get_ticks(s);                                 // 0.0
/*98  */             } else {                                                          // 0.0
/*100 */                 cur_tick = s->hpet_counter;                                   // 0.0
/*102 */             }                                                                 // 0.0
/*104 */             DPRINTF("qemu: reading counter  = %" PRIx64 "\n", cur_tick);      // 0.0
/*106 */             return cur_tick;                                                  // 0.0
/*108 */         case HPET_COUNTER + 4:                                                // 0.0
/*110 */             if (hpet_enabled(s)) {                                            // 0.0
/*112 */                 cur_tick = hpet_get_ticks(s);                                 // 0.0
/*114 */             } else {                                                          // 0.0
/*116 */                 cur_tick = s->hpet_counter;                                   // 0.0
/*118 */             }                                                                 // 0.0
/*120 */             DPRINTF("qemu: reading counter + 4  = %" PRIx64 "\n", cur_tick);  // 0.0
/*122 */             return cur_tick >> 32;                                            // 0.0
/*124 */         case HPET_STATUS:                                                     // 0.0
/*126 */             return s->isr;                                                    // 0.0
/*128 */         default:                                                              // 0.0
/*130 */             DPRINTF("qemu: invalid hpet_ram_readl\n");                        // 0.0
/*132 */             break;                                                            // 0.0
/*134 */         }                                                                     // 0.0
/*136 */     }                                                                         // 0.0
/*138 */     return 0;                                                                 // 0.0
/*140 */ }                                                                             // 0.0
