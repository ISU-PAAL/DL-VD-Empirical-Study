// commit message qemu@a7812ae412 (target=0, prob=0.015338217, correct=True): TCG variable type checking.
/*0  */ static unsigned int dec_move_mr(DisasContext *dc)        // (11) 0.03659
/*2  */ {                                                        // (25) 0.002439
/*4  */ 	int memsize = memsize_zz(dc);                           // (14) 0.02927
/*6  */ 	int insn_len;                                           // (20) 0.01707
/*8  */ 	DIS(fprintf (logfile, "move.%c [$r%u%s, $r%u\n",        // (2) 0.07073
/*10 */ 		    memsize_char(memsize),                             // (12) 0.03415
/*12 */ 		    dc->op1, dc->postinc ? "+]" : "]",                 // (5) 0.05122
/*14 */ 		    dc->op2));                                         // (17) 0.02439
/*18 */ 	if (memsize == 4) {                                     // (18) 0.02439
/*20 */ 		insn_len = dec_prep_move_m(dc, 0, 4, cpu_R[dc->op2]);  // (0) 0.07317
/*22 */ 		cris_cc_mask(dc, CC_MASK_NZ);                          // (8) 0.0439
/*24 */ 		cris_update_cc_op(dc, CC_OP_MOVE, 4);                  // (4) 0.05366
/*26 */ 		cris_update_cc_x(dc);                                  // (13) 0.03171
/*28 */ 		cris_update_result(dc, cpu_R[dc->op2]);                // (6) 0.04878
/*30 */ 	}                                                       // (23) 0.004878
/*32 */ 	else {                                                  // (22) 0.007317
/*34 */ 		TCGv t0;                                               // (19) 0.01951
/*38 */ 		t0 = tcg_temp_new(TCG_TYPE_TL);                        // (7) 0.04634
/*40 */ 		insn_len = dec_prep_move_m(dc, 0, memsize, t0);        // (3) 0.06098
/*42 */ 		cris_cc_mask(dc, CC_MASK_NZ);                          // (9) 0.0439
/*44 */ 		cris_alu(dc, CC_OP_MOVE,                               // (10) 0.04146
/*46 */ 			    cpu_R[dc->op2], cpu_R[dc->op2], t0, memsize);     // (1) 0.07317
/*48 */ 		tcg_temp_free(t0);                                     // (15) 0.02927
/*50 */ 	}                                                       // (24) 0.004878
/*52 */ 	do_postinc(dc, memsize);                                // (16) 0.02683
/*54 */ 	return insn_len;                                        // (21) 0.01707
/*56 */ }                                                        // (26) 0.002439
