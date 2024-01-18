// commit message qemu@61a36c9b5a (target=1, prob=0.51932603, correct=True): target-ppc: Add new TLB invalidate by HPTE call for hash64 MMUs
/*0  */ static RemoveResult remove_hpte(PowerPCCPU *cpu, target_ulong ptex,  // (8) 0.04492
/*2  */                                 target_ulong avpn,                   // (1) 0.07422
/*4  */                                 target_ulong flags,                  // (2) 0.07227
/*6  */                                 target_ulong *vp, target_ulong *rp)  // (0) 0.08984
/*8  */ {                                                                    // (23) 0.001953
/*10 */     CPUPPCState *env = &cpu->env;                                    // (14) 0.0293
/*12 */     uint64_t token;                                                  // (18) 0.01758
/*14 */     target_ulong v, r, rb;                                           // (17) 0.02734
/*18 */     if (!valid_pte_index(env, ptex)) {                               // (12) 0.03516
/*20 */         return REMOVE_PARM;                                          // (15) 0.0293
/*22 */     }                                                                // (21) 0.007812
/*26 */     token = ppc_hash64_start_access(cpu, ptex);                      // (9) 0.03906
/*28 */     v = ppc_hash64_load_hpte0(cpu, token, 0);                        // (6) 0.04688
/*30 */     r = ppc_hash64_load_hpte1(cpu, token, 0);                        // (7) 0.04688
/*32 */     ppc_hash64_stop_access(token);                                   // (16) 0.0293
/*36 */     if ((v & HPTE64_V_VALID) == 0 ||                                 // (11) 0.03711
/*38 */         ((flags & H_AVPN) && (v & ~0x7fULL) != avpn) ||              // (4) 0.06055
/*40 */         ((flags & H_ANDCOND) && (v & avpn) != 0)) {                  // (5) 0.05273
/*42 */         return REMOVE_NOT_FOUND;                                     // (13) 0.0332
/*44 */     }                                                                // (22) 0.007812
/*46 */     *vp = v;                                                         // (20) 0.01562
/*48 */     *rp = r;                                                         // (19) 0.01758
/*50 */     ppc_hash64_store_hpte(cpu, ptex, HPTE64_V_HPTE_DIRTY, 0);        // (3) 0.06641
/*52 */     rb = compute_tlbie_rb(v, r, ptex);                               // (10) 0.03906
/*54 */     ppc_tlb_invalidate_one(env, rb);                                 // 0.0
/*56 */     return REMOVE_SUCCESS;                                           // 0.0
/*58 */ }                                                                    // 0.0
