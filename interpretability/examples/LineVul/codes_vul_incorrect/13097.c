// commit message qemu@2ebafc854d (target=1, prob=0.12576547, correct=False): qcow2: Fix header extension size check
/*0   */ static int qcow2_read_extensions(BlockDriverState *bs, uint64_t start_offset,         // (7) 0.04883
/*2   */                                  uint64_t end_offset, void **p_feature_table,         // (0) 0.09375
/*4   */                                  Error **errp)                                        // (3) 0.07227
/*6   */ {                                                                                     // (25) 0.001953
/*8   */     BDRVQcowState *s = bs->opaque;                                                    // (10) 0.03516
/*10  */     QCowExtension ext;                                                                // (16) 0.01758
/*12  */     uint64_t offset;                                                                  // (17) 0.01758
/*14  */     int ret;                                                                          // (20) 0.01172
/*18  */ #ifdef DEBUG_EXT                                                                      // (22) 0.01172
/*20  */     printf("qcow2_read_extensions: start=%ld end=%ld\n", start_offset, end_offset);   // (4) 0.06445
/*22  */ #endif                                                                                // (23) 0.003906
/*24  */     offset = start_offset;                                                            // (18) 0.01758
/*26  */     while (offset < end_offset) {                                                     // (14) 0.02344
/*30  */ #ifdef DEBUG_EXT                                                                      // (21) 0.01172
/*32  */         /* Sanity check */                                                            // (15) 0.02344
/*34  */         if (offset > s->cluster_size)                                                 // (11) 0.03516
/*36  */             printf("qcow2_read_extension: suspicious offset %lu\n", offset);          // (5) 0.06055
/*40  */         printf("attempting to read extended header in offset %lu\n", offset);         // (8) 0.04883
/*42  */ #endif                                                                                // (24) 0.003906
/*46  */         ret = bdrv_pread(bs->file, offset, &ext, sizeof(ext));                        // (6) 0.05469
/*48  */         if (ret < 0) {                                                                // (12) 0.02734
/*50  */             error_setg_errno(errp, -ret, "qcow2_read_extension: ERROR: "              // (2) 0.07422
/*52  */                              "pread fail from offset %" PRIu64, offset);              // (1) 0.08203
/*54  */             return 1;                                                                 // (13) 0.02734
/*56  */         }                                                                             // (19) 0.01562
/*58  */         be32_to_cpus(&ext.magic);                                                     // (9) 0.03711
/*60  */         be32_to_cpus(&ext.len);                                                       // 0.0
/*62  */         offset += sizeof(ext);                                                        // 0.0
/*64  */ #ifdef DEBUG_EXT                                                                      // 0.0
/*66  */         printf("ext.magic = 0x%x\n", ext.magic);                                      // 0.0
/*68  */ #endif                                                                                // 0.0
/*70  */         if (ext.len > end_offset - offset) {                                          // 0.0
/*72  */             error_setg(errp, "Header extension too large");                           // 0.0
/*74  */             return -EINVAL;                                                           // 0.0
/*76  */         }                                                                             // 0.0
/*80  */         switch (ext.magic) {                                                          // 0.0
/*82  */         case QCOW2_EXT_MAGIC_END:                                                     // 0.0
/*84  */             return 0;                                                                 // 0.0
/*88  */         case QCOW2_EXT_MAGIC_BACKING_FORMAT:                                          // 0.0
/*90  */             if (ext.len >= sizeof(bs->backing_format)) {                              // 0.0
/*92  */                 error_setg(errp, "ERROR: ext_backing_format: len=%" PRIu32            // 0.0
/*94  */                            " too large (>=%zu)", ext.len,                             // 0.0
/*96  */                            sizeof(bs->backing_format));                               // 0.0
/*98  */                 return 2;                                                             // 0.0
/*100 */             }                                                                         // 0.0
/*102 */             ret = bdrv_pread(bs->file, offset, bs->backing_format, ext.len);          // 0.0
/*104 */             if (ret < 0) {                                                            // 0.0
/*106 */                 error_setg_errno(errp, -ret, "ERROR: ext_backing_format: "            // 0.0
/*108 */                                  "Could not read format name");                       // 0.0
/*110 */                 return 3;                                                             // 0.0
/*112 */             }                                                                         // 0.0
/*114 */             bs->backing_format[ext.len] = '\0';                                       // 0.0
/*116 */ #ifdef DEBUG_EXT                                                                      // 0.0
/*118 */             printf("Qcow2: Got format extension %s\n", bs->backing_format);           // 0.0
/*120 */ #endif                                                                                // 0.0
/*122 */             break;                                                                    // 0.0
/*126 */         case QCOW2_EXT_MAGIC_FEATURE_TABLE:                                           // 0.0
/*128 */             if (p_feature_table != NULL) {                                            // 0.0
/*130 */                 void* feature_table = g_malloc0(ext.len + 2 * sizeof(Qcow2Feature));  // 0.0
/*132 */                 ret = bdrv_pread(bs->file, offset , feature_table, ext.len);          // 0.0
/*134 */                 if (ret < 0) {                                                        // 0.0
/*136 */                     error_setg_errno(errp, -ret, "ERROR: ext_feature_table: "         // 0.0
/*138 */                                      "Could not read table");                         // 0.0
/*140 */                     return ret;                                                       // 0.0
/*142 */                 }                                                                     // 0.0
/*146 */                 *p_feature_table = feature_table;                                     // 0.0
/*148 */             }                                                                         // 0.0
/*150 */             break;                                                                    // 0.0
/*154 */         default:                                                                      // 0.0
/*156 */             /* unknown magic - save it in case we need to rewrite the header */       // 0.0
/*158 */             {                                                                         // 0.0
/*160 */                 Qcow2UnknownHeaderExtension *uext;                                    // 0.0
/*164 */                 uext = g_malloc0(sizeof(*uext)  + ext.len);                           // 0.0
/*166 */                 uext->magic = ext.magic;                                              // 0.0
/*168 */                 uext->len = ext.len;                                                  // 0.0
/*170 */                 QLIST_INSERT_HEAD(&s->unknown_header_ext, uext, next);                // 0.0
/*174 */                 ret = bdrv_pread(bs->file, offset , uext->data, uext->len);           // 0.0
/*176 */                 if (ret < 0) {                                                        // 0.0
/*178 */                     error_setg_errno(errp, -ret, "ERROR: unknown extension: "         // 0.0
/*180 */                                      "Could not read data");                          // 0.0
/*182 */                     return ret;                                                       // 0.0
/*184 */                 }                                                                     // 0.0
/*186 */             }                                                                         // 0.0
/*188 */             break;                                                                    // 0.0
/*190 */         }                                                                             // 0.0
/*194 */         offset += ((ext.len + 7) & ~7);                                               // 0.0
/*196 */     }                                                                                 // 0.0
/*200 */     return 0;                                                                         // 0.0
/*202 */ }                                                                                     // 0.0
