// commit message qemu@786a4ea82e (target=0, prob=0.35272607, correct=True): Convert (ffs(val) - 1) to ctz32(val)
/*0   */ static int bdrv_qed_open(BlockDriverState *bs, QDict *options, int flags,         // (6) 0.05078
/*2   */                          Error **errp)                                            // (1) 0.05664
/*4   */ {                                                                                 // (27) 0.001953
/*6   */     BDRVQEDState *s = bs->opaque;                                                 // (12) 0.03516
/*8   */     QEDHeader le_header;                                                          // (19) 0.01953
/*10  */     int64_t file_size;                                                            // (18) 0.02148
/*12  */     int ret;                                                                      // (23) 0.01172
/*16  */     s->bs = bs;                                                                   // (20) 0.01953
/*18  */     QSIMPLEQ_INIT(&s->allocating_write_reqs);                                     // (11) 0.04102
/*22  */     ret = bdrv_pread(bs->file, 0, &le_header, sizeof(le_header));                 // (3) 0.05469
/*24  */     if (ret < 0) {                                                                // (22) 0.01953
/*26  */         return ret;                                                               // (21) 0.01953
/*28  */     }                                                                             // (24) 0.007812
/*30  */     qed_header_le_to_cpu(&le_header, &s->header);                                 // (7) 0.04492
/*34  */     if (s->header.magic != QED_MAGIC) {                                           // (13) 0.03516
/*36  */         error_setg(errp, "Image not in QED format");                              // (8) 0.04492
/*38  */         return -EINVAL;                                                           // (16) 0.02539
/*40  */     }                                                                             // (25) 0.007812
/*42  */     if (s->header.features & ~QED_FEATURE_MASK) {                                 // (10) 0.04297
/*44  */         /* image uses unsupported feature bits */                                 // (14) 0.02734
/*46  */         char buf[64];                                                             // (17) 0.02344
/*48  */         snprintf(buf, sizeof(buf), "%" PRIx64,                                    // (9) 0.04492
/*50  */             s->header.features & ~QED_FEATURE_MASK);                              // (5) 0.05273
/*52  */         error_set(errp, QERR_UNKNOWN_BLOCK_FORMAT_FEATURE,                        // (0) 0.05859
/*54  */             bdrv_get_device_name(bs), "QED", buf);                                // (2) 0.05664
/*56  */         return -ENOTSUP;                                                          // (15) 0.02539
/*58  */     }                                                                             // (26) 0.007812
/*60  */     if (!qed_is_cluster_size_valid(s->header.cluster_size)) {                     // (4) 0.05273
/*62  */         return -EINVAL;                                                           // 0.0
/*64  */     }                                                                             // 0.0
/*68  */     /* Round down file size to the last cluster */                                // 0.0
/*70  */     file_size = bdrv_getlength(bs->file);                                         // 0.0
/*72  */     if (file_size < 0) {                                                          // 0.0
/*74  */         return file_size;                                                         // 0.0
/*76  */     }                                                                             // 0.0
/*78  */     s->file_size = qed_start_of_cluster(s, file_size);                            // 0.0
/*82  */     if (!qed_is_table_size_valid(s->header.table_size)) {                         // 0.0
/*84  */         return -EINVAL;                                                           // 0.0
/*86  */     }                                                                             // 0.0
/*88  */     if (!qed_is_image_size_valid(s->header.image_size,                            // 0.0
/*90  */                                  s->header.cluster_size,                          // 0.0
/*92  */                                  s->header.table_size)) {                         // 0.0
/*94  */         return -EINVAL;                                                           // 0.0
/*96  */     }                                                                             // 0.0
/*98  */     if (!qed_check_table_offset(s, s->header.l1_table_offset)) {                  // 0.0
/*100 */         return -EINVAL;                                                           // 0.0
/*102 */     }                                                                             // 0.0
/*106 */     s->table_nelems = (s->header.cluster_size * s->header.table_size) /           // 0.0
/*108 */                       sizeof(uint64_t);                                           // 0.0
/*110 */     s->l2_shift = ffs(s->header.cluster_size) - 1;                                // 0.0
/*112 */     s->l2_mask = s->table_nelems - 1;                                             // 0.0
/*114 */     s->l1_shift = s->l2_shift + ffs(s->table_nelems) - 1;                         // 0.0
/*118 */     /* Header size calculation must not overflow uint32_t */                      // 0.0
/*120 */     if (s->header.header_size > UINT32_MAX / s->header.cluster_size) {            // 0.0
/*122 */         return -EINVAL;                                                           // 0.0
/*124 */     }                                                                             // 0.0
/*128 */     if ((s->header.features & QED_F_BACKING_FILE)) {                              // 0.0
/*130 */         if ((uint64_t)s->header.backing_filename_offset +                         // 0.0
/*132 */             s->header.backing_filename_size >                                     // 0.0
/*134 */             s->header.cluster_size * s->header.header_size) {                     // 0.0
/*136 */             return -EINVAL;                                                       // 0.0
/*138 */         }                                                                         // 0.0
/*142 */         ret = qed_read_string(bs->file, s->header.backing_filename_offset,        // 0.0
/*144 */                               s->header.backing_filename_size, bs->backing_file,  // 0.0
/*146 */                               sizeof(bs->backing_file));                          // 0.0
/*148 */         if (ret < 0) {                                                            // 0.0
/*150 */             return ret;                                                           // 0.0
/*152 */         }                                                                         // 0.0
/*156 */         if (s->header.features & QED_F_BACKING_FORMAT_NO_PROBE) {                 // 0.0
/*158 */             pstrcpy(bs->backing_format, sizeof(bs->backing_format), "raw");       // 0.0
/*160 */         }                                                                         // 0.0
/*162 */     }                                                                             // 0.0
/*166 */     /* Reset unknown autoclear feature bits.  This is a backwards                 // 0.0
/*168 */      * compatibility mechanism that allows images to be opened by older           // 0.0
/*170 */      * programs, which "knock out" unknown feature bits.  When an image is        // 0.0
/*172 */      * opened by a newer program again it can detect that the autoclear           // 0.0
/*174 */      * feature is no longer valid.                                                // 0.0
/*176 */      */                                                                           // 0.0
/*178 */     if ((s->header.autoclear_features & ~QED_AUTOCLEAR_FEATURE_MASK) != 0 &&      // 0.0
/*180 */         !bdrv_is_read_only(bs->file) && !(flags & BDRV_O_INCOMING)) {             // 0.0
/*182 */         s->header.autoclear_features &= QED_AUTOCLEAR_FEATURE_MASK;               // 0.0
/*186 */         ret = qed_write_header_sync(s);                                           // 0.0
/*188 */         if (ret) {                                                                // 0.0
/*190 */             return ret;                                                           // 0.0
/*192 */         }                                                                         // 0.0
/*196 */         /* From here on only known autoclear feature bits are valid */            // 0.0
/*198 */         bdrv_flush(bs->file);                                                     // 0.0
/*200 */     }                                                                             // 0.0
/*204 */     s->l1_table = qed_alloc_table(s);                                             // 0.0
/*206 */     qed_init_l2_cache(&s->l2_cache);                                              // 0.0
/*210 */     ret = qed_read_l1_table_sync(s);                                              // 0.0
/*212 */     if (ret) {                                                                    // 0.0
/*214 */         goto out;                                                                 // 0.0
/*216 */     }                                                                             // 0.0
/*220 */     /* If image was not closed cleanly, check consistency */                      // 0.0
/*222 */     if (!(flags & BDRV_O_CHECK) && (s->header.features & QED_F_NEED_CHECK)) {     // 0.0
/*224 */         /* Read-only images cannot be fixed.  There is no risk of corruption      // 0.0
/*226 */          * since write operations are not possible.  Therefore, allow             // 0.0
/*228 */          * potentially inconsistent images to be opened read-only.  This can      // 0.0
/*230 */          * aid data recovery from an otherwise inconsistent image.                // 0.0
/*232 */          */                                                                       // 0.0
/*234 */         if (!bdrv_is_read_only(bs->file) &&                                       // 0.0
/*236 */             !(flags & BDRV_O_INCOMING)) {                                         // 0.0
/*238 */             BdrvCheckResult result = {0};                                         // 0.0
/*242 */             ret = qed_check(s, &result, true);                                    // 0.0
/*244 */             if (ret) {                                                            // 0.0
/*246 */                 goto out;                                                         // 0.0
/*248 */             }                                                                     // 0.0
/*250 */         }                                                                         // 0.0
/*252 */     }                                                                             // 0.0
/*256 */     bdrv_qed_attach_aio_context(bs, bdrv_get_aio_context(bs));                    // 0.0
/*260 */ out:                                                                              // 0.0
/*262 */     if (ret) {                                                                    // 0.0
/*264 */         qed_free_l2_cache(&s->l2_cache);                                          // 0.0
/*266 */         qemu_vfree(s->l1_table);                                                  // 0.0
/*268 */     }                                                                             // 0.0
/*270 */     return ret;                                                                   // 0.0
/*272 */ }                                                                                 // 0.0
