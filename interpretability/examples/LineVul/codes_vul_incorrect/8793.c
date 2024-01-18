// commit message qemu@ff74f33c31 (target=1, prob=0.27212474, correct=False): vmdk: fix vmdk_parse_extents() extent_file leaks
/*0   */ static int vmdk_parse_extents(const char *desc, BlockDriverState *bs,                // (6) 0.04297
/*2   */                               const char *desc_file_path, Error **errp)              // (1) 0.08398
/*4   */ {                                                                                    // (26) 0.001953
/*6   */     int ret;                                                                         // (25) 0.01172
/*8   */     char access[11];                                                                 // (23) 0.01562
/*10  */     char type[11];                                                                   // (24) 0.01562
/*12  */     char fname[512];                                                                 // (20) 0.01758
/*14  */     const char *p = desc;                                                            // (18) 0.01953
/*16  */     int64_t sectors = 0;                                                             // (16) 0.02148
/*18  */     int64_t flat_offset;                                                             // (17) 0.02148
/*20  */     char extent_path[PATH_MAX];                                                      // (13) 0.02344
/*22  */     BlockDriverState *extent_file;                                                   // (12) 0.02344
/*24  */     BDRVVmdkState *s = bs->opaque;                                                   // (9) 0.03711
/*26  */     VmdkExtent *extent;                                                              // (15) 0.02344
/*30  */     while (*p) {                                                                     // (22) 0.01562
/*32  */         /* parse extent line:                                                        // (14) 0.02344
/*34  */          * RW [size in sectors] FLAT "file-name.vmdk" OFFSET                         // (3) 0.05664
/*36  */          * or                                                                        // (19) 0.01953
/*38  */          * RW [size in sectors] SPARSE "file-name.vmdk"                              // (4) 0.05273
/*40  */          */                                                                          // (21) 0.01758
/*42  */         flat_offset = -1;                                                            // (11) 0.02734
/*44  */         ret = sscanf(p, "%10s %" SCNd64 " %10s \"%511[^\n\r\"]\" %" SCNd64,          // (0) 0.0918
/*46  */                 access, &sectors, type, fname, &flat_offset);                        // (2) 0.06055
/*48  */         if (ret < 4 || strcmp(access, "RW")) {                                       // (7) 0.04297
/*50  */             goto next_line;                                                          // (10) 0.03125
/*52  */         } else if (!strcmp(type, "FLAT")) {                                          // (8) 0.04102
/*54  */             if (ret != 5 || flat_offset < 0) {                                       // (5) 0.04687
/*56  */                 error_setg(errp, "Invalid extent lines: \n%s", p);                   // 0.0
/*58  */                 return -EINVAL;                                                      // 0.0
/*60  */             }                                                                        // 0.0
/*62  */         } else if (!strcmp(type, "VMFS")) {                                          // 0.0
/*64  */             if (ret == 4) {                                                          // 0.0
/*66  */                 flat_offset = 0;                                                     // 0.0
/*68  */             } else {                                                                 // 0.0
/*70  */                 error_setg(errp, "Invalid extent lines:\n%s", p);                    // 0.0
/*72  */                 return -EINVAL;                                                      // 0.0
/*74  */             }                                                                        // 0.0
/*76  */         } else if (ret != 4) {                                                       // 0.0
/*78  */             error_setg(errp, "Invalid extent lines:\n%s", p);                        // 0.0
/*80  */             return -EINVAL;                                                          // 0.0
/*82  */         }                                                                            // 0.0
/*86  */         if (sectors <= 0 ||                                                          // 0.0
/*88  */             (strcmp(type, "FLAT") && strcmp(type, "SPARSE") &&                       // 0.0
/*90  */              strcmp(type, "VMFS") && strcmp(type, "VMFSSPARSE")) ||                  // 0.0
/*92  */             (strcmp(access, "RW"))) {                                                // 0.0
/*94  */             goto next_line;                                                          // 0.0
/*96  */         }                                                                            // 0.0
/*100 */         path_combine(extent_path, sizeof(extent_path),                               // 0.0
/*102 */                 desc_file_path, fname);                                              // 0.0
/*104 */         extent_file = NULL;                                                          // 0.0
/*106 */         ret = bdrv_open(&extent_file, extent_path, NULL, NULL,                       // 0.0
/*108 */                         bs->open_flags | BDRV_O_PROTOCOL, NULL, errp);               // 0.0
/*110 */         if (ret) {                                                                   // 0.0
/*112 */             return ret;                                                              // 0.0
/*114 */         }                                                                            // 0.0
/*118 */         /* save to extents array */                                                  // 0.0
/*120 */         if (!strcmp(type, "FLAT") || !strcmp(type, "VMFS")) {                        // 0.0
/*122 */             /* FLAT extent */                                                        // 0.0
/*126 */             ret = vmdk_add_extent(bs, extent_file, true, sectors,                    // 0.0
/*128 */                             0, 0, 0, 0, 0, &extent, errp);                           // 0.0
/*130 */             if (ret < 0) {                                                           // 0.0
/*133 */                 return ret;                                                          // 0.0
/*135 */             }                                                                        // 0.0
/*137 */             extent->flat_start_offset = flat_offset << 9;                            // 0.0
/*139 */         } else if (!strcmp(type, "SPARSE") || !strcmp(type, "VMFSSPARSE")) {         // 0.0
/*141 */             /* SPARSE extent and VMFSSPARSE extent are both "COWD" sparse file*/     // 0.0
/*143 */             char *buf = vmdk_read_desc(extent_file, 0, errp);                        // 0.0
/*145 */             if (!buf) {                                                              // 0.0
/*147 */                 ret = -EINVAL;                                                       // 0.0
/*149 */             } else {                                                                 // 0.0
/*151 */                 ret = vmdk_open_sparse(bs, extent_file, bs->open_flags, buf, errp);  // 0.0
/*153 */             }                                                                        // 0.0
/*155 */             if (ret) {                                                               // 0.0
/*157 */                 g_free(buf);                                                         // 0.0
/*160 */                 return ret;                                                          // 0.0
/*162 */             }                                                                        // 0.0
/*164 */             extent = &s->extents[s->num_extents - 1];                                // 0.0
/*166 */         } else {                                                                     // 0.0
/*168 */             error_setg(errp, "Unsupported extent type '%s'", type);                  // 0.0
/*171 */             return -ENOTSUP;                                                         // 0.0
/*173 */         }                                                                            // 0.0
/*175 */         extent->type = g_strdup(type);                                               // 0.0
/*177 */ next_line:                                                                           // 0.0
/*179 */         /* move to next line */                                                      // 0.0
/*181 */         while (*p) {                                                                 // 0.0
/*183 */             if (*p == '\n') {                                                        // 0.0
/*185 */                 p++;                                                                 // 0.0
/*187 */                 break;                                                               // 0.0
/*189 */             }                                                                        // 0.0
/*191 */             p++;                                                                     // 0.0
/*193 */         }                                                                            // 0.0
/*195 */     }                                                                                // 0.0
/*197 */     return 0;                                                                        // 0.0
/*199 */ }                                                                                    // 0.0
