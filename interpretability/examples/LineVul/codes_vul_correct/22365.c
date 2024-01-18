// commit message qemu@b0ad5a455d (target=1, prob=0.59839, correct=True): cow: Use bdrv_(p)write_sync for metadata writes
/*0  */ static inline int cow_set_bit(BlockDriverState *bs, int64_t bitnum)  // (3) 0.1058
/*2  */ {                                                                    // (13) 0.004808
/*4  */     uint64_t offset = sizeof(struct cow_header_v2) + bitnum / 8;     // (2) 0.1202
/*6  */     uint8_t bitmap;                                                  // (7) 0.04808
/*10 */     if (bdrv_pread(bs->file, offset, &bitmap, sizeof(bitmap)) !=     // (1) 0.1298
/*12 */ 	    sizeof(bitmap)) {                                               // (8) 0.04808
/*14 */        return -errno;                                                // (5) 0.05288
/*16 */     }                                                                // (11) 0.01923
/*20 */     bitmap |= (1 << (bitnum % 8));                                   // (4) 0.07692
/*24 */     if (bdrv_pwrite(bs->file, offset, &bitmap, sizeof(bitmap)) !=    // (0) 0.1346
/*26 */ 	    sizeof(bitmap)) {                                               // (9) 0.04808
/*28 */        return -errno;                                                // (6) 0.05288
/*30 */     }                                                                // (12) 0.01923
/*32 */     return 0;                                                        // (10) 0.02885
/*34 */ }                                                                    // (14) 0.004808
