// commit message qemu@84ebd3e8c7 (target=1, prob=0.9990671, correct=True): watchdog/wdt_diag288: Mark diag288 watchdog as non-hotpluggable
/*0  */ static void wdt_diag288_class_init(ObjectClass *klass, void *data)  // (0) 0.1173
/*2  */ {                                                                   // (9) 0.005102
/*4  */     DeviceClass *dc = DEVICE_CLASS(klass);                          // (7) 0.08163
/*6  */     DIAG288Class *diag288 = DIAG288_CLASS(klass);                   // (2) 0.1173
/*10 */     dc->realize = wdt_diag288_realize;                              // (5) 0.09184
/*12 */     dc->unrealize = wdt_diag288_unrealize;                          // (4) 0.102
/*14 */     dc->reset = wdt_diag288_reset;                                  // (8) 0.08163
/*17 */     set_bit(DEVICE_CATEGORY_MISC, dc->categories);                  // (1) 0.1173
/*19 */     dc->vmsd = &vmstate_diag288;                                    // (6) 0.08673
/*21 */     diag288->handle_timer = wdt_diag288_handle_timer;               // (3) 0.1122
/*23 */ }                                                                   // (10) 0.005102
