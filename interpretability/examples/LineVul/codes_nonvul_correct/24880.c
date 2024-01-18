// commit message qemu@786a4ea82e (target=0, prob=0.37380564, correct=True): Convert (ffs(val) - 1) to ctz32(val)
/*0  */ int qcow2_pre_write_overlap_check(BlockDriverState *bs, int ign, int64_t offset,  // (4) 0.08555
/*2  */                                   int64_t size)                                   // (2) 0.115
/*4  */ {                                                                                 // (14) 0.00295
/*6  */     int ret = qcow2_check_metadata_overlap(bs, ign, offset, size);                // (6) 0.07375
/*10 */     if (ret < 0) {                                                                // (10) 0.0295
/*12 */         return ret;                                                               // (11) 0.0295
/*14 */     } else if (ret > 0) {                                                         // (8) 0.0354
/*16 */         int metadata_ol_bitnr = ffs(ret) - 1;                                     // (7) 0.06785
/*18 */         assert(metadata_ol_bitnr < QCOW2_OL_MAX_BITNR);                           // (5) 0.07965
/*22 */         qcow2_signal_corruption(bs, true, offset, size, "Preventing invalid "     // (3) 0.0885
/*24 */                                 "write on metadata (overlaps with %s)",           // (1) 0.1268
/*26 */                                 metadata_ol_names[metadata_ol_bitnr]);            // (0) 0.1298
/*28 */         return -EIO;                                                              // (9) 0.0354
/*30 */     }                                                                             // (13) 0.0118
/*34 */     return 0;                                                                     // (12) 0.0177
/*36 */ }                                                                                 // (15) 0.00295
