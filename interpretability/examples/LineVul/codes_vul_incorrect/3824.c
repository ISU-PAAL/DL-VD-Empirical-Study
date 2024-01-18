// commit message qemu@6764579f89 (target=1, prob=0.24306573, correct=False): block/cow: Avoid use of uninitialized cow_bs in error path
/*0   */ static int cow_create(const char *filename, QemuOpts *opts, Error **errp)  // (3) 0.04883
/*2   */ {                                                                          // (29) 0.001953
/*4   */     struct cow_header_v2 cow_header;                                       // (13) 0.02734
/*6   */     struct stat st;                                                        // (25) 0.01367
/*8   */     int64_t image_sectors = 0;                                             // (14) 0.02734
/*10  */     char *image_filename = NULL;                                           // (16) 0.02148
/*12  */     Error *local_err = NULL;                                               // (17) 0.02148
/*14  */     int ret;                                                               // (26) 0.01172
/*16  */     BlockDriverState *cow_bs;                                              // (15) 0.02148
/*20  */     /* Read out options */                                                 // (24) 0.01563
/*22  */     image_sectors = qemu_opt_get_size_del(opts, BLOCK_OPT_SIZE, 0) / 512;  // (1) 0.07031
/*24  */     image_filename = qemu_opt_get_del(opts, BLOCK_OPT_BACKING_FILE);       // (2) 0.06055
/*28  */     ret = bdrv_create_file(filename, opts, &local_err);                    // (4) 0.04492
/*30  */     if (ret < 0) {                                                         // (21) 0.01953
/*32  */         error_propagate(errp, local_err);                                  // (10) 0.03711
/*34  */         goto exit;                                                         // (18) 0.01953
/*36  */     }                                                                      // (27) 0.007812
/*40  */     cow_bs = NULL;                                                         // (23) 0.01758
/*42  */     ret = bdrv_open(&cow_bs, filename, NULL, NULL,                         // (7) 0.04102
/*44  */                     BDRV_O_RDWR | BDRV_O_PROTOCOL, NULL, &local_err);      // (0) 0.08984
/*46  */     if (ret < 0) {                                                         // (22) 0.01953
/*48  */         error_propagate(errp, local_err);                                  // (11) 0.03711
/*50  */         goto exit;                                                         // (19) 0.01953
/*52  */     }                                                                      // (28) 0.007812
/*56  */     memset(&cow_header, 0, sizeof(cow_header));                            // (12) 0.03516
/*58  */     cow_header.magic = cpu_to_be32(COW_MAGIC);                             // (6) 0.04297
/*60  */     cow_header.version = cpu_to_be32(COW_VERSION);                         // (9) 0.04102
/*62  */     if (image_filename) {                                                  // (20) 0.01953
/*64  */         /* Note: if no file, we put a dummy mtime */                       // (8) 0.04102
/*66  */         cow_header.mtime = cpu_to_be32(0);                                 // (5) 0.04492
/*70  */         if (stat(image_filename, &st) != 0) {                              // 0.0
/*72  */             goto mtime_fail;                                               // 0.0
/*74  */         }                                                                  // 0.0
/*76  */         cow_header.mtime = cpu_to_be32(st.st_mtime);                       // 0.0
/*78  */     mtime_fail:                                                            // 0.0
/*80  */         pstrcpy(cow_header.backing_file, sizeof(cow_header.backing_file),  // 0.0
/*82  */                 image_filename);                                           // 0.0
/*84  */     }                                                                      // 0.0
/*86  */     cow_header.sectorsize = cpu_to_be32(512);                              // 0.0
/*88  */     cow_header.size = cpu_to_be64(image_sectors * 512);                    // 0.0
/*90  */     ret = bdrv_pwrite(cow_bs, 0, &cow_header, sizeof(cow_header));         // 0.0
/*92  */     if (ret < 0) {                                                         // 0.0
/*94  */         goto exit;                                                         // 0.0
/*96  */     }                                                                      // 0.0
/*100 */     /* resize to include at least all the bitmap */                        // 0.0
/*102 */     ret = bdrv_truncate(cow_bs,                                            // 0.0
/*104 */         sizeof(cow_header) + ((image_sectors + 7) >> 3));                  // 0.0
/*106 */     if (ret < 0) {                                                         // 0.0
/*108 */         goto exit;                                                         // 0.0
/*110 */     }                                                                      // 0.0
/*114 */ exit:                                                                      // 0.0
/*116 */     g_free(image_filename);                                                // 0.0
/*118 */     bdrv_unref(cow_bs);                                                    // 0.0
/*120 */     return ret;                                                            // 0.0
/*122 */ }                                                                          // 0.0
