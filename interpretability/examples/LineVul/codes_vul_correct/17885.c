// commit message qemu@da5361cc68 (target=1, prob=0.6686872, correct=True): ccid: make threads joinable
/*0  */ static int emulated_exitfn(CCIDCardState *base)                        // (15) 0.03866
/*2  */ {                                                                      // (17) 0.002577
/*4  */     EmulatedState *card = DO_UPCAST(EmulatedState, base, base);        // (4) 0.05928
/*6  */     VEvent *vevent = vevent_new(VEVENT_LAST, NULL, NULL);              // (1) 0.06443
/*10 */     vevent_queue_vevent(vevent); /* stop vevent thread */              // (12) 0.05155
/*12 */     qemu_mutex_lock(&card->apdu_thread_quit_mutex);                    // (2) 0.06185
/*14 */     card->quit_apdu_thread = 1; /* stop handle_apdu thread */          // (5) 0.0567
/*16 */     qemu_cond_signal(&card->handle_apdu_cond);                         // (10) 0.05412
/*18 */     qemu_cond_wait(&card->apdu_thread_quit_cond,                       // (7) 0.0567
/*20 */                       &card->apdu_thread_quit_mutex);                  // (0) 0.08763
/*22 */     /* handle_apdu thread stopped, can destroy all of it's mutexes */  // (9) 0.05413
/*24 */     qemu_cond_destroy(&card->handle_apdu_cond);                        // (13) 0.05155
/*26 */     qemu_cond_destroy(&card->apdu_thread_quit_cond);                   // (6) 0.0567
/*28 */     qemu_mutex_destroy(&card->apdu_thread_quit_mutex);                 // (3) 0.06185
/*30 */     qemu_mutex_destroy(&card->handle_apdu_mutex);                      // (8) 0.0567
/*32 */     qemu_mutex_destroy(&card->vreader_mutex);                          // (14) 0.05155
/*34 */     qemu_mutex_destroy(&card->event_list_mutex);                       // (11) 0.05412
/*36 */     return 0;                                                          // (16) 0.01546
/*38 */ }                                                                      // (18) 0.002577
