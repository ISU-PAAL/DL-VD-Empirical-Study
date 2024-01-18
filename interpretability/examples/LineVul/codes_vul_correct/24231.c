// commit message qemu@728470bea1 (target=1, prob=0.75324756, correct=True): rdma: fix memory leak
/*0  */ static void *qemu_fopen_rdma(RDMAContext *rdma, const char *mode)  // (3) 0.1233
/*2  */ {                                                                  // (12) 0.004566
/*4  */     QEMUFileRDMA *r = g_malloc0(sizeof(QEMUFileRDMA));             // (2) 0.1279
/*8  */     if (qemu_file_mode_is_not_valid(mode)) {                       // (4) 0.1005
/*10 */         return NULL;                                               // (7) 0.04566
/*12 */     }                                                              // (10) 0.01826
/*16 */     r->rdma = rdma;                                                // (6) 0.05479
/*20 */     if (mode[0] == 'w') {                                          // (5) 0.06393
/*22 */         r->file = qemu_fopen_ops(r, &rdma_write_ops);              // (0) 0.137
/*24 */     } else {                                                       // (9) 0.0274
/*26 */         r->file = qemu_fopen_ops(r, &rdma_read_ops);               // (1) 0.137
/*28 */     }                                                              // (11) 0.01826
/*32 */     return r->file;                                                // (8) 0.03653
/*34 */ }                                                                  // (13) 0.004566
