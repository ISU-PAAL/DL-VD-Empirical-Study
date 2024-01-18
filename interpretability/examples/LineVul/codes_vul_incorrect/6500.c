// commit message qemu@e13e973eed (target=1, prob=0.17135823, correct=False): usb-ccid: Plug memory leak on qdev exit()
/*0  */ static int ccid_initfn(USBDevice *dev)                    // (13) 0.03963
/*2  */ {                                                         // (21) 0.003049
/*4  */     USBCCIDState *s = DO_UPCAST(USBCCIDState, dev, dev);  // (0) 0.08232
/*8  */     s->bus = ccid_bus_new(&dev->qdev);                    // (1) 0.05793
/*10 */     s->card = NULL;                                       // (18) 0.02744
/*12 */     s->cardinfo = NULL;                                   // (16) 0.03049
/*14 */     s->migration_state = MIGRATION_NONE;                  // (2) 0.05488
/*16 */     s->migration_target_ip = 0;                           // (7) 0.04268
/*18 */     s->migration_target_port = 0;                         // (8) 0.04268
/*20 */     s->dev.speed = USB_SPEED_FULL;                        // (3) 0.05183
/*22 */     s->notify_slot_change = false;                        // (9) 0.04268
/*24 */     s->powered = true;                                    // (19) 0.02744
/*26 */     s->pending_answers_num = 0;                           // (6) 0.04878
/*28 */     s->last_answer_error = 0;                             // (14) 0.03963
/*30 */     s->bulk_in_pending_start = 0;                         // (4) 0.05183
/*32 */     s->bulk_in_pending_end = 0;                           // (5) 0.05183
/*34 */     s->current_bulk_in = NULL;                            // (10) 0.04268
/*36 */     ccid_reset_error_status(s);                           // (11) 0.04268
/*38 */     s->bulk_out_pos = 0;                                  // (12) 0.04268
/*40 */     ccid_reset_parameters(s);                             // (15) 0.03963
/*42 */     ccid_reset(s);                                        // (17) 0.03049
/*44 */     return 0;                                             // (20) 0.01829
/*46 */ }                                                         // (22) 0.003049
