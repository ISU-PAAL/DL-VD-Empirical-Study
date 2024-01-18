// commit message qemu@60fe637bf0 (target=1, prob=0.7558568, correct=True): Start migrating migration code into a migration directory
/*0   */ static uint64_t qemu_rdma_poll(RDMAContext *rdma, uint64_t *wr_id_out,            // (4) 0.06641
/*2   */                                uint32_t *byte_len)                                // (2) 0.07617
/*4   */ {                                                                                 // (24) 0.001955
/*6   */     int ret;                                                                      // (20) 0.01172
/*8   */     struct ibv_wc wc;                                                             // (13) 0.02344
/*10  */     uint64_t wr_id;                                                               // (14) 0.02148
/*14  */     ret = ibv_poll_cq(rdma->cq, 1, &wc);                                          // (8) 0.04883
/*18  */     if (!ret) {                                                                   // (19) 0.01562
/*20  */         *wr_id_out = RDMA_WRID_NONE;                                              // (10) 0.04492
/*22  */         return 0;                                                                 // (18) 0.01953
/*24  */     }                                                                             // (23) 0.007812
/*28  */     if (ret < 0) {                                                                // (16) 0.01953
/*30  */         fprintf(stderr, "ibv_poll_cq return %d!\n", ret);                         // (6) 0.06055
/*32  */         return ret;                                                               // (17) 0.01953
/*34  */     }                                                                             // (22) 0.007812
/*38  */     wr_id = wc.wr_id & RDMA_WRID_TYPE_MASK;                                       // (9) 0.04883
/*42  */     if (wc.status != IBV_WC_SUCCESS) {                                            // (11) 0.03906
/*44  */         fprintf(stderr, "ibv_poll_cq wc.status=%d %s!\n",                         // (3) 0.06836
/*46  */                         wc.status, ibv_wc_status_str(wc.status));                 // (0) 0.08398
/*48  */         fprintf(stderr, "ibv_poll_cq wrid=%s!\n", wrid_desc[wr_id]);              // (1) 0.07812
/*52  */         return -1;                                                                // (15) 0.02148
/*54  */     }                                                                             // (21) 0.007812
/*58  */     if (rdma->control_ready_expected &&                                           // (12) 0.02734
/*60  */         (wr_id >= RDMA_WRID_RECV_CONTROL)) {                                      // (7) 0.05078
/*62  */         DDDPRINTF("completion %s #%" PRId64 " received (%" PRId64 ")"             // (5) 0.06055
/*64  */                   " left %d\n", wrid_desc[RDMA_WRID_RECV_CONTROL],                // 0.0
/*66  */                   wr_id - RDMA_WRID_RECV_CONTROL, wr_id, rdma->nb_sent);          // 0.0
/*68  */         rdma->control_ready_expected = 0;                                         // 0.0
/*70  */     }                                                                             // 0.0
/*74  */     if (wr_id == RDMA_WRID_RDMA_WRITE) {                                          // 0.0
/*76  */         uint64_t chunk =                                                          // 0.0
/*78  */             (wc.wr_id & RDMA_WRID_CHUNK_MASK) >> RDMA_WRID_CHUNK_SHIFT;           // 0.0
/*80  */         uint64_t index =                                                          // 0.0
/*82  */             (wc.wr_id & RDMA_WRID_BLOCK_MASK) >> RDMA_WRID_BLOCK_SHIFT;           // 0.0
/*84  */         RDMALocalBlock *block = &(rdma->local_ram_blocks.block[index]);           // 0.0
/*88  */         DDDPRINTF("completions %s (%" PRId64 ") left %d, "                        // 0.0
/*90  */                  "block %" PRIu64 ", chunk: %" PRIu64 " %p %p\n",                 // 0.0
/*92  */                  print_wrid(wr_id), wr_id, rdma->nb_sent, index, chunk,           // 0.0
/*94  */                  block->local_host_addr, (void *)block->remote_host_addr);        // 0.0
/*98  */         clear_bit(chunk, block->transit_bitmap);                                  // 0.0
/*102 */         if (rdma->nb_sent > 0) {                                                  // 0.0
/*104 */             rdma->nb_sent--;                                                      // 0.0
/*106 */         }                                                                         // 0.0
/*110 */         if (!rdma->pin_all) {                                                     // 0.0
/*112 */             /*                                                                    // 0.0
/*114 */              * FYI: If one wanted to signal a specific chunk to be unregistered   // 0.0
/*116 */              * using LRU or workload-specific information, this is the function   // 0.0
/*118 */              * you would call to do so. That chunk would then get asynchronously  // 0.0
/*120 */              * unregistered later.                                                // 0.0
/*122 */              */                                                                   // 0.0
/*124 */ #ifdef RDMA_UNREGISTRATION_EXAMPLE                                                // 0.0
/*126 */             qemu_rdma_signal_unregister(rdma, index, chunk, wc.wr_id);            // 0.0
/*128 */ #endif                                                                            // 0.0
/*130 */         }                                                                         // 0.0
/*132 */     } else {                                                                      // 0.0
/*134 */         DDDPRINTF("other completion %s (%" PRId64 ") received left %d\n",         // 0.0
/*136 */             print_wrid(wr_id), wr_id, rdma->nb_sent);                             // 0.0
/*138 */     }                                                                             // 0.0
/*142 */     *wr_id_out = wc.wr_id;                                                        // 0.0
/*144 */     if (byte_len) {                                                               // 0.0
/*146 */         *byte_len = wc.byte_len;                                                  // 0.0
/*148 */     }                                                                             // 0.0
/*152 */     return  0;                                                                    // 0.0
/*154 */ }                                                                                 // 0.0
