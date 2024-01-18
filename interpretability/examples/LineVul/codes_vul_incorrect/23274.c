// commit message qemu@9366f41860 (target=1, prob=0.3021791, correct=False): Introduce v3 of savevm protocol
/*0  */ int register_savevm(const char *idstr,                        // (16) 0.024
/*2  */                     int instance_id,                          // (8) 0.048
/*4  */                     int version_id,                           // (6) 0.048
/*6  */                     SaveStateHandler *save_state,             // (2) 0.054
/*8  */                     LoadStateHandler *load_state,             // (4) 0.054
/*10 */                     void *opaque)                             // (5) 0.048
/*12 */ {                                                             // (29) 0.002
/*14 */     SaveStateEntry *se, **pse;                                // (17) 0.024
/*18 */     se = qemu_malloc(sizeof(SaveStateEntry));                 // (10) 0.038
/*20 */     if (!se)                                                  // (25) 0.014
/*22 */         return -1;                                            // (19) 0.022
/*24 */     pstrcpy(se->idstr, sizeof(se->idstr), idstr);             // (9) 0.046
/*26 */     se->instance_id = (instance_id == -1) ? 0 : instance_id;  // (7) 0.048
/*28 */     se->version_id = version_id;                              // (13) 0.026
/*30 */     se->save_state = save_state;                              // (15) 0.026
/*32 */     se->load_state = load_state;                              // (14) 0.026
/*34 */     se->opaque = opaque;                                      // (20) 0.02
/*36 */     se->next = NULL;                                          // (23) 0.018
/*40 */     /* add at the end of list */                              // (18) 0.022
/*42 */     pse = &first_se;                                          // (22) 0.02
/*44 */     while (*pse != NULL) {                                    // (21) 0.02
/*46 */         if (instance_id == -1                                 // (12) 0.03
/*48 */                 && strcmp(se->idstr, (*pse)->idstr) == 0      // (0) 0.066
/*50 */                 && se->instance_id <= (*pse)->instance_id)    // (1) 0.06
/*52 */             se->instance_id = (*pse)->instance_id + 1;        // (3) 0.054
/*54 */         pse = &(*pse)->next;                                  // (11) 0.032
/*56 */     }                                                         // (27) 0.008
/*58 */     *pse = se;                                                // (24) 0.016
/*60 */     return 0;                                                 // (26) 0.012
/*62 */ }                                                             // (28) 0.002002
