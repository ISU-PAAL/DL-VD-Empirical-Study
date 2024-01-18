// commit message qemu@0647d47cc1 (target=1, prob=0.056904554, correct=False): qcow2: avoid memcpy(dst, NULL, len)
/*0  */ static size_t header_ext_add(char *buf, uint32_t magic, const void *s,  // (1) 0.1046
/*2  */     size_t len, size_t buflen)                                          // (7) 0.06276
/*4  */ {                                                                       // (13) 0.004184
/*6  */     QCowExtension *ext_backing_fmt = (QCowExtension*) buf;              // (2) 0.1004
/*8  */     size_t ext_len = sizeof(QCowExtension) + ((len + 7) & ~7);          // (0) 0.113
/*12 */     if (buflen < ext_len) {                                             // (8) 0.05858
/*14 */         return -ENOSPC;                                                 // (9) 0.05439
/*16 */     }                                                                   // (12) 0.01674
/*20 */     *ext_backing_fmt = (QCowExtension) {                                // (6) 0.0795
/*22 */         .magic  = cpu_to_be32(magic),                                   // (4) 0.08368
/*24 */         .len    = cpu_to_be32(len),                                     // (3) 0.09205
/*26 */     };                                                                  // (11) 0.01674
/*28 */     memcpy(buf + sizeof(QCowExtension), s, len);                        // (5) 0.08368
/*32 */     return ext_len;                                                     // (10) 0.03347
/*34 */ }                                                                       // (14) 0.004184
