// commit message qemu@0524951788 (target=0, prob=0.4917387, correct=True): spapr_nvram: Check return value from blk_getlength()
/*0  */ static void spapr_nvram_realize(VIOsPAPRDevice *dev, Error **errp)               // (6) 0.05273
/*2  */ {                                                                                // (23) 0.001953
/*4  */     sPAPRNVRAM *nvram = VIO_SPAPR_NVRAM(dev);                                    // (7) 0.05078
/*6  */     int ret;                                                                     // (19) 0.01172
/*10 */     if (nvram->blk) {                                                            // (15) 0.02344
/*12 */         nvram->size = blk_getlength(nvram->blk);                                 // (8) 0.04883
/*16 */         ret = blk_set_perm(nvram->blk,                                           // (9) 0.04297
/*18 */                            BLK_PERM_CONSISTENT_READ | BLK_PERM_WRITE,            // (0) 0.09375
/*20 */                            BLK_PERM_ALL, errp);                                  // (1) 0.07227
/*22 */         if (ret < 0) {                                                           // (13) 0.02734
/*24 */             return;                                                              // (14) 0.02539
/*26 */         }                                                                        // (18) 0.01562
/*28 */     } else {                                                                     // (20) 0.01172
/*30 */         nvram->size = DEFAULT_NVRAM_SIZE;                                        // (10) 0.04297
/*32 */     }                                                                            // (21) 0.007812
/*36 */     nvram->buf = g_malloc0(nvram->size);                                         // (11) 0.03906
/*40 */     if ((nvram->size < MIN_NVRAM_SIZE) || (nvram->size > MAX_NVRAM_SIZE)) {      // (3) 0.06641
/*42 */         error_setg(errp, "spapr-nvram must be between %d and %d bytes in size",  // (4) 0.06641
/*44 */                    MIN_NVRAM_SIZE, MAX_NVRAM_SIZE);                              // (5) 0.06641
/*46 */         return;                                                                  // (17) 0.01758
/*48 */     }                                                                            // (22) 0.007812
/*52 */     if (nvram->blk) {                                                            // (16) 0.02344
/*54 */         int alen = blk_pread(nvram->blk, 0, nvram->buf, nvram->size);            // (2) 0.07031
/*58 */         if (alen != nvram->size) {                                               // (12) 0.03711
/*60 */             error_setg(errp, "can't read spapr-nvram contents");                 // 0.0
/*62 */             return;                                                              // 0.0
/*64 */         }                                                                        // 0.0
/*66 */     } else if (nb_prom_envs > 0) {                                               // 0.0
/*68 */         /* Create a system partition to pass the -prom-env variables */          // 0.0
/*70 */         chrp_nvram_create_system_partition(nvram->buf, MIN_NVRAM_SIZE / 4);      // 0.0
/*72 */         chrp_nvram_create_free_partition(&nvram->buf[MIN_NVRAM_SIZE / 4],        // 0.0
/*74 */                                          nvram->size - MIN_NVRAM_SIZE / 4);      // 0.0
/*76 */     }                                                                            // 0.0
/*80 */     spapr_rtas_register(RTAS_NVRAM_FETCH, "nvram-fetch", rtas_nvram_fetch);      // 0.0
/*82 */     spapr_rtas_register(RTAS_NVRAM_STORE, "nvram-store", rtas_nvram_store);      // 0.0
/*84 */ }                                                                                // 0.0
