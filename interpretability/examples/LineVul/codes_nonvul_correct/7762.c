// commit message qemu@f9749f28b7 (target=0, prob=0.079735234, correct=True): stream: tweak usage of bdrv_co_is_allocated
/*0  */ static int coroutine_fn is_allocated_base(BlockDriverState *top,            // (8) 0.03711
/*2  */                                           BlockDriverState *base,           // (2) 0.0918
/*4  */                                           int64_t sector_num,               // (1) 0.0957
/*6  */                                           int nb_sectors, int *pnum)        // (0) 0.1035
/*8  */ {                                                                           // (25) 0.001953
/*10 */     BlockDriverState *intermediate;                                         // (18) 0.01953
/*12 */     int ret, n;                                                             // (20) 0.01562
/*16 */     ret = bdrv_co_is_allocated(top, sector_num, nb_sectors, &n);            // (5) 0.06055
/*18 */     if (ret) {                                                              // (21) 0.01562
/*20 */         *pnum = n;                                                          // (13) 0.02539
/*22 */         return ret;                                                         // (19) 0.01953
/*24 */     }                                                                       // (23) 0.007812
/*28 */     /*                                                                      // (24) 0.007812
/*30 */      * Is the unallocated chunk [sector_num, n] also                        // (7) 0.03711
/*32 */      * unallocated between base and top?                                    // (14) 0.02539
/*34 */      */                                                                     // (22) 0.009766
/*36 */     intermediate = top->backing_hd;                                         // (16) 0.02344
/*40 */     while (intermediate != base) {                                          // (17) 0.02148
/*42 */         int pnum_inter;                                                     // (15) 0.02539
/*46 */         ret = bdrv_co_is_allocated(intermediate, sector_num, nb_sectors,    // (4) 0.06445
/*48 */                                    &pnum_inter);                            // (3) 0.07812
/*50 */         if (ret < 0) {                                                      // (9) 0.02734
/*52 */             return ret;                                                     // (10) 0.02734
/*54 */         } else if (ret) {                                                   // (11) 0.02734
/*56 */             *pnum = pnum_inter;                                             // (6) 0.03906
/*58 */             return 0;                                                       // (12) 0.02734
/*60 */         }                                                                   // 0.0
/*64 */         /*                                                                  // 0.0
/*66 */          * [sector_num, nb_sectors] is unallocated on top but intermediate  // 0.0
/*68 */          * might have                                                       // 0.0
/*70 */          *                                                                  // 0.0
/*72 */          * [sector_num+x, nr_sectors] allocated.                            // 0.0
/*74 */          */                                                                 // 0.0
/*76 */         if (n > pnum_inter) {                                               // 0.0
/*78 */             n = pnum_inter;                                                 // 0.0
/*80 */         }                                                                   // 0.0
/*84 */         intermediate = intermediate->backing_hd;                            // 0.0
/*86 */     }                                                                       // 0.0
/*90 */     *pnum = n;                                                              // 0.0
/*92 */     return 1;                                                               // 0.0
/*94 */ }                                                                           // 0.0
