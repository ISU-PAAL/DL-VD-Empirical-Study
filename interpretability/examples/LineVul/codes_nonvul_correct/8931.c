// commit message qemu@41ecc72ba5 (target=0, prob=0.07066515, correct=True): signal/all: remove return value from setup_sigcontext
/*0  */ setup_sigcontext(struct target_sigcontext *sc, struct target_fpstate *fpstate,  // (5) 0.04688
/*2  */ 		 CPUX86State *env, abi_ulong mask, abi_ulong fpstate_addr)                    // (4) 0.05273
/*4  */ {                                                                               // (21) 0.001953
/*6  */     CPUState *cs = CPU(x86_env_get_cpu(env));                                   // (14) 0.04102
/*8  */     int err = 0;                                                                // (20) 0.01563
/*10 */     uint16_t magic;                                                             // (19) 0.01758
/*14 */ 	/* already locked in setup_frame() */                                          // (18) 0.01953
/*16 */     __put_user(env->segs[R_GS].selector, (unsigned int *)&sc->gs);              // (1) 0.05664
/*18 */     __put_user(env->segs[R_FS].selector, (unsigned int *)&sc->fs);              // (3) 0.05664
/*20 */     __put_user(env->segs[R_ES].selector, (unsigned int *)&sc->es);              // (2) 0.05664
/*22 */     __put_user(env->segs[R_DS].selector, (unsigned int *)&sc->ds);              // (0) 0.05664
/*24 */     __put_user(env->regs[R_EDI], &sc->edi);                                     // (13) 0.04492
/*26 */     __put_user(env->regs[R_ESI], &sc->esi);                                     // (12) 0.04492
/*28 */     __put_user(env->regs[R_EBP], &sc->ebp);                                     // (8) 0.04687
/*30 */     __put_user(env->regs[R_ESP], &sc->esp);                                     // (11) 0.04492
/*32 */     __put_user(env->regs[R_EBX], &sc->ebx);                                     // (7) 0.04687
/*34 */     __put_user(env->regs[R_EDX], &sc->edx);                                     // (9) 0.04687
/*36 */     __put_user(env->regs[R_ECX], &sc->ecx);                                     // (10) 0.04687
/*38 */     __put_user(env->regs[R_EAX], &sc->eax);                                     // (6) 0.04687
/*40 */     __put_user(cs->exception_index, &sc->trapno);                               // (15) 0.04102
/*42 */     __put_user(env->error_code, &sc->err);                                      // (16) 0.03711
/*44 */     __put_user(env->eip, &sc->eip);                                             // (17) 0.03711
/*46 */     __put_user(env->segs[R_CS].selector, (unsigned int *)&sc->cs);              // 0.0
/*48 */     __put_user(env->eflags, &sc->eflags);                                       // 0.0
/*50 */     __put_user(env->regs[R_ESP], &sc->esp_at_signal);                           // 0.0
/*52 */     __put_user(env->segs[R_SS].selector, (unsigned int *)&sc->ss);              // 0.0
/*56 */         cpu_x86_fsave(env, fpstate_addr, 1);                                    // 0.0
/*58 */         fpstate->status = fpstate->sw;                                          // 0.0
/*60 */         magic = 0xffff;                                                         // 0.0
/*62 */     __put_user(magic, &fpstate->magic);                                         // 0.0
/*64 */     __put_user(fpstate_addr, &sc->fpstate);                                     // 0.0
/*68 */ 	/* non-iBCS2 extensions.. */                                                   // 0.0
/*70 */     __put_user(mask, &sc->oldmask);                                             // 0.0
/*72 */     __put_user(env->cr[2], &sc->cr2);                                           // 0.0
/*74 */ 	return err;                                                                    // 0.0
/*76 */ }                                                                               // 0.0
