// commit message qemu@129c7d1c53 (target=1, prob=0.36757156, correct=False): block: Document -drive problematic code and bugs
/*0   */ static int hdev_open(BlockDriverState *bs, QDict *options, int flags,            // (5) 0.04297
/*2   */                      Error **errp)                                               // (3) 0.04883
/*4   */ {                                                                                // (25) 0.001953
/*6   */     BDRVRawState *s = bs->opaque;                                                // (14) 0.0332
/*8   */     Error *local_err = NULL;                                                     // (20) 0.02148
/*10  */     int ret;                                                                     // (24) 0.01172
/*14  */ #if defined(__APPLE__) && defined(__MACH__)                                      // (15) 0.0332
/*22  */     const char *filename = qdict_get_str(options, "filename");                   // (9) 0.03906
/*24  */     char bsd_path[MAXPATHLEN] = "";                                              // (11) 0.03516
/*26  */     bool error_occurred = false;                                                 // (22) 0.02148
/*30  */     /* If using a real cdrom */                                                  // (21) 0.02148
/*32  */     if (strcmp(filename, "/dev/cdrom") == 0) {                                   // (10) 0.03906
/*34  */         char *mediaType = NULL;                                                  // (19) 0.02734
/*36  */         kern_return_t ret_val;                                                   // (17) 0.0332
/*38  */         io_iterator_t mediaIterator = 0;                                         // (16) 0.0332
/*42  */         mediaType = FindEjectableOpticalMedia(&mediaIterator);                   // (7) 0.04102
/*44  */         if (mediaType == NULL) {                                                 // (18) 0.0293
/*46  */             error_setg(errp, "Please make sure your CD/DVD is in the optical"    // (1) 0.0625
/*48  */                        " drive");                                                // (4) 0.04883
/*50  */             error_occurred = true;                                               // (12) 0.03516
/*52  */             goto hdev_open_Mac_error;                                            // (6) 0.04102
/*54  */         }                                                                        // (23) 0.01562
/*58  */         ret_val = GetBSDPath(mediaIterator, bsd_path, sizeof(bsd_path), flags);  // (0) 0.06445
/*60  */         if (ret_val != KERN_SUCCESS) {                                           // (8) 0.04102
/*62  */             error_setg(errp, "Could not get BSD path for optical drive");        // (2) 0.05859
/*64  */             error_occurred = true;                                               // (13) 0.03516
/*66  */             goto hdev_open_Mac_error;                                            // 0.0
/*68  */         }                                                                        // 0.0
/*72  */         /* If a real optical drive was not found */                              // 0.0
/*74  */         if (bsd_path[0] == '\0') {                                               // 0.0
/*76  */             error_setg(errp, "Failed to obtain bsd path for optical drive");     // 0.0
/*78  */             error_occurred = true;                                               // 0.0
/*80  */             goto hdev_open_Mac_error;                                            // 0.0
/*82  */         }                                                                        // 0.0
/*86  */         /* If using a cdrom disc and finding a partition on the disc failed */   // 0.0
/*88  */         if (strncmp(mediaType, kIOCDMediaClass, 9) == 0 &&                       // 0.0
/*90  */             setup_cdrom(bsd_path, errp) == false) {                              // 0.0
/*92  */             print_unmounting_directions(bsd_path);                               // 0.0
/*94  */             error_occurred = true;                                               // 0.0
/*96  */             goto hdev_open_Mac_error;                                            // 0.0
/*98  */         }                                                                        // 0.0
/*102 */         qdict_put(options, "filename", qstring_from_str(bsd_path));              // 0.0
/*106 */ hdev_open_Mac_error:                                                             // 0.0
/*108 */         g_free(mediaType);                                                       // 0.0
/*110 */         if (mediaIterator) {                                                     // 0.0
/*112 */             IOObjectRelease(mediaIterator);                                      // 0.0
/*114 */         }                                                                        // 0.0
/*116 */         if (error_occurred) {                                                    // 0.0
/*118 */             return -ENOENT;                                                      // 0.0
/*120 */         }                                                                        // 0.0
/*122 */     }                                                                            // 0.0
/*124 */ #endif /* defined(__APPLE__) && defined(__MACH__) */                             // 0.0
/*128 */     s->type = FTYPE_FILE;                                                        // 0.0
/*132 */     ret = raw_open_common(bs, options, flags, 0, &local_err);                    // 0.0
/*134 */     if (ret < 0) {                                                               // 0.0
/*136 */         error_propagate(errp, local_err);                                        // 0.0
/*138 */ #if defined(__APPLE__) && defined(__MACH__)                                      // 0.0
/*140 */         if (*bsd_path) {                                                         // 0.0
/*142 */             filename = bsd_path;                                                 // 0.0
/*144 */         }                                                                        // 0.0
/*146 */         /* if a physical device experienced an error while being opened */       // 0.0
/*148 */         if (strncmp(filename, "/dev/", 5) == 0) {                                // 0.0
/*150 */             print_unmounting_directions(filename);                               // 0.0
/*152 */         }                                                                        // 0.0
/*154 */ #endif /* defined(__APPLE__) && defined(__MACH__) */                             // 0.0
/*156 */         return ret;                                                              // 0.0
/*158 */     }                                                                            // 0.0
/*162 */     /* Since this does ioctl the device must be already opened */                // 0.0
/*164 */     bs->sg = hdev_is_sg(bs);                                                     // 0.0
/*168 */     if (flags & BDRV_O_RDWR) {                                                   // 0.0
/*170 */         ret = check_hdev_writable(s);                                            // 0.0
/*172 */         if (ret < 0) {                                                           // 0.0
/*174 */             raw_close(bs);                                                       // 0.0
/*176 */             error_setg_errno(errp, -ret, "The device is not writable");          // 0.0
/*178 */             return ret;                                                          // 0.0
/*180 */         }                                                                        // 0.0
/*182 */     }                                                                            // 0.0
/*186 */     return ret;                                                                  // 0.0
/*188 */ }                                                                                // 0.0
