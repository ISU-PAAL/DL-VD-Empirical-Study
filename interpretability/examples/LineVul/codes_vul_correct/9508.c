// commit message qemu@97f3ad3551 (target=1, prob=0.86397874, correct=True): migration: Use g_new() & friends where that makes obvious sense
/*0   */ static int qemu_rdma_register_and_get_keys(RDMAContext *rdma,                   // (5) 0.05078
/*2   */         RDMALocalBlock *block, uintptr_t host_addr,                             // (7) 0.04492
/*4   */         uint32_t *lkey, uint32_t *rkey, int chunk,                              // (4) 0.05078
/*6   */         uint8_t *chunk_start, uint8_t *chunk_end)                               // (3) 0.05273
/*8   */ {                                                                               // (27) 0.001953
/*10  */     if (block->mr) {                                                            // (18) 0.01953
/*12  */         if (lkey) {                                                             // (14) 0.02539
/*14  */             *lkey = block->mr->lkey;                                            // (9) 0.04297
/*16  */         }                                                                       // (20) 0.01562
/*18  */         if (rkey) {                                                             // (15) 0.02539
/*20  */             *rkey = block->mr->rkey;                                            // (10) 0.04297
/*22  */         }                                                                       // (21) 0.01562
/*24  */         return 0;                                                               // (19) 0.01953
/*26  */     }                                                                           // (25) 0.007812
/*30  */     /* allocate memory to store chunk MRs */                                    // (16) 0.02344
/*32  */     if (!block->pmr) {                                                          // (17) 0.02148
/*34  */         block->pmr = g_malloc0(block->nb_chunks * sizeof(struct ibv_mr *));     // (0) 0.06641
/*36  */     }                                                                           // (26) 0.007812
/*40  */     /*                                                                          // (24) 0.007813
/*42  */      * If 'rkey', then we're the destination, so grant access to the source.    // (8) 0.04492
/*44  */      *                                                                          // (22) 0.009766
/*46  */      * If 'lkey', then we're the source VM, so grant access only to ourselves.  // (6) 0.04688
/*48  */      */                                                                         // (23) 0.009766
/*50  */     if (!block->pmr[chunk]) {                                                   // (13) 0.02734
/*52  */         uint64_t len = chunk_end - chunk_start;                                 // (11) 0.04102
/*56  */         trace_qemu_rdma_register_and_get_keys(len, chunk_start);                // (1) 0.05859
/*60  */         block->pmr[chunk] = ibv_reg_mr(rdma->pd,                                // (2) 0.05469
/*62  */                 chunk_start, len,                                               // (12) 0.04102
/*64  */                 (rkey ? (IBV_ACCESS_LOCAL_WRITE |                               // 0.0
/*66  */                         IBV_ACCESS_REMOTE_WRITE) : 0));                         // 0.0
/*70  */         if (!block->pmr[chunk]) {                                               // 0.0
/*72  */             perror("Failed to register chunk!");                                // 0.0
/*74  */             fprintf(stderr, "Chunk details: block: %d chunk index %d"           // 0.0
/*76  */                             " start %" PRIuPTR " end %" PRIuPTR                 // 0.0
/*78  */                             " host %" PRIuPTR                                   // 0.0
/*80  */                             " local %" PRIuPTR " registrations: %d\n",          // 0.0
/*82  */                             block->index, chunk, (uintptr_t)chunk_start,        // 0.0
/*84  */                             (uintptr_t)chunk_end, host_addr,                    // 0.0
/*86  */                             (uintptr_t)block->local_host_addr,                  // 0.0
/*88  */                             rdma->total_registrations);                         // 0.0
/*90  */             return -1;                                                          // 0.0
/*92  */         }                                                                       // 0.0
/*94  */         rdma->total_registrations++;                                            // 0.0
/*96  */     }                                                                           // 0.0
/*100 */     if (lkey) {                                                                 // 0.0
/*102 */         *lkey = block->pmr[chunk]->lkey;                                        // 0.0
/*104 */     }                                                                           // 0.0
/*106 */     if (rkey) {                                                                 // 0.0
/*108 */         *rkey = block->pmr[chunk]->rkey;                                        // 0.0
/*110 */     }                                                                           // 0.0
/*112 */     return 0;                                                                   // 0.0
/*114 */ }                                                                               // 0.0
