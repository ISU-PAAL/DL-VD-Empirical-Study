// commit message qemu@4a917c39ae (target=0, prob=0.43239605, correct=True): convert net_init_vde() to NetClientOptions
/*0  */ int net_init_vde(QemuOpts *opts, const NetClientOptions *new_opts,         // (2) 0.1093
/*2  */                  const char *name, VLANState *vlan)                        // (1) 0.1134
/*4  */ {                                                                          // (13) 0.004049
/*6  */     const char *sock;                                                      // (8) 0.03644
/*8  */     const char *group;                                                     // (10) 0.03239
/*10 */     int port, mode;                                                        // (9) 0.03239
/*14 */     sock  = qemu_opt_get(opts, "sock");                                    // (5) 0.08502
/*16 */     group = qemu_opt_get(opts, "group");                                   // (6) 0.07692
/*20 */     port = qemu_opt_get_number(opts, "port", 0);                           // (4) 0.09312
/*22 */     mode = qemu_opt_get_number(opts, "mode", 0700);                        // (3) 0.09717
/*26 */     if (net_vde_init(vlan, "vde", name, sock, port, group, mode) == -1) {  // (0) 0.1377
/*28 */         return -1;                                                         // (7) 0.04453
/*30 */     }                                                                      // (12) 0.01619
/*34 */     return 0;                                                              // (11) 0.02429
/*36 */ }                                                                          // (14) 0.004049
