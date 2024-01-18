// commit message qemu@fa3aad24d9 (target=0, prob=0.59453696, correct=False): VMState: Fix sub-structs versioning
/*0  */ int vmstate_load_state(QEMUFile *f, const VMStateDescription *vmsd,              // (5) 0.04688
/*2  */                        void *opaque, int version_id)                             // (1) 0.0625
/*4  */ {                                                                                // (24) 0.001953
/*6  */     VMStateField *field = vmsd->fields;                                          // (15) 0.0293
/*10 */     if (version_id > vmsd->version_id) {                                         // (14) 0.03516
/*12 */         return -EINVAL;                                                          // (17) 0.02539
/*14 */     }                                                                            // (23) 0.007812
/*16 */     if (version_id < vmsd->minimum_version_id_old) {                             // (11) 0.04297
/*18 */         return -EINVAL;                                                          // (16) 0.02539
/*20 */     }                                                                            // (22) 0.007812
/*22 */     if  (version_id < vmsd->minimum_version_id) {                                // (12) 0.04102
/*24 */         return vmsd->load_state_old(f, opaque, version_id);                      // (4) 0.05078
/*26 */     }                                                                            // (21) 0.007812
/*28 */     while(field->name) {                                                         // (20) 0.01953
/*30 */         if (field->version_id <= version_id) {                                   // (13) 0.03906
/*32 */             void *base_addr = opaque + field->offset;                            // (10) 0.04492
/*34 */             int ret, i, n_elems = 1;                                             // (9) 0.04492
/*38 */             if (field->flags & VMS_ARRAY) {                                      // (7) 0.04687
/*40 */                 n_elems = field->num;                                            // (6) 0.04687
/*42 */             } else if (field->flags & VMS_VARRAY) {                              // (3) 0.05273
/*44 */                 n_elems = *(size_t *)(opaque+field->num_offset);                 // (0) 0.07031
/*46 */             }                                                                    // (18) 0.02344
/*48 */             if (field->flags & VMS_POINTER) {                                    // (8) 0.04687
/*50 */                 base_addr = *(void **)base_addr;                                 // (2) 0.05469
/*52 */             }                                                                    // (19) 0.02344
/*54 */             for (i = 0; i < n_elems; i++) {                                      // 0.0
/*56 */                 void *addr = base_addr + field->size * i;                        // 0.0
/*60 */                 if (field->flags & VMS_STRUCT) {                                 // 0.0
/*62 */                     ret = vmstate_load_state(f, field->vmsd, addr, version_id);  // 0.0
/*64 */                 } else {                                                         // 0.0
/*66 */                     ret = field->info->get(f, addr, field->size);                // 0.0
/*70 */                 }                                                                // 0.0
/*72 */                 if (ret < 0) {                                                   // 0.0
/*74 */                     return ret;                                                  // 0.0
/*76 */                 }                                                                // 0.0
/*78 */             }                                                                    // 0.0
/*80 */         }                                                                        // 0.0
/*82 */         field++;                                                                 // 0.0
/*84 */     }                                                                            // 0.0
/*86 */     if (vmsd->run_after_load)                                                    // 0.0
/*88 */         return vmsd->run_after_load(opaque);                                     // 0.0
/*90 */     return 0;                                                                    // 0.0
/*92 */ }                                                                                // 0.0
