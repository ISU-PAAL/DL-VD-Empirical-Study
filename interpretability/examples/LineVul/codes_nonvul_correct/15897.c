// commit message qemu@a7812ae412 (target=0, prob=0.007937078, correct=True): TCG variable type checking.
/*0  */ static unsigned int dec_adds_r(DisasContext *dc)  // (5) 0.06667
/*2  */ {                                                 // (14) 0.004167
/*4  */ 	TCGv t0;                                         // (12) 0.02917
/*6  */ 	int size = memsize_z(dc);                        // (10) 0.04583
/*8  */ 	DIS(fprintf (logfile, "adds.%c $r%u, $r%u\n",    // (1) 0.1125
/*10 */ 		    memsize_char(size),                         // (9) 0.05
/*12 */ 		    dc->op1, dc->op2));                         // (6) 0.0625
/*16 */ 	cris_cc_mask(dc, CC_MASK_NZVC);                  // (3) 0.075
/*18 */ 	t0 = tcg_temp_new(TCG_TYPE_TL);                  // (4) 0.075
/*20 */ 	/* Size can only be qi or hi.  */                // (8) 0.05417
/*22 */ 	t_gen_sext(t0, cpu_R[dc->op1], size);            // (2) 0.09167
/*24 */ 	cris_alu(dc, CC_OP_ADD,                          // (7) 0.0625
/*26 */ 		    cpu_R[dc->op2], cpu_R[dc->op2], t0, 4);     // (0) 0.1167
/*28 */ 	tcg_temp_free(t0);                               // (11) 0.04583
/*30 */ 	return 2;                                        // (13) 0.01667
/*32 */ }                                                 // (15) 0.004167
