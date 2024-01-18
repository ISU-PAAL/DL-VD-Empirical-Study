// commit message qemu@a8170e5e97 (target=0, prob=0.35251048, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ void address_space_unmap(AddressSpace *as, void *buffer, target_phys_addr_t len,  // (4) 0.0519
/*2  */                          int is_write, target_phys_addr_t access_len)             // (0) 0.07984
/*4  */ {                                                                                 // (26) 0.001996
/*6  */     if (buffer != bounce.buffer) {                                                // (17) 0.02395
/*8  */         if (is_write) {                                                           // (15) 0.02794
/*10 */             ram_addr_t addr1 = qemu_ram_addr_from_host_nofail(buffer);            // (1) 0.07385
/*12 */             while (access_len) {                                                  // (11) 0.03593
/*14 */                 unsigned l;                                                       // (12) 0.03593
/*16 */                 l = TARGET_PAGE_SIZE;                                             // (5) 0.0499
/*18 */                 if (l > access_len)                                               // (8) 0.04591
/*20 */                     l = access_len;                                               // (6) 0.0499
/*22 */                 invalidate_and_set_dirty(addr1, l);                               // (2) 0.05788
/*24 */                 addr1 += l;                                                       // (10) 0.03992
/*26 */                 access_len -= l;                                                  // (9) 0.04192
/*28 */             }                                                                     // (18) 0.02395
/*30 */         }                                                                         // (22) 0.01597
/*32 */         if (xen_enabled()) {                                                      // (13) 0.02994
/*34 */             xen_invalidate_map_cache_entry(buffer);                               // (7) 0.0499
/*36 */         }                                                                         // (23) 0.01597
/*38 */         return;                                                                   // (20) 0.01796
/*40 */     }                                                                             // (24) 0.007984
/*42 */     if (is_write) {                                                               // (19) 0.01996
/*44 */         address_space_write(as, bounce.addr, bounce.buffer, access_len);          // (3) 0.05389
/*46 */     }                                                                             // (25) 0.007984
/*48 */     qemu_vfree(bounce.buffer);                                                    // (14) 0.02994
/*50 */     bounce.buffer = NULL;                                                         // (21) 0.01796
/*52 */     cpu_notify_map_clients();                                                     // (16) 0.02595
/*54 */ }                                                                                 // (27) 0.001996
