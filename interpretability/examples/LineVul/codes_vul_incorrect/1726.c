// commit message qemu@e2b72cb6e0 (target=1, prob=0.1690991, correct=False): ui: fix VNC client throttling when audio capture is active
/*0  */ static bool vnc_should_update(VncState *vs)                     // (4) 0.06849
/*2  */ {                                                               // (16) 0.004566
/*4  */     switch (vs->update) {                                       // (8) 0.04566
/*6  */     case VNC_STATE_UPDATE_NONE:                                 // (5) 0.06393
/*8  */         break;                                                  // (10) 0.0411
/*10 */     case VNC_STATE_UPDATE_INCREMENTAL:                          // (2) 0.07306
/*12 */         /* Only allow incremental updates if the output buffer  // (3) 0.07306
/*14 */          * is empty, or if audio capture is enabled.            // (1) 0.08676
/*16 */          */                                                     // (11) 0.0411
/*18 */         if (!vs->output.offset || vs->audio_cap) {              // (0) 0.1005
/*20 */             return true;                                        // (7) 0.06393
/*22 */         }                                                       // (13) 0.03653
/*24 */         break;                                                  // (12) 0.0411
/*26 */     case VNC_STATE_UPDATE_FORCE:                                // (6) 0.06393
/*28 */         return true;                                            // (9) 0.04566
/*30 */     }                                                           // (15) 0.01826
/*32 */     return false;                                               // (14) 0.0274
/*34 */ }                                                               // (17) 0.004566
