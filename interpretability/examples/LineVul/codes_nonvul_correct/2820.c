// commit message qemu@ddca7f86ac (target=0, prob=0.2181374, correct=True): hw/9pfs: Add validation to {un}marshal code
/*0  */ static void v9fs_stat(void *opaque)                                     // (15) 0.02539
/*2  */ {                                                                       // (32) 0.001953
/*4  */     int32_t fid;                                                        // (24) 0.01758
/*6  */     V9fsStat v9stat;                                                    // (17) 0.02148
/*8  */     ssize_t err = 0;                                                    // (18) 0.02148
/*10 */     size_t offset = 7;                                                  // (19) 0.01953
/*12 */     struct stat stbuf;                                                  // (25) 0.01562
/*14 */     V9fsFidState *fidp;                                                 // (10) 0.02734
/*16 */     V9fsPDU *pdu = opaque;                                              // (11) 0.02734
/*18 */     V9fsState *s = pdu->s;                                              // (8) 0.0293
/*22 */     pdu_unmarshal(pdu, offset, "d", &fid);                              // (5) 0.04492
/*24 */     trace_v9fs_stat(pdu->tag, pdu->id, fid);                            // (6) 0.04492
/*28 */     fidp = get_fid(pdu, fid);                                           // (7) 0.03125
/*30 */     if (fidp == NULL) {                                                 // (16) 0.02344
/*32 */         err = -ENOENT;                                                  // (12) 0.02734
/*34 */         goto out_nofid;                                                 // (13) 0.02734
/*36 */     }                                                                   // (28) 0.007812
/*38 */     err = v9fs_co_lstat(pdu, &fidp->path, &stbuf);                      // (3) 0.05469
/*40 */     if (err < 0) {                                                      // (20) 0.01953
/*42 */         goto out;                                                       // (21) 0.01953
/*44 */     }                                                                   // (29) 0.007812
/*46 */     err = stat_to_v9stat(pdu, &fidp->path, &stbuf, &v9stat);            // (1) 0.0625
/*48 */     if (err < 0) {                                                      // (22) 0.01953
/*50 */         goto out;                                                       // (23) 0.01953
/*52 */     }                                                                   // (30) 0.007812
/*54 */     offset += pdu_marshal(pdu, offset, "wS", 0, &v9stat);               // (4) 0.05469
/*56 */     err = offset;                                                       // (26) 0.01367
/*58 */     trace_v9fs_stat_return(pdu->tag, pdu->id, v9stat.mode,              // (2) 0.05664
/*60 */                            v9stat.atime, v9stat.mtime, v9stat.length);  // (0) 0.08984
/*62 */     v9fs_stat_free(&v9stat);                                            // (9) 0.0293
/*64 */ out:                                                                    // (31) 0.003906
/*66 */     put_fid(pdu, fidp);                                                 // (14) 0.02734
/*68 */ out_nofid:                                                              // (27) 0.01172
/*70 */     complete_pdu(s, pdu, err);                                          // 0.0
/*72 */ }                                                                       // 0.0
