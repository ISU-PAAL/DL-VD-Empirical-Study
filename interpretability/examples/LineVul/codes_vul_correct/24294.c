// commit message qemu@12d4536f7d (target=1, prob=0.51251894, correct=True): main: force enabling of I/O thread
/*0   */ static void main_loop(void)                                  // (22) 0.01563
/*2   */ {                                                            // (35) 0.001953
/*4   */     bool nonblocking;                                        // (28) 0.01367
/*6   */     int last_io __attribute__ ((unused)) = 0;                // (11) 0.0332
/*8   */ #ifdef CONFIG_PROFILER                                       // (18) 0.01758
/*10  */     int64_t ti;                                              // (20) 0.01758
/*12  */ #endif                                                       // (31) 0.003906
/*14  */     int r;                                                   // (29) 0.01172
/*18  */     qemu_main_loop_start();                                  // (16) 0.02539
/*22  */     for (;;) {                                               // (23) 0.01563
/*24  */ #ifdef CONFIG_IOTHREAD                                       // (24) 0.01562
/*26  */         nonblocking = !kvm_enabled() && last_io > 0;         // (2) 0.04492
/*28  */ #else                                                        // (34) 0.003906
/*30  */         nonblocking = cpu_exec_all();                        // (13) 0.03125
/*32  */         if (vm_request_pending()) {                          // (10) 0.0332
/*34  */             nonblocking = true;                              // (14) 0.03125
/*36  */         }                                                    // (25) 0.01562
/*38  */ #endif                                                       // (30) 0.003906
/*40  */ #ifdef CONFIG_PROFILER                                       // (19) 0.01758
/*42  */         ti = profile_getclock();                             // (15) 0.02734
/*44  */ #endif                                                       // (33) 0.003906
/*46  */         last_io = main_loop_wait(nonblocking);               // (4) 0.03906
/*48  */ #ifdef CONFIG_PROFILER                                       // (21) 0.01758
/*50  */         dev_time += profile_getclock() - ti;                 // (8) 0.03711
/*52  */ #endif                                                       // (32) 0.003906
/*56  */         if (qemu_debug_requested()) {                        // (7) 0.03711
/*58  */             vm_stop(VMSTOP_DEBUG);                           // (3) 0.04102
/*60  */         }                                                    // (26) 0.01562
/*62  */         if (qemu_shutdown_requested()) {                     // (5) 0.03906
/*64  */             qemu_kill_report();                              // (6) 0.03711
/*66  */             monitor_protocol_event(QEVENT_SHUTDOWN, NULL);   // (0) 0.05469
/*68  */             if (no_shutdown) {                               // (9) 0.03711
/*70  */                 vm_stop(VMSTOP_SHUTDOWN);                    // (1) 0.05273
/*72  */             } else                                           // (17) 0.02539
/*74  */                 break;                                       // (12) 0.0332
/*76  */         }                                                    // (27) 0.01562
/*78  */         if (qemu_reset_requested()) {                        // 0.0
/*80  */             pause_all_vcpus();                               // 0.0
/*82  */             cpu_synchronize_all_states();                    // 0.0
/*84  */             qemu_system_reset(VMRESET_REPORT);               // 0.0
/*86  */             resume_all_vcpus();                              // 0.0
/*88  */         }                                                    // 0.0
/*90  */         if (qemu_powerdown_requested()) {                    // 0.0
/*92  */             monitor_protocol_event(QEVENT_POWERDOWN, NULL);  // 0.0
/*94  */             qemu_irq_raise(qemu_system_powerdown);           // 0.0
/*96  */         }                                                    // 0.0
/*98  */         if ((r = qemu_vmstop_requested())) {                 // 0.0
/*100 */             vm_stop(r);                                      // 0.0
/*102 */         }                                                    // 0.0
/*104 */     }                                                        // 0.0
/*106 */     bdrv_close_all();                                        // 0.0
/*108 */     pause_all_vcpus();                                       // 0.0
/*110 */ }                                                            // 0.0
