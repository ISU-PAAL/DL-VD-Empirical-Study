// commit message qemu@fd56356422 (target=1, prob=0.24832106, correct=False): kvm: irqchip: skip update msi when disabled
/*0  */ static void kvm_update_msi_routes_all(void *private, bool global,     // (4) 0.07395
/*2  */                                       uint32_t index, uint32_t mask)  // (0) 0.1576
/*4  */ {                                                                     // (14) 0.003215
/*6  */     int cnt = 0;                                                      // (11) 0.02894
/*8  */     MSIRouteEntry *entry;                                             // (9) 0.03215
/*10 */     MSIMessage msg;                                                   // (12) 0.02572
/*12 */     /* TODO: explicit route update */                                 // (8) 0.03537
/*14 */     QLIST_FOREACH(entry, &msi_route_list, list) {                     // (6) 0.07074
/*16 */         cnt++;                                                        // (10) 0.03215
/*18 */         msg = pci_get_msi_message(entry->dev, entry->vector);         // (3) 0.0836
/*20 */         kvm_irqchip_update_msi_route(kvm_state, entry->virq,          // (2) 0.09968
/*22 */                                      msg, entry->dev);                // (1) 0.135
/*24 */     }                                                                 // (13) 0.01286
/*26 */     kvm_irqchip_commit_routes(kvm_state);                             // (7) 0.06752
/*28 */     trace_kvm_x86_update_msi_routes(cnt);                             // (5) 0.07395
/*30 */ }                                                                     // (15) 0.003215
