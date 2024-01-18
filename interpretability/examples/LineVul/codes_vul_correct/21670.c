// commit message qemu@f68945d42b (target=1, prob=0.99922705, correct=True): Add a protective section footer
/*0   */ void qemu_savevm_state_complete(QEMUFile *f)                               // (10) 0.03711
/*2   */ {                                                                          // (28) 0.001953
/*4   */     QJSON *vmdesc;                                                         // (20) 0.01953
/*6   */     int vmdesc_len;                                                        // (21) 0.01953
/*8   */     SaveStateEntry *se;                                                    // (22) 0.01758
/*10  */     int ret;                                                               // (26) 0.01172
/*14  */     trace_savevm_state_complete();                                         // (17) 0.02344
/*18  */     cpu_synchronize_all_states();                                          // (14) 0.02539
/*22  */     QTAILQ_FOREACH(se, &savevm_state.handlers, entry) {                    // (6) 0.04883
/*24  */         if (!se->ops || !se->ops->save_live_complete) {                    // (7) 0.04883
/*26  */             continue;                                                      // (15) 0.02539
/*28  */         }                                                                  // (23) 0.01562
/*30  */         if (se->ops && se->ops->is_active) {                               // (9) 0.04297
/*32  */             if (!se->ops->is_active(se->opaque)) {                         // (2) 0.05273
/*34  */                 continue;                                                  // (11) 0.0332
/*36  */             }                                                              // (18) 0.02344
/*38  */         }                                                                  // (24) 0.01562
/*40  */         trace_savevm_section_start(se->idstr, se->section_id);             // (3) 0.05273
/*44  */         save_section_header(f, se, QEMU_VM_SECTION_END);                   // (1) 0.05469
/*48  */         ret = se->ops->save_live_complete(f, se->opaque);                  // (4) 0.05078
/*50  */         trace_savevm_section_end(se->idstr, se->section_id, ret);          // (0) 0.05664
/*53  */         if (ret < 0) {                                                     // (13) 0.02734
/*55  */             qemu_file_set_error(f, ret);                                   // (8) 0.04883
/*57  */             return;                                                        // (16) 0.02539
/*59  */         }                                                                  // (25) 0.01562
/*61  */     }                                                                      // (27) 0.007812
/*65  */     vmdesc = qjson_new();                                                  // (19) 0.02344
/*67  */     json_prop_int(vmdesc, "page_size", TARGET_PAGE_SIZE);                  // (5) 0.05078
/*69  */     json_start_array(vmdesc, "devices");                                   // (12) 0.03125
/*71  */     QTAILQ_FOREACH(se, &savevm_state.handlers, entry) {                    // 0.0
/*75  */         if ((!se->ops || !se->ops->save_state) && !se->vmsd) {             // 0.0
/*77  */             continue;                                                      // 0.0
/*79  */         }                                                                  // 0.0
/*81  */         trace_savevm_section_start(se->idstr, se->section_id);             // 0.0
/*85  */         json_start_object(vmdesc, NULL);                                   // 0.0
/*87  */         json_prop_str(vmdesc, "name", se->idstr);                          // 0.0
/*89  */         json_prop_int(vmdesc, "instance_id", se->instance_id);             // 0.0
/*93  */         save_section_header(f, se, QEMU_VM_SECTION_FULL);                  // 0.0
/*97  */         vmstate_save(f, se, vmdesc);                                       // 0.0
/*101 */         json_end_object(vmdesc);                                           // 0.0
/*103 */         trace_savevm_section_end(se->idstr, se->section_id, 0);            // 0.0
/*106 */     }                                                                      // 0.0
/*110 */     qemu_put_byte(f, QEMU_VM_EOF);                                         // 0.0
/*114 */     json_end_array(vmdesc);                                                // 0.0
/*116 */     qjson_finish(vmdesc);                                                  // 0.0
/*118 */     vmdesc_len = strlen(qjson_get_str(vmdesc));                            // 0.0
/*122 */     if (should_send_vmdesc()) {                                            // 0.0
/*124 */         qemu_put_byte(f, QEMU_VM_VMDESCRIPTION);                           // 0.0
/*126 */         qemu_put_be32(f, vmdesc_len);                                      // 0.0
/*128 */         qemu_put_buffer(f, (uint8_t *)qjson_get_str(vmdesc), vmdesc_len);  // 0.0
/*130 */     }                                                                      // 0.0
/*132 */     object_unref(OBJECT(vmdesc));                                          // 0.0
/*136 */     qemu_fflush(f);                                                        // 0.0
/*138 */ }                                                                          // 0.0
