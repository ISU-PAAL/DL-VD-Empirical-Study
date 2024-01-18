// commit message qemu@d516f74c99 (target=0, prob=0.51823413, correct=False): s390x/tcg: cleanup service interrupt injection
/*0   */ static void do_ext_interrupt(CPUS390XState *env)                            // (14) 0.0332
/*2   */ {                                                                           // (24) 0.001953
/*4   */     S390CPU *cpu = s390_env_get_cpu(env);                                   // (12) 0.03906
/*6   */     uint64_t mask, addr;                                                    // (18) 0.02148
/*8   */     LowCore *lowcore;                                                       // (19) 0.01758
/*10  */     ExtQueue *q;                                                            // (21) 0.01563
/*14  */     if (!(env->psw.mask & PSW_MASK_EXT)) {                                  // (10) 0.04297
/*16  */         cpu_abort(CPU(cpu), "Ext int w/o ext mask\n");                      // (5) 0.05273
/*18  */     }                                                                       // (23) 0.007813
/*22  */     lowcore = cpu_map_lowcore(env);                                         // (17) 0.0293
/*26  */     if (env->pending_int & INTERRUPT_EXT_CLOCK_COMPARATOR) {                // (6) 0.05273
/*28  */         lowcore->ext_int_code = cpu_to_be16(EXT_CLOCK_COMP);                // (0) 0.06055
/*30  */         lowcore->cpu_addr = 0;                                              // (15) 0.03125
/*32  */         env->pending_int &= ~INTERRUPT_EXT_CLOCK_COMPARATOR;                // (2) 0.05859
/*34  */     } else if (env->pending_int & INTERRUPT_EXT_CPU_TIMER) {                // (4) 0.05469
/*36  */         lowcore->ext_int_code = cpu_to_be16(EXT_CPU_TIMER);                 // (1) 0.06055
/*38  */         lowcore->cpu_addr = 0;                                              // (16) 0.03125
/*40  */         env->pending_int &= ~INTERRUPT_EXT_CPU_TIMER;                       // (3) 0.05664
/*42  */     } else if (env->pending_int & INTERRUPT_EXT_SERVICE) {                  // (8) 0.04883
/*44  */         g_assert(env->ext_index >= 0);                                      // (13) 0.03711
/*46  */         /*                                                                  // (22) 0.01563
/*48  */          * FIXME: floating IRQs should be considered by all CPUs and        // (9) 0.04492
/*50  */          *        shuld not get cleared by CPU reset.                       // (7) 0.04883
/*52  */          */                                                                 // (20) 0.01758
/*54  */         q = &env->ext_queue[env->ext_index];                                // (11) 0.04297
/*56  */         lowcore->ext_int_code = cpu_to_be16(q->code);                       // 0.0
/*58  */         lowcore->ext_params = cpu_to_be32(q->param);                        // 0.0
/*60  */         lowcore->ext_params2 = cpu_to_be64(q->param64);                     // 0.0
/*62  */         lowcore->cpu_addr = cpu_to_be16(env->core_id | VIRTIO_SUBCODE_64);  // 0.0
/*64  */         env->ext_index--;                                                   // 0.0
/*66  */         if (env->ext_index == -1) {                                         // 0.0
/*68  */             env->pending_int &= ~INTERRUPT_EXT_SERVICE;                     // 0.0
/*70  */         }                                                                   // 0.0
/*72  */     } else {                                                                // 0.0
/*74  */         g_assert_not_reached();                                             // 0.0
/*76  */     }                                                                       // 0.0
/*80  */     mask = be64_to_cpu(lowcore->external_new_psw.mask);                     // 0.0
/*82  */     addr = be64_to_cpu(lowcore->external_new_psw.addr);                     // 0.0
/*84  */     lowcore->external_old_psw.mask = cpu_to_be64(get_psw_mask(env));        // 0.0
/*86  */     lowcore->external_old_psw.addr = cpu_to_be64(env->psw.addr);            // 0.0
/*90  */     cpu_unmap_lowcore(lowcore);                                             // 0.0
/*94  */     DPRINTF("%s: %" PRIx64 " %" PRIx64 "\n", __func__,                      // 0.0
/*96  */             env->psw.mask, env->psw.addr);                                  // 0.0
/*100 */     load_psw(env, mask, addr);                                              // 0.0
/*102 */ }                                                                           // 0.0
