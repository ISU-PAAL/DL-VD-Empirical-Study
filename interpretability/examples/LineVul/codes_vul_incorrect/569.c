// commit message qemu@c5a49c63fa (target=1, prob=0.25846833, correct=False): tcg: convert tb->cflags reads to tb_cflags(tb)
/*0    */ static target_ulong disas_insn(DisasContext *s, CPUState *cpu)                                // (2) 0.04299
/*2    */ {                                                                                             // (36) 0.001962
/*4    */     CPUX86State *env = cpu->env_ptr;                                                          // (10) 0.03125
/*6    */     int b, prefixes;                                                                          // (27) 0.01758
/*8    */     int shift;                                                                                // (32) 0.01173
/*10   */     TCGMemOp ot, aflag, dflag;                                                                // (11) 0.02931
/*12   */     int modrm, reg, rm, mod, op, opreg, val;                                                  // (3) 0.03914
/*14   */     target_ulong next_eip, tval;                                                              // (12) 0.02929
/*16   */     int rex_w, rex_r;                                                                         // (13) 0.02734
/*18   */     target_ulong pc_start = s->base.pc_next;                                                  // (4) 0.0371
/*22   */     s->pc_start = s->pc = pc_start;                                                           // (9) 0.03319
/*24   */     prefixes = 0;                                                                             // (29) 0.01562
/*26   */     s->override = -1;                                                                         // (20) 0.02148
/*28   */     rex_w = -1;                                                                               // (22) 0.02148
/*30   */     rex_r = 0;                                                                                // (25) 0.01953
/*32   */ #ifdef TARGET_X86_64                                                                          // (24) 0.01953
/*34   */     s->rex_x = 0;                                                                             // (21) 0.02148
/*36   */     s->rex_b = 0;                                                                             // (23) 0.02148
/*38   */     x86_64_hregs = 0;                                                                         // (14) 0.02734
/*40   */ #endif                                                                                        // (35) 0.003905
/*42   */     s->rip_offset = 0; /* for relative ip address */                                          // (8) 0.03319
/*44   */     s->vex_l = 0;                                                                             // (18) 0.02343
/*46   */     s->vex_v = 0;                                                                             // (19) 0.02343
/*48   */     if (sigsetjmp(s->jmpbuf, 0) != 0) {                                                       // (1) 0.04491
/*50   */         gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                                  // (0) 0.06248
/*52   */         return s->pc;                                                                         // (16) 0.02343
/*54   */     }                                                                                         // (34) 0.007811
/*58   */  next_byte:                                                                                   // (33) 0.007811
/*60   */     b = x86_ldub_code(env, s);                                                                // (7) 0.0332
/*62   */     /* Collect prefixes.  */                                                                  // (26) 0.01953
/*64   */     switch (b) {                                                                              // (28) 0.01562
/*66   */     case 0xf3:                                                                                // (31) 0.01562
/*68   */         prefixes |= PREFIX_REPZ;                                                              // (6) 0.0332
/*70   */         goto next_byte;                                                                       // (15) 0.02343
/*72   */     case 0xf2:                                                                                // (30) 0.01562
/*74   */         prefixes |= PREFIX_REPNZ;                                                             // (5) 0.03515
/*76   */         goto next_byte;                                                                       // (17) 0.02343
/*78   */     case 0xf0:                                                                                // 0.0
/*80   */         prefixes |= PREFIX_LOCK;                                                              // 0.0
/*82   */         goto next_byte;                                                                       // 0.0
/*84   */     case 0x2e:                                                                                // 0.0
/*86   */         s->override = R_CS;                                                                   // 0.0
/*88   */         goto next_byte;                                                                       // 0.0
/*90   */     case 0x36:                                                                                // 0.0
/*92   */         s->override = R_SS;                                                                   // 0.0
/*94   */         goto next_byte;                                                                       // 0.0
/*96   */     case 0x3e:                                                                                // 0.0
/*98   */         s->override = R_DS;                                                                   // 0.0
/*100  */         goto next_byte;                                                                       // 0.0
/*102  */     case 0x26:                                                                                // 0.0
/*104  */         s->override = R_ES;                                                                   // 0.0
/*106  */         goto next_byte;                                                                       // 0.0
/*108  */     case 0x64:                                                                                // 0.0
/*110  */         s->override = R_FS;                                                                   // 0.0
/*112  */         goto next_byte;                                                                       // 0.0
/*114  */     case 0x65:                                                                                // 0.0
/*116  */         s->override = R_GS;                                                                   // 0.0
/*118  */         goto next_byte;                                                                       // 0.0
/*120  */     case 0x66:                                                                                // 0.0
/*122  */         prefixes |= PREFIX_DATA;                                                              // 0.0
/*124  */         goto next_byte;                                                                       // 0.0
/*126  */     case 0x67:                                                                                // 0.0
/*128  */         prefixes |= PREFIX_ADR;                                                               // 0.0
/*130  */         goto next_byte;                                                                       // 0.0
/*132  */ #ifdef TARGET_X86_64                                                                          // 0.0
/*134  */     case 0x40 ... 0x4f:                                                                       // 0.0
/*136  */         if (CODE64(s)) {                                                                      // 0.0
/*138  */             /* REX prefix */                                                                  // 0.0
/*140  */             rex_w = (b >> 3) & 1;                                                             // 0.0
/*142  */             rex_r = (b & 0x4) << 1;                                                           // 0.0
/*144  */             s->rex_x = (b & 0x2) << 2;                                                        // 0.0
/*146  */             REX_B(s) = (b & 0x1) << 3;                                                        // 0.0
/*148  */             x86_64_hregs = 1; /* select uniform byte register addressing */                   // 0.0
/*150  */             goto next_byte;                                                                   // 0.0
/*152  */         }                                                                                     // 0.0
/*154  */         break;                                                                                // 0.0
/*156  */ #endif                                                                                        // 0.0
/*158  */     case 0xc5: /* 2-byte VEX */                                                               // 0.0
/*160  */     case 0xc4: /* 3-byte VEX */                                                               // 0.0
/*162  */         /* VEX prefixes cannot be used except in 32-bit mode.                                 // 0.0
/*164  */            Otherwise the instruction is LES or LDS.  */                                       // 0.0
/*166  */         if (s->code32 && !s->vm86) {                                                          // 0.0
/*168  */             static const int pp_prefix[4] = {                                                 // 0.0
/*170  */                 0, PREFIX_DATA, PREFIX_REPZ, PREFIX_REPNZ                                     // 0.0
/*172  */             };                                                                                // 0.0
/*174  */             int vex3, vex2 = x86_ldub_code(env, s);                                           // 0.0
/*178  */             if (!CODE64(s) && (vex2 & 0xc0) != 0xc0) {                                        // 0.0
/*180  */                 /* 4.1.4.6: In 32-bit mode, bits [7:6] must be 11b,                           // 0.0
/*182  */                    otherwise the instruction is LES or LDS.  */                               // 0.0
/*184  */                 break;                                                                        // 0.0
/*186  */             }                                                                                 // 0.0
/*188  */             s->pc++;                                                                          // 0.0
/*192  */             /* 4.1.1-4.1.3: No preceding lock, 66, f2, f3, or rex prefixes. */                // 0.0
/*194  */             if (prefixes & (PREFIX_REPZ | PREFIX_REPNZ                                        // 0.0
/*196  */                             | PREFIX_LOCK | PREFIX_DATA)) {                                   // 0.0
/*198  */                 goto illegal_op;                                                              // 0.0
/*200  */             }                                                                                 // 0.0
/*202  */ #ifdef TARGET_X86_64                                                                          // 0.0
/*204  */             if (x86_64_hregs) {                                                               // 0.0
/*206  */                 goto illegal_op;                                                              // 0.0
/*208  */             }                                                                                 // 0.0
/*210  */ #endif                                                                                        // 0.0
/*212  */             rex_r = (~vex2 >> 4) & 8;                                                         // 0.0
/*214  */             if (b == 0xc5) {                                                                  // 0.0
/*216  */                 vex3 = vex2;                                                                  // 0.0
/*218  */                 b = x86_ldub_code(env, s);                                                    // 0.0
/*220  */             } else {                                                                          // 0.0
/*222  */ #ifdef TARGET_X86_64                                                                          // 0.0
/*224  */                 s->rex_x = (~vex2 >> 3) & 8;                                                  // 0.0
/*226  */                 s->rex_b = (~vex2 >> 2) & 8;                                                  // 0.0
/*228  */ #endif                                                                                        // 0.0
/*230  */                 vex3 = x86_ldub_code(env, s);                                                 // 0.0
/*232  */                 rex_w = (vex3 >> 7) & 1;                                                      // 0.0
/*234  */                 switch (vex2 & 0x1f) {                                                        // 0.0
/*236  */                 case 0x01: /* Implied 0f leading opcode bytes.  */                            // 0.0
/*238  */                     b = x86_ldub_code(env, s) | 0x100;                                        // 0.0
/*240  */                     break;                                                                    // 0.0
/*242  */                 case 0x02: /* Implied 0f 38 leading opcode bytes.  */                         // 0.0
/*244  */                     b = 0x138;                                                                // 0.0
/*246  */                     break;                                                                    // 0.0
/*248  */                 case 0x03: /* Implied 0f 3a leading opcode bytes.  */                         // 0.0
/*250  */                     b = 0x13a;                                                                // 0.0
/*252  */                     break;                                                                    // 0.0
/*254  */                 default:   /* Reserved for future use.  */                                    // 0.0
/*256  */                     goto unknown_op;                                                          // 0.0
/*258  */                 }                                                                             // 0.0
/*260  */             }                                                                                 // 0.0
/*262  */             s->vex_v = (~vex3 >> 3) & 0xf;                                                    // 0.0
/*264  */             s->vex_l = (vex3 >> 2) & 1;                                                       // 0.0
/*266  */             prefixes |= pp_prefix[vex3 & 3] | PREFIX_VEX;                                     // 0.0
/*268  */         }                                                                                     // 0.0
/*270  */         break;                                                                                // 0.0
/*272  */     }                                                                                         // 0.0
/*276  */     /* Post-process prefixes.  */                                                             // 0.0
/*278  */     if (CODE64(s)) {                                                                          // 0.0
/*280  */         /* In 64-bit mode, the default data size is 32-bit.  Select 64-bit                    // 0.0
/*282  */            data with rex_w, and 16-bit data with 0x66; rex_w takes precedence                 // 0.0
/*284  */            over 0x66 if both are present.  */                                                 // 0.0
/*286  */         dflag = (rex_w > 0 ? MO_64 : prefixes & PREFIX_DATA ? MO_16 : MO_32);                 // 0.0
/*288  */         /* In 64-bit mode, 0x67 selects 32-bit addressing.  */                                // 0.0
/*290  */         aflag = (prefixes & PREFIX_ADR ? MO_32 : MO_64);                                      // 0.0
/*292  */     } else {                                                                                  // 0.0
/*294  */         /* In 16/32-bit mode, 0x66 selects the opposite data size.  */                        // 0.0
/*296  */         if (s->code32 ^ ((prefixes & PREFIX_DATA) != 0)) {                                    // 0.0
/*298  */             dflag = MO_32;                                                                    // 0.0
/*300  */         } else {                                                                              // 0.0
/*302  */             dflag = MO_16;                                                                    // 0.0
/*304  */         }                                                                                     // 0.0
/*306  */         /* In 16/32-bit mode, 0x67 selects the opposite addressing.  */                       // 0.0
/*308  */         if (s->code32 ^ ((prefixes & PREFIX_ADR) != 0)) {                                     // 0.0
/*310  */             aflag = MO_32;                                                                    // 0.0
/*312  */         }  else {                                                                             // 0.0
/*314  */             aflag = MO_16;                                                                    // 0.0
/*316  */         }                                                                                     // 0.0
/*318  */     }                                                                                         // 0.0
/*322  */     s->prefix = prefixes;                                                                     // 0.0
/*324  */     s->aflag = aflag;                                                                         // 0.0
/*326  */     s->dflag = dflag;                                                                         // 0.0
/*330  */     /* now check op code */                                                                   // 0.0
/*332  */  reswitch:                                                                                    // 0.0
/*334  */     switch(b) {                                                                               // 0.0
/*336  */     case 0x0f:                                                                                // 0.0
/*338  */         /**************************/                                                          // 0.0
/*340  */         /* extended op code */                                                                // 0.0
/*342  */         b = x86_ldub_code(env, s) | 0x100;                                                    // 0.0
/*344  */         goto reswitch;                                                                        // 0.0
/*348  */         /**************************/                                                          // 0.0
/*350  */         /* arith & logic */                                                                   // 0.0
/*352  */     case 0x00 ... 0x05:                                                                       // 0.0
/*354  */     case 0x08 ... 0x0d:                                                                       // 0.0
/*356  */     case 0x10 ... 0x15:                                                                       // 0.0
/*358  */     case 0x18 ... 0x1d:                                                                       // 0.0
/*360  */     case 0x20 ... 0x25:                                                                       // 0.0
/*362  */     case 0x28 ... 0x2d:                                                                       // 0.0
/*364  */     case 0x30 ... 0x35:                                                                       // 0.0
/*366  */     case 0x38 ... 0x3d:                                                                       // 0.0
/*368  */         {                                                                                     // 0.0
/*370  */             int op, f, val;                                                                   // 0.0
/*372  */             op = (b >> 3) & 7;                                                                // 0.0
/*374  */             f = (b >> 1) & 3;                                                                 // 0.0
/*378  */             ot = mo_b_d(b, dflag);                                                            // 0.0
/*382  */             switch(f) {                                                                       // 0.0
/*384  */             case 0: /* OP Ev, Gv */                                                           // 0.0
/*386  */                 modrm = x86_ldub_code(env, s);                                                // 0.0
/*388  */                 reg = ((modrm >> 3) & 7) | rex_r;                                             // 0.0
/*390  */                 mod = (modrm >> 6) & 3;                                                       // 0.0
/*392  */                 rm = (modrm & 7) | REX_B(s);                                                  // 0.0
/*394  */                 if (mod != 3) {                                                               // 0.0
/*396  */                     gen_lea_modrm(env, s, modrm);                                             // 0.0
/*398  */                     opreg = OR_TMP0;                                                          // 0.0
/*400  */                 } else if (op == OP_XORL && rm == reg) {                                      // 0.0
/*402  */                 xor_zero:                                                                     // 0.0
/*404  */                     /* xor reg, reg optimisation */                                           // 0.0
/*406  */                     set_cc_op(s, CC_OP_CLR);                                                  // 0.0
/*408  */                     tcg_gen_movi_tl(cpu_T0, 0);                                               // 0.0
/*410  */                     gen_op_mov_reg_v(ot, reg, cpu_T0);                                        // 0.0
/*412  */                     break;                                                                    // 0.0
/*414  */                 } else {                                                                      // 0.0
/*416  */                     opreg = rm;                                                               // 0.0
/*418  */                 }                                                                             // 0.0
/*420  */                 gen_op_mov_v_reg(ot, cpu_T1, reg);                                            // 0.0
/*422  */                 gen_op(s, op, ot, opreg);                                                     // 0.0
/*424  */                 break;                                                                        // 0.0
/*426  */             case 1: /* OP Gv, Ev */                                                           // 0.0
/*428  */                 modrm = x86_ldub_code(env, s);                                                // 0.0
/*430  */                 mod = (modrm >> 6) & 3;                                                       // 0.0
/*432  */                 reg = ((modrm >> 3) & 7) | rex_r;                                             // 0.0
/*434  */                 rm = (modrm & 7) | REX_B(s);                                                  // 0.0
/*436  */                 if (mod != 3) {                                                               // 0.0
/*438  */                     gen_lea_modrm(env, s, modrm);                                             // 0.0
/*440  */                     gen_op_ld_v(s, ot, cpu_T1, cpu_A0);                                       // 0.0
/*442  */                 } else if (op == OP_XORL && rm == reg) {                                      // 0.0
/*444  */                     goto xor_zero;                                                            // 0.0
/*446  */                 } else {                                                                      // 0.0
/*448  */                     gen_op_mov_v_reg(ot, cpu_T1, rm);                                         // 0.0
/*450  */                 }                                                                             // 0.0
/*452  */                 gen_op(s, op, ot, reg);                                                       // 0.0
/*454  */                 break;                                                                        // 0.0
/*456  */             case 2: /* OP A, Iv */                                                            // 0.0
/*458  */                 val = insn_get(env, s, ot);                                                   // 0.0
/*460  */                 tcg_gen_movi_tl(cpu_T1, val);                                                 // 0.0
/*462  */                 gen_op(s, op, ot, OR_EAX);                                                    // 0.0
/*464  */                 break;                                                                        // 0.0
/*466  */             }                                                                                 // 0.0
/*468  */         }                                                                                     // 0.0
/*470  */         break;                                                                                // 0.0
/*474  */     case 0x82:                                                                                // 0.0
/*476  */         if (CODE64(s))                                                                        // 0.0
/*478  */             goto illegal_op;                                                                  // 0.0
/*480  */     case 0x80: /* GRP1 */                                                                     // 0.0
/*482  */     case 0x81:                                                                                // 0.0
/*484  */     case 0x83:                                                                                // 0.0
/*486  */         {                                                                                     // 0.0
/*488  */             int val;                                                                          // 0.0
/*492  */             ot = mo_b_d(b, dflag);                                                            // 0.0
/*496  */             modrm = x86_ldub_code(env, s);                                                    // 0.0
/*498  */             mod = (modrm >> 6) & 3;                                                           // 0.0
/*500  */             rm = (modrm & 7) | REX_B(s);                                                      // 0.0
/*502  */             op = (modrm >> 3) & 7;                                                            // 0.0
/*506  */             if (mod != 3) {                                                                   // 0.0
/*508  */                 if (b == 0x83)                                                                // 0.0
/*510  */                     s->rip_offset = 1;                                                        // 0.0
/*512  */                 else                                                                          // 0.0
/*514  */                     s->rip_offset = insn_const_size(ot);                                      // 0.0
/*516  */                 gen_lea_modrm(env, s, modrm);                                                 // 0.0
/*518  */                 opreg = OR_TMP0;                                                              // 0.0
/*520  */             } else {                                                                          // 0.0
/*522  */                 opreg = rm;                                                                   // 0.0
/*524  */             }                                                                                 // 0.0
/*528  */             switch(b) {                                                                       // 0.0
/*530  */             default:                                                                          // 0.0
/*532  */             case 0x80:                                                                        // 0.0
/*534  */             case 0x81:                                                                        // 0.0
/*536  */             case 0x82:                                                                        // 0.0
/*538  */                 val = insn_get(env, s, ot);                                                   // 0.0
/*540  */                 break;                                                                        // 0.0
/*542  */             case 0x83:                                                                        // 0.0
/*544  */                 val = (int8_t)insn_get(env, s, MO_8);                                         // 0.0
/*546  */                 break;                                                                        // 0.0
/*548  */             }                                                                                 // 0.0
/*550  */             tcg_gen_movi_tl(cpu_T1, val);                                                     // 0.0
/*552  */             gen_op(s, op, ot, opreg);                                                         // 0.0
/*554  */         }                                                                                     // 0.0
/*556  */         break;                                                                                // 0.0
/*560  */         /**************************/                                                          // 0.0
/*562  */         /* inc, dec, and other misc arith */                                                  // 0.0
/*564  */     case 0x40 ... 0x47: /* inc Gv */                                                          // 0.0
/*566  */         ot = dflag;                                                                           // 0.0
/*568  */         gen_inc(s, ot, OR_EAX + (b & 7), 1);                                                  // 0.0
/*570  */         break;                                                                                // 0.0
/*572  */     case 0x48 ... 0x4f: /* dec Gv */                                                          // 0.0
/*574  */         ot = dflag;                                                                           // 0.0
/*576  */         gen_inc(s, ot, OR_EAX + (b & 7), -1);                                                 // 0.0
/*578  */         break;                                                                                // 0.0
/*580  */     case 0xf6: /* GRP3 */                                                                     // 0.0
/*582  */     case 0xf7:                                                                                // 0.0
/*584  */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*588  */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*590  */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*592  */         rm = (modrm & 7) | REX_B(s);                                                          // 0.0
/*594  */         op = (modrm >> 3) & 7;                                                                // 0.0
/*596  */         if (mod != 3) {                                                                       // 0.0
/*598  */             if (op == 0) {                                                                    // 0.0
/*600  */                 s->rip_offset = insn_const_size(ot);                                          // 0.0
/*602  */             }                                                                                 // 0.0
/*604  */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*606  */             /* For those below that handle locked memory, don't load here.  */                // 0.0
/*608  */             if (!(s->prefix & PREFIX_LOCK)                                                    // 0.0
/*610  */                 || op != 2) {                                                                 // 0.0
/*612  */                 gen_op_ld_v(s, ot, cpu_T0, cpu_A0);                                           // 0.0
/*614  */             }                                                                                 // 0.0
/*616  */         } else {                                                                              // 0.0
/*618  */             gen_op_mov_v_reg(ot, cpu_T0, rm);                                                 // 0.0
/*620  */         }                                                                                     // 0.0
/*624  */         switch(op) {                                                                          // 0.0
/*626  */         case 0: /* test */                                                                    // 0.0
/*628  */             val = insn_get(env, s, ot);                                                       // 0.0
/*630  */             tcg_gen_movi_tl(cpu_T1, val);                                                     // 0.0
/*632  */             gen_op_testl_T0_T1_cc();                                                          // 0.0
/*634  */             set_cc_op(s, CC_OP_LOGICB + ot);                                                  // 0.0
/*636  */             break;                                                                            // 0.0
/*638  */         case 2: /* not */                                                                     // 0.0
/*640  */             if (s->prefix & PREFIX_LOCK) {                                                    // 0.0
/*642  */                 if (mod == 3) {                                                               // 0.0
/*644  */                     goto illegal_op;                                                          // 0.0
/*646  */                 }                                                                             // 0.0
/*648  */                 tcg_gen_movi_tl(cpu_T0, ~0);                                                  // 0.0
/*650  */                 tcg_gen_atomic_xor_fetch_tl(cpu_T0, cpu_A0, cpu_T0,                           // 0.0
/*652  */                                             s->mem_index, ot | MO_LE);                        // 0.0
/*654  */             } else {                                                                          // 0.0
/*656  */                 tcg_gen_not_tl(cpu_T0, cpu_T0);                                               // 0.0
/*658  */                 if (mod != 3) {                                                               // 0.0
/*660  */                     gen_op_st_v(s, ot, cpu_T0, cpu_A0);                                       // 0.0
/*662  */                 } else {                                                                      // 0.0
/*664  */                     gen_op_mov_reg_v(ot, rm, cpu_T0);                                         // 0.0
/*666  */                 }                                                                             // 0.0
/*668  */             }                                                                                 // 0.0
/*670  */             break;                                                                            // 0.0
/*672  */         case 3: /* neg */                                                                     // 0.0
/*674  */             if (s->prefix & PREFIX_LOCK) {                                                    // 0.0
/*676  */                 TCGLabel *label1;                                                             // 0.0
/*678  */                 TCGv a0, t0, t1, t2;                                                          // 0.0
/*682  */                 if (mod == 3) {                                                               // 0.0
/*684  */                     goto illegal_op;                                                          // 0.0
/*686  */                 }                                                                             // 0.0
/*688  */                 a0 = tcg_temp_local_new();                                                    // 0.0
/*690  */                 t0 = tcg_temp_local_new();                                                    // 0.0
/*692  */                 label1 = gen_new_label();                                                     // 0.0
/*696  */                 tcg_gen_mov_tl(a0, cpu_A0);                                                   // 0.0
/*698  */                 tcg_gen_mov_tl(t0, cpu_T0);                                                   // 0.0
/*702  */                 gen_set_label(label1);                                                        // 0.0
/*704  */                 t1 = tcg_temp_new();                                                          // 0.0
/*706  */                 t2 = tcg_temp_new();                                                          // 0.0
/*708  */                 tcg_gen_mov_tl(t2, t0);                                                       // 0.0
/*710  */                 tcg_gen_neg_tl(t1, t0);                                                       // 0.0
/*712  */                 tcg_gen_atomic_cmpxchg_tl(t0, a0, t0, t1,                                     // 0.0
/*714  */                                           s->mem_index, ot | MO_LE);                          // 0.0
/*716  */                 tcg_temp_free(t1);                                                            // 0.0
/*718  */                 tcg_gen_brcond_tl(TCG_COND_NE, t0, t2, label1);                               // 0.0
/*722  */                 tcg_temp_free(t2);                                                            // 0.0
/*724  */                 tcg_temp_free(a0);                                                            // 0.0
/*726  */                 tcg_gen_mov_tl(cpu_T0, t0);                                                   // 0.0
/*728  */                 tcg_temp_free(t0);                                                            // 0.0
/*730  */             } else {                                                                          // 0.0
/*732  */                 tcg_gen_neg_tl(cpu_T0, cpu_T0);                                               // 0.0
/*734  */                 if (mod != 3) {                                                               // 0.0
/*736  */                     gen_op_st_v(s, ot, cpu_T0, cpu_A0);                                       // 0.0
/*738  */                 } else {                                                                      // 0.0
/*740  */                     gen_op_mov_reg_v(ot, rm, cpu_T0);                                         // 0.0
/*742  */                 }                                                                             // 0.0
/*744  */             }                                                                                 // 0.0
/*746  */             gen_op_update_neg_cc();                                                           // 0.0
/*748  */             set_cc_op(s, CC_OP_SUBB + ot);                                                    // 0.0
/*750  */             break;                                                                            // 0.0
/*752  */         case 4: /* mul */                                                                     // 0.0
/*754  */             switch(ot) {                                                                      // 0.0
/*756  */             case MO_8:                                                                        // 0.0
/*758  */                 gen_op_mov_v_reg(MO_8, cpu_T1, R_EAX);                                        // 0.0
/*760  */                 tcg_gen_ext8u_tl(cpu_T0, cpu_T0);                                             // 0.0
/*762  */                 tcg_gen_ext8u_tl(cpu_T1, cpu_T1);                                             // 0.0
/*764  */                 /* XXX: use 32 bit mul which could be faster */                               // 0.0
/*766  */                 tcg_gen_mul_tl(cpu_T0, cpu_T0, cpu_T1);                                       // 0.0
/*768  */                 gen_op_mov_reg_v(MO_16, R_EAX, cpu_T0);                                       // 0.0
/*770  */                 tcg_gen_mov_tl(cpu_cc_dst, cpu_T0);                                           // 0.0
/*772  */                 tcg_gen_andi_tl(cpu_cc_src, cpu_T0, 0xff00);                                  // 0.0
/*774  */                 set_cc_op(s, CC_OP_MULB);                                                     // 0.0
/*776  */                 break;                                                                        // 0.0
/*778  */             case MO_16:                                                                       // 0.0
/*780  */                 gen_op_mov_v_reg(MO_16, cpu_T1, R_EAX);                                       // 0.0
/*782  */                 tcg_gen_ext16u_tl(cpu_T0, cpu_T0);                                            // 0.0
/*784  */                 tcg_gen_ext16u_tl(cpu_T1, cpu_T1);                                            // 0.0
/*786  */                 /* XXX: use 32 bit mul which could be faster */                               // 0.0
/*788  */                 tcg_gen_mul_tl(cpu_T0, cpu_T0, cpu_T1);                                       // 0.0
/*790  */                 gen_op_mov_reg_v(MO_16, R_EAX, cpu_T0);                                       // 0.0
/*792  */                 tcg_gen_mov_tl(cpu_cc_dst, cpu_T0);                                           // 0.0
/*794  */                 tcg_gen_shri_tl(cpu_T0, cpu_T0, 16);                                          // 0.0
/*796  */                 gen_op_mov_reg_v(MO_16, R_EDX, cpu_T0);                                       // 0.0
/*798  */                 tcg_gen_mov_tl(cpu_cc_src, cpu_T0);                                           // 0.0
/*800  */                 set_cc_op(s, CC_OP_MULW);                                                     // 0.0
/*802  */                 break;                                                                        // 0.0
/*804  */             default:                                                                          // 0.0
/*806  */             case MO_32:                                                                       // 0.0
/*808  */                 tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                   // 0.0
/*810  */                 tcg_gen_trunc_tl_i32(cpu_tmp3_i32, cpu_regs[R_EAX]);                          // 0.0
/*812  */                 tcg_gen_mulu2_i32(cpu_tmp2_i32, cpu_tmp3_i32,                                 // 0.0
/*814  */                                   cpu_tmp2_i32, cpu_tmp3_i32);                                // 0.0
/*816  */                 tcg_gen_extu_i32_tl(cpu_regs[R_EAX], cpu_tmp2_i32);                           // 0.0
/*818  */                 tcg_gen_extu_i32_tl(cpu_regs[R_EDX], cpu_tmp3_i32);                           // 0.0
/*820  */                 tcg_gen_mov_tl(cpu_cc_dst, cpu_regs[R_EAX]);                                  // 0.0
/*822  */                 tcg_gen_mov_tl(cpu_cc_src, cpu_regs[R_EDX]);                                  // 0.0
/*824  */                 set_cc_op(s, CC_OP_MULL);                                                     // 0.0
/*826  */                 break;                                                                        // 0.0
/*828  */ #ifdef TARGET_X86_64                                                                          // 0.0
/*830  */             case MO_64:                                                                       // 0.0
/*832  */                 tcg_gen_mulu2_i64(cpu_regs[R_EAX], cpu_regs[R_EDX],                           // 0.0
/*834  */                                   cpu_T0, cpu_regs[R_EAX]);                                   // 0.0
/*836  */                 tcg_gen_mov_tl(cpu_cc_dst, cpu_regs[R_EAX]);                                  // 0.0
/*838  */                 tcg_gen_mov_tl(cpu_cc_src, cpu_regs[R_EDX]);                                  // 0.0
/*840  */                 set_cc_op(s, CC_OP_MULQ);                                                     // 0.0
/*842  */                 break;                                                                        // 0.0
/*844  */ #endif                                                                                        // 0.0
/*846  */             }                                                                                 // 0.0
/*848  */             break;                                                                            // 0.0
/*850  */         case 5: /* imul */                                                                    // 0.0
/*852  */             switch(ot) {                                                                      // 0.0
/*854  */             case MO_8:                                                                        // 0.0
/*856  */                 gen_op_mov_v_reg(MO_8, cpu_T1, R_EAX);                                        // 0.0
/*858  */                 tcg_gen_ext8s_tl(cpu_T0, cpu_T0);                                             // 0.0
/*860  */                 tcg_gen_ext8s_tl(cpu_T1, cpu_T1);                                             // 0.0
/*862  */                 /* XXX: use 32 bit mul which could be faster */                               // 0.0
/*864  */                 tcg_gen_mul_tl(cpu_T0, cpu_T0, cpu_T1);                                       // 0.0
/*866  */                 gen_op_mov_reg_v(MO_16, R_EAX, cpu_T0);                                       // 0.0
/*868  */                 tcg_gen_mov_tl(cpu_cc_dst, cpu_T0);                                           // 0.0
/*870  */                 tcg_gen_ext8s_tl(cpu_tmp0, cpu_T0);                                           // 0.0
/*872  */                 tcg_gen_sub_tl(cpu_cc_src, cpu_T0, cpu_tmp0);                                 // 0.0
/*874  */                 set_cc_op(s, CC_OP_MULB);                                                     // 0.0
/*876  */                 break;                                                                        // 0.0
/*878  */             case MO_16:                                                                       // 0.0
/*880  */                 gen_op_mov_v_reg(MO_16, cpu_T1, R_EAX);                                       // 0.0
/*882  */                 tcg_gen_ext16s_tl(cpu_T0, cpu_T0);                                            // 0.0
/*884  */                 tcg_gen_ext16s_tl(cpu_T1, cpu_T1);                                            // 0.0
/*886  */                 /* XXX: use 32 bit mul which could be faster */                               // 0.0
/*888  */                 tcg_gen_mul_tl(cpu_T0, cpu_T0, cpu_T1);                                       // 0.0
/*890  */                 gen_op_mov_reg_v(MO_16, R_EAX, cpu_T0);                                       // 0.0
/*892  */                 tcg_gen_mov_tl(cpu_cc_dst, cpu_T0);                                           // 0.0
/*894  */                 tcg_gen_ext16s_tl(cpu_tmp0, cpu_T0);                                          // 0.0
/*896  */                 tcg_gen_sub_tl(cpu_cc_src, cpu_T0, cpu_tmp0);                                 // 0.0
/*898  */                 tcg_gen_shri_tl(cpu_T0, cpu_T0, 16);                                          // 0.0
/*900  */                 gen_op_mov_reg_v(MO_16, R_EDX, cpu_T0);                                       // 0.0
/*902  */                 set_cc_op(s, CC_OP_MULW);                                                     // 0.0
/*904  */                 break;                                                                        // 0.0
/*906  */             default:                                                                          // 0.0
/*908  */             case MO_32:                                                                       // 0.0
/*910  */                 tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                   // 0.0
/*912  */                 tcg_gen_trunc_tl_i32(cpu_tmp3_i32, cpu_regs[R_EAX]);                          // 0.0
/*914  */                 tcg_gen_muls2_i32(cpu_tmp2_i32, cpu_tmp3_i32,                                 // 0.0
/*916  */                                   cpu_tmp2_i32, cpu_tmp3_i32);                                // 0.0
/*918  */                 tcg_gen_extu_i32_tl(cpu_regs[R_EAX], cpu_tmp2_i32);                           // 0.0
/*920  */                 tcg_gen_extu_i32_tl(cpu_regs[R_EDX], cpu_tmp3_i32);                           // 0.0
/*922  */                 tcg_gen_sari_i32(cpu_tmp2_i32, cpu_tmp2_i32, 31);                             // 0.0
/*924  */                 tcg_gen_mov_tl(cpu_cc_dst, cpu_regs[R_EAX]);                                  // 0.0
/*926  */                 tcg_gen_sub_i32(cpu_tmp2_i32, cpu_tmp2_i32, cpu_tmp3_i32);                    // 0.0
/*928  */                 tcg_gen_extu_i32_tl(cpu_cc_src, cpu_tmp2_i32);                                // 0.0
/*930  */                 set_cc_op(s, CC_OP_MULL);                                                     // 0.0
/*932  */                 break;                                                                        // 0.0
/*934  */ #ifdef TARGET_X86_64                                                                          // 0.0
/*936  */             case MO_64:                                                                       // 0.0
/*938  */                 tcg_gen_muls2_i64(cpu_regs[R_EAX], cpu_regs[R_EDX],                           // 0.0
/*940  */                                   cpu_T0, cpu_regs[R_EAX]);                                   // 0.0
/*942  */                 tcg_gen_mov_tl(cpu_cc_dst, cpu_regs[R_EAX]);                                  // 0.0
/*944  */                 tcg_gen_sari_tl(cpu_cc_src, cpu_regs[R_EAX], 63);                             // 0.0
/*946  */                 tcg_gen_sub_tl(cpu_cc_src, cpu_cc_src, cpu_regs[R_EDX]);                      // 0.0
/*948  */                 set_cc_op(s, CC_OP_MULQ);                                                     // 0.0
/*950  */                 break;                                                                        // 0.0
/*952  */ #endif                                                                                        // 0.0
/*954  */             }                                                                                 // 0.0
/*956  */             break;                                                                            // 0.0
/*958  */         case 6: /* div */                                                                     // 0.0
/*960  */             switch(ot) {                                                                      // 0.0
/*962  */             case MO_8:                                                                        // 0.0
/*964  */                 gen_helper_divb_AL(cpu_env, cpu_T0);                                          // 0.0
/*966  */                 break;                                                                        // 0.0
/*968  */             case MO_16:                                                                       // 0.0
/*970  */                 gen_helper_divw_AX(cpu_env, cpu_T0);                                          // 0.0
/*972  */                 break;                                                                        // 0.0
/*974  */             default:                                                                          // 0.0
/*976  */             case MO_32:                                                                       // 0.0
/*978  */                 gen_helper_divl_EAX(cpu_env, cpu_T0);                                         // 0.0
/*980  */                 break;                                                                        // 0.0
/*982  */ #ifdef TARGET_X86_64                                                                          // 0.0
/*984  */             case MO_64:                                                                       // 0.0
/*986  */                 gen_helper_divq_EAX(cpu_env, cpu_T0);                                         // 0.0
/*988  */                 break;                                                                        // 0.0
/*990  */ #endif                                                                                        // 0.0
/*992  */             }                                                                                 // 0.0
/*994  */             break;                                                                            // 0.0
/*996  */         case 7: /* idiv */                                                                    // 0.0
/*998  */             switch(ot) {                                                                      // 0.0
/*1000 */             case MO_8:                                                                        // 0.0
/*1002 */                 gen_helper_idivb_AL(cpu_env, cpu_T0);                                         // 0.0
/*1004 */                 break;                                                                        // 0.0
/*1006 */             case MO_16:                                                                       // 0.0
/*1008 */                 gen_helper_idivw_AX(cpu_env, cpu_T0);                                         // 0.0
/*1010 */                 break;                                                                        // 0.0
/*1012 */             default:                                                                          // 0.0
/*1014 */             case MO_32:                                                                       // 0.0
/*1016 */                 gen_helper_idivl_EAX(cpu_env, cpu_T0);                                        // 0.0
/*1018 */                 break;                                                                        // 0.0
/*1020 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*1022 */             case MO_64:                                                                       // 0.0
/*1024 */                 gen_helper_idivq_EAX(cpu_env, cpu_T0);                                        // 0.0
/*1026 */                 break;                                                                        // 0.0
/*1028 */ #endif                                                                                        // 0.0
/*1030 */             }                                                                                 // 0.0
/*1032 */             break;                                                                            // 0.0
/*1034 */         default:                                                                              // 0.0
/*1036 */             goto unknown_op;                                                                  // 0.0
/*1038 */         }                                                                                     // 0.0
/*1040 */         break;                                                                                // 0.0
/*1044 */     case 0xfe: /* GRP4 */                                                                     // 0.0
/*1046 */     case 0xff: /* GRP5 */                                                                     // 0.0
/*1048 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*1052 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*1054 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*1056 */         rm = (modrm & 7) | REX_B(s);                                                          // 0.0
/*1058 */         op = (modrm >> 3) & 7;                                                                // 0.0
/*1060 */         if (op >= 2 && b == 0xfe) {                                                           // 0.0
/*1062 */             goto unknown_op;                                                                  // 0.0
/*1064 */         }                                                                                     // 0.0
/*1066 */         if (CODE64(s)) {                                                                      // 0.0
/*1068 */             if (op == 2 || op == 4) {                                                         // 0.0
/*1070 */                 /* operand size for jumps is 64 bit */                                        // 0.0
/*1072 */                 ot = MO_64;                                                                   // 0.0
/*1074 */             } else if (op == 3 || op == 5) {                                                  // 0.0
/*1076 */                 ot = dflag != MO_16 ? MO_32 + (rex_w == 1) : MO_16;                           // 0.0
/*1078 */             } else if (op == 6) {                                                             // 0.0
/*1080 */                 /* default push size is 64 bit */                                             // 0.0
/*1082 */                 ot = mo_pushpop(s, dflag);                                                    // 0.0
/*1084 */             }                                                                                 // 0.0
/*1086 */         }                                                                                     // 0.0
/*1088 */         if (mod != 3) {                                                                       // 0.0
/*1090 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*1092 */             if (op >= 2 && op != 3 && op != 5)                                                // 0.0
/*1094 */                 gen_op_ld_v(s, ot, cpu_T0, cpu_A0);                                           // 0.0
/*1096 */         } else {                                                                              // 0.0
/*1098 */             gen_op_mov_v_reg(ot, cpu_T0, rm);                                                 // 0.0
/*1100 */         }                                                                                     // 0.0
/*1104 */         switch(op) {                                                                          // 0.0
/*1106 */         case 0: /* inc Ev */                                                                  // 0.0
/*1108 */             if (mod != 3)                                                                     // 0.0
/*1110 */                 opreg = OR_TMP0;                                                              // 0.0
/*1112 */             else                                                                              // 0.0
/*1114 */                 opreg = rm;                                                                   // 0.0
/*1116 */             gen_inc(s, ot, opreg, 1);                                                         // 0.0
/*1118 */             break;                                                                            // 0.0
/*1120 */         case 1: /* dec Ev */                                                                  // 0.0
/*1122 */             if (mod != 3)                                                                     // 0.0
/*1124 */                 opreg = OR_TMP0;                                                              // 0.0
/*1126 */             else                                                                              // 0.0
/*1128 */                 opreg = rm;                                                                   // 0.0
/*1130 */             gen_inc(s, ot, opreg, -1);                                                        // 0.0
/*1132 */             break;                                                                            // 0.0
/*1134 */         case 2: /* call Ev */                                                                 // 0.0
/*1136 */             /* XXX: optimize if memory (no 'and' is necessary) */                             // 0.0
/*1138 */             if (dflag == MO_16) {                                                             // 0.0
/*1140 */                 tcg_gen_ext16u_tl(cpu_T0, cpu_T0);                                            // 0.0
/*1142 */             }                                                                                 // 0.0
/*1144 */             next_eip = s->pc - s->cs_base;                                                    // 0.0
/*1146 */             tcg_gen_movi_tl(cpu_T1, next_eip);                                                // 0.0
/*1148 */             gen_push_v(s, cpu_T1);                                                            // 0.0
/*1150 */             gen_op_jmp_v(cpu_T0);                                                             // 0.0
/*1152 */             gen_bnd_jmp(s);                                                                   // 0.0
/*1154 */             gen_jr(s, cpu_T0);                                                                // 0.0
/*1156 */             break;                                                                            // 0.0
/*1158 */         case 3: /* lcall Ev */                                                                // 0.0
/*1160 */             gen_op_ld_v(s, ot, cpu_T1, cpu_A0);                                               // 0.0
/*1162 */             gen_add_A0_im(s, 1 << ot);                                                        // 0.0
/*1164 */             gen_op_ld_v(s, MO_16, cpu_T0, cpu_A0);                                            // 0.0
/*1166 */         do_lcall:                                                                             // 0.0
/*1168 */             if (s->pe && !s->vm86) {                                                          // 0.0
/*1170 */                 tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                   // 0.0
/*1172 */                 gen_helper_lcall_protected(cpu_env, cpu_tmp2_i32, cpu_T1,                     // 0.0
/*1174 */                                            tcg_const_i32(dflag - 1),                          // 0.0
/*1176 */                                            tcg_const_tl(s->pc - s->cs_base));                 // 0.0
/*1178 */             } else {                                                                          // 0.0
/*1180 */                 tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                   // 0.0
/*1182 */                 gen_helper_lcall_real(cpu_env, cpu_tmp2_i32, cpu_T1,                          // 0.0
/*1184 */                                       tcg_const_i32(dflag - 1),                               // 0.0
/*1186 */                                       tcg_const_i32(s->pc - s->cs_base));                     // 0.0
/*1188 */             }                                                                                 // 0.0
/*1190 */             tcg_gen_ld_tl(cpu_tmp4, cpu_env, offsetof(CPUX86State, eip));                     // 0.0
/*1192 */             gen_jr(s, cpu_tmp4);                                                              // 0.0
/*1194 */             break;                                                                            // 0.0
/*1196 */         case 4: /* jmp Ev */                                                                  // 0.0
/*1198 */             if (dflag == MO_16) {                                                             // 0.0
/*1200 */                 tcg_gen_ext16u_tl(cpu_T0, cpu_T0);                                            // 0.0
/*1202 */             }                                                                                 // 0.0
/*1204 */             gen_op_jmp_v(cpu_T0);                                                             // 0.0
/*1206 */             gen_bnd_jmp(s);                                                                   // 0.0
/*1208 */             gen_jr(s, cpu_T0);                                                                // 0.0
/*1210 */             break;                                                                            // 0.0
/*1212 */         case 5: /* ljmp Ev */                                                                 // 0.0
/*1214 */             gen_op_ld_v(s, ot, cpu_T1, cpu_A0);                                               // 0.0
/*1216 */             gen_add_A0_im(s, 1 << ot);                                                        // 0.0
/*1218 */             gen_op_ld_v(s, MO_16, cpu_T0, cpu_A0);                                            // 0.0
/*1220 */         do_ljmp:                                                                              // 0.0
/*1222 */             if (s->pe && !s->vm86) {                                                          // 0.0
/*1224 */                 tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                   // 0.0
/*1226 */                 gen_helper_ljmp_protected(cpu_env, cpu_tmp2_i32, cpu_T1,                      // 0.0
/*1228 */                                           tcg_const_tl(s->pc - s->cs_base));                  // 0.0
/*1230 */             } else {                                                                          // 0.0
/*1232 */                 gen_op_movl_seg_T0_vm(R_CS);                                                  // 0.0
/*1234 */                 gen_op_jmp_v(cpu_T1);                                                         // 0.0
/*1236 */             }                                                                                 // 0.0
/*1238 */             tcg_gen_ld_tl(cpu_tmp4, cpu_env, offsetof(CPUX86State, eip));                     // 0.0
/*1240 */             gen_jr(s, cpu_tmp4);                                                              // 0.0
/*1242 */             break;                                                                            // 0.0
/*1244 */         case 6: /* push Ev */                                                                 // 0.0
/*1246 */             gen_push_v(s, cpu_T0);                                                            // 0.0
/*1248 */             break;                                                                            // 0.0
/*1250 */         default:                                                                              // 0.0
/*1252 */             goto unknown_op;                                                                  // 0.0
/*1254 */         }                                                                                     // 0.0
/*1256 */         break;                                                                                // 0.0
/*1260 */     case 0x84: /* test Ev, Gv */                                                              // 0.0
/*1262 */     case 0x85:                                                                                // 0.0
/*1264 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*1268 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*1270 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*1274 */         gen_ldst_modrm(env, s, modrm, ot, OR_TMP0, 0);                                        // 0.0
/*1276 */         gen_op_mov_v_reg(ot, cpu_T1, reg);                                                    // 0.0
/*1278 */         gen_op_testl_T0_T1_cc();                                                              // 0.0
/*1280 */         set_cc_op(s, CC_OP_LOGICB + ot);                                                      // 0.0
/*1282 */         break;                                                                                // 0.0
/*1286 */     case 0xa8: /* test eAX, Iv */                                                             // 0.0
/*1288 */     case 0xa9:                                                                                // 0.0
/*1290 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*1292 */         val = insn_get(env, s, ot);                                                           // 0.0
/*1296 */         gen_op_mov_v_reg(ot, cpu_T0, OR_EAX);                                                 // 0.0
/*1298 */         tcg_gen_movi_tl(cpu_T1, val);                                                         // 0.0
/*1300 */         gen_op_testl_T0_T1_cc();                                                              // 0.0
/*1302 */         set_cc_op(s, CC_OP_LOGICB + ot);                                                      // 0.0
/*1304 */         break;                                                                                // 0.0
/*1308 */     case 0x98: /* CWDE/CBW */                                                                 // 0.0
/*1310 */         switch (dflag) {                                                                      // 0.0
/*1312 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*1314 */         case MO_64:                                                                           // 0.0
/*1316 */             gen_op_mov_v_reg(MO_32, cpu_T0, R_EAX);                                           // 0.0
/*1318 */             tcg_gen_ext32s_tl(cpu_T0, cpu_T0);                                                // 0.0
/*1320 */             gen_op_mov_reg_v(MO_64, R_EAX, cpu_T0);                                           // 0.0
/*1322 */             break;                                                                            // 0.0
/*1324 */ #endif                                                                                        // 0.0
/*1326 */         case MO_32:                                                                           // 0.0
/*1328 */             gen_op_mov_v_reg(MO_16, cpu_T0, R_EAX);                                           // 0.0
/*1330 */             tcg_gen_ext16s_tl(cpu_T0, cpu_T0);                                                // 0.0
/*1332 */             gen_op_mov_reg_v(MO_32, R_EAX, cpu_T0);                                           // 0.0
/*1334 */             break;                                                                            // 0.0
/*1336 */         case MO_16:                                                                           // 0.0
/*1338 */             gen_op_mov_v_reg(MO_8, cpu_T0, R_EAX);                                            // 0.0
/*1340 */             tcg_gen_ext8s_tl(cpu_T0, cpu_T0);                                                 // 0.0
/*1342 */             gen_op_mov_reg_v(MO_16, R_EAX, cpu_T0);                                           // 0.0
/*1344 */             break;                                                                            // 0.0
/*1346 */         default:                                                                              // 0.0
/*1348 */             tcg_abort();                                                                      // 0.0
/*1350 */         }                                                                                     // 0.0
/*1352 */         break;                                                                                // 0.0
/*1354 */     case 0x99: /* CDQ/CWD */                                                                  // 0.0
/*1356 */         switch (dflag) {                                                                      // 0.0
/*1358 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*1360 */         case MO_64:                                                                           // 0.0
/*1362 */             gen_op_mov_v_reg(MO_64, cpu_T0, R_EAX);                                           // 0.0
/*1364 */             tcg_gen_sari_tl(cpu_T0, cpu_T0, 63);                                              // 0.0
/*1366 */             gen_op_mov_reg_v(MO_64, R_EDX, cpu_T0);                                           // 0.0
/*1368 */             break;                                                                            // 0.0
/*1370 */ #endif                                                                                        // 0.0
/*1372 */         case MO_32:                                                                           // 0.0
/*1374 */             gen_op_mov_v_reg(MO_32, cpu_T0, R_EAX);                                           // 0.0
/*1376 */             tcg_gen_ext32s_tl(cpu_T0, cpu_T0);                                                // 0.0
/*1378 */             tcg_gen_sari_tl(cpu_T0, cpu_T0, 31);                                              // 0.0
/*1380 */             gen_op_mov_reg_v(MO_32, R_EDX, cpu_T0);                                           // 0.0
/*1382 */             break;                                                                            // 0.0
/*1384 */         case MO_16:                                                                           // 0.0
/*1386 */             gen_op_mov_v_reg(MO_16, cpu_T0, R_EAX);                                           // 0.0
/*1388 */             tcg_gen_ext16s_tl(cpu_T0, cpu_T0);                                                // 0.0
/*1390 */             tcg_gen_sari_tl(cpu_T0, cpu_T0, 15);                                              // 0.0
/*1392 */             gen_op_mov_reg_v(MO_16, R_EDX, cpu_T0);                                           // 0.0
/*1394 */             break;                                                                            // 0.0
/*1396 */         default:                                                                              // 0.0
/*1398 */             tcg_abort();                                                                      // 0.0
/*1400 */         }                                                                                     // 0.0
/*1402 */         break;                                                                                // 0.0
/*1404 */     case 0x1af: /* imul Gv, Ev */                                                             // 0.0
/*1406 */     case 0x69: /* imul Gv, Ev, I */                                                           // 0.0
/*1408 */     case 0x6b:                                                                                // 0.0
/*1410 */         ot = dflag;                                                                           // 0.0
/*1412 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*1414 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*1416 */         if (b == 0x69)                                                                        // 0.0
/*1418 */             s->rip_offset = insn_const_size(ot);                                              // 0.0
/*1420 */         else if (b == 0x6b)                                                                   // 0.0
/*1422 */             s->rip_offset = 1;                                                                // 0.0
/*1424 */         gen_ldst_modrm(env, s, modrm, ot, OR_TMP0, 0);                                        // 0.0
/*1426 */         if (b == 0x69) {                                                                      // 0.0
/*1428 */             val = insn_get(env, s, ot);                                                       // 0.0
/*1430 */             tcg_gen_movi_tl(cpu_T1, val);                                                     // 0.0
/*1432 */         } else if (b == 0x6b) {                                                               // 0.0
/*1434 */             val = (int8_t)insn_get(env, s, MO_8);                                             // 0.0
/*1436 */             tcg_gen_movi_tl(cpu_T1, val);                                                     // 0.0
/*1438 */         } else {                                                                              // 0.0
/*1440 */             gen_op_mov_v_reg(ot, cpu_T1, reg);                                                // 0.0
/*1442 */         }                                                                                     // 0.0
/*1444 */         switch (ot) {                                                                         // 0.0
/*1446 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*1448 */         case MO_64:                                                                           // 0.0
/*1450 */             tcg_gen_muls2_i64(cpu_regs[reg], cpu_T1, cpu_T0, cpu_T1);                         // 0.0
/*1452 */             tcg_gen_mov_tl(cpu_cc_dst, cpu_regs[reg]);                                        // 0.0
/*1454 */             tcg_gen_sari_tl(cpu_cc_src, cpu_cc_dst, 63);                                      // 0.0
/*1456 */             tcg_gen_sub_tl(cpu_cc_src, cpu_cc_src, cpu_T1);                                   // 0.0
/*1458 */             break;                                                                            // 0.0
/*1460 */ #endif                                                                                        // 0.0
/*1462 */         case MO_32:                                                                           // 0.0
/*1464 */             tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                       // 0.0
/*1466 */             tcg_gen_trunc_tl_i32(cpu_tmp3_i32, cpu_T1);                                       // 0.0
/*1468 */             tcg_gen_muls2_i32(cpu_tmp2_i32, cpu_tmp3_i32,                                     // 0.0
/*1470 */                               cpu_tmp2_i32, cpu_tmp3_i32);                                    // 0.0
/*1472 */             tcg_gen_extu_i32_tl(cpu_regs[reg], cpu_tmp2_i32);                                 // 0.0
/*1474 */             tcg_gen_sari_i32(cpu_tmp2_i32, cpu_tmp2_i32, 31);                                 // 0.0
/*1476 */             tcg_gen_mov_tl(cpu_cc_dst, cpu_regs[reg]);                                        // 0.0
/*1478 */             tcg_gen_sub_i32(cpu_tmp2_i32, cpu_tmp2_i32, cpu_tmp3_i32);                        // 0.0
/*1480 */             tcg_gen_extu_i32_tl(cpu_cc_src, cpu_tmp2_i32);                                    // 0.0
/*1482 */             break;                                                                            // 0.0
/*1484 */         default:                                                                              // 0.0
/*1486 */             tcg_gen_ext16s_tl(cpu_T0, cpu_T0);                                                // 0.0
/*1488 */             tcg_gen_ext16s_tl(cpu_T1, cpu_T1);                                                // 0.0
/*1490 */             /* XXX: use 32 bit mul which could be faster */                                   // 0.0
/*1492 */             tcg_gen_mul_tl(cpu_T0, cpu_T0, cpu_T1);                                           // 0.0
/*1494 */             tcg_gen_mov_tl(cpu_cc_dst, cpu_T0);                                               // 0.0
/*1496 */             tcg_gen_ext16s_tl(cpu_tmp0, cpu_T0);                                              // 0.0
/*1498 */             tcg_gen_sub_tl(cpu_cc_src, cpu_T0, cpu_tmp0);                                     // 0.0
/*1500 */             gen_op_mov_reg_v(ot, reg, cpu_T0);                                                // 0.0
/*1502 */             break;                                                                            // 0.0
/*1504 */         }                                                                                     // 0.0
/*1506 */         set_cc_op(s, CC_OP_MULB + ot);                                                        // 0.0
/*1508 */         break;                                                                                // 0.0
/*1510 */     case 0x1c0:                                                                               // 0.0
/*1512 */     case 0x1c1: /* xadd Ev, Gv */                                                             // 0.0
/*1514 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*1516 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*1518 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*1520 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*1522 */         gen_op_mov_v_reg(ot, cpu_T0, reg);                                                    // 0.0
/*1524 */         if (mod == 3) {                                                                       // 0.0
/*1526 */             rm = (modrm & 7) | REX_B(s);                                                      // 0.0
/*1528 */             gen_op_mov_v_reg(ot, cpu_T1, rm);                                                 // 0.0
/*1530 */             tcg_gen_add_tl(cpu_T0, cpu_T0, cpu_T1);                                           // 0.0
/*1532 */             gen_op_mov_reg_v(ot, reg, cpu_T1);                                                // 0.0
/*1534 */             gen_op_mov_reg_v(ot, rm, cpu_T0);                                                 // 0.0
/*1536 */         } else {                                                                              // 0.0
/*1538 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*1540 */             if (s->prefix & PREFIX_LOCK) {                                                    // 0.0
/*1542 */                 tcg_gen_atomic_fetch_add_tl(cpu_T1, cpu_A0, cpu_T0,                           // 0.0
/*1544 */                                             s->mem_index, ot | MO_LE);                        // 0.0
/*1546 */                 tcg_gen_add_tl(cpu_T0, cpu_T0, cpu_T1);                                       // 0.0
/*1548 */             } else {                                                                          // 0.0
/*1550 */                 gen_op_ld_v(s, ot, cpu_T1, cpu_A0);                                           // 0.0
/*1552 */                 tcg_gen_add_tl(cpu_T0, cpu_T0, cpu_T1);                                       // 0.0
/*1554 */                 gen_op_st_v(s, ot, cpu_T0, cpu_A0);                                           // 0.0
/*1556 */             }                                                                                 // 0.0
/*1558 */             gen_op_mov_reg_v(ot, reg, cpu_T1);                                                // 0.0
/*1560 */         }                                                                                     // 0.0
/*1562 */         gen_op_update2_cc();                                                                  // 0.0
/*1564 */         set_cc_op(s, CC_OP_ADDB + ot);                                                        // 0.0
/*1566 */         break;                                                                                // 0.0
/*1568 */     case 0x1b0:                                                                               // 0.0
/*1570 */     case 0x1b1: /* cmpxchg Ev, Gv */                                                          // 0.0
/*1572 */         {                                                                                     // 0.0
/*1574 */             TCGv oldv, newv, cmpv;                                                            // 0.0
/*1578 */             ot = mo_b_d(b, dflag);                                                            // 0.0
/*1580 */             modrm = x86_ldub_code(env, s);                                                    // 0.0
/*1582 */             reg = ((modrm >> 3) & 7) | rex_r;                                                 // 0.0
/*1584 */             mod = (modrm >> 6) & 3;                                                           // 0.0
/*1586 */             oldv = tcg_temp_new();                                                            // 0.0
/*1588 */             newv = tcg_temp_new();                                                            // 0.0
/*1590 */             cmpv = tcg_temp_new();                                                            // 0.0
/*1592 */             gen_op_mov_v_reg(ot, newv, reg);                                                  // 0.0
/*1594 */             tcg_gen_mov_tl(cmpv, cpu_regs[R_EAX]);                                            // 0.0
/*1598 */             if (s->prefix & PREFIX_LOCK) {                                                    // 0.0
/*1600 */                 if (mod == 3) {                                                               // 0.0
/*1602 */                     goto illegal_op;                                                          // 0.0
/*1604 */                 }                                                                             // 0.0
/*1606 */                 gen_lea_modrm(env, s, modrm);                                                 // 0.0
/*1608 */                 tcg_gen_atomic_cmpxchg_tl(oldv, cpu_A0, cmpv, newv,                           // 0.0
/*1610 */                                           s->mem_index, ot | MO_LE);                          // 0.0
/*1612 */                 gen_op_mov_reg_v(ot, R_EAX, oldv);                                            // 0.0
/*1614 */             } else {                                                                          // 0.0
/*1616 */                 if (mod == 3) {                                                               // 0.0
/*1618 */                     rm = (modrm & 7) | REX_B(s);                                              // 0.0
/*1620 */                     gen_op_mov_v_reg(ot, oldv, rm);                                           // 0.0
/*1622 */                 } else {                                                                      // 0.0
/*1624 */                     gen_lea_modrm(env, s, modrm);                                             // 0.0
/*1626 */                     gen_op_ld_v(s, ot, oldv, cpu_A0);                                         // 0.0
/*1628 */                     rm = 0; /* avoid warning */                                               // 0.0
/*1630 */                 }                                                                             // 0.0
/*1632 */                 gen_extu(ot, oldv);                                                           // 0.0
/*1634 */                 gen_extu(ot, cmpv);                                                           // 0.0
/*1636 */                 /* store value = (old == cmp ? new : old);  */                                // 0.0
/*1638 */                 tcg_gen_movcond_tl(TCG_COND_EQ, newv, oldv, cmpv, newv, oldv);                // 0.0
/*1640 */                 if (mod == 3) {                                                               // 0.0
/*1642 */                     gen_op_mov_reg_v(ot, R_EAX, oldv);                                        // 0.0
/*1644 */                     gen_op_mov_reg_v(ot, rm, newv);                                           // 0.0
/*1646 */                 } else {                                                                      // 0.0
/*1648 */                     /* Perform an unconditional store cycle like physical cpu;                // 0.0
/*1650 */                        must be before changing accumulator to ensure                          // 0.0
/*1652 */                        idempotency if the store faults and the instruction                    // 0.0
/*1654 */                        is restarted */                                                        // 0.0
/*1656 */                     gen_op_st_v(s, ot, newv, cpu_A0);                                         // 0.0
/*1658 */                     gen_op_mov_reg_v(ot, R_EAX, oldv);                                        // 0.0
/*1660 */                 }                                                                             // 0.0
/*1662 */             }                                                                                 // 0.0
/*1664 */             tcg_gen_mov_tl(cpu_cc_src, oldv);                                                 // 0.0
/*1666 */             tcg_gen_mov_tl(cpu_cc_srcT, cmpv);                                                // 0.0
/*1668 */             tcg_gen_sub_tl(cpu_cc_dst, cmpv, oldv);                                           // 0.0
/*1670 */             set_cc_op(s, CC_OP_SUBB + ot);                                                    // 0.0
/*1672 */             tcg_temp_free(oldv);                                                              // 0.0
/*1674 */             tcg_temp_free(newv);                                                              // 0.0
/*1676 */             tcg_temp_free(cmpv);                                                              // 0.0
/*1678 */         }                                                                                     // 0.0
/*1680 */         break;                                                                                // 0.0
/*1682 */     case 0x1c7: /* cmpxchg8b */                                                               // 0.0
/*1684 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*1686 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*1688 */         if ((mod == 3) || ((modrm & 0x38) != 0x8))                                            // 0.0
/*1690 */             goto illegal_op;                                                                  // 0.0
/*1692 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*1694 */         if (dflag == MO_64) {                                                                 // 0.0
/*1696 */             if (!(s->cpuid_ext_features & CPUID_EXT_CX16))                                    // 0.0
/*1698 */                 goto illegal_op;                                                              // 0.0
/*1700 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*1702 */             if ((s->prefix & PREFIX_LOCK) && parallel_cpus) {                                 // 0.0
/*1704 */                 gen_helper_cmpxchg16b(cpu_env, cpu_A0);                                       // 0.0
/*1706 */             } else {                                                                          // 0.0
/*1708 */                 gen_helper_cmpxchg16b_unlocked(cpu_env, cpu_A0);                              // 0.0
/*1710 */             }                                                                                 // 0.0
/*1712 */         } else                                                                                // 0.0
/*1714 */ #endif                                                                                        // 0.0
/*1716 */         {                                                                                     // 0.0
/*1718 */             if (!(s->cpuid_features & CPUID_CX8))                                             // 0.0
/*1720 */                 goto illegal_op;                                                              // 0.0
/*1722 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*1724 */             if ((s->prefix & PREFIX_LOCK) && parallel_cpus) {                                 // 0.0
/*1726 */                 gen_helper_cmpxchg8b(cpu_env, cpu_A0);                                        // 0.0
/*1728 */             } else {                                                                          // 0.0
/*1730 */                 gen_helper_cmpxchg8b_unlocked(cpu_env, cpu_A0);                               // 0.0
/*1732 */             }                                                                                 // 0.0
/*1734 */         }                                                                                     // 0.0
/*1736 */         set_cc_op(s, CC_OP_EFLAGS);                                                           // 0.0
/*1738 */         break;                                                                                // 0.0
/*1742 */         /**************************/                                                          // 0.0
/*1744 */         /* push/pop */                                                                        // 0.0
/*1746 */     case 0x50 ... 0x57: /* push */                                                            // 0.0
/*1748 */         gen_op_mov_v_reg(MO_32, cpu_T0, (b & 7) | REX_B(s));                                  // 0.0
/*1750 */         gen_push_v(s, cpu_T0);                                                                // 0.0
/*1752 */         break;                                                                                // 0.0
/*1754 */     case 0x58 ... 0x5f: /* pop */                                                             // 0.0
/*1756 */         ot = gen_pop_T0(s);                                                                   // 0.0
/*1758 */         /* NOTE: order is important for pop %sp */                                            // 0.0
/*1760 */         gen_pop_update(s, ot);                                                                // 0.0
/*1762 */         gen_op_mov_reg_v(ot, (b & 7) | REX_B(s), cpu_T0);                                     // 0.0
/*1764 */         break;                                                                                // 0.0
/*1766 */     case 0x60: /* pusha */                                                                    // 0.0
/*1768 */         if (CODE64(s))                                                                        // 0.0
/*1770 */             goto illegal_op;                                                                  // 0.0
/*1772 */         gen_pusha(s);                                                                         // 0.0
/*1774 */         break;                                                                                // 0.0
/*1776 */     case 0x61: /* popa */                                                                     // 0.0
/*1778 */         if (CODE64(s))                                                                        // 0.0
/*1780 */             goto illegal_op;                                                                  // 0.0
/*1782 */         gen_popa(s);                                                                          // 0.0
/*1784 */         break;                                                                                // 0.0
/*1786 */     case 0x68: /* push Iv */                                                                  // 0.0
/*1788 */     case 0x6a:                                                                                // 0.0
/*1790 */         ot = mo_pushpop(s, dflag);                                                            // 0.0
/*1792 */         if (b == 0x68)                                                                        // 0.0
/*1794 */             val = insn_get(env, s, ot);                                                       // 0.0
/*1796 */         else                                                                                  // 0.0
/*1798 */             val = (int8_t)insn_get(env, s, MO_8);                                             // 0.0
/*1800 */         tcg_gen_movi_tl(cpu_T0, val);                                                         // 0.0
/*1802 */         gen_push_v(s, cpu_T0);                                                                // 0.0
/*1804 */         break;                                                                                // 0.0
/*1806 */     case 0x8f: /* pop Ev */                                                                   // 0.0
/*1808 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*1810 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*1812 */         ot = gen_pop_T0(s);                                                                   // 0.0
/*1814 */         if (mod == 3) {                                                                       // 0.0
/*1816 */             /* NOTE: order is important for pop %sp */                                        // 0.0
/*1818 */             gen_pop_update(s, ot);                                                            // 0.0
/*1820 */             rm = (modrm & 7) | REX_B(s);                                                      // 0.0
/*1822 */             gen_op_mov_reg_v(ot, rm, cpu_T0);                                                 // 0.0
/*1824 */         } else {                                                                              // 0.0
/*1826 */             /* NOTE: order is important too for MMU exceptions */                             // 0.0
/*1828 */             s->popl_esp_hack = 1 << ot;                                                       // 0.0
/*1830 */             gen_ldst_modrm(env, s, modrm, ot, OR_TMP0, 1);                                    // 0.0
/*1832 */             s->popl_esp_hack = 0;                                                             // 0.0
/*1834 */             gen_pop_update(s, ot);                                                            // 0.0
/*1836 */         }                                                                                     // 0.0
/*1838 */         break;                                                                                // 0.0
/*1840 */     case 0xc8: /* enter */                                                                    // 0.0
/*1842 */         {                                                                                     // 0.0
/*1844 */             int level;                                                                        // 0.0
/*1846 */             val = x86_lduw_code(env, s);                                                      // 0.0
/*1848 */             level = x86_ldub_code(env, s);                                                    // 0.0
/*1850 */             gen_enter(s, val, level);                                                         // 0.0
/*1852 */         }                                                                                     // 0.0
/*1854 */         break;                                                                                // 0.0
/*1856 */     case 0xc9: /* leave */                                                                    // 0.0
/*1858 */         gen_leave(s);                                                                         // 0.0
/*1860 */         break;                                                                                // 0.0
/*1862 */     case 0x06: /* push es */                                                                  // 0.0
/*1864 */     case 0x0e: /* push cs */                                                                  // 0.0
/*1866 */     case 0x16: /* push ss */                                                                  // 0.0
/*1868 */     case 0x1e: /* push ds */                                                                  // 0.0
/*1870 */         if (CODE64(s))                                                                        // 0.0
/*1872 */             goto illegal_op;                                                                  // 0.0
/*1874 */         gen_op_movl_T0_seg(b >> 3);                                                           // 0.0
/*1876 */         gen_push_v(s, cpu_T0);                                                                // 0.0
/*1878 */         break;                                                                                // 0.0
/*1880 */     case 0x1a0: /* push fs */                                                                 // 0.0
/*1882 */     case 0x1a8: /* push gs */                                                                 // 0.0
/*1884 */         gen_op_movl_T0_seg((b >> 3) & 7);                                                     // 0.0
/*1886 */         gen_push_v(s, cpu_T0);                                                                // 0.0
/*1888 */         break;                                                                                // 0.0
/*1890 */     case 0x07: /* pop es */                                                                   // 0.0
/*1892 */     case 0x17: /* pop ss */                                                                   // 0.0
/*1894 */     case 0x1f: /* pop ds */                                                                   // 0.0
/*1896 */         if (CODE64(s))                                                                        // 0.0
/*1898 */             goto illegal_op;                                                                  // 0.0
/*1900 */         reg = b >> 3;                                                                         // 0.0
/*1902 */         ot = gen_pop_T0(s);                                                                   // 0.0
/*1904 */         gen_movl_seg_T0(s, reg);                                                              // 0.0
/*1906 */         gen_pop_update(s, ot);                                                                // 0.0
/*1908 */         /* Note that reg == R_SS in gen_movl_seg_T0 always sets is_jmp.  */                   // 0.0
/*1910 */         if (s->base.is_jmp) {                                                                 // 0.0
/*1912 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*1914 */             if (reg == R_SS) {                                                                // 0.0
/*1916 */                 s->tf = 0;                                                                    // 0.0
/*1918 */                 gen_eob_inhibit_irq(s, true);                                                 // 0.0
/*1920 */             } else {                                                                          // 0.0
/*1922 */                 gen_eob(s);                                                                   // 0.0
/*1924 */             }                                                                                 // 0.0
/*1926 */         }                                                                                     // 0.0
/*1928 */         break;                                                                                // 0.0
/*1930 */     case 0x1a1: /* pop fs */                                                                  // 0.0
/*1932 */     case 0x1a9: /* pop gs */                                                                  // 0.0
/*1934 */         ot = gen_pop_T0(s);                                                                   // 0.0
/*1936 */         gen_movl_seg_T0(s, (b >> 3) & 7);                                                     // 0.0
/*1938 */         gen_pop_update(s, ot);                                                                // 0.0
/*1940 */         if (s->base.is_jmp) {                                                                 // 0.0
/*1942 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*1944 */             gen_eob(s);                                                                       // 0.0
/*1946 */         }                                                                                     // 0.0
/*1948 */         break;                                                                                // 0.0
/*1952 */         /**************************/                                                          // 0.0
/*1954 */         /* mov */                                                                             // 0.0
/*1956 */     case 0x88:                                                                                // 0.0
/*1958 */     case 0x89: /* mov Gv, Ev */                                                               // 0.0
/*1960 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*1962 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*1964 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*1968 */         /* generate a generic store */                                                        // 0.0
/*1970 */         gen_ldst_modrm(env, s, modrm, ot, reg, 1);                                            // 0.0
/*1972 */         break;                                                                                // 0.0
/*1974 */     case 0xc6:                                                                                // 0.0
/*1976 */     case 0xc7: /* mov Ev, Iv */                                                               // 0.0
/*1978 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*1980 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*1982 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*1984 */         if (mod != 3) {                                                                       // 0.0
/*1986 */             s->rip_offset = insn_const_size(ot);                                              // 0.0
/*1988 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*1990 */         }                                                                                     // 0.0
/*1992 */         val = insn_get(env, s, ot);                                                           // 0.0
/*1994 */         tcg_gen_movi_tl(cpu_T0, val);                                                         // 0.0
/*1996 */         if (mod != 3) {                                                                       // 0.0
/*1998 */             gen_op_st_v(s, ot, cpu_T0, cpu_A0);                                               // 0.0
/*2000 */         } else {                                                                              // 0.0
/*2002 */             gen_op_mov_reg_v(ot, (modrm & 7) | REX_B(s), cpu_T0);                             // 0.0
/*2004 */         }                                                                                     // 0.0
/*2006 */         break;                                                                                // 0.0
/*2008 */     case 0x8a:                                                                                // 0.0
/*2010 */     case 0x8b: /* mov Ev, Gv */                                                               // 0.0
/*2012 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*2014 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*2016 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*2020 */         gen_ldst_modrm(env, s, modrm, ot, OR_TMP0, 0);                                        // 0.0
/*2022 */         gen_op_mov_reg_v(ot, reg, cpu_T0);                                                    // 0.0
/*2024 */         break;                                                                                // 0.0
/*2026 */     case 0x8e: /* mov seg, Gv */                                                              // 0.0
/*2028 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*2030 */         reg = (modrm >> 3) & 7;                                                               // 0.0
/*2032 */         if (reg >= 6 || reg == R_CS)                                                          // 0.0
/*2034 */             goto illegal_op;                                                                  // 0.0
/*2036 */         gen_ldst_modrm(env, s, modrm, MO_16, OR_TMP0, 0);                                     // 0.0
/*2038 */         gen_movl_seg_T0(s, reg);                                                              // 0.0
/*2040 */         /* Note that reg == R_SS in gen_movl_seg_T0 always sets is_jmp.  */                   // 0.0
/*2042 */         if (s->base.is_jmp) {                                                                 // 0.0
/*2044 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*2046 */             if (reg == R_SS) {                                                                // 0.0
/*2048 */                 s->tf = 0;                                                                    // 0.0
/*2050 */                 gen_eob_inhibit_irq(s, true);                                                 // 0.0
/*2052 */             } else {                                                                          // 0.0
/*2054 */                 gen_eob(s);                                                                   // 0.0
/*2056 */             }                                                                                 // 0.0
/*2058 */         }                                                                                     // 0.0
/*2060 */         break;                                                                                // 0.0
/*2062 */     case 0x8c: /* mov Gv, seg */                                                              // 0.0
/*2064 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*2066 */         reg = (modrm >> 3) & 7;                                                               // 0.0
/*2068 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*2070 */         if (reg >= 6)                                                                         // 0.0
/*2072 */             goto illegal_op;                                                                  // 0.0
/*2074 */         gen_op_movl_T0_seg(reg);                                                              // 0.0
/*2076 */         ot = mod == 3 ? dflag : MO_16;                                                        // 0.0
/*2078 */         gen_ldst_modrm(env, s, modrm, ot, OR_TMP0, 1);                                        // 0.0
/*2080 */         break;                                                                                // 0.0
/*2084 */     case 0x1b6: /* movzbS Gv, Eb */                                                           // 0.0
/*2086 */     case 0x1b7: /* movzwS Gv, Eb */                                                           // 0.0
/*2088 */     case 0x1be: /* movsbS Gv, Eb */                                                           // 0.0
/*2090 */     case 0x1bf: /* movswS Gv, Eb */                                                           // 0.0
/*2092 */         {                                                                                     // 0.0
/*2094 */             TCGMemOp d_ot;                                                                    // 0.0
/*2096 */             TCGMemOp s_ot;                                                                    // 0.0
/*2100 */             /* d_ot is the size of destination */                                             // 0.0
/*2102 */             d_ot = dflag;                                                                     // 0.0
/*2104 */             /* ot is the size of source */                                                    // 0.0
/*2106 */             ot = (b & 1) + MO_8;                                                              // 0.0
/*2108 */             /* s_ot is the sign+size of source */                                             // 0.0
/*2110 */             s_ot = b & 8 ? MO_SIGN | ot : ot;                                                 // 0.0
/*2114 */             modrm = x86_ldub_code(env, s);                                                    // 0.0
/*2116 */             reg = ((modrm >> 3) & 7) | rex_r;                                                 // 0.0
/*2118 */             mod = (modrm >> 6) & 3;                                                           // 0.0
/*2120 */             rm = (modrm & 7) | REX_B(s);                                                      // 0.0
/*2124 */             if (mod == 3) {                                                                   // 0.0
/*2126 */                 if (s_ot == MO_SB && byte_reg_is_xH(rm)) {                                    // 0.0
/*2128 */                     tcg_gen_sextract_tl(cpu_T0, cpu_regs[rm - 4], 8, 8);                      // 0.0
/*2130 */                 } else {                                                                      // 0.0
/*2132 */                     gen_op_mov_v_reg(ot, cpu_T0, rm);                                         // 0.0
/*2134 */                     switch (s_ot) {                                                           // 0.0
/*2136 */                     case MO_UB:                                                               // 0.0
/*2138 */                         tcg_gen_ext8u_tl(cpu_T0, cpu_T0);                                     // 0.0
/*2140 */                         break;                                                                // 0.0
/*2142 */                     case MO_SB:                                                               // 0.0
/*2144 */                         tcg_gen_ext8s_tl(cpu_T0, cpu_T0);                                     // 0.0
/*2146 */                         break;                                                                // 0.0
/*2148 */                     case MO_UW:                                                               // 0.0
/*2150 */                         tcg_gen_ext16u_tl(cpu_T0, cpu_T0);                                    // 0.0
/*2152 */                         break;                                                                // 0.0
/*2154 */                     default:                                                                  // 0.0
/*2156 */                     case MO_SW:                                                               // 0.0
/*2158 */                         tcg_gen_ext16s_tl(cpu_T0, cpu_T0);                                    // 0.0
/*2160 */                         break;                                                                // 0.0
/*2162 */                     }                                                                         // 0.0
/*2164 */                 }                                                                             // 0.0
/*2166 */                 gen_op_mov_reg_v(d_ot, reg, cpu_T0);                                          // 0.0
/*2168 */             } else {                                                                          // 0.0
/*2170 */                 gen_lea_modrm(env, s, modrm);                                                 // 0.0
/*2172 */                 gen_op_ld_v(s, s_ot, cpu_T0, cpu_A0);                                         // 0.0
/*2174 */                 gen_op_mov_reg_v(d_ot, reg, cpu_T0);                                          // 0.0
/*2176 */             }                                                                                 // 0.0
/*2178 */         }                                                                                     // 0.0
/*2180 */         break;                                                                                // 0.0
/*2184 */     case 0x8d: /* lea */                                                                      // 0.0
/*2186 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*2188 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*2190 */         if (mod == 3)                                                                         // 0.0
/*2192 */             goto illegal_op;                                                                  // 0.0
/*2194 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*2196 */         {                                                                                     // 0.0
/*2198 */             AddressParts a = gen_lea_modrm_0(env, s, modrm);                                  // 0.0
/*2200 */             TCGv ea = gen_lea_modrm_1(a);                                                     // 0.0
/*2202 */             gen_lea_v_seg(s, s->aflag, ea, -1, -1);                                           // 0.0
/*2204 */             gen_op_mov_reg_v(dflag, reg, cpu_A0);                                             // 0.0
/*2206 */         }                                                                                     // 0.0
/*2208 */         break;                                                                                // 0.0
/*2212 */     case 0xa0: /* mov EAX, Ov */                                                              // 0.0
/*2214 */     case 0xa1:                                                                                // 0.0
/*2216 */     case 0xa2: /* mov Ov, EAX */                                                              // 0.0
/*2218 */     case 0xa3:                                                                                // 0.0
/*2220 */         {                                                                                     // 0.0
/*2222 */             target_ulong offset_addr;                                                         // 0.0
/*2226 */             ot = mo_b_d(b, dflag);                                                            // 0.0
/*2228 */             switch (s->aflag) {                                                               // 0.0
/*2230 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*2232 */             case MO_64:                                                                       // 0.0
/*2234 */                 offset_addr = x86_ldq_code(env, s);                                           // 0.0
/*2236 */                 break;                                                                        // 0.0
/*2238 */ #endif                                                                                        // 0.0
/*2240 */             default:                                                                          // 0.0
/*2242 */                 offset_addr = insn_get(env, s, s->aflag);                                     // 0.0
/*2244 */                 break;                                                                        // 0.0
/*2246 */             }                                                                                 // 0.0
/*2248 */             tcg_gen_movi_tl(cpu_A0, offset_addr);                                             // 0.0
/*2250 */             gen_add_A0_ds_seg(s);                                                             // 0.0
/*2252 */             if ((b & 2) == 0) {                                                               // 0.0
/*2254 */                 gen_op_ld_v(s, ot, cpu_T0, cpu_A0);                                           // 0.0
/*2256 */                 gen_op_mov_reg_v(ot, R_EAX, cpu_T0);                                          // 0.0
/*2258 */             } else {                                                                          // 0.0
/*2260 */                 gen_op_mov_v_reg(ot, cpu_T0, R_EAX);                                          // 0.0
/*2262 */                 gen_op_st_v(s, ot, cpu_T0, cpu_A0);                                           // 0.0
/*2264 */             }                                                                                 // 0.0
/*2266 */         }                                                                                     // 0.0
/*2268 */         break;                                                                                // 0.0
/*2270 */     case 0xd7: /* xlat */                                                                     // 0.0
/*2272 */         tcg_gen_mov_tl(cpu_A0, cpu_regs[R_EBX]);                                              // 0.0
/*2274 */         tcg_gen_ext8u_tl(cpu_T0, cpu_regs[R_EAX]);                                            // 0.0
/*2276 */         tcg_gen_add_tl(cpu_A0, cpu_A0, cpu_T0);                                               // 0.0
/*2278 */         gen_extu(s->aflag, cpu_A0);                                                           // 0.0
/*2280 */         gen_add_A0_ds_seg(s);                                                                 // 0.0
/*2282 */         gen_op_ld_v(s, MO_8, cpu_T0, cpu_A0);                                                 // 0.0
/*2284 */         gen_op_mov_reg_v(MO_8, R_EAX, cpu_T0);                                                // 0.0
/*2286 */         break;                                                                                // 0.0
/*2288 */     case 0xb0 ... 0xb7: /* mov R, Ib */                                                       // 0.0
/*2290 */         val = insn_get(env, s, MO_8);                                                         // 0.0
/*2292 */         tcg_gen_movi_tl(cpu_T0, val);                                                         // 0.0
/*2294 */         gen_op_mov_reg_v(MO_8, (b & 7) | REX_B(s), cpu_T0);                                   // 0.0
/*2296 */         break;                                                                                // 0.0
/*2298 */     case 0xb8 ... 0xbf: /* mov R, Iv */                                                       // 0.0
/*2300 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*2302 */         if (dflag == MO_64) {                                                                 // 0.0
/*2304 */             uint64_t tmp;                                                                     // 0.0
/*2306 */             /* 64 bit case */                                                                 // 0.0
/*2308 */             tmp = x86_ldq_code(env, s);                                                       // 0.0
/*2310 */             reg = (b & 7) | REX_B(s);                                                         // 0.0
/*2312 */             tcg_gen_movi_tl(cpu_T0, tmp);                                                     // 0.0
/*2314 */             gen_op_mov_reg_v(MO_64, reg, cpu_T0);                                             // 0.0
/*2316 */         } else                                                                                // 0.0
/*2318 */ #endif                                                                                        // 0.0
/*2320 */         {                                                                                     // 0.0
/*2322 */             ot = dflag;                                                                       // 0.0
/*2324 */             val = insn_get(env, s, ot);                                                       // 0.0
/*2326 */             reg = (b & 7) | REX_B(s);                                                         // 0.0
/*2328 */             tcg_gen_movi_tl(cpu_T0, val);                                                     // 0.0
/*2330 */             gen_op_mov_reg_v(ot, reg, cpu_T0);                                                // 0.0
/*2332 */         }                                                                                     // 0.0
/*2334 */         break;                                                                                // 0.0
/*2338 */     case 0x91 ... 0x97: /* xchg R, EAX */                                                     // 0.0
/*2340 */     do_xchg_reg_eax:                                                                          // 0.0
/*2342 */         ot = dflag;                                                                           // 0.0
/*2344 */         reg = (b & 7) | REX_B(s);                                                             // 0.0
/*2346 */         rm = R_EAX;                                                                           // 0.0
/*2348 */         goto do_xchg_reg;                                                                     // 0.0
/*2350 */     case 0x86:                                                                                // 0.0
/*2352 */     case 0x87: /* xchg Ev, Gv */                                                              // 0.0
/*2354 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*2356 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*2358 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*2360 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*2362 */         if (mod == 3) {                                                                       // 0.0
/*2364 */             rm = (modrm & 7) | REX_B(s);                                                      // 0.0
/*2366 */         do_xchg_reg:                                                                          // 0.0
/*2368 */             gen_op_mov_v_reg(ot, cpu_T0, reg);                                                // 0.0
/*2370 */             gen_op_mov_v_reg(ot, cpu_T1, rm);                                                 // 0.0
/*2372 */             gen_op_mov_reg_v(ot, rm, cpu_T0);                                                 // 0.0
/*2374 */             gen_op_mov_reg_v(ot, reg, cpu_T1);                                                // 0.0
/*2376 */         } else {                                                                              // 0.0
/*2378 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*2380 */             gen_op_mov_v_reg(ot, cpu_T0, reg);                                                // 0.0
/*2382 */             /* for xchg, lock is implicit */                                                  // 0.0
/*2384 */             tcg_gen_atomic_xchg_tl(cpu_T1, cpu_A0, cpu_T0,                                    // 0.0
/*2386 */                                    s->mem_index, ot | MO_LE);                                 // 0.0
/*2388 */             gen_op_mov_reg_v(ot, reg, cpu_T1);                                                // 0.0
/*2390 */         }                                                                                     // 0.0
/*2392 */         break;                                                                                // 0.0
/*2394 */     case 0xc4: /* les Gv */                                                                   // 0.0
/*2396 */         /* In CODE64 this is VEX3; see above.  */                                             // 0.0
/*2398 */         op = R_ES;                                                                            // 0.0
/*2400 */         goto do_lxx;                                                                          // 0.0
/*2402 */     case 0xc5: /* lds Gv */                                                                   // 0.0
/*2404 */         /* In CODE64 this is VEX2; see above.  */                                             // 0.0
/*2406 */         op = R_DS;                                                                            // 0.0
/*2408 */         goto do_lxx;                                                                          // 0.0
/*2410 */     case 0x1b2: /* lss Gv */                                                                  // 0.0
/*2412 */         op = R_SS;                                                                            // 0.0
/*2414 */         goto do_lxx;                                                                          // 0.0
/*2416 */     case 0x1b4: /* lfs Gv */                                                                  // 0.0
/*2418 */         op = R_FS;                                                                            // 0.0
/*2420 */         goto do_lxx;                                                                          // 0.0
/*2422 */     case 0x1b5: /* lgs Gv */                                                                  // 0.0
/*2424 */         op = R_GS;                                                                            // 0.0
/*2426 */     do_lxx:                                                                                   // 0.0
/*2428 */         ot = dflag != MO_16 ? MO_32 : MO_16;                                                  // 0.0
/*2430 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*2432 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*2434 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*2436 */         if (mod == 3)                                                                         // 0.0
/*2438 */             goto illegal_op;                                                                  // 0.0
/*2440 */         gen_lea_modrm(env, s, modrm);                                                         // 0.0
/*2442 */         gen_op_ld_v(s, ot, cpu_T1, cpu_A0);                                                   // 0.0
/*2444 */         gen_add_A0_im(s, 1 << ot);                                                            // 0.0
/*2446 */         /* load the segment first to handle exceptions properly */                            // 0.0
/*2448 */         gen_op_ld_v(s, MO_16, cpu_T0, cpu_A0);                                                // 0.0
/*2450 */         gen_movl_seg_T0(s, op);                                                               // 0.0
/*2452 */         /* then put the data */                                                               // 0.0
/*2454 */         gen_op_mov_reg_v(ot, reg, cpu_T1);                                                    // 0.0
/*2456 */         if (s->base.is_jmp) {                                                                 // 0.0
/*2458 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*2460 */             gen_eob(s);                                                                       // 0.0
/*2462 */         }                                                                                     // 0.0
/*2464 */         break;                                                                                // 0.0
/*2468 */         /************************/                                                            // 0.0
/*2470 */         /* shifts */                                                                          // 0.0
/*2472 */     case 0xc0:                                                                                // 0.0
/*2474 */     case 0xc1:                                                                                // 0.0
/*2476 */         /* shift Ev,Ib */                                                                     // 0.0
/*2478 */         shift = 2;                                                                            // 0.0
/*2480 */     grp2:                                                                                     // 0.0
/*2482 */         {                                                                                     // 0.0
/*2484 */             ot = mo_b_d(b, dflag);                                                            // 0.0
/*2486 */             modrm = x86_ldub_code(env, s);                                                    // 0.0
/*2488 */             mod = (modrm >> 6) & 3;                                                           // 0.0
/*2490 */             op = (modrm >> 3) & 7;                                                            // 0.0
/*2494 */             if (mod != 3) {                                                                   // 0.0
/*2496 */                 if (shift == 2) {                                                             // 0.0
/*2498 */                     s->rip_offset = 1;                                                        // 0.0
/*2500 */                 }                                                                             // 0.0
/*2502 */                 gen_lea_modrm(env, s, modrm);                                                 // 0.0
/*2504 */                 opreg = OR_TMP0;                                                              // 0.0
/*2506 */             } else {                                                                          // 0.0
/*2508 */                 opreg = (modrm & 7) | REX_B(s);                                               // 0.0
/*2510 */             }                                                                                 // 0.0
/*2514 */             /* simpler op */                                                                  // 0.0
/*2516 */             if (shift == 0) {                                                                 // 0.0
/*2518 */                 gen_shift(s, op, ot, opreg, OR_ECX);                                          // 0.0
/*2520 */             } else {                                                                          // 0.0
/*2522 */                 if (shift == 2) {                                                             // 0.0
/*2524 */                     shift = x86_ldub_code(env, s);                                            // 0.0
/*2526 */                 }                                                                             // 0.0
/*2528 */                 gen_shifti(s, op, ot, opreg, shift);                                          // 0.0
/*2530 */             }                                                                                 // 0.0
/*2532 */         }                                                                                     // 0.0
/*2534 */         break;                                                                                // 0.0
/*2536 */     case 0xd0:                                                                                // 0.0
/*2538 */     case 0xd1:                                                                                // 0.0
/*2540 */         /* shift Ev,1 */                                                                      // 0.0
/*2542 */         shift = 1;                                                                            // 0.0
/*2544 */         goto grp2;                                                                            // 0.0
/*2546 */     case 0xd2:                                                                                // 0.0
/*2548 */     case 0xd3:                                                                                // 0.0
/*2550 */         /* shift Ev,cl */                                                                     // 0.0
/*2552 */         shift = 0;                                                                            // 0.0
/*2554 */         goto grp2;                                                                            // 0.0
/*2558 */     case 0x1a4: /* shld imm */                                                                // 0.0
/*2560 */         op = 0;                                                                               // 0.0
/*2562 */         shift = 1;                                                                            // 0.0
/*2564 */         goto do_shiftd;                                                                       // 0.0
/*2566 */     case 0x1a5: /* shld cl */                                                                 // 0.0
/*2568 */         op = 0;                                                                               // 0.0
/*2570 */         shift = 0;                                                                            // 0.0
/*2572 */         goto do_shiftd;                                                                       // 0.0
/*2574 */     case 0x1ac: /* shrd imm */                                                                // 0.0
/*2576 */         op = 1;                                                                               // 0.0
/*2578 */         shift = 1;                                                                            // 0.0
/*2580 */         goto do_shiftd;                                                                       // 0.0
/*2582 */     case 0x1ad: /* shrd cl */                                                                 // 0.0
/*2584 */         op = 1;                                                                               // 0.0
/*2586 */         shift = 0;                                                                            // 0.0
/*2588 */     do_shiftd:                                                                                // 0.0
/*2590 */         ot = dflag;                                                                           // 0.0
/*2592 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*2594 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*2596 */         rm = (modrm & 7) | REX_B(s);                                                          // 0.0
/*2598 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*2600 */         if (mod != 3) {                                                                       // 0.0
/*2602 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*2604 */             opreg = OR_TMP0;                                                                  // 0.0
/*2606 */         } else {                                                                              // 0.0
/*2608 */             opreg = rm;                                                                       // 0.0
/*2610 */         }                                                                                     // 0.0
/*2612 */         gen_op_mov_v_reg(ot, cpu_T1, reg);                                                    // 0.0
/*2616 */         if (shift) {                                                                          // 0.0
/*2618 */             TCGv imm = tcg_const_tl(x86_ldub_code(env, s));                                   // 0.0
/*2620 */             gen_shiftd_rm_T1(s, ot, opreg, op, imm);                                          // 0.0
/*2622 */             tcg_temp_free(imm);                                                               // 0.0
/*2624 */         } else {                                                                              // 0.0
/*2626 */             gen_shiftd_rm_T1(s, ot, opreg, op, cpu_regs[R_ECX]);                              // 0.0
/*2628 */         }                                                                                     // 0.0
/*2630 */         break;                                                                                // 0.0
/*2634 */         /************************/                                                            // 0.0
/*2636 */         /* floats */                                                                          // 0.0
/*2638 */     case 0xd8 ... 0xdf:                                                                       // 0.0
/*2640 */         if (s->flags & (HF_EM_MASK | HF_TS_MASK)) {                                           // 0.0
/*2642 */             /* if CR0.EM or CR0.TS are set, generate an FPU exception */                      // 0.0
/*2644 */             /* XXX: what to do if illegal op ? */                                             // 0.0
/*2646 */             gen_exception(s, EXCP07_PREX, pc_start - s->cs_base);                             // 0.0
/*2648 */             break;                                                                            // 0.0
/*2650 */         }                                                                                     // 0.0
/*2652 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*2654 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*2656 */         rm = modrm & 7;                                                                       // 0.0
/*2658 */         op = ((b & 7) << 3) | ((modrm >> 3) & 7);                                             // 0.0
/*2660 */         if (mod != 3) {                                                                       // 0.0
/*2662 */             /* memory op */                                                                   // 0.0
/*2664 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*2666 */             switch(op) {                                                                      // 0.0
/*2668 */             case 0x00 ... 0x07: /* fxxxs */                                                   // 0.0
/*2670 */             case 0x10 ... 0x17: /* fixxxl */                                                  // 0.0
/*2672 */             case 0x20 ... 0x27: /* fxxxl */                                                   // 0.0
/*2674 */             case 0x30 ... 0x37: /* fixxx */                                                   // 0.0
/*2676 */                 {                                                                             // 0.0
/*2678 */                     int op1;                                                                  // 0.0
/*2680 */                     op1 = op & 7;                                                             // 0.0
/*2684 */                     switch(op >> 4) {                                                         // 0.0
/*2686 */                     case 0:                                                                   // 0.0
/*2688 */                         tcg_gen_qemu_ld_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2690 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*2692 */                         gen_helper_flds_FT0(cpu_env, cpu_tmp2_i32);                           // 0.0
/*2694 */                         break;                                                                // 0.0
/*2696 */                     case 1:                                                                   // 0.0
/*2698 */                         tcg_gen_qemu_ld_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2700 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*2702 */                         gen_helper_fildl_FT0(cpu_env, cpu_tmp2_i32);                          // 0.0
/*2704 */                         break;                                                                // 0.0
/*2706 */                     case 2:                                                                   // 0.0
/*2708 */                         tcg_gen_qemu_ld_i64(cpu_tmp1_i64, cpu_A0,                             // 0.0
/*2710 */                                             s->mem_index, MO_LEQ);                            // 0.0
/*2712 */                         gen_helper_fldl_FT0(cpu_env, cpu_tmp1_i64);                           // 0.0
/*2714 */                         break;                                                                // 0.0
/*2716 */                     case 3:                                                                   // 0.0
/*2718 */                     default:                                                                  // 0.0
/*2720 */                         tcg_gen_qemu_ld_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2722 */                                             s->mem_index, MO_LESW);                           // 0.0
/*2724 */                         gen_helper_fildl_FT0(cpu_env, cpu_tmp2_i32);                          // 0.0
/*2726 */                         break;                                                                // 0.0
/*2728 */                     }                                                                         // 0.0
/*2732 */                     gen_helper_fp_arith_ST0_FT0(op1);                                         // 0.0
/*2734 */                     if (op1 == 3) {                                                           // 0.0
/*2736 */                         /* fcomp needs pop */                                                 // 0.0
/*2738 */                         gen_helper_fpop(cpu_env);                                             // 0.0
/*2740 */                     }                                                                         // 0.0
/*2742 */                 }                                                                             // 0.0
/*2744 */                 break;                                                                        // 0.0
/*2746 */             case 0x08: /* flds */                                                             // 0.0
/*2748 */             case 0x0a: /* fsts */                                                             // 0.0
/*2750 */             case 0x0b: /* fstps */                                                            // 0.0
/*2752 */             case 0x18 ... 0x1b: /* fildl, fisttpl, fistl, fistpl */                           // 0.0
/*2754 */             case 0x28 ... 0x2b: /* fldl, fisttpll, fstl, fstpl */                             // 0.0
/*2756 */             case 0x38 ... 0x3b: /* filds, fisttps, fists, fistps */                           // 0.0
/*2758 */                 switch(op & 7) {                                                              // 0.0
/*2760 */                 case 0:                                                                       // 0.0
/*2762 */                     switch(op >> 4) {                                                         // 0.0
/*2764 */                     case 0:                                                                   // 0.0
/*2766 */                         tcg_gen_qemu_ld_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2768 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*2770 */                         gen_helper_flds_ST0(cpu_env, cpu_tmp2_i32);                           // 0.0
/*2772 */                         break;                                                                // 0.0
/*2774 */                     case 1:                                                                   // 0.0
/*2776 */                         tcg_gen_qemu_ld_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2778 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*2780 */                         gen_helper_fildl_ST0(cpu_env, cpu_tmp2_i32);                          // 0.0
/*2782 */                         break;                                                                // 0.0
/*2784 */                     case 2:                                                                   // 0.0
/*2786 */                         tcg_gen_qemu_ld_i64(cpu_tmp1_i64, cpu_A0,                             // 0.0
/*2788 */                                             s->mem_index, MO_LEQ);                            // 0.0
/*2790 */                         gen_helper_fldl_ST0(cpu_env, cpu_tmp1_i64);                           // 0.0
/*2792 */                         break;                                                                // 0.0
/*2794 */                     case 3:                                                                   // 0.0
/*2796 */                     default:                                                                  // 0.0
/*2798 */                         tcg_gen_qemu_ld_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2800 */                                             s->mem_index, MO_LESW);                           // 0.0
/*2802 */                         gen_helper_fildl_ST0(cpu_env, cpu_tmp2_i32);                          // 0.0
/*2804 */                         break;                                                                // 0.0
/*2806 */                     }                                                                         // 0.0
/*2808 */                     break;                                                                    // 0.0
/*2810 */                 case 1:                                                                       // 0.0
/*2812 */                     /* XXX: the corresponding CPUID bit must be tested ! */                   // 0.0
/*2814 */                     switch(op >> 4) {                                                         // 0.0
/*2816 */                     case 1:                                                                   // 0.0
/*2818 */                         gen_helper_fisttl_ST0(cpu_tmp2_i32, cpu_env);                         // 0.0
/*2820 */                         tcg_gen_qemu_st_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2822 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*2824 */                         break;                                                                // 0.0
/*2826 */                     case 2:                                                                   // 0.0
/*2828 */                         gen_helper_fisttll_ST0(cpu_tmp1_i64, cpu_env);                        // 0.0
/*2830 */                         tcg_gen_qemu_st_i64(cpu_tmp1_i64, cpu_A0,                             // 0.0
/*2832 */                                             s->mem_index, MO_LEQ);                            // 0.0
/*2834 */                         break;                                                                // 0.0
/*2836 */                     case 3:                                                                   // 0.0
/*2838 */                     default:                                                                  // 0.0
/*2840 */                         gen_helper_fistt_ST0(cpu_tmp2_i32, cpu_env);                          // 0.0
/*2842 */                         tcg_gen_qemu_st_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2844 */                                             s->mem_index, MO_LEUW);                           // 0.0
/*2846 */                         break;                                                                // 0.0
/*2848 */                     }                                                                         // 0.0
/*2850 */                     gen_helper_fpop(cpu_env);                                                 // 0.0
/*2852 */                     break;                                                                    // 0.0
/*2854 */                 default:                                                                      // 0.0
/*2856 */                     switch(op >> 4) {                                                         // 0.0
/*2858 */                     case 0:                                                                   // 0.0
/*2860 */                         gen_helper_fsts_ST0(cpu_tmp2_i32, cpu_env);                           // 0.0
/*2862 */                         tcg_gen_qemu_st_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2864 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*2866 */                         break;                                                                // 0.0
/*2868 */                     case 1:                                                                   // 0.0
/*2870 */                         gen_helper_fistl_ST0(cpu_tmp2_i32, cpu_env);                          // 0.0
/*2872 */                         tcg_gen_qemu_st_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2874 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*2876 */                         break;                                                                // 0.0
/*2878 */                     case 2:                                                                   // 0.0
/*2880 */                         gen_helper_fstl_ST0(cpu_tmp1_i64, cpu_env);                           // 0.0
/*2882 */                         tcg_gen_qemu_st_i64(cpu_tmp1_i64, cpu_A0,                             // 0.0
/*2884 */                                             s->mem_index, MO_LEQ);                            // 0.0
/*2886 */                         break;                                                                // 0.0
/*2888 */                     case 3:                                                                   // 0.0
/*2890 */                     default:                                                                  // 0.0
/*2892 */                         gen_helper_fist_ST0(cpu_tmp2_i32, cpu_env);                           // 0.0
/*2894 */                         tcg_gen_qemu_st_i32(cpu_tmp2_i32, cpu_A0,                             // 0.0
/*2896 */                                             s->mem_index, MO_LEUW);                           // 0.0
/*2898 */                         break;                                                                // 0.0
/*2900 */                     }                                                                         // 0.0
/*2902 */                     if ((op & 7) == 3)                                                        // 0.0
/*2904 */                         gen_helper_fpop(cpu_env);                                             // 0.0
/*2906 */                     break;                                                                    // 0.0
/*2908 */                 }                                                                             // 0.0
/*2910 */                 break;                                                                        // 0.0
/*2912 */             case 0x0c: /* fldenv mem */                                                       // 0.0
/*2914 */                 gen_helper_fldenv(cpu_env, cpu_A0, tcg_const_i32(dflag - 1));                 // 0.0
/*2916 */                 break;                                                                        // 0.0
/*2918 */             case 0x0d: /* fldcw mem */                                                        // 0.0
/*2920 */                 tcg_gen_qemu_ld_i32(cpu_tmp2_i32, cpu_A0,                                     // 0.0
/*2922 */                                     s->mem_index, MO_LEUW);                                   // 0.0
/*2924 */                 gen_helper_fldcw(cpu_env, cpu_tmp2_i32);                                      // 0.0
/*2926 */                 break;                                                                        // 0.0
/*2928 */             case 0x0e: /* fnstenv mem */                                                      // 0.0
/*2930 */                 gen_helper_fstenv(cpu_env, cpu_A0, tcg_const_i32(dflag - 1));                 // 0.0
/*2932 */                 break;                                                                        // 0.0
/*2934 */             case 0x0f: /* fnstcw mem */                                                       // 0.0
/*2936 */                 gen_helper_fnstcw(cpu_tmp2_i32, cpu_env);                                     // 0.0
/*2938 */                 tcg_gen_qemu_st_i32(cpu_tmp2_i32, cpu_A0,                                     // 0.0
/*2940 */                                     s->mem_index, MO_LEUW);                                   // 0.0
/*2942 */                 break;                                                                        // 0.0
/*2944 */             case 0x1d: /* fldt mem */                                                         // 0.0
/*2946 */                 gen_helper_fldt_ST0(cpu_env, cpu_A0);                                         // 0.0
/*2948 */                 break;                                                                        // 0.0
/*2950 */             case 0x1f: /* fstpt mem */                                                        // 0.0
/*2952 */                 gen_helper_fstt_ST0(cpu_env, cpu_A0);                                         // 0.0
/*2954 */                 gen_helper_fpop(cpu_env);                                                     // 0.0
/*2956 */                 break;                                                                        // 0.0
/*2958 */             case 0x2c: /* frstor mem */                                                       // 0.0
/*2960 */                 gen_helper_frstor(cpu_env, cpu_A0, tcg_const_i32(dflag - 1));                 // 0.0
/*2962 */                 break;                                                                        // 0.0
/*2964 */             case 0x2e: /* fnsave mem */                                                       // 0.0
/*2966 */                 gen_helper_fsave(cpu_env, cpu_A0, tcg_const_i32(dflag - 1));                  // 0.0
/*2968 */                 break;                                                                        // 0.0
/*2970 */             case 0x2f: /* fnstsw mem */                                                       // 0.0
/*2972 */                 gen_helper_fnstsw(cpu_tmp2_i32, cpu_env);                                     // 0.0
/*2974 */                 tcg_gen_qemu_st_i32(cpu_tmp2_i32, cpu_A0,                                     // 0.0
/*2976 */                                     s->mem_index, MO_LEUW);                                   // 0.0
/*2978 */                 break;                                                                        // 0.0
/*2980 */             case 0x3c: /* fbld */                                                             // 0.0
/*2982 */                 gen_helper_fbld_ST0(cpu_env, cpu_A0);                                         // 0.0
/*2984 */                 break;                                                                        // 0.0
/*2986 */             case 0x3e: /* fbstp */                                                            // 0.0
/*2988 */                 gen_helper_fbst_ST0(cpu_env, cpu_A0);                                         // 0.0
/*2990 */                 gen_helper_fpop(cpu_env);                                                     // 0.0
/*2992 */                 break;                                                                        // 0.0
/*2994 */             case 0x3d: /* fildll */                                                           // 0.0
/*2996 */                 tcg_gen_qemu_ld_i64(cpu_tmp1_i64, cpu_A0, s->mem_index, MO_LEQ);              // 0.0
/*2998 */                 gen_helper_fildll_ST0(cpu_env, cpu_tmp1_i64);                                 // 0.0
/*3000 */                 break;                                                                        // 0.0
/*3002 */             case 0x3f: /* fistpll */                                                          // 0.0
/*3004 */                 gen_helper_fistll_ST0(cpu_tmp1_i64, cpu_env);                                 // 0.0
/*3006 */                 tcg_gen_qemu_st_i64(cpu_tmp1_i64, cpu_A0, s->mem_index, MO_LEQ);              // 0.0
/*3008 */                 gen_helper_fpop(cpu_env);                                                     // 0.0
/*3010 */                 break;                                                                        // 0.0
/*3012 */             default:                                                                          // 0.0
/*3014 */                 goto unknown_op;                                                              // 0.0
/*3016 */             }                                                                                 // 0.0
/*3018 */         } else {                                                                              // 0.0
/*3020 */             /* register float ops */                                                          // 0.0
/*3022 */             opreg = rm;                                                                       // 0.0
/*3026 */             switch(op) {                                                                      // 0.0
/*3028 */             case 0x08: /* fld sti */                                                          // 0.0
/*3030 */                 gen_helper_fpush(cpu_env);                                                    // 0.0
/*3032 */                 gen_helper_fmov_ST0_STN(cpu_env,                                              // 0.0
/*3034 */                                         tcg_const_i32((opreg + 1) & 7));                      // 0.0
/*3036 */                 break;                                                                        // 0.0
/*3038 */             case 0x09: /* fxchg sti */                                                        // 0.0
/*3040 */             case 0x29: /* fxchg4 sti, undocumented op */                                      // 0.0
/*3042 */             case 0x39: /* fxchg7 sti, undocumented op */                                      // 0.0
/*3044 */                 gen_helper_fxchg_ST0_STN(cpu_env, tcg_const_i32(opreg));                      // 0.0
/*3046 */                 break;                                                                        // 0.0
/*3048 */             case 0x0a: /* grp d9/2 */                                                         // 0.0
/*3050 */                 switch(rm) {                                                                  // 0.0
/*3052 */                 case 0: /* fnop */                                                            // 0.0
/*3054 */                     /* check exceptions (FreeBSD FPU probe) */                                // 0.0
/*3056 */                     gen_helper_fwait(cpu_env);                                                // 0.0
/*3058 */                     break;                                                                    // 0.0
/*3060 */                 default:                                                                      // 0.0
/*3062 */                     goto unknown_op;                                                          // 0.0
/*3064 */                 }                                                                             // 0.0
/*3066 */                 break;                                                                        // 0.0
/*3068 */             case 0x0c: /* grp d9/4 */                                                         // 0.0
/*3070 */                 switch(rm) {                                                                  // 0.0
/*3072 */                 case 0: /* fchs */                                                            // 0.0
/*3074 */                     gen_helper_fchs_ST0(cpu_env);                                             // 0.0
/*3076 */                     break;                                                                    // 0.0
/*3078 */                 case 1: /* fabs */                                                            // 0.0
/*3080 */                     gen_helper_fabs_ST0(cpu_env);                                             // 0.0
/*3082 */                     break;                                                                    // 0.0
/*3084 */                 case 4: /* ftst */                                                            // 0.0
/*3086 */                     gen_helper_fldz_FT0(cpu_env);                                             // 0.0
/*3088 */                     gen_helper_fcom_ST0_FT0(cpu_env);                                         // 0.0
/*3090 */                     break;                                                                    // 0.0
/*3092 */                 case 5: /* fxam */                                                            // 0.0
/*3094 */                     gen_helper_fxam_ST0(cpu_env);                                             // 0.0
/*3096 */                     break;                                                                    // 0.0
/*3098 */                 default:                                                                      // 0.0
/*3100 */                     goto unknown_op;                                                          // 0.0
/*3102 */                 }                                                                             // 0.0
/*3104 */                 break;                                                                        // 0.0
/*3106 */             case 0x0d: /* grp d9/5 */                                                         // 0.0
/*3108 */                 {                                                                             // 0.0
/*3110 */                     switch(rm) {                                                              // 0.0
/*3112 */                     case 0:                                                                   // 0.0
/*3114 */                         gen_helper_fpush(cpu_env);                                            // 0.0
/*3116 */                         gen_helper_fld1_ST0(cpu_env);                                         // 0.0
/*3118 */                         break;                                                                // 0.0
/*3120 */                     case 1:                                                                   // 0.0
/*3122 */                         gen_helper_fpush(cpu_env);                                            // 0.0
/*3124 */                         gen_helper_fldl2t_ST0(cpu_env);                                       // 0.0
/*3126 */                         break;                                                                // 0.0
/*3128 */                     case 2:                                                                   // 0.0
/*3130 */                         gen_helper_fpush(cpu_env);                                            // 0.0
/*3132 */                         gen_helper_fldl2e_ST0(cpu_env);                                       // 0.0
/*3134 */                         break;                                                                // 0.0
/*3136 */                     case 3:                                                                   // 0.0
/*3138 */                         gen_helper_fpush(cpu_env);                                            // 0.0
/*3140 */                         gen_helper_fldpi_ST0(cpu_env);                                        // 0.0
/*3142 */                         break;                                                                // 0.0
/*3144 */                     case 4:                                                                   // 0.0
/*3146 */                         gen_helper_fpush(cpu_env);                                            // 0.0
/*3148 */                         gen_helper_fldlg2_ST0(cpu_env);                                       // 0.0
/*3150 */                         break;                                                                // 0.0
/*3152 */                     case 5:                                                                   // 0.0
/*3154 */                         gen_helper_fpush(cpu_env);                                            // 0.0
/*3156 */                         gen_helper_fldln2_ST0(cpu_env);                                       // 0.0
/*3158 */                         break;                                                                // 0.0
/*3160 */                     case 6:                                                                   // 0.0
/*3162 */                         gen_helper_fpush(cpu_env);                                            // 0.0
/*3164 */                         gen_helper_fldz_ST0(cpu_env);                                         // 0.0
/*3166 */                         break;                                                                // 0.0
/*3168 */                     default:                                                                  // 0.0
/*3170 */                         goto unknown_op;                                                      // 0.0
/*3172 */                     }                                                                         // 0.0
/*3174 */                 }                                                                             // 0.0
/*3176 */                 break;                                                                        // 0.0
/*3178 */             case 0x0e: /* grp d9/6 */                                                         // 0.0
/*3180 */                 switch(rm) {                                                                  // 0.0
/*3182 */                 case 0: /* f2xm1 */                                                           // 0.0
/*3184 */                     gen_helper_f2xm1(cpu_env);                                                // 0.0
/*3186 */                     break;                                                                    // 0.0
/*3188 */                 case 1: /* fyl2x */                                                           // 0.0
/*3190 */                     gen_helper_fyl2x(cpu_env);                                                // 0.0
/*3192 */                     break;                                                                    // 0.0
/*3194 */                 case 2: /* fptan */                                                           // 0.0
/*3196 */                     gen_helper_fptan(cpu_env);                                                // 0.0
/*3198 */                     break;                                                                    // 0.0
/*3200 */                 case 3: /* fpatan */                                                          // 0.0
/*3202 */                     gen_helper_fpatan(cpu_env);                                               // 0.0
/*3204 */                     break;                                                                    // 0.0
/*3206 */                 case 4: /* fxtract */                                                         // 0.0
/*3208 */                     gen_helper_fxtract(cpu_env);                                              // 0.0
/*3210 */                     break;                                                                    // 0.0
/*3212 */                 case 5: /* fprem1 */                                                          // 0.0
/*3214 */                     gen_helper_fprem1(cpu_env);                                               // 0.0
/*3216 */                     break;                                                                    // 0.0
/*3218 */                 case 6: /* fdecstp */                                                         // 0.0
/*3220 */                     gen_helper_fdecstp(cpu_env);                                              // 0.0
/*3222 */                     break;                                                                    // 0.0
/*3224 */                 default:                                                                      // 0.0
/*3226 */                 case 7: /* fincstp */                                                         // 0.0
/*3228 */                     gen_helper_fincstp(cpu_env);                                              // 0.0
/*3230 */                     break;                                                                    // 0.0
/*3232 */                 }                                                                             // 0.0
/*3234 */                 break;                                                                        // 0.0
/*3236 */             case 0x0f: /* grp d9/7 */                                                         // 0.0
/*3238 */                 switch(rm) {                                                                  // 0.0
/*3240 */                 case 0: /* fprem */                                                           // 0.0
/*3242 */                     gen_helper_fprem(cpu_env);                                                // 0.0
/*3244 */                     break;                                                                    // 0.0
/*3246 */                 case 1: /* fyl2xp1 */                                                         // 0.0
/*3248 */                     gen_helper_fyl2xp1(cpu_env);                                              // 0.0
/*3250 */                     break;                                                                    // 0.0
/*3252 */                 case 2: /* fsqrt */                                                           // 0.0
/*3254 */                     gen_helper_fsqrt(cpu_env);                                                // 0.0
/*3256 */                     break;                                                                    // 0.0
/*3258 */                 case 3: /* fsincos */                                                         // 0.0
/*3260 */                     gen_helper_fsincos(cpu_env);                                              // 0.0
/*3262 */                     break;                                                                    // 0.0
/*3264 */                 case 5: /* fscale */                                                          // 0.0
/*3266 */                     gen_helper_fscale(cpu_env);                                               // 0.0
/*3268 */                     break;                                                                    // 0.0
/*3270 */                 case 4: /* frndint */                                                         // 0.0
/*3272 */                     gen_helper_frndint(cpu_env);                                              // 0.0
/*3274 */                     break;                                                                    // 0.0
/*3276 */                 case 6: /* fsin */                                                            // 0.0
/*3278 */                     gen_helper_fsin(cpu_env);                                                 // 0.0
/*3280 */                     break;                                                                    // 0.0
/*3282 */                 default:                                                                      // 0.0
/*3284 */                 case 7: /* fcos */                                                            // 0.0
/*3286 */                     gen_helper_fcos(cpu_env);                                                 // 0.0
/*3288 */                     break;                                                                    // 0.0
/*3290 */                 }                                                                             // 0.0
/*3292 */                 break;                                                                        // 0.0
/*3294 */             case 0x00: case 0x01: case 0x04 ... 0x07: /* fxxx st, sti */                      // 0.0
/*3296 */             case 0x20: case 0x21: case 0x24 ... 0x27: /* fxxx sti, st */                      // 0.0
/*3298 */             case 0x30: case 0x31: case 0x34 ... 0x37: /* fxxxp sti, st */                     // 0.0
/*3300 */                 {                                                                             // 0.0
/*3302 */                     int op1;                                                                  // 0.0
/*3306 */                     op1 = op & 7;                                                             // 0.0
/*3308 */                     if (op >= 0x20) {                                                         // 0.0
/*3310 */                         gen_helper_fp_arith_STN_ST0(op1, opreg);                              // 0.0
/*3312 */                         if (op >= 0x30)                                                       // 0.0
/*3314 */                             gen_helper_fpop(cpu_env);                                         // 0.0
/*3316 */                     } else {                                                                  // 0.0
/*3318 */                         gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(opreg));               // 0.0
/*3320 */                         gen_helper_fp_arith_ST0_FT0(op1);                                     // 0.0
/*3322 */                     }                                                                         // 0.0
/*3324 */                 }                                                                             // 0.0
/*3326 */                 break;                                                                        // 0.0
/*3328 */             case 0x02: /* fcom */                                                             // 0.0
/*3330 */             case 0x22: /* fcom2, undocumented op */                                           // 0.0
/*3332 */                 gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(opreg));                       // 0.0
/*3334 */                 gen_helper_fcom_ST0_FT0(cpu_env);                                             // 0.0
/*3336 */                 break;                                                                        // 0.0
/*3338 */             case 0x03: /* fcomp */                                                            // 0.0
/*3340 */             case 0x23: /* fcomp3, undocumented op */                                          // 0.0
/*3342 */             case 0x32: /* fcomp5, undocumented op */                                          // 0.0
/*3344 */                 gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(opreg));                       // 0.0
/*3346 */                 gen_helper_fcom_ST0_FT0(cpu_env);                                             // 0.0
/*3348 */                 gen_helper_fpop(cpu_env);                                                     // 0.0
/*3350 */                 break;                                                                        // 0.0
/*3352 */             case 0x15: /* da/5 */                                                             // 0.0
/*3354 */                 switch(rm) {                                                                  // 0.0
/*3356 */                 case 1: /* fucompp */                                                         // 0.0
/*3358 */                     gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(1));                       // 0.0
/*3360 */                     gen_helper_fucom_ST0_FT0(cpu_env);                                        // 0.0
/*3362 */                     gen_helper_fpop(cpu_env);                                                 // 0.0
/*3364 */                     gen_helper_fpop(cpu_env);                                                 // 0.0
/*3366 */                     break;                                                                    // 0.0
/*3368 */                 default:                                                                      // 0.0
/*3370 */                     goto unknown_op;                                                          // 0.0
/*3372 */                 }                                                                             // 0.0
/*3374 */                 break;                                                                        // 0.0
/*3376 */             case 0x1c:                                                                        // 0.0
/*3378 */                 switch(rm) {                                                                  // 0.0
/*3380 */                 case 0: /* feni (287 only, just do nop here) */                               // 0.0
/*3382 */                     break;                                                                    // 0.0
/*3384 */                 case 1: /* fdisi (287 only, just do nop here) */                              // 0.0
/*3386 */                     break;                                                                    // 0.0
/*3388 */                 case 2: /* fclex */                                                           // 0.0
/*3390 */                     gen_helper_fclex(cpu_env);                                                // 0.0
/*3392 */                     break;                                                                    // 0.0
/*3394 */                 case 3: /* fninit */                                                          // 0.0
/*3396 */                     gen_helper_fninit(cpu_env);                                               // 0.0
/*3398 */                     break;                                                                    // 0.0
/*3400 */                 case 4: /* fsetpm (287 only, just do nop here) */                             // 0.0
/*3402 */                     break;                                                                    // 0.0
/*3404 */                 default:                                                                      // 0.0
/*3406 */                     goto unknown_op;                                                          // 0.0
/*3408 */                 }                                                                             // 0.0
/*3410 */                 break;                                                                        // 0.0
/*3412 */             case 0x1d: /* fucomi */                                                           // 0.0
/*3414 */                 if (!(s->cpuid_features & CPUID_CMOV)) {                                      // 0.0
/*3416 */                     goto illegal_op;                                                          // 0.0
/*3418 */                 }                                                                             // 0.0
/*3420 */                 gen_update_cc_op(s);                                                          // 0.0
/*3422 */                 gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(opreg));                       // 0.0
/*3424 */                 gen_helper_fucomi_ST0_FT0(cpu_env);                                           // 0.0
/*3426 */                 set_cc_op(s, CC_OP_EFLAGS);                                                   // 0.0
/*3428 */                 break;                                                                        // 0.0
/*3430 */             case 0x1e: /* fcomi */                                                            // 0.0
/*3432 */                 if (!(s->cpuid_features & CPUID_CMOV)) {                                      // 0.0
/*3434 */                     goto illegal_op;                                                          // 0.0
/*3436 */                 }                                                                             // 0.0
/*3438 */                 gen_update_cc_op(s);                                                          // 0.0
/*3440 */                 gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(opreg));                       // 0.0
/*3442 */                 gen_helper_fcomi_ST0_FT0(cpu_env);                                            // 0.0
/*3444 */                 set_cc_op(s, CC_OP_EFLAGS);                                                   // 0.0
/*3446 */                 break;                                                                        // 0.0
/*3448 */             case 0x28: /* ffree sti */                                                        // 0.0
/*3450 */                 gen_helper_ffree_STN(cpu_env, tcg_const_i32(opreg));                          // 0.0
/*3452 */                 break;                                                                        // 0.0
/*3454 */             case 0x2a: /* fst sti */                                                          // 0.0
/*3456 */                 gen_helper_fmov_STN_ST0(cpu_env, tcg_const_i32(opreg));                       // 0.0
/*3458 */                 break;                                                                        // 0.0
/*3460 */             case 0x2b: /* fstp sti */                                                         // 0.0
/*3462 */             case 0x0b: /* fstp1 sti, undocumented op */                                       // 0.0
/*3464 */             case 0x3a: /* fstp8 sti, undocumented op */                                       // 0.0
/*3466 */             case 0x3b: /* fstp9 sti, undocumented op */                                       // 0.0
/*3468 */                 gen_helper_fmov_STN_ST0(cpu_env, tcg_const_i32(opreg));                       // 0.0
/*3470 */                 gen_helper_fpop(cpu_env);                                                     // 0.0
/*3472 */                 break;                                                                        // 0.0
/*3474 */             case 0x2c: /* fucom st(i) */                                                      // 0.0
/*3476 */                 gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(opreg));                       // 0.0
/*3478 */                 gen_helper_fucom_ST0_FT0(cpu_env);                                            // 0.0
/*3480 */                 break;                                                                        // 0.0
/*3482 */             case 0x2d: /* fucomp st(i) */                                                     // 0.0
/*3484 */                 gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(opreg));                       // 0.0
/*3486 */                 gen_helper_fucom_ST0_FT0(cpu_env);                                            // 0.0
/*3488 */                 gen_helper_fpop(cpu_env);                                                     // 0.0
/*3490 */                 break;                                                                        // 0.0
/*3492 */             case 0x33: /* de/3 */                                                             // 0.0
/*3494 */                 switch(rm) {                                                                  // 0.0
/*3496 */                 case 1: /* fcompp */                                                          // 0.0
/*3498 */                     gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(1));                       // 0.0
/*3500 */                     gen_helper_fcom_ST0_FT0(cpu_env);                                         // 0.0
/*3502 */                     gen_helper_fpop(cpu_env);                                                 // 0.0
/*3504 */                     gen_helper_fpop(cpu_env);                                                 // 0.0
/*3506 */                     break;                                                                    // 0.0
/*3508 */                 default:                                                                      // 0.0
/*3510 */                     goto unknown_op;                                                          // 0.0
/*3512 */                 }                                                                             // 0.0
/*3514 */                 break;                                                                        // 0.0
/*3516 */             case 0x38: /* ffreep sti, undocumented op */                                      // 0.0
/*3518 */                 gen_helper_ffree_STN(cpu_env, tcg_const_i32(opreg));                          // 0.0
/*3520 */                 gen_helper_fpop(cpu_env);                                                     // 0.0
/*3522 */                 break;                                                                        // 0.0
/*3524 */             case 0x3c: /* df/4 */                                                             // 0.0
/*3526 */                 switch(rm) {                                                                  // 0.0
/*3528 */                 case 0:                                                                       // 0.0
/*3530 */                     gen_helper_fnstsw(cpu_tmp2_i32, cpu_env);                                 // 0.0
/*3532 */                     tcg_gen_extu_i32_tl(cpu_T0, cpu_tmp2_i32);                                // 0.0
/*3534 */                     gen_op_mov_reg_v(MO_16, R_EAX, cpu_T0);                                   // 0.0
/*3536 */                     break;                                                                    // 0.0
/*3538 */                 default:                                                                      // 0.0
/*3540 */                     goto unknown_op;                                                          // 0.0
/*3542 */                 }                                                                             // 0.0
/*3544 */                 break;                                                                        // 0.0
/*3546 */             case 0x3d: /* fucomip */                                                          // 0.0
/*3548 */                 if (!(s->cpuid_features & CPUID_CMOV)) {                                      // 0.0
/*3550 */                     goto illegal_op;                                                          // 0.0
/*3552 */                 }                                                                             // 0.0
/*3554 */                 gen_update_cc_op(s);                                                          // 0.0
/*3556 */                 gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(opreg));                       // 0.0
/*3558 */                 gen_helper_fucomi_ST0_FT0(cpu_env);                                           // 0.0
/*3560 */                 gen_helper_fpop(cpu_env);                                                     // 0.0
/*3562 */                 set_cc_op(s, CC_OP_EFLAGS);                                                   // 0.0
/*3564 */                 break;                                                                        // 0.0
/*3566 */             case 0x3e: /* fcomip */                                                           // 0.0
/*3568 */                 if (!(s->cpuid_features & CPUID_CMOV)) {                                      // 0.0
/*3570 */                     goto illegal_op;                                                          // 0.0
/*3572 */                 }                                                                             // 0.0
/*3574 */                 gen_update_cc_op(s);                                                          // 0.0
/*3576 */                 gen_helper_fmov_FT0_STN(cpu_env, tcg_const_i32(opreg));                       // 0.0
/*3578 */                 gen_helper_fcomi_ST0_FT0(cpu_env);                                            // 0.0
/*3580 */                 gen_helper_fpop(cpu_env);                                                     // 0.0
/*3582 */                 set_cc_op(s, CC_OP_EFLAGS);                                                   // 0.0
/*3584 */                 break;                                                                        // 0.0
/*3586 */             case 0x10 ... 0x13: /* fcmovxx */                                                 // 0.0
/*3588 */             case 0x18 ... 0x1b:                                                               // 0.0
/*3590 */                 {                                                                             // 0.0
/*3592 */                     int op1;                                                                  // 0.0
/*3594 */                     TCGLabel *l1;                                                             // 0.0
/*3596 */                     static const uint8_t fcmov_cc[8] = {                                      // 0.0
/*3598 */                         (JCC_B << 1),                                                         // 0.0
/*3600 */                         (JCC_Z << 1),                                                         // 0.0
/*3602 */                         (JCC_BE << 1),                                                        // 0.0
/*3604 */                         (JCC_P << 1),                                                         // 0.0
/*3606 */                     };                                                                        // 0.0
/*3610 */                     if (!(s->cpuid_features & CPUID_CMOV)) {                                  // 0.0
/*3612 */                         goto illegal_op;                                                      // 0.0
/*3614 */                     }                                                                         // 0.0
/*3616 */                     op1 = fcmov_cc[op & 3] | (((op >> 3) & 1) ^ 1);                           // 0.0
/*3618 */                     l1 = gen_new_label();                                                     // 0.0
/*3620 */                     gen_jcc1_noeob(s, op1, l1);                                               // 0.0
/*3622 */                     gen_helper_fmov_ST0_STN(cpu_env, tcg_const_i32(opreg));                   // 0.0
/*3624 */                     gen_set_label(l1);                                                        // 0.0
/*3626 */                 }                                                                             // 0.0
/*3628 */                 break;                                                                        // 0.0
/*3630 */             default:                                                                          // 0.0
/*3632 */                 goto unknown_op;                                                              // 0.0
/*3634 */             }                                                                                 // 0.0
/*3636 */         }                                                                                     // 0.0
/*3638 */         break;                                                                                // 0.0
/*3640 */         /************************/                                                            // 0.0
/*3642 */         /* string ops */                                                                      // 0.0
/*3646 */     case 0xa4: /* movsS */                                                                    // 0.0
/*3648 */     case 0xa5:                                                                                // 0.0
/*3650 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*3652 */         if (prefixes & (PREFIX_REPZ | PREFIX_REPNZ)) {                                        // 0.0
/*3654 */             gen_repz_movs(s, ot, pc_start - s->cs_base, s->pc - s->cs_base);                  // 0.0
/*3656 */         } else {                                                                              // 0.0
/*3658 */             gen_movs(s, ot);                                                                  // 0.0
/*3660 */         }                                                                                     // 0.0
/*3662 */         break;                                                                                // 0.0
/*3666 */     case 0xaa: /* stosS */                                                                    // 0.0
/*3668 */     case 0xab:                                                                                // 0.0
/*3670 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*3672 */         if (prefixes & (PREFIX_REPZ | PREFIX_REPNZ)) {                                        // 0.0
/*3674 */             gen_repz_stos(s, ot, pc_start - s->cs_base, s->pc - s->cs_base);                  // 0.0
/*3676 */         } else {                                                                              // 0.0
/*3678 */             gen_stos(s, ot);                                                                  // 0.0
/*3680 */         }                                                                                     // 0.0
/*3682 */         break;                                                                                // 0.0
/*3684 */     case 0xac: /* lodsS */                                                                    // 0.0
/*3686 */     case 0xad:                                                                                // 0.0
/*3688 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*3690 */         if (prefixes & (PREFIX_REPZ | PREFIX_REPNZ)) {                                        // 0.0
/*3692 */             gen_repz_lods(s, ot, pc_start - s->cs_base, s->pc - s->cs_base);                  // 0.0
/*3694 */         } else {                                                                              // 0.0
/*3696 */             gen_lods(s, ot);                                                                  // 0.0
/*3698 */         }                                                                                     // 0.0
/*3700 */         break;                                                                                // 0.0
/*3702 */     case 0xae: /* scasS */                                                                    // 0.0
/*3704 */     case 0xaf:                                                                                // 0.0
/*3706 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*3708 */         if (prefixes & PREFIX_REPNZ) {                                                        // 0.0
/*3710 */             gen_repz_scas(s, ot, pc_start - s->cs_base, s->pc - s->cs_base, 1);               // 0.0
/*3712 */         } else if (prefixes & PREFIX_REPZ) {                                                  // 0.0
/*3714 */             gen_repz_scas(s, ot, pc_start - s->cs_base, s->pc - s->cs_base, 0);               // 0.0
/*3716 */         } else {                                                                              // 0.0
/*3718 */             gen_scas(s, ot);                                                                  // 0.0
/*3720 */         }                                                                                     // 0.0
/*3722 */         break;                                                                                // 0.0
/*3726 */     case 0xa6: /* cmpsS */                                                                    // 0.0
/*3728 */     case 0xa7:                                                                                // 0.0
/*3730 */         ot = mo_b_d(b, dflag);                                                                // 0.0
/*3732 */         if (prefixes & PREFIX_REPNZ) {                                                        // 0.0
/*3734 */             gen_repz_cmps(s, ot, pc_start - s->cs_base, s->pc - s->cs_base, 1);               // 0.0
/*3736 */         } else if (prefixes & PREFIX_REPZ) {                                                  // 0.0
/*3738 */             gen_repz_cmps(s, ot, pc_start - s->cs_base, s->pc - s->cs_base, 0);               // 0.0
/*3740 */         } else {                                                                              // 0.0
/*3742 */             gen_cmps(s, ot);                                                                  // 0.0
/*3744 */         }                                                                                     // 0.0
/*3746 */         break;                                                                                // 0.0
/*3748 */     case 0x6c: /* insS */                                                                     // 0.0
/*3750 */     case 0x6d:                                                                                // 0.0
/*3752 */         ot = mo_b_d32(b, dflag);                                                              // 0.0
/*3754 */         tcg_gen_ext16u_tl(cpu_T0, cpu_regs[R_EDX]);                                           // 0.0
/*3756 */         gen_check_io(s, ot, pc_start - s->cs_base,                                            // 0.0
/*3758 */                      SVM_IOIO_TYPE_MASK | svm_is_rep(prefixes) | 4);                          // 0.0
/*3760 */         if (prefixes & (PREFIX_REPZ | PREFIX_REPNZ)) {                                        // 0.0
/*3762 */             gen_repz_ins(s, ot, pc_start - s->cs_base, s->pc - s->cs_base);                   // 0.0
/*3764 */         } else {                                                                              // 0.0
/*3766 */             gen_ins(s, ot);                                                                   // 0.0
/*3768 */             if (s->base.tb->cflags & CF_USE_ICOUNT) {                                         // 0.0
/*3770 */                 gen_jmp(s, s->pc - s->cs_base);                                               // 0.0
/*3772 */             }                                                                                 // 0.0
/*3774 */         }                                                                                     // 0.0
/*3776 */         break;                                                                                // 0.0
/*3778 */     case 0x6e: /* outsS */                                                                    // 0.0
/*3780 */     case 0x6f:                                                                                // 0.0
/*3782 */         ot = mo_b_d32(b, dflag);                                                              // 0.0
/*3784 */         tcg_gen_ext16u_tl(cpu_T0, cpu_regs[R_EDX]);                                           // 0.0
/*3786 */         gen_check_io(s, ot, pc_start - s->cs_base,                                            // 0.0
/*3788 */                      svm_is_rep(prefixes) | 4);                                               // 0.0
/*3790 */         if (prefixes & (PREFIX_REPZ | PREFIX_REPNZ)) {                                        // 0.0
/*3792 */             gen_repz_outs(s, ot, pc_start - s->cs_base, s->pc - s->cs_base);                  // 0.0
/*3794 */         } else {                                                                              // 0.0
/*3796 */             gen_outs(s, ot);                                                                  // 0.0
/*3798 */             if (s->base.tb->cflags & CF_USE_ICOUNT) {                                         // 0.0
/*3800 */                 gen_jmp(s, s->pc - s->cs_base);                                               // 0.0
/*3802 */             }                                                                                 // 0.0
/*3804 */         }                                                                                     // 0.0
/*3806 */         break;                                                                                // 0.0
/*3810 */         /************************/                                                            // 0.0
/*3812 */         /* port I/O */                                                                        // 0.0
/*3816 */     case 0xe4:                                                                                // 0.0
/*3818 */     case 0xe5:                                                                                // 0.0
/*3820 */         ot = mo_b_d32(b, dflag);                                                              // 0.0
/*3822 */         val = x86_ldub_code(env, s);                                                          // 0.0
/*3824 */         tcg_gen_movi_tl(cpu_T0, val);                                                         // 0.0
/*3826 */         gen_check_io(s, ot, pc_start - s->cs_base,                                            // 0.0
/*3828 */                      SVM_IOIO_TYPE_MASK | svm_is_rep(prefixes));                              // 0.0
/*3830 */         if (s->base.tb->cflags & CF_USE_ICOUNT) {                                             // 0.0
/*3832 */             gen_io_start();                                                                   // 0.0
/*3834 */ 	}                                                                                            // 0.0
/*3836 */         tcg_gen_movi_i32(cpu_tmp2_i32, val);                                                  // 0.0
/*3838 */         gen_helper_in_func(ot, cpu_T1, cpu_tmp2_i32);                                         // 0.0
/*3840 */         gen_op_mov_reg_v(ot, R_EAX, cpu_T1);                                                  // 0.0
/*3842 */         gen_bpt_io(s, cpu_tmp2_i32, ot);                                                      // 0.0
/*3844 */         if (s->base.tb->cflags & CF_USE_ICOUNT) {                                             // 0.0
/*3846 */             gen_io_end();                                                                     // 0.0
/*3848 */             gen_jmp(s, s->pc - s->cs_base);                                                   // 0.0
/*3850 */         }                                                                                     // 0.0
/*3852 */         break;                                                                                // 0.0
/*3854 */     case 0xe6:                                                                                // 0.0
/*3856 */     case 0xe7:                                                                                // 0.0
/*3858 */         ot = mo_b_d32(b, dflag);                                                              // 0.0
/*3860 */         val = x86_ldub_code(env, s);                                                          // 0.0
/*3862 */         tcg_gen_movi_tl(cpu_T0, val);                                                         // 0.0
/*3864 */         gen_check_io(s, ot, pc_start - s->cs_base,                                            // 0.0
/*3866 */                      svm_is_rep(prefixes));                                                   // 0.0
/*3868 */         gen_op_mov_v_reg(ot, cpu_T1, R_EAX);                                                  // 0.0
/*3872 */         if (s->base.tb->cflags & CF_USE_ICOUNT) {                                             // 0.0
/*3874 */             gen_io_start();                                                                   // 0.0
/*3876 */ 	}                                                                                            // 0.0
/*3878 */         tcg_gen_movi_i32(cpu_tmp2_i32, val);                                                  // 0.0
/*3880 */         tcg_gen_trunc_tl_i32(cpu_tmp3_i32, cpu_T1);                                           // 0.0
/*3882 */         gen_helper_out_func(ot, cpu_tmp2_i32, cpu_tmp3_i32);                                  // 0.0
/*3884 */         gen_bpt_io(s, cpu_tmp2_i32, ot);                                                      // 0.0
/*3886 */         if (s->base.tb->cflags & CF_USE_ICOUNT) {                                             // 0.0
/*3888 */             gen_io_end();                                                                     // 0.0
/*3890 */             gen_jmp(s, s->pc - s->cs_base);                                                   // 0.0
/*3892 */         }                                                                                     // 0.0
/*3894 */         break;                                                                                // 0.0
/*3896 */     case 0xec:                                                                                // 0.0
/*3898 */     case 0xed:                                                                                // 0.0
/*3900 */         ot = mo_b_d32(b, dflag);                                                              // 0.0
/*3902 */         tcg_gen_ext16u_tl(cpu_T0, cpu_regs[R_EDX]);                                           // 0.0
/*3904 */         gen_check_io(s, ot, pc_start - s->cs_base,                                            // 0.0
/*3906 */                      SVM_IOIO_TYPE_MASK | svm_is_rep(prefixes));                              // 0.0
/*3908 */         if (s->base.tb->cflags & CF_USE_ICOUNT) {                                             // 0.0
/*3910 */             gen_io_start();                                                                   // 0.0
/*3912 */ 	}                                                                                            // 0.0
/*3914 */         tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                           // 0.0
/*3916 */         gen_helper_in_func(ot, cpu_T1, cpu_tmp2_i32);                                         // 0.0
/*3918 */         gen_op_mov_reg_v(ot, R_EAX, cpu_T1);                                                  // 0.0
/*3920 */         gen_bpt_io(s, cpu_tmp2_i32, ot);                                                      // 0.0
/*3922 */         if (s->base.tb->cflags & CF_USE_ICOUNT) {                                             // 0.0
/*3924 */             gen_io_end();                                                                     // 0.0
/*3926 */             gen_jmp(s, s->pc - s->cs_base);                                                   // 0.0
/*3928 */         }                                                                                     // 0.0
/*3930 */         break;                                                                                // 0.0
/*3932 */     case 0xee:                                                                                // 0.0
/*3934 */     case 0xef:                                                                                // 0.0
/*3936 */         ot = mo_b_d32(b, dflag);                                                              // 0.0
/*3938 */         tcg_gen_ext16u_tl(cpu_T0, cpu_regs[R_EDX]);                                           // 0.0
/*3940 */         gen_check_io(s, ot, pc_start - s->cs_base,                                            // 0.0
/*3942 */                      svm_is_rep(prefixes));                                                   // 0.0
/*3944 */         gen_op_mov_v_reg(ot, cpu_T1, R_EAX);                                                  // 0.0
/*3948 */         if (s->base.tb->cflags & CF_USE_ICOUNT) {                                             // 0.0
/*3950 */             gen_io_start();                                                                   // 0.0
/*3952 */ 	}                                                                                            // 0.0
/*3954 */         tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                           // 0.0
/*3956 */         tcg_gen_trunc_tl_i32(cpu_tmp3_i32, cpu_T1);                                           // 0.0
/*3958 */         gen_helper_out_func(ot, cpu_tmp2_i32, cpu_tmp3_i32);                                  // 0.0
/*3960 */         gen_bpt_io(s, cpu_tmp2_i32, ot);                                                      // 0.0
/*3962 */         if (s->base.tb->cflags & CF_USE_ICOUNT) {                                             // 0.0
/*3964 */             gen_io_end();                                                                     // 0.0
/*3966 */             gen_jmp(s, s->pc - s->cs_base);                                                   // 0.0
/*3968 */         }                                                                                     // 0.0
/*3970 */         break;                                                                                // 0.0
/*3974 */         /************************/                                                            // 0.0
/*3976 */         /* control */                                                                         // 0.0
/*3978 */     case 0xc2: /* ret im */                                                                   // 0.0
/*3980 */         val = x86_ldsw_code(env, s);                                                          // 0.0
/*3982 */         ot = gen_pop_T0(s);                                                                   // 0.0
/*3984 */         gen_stack_update(s, val + (1 << ot));                                                 // 0.0
/*3986 */         /* Note that gen_pop_T0 uses a zero-extending load.  */                               // 0.0
/*3988 */         gen_op_jmp_v(cpu_T0);                                                                 // 0.0
/*3990 */         gen_bnd_jmp(s);                                                                       // 0.0
/*3992 */         gen_jr(s, cpu_T0);                                                                    // 0.0
/*3994 */         break;                                                                                // 0.0
/*3996 */     case 0xc3: /* ret */                                                                      // 0.0
/*3998 */         ot = gen_pop_T0(s);                                                                   // 0.0
/*4000 */         gen_pop_update(s, ot);                                                                // 0.0
/*4002 */         /* Note that gen_pop_T0 uses a zero-extending load.  */                               // 0.0
/*4004 */         gen_op_jmp_v(cpu_T0);                                                                 // 0.0
/*4006 */         gen_bnd_jmp(s);                                                                       // 0.0
/*4008 */         gen_jr(s, cpu_T0);                                                                    // 0.0
/*4010 */         break;                                                                                // 0.0
/*4012 */     case 0xca: /* lret im */                                                                  // 0.0
/*4014 */         val = x86_ldsw_code(env, s);                                                          // 0.0
/*4016 */     do_lret:                                                                                  // 0.0
/*4018 */         if (s->pe && !s->vm86) {                                                              // 0.0
/*4020 */             gen_update_cc_op(s);                                                              // 0.0
/*4022 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*4024 */             gen_helper_lret_protected(cpu_env, tcg_const_i32(dflag - 1),                      // 0.0
/*4026 */                                       tcg_const_i32(val));                                    // 0.0
/*4028 */         } else {                                                                              // 0.0
/*4030 */             gen_stack_A0(s);                                                                  // 0.0
/*4032 */             /* pop offset */                                                                  // 0.0
/*4034 */             gen_op_ld_v(s, dflag, cpu_T0, cpu_A0);                                            // 0.0
/*4036 */             /* NOTE: keeping EIP updated is not a problem in case of                          // 0.0
/*4038 */                exception */                                                                   // 0.0
/*4040 */             gen_op_jmp_v(cpu_T0);                                                             // 0.0
/*4042 */             /* pop selector */                                                                // 0.0
/*4044 */             gen_add_A0_im(s, 1 << dflag);                                                     // 0.0
/*4046 */             gen_op_ld_v(s, dflag, cpu_T0, cpu_A0);                                            // 0.0
/*4048 */             gen_op_movl_seg_T0_vm(R_CS);                                                      // 0.0
/*4050 */             /* add stack offset */                                                            // 0.0
/*4052 */             gen_stack_update(s, val + (2 << dflag));                                          // 0.0
/*4054 */         }                                                                                     // 0.0
/*4056 */         gen_eob(s);                                                                           // 0.0
/*4058 */         break;                                                                                // 0.0
/*4060 */     case 0xcb: /* lret */                                                                     // 0.0
/*4062 */         val = 0;                                                                              // 0.0
/*4064 */         goto do_lret;                                                                         // 0.0
/*4066 */     case 0xcf: /* iret */                                                                     // 0.0
/*4068 */         gen_svm_check_intercept(s, pc_start, SVM_EXIT_IRET);                                  // 0.0
/*4070 */         if (!s->pe) {                                                                         // 0.0
/*4072 */             /* real mode */                                                                   // 0.0
/*4074 */             gen_helper_iret_real(cpu_env, tcg_const_i32(dflag - 1));                          // 0.0
/*4076 */             set_cc_op(s, CC_OP_EFLAGS);                                                       // 0.0
/*4078 */         } else if (s->vm86) {                                                                 // 0.0
/*4080 */             if (s->iopl != 3) {                                                               // 0.0
/*4082 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*4084 */             } else {                                                                          // 0.0
/*4086 */                 gen_helper_iret_real(cpu_env, tcg_const_i32(dflag - 1));                      // 0.0
/*4088 */                 set_cc_op(s, CC_OP_EFLAGS);                                                   // 0.0
/*4090 */             }                                                                                 // 0.0
/*4092 */         } else {                                                                              // 0.0
/*4094 */             gen_helper_iret_protected(cpu_env, tcg_const_i32(dflag - 1),                      // 0.0
/*4096 */                                       tcg_const_i32(s->pc - s->cs_base));                     // 0.0
/*4098 */             set_cc_op(s, CC_OP_EFLAGS);                                                       // 0.0
/*4100 */         }                                                                                     // 0.0
/*4102 */         gen_eob(s);                                                                           // 0.0
/*4104 */         break;                                                                                // 0.0
/*4106 */     case 0xe8: /* call im */                                                                  // 0.0
/*4108 */         {                                                                                     // 0.0
/*4110 */             if (dflag != MO_16) {                                                             // 0.0
/*4112 */                 tval = (int32_t)insn_get(env, s, MO_32);                                      // 0.0
/*4114 */             } else {                                                                          // 0.0
/*4116 */                 tval = (int16_t)insn_get(env, s, MO_16);                                      // 0.0
/*4118 */             }                                                                                 // 0.0
/*4120 */             next_eip = s->pc - s->cs_base;                                                    // 0.0
/*4122 */             tval += next_eip;                                                                 // 0.0
/*4124 */             if (dflag == MO_16) {                                                             // 0.0
/*4126 */                 tval &= 0xffff;                                                               // 0.0
/*4128 */             } else if (!CODE64(s)) {                                                          // 0.0
/*4130 */                 tval &= 0xffffffff;                                                           // 0.0
/*4132 */             }                                                                                 // 0.0
/*4134 */             tcg_gen_movi_tl(cpu_T0, next_eip);                                                // 0.0
/*4136 */             gen_push_v(s, cpu_T0);                                                            // 0.0
/*4138 */             gen_bnd_jmp(s);                                                                   // 0.0
/*4140 */             gen_jmp(s, tval);                                                                 // 0.0
/*4142 */         }                                                                                     // 0.0
/*4144 */         break;                                                                                // 0.0
/*4146 */     case 0x9a: /* lcall im */                                                                 // 0.0
/*4148 */         {                                                                                     // 0.0
/*4150 */             unsigned int selector, offset;                                                    // 0.0
/*4154 */             if (CODE64(s))                                                                    // 0.0
/*4156 */                 goto illegal_op;                                                              // 0.0
/*4158 */             ot = dflag;                                                                       // 0.0
/*4160 */             offset = insn_get(env, s, ot);                                                    // 0.0
/*4162 */             selector = insn_get(env, s, MO_16);                                               // 0.0
/*4166 */             tcg_gen_movi_tl(cpu_T0, selector);                                                // 0.0
/*4168 */             tcg_gen_movi_tl(cpu_T1, offset);                                                  // 0.0
/*4170 */         }                                                                                     // 0.0
/*4172 */         goto do_lcall;                                                                        // 0.0
/*4174 */     case 0xe9: /* jmp im */                                                                   // 0.0
/*4176 */         if (dflag != MO_16) {                                                                 // 0.0
/*4178 */             tval = (int32_t)insn_get(env, s, MO_32);                                          // 0.0
/*4180 */         } else {                                                                              // 0.0
/*4182 */             tval = (int16_t)insn_get(env, s, MO_16);                                          // 0.0
/*4184 */         }                                                                                     // 0.0
/*4186 */         tval += s->pc - s->cs_base;                                                           // 0.0
/*4188 */         if (dflag == MO_16) {                                                                 // 0.0
/*4190 */             tval &= 0xffff;                                                                   // 0.0
/*4192 */         } else if (!CODE64(s)) {                                                              // 0.0
/*4194 */             tval &= 0xffffffff;                                                               // 0.0
/*4196 */         }                                                                                     // 0.0
/*4198 */         gen_bnd_jmp(s);                                                                       // 0.0
/*4200 */         gen_jmp(s, tval);                                                                     // 0.0
/*4202 */         break;                                                                                // 0.0
/*4204 */     case 0xea: /* ljmp im */                                                                  // 0.0
/*4206 */         {                                                                                     // 0.0
/*4208 */             unsigned int selector, offset;                                                    // 0.0
/*4212 */             if (CODE64(s))                                                                    // 0.0
/*4214 */                 goto illegal_op;                                                              // 0.0
/*4216 */             ot = dflag;                                                                       // 0.0
/*4218 */             offset = insn_get(env, s, ot);                                                    // 0.0
/*4220 */             selector = insn_get(env, s, MO_16);                                               // 0.0
/*4224 */             tcg_gen_movi_tl(cpu_T0, selector);                                                // 0.0
/*4226 */             tcg_gen_movi_tl(cpu_T1, offset);                                                  // 0.0
/*4228 */         }                                                                                     // 0.0
/*4230 */         goto do_ljmp;                                                                         // 0.0
/*4232 */     case 0xeb: /* jmp Jb */                                                                   // 0.0
/*4234 */         tval = (int8_t)insn_get(env, s, MO_8);                                                // 0.0
/*4236 */         tval += s->pc - s->cs_base;                                                           // 0.0
/*4238 */         if (dflag == MO_16) {                                                                 // 0.0
/*4240 */             tval &= 0xffff;                                                                   // 0.0
/*4242 */         }                                                                                     // 0.0
/*4244 */         gen_jmp(s, tval);                                                                     // 0.0
/*4246 */         break;                                                                                // 0.0
/*4248 */     case 0x70 ... 0x7f: /* jcc Jb */                                                          // 0.0
/*4250 */         tval = (int8_t)insn_get(env, s, MO_8);                                                // 0.0
/*4252 */         goto do_jcc;                                                                          // 0.0
/*4254 */     case 0x180 ... 0x18f: /* jcc Jv */                                                        // 0.0
/*4256 */         if (dflag != MO_16) {                                                                 // 0.0
/*4258 */             tval = (int32_t)insn_get(env, s, MO_32);                                          // 0.0
/*4260 */         } else {                                                                              // 0.0
/*4262 */             tval = (int16_t)insn_get(env, s, MO_16);                                          // 0.0
/*4264 */         }                                                                                     // 0.0
/*4266 */     do_jcc:                                                                                   // 0.0
/*4268 */         next_eip = s->pc - s->cs_base;                                                        // 0.0
/*4270 */         tval += next_eip;                                                                     // 0.0
/*4272 */         if (dflag == MO_16) {                                                                 // 0.0
/*4274 */             tval &= 0xffff;                                                                   // 0.0
/*4276 */         }                                                                                     // 0.0
/*4278 */         gen_bnd_jmp(s);                                                                       // 0.0
/*4280 */         gen_jcc(s, b, tval, next_eip);                                                        // 0.0
/*4282 */         break;                                                                                // 0.0
/*4286 */     case 0x190 ... 0x19f: /* setcc Gv */                                                      // 0.0
/*4288 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*4290 */         gen_setcc1(s, b, cpu_T0);                                                             // 0.0
/*4292 */         gen_ldst_modrm(env, s, modrm, MO_8, OR_TMP0, 1);                                      // 0.0
/*4294 */         break;                                                                                // 0.0
/*4296 */     case 0x140 ... 0x14f: /* cmov Gv, Ev */                                                   // 0.0
/*4298 */         if (!(s->cpuid_features & CPUID_CMOV)) {                                              // 0.0
/*4300 */             goto illegal_op;                                                                  // 0.0
/*4302 */         }                                                                                     // 0.0
/*4304 */         ot = dflag;                                                                           // 0.0
/*4306 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*4308 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*4310 */         gen_cmovcc1(env, s, ot, b, modrm, reg);                                               // 0.0
/*4312 */         break;                                                                                // 0.0
/*4316 */         /************************/                                                            // 0.0
/*4318 */         /* flags */                                                                           // 0.0
/*4320 */     case 0x9c: /* pushf */                                                                    // 0.0
/*4322 */         gen_svm_check_intercept(s, pc_start, SVM_EXIT_PUSHF);                                 // 0.0
/*4324 */         if (s->vm86 && s->iopl != 3) {                                                        // 0.0
/*4326 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*4328 */         } else {                                                                              // 0.0
/*4330 */             gen_update_cc_op(s);                                                              // 0.0
/*4332 */             gen_helper_read_eflags(cpu_T0, cpu_env);                                          // 0.0
/*4334 */             gen_push_v(s, cpu_T0);                                                            // 0.0
/*4336 */         }                                                                                     // 0.0
/*4338 */         break;                                                                                // 0.0
/*4340 */     case 0x9d: /* popf */                                                                     // 0.0
/*4342 */         gen_svm_check_intercept(s, pc_start, SVM_EXIT_POPF);                                  // 0.0
/*4344 */         if (s->vm86 && s->iopl != 3) {                                                        // 0.0
/*4346 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*4348 */         } else {                                                                              // 0.0
/*4350 */             ot = gen_pop_T0(s);                                                               // 0.0
/*4352 */             if (s->cpl == 0) {                                                                // 0.0
/*4354 */                 if (dflag != MO_16) {                                                         // 0.0
/*4356 */                     gen_helper_write_eflags(cpu_env, cpu_T0,                                  // 0.0
/*4358 */                                             tcg_const_i32((TF_MASK | AC_MASK |                // 0.0
/*4360 */                                                            ID_MASK | NT_MASK |                // 0.0
/*4362 */                                                            IF_MASK |                          // 0.0
/*4364 */                                                            IOPL_MASK)));                      // 0.0
/*4366 */                 } else {                                                                      // 0.0
/*4368 */                     gen_helper_write_eflags(cpu_env, cpu_T0,                                  // 0.0
/*4370 */                                             tcg_const_i32((TF_MASK | AC_MASK |                // 0.0
/*4372 */                                                            ID_MASK | NT_MASK |                // 0.0
/*4374 */                                                            IF_MASK | IOPL_MASK)               // 0.0
/*4376 */                                                           & 0xffff));                         // 0.0
/*4378 */                 }                                                                             // 0.0
/*4380 */             } else {                                                                          // 0.0
/*4382 */                 if (s->cpl <= s->iopl) {                                                      // 0.0
/*4384 */                     if (dflag != MO_16) {                                                     // 0.0
/*4386 */                         gen_helper_write_eflags(cpu_env, cpu_T0,                              // 0.0
/*4388 */                                                 tcg_const_i32((TF_MASK |                      // 0.0
/*4390 */                                                                AC_MASK |                      // 0.0
/*4392 */                                                                ID_MASK |                      // 0.0
/*4394 */                                                                NT_MASK |                      // 0.0
/*4396 */                                                                IF_MASK)));                    // 0.0
/*4398 */                     } else {                                                                  // 0.0
/*4400 */                         gen_helper_write_eflags(cpu_env, cpu_T0,                              // 0.0
/*4402 */                                                 tcg_const_i32((TF_MASK |                      // 0.0
/*4404 */                                                                AC_MASK |                      // 0.0
/*4406 */                                                                ID_MASK |                      // 0.0
/*4408 */                                                                NT_MASK |                      // 0.0
/*4410 */                                                                IF_MASK)                       // 0.0
/*4412 */                                                               & 0xffff));                     // 0.0
/*4414 */                     }                                                                         // 0.0
/*4416 */                 } else {                                                                      // 0.0
/*4418 */                     if (dflag != MO_16) {                                                     // 0.0
/*4420 */                         gen_helper_write_eflags(cpu_env, cpu_T0,                              // 0.0
/*4422 */                                            tcg_const_i32((TF_MASK | AC_MASK |                 // 0.0
/*4424 */                                                           ID_MASK | NT_MASK)));               // 0.0
/*4426 */                     } else {                                                                  // 0.0
/*4428 */                         gen_helper_write_eflags(cpu_env, cpu_T0,                              // 0.0
/*4430 */                                            tcg_const_i32((TF_MASK | AC_MASK |                 // 0.0
/*4432 */                                                           ID_MASK | NT_MASK)                  // 0.0
/*4434 */                                                          & 0xffff));                          // 0.0
/*4436 */                     }                                                                         // 0.0
/*4438 */                 }                                                                             // 0.0
/*4440 */             }                                                                                 // 0.0
/*4442 */             gen_pop_update(s, ot);                                                            // 0.0
/*4444 */             set_cc_op(s, CC_OP_EFLAGS);                                                       // 0.0
/*4446 */             /* abort translation because TF/AC flag may change */                             // 0.0
/*4448 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*4450 */             gen_eob(s);                                                                       // 0.0
/*4452 */         }                                                                                     // 0.0
/*4454 */         break;                                                                                // 0.0
/*4456 */     case 0x9e: /* sahf */                                                                     // 0.0
/*4458 */         if (CODE64(s) && !(s->cpuid_ext3_features & CPUID_EXT3_LAHF_LM))                      // 0.0
/*4460 */             goto illegal_op;                                                                  // 0.0
/*4462 */         gen_op_mov_v_reg(MO_8, cpu_T0, R_AH);                                                 // 0.0
/*4464 */         gen_compute_eflags(s);                                                                // 0.0
/*4466 */         tcg_gen_andi_tl(cpu_cc_src, cpu_cc_src, CC_O);                                        // 0.0
/*4468 */         tcg_gen_andi_tl(cpu_T0, cpu_T0, CC_S | CC_Z | CC_A | CC_P | CC_C);                    // 0.0
/*4470 */         tcg_gen_or_tl(cpu_cc_src, cpu_cc_src, cpu_T0);                                        // 0.0
/*4472 */         break;                                                                                // 0.0
/*4474 */     case 0x9f: /* lahf */                                                                     // 0.0
/*4476 */         if (CODE64(s) && !(s->cpuid_ext3_features & CPUID_EXT3_LAHF_LM))                      // 0.0
/*4478 */             goto illegal_op;                                                                  // 0.0
/*4480 */         gen_compute_eflags(s);                                                                // 0.0
/*4482 */         /* Note: gen_compute_eflags() only gives the condition codes */                       // 0.0
/*4484 */         tcg_gen_ori_tl(cpu_T0, cpu_cc_src, 0x02);                                             // 0.0
/*4486 */         gen_op_mov_reg_v(MO_8, R_AH, cpu_T0);                                                 // 0.0
/*4488 */         break;                                                                                // 0.0
/*4490 */     case 0xf5: /* cmc */                                                                      // 0.0
/*4492 */         gen_compute_eflags(s);                                                                // 0.0
/*4494 */         tcg_gen_xori_tl(cpu_cc_src, cpu_cc_src, CC_C);                                        // 0.0
/*4496 */         break;                                                                                // 0.0
/*4498 */     case 0xf8: /* clc */                                                                      // 0.0
/*4500 */         gen_compute_eflags(s);                                                                // 0.0
/*4502 */         tcg_gen_andi_tl(cpu_cc_src, cpu_cc_src, ~CC_C);                                       // 0.0
/*4504 */         break;                                                                                // 0.0
/*4506 */     case 0xf9: /* stc */                                                                      // 0.0
/*4508 */         gen_compute_eflags(s);                                                                // 0.0
/*4510 */         tcg_gen_ori_tl(cpu_cc_src, cpu_cc_src, CC_C);                                         // 0.0
/*4512 */         break;                                                                                // 0.0
/*4514 */     case 0xfc: /* cld */                                                                      // 0.0
/*4516 */         tcg_gen_movi_i32(cpu_tmp2_i32, 1);                                                    // 0.0
/*4518 */         tcg_gen_st_i32(cpu_tmp2_i32, cpu_env, offsetof(CPUX86State, df));                     // 0.0
/*4520 */         break;                                                                                // 0.0
/*4522 */     case 0xfd: /* std */                                                                      // 0.0
/*4524 */         tcg_gen_movi_i32(cpu_tmp2_i32, -1);                                                   // 0.0
/*4526 */         tcg_gen_st_i32(cpu_tmp2_i32, cpu_env, offsetof(CPUX86State, df));                     // 0.0
/*4528 */         break;                                                                                // 0.0
/*4532 */         /************************/                                                            // 0.0
/*4534 */         /* bit operations */                                                                  // 0.0
/*4536 */     case 0x1ba: /* bt/bts/btr/btc Gv, im */                                                   // 0.0
/*4538 */         ot = dflag;                                                                           // 0.0
/*4540 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*4542 */         op = (modrm >> 3) & 7;                                                                // 0.0
/*4544 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*4546 */         rm = (modrm & 7) | REX_B(s);                                                          // 0.0
/*4548 */         if (mod != 3) {                                                                       // 0.0
/*4550 */             s->rip_offset = 1;                                                                // 0.0
/*4552 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*4554 */             if (!(s->prefix & PREFIX_LOCK)) {                                                 // 0.0
/*4556 */                 gen_op_ld_v(s, ot, cpu_T0, cpu_A0);                                           // 0.0
/*4558 */             }                                                                                 // 0.0
/*4560 */         } else {                                                                              // 0.0
/*4562 */             gen_op_mov_v_reg(ot, cpu_T0, rm);                                                 // 0.0
/*4564 */         }                                                                                     // 0.0
/*4566 */         /* load shift */                                                                      // 0.0
/*4568 */         val = x86_ldub_code(env, s);                                                          // 0.0
/*4570 */         tcg_gen_movi_tl(cpu_T1, val);                                                         // 0.0
/*4572 */         if (op < 4)                                                                           // 0.0
/*4574 */             goto unknown_op;                                                                  // 0.0
/*4576 */         op -= 4;                                                                              // 0.0
/*4578 */         goto bt_op;                                                                           // 0.0
/*4580 */     case 0x1a3: /* bt Gv, Ev */                                                               // 0.0
/*4582 */         op = 0;                                                                               // 0.0
/*4584 */         goto do_btx;                                                                          // 0.0
/*4586 */     case 0x1ab: /* bts */                                                                     // 0.0
/*4588 */         op = 1;                                                                               // 0.0
/*4590 */         goto do_btx;                                                                          // 0.0
/*4592 */     case 0x1b3: /* btr */                                                                     // 0.0
/*4594 */         op = 2;                                                                               // 0.0
/*4596 */         goto do_btx;                                                                          // 0.0
/*4598 */     case 0x1bb: /* btc */                                                                     // 0.0
/*4600 */         op = 3;                                                                               // 0.0
/*4602 */     do_btx:                                                                                   // 0.0
/*4604 */         ot = dflag;                                                                           // 0.0
/*4606 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*4608 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*4610 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*4612 */         rm = (modrm & 7) | REX_B(s);                                                          // 0.0
/*4614 */         gen_op_mov_v_reg(MO_32, cpu_T1, reg);                                                 // 0.0
/*4616 */         if (mod != 3) {                                                                       // 0.0
/*4618 */             AddressParts a = gen_lea_modrm_0(env, s, modrm);                                  // 0.0
/*4620 */             /* specific case: we need to add a displacement */                                // 0.0
/*4622 */             gen_exts(ot, cpu_T1);                                                             // 0.0
/*4624 */             tcg_gen_sari_tl(cpu_tmp0, cpu_T1, 3 + ot);                                        // 0.0
/*4626 */             tcg_gen_shli_tl(cpu_tmp0, cpu_tmp0, ot);                                          // 0.0
/*4628 */             tcg_gen_add_tl(cpu_A0, gen_lea_modrm_1(a), cpu_tmp0);                             // 0.0
/*4630 */             gen_lea_v_seg(s, s->aflag, cpu_A0, a.def_seg, s->override);                       // 0.0
/*4632 */             if (!(s->prefix & PREFIX_LOCK)) {                                                 // 0.0
/*4634 */                 gen_op_ld_v(s, ot, cpu_T0, cpu_A0);                                           // 0.0
/*4636 */             }                                                                                 // 0.0
/*4638 */         } else {                                                                              // 0.0
/*4640 */             gen_op_mov_v_reg(ot, cpu_T0, rm);                                                 // 0.0
/*4642 */         }                                                                                     // 0.0
/*4644 */     bt_op:                                                                                    // 0.0
/*4646 */         tcg_gen_andi_tl(cpu_T1, cpu_T1, (1 << (3 + ot)) - 1);                                 // 0.0
/*4648 */         tcg_gen_movi_tl(cpu_tmp0, 1);                                                         // 0.0
/*4650 */         tcg_gen_shl_tl(cpu_tmp0, cpu_tmp0, cpu_T1);                                           // 0.0
/*4652 */         if (s->prefix & PREFIX_LOCK) {                                                        // 0.0
/*4654 */             switch (op) {                                                                     // 0.0
/*4656 */             case 0: /* bt */                                                                  // 0.0
/*4658 */                 /* Needs no atomic ops; we surpressed the normal                              // 0.0
/*4660 */                    memory load for LOCK above so do it now.  */                               // 0.0
/*4662 */                 gen_op_ld_v(s, ot, cpu_T0, cpu_A0);                                           // 0.0
/*4664 */                 break;                                                                        // 0.0
/*4666 */             case 1: /* bts */                                                                 // 0.0
/*4668 */                 tcg_gen_atomic_fetch_or_tl(cpu_T0, cpu_A0, cpu_tmp0,                          // 0.0
/*4670 */                                            s->mem_index, ot | MO_LE);                         // 0.0
/*4672 */                 break;                                                                        // 0.0
/*4674 */             case 2: /* btr */                                                                 // 0.0
/*4676 */                 tcg_gen_not_tl(cpu_tmp0, cpu_tmp0);                                           // 0.0
/*4678 */                 tcg_gen_atomic_fetch_and_tl(cpu_T0, cpu_A0, cpu_tmp0,                         // 0.0
/*4680 */                                             s->mem_index, ot | MO_LE);                        // 0.0
/*4682 */                 break;                                                                        // 0.0
/*4684 */             default:                                                                          // 0.0
/*4686 */             case 3: /* btc */                                                                 // 0.0
/*4688 */                 tcg_gen_atomic_fetch_xor_tl(cpu_T0, cpu_A0, cpu_tmp0,                         // 0.0
/*4690 */                                             s->mem_index, ot | MO_LE);                        // 0.0
/*4692 */                 break;                                                                        // 0.0
/*4694 */             }                                                                                 // 0.0
/*4696 */             tcg_gen_shr_tl(cpu_tmp4, cpu_T0, cpu_T1);                                         // 0.0
/*4698 */         } else {                                                                              // 0.0
/*4700 */             tcg_gen_shr_tl(cpu_tmp4, cpu_T0, cpu_T1);                                         // 0.0
/*4702 */             switch (op) {                                                                     // 0.0
/*4704 */             case 0: /* bt */                                                                  // 0.0
/*4706 */                 /* Data already loaded; nothing to do.  */                                    // 0.0
/*4708 */                 break;                                                                        // 0.0
/*4710 */             case 1: /* bts */                                                                 // 0.0
/*4712 */                 tcg_gen_or_tl(cpu_T0, cpu_T0, cpu_tmp0);                                      // 0.0
/*4714 */                 break;                                                                        // 0.0
/*4716 */             case 2: /* btr */                                                                 // 0.0
/*4718 */                 tcg_gen_andc_tl(cpu_T0, cpu_T0, cpu_tmp0);                                    // 0.0
/*4720 */                 break;                                                                        // 0.0
/*4722 */             default:                                                                          // 0.0
/*4724 */             case 3: /* btc */                                                                 // 0.0
/*4726 */                 tcg_gen_xor_tl(cpu_T0, cpu_T0, cpu_tmp0);                                     // 0.0
/*4728 */                 break;                                                                        // 0.0
/*4730 */             }                                                                                 // 0.0
/*4732 */             if (op != 0) {                                                                    // 0.0
/*4734 */                 if (mod != 3) {                                                               // 0.0
/*4736 */                     gen_op_st_v(s, ot, cpu_T0, cpu_A0);                                       // 0.0
/*4738 */                 } else {                                                                      // 0.0
/*4740 */                     gen_op_mov_reg_v(ot, rm, cpu_T0);                                         // 0.0
/*4742 */                 }                                                                             // 0.0
/*4744 */             }                                                                                 // 0.0
/*4746 */         }                                                                                     // 0.0
/*4750 */         /* Delay all CC updates until after the store above.  Note that                       // 0.0
/*4752 */            C is the result of the test, Z is unchanged, and the others                        // 0.0
/*4754 */            are all undefined.  */                                                             // 0.0
/*4756 */         switch (s->cc_op) {                                                                   // 0.0
/*4758 */         case CC_OP_MULB ... CC_OP_MULQ:                                                       // 0.0
/*4760 */         case CC_OP_ADDB ... CC_OP_ADDQ:                                                       // 0.0
/*4762 */         case CC_OP_ADCB ... CC_OP_ADCQ:                                                       // 0.0
/*4764 */         case CC_OP_SUBB ... CC_OP_SUBQ:                                                       // 0.0
/*4766 */         case CC_OP_SBBB ... CC_OP_SBBQ:                                                       // 0.0
/*4768 */         case CC_OP_LOGICB ... CC_OP_LOGICQ:                                                   // 0.0
/*4770 */         case CC_OP_INCB ... CC_OP_INCQ:                                                       // 0.0
/*4772 */         case CC_OP_DECB ... CC_OP_DECQ:                                                       // 0.0
/*4774 */         case CC_OP_SHLB ... CC_OP_SHLQ:                                                       // 0.0
/*4776 */         case CC_OP_SARB ... CC_OP_SARQ:                                                       // 0.0
/*4778 */         case CC_OP_BMILGB ... CC_OP_BMILGQ:                                                   // 0.0
/*4780 */             /* Z was going to be computed from the non-zero status of CC_DST.                 // 0.0
/*4782 */                We can get that same Z value (and the new C value) by leaving                  // 0.0
/*4784 */                CC_DST alone, setting CC_SRC, and using a CC_OP_SAR of the                     // 0.0
/*4786 */                same width.  */                                                                // 0.0
/*4788 */             tcg_gen_mov_tl(cpu_cc_src, cpu_tmp4);                                             // 0.0
/*4790 */             set_cc_op(s, ((s->cc_op - CC_OP_MULB) & 3) + CC_OP_SARB);                         // 0.0
/*4792 */             break;                                                                            // 0.0
/*4794 */         default:                                                                              // 0.0
/*4796 */             /* Otherwise, generate EFLAGS and replace the C bit.  */                          // 0.0
/*4798 */             gen_compute_eflags(s);                                                            // 0.0
/*4800 */             tcg_gen_deposit_tl(cpu_cc_src, cpu_cc_src, cpu_tmp4,                              // 0.0
/*4802 */                                ctz32(CC_C), 1);                                               // 0.0
/*4804 */             break;                                                                            // 0.0
/*4806 */         }                                                                                     // 0.0
/*4808 */         break;                                                                                // 0.0
/*4810 */     case 0x1bc: /* bsf / tzcnt */                                                             // 0.0
/*4812 */     case 0x1bd: /* bsr / lzcnt */                                                             // 0.0
/*4814 */         ot = dflag;                                                                           // 0.0
/*4816 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*4818 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*4820 */         gen_ldst_modrm(env, s, modrm, ot, OR_TMP0, 0);                                        // 0.0
/*4822 */         gen_extu(ot, cpu_T0);                                                                 // 0.0
/*4826 */         /* Note that lzcnt and tzcnt are in different extensions.  */                         // 0.0
/*4828 */         if ((prefixes & PREFIX_REPZ)                                                          // 0.0
/*4830 */             && (b & 1                                                                         // 0.0
/*4832 */                 ? s->cpuid_ext3_features & CPUID_EXT3_ABM                                     // 0.0
/*4834 */                 : s->cpuid_7_0_ebx_features & CPUID_7_0_EBX_BMI1)) {                          // 0.0
/*4836 */             int size = 8 << ot;                                                               // 0.0
/*4838 */             /* For lzcnt/tzcnt, C bit is defined related to the input. */                     // 0.0
/*4840 */             tcg_gen_mov_tl(cpu_cc_src, cpu_T0);                                               // 0.0
/*4842 */             if (b & 1) {                                                                      // 0.0
/*4844 */                 /* For lzcnt, reduce the target_ulong result by the                           // 0.0
/*4846 */                    number of zeros that we expect to find at the top.  */                     // 0.0
/*4848 */                 tcg_gen_clzi_tl(cpu_T0, cpu_T0, TARGET_LONG_BITS);                            // 0.0
/*4850 */                 tcg_gen_subi_tl(cpu_T0, cpu_T0, TARGET_LONG_BITS - size);                     // 0.0
/*4852 */             } else {                                                                          // 0.0
/*4854 */                 /* For tzcnt, a zero input must return the operand size.  */                  // 0.0
/*4856 */                 tcg_gen_ctzi_tl(cpu_T0, cpu_T0, size);                                        // 0.0
/*4858 */             }                                                                                 // 0.0
/*4860 */             /* For lzcnt/tzcnt, Z bit is defined related to the result.  */                   // 0.0
/*4862 */             gen_op_update1_cc();                                                              // 0.0
/*4864 */             set_cc_op(s, CC_OP_BMILGB + ot);                                                  // 0.0
/*4866 */         } else {                                                                              // 0.0
/*4868 */             /* For bsr/bsf, only the Z bit is defined and it is related                       // 0.0
/*4870 */                to the input and not the result.  */                                           // 0.0
/*4872 */             tcg_gen_mov_tl(cpu_cc_dst, cpu_T0);                                               // 0.0
/*4874 */             set_cc_op(s, CC_OP_LOGICB + ot);                                                  // 0.0
/*4878 */             /* ??? The manual says that the output is undefined when the                      // 0.0
/*4880 */                input is zero, but real hardware leaves it unchanged, and                      // 0.0
/*4882 */                real programs appear to depend on that.  Accomplish this                       // 0.0
/*4884 */                by passing the output as the value to return upon zero.  */                    // 0.0
/*4886 */             if (b & 1) {                                                                      // 0.0
/*4888 */                 /* For bsr, return the bit index of the first 1 bit,                          // 0.0
/*4890 */                    not the count of leading zeros.  */                                        // 0.0
/*4892 */                 tcg_gen_xori_tl(cpu_T1, cpu_regs[reg], TARGET_LONG_BITS - 1);                 // 0.0
/*4894 */                 tcg_gen_clz_tl(cpu_T0, cpu_T0, cpu_T1);                                       // 0.0
/*4896 */                 tcg_gen_xori_tl(cpu_T0, cpu_T0, TARGET_LONG_BITS - 1);                        // 0.0
/*4898 */             } else {                                                                          // 0.0
/*4900 */                 tcg_gen_ctz_tl(cpu_T0, cpu_T0, cpu_regs[reg]);                                // 0.0
/*4902 */             }                                                                                 // 0.0
/*4904 */         }                                                                                     // 0.0
/*4906 */         gen_op_mov_reg_v(ot, reg, cpu_T0);                                                    // 0.0
/*4908 */         break;                                                                                // 0.0
/*4910 */         /************************/                                                            // 0.0
/*4912 */         /* bcd */                                                                             // 0.0
/*4914 */     case 0x27: /* daa */                                                                      // 0.0
/*4916 */         if (CODE64(s))                                                                        // 0.0
/*4918 */             goto illegal_op;                                                                  // 0.0
/*4920 */         gen_update_cc_op(s);                                                                  // 0.0
/*4922 */         gen_helper_daa(cpu_env);                                                              // 0.0
/*4924 */         set_cc_op(s, CC_OP_EFLAGS);                                                           // 0.0
/*4926 */         break;                                                                                // 0.0
/*4928 */     case 0x2f: /* das */                                                                      // 0.0
/*4930 */         if (CODE64(s))                                                                        // 0.0
/*4932 */             goto illegal_op;                                                                  // 0.0
/*4934 */         gen_update_cc_op(s);                                                                  // 0.0
/*4936 */         gen_helper_das(cpu_env);                                                              // 0.0
/*4938 */         set_cc_op(s, CC_OP_EFLAGS);                                                           // 0.0
/*4940 */         break;                                                                                // 0.0
/*4942 */     case 0x37: /* aaa */                                                                      // 0.0
/*4944 */         if (CODE64(s))                                                                        // 0.0
/*4946 */             goto illegal_op;                                                                  // 0.0
/*4948 */         gen_update_cc_op(s);                                                                  // 0.0
/*4950 */         gen_helper_aaa(cpu_env);                                                              // 0.0
/*4952 */         set_cc_op(s, CC_OP_EFLAGS);                                                           // 0.0
/*4954 */         break;                                                                                // 0.0
/*4956 */     case 0x3f: /* aas */                                                                      // 0.0
/*4958 */         if (CODE64(s))                                                                        // 0.0
/*4960 */             goto illegal_op;                                                                  // 0.0
/*4962 */         gen_update_cc_op(s);                                                                  // 0.0
/*4964 */         gen_helper_aas(cpu_env);                                                              // 0.0
/*4966 */         set_cc_op(s, CC_OP_EFLAGS);                                                           // 0.0
/*4968 */         break;                                                                                // 0.0
/*4970 */     case 0xd4: /* aam */                                                                      // 0.0
/*4972 */         if (CODE64(s))                                                                        // 0.0
/*4974 */             goto illegal_op;                                                                  // 0.0
/*4976 */         val = x86_ldub_code(env, s);                                                          // 0.0
/*4978 */         if (val == 0) {                                                                       // 0.0
/*4980 */             gen_exception(s, EXCP00_DIVZ, pc_start - s->cs_base);                             // 0.0
/*4982 */         } else {                                                                              // 0.0
/*4984 */             gen_helper_aam(cpu_env, tcg_const_i32(val));                                      // 0.0
/*4986 */             set_cc_op(s, CC_OP_LOGICB);                                                       // 0.0
/*4988 */         }                                                                                     // 0.0
/*4990 */         break;                                                                                // 0.0
/*4992 */     case 0xd5: /* aad */                                                                      // 0.0
/*4994 */         if (CODE64(s))                                                                        // 0.0
/*4996 */             goto illegal_op;                                                                  // 0.0
/*4998 */         val = x86_ldub_code(env, s);                                                          // 0.0
/*5000 */         gen_helper_aad(cpu_env, tcg_const_i32(val));                                          // 0.0
/*5002 */         set_cc_op(s, CC_OP_LOGICB);                                                           // 0.0
/*5004 */         break;                                                                                // 0.0
/*5006 */         /************************/                                                            // 0.0
/*5008 */         /* misc */                                                                            // 0.0
/*5010 */     case 0x90: /* nop */                                                                      // 0.0
/*5012 */         /* XXX: correct lock test for all insn */                                             // 0.0
/*5014 */         if (prefixes & PREFIX_LOCK) {                                                         // 0.0
/*5016 */             goto illegal_op;                                                                  // 0.0
/*5018 */         }                                                                                     // 0.0
/*5020 */         /* If REX_B is set, then this is xchg eax, r8d, not a nop.  */                        // 0.0
/*5022 */         if (REX_B(s)) {                                                                       // 0.0
/*5024 */             goto do_xchg_reg_eax;                                                             // 0.0
/*5026 */         }                                                                                     // 0.0
/*5028 */         if (prefixes & PREFIX_REPZ) {                                                         // 0.0
/*5030 */             gen_update_cc_op(s);                                                              // 0.0
/*5032 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*5034 */             gen_helper_pause(cpu_env, tcg_const_i32(s->pc - pc_start));                       // 0.0
/*5036 */             s->base.is_jmp = DISAS_NORETURN;                                                  // 0.0
/*5038 */         }                                                                                     // 0.0
/*5040 */         break;                                                                                // 0.0
/*5042 */     case 0x9b: /* fwait */                                                                    // 0.0
/*5044 */         if ((s->flags & (HF_MP_MASK | HF_TS_MASK)) ==                                         // 0.0
/*5046 */             (HF_MP_MASK | HF_TS_MASK)) {                                                      // 0.0
/*5048 */             gen_exception(s, EXCP07_PREX, pc_start - s->cs_base);                             // 0.0
/*5050 */         } else {                                                                              // 0.0
/*5052 */             gen_helper_fwait(cpu_env);                                                        // 0.0
/*5054 */         }                                                                                     // 0.0
/*5056 */         break;                                                                                // 0.0
/*5058 */     case 0xcc: /* int3 */                                                                     // 0.0
/*5060 */         gen_interrupt(s, EXCP03_INT3, pc_start - s->cs_base, s->pc - s->cs_base);             // 0.0
/*5062 */         break;                                                                                // 0.0
/*5064 */     case 0xcd: /* int N */                                                                    // 0.0
/*5066 */         val = x86_ldub_code(env, s);                                                          // 0.0
/*5068 */         if (s->vm86 && s->iopl != 3) {                                                        // 0.0
/*5070 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*5072 */         } else {                                                                              // 0.0
/*5074 */             gen_interrupt(s, val, pc_start - s->cs_base, s->pc - s->cs_base);                 // 0.0
/*5076 */         }                                                                                     // 0.0
/*5078 */         break;                                                                                // 0.0
/*5080 */     case 0xce: /* into */                                                                     // 0.0
/*5082 */         if (CODE64(s))                                                                        // 0.0
/*5084 */             goto illegal_op;                                                                  // 0.0
/*5086 */         gen_update_cc_op(s);                                                                  // 0.0
/*5088 */         gen_jmp_im(pc_start - s->cs_base);                                                    // 0.0
/*5090 */         gen_helper_into(cpu_env, tcg_const_i32(s->pc - pc_start));                            // 0.0
/*5092 */         break;                                                                                // 0.0
/*5094 */ #ifdef WANT_ICEBP                                                                             // 0.0
/*5096 */     case 0xf1: /* icebp (undocumented, exits to external debugger) */                         // 0.0
/*5098 */         gen_svm_check_intercept(s, pc_start, SVM_EXIT_ICEBP);                                 // 0.0
/*5100 */ #if 1                                                                                         // 0.0
/*5102 */         gen_debug(s, pc_start - s->cs_base);                                                  // 0.0
/*5104 */ #else                                                                                         // 0.0
/*5106 */         /* start debug */                                                                     // 0.0
/*5108 */         tb_flush(CPU(x86_env_get_cpu(env)));                                                  // 0.0
/*5110 */         qemu_set_log(CPU_LOG_INT | CPU_LOG_TB_IN_ASM);                                        // 0.0
/*5112 */ #endif                                                                                        // 0.0
/*5114 */         break;                                                                                // 0.0
/*5116 */ #endif                                                                                        // 0.0
/*5118 */     case 0xfa: /* cli */                                                                      // 0.0
/*5120 */         if (!s->vm86) {                                                                       // 0.0
/*5122 */             if (s->cpl <= s->iopl) {                                                          // 0.0
/*5124 */                 gen_helper_cli(cpu_env);                                                      // 0.0
/*5126 */             } else {                                                                          // 0.0
/*5128 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*5130 */             }                                                                                 // 0.0
/*5132 */         } else {                                                                              // 0.0
/*5134 */             if (s->iopl == 3) {                                                               // 0.0
/*5136 */                 gen_helper_cli(cpu_env);                                                      // 0.0
/*5138 */             } else {                                                                          // 0.0
/*5140 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*5142 */             }                                                                                 // 0.0
/*5144 */         }                                                                                     // 0.0
/*5146 */         break;                                                                                // 0.0
/*5148 */     case 0xfb: /* sti */                                                                      // 0.0
/*5150 */         if (s->vm86 ? s->iopl == 3 : s->cpl <= s->iopl) {                                     // 0.0
/*5152 */             gen_helper_sti(cpu_env);                                                          // 0.0
/*5154 */             /* interruptions are enabled only the first insn after sti */                     // 0.0
/*5156 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*5158 */             gen_eob_inhibit_irq(s, true);                                                     // 0.0
/*5160 */         } else {                                                                              // 0.0
/*5162 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*5164 */         }                                                                                     // 0.0
/*5166 */         break;                                                                                // 0.0
/*5168 */     case 0x62: /* bound */                                                                    // 0.0
/*5170 */         if (CODE64(s))                                                                        // 0.0
/*5172 */             goto illegal_op;                                                                  // 0.0
/*5174 */         ot = dflag;                                                                           // 0.0
/*5176 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*5178 */         reg = (modrm >> 3) & 7;                                                               // 0.0
/*5180 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*5182 */         if (mod == 3)                                                                         // 0.0
/*5184 */             goto illegal_op;                                                                  // 0.0
/*5186 */         gen_op_mov_v_reg(ot, cpu_T0, reg);                                                    // 0.0
/*5188 */         gen_lea_modrm(env, s, modrm);                                                         // 0.0
/*5190 */         tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                           // 0.0
/*5192 */         if (ot == MO_16) {                                                                    // 0.0
/*5194 */             gen_helper_boundw(cpu_env, cpu_A0, cpu_tmp2_i32);                                 // 0.0
/*5196 */         } else {                                                                              // 0.0
/*5198 */             gen_helper_boundl(cpu_env, cpu_A0, cpu_tmp2_i32);                                 // 0.0
/*5200 */         }                                                                                     // 0.0
/*5202 */         break;                                                                                // 0.0
/*5204 */     case 0x1c8 ... 0x1cf: /* bswap reg */                                                     // 0.0
/*5206 */         reg = (b & 7) | REX_B(s);                                                             // 0.0
/*5208 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*5210 */         if (dflag == MO_64) {                                                                 // 0.0
/*5212 */             gen_op_mov_v_reg(MO_64, cpu_T0, reg);                                             // 0.0
/*5214 */             tcg_gen_bswap64_i64(cpu_T0, cpu_T0);                                              // 0.0
/*5216 */             gen_op_mov_reg_v(MO_64, reg, cpu_T0);                                             // 0.0
/*5218 */         } else                                                                                // 0.0
/*5220 */ #endif                                                                                        // 0.0
/*5222 */         {                                                                                     // 0.0
/*5224 */             gen_op_mov_v_reg(MO_32, cpu_T0, reg);                                             // 0.0
/*5226 */             tcg_gen_ext32u_tl(cpu_T0, cpu_T0);                                                // 0.0
/*5228 */             tcg_gen_bswap32_tl(cpu_T0, cpu_T0);                                               // 0.0
/*5230 */             gen_op_mov_reg_v(MO_32, reg, cpu_T0);                                             // 0.0
/*5232 */         }                                                                                     // 0.0
/*5234 */         break;                                                                                // 0.0
/*5236 */     case 0xd6: /* salc */                                                                     // 0.0
/*5238 */         if (CODE64(s))                                                                        // 0.0
/*5240 */             goto illegal_op;                                                                  // 0.0
/*5242 */         gen_compute_eflags_c(s, cpu_T0);                                                      // 0.0
/*5244 */         tcg_gen_neg_tl(cpu_T0, cpu_T0);                                                       // 0.0
/*5246 */         gen_op_mov_reg_v(MO_8, R_EAX, cpu_T0);                                                // 0.0
/*5248 */         break;                                                                                // 0.0
/*5250 */     case 0xe0: /* loopnz */                                                                   // 0.0
/*5252 */     case 0xe1: /* loopz */                                                                    // 0.0
/*5254 */     case 0xe2: /* loop */                                                                     // 0.0
/*5256 */     case 0xe3: /* jecxz */                                                                    // 0.0
/*5258 */         {                                                                                     // 0.0
/*5260 */             TCGLabel *l1, *l2, *l3;                                                           // 0.0
/*5264 */             tval = (int8_t)insn_get(env, s, MO_8);                                            // 0.0
/*5266 */             next_eip = s->pc - s->cs_base;                                                    // 0.0
/*5268 */             tval += next_eip;                                                                 // 0.0
/*5270 */             if (dflag == MO_16) {                                                             // 0.0
/*5272 */                 tval &= 0xffff;                                                               // 0.0
/*5274 */             }                                                                                 // 0.0
/*5278 */             l1 = gen_new_label();                                                             // 0.0
/*5280 */             l2 = gen_new_label();                                                             // 0.0
/*5282 */             l3 = gen_new_label();                                                             // 0.0
/*5284 */             b &= 3;                                                                           // 0.0
/*5286 */             switch(b) {                                                                       // 0.0
/*5288 */             case 0: /* loopnz */                                                              // 0.0
/*5290 */             case 1: /* loopz */                                                               // 0.0
/*5292 */                 gen_op_add_reg_im(s->aflag, R_ECX, -1);                                       // 0.0
/*5294 */                 gen_op_jz_ecx(s->aflag, l3);                                                  // 0.0
/*5296 */                 gen_jcc1(s, (JCC_Z << 1) | (b ^ 1), l1);                                      // 0.0
/*5298 */                 break;                                                                        // 0.0
/*5300 */             case 2: /* loop */                                                                // 0.0
/*5302 */                 gen_op_add_reg_im(s->aflag, R_ECX, -1);                                       // 0.0
/*5304 */                 gen_op_jnz_ecx(s->aflag, l1);                                                 // 0.0
/*5306 */                 break;                                                                        // 0.0
/*5308 */             default:                                                                          // 0.0
/*5310 */             case 3: /* jcxz */                                                                // 0.0
/*5312 */                 gen_op_jz_ecx(s->aflag, l1);                                                  // 0.0
/*5314 */                 break;                                                                        // 0.0
/*5316 */             }                                                                                 // 0.0
/*5320 */             gen_set_label(l3);                                                                // 0.0
/*5322 */             gen_jmp_im(next_eip);                                                             // 0.0
/*5324 */             tcg_gen_br(l2);                                                                   // 0.0
/*5328 */             gen_set_label(l1);                                                                // 0.0
/*5330 */             gen_jmp_im(tval);                                                                 // 0.0
/*5332 */             gen_set_label(l2);                                                                // 0.0
/*5334 */             gen_eob(s);                                                                       // 0.0
/*5336 */         }                                                                                     // 0.0
/*5338 */         break;                                                                                // 0.0
/*5340 */     case 0x130: /* wrmsr */                                                                   // 0.0
/*5342 */     case 0x132: /* rdmsr */                                                                   // 0.0
/*5344 */         if (s->cpl != 0) {                                                                    // 0.0
/*5346 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*5348 */         } else {                                                                              // 0.0
/*5350 */             gen_update_cc_op(s);                                                              // 0.0
/*5352 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*5354 */             if (b & 2) {                                                                      // 0.0
/*5356 */                 gen_helper_rdmsr(cpu_env);                                                    // 0.0
/*5358 */             } else {                                                                          // 0.0
/*5360 */                 gen_helper_wrmsr(cpu_env);                                                    // 0.0
/*5362 */             }                                                                                 // 0.0
/*5364 */         }                                                                                     // 0.0
/*5366 */         break;                                                                                // 0.0
/*5368 */     case 0x131: /* rdtsc */                                                                   // 0.0
/*5370 */         gen_update_cc_op(s);                                                                  // 0.0
/*5372 */         gen_jmp_im(pc_start - s->cs_base);                                                    // 0.0
/*5374 */         if (s->base.tb->cflags & CF_USE_ICOUNT) {                                             // 0.0
/*5376 */             gen_io_start();                                                                   // 0.0
/*5378 */ 	}                                                                                            // 0.0
/*5380 */         gen_helper_rdtsc(cpu_env);                                                            // 0.0
/*5382 */         if (s->base.tb->cflags & CF_USE_ICOUNT) {                                             // 0.0
/*5384 */             gen_io_end();                                                                     // 0.0
/*5386 */             gen_jmp(s, s->pc - s->cs_base);                                                   // 0.0
/*5388 */         }                                                                                     // 0.0
/*5390 */         break;                                                                                // 0.0
/*5392 */     case 0x133: /* rdpmc */                                                                   // 0.0
/*5394 */         gen_update_cc_op(s);                                                                  // 0.0
/*5396 */         gen_jmp_im(pc_start - s->cs_base);                                                    // 0.0
/*5398 */         gen_helper_rdpmc(cpu_env);                                                            // 0.0
/*5400 */         break;                                                                                // 0.0
/*5402 */     case 0x134: /* sysenter */                                                                // 0.0
/*5404 */         /* For Intel SYSENTER is valid on 64-bit */                                           // 0.0
/*5406 */         if (CODE64(s) && env->cpuid_vendor1 != CPUID_VENDOR_INTEL_1)                          // 0.0
/*5408 */             goto illegal_op;                                                                  // 0.0
/*5410 */         if (!s->pe) {                                                                         // 0.0
/*5412 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*5414 */         } else {                                                                              // 0.0
/*5416 */             gen_helper_sysenter(cpu_env);                                                     // 0.0
/*5418 */             gen_eob(s);                                                                       // 0.0
/*5420 */         }                                                                                     // 0.0
/*5422 */         break;                                                                                // 0.0
/*5424 */     case 0x135: /* sysexit */                                                                 // 0.0
/*5426 */         /* For Intel SYSEXIT is valid on 64-bit */                                            // 0.0
/*5428 */         if (CODE64(s) && env->cpuid_vendor1 != CPUID_VENDOR_INTEL_1)                          // 0.0
/*5430 */             goto illegal_op;                                                                  // 0.0
/*5432 */         if (!s->pe) {                                                                         // 0.0
/*5434 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*5436 */         } else {                                                                              // 0.0
/*5438 */             gen_helper_sysexit(cpu_env, tcg_const_i32(dflag - 1));                            // 0.0
/*5440 */             gen_eob(s);                                                                       // 0.0
/*5442 */         }                                                                                     // 0.0
/*5444 */         break;                                                                                // 0.0
/*5446 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*5448 */     case 0x105: /* syscall */                                                                 // 0.0
/*5450 */         /* XXX: is it usable in real mode ? */                                                // 0.0
/*5452 */         gen_update_cc_op(s);                                                                  // 0.0
/*5454 */         gen_jmp_im(pc_start - s->cs_base);                                                    // 0.0
/*5456 */         gen_helper_syscall(cpu_env, tcg_const_i32(s->pc - pc_start));                         // 0.0
/*5458 */         /* TF handling for the syscall insn is different. The TF bit is  checked              // 0.0
/*5460 */            after the syscall insn completes. This allows #DB to not be                        // 0.0
/*5462 */            generated after one has entered CPL0 if TF is set in FMASK.  */                    // 0.0
/*5464 */         gen_eob_worker(s, false, true);                                                       // 0.0
/*5466 */         break;                                                                                // 0.0
/*5468 */     case 0x107: /* sysret */                                                                  // 0.0
/*5470 */         if (!s->pe) {                                                                         // 0.0
/*5472 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*5474 */         } else {                                                                              // 0.0
/*5476 */             gen_helper_sysret(cpu_env, tcg_const_i32(dflag - 1));                             // 0.0
/*5478 */             /* condition codes are modified only in long mode */                              // 0.0
/*5480 */             if (s->lma) {                                                                     // 0.0
/*5482 */                 set_cc_op(s, CC_OP_EFLAGS);                                                   // 0.0
/*5484 */             }                                                                                 // 0.0
/*5486 */             /* TF handling for the sysret insn is different. The TF bit is                    // 0.0
/*5488 */                checked after the sysret insn completes. This allows #DB to be                 // 0.0
/*5490 */                generated "as if" the syscall insn in userspace has just                       // 0.0
/*5492 */                completed.  */                                                                 // 0.0
/*5494 */             gen_eob_worker(s, false, true);                                                   // 0.0
/*5496 */         }                                                                                     // 0.0
/*5498 */         break;                                                                                // 0.0
/*5500 */ #endif                                                                                        // 0.0
/*5502 */     case 0x1a2: /* cpuid */                                                                   // 0.0
/*5504 */         gen_update_cc_op(s);                                                                  // 0.0
/*5506 */         gen_jmp_im(pc_start - s->cs_base);                                                    // 0.0
/*5508 */         gen_helper_cpuid(cpu_env);                                                            // 0.0
/*5510 */         break;                                                                                // 0.0
/*5512 */     case 0xf4: /* hlt */                                                                      // 0.0
/*5514 */         if (s->cpl != 0) {                                                                    // 0.0
/*5516 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*5518 */         } else {                                                                              // 0.0
/*5520 */             gen_update_cc_op(s);                                                              // 0.0
/*5522 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*5524 */             gen_helper_hlt(cpu_env, tcg_const_i32(s->pc - pc_start));                         // 0.0
/*5526 */             s->base.is_jmp = DISAS_NORETURN;                                                  // 0.0
/*5528 */         }                                                                                     // 0.0
/*5530 */         break;                                                                                // 0.0
/*5532 */     case 0x100:                                                                               // 0.0
/*5534 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*5536 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*5538 */         op = (modrm >> 3) & 7;                                                                // 0.0
/*5540 */         switch(op) {                                                                          // 0.0
/*5542 */         case 0: /* sldt */                                                                    // 0.0
/*5544 */             if (!s->pe || s->vm86)                                                            // 0.0
/*5546 */                 goto illegal_op;                                                              // 0.0
/*5548 */             gen_svm_check_intercept(s, pc_start, SVM_EXIT_LDTR_READ);                         // 0.0
/*5550 */             tcg_gen_ld32u_tl(cpu_T0, cpu_env,                                                 // 0.0
/*5552 */                              offsetof(CPUX86State, ldt.selector));                            // 0.0
/*5554 */             ot = mod == 3 ? dflag : MO_16;                                                    // 0.0
/*5556 */             gen_ldst_modrm(env, s, modrm, ot, OR_TMP0, 1);                                    // 0.0
/*5558 */             break;                                                                            // 0.0
/*5560 */         case 2: /* lldt */                                                                    // 0.0
/*5562 */             if (!s->pe || s->vm86)                                                            // 0.0
/*5564 */                 goto illegal_op;                                                              // 0.0
/*5566 */             if (s->cpl != 0) {                                                                // 0.0
/*5568 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*5570 */             } else {                                                                          // 0.0
/*5572 */                 gen_svm_check_intercept(s, pc_start, SVM_EXIT_LDTR_WRITE);                    // 0.0
/*5574 */                 gen_ldst_modrm(env, s, modrm, MO_16, OR_TMP0, 0);                             // 0.0
/*5576 */                 tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                   // 0.0
/*5578 */                 gen_helper_lldt(cpu_env, cpu_tmp2_i32);                                       // 0.0
/*5580 */             }                                                                                 // 0.0
/*5582 */             break;                                                                            // 0.0
/*5584 */         case 1: /* str */                                                                     // 0.0
/*5586 */             if (!s->pe || s->vm86)                                                            // 0.0
/*5588 */                 goto illegal_op;                                                              // 0.0
/*5590 */             gen_svm_check_intercept(s, pc_start, SVM_EXIT_TR_READ);                           // 0.0
/*5592 */             tcg_gen_ld32u_tl(cpu_T0, cpu_env,                                                 // 0.0
/*5594 */                              offsetof(CPUX86State, tr.selector));                             // 0.0
/*5596 */             ot = mod == 3 ? dflag : MO_16;                                                    // 0.0
/*5598 */             gen_ldst_modrm(env, s, modrm, ot, OR_TMP0, 1);                                    // 0.0
/*5600 */             break;                                                                            // 0.0
/*5602 */         case 3: /* ltr */                                                                     // 0.0
/*5604 */             if (!s->pe || s->vm86)                                                            // 0.0
/*5606 */                 goto illegal_op;                                                              // 0.0
/*5608 */             if (s->cpl != 0) {                                                                // 0.0
/*5610 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*5612 */             } else {                                                                          // 0.0
/*5614 */                 gen_svm_check_intercept(s, pc_start, SVM_EXIT_TR_WRITE);                      // 0.0
/*5616 */                 gen_ldst_modrm(env, s, modrm, MO_16, OR_TMP0, 0);                             // 0.0
/*5618 */                 tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                                   // 0.0
/*5620 */                 gen_helper_ltr(cpu_env, cpu_tmp2_i32);                                        // 0.0
/*5622 */             }                                                                                 // 0.0
/*5624 */             break;                                                                            // 0.0
/*5626 */         case 4: /* verr */                                                                    // 0.0
/*5628 */         case 5: /* verw */                                                                    // 0.0
/*5630 */             if (!s->pe || s->vm86)                                                            // 0.0
/*5632 */                 goto illegal_op;                                                              // 0.0
/*5634 */             gen_ldst_modrm(env, s, modrm, MO_16, OR_TMP0, 0);                                 // 0.0
/*5636 */             gen_update_cc_op(s);                                                              // 0.0
/*5638 */             if (op == 4) {                                                                    // 0.0
/*5640 */                 gen_helper_verr(cpu_env, cpu_T0);                                             // 0.0
/*5642 */             } else {                                                                          // 0.0
/*5644 */                 gen_helper_verw(cpu_env, cpu_T0);                                             // 0.0
/*5646 */             }                                                                                 // 0.0
/*5648 */             set_cc_op(s, CC_OP_EFLAGS);                                                       // 0.0
/*5650 */             break;                                                                            // 0.0
/*5652 */         default:                                                                              // 0.0
/*5654 */             goto unknown_op;                                                                  // 0.0
/*5656 */         }                                                                                     // 0.0
/*5658 */         break;                                                                                // 0.0
/*5662 */     case 0x101:                                                                               // 0.0
/*5664 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*5666 */         switch (modrm) {                                                                      // 0.0
/*5668 */         CASE_MODRM_MEM_OP(0): /* sgdt */                                                      // 0.0
/*5670 */             gen_svm_check_intercept(s, pc_start, SVM_EXIT_GDTR_READ);                         // 0.0
/*5672 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*5674 */             tcg_gen_ld32u_tl(cpu_T0,                                                          // 0.0
/*5676 */                              cpu_env, offsetof(CPUX86State, gdt.limit));                      // 0.0
/*5678 */             gen_op_st_v(s, MO_16, cpu_T0, cpu_A0);                                            // 0.0
/*5680 */             gen_add_A0_im(s, 2);                                                              // 0.0
/*5682 */             tcg_gen_ld_tl(cpu_T0, cpu_env, offsetof(CPUX86State, gdt.base));                  // 0.0
/*5684 */             if (dflag == MO_16) {                                                             // 0.0
/*5686 */                 tcg_gen_andi_tl(cpu_T0, cpu_T0, 0xffffff);                                    // 0.0
/*5688 */             }                                                                                 // 0.0
/*5690 */             gen_op_st_v(s, CODE64(s) + MO_32, cpu_T0, cpu_A0);                                // 0.0
/*5692 */             break;                                                                            // 0.0
/*5696 */         case 0xc8: /* monitor */                                                              // 0.0
/*5698 */             if (!(s->cpuid_ext_features & CPUID_EXT_MONITOR) || s->cpl != 0) {                // 0.0
/*5700 */                 goto illegal_op;                                                              // 0.0
/*5702 */             }                                                                                 // 0.0
/*5704 */             gen_update_cc_op(s);                                                              // 0.0
/*5706 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*5708 */             tcg_gen_mov_tl(cpu_A0, cpu_regs[R_EAX]);                                          // 0.0
/*5710 */             gen_extu(s->aflag, cpu_A0);                                                       // 0.0
/*5712 */             gen_add_A0_ds_seg(s);                                                             // 0.0
/*5714 */             gen_helper_monitor(cpu_env, cpu_A0);                                              // 0.0
/*5716 */             break;                                                                            // 0.0
/*5720 */         case 0xc9: /* mwait */                                                                // 0.0
/*5722 */             if (!(s->cpuid_ext_features & CPUID_EXT_MONITOR) || s->cpl != 0) {                // 0.0
/*5724 */                 goto illegal_op;                                                              // 0.0
/*5726 */             }                                                                                 // 0.0
/*5728 */             gen_update_cc_op(s);                                                              // 0.0
/*5730 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*5732 */             gen_helper_mwait(cpu_env, tcg_const_i32(s->pc - pc_start));                       // 0.0
/*5734 */             gen_eob(s);                                                                       // 0.0
/*5736 */             break;                                                                            // 0.0
/*5740 */         case 0xca: /* clac */                                                                 // 0.0
/*5742 */             if (!(s->cpuid_7_0_ebx_features & CPUID_7_0_EBX_SMAP)                             // 0.0
/*5744 */                 || s->cpl != 0) {                                                             // 0.0
/*5746 */                 goto illegal_op;                                                              // 0.0
/*5748 */             }                                                                                 // 0.0
/*5750 */             gen_helper_clac(cpu_env);                                                         // 0.0
/*5752 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*5754 */             gen_eob(s);                                                                       // 0.0
/*5756 */             break;                                                                            // 0.0
/*5760 */         case 0xcb: /* stac */                                                                 // 0.0
/*5762 */             if (!(s->cpuid_7_0_ebx_features & CPUID_7_0_EBX_SMAP)                             // 0.0
/*5764 */                 || s->cpl != 0) {                                                             // 0.0
/*5766 */                 goto illegal_op;                                                              // 0.0
/*5768 */             }                                                                                 // 0.0
/*5770 */             gen_helper_stac(cpu_env);                                                         // 0.0
/*5772 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*5774 */             gen_eob(s);                                                                       // 0.0
/*5776 */             break;                                                                            // 0.0
/*5780 */         CASE_MODRM_MEM_OP(1): /* sidt */                                                      // 0.0
/*5782 */             gen_svm_check_intercept(s, pc_start, SVM_EXIT_IDTR_READ);                         // 0.0
/*5784 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*5786 */             tcg_gen_ld32u_tl(cpu_T0, cpu_env, offsetof(CPUX86State, idt.limit));              // 0.0
/*5788 */             gen_op_st_v(s, MO_16, cpu_T0, cpu_A0);                                            // 0.0
/*5790 */             gen_add_A0_im(s, 2);                                                              // 0.0
/*5792 */             tcg_gen_ld_tl(cpu_T0, cpu_env, offsetof(CPUX86State, idt.base));                  // 0.0
/*5794 */             if (dflag == MO_16) {                                                             // 0.0
/*5796 */                 tcg_gen_andi_tl(cpu_T0, cpu_T0, 0xffffff);                                    // 0.0
/*5798 */             }                                                                                 // 0.0
/*5800 */             gen_op_st_v(s, CODE64(s) + MO_32, cpu_T0, cpu_A0);                                // 0.0
/*5802 */             break;                                                                            // 0.0
/*5806 */         case 0xd0: /* xgetbv */                                                               // 0.0
/*5808 */             if ((s->cpuid_ext_features & CPUID_EXT_XSAVE) == 0                                // 0.0
/*5810 */                 || (s->prefix & (PREFIX_LOCK | PREFIX_DATA                                    // 0.0
/*5812 */                                  | PREFIX_REPZ | PREFIX_REPNZ))) {                            // 0.0
/*5814 */                 goto illegal_op;                                                              // 0.0
/*5816 */             }                                                                                 // 0.0
/*5818 */             tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_regs[R_ECX]);                              // 0.0
/*5820 */             gen_helper_xgetbv(cpu_tmp1_i64, cpu_env, cpu_tmp2_i32);                           // 0.0
/*5822 */             tcg_gen_extr_i64_tl(cpu_regs[R_EAX], cpu_regs[R_EDX], cpu_tmp1_i64);              // 0.0
/*5824 */             break;                                                                            // 0.0
/*5828 */         case 0xd1: /* xsetbv */                                                               // 0.0
/*5830 */             if ((s->cpuid_ext_features & CPUID_EXT_XSAVE) == 0                                // 0.0
/*5832 */                 || (s->prefix & (PREFIX_LOCK | PREFIX_DATA                                    // 0.0
/*5834 */                                  | PREFIX_REPZ | PREFIX_REPNZ))) {                            // 0.0
/*5836 */                 goto illegal_op;                                                              // 0.0
/*5838 */             }                                                                                 // 0.0
/*5840 */             if (s->cpl != 0) {                                                                // 0.0
/*5842 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*5844 */                 break;                                                                        // 0.0
/*5846 */             }                                                                                 // 0.0
/*5848 */             tcg_gen_concat_tl_i64(cpu_tmp1_i64, cpu_regs[R_EAX],                              // 0.0
/*5850 */                                   cpu_regs[R_EDX]);                                           // 0.0
/*5852 */             tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_regs[R_ECX]);                              // 0.0
/*5854 */             gen_helper_xsetbv(cpu_env, cpu_tmp2_i32, cpu_tmp1_i64);                           // 0.0
/*5856 */             /* End TB because translation flags may change.  */                               // 0.0
/*5858 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*5860 */             gen_eob(s);                                                                       // 0.0
/*5862 */             break;                                                                            // 0.0
/*5866 */         case 0xd8: /* VMRUN */                                                                // 0.0
/*5868 */             if (!(s->flags & HF_SVME_MASK) || !s->pe) {                                       // 0.0
/*5870 */                 goto illegal_op;                                                              // 0.0
/*5872 */             }                                                                                 // 0.0
/*5874 */             if (s->cpl != 0) {                                                                // 0.0
/*5876 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*5878 */                 break;                                                                        // 0.0
/*5880 */             }                                                                                 // 0.0
/*5882 */             gen_update_cc_op(s);                                                              // 0.0
/*5884 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*5886 */             gen_helper_vmrun(cpu_env, tcg_const_i32(s->aflag - 1),                            // 0.0
/*5888 */                              tcg_const_i32(s->pc - pc_start));                                // 0.0
/*5890 */             tcg_gen_exit_tb(0);                                                               // 0.0
/*5892 */             s->base.is_jmp = DISAS_NORETURN;                                                  // 0.0
/*5894 */             break;                                                                            // 0.0
/*5898 */         case 0xd9: /* VMMCALL */                                                              // 0.0
/*5900 */             if (!(s->flags & HF_SVME_MASK)) {                                                 // 0.0
/*5902 */                 goto illegal_op;                                                              // 0.0
/*5904 */             }                                                                                 // 0.0
/*5906 */             gen_update_cc_op(s);                                                              // 0.0
/*5908 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*5910 */             gen_helper_vmmcall(cpu_env);                                                      // 0.0
/*5912 */             break;                                                                            // 0.0
/*5916 */         case 0xda: /* VMLOAD */                                                               // 0.0
/*5918 */             if (!(s->flags & HF_SVME_MASK) || !s->pe) {                                       // 0.0
/*5920 */                 goto illegal_op;                                                              // 0.0
/*5922 */             }                                                                                 // 0.0
/*5924 */             if (s->cpl != 0) {                                                                // 0.0
/*5926 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*5928 */                 break;                                                                        // 0.0
/*5930 */             }                                                                                 // 0.0
/*5932 */             gen_update_cc_op(s);                                                              // 0.0
/*5934 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*5936 */             gen_helper_vmload(cpu_env, tcg_const_i32(s->aflag - 1));                          // 0.0
/*5938 */             break;                                                                            // 0.0
/*5942 */         case 0xdb: /* VMSAVE */                                                               // 0.0
/*5944 */             if (!(s->flags & HF_SVME_MASK) || !s->pe) {                                       // 0.0
/*5946 */                 goto illegal_op;                                                              // 0.0
/*5948 */             }                                                                                 // 0.0
/*5950 */             if (s->cpl != 0) {                                                                // 0.0
/*5952 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*5954 */                 break;                                                                        // 0.0
/*5956 */             }                                                                                 // 0.0
/*5958 */             gen_update_cc_op(s);                                                              // 0.0
/*5960 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*5962 */             gen_helper_vmsave(cpu_env, tcg_const_i32(s->aflag - 1));                          // 0.0
/*5964 */             break;                                                                            // 0.0
/*5968 */         case 0xdc: /* STGI */                                                                 // 0.0
/*5970 */             if ((!(s->flags & HF_SVME_MASK)                                                   // 0.0
/*5972 */                    && !(s->cpuid_ext3_features & CPUID_EXT3_SKINIT))                          // 0.0
/*5974 */                 || !s->pe) {                                                                  // 0.0
/*5976 */                 goto illegal_op;                                                              // 0.0
/*5978 */             }                                                                                 // 0.0
/*5980 */             if (s->cpl != 0) {                                                                // 0.0
/*5982 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*5984 */                 break;                                                                        // 0.0
/*5986 */             }                                                                                 // 0.0
/*5988 */             gen_update_cc_op(s);                                                              // 0.0
/*5990 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*5992 */             gen_helper_stgi(cpu_env);                                                         // 0.0
/*5994 */             break;                                                                            // 0.0
/*5998 */         case 0xdd: /* CLGI */                                                                 // 0.0
/*6000 */             if (!(s->flags & HF_SVME_MASK) || !s->pe) {                                       // 0.0
/*6002 */                 goto illegal_op;                                                              // 0.0
/*6004 */             }                                                                                 // 0.0
/*6006 */             if (s->cpl != 0) {                                                                // 0.0
/*6008 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*6010 */                 break;                                                                        // 0.0
/*6012 */             }                                                                                 // 0.0
/*6014 */             gen_update_cc_op(s);                                                              // 0.0
/*6016 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*6018 */             gen_helper_clgi(cpu_env);                                                         // 0.0
/*6020 */             break;                                                                            // 0.0
/*6024 */         case 0xde: /* SKINIT */                                                               // 0.0
/*6026 */             if ((!(s->flags & HF_SVME_MASK)                                                   // 0.0
/*6028 */                  && !(s->cpuid_ext3_features & CPUID_EXT3_SKINIT))                            // 0.0
/*6030 */                 || !s->pe) {                                                                  // 0.0
/*6032 */                 goto illegal_op;                                                              // 0.0
/*6034 */             }                                                                                 // 0.0
/*6036 */             gen_update_cc_op(s);                                                              // 0.0
/*6038 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*6040 */             gen_helper_skinit(cpu_env);                                                       // 0.0
/*6042 */             break;                                                                            // 0.0
/*6046 */         case 0xdf: /* INVLPGA */                                                              // 0.0
/*6048 */             if (!(s->flags & HF_SVME_MASK) || !s->pe) {                                       // 0.0
/*6050 */                 goto illegal_op;                                                              // 0.0
/*6052 */             }                                                                                 // 0.0
/*6054 */             if (s->cpl != 0) {                                                                // 0.0
/*6056 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*6058 */                 break;                                                                        // 0.0
/*6060 */             }                                                                                 // 0.0
/*6062 */             gen_update_cc_op(s);                                                              // 0.0
/*6064 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*6066 */             gen_helper_invlpga(cpu_env, tcg_const_i32(s->aflag - 1));                         // 0.0
/*6068 */             break;                                                                            // 0.0
/*6072 */         CASE_MODRM_MEM_OP(2): /* lgdt */                                                      // 0.0
/*6074 */             if (s->cpl != 0) {                                                                // 0.0
/*6076 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*6078 */                 break;                                                                        // 0.0
/*6080 */             }                                                                                 // 0.0
/*6082 */             gen_svm_check_intercept(s, pc_start, SVM_EXIT_GDTR_WRITE);                        // 0.0
/*6084 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*6086 */             gen_op_ld_v(s, MO_16, cpu_T1, cpu_A0);                                            // 0.0
/*6088 */             gen_add_A0_im(s, 2);                                                              // 0.0
/*6090 */             gen_op_ld_v(s, CODE64(s) + MO_32, cpu_T0, cpu_A0);                                // 0.0
/*6092 */             if (dflag == MO_16) {                                                             // 0.0
/*6094 */                 tcg_gen_andi_tl(cpu_T0, cpu_T0, 0xffffff);                                    // 0.0
/*6096 */             }                                                                                 // 0.0
/*6098 */             tcg_gen_st_tl(cpu_T0, cpu_env, offsetof(CPUX86State, gdt.base));                  // 0.0
/*6100 */             tcg_gen_st32_tl(cpu_T1, cpu_env, offsetof(CPUX86State, gdt.limit));               // 0.0
/*6102 */             break;                                                                            // 0.0
/*6106 */         CASE_MODRM_MEM_OP(3): /* lidt */                                                      // 0.0
/*6108 */             if (s->cpl != 0) {                                                                // 0.0
/*6110 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*6112 */                 break;                                                                        // 0.0
/*6114 */             }                                                                                 // 0.0
/*6116 */             gen_svm_check_intercept(s, pc_start, SVM_EXIT_IDTR_WRITE);                        // 0.0
/*6118 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*6120 */             gen_op_ld_v(s, MO_16, cpu_T1, cpu_A0);                                            // 0.0
/*6122 */             gen_add_A0_im(s, 2);                                                              // 0.0
/*6124 */             gen_op_ld_v(s, CODE64(s) + MO_32, cpu_T0, cpu_A0);                                // 0.0
/*6126 */             if (dflag == MO_16) {                                                             // 0.0
/*6128 */                 tcg_gen_andi_tl(cpu_T0, cpu_T0, 0xffffff);                                    // 0.0
/*6130 */             }                                                                                 // 0.0
/*6132 */             tcg_gen_st_tl(cpu_T0, cpu_env, offsetof(CPUX86State, idt.base));                  // 0.0
/*6134 */             tcg_gen_st32_tl(cpu_T1, cpu_env, offsetof(CPUX86State, idt.limit));               // 0.0
/*6136 */             break;                                                                            // 0.0
/*6140 */         CASE_MODRM_OP(4): /* smsw */                                                          // 0.0
/*6142 */             gen_svm_check_intercept(s, pc_start, SVM_EXIT_READ_CR0);                          // 0.0
/*6144 */             tcg_gen_ld_tl(cpu_T0, cpu_env, offsetof(CPUX86State, cr[0]));                     // 0.0
/*6146 */             if (CODE64(s)) {                                                                  // 0.0
/*6148 */                 mod = (modrm >> 6) & 3;                                                       // 0.0
/*6150 */                 ot = (mod != 3 ? MO_16 : s->dflag);                                           // 0.0
/*6152 */             } else {                                                                          // 0.0
/*6154 */                 ot = MO_16;                                                                   // 0.0
/*6156 */             }                                                                                 // 0.0
/*6158 */             gen_ldst_modrm(env, s, modrm, ot, OR_TMP0, 1);                                    // 0.0
/*6160 */             break;                                                                            // 0.0
/*6162 */         case 0xee: /* rdpkru */                                                               // 0.0
/*6164 */             if (prefixes & PREFIX_LOCK) {                                                     // 0.0
/*6166 */                 goto illegal_op;                                                              // 0.0
/*6168 */             }                                                                                 // 0.0
/*6170 */             tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_regs[R_ECX]);                              // 0.0
/*6172 */             gen_helper_rdpkru(cpu_tmp1_i64, cpu_env, cpu_tmp2_i32);                           // 0.0
/*6174 */             tcg_gen_extr_i64_tl(cpu_regs[R_EAX], cpu_regs[R_EDX], cpu_tmp1_i64);              // 0.0
/*6176 */             break;                                                                            // 0.0
/*6178 */         case 0xef: /* wrpkru */                                                               // 0.0
/*6180 */             if (prefixes & PREFIX_LOCK) {                                                     // 0.0
/*6182 */                 goto illegal_op;                                                              // 0.0
/*6184 */             }                                                                                 // 0.0
/*6186 */             tcg_gen_concat_tl_i64(cpu_tmp1_i64, cpu_regs[R_EAX],                              // 0.0
/*6188 */                                   cpu_regs[R_EDX]);                                           // 0.0
/*6190 */             tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_regs[R_ECX]);                              // 0.0
/*6192 */             gen_helper_wrpkru(cpu_env, cpu_tmp2_i32, cpu_tmp1_i64);                           // 0.0
/*6194 */             break;                                                                            // 0.0
/*6196 */         CASE_MODRM_OP(6): /* lmsw */                                                          // 0.0
/*6198 */             if (s->cpl != 0) {                                                                // 0.0
/*6200 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*6202 */                 break;                                                                        // 0.0
/*6204 */             }                                                                                 // 0.0
/*6206 */             gen_svm_check_intercept(s, pc_start, SVM_EXIT_WRITE_CR0);                         // 0.0
/*6208 */             gen_ldst_modrm(env, s, modrm, MO_16, OR_TMP0, 0);                                 // 0.0
/*6210 */             gen_helper_lmsw(cpu_env, cpu_T0);                                                 // 0.0
/*6212 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*6214 */             gen_eob(s);                                                                       // 0.0
/*6216 */             break;                                                                            // 0.0
/*6220 */         CASE_MODRM_MEM_OP(7): /* invlpg */                                                    // 0.0
/*6222 */             if (s->cpl != 0) {                                                                // 0.0
/*6224 */                 gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                          // 0.0
/*6226 */                 break;                                                                        // 0.0
/*6228 */             }                                                                                 // 0.0
/*6230 */             gen_update_cc_op(s);                                                              // 0.0
/*6232 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*6234 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*6236 */             gen_helper_invlpg(cpu_env, cpu_A0);                                               // 0.0
/*6238 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*6240 */             gen_eob(s);                                                                       // 0.0
/*6242 */             break;                                                                            // 0.0
/*6246 */         case 0xf8: /* swapgs */                                                               // 0.0
/*6248 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*6250 */             if (CODE64(s)) {                                                                  // 0.0
/*6252 */                 if (s->cpl != 0) {                                                            // 0.0
/*6254 */                     gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                      // 0.0
/*6256 */                 } else {                                                                      // 0.0
/*6258 */                     tcg_gen_mov_tl(cpu_T0, cpu_seg_base[R_GS]);                               // 0.0
/*6260 */                     tcg_gen_ld_tl(cpu_seg_base[R_GS], cpu_env,                                // 0.0
/*6262 */                                   offsetof(CPUX86State, kernelgsbase));                       // 0.0
/*6264 */                     tcg_gen_st_tl(cpu_T0, cpu_env,                                            // 0.0
/*6266 */                                   offsetof(CPUX86State, kernelgsbase));                       // 0.0
/*6268 */                 }                                                                             // 0.0
/*6270 */                 break;                                                                        // 0.0
/*6272 */             }                                                                                 // 0.0
/*6274 */ #endif                                                                                        // 0.0
/*6276 */             goto illegal_op;                                                                  // 0.0
/*6280 */         case 0xf9: /* rdtscp */                                                               // 0.0
/*6282 */             if (!(s->cpuid_ext2_features & CPUID_EXT2_RDTSCP)) {                              // 0.0
/*6284 */                 goto illegal_op;                                                              // 0.0
/*6286 */             }                                                                                 // 0.0
/*6288 */             gen_update_cc_op(s);                                                              // 0.0
/*6290 */             gen_jmp_im(pc_start - s->cs_base);                                                // 0.0
/*6292 */             if (s->base.tb->cflags & CF_USE_ICOUNT) {                                         // 0.0
/*6294 */                 gen_io_start();                                                               // 0.0
/*6296 */             }                                                                                 // 0.0
/*6298 */             gen_helper_rdtscp(cpu_env);                                                       // 0.0
/*6300 */             if (s->base.tb->cflags & CF_USE_ICOUNT) {                                         // 0.0
/*6302 */                 gen_io_end();                                                                 // 0.0
/*6304 */                 gen_jmp(s, s->pc - s->cs_base);                                               // 0.0
/*6306 */             }                                                                                 // 0.0
/*6308 */             break;                                                                            // 0.0
/*6312 */         default:                                                                              // 0.0
/*6314 */             goto unknown_op;                                                                  // 0.0
/*6316 */         }                                                                                     // 0.0
/*6318 */         break;                                                                                // 0.0
/*6322 */     case 0x108: /* invd */                                                                    // 0.0
/*6324 */     case 0x109: /* wbinvd */                                                                  // 0.0
/*6326 */         if (s->cpl != 0) {                                                                    // 0.0
/*6328 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*6330 */         } else {                                                                              // 0.0
/*6332 */             gen_svm_check_intercept(s, pc_start, (b & 2) ? SVM_EXIT_INVD : SVM_EXIT_WBINVD);  // 0.0
/*6334 */             /* nothing to do */                                                               // 0.0
/*6336 */         }                                                                                     // 0.0
/*6338 */         break;                                                                                // 0.0
/*6340 */     case 0x63: /* arpl or movslS (x86_64) */                                                  // 0.0
/*6342 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*6344 */         if (CODE64(s)) {                                                                      // 0.0
/*6346 */             int d_ot;                                                                         // 0.0
/*6348 */             /* d_ot is the size of destination */                                             // 0.0
/*6350 */             d_ot = dflag;                                                                     // 0.0
/*6354 */             modrm = x86_ldub_code(env, s);                                                    // 0.0
/*6356 */             reg = ((modrm >> 3) & 7) | rex_r;                                                 // 0.0
/*6358 */             mod = (modrm >> 6) & 3;                                                           // 0.0
/*6360 */             rm = (modrm & 7) | REX_B(s);                                                      // 0.0
/*6364 */             if (mod == 3) {                                                                   // 0.0
/*6366 */                 gen_op_mov_v_reg(MO_32, cpu_T0, rm);                                          // 0.0
/*6368 */                 /* sign extend */                                                             // 0.0
/*6370 */                 if (d_ot == MO_64) {                                                          // 0.0
/*6372 */                     tcg_gen_ext32s_tl(cpu_T0, cpu_T0);                                        // 0.0
/*6374 */                 }                                                                             // 0.0
/*6376 */                 gen_op_mov_reg_v(d_ot, reg, cpu_T0);                                          // 0.0
/*6378 */             } else {                                                                          // 0.0
/*6380 */                 gen_lea_modrm(env, s, modrm);                                                 // 0.0
/*6382 */                 gen_op_ld_v(s, MO_32 | MO_SIGN, cpu_T0, cpu_A0);                              // 0.0
/*6384 */                 gen_op_mov_reg_v(d_ot, reg, cpu_T0);                                          // 0.0
/*6386 */             }                                                                                 // 0.0
/*6388 */         } else                                                                                // 0.0
/*6390 */ #endif                                                                                        // 0.0
/*6392 */         {                                                                                     // 0.0
/*6394 */             TCGLabel *label1;                                                                 // 0.0
/*6396 */             TCGv t0, t1, t2, a0;                                                              // 0.0
/*6400 */             if (!s->pe || s->vm86)                                                            // 0.0
/*6402 */                 goto illegal_op;                                                              // 0.0
/*6404 */             t0 = tcg_temp_local_new();                                                        // 0.0
/*6406 */             t1 = tcg_temp_local_new();                                                        // 0.0
/*6408 */             t2 = tcg_temp_local_new();                                                        // 0.0
/*6410 */             ot = MO_16;                                                                       // 0.0
/*6412 */             modrm = x86_ldub_code(env, s);                                                    // 0.0
/*6414 */             reg = (modrm >> 3) & 7;                                                           // 0.0
/*6416 */             mod = (modrm >> 6) & 3;                                                           // 0.0
/*6418 */             rm = modrm & 7;                                                                   // 0.0
/*6420 */             if (mod != 3) {                                                                   // 0.0
/*6422 */                 gen_lea_modrm(env, s, modrm);                                                 // 0.0
/*6424 */                 gen_op_ld_v(s, ot, t0, cpu_A0);                                               // 0.0
/*6426 */                 a0 = tcg_temp_local_new();                                                    // 0.0
/*6428 */                 tcg_gen_mov_tl(a0, cpu_A0);                                                   // 0.0
/*6430 */             } else {                                                                          // 0.0
/*6432 */                 gen_op_mov_v_reg(ot, t0, rm);                                                 // 0.0
/*6434 */                 TCGV_UNUSED(a0);                                                              // 0.0
/*6436 */             }                                                                                 // 0.0
/*6438 */             gen_op_mov_v_reg(ot, t1, reg);                                                    // 0.0
/*6440 */             tcg_gen_andi_tl(cpu_tmp0, t0, 3);                                                 // 0.0
/*6442 */             tcg_gen_andi_tl(t1, t1, 3);                                                       // 0.0
/*6444 */             tcg_gen_movi_tl(t2, 0);                                                           // 0.0
/*6446 */             label1 = gen_new_label();                                                         // 0.0
/*6448 */             tcg_gen_brcond_tl(TCG_COND_GE, cpu_tmp0, t1, label1);                             // 0.0
/*6450 */             tcg_gen_andi_tl(t0, t0, ~3);                                                      // 0.0
/*6452 */             tcg_gen_or_tl(t0, t0, t1);                                                        // 0.0
/*6454 */             tcg_gen_movi_tl(t2, CC_Z);                                                        // 0.0
/*6456 */             gen_set_label(label1);                                                            // 0.0
/*6458 */             if (mod != 3) {                                                                   // 0.0
/*6460 */                 gen_op_st_v(s, ot, t0, a0);                                                   // 0.0
/*6462 */                 tcg_temp_free(a0);                                                            // 0.0
/*6464 */            } else {                                                                           // 0.0
/*6466 */                 gen_op_mov_reg_v(ot, rm, t0);                                                 // 0.0
/*6468 */             }                                                                                 // 0.0
/*6470 */             gen_compute_eflags(s);                                                            // 0.0
/*6472 */             tcg_gen_andi_tl(cpu_cc_src, cpu_cc_src, ~CC_Z);                                   // 0.0
/*6474 */             tcg_gen_or_tl(cpu_cc_src, cpu_cc_src, t2);                                        // 0.0
/*6476 */             tcg_temp_free(t0);                                                                // 0.0
/*6478 */             tcg_temp_free(t1);                                                                // 0.0
/*6480 */             tcg_temp_free(t2);                                                                // 0.0
/*6482 */         }                                                                                     // 0.0
/*6484 */         break;                                                                                // 0.0
/*6486 */     case 0x102: /* lar */                                                                     // 0.0
/*6488 */     case 0x103: /* lsl */                                                                     // 0.0
/*6490 */         {                                                                                     // 0.0
/*6492 */             TCGLabel *label1;                                                                 // 0.0
/*6494 */             TCGv t0;                                                                          // 0.0
/*6496 */             if (!s->pe || s->vm86)                                                            // 0.0
/*6498 */                 goto illegal_op;                                                              // 0.0
/*6500 */             ot = dflag != MO_16 ? MO_32 : MO_16;                                              // 0.0
/*6502 */             modrm = x86_ldub_code(env, s);                                                    // 0.0
/*6504 */             reg = ((modrm >> 3) & 7) | rex_r;                                                 // 0.0
/*6506 */             gen_ldst_modrm(env, s, modrm, MO_16, OR_TMP0, 0);                                 // 0.0
/*6508 */             t0 = tcg_temp_local_new();                                                        // 0.0
/*6510 */             gen_update_cc_op(s);                                                              // 0.0
/*6512 */             if (b == 0x102) {                                                                 // 0.0
/*6514 */                 gen_helper_lar(t0, cpu_env, cpu_T0);                                          // 0.0
/*6516 */             } else {                                                                          // 0.0
/*6518 */                 gen_helper_lsl(t0, cpu_env, cpu_T0);                                          // 0.0
/*6520 */             }                                                                                 // 0.0
/*6522 */             tcg_gen_andi_tl(cpu_tmp0, cpu_cc_src, CC_Z);                                      // 0.0
/*6524 */             label1 = gen_new_label();                                                         // 0.0
/*6526 */             tcg_gen_brcondi_tl(TCG_COND_EQ, cpu_tmp0, 0, label1);                             // 0.0
/*6528 */             gen_op_mov_reg_v(ot, reg, t0);                                                    // 0.0
/*6530 */             gen_set_label(label1);                                                            // 0.0
/*6532 */             set_cc_op(s, CC_OP_EFLAGS);                                                       // 0.0
/*6534 */             tcg_temp_free(t0);                                                                // 0.0
/*6536 */         }                                                                                     // 0.0
/*6538 */         break;                                                                                // 0.0
/*6540 */     case 0x118:                                                                               // 0.0
/*6542 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*6544 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*6546 */         op = (modrm >> 3) & 7;                                                                // 0.0
/*6548 */         switch(op) {                                                                          // 0.0
/*6550 */         case 0: /* prefetchnta */                                                             // 0.0
/*6552 */         case 1: /* prefetchnt0 */                                                             // 0.0
/*6554 */         case 2: /* prefetchnt0 */                                                             // 0.0
/*6556 */         case 3: /* prefetchnt0 */                                                             // 0.0
/*6558 */             if (mod == 3)                                                                     // 0.0
/*6560 */                 goto illegal_op;                                                              // 0.0
/*6562 */             gen_nop_modrm(env, s, modrm);                                                     // 0.0
/*6564 */             /* nothing more to do */                                                          // 0.0
/*6566 */             break;                                                                            // 0.0
/*6568 */         default: /* nop (multi byte) */                                                       // 0.0
/*6570 */             gen_nop_modrm(env, s, modrm);                                                     // 0.0
/*6572 */             break;                                                                            // 0.0
/*6574 */         }                                                                                     // 0.0
/*6576 */         break;                                                                                // 0.0
/*6578 */     case 0x11a:                                                                               // 0.0
/*6580 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*6582 */         if (s->flags & HF_MPX_EN_MASK) {                                                      // 0.0
/*6584 */             mod = (modrm >> 6) & 3;                                                           // 0.0
/*6586 */             reg = ((modrm >> 3) & 7) | rex_r;                                                 // 0.0
/*6588 */             if (prefixes & PREFIX_REPZ) {                                                     // 0.0
/*6590 */                 /* bndcl */                                                                   // 0.0
/*6592 */                 if (reg >= 4                                                                  // 0.0
/*6594 */                     || (prefixes & PREFIX_LOCK)                                               // 0.0
/*6596 */                     || s->aflag == MO_16) {                                                   // 0.0
/*6598 */                     goto illegal_op;                                                          // 0.0
/*6600 */                 }                                                                             // 0.0
/*6602 */                 gen_bndck(env, s, modrm, TCG_COND_LTU, cpu_bndl[reg]);                        // 0.0
/*6604 */             } else if (prefixes & PREFIX_REPNZ) {                                             // 0.0
/*6606 */                 /* bndcu */                                                                   // 0.0
/*6608 */                 if (reg >= 4                                                                  // 0.0
/*6610 */                     || (prefixes & PREFIX_LOCK)                                               // 0.0
/*6612 */                     || s->aflag == MO_16) {                                                   // 0.0
/*6614 */                     goto illegal_op;                                                          // 0.0
/*6616 */                 }                                                                             // 0.0
/*6618 */                 TCGv_i64 notu = tcg_temp_new_i64();                                           // 0.0
/*6620 */                 tcg_gen_not_i64(notu, cpu_bndu[reg]);                                         // 0.0
/*6622 */                 gen_bndck(env, s, modrm, TCG_COND_GTU, notu);                                 // 0.0
/*6624 */                 tcg_temp_free_i64(notu);                                                      // 0.0
/*6626 */             } else if (prefixes & PREFIX_DATA) {                                              // 0.0
/*6628 */                 /* bndmov -- from reg/mem */                                                  // 0.0
/*6630 */                 if (reg >= 4 || s->aflag == MO_16) {                                          // 0.0
/*6632 */                     goto illegal_op;                                                          // 0.0
/*6634 */                 }                                                                             // 0.0
/*6636 */                 if (mod == 3) {                                                               // 0.0
/*6638 */                     int reg2 = (modrm & 7) | REX_B(s);                                        // 0.0
/*6640 */                     if (reg2 >= 4 || (prefixes & PREFIX_LOCK)) {                              // 0.0
/*6642 */                         goto illegal_op;                                                      // 0.0
/*6644 */                     }                                                                         // 0.0
/*6646 */                     if (s->flags & HF_MPX_IU_MASK) {                                          // 0.0
/*6648 */                         tcg_gen_mov_i64(cpu_bndl[reg], cpu_bndl[reg2]);                       // 0.0
/*6650 */                         tcg_gen_mov_i64(cpu_bndu[reg], cpu_bndu[reg2]);                       // 0.0
/*6652 */                     }                                                                         // 0.0
/*6654 */                 } else {                                                                      // 0.0
/*6656 */                     gen_lea_modrm(env, s, modrm);                                             // 0.0
/*6658 */                     if (CODE64(s)) {                                                          // 0.0
/*6660 */                         tcg_gen_qemu_ld_i64(cpu_bndl[reg], cpu_A0,                            // 0.0
/*6662 */                                             s->mem_index, MO_LEQ);                            // 0.0
/*6664 */                         tcg_gen_addi_tl(cpu_A0, cpu_A0, 8);                                   // 0.0
/*6666 */                         tcg_gen_qemu_ld_i64(cpu_bndu[reg], cpu_A0,                            // 0.0
/*6668 */                                             s->mem_index, MO_LEQ);                            // 0.0
/*6670 */                     } else {                                                                  // 0.0
/*6672 */                         tcg_gen_qemu_ld_i64(cpu_bndl[reg], cpu_A0,                            // 0.0
/*6674 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*6676 */                         tcg_gen_addi_tl(cpu_A0, cpu_A0, 4);                                   // 0.0
/*6678 */                         tcg_gen_qemu_ld_i64(cpu_bndu[reg], cpu_A0,                            // 0.0
/*6680 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*6682 */                     }                                                                         // 0.0
/*6684 */                     /* bnd registers are now in-use */                                        // 0.0
/*6686 */                     gen_set_hflag(s, HF_MPX_IU_MASK);                                         // 0.0
/*6688 */                 }                                                                             // 0.0
/*6690 */             } else if (mod != 3) {                                                            // 0.0
/*6692 */                 /* bndldx */                                                                  // 0.0
/*6694 */                 AddressParts a = gen_lea_modrm_0(env, s, modrm);                              // 0.0
/*6696 */                 if (reg >= 4                                                                  // 0.0
/*6698 */                     || (prefixes & PREFIX_LOCK)                                               // 0.0
/*6700 */                     || s->aflag == MO_16                                                      // 0.0
/*6702 */                     || a.base < -1) {                                                         // 0.0
/*6704 */                     goto illegal_op;                                                          // 0.0
/*6706 */                 }                                                                             // 0.0
/*6708 */                 if (a.base >= 0) {                                                            // 0.0
/*6710 */                     tcg_gen_addi_tl(cpu_A0, cpu_regs[a.base], a.disp);                        // 0.0
/*6712 */                 } else {                                                                      // 0.0
/*6714 */                     tcg_gen_movi_tl(cpu_A0, 0);                                               // 0.0
/*6716 */                 }                                                                             // 0.0
/*6718 */                 gen_lea_v_seg(s, s->aflag, cpu_A0, a.def_seg, s->override);                   // 0.0
/*6720 */                 if (a.index >= 0) {                                                           // 0.0
/*6722 */                     tcg_gen_mov_tl(cpu_T0, cpu_regs[a.index]);                                // 0.0
/*6724 */                 } else {                                                                      // 0.0
/*6726 */                     tcg_gen_movi_tl(cpu_T0, 0);                                               // 0.0
/*6728 */                 }                                                                             // 0.0
/*6730 */                 if (CODE64(s)) {                                                              // 0.0
/*6732 */                     gen_helper_bndldx64(cpu_bndl[reg], cpu_env, cpu_A0, cpu_T0);              // 0.0
/*6734 */                     tcg_gen_ld_i64(cpu_bndu[reg], cpu_env,                                    // 0.0
/*6736 */                                    offsetof(CPUX86State, mmx_t0.MMX_Q(0)));                   // 0.0
/*6738 */                 } else {                                                                      // 0.0
/*6740 */                     gen_helper_bndldx32(cpu_bndu[reg], cpu_env, cpu_A0, cpu_T0);              // 0.0
/*6742 */                     tcg_gen_ext32u_i64(cpu_bndl[reg], cpu_bndu[reg]);                         // 0.0
/*6744 */                     tcg_gen_shri_i64(cpu_bndu[reg], cpu_bndu[reg], 32);                       // 0.0
/*6746 */                 }                                                                             // 0.0
/*6748 */                 gen_set_hflag(s, HF_MPX_IU_MASK);                                             // 0.0
/*6750 */             }                                                                                 // 0.0
/*6752 */         }                                                                                     // 0.0
/*6754 */         gen_nop_modrm(env, s, modrm);                                                         // 0.0
/*6756 */         break;                                                                                // 0.0
/*6758 */     case 0x11b:                                                                               // 0.0
/*6760 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*6762 */         if (s->flags & HF_MPX_EN_MASK) {                                                      // 0.0
/*6764 */             mod = (modrm >> 6) & 3;                                                           // 0.0
/*6766 */             reg = ((modrm >> 3) & 7) | rex_r;                                                 // 0.0
/*6768 */             if (mod != 3 && (prefixes & PREFIX_REPZ)) {                                       // 0.0
/*6770 */                 /* bndmk */                                                                   // 0.0
/*6772 */                 if (reg >= 4                                                                  // 0.0
/*6774 */                     || (prefixes & PREFIX_LOCK)                                               // 0.0
/*6776 */                     || s->aflag == MO_16) {                                                   // 0.0
/*6778 */                     goto illegal_op;                                                          // 0.0
/*6780 */                 }                                                                             // 0.0
/*6782 */                 AddressParts a = gen_lea_modrm_0(env, s, modrm);                              // 0.0
/*6784 */                 if (a.base >= 0) {                                                            // 0.0
/*6786 */                     tcg_gen_extu_tl_i64(cpu_bndl[reg], cpu_regs[a.base]);                     // 0.0
/*6788 */                     if (!CODE64(s)) {                                                         // 0.0
/*6790 */                         tcg_gen_ext32u_i64(cpu_bndl[reg], cpu_bndl[reg]);                     // 0.0
/*6792 */                     }                                                                         // 0.0
/*6794 */                 } else if (a.base == -1) {                                                    // 0.0
/*6796 */                     /* no base register has lower bound of 0 */                               // 0.0
/*6798 */                     tcg_gen_movi_i64(cpu_bndl[reg], 0);                                       // 0.0
/*6800 */                 } else {                                                                      // 0.0
/*6802 */                     /* rip-relative generates #ud */                                          // 0.0
/*6804 */                     goto illegal_op;                                                          // 0.0
/*6806 */                 }                                                                             // 0.0
/*6808 */                 tcg_gen_not_tl(cpu_A0, gen_lea_modrm_1(a));                                   // 0.0
/*6810 */                 if (!CODE64(s)) {                                                             // 0.0
/*6812 */                     tcg_gen_ext32u_tl(cpu_A0, cpu_A0);                                        // 0.0
/*6814 */                 }                                                                             // 0.0
/*6816 */                 tcg_gen_extu_tl_i64(cpu_bndu[reg], cpu_A0);                                   // 0.0
/*6818 */                 /* bnd registers are now in-use */                                            // 0.0
/*6820 */                 gen_set_hflag(s, HF_MPX_IU_MASK);                                             // 0.0
/*6822 */                 break;                                                                        // 0.0
/*6824 */             } else if (prefixes & PREFIX_REPNZ) {                                             // 0.0
/*6826 */                 /* bndcn */                                                                   // 0.0
/*6828 */                 if (reg >= 4                                                                  // 0.0
/*6830 */                     || (prefixes & PREFIX_LOCK)                                               // 0.0
/*6832 */                     || s->aflag == MO_16) {                                                   // 0.0
/*6834 */                     goto illegal_op;                                                          // 0.0
/*6836 */                 }                                                                             // 0.0
/*6838 */                 gen_bndck(env, s, modrm, TCG_COND_GTU, cpu_bndu[reg]);                        // 0.0
/*6840 */             } else if (prefixes & PREFIX_DATA) {                                              // 0.0
/*6842 */                 /* bndmov -- to reg/mem */                                                    // 0.0
/*6844 */                 if (reg >= 4 || s->aflag == MO_16) {                                          // 0.0
/*6846 */                     goto illegal_op;                                                          // 0.0
/*6848 */                 }                                                                             // 0.0
/*6850 */                 if (mod == 3) {                                                               // 0.0
/*6852 */                     int reg2 = (modrm & 7) | REX_B(s);                                        // 0.0
/*6854 */                     if (reg2 >= 4 || (prefixes & PREFIX_LOCK)) {                              // 0.0
/*6856 */                         goto illegal_op;                                                      // 0.0
/*6858 */                     }                                                                         // 0.0
/*6860 */                     if (s->flags & HF_MPX_IU_MASK) {                                          // 0.0
/*6862 */                         tcg_gen_mov_i64(cpu_bndl[reg2], cpu_bndl[reg]);                       // 0.0
/*6864 */                         tcg_gen_mov_i64(cpu_bndu[reg2], cpu_bndu[reg]);                       // 0.0
/*6866 */                     }                                                                         // 0.0
/*6868 */                 } else {                                                                      // 0.0
/*6870 */                     gen_lea_modrm(env, s, modrm);                                             // 0.0
/*6872 */                     if (CODE64(s)) {                                                          // 0.0
/*6874 */                         tcg_gen_qemu_st_i64(cpu_bndl[reg], cpu_A0,                            // 0.0
/*6876 */                                             s->mem_index, MO_LEQ);                            // 0.0
/*6878 */                         tcg_gen_addi_tl(cpu_A0, cpu_A0, 8);                                   // 0.0
/*6880 */                         tcg_gen_qemu_st_i64(cpu_bndu[reg], cpu_A0,                            // 0.0
/*6882 */                                             s->mem_index, MO_LEQ);                            // 0.0
/*6884 */                     } else {                                                                  // 0.0
/*6886 */                         tcg_gen_qemu_st_i64(cpu_bndl[reg], cpu_A0,                            // 0.0
/*6888 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*6890 */                         tcg_gen_addi_tl(cpu_A0, cpu_A0, 4);                                   // 0.0
/*6892 */                         tcg_gen_qemu_st_i64(cpu_bndu[reg], cpu_A0,                            // 0.0
/*6894 */                                             s->mem_index, MO_LEUL);                           // 0.0
/*6896 */                     }                                                                         // 0.0
/*6898 */                 }                                                                             // 0.0
/*6900 */             } else if (mod != 3) {                                                            // 0.0
/*6902 */                 /* bndstx */                                                                  // 0.0
/*6904 */                 AddressParts a = gen_lea_modrm_0(env, s, modrm);                              // 0.0
/*6906 */                 if (reg >= 4                                                                  // 0.0
/*6908 */                     || (prefixes & PREFIX_LOCK)                                               // 0.0
/*6910 */                     || s->aflag == MO_16                                                      // 0.0
/*6912 */                     || a.base < -1) {                                                         // 0.0
/*6914 */                     goto illegal_op;                                                          // 0.0
/*6916 */                 }                                                                             // 0.0
/*6918 */                 if (a.base >= 0) {                                                            // 0.0
/*6920 */                     tcg_gen_addi_tl(cpu_A0, cpu_regs[a.base], a.disp);                        // 0.0
/*6922 */                 } else {                                                                      // 0.0
/*6924 */                     tcg_gen_movi_tl(cpu_A0, 0);                                               // 0.0
/*6926 */                 }                                                                             // 0.0
/*6928 */                 gen_lea_v_seg(s, s->aflag, cpu_A0, a.def_seg, s->override);                   // 0.0
/*6930 */                 if (a.index >= 0) {                                                           // 0.0
/*6932 */                     tcg_gen_mov_tl(cpu_T0, cpu_regs[a.index]);                                // 0.0
/*6934 */                 } else {                                                                      // 0.0
/*6936 */                     tcg_gen_movi_tl(cpu_T0, 0);                                               // 0.0
/*6938 */                 }                                                                             // 0.0
/*6940 */                 if (CODE64(s)) {                                                              // 0.0
/*6942 */                     gen_helper_bndstx64(cpu_env, cpu_A0, cpu_T0,                              // 0.0
/*6944 */                                         cpu_bndl[reg], cpu_bndu[reg]);                        // 0.0
/*6946 */                 } else {                                                                      // 0.0
/*6948 */                     gen_helper_bndstx32(cpu_env, cpu_A0, cpu_T0,                              // 0.0
/*6950 */                                         cpu_bndl[reg], cpu_bndu[reg]);                        // 0.0
/*6952 */                 }                                                                             // 0.0
/*6954 */             }                                                                                 // 0.0
/*6956 */         }                                                                                     // 0.0
/*6958 */         gen_nop_modrm(env, s, modrm);                                                         // 0.0
/*6960 */         break;                                                                                // 0.0
/*6962 */     case 0x119: case 0x11c ... 0x11f: /* nop (multi byte) */                                  // 0.0
/*6964 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*6966 */         gen_nop_modrm(env, s, modrm);                                                         // 0.0
/*6968 */         break;                                                                                // 0.0
/*6970 */     case 0x120: /* mov reg, crN */                                                            // 0.0
/*6972 */     case 0x122: /* mov crN, reg */                                                            // 0.0
/*6974 */         if (s->cpl != 0) {                                                                    // 0.0
/*6976 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*6978 */         } else {                                                                              // 0.0
/*6980 */             modrm = x86_ldub_code(env, s);                                                    // 0.0
/*6982 */             /* Ignore the mod bits (assume (modrm&0xc0)==0xc0).                               // 0.0
/*6984 */              * AMD documentation (24594.pdf) and testing of                                   // 0.0
/*6986 */              * intel 386 and 486 processors all show that the mod bits                        // 0.0
/*6988 */              * are assumed to be 1's, regardless of actual values.                            // 0.0
/*6990 */              */                                                                               // 0.0
/*6992 */             rm = (modrm & 7) | REX_B(s);                                                      // 0.0
/*6994 */             reg = ((modrm >> 3) & 7) | rex_r;                                                 // 0.0
/*6996 */             if (CODE64(s))                                                                    // 0.0
/*6998 */                 ot = MO_64;                                                                   // 0.0
/*7000 */             else                                                                              // 0.0
/*7002 */                 ot = MO_32;                                                                   // 0.0
/*7004 */             if ((prefixes & PREFIX_LOCK) && (reg == 0) &&                                     // 0.0
/*7006 */                 (s->cpuid_ext3_features & CPUID_EXT3_CR8LEG)) {                               // 0.0
/*7008 */                 reg = 8;                                                                      // 0.0
/*7010 */             }                                                                                 // 0.0
/*7012 */             switch(reg) {                                                                     // 0.0
/*7014 */             case 0:                                                                           // 0.0
/*7016 */             case 2:                                                                           // 0.0
/*7018 */             case 3:                                                                           // 0.0
/*7020 */             case 4:                                                                           // 0.0
/*7022 */             case 8:                                                                           // 0.0
/*7024 */                 gen_update_cc_op(s);                                                          // 0.0
/*7026 */                 gen_jmp_im(pc_start - s->cs_base);                                            // 0.0
/*7028 */                 if (b & 2) {                                                                  // 0.0
/*7030 */                     if (s->base.tb->cflags & CF_USE_ICOUNT) {                                 // 0.0
/*7032 */                         gen_io_start();                                                       // 0.0
/*7034 */                     }                                                                         // 0.0
/*7036 */                     gen_op_mov_v_reg(ot, cpu_T0, rm);                                         // 0.0
/*7038 */                     gen_helper_write_crN(cpu_env, tcg_const_i32(reg),                         // 0.0
/*7040 */                                          cpu_T0);                                             // 0.0
/*7042 */                     if (s->base.tb->cflags & CF_USE_ICOUNT) {                                 // 0.0
/*7044 */                         gen_io_end();                                                         // 0.0
/*7046 */                     }                                                                         // 0.0
/*7048 */                     gen_jmp_im(s->pc - s->cs_base);                                           // 0.0
/*7050 */                     gen_eob(s);                                                               // 0.0
/*7052 */                 } else {                                                                      // 0.0
/*7054 */                     if (s->base.tb->cflags & CF_USE_ICOUNT) {                                 // 0.0
/*7056 */                         gen_io_start();                                                       // 0.0
/*7058 */                     }                                                                         // 0.0
/*7060 */                     gen_helper_read_crN(cpu_T0, cpu_env, tcg_const_i32(reg));                 // 0.0
/*7062 */                     gen_op_mov_reg_v(ot, rm, cpu_T0);                                         // 0.0
/*7064 */                     if (s->base.tb->cflags & CF_USE_ICOUNT) {                                 // 0.0
/*7066 */                         gen_io_end();                                                         // 0.0
/*7068 */                     }                                                                         // 0.0
/*7070 */                 }                                                                             // 0.0
/*7072 */                 break;                                                                        // 0.0
/*7074 */             default:                                                                          // 0.0
/*7076 */                 goto unknown_op;                                                              // 0.0
/*7078 */             }                                                                                 // 0.0
/*7080 */         }                                                                                     // 0.0
/*7082 */         break;                                                                                // 0.0
/*7084 */     case 0x121: /* mov reg, drN */                                                            // 0.0
/*7086 */     case 0x123: /* mov drN, reg */                                                            // 0.0
/*7088 */         if (s->cpl != 0) {                                                                    // 0.0
/*7090 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*7092 */         } else {                                                                              // 0.0
/*7094 */             modrm = x86_ldub_code(env, s);                                                    // 0.0
/*7096 */             /* Ignore the mod bits (assume (modrm&0xc0)==0xc0).                               // 0.0
/*7098 */              * AMD documentation (24594.pdf) and testing of                                   // 0.0
/*7100 */              * intel 386 and 486 processors all show that the mod bits                        // 0.0
/*7102 */              * are assumed to be 1's, regardless of actual values.                            // 0.0
/*7104 */              */                                                                               // 0.0
/*7106 */             rm = (modrm & 7) | REX_B(s);                                                      // 0.0
/*7108 */             reg = ((modrm >> 3) & 7) | rex_r;                                                 // 0.0
/*7110 */             if (CODE64(s))                                                                    // 0.0
/*7112 */                 ot = MO_64;                                                                   // 0.0
/*7114 */             else                                                                              // 0.0
/*7116 */                 ot = MO_32;                                                                   // 0.0
/*7118 */             if (reg >= 8) {                                                                   // 0.0
/*7120 */                 goto illegal_op;                                                              // 0.0
/*7122 */             }                                                                                 // 0.0
/*7124 */             if (b & 2) {                                                                      // 0.0
/*7126 */                 gen_svm_check_intercept(s, pc_start, SVM_EXIT_WRITE_DR0 + reg);               // 0.0
/*7128 */                 gen_op_mov_v_reg(ot, cpu_T0, rm);                                             // 0.0
/*7130 */                 tcg_gen_movi_i32(cpu_tmp2_i32, reg);                                          // 0.0
/*7132 */                 gen_helper_set_dr(cpu_env, cpu_tmp2_i32, cpu_T0);                             // 0.0
/*7134 */                 gen_jmp_im(s->pc - s->cs_base);                                               // 0.0
/*7136 */                 gen_eob(s);                                                                   // 0.0
/*7138 */             } else {                                                                          // 0.0
/*7140 */                 gen_svm_check_intercept(s, pc_start, SVM_EXIT_READ_DR0 + reg);                // 0.0
/*7142 */                 tcg_gen_movi_i32(cpu_tmp2_i32, reg);                                          // 0.0
/*7144 */                 gen_helper_get_dr(cpu_T0, cpu_env, cpu_tmp2_i32);                             // 0.0
/*7146 */                 gen_op_mov_reg_v(ot, rm, cpu_T0);                                             // 0.0
/*7148 */             }                                                                                 // 0.0
/*7150 */         }                                                                                     // 0.0
/*7152 */         break;                                                                                // 0.0
/*7154 */     case 0x106: /* clts */                                                                    // 0.0
/*7156 */         if (s->cpl != 0) {                                                                    // 0.0
/*7158 */             gen_exception(s, EXCP0D_GPF, pc_start - s->cs_base);                              // 0.0
/*7160 */         } else {                                                                              // 0.0
/*7162 */             gen_svm_check_intercept(s, pc_start, SVM_EXIT_WRITE_CR0);                         // 0.0
/*7164 */             gen_helper_clts(cpu_env);                                                         // 0.0
/*7166 */             /* abort block because static cpu state changed */                                // 0.0
/*7168 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*7170 */             gen_eob(s);                                                                       // 0.0
/*7172 */         }                                                                                     // 0.0
/*7174 */         break;                                                                                // 0.0
/*7176 */     /* MMX/3DNow!/SSE/SSE2/SSE3/SSSE3/SSE4 support */                                         // 0.0
/*7178 */     case 0x1c3: /* MOVNTI reg, mem */                                                         // 0.0
/*7180 */         if (!(s->cpuid_features & CPUID_SSE2))                                                // 0.0
/*7182 */             goto illegal_op;                                                                  // 0.0
/*7184 */         ot = mo_64_32(dflag);                                                                 // 0.0
/*7186 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*7188 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*7190 */         if (mod == 3)                                                                         // 0.0
/*7192 */             goto illegal_op;                                                                  // 0.0
/*7194 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*7196 */         /* generate a generic store */                                                        // 0.0
/*7198 */         gen_ldst_modrm(env, s, modrm, ot, reg, 1);                                            // 0.0
/*7200 */         break;                                                                                // 0.0
/*7202 */     case 0x1ae:                                                                               // 0.0
/*7204 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*7206 */         switch (modrm) {                                                                      // 0.0
/*7208 */         CASE_MODRM_MEM_OP(0): /* fxsave */                                                    // 0.0
/*7210 */             if (!(s->cpuid_features & CPUID_FXSR)                                             // 0.0
/*7212 */                 || (prefixes & PREFIX_LOCK)) {                                                // 0.0
/*7214 */                 goto illegal_op;                                                              // 0.0
/*7216 */             }                                                                                 // 0.0
/*7218 */             if ((s->flags & HF_EM_MASK) || (s->flags & HF_TS_MASK)) {                         // 0.0
/*7220 */                 gen_exception(s, EXCP07_PREX, pc_start - s->cs_base);                         // 0.0
/*7222 */                 break;                                                                        // 0.0
/*7224 */             }                                                                                 // 0.0
/*7226 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*7228 */             gen_helper_fxsave(cpu_env, cpu_A0);                                               // 0.0
/*7230 */             break;                                                                            // 0.0
/*7234 */         CASE_MODRM_MEM_OP(1): /* fxrstor */                                                   // 0.0
/*7236 */             if (!(s->cpuid_features & CPUID_FXSR)                                             // 0.0
/*7238 */                 || (prefixes & PREFIX_LOCK)) {                                                // 0.0
/*7240 */                 goto illegal_op;                                                              // 0.0
/*7242 */             }                                                                                 // 0.0
/*7244 */             if ((s->flags & HF_EM_MASK) || (s->flags & HF_TS_MASK)) {                         // 0.0
/*7246 */                 gen_exception(s, EXCP07_PREX, pc_start - s->cs_base);                         // 0.0
/*7248 */                 break;                                                                        // 0.0
/*7250 */             }                                                                                 // 0.0
/*7252 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*7254 */             gen_helper_fxrstor(cpu_env, cpu_A0);                                              // 0.0
/*7256 */             break;                                                                            // 0.0
/*7260 */         CASE_MODRM_MEM_OP(2): /* ldmxcsr */                                                   // 0.0
/*7262 */             if ((s->flags & HF_EM_MASK) || !(s->flags & HF_OSFXSR_MASK)) {                    // 0.0
/*7264 */                 goto illegal_op;                                                              // 0.0
/*7266 */             }                                                                                 // 0.0
/*7268 */             if (s->flags & HF_TS_MASK) {                                                      // 0.0
/*7270 */                 gen_exception(s, EXCP07_PREX, pc_start - s->cs_base);                         // 0.0
/*7272 */                 break;                                                                        // 0.0
/*7274 */             }                                                                                 // 0.0
/*7276 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*7278 */             tcg_gen_qemu_ld_i32(cpu_tmp2_i32, cpu_A0, s->mem_index, MO_LEUL);                 // 0.0
/*7280 */             gen_helper_ldmxcsr(cpu_env, cpu_tmp2_i32);                                        // 0.0
/*7282 */             break;                                                                            // 0.0
/*7286 */         CASE_MODRM_MEM_OP(3): /* stmxcsr */                                                   // 0.0
/*7288 */             if ((s->flags & HF_EM_MASK) || !(s->flags & HF_OSFXSR_MASK)) {                    // 0.0
/*7290 */                 goto illegal_op;                                                              // 0.0
/*7292 */             }                                                                                 // 0.0
/*7294 */             if (s->flags & HF_TS_MASK) {                                                      // 0.0
/*7296 */                 gen_exception(s, EXCP07_PREX, pc_start - s->cs_base);                         // 0.0
/*7298 */                 break;                                                                        // 0.0
/*7300 */             }                                                                                 // 0.0
/*7302 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*7304 */             tcg_gen_ld32u_tl(cpu_T0, cpu_env, offsetof(CPUX86State, mxcsr));                  // 0.0
/*7306 */             gen_op_st_v(s, MO_32, cpu_T0, cpu_A0);                                            // 0.0
/*7308 */             break;                                                                            // 0.0
/*7312 */         CASE_MODRM_MEM_OP(4): /* xsave */                                                     // 0.0
/*7314 */             if ((s->cpuid_ext_features & CPUID_EXT_XSAVE) == 0                                // 0.0
/*7316 */                 || (prefixes & (PREFIX_LOCK | PREFIX_DATA                                     // 0.0
/*7318 */                                 | PREFIX_REPZ | PREFIX_REPNZ))) {                             // 0.0
/*7320 */                 goto illegal_op;                                                              // 0.0
/*7322 */             }                                                                                 // 0.0
/*7324 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*7326 */             tcg_gen_concat_tl_i64(cpu_tmp1_i64, cpu_regs[R_EAX],                              // 0.0
/*7328 */                                   cpu_regs[R_EDX]);                                           // 0.0
/*7330 */             gen_helper_xsave(cpu_env, cpu_A0, cpu_tmp1_i64);                                  // 0.0
/*7332 */             break;                                                                            // 0.0
/*7336 */         CASE_MODRM_MEM_OP(5): /* xrstor */                                                    // 0.0
/*7338 */             if ((s->cpuid_ext_features & CPUID_EXT_XSAVE) == 0                                // 0.0
/*7340 */                 || (prefixes & (PREFIX_LOCK | PREFIX_DATA                                     // 0.0
/*7342 */                                 | PREFIX_REPZ | PREFIX_REPNZ))) {                             // 0.0
/*7344 */                 goto illegal_op;                                                              // 0.0
/*7346 */             }                                                                                 // 0.0
/*7348 */             gen_lea_modrm(env, s, modrm);                                                     // 0.0
/*7350 */             tcg_gen_concat_tl_i64(cpu_tmp1_i64, cpu_regs[R_EAX],                              // 0.0
/*7352 */                                   cpu_regs[R_EDX]);                                           // 0.0
/*7354 */             gen_helper_xrstor(cpu_env, cpu_A0, cpu_tmp1_i64);                                 // 0.0
/*7356 */             /* XRSTOR is how MPX is enabled, which changes how                                // 0.0
/*7358 */                we translate.  Thus we need to end the TB.  */                                 // 0.0
/*7360 */             gen_update_cc_op(s);                                                              // 0.0
/*7362 */             gen_jmp_im(s->pc - s->cs_base);                                                   // 0.0
/*7364 */             gen_eob(s);                                                                       // 0.0
/*7366 */             break;                                                                            // 0.0
/*7370 */         CASE_MODRM_MEM_OP(6): /* xsaveopt / clwb */                                           // 0.0
/*7372 */             if (prefixes & PREFIX_LOCK) {                                                     // 0.0
/*7374 */                 goto illegal_op;                                                              // 0.0
/*7376 */             }                                                                                 // 0.0
/*7378 */             if (prefixes & PREFIX_DATA) {                                                     // 0.0
/*7380 */                 /* clwb */                                                                    // 0.0
/*7382 */                 if (!(s->cpuid_7_0_ebx_features & CPUID_7_0_EBX_CLWB)) {                      // 0.0
/*7384 */                     goto illegal_op;                                                          // 0.0
/*7386 */                 }                                                                             // 0.0
/*7388 */                 gen_nop_modrm(env, s, modrm);                                                 // 0.0
/*7390 */             } else {                                                                          // 0.0
/*7392 */                 /* xsaveopt */                                                                // 0.0
/*7394 */                 if ((s->cpuid_ext_features & CPUID_EXT_XSAVE) == 0                            // 0.0
/*7396 */                     || (s->cpuid_xsave_features & CPUID_XSAVE_XSAVEOPT) == 0                  // 0.0
/*7398 */                     || (prefixes & (PREFIX_REPZ | PREFIX_REPNZ))) {                           // 0.0
/*7400 */                     goto illegal_op;                                                          // 0.0
/*7402 */                 }                                                                             // 0.0
/*7404 */                 gen_lea_modrm(env, s, modrm);                                                 // 0.0
/*7406 */                 tcg_gen_concat_tl_i64(cpu_tmp1_i64, cpu_regs[R_EAX],                          // 0.0
/*7408 */                                       cpu_regs[R_EDX]);                                       // 0.0
/*7410 */                 gen_helper_xsaveopt(cpu_env, cpu_A0, cpu_tmp1_i64);                           // 0.0
/*7412 */             }                                                                                 // 0.0
/*7414 */             break;                                                                            // 0.0
/*7418 */         CASE_MODRM_MEM_OP(7): /* clflush / clflushopt */                                      // 0.0
/*7420 */             if (prefixes & PREFIX_LOCK) {                                                     // 0.0
/*7422 */                 goto illegal_op;                                                              // 0.0
/*7424 */             }                                                                                 // 0.0
/*7426 */             if (prefixes & PREFIX_DATA) {                                                     // 0.0
/*7428 */                 /* clflushopt */                                                              // 0.0
/*7430 */                 if (!(s->cpuid_7_0_ebx_features & CPUID_7_0_EBX_CLFLUSHOPT)) {                // 0.0
/*7432 */                     goto illegal_op;                                                          // 0.0
/*7434 */                 }                                                                             // 0.0
/*7436 */             } else {                                                                          // 0.0
/*7438 */                 /* clflush */                                                                 // 0.0
/*7440 */                 if ((s->prefix & (PREFIX_REPZ | PREFIX_REPNZ))                                // 0.0
/*7442 */                     || !(s->cpuid_features & CPUID_CLFLUSH)) {                                // 0.0
/*7444 */                     goto illegal_op;                                                          // 0.0
/*7446 */                 }                                                                             // 0.0
/*7448 */             }                                                                                 // 0.0
/*7450 */             gen_nop_modrm(env, s, modrm);                                                     // 0.0
/*7452 */             break;                                                                            // 0.0
/*7456 */         case 0xc0 ... 0xc7: /* rdfsbase (f3 0f ae /0) */                                      // 0.0
/*7458 */         case 0xc8 ... 0xcf: /* rdgsbase (f3 0f ae /1) */                                      // 0.0
/*7460 */         case 0xd0 ... 0xd7: /* wrfsbase (f3 0f ae /2) */                                      // 0.0
/*7462 */         case 0xd8 ... 0xdf: /* wrgsbase (f3 0f ae /3) */                                      // 0.0
/*7464 */             if (CODE64(s)                                                                     // 0.0
/*7466 */                 && (prefixes & PREFIX_REPZ)                                                   // 0.0
/*7468 */                 && !(prefixes & PREFIX_LOCK)                                                  // 0.0
/*7470 */                 && (s->cpuid_7_0_ebx_features & CPUID_7_0_EBX_FSGSBASE)) {                    // 0.0
/*7472 */                 TCGv base, treg, src, dst;                                                    // 0.0
/*7476 */                 /* Preserve hflags bits by testing CR4 at runtime.  */                        // 0.0
/*7478 */                 tcg_gen_movi_i32(cpu_tmp2_i32, CR4_FSGSBASE_MASK);                            // 0.0
/*7480 */                 gen_helper_cr4_testbit(cpu_env, cpu_tmp2_i32);                                // 0.0
/*7484 */                 base = cpu_seg_base[modrm & 8 ? R_GS : R_FS];                                 // 0.0
/*7486 */                 treg = cpu_regs[(modrm & 7) | REX_B(s)];                                      // 0.0
/*7490 */                 if (modrm & 0x10) {                                                           // 0.0
/*7492 */                     /* wr*base */                                                             // 0.0
/*7494 */                     dst = base, src = treg;                                                   // 0.0
/*7496 */                 } else {                                                                      // 0.0
/*7498 */                     /* rd*base */                                                             // 0.0
/*7500 */                     dst = treg, src = base;                                                   // 0.0
/*7502 */                 }                                                                             // 0.0
/*7506 */                 if (s->dflag == MO_32) {                                                      // 0.0
/*7508 */                     tcg_gen_ext32u_tl(dst, src);                                              // 0.0
/*7510 */                 } else {                                                                      // 0.0
/*7512 */                     tcg_gen_mov_tl(dst, src);                                                 // 0.0
/*7514 */                 }                                                                             // 0.0
/*7516 */                 break;                                                                        // 0.0
/*7518 */             }                                                                                 // 0.0
/*7520 */             goto unknown_op;                                                                  // 0.0
/*7524 */         case 0xf8: /* sfence / pcommit */                                                     // 0.0
/*7526 */             if (prefixes & PREFIX_DATA) {                                                     // 0.0
/*7528 */                 /* pcommit */                                                                 // 0.0
/*7530 */                 if (!(s->cpuid_7_0_ebx_features & CPUID_7_0_EBX_PCOMMIT)                      // 0.0
/*7532 */                     || (prefixes & PREFIX_LOCK)) {                                            // 0.0
/*7534 */                     goto illegal_op;                                                          // 0.0
/*7536 */                 }                                                                             // 0.0
/*7538 */                 break;                                                                        // 0.0
/*7540 */             }                                                                                 // 0.0
/*7542 */             /* fallthru */                                                                    // 0.0
/*7544 */         case 0xf9 ... 0xff: /* sfence */                                                      // 0.0
/*7546 */             if (!(s->cpuid_features & CPUID_SSE)                                              // 0.0
/*7548 */                 || (prefixes & PREFIX_LOCK)) {                                                // 0.0
/*7550 */                 goto illegal_op;                                                              // 0.0
/*7552 */             }                                                                                 // 0.0
/*7554 */             tcg_gen_mb(TCG_MO_ST_ST | TCG_BAR_SC);                                            // 0.0
/*7556 */             break;                                                                            // 0.0
/*7558 */         case 0xe8 ... 0xef: /* lfence */                                                      // 0.0
/*7560 */             if (!(s->cpuid_features & CPUID_SSE)                                              // 0.0
/*7562 */                 || (prefixes & PREFIX_LOCK)) {                                                // 0.0
/*7564 */                 goto illegal_op;                                                              // 0.0
/*7566 */             }                                                                                 // 0.0
/*7568 */             tcg_gen_mb(TCG_MO_LD_LD | TCG_BAR_SC);                                            // 0.0
/*7570 */             break;                                                                            // 0.0
/*7572 */         case 0xf0 ... 0xf7: /* mfence */                                                      // 0.0
/*7574 */             if (!(s->cpuid_features & CPUID_SSE2)                                             // 0.0
/*7576 */                 || (prefixes & PREFIX_LOCK)) {                                                // 0.0
/*7578 */                 goto illegal_op;                                                              // 0.0
/*7580 */             }                                                                                 // 0.0
/*7582 */             tcg_gen_mb(TCG_MO_ALL | TCG_BAR_SC);                                              // 0.0
/*7584 */             break;                                                                            // 0.0
/*7588 */         default:                                                                              // 0.0
/*7590 */             goto unknown_op;                                                                  // 0.0
/*7592 */         }                                                                                     // 0.0
/*7594 */         break;                                                                                // 0.0
/*7598 */     case 0x10d: /* 3DNow! prefetch(w) */                                                      // 0.0
/*7600 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*7602 */         mod = (modrm >> 6) & 3;                                                               // 0.0
/*7604 */         if (mod == 3)                                                                         // 0.0
/*7606 */             goto illegal_op;                                                                  // 0.0
/*7608 */         gen_nop_modrm(env, s, modrm);                                                         // 0.0
/*7610 */         break;                                                                                // 0.0
/*7612 */     case 0x1aa: /* rsm */                                                                     // 0.0
/*7614 */         gen_svm_check_intercept(s, pc_start, SVM_EXIT_RSM);                                   // 0.0
/*7616 */         if (!(s->flags & HF_SMM_MASK))                                                        // 0.0
/*7618 */             goto illegal_op;                                                                  // 0.0
/*7620 */         gen_update_cc_op(s);                                                                  // 0.0
/*7622 */         gen_jmp_im(s->pc - s->cs_base);                                                       // 0.0
/*7624 */         gen_helper_rsm(cpu_env);                                                              // 0.0
/*7626 */         gen_eob(s);                                                                           // 0.0
/*7628 */         break;                                                                                // 0.0
/*7630 */     case 0x1b8: /* SSE4.2 popcnt */                                                           // 0.0
/*7632 */         if ((prefixes & (PREFIX_REPZ | PREFIX_LOCK | PREFIX_REPNZ)) !=                        // 0.0
/*7634 */              PREFIX_REPZ)                                                                     // 0.0
/*7636 */             goto illegal_op;                                                                  // 0.0
/*7638 */         if (!(s->cpuid_ext_features & CPUID_EXT_POPCNT))                                      // 0.0
/*7640 */             goto illegal_op;                                                                  // 0.0
/*7644 */         modrm = x86_ldub_code(env, s);                                                        // 0.0
/*7646 */         reg = ((modrm >> 3) & 7) | rex_r;                                                     // 0.0
/*7650 */         if (s->prefix & PREFIX_DATA) {                                                        // 0.0
/*7652 */             ot = MO_16;                                                                       // 0.0
/*7654 */         } else {                                                                              // 0.0
/*7656 */             ot = mo_64_32(dflag);                                                             // 0.0
/*7658 */         }                                                                                     // 0.0
/*7662 */         gen_ldst_modrm(env, s, modrm, ot, OR_TMP0, 0);                                        // 0.0
/*7664 */         gen_extu(ot, cpu_T0);                                                                 // 0.0
/*7666 */         tcg_gen_mov_tl(cpu_cc_src, cpu_T0);                                                   // 0.0
/*7668 */         tcg_gen_ctpop_tl(cpu_T0, cpu_T0);                                                     // 0.0
/*7670 */         gen_op_mov_reg_v(ot, reg, cpu_T0);                                                    // 0.0
/*7674 */         set_cc_op(s, CC_OP_POPCNT);                                                           // 0.0
/*7676 */         break;                                                                                // 0.0
/*7678 */     case 0x10e ... 0x10f:                                                                     // 0.0
/*7680 */         /* 3DNow! instructions, ignore prefixes */                                            // 0.0
/*7682 */         s->prefix &= ~(PREFIX_REPZ | PREFIX_REPNZ | PREFIX_DATA);                             // 0.0
/*7684 */     case 0x110 ... 0x117:                                                                     // 0.0
/*7686 */     case 0x128 ... 0x12f:                                                                     // 0.0
/*7688 */     case 0x138 ... 0x13a:                                                                     // 0.0
/*7690 */     case 0x150 ... 0x179:                                                                     // 0.0
/*7692 */     case 0x17c ... 0x17f:                                                                     // 0.0
/*7694 */     case 0x1c2:                                                                               // 0.0
/*7696 */     case 0x1c4 ... 0x1c6:                                                                     // 0.0
/*7698 */     case 0x1d0 ... 0x1fe:                                                                     // 0.0
/*7700 */         gen_sse(env, s, b, pc_start, rex_r);                                                  // 0.0
/*7702 */         break;                                                                                // 0.0
/*7704 */     default:                                                                                  // 0.0
/*7706 */         goto unknown_op;                                                                      // 0.0
/*7708 */     }                                                                                         // 0.0
/*7710 */     return s->pc;                                                                             // 0.0
/*7712 */  illegal_op:                                                                                  // 0.0
/*7714 */     gen_illegal_opcode(s);                                                                    // 0.0
/*7716 */     return s->pc;                                                                             // 0.0
/*7718 */  unknown_op:                                                                                  // 0.0
/*7720 */     gen_unknown_opcode(env, s);                                                               // 0.0
/*7722 */     return s->pc;                                                                             // 0.0
/*7724 */ }                                                                                             // 0.0
