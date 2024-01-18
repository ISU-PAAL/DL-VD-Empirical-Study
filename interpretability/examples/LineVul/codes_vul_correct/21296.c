// commit message qemu@1ee24514ae (target=1, prob=0.6275878, correct=True): nvme: Add tracing
/*0  */ static uint16_t nvme_io_cmd(NvmeCtrl *n, NvmeCmd *cmd, NvmeRequest *req)  // (0) 0.1033
/*2  */ {                                                                         // (18) 0.00304
/*4  */     NvmeNamespace *ns;                                                    // (13) 0.03343
/*6  */     uint32_t nsid = le32_to_cpu(cmd->nsid);                               // (4) 0.06687
/*10 */     if (nsid == 0 || nsid > n->num_namespaces) {                          // (7) 0.06383
/*12 */         return NVME_INVALID_NSID | NVME_DNR;                              // (3) 0.07295
/*14 */     }                                                                     // (16) 0.01216
/*18 */     ns = &n->namespaces[nsid - 1];                                        // (9) 0.04863
/*20 */     switch (cmd->opcode) {                                                // (14) 0.03343
/*22 */     case NVME_CMD_FLUSH:                                                  // (10) 0.03951
/*24 */         return nvme_flush(n, ns, cmd, req);                               // (5) 0.06687
/*26 */     case NVME_CMD_WRITE_ZEROS:                                            // (8) 0.05167
/*28 */         return nvme_write_zeros(n, ns, cmd, req);                         // (1) 0.07599
/*30 */     case NVME_CMD_WRITE:                                                  // (11) 0.03951
/*32 */     case NVME_CMD_READ:                                                   // (12) 0.03647
/*34 */         return nvme_rw(n, ns, cmd, req);                                  // (6) 0.06687
/*36 */     default:                                                              // (15) 0.0152
/*38 */         return NVME_INVALID_OPCODE | NVME_DNR;                            // (2) 0.07599
/*40 */     }                                                                     // (17) 0.01216
/*42 */ }                                                                         // (19) 0.00304
