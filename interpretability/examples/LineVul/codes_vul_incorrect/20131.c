// commit message qemu@e95205e1f9 (target=1, prob=0.2370813, correct=False): dma-helpers: Fix race condition of continue_after_map_failure and dma_aio_cancel
/*0  */ static void continue_after_map_failure(void *opaque)  // (3) 0.1702
/*2  */ {                                                     // (4) 0.01064
/*4  */     DMAAIOCB *dbs = (DMAAIOCB *)opaque;               // (1) 0.234
/*8  */     dbs->bh = qemu_bh_new(reschedule_dma, dbs);       // (0) 0.2766
/*10 */     qemu_bh_schedule(dbs->bh);                        // (2) 0.1809
/*12 */ }                                                     // (5) 0.01064
