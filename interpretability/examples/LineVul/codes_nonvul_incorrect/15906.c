// commit message FFmpeg@02055b6d40 (target=0, prob=0.78656226, correct=False): vorbisdec: check memory allocations
/*0  */ static void create_map(vorbis_context *vc, unsigned floor_number)           // (14) 0.03516
/*2  */ {                                                                           // (22) 0.001953
/*4  */     vorbis_floor *floors = vc->floors;                                      // (13) 0.03516
/*6  */     vorbis_floor0 *vf;                                                      // (16) 0.02539
/*8  */     int idx;                                                                // (20) 0.01367
/*10 */     int blockflag, n;                                                       // (18) 0.01758
/*12 */     int32_t *map;                                                           // (17) 0.01953
/*16 */     for (blockflag = 0; blockflag < 2; ++blockflag) {                       // (12) 0.03906
/*18 */         n = vc->blocksize[blockflag] / 2;                                   // (9) 0.04102
/*20 */         floors[floor_number].data.t0.map[blockflag] =                       // (7) 0.04688
/*22 */             av_malloc((n + 1) * sizeof(int32_t)); // n + sentinel           // (2) 0.06445
/*26 */         map =  floors[floor_number].data.t0.map[blockflag];                 // (5) 0.05078
/*28 */         vf  = &floors[floor_number].data.t0;                                // (6) 0.04688
/*32 */         for (idx = 0; idx < n; ++idx) {                                     // (8) 0.04687
/*34 */             map[idx] = floor(BARK((vf->rate * idx) / (2.0f * n)) *          // (1) 0.07812
/*36 */                              (vf->bark_map_size / BARK(vf->rate / 2.0f)));  // (0) 0.1035
/*38 */             if (vf->bark_map_size-1 < map[idx])                             // (4) 0.05859
/*40 */                 map[idx] = vf->bark_map_size - 1;                           // (3) 0.06445
/*42 */         }                                                                   // (19) 0.01562
/*44 */         map[n] = -1;                                                        // (15) 0.0293
/*46 */         vf->map_size[blockflag] = n;                                        // (10) 0.03906
/*48 */     }                                                                       // (21) 0.007813
/*52 */     for (idx = 0; idx <= n; ++idx) {                                        // (11) 0.03906
/*54 */         av_dlog(NULL, "floor0 map: map at pos %d is %d\n", idx, map[idx]);  // 0.0
/*56 */     }                                                                       // 0.0
/*58 */ }                                                                           // 0.0
