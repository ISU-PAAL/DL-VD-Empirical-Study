// commit message qemu@79853e18d9 (target=0, prob=0.19746256, correct=True): spapr_events: event-scan RTAS interface
/*0   */ static void spapr_hotplug_req_event(sPAPRDRConnector *drc, uint8_t hp_action)  // (3) 0.06055
/*2   */ {                                                                              // (19) 0.001953
/*4   */     struct hp_log_full *new_hp;                                                // (14) 0.02734
/*6   */     struct rtas_error_log *hdr;                                                // (13) 0.0293
/*8   */     struct rtas_event_log_v6 *v6hdr;                                           // (10) 0.03906
/*10  */     struct rtas_event_log_v6_maina *maina;                                     // (8) 0.04102
/*12  */     struct rtas_event_log_v6_mainb *mainb;                                     // (9) 0.04102
/*14  */     struct rtas_event_log_v6_hp *hp;                                           // (11) 0.03711
/*16  */     sPAPRDRConnectorClass *drck = SPAPR_DR_CONNECTOR_GET_CLASS(drc);           // (4) 0.06055
/*18  */     sPAPRDRConnectorType drc_type = drck->get_type(drc);                       // (5) 0.04883
/*22  */     new_hp = g_malloc0(sizeof(struct hp_log_full));                            // (6) 0.04492
/*24  */     hdr = &new_hp->hdr;                                                        // (15) 0.02734
/*26  */     v6hdr = &new_hp->v6hdr;                                                    // (12) 0.03516
/*28  */     maina = &new_hp->maina;                                                    // (16) 0.02734
/*30  */     mainb = &new_hp->mainb;                                                    // (17) 0.02734
/*32  */     hp = &new_hp->hp;                                                          // (18) 0.02344
/*36  */     hdr->summary = cpu_to_be32(RTAS_LOG_VERSION_6                              // (7) 0.04492
/*38  */                                | RTAS_LOG_SEVERITY_EVENT                       // (2) 0.08203
/*40  */                                | RTAS_LOG_DISPOSITION_NOT_RECOVERED            // (0) 0.08984
/*42  */                                | RTAS_LOG_OPTIONAL_PART_PRESENT                // (1) 0.08594
/*44  */                                | RTAS_LOG_INITIATOR_HOTPLUG                    // 0.0
/*46  */                                | RTAS_LOG_TYPE_HOTPLUG);                       // 0.0
/*48  */     hdr->extended_length = cpu_to_be32(sizeof(*new_hp)                         // 0.0
/*50  */                                        - sizeof(new_hp->hdr));                 // 0.0
/*54  */     spapr_init_v6hdr(v6hdr);                                                   // 0.0
/*56  */     spapr_init_maina(maina, 3 /* Main-A, Main-B, HP */);                       // 0.0
/*60  */     mainb->hdr.section_id = cpu_to_be16(RTAS_LOG_V6_SECTION_ID_MAINB);         // 0.0
/*62  */     mainb->hdr.section_length = cpu_to_be16(sizeof(*mainb));                   // 0.0
/*64  */     mainb->subsystem_id = 0x80; /* External environment */                     // 0.0
/*66  */     mainb->event_severity = 0x00; /* Informational / non-error */              // 0.0
/*68  */     mainb->event_subtype = 0x00; /* Normal shutdown */                         // 0.0
/*72  */     hp->hdr.section_id = cpu_to_be16(RTAS_LOG_V6_SECTION_ID_HOTPLUG);          // 0.0
/*74  */     hp->hdr.section_length = cpu_to_be16(sizeof(*hp));                         // 0.0
/*76  */     hp->hdr.section_version = 1; /* includes extended modifier */              // 0.0
/*78  */     hp->hotplug_action = hp_action;                                            // 0.0
/*84  */     switch (drc_type) {                                                        // 0.0
/*86  */     case SPAPR_DR_CONNECTOR_TYPE_PCI:                                          // 0.0
/*88  */         hp->drc.index = cpu_to_be32(drck->get_index(drc));                     // 0.0
/*90  */         hp->hotplug_identifier = RTAS_LOG_V6_HP_ID_DRC_INDEX;                  // 0.0
/*92  */         hp->hotplug_type = RTAS_LOG_V6_HP_TYPE_PCI;                            // 0.0
/*94  */         break;                                                                 // 0.0
/*96  */     default:                                                                   // 0.0
/*98  */         /* we shouldn't be signaling hotplug events for resources              // 0.0
/*100 */          * that don't support them                                             // 0.0
/*102 */          */                                                                    // 0.0
/*104 */         g_assert(false);                                                       // 0.0
/*106 */         return;                                                                // 0.0
/*108 */     }                                                                          // 0.0
/*112 */     rtas_event_log_queue(RTAS_LOG_TYPE_HOTPLUG, new_hp);                       // 0.0
/*116 */     qemu_irq_pulse(xics_get_qirq(spapr->icp, spapr->check_exception_irq));     // 0.0
/*118 */ }                                                                              // 0.0
