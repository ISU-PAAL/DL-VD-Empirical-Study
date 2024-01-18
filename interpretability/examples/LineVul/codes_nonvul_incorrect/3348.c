// commit message qemu@8857188251 (target=0, prob=0.8102449, correct=False): rdma: check if RDMAControlHeader::len match transferred byte
/*0   */ static int qemu_rdma_block_for_wrid(RDMAContext *rdma, int wrid_requested)     // (2) 0.0625
/*2   */ {                                                                              // (28) 0.001953
/*4   */     int num_cq_events = 0, ret = 0;                                            // (10) 0.0332
/*6   */     struct ibv_cq *cq;                                                         // (15) 0.02539
/*8   */     void *cq_ctx;                                                              // (18) 0.01953
/*10  */     uint64_t wr_id = RDMA_WRID_NONE, wr_id_in;                                 // (5) 0.05078
/*14  */     if (ibv_req_notify_cq(rdma->cq, 0)) {                                      // (7) 0.04883
/*16  */         return -1;                                                             // (17) 0.02148
/*18  */     }                                                                          // (25) 0.007812
/*20  */     /* poll cq first */                                                        // (20) 0.01758
/*22  */     while (wr_id != wrid_requested) {                                          // (11) 0.03125
/*24  */         ret = qemu_rdma_poll(rdma, &wr_id_in);                                 // (3) 0.05469
/*26  */         if (ret < 0) {                                                         // (13) 0.02734
/*28  */             return ret;                                                        // (14) 0.02734
/*30  */         }                                                                      // (21) 0.01562
/*34  */         wr_id = wr_id_in & RDMA_WRID_TYPE_MASK;                                // (4) 0.05469
/*38  */         if (wr_id == RDMA_WRID_NONE) {                                         // (8) 0.04492
/*40  */             break;                                                             // (16) 0.02539
/*42  */         }                                                                      // (22) 0.01562
/*44  */         if (wr_id != wrid_requested) {                                         // (9) 0.03906
/*46  */             DDDPRINTF("A Wanted wrid %s (%d) but got %s (%" PRIu64 ")\n",      // (0) 0.07812
/*48  */                 print_wrid(wrid_requested),                                    // (6) 0.05078
/*50  */                 wrid_requested, print_wrid(wr_id), wr_id);                     // (1) 0.06641
/*52  */         }                                                                      // (23) 0.01562
/*54  */     }                                                                          // (26) 0.007812
/*58  */     if (wr_id == wrid_requested) {                                             // (12) 0.03125
/*60  */         return 0;                                                              // (19) 0.01953
/*62  */     }                                                                          // (27) 0.007812
/*66  */     while (1) {                                                                // (24) 0.01562
/*68  */         /*                                                                     // 0.0
/*70  */          * Coroutine doesn't start until process_incoming_migration()          // 0.0
/*72  */          * so don't yield unless we know we're running inside of a coroutine.  // 0.0
/*74  */          */                                                                    // 0.0
/*76  */         if (rdma->migration_started_on_destination) {                          // 0.0
/*78  */             yield_until_fd_readable(rdma->comp_channel->fd);                   // 0.0
/*80  */         }                                                                      // 0.0
/*84  */         if (ibv_get_cq_event(rdma->comp_channel, &cq, &cq_ctx)) {              // 0.0
/*86  */             perror("ibv_get_cq_event");                                        // 0.0
/*88  */             goto err_block_for_wrid;                                           // 0.0
/*90  */         }                                                                      // 0.0
/*94  */         num_cq_events++;                                                       // 0.0
/*98  */         if (ibv_req_notify_cq(cq, 0)) {                                        // 0.0
/*100 */             goto err_block_for_wrid;                                           // 0.0
/*102 */         }                                                                      // 0.0
/*106 */         while (wr_id != wrid_requested) {                                      // 0.0
/*108 */             ret = qemu_rdma_poll(rdma, &wr_id_in);                             // 0.0
/*110 */             if (ret < 0) {                                                     // 0.0
/*112 */                 goto err_block_for_wrid;                                       // 0.0
/*114 */             }                                                                  // 0.0
/*118 */             wr_id = wr_id_in & RDMA_WRID_TYPE_MASK;                            // 0.0
/*122 */             if (wr_id == RDMA_WRID_NONE) {                                     // 0.0
/*124 */                 break;                                                         // 0.0
/*126 */             }                                                                  // 0.0
/*128 */             if (wr_id != wrid_requested) {                                     // 0.0
/*130 */                 DDDPRINTF("B Wanted wrid %s (%d) but got %s (%" PRIu64 ")\n",  // 0.0
/*132 */                     print_wrid(wrid_requested), wrid_requested,                // 0.0
/*134 */                     print_wrid(wr_id), wr_id);                                 // 0.0
/*136 */             }                                                                  // 0.0
/*138 */         }                                                                      // 0.0
/*142 */         if (wr_id == wrid_requested) {                                         // 0.0
/*144 */             goto success_block_for_wrid;                                       // 0.0
/*146 */         }                                                                      // 0.0
/*148 */     }                                                                          // 0.0
/*152 */ success_block_for_wrid:                                                        // 0.0
/*154 */     if (num_cq_events) {                                                       // 0.0
/*156 */         ibv_ack_cq_events(cq, num_cq_events);                                  // 0.0
/*158 */     }                                                                          // 0.0
/*160 */     return 0;                                                                  // 0.0
/*164 */ err_block_for_wrid:                                                            // 0.0
/*166 */     if (num_cq_events) {                                                       // 0.0
/*168 */         ibv_ack_cq_events(cq, num_cq_events);                                  // 0.0
/*170 */     }                                                                          // 0.0
/*172 */     return ret;                                                                // 0.0
/*174 */ }                                                                              // 0.0
