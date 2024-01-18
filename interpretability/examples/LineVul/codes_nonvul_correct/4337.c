// commit message qemu@9d27abd94f (target=0, prob=0.29534087, correct=True): fixed invalid CPL logic in vm86 mode - use generic CPU dump state function
/*0  */ static void cpu_x86_dump_state(FILE *f)                                               // (12) 0.0293
/*2  */ {                                                                                     // (18) 0.001953
/*4  */     int eflags;                                                                       // (16) 0.01367
/*6  */     char cc_op_name[32];                                                              // (14) 0.02344
/*8  */     eflags = cc_table[CC_OP].compute_all();                                           // (11) 0.03711
/*10 */     eflags |= (DF & DF_MASK);                                                         // (13) 0.0293
/*12 */     if ((unsigned)env->cc_op < CC_OP_NB)                                              // (10) 0.03711
/*14 */         strcpy(cc_op_name, cc_op_str[env->cc_op]);                                    // (7) 0.05664
/*16 */     else                                                                              // (17) 0.007812
/*18 */         snprintf(cc_op_name, sizeof(cc_op_name), "[%d]", env->cc_op);                 // (5) 0.06836
/*20 */     fprintf(f,                                                                        // (15) 0.01758
/*22 */             "EAX=%08x EBX=%08X ECX=%08x EDX=%08x\n"                                   // (3) 0.07617
/*24 */             "ESI=%08x EDI=%08X EBP=%08x ESP=%08x\n"                                   // (4) 0.07422
/*26 */             "CCS=%08x CCD=%08x CCO=%-8s EFL=%c%c%c%c%c%c%c\n"                         // (2) 0.09766
/*28 */             "EIP=%08x\n",                                                             // (9) 0.04102
/*30 */             env->regs[R_EAX], env->regs[R_EBX], env->regs[R_ECX], env->regs[R_EDX],   // (1) 0.1016
/*32 */             env->regs[R_ESI], env->regs[R_EDI], env->regs[R_EBP], env->regs[R_ESP],   // (0) 0.1016
/*34 */             env->cc_src, env->cc_dst, cc_op_name,                                     // (6) 0.05859
/*36 */             eflags & DF_MASK ? 'D' : '-',                                             // (8) 0.05078
/*38 */             eflags & CC_O ? 'O' : '-',                                                // 0.0
/*40 */             eflags & CC_S ? 'S' : '-',                                                // 0.0
/*42 */             eflags & CC_Z ? 'Z' : '-',                                                // 0.0
/*44 */             eflags & CC_A ? 'A' : '-',                                                // 0.0
/*46 */             eflags & CC_P ? 'P' : '-',                                                // 0.0
/*48 */             eflags & CC_C ? 'C' : '-',                                                // 0.0
/*50 */             env->eip);                                                                // 0.0
/*52 */ #if 1                                                                                 // 0.0
/*54 */     fprintf(f, "ST0=%f ST1=%f ST2=%f ST3=%f\n",                                       // 0.0
/*56 */             (double)ST0, (double)ST1, (double)ST(2), (double)ST(3));                  // 0.0
/*58 */ #endif                                                                                // 0.0
/*60 */ }                                                                                     // 0.0
