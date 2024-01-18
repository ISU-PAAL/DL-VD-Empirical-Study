// commit message qemu@6fa2c95f27 (target=0, prob=0.5211098, correct=False): scsi-disk: Move active request asserts
/*0  */ static void scsi_read_data(SCSIDevice *d, uint32_t tag)             // (2) 0.09914
/*2  */ {                                                                   // (13) 0.00431
/*4  */     SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, d);           // (1) 0.1207
/*6  */     SCSIDiskReq *r;                                                 // (8) 0.05172
/*10 */     r = scsi_find_request(s, tag);                                  // (5) 0.06897
/*12 */     if (!r) {                                                       // (11) 0.03448
/*14 */         BADF("Bad read tag 0x%x\n", tag);                           // (3) 0.09483
/*16 */         /* ??? This is the wrong error.  */                         // (4) 0.07328
/*18 */         scsi_command_complete(r, CHECK_CONDITION, HARDWARE_ERROR);  // (0) 0.125
/*20 */         return;                                                     // (10) 0.03879
/*22 */     }                                                               // (12) 0.01724
/*26 */     /* No data transfer may already be in progress */               // (7) 0.05603
/*28 */     assert(r->req.aiocb == NULL);                                   // (6) 0.06466
/*32 */     scsi_read_request(r);                                           // (9) 0.05172
/*34 */ }                                                                   // (14) 0.00431
