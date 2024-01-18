// commit message qemu@0a73336d96 (target=1, prob=0.2726115, correct=False): net: don't poke at chardev internal QemuOpts
/*0  */ int net_init_vhost_user(const Netdev *netdev, const char *name,             // (9) 0.04481
/*2  */                         NetClientState *peer, Error **errp)                 // (2) 0.06925
/*4  */ {                                                                           // (24) 0.002037
/*6  */     int queues;                                                             // (20) 0.01222
/*8  */     const NetdevVhostUserOptions *vhost_user_opts;                          // (12) 0.0387
/*10 */     CharDriverState *chr;                                                   // (17) 0.02037
/*14 */     assert(netdev->type == NET_CLIENT_DRIVER_VHOST_USER);                   // (8) 0.04888
/*16 */     vhost_user_opts = &netdev->u.vhost_user;                                // (10) 0.04481
/*20 */     chr = net_vhost_parse_chardev(vhost_user_opts, errp);                   // (6) 0.05499
/*22 */     if (!chr) {                                                             // (18) 0.01833
/*24 */         return -1;                                                          // (14) 0.0224
/*26 */     }                                                                       // (21) 0.008147
/*30 */     /* verify net frontend */                                               // (19) 0.01833
/*32 */     if (qemu_opts_foreach(qemu_find_opts("device"), net_vhost_check_net,    // (1) 0.07128
/*34 */                           (char *)name, errp)) {                            // (3) 0.06925
/*36 */         return -1;                                                          // (15) 0.0224
/*38 */     }                                                                       // (22) 0.008147
/*42 */     queues = vhost_user_opts->has_queues ? vhost_user_opts->queues : 1;     // (4) 0.06314
/*44 */     if (queues < 1 || queues > MAX_QUEUE_NUM) {                             // (11) 0.04277
/*46 */         error_setg(errp,                                                    // (13) 0.03055
/*48 */                    "vhost-user number of queues must be in range [1, %d]",  // (0) 0.07536
/*50 */                    MAX_QUEUE_NUM);                                          // (7) 0.05295
/*52 */         return -1;                                                          // (16) 0.0224
/*54 */     }                                                                       // (23) 0.008147
/*58 */     return net_vhost_user_init(peer, "vhost_user", name, chr, queues);      // (5) 0.05703
/*60 */ }                                                                           // (25) 0.002037
