// commit message qemu@d4754a9531 (target=1, prob=0.082183346, correct=False): l2tpv3: fix fd leak
/*0  */ static void net_l2tpv3_cleanup(NetClientState *nc)          // (2) 0.08636
/*2  */ {                                                           // (12) 0.004545
/*4  */     NetL2TPV3State *s = DO_UPCAST(NetL2TPV3State, nc, nc);  // (0) 0.15
/*6  */     qemu_purge_queued_packets(nc);                          // (3) 0.08182
/*8  */     l2tpv3_read_poll(s, false);                             // (4) 0.07727
/*10 */     l2tpv3_write_poll(s, false);                            // (5) 0.07727
/*12 */     if (s->fd > 0) {                                        // (9) 0.05455
/*14 */         close(s->fd);                                       // (7) 0.05909
/*16 */     }                                                       // (11) 0.01818
/*18 */     destroy_vector(s->msgvec, MAX_L2TPV3_MSGCNT, IOVSIZE);  // (1) 0.1273
/*20 */     g_free(s->vec);                                         // (10) 0.05
/*22 */     g_free(s->header_buf);                                  // (8) 0.05909
/*24 */     g_free(s->dgram_dst);                                   // (6) 0.06818
/*26 */ }                                                           // (13) 0.004545
