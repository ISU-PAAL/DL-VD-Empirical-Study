// commit message qemu@5e30a07d6d (target=1, prob=0.9708044, correct=True): scsi: Sanitize command definitions
/*0   */ static int scsi_req_length(SCSIRequest *req, uint8_t *cmd)                             // (4) 0.04297
/*2   */ {                                                                                      // (33) 0.001953
/*4   */     switch (cmd[0] >> 5) {                                                             // (13) 0.02539
/*6   */     case 0:                                                                            // (26) 0.01172
/*8   */         req->cmd.xfer = cmd[4];                                                        // (6) 0.03516
/*10  */         req->cmd.len = 6;                                                              // (8) 0.0293
/*12  */         /* length 0 means 256 blocks */                                                // (12) 0.02734
/*14  */         if (req->cmd.xfer == 0)                                                        // (7) 0.03516
/*16  */             req->cmd.xfer = 256;                                                       // (5) 0.03906
/*18  */         break;                                                                         // (19) 0.01758
/*20  */     case 1:                                                                            // (27) 0.01172
/*22  */     case 2:                                                                            // (28) 0.01172
/*24  */         req->cmd.xfer = cmd[8] | (cmd[7] << 8);                                        // (3) 0.05273
/*26  */         req->cmd.len = 10;                                                             // (9) 0.0293
/*28  */         break;                                                                         // (20) 0.01758
/*30  */     case 4:                                                                            // (29) 0.01172
/*32  */         req->cmd.xfer = cmd[13] | (cmd[12] << 8) | (cmd[11] << 16) | (cmd[10] << 24);  // (0) 0.08789
/*34  */         req->cmd.len = 16;                                                             // (10) 0.0293
/*36  */         break;                                                                         // (21) 0.01758
/*38  */     case 5:                                                                            // (30) 0.01172
/*40  */         req->cmd.xfer = cmd[9] | (cmd[8] << 8) | (cmd[7] << 16) | (cmd[6] << 24);      // (1) 0.08789
/*42  */         req->cmd.len = 12;                                                             // (11) 0.0293
/*44  */         break;                                                                         // (22) 0.01758
/*46  */     default:                                                                           // (31) 0.009766
/*48  */         trace_scsi_req_parse_bad(req->dev->id, req->lun, req->tag, cmd[0]);            // (2) 0.07227
/*50  */         return -1;                                                                     // (16) 0.02148
/*52  */     }                                                                                  // (32) 0.007812
/*56  */     switch(cmd[0]) {                                                                   // (17) 0.01953
/*58  */     case TEST_UNIT_READY:                                                              // (14) 0.02344
/*60  */     case START_STOP:                                                                   // (23) 0.01758
/*62  */     case SEEK_6:                                                                       // (18) 0.01758
/*64  */     case WRITE_FILEMARKS:                                                              // (15) 0.02148
/*66  */     case SPACE:                                                                        // (25) 0.01172
/*68  */     case RESERVE:                                                                      // (24) 0.01562
/*70  */     case RELEASE:                                                                      // 0.0
/*72  */     case ERASE:                                                                        // 0.0
/*74  */     case ALLOW_MEDIUM_REMOVAL:                                                         // 0.0
/*76  */     case VERIFY:                                                                       // 0.0
/*78  */     case SEEK_10:                                                                      // 0.0
/*80  */     case SYNCHRONIZE_CACHE:                                                            // 0.0
/*82  */     case LOCK_UNLOCK_CACHE:                                                            // 0.0
/*84  */     case LOAD_UNLOAD:                                                                  // 0.0
/*86  */     case SET_CD_SPEED:                                                                 // 0.0
/*88  */     case SET_LIMITS:                                                                   // 0.0
/*90  */     case WRITE_LONG:                                                                   // 0.0
/*92  */     case MOVE_MEDIUM:                                                                  // 0.0
/*94  */     case UPDATE_BLOCK:                                                                 // 0.0
/*96  */         req->cmd.xfer = 0;                                                             // 0.0
/*98  */         break;                                                                         // 0.0
/*100 */     case MODE_SENSE:                                                                   // 0.0
/*102 */         break;                                                                         // 0.0
/*104 */     case WRITE_SAME:                                                                   // 0.0
/*106 */         req->cmd.xfer = 1;                                                             // 0.0
/*108 */         break;                                                                         // 0.0
/*110 */     case READ_CAPACITY:                                                                // 0.0
/*112 */         req->cmd.xfer = 8;                                                             // 0.0
/*114 */         break;                                                                         // 0.0
/*116 */     case READ_BLOCK_LIMITS:                                                            // 0.0
/*118 */         req->cmd.xfer = 6;                                                             // 0.0
/*120 */         break;                                                                         // 0.0
/*122 */     case READ_POSITION:                                                                // 0.0
/*124 */         req->cmd.xfer = 20;                                                            // 0.0
/*126 */         break;                                                                         // 0.0
/*128 */     case SEND_VOLUME_TAG:                                                              // 0.0
/*130 */         req->cmd.xfer *= 40;                                                           // 0.0
/*132 */         break;                                                                         // 0.0
/*134 */     case MEDIUM_SCAN:                                                                  // 0.0
/*136 */         req->cmd.xfer *= 8;                                                            // 0.0
/*138 */         break;                                                                         // 0.0
/*140 */     case WRITE_10:                                                                     // 0.0
/*142 */     case WRITE_VERIFY:                                                                 // 0.0
/*144 */     case WRITE_6:                                                                      // 0.0
/*146 */     case WRITE_12:                                                                     // 0.0
/*148 */     case WRITE_VERIFY_12:                                                              // 0.0
/*150 */     case WRITE_16:                                                                     // 0.0
/*152 */     case WRITE_VERIFY_16:                                                              // 0.0
/*154 */         req->cmd.xfer *= req->dev->blocksize;                                          // 0.0
/*156 */         break;                                                                         // 0.0
/*158 */     case READ_10:                                                                      // 0.0
/*160 */     case READ_6:                                                                       // 0.0
/*162 */     case READ_REVERSE:                                                                 // 0.0
/*164 */     case RECOVER_BUFFERED_DATA:                                                        // 0.0
/*166 */     case READ_12:                                                                      // 0.0
/*168 */     case READ_16:                                                                      // 0.0
/*170 */         req->cmd.xfer *= req->dev->blocksize;                                          // 0.0
/*172 */         break;                                                                         // 0.0
/*174 */     case INQUIRY:                                                                      // 0.0
/*176 */         req->cmd.xfer = cmd[4] | (cmd[3] << 8);                                        // 0.0
/*178 */         break;                                                                         // 0.0
/*180 */     case MAINTENANCE_OUT:                                                              // 0.0
/*182 */     case MAINTENANCE_IN:                                                               // 0.0
/*184 */         if (req->dev->type == TYPE_ROM) {                                              // 0.0
/*186 */             /* GPCMD_REPORT_KEY and GPCMD_SEND_KEY from multi media commands */        // 0.0
/*188 */             req->cmd.xfer = cmd[9] | (cmd[8] << 8);                                    // 0.0
/*190 */         }                                                                              // 0.0
/*192 */         break;                                                                         // 0.0
/*194 */     }                                                                                  // 0.0
/*196 */     return 0;                                                                          // 0.0
/*198 */ }                                                                                      // 0.0
