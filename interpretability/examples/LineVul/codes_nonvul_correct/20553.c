// commit message qemu@72cf2d4f0e (target=0, prob=0.11567662, correct=True): Fix sys-queue.h conflict for good
/*0  */ envlist_free(envlist_t *envlist)                 // (3) 0.1024
/*2  */ {                                                // (10) 0.007874
/*4  */ 	struct envlist_entry *entry;                    // (5) 0.07087
/*8  */ 	assert(envlist != NULL);                        // (6) 0.06299
/*12 */ 	while (envlist->el_entries.lh_first != NULL) {  // (0) 0.1496
/*14 */ 		entry = envlist->el_entries.lh_first;          // (1) 0.1339
/*16 */ 		LIST_REMOVE(entry, ev_link);                   // (2) 0.1102
/*20 */ 		free((char *)entry->ev_var);                   // (4) 0.09449
/*22 */ 		free(entry);                                   // (7) 0.04724
/*24 */ 	}                                               // (9) 0.01575
/*26 */ 	free(envlist);                                  // (8) 0.04724
/*28 */ }                                                // (11) 0.007874
