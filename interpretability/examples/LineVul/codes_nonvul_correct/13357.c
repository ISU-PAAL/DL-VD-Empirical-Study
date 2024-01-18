// commit message qemu@ddca7f86ac (target=0, prob=0.21820278, correct=True): hw/9pfs: Add validation to {un}marshal code
/*0  */ static void v9fs_readdir(void *opaque)                                      // (10) 0.02734
/*2  */ {                                                                           // (34) 0.001953
/*4  */     int32_t fid;                                                            // (25) 0.01758
/*6  */     V9fsFidState *fidp;                                                     // (11) 0.02734
/*8  */     ssize_t retval = 0;                                                     // (15) 0.02344
/*10 */     size_t offset = 7;                                                      // (21) 0.01953
/*12 */     uint64_t initial_offset;                                                // (19) 0.02148
/*14 */     int32_t count;                                                          // (26) 0.01758
/*16 */     uint32_t max_count;                                                     // (20) 0.02148
/*18 */     V9fsPDU *pdu = opaque;                                                  // (12) 0.02734
/*20 */     V9fsState *s = pdu->s;                                                  // (7) 0.0293
/*24 */     pdu_unmarshal(pdu, offset, "dqd", &fid, &initial_offset, &max_count);   // (0) 0.06641
/*28 */     trace_v9fs_readdir(pdu->tag, pdu->id, fid, initial_offset, max_count);  // (1) 0.0625
/*32 */     fidp = get_fid(pdu, fid);                                               // (6) 0.03125
/*34 */     if (fidp == NULL) {                                                     // (16) 0.02344
/*36 */         retval = -EINVAL;                                                   // (8) 0.0293
/*38 */         goto out_nofid;                                                     // (13) 0.02734
/*40 */     }                                                                       // (30) 0.007812
/*42 */     if (!fidp->fs.dir) {                                                    // (14) 0.02734
/*44 */         retval = -EINVAL;                                                   // (9) 0.0293
/*46 */         goto out;                                                           // (22) 0.01953
/*48 */     }                                                                       // (31) 0.007812
/*50 */     if (initial_offset == 0) {                                              // (17) 0.02344
/*52 */         v9fs_co_rewinddir(pdu, fidp);                                       // (4) 0.04492
/*54 */     } else {                                                                // (29) 0.01172
/*56 */         v9fs_co_seekdir(pdu, fidp, initial_offset);                         // (2) 0.05078
/*58 */     }                                                                       // (32) 0.007812
/*60 */     count = v9fs_do_readdir(pdu, fidp, max_count);                          // (3) 0.04688
/*62 */     if (count < 0) {                                                        // (23) 0.01953
/*64 */         retval = count;                                                     // (18) 0.02344
/*66 */         goto out;                                                           // (24) 0.01953
/*68 */     }                                                                       // (33) 0.007812
/*70 */     retval = offset;                                                        // (27) 0.01562
/*72 */     retval += pdu_marshal(pdu, offset, "d", count);                         // (5) 0.04492
/*74 */     retval += count;                                                        // (28) 0.01562
/*76 */     trace_v9fs_readdir_return(pdu->tag, pdu->id, count, retval);            // 0.0
/*78 */ out:                                                                        // 0.0
/*80 */     put_fid(pdu, fidp);                                                     // 0.0
/*82 */ out_nofid:                                                                  // 0.0
/*84 */     complete_pdu(s, pdu, retval);                                           // 0.0
/*86 */ }                                                                           // 0.0
