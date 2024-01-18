// commit message qemu@846424350b (target=1, prob=0.3264107, correct=False): scsi: Allocate SCSITargetReq r->buf dynamically [CVE-2013-4344]
/*0   */ static bool scsi_target_emulate_inquiry(SCSITargetReq *r)                         // (5) 0.04297
/*2   */ {                                                                                 // (29) 0.001953
/*4   */     assert(r->req.dev->lun != r->req.lun);                                        // (6) 0.04102
/*6   */     if (r->req.cmd.buf[1] & 0x2) {                                                // (7) 0.04102
/*8   */         /* Command support data - optional, not implemented */                    // (12) 0.0332
/*10  */         return false;                                                             // (21) 0.01953
/*12  */     }                                                                             // (27) 0.007812
/*16  */     if (r->req.cmd.buf[1] & 0x1) {                                                // (8) 0.04102
/*18  */         /* Vital product data */                                                  // (19) 0.02344
/*20  */         uint8_t page_code = r->req.cmd.buf[2];                                    // (3) 0.04883
/*22  */         r->buf[r->len++] = page_code ; /* this page */                            // (4) 0.04883
/*24  */         r->buf[r->len++] = 0x00;                                                  // (9) 0.04102
/*28  */         switch (page_code) {                                                      // (14) 0.02734
/*30  */         case 0x00: /* Supported page codes, mandatory */                          // (10) 0.03711
/*32  */         {                                                                         // (24) 0.01562
/*34  */             int pages;                                                            // (15) 0.02734
/*36  */             pages = r->len++;                                                     // (13) 0.0332
/*38  */             r->buf[r->len++] = 0x00; /* list of supported pages (this page) */    // (0) 0.06836
/*40  */             r->buf[pages] = r->len - pages - 1; /* number of pages */             // (1) 0.06055
/*42  */             break;                                                                // (17) 0.02539
/*44  */         }                                                                         // (25) 0.01562
/*46  */         default:                                                                  // (23) 0.01758
/*48  */             return false;                                                         // (16) 0.02734
/*50  */         }                                                                         // (26) 0.01562
/*52  */         /* done with EVPD */                                                      // (18) 0.02539
/*54  */         assert(r->len < sizeof(r->buf));                                          // (11) 0.03711
/*56  */         r->len = MIN(r->req.cmd.xfer, r->len);                                    // (2) 0.05078
/*58  */         return true;                                                              // (22) 0.01953
/*60  */     }                                                                             // (28) 0.007812
/*64  */     /* Standard INQUIRY data */                                                   // (20) 0.02148
/*66  */     if (r->req.cmd.buf[2] != 0) {                                                 // 0.0
/*68  */         return false;                                                             // 0.0
/*70  */     }                                                                             // 0.0
/*74  */     /* PAGE CODE == 0 */                                                          // 0.0
/*76  */     r->len = MIN(r->req.cmd.xfer, 36);                                            // 0.0
/*78  */     memset(r->buf, 0, r->len);                                                    // 0.0
/*80  */     if (r->req.lun != 0) {                                                        // 0.0
/*82  */         r->buf[0] = TYPE_NO_LUN;                                                  // 0.0
/*84  */     } else {                                                                      // 0.0
/*86  */         r->buf[0] = TYPE_NOT_PRESENT | TYPE_INACTIVE;                             // 0.0
/*88  */         r->buf[2] = 5; /* Version */                                              // 0.0
/*90  */         r->buf[3] = 2 | 0x10; /* HiSup, response data format */                   // 0.0
/*92  */         r->buf[4] = r->len - 5; /* Additional Length = (Len - 1) - 4 */           // 0.0
/*94  */         r->buf[7] = 0x10 | (r->req.bus->info->tcq ? 0x02 : 0); /* Sync, TCQ.  */  // 0.0
/*96  */         memcpy(&r->buf[8], "QEMU    ", 8);                                        // 0.0
/*98  */         memcpy(&r->buf[16], "QEMU TARGET     ", 16);                              // 0.0
/*100 */         pstrcpy((char *) &r->buf[32], 4, qemu_get_version());                     // 0.0
/*102 */     }                                                                             // 0.0
/*104 */     return true;                                                                  // 0.0
/*106 */ }                                                                                 // 0.0
