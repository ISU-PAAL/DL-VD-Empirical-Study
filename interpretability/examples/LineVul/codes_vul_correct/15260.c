// commit message qemu@8de433cb08 (target=1, prob=0.9990695, correct=True): pc: Fix crash when attempting to hotplug CPU with negative ID
/*0  */ void pc_hot_add_cpu(const int64_t id, Error **errp)                        // (8) 0.06383
/*1  */ {                                                                          // (12) 0.00304
/*2  */     DeviceState *icc_bridge;                                               // (11) 0.0304
/*3  */     int64_t apic_id = x86_cpu_apic_id_from_index(id);                      // (3) 0.08511
/*4  */     if (cpu_exists(apic_id)) {                                             // (9) 0.04863
/*5  */         error_setg(errp, "Unable to add CPU: %" PRIi64                     // (4) 0.08511
/*6  */                    ", it already exists", id);                             // (6) 0.07599
/*7  */     if (id >= max_cpus) {                                                  // (10) 0.03951
/*8  */         error_setg(errp, "Unable to add CPU: %" PRIi64                     // (5) 0.08511
/*9  */                    ", max allowed: %d", id, max_cpus - 1);                 // (1) 0.1033
/*10 */     icc_bridge = DEVICE(object_resolve_path_type("icc-bridge",             // (7) 0.07295
/*11 */                                                  TYPE_ICC_BRIDGE, NULL));  // (0) 0.1793
/*12 */     pc_new_cpu(current_cpu_model, apic_id, icc_bridge, errp);              // (2) 0.08511
