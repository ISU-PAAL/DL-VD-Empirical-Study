// commit message qemu@8297be80f7 (target=0, prob=0.2349791, correct=True): Convert multi-line fprintf() to warn_report()
/*0  */ void net_hub_check_clients(void)                                            // (19) 0.02344
/*2  */ {                                                                           // (24) 0.001953
/*4  */     NetHub *hub;                                                            // (23) 0.01563
/*6  */     NetHubPort *port;                                                       // (21) 0.01758
/*8  */     NetClientState *peer;                                                   // (22) 0.01758
/*12 */     QLIST_FOREACH(hub, &hubs, next) {                                       // (14) 0.03516
/*14 */         int has_nic = 0, has_host_dev = 0;                                  // (9) 0.04297
/*18 */         QLIST_FOREACH(port, &hub->ports, next) {                            // (4) 0.04492
/*20 */             peer = port->nc.peer;                                           // (13) 0.03711
/*22 */             if (!peer) {                                                    // (18) 0.03125
/*24 */                 fprintf(stderr, "Warning: hub port %s has no peer\n",       // (0) 0.06836
/*26 */                         port->nc.name);                                     // (1) 0.05664
/*28 */                 continue;                                                   // (15) 0.0332
/*30 */             }                                                               // (20) 0.02344
/*34 */             switch (peer->info->type) {                                     // (12) 0.03906
/*36 */             case NET_CLIENT_DRIVER_NIC:                                     // (6) 0.04492
/*38 */                 has_nic = 1;                                                // (11) 0.04102
/*40 */                 break;                                                      // (16) 0.0332
/*42 */             case NET_CLIENT_DRIVER_USER:                                    // (10) 0.04297
/*44 */             case NET_CLIENT_DRIVER_TAP:                                     // (5) 0.04492
/*46 */             case NET_CLIENT_DRIVER_SOCKET:                                  // (3) 0.04688
/*48 */             case NET_CLIENT_DRIVER_VDE:                                     // (8) 0.04492
/*50 */             case NET_CLIENT_DRIVER_VHOST_USER:                              // (2) 0.05078
/*52 */                 has_host_dev = 1;                                           // (7) 0.04492
/*54 */                 break;                                                      // (17) 0.0332
/*56 */             default:                                                        // 0.0
/*58 */                 break;                                                      // 0.0
/*60 */             }                                                               // 0.0
/*62 */         }                                                                   // 0.0
/*64 */         if (has_host_dev && !has_nic) {                                     // 0.0
/*66 */             warn_report("vlan %d with no nics", hub->id);                   // 0.0
/*68 */         }                                                                   // 0.0
/*70 */         if (has_nic && !has_host_dev) {                                     // 0.0
/*72 */             fprintf(stderr,                                                 // 0.0
/*74 */                     "Warning: vlan %d is not connected to host network\n",  // 0.0
/*76 */                     hub->id);                                               // 0.0
/*78 */         }                                                                   // 0.0
/*80 */     }                                                                       // 0.0
/*82 */ }                                                                           // 0.0
