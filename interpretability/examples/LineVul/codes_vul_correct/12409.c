// commit message qemu@7ef8cf9a08 (target=1, prob=0.6342836, correct=True): scsi-bus: Fix transfer length for VERIFY with BYTCHK=11b
/*0   */ static int scsi_req_length(SCSICommand *cmd, SCSIDevice *dev, uint8_t *buf)      // (0) 0.0625
/*2   */ {                                                                                // (38) 0.001953
/*4   */     cmd->xfer = scsi_cdb_length(buf);                                            // (3) 0.03516
/*6   */     switch (buf[0]) {                                                            // (20) 0.01953
/*8   */     case TEST_UNIT_READY:                                                        // (12) 0.02344
/*10  */     case REWIND:                                                                 // (34) 0.01367
/*12  */     case START_STOP:                                                             // (27) 0.01758
/*14  */     case SET_CAPACITY:                                                           // (21) 0.01953
/*16  */     case WRITE_FILEMARKS:                                                        // (14) 0.02148
/*18  */     case WRITE_FILEMARKS_16:                                                     // (11) 0.02539
/*20  */     case SPACE:                                                                  // (36) 0.01172
/*22  */     case RESERVE:                                                                // (32) 0.01562
/*24  */     case RELEASE:                                                                // (37) 0.01172
/*26  */     case ERASE:                                                                  // (35) 0.01367
/*28  */     case ALLOW_MEDIUM_REMOVAL:                                                   // (7) 0.02734
/*30  */     case SEEK_10:                                                                // (28) 0.01758
/*32  */     case SYNCHRONIZE_CACHE:                                                      // (8) 0.02734
/*34  */     case SYNCHRONIZE_CACHE_16:                                                   // (6) 0.03125
/*36  */     case LOCATE_16:                                                              // (29) 0.01758
/*38  */     case LOCK_UNLOCK_CACHE:                                                      // (9) 0.02734
/*40  */     case SET_CD_SPEED:                                                           // (15) 0.02148
/*42  */     case SET_LIMITS:                                                             // (22) 0.01953
/*44  */     case WRITE_LONG_10:                                                          // (16) 0.02148
/*46  */     case UPDATE_BLOCK:                                                           // (30) 0.01758
/*48  */     case RESERVE_TRACK:                                                          // (17) 0.02148
/*50  */     case SET_READ_AHEAD:                                                         // (18) 0.02148
/*52  */     case PRE_FETCH:                                                              // (23) 0.01953
/*54  */     case PRE_FETCH_16:                                                           // (13) 0.02344
/*56  */     case ALLOW_OVERWRITE:                                                        // (19) 0.02148
/*58  */         cmd->xfer = 0;                                                           // (10) 0.02734
/*60  */         break;                                                                   // (31) 0.01758
/*62  */     case VERIFY_10:                                                              // (24) 0.01953
/*64  */     case VERIFY_12:                                                              // (25) 0.01953
/*66  */     case VERIFY_16:                                                              // (26) 0.01953
/*68  */         if ((buf[1] & 2) == 0) {                                                 // (2) 0.03906
/*70  */             cmd->xfer = 0;                                                       // (4) 0.03516
/*72  */         } else if ((buf[1] & 4) == 1) {                                          // (1) 0.04297
/*74  */             cmd->xfer = 1;                                                       // (5) 0.03516
/*76  */         }                                                                        // (33) 0.01562
/*78  */         cmd->xfer *= dev->blocksize;                                             // 0.0
/*80  */         break;                                                                   // 0.0
/*82  */     case MODE_SENSE:                                                             // 0.0
/*84  */         break;                                                                   // 0.0
/*86  */     case WRITE_SAME_10:                                                          // 0.0
/*88  */     case WRITE_SAME_16:                                                          // 0.0
/*90  */         cmd->xfer = dev->blocksize;                                              // 0.0
/*92  */         break;                                                                   // 0.0
/*94  */     case READ_CAPACITY_10:                                                       // 0.0
/*96  */         cmd->xfer = 8;                                                           // 0.0
/*98  */         break;                                                                   // 0.0
/*100 */     case READ_BLOCK_LIMITS:                                                      // 0.0
/*102 */         cmd->xfer = 6;                                                           // 0.0
/*104 */         break;                                                                   // 0.0
/*106 */     case SEND_VOLUME_TAG:                                                        // 0.0
/*108 */         /* GPCMD_SET_STREAMING from multimedia commands.  */                     // 0.0
/*110 */         if (dev->type == TYPE_ROM) {                                             // 0.0
/*112 */             cmd->xfer = buf[10] | (buf[9] << 8);                                 // 0.0
/*114 */         } else {                                                                 // 0.0
/*116 */             cmd->xfer = buf[9] | (buf[8] << 8);                                  // 0.0
/*118 */         }                                                                        // 0.0
/*120 */         break;                                                                   // 0.0
/*122 */     case WRITE_6:                                                                // 0.0
/*124 */         /* length 0 means 256 blocks */                                          // 0.0
/*126 */         if (cmd->xfer == 0) {                                                    // 0.0
/*128 */             cmd->xfer = 256;                                                     // 0.0
/*130 */         }                                                                        // 0.0
/*132 */     case WRITE_10:                                                               // 0.0
/*134 */     case WRITE_VERIFY_10:                                                        // 0.0
/*136 */     case WRITE_12:                                                               // 0.0
/*138 */     case WRITE_VERIFY_12:                                                        // 0.0
/*140 */     case WRITE_16:                                                               // 0.0
/*142 */     case WRITE_VERIFY_16:                                                        // 0.0
/*144 */         cmd->xfer *= dev->blocksize;                                             // 0.0
/*146 */         break;                                                                   // 0.0
/*148 */     case READ_6:                                                                 // 0.0
/*150 */     case READ_REVERSE:                                                           // 0.0
/*152 */         /* length 0 means 256 blocks */                                          // 0.0
/*154 */         if (cmd->xfer == 0) {                                                    // 0.0
/*156 */             cmd->xfer = 256;                                                     // 0.0
/*158 */         }                                                                        // 0.0
/*160 */     case READ_10:                                                                // 0.0
/*162 */     case RECOVER_BUFFERED_DATA:                                                  // 0.0
/*164 */     case READ_12:                                                                // 0.0
/*166 */     case READ_16:                                                                // 0.0
/*168 */         cmd->xfer *= dev->blocksize;                                             // 0.0
/*170 */         break;                                                                   // 0.0
/*172 */     case FORMAT_UNIT:                                                            // 0.0
/*174 */         /* MMC mandates the parameter list to be 12-bytes long.  Parameters      // 0.0
/*176 */          * for block devices are restricted to the header right now.  */         // 0.0
/*178 */         if (dev->type == TYPE_ROM && (buf[1] & 16)) {                            // 0.0
/*180 */             cmd->xfer = 12;                                                      // 0.0
/*182 */         } else {                                                                 // 0.0
/*184 */             cmd->xfer = (buf[1] & 16) == 0 ? 0 : (buf[1] & 32 ? 8 : 4);          // 0.0
/*186 */         }                                                                        // 0.0
/*188 */         break;                                                                   // 0.0
/*190 */     case INQUIRY:                                                                // 0.0
/*192 */     case RECEIVE_DIAGNOSTIC:                                                     // 0.0
/*194 */     case SEND_DIAGNOSTIC:                                                        // 0.0
/*196 */         cmd->xfer = buf[4] | (buf[3] << 8);                                      // 0.0
/*198 */         break;                                                                   // 0.0
/*200 */     case READ_CD:                                                                // 0.0
/*202 */     case READ_BUFFER:                                                            // 0.0
/*204 */     case WRITE_BUFFER:                                                           // 0.0
/*206 */     case SEND_CUE_SHEET:                                                         // 0.0
/*208 */         cmd->xfer = buf[8] | (buf[7] << 8) | (buf[6] << 16);                     // 0.0
/*210 */         break;                                                                   // 0.0
/*212 */     case PERSISTENT_RESERVE_OUT:                                                 // 0.0
/*214 */         cmd->xfer = ldl_be_p(&buf[5]) & 0xffffffffULL;                           // 0.0
/*216 */         break;                                                                   // 0.0
/*218 */     case ERASE_12:                                                               // 0.0
/*220 */         if (dev->type == TYPE_ROM) {                                             // 0.0
/*222 */             /* MMC command GET PERFORMANCE.  */                                  // 0.0
/*224 */             cmd->xfer = scsi_get_performance_length(buf[9] | (buf[8] << 8),      // 0.0
/*226 */                                                     buf[10], buf[1] & 0x1f);     // 0.0
/*228 */         }                                                                        // 0.0
/*230 */         break;                                                                   // 0.0
/*232 */     case MECHANISM_STATUS:                                                       // 0.0
/*234 */     case READ_DVD_STRUCTURE:                                                     // 0.0
/*236 */     case SEND_DVD_STRUCTURE:                                                     // 0.0
/*238 */     case MAINTENANCE_OUT:                                                        // 0.0
/*240 */     case MAINTENANCE_IN:                                                         // 0.0
/*242 */         if (dev->type == TYPE_ROM) {                                             // 0.0
/*244 */             /* GPCMD_REPORT_KEY and GPCMD_SEND_KEY from multi media commands */  // 0.0
/*246 */             cmd->xfer = buf[9] | (buf[8] << 8);                                  // 0.0
/*248 */         }                                                                        // 0.0
/*250 */         break;                                                                   // 0.0
/*252 */     case ATA_PASSTHROUGH_12:                                                     // 0.0
/*254 */         if (dev->type == TYPE_ROM) {                                             // 0.0
/*256 */             /* BLANK command of MMC */                                           // 0.0
/*258 */             cmd->xfer = 0;                                                       // 0.0
/*260 */         } else {                                                                 // 0.0
/*262 */             cmd->xfer = ata_passthrough_12_xfer_size(dev, buf);                  // 0.0
/*264 */         }                                                                        // 0.0
/*266 */         break;                                                                   // 0.0
/*268 */     case ATA_PASSTHROUGH_16:                                                     // 0.0
/*270 */         cmd->xfer = ata_passthrough_16_xfer_size(dev, buf);                      // 0.0
/*272 */         break;                                                                   // 0.0
/*274 */     }                                                                            // 0.0
/*276 */     return 0;                                                                    // 0.0
/*278 */ }                                                                                // 0.0
