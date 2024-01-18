// commit message qemu@72cf2d4f0e (target=0, prob=0.07981065, correct=True): Fix sys-queue.h conflict for good
/*0  */ int select_watchdog(const char *p)                                          // (16) 0.0235
/*2  */ {                                                                           // (25) 0.002137
/*4  */     WatchdogTimerModel *model;                                              // (17) 0.02137
/*6  */     QemuOpts *opts;                                                         // (15) 0.02564
/*10 */     /* -watchdog ? lists available devices and exits cleanly. */            // (11) 0.03632
/*12 */     if (strcmp(p, "?") == 0) {                                              // (12) 0.03632
/*14 */         LIST_FOREACH(model, &watchdog_list, entry) {                        // (7) 0.04915
/*16 */             fprintf(stderr, "\t%s\t%s\n",                                   // (3) 0.06197
/*18 */                      model->wdt_name, model->wdt_description);              // (1) 0.07265
/*20 */         }                                                                   // (19) 0.01709
/*22 */         return 2;                                                           // (18) 0.02137
/*24 */     }                                                                       // (22) 0.008547
/*28 */     LIST_FOREACH(model, &watchdog_list, entry) {                            // (9) 0.0406
/*30 */         if (strcasecmp(model->wdt_name, p) == 0) {                          // (5) 0.05556
/*32 */             /* add the device */                                            // (13) 0.03419
/*34 */             opts = qemu_opts_create(&qemu_device_opts, NULL, 0);            // (0) 0.07692
/*36 */             qemu_opt_set(opts, "driver", p);                                // (4) 0.05769
/*38 */             return 0;                                                       // (14) 0.02991
/*40 */         }                                                                   // (20) 0.01709
/*42 */     }                                                                       // (23) 0.008547
/*46 */     fprintf(stderr, "Unknown -watchdog device. Supported devices are:\n");  // (8) 0.04915
/*48 */     LIST_FOREACH(model, &watchdog_list, entry) {                            // (10) 0.0406
/*50 */         fprintf(stderr, "\t%s\t%s\n",                                       // (6) 0.05342
/*52 */                  model->wdt_name, model->wdt_description);                  // (2) 0.0641
/*54 */     }                                                                       // (24) 0.008547
/*56 */     return 1;                                                               // (21) 0.01282
/*58 */ }                                                                           // (26) 0.002137
