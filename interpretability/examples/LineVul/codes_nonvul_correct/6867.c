// commit message qemu@b931bfbf04 (target=0, prob=0.27349624, correct=True): vhost-user: add multiple queue support
/*0  */ static int vhost_user_start(VhostUserState *s)       // (3) 0.09816
/*2  */ {                                                    // (10) 0.006135
/*4  */     VhostNetOptions options;                         // (8) 0.05521
/*8  */     if (vhost_user_running(s)) {                     // (4) 0.09202
/*10 */         return 0;                                    // (7) 0.06135
/*12 */     }                                                // (9) 0.02454
/*16 */     options.backend_type = VHOST_BACKEND_TYPE_USER;  // (0) 0.1288
/*18 */     options.net_backend = &s->nc;                    // (5) 0.09202
/*20 */     options.opaque = s->chr;                         // (6) 0.07975
/*24 */     s->vhost_net = vhost_net_init(&options);         // (1) 0.1166
/*28 */     return vhost_user_running(s) ? 0 : -1;           // (2) 0.1166
/*30 */ }                                                    // (11) 0.006135
