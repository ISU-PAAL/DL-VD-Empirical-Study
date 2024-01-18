// commit message qemu@2a313e5cf6 (target=0, prob=0.49475157, correct=True): migration: Don't play games with the requested cache size
/*0  */ int64_t xbzrle_cache_resize(int64_t new_size, Error **errp)           // (4) 0.05469
/*2  */ {                                                                     // (29) 0.001953
/*4  */     PageCache *new_cache;                                             // (20) 0.01953
/*6  */     int64_t ret;                                                      // (21) 0.01758
/*10 */     /* Check for truncation */                                        // (22) 0.01758
/*12 */     if (new_size != (size_t)new_size) {                               // (8) 0.03711
/*14 */         error_setg(errp, QERR_INVALID_PARAMETER_VALUE, "cache size",  // (1) 0.06641
/*16 */                    "exceeding address space");                        // (6) 0.04883
/*18 */         return -1;                                                    // (18) 0.02148
/*20 */     }                                                                 // (26) 0.007812
/*24 */     /* Cache should not be larger than guest ram size */              // (14) 0.02734
/*26 */     if (new_size > ram_bytes_total()) {                               // (12) 0.03125
/*28 */         error_setg(errp, QERR_INVALID_PARAMETER_VALUE, "cache size",  // (0) 0.06641
/*30 */                    "exceeds guest ram size");                         // (5) 0.05078
/*32 */         return -1;                                                    // (19) 0.02148
/*34 */     }                                                                 // (27) 0.007812
/*38 */     XBZRLE_cache_lock();                                              // (17) 0.02539
/*42 */     if (XBZRLE.cache != NULL) {                                       // (13) 0.03125
/*44 */         if (pow2floor(new_size) == migrate_xbzrle_cache_size()) {     // (2) 0.06055
/*46 */             goto out_new_size;                                        // (10) 0.03516
/*48 */         }                                                             // (23) 0.01562
/*50 */         new_cache = cache_init(new_size, TARGET_PAGE_SIZE, errp);     // (3) 0.05859
/*52 */         if (!new_cache) {                                             // (15) 0.02734
/*54 */             ret = -1;                                                 // (11) 0.03125
/*56 */             goto out;                                                 // (16) 0.02734
/*58 */         }                                                             // (24) 0.01562
/*62 */         cache_fini(XBZRLE.cache);                                     // (7) 0.03906
/*64 */         XBZRLE.cache = new_cache;                                     // (9) 0.03711
/*66 */     }                                                                 // (28) 0.007812
/*70 */ out_new_size:                                                         // (25) 0.01172
/*72 */     ret = pow2floor(new_size);                                        // 0.0
/*74 */ out:                                                                  // 0.0
/*76 */     XBZRLE_cache_unlock();                                            // 0.0
/*78 */     return ret;                                                       // 0.0
/*80 */ }                                                                     // 0.0
