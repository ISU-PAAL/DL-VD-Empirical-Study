// commit message qemu@9abc62f644 (target=0, prob=0.32702753, correct=True): vl: drop is_suspended variable
/*0  */ void qemu_system_wakeup_request(WakeupReason reason)   // (3) 0.09783
/*2  */ {                                                      // (13) 0.005435
/*4  */     if (!is_suspended) {                               // (6) 0.05978
/*6  */         return;                                        // (9) 0.04891
/*8  */     }                                                  // (11) 0.02174
/*10 */     if (!(wakeup_reason_mask & (1 << reason))) {       // (2) 0.1033
/*12 */         return;                                        // (10) 0.04891
/*14 */     }                                                  // (12) 0.02174
/*16 */     runstate_set(RUN_STATE_RUNNING);                   // (4) 0.09239
/*18 */     monitor_protocol_event(QEVENT_WAKEUP, NULL);       // (0) 0.1087
/*20 */     notifier_list_notify(&wakeup_notifiers, &reason);  // (1) 0.1087
/*22 */     reset_requested = 1;                               // (7) 0.05435
/*24 */     qemu_notify_event();                               // (5) 0.06522
/*26 */     is_suspended = false;                              // (8) 0.05435
/*28 */ }                                                      // (14) 0.005435
