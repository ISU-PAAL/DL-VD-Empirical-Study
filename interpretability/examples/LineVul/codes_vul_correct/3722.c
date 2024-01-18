// commit message FFmpeg@dae7ff0416 (target=1, prob=0.9905344, correct=True): wmall: remove tabs that leaked in from a merge and seem to have managed to silently bypass the push checks.
/*0  */ static void decode_mclms(WmallDecodeCtx *s)                                         // (10) 0.045
/*2  */ {                                                                                   // (22) 0.0025
/*4  */     s->mclms_order = (get_bits(&s->gb, 4) + 1) * 2;                                 // (4) 0.07
/*6  */     s->mclms_scaling = get_bits(&s->gb, 4);                                         // (5) 0.055
/*8  */     if(get_bits1(&s->gb)) {                                                         // (12) 0.0375
/*10 */ 	// mclms_send_coef                                                                 // (13) 0.025
/*12 */ 	int i;                                                                             // (18) 0.01
/*14 */ 	int send_coef_bits;                                                                // (14) 0.0225
/*16 */ 	int cbits = av_log2(s->mclms_scaling + 1);                                         // (7) 0.0525
/*18 */ 	assert(cbits == my_log2(s->mclms_scaling + 1));                                    // (6) 0.055
/*20 */ 	if(1 << cbits < s->mclms_scaling + 1)                                              // (8) 0.0475
/*22 */ 	    cbits++;                                                                       // (15) 0.0175
/*26 */ 	send_coef_bits = (cbits ? get_bits(&s->gb, cbits) : 0) + 2;                        // (3) 0.0725
/*30 */ 	for(i = 0; i < s->mclms_order * s->num_channels * s->num_channels; i++) {          // (1) 0.085
/*32 */ 	    s->mclms_coeffs[i] = get_bits(&s->gb, send_coef_bits);                         // (2) 0.08
/*34 */ 	}                                                                                  // (20) 0.005
/*38 */ 	for(i = 0; i < s->num_channels; i++) {                                             // (9) 0.0475
/*40 */ 	    int c;                                                                         // (16) 0.0175
/*42 */ 	    for(c = 0; c < i; c++) {                                                       // (11) 0.0425
/*44 */ 		s->mclms_coeffs_cur[i * s->num_channels + c] = get_bits(&s->gb, send_coef_bits);  // (0) 0.1025
/*46 */ 	    }                                                                              // (17) 0.0125
/*48 */ 	}                                                                                  // (21) 0.005
/*50 */     }                                                                               // (19) 0.01
/*52 */ }                                                                                   // (23) 0.0025
