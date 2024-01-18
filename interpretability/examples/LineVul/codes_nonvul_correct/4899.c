// commit message qemu@a7812ae412 (target=0, prob=0.011987609, correct=True): TCG variable type checking.
/*0  */ static unsigned int dec_addi_r(DisasContext *dc)                // (5) 0.07729
/*2  */ {                                                               // (10) 0.004831
/*4  */ 	TCGv t0;                                                       // (8) 0.03382
/*6  */ 	DIS(fprintf (logfile, "addi.%c $r%u, $r%u\n",                  // (3) 0.1304
/*8  */ 		    memsize_char(memsize_zz(dc)), dc->op2, dc->op1));         // (2) 0.1353
/*10 */ 	cris_cc_mask(dc, 0);                                           // (6) 0.05797
/*12 */ 	t0 = tcg_temp_new(TCG_TYPE_TL);                                // (4) 0.08696
/*14 */ 	tcg_gen_shl_tl(t0, cpu_R[dc->op2], tcg_const_tl(dc->zzsize));  // (0) 0.1691
/*16 */ 	tcg_gen_add_tl(cpu_R[dc->op1], cpu_R[dc->op1], t0);            // (1) 0.1498
/*18 */ 	tcg_temp_free(t0);                                             // (7) 0.05314
/*20 */ 	return 2;                                                      // (9) 0.01932
/*22 */ }                                                               // (11) 0.004831
