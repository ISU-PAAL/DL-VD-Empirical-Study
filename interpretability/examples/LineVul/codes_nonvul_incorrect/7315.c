// commit message qemu@afa46c468a (target=0, prob=0.55084646, correct=False): scsi: move request parsing to common code
/*0   */ static int32_t scsi_send_command(SCSIRequest *req, uint8_t *cmd)                // (7) 0.04883
/*2   */ {                                                                               // (26) 0.001953
/*4   */     SCSIGenericState *s = DO_UPCAST(SCSIGenericState, qdev, req->dev);          // (2) 0.0625
/*6   */     SCSIGenericReq *r = DO_UPCAST(SCSIGenericReq, req, req);                    // (3) 0.06055
/*8   */     int ret;                                                                    // (21) 0.01172
/*12  */     if (cmd[0] != REQUEST_SENSE && req->lun != s->qdev.lun) {                   // (4) 0.05859
/*14  */         DPRINTF("Unimplemented LUN %d\n", req->lun);                            // (5) 0.05273
/*16  */         scsi_req_build_sense(&r->req, SENSE_CODE(LUN_NOT_SUPPORTED));           // (0) 0.06836
/*18  */         scsi_req_complete(&r->req, CHECK_CONDITION);                            // (8) 0.04883
/*20  */         return 0;                                                               // (16) 0.01953
/*22  */     }                                                                           // (22) 0.007812
/*26  */     if (-1 == scsi_req_parse(&r->req, cmd)) {                                   // (12) 0.04102
/*28  */         BADF("Unsupported command length, command %x\n", cmd[0]);               // (9) 0.04883
/*30  */         scsi_command_complete(r, -EINVAL);                                      // (13) 0.04102
/*32  */         return 0;                                                               // (17) 0.01953
/*34  */     }                                                                           // (23) 0.007812
/*36  */     scsi_req_fixup(&r->req);                                                    // (14) 0.0293
/*40  */     DPRINTF("Command: lun=%d tag=0x%x len %zd data=0x%02x", lun, tag,           // (1) 0.06836
/*42  */             r->req.cmd.xfer, cmd[0]);                                           // (10) 0.04688
/*46  */ #ifdef DEBUG_SCSI                                                               // (20) 0.01367
/*48  */     {                                                                           // (24) 0.007812
/*50  */         int i;                                                                  // (18) 0.01953
/*52  */         for (i = 1; i < r->req.cmd.len; i++) {                                  // (6) 0.05078
/*54  */             printf(" 0x%02x", cmd[i]);                                          // (11) 0.04492
/*56  */         }                                                                       // (19) 0.01562
/*58  */         printf("\n");                                                           // (15) 0.02344
/*60  */     }                                                                           // (25) 0.007812
/*62  */ #endif                                                                          // 0.0
/*66  */     if (r->req.cmd.xfer == 0) {                                                 // 0.0
/*68  */         if (r->buf != NULL)                                                     // 0.0
/*70  */             qemu_free(r->buf);                                                  // 0.0
/*72  */         r->buflen = 0;                                                          // 0.0
/*74  */         r->buf = NULL;                                                          // 0.0
/*76  */         ret = execute_command(s->bs, r, SG_DXFER_NONE, scsi_command_complete);  // 0.0
/*78  */         if (ret < 0) {                                                          // 0.0
/*80  */             scsi_command_complete(r, ret);                                      // 0.0
/*82  */             return 0;                                                           // 0.0
/*84  */         }                                                                       // 0.0
/*86  */         return 0;                                                               // 0.0
/*88  */     }                                                                           // 0.0
/*92  */     if (r->buflen != r->req.cmd.xfer) {                                         // 0.0
/*94  */         if (r->buf != NULL)                                                     // 0.0
/*96  */             qemu_free(r->buf);                                                  // 0.0
/*98  */         r->buf = qemu_malloc(r->req.cmd.xfer);                                  // 0.0
/*100 */         r->buflen = r->req.cmd.xfer;                                            // 0.0
/*102 */     }                                                                           // 0.0
/*106 */     memset(r->buf, 0, r->buflen);                                               // 0.0
/*108 */     r->len = r->req.cmd.xfer;                                                   // 0.0
/*110 */     if (r->req.cmd.mode == SCSI_XFER_TO_DEV) {                                  // 0.0
/*112 */         r->len = 0;                                                             // 0.0
/*114 */         return -r->req.cmd.xfer;                                                // 0.0
/*116 */     } else {                                                                    // 0.0
/*118 */         return r->req.cmd.xfer;                                                 // 0.0
/*120 */     }                                                                           // 0.0
/*122 */ }                                                                               // 0.0
