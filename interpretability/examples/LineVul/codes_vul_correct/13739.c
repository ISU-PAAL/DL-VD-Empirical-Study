// commit message qemu@b71706d122 (target=1, prob=0.9990977, correct=True): qemu-ga: for w32, fix leaked handle ov.hEvent in ga_channel_write()
/*0  */ static GIOStatus ga_channel_write(GAChannel *c, const char *buf, size_t size,  // (5) 0.04883
/*2  */                                   size_t *count)                               // (0) 0.07617
/*4  */ {                                                                              // (25) 0.001953
/*6  */     GIOStatus status;                                                          // (20) 0.01563
/*8  */     OVERLAPPED ov = {0};                                                       // (17) 0.02344
/*10 */     BOOL ret;                                                                  // (23) 0.01367
/*12 */     DWORD written;                                                             // (22) 0.01367
/*16 */     ov.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);                         // (12) 0.03711
/*18 */     ret = WriteFile(c->handle, buf, size, &written, &ov);                      // (7) 0.04297
/*20 */     if (!ret) {                                                                // (21) 0.01562
/*22 */         if (GetLastError() == ERROR_IO_PENDING) {                              // (6) 0.04492
/*24 */             /* write is pending */                                             // (14) 0.03125
/*26 */             ret = GetOverlappedResult(c->handle, &ov, &written, TRUE);         // (1) 0.06055
/*28 */             if (!ret) {                                                        // (15) 0.03125
/*30 */                 if (!GetLastError()) {                                         // (8) 0.04297
/*32 */                     status = G_IO_STATUS_AGAIN;                                // (2) 0.06055
/*34 */                 } else {                                                       // (13) 0.03516
/*36 */                     status = G_IO_STATUS_ERROR;                                // (3) 0.05859
/*39 */             } else {                                                           // (16) 0.02734
/*41 */                 /* write is complete */                                        // (10) 0.03906
/*43 */                 status = G_IO_STATUS_NORMAL;                                   // (4) 0.05273
/*45 */                 *count = written;                                              // (11) 0.03906
/*48 */         } else {                                                               // (19) 0.01953
/*50 */             status = G_IO_STATUS_ERROR;                                        // (9) 0.04297
/*53 */     } else {                                                                   // (24) 0.01172
/*55 */         /* write returned immediately */                                       // (18) 0.02344
/*57 */         status = G_IO_STATUS_NORMAL;                                           // 0.0
/*59 */         *count = written;                                                      // 0.0
/*68 */     return status;                                                             // 0.0
