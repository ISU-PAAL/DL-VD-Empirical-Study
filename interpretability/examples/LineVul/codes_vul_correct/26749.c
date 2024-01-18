// commit message qemu@1ee24514ae (target=1, prob=0.9909484, correct=True): nvme: Add tracing
/*0  */ static uint16_t nvme_create_sq(NvmeCtrl *n, NvmeCmd *cmd)  // (0) 0.05273
/*2  */ {                                                          // (24) 0.001953
/*4  */     NvmeSQueue *sq;                                        // (18) 0.02148
/*6  */     NvmeCreateSq *c = (NvmeCreateSq *)cmd;                 // (13) 0.04297
/*10 */     uint16_t cqid = le16_to_cpu(c->cqid);                  // (5) 0.04687
/*12 */     uint16_t sqid = le16_to_cpu(c->sqid);                  // (14) 0.04297
/*14 */     uint16_t qsize = le16_to_cpu(c->qsize);                // (15) 0.04297
/*16 */     uint16_t qflags = le16_to_cpu(c->sq_flags);            // (9) 0.04492
/*18 */     uint64_t prp1 = le64_to_cpu(c->prp1);                  // (6) 0.04687
/*22 */     if (!cqid || nvme_check_cqid(n, cqid)) {               // (3) 0.05078
/*24 */         return NVME_INVALID_CQID | NVME_DNR;               // (4) 0.04883
/*26 */     }                                                      // (19) 0.007812
/*28 */     if (!sqid || !nvme_check_sqid(n, sqid)) {              // (10) 0.04492
/*30 */         return NVME_INVALID_QID | NVME_DNR;                // (7) 0.04687
/*32 */     }                                                      // (20) 0.007812
/*34 */     if (!qsize || qsize > NVME_CAP_MQES(n->bar.cap)) {     // (2) 0.05078
/*36 */         return NVME_MAX_QSIZE_EXCEEDED | NVME_DNR;         // (1) 0.05273
/*38 */     }                                                      // (21) 0.007812
/*40 */     if (!prp1 || prp1 & (n->page_size - 1)) {              // (8) 0.04492
/*42 */         return NVME_INVALID_FIELD | NVME_DNR;              // (11) 0.04492
/*44 */     }                                                      // (22) 0.007812
/*46 */     if (!(NVME_SQ_FLAGS_PC(qflags))) {                     // (16) 0.04102
/*48 */         return NVME_INVALID_FIELD | NVME_DNR;              // (12) 0.04492
/*50 */     }                                                      // (23) 0.007812
/*52 */     sq = g_malloc0(sizeof(*sq));                           // (17) 0.03125
/*54 */     nvme_init_sq(sq, n, prp1, sqid, cqid, qsize + 1);      // 0.0
/*56 */     return NVME_SUCCESS;                                   // 0.0
/*58 */ }                                                          // 0.0
