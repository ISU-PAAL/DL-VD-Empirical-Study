// commit message qemu@4be746345f (target=0, prob=0.07003819, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static unsigned int event_status_media(IDEState *s,            // (14) 0.0307
/*2  */                                        uint8_t *buf)           // (0) 0.09868
/*4  */ {                                                              // (26) 0.002193
/*6  */     uint8_t event_code, media_status;                          // (12) 0.03289
/*10 */     media_status = 0;                                          // (21) 0.01974
/*12 */     if (s->tray_open) {                                        // (16) 0.02851
/*14 */         media_status = MS_TRAY_OPEN;                           // (7) 0.04167
/*16 */     } else if (bdrv_is_inserted(s->bs)) {                      // (4) 0.04605
/*18 */         media_status = MS_MEDIA_PRESENT;                       // (8) 0.04167
/*20 */     }                                                          // (24) 0.008772
/*24 */     /* Event notification descriptor */                        // (22) 0.01754
/*26 */     event_code = MEC_NO_CHANGE;                                // (13) 0.03289
/*28 */     if (media_status != MS_TRAY_OPEN) {                        // (9) 0.03947
/*30 */         if (s->events.new_media) {                             // (10) 0.03947
/*32 */             event_code = MEC_NEW_MEDIA;                        // (2) 0.05044
/*34 */             s->events.new_media = false;                       // (5) 0.04605
/*36 */         } else if (s->events.eject_request) {                  // (6) 0.04605
/*38 */             event_code = MEC_EJECT_REQUESTED;                  // (1) 0.05482
/*40 */             s->events.eject_request = false;                   // (3) 0.04825
/*42 */         }                                                      // (23) 0.01754
/*44 */     }                                                          // (25) 0.008772
/*48 */     buf[4] = event_code;                                       // (17) 0.02632
/*50 */     buf[5] = media_status;                                     // (18) 0.02632
/*54 */     /* These fields are reserved, just clear them. */          // (15) 0.0307
/*56 */     buf[6] = 0;                                                // (19) 0.02193
/*58 */     buf[7] = 0;                                                // (20) 0.02193
/*62 */     return 8; /* We wrote to 4 extra bytes from the header */  // (11) 0.03728
/*64 */ }                                                              // (27) 0.002193
