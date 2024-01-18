// commit message qemu@d861b05ea3 (target=1, prob=0.22148496, correct=False): Avoid buffer overflow when sending slirp packets.
/*0  */ static int net_slirp_init(VLANState *vlan)                                        // (3) 0.09091
/*2  */ {                                                                                 // (9) 0.005348
/*4  */     if (!slirp_inited) {                                                          // (5) 0.06952
/*6  */         slirp_inited = 1;                                                         // (4) 0.08556
/*8  */         slirp_init();                                                             // (6) 0.06952
/*10 */     }                                                                             // (8) 0.02139
/*12 */     slirp_vc = qemu_new_vlan_client(vlan,                                         // (2) 0.1283
/*14 */                                     slirp_receive, NULL);                         // (0) 0.2353
/*16 */     snprintf(slirp_vc->info_str, sizeof(slirp_vc->info_str), "user redirector");  // (1) 0.1765
/*18 */     return 0;                                                                     // (7) 0.03209
/*20 */ }                                                                                 // (10) 0.005348
