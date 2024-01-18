// commit message qemu@6240d64670 (target=0, prob=0.030563224, correct=True):  Fix setting counter limit to 0 (Robert Reif)
/*0   */ static void slavio_timer_mem_writel(void *opaque, target_phys_addr_t addr,      // (6) 0.05273
/*2   */                                     uint32_t val)                               // (0) 0.08008
/*4   */ {                                                                               // (22) 0.001953
/*6   */     SLAVIO_TIMERState *s = opaque;                                              // (16) 0.03125
/*8   */     uint32_t saddr;                                                             // (18) 0.01953
/*10  */     int reload = 0;                                                             // (21) 0.01563
/*14  */     DPRINTF("write " TARGET_FMT_plx " %08x\n", addr, val);                      // (4) 0.05469
/*16  */     saddr = (addr & TIMER_MAXADDR) >> 2;                                        // (13) 0.03711
/*18  */     switch (saddr) {                                                            // (20) 0.01758
/*20  */     case TIMER_LIMIT:                                                           // (17) 0.02148
/*22  */         if (slavio_timer_is_user(s)) {                                          // (11) 0.04297
/*24  */             // set user counter MSW, reset counter                              // (12) 0.03906
/*26  */             qemu_irq_lower(s->irq);                                             // (8) 0.04883
/*28  */             s->limit = TIMER_MAX_COUNT64;                                       // (10) 0.04687
/*30  */             DPRINTF("processor %d user timer reset\n", s->slave_index);         // (2) 0.05859
/*32  */             ptimer_set_limit(s->timer, LIMIT_TO_PERIODS(s->limit), 1);          // (1) 0.07422
/*34  */         } else {                                                                // (19) 0.01953
/*36  */             // set limit, reset counter                                         // (14) 0.0332
/*38  */             qemu_irq_lower(s->irq);                                             // (9) 0.04883
/*40  */             s->limit = val & TIMER_MAX_COUNT32;                                 // (7) 0.05078
/*42  */             if (!s->limit)                                                      // (15) 0.0332
/*44  */                 s->limit = TIMER_MAX_COUNT32;                                   // (5) 0.05469
/*46  */             ptimer_set_limit(s->timer, s->limit >> 9, 1);                       // (3) 0.05859
/*48  */         }                                                                       // 0.0
/*50  */         break;                                                                  // 0.0
/*52  */     case TIMER_COUNTER:                                                         // 0.0
/*54  */         if (slavio_timer_is_user(s)) {                                          // 0.0
/*56  */             // set user counter LSW, reset counter                              // 0.0
/*58  */             qemu_irq_lower(s->irq);                                             // 0.0
/*60  */             s->limit = TIMER_MAX_COUNT64;                                       // 0.0
/*62  */             DPRINTF("processor %d user timer reset\n", s->slave_index);         // 0.0
/*64  */             ptimer_set_limit(s->timer, LIMIT_TO_PERIODS(s->limit), 1);          // 0.0
/*66  */         } else                                                                  // 0.0
/*68  */             DPRINTF("not user timer\n");                                        // 0.0
/*70  */         break;                                                                  // 0.0
/*72  */     case TIMER_COUNTER_NORST:                                                   // 0.0
/*74  */         // set limit without resetting counter                                  // 0.0
/*76  */         s->limit = val & TIMER_MAX_COUNT32;                                     // 0.0
/*78  */         if (!s->limit)                                                          // 0.0
/*80  */             s->limit = TIMER_MAX_COUNT32;                                       // 0.0
/*82  */         ptimer_set_limit(s->timer, LIMIT_TO_PERIODS(s->limit), reload);         // 0.0
/*84  */         break;                                                                  // 0.0
/*86  */     case TIMER_STATUS:                                                          // 0.0
/*88  */         if (slavio_timer_is_user(s)) {                                          // 0.0
/*90  */             // start/stop user counter                                          // 0.0
/*92  */             if ((val & 1) && !s->running) {                                     // 0.0
/*94  */                 DPRINTF("processor %d user timer started\n", s->slave_index);   // 0.0
/*96  */                 ptimer_run(s->timer, 0);                                        // 0.0
/*98  */                 s->running = 1;                                                 // 0.0
/*100 */             } else if (!(val & 1) && s->running) {                              // 0.0
/*102 */                 DPRINTF("processor %d user timer stopped\n", s->slave_index);   // 0.0
/*104 */                 ptimer_stop(s->timer);                                          // 0.0
/*106 */                 s->running = 0;                                                 // 0.0
/*108 */             }                                                                   // 0.0
/*110 */         }                                                                       // 0.0
/*112 */         break;                                                                  // 0.0
/*114 */     case TIMER_MODE:                                                            // 0.0
/*116 */         if (s->master == NULL) {                                                // 0.0
/*118 */             unsigned int i;                                                     // 0.0
/*122 */             for (i = 0; i < s->num_slaves; i++) {                               // 0.0
/*124 */                 if (val & (1 << i)) {                                           // 0.0
/*126 */                     qemu_irq_lower(s->slave[i]->irq);                           // 0.0
/*128 */                     s->slave[i]->limit = -1ULL;                                 // 0.0
/*130 */                 }                                                               // 0.0
/*132 */                 if ((val & (1 << i)) != (s->slave_mode & (1 << i))) {           // 0.0
/*134 */                     ptimer_stop(s->slave[i]->timer);                            // 0.0
/*136 */                     ptimer_set_limit(s->slave[i]->timer,                        // 0.0
/*138 */                                      LIMIT_TO_PERIODS(s->slave[i]->limit), 1);  // 0.0
/*140 */                     DPRINTF("processor %d timer changed\n",                     // 0.0
/*142 */                             s->slave[i]->slave_index);                          // 0.0
/*144 */                     ptimer_run(s->slave[i]->timer, 0);                          // 0.0
/*146 */                 }                                                               // 0.0
/*148 */             }                                                                   // 0.0
/*150 */             s->slave_mode = val & ((1 << s->num_slaves) - 1);                   // 0.0
/*152 */         } else                                                                  // 0.0
/*154 */             DPRINTF("not system timer\n");                                      // 0.0
/*156 */         break;                                                                  // 0.0
/*158 */     default:                                                                    // 0.0
/*160 */         DPRINTF("invalid write address " TARGET_FMT_plx "\n", addr);            // 0.0
/*162 */         break;                                                                  // 0.0
/*164 */     }                                                                           // 0.0
/*166 */ }                                                                               // 0.0
