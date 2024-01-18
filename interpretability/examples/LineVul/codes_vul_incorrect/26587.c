// commit message qemu@b248ede2ef (target=1, prob=0.39658016, correct=False): slirp: Fix requeuing of batchq packets in if_start
/*0   */ if_start(Slirp *slirp)                                            // (16) 0.02344
/*2   */ {                                                                 // (37) 0.001953
/*4   */     uint64_t now = qemu_get_clock_ns(rt_clock);                   // (3) 0.04492
/*6   */     int requeued = 0;                                             // (25) 0.01953
/*8   */ 	struct mbuf *ifm, *ifqt;                                         // (17) 0.02344
/*12  */ 	DEBUG_CALL("if_start");                                          // (23) 0.01953
/*16  */ 	if (slirp->if_queued == 0)                                       // (13) 0.02734
/*18  */ 	   return; /* Nothing to do */                                   // (24) 0.01953
/*22  */  again:                                                           // (32) 0.003906
/*24  */         /* check if we can really output */                       // (11) 0.0293
/*26  */         if (!slirp_can_output(slirp->opaque))                     // (2) 0.04687
/*28  */             return;                                               // (15) 0.02539
/*32  */ 	/*                                                               // (34) 0.003906
/*34  */ 	 * See which queue to get next packet from                       // (26) 0.01953
/*36  */ 	 * If there's something in the fastq, select it immediately      // (14) 0.02734
/*38  */ 	 */                                                              // (35) 0.003906
/*40  */ 	if (slirp->if_fastq.ifq_next != &slirp->if_fastq) {              // (0) 0.05469
/*42  */ 		ifm = slirp->if_fastq.ifq_next;                                 // (6) 0.03711
/*44  */ 	} else {                                                         // (30) 0.007812
/*46  */ 		/* Nothing on fastq, see if next_m is valid */                  // (10) 0.03125
/*48  */ 		if (slirp->next_m != &slirp->if_batchq)                         // (4) 0.04297
/*50  */ 		   ifm = slirp->next_m;                                         // (12) 0.0293
/*52  */ 		else                                                            // (31) 0.005859
/*54  */ 		   ifm = slirp->if_batchq.ifq_next;                             // (5) 0.04102
/*58  */ 		/* Set which packet to send on next iteration */                // (18) 0.02344
/*60  */ 		slirp->next_m = ifm->ifq_next;                                  // (7) 0.03516
/*62  */ 	}                                                                // (36) 0.003906
/*64  */ 	/* Remove it from the queue */                                   // (28) 0.01562
/*66  */ 	ifqt = ifm->ifq_prev;                                            // (19) 0.02344
/*68  */ 	remque(ifm);                                                     // (29) 0.01367
/*70  */ 	slirp->if_queued--;                                              // (22) 0.02148
/*74  */ 	/* If there are more packets for this session, re-queue them */  // (8) 0.03125
/*76  */ 	if (ifm->ifs_next != /* ifm->ifs_prev != */ ifm) {               // (1) 0.04883
/*78  */ 		insque(ifm->ifs_next, ifqt);                                    // (9) 0.03125
/*80  */ 		ifs_remque(ifm);                                                // (21) 0.02148
/*82  */ 	}                                                                // (33) 0.003906
/*86  */ 	/* Update so_queued */                                           // (27) 0.01563
/*88  */ 	if (ifm->ifq_so) {                                               // (20) 0.02344
/*90  */ 		if (--ifm->ifq_so->so_queued == 0)                              // 0.0
/*92  */ 		   /* If there's no more queued, reset nqueued */               // 0.0
/*94  */ 		   ifm->ifq_so->so_nqueued = 0;                                 // 0.0
/*96  */ 	}                                                                // 0.0
/*100 */         if (ifm->expiration_date < now) {                         // 0.0
/*102 */             /* Expired */                                         // 0.0
/*104 */             m_free(ifm);                                          // 0.0
/*106 */         } else {                                                  // 0.0
/*108 */             /* Encapsulate the packet for sending */              // 0.0
/*110 */             if (if_encap(slirp, ifm)) {                           // 0.0
/*112 */                 m_free(ifm);                                      // 0.0
/*114 */             } else {                                              // 0.0
/*116 */                 /* re-queue */                                    // 0.0
/*118 */                 insque(ifm, ifqt);                                // 0.0
/*120 */                 requeued++;                                       // 0.0
/*122 */             }                                                     // 0.0
/*124 */         }                                                         // 0.0
/*128 */ 	if (slirp->if_queued)                                            // 0.0
/*130 */ 	   goto again;                                                   // 0.0
/*134 */         slirp->if_queued = requeued;                              // 0.0
/*136 */ }                                                                 // 0.0
