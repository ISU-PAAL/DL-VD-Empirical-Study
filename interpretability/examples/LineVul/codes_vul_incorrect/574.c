// commit message qemu@635db18f68 (target=1, prob=0.19435847, correct=False): qmp: Clean up how we enforce capability negotiation
/*0  */ CommandInfoList *qmp_query_commands(Error **errp)                   // (1) 0.2237
/*2  */ {                                                                   // (4) 0.01316
/*4  */     CommandInfoList *list = NULL;                                   // (2) 0.1447
/*8  */     qmp_for_each_command(&qmp_commands, query_commands_cb, &list);  // (0) 0.3684
/*12 */     return list;                                                    // (3) 0.07895
/*14 */ }                                                                   // (5) 0.01316
