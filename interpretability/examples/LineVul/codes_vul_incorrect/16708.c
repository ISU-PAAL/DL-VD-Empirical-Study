// commit message qemu@6982d6647e (target=1, prob=0.07747293, correct=False): hpet: Catch out-of-bounds timer access
/*0   */ static uint32_t hpet_ram_readl(void *opaque, target_phys_addr_t addr)             // (1) 0.05273
/*2   */ {                                                                                 // (23) 0.001953
/*4   */     HPETState *s = (HPETState *)opaque;                                           // (17) 0.0332
/*6   */     uint64_t cur_tick, index;                                                     // (19) 0.02539
/*10  */     DPRINTF("qemu: Enter hpet_ram_readl at %" PRIx64 "\n", addr);                 // (0) 0.06055
/*12  */     index = addr;                                                                 // (22) 0.01367
/*14  */     /*address range of all TN regs*/                                              // (20) 0.02344
/*16  */     if (index >= 0x100 && index <= 0x3ff) {                                       // (16) 0.03711
/*18  */         uint8_t timer_id = (addr - 0x100) / 0x20;                                 // (2) 0.05273
/*20  */         if (timer_id > HPET_NUM_TIMERS - 1) {                                     // (5) 0.04883
/*22  */             printf("qemu: timer id out of range\n");                              // (4) 0.04883
/*24  */             return 0;                                                             // (18) 0.02734
/*26  */         }                                                                         // (21) 0.01562
/*28  */         HPETTimer *timer = &s->timer[timer_id];                                   // (7) 0.04297
/*32  */         switch ((addr - 0x100) % 0x20) {                                          // (12) 0.04102
/*34  */             case HPET_TN_CFG:                                                     // (13) 0.03906
/*36  */                 return timer->config;                                             // (14) 0.03906
/*38  */             case HPET_TN_CFG + 4: // Interrupt capabilities                       // (3) 0.05078
/*40  */                 return timer->config >> 32;                                       // (8) 0.04297
/*42  */             case HPET_TN_CMP: // comparator register                              // (6) 0.04687
/*44  */                 return timer->cmp;                                                // (15) 0.03906
/*46  */             case HPET_TN_CMP + 4:                                                 // (9) 0.04297
/*48  */                 return timer->cmp >> 32;                                          // (10) 0.04297
/*50  */             case HPET_TN_ROUTE:                                                   // (11) 0.04102
/*52  */                 return timer->fsb >> 32;                                          // 0.0
/*54  */             default:                                                              // 0.0
/*56  */                 DPRINTF("qemu: invalid hpet_ram_readl\n");                        // 0.0
/*58  */                 break;                                                            // 0.0
/*60  */         }                                                                         // 0.0
/*62  */     } else {                                                                      // 0.0
/*64  */         switch (index) {                                                          // 0.0
/*66  */             case HPET_ID:                                                         // 0.0
/*68  */                 return s->capability;                                             // 0.0
/*70  */             case HPET_PERIOD:                                                     // 0.0
/*72  */                 return s->capability >> 32;                                       // 0.0
/*74  */             case HPET_CFG:                                                        // 0.0
/*76  */                 return s->config;                                                 // 0.0
/*78  */             case HPET_CFG + 4:                                                    // 0.0
/*80  */                 DPRINTF("qemu: invalid HPET_CFG + 4 hpet_ram_readl \n");          // 0.0
/*82  */                 return 0;                                                         // 0.0
/*84  */             case HPET_COUNTER:                                                    // 0.0
/*86  */                 if (hpet_enabled())                                               // 0.0
/*88  */                     cur_tick = hpet_get_ticks();                                  // 0.0
/*90  */                 else                                                              // 0.0
/*92  */                     cur_tick = s->hpet_counter;                                   // 0.0
/*94  */                 DPRINTF("qemu: reading counter  = %" PRIx64 "\n", cur_tick);      // 0.0
/*96  */                 return cur_tick;                                                  // 0.0
/*98  */             case HPET_COUNTER + 4:                                                // 0.0
/*100 */                 if (hpet_enabled())                                               // 0.0
/*102 */                     cur_tick = hpet_get_ticks();                                  // 0.0
/*104 */                 else                                                              // 0.0
/*106 */                     cur_tick = s->hpet_counter;                                   // 0.0
/*108 */                 DPRINTF("qemu: reading counter + 4  = %" PRIx64 "\n", cur_tick);  // 0.0
/*110 */                 return cur_tick >> 32;                                            // 0.0
/*112 */             case HPET_STATUS:                                                     // 0.0
/*114 */                 return s->isr;                                                    // 0.0
/*116 */             default:                                                              // 0.0
/*118 */                 DPRINTF("qemu: invalid hpet_ram_readl\n");                        // 0.0
/*120 */                 break;                                                            // 0.0
/*122 */         }                                                                         // 0.0
/*124 */     }                                                                             // 0.0
/*126 */     return 0;                                                                     // 0.0
/*128 */ }                                                                                 // 0.0
