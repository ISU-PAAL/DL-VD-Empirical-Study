// commit message qemu@39a611a3e0 (target=1, prob=0.54422754, correct=True): block: Don't throw away errno via error_setg
/*0   */ void commit_active_start(BlockDriverState *bs, BlockDriverState *base,          // (9) 0.03711
/*2   */                          int64_t speed,                                         // (4) 0.05859
/*4   */                          BlockdevOnError on_error,                              // (3) 0.0625
/*6   */                          BlockDriverCompletionFunc *cb,                         // (2) 0.06445
/*8   */                          void *opaque, Error **errp)                            // (0) 0.06642
/*10  */ {                                                                               // (24) 0.001953
/*12  */     int64_t length, base_length;                                                // (15) 0.02539
/*14  */     int orig_base_flags;                                                        // (18) 0.01953
/*18  */     orig_base_flags = bdrv_get_flags(base);                                     // (10) 0.03711
/*22  */     if (bdrv_reopen(base, bs->open_flags, errp)) {                              // (7) 0.04883
/*24  */         return;                                                                 // (20) 0.01758
/*26  */     }                                                                           // (21) 0.007812
/*30  */     length = bdrv_getlength(bs);                                                // (14) 0.02734
/*32  */     if (length < 0) {                                                           // (19) 0.01953
/*34  */         error_setg(errp, "Unable to determine length of %s", bs->filename);     // (5) 0.05859
/*36  */         goto error_restore_flags;                                               // (13) 0.0293
/*38  */     }                                                                           // (22) 0.007812
/*42  */     base_length = bdrv_getlength(base);                                         // (11) 0.03125
/*44  */     if (base_length < 0) {                                                      // (17) 0.02344
/*46  */         error_setg(errp, "Unable to determine length of %s", base->filename);   // (6) 0.05664
/*48  */         goto error_restore_flags;                                               // (12) 0.0293
/*50  */     }                                                                           // (23) 0.007812
/*54  */     if (length > base_length) {                                                 // (16) 0.02344
/*56  */         if (bdrv_truncate(base, length) < 0) {                                  // (8) 0.04883
/*58  */             error_setg(errp, "Top image %s is larger than base image %s, and "  // (1) 0.06641
/*60  */                              "resize of base image failed",                     // 0.0
/*62  */                              bs->filename, base->filename);                     // 0.0
/*64  */             goto error_restore_flags;                                           // 0.0
/*66  */         }                                                                       // 0.0
/*68  */     }                                                                           // 0.0
/*72  */     bdrv_ref(base);                                                             // 0.0
/*74  */     mirror_start_job(bs, base, speed, 0, 0,                                     // 0.0
/*76  */                      on_error, on_error, cb, opaque, errp,                      // 0.0
/*78  */                      &commit_active_job_driver, false, base);                   // 0.0
/*80  */     if (error_is_set(errp)) {                                                   // 0.0
/*82  */         goto error_restore_flags;                                               // 0.0
/*84  */     }                                                                           // 0.0
/*88  */     return;                                                                     // 0.0
/*92  */ error_restore_flags:                                                            // 0.0
/*94  */     /* ignore error and errp for bdrv_reopen, because we want to propagate      // 0.0
/*96  */      * the original error */                                                    // 0.0
/*98  */     bdrv_reopen(base, orig_base_flags, NULL);                                   // 0.0
/*100 */     return;                                                                     // 0.0
/*102 */ }                                                                               // 0.0
