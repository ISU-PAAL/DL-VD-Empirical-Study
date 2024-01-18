// commit message qemu@28b70c9dbd (target=0, prob=0.8132165, correct=False): scsi: Ensure command and transfer lengths are set for all SCSI devices
/*0  */ static int scsi_req_stream_length(SCSICommand *cmd, SCSIDevice *dev, uint8_t *buf)  // (0) 0.06641
/*2  */ {                                                                                   // (34) 0.001953
/*4  */     switch (buf[0]) {                                                               // (15) 0.01953
/*6  */     /* stream commands */                                                           // (32) 0.01367
/*8  */     case ERASE_12:                                                                  // (19) 0.01758
/*10 */     case ERASE_16:                                                                  // (20) 0.01758
/*12 */         cmd->xfer = 0;                                                              // (8) 0.02734
/*14 */         break;                                                                      // (21) 0.01758
/*16 */     case READ_6:                                                                    // (25) 0.01562
/*18 */     case READ_REVERSE:                                                              // (16) 0.01953
/*20 */     case RECOVER_BUFFERED_DATA:                                                     // (10) 0.02539
/*22 */     case WRITE_6:                                                                   // (26) 0.01562
/*24 */         cmd->len = 6;                                                               // (11) 0.02539
/*26 */         cmd->xfer = buf[4] | (buf[3] << 8) | (buf[2] << 16);                        // (1) 0.06641
/*28 */         if (buf[1] & 0x01) { /* fixed */                                            // (4) 0.04297
/*30 */             cmd->xfer *= dev->blocksize;                                            // (5) 0.04297
/*32 */         }                                                                           // (27) 0.01562
/*34 */         break;                                                                      // (22) 0.01758
/*36 */     case READ_16:                                                                   // (28) 0.01562
/*38 */     case READ_REVERSE_16:                                                           // (14) 0.02344
/*40 */     case VERIFY_16:                                                                 // (17) 0.01953
/*42 */     case WRITE_16:                                                                  // (29) 0.01562
/*44 */         cmd->len = 16;                                                              // (12) 0.02539
/*46 */         cmd->xfer = buf[14] | (buf[13] << 8) | (buf[12] << 16);                     // (2) 0.06641
/*48 */         if (buf[1] & 0x01) { /* fixed */                                            // (6) 0.04297
/*50 */             cmd->xfer *= dev->blocksize;                                            // (7) 0.04297
/*52 */         }                                                                           // (30) 0.01562
/*54 */         break;                                                                      // (23) 0.01758
/*56 */     case REWIND:                                                                    // (33) 0.01367
/*58 */     case LOAD_UNLOAD:                                                               // (18) 0.01953
/*60 */         cmd->len = 6;                                                               // (13) 0.02539
/*62 */         cmd->xfer = 0;                                                              // (9) 0.02734
/*64 */         break;                                                                      // (24) 0.01758
/*66 */     case SPACE_16:                                                                  // (31) 0.01562
/*68 */         cmd->xfer = buf[13] | (buf[12] << 8);                                       // (3) 0.04883
/*70 */         break;                                                                      // 0.0
/*72 */     case READ_POSITION:                                                             // 0.0
/*74 */         cmd->xfer = buf[8] | (buf[7] << 8);                                         // 0.0
/*76 */         break;                                                                      // 0.0
/*78 */     case FORMAT_UNIT:                                                               // 0.0
/*80 */         cmd->xfer = buf[4] | (buf[3] << 8);                                         // 0.0
/*82 */         break;                                                                      // 0.0
/*84 */     /* generic commands */                                                          // 0.0
/*86 */     default:                                                                        // 0.0
/*88 */         return scsi_req_length(cmd, dev, buf);                                      // 0.0
/*90 */     }                                                                               // 0.0
/*92 */     return 0;                                                                       // 0.0
/*94 */ }                                                                                   // 0.0
