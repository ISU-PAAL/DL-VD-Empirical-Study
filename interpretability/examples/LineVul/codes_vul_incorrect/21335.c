// commit message qemu@07d4e69147 (target=1, prob=0.44295335, correct=False): migration/vmstate: fix array of ptr with nullptrs
/*0   */ int vmstate_load_state(QEMUFile *f, const VMStateDescription *vmsd,      // (8) 0.04688
/*2   */                        void *opaque, int version_id)                     // (3) 0.0625
/*4   */ {                                                                        // (21) 0.001953
/*6   */     VMStateField *field = vmsd->fields;                                  // (15) 0.0293
/*8   */     int ret = 0;                                                         // (18) 0.01563
/*12  */     trace_vmstate_load_state(vmsd->name, version_id);                    // (11) 0.04297
/*14  */     if (version_id > vmsd->version_id) {                                 // (14) 0.03516
/*16  */         error_report("%s: incoming version_id %d is too new "            // (9) 0.04688
/*18  */                      "for local version_id %d",                          // (6) 0.05664
/*20  */                      vmsd->name, version_id, vmsd->version_id);          // (0) 0.07422
/*22  */         trace_vmstate_load_state_end(vmsd->name, "too new", -EINVAL);    // (2) 0.06445
/*24  */         return -EINVAL;                                                  // (17) 0.02539
/*26  */     }                                                                    // (20) 0.007812
/*28  */     if  (version_id < vmsd->minimum_version_id) {                        // (12) 0.04102
/*30  */         if (vmsd->load_state_old &&                                      // (13) 0.03711
/*32  */             version_id >= vmsd->minimum_version_id_old) {                // (7) 0.05469
/*34  */             ret = vmsd->load_state_old(f, opaque, version_id);           // (4) 0.06055
/*36  */             trace_vmstate_load_state_end(vmsd->name, "old path", ret);   // (1) 0.06641
/*38  */             return ret;                                                  // (16) 0.02734
/*40  */         }                                                                // (19) 0.01563
/*42  */         error_report("%s: incoming version_id %d is too old "            // (10) 0.04688
/*44  */                      "for local minimum version_id  %d",                 // (5) 0.06055
/*46  */                      vmsd->name, version_id, vmsd->minimum_version_id);  // 0.0
/*48  */         trace_vmstate_load_state_end(vmsd->name, "too old", -EINVAL);    // 0.0
/*50  */         return -EINVAL;                                                  // 0.0
/*52  */     }                                                                    // 0.0
/*54  */     if (vmsd->pre_load) {                                                // 0.0
/*56  */         int ret = vmsd->pre_load(opaque);                                // 0.0
/*58  */         if (ret) {                                                       // 0.0
/*60  */             return ret;                                                  // 0.0
/*62  */         }                                                                // 0.0
/*64  */     }                                                                    // 0.0
/*66  */     while (field->name) {                                                // 0.0
/*68  */         trace_vmstate_load_state_field(vmsd->name, field->name);         // 0.0
/*70  */         if ((field->field_exists &&                                      // 0.0
/*72  */              field->field_exists(opaque, version_id)) ||                 // 0.0
/*74  */             (!field->field_exists &&                                     // 0.0
/*76  */              field->version_id <= version_id)) {                         // 0.0
/*78  */             void *first_elem = opaque + field->offset;                   // 0.0
/*80  */             int i, n_elems = vmstate_n_elems(opaque, field);             // 0.0
/*82  */             int size = vmstate_size(opaque, field);                      // 0.0
/*86  */             vmstate_handle_alloc(first_elem, field, opaque);             // 0.0
/*88  */             if (field->flags & VMS_POINTER) {                            // 0.0
/*90  */                 first_elem = *(void **)first_elem;                       // 0.0
/*92  */                 assert(first_elem  || !n_elems);                         // 0.0
/*94  */             }                                                            // 0.0
/*96  */             for (i = 0; i < n_elems; i++) {                              // 0.0
/*98  */                 void *curr_elem = first_elem + size * i;                 // 0.0
/*102 */                 if (field->flags & VMS_ARRAY_OF_POINTER) {               // 0.0
/*104 */                     curr_elem = *(void **)curr_elem;                     // 0.0
/*106 */                 }                                                        // 0.0
/*108 */                 if (field->flags & VMS_STRUCT) {                         // 0.0
/*110 */                     ret = vmstate_load_state(f, field->vmsd, curr_elem,  // 0.0
/*112 */                                              field->vmsd->version_id);   // 0.0
/*114 */                 } else {                                                 // 0.0
/*116 */                     ret = field->info->get(f, curr_elem, size, field);   // 0.0
/*118 */                 }                                                        // 0.0
/*120 */                 if (ret >= 0) {                                          // 0.0
/*122 */                     ret = qemu_file_get_error(f);                        // 0.0
/*124 */                 }                                                        // 0.0
/*126 */                 if (ret < 0) {                                           // 0.0
/*128 */                     qemu_file_set_error(f, ret);                         // 0.0
/*130 */                     error_report("Failed to load %s:%s", vmsd->name,     // 0.0
/*132 */                                  field->name);                           // 0.0
/*134 */                     trace_vmstate_load_field_error(field->name, ret);    // 0.0
/*136 */                     return ret;                                          // 0.0
/*138 */                 }                                                        // 0.0
/*140 */             }                                                            // 0.0
/*142 */         } else if (field->flags & VMS_MUST_EXIST) {                      // 0.0
/*144 */             error_report("Input validation failed: %s/%s",               // 0.0
/*146 */                          vmsd->name, field->name);                       // 0.0
/*148 */             return -1;                                                   // 0.0
/*150 */         }                                                                // 0.0
/*152 */         field++;                                                         // 0.0
/*154 */     }                                                                    // 0.0
/*156 */     ret = vmstate_subsection_load(f, vmsd, opaque);                      // 0.0
/*158 */     if (ret != 0) {                                                      // 0.0
/*160 */         return ret;                                                      // 0.0
/*162 */     }                                                                    // 0.0
/*164 */     if (vmsd->post_load) {                                               // 0.0
/*166 */         ret = vmsd->post_load(opaque, version_id);                       // 0.0
/*168 */     }                                                                    // 0.0
/*170 */     trace_vmstate_load_state_end(vmsd->name, "end", ret);                // 0.0
/*172 */     return ret;                                                          // 0.0
/*174 */ }                                                                        // 0.0
