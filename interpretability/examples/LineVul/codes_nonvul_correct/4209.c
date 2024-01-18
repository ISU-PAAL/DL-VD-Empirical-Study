// commit message qemu@e8f1f9db87 (target=0, prob=0.32219878, correct=True): net: Check device passed to host_net_remove (Jan Kiszka)
/*0  */ void net_host_device_remove(Monitor *mon, int vlan_id, const char *device)  // (2) 0.1165
/*2  */ {                                                                           // (12) 0.004854
/*4  */     VLANState *vlan;                                                        // (7) 0.04854
/*6  */     VLANClientState *vc;                                                    // (8) 0.04854
/*10 */     vlan = qemu_find_vlan(vlan_id);                                         // (3) 0.09709
/*14 */    for(vc = vlan->first_client; vc != NULL; vc = vc->next)                  // (0) 0.1262
/*16 */         if (!strcmp(vc->name, device))                                      // (4) 0.08738
/*18 */             break;                                                          // (6) 0.06311
/*22 */     if (!vc) {                                                              // (10) 0.03883
/*24 */         monitor_printf(mon, "can't find device %s\n", device);              // (1) 0.1214
/*26 */         return;                                                             // (9) 0.04369
/*28 */     }                                                                       // (11) 0.01942
/*30 */     qemu_del_vlan_client(vc);                                               // (5) 0.07767
/*32 */ }                                                                           // (13) 0.004854
