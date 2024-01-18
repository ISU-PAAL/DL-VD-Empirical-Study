// commit message qemu@e36c87667a (target=1, prob=0.060094256, correct=False): qapi: Fix memory leak
/*0  */ opts_visitor_cleanup(OptsVisitor *ov)                // (2) 0.1509
/*2  */ {                                                    // (6) 0.009434
/*4  */     if (ov->unprocessed_opts != NULL) {              // (1) 0.1604
/*6  */         g_hash_table_destroy(ov->unprocessed_opts);  // (0) 0.2264
/*8  */     }                                                // (5) 0.03774
/*10 */     g_free(ov->fake_id_opt);                         // (4) 0.1415
/*12 */     memset(ov, '\0', sizeof *ov);                    // (3) 0.1509
/*14 */ }                                                    // (7) 0.009434
