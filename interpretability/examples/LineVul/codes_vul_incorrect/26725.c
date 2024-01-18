// commit message qemu@e25cad6921 (target=1, prob=0.3827593, correct=False): sheepdog: Fix error handling in sd_snapshot_delete()
/*0   */ static int sd_snapshot_delete(BlockDriverState *bs,                     // (13) 0.0293
/*2   */                               const char *snapshot_id,                  // (0) 0.07227
/*4   */                               const char *name,                         // (3) 0.06641
/*6   */                               Error **errp)                             // (2) 0.06641
/*8   */ {                                                                       // (25) 0.001954
/*10  */     unsigned long snap_id = 0;                                          // (19) 0.02148
/*12  */     char snap_tag[SD_MAX_VDI_TAG_LEN];                                  // (10) 0.03906
/*14  */     Error *local_err = NULL;                                            // (18) 0.02148
/*16  */     int fd, ret;                                                        // (22) 0.01758
/*18  */     char buf[SD_MAX_VDI_LEN + SD_MAX_VDI_TAG_LEN];                      // (4) 0.05469
/*20  */     BDRVSheepdogState *s = bs->opaque;                                  // (11) 0.03711
/*22  */     unsigned int wlen = SD_MAX_VDI_LEN + SD_MAX_VDI_TAG_LEN, rlen = 0;  // (1) 0.06836
/*24  */     uint32_t vid;                                                       // (21) 0.01953
/*26  */     SheepdogVdiReq hdr = {                                              // (16) 0.02539
/*28  */         .opcode = SD_OP_DEL_VDI,                                        // (8) 0.04102
/*30  */         .data_length = wlen,                                            // (14) 0.0293
/*32  */         .flags = SD_FLAG_CMD_WRITE,                                     // (9) 0.03906
/*34  */     };                                                                  // (23) 0.007812
/*36  */     SheepdogVdiRsp *rsp = (SheepdogVdiRsp *)&hdr;                       // (6) 0.05078
/*40  */     if (!remove_objects(s)) {                                           // (17) 0.02344
/*42  */         return -1;                                                      // (20) 0.02148
/*44  */     }                                                                   // (24) 0.007812
/*48  */     memset(buf, 0, sizeof(buf));                                        // (15) 0.02734
/*50  */     memset(snap_tag, 0, sizeof(snap_tag));                              // (12) 0.03516
/*52  */     pstrcpy(buf, SD_MAX_VDI_LEN, s->name);                              // (7) 0.04687
/*54  */     ret = qemu_strtoul(snapshot_id, NULL, 10, &snap_id);                // (5) 0.05273
/*56  */     if (ret || snap_id > UINT32_MAX) {                                  // 0.0
/*58  */         error_setg(errp, "Invalid snapshot ID: %s",                     // 0.0
/*60  */                          snapshot_id ? snapshot_id : "<null>");         // 0.0
/*62  */         return -EINVAL;                                                 // 0.0
/*64  */     }                                                                   // 0.0
/*68  */     if (snap_id) {                                                      // 0.0
/*70  */         hdr.snapid = (uint32_t) snap_id;                                // 0.0
/*72  */     } else {                                                            // 0.0
/*74  */         pstrcpy(snap_tag, sizeof(snap_tag), snapshot_id);               // 0.0
/*76  */         pstrcpy(buf + SD_MAX_VDI_LEN, SD_MAX_VDI_TAG_LEN, snap_tag);    // 0.0
/*78  */     }                                                                   // 0.0
/*82  */     ret = find_vdi_name(s, s->name, snap_id, snap_tag, &vid, true,      // 0.0
/*84  */                         &local_err);                                    // 0.0
/*86  */     if (ret) {                                                          // 0.0
/*88  */         return ret;                                                     // 0.0
/*90  */     }                                                                   // 0.0
/*94  */     fd = connect_to_sdog(s, &local_err);                                // 0.0
/*96  */     if (fd < 0) {                                                       // 0.0
/*98  */         error_report_err(local_err);                                    // 0.0
/*100 */         return -1;                                                      // 0.0
/*102 */     }                                                                   // 0.0
/*106 */     ret = do_req(fd, s->bs, (SheepdogReq *)&hdr,                        // 0.0
/*108 */                  buf, &wlen, &rlen);                                    // 0.0
/*110 */     closesocket(fd);                                                    // 0.0
/*112 */     if (ret) {                                                          // 0.0
/*114 */         return ret;                                                     // 0.0
/*116 */     }                                                                   // 0.0
/*120 */     switch (rsp->result) {                                              // 0.0
/*122 */     case SD_RES_NO_VDI:                                                 // 0.0
/*124 */         error_report("%s was already deleted", s->name);                // 0.0
/*126 */     case SD_RES_SUCCESS:                                                // 0.0
/*128 */         break;                                                          // 0.0
/*130 */     default:                                                            // 0.0
/*132 */         error_report("%s, %s", sd_strerror(rsp->result), s->name);      // 0.0
/*134 */         return -1;                                                      // 0.0
/*136 */     }                                                                   // 0.0
/*140 */     return ret;                                                         // 0.0
/*142 */ }                                                                       // 0.0
