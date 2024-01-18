// commit message qemu@a7812ae412 (target=0, prob=0.017041834, correct=True): TCG variable type checking.
/*0  */ static inline void t_gen_addx_carry(DisasContext *dc, TCGv d)  // (1) 0.05263
/*2  */ {                                                              // (27) 0.002288
/*4  */ 	if (dc->flagx_known) {                                        // (18) 0.02517
/*6  */ 		if (dc->flags_x) {                                           // (19) 0.02517
/*8  */ 			TCGv c;                                                     // (23) 0.01831
/*10 */                                                                // (16) 0.02746
/*12 */ 			c = tcg_temp_new(TCG_TYPE_TL);                              // (6) 0.04348
/*14 */ 			t_gen_mov_TN_preg(c, PR_CCS);                               // (2) 0.05034
/*16 */ 			/* C flag is already at bit 0.  */                          // (15) 0.03204
/*18 */ 			tcg_gen_andi_tl(c, c, C_FLAG);                              // (4) 0.04577
/*20 */ 			tcg_gen_add_tl(d, d, c);                                    // (10) 0.04119
/*22 */ 			tcg_temp_free(c);                                           // (17) 0.02746
/*24 */ 		}                                                            // (25) 0.006865
/*26 */ 	} else {                                                      // (24) 0.009153
/*28 */ 		TCGv x, c;                                                   // (22) 0.02059
/*32 */ 		x = tcg_temp_new(TCG_TYPE_TL);                               // (8) 0.04119
/*34 */ 		c = tcg_temp_new(TCG_TYPE_TL);                               // (11) 0.04119
/*36 */ 		t_gen_mov_TN_preg(x, PR_CCS);                                // (3) 0.04805
/*38 */ 		tcg_gen_mov_tl(c, x);                                        // (14) 0.03661
/*42 */ 		/* Propagate carry into d if X is set. Branch free.  */      // (9) 0.04119
/*44 */ 		tcg_gen_andi_tl(c, c, C_FLAG);                               // (7) 0.04348
/*46 */ 		tcg_gen_andi_tl(x, x, X_FLAG);                               // (5) 0.04348
/*48 */ 		tcg_gen_shri_tl(x, x, 4);                                    // (12) 0.04119
/*52 */ 		tcg_gen_and_tl(x, x, c);                                     // (13) 0.0389
/*54 */ 		tcg_gen_add_tl(d, d, x);                                     // (0) 0.05721
/*56 */ 		tcg_temp_free(x);                                            // (20) 0.02517
/*58 */ 		tcg_temp_free(c);                                            // (21) 0.02517
/*60 */ 	}                                                             // (26) 0.004577
/*62 */ }                                                              // (28) 0.002288
