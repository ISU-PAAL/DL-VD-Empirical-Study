// commit message qemu@7873df408d (target=0, prob=0.3792341, correct=True): tap: properly initialize vhostfds
/*0   */ static int net_init_tap_one(const NetdevTapOptions *tap, NetClientState *peer,   // (8) 0.04688
/*2   */                             const char *model, const char *name,                 // (3) 0.07227
/*4   */                             const char *ifname, const char *script,              // (1) 0.07422
/*6   */                             const char *downscript, const char *vhostfdname,     // (0) 0.08008
/*8   */                             int vnet_hdr, int fd)                                // (2) 0.07422
/*10  */ {                                                                                // (21) 0.001953
/*12  */     TAPState *s;                                                                 // (16) 0.01758
/*16  */     s = net_tap_fd_init(peer, model, name, fd, vnet_hdr);                        // (6) 0.05469
/*18  */     if (!s) {                                                                    // (17) 0.01562
/*20  */         close(fd);                                                               // (13) 0.02148
/*22  */         return -1;                                                               // (14) 0.02148
/*24  */     }                                                                            // (19) 0.007812
/*28  */     if (tap_set_sndbuf(s->fd, tap) < 0) {                                        // (9) 0.04492
/*30  */         return -1;                                                               // (15) 0.02148
/*32  */     }                                                                            // (20) 0.007812
/*36  */     if (tap->has_fd || tap->has_fds) {                                           // (11) 0.03711
/*38  */         snprintf(s->nc.info_str, sizeof(s->nc.info_str), "fd=%d", fd);           // (4) 0.07227
/*40  */     } else if (tap->has_helper) {                                                // (12) 0.0293
/*42  */         snprintf(s->nc.info_str, sizeof(s->nc.info_str), "helper=%s",            // (5) 0.06836
/*44  */                  tap->helper);                                                   // (10) 0.04102
/*46  */     } else {                                                                     // (18) 0.01172
/*48  */         snprintf(s->nc.info_str, sizeof(s->nc.info_str),                         // (7) 0.05469
/*50  */                  "ifname=%s,script=%s,downscript=%s", ifname, script,            // 0.0
/*52  */                  downscript);                                                    // 0.0
/*56  */         if (strcmp(downscript, "no") != 0) {                                     // 0.0
/*58  */             snprintf(s->down_script, sizeof(s->down_script), "%s", downscript);  // 0.0
/*60  */             snprintf(s->down_script_arg, sizeof(s->down_script_arg),             // 0.0
/*62  */                      "%s", ifname);                                              // 0.0
/*64  */         }                                                                        // 0.0
/*66  */     }                                                                            // 0.0
/*70  */     if (tap->has_vhost ? tap->vhost :                                            // 0.0
/*72  */         vhostfdname || (tap->has_vhostforce && tap->vhostforce)) {               // 0.0
/*74  */         int vhostfd;                                                             // 0.0
/*78  */         if (tap->has_vhostfd) {                                                  // 0.0
/*80  */             vhostfd = monitor_handle_fd_param(cur_mon, vhostfdname);             // 0.0
/*82  */             if (vhostfd == -1) {                                                 // 0.0
/*84  */                 return -1;                                                       // 0.0
/*86  */             }                                                                    // 0.0
/*88  */         } else {                                                                 // 0.0
/*90  */             vhostfd = -1;                                                        // 0.0
/*92  */         }                                                                        // 0.0
/*96  */         s->vhost_net = vhost_net_init(&s->nc, vhostfd,                           // 0.0
/*98  */                                       tap->has_vhostforce && tap->vhostforce);   // 0.0
/*100 */         if (!s->vhost_net) {                                                     // 0.0
/*102 */             error_report("vhost-net requested but could not be initialized");    // 0.0
/*104 */             return -1;                                                           // 0.0
/*106 */         }                                                                        // 0.0
/*108 */     } else if (tap->has_vhostfd || tap->has_vhostfds) {                          // 0.0
/*110 */         error_report("vhostfd= is not valid without vhost");                     // 0.0
/*112 */         return -1;                                                               // 0.0
/*114 */     }                                                                            // 0.0
/*118 */     return 0;                                                                    // 0.0
/*120 */ }                                                                                // 0.0
