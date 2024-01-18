// commit message qemu@bf43330aa4 (target=1, prob=0.07383486, correct=False): sun4u: split NPT and INT_DIS accesses between timer and compare registers
/*0  */ void cpu_tick_set_count(CPUTimer *timer, uint64_t count)               // (5) 0.07836
/*2  */ {                                                                      // (10) 0.003731
/*4  */     uint64_t real_count = count & ~timer->disabled_mask;               // (6) 0.07463
/*6  */     uint64_t disabled_bit = count & timer->disabled_mask;              // (7) 0.0709
/*10 */     int64_t vm_clock_offset = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) -  // (1) 0.1306
/*12 */                     cpu_to_timer_ticks(real_count, timer->frequency);  // (0) 0.1343
/*16 */     TIMER_DPRINTF("%s set_count count=0x%016lx (%s) p=%p\n",           // (2) 0.1269
/*18 */                   timer->name, real_count,                             // (4) 0.09328
/*20 */                   timer->disabled?"disabled":"enabled", timer);        // (3) 0.1007
/*24 */     timer->disabled = disabled_bit ? 1 : 0;                            // (8) 0.05597
/*26 */     timer->clock_offset = vm_clock_offset;                             // (9) 0.05597
/*28 */ }                                                                      // (11) 0.003731
