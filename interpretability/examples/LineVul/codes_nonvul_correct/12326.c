// commit message qemu@333d50fe3d (target=0, prob=0.40355, correct=True): scsi-disk: fix the check of the DBD bit in the MODE SENSE command
/*0   */ static int scsi_disk_emulate_mode_sense(SCSIRequest *req, uint8_t *outbuf)   // (3) 0.05469
/*2   */ {                                                                            // (25) 0.001953
/*4   */     SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, req->dev);             // (1) 0.05859
/*6   */     uint64_t nb_sectors;                                                     // (18) 0.02539
/*8   */     int page, dbd, buflen, page_control;                                     // (15) 0.0332
/*10  */     uint8_t *p;                                                              // (21) 0.01953
/*12  */     uint8_t dev_specific_param;                                              // (19) 0.02539
/*16  */     dbd = req->cmd.buf[1]  & 0x8;                                            // (10) 0.03906
/*18  */     page = req->cmd.buf[2] & 0x3f;                                           // (12) 0.03711
/*20  */     page_control = (req->cmd.buf[2] & 0xc0) >> 6;                            // (4) 0.04688
/*22  */     DPRINTF("Mode Sense(%d) (page %d, len %d, page_control %d)\n",           // (2) 0.05859
/*24  */         (req->cmd.buf[0] == MODE_SENSE) ? 6 : 10, page, len, page_control);  // (0) 0.07031
/*26  */     memset(outbuf, 0, req->cmd.xfer);                                        // (13) 0.03516
/*28  */     p = outbuf;                                                              // (22) 0.01563
/*32  */     if (bdrv_is_read_only(s->bs)) {                                          // (11) 0.03906
/*34  */         dev_specific_param = 0x80; /* Readonly.  */                          // (5) 0.04492
/*36  */     } else {                                                                 // (23) 0.01172
/*38  */         dev_specific_param = 0x00;                                           // (16) 0.0332
/*40  */     }                                                                        // (24) 0.007812
/*44  */     if (req->cmd.buf[0] == MODE_SENSE) {                                     // (8) 0.04102
/*46  */         p[1] = 0; /* Default media type.  */                                 // (7) 0.04102
/*48  */         p[2] = dev_specific_param;                                           // (14) 0.03516
/*50  */         p[3] = 0; /* Block descriptor length.  */                            // (6) 0.04102
/*52  */         p += 4;                                                              // (20) 0.02148
/*54  */     } else { /* MODE_SENSE_10 */                                             // (17) 0.0293
/*56  */         p[2] = 0; /* Default media type.  */                                 // (9) 0.04102
/*58  */         p[3] = dev_specific_param;                                           // 0.0
/*60  */         p[6] = p[7] = 0; /* Block descriptor length.  */                     // 0.0
/*62  */         p += 8;                                                              // 0.0
/*64  */     }                                                                        // 0.0
/*68  */     bdrv_get_geometry(s->bs, &nb_sectors);                                   // 0.0
/*70  */     if ((~dbd) & nb_sectors) {                                               // 0.0
/*72  */         if (req->cmd.buf[0] == MODE_SENSE) {                                 // 0.0
/*74  */             outbuf[3] = 8; /* Block descriptor length  */                    // 0.0
/*76  */         } else { /* MODE_SENSE_10 */                                         // 0.0
/*78  */             outbuf[7] = 8; /* Block descriptor length  */                    // 0.0
/*80  */         }                                                                    // 0.0
/*82  */         nb_sectors /= s->cluster_size;                                       // 0.0
/*84  */         if (nb_sectors > 0xffffff)                                           // 0.0
/*86  */             nb_sectors = 0;                                                  // 0.0
/*88  */         p[0] = 0; /* media density code */                                   // 0.0
/*90  */         p[1] = (nb_sectors >> 16) & 0xff;                                    // 0.0
/*92  */         p[2] = (nb_sectors >> 8) & 0xff;                                     // 0.0
/*94  */         p[3] = nb_sectors & 0xff;                                            // 0.0
/*96  */         p[4] = 0; /* reserved */                                             // 0.0
/*98  */         p[5] = 0; /* bytes 5-7 are the sector size in bytes */               // 0.0
/*100 */         p[6] = s->cluster_size * 2;                                          // 0.0
/*102 */         p[7] = 0;                                                            // 0.0
/*104 */         p += 8;                                                              // 0.0
/*106 */     }                                                                        // 0.0
/*110 */     if (page_control == 3) { /* Saved Values */                              // 0.0
/*112 */         return -1; /* ILLEGAL_REQUEST */                                     // 0.0
/*114 */     }                                                                        // 0.0
/*118 */     switch (page) {                                                          // 0.0
/*120 */     case 0x04:                                                               // 0.0
/*122 */     case 0x05:                                                               // 0.0
/*124 */     case 0x08:                                                               // 0.0
/*126 */     case 0x2a:                                                               // 0.0
/*128 */         p += mode_sense_page(req, page, p, page_control);                    // 0.0
/*130 */         break;                                                               // 0.0
/*132 */     case 0x3f:                                                               // 0.0
/*134 */         p += mode_sense_page(req, 0x08, p, page_control);                    // 0.0
/*136 */         p += mode_sense_page(req, 0x2a, p, page_control);                    // 0.0
/*138 */         break;                                                               // 0.0
/*140 */     default:                                                                 // 0.0
/*142 */         return -1; /* ILLEGAL_REQUEST */                                     // 0.0
/*144 */     }                                                                        // 0.0
/*148 */     buflen = p - outbuf;                                                     // 0.0
/*150 */     /*                                                                       // 0.0
/*152 */      * The mode data length field specifies the length in bytes of the       // 0.0
/*154 */      * following data that is available to be transferred. The mode data     // 0.0
/*156 */      * length does not include itself.                                       // 0.0
/*158 */      */                                                                      // 0.0
/*160 */     if (req->cmd.buf[0] == MODE_SENSE) {                                     // 0.0
/*162 */         outbuf[0] = buflen - 1;                                              // 0.0
/*164 */     } else { /* MODE_SENSE_10 */                                             // 0.0
/*166 */         outbuf[0] = ((buflen - 2) >> 8) & 0xff;                              // 0.0
/*168 */         outbuf[1] = (buflen - 2) & 0xff;                                     // 0.0
/*170 */     }                                                                        // 0.0
/*172 */     if (buflen > req->cmd.xfer)                                              // 0.0
/*174 */         buflen = req->cmd.xfer;                                              // 0.0
/*176 */     return buflen;                                                           // 0.0
/*178 */ }                                                                            // 0.0
