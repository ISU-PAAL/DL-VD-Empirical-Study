// commit message qemu@895b00f62a (target=1, prob=0.5051688, correct=True): qga: flush explicitly when needed
/*0  */ void qmp_guest_file_flush(int64_t handle, Error **errp)           // (2) 0.1287
/*2  */ {                                                                 // (12) 0.005848
/*4  */     GuestFileHandle *gfh = guest_file_handle_find(handle, errp);  // (1) 0.1404
/*6  */     FILE *fh;                                                     // (8) 0.04678
/*8  */     int ret;                                                      // (9) 0.03509
/*12 */     if (!gfh) {                                                   // (6) 0.05848
/*14 */         return;                                                   // (7) 0.05263
/*16 */     }                                                             // (10) 0.02339
/*20 */     fh = gfh->fh;                                                 // (3) 0.07602
/*22 */     ret = fflush(fh);                                             // (4) 0.06433
/*24 */     if (ret == EOF) {                                             // (5) 0.06433
/*26 */         error_setg_errno(errp, errno, "failed to flush file");    // (0) 0.1579
/*30 */     }                                                             // (11) 0.02339
/*32 */ }                                                                 // (13) 0.005848
