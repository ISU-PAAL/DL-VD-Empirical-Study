// commit message qemu@b931bfbf04 (target=0, prob=0.042867076, correct=True): vhost-user: add multiple queue support
/*0  */ static void net_vhost_link_down(VhostUserState *s, bool link_down)  // (2) 0.1156
/*2  */ {                                                                   // (11) 0.005025
/*4  */     s->nc.link_down = link_down;                                    // (6) 0.07538
/*8  */     if (s->nc.peer) {                                               // (7) 0.0603
/*10 */         s->nc.peer->link_down = link_down;                          // (4) 0.1055
/*12 */     }                                                               // (8) 0.0201
/*16 */     if (s->nc.info->link_status_changed) {                          // (5) 0.09045
/*18 */         s->nc.info->link_status_changed(&s->nc);                    // (3) 0.1156
/*20 */     }                                                               // (9) 0.0201
/*24 */     if (s->nc.peer && s->nc.peer->info->link_status_changed) {      // (1) 0.1307
/*26 */         s->nc.peer->info->link_status_changed(s->nc.peer);          // (0) 0.1357
/*28 */     }                                                               // (10) 0.0201
/*30 */ }                                                                   // (12) 0.005025
