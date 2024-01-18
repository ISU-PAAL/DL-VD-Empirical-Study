// commit message qemu@c60bf3391b (target=0, prob=0.33671692, correct=True): readline: decouple readline from the monitor
/*0  */ static void bdrv_password_cb(Monitor *mon, const char *password, void *opaque)  // (1) 0.1379
/*2  */ {                                                                               // (10) 0.005747
/*4  */     BlockDriverState *bs = opaque;                                              // (7) 0.06322
/*6  */     int ret = 0;                                                                // (8) 0.04598
/*10 */     if (bdrv_set_key(bs, password) != 0) {                                      // (2) 0.1207
/*12 */         monitor_printf(mon, "invalid password\n");                              // (3) 0.1149
/*14 */         ret = -EPERM;                                                           // (5) 0.08046
/*16 */     }                                                                           // (9) 0.02299
/*18 */     if (mon->password_completion_cb)                                            // (4) 0.08046
/*20 */         mon->password_completion_cb(mon->password_opaque, ret);                 // (0) 0.1437
/*24 */     monitor_read_command(mon, 1);                                               // (6) 0.07471
/*26 */ }                                                                               // (11) 0.005747
