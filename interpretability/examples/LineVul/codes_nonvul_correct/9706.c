// commit message qemu@fdaef06917 (target=0, prob=0.21154968, correct=True): scsi: move handling of REPORT LUNS and invalid LUNs to common code
/*0   */ static int scsi_disk_emulate_command(SCSIDiskReq *r, uint8_t *outbuf)          // (3) 0.05664
/*2   */ {                                                                              // (27) 0.001953
/*4   */     SCSIRequest *req = &r->req;                                                // (14) 0.02734
/*6   */     SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, req->dev);               // (2) 0.05859
/*8   */     uint64_t nb_sectors;                                                       // (16) 0.02539
/*10  */     int buflen = 0;                                                            // (19) 0.01953
/*12  */     int ret;                                                                   // (26) 0.01172
/*16  */     switch (req->cmd.buf[0]) {                                                 // (15) 0.02734
/*18  */     case TEST_UNIT_READY:                                                      // (17) 0.02344
/*20  */         if (!bdrv_is_inserted(s->bs))                                          // (6) 0.04297
/*22  */             goto not_ready;                                                    // (8) 0.03125
/*24  */         break;                                                                 // (22) 0.01758
/*26  */     case REQUEST_SENSE:                                                        // (20) 0.01953
/*28  */         if (req->cmd.xfer < 4)                                                 // (7) 0.03516
/*30  */             goto illegal_request;                                              // (9) 0.03125
/*32  */         buflen = scsi_device_get_sense(&s->qdev, outbuf, req->cmd.xfer,        // (1) 0.06836
/*34  */                                        (req->cmd.buf[1] & 1) == 0);            // (0) 0.1035
/*36  */         break;                                                                 // (23) 0.01758
/*38  */     case INQUIRY:                                                              // (24) 0.01758
/*40  */         buflen = scsi_disk_emulate_inquiry(req, outbuf);                       // (5) 0.05273
/*42  */         if (buflen < 0)                                                        // (12) 0.0293
/*44  */             goto illegal_request;                                              // (10) 0.03125
/*46  */         break;                                                                 // (25) 0.01758
/*48  */     case MODE_SENSE:                                                           // (21) 0.01953
/*50  */     case MODE_SENSE_10:                                                        // (18) 0.02344
/*52  */         buflen = scsi_disk_emulate_mode_sense(req, outbuf);                    // (4) 0.05469
/*54  */         if (buflen < 0)                                                        // (13) 0.0293
/*56  */             goto illegal_request;                                              // (11) 0.03125
/*58  */         break;                                                                 // 0.0
/*60  */     case READ_TOC:                                                             // 0.0
/*62  */         buflen = scsi_disk_emulate_read_toc(req, outbuf);                      // 0.0
/*64  */         if (buflen < 0)                                                        // 0.0
/*66  */             goto illegal_request;                                              // 0.0
/*68  */         break;                                                                 // 0.0
/*70  */     case RESERVE:                                                              // 0.0
/*72  */         if (req->cmd.buf[1] & 1)                                               // 0.0
/*74  */             goto illegal_request;                                              // 0.0
/*76  */         break;                                                                 // 0.0
/*78  */     case RESERVE_10:                                                           // 0.0
/*80  */         if (req->cmd.buf[1] & 3)                                               // 0.0
/*82  */             goto illegal_request;                                              // 0.0
/*84  */         break;                                                                 // 0.0
/*86  */     case RELEASE:                                                              // 0.0
/*88  */         if (req->cmd.buf[1] & 1)                                               // 0.0
/*90  */             goto illegal_request;                                              // 0.0
/*92  */         break;                                                                 // 0.0
/*94  */     case RELEASE_10:                                                           // 0.0
/*96  */         if (req->cmd.buf[1] & 3)                                               // 0.0
/*98  */             goto illegal_request;                                              // 0.0
/*100 */         break;                                                                 // 0.0
/*102 */     case START_STOP:                                                           // 0.0
/*104 */         if (s->qdev.type == TYPE_ROM && (req->cmd.buf[4] & 2)) {               // 0.0
/*106 */             /* load/eject medium */                                            // 0.0
/*108 */             bdrv_eject(s->bs, !(req->cmd.buf[4] & 1));                         // 0.0
/*110 */         }                                                                      // 0.0
/*112 */         break;                                                                 // 0.0
/*114 */     case ALLOW_MEDIUM_REMOVAL:                                                 // 0.0
/*116 */         bdrv_set_locked(s->bs, req->cmd.buf[4] & 1);                           // 0.0
/*118 */         break;                                                                 // 0.0
/*120 */     case READ_CAPACITY_10:                                                     // 0.0
/*122 */         /* The normal LEN field for this command is zero.  */                  // 0.0
/*124 */         memset(outbuf, 0, 8);                                                  // 0.0
/*126 */         bdrv_get_geometry(s->bs, &nb_sectors);                                 // 0.0
/*128 */         if (!nb_sectors)                                                       // 0.0
/*130 */             goto not_ready;                                                    // 0.0
/*132 */         nb_sectors /= s->cluster_size;                                         // 0.0
/*134 */         /* Returned value is the address of the last sector.  */               // 0.0
/*136 */         nb_sectors--;                                                          // 0.0
/*138 */         /* Remember the new size for read/write sanity checking. */            // 0.0
/*140 */         s->max_lba = nb_sectors;                                               // 0.0
/*142 */         /* Clip to 2TB, instead of returning capacity modulo 2TB. */           // 0.0
/*144 */         if (nb_sectors > UINT32_MAX)                                           // 0.0
/*146 */             nb_sectors = UINT32_MAX;                                           // 0.0
/*148 */         outbuf[0] = (nb_sectors >> 24) & 0xff;                                 // 0.0
/*150 */         outbuf[1] = (nb_sectors >> 16) & 0xff;                                 // 0.0
/*152 */         outbuf[2] = (nb_sectors >> 8) & 0xff;                                  // 0.0
/*154 */         outbuf[3] = nb_sectors & 0xff;                                         // 0.0
/*156 */         outbuf[4] = 0;                                                         // 0.0
/*158 */         outbuf[5] = 0;                                                         // 0.0
/*160 */         outbuf[6] = s->cluster_size * 2;                                       // 0.0
/*162 */         outbuf[7] = 0;                                                         // 0.0
/*164 */         buflen = 8;                                                            // 0.0
/*166 */         break;                                                                 // 0.0
/*168 */     case SYNCHRONIZE_CACHE:                                                    // 0.0
/*170 */         ret = bdrv_flush(s->bs);                                               // 0.0
/*172 */         if (ret < 0) {                                                         // 0.0
/*174 */             if (scsi_handle_rw_error(r, -ret, SCSI_REQ_STATUS_RETRY_FLUSH)) {  // 0.0
/*176 */                 return -1;                                                     // 0.0
/*178 */             }                                                                  // 0.0
/*180 */         }                                                                      // 0.0
/*182 */         break;                                                                 // 0.0
/*184 */     case GET_CONFIGURATION:                                                    // 0.0
/*186 */         memset(outbuf, 0, 8);                                                  // 0.0
/*188 */         /* ??? This should probably return much more information.  For now     // 0.0
/*190 */            just return the basic header indicating the CD-ROM profile.  */     // 0.0
/*192 */         outbuf[7] = 8; // CD-ROM                                               // 0.0
/*194 */         buflen = 8;                                                            // 0.0
/*196 */         break;                                                                 // 0.0
/*198 */     case SERVICE_ACTION_IN:                                                    // 0.0
/*200 */         /* Service Action In subcommands. */                                   // 0.0
/*202 */         if ((req->cmd.buf[1] & 31) == 0x10) {                                  // 0.0
/*204 */             DPRINTF("SAI READ CAPACITY(16)\n");                                // 0.0
/*206 */             memset(outbuf, 0, req->cmd.xfer);                                  // 0.0
/*208 */             bdrv_get_geometry(s->bs, &nb_sectors);                             // 0.0
/*210 */             if (!nb_sectors)                                                   // 0.0
/*212 */                 goto not_ready;                                                // 0.0
/*214 */             nb_sectors /= s->cluster_size;                                     // 0.0
/*216 */             /* Returned value is the address of the last sector.  */           // 0.0
/*218 */             nb_sectors--;                                                      // 0.0
/*220 */             /* Remember the new size for read/write sanity checking. */        // 0.0
/*222 */             s->max_lba = nb_sectors;                                           // 0.0
/*224 */             outbuf[0] = (nb_sectors >> 56) & 0xff;                             // 0.0
/*226 */             outbuf[1] = (nb_sectors >> 48) & 0xff;                             // 0.0
/*228 */             outbuf[2] = (nb_sectors >> 40) & 0xff;                             // 0.0
/*230 */             outbuf[3] = (nb_sectors >> 32) & 0xff;                             // 0.0
/*232 */             outbuf[4] = (nb_sectors >> 24) & 0xff;                             // 0.0
/*234 */             outbuf[5] = (nb_sectors >> 16) & 0xff;                             // 0.0
/*236 */             outbuf[6] = (nb_sectors >> 8) & 0xff;                              // 0.0
/*238 */             outbuf[7] = nb_sectors & 0xff;                                     // 0.0
/*240 */             outbuf[8] = 0;                                                     // 0.0
/*242 */             outbuf[9] = 0;                                                     // 0.0
/*244 */             outbuf[10] = s->cluster_size * 2;                                  // 0.0
/*246 */             outbuf[11] = 0;                                                    // 0.0
/*248 */             outbuf[12] = 0;                                                    // 0.0
/*250 */             outbuf[13] = get_physical_block_exp(&s->qdev.conf);                // 0.0
/*254 */             /* set TPE bit if the format supports discard */                   // 0.0
/*256 */             if (s->qdev.conf.discard_granularity) {                            // 0.0
/*258 */                 outbuf[14] = 0x80;                                             // 0.0
/*260 */             }                                                                  // 0.0
/*264 */             /* Protection, exponent and lowest lba field left blank. */        // 0.0
/*266 */             buflen = req->cmd.xfer;                                            // 0.0
/*268 */             break;                                                             // 0.0
/*270 */         }                                                                      // 0.0
/*272 */         DPRINTF("Unsupported Service Action In\n");                            // 0.0
/*274 */         goto illegal_request;                                                  // 0.0
/*276 */     case REPORT_LUNS:                                                          // 0.0
/*278 */         if (req->cmd.xfer < 16)                                                // 0.0
/*280 */             goto illegal_request;                                              // 0.0
/*282 */         memset(outbuf, 0, 16);                                                 // 0.0
/*284 */         outbuf[3] = 8;                                                         // 0.0
/*286 */         buflen = 16;                                                           // 0.0
/*288 */         break;                                                                 // 0.0
/*290 */     case VERIFY_10:                                                            // 0.0
/*292 */         break;                                                                 // 0.0
/*294 */     default:                                                                   // 0.0
/*296 */         scsi_check_condition(r, SENSE_CODE(INVALID_OPCODE));                   // 0.0
/*298 */         return -1;                                                             // 0.0
/*300 */     }                                                                          // 0.0
/*302 */     return buflen;                                                             // 0.0
/*306 */ not_ready:                                                                     // 0.0
/*308 */     if (!bdrv_is_inserted(s->bs)) {                                            // 0.0
/*310 */         scsi_check_condition(r, SENSE_CODE(NO_MEDIUM));                        // 0.0
/*312 */     } else {                                                                   // 0.0
/*314 */         scsi_check_condition(r, SENSE_CODE(LUN_NOT_READY));                    // 0.0
/*316 */     }                                                                          // 0.0
/*318 */     return -1;                                                                 // 0.0
/*322 */ illegal_request:                                                               // 0.0
/*324 */     scsi_check_condition(r, SENSE_CODE(INVALID_FIELD));                        // 0.0
/*326 */     return -1;                                                                 // 0.0
/*328 */ }                                                                              // 0.0
