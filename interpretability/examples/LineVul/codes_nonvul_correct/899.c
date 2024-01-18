// commit message qemu@0e7106d8b5 (target=0, prob=0.34401247, correct=True): sheepdog: implement direct write semantics
/*0   */ static int sd_snapshot_create(BlockDriverState *bs, QEMUSnapshotInfo *sn_info)    // (6) 0.05273
/*2   */ {                                                                                 // (23) 0.001955
/*4   */     BDRVSheepdogState *s = bs->opaque;                                            // (12) 0.03711
/*6   */     int ret, fd;                                                                  // (19) 0.01758
/*8   */     uint32_t new_vid;                                                             // (18) 0.02148
/*10  */     SheepdogInode *inode;                                                         // (17) 0.02148
/*12  */     unsigned int datalen;                                                         // (20) 0.01758
/*16  */     dprintf("sn_info: name %s id_str %s s: name %s vm_state_size %" PRId64 " "    // (1) 0.06836
/*18  */             "is_snapshot %d\n", sn_info->name, sn_info->id_str,                   // (2) 0.06836
/*20  */             s->name, sn_info->vm_state_size, s->is_snapshot);                     // (3) 0.0625
/*24  */     if (s->is_snapshot) {                                                         // (15) 0.02539
/*26  */         error_report("You can't create a snapshot of a snapshot VDI, "            // (9) 0.04687
/*28  */                      "%s (%" PRIu32 ").", s->name, s->inode.vdi_id);              // (0) 0.08789
/*32  */         return -EINVAL;                                                           // (16) 0.02539
/*34  */     }                                                                             // (22) 0.007812
/*38  */     dprintf("%s %s\n", sn_info->name, sn_info->id_str);                           // (7) 0.05273
/*42  */     s->inode.vm_state_size = sn_info->vm_state_size;                              // (10) 0.04687
/*44  */     s->inode.vm_clock_nsec = sn_info->vm_clock_nsec;                              // (8) 0.05078
/*46  */     /* It appears that inode.tag does not require a NUL terminator,               // (11) 0.03906
/*48  */      * which means this use of strncpy is ok.                                     // (13) 0.03125
/*50  */      */                                                                           // (21) 0.009766
/*52  */     strncpy(s->inode.tag, sn_info->name, sizeof(s->inode.tag));                   // (4) 0.05664
/*54  */     /* we don't need to update entire object */                                   // (14) 0.02539
/*56  */     datalen = SD_INODE_SIZE - sizeof(s->inode.data_vdi_id);                       // (5) 0.05469
/*60  */     /* refresh inode. */                                                          // 0.0
/*62  */     fd = connect_to_sdog(s->addr, s->port);                                       // 0.0
/*64  */     if (fd < 0) {                                                                 // 0.0
/*66  */         ret = fd;                                                                 // 0.0
/*68  */         goto cleanup;                                                             // 0.0
/*70  */     }                                                                             // 0.0
/*74  */     ret = write_object(fd, (char *)&s->inode, vid_to_vdi_oid(s->inode.vdi_id),    // 0.0
/*76  */                        s->inode.nr_copies, datalen, 0, false, s->cache_enabled);  // 0.0
/*78  */     if (ret < 0) {                                                                // 0.0
/*80  */         error_report("failed to write snapshot's inode.");                        // 0.0
/*82  */         goto cleanup;                                                             // 0.0
/*84  */     }                                                                             // 0.0
/*88  */     ret = do_sd_create(s->name, s->inode.vdi_size, s->inode.vdi_id, &new_vid, 1,  // 0.0
/*90  */                        s->addr, s->port);                                         // 0.0
/*92  */     if (ret < 0) {                                                                // 0.0
/*94  */         error_report("failed to create inode for snapshot. %s",                   // 0.0
/*96  */                      strerror(errno));                                            // 0.0
/*98  */         goto cleanup;                                                             // 0.0
/*100 */     }                                                                             // 0.0
/*104 */     inode = (SheepdogInode *)g_malloc(datalen);                                   // 0.0
/*108 */     ret = read_object(fd, (char *)inode, vid_to_vdi_oid(new_vid),                 // 0.0
/*110 */                       s->inode.nr_copies, datalen, 0, s->cache_enabled);          // 0.0
/*114 */     if (ret < 0) {                                                                // 0.0
/*116 */         error_report("failed to read new inode info. %s", strerror(errno));       // 0.0
/*118 */         goto cleanup;                                                             // 0.0
/*120 */     }                                                                             // 0.0
/*124 */     memcpy(&s->inode, inode, datalen);                                            // 0.0
/*126 */     dprintf("s->inode: name %s snap_id %x oid %x\n",                              // 0.0
/*128 */             s->inode.name, s->inode.snap_id, s->inode.vdi_id);                    // 0.0
/*132 */ cleanup:                                                                          // 0.0
/*134 */     closesocket(fd);                                                              // 0.0
/*136 */     return ret;                                                                   // 0.0
/*138 */ }                                                                                 // 0.0
