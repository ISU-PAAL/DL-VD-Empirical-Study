// commit message qemu@8ec1440202 (target=0, prob=0.23304272, correct=True): colo-compare: compare the packet in a specified Connection
/*0  */ static void compare_sec_rs_finalize(SocketReadState *sec_rs)          // (4) 0.125
/*2  */ {                                                                     // (8) 0.006579
/*4  */     CompareState *s = container_of(sec_rs, CompareState, sec_rs);     // (1) 0.1513
/*8  */     if (packet_enqueue(s, SECONDARY_IN)) {                            // (3) 0.1316
/*10 */         trace_colo_compare_main("secondary: unsupported packet in");  // (2) 0.1447
/*12 */     } else {                                                          // (6) 0.03947
/*14 */         /* compare connection */                                      // (5) 0.07237
/*16 */         g_queue_foreach(&s->conn_list, colo_compare_connection, s);   // (0) 0.1974
/*18 */     }                                                                 // (7) 0.02632
/*20 */ }                                                                     // (9) 0.006579
