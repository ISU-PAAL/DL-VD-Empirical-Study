// commit message qemu@74892d2468 (target=1, prob=0.99923015, correct=True): vl: allow other threads to do qemu_system_vmstop_request
/*0  */ int vm_stop(RunState state)                                 // (7) 0.0566
/*2  */ {                                                           // (11) 0.006289
/*4  */     if (qemu_in_vcpu_thread()) {                            // (2) 0.1069
/*7  */         qemu_system_vmstop_request(state);                  // (1) 0.1258
/*9  */         /*                                                  // (9) 0.05031
/*11 */          * FIXME: should not return to device code in case  // (0) 0.1258
/*13 */          * vm_stop() has been requested.                    // (3) 0.1069
/*15 */          */                                                 // (8) 0.0566
/*17 */         cpu_stop_current();                                 // (4) 0.08176
/*19 */         return 0;                                           // (6) 0.06289
/*21 */     }                                                       // (10) 0.02516
/*25 */     return do_vm_stop(state);                               // (5) 0.07547
/*27 */ }                                                           // (12) 0.006289
