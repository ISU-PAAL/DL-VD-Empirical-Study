// commit message qemu@86865c5ff1 (target=1, prob=0.4763812, correct=False): target-sh4: fix fpu disabled/illegal exception
/*0    */ static void _decode_opc(DisasContext * ctx)                                                                     // (17) 0.03125
/*2    */ {                                                                                                               // (26) 0.001953
/*4    */     /* This code tries to make movcal emulation sufficiently                                                    // (20) 0.02539
/*6    */        accurate for Linux purposes.  This instruction writes                                                    // (19) 0.0293
/*8    */        memory, and prior to that, always allocates a cache line.                                                // (9) 0.03906
/*10   */        It is used in two contexts:                                                                              // (22) 0.02539
/*12   */        - in memcpy, where data is copied in blocks, the first write                                             // (7) 0.04297
/*14   */        of to a block uses movca.l for performance.                                                              // (13) 0.03516
/*16   */        - in arch/sh/mm/cache-sh4.c, movcal.l + ocbi combination is used                                         // (0) 0.0625
/*18   */        to flush the cache. Here, the data written by movcal.l is never                                          // (4) 0.04492
/*20   */        written to memory, and the data written is just bogus.                                                   // (14) 0.03516
/*24   */        To simulate this, we simulate movcal.l, we store the value to memory,                                    // (2) 0.04687
/*26   */        but we also remember the previous content. If we see ocbi, we check                                      // (5) 0.04492
/*28   */        if movcal.l for that address was done previously. If so, the write should                                // (3) 0.04687
/*30   */        not have hit the memory, so we restore the previous content.                                             // (10) 0.03711
/*32   */        When we see an instruction that is neither movca.l                                                       // (11) 0.03516
/*34   */        nor ocbi, the previous content is discarded.                                                             // (15) 0.0332
/*38   */        To optimize, we only try to flush stores when we're at the start of                                      // (6) 0.04297
/*40   */        TB, or if we already saw movca.l in this TB and did not flush stores                                     // (1) 0.04883
/*42   */        yet.  */                                                                                                 // (23) 0.01953
/*44   */     if (ctx->has_movcal)                                                                                        // (21) 0.02539
/*46   */ 	{                                                                                                              // (25) 0.003906
/*48   */ 	  int opcode = ctx->opcode & 0xf0ff;                                                                           // (16) 0.0332
/*50   */ 	  if (opcode != 0x0093 /* ocbi */                                                                              // (18) 0.03125
/*52   */ 	      && opcode != 0x00c3 /* movca.l */)                                                                       // (8) 0.04297
/*54   */ 	      {                                                                                                        // (24) 0.01367
/*56   */ 		  gen_helper_discard_movcal_backup ();                                                                        // (12) 0.03516
/*58   */ 		  ctx->has_movcal = 0;                                                                                        // 0.0
/*60   */ 	      }                                                                                                        // 0.0
/*62   */ 	}                                                                                                              // 0.0
/*66   */ #if 0                                                                                                           // 0.0
/*68   */     fprintf(stderr, "Translating opcode 0x%04x\n", ctx->opcode);                                                // 0.0
/*70   */ #endif                                                                                                          // 0.0
/*74   */     switch (ctx->opcode) {                                                                                      // 0.0
/*76   */     case 0x0019:		/* div0u */                                                                                   // 0.0
/*78   */ 	tcg_gen_andi_i32(cpu_sr, cpu_sr, ~(SR_M | SR_Q | SR_T));                                                       // 0.0
/*80   */ 	return;                                                                                                        // 0.0
/*82   */     case 0x000b:		/* rts */                                                                                     // 0.0
/*84   */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*86   */ 	tcg_gen_mov_i32(cpu_delayed_pc, cpu_pr);                                                                       // 0.0
/*88   */ 	ctx->flags |= DELAY_SLOT;                                                                                      // 0.0
/*90   */ 	ctx->delayed_pc = (uint32_t) - 1;                                                                              // 0.0
/*92   */ 	return;                                                                                                        // 0.0
/*94   */     case 0x0028:		/* clrmac */                                                                                  // 0.0
/*96   */ 	tcg_gen_movi_i32(cpu_mach, 0);                                                                                 // 0.0
/*98   */ 	tcg_gen_movi_i32(cpu_macl, 0);                                                                                 // 0.0
/*100  */ 	return;                                                                                                        // 0.0
/*102  */     case 0x0048:		/* clrs */                                                                                    // 0.0
/*104  */ 	tcg_gen_andi_i32(cpu_sr, cpu_sr, ~SR_S);                                                                       // 0.0
/*106  */ 	return;                                                                                                        // 0.0
/*108  */     case 0x0008:		/* clrt */                                                                                    // 0.0
/*110  */ 	gen_clr_t();                                                                                                   // 0.0
/*112  */ 	return;                                                                                                        // 0.0
/*114  */     case 0x0038:		/* ldtlb */                                                                                   // 0.0
/*116  */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*118  */ 	gen_helper_ldtlb();                                                                                            // 0.0
/*120  */ 	return;                                                                                                        // 0.0
/*122  */     case 0x002b:		/* rte */                                                                                     // 0.0
/*124  */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*126  */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*128  */ 	tcg_gen_mov_i32(cpu_sr, cpu_ssr);                                                                              // 0.0
/*130  */ 	tcg_gen_mov_i32(cpu_delayed_pc, cpu_spc);                                                                      // 0.0
/*132  */ 	ctx->flags |= DELAY_SLOT;                                                                                      // 0.0
/*134  */ 	ctx->delayed_pc = (uint32_t) - 1;                                                                              // 0.0
/*136  */ 	return;                                                                                                        // 0.0
/*138  */     case 0x0058:		/* sets */                                                                                    // 0.0
/*140  */ 	tcg_gen_ori_i32(cpu_sr, cpu_sr, SR_S);                                                                         // 0.0
/*142  */ 	return;                                                                                                        // 0.0
/*144  */     case 0x0018:		/* sett */                                                                                    // 0.0
/*146  */ 	gen_set_t();                                                                                                   // 0.0
/*148  */ 	return;                                                                                                        // 0.0
/*150  */     case 0xfbfd:		/* frchg */                                                                                   // 0.0
/*152  */ 	tcg_gen_xori_i32(cpu_fpscr, cpu_fpscr, FPSCR_FR);                                                              // 0.0
/*154  */ 	ctx->bstate = BS_STOP;                                                                                         // 0.0
/*156  */ 	return;                                                                                                        // 0.0
/*158  */     case 0xf3fd:		/* fschg */                                                                                   // 0.0
/*160  */ 	tcg_gen_xori_i32(cpu_fpscr, cpu_fpscr, FPSCR_SZ);                                                              // 0.0
/*162  */ 	ctx->bstate = BS_STOP;                                                                                         // 0.0
/*164  */ 	return;                                                                                                        // 0.0
/*166  */     case 0x0009:		/* nop */                                                                                     // 0.0
/*168  */ 	return;                                                                                                        // 0.0
/*170  */     case 0x001b:		/* sleep */                                                                                   // 0.0
/*172  */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*174  */ 	gen_helper_sleep(tcg_const_i32(ctx->pc + 2));                                                                  // 0.0
/*176  */ 	return;                                                                                                        // 0.0
/*178  */     }                                                                                                           // 0.0
/*182  */     switch (ctx->opcode & 0xf000) {                                                                             // 0.0
/*184  */     case 0x1000:		/* mov.l Rm,@(disp,Rn) */                                                                     // 0.0
/*186  */ 	{                                                                                                              // 0.0
/*188  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*190  */ 	    tcg_gen_addi_i32(addr, REG(B11_8), B3_0 * 4);                                                              // 0.0
/*192  */ 	    tcg_gen_qemu_st32(REG(B7_4), addr, ctx->memidx);                                                           // 0.0
/*194  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*196  */ 	}                                                                                                              // 0.0
/*198  */ 	return;                                                                                                        // 0.0
/*200  */     case 0x5000:		/* mov.l @(disp,Rm),Rn */                                                                     // 0.0
/*202  */ 	{                                                                                                              // 0.0
/*204  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*206  */ 	    tcg_gen_addi_i32(addr, REG(B7_4), B3_0 * 4);                                                               // 0.0
/*208  */ 	    tcg_gen_qemu_ld32s(REG(B11_8), addr, ctx->memidx);                                                         // 0.0
/*210  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*212  */ 	}                                                                                                              // 0.0
/*214  */ 	return;                                                                                                        // 0.0
/*216  */     case 0xe000:		/* mov #imm,Rn */                                                                             // 0.0
/*218  */ 	tcg_gen_movi_i32(REG(B11_8), B7_0s);                                                                           // 0.0
/*220  */ 	return;                                                                                                        // 0.0
/*222  */     case 0x9000:		/* mov.w @(disp,PC),Rn */                                                                     // 0.0
/*224  */ 	{                                                                                                              // 0.0
/*226  */ 	    TCGv addr = tcg_const_i32(ctx->pc + 4 + B7_0 * 2);                                                         // 0.0
/*228  */ 	    tcg_gen_qemu_ld16s(REG(B11_8), addr, ctx->memidx);                                                         // 0.0
/*230  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*232  */ 	}                                                                                                              // 0.0
/*234  */ 	return;                                                                                                        // 0.0
/*236  */     case 0xd000:		/* mov.l @(disp,PC),Rn */                                                                     // 0.0
/*238  */ 	{                                                                                                              // 0.0
/*240  */ 	    TCGv addr = tcg_const_i32((ctx->pc + 4 + B7_0 * 4) & ~3);                                                  // 0.0
/*242  */ 	    tcg_gen_qemu_ld32s(REG(B11_8), addr, ctx->memidx);                                                         // 0.0
/*244  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*246  */ 	}                                                                                                              // 0.0
/*248  */ 	return;                                                                                                        // 0.0
/*250  */     case 0x7000:		/* add #imm,Rn */                                                                             // 0.0
/*252  */ 	tcg_gen_addi_i32(REG(B11_8), REG(B11_8), B7_0s);                                                               // 0.0
/*254  */ 	return;                                                                                                        // 0.0
/*256  */     case 0xa000:		/* bra disp */                                                                                // 0.0
/*258  */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*260  */ 	ctx->delayed_pc = ctx->pc + 4 + B11_0s * 2;                                                                    // 0.0
/*262  */ 	tcg_gen_movi_i32(cpu_delayed_pc, ctx->delayed_pc);                                                             // 0.0
/*264  */ 	ctx->flags |= DELAY_SLOT;                                                                                      // 0.0
/*266  */ 	return;                                                                                                        // 0.0
/*268  */     case 0xb000:		/* bsr disp */                                                                                // 0.0
/*270  */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*272  */ 	tcg_gen_movi_i32(cpu_pr, ctx->pc + 4);                                                                         // 0.0
/*274  */ 	ctx->delayed_pc = ctx->pc + 4 + B11_0s * 2;                                                                    // 0.0
/*276  */ 	tcg_gen_movi_i32(cpu_delayed_pc, ctx->delayed_pc);                                                             // 0.0
/*278  */ 	ctx->flags |= DELAY_SLOT;                                                                                      // 0.0
/*280  */ 	return;                                                                                                        // 0.0
/*282  */     }                                                                                                           // 0.0
/*286  */     switch (ctx->opcode & 0xf00f) {                                                                             // 0.0
/*288  */     case 0x6003:		/* mov Rm,Rn */                                                                               // 0.0
/*290  */ 	tcg_gen_mov_i32(REG(B11_8), REG(B7_4));                                                                        // 0.0
/*292  */ 	return;                                                                                                        // 0.0
/*294  */     case 0x2000:		/* mov.b Rm,@Rn */                                                                            // 0.0
/*296  */ 	tcg_gen_qemu_st8(REG(B7_4), REG(B11_8), ctx->memidx);                                                          // 0.0
/*298  */ 	return;                                                                                                        // 0.0
/*300  */     case 0x2001:		/* mov.w Rm,@Rn */                                                                            // 0.0
/*302  */ 	tcg_gen_qemu_st16(REG(B7_4), REG(B11_8), ctx->memidx);                                                         // 0.0
/*304  */ 	return;                                                                                                        // 0.0
/*306  */     case 0x2002:		/* mov.l Rm,@Rn */                                                                            // 0.0
/*308  */ 	tcg_gen_qemu_st32(REG(B7_4), REG(B11_8), ctx->memidx);                                                         // 0.0
/*310  */ 	return;                                                                                                        // 0.0
/*312  */     case 0x6000:		/* mov.b @Rm,Rn */                                                                            // 0.0
/*314  */ 	tcg_gen_qemu_ld8s(REG(B11_8), REG(B7_4), ctx->memidx);                                                         // 0.0
/*316  */ 	return;                                                                                                        // 0.0
/*318  */     case 0x6001:		/* mov.w @Rm,Rn */                                                                            // 0.0
/*320  */ 	tcg_gen_qemu_ld16s(REG(B11_8), REG(B7_4), ctx->memidx);                                                        // 0.0
/*322  */ 	return;                                                                                                        // 0.0
/*324  */     case 0x6002:		/* mov.l @Rm,Rn */                                                                            // 0.0
/*326  */ 	tcg_gen_qemu_ld32s(REG(B11_8), REG(B7_4), ctx->memidx);                                                        // 0.0
/*328  */ 	return;                                                                                                        // 0.0
/*330  */     case 0x2004:		/* mov.b Rm,@-Rn */                                                                           // 0.0
/*332  */ 	{                                                                                                              // 0.0
/*334  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*336  */ 	    tcg_gen_subi_i32(addr, REG(B11_8), 1);                                                                     // 0.0
/*338  */ 	    tcg_gen_qemu_st8(REG(B7_4), addr, ctx->memidx);	/* might cause re-execution */                             // 0.0
/*340  */ 	    tcg_gen_mov_i32(REG(B11_8), addr);			/* modify register status */                                          // 0.0
/*342  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*344  */ 	}                                                                                                              // 0.0
/*346  */ 	return;                                                                                                        // 0.0
/*348  */     case 0x2005:		/* mov.w Rm,@-Rn */                                                                           // 0.0
/*350  */ 	{                                                                                                              // 0.0
/*352  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*354  */ 	    tcg_gen_subi_i32(addr, REG(B11_8), 2);                                                                     // 0.0
/*356  */ 	    tcg_gen_qemu_st16(REG(B7_4), addr, ctx->memidx);                                                           // 0.0
/*358  */ 	    tcg_gen_mov_i32(REG(B11_8), addr);                                                                         // 0.0
/*360  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*362  */ 	}                                                                                                              // 0.0
/*364  */ 	return;                                                                                                        // 0.0
/*366  */     case 0x2006:		/* mov.l Rm,@-Rn */                                                                           // 0.0
/*368  */ 	{                                                                                                              // 0.0
/*370  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*372  */ 	    tcg_gen_subi_i32(addr, REG(B11_8), 4);                                                                     // 0.0
/*374  */ 	    tcg_gen_qemu_st32(REG(B7_4), addr, ctx->memidx);                                                           // 0.0
/*376  */ 	    tcg_gen_mov_i32(REG(B11_8), addr);                                                                         // 0.0
/*378  */ 	}                                                                                                              // 0.0
/*380  */ 	return;                                                                                                        // 0.0
/*382  */     case 0x6004:		/* mov.b @Rm+,Rn */                                                                           // 0.0
/*384  */ 	tcg_gen_qemu_ld8s(REG(B11_8), REG(B7_4), ctx->memidx);                                                         // 0.0
/*386  */ 	if ( B11_8 != B7_4 )                                                                                           // 0.0
/*388  */ 		tcg_gen_addi_i32(REG(B7_4), REG(B7_4), 1);                                                                    // 0.0
/*390  */ 	return;                                                                                                        // 0.0
/*392  */     case 0x6005:		/* mov.w @Rm+,Rn */                                                                           // 0.0
/*394  */ 	tcg_gen_qemu_ld16s(REG(B11_8), REG(B7_4), ctx->memidx);                                                        // 0.0
/*396  */ 	if ( B11_8 != B7_4 )                                                                                           // 0.0
/*398  */ 		tcg_gen_addi_i32(REG(B7_4), REG(B7_4), 2);                                                                    // 0.0
/*400  */ 	return;                                                                                                        // 0.0
/*402  */     case 0x6006:		/* mov.l @Rm+,Rn */                                                                           // 0.0
/*404  */ 	tcg_gen_qemu_ld32s(REG(B11_8), REG(B7_4), ctx->memidx);                                                        // 0.0
/*406  */ 	if ( B11_8 != B7_4 )                                                                                           // 0.0
/*408  */ 		tcg_gen_addi_i32(REG(B7_4), REG(B7_4), 4);                                                                    // 0.0
/*410  */ 	return;                                                                                                        // 0.0
/*412  */     case 0x0004:		/* mov.b Rm,@(R0,Rn) */                                                                       // 0.0
/*414  */ 	{                                                                                                              // 0.0
/*416  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*418  */ 	    tcg_gen_add_i32(addr, REG(B11_8), REG(0));                                                                 // 0.0
/*420  */ 	    tcg_gen_qemu_st8(REG(B7_4), addr, ctx->memidx);                                                            // 0.0
/*422  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*424  */ 	}                                                                                                              // 0.0
/*426  */ 	return;                                                                                                        // 0.0
/*428  */     case 0x0005:		/* mov.w Rm,@(R0,Rn) */                                                                       // 0.0
/*430  */ 	{                                                                                                              // 0.0
/*432  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*434  */ 	    tcg_gen_add_i32(addr, REG(B11_8), REG(0));                                                                 // 0.0
/*436  */ 	    tcg_gen_qemu_st16(REG(B7_4), addr, ctx->memidx);                                                           // 0.0
/*438  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*440  */ 	}                                                                                                              // 0.0
/*442  */ 	return;                                                                                                        // 0.0
/*444  */     case 0x0006:		/* mov.l Rm,@(R0,Rn) */                                                                       // 0.0
/*446  */ 	{                                                                                                              // 0.0
/*448  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*450  */ 	    tcg_gen_add_i32(addr, REG(B11_8), REG(0));                                                                 // 0.0
/*452  */ 	    tcg_gen_qemu_st32(REG(B7_4), addr, ctx->memidx);                                                           // 0.0
/*454  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*456  */ 	}                                                                                                              // 0.0
/*458  */ 	return;                                                                                                        // 0.0
/*460  */     case 0x000c:		/* mov.b @(R0,Rm),Rn */                                                                       // 0.0
/*462  */ 	{                                                                                                              // 0.0
/*464  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*466  */ 	    tcg_gen_add_i32(addr, REG(B7_4), REG(0));                                                                  // 0.0
/*468  */ 	    tcg_gen_qemu_ld8s(REG(B11_8), addr, ctx->memidx);                                                          // 0.0
/*470  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*472  */ 	}                                                                                                              // 0.0
/*474  */ 	return;                                                                                                        // 0.0
/*476  */     case 0x000d:		/* mov.w @(R0,Rm),Rn */                                                                       // 0.0
/*478  */ 	{                                                                                                              // 0.0
/*480  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*482  */ 	    tcg_gen_add_i32(addr, REG(B7_4), REG(0));                                                                  // 0.0
/*484  */ 	    tcg_gen_qemu_ld16s(REG(B11_8), addr, ctx->memidx);                                                         // 0.0
/*486  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*488  */ 	}                                                                                                              // 0.0
/*490  */ 	return;                                                                                                        // 0.0
/*492  */     case 0x000e:		/* mov.l @(R0,Rm),Rn */                                                                       // 0.0
/*494  */ 	{                                                                                                              // 0.0
/*496  */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*498  */ 	    tcg_gen_add_i32(addr, REG(B7_4), REG(0));                                                                  // 0.0
/*500  */ 	    tcg_gen_qemu_ld32s(REG(B11_8), addr, ctx->memidx);                                                         // 0.0
/*502  */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*504  */ 	}                                                                                                              // 0.0
/*506  */ 	return;                                                                                                        // 0.0
/*508  */     case 0x6008:		/* swap.b Rm,Rn */                                                                            // 0.0
/*510  */ 	{                                                                                                              // 0.0
/*512  */ 	    TCGv high, low;                                                                                            // 0.0
/*514  */ 	    high = tcg_temp_new();                                                                                     // 0.0
/*516  */ 	    tcg_gen_andi_i32(high, REG(B7_4), 0xffff0000);                                                             // 0.0
/*518  */ 	    low = tcg_temp_new();                                                                                      // 0.0
/*520  */ 	    tcg_gen_ext16u_i32(low, REG(B7_4));                                                                        // 0.0
/*522  */ 	    tcg_gen_bswap16_i32(low, low);                                                                             // 0.0
/*524  */ 	    tcg_gen_or_i32(REG(B11_8), high, low);                                                                     // 0.0
/*526  */ 	    tcg_temp_free(low);                                                                                        // 0.0
/*528  */ 	    tcg_temp_free(high);                                                                                       // 0.0
/*530  */ 	}                                                                                                              // 0.0
/*532  */ 	return;                                                                                                        // 0.0
/*534  */     case 0x6009:		/* swap.w Rm,Rn */                                                                            // 0.0
/*536  */ 	{                                                                                                              // 0.0
/*538  */ 	    TCGv high, low;                                                                                            // 0.0
/*540  */ 	    high = tcg_temp_new();                                                                                     // 0.0
/*542  */ 	    tcg_gen_shli_i32(high, REG(B7_4), 16);                                                                     // 0.0
/*544  */ 	    low = tcg_temp_new();                                                                                      // 0.0
/*546  */ 	    tcg_gen_shri_i32(low, REG(B7_4), 16);                                                                      // 0.0
/*548  */ 	    tcg_gen_ext16u_i32(low, low);                                                                              // 0.0
/*550  */ 	    tcg_gen_or_i32(REG(B11_8), high, low);                                                                     // 0.0
/*552  */ 	    tcg_temp_free(low);                                                                                        // 0.0
/*554  */ 	    tcg_temp_free(high);                                                                                       // 0.0
/*556  */ 	}                                                                                                              // 0.0
/*558  */ 	return;                                                                                                        // 0.0
/*560  */     case 0x200d:		/* xtrct Rm,Rn */                                                                             // 0.0
/*562  */ 	{                                                                                                              // 0.0
/*564  */ 	    TCGv high, low;                                                                                            // 0.0
/*566  */ 	    high = tcg_temp_new();                                                                                     // 0.0
/*568  */ 	    tcg_gen_shli_i32(high, REG(B7_4), 16);                                                                     // 0.0
/*570  */ 	    low = tcg_temp_new();                                                                                      // 0.0
/*572  */ 	    tcg_gen_shri_i32(low, REG(B11_8), 16);                                                                     // 0.0
/*574  */ 	    tcg_gen_ext16u_i32(low, low);                                                                              // 0.0
/*576  */ 	    tcg_gen_or_i32(REG(B11_8), high, low);                                                                     // 0.0
/*578  */ 	    tcg_temp_free(low);                                                                                        // 0.0
/*580  */ 	    tcg_temp_free(high);                                                                                       // 0.0
/*582  */ 	}                                                                                                              // 0.0
/*584  */ 	return;                                                                                                        // 0.0
/*586  */     case 0x300c:		/* add Rm,Rn */                                                                               // 0.0
/*588  */ 	tcg_gen_add_i32(REG(B11_8), REG(B11_8), REG(B7_4));                                                            // 0.0
/*590  */ 	return;                                                                                                        // 0.0
/*592  */     case 0x300e:		/* addc Rm,Rn */                                                                              // 0.0
/*594  */ 	gen_helper_addc(REG(B11_8), REG(B7_4), REG(B11_8));                                                            // 0.0
/*596  */ 	return;                                                                                                        // 0.0
/*598  */     case 0x300f:		/* addv Rm,Rn */                                                                              // 0.0
/*600  */ 	gen_helper_addv(REG(B11_8), REG(B7_4), REG(B11_8));                                                            // 0.0
/*602  */ 	return;                                                                                                        // 0.0
/*604  */     case 0x2009:		/* and Rm,Rn */                                                                               // 0.0
/*606  */ 	tcg_gen_and_i32(REG(B11_8), REG(B11_8), REG(B7_4));                                                            // 0.0
/*608  */ 	return;                                                                                                        // 0.0
/*610  */     case 0x3000:		/* cmp/eq Rm,Rn */                                                                            // 0.0
/*612  */ 	gen_cmp(TCG_COND_EQ, REG(B7_4), REG(B11_8));                                                                   // 0.0
/*614  */ 	return;                                                                                                        // 0.0
/*616  */     case 0x3003:		/* cmp/ge Rm,Rn */                                                                            // 0.0
/*618  */ 	gen_cmp(TCG_COND_GE, REG(B7_4), REG(B11_8));                                                                   // 0.0
/*620  */ 	return;                                                                                                        // 0.0
/*622  */     case 0x3007:		/* cmp/gt Rm,Rn */                                                                            // 0.0
/*624  */ 	gen_cmp(TCG_COND_GT, REG(B7_4), REG(B11_8));                                                                   // 0.0
/*626  */ 	return;                                                                                                        // 0.0
/*628  */     case 0x3006:		/* cmp/hi Rm,Rn */                                                                            // 0.0
/*630  */ 	gen_cmp(TCG_COND_GTU, REG(B7_4), REG(B11_8));                                                                  // 0.0
/*632  */ 	return;                                                                                                        // 0.0
/*634  */     case 0x3002:		/* cmp/hs Rm,Rn */                                                                            // 0.0
/*636  */ 	gen_cmp(TCG_COND_GEU, REG(B7_4), REG(B11_8));                                                                  // 0.0
/*638  */ 	return;                                                                                                        // 0.0
/*640  */     case 0x200c:		/* cmp/str Rm,Rn */                                                                           // 0.0
/*642  */ 	{                                                                                                              // 0.0
/*644  */ 	    int label1 = gen_new_label();                                                                              // 0.0
/*646  */ 	    int label2 = gen_new_label();                                                                              // 0.0
/*648  */ 	    TCGv cmp1 = tcg_temp_local_new();                                                                          // 0.0
/*650  */ 	    TCGv cmp2 = tcg_temp_local_new();                                                                          // 0.0
/*652  */ 	    tcg_gen_xor_i32(cmp1, REG(B7_4), REG(B11_8));                                                              // 0.0
/*654  */ 	    tcg_gen_andi_i32(cmp2, cmp1, 0xff000000);                                                                  // 0.0
/*656  */ 	    tcg_gen_brcondi_i32(TCG_COND_EQ, cmp2, 0, label1);                                                         // 0.0
/*658  */ 	    tcg_gen_andi_i32(cmp2, cmp1, 0x00ff0000);                                                                  // 0.0
/*660  */ 	    tcg_gen_brcondi_i32(TCG_COND_EQ, cmp2, 0, label1);                                                         // 0.0
/*662  */ 	    tcg_gen_andi_i32(cmp2, cmp1, 0x0000ff00);                                                                  // 0.0
/*664  */ 	    tcg_gen_brcondi_i32(TCG_COND_EQ, cmp2, 0, label1);                                                         // 0.0
/*666  */ 	    tcg_gen_andi_i32(cmp2, cmp1, 0x000000ff);                                                                  // 0.0
/*668  */ 	    tcg_gen_brcondi_i32(TCG_COND_EQ, cmp2, 0, label1);                                                         // 0.0
/*670  */ 	    tcg_gen_andi_i32(cpu_sr, cpu_sr, ~SR_T);                                                                   // 0.0
/*672  */ 	    tcg_gen_br(label2);                                                                                        // 0.0
/*674  */ 	    gen_set_label(label1);                                                                                     // 0.0
/*676  */ 	    tcg_gen_ori_i32(cpu_sr, cpu_sr, SR_T);                                                                     // 0.0
/*678  */ 	    gen_set_label(label2);                                                                                     // 0.0
/*680  */ 	    tcg_temp_free(cmp2);                                                                                       // 0.0
/*682  */ 	    tcg_temp_free(cmp1);                                                                                       // 0.0
/*684  */ 	}                                                                                                              // 0.0
/*686  */ 	return;                                                                                                        // 0.0
/*688  */     case 0x2007:		/* div0s Rm,Rn */                                                                             // 0.0
/*690  */ 	{                                                                                                              // 0.0
/*692  */ 	    gen_copy_bit_i32(cpu_sr, 8, REG(B11_8), 31);	/* SR_Q */                                                    // 0.0
/*694  */ 	    gen_copy_bit_i32(cpu_sr, 9, REG(B7_4), 31);		/* SR_M */                                                    // 0.0
/*696  */ 	    TCGv val = tcg_temp_new();                                                                                 // 0.0
/*698  */ 	    tcg_gen_xor_i32(val, REG(B7_4), REG(B11_8));                                                               // 0.0
/*700  */ 	    gen_copy_bit_i32(cpu_sr, 0, val, 31);		/* SR_T */                                                          // 0.0
/*702  */ 	    tcg_temp_free(val);                                                                                        // 0.0
/*704  */ 	}                                                                                                              // 0.0
/*706  */ 	return;                                                                                                        // 0.0
/*708  */     case 0x3004:		/* div1 Rm,Rn */                                                                              // 0.0
/*710  */ 	gen_helper_div1(REG(B11_8), REG(B7_4), REG(B11_8));                                                            // 0.0
/*712  */ 	return;                                                                                                        // 0.0
/*714  */     case 0x300d:		/* dmuls.l Rm,Rn */                                                                           // 0.0
/*716  */ 	{                                                                                                              // 0.0
/*718  */ 	    TCGv_i64 tmp1 = tcg_temp_new_i64();                                                                        // 0.0
/*720  */ 	    TCGv_i64 tmp2 = tcg_temp_new_i64();                                                                        // 0.0
/*724  */ 	    tcg_gen_ext_i32_i64(tmp1, REG(B7_4));                                                                      // 0.0
/*726  */ 	    tcg_gen_ext_i32_i64(tmp2, REG(B11_8));                                                                     // 0.0
/*728  */ 	    tcg_gen_mul_i64(tmp1, tmp1, tmp2);                                                                         // 0.0
/*730  */ 	    tcg_gen_trunc_i64_i32(cpu_macl, tmp1);                                                                     // 0.0
/*732  */ 	    tcg_gen_shri_i64(tmp1, tmp1, 32);                                                                          // 0.0
/*734  */ 	    tcg_gen_trunc_i64_i32(cpu_mach, tmp1);                                                                     // 0.0
/*738  */ 	    tcg_temp_free_i64(tmp2);                                                                                   // 0.0
/*740  */ 	    tcg_temp_free_i64(tmp1);                                                                                   // 0.0
/*742  */ 	}                                                                                                              // 0.0
/*744  */ 	return;                                                                                                        // 0.0
/*746  */     case 0x3005:		/* dmulu.l Rm,Rn */                                                                           // 0.0
/*748  */ 	{                                                                                                              // 0.0
/*750  */ 	    TCGv_i64 tmp1 = tcg_temp_new_i64();                                                                        // 0.0
/*752  */ 	    TCGv_i64 tmp2 = tcg_temp_new_i64();                                                                        // 0.0
/*756  */ 	    tcg_gen_extu_i32_i64(tmp1, REG(B7_4));                                                                     // 0.0
/*758  */ 	    tcg_gen_extu_i32_i64(tmp2, REG(B11_8));                                                                    // 0.0
/*760  */ 	    tcg_gen_mul_i64(tmp1, tmp1, tmp2);                                                                         // 0.0
/*762  */ 	    tcg_gen_trunc_i64_i32(cpu_macl, tmp1);                                                                     // 0.0
/*764  */ 	    tcg_gen_shri_i64(tmp1, tmp1, 32);                                                                          // 0.0
/*766  */ 	    tcg_gen_trunc_i64_i32(cpu_mach, tmp1);                                                                     // 0.0
/*770  */ 	    tcg_temp_free_i64(tmp2);                                                                                   // 0.0
/*772  */ 	    tcg_temp_free_i64(tmp1);                                                                                   // 0.0
/*774  */ 	}                                                                                                              // 0.0
/*776  */ 	return;                                                                                                        // 0.0
/*778  */     case 0x600e:		/* exts.b Rm,Rn */                                                                            // 0.0
/*780  */ 	tcg_gen_ext8s_i32(REG(B11_8), REG(B7_4));                                                                      // 0.0
/*782  */ 	return;                                                                                                        // 0.0
/*784  */     case 0x600f:		/* exts.w Rm,Rn */                                                                            // 0.0
/*786  */ 	tcg_gen_ext16s_i32(REG(B11_8), REG(B7_4));                                                                     // 0.0
/*788  */ 	return;                                                                                                        // 0.0
/*790  */     case 0x600c:		/* extu.b Rm,Rn */                                                                            // 0.0
/*792  */ 	tcg_gen_ext8u_i32(REG(B11_8), REG(B7_4));                                                                      // 0.0
/*794  */ 	return;                                                                                                        // 0.0
/*796  */     case 0x600d:		/* extu.w Rm,Rn */                                                                            // 0.0
/*798  */ 	tcg_gen_ext16u_i32(REG(B11_8), REG(B7_4));                                                                     // 0.0
/*800  */ 	return;                                                                                                        // 0.0
/*802  */     case 0x000f:		/* mac.l @Rm+,@Rn+ */                                                                         // 0.0
/*804  */ 	{                                                                                                              // 0.0
/*806  */ 	    TCGv arg0, arg1;                                                                                           // 0.0
/*808  */ 	    arg0 = tcg_temp_new();                                                                                     // 0.0
/*810  */ 	    tcg_gen_qemu_ld32s(arg0, REG(B7_4), ctx->memidx);                                                          // 0.0
/*812  */ 	    arg1 = tcg_temp_new();                                                                                     // 0.0
/*814  */ 	    tcg_gen_qemu_ld32s(arg1, REG(B11_8), ctx->memidx);                                                         // 0.0
/*816  */ 	    gen_helper_macl(arg0, arg1);                                                                               // 0.0
/*818  */ 	    tcg_temp_free(arg1);                                                                                       // 0.0
/*820  */ 	    tcg_temp_free(arg0);                                                                                       // 0.0
/*822  */ 	    tcg_gen_addi_i32(REG(B7_4), REG(B7_4), 4);                                                                 // 0.0
/*824  */ 	    tcg_gen_addi_i32(REG(B11_8), REG(B11_8), 4);                                                               // 0.0
/*826  */ 	}                                                                                                              // 0.0
/*828  */ 	return;                                                                                                        // 0.0
/*830  */     case 0x400f:		/* mac.w @Rm+,@Rn+ */                                                                         // 0.0
/*832  */ 	{                                                                                                              // 0.0
/*834  */ 	    TCGv arg0, arg1;                                                                                           // 0.0
/*836  */ 	    arg0 = tcg_temp_new();                                                                                     // 0.0
/*838  */ 	    tcg_gen_qemu_ld32s(arg0, REG(B7_4), ctx->memidx);                                                          // 0.0
/*840  */ 	    arg1 = tcg_temp_new();                                                                                     // 0.0
/*842  */ 	    tcg_gen_qemu_ld32s(arg1, REG(B11_8), ctx->memidx);                                                         // 0.0
/*844  */ 	    gen_helper_macw(arg0, arg1);                                                                               // 0.0
/*846  */ 	    tcg_temp_free(arg1);                                                                                       // 0.0
/*848  */ 	    tcg_temp_free(arg0);                                                                                       // 0.0
/*850  */ 	    tcg_gen_addi_i32(REG(B11_8), REG(B11_8), 2);                                                               // 0.0
/*852  */ 	    tcg_gen_addi_i32(REG(B7_4), REG(B7_4), 2);                                                                 // 0.0
/*854  */ 	}                                                                                                              // 0.0
/*856  */ 	return;                                                                                                        // 0.0
/*858  */     case 0x0007:		/* mul.l Rm,Rn */                                                                             // 0.0
/*860  */ 	tcg_gen_mul_i32(cpu_macl, REG(B7_4), REG(B11_8));                                                              // 0.0
/*862  */ 	return;                                                                                                        // 0.0
/*864  */     case 0x200f:		/* muls.w Rm,Rn */                                                                            // 0.0
/*866  */ 	{                                                                                                              // 0.0
/*868  */ 	    TCGv arg0, arg1;                                                                                           // 0.0
/*870  */ 	    arg0 = tcg_temp_new();                                                                                     // 0.0
/*872  */ 	    tcg_gen_ext16s_i32(arg0, REG(B7_4));                                                                       // 0.0
/*874  */ 	    arg1 = tcg_temp_new();                                                                                     // 0.0
/*876  */ 	    tcg_gen_ext16s_i32(arg1, REG(B11_8));                                                                      // 0.0
/*878  */ 	    tcg_gen_mul_i32(cpu_macl, arg0, arg1);                                                                     // 0.0
/*880  */ 	    tcg_temp_free(arg1);                                                                                       // 0.0
/*882  */ 	    tcg_temp_free(arg0);                                                                                       // 0.0
/*884  */ 	}                                                                                                              // 0.0
/*886  */ 	return;                                                                                                        // 0.0
/*888  */     case 0x200e:		/* mulu.w Rm,Rn */                                                                            // 0.0
/*890  */ 	{                                                                                                              // 0.0
/*892  */ 	    TCGv arg0, arg1;                                                                                           // 0.0
/*894  */ 	    arg0 = tcg_temp_new();                                                                                     // 0.0
/*896  */ 	    tcg_gen_ext16u_i32(arg0, REG(B7_4));                                                                       // 0.0
/*898  */ 	    arg1 = tcg_temp_new();                                                                                     // 0.0
/*900  */ 	    tcg_gen_ext16u_i32(arg1, REG(B11_8));                                                                      // 0.0
/*902  */ 	    tcg_gen_mul_i32(cpu_macl, arg0, arg1);                                                                     // 0.0
/*904  */ 	    tcg_temp_free(arg1);                                                                                       // 0.0
/*906  */ 	    tcg_temp_free(arg0);                                                                                       // 0.0
/*908  */ 	}                                                                                                              // 0.0
/*910  */ 	return;                                                                                                        // 0.0
/*912  */     case 0x600b:		/* neg Rm,Rn */                                                                               // 0.0
/*914  */ 	tcg_gen_neg_i32(REG(B11_8), REG(B7_4));                                                                        // 0.0
/*916  */ 	return;                                                                                                        // 0.0
/*918  */     case 0x600a:		/* negc Rm,Rn */                                                                              // 0.0
/*920  */ 	gen_helper_negc(REG(B11_8), REG(B7_4));                                                                        // 0.0
/*922  */ 	return;                                                                                                        // 0.0
/*924  */     case 0x6007:		/* not Rm,Rn */                                                                               // 0.0
/*926  */ 	tcg_gen_not_i32(REG(B11_8), REG(B7_4));                                                                        // 0.0
/*928  */ 	return;                                                                                                        // 0.0
/*930  */     case 0x200b:		/* or Rm,Rn */                                                                                // 0.0
/*932  */ 	tcg_gen_or_i32(REG(B11_8), REG(B11_8), REG(B7_4));                                                             // 0.0
/*934  */ 	return;                                                                                                        // 0.0
/*936  */     case 0x400c:		/* shad Rm,Rn */                                                                              // 0.0
/*938  */ 	{                                                                                                              // 0.0
/*940  */ 	    int label1 = gen_new_label();                                                                              // 0.0
/*942  */ 	    int label2 = gen_new_label();                                                                              // 0.0
/*944  */ 	    int label3 = gen_new_label();                                                                              // 0.0
/*946  */ 	    int label4 = gen_new_label();                                                                              // 0.0
/*948  */ 	    TCGv shift;                                                                                                // 0.0
/*950  */ 	    tcg_gen_brcondi_i32(TCG_COND_LT, REG(B7_4), 0, label1);                                                    // 0.0
/*952  */ 	    /* Rm positive, shift to the left */                                                                       // 0.0
/*954  */             shift = tcg_temp_new();                                                                             // 0.0
/*956  */ 	    tcg_gen_andi_i32(shift, REG(B7_4), 0x1f);                                                                  // 0.0
/*958  */ 	    tcg_gen_shl_i32(REG(B11_8), REG(B11_8), shift);                                                            // 0.0
/*960  */ 	    tcg_temp_free(shift);                                                                                      // 0.0
/*962  */ 	    tcg_gen_br(label4);                                                                                        // 0.0
/*964  */ 	    /* Rm negative, shift to the right */                                                                      // 0.0
/*966  */ 	    gen_set_label(label1);                                                                                     // 0.0
/*968  */             shift = tcg_temp_new();                                                                             // 0.0
/*970  */ 	    tcg_gen_andi_i32(shift, REG(B7_4), 0x1f);                                                                  // 0.0
/*972  */ 	    tcg_gen_brcondi_i32(TCG_COND_EQ, shift, 0, label2);                                                        // 0.0
/*974  */ 	    tcg_gen_not_i32(shift, REG(B7_4));                                                                         // 0.0
/*976  */ 	    tcg_gen_andi_i32(shift, shift, 0x1f);                                                                      // 0.0
/*978  */ 	    tcg_gen_addi_i32(shift, shift, 1);                                                                         // 0.0
/*980  */ 	    tcg_gen_sar_i32(REG(B11_8), REG(B11_8), shift);                                                            // 0.0
/*982  */ 	    tcg_temp_free(shift);                                                                                      // 0.0
/*984  */ 	    tcg_gen_br(label4);                                                                                        // 0.0
/*986  */ 	    /* Rm = -32 */                                                                                             // 0.0
/*988  */ 	    gen_set_label(label2);                                                                                     // 0.0
/*990  */ 	    tcg_gen_brcondi_i32(TCG_COND_LT, REG(B11_8), 0, label3);                                                   // 0.0
/*992  */ 	    tcg_gen_movi_i32(REG(B11_8), 0);                                                                           // 0.0
/*994  */ 	    tcg_gen_br(label4);                                                                                        // 0.0
/*996  */ 	    gen_set_label(label3);                                                                                     // 0.0
/*998  */ 	    tcg_gen_movi_i32(REG(B11_8), 0xffffffff);                                                                  // 0.0
/*1000 */ 	    gen_set_label(label4);                                                                                     // 0.0
/*1002 */ 	}                                                                                                              // 0.0
/*1004 */ 	return;                                                                                                        // 0.0
/*1006 */     case 0x400d:		/* shld Rm,Rn */                                                                              // 0.0
/*1008 */ 	{                                                                                                              // 0.0
/*1010 */ 	    int label1 = gen_new_label();                                                                              // 0.0
/*1012 */ 	    int label2 = gen_new_label();                                                                              // 0.0
/*1014 */ 	    int label3 = gen_new_label();                                                                              // 0.0
/*1016 */ 	    TCGv shift;                                                                                                // 0.0
/*1018 */ 	    tcg_gen_brcondi_i32(TCG_COND_LT, REG(B7_4), 0, label1);                                                    // 0.0
/*1020 */ 	    /* Rm positive, shift to the left */                                                                       // 0.0
/*1022 */             shift = tcg_temp_new();                                                                             // 0.0
/*1024 */ 	    tcg_gen_andi_i32(shift, REG(B7_4), 0x1f);                                                                  // 0.0
/*1026 */ 	    tcg_gen_shl_i32(REG(B11_8), REG(B11_8), shift);                                                            // 0.0
/*1028 */ 	    tcg_temp_free(shift);                                                                                      // 0.0
/*1030 */ 	    tcg_gen_br(label3);                                                                                        // 0.0
/*1032 */ 	    /* Rm negative, shift to the right */                                                                      // 0.0
/*1034 */ 	    gen_set_label(label1);                                                                                     // 0.0
/*1036 */             shift = tcg_temp_new();                                                                             // 0.0
/*1038 */ 	    tcg_gen_andi_i32(shift, REG(B7_4), 0x1f);                                                                  // 0.0
/*1040 */ 	    tcg_gen_brcondi_i32(TCG_COND_EQ, shift, 0, label2);                                                        // 0.0
/*1042 */ 	    tcg_gen_not_i32(shift, REG(B7_4));                                                                         // 0.0
/*1044 */ 	    tcg_gen_andi_i32(shift, shift, 0x1f);                                                                      // 0.0
/*1046 */ 	    tcg_gen_addi_i32(shift, shift, 1);                                                                         // 0.0
/*1048 */ 	    tcg_gen_shr_i32(REG(B11_8), REG(B11_8), shift);                                                            // 0.0
/*1050 */ 	    tcg_temp_free(shift);                                                                                      // 0.0
/*1052 */ 	    tcg_gen_br(label3);                                                                                        // 0.0
/*1054 */ 	    /* Rm = -32 */                                                                                             // 0.0
/*1056 */ 	    gen_set_label(label2);                                                                                     // 0.0
/*1058 */ 	    tcg_gen_movi_i32(REG(B11_8), 0);                                                                           // 0.0
/*1060 */ 	    gen_set_label(label3);                                                                                     // 0.0
/*1062 */ 	}                                                                                                              // 0.0
/*1064 */ 	return;                                                                                                        // 0.0
/*1066 */     case 0x3008:		/* sub Rm,Rn */                                                                               // 0.0
/*1068 */ 	tcg_gen_sub_i32(REG(B11_8), REG(B11_8), REG(B7_4));                                                            // 0.0
/*1070 */ 	return;                                                                                                        // 0.0
/*1072 */     case 0x300a:		/* subc Rm,Rn */                                                                              // 0.0
/*1074 */ 	gen_helper_subc(REG(B11_8), REG(B7_4), REG(B11_8));                                                            // 0.0
/*1076 */ 	return;                                                                                                        // 0.0
/*1078 */     case 0x300b:		/* subv Rm,Rn */                                                                              // 0.0
/*1080 */ 	gen_helper_subv(REG(B11_8), REG(B7_4), REG(B11_8));                                                            // 0.0
/*1082 */ 	return;                                                                                                        // 0.0
/*1084 */     case 0x2008:		/* tst Rm,Rn */                                                                               // 0.0
/*1086 */ 	{                                                                                                              // 0.0
/*1088 */ 	    TCGv val = tcg_temp_new();                                                                                 // 0.0
/*1090 */ 	    tcg_gen_and_i32(val, REG(B7_4), REG(B11_8));                                                               // 0.0
/*1092 */ 	    gen_cmp_imm(TCG_COND_EQ, val, 0);                                                                          // 0.0
/*1094 */ 	    tcg_temp_free(val);                                                                                        // 0.0
/*1096 */ 	}                                                                                                              // 0.0
/*1098 */ 	return;                                                                                                        // 0.0
/*1100 */     case 0x200a:		/* xor Rm,Rn */                                                                               // 0.0
/*1102 */ 	tcg_gen_xor_i32(REG(B11_8), REG(B11_8), REG(B7_4));                                                            // 0.0
/*1104 */ 	return;                                                                                                        // 0.0
/*1106 */     case 0xf00c: /* fmov {F,D,X}Rm,{F,D,X}Rn - FPSCR: Nothing */                                                // 0.0
/*1108 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*1110 */ 	if (ctx->fpscr & FPSCR_SZ) {                                                                                   // 0.0
/*1112 */ 	    TCGv_i64 fp = tcg_temp_new_i64();                                                                          // 0.0
/*1114 */ 	    gen_load_fpr64(fp, XREG(B7_4));                                                                            // 0.0
/*1116 */ 	    gen_store_fpr64(fp, XREG(B11_8));                                                                          // 0.0
/*1118 */ 	    tcg_temp_free_i64(fp);                                                                                     // 0.0
/*1120 */ 	} else {                                                                                                       // 0.0
/*1122 */ 	    tcg_gen_mov_i32(cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B7_4)]);                                            // 0.0
/*1124 */ 	}                                                                                                              // 0.0
/*1126 */ 	return;                                                                                                        // 0.0
/*1128 */     case 0xf00a: /* fmov {F,D,X}Rm,@Rn - FPSCR: Nothing */                                                      // 0.0
/*1130 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*1132 */ 	if (ctx->fpscr & FPSCR_SZ) {                                                                                   // 0.0
/*1134 */ 	    TCGv addr_hi = tcg_temp_new();                                                                             // 0.0
/*1136 */ 	    int fr = XREG(B7_4);                                                                                       // 0.0
/*1138 */ 	    tcg_gen_addi_i32(addr_hi, REG(B11_8), 4);                                                                  // 0.0
/*1140 */ 	    tcg_gen_qemu_st32(cpu_fregs[fr  ], REG(B11_8), ctx->memidx);                                               // 0.0
/*1142 */ 	    tcg_gen_qemu_st32(cpu_fregs[fr+1], addr_hi,	   ctx->memidx);                                               // 0.0
/*1144 */ 	    tcg_temp_free(addr_hi);                                                                                    // 0.0
/*1146 */ 	} else {                                                                                                       // 0.0
/*1148 */ 	    tcg_gen_qemu_st32(cpu_fregs[FREG(B7_4)], REG(B11_8), ctx->memidx);                                         // 0.0
/*1150 */ 	}                                                                                                              // 0.0
/*1152 */ 	return;                                                                                                        // 0.0
/*1154 */     case 0xf008: /* fmov @Rm,{F,D,X}Rn - FPSCR: Nothing */                                                      // 0.0
/*1156 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*1158 */ 	if (ctx->fpscr & FPSCR_SZ) {                                                                                   // 0.0
/*1160 */ 	    TCGv addr_hi = tcg_temp_new();                                                                             // 0.0
/*1162 */ 	    int fr = XREG(B11_8);                                                                                      // 0.0
/*1164 */ 	    tcg_gen_addi_i32(addr_hi, REG(B7_4), 4);                                                                   // 0.0
/*1166 */ 	    tcg_gen_qemu_ld32u(cpu_fregs[fr  ], REG(B7_4), ctx->memidx);                                               // 0.0
/*1168 */ 	    tcg_gen_qemu_ld32u(cpu_fregs[fr+1], addr_hi,   ctx->memidx);                                               // 0.0
/*1170 */ 	    tcg_temp_free(addr_hi);                                                                                    // 0.0
/*1172 */ 	} else {                                                                                                       // 0.0
/*1174 */ 	    tcg_gen_qemu_ld32u(cpu_fregs[FREG(B11_8)], REG(B7_4), ctx->memidx);                                        // 0.0
/*1176 */ 	}                                                                                                              // 0.0
/*1178 */ 	return;                                                                                                        // 0.0
/*1180 */     case 0xf009: /* fmov @Rm+,{F,D,X}Rn - FPSCR: Nothing */                                                     // 0.0
/*1182 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*1184 */ 	if (ctx->fpscr & FPSCR_SZ) {                                                                                   // 0.0
/*1186 */ 	    TCGv addr_hi = tcg_temp_new();                                                                             // 0.0
/*1188 */ 	    int fr = XREG(B11_8);                                                                                      // 0.0
/*1190 */ 	    tcg_gen_addi_i32(addr_hi, REG(B7_4), 4);                                                                   // 0.0
/*1192 */ 	    tcg_gen_qemu_ld32u(cpu_fregs[fr  ], REG(B7_4), ctx->memidx);                                               // 0.0
/*1194 */ 	    tcg_gen_qemu_ld32u(cpu_fregs[fr+1], addr_hi,   ctx->memidx);                                               // 0.0
/*1196 */ 	    tcg_gen_addi_i32(REG(B7_4), REG(B7_4), 8);                                                                 // 0.0
/*1198 */ 	    tcg_temp_free(addr_hi);                                                                                    // 0.0
/*1200 */ 	} else {                                                                                                       // 0.0
/*1202 */ 	    tcg_gen_qemu_ld32u(cpu_fregs[FREG(B11_8)], REG(B7_4), ctx->memidx);                                        // 0.0
/*1204 */ 	    tcg_gen_addi_i32(REG(B7_4), REG(B7_4), 4);                                                                 // 0.0
/*1206 */ 	}                                                                                                              // 0.0
/*1208 */ 	return;                                                                                                        // 0.0
/*1210 */     case 0xf00b: /* fmov {F,D,X}Rm,@-Rn - FPSCR: Nothing */                                                     // 0.0
/*1212 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*1214 */ 	if (ctx->fpscr & FPSCR_SZ) {                                                                                   // 0.0
/*1216 */ 	    TCGv addr = tcg_temp_new_i32();                                                                            // 0.0
/*1218 */ 	    int fr = XREG(B7_4);                                                                                       // 0.0
/*1220 */ 	    tcg_gen_subi_i32(addr, REG(B11_8), 4);                                                                     // 0.0
/*1222 */ 	    tcg_gen_qemu_st32(cpu_fregs[fr+1], addr, ctx->memidx);                                                     // 0.0
/*1224 */ 	    tcg_gen_subi_i32(addr, addr, 4);                                                                           // 0.0
/*1226 */ 	    tcg_gen_qemu_st32(cpu_fregs[fr  ], addr, ctx->memidx);                                                     // 0.0
/*1228 */ 	    tcg_gen_mov_i32(REG(B11_8), addr);                                                                         // 0.0
/*1230 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1232 */ 	} else {                                                                                                       // 0.0
/*1234 */ 	    TCGv addr;                                                                                                 // 0.0
/*1236 */ 	    addr = tcg_temp_new_i32();                                                                                 // 0.0
/*1238 */ 	    tcg_gen_subi_i32(addr, REG(B11_8), 4);                                                                     // 0.0
/*1240 */ 	    tcg_gen_qemu_st32(cpu_fregs[FREG(B7_4)], addr, ctx->memidx);                                               // 0.0
/*1242 */ 	    tcg_gen_mov_i32(REG(B11_8), addr);                                                                         // 0.0
/*1244 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1246 */ 	}                                                                                                              // 0.0
/*1248 */ 	return;                                                                                                        // 0.0
/*1250 */     case 0xf006: /* fmov @(R0,Rm),{F,D,X}Rm - FPSCR: Nothing */                                                 // 0.0
/*1252 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*1254 */ 	{                                                                                                              // 0.0
/*1256 */ 	    TCGv addr = tcg_temp_new_i32();                                                                            // 0.0
/*1258 */ 	    tcg_gen_add_i32(addr, REG(B7_4), REG(0));                                                                  // 0.0
/*1260 */ 	    if (ctx->fpscr & FPSCR_SZ) {                                                                               // 0.0
/*1262 */ 		int fr = XREG(B11_8);                                                                                         // 0.0
/*1264 */ 		tcg_gen_qemu_ld32u(cpu_fregs[fr	 ], addr, ctx->memidx);                                                       // 0.0
/*1266 */ 		tcg_gen_addi_i32(addr, addr, 4);                                                                              // 0.0
/*1268 */ 		tcg_gen_qemu_ld32u(cpu_fregs[fr+1], addr, ctx->memidx);                                                       // 0.0
/*1270 */ 	    } else {                                                                                                   // 0.0
/*1272 */ 		tcg_gen_qemu_ld32u(cpu_fregs[FREG(B11_8)], addr, ctx->memidx);                                                // 0.0
/*1274 */ 	    }                                                                                                          // 0.0
/*1276 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1278 */ 	}                                                                                                              // 0.0
/*1280 */ 	return;                                                                                                        // 0.0
/*1282 */     case 0xf007: /* fmov {F,D,X}Rn,@(R0,Rn) - FPSCR: Nothing */                                                 // 0.0
/*1284 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*1286 */ 	{                                                                                                              // 0.0
/*1288 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1290 */ 	    tcg_gen_add_i32(addr, REG(B11_8), REG(0));                                                                 // 0.0
/*1292 */ 	    if (ctx->fpscr & FPSCR_SZ) {                                                                               // 0.0
/*1294 */ 		int fr = XREG(B7_4);                                                                                          // 0.0
/*1296 */ 		tcg_gen_qemu_ld32u(cpu_fregs[fr	 ], addr, ctx->memidx);                                                       // 0.0
/*1298 */ 		tcg_gen_addi_i32(addr, addr, 4);                                                                              // 0.0
/*1300 */ 		tcg_gen_qemu_ld32u(cpu_fregs[fr+1], addr, ctx->memidx);                                                       // 0.0
/*1302 */ 	    } else {                                                                                                   // 0.0
/*1304 */ 		tcg_gen_qemu_st32(cpu_fregs[FREG(B7_4)], addr, ctx->memidx);                                                  // 0.0
/*1306 */ 	    }                                                                                                          // 0.0
/*1308 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1310 */ 	}                                                                                                              // 0.0
/*1312 */ 	return;                                                                                                        // 0.0
/*1314 */     case 0xf000: /* fadd Rm,Rn - FPSCR: R[PR,Enable.O/U/I]/W[Cause,Flag] */                                     // 0.0
/*1316 */     case 0xf001: /* fsub Rm,Rn - FPSCR: R[PR,Enable.O/U/I]/W[Cause,Flag] */                                     // 0.0
/*1318 */     case 0xf002: /* fmul Rm,Rn - FPSCR: R[PR,Enable.O/U/I]/W[Cause,Flag] */                                     // 0.0
/*1320 */     case 0xf003: /* fdiv Rm,Rn - FPSCR: R[PR,Enable.O/U/I]/W[Cause,Flag] */                                     // 0.0
/*1322 */     case 0xf004: /* fcmp/eq Rm,Rn - FPSCR: R[PR,Enable.V]/W[Cause,Flag] */                                      // 0.0
/*1324 */     case 0xf005: /* fcmp/gt Rm,Rn - FPSCR: R[PR,Enable.V]/W[Cause,Flag] */                                      // 0.0
/*1326 */ 	{                                                                                                              // 0.0
/*1328 */ 	    CHECK_FPU_ENABLED                                                                                          // 0.0
/*1330 */ 	    if (ctx->fpscr & FPSCR_PR) {                                                                               // 0.0
/*1332 */                 TCGv_i64 fp0, fp1;                                                                              // 0.0
/*1336 */ 		if (ctx->opcode & 0x0110)                                                                                     // 0.0
/*1338 */ 		    break; /* illegal instruction */                                                                          // 0.0
/*1340 */ 		fp0 = tcg_temp_new_i64();                                                                                     // 0.0
/*1342 */ 		fp1 = tcg_temp_new_i64();                                                                                     // 0.0
/*1344 */ 		gen_load_fpr64(fp0, DREG(B11_8));                                                                             // 0.0
/*1346 */ 		gen_load_fpr64(fp1, DREG(B7_4));                                                                              // 0.0
/*1348 */                 switch (ctx->opcode & 0xf00f) {                                                                 // 0.0
/*1350 */                 case 0xf000:		/* fadd Rm,Rn */                                                                  // 0.0
/*1352 */                     gen_helper_fadd_DT(fp0, fp0, fp1);                                                          // 0.0
/*1354 */                     break;                                                                                      // 0.0
/*1356 */                 case 0xf001:		/* fsub Rm,Rn */                                                                  // 0.0
/*1358 */                     gen_helper_fsub_DT(fp0, fp0, fp1);                                                          // 0.0
/*1360 */                     break;                                                                                      // 0.0
/*1362 */                 case 0xf002:		/* fmul Rm,Rn */                                                                  // 0.0
/*1364 */                     gen_helper_fmul_DT(fp0, fp0, fp1);                                                          // 0.0
/*1366 */                     break;                                                                                      // 0.0
/*1368 */                 case 0xf003:		/* fdiv Rm,Rn */                                                                  // 0.0
/*1370 */                     gen_helper_fdiv_DT(fp0, fp0, fp1);                                                          // 0.0
/*1372 */                     break;                                                                                      // 0.0
/*1374 */                 case 0xf004:		/* fcmp/eq Rm,Rn */                                                               // 0.0
/*1376 */                     gen_helper_fcmp_eq_DT(fp0, fp1);                                                            // 0.0
/*1378 */                     return;                                                                                     // 0.0
/*1380 */                 case 0xf005:		/* fcmp/gt Rm,Rn */                                                               // 0.0
/*1382 */                     gen_helper_fcmp_gt_DT(fp0, fp1);                                                            // 0.0
/*1384 */                     return;                                                                                     // 0.0
/*1386 */                 }                                                                                               // 0.0
/*1388 */ 		gen_store_fpr64(fp0, DREG(B11_8));                                                                            // 0.0
/*1390 */                 tcg_temp_free_i64(fp0);                                                                         // 0.0
/*1392 */                 tcg_temp_free_i64(fp1);                                                                         // 0.0
/*1394 */ 	    } else {                                                                                                   // 0.0
/*1396 */                 switch (ctx->opcode & 0xf00f) {                                                                 // 0.0
/*1398 */                 case 0xf000:		/* fadd Rm,Rn */                                                                  // 0.0
/*1400 */                     gen_helper_fadd_FT(cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B7_4)]);  // 0.0
/*1402 */                     break;                                                                                      // 0.0
/*1404 */                 case 0xf001:		/* fsub Rm,Rn */                                                                  // 0.0
/*1406 */                     gen_helper_fsub_FT(cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B7_4)]);  // 0.0
/*1408 */                     break;                                                                                      // 0.0
/*1410 */                 case 0xf002:		/* fmul Rm,Rn */                                                                  // 0.0
/*1412 */                     gen_helper_fmul_FT(cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B7_4)]);  // 0.0
/*1414 */                     break;                                                                                      // 0.0
/*1416 */                 case 0xf003:		/* fdiv Rm,Rn */                                                                  // 0.0
/*1418 */                     gen_helper_fdiv_FT(cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B7_4)]);  // 0.0
/*1420 */                     break;                                                                                      // 0.0
/*1422 */                 case 0xf004:		/* fcmp/eq Rm,Rn */                                                               // 0.0
/*1424 */                     gen_helper_fcmp_eq_FT(cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B7_4)]);                       // 0.0
/*1426 */                     return;                                                                                     // 0.0
/*1428 */                 case 0xf005:		/* fcmp/gt Rm,Rn */                                                               // 0.0
/*1430 */                     gen_helper_fcmp_gt_FT(cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B7_4)]);                       // 0.0
/*1432 */                     return;                                                                                     // 0.0
/*1434 */                 }                                                                                               // 0.0
/*1436 */ 	    }                                                                                                          // 0.0
/*1438 */ 	}                                                                                                              // 0.0
/*1440 */ 	return;                                                                                                        // 0.0
/*1442 */     case 0xf00e: /* fmac FR0,RM,Rn */                                                                           // 0.0
/*1444 */         {                                                                                                       // 0.0
/*1446 */             CHECK_FPU_ENABLED                                                                                   // 0.0
/*1448 */             if (ctx->fpscr & FPSCR_PR) {                                                                        // 0.0
/*1450 */                 break; /* illegal instruction */                                                                // 0.0
/*1452 */             } else {                                                                                            // 0.0
/*1454 */                 gen_helper_fmac_FT(cpu_fregs[FREG(B11_8)],                                                      // 0.0
/*1456 */                                    cpu_fregs[FREG(0)], cpu_fregs[FREG(B7_4)], cpu_fregs[FREG(B11_8)]);          // 0.0
/*1458 */                 return;                                                                                         // 0.0
/*1460 */             }                                                                                                   // 0.0
/*1462 */         }                                                                                                       // 0.0
/*1464 */     }                                                                                                           // 0.0
/*1468 */     switch (ctx->opcode & 0xff00) {                                                                             // 0.0
/*1470 */     case 0xc900:		/* and #imm,R0 */                                                                             // 0.0
/*1472 */ 	tcg_gen_andi_i32(REG(0), REG(0), B7_0);                                                                        // 0.0
/*1474 */ 	return;                                                                                                        // 0.0
/*1476 */     case 0xcd00:		/* and.b #imm,@(R0,GBR) */                                                                    // 0.0
/*1478 */ 	{                                                                                                              // 0.0
/*1480 */ 	    TCGv addr, val;                                                                                            // 0.0
/*1482 */ 	    addr = tcg_temp_new();                                                                                     // 0.0
/*1484 */ 	    tcg_gen_add_i32(addr, REG(0), cpu_gbr);                                                                    // 0.0
/*1486 */ 	    val = tcg_temp_new();                                                                                      // 0.0
/*1488 */ 	    tcg_gen_qemu_ld8u(val, addr, ctx->memidx);                                                                 // 0.0
/*1490 */ 	    tcg_gen_andi_i32(val, val, B7_0);                                                                          // 0.0
/*1492 */ 	    tcg_gen_qemu_st8(val, addr, ctx->memidx);                                                                  // 0.0
/*1494 */ 	    tcg_temp_free(val);                                                                                        // 0.0
/*1496 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1498 */ 	}                                                                                                              // 0.0
/*1500 */ 	return;                                                                                                        // 0.0
/*1502 */     case 0x8b00:		/* bf label */                                                                                // 0.0
/*1504 */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*1506 */ 	    gen_conditional_jump(ctx, ctx->pc + 2,                                                                     // 0.0
/*1508 */ 				 ctx->pc + 4 + B7_0s * 2);                                                                                  // 0.0
/*1510 */ 	ctx->bstate = BS_BRANCH;                                                                                       // 0.0
/*1512 */ 	return;                                                                                                        // 0.0
/*1514 */     case 0x8f00:		/* bf/s label */                                                                              // 0.0
/*1516 */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*1518 */ 	gen_branch_slot(ctx->delayed_pc = ctx->pc + 4 + B7_0s * 2, 0);                                                 // 0.0
/*1520 */ 	ctx->flags |= DELAY_SLOT_CONDITIONAL;                                                                          // 0.0
/*1522 */ 	return;                                                                                                        // 0.0
/*1524 */     case 0x8900:		/* bt label */                                                                                // 0.0
/*1526 */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*1528 */ 	    gen_conditional_jump(ctx, ctx->pc + 4 + B7_0s * 2,                                                         // 0.0
/*1530 */ 				 ctx->pc + 2);                                                                                              // 0.0
/*1532 */ 	ctx->bstate = BS_BRANCH;                                                                                       // 0.0
/*1534 */ 	return;                                                                                                        // 0.0
/*1536 */     case 0x8d00:		/* bt/s label */                                                                              // 0.0
/*1538 */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*1540 */ 	gen_branch_slot(ctx->delayed_pc = ctx->pc + 4 + B7_0s * 2, 1);                                                 // 0.0
/*1542 */ 	ctx->flags |= DELAY_SLOT_CONDITIONAL;                                                                          // 0.0
/*1544 */ 	return;                                                                                                        // 0.0
/*1546 */     case 0x8800:		/* cmp/eq #imm,R0 */                                                                          // 0.0
/*1548 */ 	gen_cmp_imm(TCG_COND_EQ, REG(0), B7_0s);                                                                       // 0.0
/*1550 */ 	return;                                                                                                        // 0.0
/*1552 */     case 0xc400:		/* mov.b @(disp,GBR),R0 */                                                                    // 0.0
/*1554 */ 	{                                                                                                              // 0.0
/*1556 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1558 */ 	    tcg_gen_addi_i32(addr, cpu_gbr, B7_0);                                                                     // 0.0
/*1560 */ 	    tcg_gen_qemu_ld8s(REG(0), addr, ctx->memidx);                                                              // 0.0
/*1562 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1564 */ 	}                                                                                                              // 0.0
/*1566 */ 	return;                                                                                                        // 0.0
/*1568 */     case 0xc500:		/* mov.w @(disp,GBR),R0 */                                                                    // 0.0
/*1570 */ 	{                                                                                                              // 0.0
/*1572 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1574 */ 	    tcg_gen_addi_i32(addr, cpu_gbr, B7_0 * 2);                                                                 // 0.0
/*1576 */ 	    tcg_gen_qemu_ld16s(REG(0), addr, ctx->memidx);                                                             // 0.0
/*1578 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1580 */ 	}                                                                                                              // 0.0
/*1582 */ 	return;                                                                                                        // 0.0
/*1584 */     case 0xc600:		/* mov.l @(disp,GBR),R0 */                                                                    // 0.0
/*1586 */ 	{                                                                                                              // 0.0
/*1588 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1590 */ 	    tcg_gen_addi_i32(addr, cpu_gbr, B7_0 * 4);                                                                 // 0.0
/*1592 */ 	    tcg_gen_qemu_ld32s(REG(0), addr, ctx->memidx);                                                             // 0.0
/*1594 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1596 */ 	}                                                                                                              // 0.0
/*1598 */ 	return;                                                                                                        // 0.0
/*1600 */     case 0xc000:		/* mov.b R0,@(disp,GBR) */                                                                    // 0.0
/*1602 */ 	{                                                                                                              // 0.0
/*1604 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1606 */ 	    tcg_gen_addi_i32(addr, cpu_gbr, B7_0);                                                                     // 0.0
/*1608 */ 	    tcg_gen_qemu_st8(REG(0), addr, ctx->memidx);                                                               // 0.0
/*1610 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1612 */ 	}                                                                                                              // 0.0
/*1614 */ 	return;                                                                                                        // 0.0
/*1616 */     case 0xc100:		/* mov.w R0,@(disp,GBR) */                                                                    // 0.0
/*1618 */ 	{                                                                                                              // 0.0
/*1620 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1622 */ 	    tcg_gen_addi_i32(addr, cpu_gbr, B7_0 * 2);                                                                 // 0.0
/*1624 */ 	    tcg_gen_qemu_st16(REG(0), addr, ctx->memidx);                                                              // 0.0
/*1626 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1628 */ 	}                                                                                                              // 0.0
/*1630 */ 	return;                                                                                                        // 0.0
/*1632 */     case 0xc200:		/* mov.l R0,@(disp,GBR) */                                                                    // 0.0
/*1634 */ 	{                                                                                                              // 0.0
/*1636 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1638 */ 	    tcg_gen_addi_i32(addr, cpu_gbr, B7_0 * 4);                                                                 // 0.0
/*1640 */ 	    tcg_gen_qemu_st32(REG(0), addr, ctx->memidx);                                                              // 0.0
/*1642 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1644 */ 	}                                                                                                              // 0.0
/*1646 */ 	return;                                                                                                        // 0.0
/*1648 */     case 0x8000:		/* mov.b R0,@(disp,Rn) */                                                                     // 0.0
/*1650 */ 	{                                                                                                              // 0.0
/*1652 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1654 */ 	    tcg_gen_addi_i32(addr, REG(B7_4), B3_0);                                                                   // 0.0
/*1656 */ 	    tcg_gen_qemu_st8(REG(0), addr, ctx->memidx);                                                               // 0.0
/*1658 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1660 */ 	}                                                                                                              // 0.0
/*1662 */ 	return;                                                                                                        // 0.0
/*1664 */     case 0x8100:		/* mov.w R0,@(disp,Rn) */                                                                     // 0.0
/*1666 */ 	{                                                                                                              // 0.0
/*1668 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1670 */ 	    tcg_gen_addi_i32(addr, REG(B7_4), B3_0 * 2);                                                               // 0.0
/*1672 */ 	    tcg_gen_qemu_st16(REG(0), addr, ctx->memidx);                                                              // 0.0
/*1674 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1676 */ 	}                                                                                                              // 0.0
/*1678 */ 	return;                                                                                                        // 0.0
/*1680 */     case 0x8400:		/* mov.b @(disp,Rn),R0 */                                                                     // 0.0
/*1682 */ 	{                                                                                                              // 0.0
/*1684 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1686 */ 	    tcg_gen_addi_i32(addr, REG(B7_4), B3_0);                                                                   // 0.0
/*1688 */ 	    tcg_gen_qemu_ld8s(REG(0), addr, ctx->memidx);                                                              // 0.0
/*1690 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1692 */ 	}                                                                                                              // 0.0
/*1694 */ 	return;                                                                                                        // 0.0
/*1696 */     case 0x8500:		/* mov.w @(disp,Rn),R0 */                                                                     // 0.0
/*1698 */ 	{                                                                                                              // 0.0
/*1700 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1702 */ 	    tcg_gen_addi_i32(addr, REG(B7_4), B3_0 * 2);                                                               // 0.0
/*1704 */ 	    tcg_gen_qemu_ld16s(REG(0), addr, ctx->memidx);                                                             // 0.0
/*1706 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1708 */ 	}                                                                                                              // 0.0
/*1710 */ 	return;                                                                                                        // 0.0
/*1712 */     case 0xc700:		/* mova @(disp,PC),R0 */                                                                      // 0.0
/*1714 */ 	tcg_gen_movi_i32(REG(0), ((ctx->pc & 0xfffffffc) + 4 + B7_0 * 4) & ~3);                                        // 0.0
/*1716 */ 	return;                                                                                                        // 0.0
/*1718 */     case 0xcb00:		/* or #imm,R0 */                                                                              // 0.0
/*1720 */ 	tcg_gen_ori_i32(REG(0), REG(0), B7_0);                                                                         // 0.0
/*1722 */ 	return;                                                                                                        // 0.0
/*1724 */     case 0xcf00:		/* or.b #imm,@(R0,GBR) */                                                                     // 0.0
/*1726 */ 	{                                                                                                              // 0.0
/*1728 */ 	    TCGv addr, val;                                                                                            // 0.0
/*1730 */ 	    addr = tcg_temp_new();                                                                                     // 0.0
/*1732 */ 	    tcg_gen_add_i32(addr, REG(0), cpu_gbr);                                                                    // 0.0
/*1734 */ 	    val = tcg_temp_new();                                                                                      // 0.0
/*1736 */ 	    tcg_gen_qemu_ld8u(val, addr, ctx->memidx);                                                                 // 0.0
/*1738 */ 	    tcg_gen_ori_i32(val, val, B7_0);                                                                           // 0.0
/*1740 */ 	    tcg_gen_qemu_st8(val, addr, ctx->memidx);                                                                  // 0.0
/*1742 */ 	    tcg_temp_free(val);                                                                                        // 0.0
/*1744 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1746 */ 	}                                                                                                              // 0.0
/*1748 */ 	return;                                                                                                        // 0.0
/*1750 */     case 0xc300:		/* trapa #imm */                                                                              // 0.0
/*1752 */ 	{                                                                                                              // 0.0
/*1754 */ 	    TCGv imm;                                                                                                  // 0.0
/*1756 */ 	    CHECK_NOT_DELAY_SLOT                                                                                       // 0.0
/*1758 */ 	    tcg_gen_movi_i32(cpu_pc, ctx->pc);                                                                         // 0.0
/*1760 */ 	    imm = tcg_const_i32(B7_0);                                                                                 // 0.0
/*1762 */ 	    gen_helper_trapa(imm);                                                                                     // 0.0
/*1764 */ 	    tcg_temp_free(imm);                                                                                        // 0.0
/*1766 */ 	    ctx->bstate = BS_BRANCH;                                                                                   // 0.0
/*1768 */ 	}                                                                                                              // 0.0
/*1770 */ 	return;                                                                                                        // 0.0
/*1772 */     case 0xc800:		/* tst #imm,R0 */                                                                             // 0.0
/*1774 */ 	{                                                                                                              // 0.0
/*1776 */ 	    TCGv val = tcg_temp_new();                                                                                 // 0.0
/*1778 */ 	    tcg_gen_andi_i32(val, REG(0), B7_0);                                                                       // 0.0
/*1780 */ 	    gen_cmp_imm(TCG_COND_EQ, val, 0);                                                                          // 0.0
/*1782 */ 	    tcg_temp_free(val);                                                                                        // 0.0
/*1784 */ 	}                                                                                                              // 0.0
/*1786 */ 	return;                                                                                                        // 0.0
/*1788 */     case 0xcc00:		/* tst.b #imm,@(R0,GBR) */                                                                    // 0.0
/*1790 */ 	{                                                                                                              // 0.0
/*1792 */ 	    TCGv val = tcg_temp_new();                                                                                 // 0.0
/*1794 */ 	    tcg_gen_add_i32(val, REG(0), cpu_gbr);                                                                     // 0.0
/*1796 */ 	    tcg_gen_qemu_ld8u(val, val, ctx->memidx);                                                                  // 0.0
/*1798 */ 	    tcg_gen_andi_i32(val, val, B7_0);                                                                          // 0.0
/*1800 */ 	    gen_cmp_imm(TCG_COND_EQ, val, 0);                                                                          // 0.0
/*1802 */ 	    tcg_temp_free(val);                                                                                        // 0.0
/*1804 */ 	}                                                                                                              // 0.0
/*1806 */ 	return;                                                                                                        // 0.0
/*1808 */     case 0xca00:		/* xor #imm,R0 */                                                                             // 0.0
/*1810 */ 	tcg_gen_xori_i32(REG(0), REG(0), B7_0);                                                                        // 0.0
/*1812 */ 	return;                                                                                                        // 0.0
/*1814 */     case 0xce00:		/* xor.b #imm,@(R0,GBR) */                                                                    // 0.0
/*1816 */ 	{                                                                                                              // 0.0
/*1818 */ 	    TCGv addr, val;                                                                                            // 0.0
/*1820 */ 	    addr = tcg_temp_new();                                                                                     // 0.0
/*1822 */ 	    tcg_gen_add_i32(addr, REG(0), cpu_gbr);                                                                    // 0.0
/*1824 */ 	    val = tcg_temp_new();                                                                                      // 0.0
/*1826 */ 	    tcg_gen_qemu_ld8u(val, addr, ctx->memidx);                                                                 // 0.0
/*1828 */ 	    tcg_gen_xori_i32(val, val, B7_0);                                                                          // 0.0
/*1830 */ 	    tcg_gen_qemu_st8(val, addr, ctx->memidx);                                                                  // 0.0
/*1832 */ 	    tcg_temp_free(val);                                                                                        // 0.0
/*1834 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1836 */ 	}                                                                                                              // 0.0
/*1838 */ 	return;                                                                                                        // 0.0
/*1840 */     }                                                                                                           // 0.0
/*1844 */     switch (ctx->opcode & 0xf08f) {                                                                             // 0.0
/*1846 */     case 0x408e:		/* ldc Rm,Rn_BANK */                                                                          // 0.0
/*1848 */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*1850 */ 	tcg_gen_mov_i32(ALTREG(B6_4), REG(B11_8));                                                                     // 0.0
/*1852 */ 	return;                                                                                                        // 0.0
/*1854 */     case 0x4087:		/* ldc.l @Rm+,Rn_BANK */                                                                      // 0.0
/*1856 */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*1858 */ 	tcg_gen_qemu_ld32s(ALTREG(B6_4), REG(B11_8), ctx->memidx);                                                     // 0.0
/*1860 */ 	tcg_gen_addi_i32(REG(B11_8), REG(B11_8), 4);                                                                   // 0.0
/*1862 */ 	return;                                                                                                        // 0.0
/*1864 */     case 0x0082:		/* stc Rm_BANK,Rn */                                                                          // 0.0
/*1866 */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*1868 */ 	tcg_gen_mov_i32(REG(B11_8), ALTREG(B6_4));                                                                     // 0.0
/*1870 */ 	return;                                                                                                        // 0.0
/*1872 */     case 0x4083:		/* stc.l Rm_BANK,@-Rn */                                                                      // 0.0
/*1874 */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*1876 */ 	{                                                                                                              // 0.0
/*1878 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*1880 */ 	    tcg_gen_subi_i32(addr, REG(B11_8), 4);                                                                     // 0.0
/*1882 */ 	    tcg_gen_qemu_st32(ALTREG(B6_4), addr, ctx->memidx);                                                        // 0.0
/*1884 */ 	    tcg_gen_mov_i32(REG(B11_8), addr);                                                                         // 0.0
/*1886 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*1888 */ 	}                                                                                                              // 0.0
/*1890 */ 	return;                                                                                                        // 0.0
/*1892 */     }                                                                                                           // 0.0
/*1896 */     switch (ctx->opcode & 0xf0ff) {                                                                             // 0.0
/*1898 */     case 0x0023:		/* braf Rn */                                                                                 // 0.0
/*1900 */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*1902 */ 	tcg_gen_addi_i32(cpu_delayed_pc, REG(B11_8), ctx->pc + 4);                                                     // 0.0
/*1904 */ 	ctx->flags |= DELAY_SLOT;                                                                                      // 0.0
/*1906 */ 	ctx->delayed_pc = (uint32_t) - 1;                                                                              // 0.0
/*1908 */ 	return;                                                                                                        // 0.0
/*1910 */     case 0x0003:		/* bsrf Rn */                                                                                 // 0.0
/*1912 */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*1914 */ 	tcg_gen_movi_i32(cpu_pr, ctx->pc + 4);                                                                         // 0.0
/*1916 */ 	tcg_gen_add_i32(cpu_delayed_pc, REG(B11_8), cpu_pr);                                                           // 0.0
/*1918 */ 	ctx->flags |= DELAY_SLOT;                                                                                      // 0.0
/*1920 */ 	ctx->delayed_pc = (uint32_t) - 1;                                                                              // 0.0
/*1922 */ 	return;                                                                                                        // 0.0
/*1924 */     case 0x4015:		/* cmp/pl Rn */                                                                               // 0.0
/*1926 */ 	gen_cmp_imm(TCG_COND_GT, REG(B11_8), 0);                                                                       // 0.0
/*1928 */ 	return;                                                                                                        // 0.0
/*1930 */     case 0x4011:		/* cmp/pz Rn */                                                                               // 0.0
/*1932 */ 	gen_cmp_imm(TCG_COND_GE, REG(B11_8), 0);                                                                       // 0.0
/*1934 */ 	return;                                                                                                        // 0.0
/*1936 */     case 0x4010:		/* dt Rn */                                                                                   // 0.0
/*1938 */ 	tcg_gen_subi_i32(REG(B11_8), REG(B11_8), 1);                                                                   // 0.0
/*1940 */ 	gen_cmp_imm(TCG_COND_EQ, REG(B11_8), 0);                                                                       // 0.0
/*1942 */ 	return;                                                                                                        // 0.0
/*1944 */     case 0x402b:		/* jmp @Rn */                                                                                 // 0.0
/*1946 */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*1948 */ 	tcg_gen_mov_i32(cpu_delayed_pc, REG(B11_8));                                                                   // 0.0
/*1950 */ 	ctx->flags |= DELAY_SLOT;                                                                                      // 0.0
/*1952 */ 	ctx->delayed_pc = (uint32_t) - 1;                                                                              // 0.0
/*1954 */ 	return;                                                                                                        // 0.0
/*1956 */     case 0x400b:		/* jsr @Rn */                                                                                 // 0.0
/*1958 */ 	CHECK_NOT_DELAY_SLOT                                                                                           // 0.0
/*1960 */ 	tcg_gen_movi_i32(cpu_pr, ctx->pc + 4);                                                                         // 0.0
/*1962 */ 	tcg_gen_mov_i32(cpu_delayed_pc, REG(B11_8));                                                                   // 0.0
/*1964 */ 	ctx->flags |= DELAY_SLOT;                                                                                      // 0.0
/*1966 */ 	ctx->delayed_pc = (uint32_t) - 1;                                                                              // 0.0
/*1968 */ 	return;                                                                                                        // 0.0
/*1970 */     case 0x400e:		/* ldc Rm,SR */                                                                               // 0.0
/*1972 */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*1974 */ 	tcg_gen_andi_i32(cpu_sr, REG(B11_8), 0x700083f3);                                                              // 0.0
/*1976 */ 	ctx->bstate = BS_STOP;                                                                                         // 0.0
/*1978 */ 	return;                                                                                                        // 0.0
/*1980 */     case 0x4007:		/* ldc.l @Rm+,SR */                                                                           // 0.0
/*1982 */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*1984 */ 	{                                                                                                              // 0.0
/*1986 */ 	    TCGv val = tcg_temp_new();                                                                                 // 0.0
/*1988 */ 	    tcg_gen_qemu_ld32s(val, REG(B11_8), ctx->memidx);                                                          // 0.0
/*1990 */ 	    tcg_gen_andi_i32(cpu_sr, val, 0x700083f3);                                                                 // 0.0
/*1992 */ 	    tcg_temp_free(val);                                                                                        // 0.0
/*1994 */ 	    tcg_gen_addi_i32(REG(B11_8), REG(B11_8), 4);                                                               // 0.0
/*1996 */ 	    ctx->bstate = BS_STOP;                                                                                     // 0.0
/*1998 */ 	}                                                                                                              // 0.0
/*2000 */ 	return;                                                                                                        // 0.0
/*2002 */     case 0x0002:		/* stc SR,Rn */                                                                               // 0.0
/*2004 */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*2006 */ 	tcg_gen_mov_i32(REG(B11_8), cpu_sr);                                                                           // 0.0
/*2008 */ 	return;                                                                                                        // 0.0
/*2010 */     case 0x4003:		/* stc SR,@-Rn */                                                                             // 0.0
/*2012 */ 	CHECK_PRIVILEGED                                                                                               // 0.0
/*2014 */ 	{                                                                                                              // 0.0
/*2016 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*2018 */ 	    tcg_gen_subi_i32(addr, REG(B11_8), 4);                                                                     // 0.0
/*2020 */ 	    tcg_gen_qemu_st32(cpu_sr, addr, ctx->memidx);                                                              // 0.0
/*2022 */ 	    tcg_gen_mov_i32(REG(B11_8), addr);                                                                         // 0.0
/*2024 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*2026 */ 	}                                                                                                              // 0.0
/*2028 */ 	return;                                                                                                        // 0.0
/*2030 */ #define LD(reg,ldnum,ldpnum,prechk)		\                                                                          // 0.0
/*2032 */   case ldnum:							\                                                                                           // 0.0
/*2034 */     prechk    							\                                                                                          // 0.0
/*2036 */     tcg_gen_mov_i32 (cpu_##reg, REG(B11_8));			\                                                                // 0.0
/*2038 */     return;							\                                                                                             // 0.0
/*2040 */   case ldpnum:							\                                                                                          // 0.0
/*2042 */     prechk    							\                                                                                          // 0.0
/*2044 */     tcg_gen_qemu_ld32s (cpu_##reg, REG(B11_8), ctx->memidx);	\                                                  // 0.0
/*2046 */     tcg_gen_addi_i32(REG(B11_8), REG(B11_8), 4);		\                                                             // 0.0
/*2048 */     return;                                                                                                     // 0.0
/*2050 */ #define ST(reg,stnum,stpnum,prechk)		\                                                                          // 0.0
/*2052 */   case stnum:							\                                                                                           // 0.0
/*2054 */     prechk    							\                                                                                          // 0.0
/*2056 */     tcg_gen_mov_i32 (REG(B11_8), cpu_##reg);			\                                                                // 0.0
/*2058 */     return;							\                                                                                             // 0.0
/*2060 */   case stpnum:							\                                                                                          // 0.0
/*2062 */     prechk    							\                                                                                          // 0.0
/*2064 */     {								\                                                                                                  // 0.0
/*2066 */ 	TCGv addr = tcg_temp_new();				\                                                                               // 0.0
/*2068 */ 	tcg_gen_subi_i32(addr, REG(B11_8), 4);			\                                                                     // 0.0
/*2070 */ 	tcg_gen_qemu_st32 (cpu_##reg, addr, ctx->memidx);	\                                                            // 0.0
/*2072 */ 	tcg_gen_mov_i32(REG(B11_8), addr);			\                                                                         // 0.0
/*2074 */ 	tcg_temp_free(addr);					\                                                                                     // 0.0
/*2076 */     }								\                                                                                                  // 0.0
/*2078 */     return;                                                                                                     // 0.0
/*2080 */ #define LDST(reg,ldnum,ldpnum,stnum,stpnum,prechk)		\                                                           // 0.0
/*2082 */ 	LD(reg,ldnum,ldpnum,prechk)				\                                                                               // 0.0
/*2084 */ 	ST(reg,stnum,stpnum,prechk)                                                                                    // 0.0
/*2086 */ 	LDST(gbr,  0x401e, 0x4017, 0x0012, 0x4013, {})                                                                 // 0.0
/*2088 */ 	LDST(vbr,  0x402e, 0x4027, 0x0022, 0x4023, CHECK_PRIVILEGED)                                                   // 0.0
/*2090 */ 	LDST(ssr,  0x403e, 0x4037, 0x0032, 0x4033, CHECK_PRIVILEGED)                                                   // 0.0
/*2092 */ 	LDST(spc,  0x404e, 0x4047, 0x0042, 0x4043, CHECK_PRIVILEGED)                                                   // 0.0
/*2094 */ 	ST(sgr,  0x003a, 0x4032, CHECK_PRIVILEGED)                                                                     // 0.0
/*2096 */ 	LD(sgr,  0x403a, 0x4036, CHECK_PRIVILEGED if (!(ctx->features & SH_FEATURE_SH4A)) break;)                      // 0.0
/*2098 */ 	LDST(dbr,  0x40fa, 0x40f6, 0x00fa, 0x40f2, CHECK_PRIVILEGED)                                                   // 0.0
/*2100 */ 	LDST(mach, 0x400a, 0x4006, 0x000a, 0x4002, {})                                                                 // 0.0
/*2102 */ 	LDST(macl, 0x401a, 0x4016, 0x001a, 0x4012, {})                                                                 // 0.0
/*2104 */ 	LDST(pr,   0x402a, 0x4026, 0x002a, 0x4022, {})                                                                 // 0.0
/*2106 */ 	LDST(fpul, 0x405a, 0x4056, 0x005a, 0x4052, {CHECK_FPU_ENABLED})                                                // 0.0
/*2108 */     case 0x406a:		/* lds Rm,FPSCR */                                                                            // 0.0
/*2110 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2112 */ 	gen_helper_ld_fpscr(REG(B11_8));                                                                               // 0.0
/*2114 */ 	ctx->bstate = BS_STOP;                                                                                         // 0.0
/*2116 */ 	return;                                                                                                        // 0.0
/*2118 */     case 0x4066:		/* lds.l @Rm+,FPSCR */                                                                        // 0.0
/*2120 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2122 */ 	{                                                                                                              // 0.0
/*2124 */ 	    TCGv addr = tcg_temp_new();                                                                                // 0.0
/*2126 */ 	    tcg_gen_qemu_ld32s(addr, REG(B11_8), ctx->memidx);                                                         // 0.0
/*2128 */ 	    tcg_gen_addi_i32(REG(B11_8), REG(B11_8), 4);                                                               // 0.0
/*2130 */ 	    gen_helper_ld_fpscr(addr);                                                                                 // 0.0
/*2132 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*2134 */ 	    ctx->bstate = BS_STOP;                                                                                     // 0.0
/*2136 */ 	}                                                                                                              // 0.0
/*2138 */ 	return;                                                                                                        // 0.0
/*2140 */     case 0x006a:		/* sts FPSCR,Rn */                                                                            // 0.0
/*2142 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2144 */ 	tcg_gen_andi_i32(REG(B11_8), cpu_fpscr, 0x003fffff);                                                           // 0.0
/*2146 */ 	return;                                                                                                        // 0.0
/*2148 */     case 0x4062:		/* sts FPSCR,@-Rn */                                                                          // 0.0
/*2150 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2152 */ 	{                                                                                                              // 0.0
/*2154 */ 	    TCGv addr, val;                                                                                            // 0.0
/*2156 */ 	    val = tcg_temp_new();                                                                                      // 0.0
/*2158 */ 	    tcg_gen_andi_i32(val, cpu_fpscr, 0x003fffff);                                                              // 0.0
/*2160 */ 	    addr = tcg_temp_new();                                                                                     // 0.0
/*2162 */ 	    tcg_gen_subi_i32(addr, REG(B11_8), 4);                                                                     // 0.0
/*2164 */ 	    tcg_gen_qemu_st32(val, addr, ctx->memidx);                                                                 // 0.0
/*2166 */ 	    tcg_gen_mov_i32(REG(B11_8), addr);                                                                         // 0.0
/*2168 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*2170 */ 	    tcg_temp_free(val);                                                                                        // 0.0
/*2172 */ 	}                                                                                                              // 0.0
/*2174 */ 	return;                                                                                                        // 0.0
/*2176 */     case 0x00c3:		/* movca.l R0,@Rm */                                                                          // 0.0
/*2178 */         {                                                                                                       // 0.0
/*2180 */             TCGv val = tcg_temp_new();                                                                          // 0.0
/*2182 */             tcg_gen_qemu_ld32u(val, REG(B11_8), ctx->memidx);                                                   // 0.0
/*2184 */             gen_helper_movcal (REG(B11_8), val);                                                                // 0.0
/*2186 */             tcg_gen_qemu_st32(REG(0), REG(B11_8), ctx->memidx);                                                 // 0.0
/*2188 */         }                                                                                                       // 0.0
/*2190 */         ctx->has_movcal = 1;                                                                                    // 0.0
/*2192 */ 	return;                                                                                                        // 0.0
/*2194 */     case 0x40a9:                                                                                                // 0.0
/*2196 */ 	/* MOVUA.L @Rm,R0 (Rm) -> R0                                                                                   // 0.0
/*2198 */ 	   Load non-boundary-aligned data */                                                                           // 0.0
/*2200 */ 	tcg_gen_qemu_ld32u(REG(0), REG(B11_8), ctx->memidx);                                                           // 0.0
/*2202 */ 	return;                                                                                                        // 0.0
/*2204 */     case 0x40e9:                                                                                                // 0.0
/*2206 */ 	/* MOVUA.L @Rm+,R0   (Rm) -> R0, Rm + 4 -> Rm                                                                  // 0.0
/*2208 */ 	   Load non-boundary-aligned data */                                                                           // 0.0
/*2210 */ 	tcg_gen_qemu_ld32u(REG(0), REG(B11_8), ctx->memidx);                                                           // 0.0
/*2212 */ 	tcg_gen_addi_i32(REG(B11_8), REG(B11_8), 4);                                                                   // 0.0
/*2214 */ 	return;                                                                                                        // 0.0
/*2216 */     case 0x0029:		/* movt Rn */                                                                                 // 0.0
/*2218 */ 	tcg_gen_andi_i32(REG(B11_8), cpu_sr, SR_T);                                                                    // 0.0
/*2220 */ 	return;                                                                                                        // 0.0
/*2222 */     case 0x0073:                                                                                                // 0.0
/*2224 */         /* MOVCO.L                                                                                              // 0.0
/*2226 */ 	       LDST -> T                                                                                               // 0.0
/*2228 */                If (T == 1) R0 -> (Rn)                                                                           // 0.0
/*2230 */                0 -> LDST                                                                                        // 0.0
/*2232 */         */                                                                                                      // 0.0
/*2234 */         if (ctx->features & SH_FEATURE_SH4A) {                                                                  // 0.0
/*2236 */ 	    int label = gen_new_label();                                                                               // 0.0
/*2238 */ 	    gen_clr_t();                                                                                               // 0.0
/*2240 */ 	    tcg_gen_or_i32(cpu_sr, cpu_sr, cpu_ldst);                                                                  // 0.0
/*2242 */ 	    tcg_gen_brcondi_i32(TCG_COND_EQ, cpu_ldst, 0, label);                                                      // 0.0
/*2244 */ 	    tcg_gen_qemu_st32(REG(0), REG(B11_8), ctx->memidx);                                                        // 0.0
/*2246 */ 	    gen_set_label(label);                                                                                      // 0.0
/*2248 */ 	    tcg_gen_movi_i32(cpu_ldst, 0);                                                                             // 0.0
/*2250 */ 	    return;                                                                                                    // 0.0
/*2252 */ 	} else                                                                                                         // 0.0
/*2254 */ 	    break;                                                                                                     // 0.0
/*2256 */     case 0x0063:                                                                                                // 0.0
/*2258 */         /* MOVLI.L @Rm,R0                                                                                       // 0.0
/*2260 */                1 -> LDST                                                                                        // 0.0
/*2262 */                (Rm) -> R0                                                                                       // 0.0
/*2264 */                When interrupt/exception                                                                         // 0.0
/*2266 */                occurred 0 -> LDST                                                                               // 0.0
/*2268 */         */                                                                                                      // 0.0
/*2270 */ 	if (ctx->features & SH_FEATURE_SH4A) {                                                                         // 0.0
/*2272 */ 	    tcg_gen_movi_i32(cpu_ldst, 0);                                                                             // 0.0
/*2274 */ 	    tcg_gen_qemu_ld32s(REG(0), REG(B11_8), ctx->memidx);                                                       // 0.0
/*2276 */ 	    tcg_gen_movi_i32(cpu_ldst, 1);                                                                             // 0.0
/*2278 */ 	    return;                                                                                                    // 0.0
/*2280 */ 	} else                                                                                                         // 0.0
/*2282 */ 	    break;                                                                                                     // 0.0
/*2284 */     case 0x0093:		/* ocbi @Rn */                                                                                // 0.0
/*2286 */ 	{                                                                                                              // 0.0
/*2288 */ 	    gen_helper_ocbi (REG(B11_8));                                                                              // 0.0
/*2290 */ 	}                                                                                                              // 0.0
/*2292 */ 	return;                                                                                                        // 0.0
/*2294 */     case 0x00a3:		/* ocbp @Rn */                                                                                // 0.0
/*2296 */ 	{                                                                                                              // 0.0
/*2298 */ 	    TCGv dummy = tcg_temp_new();                                                                               // 0.0
/*2300 */ 	    tcg_gen_qemu_ld32s(dummy, REG(B11_8), ctx->memidx);                                                        // 0.0
/*2302 */ 	    tcg_temp_free(dummy);                                                                                      // 0.0
/*2304 */ 	}                                                                                                              // 0.0
/*2306 */ 	return;                                                                                                        // 0.0
/*2308 */     case 0x00b3:		/* ocbwb @Rn */                                                                               // 0.0
/*2310 */ 	{                                                                                                              // 0.0
/*2312 */ 	    TCGv dummy = tcg_temp_new();                                                                               // 0.0
/*2314 */ 	    tcg_gen_qemu_ld32s(dummy, REG(B11_8), ctx->memidx);                                                        // 0.0
/*2316 */ 	    tcg_temp_free(dummy);                                                                                      // 0.0
/*2318 */ 	}                                                                                                              // 0.0
/*2320 */ 	return;                                                                                                        // 0.0
/*2322 */     case 0x0083:		/* pref @Rn */                                                                                // 0.0
/*2324 */ 	return;                                                                                                        // 0.0
/*2326 */     case 0x00d3:		/* prefi @Rn */                                                                               // 0.0
/*2328 */ 	if (ctx->features & SH_FEATURE_SH4A)                                                                           // 0.0
/*2330 */ 	    return;                                                                                                    // 0.0
/*2332 */ 	else                                                                                                           // 0.0
/*2334 */ 	    break;                                                                                                     // 0.0
/*2336 */     case 0x00e3:		/* icbi @Rn */                                                                                // 0.0
/*2338 */ 	if (ctx->features & SH_FEATURE_SH4A)                                                                           // 0.0
/*2340 */ 	    return;                                                                                                    // 0.0
/*2342 */ 	else                                                                                                           // 0.0
/*2344 */ 	    break;                                                                                                     // 0.0
/*2346 */     case 0x00ab:		/* synco */                                                                                   // 0.0
/*2348 */ 	if (ctx->features & SH_FEATURE_SH4A)                                                                           // 0.0
/*2350 */ 	    return;                                                                                                    // 0.0
/*2352 */ 	else                                                                                                           // 0.0
/*2354 */ 	    break;                                                                                                     // 0.0
/*2356 */     case 0x4024:		/* rotcl Rn */                                                                                // 0.0
/*2358 */ 	{                                                                                                              // 0.0
/*2360 */ 	    TCGv tmp = tcg_temp_new();                                                                                 // 0.0
/*2362 */ 	    tcg_gen_mov_i32(tmp, cpu_sr);                                                                              // 0.0
/*2364 */ 	    gen_copy_bit_i32(cpu_sr, 0, REG(B11_8), 31);                                                               // 0.0
/*2366 */ 	    tcg_gen_shli_i32(REG(B11_8), REG(B11_8), 1);                                                               // 0.0
/*2368 */ 	    gen_copy_bit_i32(REG(B11_8), 0, tmp, 0);                                                                   // 0.0
/*2370 */ 	    tcg_temp_free(tmp);                                                                                        // 0.0
/*2372 */ 	}                                                                                                              // 0.0
/*2374 */ 	return;                                                                                                        // 0.0
/*2376 */     case 0x4025:		/* rotcr Rn */                                                                                // 0.0
/*2378 */ 	{                                                                                                              // 0.0
/*2380 */ 	    TCGv tmp = tcg_temp_new();                                                                                 // 0.0
/*2382 */ 	    tcg_gen_mov_i32(tmp, cpu_sr);                                                                              // 0.0
/*2384 */ 	    gen_copy_bit_i32(cpu_sr, 0, REG(B11_8), 0);                                                                // 0.0
/*2386 */ 	    tcg_gen_shri_i32(REG(B11_8), REG(B11_8), 1);                                                               // 0.0
/*2388 */ 	    gen_copy_bit_i32(REG(B11_8), 31, tmp, 0);                                                                  // 0.0
/*2390 */ 	    tcg_temp_free(tmp);                                                                                        // 0.0
/*2392 */ 	}                                                                                                              // 0.0
/*2394 */ 	return;                                                                                                        // 0.0
/*2396 */     case 0x4004:		/* rotl Rn */                                                                                 // 0.0
/*2398 */ 	gen_copy_bit_i32(cpu_sr, 0, REG(B11_8), 31);                                                                   // 0.0
/*2400 */ 	tcg_gen_shli_i32(REG(B11_8), REG(B11_8), 1);                                                                   // 0.0
/*2402 */ 	gen_copy_bit_i32(REG(B11_8), 0, cpu_sr, 0);                                                                    // 0.0
/*2404 */ 	return;                                                                                                        // 0.0
/*2406 */     case 0x4005:		/* rotr Rn */                                                                                 // 0.0
/*2408 */ 	gen_copy_bit_i32(cpu_sr, 0, REG(B11_8), 0);                                                                    // 0.0
/*2410 */ 	tcg_gen_shri_i32(REG(B11_8), REG(B11_8), 1);                                                                   // 0.0
/*2412 */ 	gen_copy_bit_i32(REG(B11_8), 31, cpu_sr, 0);                                                                   // 0.0
/*2414 */ 	return;                                                                                                        // 0.0
/*2416 */     case 0x4000:		/* shll Rn */                                                                                 // 0.0
/*2418 */     case 0x4020:		/* shal Rn */                                                                                 // 0.0
/*2420 */ 	gen_copy_bit_i32(cpu_sr, 0, REG(B11_8), 31);                                                                   // 0.0
/*2422 */ 	tcg_gen_shli_i32(REG(B11_8), REG(B11_8), 1);                                                                   // 0.0
/*2424 */ 	return;                                                                                                        // 0.0
/*2426 */     case 0x4021:		/* shar Rn */                                                                                 // 0.0
/*2428 */ 	gen_copy_bit_i32(cpu_sr, 0, REG(B11_8), 0);                                                                    // 0.0
/*2430 */ 	tcg_gen_sari_i32(REG(B11_8), REG(B11_8), 1);                                                                   // 0.0
/*2432 */ 	return;                                                                                                        // 0.0
/*2434 */     case 0x4001:		/* shlr Rn */                                                                                 // 0.0
/*2436 */ 	gen_copy_bit_i32(cpu_sr, 0, REG(B11_8), 0);                                                                    // 0.0
/*2438 */ 	tcg_gen_shri_i32(REG(B11_8), REG(B11_8), 1);                                                                   // 0.0
/*2440 */ 	return;                                                                                                        // 0.0
/*2442 */     case 0x4008:		/* shll2 Rn */                                                                                // 0.0
/*2444 */ 	tcg_gen_shli_i32(REG(B11_8), REG(B11_8), 2);                                                                   // 0.0
/*2446 */ 	return;                                                                                                        // 0.0
/*2448 */     case 0x4018:		/* shll8 Rn */                                                                                // 0.0
/*2450 */ 	tcg_gen_shli_i32(REG(B11_8), REG(B11_8), 8);                                                                   // 0.0
/*2452 */ 	return;                                                                                                        // 0.0
/*2454 */     case 0x4028:		/* shll16 Rn */                                                                               // 0.0
/*2456 */ 	tcg_gen_shli_i32(REG(B11_8), REG(B11_8), 16);                                                                  // 0.0
/*2458 */ 	return;                                                                                                        // 0.0
/*2460 */     case 0x4009:		/* shlr2 Rn */                                                                                // 0.0
/*2462 */ 	tcg_gen_shri_i32(REG(B11_8), REG(B11_8), 2);                                                                   // 0.0
/*2464 */ 	return;                                                                                                        // 0.0
/*2466 */     case 0x4019:		/* shlr8 Rn */                                                                                // 0.0
/*2468 */ 	tcg_gen_shri_i32(REG(B11_8), REG(B11_8), 8);                                                                   // 0.0
/*2470 */ 	return;                                                                                                        // 0.0
/*2472 */     case 0x4029:		/* shlr16 Rn */                                                                               // 0.0
/*2474 */ 	tcg_gen_shri_i32(REG(B11_8), REG(B11_8), 16);                                                                  // 0.0
/*2476 */ 	return;                                                                                                        // 0.0
/*2478 */     case 0x401b:		/* tas.b @Rn */                                                                               // 0.0
/*2480 */ 	{                                                                                                              // 0.0
/*2482 */ 	    TCGv addr, val;                                                                                            // 0.0
/*2484 */ 	    addr = tcg_temp_local_new();                                                                               // 0.0
/*2486 */ 	    tcg_gen_mov_i32(addr, REG(B11_8));                                                                         // 0.0
/*2488 */ 	    val = tcg_temp_local_new();                                                                                // 0.0
/*2490 */ 	    tcg_gen_qemu_ld8u(val, addr, ctx->memidx);                                                                 // 0.0
/*2492 */ 	    gen_cmp_imm(TCG_COND_EQ, val, 0);                                                                          // 0.0
/*2494 */ 	    tcg_gen_ori_i32(val, val, 0x80);                                                                           // 0.0
/*2496 */ 	    tcg_gen_qemu_st8(val, addr, ctx->memidx);                                                                  // 0.0
/*2498 */ 	    tcg_temp_free(val);                                                                                        // 0.0
/*2500 */ 	    tcg_temp_free(addr);                                                                                       // 0.0
/*2502 */ 	}                                                                                                              // 0.0
/*2504 */ 	return;                                                                                                        // 0.0
/*2506 */     case 0xf00d: /* fsts FPUL,FRn - FPSCR: Nothing */                                                           // 0.0
/*2508 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2510 */ 	tcg_gen_mov_i32(cpu_fregs[FREG(B11_8)], cpu_fpul);                                                             // 0.0
/*2512 */ 	return;                                                                                                        // 0.0
/*2514 */     case 0xf01d: /* flds FRm,FPUL - FPSCR: Nothing */                                                           // 0.0
/*2516 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2518 */ 	tcg_gen_mov_i32(cpu_fpul, cpu_fregs[FREG(B11_8)]);                                                             // 0.0
/*2520 */ 	return;                                                                                                        // 0.0
/*2522 */     case 0xf02d: /* float FPUL,FRn/DRn - FPSCR: R[PR,Enable.I]/W[Cause,Flag] */                                 // 0.0
/*2524 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2526 */ 	if (ctx->fpscr & FPSCR_PR) {                                                                                   // 0.0
/*2528 */ 	    TCGv_i64 fp;                                                                                               // 0.0
/*2530 */ 	    if (ctx->opcode & 0x0100)                                                                                  // 0.0
/*2532 */ 		break; /* illegal instruction */                                                                              // 0.0
/*2534 */ 	    fp = tcg_temp_new_i64();                                                                                   // 0.0
/*2536 */ 	    gen_helper_float_DT(fp, cpu_fpul);                                                                         // 0.0
/*2538 */ 	    gen_store_fpr64(fp, DREG(B11_8));                                                                          // 0.0
/*2540 */ 	    tcg_temp_free_i64(fp);                                                                                     // 0.0
/*2542 */ 	}                                                                                                              // 0.0
/*2544 */ 	else {                                                                                                         // 0.0
/*2546 */ 	    gen_helper_float_FT(cpu_fregs[FREG(B11_8)], cpu_fpul);                                                     // 0.0
/*2548 */ 	}                                                                                                              // 0.0
/*2550 */ 	return;                                                                                                        // 0.0
/*2552 */     case 0xf03d: /* ftrc FRm/DRm,FPUL - FPSCR: R[PR,Enable.V]/W[Cause,Flag] */                                  // 0.0
/*2554 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2556 */ 	if (ctx->fpscr & FPSCR_PR) {                                                                                   // 0.0
/*2558 */ 	    TCGv_i64 fp;                                                                                               // 0.0
/*2560 */ 	    if (ctx->opcode & 0x0100)                                                                                  // 0.0
/*2562 */ 		break; /* illegal instruction */                                                                              // 0.0
/*2564 */ 	    fp = tcg_temp_new_i64();                                                                                   // 0.0
/*2566 */ 	    gen_load_fpr64(fp, DREG(B11_8));                                                                           // 0.0
/*2568 */ 	    gen_helper_ftrc_DT(cpu_fpul, fp);                                                                          // 0.0
/*2570 */ 	    tcg_temp_free_i64(fp);                                                                                     // 0.0
/*2572 */ 	}                                                                                                              // 0.0
/*2574 */ 	else {                                                                                                         // 0.0
/*2576 */ 	    gen_helper_ftrc_FT(cpu_fpul, cpu_fregs[FREG(B11_8)]);                                                      // 0.0
/*2578 */ 	}                                                                                                              // 0.0
/*2580 */ 	return;                                                                                                        // 0.0
/*2582 */     case 0xf04d: /* fneg FRn/DRn - FPSCR: Nothing */                                                            // 0.0
/*2584 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2586 */ 	{                                                                                                              // 0.0
/*2588 */ 	    gen_helper_fneg_T(cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B11_8)]);                                         // 0.0
/*2590 */ 	}                                                                                                              // 0.0
/*2592 */ 	return;                                                                                                        // 0.0
/*2594 */     case 0xf05d: /* fabs FRn/DRn */                                                                             // 0.0
/*2596 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2598 */ 	if (ctx->fpscr & FPSCR_PR) {                                                                                   // 0.0
/*2600 */ 	    if (ctx->opcode & 0x0100)                                                                                  // 0.0
/*2602 */ 		break; /* illegal instruction */                                                                              // 0.0
/*2604 */ 	    TCGv_i64 fp = tcg_temp_new_i64();                                                                          // 0.0
/*2606 */ 	    gen_load_fpr64(fp, DREG(B11_8));                                                                           // 0.0
/*2608 */ 	    gen_helper_fabs_DT(fp, fp);                                                                                // 0.0
/*2610 */ 	    gen_store_fpr64(fp, DREG(B11_8));                                                                          // 0.0
/*2612 */ 	    tcg_temp_free_i64(fp);                                                                                     // 0.0
/*2614 */ 	} else {                                                                                                       // 0.0
/*2616 */ 	    gen_helper_fabs_FT(cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B11_8)]);                                        // 0.0
/*2618 */ 	}                                                                                                              // 0.0
/*2620 */ 	return;                                                                                                        // 0.0
/*2622 */     case 0xf06d: /* fsqrt FRn */                                                                                // 0.0
/*2624 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2626 */ 	if (ctx->fpscr & FPSCR_PR) {                                                                                   // 0.0
/*2628 */ 	    if (ctx->opcode & 0x0100)                                                                                  // 0.0
/*2630 */ 		break; /* illegal instruction */                                                                              // 0.0
/*2632 */ 	    TCGv_i64 fp = tcg_temp_new_i64();                                                                          // 0.0
/*2634 */ 	    gen_load_fpr64(fp, DREG(B11_8));                                                                           // 0.0
/*2636 */ 	    gen_helper_fsqrt_DT(fp, fp);                                                                               // 0.0
/*2638 */ 	    gen_store_fpr64(fp, DREG(B11_8));                                                                          // 0.0
/*2640 */ 	    tcg_temp_free_i64(fp);                                                                                     // 0.0
/*2642 */ 	} else {                                                                                                       // 0.0
/*2644 */ 	    gen_helper_fsqrt_FT(cpu_fregs[FREG(B11_8)], cpu_fregs[FREG(B11_8)]);                                       // 0.0
/*2646 */ 	}                                                                                                              // 0.0
/*2648 */ 	return;                                                                                                        // 0.0
/*2650 */     case 0xf07d: /* fsrra FRn */                                                                                // 0.0
/*2652 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2654 */ 	break;                                                                                                         // 0.0
/*2656 */     case 0xf08d: /* fldi0 FRn - FPSCR: R[PR] */                                                                 // 0.0
/*2658 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2660 */ 	if (!(ctx->fpscr & FPSCR_PR)) {                                                                                // 0.0
/*2662 */ 	    tcg_gen_movi_i32(cpu_fregs[FREG(B11_8)], 0);                                                               // 0.0
/*2664 */ 	}                                                                                                              // 0.0
/*2666 */ 	return;                                                                                                        // 0.0
/*2668 */     case 0xf09d: /* fldi1 FRn - FPSCR: R[PR] */                                                                 // 0.0
/*2670 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2672 */ 	if (!(ctx->fpscr & FPSCR_PR)) {                                                                                // 0.0
/*2674 */ 	    tcg_gen_movi_i32(cpu_fregs[FREG(B11_8)], 0x3f800000);                                                      // 0.0
/*2676 */ 	}                                                                                                              // 0.0
/*2678 */ 	return;                                                                                                        // 0.0
/*2680 */     case 0xf0ad: /* fcnvsd FPUL,DRn */                                                                          // 0.0
/*2682 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2684 */ 	{                                                                                                              // 0.0
/*2686 */ 	    TCGv_i64 fp = tcg_temp_new_i64();                                                                          // 0.0
/*2688 */ 	    gen_helper_fcnvsd_FT_DT(fp, cpu_fpul);                                                                     // 0.0
/*2690 */ 	    gen_store_fpr64(fp, DREG(B11_8));                                                                          // 0.0
/*2692 */ 	    tcg_temp_free_i64(fp);                                                                                     // 0.0
/*2694 */ 	}                                                                                                              // 0.0
/*2696 */ 	return;                                                                                                        // 0.0
/*2698 */     case 0xf0bd: /* fcnvds DRn,FPUL */                                                                          // 0.0
/*2700 */ 	CHECK_FPU_ENABLED                                                                                              // 0.0
/*2702 */ 	{                                                                                                              // 0.0
/*2704 */ 	    TCGv_i64 fp = tcg_temp_new_i64();                                                                          // 0.0
/*2706 */ 	    gen_load_fpr64(fp, DREG(B11_8));                                                                           // 0.0
/*2708 */ 	    gen_helper_fcnvds_DT_FT(cpu_fpul, fp);                                                                     // 0.0
/*2710 */ 	    tcg_temp_free_i64(fp);                                                                                     // 0.0
/*2712 */ 	}                                                                                                              // 0.0
/*2714 */ 	return;                                                                                                        // 0.0
/*2716 */     }                                                                                                           // 0.0
/*2718 */ #if 0                                                                                                           // 0.0
/*2720 */     fprintf(stderr, "unknown instruction 0x%04x at pc 0x%08x\n",                                                // 0.0
/*2722 */ 	    ctx->opcode, ctx->pc);                                                                                     // 0.0
/*2724 */     fflush(stderr);                                                                                             // 0.0
/*2726 */ #endif                                                                                                          // 0.0
/*2728 */     gen_helper_raise_illegal_instruction();                                                                     // 0.0
/*2730 */     ctx->bstate = BS_EXCP;                                                                                      // 0.0
/*2732 */ }                                                                                                               // 0.0
