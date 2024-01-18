// commit message qemu@7bd427d801 (target=0, prob=0.06163057, correct=True): change all rt_clock references to use millisecond resolution accessors
/*0  */ static int twl92230_init(i2c_slave *i2c)                           // (5) 0.08658
/*2  */ {                                                                  // (9) 0.004329
/*4  */     MenelausState *s = FROM_I2C_SLAVE(MenelausState, i2c);         // (3) 0.1255
/*8  */     s->rtc.hz_tm = qemu_new_timer(rt_clock, menelaus_rtc_hz, s);   // (0) 0.1515
/*10 */     /* Three output pins plus one interrupt pin.  */               // (7) 0.06061
/*12 */     qdev_init_gpio_out(&i2c->qdev, s->out, 4);                     // (4) 0.1126
/*14 */     qdev_init_gpio_in(&i2c->qdev, menelaus_gpio_set, 3);           // (2) 0.1342
/*16 */     s->pwrbtn = qemu_allocate_irqs(menelaus_pwrbtn_set, s, 1)[0];  // (1) 0.1515
/*20 */     menelaus_reset(&s->i2c);                                       // (6) 0.06494
/*24 */     return 0;                                                      // (8) 0.02597
/*26 */ }                                                                  // (10) 0.004329
