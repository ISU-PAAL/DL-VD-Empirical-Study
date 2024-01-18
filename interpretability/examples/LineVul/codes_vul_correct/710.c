// commit message qemu@b6c147622d (target=1, prob=0.5762365, correct=True): qcow2: don't leak buffer for unexpected qcow_version in header
/*0   */ int qcow2_update_header(BlockDriverState *bs)                                   // (11) 0.0293
/*2   */ {                                                                               // (27) 0.001953
/*4   */     BDRVQcowState *s = bs->opaque;                                              // (8) 0.03516
/*6   */     QCowHeader *header;                                                         // (22) 0.01758
/*8   */     char *buf;                                                                  // (24) 0.01367
/*10  */     size_t buflen = s->cluster_size;                                            // (10) 0.0332
/*12  */     int ret;                                                                    // (25) 0.01172
/*14  */     uint64_t total_size;                                                        // (19) 0.02148
/*16  */     uint32_t refcount_table_clusters;                                           // (12) 0.0293
/*18  */     size_t header_length;                                                       // (21) 0.01953
/*20  */     Qcow2UnknownHeaderExtension *uext;                                          // (13) 0.02734
/*24  */     buf = qemu_blockalign(bs, buflen);                                          // (9) 0.03516
/*28  */     /* Header structure */                                                      // (23) 0.01367
/*30  */     header = (QCowHeader*) buf;                                                 // (16) 0.02344
/*34  */     if (buflen < sizeof(*header)) {                                             // (14) 0.02734
/*36  */         ret = -ENOSPC;                                                          // (15) 0.02734
/*38  */         goto fail;                                                              // (20) 0.01953
/*40  */     }                                                                           // (26) 0.007812
/*44  */     header_length = sizeof(*header) + s->unknown_header_fields_size;            // (5) 0.04297
/*46  */     total_size = bs->total_sectors * BDRV_SECTOR_SIZE;                          // (4) 0.04883
/*48  */     refcount_table_clusters = s->refcount_table_size >> (s->cluster_bits - 3);  // (3) 0.05859
/*52  */     *header = (QCowHeader) {                                                    // (17) 0.02344
/*54  */         /* Version 2 fields */                                                  // (18) 0.02344
/*56  */         .magic                  = cpu_to_be32(QCOW_MAGIC),                      // (0) 0.08008
/*58  */         .version                = cpu_to_be32(s->qcow_version),                 // (1) 0.07617
/*60  */         .backing_file_offset    = 0,                                            // (7) 0.03906
/*62  */         .backing_file_size      = 0,                                            // (6) 0.04297
/*64  */         .cluster_bits           = cpu_to_be32(s->cluster_bits),                 // (2) 0.07227
/*66  */         .size                   = cpu_to_be64(total_size),                      // 0.0
/*68  */         .crypt_method           = cpu_to_be32(s->crypt_method_header),          // 0.0
/*70  */         .l1_size                = cpu_to_be32(s->l1_size),                      // 0.0
/*72  */         .l1_table_offset        = cpu_to_be64(s->l1_table_offset),              // 0.0
/*74  */         .refcount_table_offset  = cpu_to_be64(s->refcount_table_offset),        // 0.0
/*76  */         .refcount_table_clusters = cpu_to_be32(refcount_table_clusters),        // 0.0
/*78  */         .nb_snapshots           = cpu_to_be32(s->nb_snapshots),                 // 0.0
/*80  */         .snapshots_offset       = cpu_to_be64(s->snapshots_offset),             // 0.0
/*84  */         /* Version 3 fields */                                                  // 0.0
/*86  */         .incompatible_features  = cpu_to_be64(s->incompatible_features),        // 0.0
/*88  */         .compatible_features    = cpu_to_be64(s->compatible_features),          // 0.0
/*90  */         .autoclear_features     = cpu_to_be64(s->autoclear_features),           // 0.0
/*92  */         .refcount_order         = cpu_to_be32(3 + REFCOUNT_SHIFT),              // 0.0
/*94  */         .header_length          = cpu_to_be32(header_length),                   // 0.0
/*96  */     };                                                                          // 0.0
/*100 */     /* For older versions, write a shorter header */                            // 0.0
/*102 */     switch (s->qcow_version) {                                                  // 0.0
/*104 */     case 2:                                                                     // 0.0
/*106 */         ret = offsetof(QCowHeader, incompatible_features);                      // 0.0
/*108 */         break;                                                                  // 0.0
/*110 */     case 3:                                                                     // 0.0
/*112 */         ret = sizeof(*header);                                                  // 0.0
/*114 */         break;                                                                  // 0.0
/*116 */     default:                                                                    // 0.0
/*118 */         return -EINVAL;                                                         // 0.0
/*120 */     }                                                                           // 0.0
/*124 */     buf += ret;                                                                 // 0.0
/*126 */     buflen -= ret;                                                              // 0.0
/*128 */     memset(buf, 0, buflen);                                                     // 0.0
/*132 */     /* Preserve any unknown field in the header */                              // 0.0
/*134 */     if (s->unknown_header_fields_size) {                                        // 0.0
/*136 */         if (buflen < s->unknown_header_fields_size) {                           // 0.0
/*138 */             ret = -ENOSPC;                                                      // 0.0
/*140 */             goto fail;                                                          // 0.0
/*142 */         }                                                                       // 0.0
/*146 */         memcpy(buf, s->unknown_header_fields, s->unknown_header_fields_size);   // 0.0
/*148 */         buf += s->unknown_header_fields_size;                                   // 0.0
/*150 */         buflen -= s->unknown_header_fields_size;                                // 0.0
/*152 */     }                                                                           // 0.0
/*156 */     /* Backing file format header extension */                                  // 0.0
/*158 */     if (*bs->backing_format) {                                                  // 0.0
/*160 */         ret = header_ext_add(buf, QCOW2_EXT_MAGIC_BACKING_FORMAT,               // 0.0
/*162 */                              bs->backing_format, strlen(bs->backing_format),    // 0.0
/*164 */                              buflen);                                           // 0.0
/*166 */         if (ret < 0) {                                                          // 0.0
/*168 */             goto fail;                                                          // 0.0
/*170 */         }                                                                       // 0.0
/*174 */         buf += ret;                                                             // 0.0
/*176 */         buflen -= ret;                                                          // 0.0
/*178 */     }                                                                           // 0.0
/*182 */     /* Feature table */                                                         // 0.0
/*184 */     Qcow2Feature features[] = {                                                 // 0.0
/*186 */         /* no feature defined yet */                                            // 0.0
/*188 */     };                                                                          // 0.0
/*192 */     ret = header_ext_add(buf, QCOW2_EXT_MAGIC_FEATURE_TABLE,                    // 0.0
/*194 */                          features, sizeof(features), buflen);                   // 0.0
/*196 */     if (ret < 0) {                                                              // 0.0
/*198 */         goto fail;                                                              // 0.0
/*200 */     }                                                                           // 0.0
/*202 */     buf += ret;                                                                 // 0.0
/*204 */     buflen -= ret;                                                              // 0.0
/*208 */     /* Keep unknown header extensions */                                        // 0.0
/*210 */     QLIST_FOREACH(uext, &s->unknown_header_ext, next) {                         // 0.0
/*212 */         ret = header_ext_add(buf, uext->magic, uext->data, uext->len, buflen);  // 0.0
/*214 */         if (ret < 0) {                                                          // 0.0
/*216 */             goto fail;                                                          // 0.0
/*218 */         }                                                                       // 0.0
/*222 */         buf += ret;                                                             // 0.0
/*224 */         buflen -= ret;                                                          // 0.0
/*226 */     }                                                                           // 0.0
/*230 */     /* End of header extensions */                                              // 0.0
/*232 */     ret = header_ext_add(buf, QCOW2_EXT_MAGIC_END, NULL, 0, buflen);            // 0.0
/*234 */     if (ret < 0) {                                                              // 0.0
/*236 */         goto fail;                                                              // 0.0
/*238 */     }                                                                           // 0.0
/*242 */     buf += ret;                                                                 // 0.0
/*244 */     buflen -= ret;                                                              // 0.0
/*248 */     /* Backing file name */                                                     // 0.0
/*250 */     if (*bs->backing_file) {                                                    // 0.0
/*252 */         size_t backing_file_len = strlen(bs->backing_file);                     // 0.0
/*256 */         if (buflen < backing_file_len) {                                        // 0.0
/*258 */             ret = -ENOSPC;                                                      // 0.0
/*260 */             goto fail;                                                          // 0.0
/*262 */         }                                                                       // 0.0
/*266 */         strncpy(buf, bs->backing_file, buflen);                                 // 0.0
/*270 */         header->backing_file_offset = cpu_to_be64(buf - ((char*) header));      // 0.0
/*272 */         header->backing_file_size   = cpu_to_be32(backing_file_len);            // 0.0
/*274 */     }                                                                           // 0.0
/*278 */     /* Write the new header */                                                  // 0.0
/*280 */     ret = bdrv_pwrite(bs->file, 0, header, s->cluster_size);                    // 0.0
/*282 */     if (ret < 0) {                                                              // 0.0
/*284 */         goto fail;                                                              // 0.0
/*286 */     }                                                                           // 0.0
/*290 */     ret = 0;                                                                    // 0.0
/*292 */ fail:                                                                           // 0.0
/*294 */     qemu_vfree(header);                                                         // 0.0
/*296 */     return ret;                                                                 // 0.0
/*298 */ }                                                                               // 0.0
