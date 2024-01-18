// commit message qemu@a8170e5e97 (target=0, prob=0.007791447, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static void phys_page_set(AddressSpaceDispatch *d,                          // (5) 0.07778
/*2  */                           target_phys_addr_t index, target_phys_addr_t nb,  // (0) 0.2444
/*4  */                           uint16_t leaf)                                    // (2) 0.1722
/*6  */ {                                                                           // (6) 0.005556
/*8  */     /* Wildly overreserve - it doesn't matter much. */                      // (4) 0.09444
/*10 */     phys_map_node_reserve(3 * P_L2_LEVELS);                                 // (3) 0.1278
/*14 */     phys_page_set_level(&d->phys_map, &index, &nb, leaf, P_L2_LEVELS - 1);  // (1) 0.2
/*16 */ }                                                                           // (7) 0.005556
