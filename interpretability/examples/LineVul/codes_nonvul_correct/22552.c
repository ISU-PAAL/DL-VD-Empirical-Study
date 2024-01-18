// commit message qemu@a7812ae412 (target=0, prob=0.0067189275, correct=True): TCG variable type checking.
/*0  */ static unsigned int dec_movu_r(DisasContext *dc)                   // (4) 0.07456
/*2  */ {                                                                  // (12) 0.004386
/*4  */ 	TCGv t0;                                                          // (10) 0.0307
/*6  */ 	int size = memsize_z(dc);                                         // (8) 0.04825
/*8  */ 	DIS(fprintf (logfile, "movu.%c $r%u, $r%u\n",                     // (1) 0.1228
/*10 */ 		    memsize_char(size),                                          // (7) 0.05263
/*12 */ 		    dc->op1, dc->op2));                                          // (6) 0.06579
/*16 */ 	cris_cc_mask(dc, CC_MASK_NZ);                                     // (5) 0.07456
/*18 */ 	t0 = tcg_temp_new(TCG_TYPE_TL);                                   // (3) 0.07895
/*20 */ 	dec_prep_move_r(dc, dc->op1, dc->op2, size, 0, t0);               // (2) 0.1228
/*22 */ 	cris_alu(dc, CC_OP_MOVE, cpu_R[dc->op2], cpu_R[dc->op2], t0, 4);  // (0) 0.1711
/*24 */ 	tcg_temp_free(t0);                                                // (9) 0.04825
/*26 */ 	return 2;                                                         // (11) 0.01754
/*28 */ }                                                                  // (13) 0.004386
