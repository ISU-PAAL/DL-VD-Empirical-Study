// commit message qemu@372579427a (target=1, prob=0.4585343, correct=False): tcg: enable thread-per-vCPU
/*0  */ static void qemu_tcg_init_vcpu(CPUState *cpu)                                 // (10) 0.03711
/*2  */ {                                                                             // (23) 0.001953
/*4  */     char thread_name[VCPU_THREAD_NAME_SIZE];                                  // (11) 0.03516
/*6  */     static QemuCond *tcg_halt_cond;                                           // (14) 0.0332
/*8  */     static QemuThread *tcg_cpu_thread;                                        // (16) 0.03125
/*12 */     /* share a single thread for all cpus with TCG */                         // (15) 0.03125
/*14 */     if (!tcg_cpu_thread) {                                                    // (18) 0.02539
/*16 */         cpu->thread = g_malloc0(sizeof(QemuThread));                          // (6) 0.04883
/*18 */         cpu->halt_cond = g_malloc0(sizeof(QemuCond));                         // (4) 0.05469
/*20 */         qemu_cond_init(cpu->halt_cond);                                       // (8) 0.04297
/*22 */         tcg_halt_cond = cpu->halt_cond;                                       // (7) 0.04297
/*24 */         snprintf(thread_name, VCPU_THREAD_NAME_SIZE, "CPU %d/TCG",            // (3) 0.0625
/*26 */                  cpu->cpu_index);                                             // (9) 0.04297
/*28 */         qemu_thread_create(cpu->thread, thread_name, qemu_tcg_cpu_thread_fn,  // (2) 0.07031
/*30 */                            cpu, QEMU_THREAD_JOINABLE);                        // (0) 0.07617
/*32 */ #ifdef _WIN32                                                                 // (20) 0.01172
/*34 */         cpu->hThread = qemu_thread_get_handle(cpu->thread);                   // (5) 0.05078
/*36 */ #endif                                                                        // (22) 0.003906
/*38 */         while (!cpu->created) {                                               // (17) 0.02734
/*40 */             qemu_cond_wait(&qemu_cpu_cond, &qemu_global_mutex);               // (1) 0.07227
/*42 */         }                                                                     // (19) 0.01563
/*44 */         tcg_cpu_thread = cpu->thread;                                         // (12) 0.03516
/*46 */     } else {                                                                  // (21) 0.01172
/*48 */         cpu->thread = tcg_cpu_thread;                                         // (13) 0.03516
/*50 */         cpu->halt_cond = tcg_halt_cond;                                       // 0.0
/*52 */     }                                                                         // 0.0
/*54 */ }                                                                             // 0.0
