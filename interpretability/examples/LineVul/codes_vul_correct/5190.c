// commit message FFmpeg@9af6abdc17 (target=1, prob=0.99923277, correct=True): atrac3: Fix crash in tonal component decoding. Fixes Ticket780 Bug Found by: cosminamironesei
/*0   */ static int decodeTonalComponents (GetBitContext *gb, tonal_component *pComponent, int numBands)      // (2) 0.05274
/*2   */ {                                                                                                    // (25) 0.001963
/*4   */     int i,j,k,cnt;                                                                                   // (17) 0.02539
/*6   */     int   components, coding_mode_selector, coding_mode, coded_values_per_component;                 // (3) 0.05273
/*8   */     int   sfIndx, coded_values, max_coded_values, quant_step_index, coded_components;                // (0) 0.0625
/*10  */     int   band_flags[4], mantissa[8];                                                                // (12) 0.0332
/*12  */     float  *pCoef;                                                                                   // (21) 0.01953
/*14  */     float  scalefactor;                                                                              // (24) 0.01758
/*16  */     int   component_count = 0;                                                                       // (19) 0.02344
/*20  */     components = get_bits(gb,5);                                                                     // (18) 0.02539
/*24  */     /* no tonal components */                                                                        // (23) 0.01758
/*26  */     if (components == 0)                                                                             // (20) 0.01953
/*28  */         return 0;                                                                                    // (22) 0.01953
/*32  */     coding_mode_selector = get_bits(gb,2);                                                           // (11) 0.03515
/*34  */     if (coding_mode_selector == 2)                                                                   // (16) 0.0293
/*39  */     coding_mode = coding_mode_selector & 1;                                                          // (15) 0.03125
/*43  */     for (i = 0; i < components; i++) {                                                               // (14) 0.03125
/*45  */         for (cnt = 0; cnt <= numBands; cnt++)                                                        // (5) 0.04687
/*47  */             band_flags[cnt] = get_bits1(gb);                                                         // (4) 0.05078
/*51  */         coded_values_per_component = get_bits(gb,3);                                                 // (7) 0.04492
/*55  */         quant_step_index = get_bits(gb,3);                                                           // (9) 0.04101
/*57  */         if (quant_step_index <= 1)                                                                   // (13) 0.0332
/*62  */         if (coding_mode_selector == 3)                                                               // (10) 0.03711
/*64  */             coding_mode = get_bits1(gb);                                                             // (8) 0.04297
/*68  */         for (j = 0; j < (numBands + 1) * 4; j++) {                                                   // (1) 0.05468
/*70  */             if (band_flags[j >> 2] == 0)                                                             // (6) 0.04687
/*72  */                 continue;                                                                            // 0.0
/*76  */             coded_components = get_bits(gb,3);                                                       // 0.0
/*80  */             for (k=0; k<coded_components; k++) {                                                     // 0.0
/*82  */                 sfIndx = get_bits(gb,6);                                                             // 0.0
/*86  */                 pComponent[component_count].pos = j * 64 + (get_bits(gb,6));                         // 0.0
/*88  */                 max_coded_values = SAMPLES_PER_FRAME - pComponent[component_count].pos;              // 0.0
/*90  */                 coded_values = coded_values_per_component + 1;                                       // 0.0
/*92  */                 coded_values = FFMIN(max_coded_values,coded_values);                                 // 0.0
/*96  */                 scalefactor = ff_atrac_sf_table[sfIndx] * iMaxQuant[quant_step_index];               // 0.0
/*100 */                 readQuantSpectralCoeffs(gb, quant_step_index, coding_mode, mantissa, coded_values);  // 0.0
/*104 */                 pComponent[component_count].numCoefs = coded_values;                                 // 0.0
/*108 */                 /* inverse quant */                                                                  // 0.0
/*110 */                 pCoef = pComponent[component_count].coef;                                            // 0.0
/*112 */                 for (cnt = 0; cnt < coded_values; cnt++)                                             // 0.0
/*114 */                     pCoef[cnt] = mantissa[cnt] * scalefactor;                                        // 0.0
/*118 */                 component_count++;                                                                   // 0.0
/*120 */             }                                                                                        // 0.0
/*122 */         }                                                                                            // 0.0
/*124 */     }                                                                                                // 0.0
/*128 */     return component_count;                                                                          // 0.0
/*130 */ }                                                                                                    // 0.0
