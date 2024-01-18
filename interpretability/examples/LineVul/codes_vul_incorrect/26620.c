// commit message qemu@58892b447f (target=1, prob=0.2010923, correct=False): hw/vfio/platform: irqfd setup sequence update
/*0  */ static int vfio_start_eventfd_injection(VFIOINTp *intp)                        // (2) 0.187
/*2  */ {                                                                              // (7) 0.00813
/*4  */     int ret;                                                                   // (4) 0.04878
/*8  */     ret = vfio_set_trigger_eventfd(intp, vfio_intp_interrupt);                 // (1) 0.2358
/*10 */     if (ret) {                                                                 // (3) 0.06504
/*12 */         error_report("vfio: Error: Failed to pass IRQ fd to the driver: %m");  // (0) 0.252
/*14 */     }                                                                          // (6) 0.03252
/*16 */     return ret;                                                                // (5) 0.04878
/*18 */ }                                                                              // (8) 0.00813
