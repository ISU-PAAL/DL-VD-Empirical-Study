// commit message qemu@1bcef683bf (target=0, prob=0.5812113, correct=False): Drop the incoming_expected global variable
/*0  */ void process_incoming_migration(QEMUFile *f)            // (3) 0.08791
/*2  */ {                                                       // (13) 0.005495
/*4  */     if (qemu_loadvm_state(f) < 0) {                     // (1) 0.1099
/*6  */         fprintf(stderr, "load of migration failed\n");  // (0) 0.1209
/*8  */         exit(0);                                        // (7) 0.06044
/*10 */     }                                                   // (11) 0.02198
/*12 */     qemu_announce_self();                               // (5) 0.06593
/*14 */     DPRINTF("successfully loaded vm state\n");          // (4) 0.07692
/*18 */     incoming_expected = false;                          // (9) 0.04945
/*22 */     if (autostart) {                                    // (8) 0.05495
/*24 */         vm_start();                                     // (6) 0.06044
/*26 */     } else {                                            // (10) 0.03297
/*28 */         runstate_set(RSTATE_PRE_LAUNCH);                // (2) 0.1099
/*30 */     }                                                   // (12) 0.02198
/*32 */ }                                                       // (14) 0.005495
