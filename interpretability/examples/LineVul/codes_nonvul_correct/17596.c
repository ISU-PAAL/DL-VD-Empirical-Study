// commit message qemu@3b098d5697 (target=0, prob=0.4344448, correct=True): qapi: Add new visit_complete() function
/*0  */ static void visitor_output_setup_internal(TestOutputVisitorData *data,  // (2) 0.1233
/*2  */                                           bool human)                   // (0) 0.3014
/*4  */ {                                                                       // (7) 0.006849
/*6  */     data->human = human;                                                // (6) 0.06164
/*8  */     data->sov = string_output_visitor_new(human);                       // (3) 0.1233
/*10 */     g_assert(data->sov);                                                // (4) 0.07534
/*12 */     data->ov = string_output_get_visitor(data->sov);                    // (1) 0.137
/*14 */     g_assert(data->ov);                                                 // (5) 0.07534
/*16 */ }                                                                       // (8) 0.006849
