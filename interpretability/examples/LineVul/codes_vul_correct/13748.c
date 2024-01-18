// commit message qemu@5c6c0e5136 (target=1, prob=0.58656216, correct=True): scsi: Use 'SCSIRequest' directly
/*0   */ static void vscsi_command_complete(SCSIBus *bus, int reason, uint32_t tag,      // (6) 0.05078
/*2   */                                    uint32_t arg)                                // (1) 0.07812
/*4   */ {                                                                               // (22) 0.001953
/*6   */     VSCSIState *s = DO_UPCAST(VSCSIState, vdev.qdev, bus->qbus.parent);         // (3) 0.06641
/*8   */     vscsi_req *req = vscsi_find_req(s, tag);                                    // (8) 0.04492
/*10  */     SCSIDevice *sdev;                                                           // (13) 0.02344
/*12  */     uint8_t *buf;                                                               // (17) 0.01953
/*14  */     int32_t res_in = 0, res_out = 0;                                            // (11) 0.03711
/*16  */     int len, rc = 0;                                                            // (16) 0.01953
/*20  */     dprintf("VSCSI: SCSI cmd complete, r=0x%x tag=0x%x arg=0x%x, req=%p\n",     // (0) 0.08008
/*22  */             reason, tag, arg, req);                                             // (12) 0.03711
/*24  */     if (req == NULL) {                                                          // (19) 0.01953
/*26  */         fprintf(stderr, "VSCSI: Can't find request for tag 0x%x\n", tag);       // (4) 0.06641
/*28  */         return;                                                                 // (20) 0.01758
/*30  */     }                                                                           // (21) 0.007813
/*32  */     sdev = req->sdev;                                                           // (15) 0.02148
/*36  */     if (req->sensing) {                                                         // (14) 0.02148
/*38  */         if (reason == SCSI_REASON_DONE) {                                       // (10) 0.04102
/*40  */             dprintf("VSCSI: Sense done !\n");                                   // (7) 0.04687
/*42  */             vscsi_send_rsp(s, req, CHECK_CONDITION, 0, 0);                      // (2) 0.06836
/*44  */             vscsi_put_req(s, req);                                              // (9) 0.04492
/*46  */         } else {                                                                // (18) 0.01953
/*48  */             uint8_t *buf = sdev->info->get_buf(sdev, tag);                      // (5) 0.0625
/*52  */             len = MIN(arg, SCSI_SENSE_BUF_SIZE);                                // 0.0
/*54  */             dprintf("VSCSI: Sense data, %d bytes:\n", len);                     // 0.0
/*56  */             dprintf("       %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x\n",  // 0.0
/*58  */                     buf[0], buf[1], buf[2], buf[3],                             // 0.0
/*60  */                     buf[4], buf[5], buf[6], buf[7]);                            // 0.0
/*62  */             dprintf("       %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x\n",  // 0.0
/*64  */                     buf[8], buf[9], buf[10], buf[11],                           // 0.0
/*66  */                     buf[12], buf[13], buf[14], buf[15]);                        // 0.0
/*68  */             memcpy(req->sense, buf, len);                                       // 0.0
/*70  */             req->senselen = len;                                                // 0.0
/*72  */             sdev->info->read_data(sdev, req->qtag);                             // 0.0
/*74  */         }                                                                       // 0.0
/*76  */         return;                                                                 // 0.0
/*78  */     }                                                                           // 0.0
/*82  */     if (reason == SCSI_REASON_DONE) {                                           // 0.0
/*84  */         dprintf("VSCSI: Command complete err=%d\n", arg);                       // 0.0
/*86  */         if (arg == 0) {                                                         // 0.0
/*88  */             /* We handle overflows, not underflows for normal commands,         // 0.0
/*90  */              * but hopefully nobody cares                                       // 0.0
/*92  */              */                                                                 // 0.0
/*94  */             if (req->writing) {                                                 // 0.0
/*96  */                 res_out = req->data_len;                                        // 0.0
/*98  */             } else {                                                            // 0.0
/*100 */                 res_in = req->data_len;                                         // 0.0
/*102 */             }                                                                   // 0.0
/*104 */             vscsi_send_rsp(s, req, 0, res_in, res_out);                         // 0.0
/*106 */         } else if (arg == CHECK_CONDITION) {                                    // 0.0
/*108 */             dprintf("VSCSI: Got CHECK_CONDITION, requesting sense...\n");       // 0.0
/*110 */             vscsi_send_request_sense(s, req);                                   // 0.0
/*112 */             return;                                                             // 0.0
/*114 */         } else {                                                                // 0.0
/*116 */             vscsi_send_rsp(s, req, arg, 0, 0);                                  // 0.0
/*118 */         }                                                                       // 0.0
/*120 */         vscsi_put_req(s, req);                                                  // 0.0
/*122 */         return;                                                                 // 0.0
/*124 */     }                                                                           // 0.0
/*128 */     /* "arg" is how much we have read for reads and how much we want            // 0.0
/*130 */      * to write for writes (ie, how much is to be DMA'd)                        // 0.0
/*132 */      */                                                                         // 0.0
/*134 */     if (arg) {                                                                  // 0.0
/*136 */         buf = sdev->info->get_buf(sdev, tag);                                   // 0.0
/*138 */         rc = vscsi_srp_transfer_data(s, req, req->writing, buf, arg);           // 0.0
/*140 */     }                                                                           // 0.0
/*142 */     if (rc < 0) {                                                               // 0.0
/*144 */         fprintf(stderr, "VSCSI: RDMA error rc=%d!\n", rc);                      // 0.0
/*146 */         sdev->info->cancel_io(sdev, req->qtag);                                 // 0.0
/*148 */         vscsi_makeup_sense(s, req, HARDWARE_ERROR, 0, 0);                       // 0.0
/*150 */         vscsi_send_rsp(s, req, CHECK_CONDITION, 0, 0);                          // 0.0
/*152 */         vscsi_put_req(s, req);                                                  // 0.0
/*154 */         return;                                                                 // 0.0
/*156 */     }                                                                           // 0.0
/*160 */     /* Start next chunk */                                                      // 0.0
/*162 */     req->data_len -= rc;                                                        // 0.0
/*164 */     if (req->writing) {                                                         // 0.0
/*166 */         sdev->info->write_data(sdev, req->qtag);                                // 0.0
/*168 */     } else {                                                                    // 0.0
/*170 */         sdev->info->read_data(sdev, req->qtag);                                 // 0.0
/*172 */     }                                                                           // 0.0
/*174 */ }                                                                               // 0.0
