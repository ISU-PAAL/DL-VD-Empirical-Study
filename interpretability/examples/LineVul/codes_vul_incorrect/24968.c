// commit message qemu@a1f0cce2ac (target=1, prob=0.12295289, correct=False): scsi: Update sense code handling
/*0  */ static void scsi_req_set_status(SCSIDiskReq *r, int status, int sense_code)  // (1) 0.2745
/*2  */ {                                                                            // (4) 0.009804
/*4  */     SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, r->req.dev);           // (0) 0.3137
/*8  */     r->req.status = status;                                                  // (3) 0.1078
/*10 */     scsi_disk_set_sense(s, sense_code);                                      // (2) 0.1765
/*12 */ }                                                                            // (5) 0.009804
