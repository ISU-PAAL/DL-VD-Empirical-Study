// commit message qemu@e2f89926f1 (target=1, prob=0.03707464, correct=False): usb: Convert usb_packet_{map, unmap} to universal DMA helpers
/*0  */ int usb_packet_map(USBPacket *p, QEMUSGList *sgl)             // (3) 0.06725
/*2  */ {                                                             // (21) 0.002924
/*4  */     int is_write = (p->pid == USB_TOKEN_IN);                  // (5) 0.05848
/*6  */     target_phys_addr_t len;                                   // (11) 0.03509
/*8  */     void *mem;                                                // (15) 0.02047
/*10 */     int i;                                                    // (17) 0.01754
/*14 */     for (i = 0; i < sgl->nsg; i++) {                          // (6) 0.05848
/*16 */         len = sgl->sg[i].len;                                 // (7) 0.05263
/*18 */         mem = cpu_physical_memory_map(sgl->sg[i].base, &len,  // (1) 0.0848
/*20 */                                       is_write);              // (0) 0.1199
/*22 */         if (!mem) {                                           // (12) 0.03509
/*24 */             goto err;                                         // (8) 0.04094
/*26 */         }                                                     // (13) 0.02339
/*28 */         qemu_iovec_add(&p->iov, mem, len);                    // (2) 0.0731
/*30 */         if (len != sgl->sg[i].len) {                          // (4) 0.0614
/*32 */             goto err;                                         // (9) 0.04094
/*34 */         }                                                     // (14) 0.02339
/*36 */     }                                                         // (19) 0.0117
/*38 */     return 0;                                                 // (18) 0.01754
/*42 */ err:                                                          // (20) 0.005848
/*44 */     usb_packet_unmap(p);                                      // (10) 0.03801
/*46 */     return -1;                                                // (16) 0.02047
/*48 */ }                                                             // (22) 0.002924
