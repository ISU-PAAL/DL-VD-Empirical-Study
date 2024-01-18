// commit message qemu@4be746345f (target=0, prob=0.057810828, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static int get_stream_blocksize(BlockDriverState *bdrv)                 // (6) 0.04146
/*2  */ {                                                                       // (25) 0.002439
/*4  */     uint8_t cmd[6];                                                     // (20) 0.02683
/*6  */     uint8_t buf[12];                                                    // (21) 0.02683
/*8  */     uint8_t sensebuf[8];                                                // (17) 0.02927
/*10 */     sg_io_hdr_t io_header;                                              // (7) 0.03902
/*12 */     int ret;                                                            // (23) 0.01463
/*16 */     memset(cmd, 0, sizeof(cmd));                                        // (10) 0.03415
/*18 */     memset(buf, 0, sizeof(buf));                                        // (11) 0.03415
/*20 */     cmd[0] = MODE_SENSE;                                                // (12) 0.03415
/*22 */     cmd[4] = sizeof(buf);                                               // (18) 0.02927
/*26 */     memset(&io_header, 0, sizeof(io_header));                           // (4) 0.0439
/*28 */     io_header.interface_id = 'S';                                       // (13) 0.03415
/*30 */     io_header.dxfer_direction = SG_DXFER_FROM_DEV;                      // (3) 0.05366
/*32 */     io_header.dxfer_len = sizeof(buf);                                  // (8) 0.03902
/*34 */     io_header.dxferp = buf;                                             // (15) 0.03171
/*36 */     io_header.cmdp = cmd;                                               // (19) 0.02927
/*38 */     io_header.cmd_len = sizeof(cmd);                                    // (9) 0.03659
/*40 */     io_header.mx_sb_len = sizeof(sensebuf);                             // (5) 0.0439
/*42 */     io_header.sbp = sensebuf;                                           // (16) 0.03171
/*44 */     io_header.timeout = 6000; /* XXX */                                 // (14) 0.03415
/*48 */     ret = bdrv_ioctl(bdrv, SG_IO, &io_header);                          // (2) 0.06098
/*50 */     if (ret < 0 || io_header.driver_status || io_header.host_status) {  // (0) 0.06341
/*52 */         return -1;                                                      // (22) 0.02683
/*54 */     }                                                                   // (24) 0.009756
/*56 */     return (buf[9] << 16) | (buf[10] << 8) | buf[11];                   // (1) 0.06341
/*58 */ }                                                                       // (26) 0.002439
