// commit message qemu@0d6ff71ae3 (target=0, prob=0.5048555, correct=False): slirp: Adding IPv6, ICMPv6 Echo and NDP autoconfiguration
/*0   */ void if_start(Slirp *slirp)                                                  // (20) 0.02539
/*2   */ {                                                                            // (27) 0.001953
/*4   */     uint64_t now = qemu_clock_get_ns(QEMU_CLOCK_REALTIME);                   // (0) 0.05859
/*6   */     bool from_batchq, next_from_batchq;                                      // (15) 0.03125
/*8   */     struct mbuf *ifm, *ifm_next, *ifqt;                                      // (8) 0.03906
/*12  */     DEBUG_CALL("if_start");                                                  // (21) 0.02344
/*16  */     if (slirp->if_start_busy) {                                              // (13) 0.0332
/*18  */         return;                                                              // (23) 0.01758
/*20  */     }                                                                        // (26) 0.007812
/*22  */     slirp->if_start_busy = true;                                             // (14) 0.03125
/*26  */     if (slirp->if_fastq.ifq_next != &slirp->if_fastq) {                      // (1) 0.05859
/*28  */         ifm_next = slirp->if_fastq.ifq_next;                                 // (2) 0.05078
/*30  */         next_from_batchq = false;                                            // (16) 0.03125
/*32  */     } else if (slirp->next_m != &slirp->if_batchq) {                         // (3) 0.05078
/*34  */         /* Nothing on fastq, pick up from batchq via next_m */               // (7) 0.04492
/*36  */         ifm_next = slirp->next_m;                                            // (9) 0.03906
/*38  */         next_from_batchq = true;                                             // (17) 0.03125
/*40  */     } else {                                                                 // (24) 0.01172
/*42  */         ifm_next = NULL;                                                     // (19) 0.02734
/*44  */     }                                                                        // (25) 0.007813
/*48  */     while (ifm_next) {                                                       // (22) 0.02148
/*50  */         ifm = ifm_next;                                                      // (18) 0.0293
/*52  */         from_batchq = next_from_batchq;                                      // (12) 0.03711
/*56  */         ifm_next = ifm->ifq_next;                                            // (10) 0.03906
/*58  */         if (ifm_next == &slirp->if_fastq) {                                  // (4) 0.04883
/*60  */             /* No more packets in fastq, switch to batchq */                 // (5) 0.04688
/*62  */             ifm_next = slirp->next_m;                                        // (6) 0.04688
/*64  */             next_from_batchq = true;                                         // (11) 0.03906
/*66  */         }                                                                    // 0.0
/*68  */         if (ifm_next == &slirp->if_batchq) {                                 // 0.0
/*70  */             /* end of batchq */                                              // 0.0
/*72  */             ifm_next = NULL;                                                 // 0.0
/*74  */         }                                                                    // 0.0
/*78  */         /* Try to send packet unless it already expired */                   // 0.0
/*80  */         if (ifm->expiration_date >= now && !if_encap(slirp, ifm)) {          // 0.0
/*82  */             /* Packet is delayed due to pending ARP resolution */            // 0.0
/*84  */             continue;                                                        // 0.0
/*86  */         }                                                                    // 0.0
/*90  */         if (ifm == slirp->next_m) {                                          // 0.0
/*92  */             /* Set which packet to send on next iteration */                 // 0.0
/*94  */             slirp->next_m = ifm->ifq_next;                                   // 0.0
/*96  */         }                                                                    // 0.0
/*100 */         /* Remove it from the queue */                                       // 0.0
/*102 */         ifqt = ifm->ifq_prev;                                                // 0.0
/*104 */         remque(ifm);                                                         // 0.0
/*108 */         /* If there are more packets for this session, re-queue them */      // 0.0
/*110 */         if (ifm->ifs_next != ifm) {                                          // 0.0
/*112 */             struct mbuf *next = ifm->ifs_next;                               // 0.0
/*116 */             insque(next, ifqt);                                              // 0.0
/*118 */             ifs_remque(ifm);                                                 // 0.0
/*122 */             if (!from_batchq) {                                              // 0.0
/*124 */                 /* Next packet in fastq is from the same session */          // 0.0
/*126 */                 ifm_next = next;                                             // 0.0
/*128 */                 next_from_batchq = false;                                    // 0.0
/*130 */             } else if (slirp->next_m == &slirp->if_batchq) {                 // 0.0
/*132 */                 /* Set next_m and ifm_next if the session packet is now the  // 0.0
/*134 */                  * only one on batchq */                                     // 0.0
/*136 */                 slirp->next_m = ifm_next = next;                             // 0.0
/*138 */             }                                                                // 0.0
/*140 */         }                                                                    // 0.0
/*144 */         /* Update so_queued */                                               // 0.0
/*146 */         if (ifm->ifq_so && --ifm->ifq_so->so_queued == 0) {                  // 0.0
/*148 */             /* If there's no more queued, reset nqueued */                   // 0.0
/*150 */             ifm->ifq_so->so_nqueued = 0;                                     // 0.0
/*152 */         }                                                                    // 0.0
/*156 */         m_free(ifm);                                                         // 0.0
/*158 */     }                                                                        // 0.0
/*162 */     slirp->if_start_busy = false;                                            // 0.0
/*164 */ }                                                                            // 0.0
