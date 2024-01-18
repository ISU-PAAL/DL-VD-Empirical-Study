// commit message qemu@a7812ae412 (target=0, prob=0.11967001, correct=True): TCG variable type checking.
/*0   */ static void gen_tst_cc (DisasContext *dc, TCGv cc, int cond)            // (2) 0.04492
/*2   */ {                                                                       // (37) 0.001953
/*4   */ 	int arith_opt, move_opt;                                               // (22) 0.02148
/*8   */ 	/* TODO: optimize more condition codes.  */                            // (21) 0.02344
/*12  */ 	/*                                                                     // (34) 0.003906
/*14  */ 	 * If the flags are live, we've gotta look into the bits of CCS.       // (5) 0.03711
/*16  */ 	 * Otherwise, if we just did an arithmetic operation we try to         // (14) 0.02734
/*18  */ 	 * evaluate the condition code faster.                                 // (23) 0.01562
/*20  */ 	 *                                                                     // (35) 0.003906
/*22  */ 	 * When this function is done, T0 should be non-zero if the condition  // (7) 0.03516
/*24  */ 	 * code is true.                                                       // (27) 0.01172
/*26  */ 	 */                                                                    // (36) 0.003906
/*28  */ 	arith_opt = arith_cc(dc) && !dc->flags_uptodate;                       // (3) 0.04492
/*30  */ 	move_opt = (dc->cc_op == CC_OP_MOVE) && dc->flags_uptodate;            // (0) 0.05469
/*32  */ 	switch (cond) {                                                        // (28) 0.01172
/*34  */ 		case CC_EQ:                                                           // (24) 0.01562
/*36  */ 			if (arith_opt || move_opt) {                                         // (13) 0.0293
/*38  */ 				/* If cc_result is zero, T0 should be                               // (11) 0.0332
/*40  */ 				   non-zero otherwise T0 should be zero.  */                        // (8) 0.03516
/*42  */ 				int l1;                                                             // (25) 0.01562
/*44  */ 				l1 = gen_new_label();                                               // (16) 0.02539
/*46  */ 				tcg_gen_movi_tl(cc, 0);                                             // (9) 0.03516
/*48  */ 				tcg_gen_brcondi_tl(TCG_COND_NE, cc_result,                          // (1) 0.05469
/*50  */ 						   0, l1);                                                        // (17) 0.02539
/*52  */ 				tcg_gen_movi_tl(cc, 1);                                             // (10) 0.03516
/*54  */ 				gen_set_label(l1);                                                  // (18) 0.02539
/*56  */ 			}                                                                    // (32) 0.007812
/*58  */ 			else {                                                               // (29) 0.009766
/*60  */ 				cris_evaluate_flags(dc);                                            // (19) 0.02539
/*62  */ 				tcg_gen_andi_tl(cc,                                                 // (12) 0.03125
/*64  */ 						cpu_PR[PR_CCS], Z_FLAG);                                          // (6) 0.03711
/*66  */ 			}                                                                    // (33) 0.007812
/*68  */ 			break;                                                               // (30) 0.009766
/*70  */ 		case CC_NE:                                                           // (26) 0.01367
/*72  */ 			if (arith_opt || move_opt)                                           // (15) 0.02734
/*74  */ 				tcg_gen_mov_tl(cc, cc_result);                                      // (4) 0.03906
/*76  */ 			else {                                                               // (31) 0.009766
/*78  */ 				cris_evaluate_flags(dc);                                            // (20) 0.02539
/*80  */ 				tcg_gen_xori_tl(cc, cpu_PR[PR_CCS],                                 // 0.0
/*82  */ 						Z_FLAG);                                                          // 0.0
/*84  */ 				tcg_gen_andi_tl(cc, cc, Z_FLAG);                                    // 0.0
/*86  */ 			}                                                                    // 0.0
/*88  */ 			break;                                                               // 0.0
/*90  */ 		case CC_CS:                                                           // 0.0
/*92  */ 			cris_evaluate_flags(dc);                                             // 0.0
/*94  */ 			tcg_gen_andi_tl(cc, cpu_PR[PR_CCS], C_FLAG);                         // 0.0
/*96  */ 			break;                                                               // 0.0
/*98  */ 		case CC_CC:                                                           // 0.0
/*100 */ 			cris_evaluate_flags(dc);                                             // 0.0
/*102 */ 			tcg_gen_xori_tl(cc, cpu_PR[PR_CCS], C_FLAG);                         // 0.0
/*104 */ 			tcg_gen_andi_tl(cc, cc, C_FLAG);                                     // 0.0
/*106 */ 			break;                                                               // 0.0
/*108 */ 		case CC_VS:                                                           // 0.0
/*110 */ 			cris_evaluate_flags(dc);                                             // 0.0
/*112 */ 			tcg_gen_andi_tl(cc, cpu_PR[PR_CCS], V_FLAG);                         // 0.0
/*114 */ 			break;                                                               // 0.0
/*116 */ 		case CC_VC:                                                           // 0.0
/*118 */ 			cris_evaluate_flags(dc);                                             // 0.0
/*120 */ 			tcg_gen_xori_tl(cc, cpu_PR[PR_CCS],                                  // 0.0
/*122 */ 					V_FLAG);                                                           // 0.0
/*124 */ 			tcg_gen_andi_tl(cc, cc, V_FLAG);                                     // 0.0
/*126 */ 			break;                                                               // 0.0
/*128 */ 		case CC_PL:                                                           // 0.0
/*130 */ 			if (arith_opt || move_opt) {                                         // 0.0
/*132 */ 				int bits = 31;                                                      // 0.0
/*136 */ 				if (dc->cc_size == 1)                                               // 0.0
/*138 */ 					bits = 7;                                                          // 0.0
/*140 */ 				else if (dc->cc_size == 2)                                          // 0.0
/*142 */ 					bits = 15;	                                                        // 0.0
/*146 */ 				tcg_gen_shri_tl(cc, cc_result, bits);                               // 0.0
/*148 */ 				tcg_gen_xori_tl(cc, cc, 1);                                         // 0.0
/*150 */ 			} else {                                                             // 0.0
/*152 */ 				cris_evaluate_flags(dc);                                            // 0.0
/*154 */ 				tcg_gen_xori_tl(cc, cpu_PR[PR_CCS],                                 // 0.0
/*156 */ 						N_FLAG);                                                          // 0.0
/*158 */ 				tcg_gen_andi_tl(cc, cc, N_FLAG);                                    // 0.0
/*160 */ 			}                                                                    // 0.0
/*162 */ 			break;                                                               // 0.0
/*164 */ 		case CC_MI:                                                           // 0.0
/*166 */ 			if (arith_opt || move_opt) {                                         // 0.0
/*168 */ 				int bits = 31;                                                      // 0.0
/*172 */ 				if (dc->cc_size == 1)                                               // 0.0
/*174 */ 					bits = 7;                                                          // 0.0
/*176 */ 				else if (dc->cc_size == 2)                                          // 0.0
/*178 */ 					bits = 15;	                                                        // 0.0
/*182 */ 				tcg_gen_shri_tl(cc, cc_result, 31);                                 // 0.0
/*184 */ 			}                                                                    // 0.0
/*186 */ 			else {                                                               // 0.0
/*188 */ 				cris_evaluate_flags(dc);                                            // 0.0
/*190 */ 				tcg_gen_andi_tl(cc, cpu_PR[PR_CCS],                                 // 0.0
/*192 */ 						N_FLAG);                                                          // 0.0
/*194 */ 			}                                                                    // 0.0
/*196 */ 			break;                                                               // 0.0
/*198 */ 		case CC_LS:                                                           // 0.0
/*200 */ 			cris_evaluate_flags(dc);                                             // 0.0
/*202 */ 			tcg_gen_andi_tl(cc, cpu_PR[PR_CCS],                                  // 0.0
/*204 */ 					C_FLAG | Z_FLAG);                                                  // 0.0
/*206 */ 			break;                                                               // 0.0
/*208 */ 		case CC_HI:                                                           // 0.0
/*210 */ 			cris_evaluate_flags(dc);                                             // 0.0
/*212 */ 			{                                                                    // 0.0
/*214 */ 				TCGv tmp;                                                           // 0.0
/*218 */ 				tmp = tcg_temp_new(TCG_TYPE_TL);                                    // 0.0
/*220 */ 				tcg_gen_xori_tl(tmp, cpu_PR[PR_CCS],                                // 0.0
/*222 */ 						C_FLAG | Z_FLAG);                                                 // 0.0
/*224 */ 				/* Overlay the C flag on top of the Z.  */                          // 0.0
/*226 */ 				tcg_gen_shli_tl(cc, tmp, 2);                                        // 0.0
/*228 */ 				tcg_gen_and_tl(cc, tmp, cc);                                        // 0.0
/*230 */ 				tcg_gen_andi_tl(cc, cc, Z_FLAG);                                    // 0.0
/*234 */ 				tcg_temp_free(tmp);                                                 // 0.0
/*236 */ 			}                                                                    // 0.0
/*238 */ 			break;                                                               // 0.0
/*240 */ 		case CC_GE:                                                           // 0.0
/*242 */ 			cris_evaluate_flags(dc);                                             // 0.0
/*244 */ 			/* Overlay the V flag on top of the N.  */                           // 0.0
/*246 */ 			tcg_gen_shli_tl(cc, cpu_PR[PR_CCS], 2);                              // 0.0
/*248 */ 			tcg_gen_xor_tl(cc,                                                   // 0.0
/*250 */ 				       cpu_PR[PR_CCS], cc);                                         // 0.0
/*252 */ 			tcg_gen_andi_tl(cc, cc, N_FLAG);                                     // 0.0
/*254 */ 			tcg_gen_xori_tl(cc, cc, N_FLAG);                                     // 0.0
/*256 */ 			break;                                                               // 0.0
/*258 */ 		case CC_LT:                                                           // 0.0
/*260 */ 			cris_evaluate_flags(dc);                                             // 0.0
/*262 */ 			/* Overlay the V flag on top of the N.  */                           // 0.0
/*264 */ 			tcg_gen_shli_tl(cc, cpu_PR[PR_CCS], 2);                              // 0.0
/*266 */ 			tcg_gen_xor_tl(cc,                                                   // 0.0
/*268 */ 				       cpu_PR[PR_CCS], cc);                                         // 0.0
/*270 */ 			tcg_gen_andi_tl(cc, cc, N_FLAG);                                     // 0.0
/*272 */ 			break;                                                               // 0.0
/*274 */ 		case CC_GT:                                                           // 0.0
/*276 */ 			cris_evaluate_flags(dc);                                             // 0.0
/*278 */ 			{                                                                    // 0.0
/*280 */ 				TCGv n, z;                                                          // 0.0
/*284 */ 				n = tcg_temp_new(TCG_TYPE_TL);                                      // 0.0
/*286 */ 				z = tcg_temp_new(TCG_TYPE_TL);                                      // 0.0
/*290 */ 				/* To avoid a shift we overlay everything on                        // 0.0
/*292 */ 				   the V flag.  */                                                  // 0.0
/*294 */ 				tcg_gen_shri_tl(n, cpu_PR[PR_CCS], 2);                              // 0.0
/*296 */ 				tcg_gen_shri_tl(z, cpu_PR[PR_CCS], 1);                              // 0.0
/*298 */ 				/* invert Z.  */                                                    // 0.0
/*300 */ 				tcg_gen_xori_tl(z, z, 2);                                           // 0.0
/*304 */ 				tcg_gen_xor_tl(n, n, cpu_PR[PR_CCS]);                               // 0.0
/*306 */ 				tcg_gen_xori_tl(n, n, 2);                                           // 0.0
/*308 */ 				tcg_gen_and_tl(cc, z, n);                                           // 0.0
/*310 */ 				tcg_gen_andi_tl(cc, cc, 2);                                         // 0.0
/*314 */ 				tcg_temp_free(n);                                                   // 0.0
/*316 */ 				tcg_temp_free(z);                                                   // 0.0
/*318 */ 			}                                                                    // 0.0
/*320 */ 			break;                                                               // 0.0
/*322 */ 		case CC_LE:                                                           // 0.0
/*324 */ 			cris_evaluate_flags(dc);                                             // 0.0
/*326 */ 			{                                                                    // 0.0
/*328 */ 				TCGv n, z;                                                          // 0.0
/*332 */ 				n = tcg_temp_new(TCG_TYPE_TL);                                      // 0.0
/*334 */ 				z = tcg_temp_new(TCG_TYPE_TL);                                      // 0.0
/*338 */ 				/* To avoid a shift we overlay everything on                        // 0.0
/*340 */ 				   the V flag.  */                                                  // 0.0
/*342 */ 				tcg_gen_shri_tl(n, cpu_PR[PR_CCS], 2);                              // 0.0
/*344 */ 				tcg_gen_shri_tl(z, cpu_PR[PR_CCS], 1);                              // 0.0
/*348 */ 				tcg_gen_xor_tl(n, n, cpu_PR[PR_CCS]);                               // 0.0
/*350 */ 				tcg_gen_or_tl(cc, z, n);                                            // 0.0
/*352 */ 				tcg_gen_andi_tl(cc, cc, 2);                                         // 0.0
/*356 */ 				tcg_temp_free(n);                                                   // 0.0
/*358 */ 				tcg_temp_free(z);                                                   // 0.0
/*360 */ 			}                                                                    // 0.0
/*362 */ 			break;                                                               // 0.0
/*364 */ 		case CC_P:                                                            // 0.0
/*366 */ 			cris_evaluate_flags(dc);                                             // 0.0
/*368 */ 			tcg_gen_andi_tl(cc, cpu_PR[PR_CCS], P_FLAG);                         // 0.0
/*370 */ 			break;                                                               // 0.0
/*372 */ 		case CC_A:                                                            // 0.0
/*374 */ 			tcg_gen_movi_tl(cc, 1);                                              // 0.0
/*376 */ 			break;                                                               // 0.0
/*378 */ 		default:                                                              // 0.0
/*380 */ 			BUG();                                                               // 0.0
/*382 */ 			break;                                                               // 0.0
/*384 */ 	};                                                                     // 0.0
/*386 */ }                                                                       // 0.0
