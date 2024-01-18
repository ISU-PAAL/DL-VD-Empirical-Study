// commit message qemu@47d3df2387 (target=0, prob=0.009840188, correct=True): xen: Drop __XEN_LATEST_INTERFACE_VERSION__ checks from prior to Xen 4.2
/*0  */ static int xenfb_send_motion(struct XenInput *xenfb,  // (5) 0.08416
/*2  */ 			     int rel_x, int rel_y, int rel_z)              // (0) 0.1089
/*4  */ {                                                     // (11) 0.00495
/*6  */     union xenkbd_in_event event;                      // (9) 0.06436
/*10 */     memset(&event, 0, XENKBD_IN_EVENT_SIZE);          // (1) 0.1089
/*12 */     event.type = XENKBD_TYPE_MOTION;                  // (4) 0.08911
/*14 */     event.motion.rel_x = rel_x;                       // (6) 0.07426
/*16 */     event.motion.rel_y = rel_y;                       // (7) 0.07426
/*18 */ #if __XEN_LATEST_INTERFACE_VERSION__ >= 0x00030207    // (2) 0.104
/*20 */     event.motion.rel_z = rel_z;                       // (8) 0.07426
/*22 */ #endif                                                // (10) 0.009901
/*26 */     return xenfb_kbd_event(xenfb, &event);            // (3) 0.09406
/*28 */ }                                                     // (12) 0.00495
