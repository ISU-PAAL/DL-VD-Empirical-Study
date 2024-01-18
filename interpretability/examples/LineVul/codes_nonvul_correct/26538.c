// commit message qemu@d492a75cfe (target=0, prob=0.25963345, correct=True): spapr_events: use QTAILQ_FOREACH_SAFE() in spapr_clear_pending_events()
/*0  */ void spapr_clear_pending_events(sPAPRMachineState *spapr)    // (2) 0.1597
/*2  */ {                                                            // (7) 0.006944
/*4  */     sPAPREventLogEntry *entry = NULL;                        // (4) 0.1042
/*8  */     QTAILQ_FOREACH(entry, &spapr->pending_events, next) {    // (1) 0.1806
/*10 */         QTAILQ_REMOVE(&spapr->pending_events, entry, next);  // (0) 0.2014
/*12 */         g_free(entry->extended_log);                         // (3) 0.125
/*14 */         g_free(entry);                                       // (5) 0.09028
/*16 */     }                                                        // (6) 0.02778
/*18 */ }                                                            // (8) 0.006944
