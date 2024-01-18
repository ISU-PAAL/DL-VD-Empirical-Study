// commit message qemu@e0cb42ae4b (target=1, prob=0.315647, correct=False): xen: Switch uses of xc_map_foreign_{pages,bulk} to use libxenforeignmemory API.
/*0  */ static void con_disconnect(struct XenDevice *xendev)                           // (7) 0.05357
/*2  */ {                                                                              // (15) 0.003571
/*4  */     struct XenConsole *con = container_of(xendev, struct XenConsole, xendev);  // (3) 0.08929
/*8  */     if (con->chr) {                                                            // (9) 0.03929
/*10 */         qemu_chr_add_handlers(con->chr, NULL, NULL, NULL, NULL);               // (1) 0.1143
/*12 */         qemu_chr_fe_release(con->chr);                                         // (4) 0.08214
/*14 */     }                                                                          // (13) 0.01429
/*16 */     xen_be_unbind_evtchn(&con->xendev);                                        // (5) 0.07143
/*20 */     if (con->sring) {                                                          // (10) 0.03929
/*22 */         if (!xendev->dev) {                                                    // (6) 0.05714
/*24 */             munmap(con->sring, XC_PAGE_SIZE);                                  // (2) 0.09643
/*26 */         } else {                                                               // (11) 0.03571
/*28 */             xengnttab_unmap(xendev->gnttabdev, con->sring, 1);                 // (0) 0.125
/*30 */         }                                                                      // (12) 0.02857
/*32 */         con->sring = NULL;                                                     // (8) 0.05
/*34 */     }                                                                          // (14) 0.01429
/*36 */ }                                                                              // (16) 0.003571
