// commit message qemu@1ee24514ae (target=1, prob=0.77759385, correct=True): nvme: Add tracing
/*0   */ static void nvme_process_db(NvmeCtrl *n, hwaddr addr, int val)                      // (5) 0.04883
/*2   */ {                                                                                   // (25) 0.001953
/*4   */     uint32_t qid;                                                                   // (20) 0.01953
/*8   */     if (addr & ((1 << 2) - 1)) {                                                    // (13) 0.03125
/*10  */         return;                                                                     // (21) 0.01758
/*12  */     }                                                                               // (24) 0.007812
/*16  */     if (((addr - 0x1000) >> 2) & 1) {                                               // (8) 0.03711
/*18  */         uint16_t new_head = val & 0xffff;                                           // (7) 0.04102
/*20  */         int start_sqs;                                                              // (16) 0.02539
/*22  */         NvmeCQueue *cq;                                                             // (12) 0.03125
/*26  */         qid = (addr - (0x1000 + (1 << 2))) >> 3;                                    // (4) 0.05078
/*28  */         if (nvme_check_cqid(n, qid)) {                                              // (6) 0.04688
/*30  */             return;                                                                 // (17) 0.02539
/*32  */         }                                                                           // (22) 0.01562
/*36  */         cq = n->cq[qid];                                                            // (11) 0.03516
/*38  */         if (new_head >= cq->size) {                                                 // (10) 0.03711
/*40  */             return;                                                                 // (18) 0.02539
/*42  */         }                                                                           // (23) 0.01562
/*46  */         start_sqs = nvme_cq_full(cq) ? 1 : 0;                                       // (3) 0.05664
/*48  */         cq->head = new_head;                                                        // (14) 0.03125
/*50  */         if (start_sqs) {                                                            // (15) 0.0293
/*52  */             NvmeSQueue *sq;                                                         // (9) 0.03711
/*54  */             QTAILQ_FOREACH(sq, &cq->sq_list, entry) {                               // (2) 0.0625
/*56  */                 timer_mod(sq->timer, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 500);  // (0) 0.0918
/*58  */             }                                                                       // (19) 0.02344
/*60  */             timer_mod(cq->timer, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 500);      // (1) 0.08594
/*62  */         }                                                                           // 0.0
/*66  */         if (cq->tail != cq->head) {                                                 // 0.0
/*68  */             nvme_isr_notify(n, cq);                                                 // 0.0
/*70  */         }                                                                           // 0.0
/*72  */     } else {                                                                        // 0.0
/*74  */         uint16_t new_tail = val & 0xffff;                                           // 0.0
/*76  */         NvmeSQueue *sq;                                                             // 0.0
/*80  */         qid = (addr - 0x1000) >> 3;                                                 // 0.0
/*82  */         if (nvme_check_sqid(n, qid)) {                                              // 0.0
/*84  */             return;                                                                 // 0.0
/*86  */         }                                                                           // 0.0
/*90  */         sq = n->sq[qid];                                                            // 0.0
/*92  */         if (new_tail >= sq->size) {                                                 // 0.0
/*94  */             return;                                                                 // 0.0
/*96  */         }                                                                           // 0.0
/*100 */         sq->tail = new_tail;                                                        // 0.0
/*102 */         timer_mod(sq->timer, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 500);          // 0.0
/*104 */     }                                                                               // 0.0
/*106 */ }                                                                                   // 0.0
