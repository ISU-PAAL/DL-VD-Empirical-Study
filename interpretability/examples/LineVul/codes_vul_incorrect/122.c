// commit message qemu@301c7d38a0 (target=1, prob=0.24815574, correct=False): vmdk: fix cluster size check for flat extents
/*0   */ static int vmdk_parse_extents(const char *desc, BlockDriverState *bs,             // (5) 0.04297
/*2   */         const char *desc_file_path)                                               // (10) 0.03125
/*4   */ {                                                                                 // (29) 0.001953
/*6   */     int ret;                                                                      // (28) 0.01172
/*8   */     char access[11];                                                              // (26) 0.01562
/*10  */     char type[11];                                                                // (27) 0.01562
/*12  */     char fname[512];                                                              // (23) 0.01758
/*14  */     const char *p = desc;                                                         // (21) 0.01953
/*16  */     int64_t sectors = 0;                                                          // (20) 0.02148
/*18  */     int64_t flat_offset;                                                          // (19) 0.02148
/*20  */     char extent_path[PATH_MAX];                                                   // (14) 0.02344
/*22  */     BlockDriverState *extent_file;                                                // (15) 0.02344
/*24  */     Error *local_err = NULL;                                                      // (18) 0.02148
/*28  */     while (*p) {                                                                  // (25) 0.01563
/*30  */         /* parse extent line:                                                     // (16) 0.02344
/*32  */          * RW [size in sectors] FLAT "file-name.vmdk" OFFSET                      // (2) 0.05664
/*34  */          * or                                                                     // (22) 0.01953
/*36  */          * RW [size in sectors] SPARSE "file-name.vmdk"                           // (3) 0.05273
/*38  */          */                                                                       // (24) 0.01758
/*40  */         flat_offset = -1;                                                         // (13) 0.02734
/*42  */         ret = sscanf(p, "%10s %" SCNd64 " %10s \"%511[^\n\r\"]\" %" SCNd64,       // (0) 0.0918
/*44  */                 access, &sectors, type, fname, &flat_offset);                     // (1) 0.06055
/*46  */         if (ret < 4 || strcmp(access, "RW")) {                                    // (6) 0.04297
/*48  */             goto next_line;                                                       // (11) 0.03125
/*50  */         } else if (!strcmp(type, "FLAT")) {                                       // (7) 0.04102
/*52  */             if (ret != 5 || flat_offset < 0) {                                    // (4) 0.04687
/*54  */                 return -EINVAL;                                                   // (8) 0.04102
/*56  */             }                                                                     // (17) 0.02344
/*58  */         } else if (ret != 4) {                                                    // (12) 0.03125
/*60  */             return -EINVAL;                                                       // (9) 0.0332
/*62  */         }                                                                         // 0.0
/*66  */         if (sectors <= 0 ||                                                       // 0.0
/*68  */             (strcmp(type, "FLAT") && strcmp(type, "SPARSE") &&                    // 0.0
/*70  */              strcmp(type, "VMFS") && strcmp(type, "VMFSSPARSE")) ||               // 0.0
/*72  */             (strcmp(access, "RW"))) {                                             // 0.0
/*74  */             goto next_line;                                                       // 0.0
/*76  */         }                                                                         // 0.0
/*80  */         path_combine(extent_path, sizeof(extent_path),                            // 0.0
/*82  */                 desc_file_path, fname);                                           // 0.0
/*84  */         ret = bdrv_file_open(&extent_file, extent_path, NULL, bs->open_flags,     // 0.0
/*86  */                              &local_err);                                         // 0.0
/*88  */         if (ret) {                                                                // 0.0
/*90  */             qerror_report_err(local_err);                                         // 0.0
/*92  */             error_free(local_err);                                                // 0.0
/*94  */             return ret;                                                           // 0.0
/*96  */         }                                                                         // 0.0
/*100 */         /* save to extents array */                                               // 0.0
/*102 */         if (!strcmp(type, "FLAT") || !strcmp(type, "VMFS")) {                     // 0.0
/*104 */             /* FLAT extent */                                                     // 0.0
/*106 */             VmdkExtent *extent;                                                   // 0.0
/*110 */             ret = vmdk_add_extent(bs, extent_file, true, sectors,                 // 0.0
/*112 */                             0, 0, 0, 0, sectors, &extent);                        // 0.0
/*114 */             if (ret < 0) {                                                        // 0.0
/*116 */                 return ret;                                                       // 0.0
/*118 */             }                                                                     // 0.0
/*120 */             extent->flat_start_offset = flat_offset << 9;                         // 0.0
/*122 */         } else if (!strcmp(type, "SPARSE") || !strcmp(type, "VMFSSPARSE")) {      // 0.0
/*124 */             /* SPARSE extent and VMFSSPARSE extent are both "COWD" sparse file*/  // 0.0
/*126 */             ret = vmdk_open_sparse(bs, extent_file, bs->open_flags);              // 0.0
/*128 */             if (ret) {                                                            // 0.0
/*130 */                 bdrv_unref(extent_file);                                          // 0.0
/*132 */                 return ret;                                                       // 0.0
/*134 */             }                                                                     // 0.0
/*136 */         } else {                                                                  // 0.0
/*138 */             fprintf(stderr,                                                       // 0.0
/*140 */                 "VMDK: Not supported extent type \"%s\""".\n", type);             // 0.0
/*142 */             return -ENOTSUP;                                                      // 0.0
/*144 */         }                                                                         // 0.0
/*146 */ next_line:                                                                        // 0.0
/*148 */         /* move to next line */                                                   // 0.0
/*150 */         while (*p && *p != '\n') {                                                // 0.0
/*152 */             p++;                                                                  // 0.0
/*154 */         }                                                                         // 0.0
/*156 */         p++;                                                                      // 0.0
/*158 */     }                                                                             // 0.0
/*160 */     return 0;                                                                     // 0.0
/*162 */ }                                                                                 // 0.0
