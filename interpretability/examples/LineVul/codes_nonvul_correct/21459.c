// commit message qemu@58aebb946a (target=0, prob=0.31718338, correct=True): cris: Fix TLB exec bit protection
/*0   */ static int cris_mmu_translate_page(struct cris_mmu_result *res,           // (4) 0.04297
/*2   */ 				   CPUState *env, uint32_t vaddr,                                     // (9) 0.03516
/*4   */ 				   int rw, int usermode, int debug)                                   // (12) 0.0332
/*6   */ {                                                                         // (32) 0.001954
/*8   */ 	unsigned int vpage;                                                      // (25) 0.01172
/*10  */ 	unsigned int idx;                                                        // (28) 0.01172
/*12  */ 	uint32_t pid, lo, hi;                                                    // (19) 0.02148
/*14  */ 	uint32_t tlb_vpn, tlb_pfn = 0;                                           // (8) 0.03711
/*16  */ 	int tlb_pid, tlb_g, tlb_v, tlb_k, tlb_w, tlb_x;                          // (0) 0.0625
/*18  */ 	int cfg_v, cfg_k, cfg_w, cfg_x;	                                         // (2) 0.04492
/*20  */ 	int set, match = 0;                                                      // (23) 0.01563
/*22  */ 	uint32_t r_cause;                                                        // (21) 0.01758
/*24  */ 	uint32_t r_cfg;                                                          // (22) 0.01758
/*26  */ 	int rwcause;                                                             // (27) 0.01172
/*28  */ 	int mmu = 1; /* Data mmu is default.  */                                 // (13) 0.03125
/*30  */ 	int vect_base;                                                           // (24) 0.01368
/*34  */ 	r_cause = env->sregs[SFR_R_MM_CAUSE];                                    // (6) 0.04102
/*36  */ 	r_cfg = env->sregs[SFR_RW_MM_CFG];                                       // (7) 0.04101
/*38  */ 	pid = env->pregs[PR_PID] & 0xff;                                         // (10) 0.03516
/*42  */ 	switch (rw) {                                                            // (26) 0.01172
/*44  */ 		case 2: rwcause = CRIS_MMU_ERR_EXEC; mmu = 0; break;                    // (1) 0.05469
/*46  */ 		case 1: rwcause = CRIS_MMU_ERR_WRITE; break;                            // (3) 0.04492
/*48  */ 		default:                                                                // (29) 0.007812
/*50  */ 		case 0: rwcause = CRIS_MMU_ERR_READ; break;                             // (5) 0.04297
/*52  */ 	}                                                                        // (31) 0.003906
/*56  */ 	/* I exception vectors 4 - 7, D 8 - 11.  */                              // (14) 0.03125
/*58  */ 	vect_base = (mmu + 1) * 4;                                               // (15) 0.0293
/*62  */ 	vpage = vaddr >> 13;                                                     // (20) 0.01758
/*66  */ 	/* We know the index which to check on each set.                         // (17) 0.02539
/*68  */ 	   Scan both I and D.  */                                                // (18) 0.02148
/*70  */ #if 0                                                                     // (30) 0.00586
/*72  */ 	for (set = 0; set < 4; set++) {                                          // (16) 0.02734
/*74  */ 		for (idx = 0; idx < 16; idx++) {                                        // (11) 0.03516
/*76  */ 			lo = env->tlbsets[mmu][set][idx].lo;                                   // 0.0
/*78  */ 			hi = env->tlbsets[mmu][set][idx].hi;                                   // 0.0
/*80  */ 			tlb_vpn = EXTRACT_FIELD(hi, 13, 31);                                   // 0.0
/*82  */ 			tlb_pfn = EXTRACT_FIELD(lo, 13, 31);                                   // 0.0
/*86  */ 			printf ("TLB: [%d][%d] hi=%x lo=%x v=%x p=%x\n",                       // 0.0
/*88  */ 					set, idx, hi, lo, tlb_vpn, tlb_pfn);                                 // 0.0
/*90  */ 		}                                                                       // 0.0
/*92  */ 	}                                                                        // 0.0
/*94  */ #endif                                                                    // 0.0
/*98  */ 	idx = vpage & 15;                                                        // 0.0
/*100 */ 	for (set = 0; set < 4; set++)                                            // 0.0
/*102 */ 	{                                                                        // 0.0
/*104 */ 		lo = env->tlbsets[mmu][set][idx].lo;                                    // 0.0
/*106 */ 		hi = env->tlbsets[mmu][set][idx].hi;                                    // 0.0
/*110 */ 		tlb_vpn = hi >> 13;                                                     // 0.0
/*112 */ 		tlb_pid = EXTRACT_FIELD(hi, 0, 7);                                      // 0.0
/*114 */ 		tlb_g  = EXTRACT_FIELD(lo, 4, 4);                                       // 0.0
/*118 */ 		D_LOG("TLB[%d][%d][%d] v=%x vpage=%x lo=%x hi=%x\n",                    // 0.0
/*120 */ 			 mmu, set, idx, tlb_vpn, vpage, lo, hi);                               // 0.0
/*122 */ 		if ((tlb_g || (tlb_pid == pid))                                         // 0.0
/*124 */ 		    && tlb_vpn == vpage) {                                              // 0.0
/*126 */ 			match = 1;                                                             // 0.0
/*128 */ 			break;                                                                 // 0.0
/*130 */ 		}                                                                       // 0.0
/*132 */ 	}                                                                        // 0.0
/*136 */ 	res->bf_vec = vect_base;                                                 // 0.0
/*138 */ 	if (match) {                                                             // 0.0
/*140 */ 		cfg_w  = EXTRACT_FIELD(r_cfg, 19, 19);                                  // 0.0
/*142 */ 		cfg_k  = EXTRACT_FIELD(r_cfg, 18, 18);                                  // 0.0
/*144 */ 		cfg_x  = EXTRACT_FIELD(r_cfg, 17, 17);                                  // 0.0
/*146 */ 		cfg_v  = EXTRACT_FIELD(r_cfg, 16, 16);                                  // 0.0
/*150 */ 		tlb_pfn = EXTRACT_FIELD(lo, 13, 31);                                    // 0.0
/*152 */ 		tlb_v = EXTRACT_FIELD(lo, 3, 3);                                        // 0.0
/*154 */ 		tlb_k = EXTRACT_FIELD(lo, 2, 2);                                        // 0.0
/*156 */ 		tlb_w = EXTRACT_FIELD(lo, 1, 1);                                        // 0.0
/*158 */ 		tlb_x = EXTRACT_FIELD(lo, 0, 0);                                        // 0.0
/*162 */ 		/*                                                                      // 0.0
/*164 */ 		set_exception_vector(0x04, i_mmu_refill);                               // 0.0
/*166 */ 		set_exception_vector(0x05, i_mmu_invalid);                              // 0.0
/*168 */ 		set_exception_vector(0x06, i_mmu_access);                               // 0.0
/*170 */ 		set_exception_vector(0x07, i_mmu_execute);                              // 0.0
/*172 */ 		set_exception_vector(0x08, d_mmu_refill);                               // 0.0
/*174 */ 		set_exception_vector(0x09, d_mmu_invalid);                              // 0.0
/*176 */ 		set_exception_vector(0x0a, d_mmu_access);                               // 0.0
/*178 */ 		set_exception_vector(0x0b, d_mmu_write);                                // 0.0
/*180 */ 		*/                                                                      // 0.0
/*182 */ 		if (cfg_k && tlb_k && usermode) {                                       // 0.0
/*184 */ 			D(printf ("tlb: kernel protected %x lo=%x pc=%x\n",                    // 0.0
/*186 */ 				  vaddr, lo, env->pc));                                               // 0.0
/*188 */ 			match = 0;                                                             // 0.0
/*190 */ 			res->bf_vec = vect_base + 2;                                           // 0.0
/*192 */ 		} else if (rw == 1 && cfg_w && !tlb_w) {                                // 0.0
/*194 */ 			D(printf ("tlb: write protected %x lo=%x pc=%x\n",                     // 0.0
/*196 */ 				  vaddr, lo, env->pc));                                               // 0.0
/*198 */ 			match = 0;                                                             // 0.0
/*200 */ 			/* write accesses never go through the I mmu.  */                      // 0.0
/*202 */ 			res->bf_vec = vect_base + 3;                                           // 0.0
/*204 */ 		} else if (rw == 2 && cfg_x && !tlb_x) {                                // 0.0
/*206 */ 			D(printf ("tlb: exec protected %x lo=%x pc=%x\n",                      // 0.0
/*208 */ 				 vaddr, lo, env->pc));                                                // 0.0
/*210 */ 			match = 0;                                                             // 0.0
/*212 */ 			res->bf_vec = vect_base + 3;                                           // 0.0
/*214 */ 		} else if (cfg_v && !tlb_v) {                                           // 0.0
/*216 */ 			D(printf ("tlb: invalid %x\n", vaddr));                                // 0.0
/*218 */ 			match = 0;                                                             // 0.0
/*220 */ 			res->bf_vec = vect_base + 1;                                           // 0.0
/*222 */ 		}                                                                       // 0.0
/*226 */ 		res->prot = 0;                                                          // 0.0
/*228 */ 		if (match) {                                                            // 0.0
/*230 */ 			res->prot |= PAGE_READ;                                                // 0.0
/*232 */ 			if (tlb_w)                                                             // 0.0
/*234 */ 				res->prot |= PAGE_WRITE;                                              // 0.0
/*236 */ 			if (tlb_x)                                                             // 0.0
/*238 */ 				res->prot |= PAGE_EXEC;                                               // 0.0
/*240 */ 		}                                                                       // 0.0
/*242 */ 		else                                                                    // 0.0
/*244 */ 			D(dump_tlb(env, mmu));                                                 // 0.0
/*246 */ 	} else {                                                                 // 0.0
/*248 */ 		/* If refill, provide a randomized set.  */                             // 0.0
/*250 */ 		set = env->mmu_rand_lfsr & 3;                                           // 0.0
/*252 */ 	}                                                                        // 0.0
/*256 */ 	if (!match && !debug) {                                                  // 0.0
/*258 */ 		cris_mmu_update_rand_lfsr(env);                                         // 0.0
/*262 */ 		/* Compute index.  */                                                   // 0.0
/*264 */ 		idx = vpage & 15;                                                       // 0.0
/*268 */ 		/* Update RW_MM_TLB_SEL.  */                                            // 0.0
/*270 */ 		env->sregs[SFR_RW_MM_TLB_SEL] = 0;                                      // 0.0
/*272 */ 		set_field(&env->sregs[SFR_RW_MM_TLB_SEL], idx, 0, 4);                   // 0.0
/*274 */ 		set_field(&env->sregs[SFR_RW_MM_TLB_SEL], set, 4, 2);                   // 0.0
/*278 */ 		/* Update RW_MM_CAUSE.  */                                              // 0.0
/*280 */ 		set_field(&r_cause, rwcause, 8, 2);                                     // 0.0
/*282 */ 		set_field(&r_cause, vpage, 13, 19);                                     // 0.0
/*284 */ 		set_field(&r_cause, pid, 0, 8);                                         // 0.0
/*286 */ 		env->sregs[SFR_R_MM_CAUSE] = r_cause;                                   // 0.0
/*288 */ 		D(printf("refill vaddr=%x pc=%x\n", vaddr, env->pc));                   // 0.0
/*290 */ 	}                                                                        // 0.0
/*294 */ 	D(printf ("%s rw=%d mtch=%d pc=%x va=%x vpn=%x tlbvpn=%x pfn=%x pid=%x"  // 0.0
/*296 */ 		  " %x cause=%x sel=%x sp=%x %x %x\n",                                  // 0.0
/*298 */ 		  __func__, rw, match, env->pc,                                         // 0.0
/*300 */ 		  vaddr, vpage,                                                         // 0.0
/*302 */ 		  tlb_vpn, tlb_pfn, tlb_pid,                                            // 0.0
/*304 */ 		  pid,                                                                  // 0.0
/*306 */ 		  r_cause,                                                              // 0.0
/*308 */ 		  env->sregs[SFR_RW_MM_TLB_SEL],                                        // 0.0
/*310 */ 		  env->regs[R_SP], env->pregs[PR_USP], env->ksp));                      // 0.0
/*314 */ 	res->phy = tlb_pfn << TARGET_PAGE_BITS;                                  // 0.0
/*316 */ 	return !match;                                                           // 0.0
/*318 */ }                                                                         // 0.0
