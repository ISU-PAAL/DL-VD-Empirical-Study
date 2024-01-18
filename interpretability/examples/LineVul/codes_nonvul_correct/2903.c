// commit message qemu@54421cb17b (target=0, prob=0.26730555, correct=True): Fix CDROM permission check, by Kazu <kazoo@r3.dion.ne.jp>.
/*0  */ static int hdev_open(BlockDriverState *bs, const char *filename, int flags)         // (7) 0.04102
/*2  */ {                                                                                   // (31) 0.001953
/*4  */     BDRVRawState *s = bs->opaque;                                                   // (9) 0.0332
/*6  */     int access_flags, create_flags;                                                 // (19) 0.02344
/*8  */     DWORD overlapped;                                                               // (22) 0.01563
/*10 */     char device_name[64];                                                           // (20) 0.01953
/*14 */     if (strstart(filename, "/dev/cdrom", NULL)) {                                   // (8) 0.03711
/*16 */         if (find_cdrom(device_name, sizeof(device_name)) < 0)                       // (4) 0.05273
/*18 */             return -ENOENT;                                                         // (12) 0.0332
/*20 */         filename = device_name;                                                     // (18) 0.02539
/*22 */     } else {                                                                        // (24) 0.01172
/*24 */         /* transform drive letters into device name */                              // (16) 0.0293
/*26 */         if (((filename[0] >= 'a' && filename[0] <= 'z') ||                          // (3) 0.05469
/*28 */              (filename[0] >= 'A' && filename[0] <= 'Z')) &&                         // (1) 0.0625
/*30 */             filename[1] == ':' && filename[2] == '\0') {                            // (2) 0.05664
/*32 */             snprintf(device_name, sizeof(device_name), "\\\\.\\%c:", filename[0]);  // (0) 0.07031
/*34 */             filename = device_name;                                                 // (13) 0.0332
/*36 */         }                                                                           // (23) 0.01562
/*38 */     }                                                                               // (27) 0.007812
/*40 */     s->type = find_device_type(bs, filename);                                       // (10) 0.0332
/*42 */                                                                                     // (28) 0.007812
/*44 */     if ((flags & BDRV_O_ACCESS) == O_RDWR) {                                        // (6) 0.04492
/*46 */         access_flags = GENERIC_READ | GENERIC_WRITE;                                // (5) 0.04687
/*48 */     } else {                                                                        // (25) 0.01172
/*50 */         access_flags = GENERIC_READ;                                                // (11) 0.0332
/*52 */     }                                                                               // (26) 0.007812
/*54 */     create_flags = OPEN_EXISTING;                                                   // (17) 0.02539
/*58 */ #ifdef QEMU_TOOL                                                                    // (21) 0.01758
/*60 */     overlapped = FILE_ATTRIBUTE_NORMAL;                                             // (14) 0.03125
/*62 */ #else                                                                               // (30) 0.003906
/*64 */     overlapped = FILE_FLAG_OVERLAPPED;                                              // (15) 0.0293
/*66 */ #endif                                                                              // (29) 0.003906
/*68 */     s->hfile = CreateFile(filename, access_flags,                                   // 0.0
/*70 */                           FILE_SHARE_READ, NULL,                                    // 0.0
/*72 */                           create_flags, overlapped, NULL);                          // 0.0
/*74 */     if (s->hfile == INVALID_HANDLE_VALUE)                                           // 0.0
/*76 */         return -1;                                                                  // 0.0
/*78 */     return 0;                                                                       // 0.0
/*80 */ }                                                                                   // 0.0
