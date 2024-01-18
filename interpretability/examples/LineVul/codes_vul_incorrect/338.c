// commit message qemu@fac7d7b1cd (target=1, prob=0.43084753, correct=False): tap: fix memory leak on failure in net_init_tap()
/*0   */ int net_init_tap(const Netdev *netdev, const char *name,                        // (11) 0.03711
/*2   */                  NetClientState *peer, Error **errp)                            // (5) 0.05273
/*4   */ {                                                                               // (24) 0.001954
/*6   */     const NetdevTapOptions *tap;                                                // (17) 0.02148
/*8   */     int fd, vnet_hdr = 0, i = 0, queues;                                        // (9) 0.04103
/*10  */     /* for the no-fd, no-helper case */                                         // (13) 0.03125
/*12  */     const char *script = NULL; /* suppress wrong "uninit'd use" gcc warning */  // (8) 0.04297
/*14  */     const char *downscript = NULL;                                              // (18) 0.02148
/*16  */     Error *err = NULL;                                                          // (22) 0.01758
/*18  */     const char *vhostfdname;                                                    // (19) 0.02148
/*20  */     char ifname[128];                                                           // (21) 0.01758
/*24  */     assert(netdev->type == NET_CLIENT_DRIVER_TAP);                              // (10) 0.04101
/*26  */     tap = &netdev->u.tap;                                                       // (15) 0.02539
/*28  */     queues = tap->has_queues ? tap->queues : 1;                                 // (12) 0.03711
/*30  */     vhostfdname = tap->has_vhostfd ? tap->vhostfd : NULL;                       // (7) 0.04687
/*34  */     /* QEMU vlans does not support multiqueue tap, in this case peer is set.    // (6) 0.04883
/*36  */      * For -netdev, peer is always NULL. */                                     // (14) 0.03125
/*38  */     if (peer && (tap->has_queues || tap->has_fds || tap->has_vhostfds)) {       // (1) 0.0625
/*40  */         error_setg(errp, "Multiqueue tap cannot be used with QEMU vlans");      // (2) 0.06054
/*42  */         return -1;                                                              // (20) 0.02148
/*44  */     }                                                                           // (23) 0.007812
/*48  */     if (tap->has_fd) {                                                          // (16) 0.02344
/*50  */         if (tap->has_ifname || tap->has_script || tap->has_downscript ||        // (3) 0.05664
/*52  */             tap->has_vnet_hdr || tap->has_helper || tap->has_queues ||          // (0) 0.06836
/*54  */             tap->has_fds || tap->has_vhostfds) {                                // (4) 0.05469
/*56  */             error_setg(errp, "ifname=, script=, downscript=, vnet_hdr=, "       // 0.0
/*58  */                        "helper=, queues=, fds=, and vhostfds= "                 // 0.0
/*60  */                        "are invalid with fd=");                                 // 0.0
/*62  */             return -1;                                                          // 0.0
/*64  */         }                                                                       // 0.0
/*68  */         fd = monitor_fd_param(cur_mon, tap->fd, &err);                          // 0.0
/*70  */         if (fd == -1) {                                                         // 0.0
/*72  */             error_propagate(errp, err);                                         // 0.0
/*74  */             return -1;                                                          // 0.0
/*76  */         }                                                                       // 0.0
/*80  */         fcntl(fd, F_SETFL, O_NONBLOCK);                                         // 0.0
/*84  */         vnet_hdr = tap_probe_vnet_hdr(fd);                                      // 0.0
/*88  */         net_init_tap_one(tap, peer, "tap", name, NULL,                          // 0.0
/*90  */                          script, downscript,                                    // 0.0
/*92  */                          vhostfdname, vnet_hdr, fd, &err);                      // 0.0
/*94  */         if (err) {                                                              // 0.0
/*96  */             error_propagate(errp, err);                                         // 0.0
/*98  */             return -1;                                                          // 0.0
/*100 */         }                                                                       // 0.0
/*102 */     } else if (tap->has_fds) {                                                  // 0.0
/*104 */         char **fds = g_new0(char *, MAX_TAP_QUEUES);                            // 0.0
/*106 */         char **vhost_fds = g_new0(char *, MAX_TAP_QUEUES);                      // 0.0
/*108 */         int nfds, nvhosts;                                                      // 0.0
/*112 */         if (tap->has_ifname || tap->has_script || tap->has_downscript ||        // 0.0
/*114 */             tap->has_vnet_hdr || tap->has_helper || tap->has_queues ||          // 0.0
/*116 */             tap->has_vhostfd) {                                                 // 0.0
/*118 */             error_setg(errp, "ifname=, script=, downscript=, vnet_hdr=, "       // 0.0
/*120 */                        "helper=, queues=, and vhostfd= "                        // 0.0
/*122 */                        "are invalid with fds=");                                // 0.0
/*124 */             return -1;                                                          // 0.0
/*126 */         }                                                                       // 0.0
/*130 */         nfds = get_fds(tap->fds, fds, MAX_TAP_QUEUES);                          // 0.0
/*132 */         if (tap->has_vhostfds) {                                                // 0.0
/*134 */             nvhosts = get_fds(tap->vhostfds, vhost_fds, MAX_TAP_QUEUES);        // 0.0
/*136 */             if (nfds != nvhosts) {                                              // 0.0
/*138 */                 error_setg(errp, "The number of fds passed does not match "     // 0.0
/*140 */                            "the number of vhostfds passed");                    // 0.0
/*142 */                 goto free_fail;                                                 // 0.0
/*144 */             }                                                                   // 0.0
/*146 */         }                                                                       // 0.0
/*150 */         for (i = 0; i < nfds; i++) {                                            // 0.0
/*152 */             fd = monitor_fd_param(cur_mon, fds[i], &err);                       // 0.0
/*154 */             if (fd == -1) {                                                     // 0.0
/*156 */                 error_propagate(errp, err);                                     // 0.0
/*158 */                 goto free_fail;                                                 // 0.0
/*160 */             }                                                                   // 0.0
/*164 */             fcntl(fd, F_SETFL, O_NONBLOCK);                                     // 0.0
/*168 */             if (i == 0) {                                                       // 0.0
/*170 */                 vnet_hdr = tap_probe_vnet_hdr(fd);                              // 0.0
/*172 */             } else if (vnet_hdr != tap_probe_vnet_hdr(fd)) {                    // 0.0
/*174 */                 error_setg(errp,                                                // 0.0
/*176 */                            "vnet_hdr not consistent across given tap fds");     // 0.0
/*178 */                 goto free_fail;                                                 // 0.0
/*180 */             }                                                                   // 0.0
/*184 */             net_init_tap_one(tap, peer, "tap", name, ifname,                    // 0.0
/*186 */                              script, downscript,                                // 0.0
/*188 */                              tap->has_vhostfds ? vhost_fds[i] : NULL,           // 0.0
/*190 */                              vnet_hdr, fd, &err);                               // 0.0
/*192 */             if (err) {                                                          // 0.0
/*194 */                 error_propagate(errp, err);                                     // 0.0
/*196 */                 goto free_fail;                                                 // 0.0
/*198 */             }                                                                   // 0.0
/*200 */         }                                                                       // 0.0
/*202 */         g_free(fds);                                                            // 0.0
/*204 */         g_free(vhost_fds);                                                      // 0.0
/*206 */         return 0;                                                               // 0.0
/*210 */ free_fail:                                                                      // 0.0
/*212 */         for (i = 0; i < nfds; i++) {                                            // 0.0
/*214 */             g_free(fds[i]);                                                     // 0.0
/*216 */             g_free(vhost_fds[i]);                                               // 0.0
/*218 */         }                                                                       // 0.0
/*220 */         g_free(fds);                                                            // 0.0
/*222 */         g_free(vhost_fds);                                                      // 0.0
/*224 */         return -1;                                                              // 0.0
/*226 */     } else if (tap->has_helper) {                                               // 0.0
/*228 */         if (tap->has_ifname || tap->has_script || tap->has_downscript ||        // 0.0
/*230 */             tap->has_vnet_hdr || tap->has_queues || tap->has_vhostfds) {        // 0.0
/*232 */             error_setg(errp, "ifname=, script=, downscript=, vnet_hdr=, "       // 0.0
/*234 */                        "queues=, and vhostfds= are invalid with helper=");      // 0.0
/*236 */             return -1;                                                          // 0.0
/*238 */         }                                                                       // 0.0
/*242 */         fd = net_bridge_run_helper(tap->helper,                                 // 0.0
/*244 */                                    tap->has_br ?                                // 0.0
/*246 */                                    tap->br : DEFAULT_BRIDGE_INTERFACE,          // 0.0
/*248 */                                    errp);                                       // 0.0
/*250 */         if (fd == -1) {                                                         // 0.0
/*252 */             return -1;                                                          // 0.0
/*254 */         }                                                                       // 0.0
/*258 */         fcntl(fd, F_SETFL, O_NONBLOCK);                                         // 0.0
/*260 */         vnet_hdr = tap_probe_vnet_hdr(fd);                                      // 0.0
/*264 */         net_init_tap_one(tap, peer, "bridge", name, ifname,                     // 0.0
/*266 */                          script, downscript, vhostfdname,                       // 0.0
/*268 */                          vnet_hdr, fd, &err);                                   // 0.0
/*270 */         if (err) {                                                              // 0.0
/*272 */             error_propagate(errp, err);                                         // 0.0
/*274 */             close(fd);                                                          // 0.0
/*276 */             return -1;                                                          // 0.0
/*278 */         }                                                                       // 0.0
/*280 */     } else {                                                                    // 0.0
/*282 */         if (tap->has_vhostfds) {                                                // 0.0
/*284 */             error_setg(errp, "vhostfds= is invalid if fds= wasn't specified");  // 0.0
/*286 */             return -1;                                                          // 0.0
/*288 */         }                                                                       // 0.0
/*290 */         script = tap->has_script ? tap->script : DEFAULT_NETWORK_SCRIPT;        // 0.0
/*292 */         downscript = tap->has_downscript ? tap->downscript :                    // 0.0
/*294 */             DEFAULT_NETWORK_DOWN_SCRIPT;                                        // 0.0
/*298 */         if (tap->has_ifname) {                                                  // 0.0
/*300 */             pstrcpy(ifname, sizeof ifname, tap->ifname);                        // 0.0
/*302 */         } else {                                                                // 0.0
/*304 */             ifname[0] = '\0';                                                   // 0.0
/*306 */         }                                                                       // 0.0
/*310 */         for (i = 0; i < queues; i++) {                                          // 0.0
/*312 */             fd = net_tap_init(tap, &vnet_hdr, i >= 1 ? "no" : script,           // 0.0
/*314 */                               ifname, sizeof ifname, queues > 1, errp);         // 0.0
/*316 */             if (fd == -1) {                                                     // 0.0
/*318 */                 return -1;                                                      // 0.0
/*320 */             }                                                                   // 0.0
/*324 */             if (queues > 1 && i == 0 && !tap->has_ifname) {                     // 0.0
/*326 */                 if (tap_fd_get_ifname(fd, ifname)) {                            // 0.0
/*328 */                     error_setg(errp, "Fail to get ifname");                     // 0.0
/*330 */                     close(fd);                                                  // 0.0
/*332 */                     return -1;                                                  // 0.0
/*334 */                 }                                                               // 0.0
/*336 */             }                                                                   // 0.0
/*340 */             net_init_tap_one(tap, peer, "tap", name, ifname,                    // 0.0
/*342 */                              i >= 1 ? "no" : script,                            // 0.0
/*344 */                              i >= 1 ? "no" : downscript,                        // 0.0
/*346 */                              vhostfdname, vnet_hdr, fd, &err);                  // 0.0
/*348 */             if (err) {                                                          // 0.0
/*350 */                 error_propagate(errp, err);                                     // 0.0
/*352 */                 close(fd);                                                      // 0.0
/*354 */                 return -1;                                                      // 0.0
/*356 */             }                                                                   // 0.0
/*358 */         }                                                                       // 0.0
/*360 */     }                                                                           // 0.0
/*364 */     return 0;                                                                   // 0.0
/*366 */ }                                                                               // 0.0
