// commit message qemu@e5f34cdd2d (target=1, prob=0.18594329, correct=False): vnc: track & limit connections
/*0  */ static void vnc_set_share_mode(VncState *vs, VncShareMode mode)  // (7) 0.06069
/*2  */ {                                                                // (20) 0.002639
/*4  */ #ifdef _VNC_DEBUG                                                // (14) 0.02111
/*6  */     static const char *mn[] = {                                  // (12) 0.02902
/*8  */         [0]                           = "undefined",             // (0) 0.1082
/*10 */         [VNC_SHARE_MODE_CONNECTING]   = "connecting",            // (4) 0.0686
/*12 */         [VNC_SHARE_MODE_SHARED]       = "shared",                // (2) 0.07652
/*14 */         [VNC_SHARE_MODE_EXCLUSIVE]    = "exclusive",             // (5) 0.0686
/*16 */         [VNC_SHARE_MODE_DISCONNECTED] = "disconnected",          // (6) 0.06596
/*18 */     };                                                           // (15) 0.01055
/*20 */     fprintf(stderr, "%s/%d: %s -> %s\n", __func__,               // (3) 0.07388
/*22 */             vs->csock, mn[vs->share_mode], mn[mode]);            // (1) 0.07916
/*24 */ #endif                                                           // (18) 0.005277
/*28 */     if (vs->share_mode == VNC_SHARE_MODE_EXCLUSIVE) {            // (8) 0.06069
/*30 */         vs->vd->num_exclusive--;                                 // (10) 0.04222
/*32 */     }                                                            // (16) 0.01055
/*34 */     vs->share_mode = mode;                                       // (13) 0.02902
/*36 */     if (vs->share_mode == VNC_SHARE_MODE_EXCLUSIVE) {            // (9) 0.06069
/*38 */         vs->vd->num_exclusive++;                                 // (11) 0.03958
/*40 */     }                                                            // (17) 0.01055
/*42 */ }                                                                // (19) 0.002639
