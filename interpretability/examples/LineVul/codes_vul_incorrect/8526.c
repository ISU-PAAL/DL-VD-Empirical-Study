// commit message qemu@2e11986727 (target=1, prob=0.047049414, correct=False): hw/net/stellaris_enet: Convert to vmstate
/*0  */ static void stellaris_enet_save(QEMUFile *f, void *opaque)         // (6) 0.04911
/*2  */ {                                                                  // (21) 0.002232
/*4  */     stellaris_enet_state *s = (stellaris_enet_state *)opaque;      // (3) 0.0558
/*6  */     int i;                                                         // (19) 0.01339
/*10 */     qemu_put_be32(f, s->ris);                                      // (15) 0.04018
/*12 */     qemu_put_be32(f, s->im);                                       // (16) 0.04018
/*14 */     qemu_put_be32(f, s->rctl);                                     // (8) 0.04241
/*16 */     qemu_put_be32(f, s->tctl);                                     // (9) 0.04241
/*18 */     qemu_put_be32(f, s->thr);                                      // (10) 0.04241
/*20 */     qemu_put_be32(f, s->mctl);                                     // (11) 0.04241
/*22 */     qemu_put_be32(f, s->mdv);                                      // (12) 0.04241
/*24 */     qemu_put_be32(f, s->mtxd);                                     // (13) 0.04241
/*26 */     qemu_put_be32(f, s->mrxd);                                     // (14) 0.04241
/*28 */     qemu_put_be32(f, s->np);                                       // (17) 0.04018
/*30 */     qemu_put_be32(f, s->tx_fifo_len);                              // (4) 0.05134
/*32 */     qemu_put_buffer(f, s->tx_fifo, sizeof(s->tx_fifo));            // (1) 0.06473
/*34 */     for (i = 0; i < 31; i++) {                                     // (18) 0.03571
/*36 */         qemu_put_be32(f, s->rx[i].len);                            // (2) 0.05804
/*38 */         qemu_put_buffer(f, s->rx[i].data, sizeof(s->rx[i].data));  // (0) 0.07813
/*42 */     }                                                              // (20) 0.008929
/*44 */     qemu_put_be32(f, s->next_packet);                              // (7) 0.04688
/*46 */     qemu_put_be32(f, s->rx_fifo_offset);                           // (5) 0.05134
/*48 */ }                                                                  // (22) 0.002232
