// commit message qemu@ffbb1705a3 (target=0, prob=0.12527318, correct=True): spapr_events: add support for dedicated hotplug event source
/*0   */ static void spapr_hotplug_req_event(uint8_t hp_id, uint8_t hp_action,        // (4) 0.05664
/*2   */                                     sPAPRDRConnectorType drc_type,           // (0) 0.0918
/*4   */                                     uint32_t drc)                            // (3) 0.08203
/*6   */ {                                                                            // (19) 0.001953
/*8   */     sPAPRMachineState *spapr = SPAPR_MACHINE(qdev_get_machine());            // (5) 0.05664
/*10  */     struct hp_log_full *new_hp;                                              // (14) 0.02734
/*12  */     struct rtas_error_log *hdr;                                              // (13) 0.0293
/*14  */     struct rtas_event_log_v6 *v6hdr;                                         // (10) 0.03906
/*16  */     struct rtas_event_log_v6_maina *maina;                                   // (8) 0.04102
/*18  */     struct rtas_event_log_v6_mainb *mainb;                                   // (9) 0.04102
/*20  */     struct rtas_event_log_v6_hp *hp;                                         // (11) 0.03711
/*24  */     new_hp = g_malloc0(sizeof(struct hp_log_full));                          // (7) 0.04492
/*26  */     hdr = &new_hp->hdr;                                                      // (15) 0.02734
/*28  */     v6hdr = &new_hp->v6hdr;                                                  // (12) 0.03516
/*30  */     maina = &new_hp->maina;                                                  // (16) 0.02734
/*32  */     mainb = &new_hp->mainb;                                                  // (17) 0.02734
/*34  */     hp = &new_hp->hp;                                                        // (18) 0.02344
/*38  */     hdr->summary = cpu_to_be32(RTAS_LOG_VERSION_6                            // (6) 0.04492
/*40  */                                | RTAS_LOG_SEVERITY_EVENT                     // (2) 0.08203
/*42  */                                | RTAS_LOG_DISPOSITION_NOT_RECOVERED          // (1) 0.08984
/*44  */                                | RTAS_LOG_OPTIONAL_PART_PRESENT              // 0.0
/*46  */                                | RTAS_LOG_INITIATOR_HOTPLUG                  // 0.0
/*48  */                                | RTAS_LOG_TYPE_HOTPLUG);                     // 0.0
/*50  */     hdr->extended_length = cpu_to_be32(sizeof(*new_hp)                       // 0.0
/*52  */                                        - sizeof(new_hp->hdr));               // 0.0
/*56  */     spapr_init_v6hdr(v6hdr);                                                 // 0.0
/*58  */     spapr_init_maina(maina, 3 /* Main-A, Main-B, HP */);                     // 0.0
/*62  */     mainb->hdr.section_id = cpu_to_be16(RTAS_LOG_V6_SECTION_ID_MAINB);       // 0.0
/*64  */     mainb->hdr.section_length = cpu_to_be16(sizeof(*mainb));                 // 0.0
/*66  */     mainb->subsystem_id = 0x80; /* External environment */                   // 0.0
/*68  */     mainb->event_severity = 0x00; /* Informational / non-error */            // 0.0
/*70  */     mainb->event_subtype = 0x00; /* Normal shutdown */                       // 0.0
/*74  */     hp->hdr.section_id = cpu_to_be16(RTAS_LOG_V6_SECTION_ID_HOTPLUG);        // 0.0
/*76  */     hp->hdr.section_length = cpu_to_be16(sizeof(*hp));                       // 0.0
/*78  */     hp->hdr.section_version = 1; /* includes extended modifier */            // 0.0
/*80  */     hp->hotplug_action = hp_action;                                          // 0.0
/*82  */     hp->hotplug_identifier = hp_id;                                          // 0.0
/*86  */     switch (drc_type) {                                                      // 0.0
/*88  */     case SPAPR_DR_CONNECTOR_TYPE_PCI:                                        // 0.0
/*90  */         hp->hotplug_type = RTAS_LOG_V6_HP_TYPE_PCI;                          // 0.0
/*92  */         if (hp->hotplug_action == RTAS_LOG_V6_HP_ACTION_ADD) {               // 0.0
/*94  */             spapr_hotplug_set_signalled(drc);                                // 0.0
/*96  */         }                                                                    // 0.0
/*98  */         break;                                                               // 0.0
/*100 */     case SPAPR_DR_CONNECTOR_TYPE_LMB:                                        // 0.0
/*102 */         hp->hotplug_type = RTAS_LOG_V6_HP_TYPE_MEMORY;                       // 0.0
/*104 */         break;                                                               // 0.0
/*106 */     case SPAPR_DR_CONNECTOR_TYPE_CPU:                                        // 0.0
/*108 */         hp->hotplug_type = RTAS_LOG_V6_HP_TYPE_CPU;                          // 0.0
/*110 */         break;                                                               // 0.0
/*112 */     default:                                                                 // 0.0
/*114 */         /* we shouldn't be signaling hotplug events for resources            // 0.0
/*116 */          * that don't support them                                           // 0.0
/*118 */          */                                                                  // 0.0
/*120 */         g_assert(false);                                                     // 0.0
/*122 */         return;                                                              // 0.0
/*124 */     }                                                                        // 0.0
/*128 */     if (hp_id == RTAS_LOG_V6_HP_ID_DRC_COUNT) {                              // 0.0
/*130 */         hp->drc.count = cpu_to_be32(drc);                                    // 0.0
/*132 */     } else if (hp_id == RTAS_LOG_V6_HP_ID_DRC_INDEX) {                       // 0.0
/*134 */         hp->drc.index = cpu_to_be32(drc);                                    // 0.0
/*136 */     }                                                                        // 0.0
/*140 */     rtas_event_log_queue(RTAS_LOG_TYPE_HOTPLUG, new_hp, true);               // 0.0
/*144 */     qemu_irq_pulse(xics_get_qirq(spapr->xics, spapr->check_exception_irq));  // 0.0
/*146 */ }                                                                            // 0.0
