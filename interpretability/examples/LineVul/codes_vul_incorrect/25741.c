// commit message qemu@0d4cc3e715 (target=1, prob=0.38978732, correct=False): Fix improper usage of cpu_to_be32 in vpc
/*0  */ static int vpc_write(BlockDriverState *bs, int64_t sector_num,                 // (9) 0.04102
/*2  */     const uint8_t *buf, int nb_sectors)                                        // (14) 0.03516
/*4  */ {                                                                              // (26) 0.001953
/*6  */     BDRVVPCState *s = bs->opaque;                                              // (13) 0.03516
/*8  */     int64_t offset;                                                            // (20) 0.01758
/*10 */     int64_t sectors, sectors_per_block;                                        // (16) 0.0293
/*12 */     int ret;                                                                   // (24) 0.01172
/*14 */     VHDFooter *footer =  (VHDFooter *) s->footer_buf;                          // (4) 0.04883
/*18 */     if (cpu_to_be32(footer->type) == VHD_FIXED) {                              // (5) 0.04883
/*20 */         return bdrv_write(bs->file, sector_num, buf, nb_sectors);              // (1) 0.05859
/*22 */     }                                                                          // (25) 0.007812
/*24 */     while (nb_sectors > 0) {                                                   // (19) 0.02539
/*26 */         offset = get_sector_offset(bs, sector_num, 1);                         // (7) 0.04492
/*30 */         sectors_per_block = s->block_size >> BDRV_SECTOR_BITS;                 // (2) 0.05859
/*32 */         sectors = sectors_per_block - (sector_num % sectors_per_block);        // (3) 0.05078
/*34 */         if (sectors > nb_sectors) {                                            // (11) 0.03711
/*36 */             sectors = nb_sectors;                                              // (10) 0.03711
/*38 */         }                                                                      // (21) 0.01562
/*42 */         if (offset == -1) {                                                    // (17) 0.0293
/*44 */             offset = alloc_block(bs, sector_num);                              // (8) 0.04492
/*46 */             if (offset < 0)                                                    // (15) 0.0332
/*48 */                 return -1;                                                     // (12) 0.03711
/*50 */         }                                                                      // (22) 0.01562
/*54 */         ret = bdrv_pwrite(bs->file, offset, buf, sectors * BDRV_SECTOR_SIZE);  // (0) 0.07031
/*56 */         if (ret != sectors * BDRV_SECTOR_SIZE) {                               // (6) 0.04687
/*58 */             return -1;                                                         // (18) 0.0293
/*60 */         }                                                                      // (23) 0.01562
/*64 */         nb_sectors -= sectors;                                                 // 0.0
/*66 */         sector_num += sectors;                                                 // 0.0
/*68 */         buf += sectors * BDRV_SECTOR_SIZE;                                     // 0.0
/*70 */     }                                                                          // 0.0
/*74 */     return 0;                                                                  // 0.0
/*76 */ }                                                                              // 0.0
