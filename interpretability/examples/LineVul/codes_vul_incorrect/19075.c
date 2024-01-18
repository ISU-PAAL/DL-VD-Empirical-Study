// commit message qemu@129c7d1c53 (target=1, prob=0.39355627, correct=False): block: Document -drive problematic code and bugs
/*0  */ static InetSocketAddress *ssh_config(QDict *options, Error **errp)  // (4) 0.05691
/*2  */ {                                                                   // (26) 0.00271
/*4  */     InetSocketAddress *inet = NULL;                                 // (10) 0.03252
/*6  */     QDict *addr = NULL;                                             // (12) 0.02981
/*8  */     QObject *crumpled_addr = NULL;                                  // (8) 0.03794
/*10 */     Visitor *iv = NULL;                                             // (14) 0.0271
/*12 */     Error *local_error = NULL;                                      // (13) 0.02981
/*16 */     qdict_extract_subqdict(options, &addr, "server.");              // (1) 0.05962
/*18 */     if (!qdict_size(addr)) {                                        // (9) 0.03523
/*20 */         error_setg(errp, "SSH server address missing");             // (2) 0.05962
/*22 */         goto out;                                                   // (17) 0.0271
/*24 */     }                                                               // (23) 0.01084
/*28 */     crumpled_addr = qdict_crumple(addr, errp);                      // (5) 0.05691
/*30 */     if (!crumpled_addr) {                                           // (11) 0.03252
/*32 */         goto out;                                                   // (15) 0.0271
/*34 */     }                                                               // (22) 0.01084
/*46 */     iv = qobject_input_visitor_new(crumpled_addr);                  // (3) 0.05691
/*48 */     visit_type_InetSocketAddress(iv, NULL, &inet, &local_error);    // (0) 0.06504
/*50 */     if (local_error) {                                              // (18) 0.0271
/*52 */         error_propagate(errp, local_error);                         // (6) 0.05149
/*54 */         goto out;                                                   // (16) 0.0271
/*56 */     }                                                               // (24) 0.01084
/*60 */ out:                                                                // (25) 0.00542
/*62 */     QDECREF(addr);                                                  // (20) 0.02439
/*64 */     qobject_decref(crumpled_addr);                                  // (7) 0.04065
/*66 */     visit_free(iv);                                                 // (19) 0.02439
/*68 */     return inet;                                                    // (21) 0.01897
/*70 */ }                                                                   // (27) 0.00271
