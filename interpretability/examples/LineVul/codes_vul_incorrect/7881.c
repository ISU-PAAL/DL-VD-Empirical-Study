// commit message qemu@60fe637bf0 (target=1, prob=0.1062574, correct=False): Start migrating migration code into a migration directory
/*0  */ static int qemu_rdma_get_fd(void *opaque)  // (1) 0.2308
/*2  */ {                                          // (4) 0.01282
/*4  */     QEMUFileRDMA *rfile = opaque;          // (2) 0.1923
/*6  */     RDMAContext *rdma = rfile->rdma;       // (0) 0.2308
/*10 */     return rdma->comp_channel->fd;         // (3) 0.1795
/*12 */ }                                          // (5) 0.01282
