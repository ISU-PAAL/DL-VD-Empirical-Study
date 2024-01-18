// commit message qemu@0e7106d8b5 (target=0, prob=0.5716932, correct=False): sheepdog: implement direct write semantics
/*0  */ static int sd_create_branch(BDRVSheepdogState *s)                             // (9) 0.03711
/*2  */ {                                                                             // (31) 0.001953
/*4  */     int ret, fd;                                                              // (20) 0.01758
/*6  */     uint32_t vid;                                                             // (14) 0.01953
/*8  */     char *buf;                                                                // (24) 0.01367
/*12 */     dprintf("%" PRIx32 " is snapshot.\n", s->inode.vdi_id);                   // (5) 0.05469
/*16 */     buf = g_malloc(SD_INODE_SIZE);                                            // (10) 0.0332
/*20 */     ret = do_sd_create(s->name, s->inode.vdi_size, s->inode.vdi_id, &vid, 1,  // (0) 0.07812
/*22 */                        s->addr, s->port);                                     // (3) 0.05859
/*24 */     if (ret) {                                                                // (22) 0.01562
/*26 */         goto out;                                                             // (15) 0.01953
/*28 */     }                                                                         // (27) 0.007812
/*32 */     dprintf("%" PRIx32 " is created.\n", vid);                                // (6) 0.04102
/*36 */     fd = connect_to_sdog(s->addr, s->port);                                   // (7) 0.04102
/*38 */     if (fd < 0) {                                                             // (16) 0.01953
/*40 */         error_report("failed to connect");                                    // (11) 0.0293
/*42 */         ret = fd;                                                             // (12) 0.02344
/*44 */         goto out;                                                             // (17) 0.01953
/*46 */     }                                                                         // (28) 0.007812
/*50 */     ret = read_object(fd, buf, vid_to_vdi_oid(vid), s->inode.nr_copies,       // (2) 0.06836
/*52 */                       SD_INODE_SIZE, 0, s->cache_enabled);                    // (1) 0.07031
/*56 */     closesocket(fd);                                                          // (23) 0.01562
/*60 */     if (ret < 0) {                                                            // (18) 0.01953
/*62 */         goto out;                                                             // (19) 0.01953
/*64 */     }                                                                         // (29) 0.007812
/*68 */     memcpy(&s->inode, buf, sizeof(s->inode));                                 // (8) 0.04102
/*72 */     s->is_snapshot = false;                                                   // (13) 0.02344
/*74 */     ret = 0;                                                                  // (25) 0.01367
/*76 */     dprintf("%" PRIx32 " was newly created.\n", s->inode.vdi_id);             // (4) 0.05664
/*80 */ out:                                                                          // (30) 0.003906
/*82 */     g_free(buf);                                                              // (21) 0.01758
/*86 */     return ret;                                                               // (26) 0.01172
/*88 */ }                                                                             // 0.0
