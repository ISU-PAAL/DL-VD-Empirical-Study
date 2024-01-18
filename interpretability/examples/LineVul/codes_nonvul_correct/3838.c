// commit message qemu@048c74c437 (target=0, prob=0.053984236, correct=True): mc145818rtc: fix saving of rtc-td hack properly upgrading the version number
/*0  */ static int rtc_initfn(ISADevice *dev)                                             // (14) 0.0293
/*2  */ {                                                                                 // (22) 0.001953
/*4  */     RTCState *s = DO_UPCAST(RTCState, dev, dev);                                  // (7) 0.04492
/*6  */     int base = 0x70;                                                              // (18) 0.01953
/*8  */     int isairq = 8;                                                               // (19) 0.01953
/*12 */     isa_init_irq(dev, &s->irq, isairq);                                           // (8) 0.04492
/*16 */     s->cmos_data[RTC_REG_A] = 0x26;                                               // (9) 0.04297
/*18 */     s->cmos_data[RTC_REG_B] = 0x02;                                               // (10) 0.04297
/*20 */     s->cmos_data[RTC_REG_C] = 0x00;                                               // (11) 0.04297
/*22 */     s->cmos_data[RTC_REG_D] = 0x80;                                               // (12) 0.04297
/*26 */     rtc_set_date_from_host(s);                                                    // (13) 0.03125
/*30 */     s->periodic_timer = qemu_new_timer(rtc_clock, rtc_periodic_timer, s);         // (2) 0.06445
/*32 */ #ifdef TARGET_I386                                                                // (20) 0.01562
/*34 */     if (rtc_td_hack)                                                              // (16) 0.02344
/*36 */         s->coalesced_timer =                                                      // (15) 0.0293
/*38 */             qemu_new_timer(rtc_clock, rtc_coalesced_timer, s);                    // (1) 0.06836
/*40 */ #endif                                                                            // (21) 0.003906
/*42 */     s->second_timer = qemu_new_timer(rtc_clock, rtc_update_second, s);            // (4) 0.06055
/*44 */     s->second_timer2 = qemu_new_timer(rtc_clock, rtc_update_second2, s);          // (3) 0.06445
/*48 */     s->next_second_time =                                                         // (17) 0.02148
/*50 */         qemu_get_clock(rtc_clock) + (get_ticks_per_sec() * 99) / 100;             // (0) 0.07227
/*52 */     qemu_mod_timer(s->second_timer2, s->next_second_time);                        // (5) 0.05078
/*56 */     register_ioport_write(base, 2, 1, cmos_ioport_write, s);                      // (6) 0.05078
/*58 */     register_ioport_read(base, 2, 1, cmos_ioport_read, s);                        // 0.0
/*62 */     register_savevm("mc146818rtc", base, 1, rtc_save, rtc_load, s);               // 0.0
/*64 */ #ifdef TARGET_I386                                                                // 0.0
/*66 */     if (rtc_td_hack)                                                              // 0.0
/*68 */         register_savevm("mc146818rtc-td", base, 1, rtc_save_td, rtc_load_td, s);  // 0.0
/*70 */ #endif                                                                            // 0.0
/*72 */     qemu_register_reset(rtc_reset, s);                                            // 0.0
/*74 */     return 0;                                                                     // 0.0
/*76 */ }                                                                                 // 0.0
