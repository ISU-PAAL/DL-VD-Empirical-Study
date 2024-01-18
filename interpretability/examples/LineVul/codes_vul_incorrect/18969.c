// commit message qemu@27bb0b2d6f (target=1, prob=0.05639281, correct=False): hpet: Coding style cleanups and some refactorings
/*0   */ static void hpet_ram_writel(void *opaque, target_phys_addr_t addr,                    // (7) 0.04688
/*2   */                             uint32_t value)                                           // (3) 0.06445
/*4   */ {                                                                                     // (21) 0.001953
/*6   */     int i;                                                                            // (20) 0.01172
/*8   */     HPETState *s = (HPETState *)opaque;                                               // (14) 0.0332
/*10  */     uint64_t old_val, new_val, val, index;                                            // (12) 0.03711
/*14  */     DPRINTF("qemu: Enter hpet_ram_writel at %" PRIx64 " = %#x\n", addr, value);       // (1) 0.07422
/*16  */     index = addr;                                                                     // (19) 0.01367
/*18  */     old_val = hpet_ram_readl(opaque, addr);                                           // (10) 0.03906
/*20  */     new_val = value;                                                                  // (17) 0.01758
/*24  */     /*address range of all TN regs*/                                                  // (16) 0.02344
/*26  */     if (index >= 0x100 && index <= 0x3ff) {                                           // (13) 0.03711
/*28  */         uint8_t timer_id = (addr - 0x100) / 0x20;                                     // (4) 0.05273
/*30  */         DPRINTF("qemu: hpet_ram_writel timer_id = %#x \n", timer_id);                 // (2) 0.07031
/*32  */         HPETTimer *timer = &s->timer[timer_id];                                       // (8) 0.04297
/*36  */         if (timer_id > HPET_NUM_TIMERS - 1) {                                         // (6) 0.04883
/*38  */             DPRINTF("qemu: timer id out of range\n");                                 // (5) 0.05273
/*40  */             return;                                                                   // (15) 0.02539
/*42  */         }                                                                             // (18) 0.01562
/*44  */         switch ((addr - 0x100) % 0x20) {                                              // (9) 0.04102
/*46  */             case HPET_TN_CFG:                                                         // (11) 0.03906
/*48  */                 DPRINTF("qemu: hpet_ram_writel HPET_TN_CFG\n");                       // (0) 0.07812
/*50  */                 val = hpet_fixup_reg(new_val, old_val, HPET_TN_CFG_WRITE_MASK);       // 0.0
/*52  */                 timer->config = (timer->config & 0xffffffff00000000ULL) | val;        // 0.0
/*54  */                 if (new_val & HPET_TN_32BIT) {                                        // 0.0
/*56  */                     timer->cmp = (uint32_t)timer->cmp;                                // 0.0
/*58  */                     timer->period = (uint32_t)timer->period;                          // 0.0
/*60  */                 }                                                                     // 0.0
/*62  */                 if (new_val & HPET_TIMER_TYPE_LEVEL) {                                // 0.0
/*64  */                     printf("qemu: level-triggered hpet not supported\n");             // 0.0
/*66  */                     exit (-1);                                                        // 0.0
/*68  */                 }                                                                     // 0.0
/*72  */                 break;                                                                // 0.0
/*74  */             case HPET_TN_CFG + 4: // Interrupt capabilities                           // 0.0
/*76  */                 DPRINTF("qemu: invalid HPET_TN_CFG+4 write\n");                       // 0.0
/*78  */                 break;                                                                // 0.0
/*80  */             case HPET_TN_CMP: // comparator register                                  // 0.0
/*82  */                 DPRINTF("qemu: hpet_ram_writel HPET_TN_CMP \n");                      // 0.0
/*84  */                 if (timer->config & HPET_TN_32BIT)                                    // 0.0
/*86  */                     new_val = (uint32_t)new_val;                                      // 0.0
/*88  */                 if (!timer_is_periodic(timer) ||                                      // 0.0
/*90  */                            (timer->config & HPET_TN_SETVAL))                          // 0.0
/*92  */                     timer->cmp = (timer->cmp & 0xffffffff00000000ULL)                 // 0.0
/*94  */                                   | new_val;                                          // 0.0
/*96  */                 if (timer_is_periodic(timer)) {                                       // 0.0
/*98  */                     /*                                                                // 0.0
/*100 */                      * FIXME: Clamp period to reasonable min value?                   // 0.0
/*102 */                      * Clamp period to reasonable max value                           // 0.0
/*104 */                      */                                                               // 0.0
/*106 */                     new_val &= (timer->config & HPET_TN_32BIT ? ~0u : ~0ull) >> 1;    // 0.0
/*108 */                     timer->period = (timer->period & 0xffffffff00000000ULL)           // 0.0
/*110 */                                      | new_val;                                       // 0.0
/*112 */                 }                                                                     // 0.0
/*114 */                 timer->config &= ~HPET_TN_SETVAL;                                     // 0.0
/*116 */                 if (hpet_enabled())                                                   // 0.0
/*118 */                     hpet_set_timer(timer);                                            // 0.0
/*120 */                 break;                                                                // 0.0
/*122 */             case HPET_TN_CMP + 4: // comparator register high order                   // 0.0
/*124 */                 DPRINTF("qemu: hpet_ram_writel HPET_TN_CMP + 4\n");                   // 0.0
/*126 */                 if (!timer_is_periodic(timer) ||                                      // 0.0
/*128 */                            (timer->config & HPET_TN_SETVAL))                          // 0.0
/*130 */                     timer->cmp = (timer->cmp & 0xffffffffULL)                         // 0.0
/*132 */                                   | new_val << 32;                                    // 0.0
/*134 */                 else {                                                                // 0.0
/*136 */                     /*                                                                // 0.0
/*138 */                      * FIXME: Clamp period to reasonable min value?                   // 0.0
/*140 */                      * Clamp period to reasonable max value                           // 0.0
/*142 */                      */                                                               // 0.0
/*144 */                     new_val &= (timer->config                                         // 0.0
/*146 */                                 & HPET_TN_32BIT ? ~0u : ~0ull) >> 1;                  // 0.0
/*148 */                     timer->period = (timer->period & 0xffffffffULL)                   // 0.0
/*150 */                                      | new_val << 32;                                 // 0.0
/*152 */                 }                                                                     // 0.0
/*154 */                 timer->config &= ~HPET_TN_SETVAL;                                     // 0.0
/*156 */                 if (hpet_enabled())                                                   // 0.0
/*158 */                     hpet_set_timer(timer);                                            // 0.0
/*160 */                 break;                                                                // 0.0
/*162 */             case HPET_TN_ROUTE + 4:                                                   // 0.0
/*164 */                 DPRINTF("qemu: hpet_ram_writel HPET_TN_ROUTE + 4\n");                 // 0.0
/*166 */                 break;                                                                // 0.0
/*168 */             default:                                                                  // 0.0
/*170 */                 DPRINTF("qemu: invalid hpet_ram_writel\n");                           // 0.0
/*172 */                 break;                                                                // 0.0
/*174 */         }                                                                             // 0.0
/*176 */         return;                                                                       // 0.0
/*178 */     } else {                                                                          // 0.0
/*180 */         switch (index) {                                                              // 0.0
/*182 */             case HPET_ID:                                                             // 0.0
/*184 */                 return;                                                               // 0.0
/*186 */             case HPET_CFG:                                                            // 0.0
/*188 */                 val = hpet_fixup_reg(new_val, old_val, HPET_CFG_WRITE_MASK);          // 0.0
/*190 */                 s->config = (s->config & 0xffffffff00000000ULL) | val;                // 0.0
/*192 */                 if (activating_bit(old_val, new_val, HPET_CFG_ENABLE)) {              // 0.0
/*194 */                     /* Enable main counter and interrupt generation. */               // 0.0
/*196 */                     s->hpet_offset = ticks_to_ns(s->hpet_counter)                     // 0.0
/*198 */                                      - qemu_get_clock(vm_clock);                      // 0.0
/*200 */                     for (i = 0; i < HPET_NUM_TIMERS; i++)                             // 0.0
/*202 */                         if ((&s->timer[i])->cmp != ~0ULL)                             // 0.0
/*204 */                             hpet_set_timer(&s->timer[i]);                             // 0.0
/*206 */                 }                                                                     // 0.0
/*208 */                 else if (deactivating_bit(old_val, new_val, HPET_CFG_ENABLE)) {       // 0.0
/*210 */                     /* Halt main counter and disable interrupt generation. */         // 0.0
/*212 */                     s->hpet_counter = hpet_get_ticks();                               // 0.0
/*214 */                     for (i = 0; i < HPET_NUM_TIMERS; i++)                             // 0.0
/*216 */                         hpet_del_timer(&s->timer[i]);                                 // 0.0
/*218 */                 }                                                                     // 0.0
/*220 */                 /* i8254 and RTC are disabled when HPET is in legacy mode */          // 0.0
/*222 */                 if (activating_bit(old_val, new_val, HPET_CFG_LEGACY)) {              // 0.0
/*224 */                     hpet_pit_disable();                                               // 0.0
/*226 */                 } else if (deactivating_bit(old_val, new_val, HPET_CFG_LEGACY)) {     // 0.0
/*228 */                     hpet_pit_enable();                                                // 0.0
/*230 */                 }                                                                     // 0.0
/*232 */                 break;                                                                // 0.0
/*234 */             case HPET_CFG + 4:                                                        // 0.0
/*236 */                 DPRINTF("qemu: invalid HPET_CFG+4 write \n");                         // 0.0
/*238 */                 break;                                                                // 0.0
/*240 */             case HPET_STATUS:                                                         // 0.0
/*242 */                 /* FIXME: need to handle level-triggered interrupts */                // 0.0
/*244 */                 break;                                                                // 0.0
/*246 */             case HPET_COUNTER:                                                        // 0.0
/*248 */                if (hpet_enabled())                                                    // 0.0
/*250 */                    printf("qemu: Writing counter while HPET enabled!\n");             // 0.0
/*252 */                s->hpet_counter = (s->hpet_counter & 0xffffffff00000000ULL)            // 0.0
/*254 */                                   | value;                                            // 0.0
/*256 */                DPRINTF("qemu: HPET counter written. ctr = %#x -> %" PRIx64 "\n",      // 0.0
/*258 */                         value, s->hpet_counter);                                      // 0.0
/*260 */                break;                                                                 // 0.0
/*262 */             case HPET_COUNTER + 4:                                                    // 0.0
/*264 */                if (hpet_enabled())                                                    // 0.0
/*266 */                    printf("qemu: Writing counter while HPET enabled!\n");             // 0.0
/*268 */                s->hpet_counter = (s->hpet_counter & 0xffffffffULL)                    // 0.0
/*270 */                                   | (((uint64_t)value) << 32);                        // 0.0
/*272 */                DPRINTF("qemu: HPET counter + 4 written. ctr = %#x -> %" PRIx64 "\n",  // 0.0
/*274 */                         value, s->hpet_counter);                                      // 0.0
/*276 */                break;                                                                 // 0.0
/*278 */             default:                                                                  // 0.0
/*280 */                DPRINTF("qemu: invalid hpet_ram_writel\n");                            // 0.0
/*282 */                break;                                                                 // 0.0
/*284 */         }                                                                             // 0.0
/*286 */     }                                                                                 // 0.0
/*288 */ }                                                                                     // 0.0
