// commit message qemu@4be746345f (target=0, prob=0.33102983, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static int scsi_disk_emulate_read_toc(SCSIRequest *req, uint8_t *outbuf)               // (4) 0.05545
/*2  */ {                                                                                      // (29) 0.00198
/*4  */     SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, req->dev);                       // (3) 0.05941
/*6  */     int start_track, format, msf, toclen;                                              // (8) 0.03366
/*8  */     uint64_t nb_sectors;                                                               // (16) 0.02574
/*12 */     msf = req->cmd.buf[1] & 2;                                                         // (9) 0.03366
/*14 */     format = req->cmd.buf[2] & 0xf;                                                    // (10) 0.03366
/*16 */     start_track = req->cmd.buf[6];                                                     // (15) 0.0297
/*18 */     bdrv_get_geometry(s->qdev.conf.bs, &nb_sectors);                                   // (5) 0.05347
/*20 */     DPRINTF("Read TOC (track %d format %d msf %d)\n", start_track, format, msf >> 1);  // (0) 0.06931
/*22 */     nb_sectors /= s->qdev.blocksize / 512;                                             // (6) 0.0396
/*24 */     switch (format) {                                                                  // (22) 0.01584
/*26 */     case 0:                                                                            // (24) 0.01188
/*28 */         toclen = cdrom_read_toc(nb_sectors, outbuf, msf, start_track);                 // (2) 0.06535
/*30 */         break;                                                                         // (19) 0.01782
/*32 */     case 1:                                                                            // (25) 0.01188
/*34 */         /* multi session : only a single session defined */                            // (11) 0.03366
/*36 */         toclen = 12;                                                                   // (17) 0.02574
/*38 */         memset(outbuf, 0, 12);                                                         // (12) 0.03366
/*40 */         outbuf[1] = 0x0a;                                                              // (7) 0.03564
/*42 */         outbuf[2] = 0x01;                                                              // (13) 0.03366
/*44 */         outbuf[3] = 0x01;                                                              // (14) 0.03366
/*46 */         break;                                                                         // (20) 0.01782
/*48 */     case 2:                                                                            // (26) 0.01188
/*50 */         toclen = cdrom_read_toc_raw(nb_sectors, outbuf, msf, start_track);             // (1) 0.06931
/*52 */         break;                                                                         // (21) 0.01782
/*54 */     default:                                                                           // (27) 0.009901
/*56 */         return -1;                                                                     // (18) 0.02178
/*58 */     }                                                                                  // (28) 0.007921
/*60 */     return toclen;                                                                     // (23) 0.01584
/*62 */ }                                                                                      // (30) 0.00198
