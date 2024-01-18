// commit message qemu@0e7106d8b5 (target=0, prob=0.49324667, correct=True): sheepdog: implement direct write semantics
/*0  */ static int sd_truncate(BlockDriverState *bs, int64_t offset)                      // (4) 0.04662
/*2  */ {                                                                                 // (25) 0.002331
/*4  */     BDRVSheepdogState *s = bs->opaque;                                            // (5) 0.04429
/*6  */     int ret, fd;                                                                  // (19) 0.02098
/*8  */     unsigned int datalen;                                                         // (18) 0.02098
/*12 */     if (offset < s->inode.vdi_size) {                                             // (8) 0.04196
/*14 */         error_report("shrinking is not supported");                               // (9) 0.03963
/*16 */         return -EINVAL;                                                           // (13) 0.0303
/*18 */     } else if (offset > SD_MAX_VDI_SIZE) {                                        // (6) 0.04429
/*20 */         error_report("too big image size");                                       // (10) 0.0373
/*22 */         return -EINVAL;                                                           // (12) 0.0303
/*24 */     }                                                                             // (22) 0.009324
/*28 */     fd = connect_to_sdog(s->addr, s->port);                                       // (3) 0.04895
/*30 */     if (fd < 0) {                                                                 // (16) 0.02331
/*32 */         return fd;                                                                // (15) 0.02564
/*34 */     }                                                                             // (23) 0.009324
/*38 */     /* we don't need to update entire object */                                   // (14) 0.0303
/*40 */     datalen = SD_INODE_SIZE - sizeof(s->inode.data_vdi_id);                       // (2) 0.06527
/*42 */     s->inode.vdi_size = offset;                                                   // (11) 0.03497
/*44 */     ret = write_object(fd, (char *)&s->inode, vid_to_vdi_oid(s->inode.vdi_id),    // (1) 0.09324
/*46 */                        s->inode.nr_copies, datalen, 0, false, s->cache_enabled);  // (0) 0.1072
/*48 */     close(fd);                                                                    // (20) 0.01632
/*52 */     if (ret < 0) {                                                                // (17) 0.02331
/*54 */         error_report("failed to update an inode.");                               // (7) 0.04429
/*56 */     }                                                                             // (24) 0.009324
/*60 */     return ret;                                                                   // (21) 0.01399
/*62 */ }                                                                                 // (26) 0.002331
