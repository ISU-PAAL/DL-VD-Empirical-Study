// commit message qemu@665414ad06 (target=1, prob=0.050396405, correct=False): postcopy: Add extra check for COPY function
/*0  */ static int ram_block_enable_notify(const char *block_name, void *host_addr,    // (4) 0.07869
/*2  */                                    ram_addr_t offset, ram_addr_t length,       // (0) 0.1574
/*4  */                                    void *opaque)                               // (1) 0.1279
/*6  */ {                                                                              // (12) 0.003279
/*8  */     MigrationIncomingState *mis = opaque;                                      // (10) 0.03934
/*10 */     struct uffdio_register reg_struct;                                         // (8) 0.0459
/*14 */     reg_struct.range.start = (uintptr_t)host_addr;                             // (6) 0.06885
/*16 */     reg_struct.range.len = length;                                             // (9) 0.04262
/*18 */     reg_struct.mode = UFFDIO_REGISTER_MODE_MISSING;                            // (5) 0.07541
/*22 */     /* Now tell our userfault_fd that it's responsible for this area */        // (7) 0.06557
/*24 */     if (ioctl(mis->userfault_fd, UFFDIO_REGISTER, &reg_struct)) {              // (3) 0.09836
/*26 */         error_report("%s userfault register: %s", __func__, strerror(errno));  // (2) 0.1049
/*36 */     return 0;                                                                  // (11) 0.01967
