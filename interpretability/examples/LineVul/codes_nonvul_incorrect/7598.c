// commit message FFmpeg@596b5c488f (target=0, prob=0.6501153, correct=False): wma: check memory allocations and propagate errors
/*0  */ static av_cold void init_coef_vlc(VLC *vlc, uint16_t **prun_table,              // (4) 0.05664
/*2  */                                   float **plevel_table, uint16_t **pint_table,  // (0) 0.09766
/*4  */                                   const CoefVLCTable *vlc_table)                // (1) 0.08789
/*6  */ {                                                                               // (20) 0.001953
/*8  */     int n                        = vlc_table->n;                                // (3) 0.07031
/*10 */     const uint8_t  *table_bits   = vlc_table->huffbits;                         // (5) 0.04883
/*12 */     const uint32_t *table_codes  = vlc_table->huffcodes;                        // (8) 0.04492
/*14 */     const uint16_t *levels_table = vlc_table->levels;                           // (12) 0.03906
/*16 */     uint16_t *run_table, *level_table, *int_table;                              // (9) 0.04297
/*18 */     float *flevel_table;                                                        // (18) 0.01953
/*20 */     int i, l, j, k, level;                                                      // (16) 0.02734
/*24 */     init_vlc(vlc, VLCBITS, n, table_bits, 1, 1, table_codes, 4, 4, 0);          // (2) 0.07031
/*28 */     run_table    = av_malloc(n * sizeof(uint16_t));                             // (6) 0.04688
/*30 */     level_table  = av_malloc(n * sizeof(uint16_t));                             // (10) 0.04297
/*32 */     flevel_table = av_malloc(n * sizeof(*flevel_table));                        // (11) 0.04297
/*34 */     int_table    = av_malloc(n * sizeof(uint16_t));                             // (7) 0.04688
/*36 */     i            = 2;                                                           // (14) 0.03516
/*38 */     level        = 1;                                                           // (17) 0.02734
/*40 */     k            = 0;                                                           // (13) 0.03516
/*42 */     while (i < n) {                                                             // (19) 0.01953
/*44 */         int_table[k] = i;                                                       // (15) 0.03125
/*46 */         l            = levels_table[k++];                                       // 0.0
/*48 */         for (j = 0; j < l; j++) {                                               // 0.0
/*50 */             run_table[i]    = j;                                                // 0.0
/*52 */             level_table[i]  = level;                                            // 0.0
/*54 */             flevel_table[i] = level;                                            // 0.0
/*56 */             i++;                                                                // 0.0
/*58 */         }                                                                       // 0.0
/*60 */         level++;                                                                // 0.0
/*62 */     }                                                                           // 0.0
/*64 */     *prun_table   = run_table;                                                  // 0.0
/*66 */     *plevel_table = flevel_table;                                               // 0.0
/*68 */     *pint_table   = int_table;                                                  // 0.0
/*70 */     av_free(level_table);                                                       // 0.0
/*72 */ }                                                                               // 0.0
