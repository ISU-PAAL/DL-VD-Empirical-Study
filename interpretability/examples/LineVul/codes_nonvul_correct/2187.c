// commit message qemu@838ef60249 (target=0, prob=0.05742477, correct=True): curl: Eliminate unnecessary use of curl_multi_socket_all
/*0  */ static void curl_multi_do(void *arg)                    // (3) 0.07947
/*2  */ {                                                       // (11) 0.006623
/*4  */     BDRVCURLState *s = (BDRVCURLState *)arg;            // (2) 0.1325
/*6  */     int running;                                        // (7) 0.03974
/*8  */     int r;                                              // (8) 0.03974
/*12 */     if (!s->multi) {                                    // (5) 0.06623
/*14 */         return;                                         // (6) 0.0596
/*16 */     }                                                   // (10) 0.02649
/*20 */     do {                                                // (9) 0.03311
/*22 */         r = curl_multi_socket_all(s->multi, &running);  // (0) 0.1589
/*24 */     } while(r == CURLM_CALL_MULTI_PERFORM);             // (1) 0.1457
/*28 */     curl_multi_read(s);                                 // (4) 0.07285
/*30 */ }                                                       // (12) 0.006623
