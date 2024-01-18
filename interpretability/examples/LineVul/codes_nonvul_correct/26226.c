// commit message qemu@90e56fb46d (target=0, prob=0.4830133, correct=True): migration: protect the quit flag by lock
/*0  */ static void *do_data_decompress(void *opaque)                              // (15) 0.03125
/*2  */ {                                                                          // (26) 0.001953
/*4  */     DecompressParam *param = opaque;                                       // (20) 0.02344
/*6  */     unsigned long pagesize;                                                // (21) 0.01563
/*10 */     while (!quit_decomp_thread) {                                          // (16) 0.02539
/*12 */         qemu_mutex_lock(&param->mutex);                                    // (13) 0.04102
/*14 */         while (!param->start && !quit_decomp_thread) {                     // (10) 0.04297
/*16 */             qemu_cond_wait(&param->cond, &param->mutex);                   // (1) 0.05664
/*18 */         }                                                                  // (22) 0.01562
/*20 */         if (!quit_decomp_thread) {                                         // (14) 0.0332
/*22 */             pagesize = TARGET_PAGE_SIZE;                                   // (11) 0.04297
/*24 */             /* uncompress() will return failed in some case, especially    // (8) 0.04492
/*26 */              * when the page is dirted when doing the compression, it's    // (2) 0.05078
/*28 */              * not a problem because the dirty page will be retransferred  // (4) 0.04883
/*30 */              * and uncompress() won't break the data in other pages.       // (3) 0.05078
/*32 */              */                                                            // (18) 0.02539
/*34 */             uncompress((Bytef *)param->des, &pagesize,                     // (5) 0.04883
/*36 */                        (const Bytef *)param->compbuf, param->len);         // (0) 0.07031
/*38 */         }                                                                  // (23) 0.01562
/*40 */         param->start = false;                                              // (19) 0.02539
/*42 */         qemu_mutex_unlock(&param->mutex);                                  // (12) 0.04297
/*46 */         qemu_mutex_lock(&decomp_done_lock);                                // (9) 0.04492
/*48 */         param->done = true;                                                // (17) 0.02539
/*50 */         qemu_cond_signal(&decomp_done_cond);                               // (7) 0.04492
/*52 */         qemu_mutex_unlock(&decomp_done_lock);                              // (6) 0.04687
/*54 */     }                                                                      // (25) 0.007812
/*58 */     return NULL;                                                           // (24) 0.01172
/*60 */ }                                                                          // 0.0
