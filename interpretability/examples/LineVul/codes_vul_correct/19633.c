// commit message qemu@302d9d6fd8 (target=1, prob=0.6416082, correct=True): ui/vnc: Convert sasl.mechlist to g_malloc() & friends
/*0  */ void vnc_sasl_client_cleanup(VncState *vs)                               // (4) 0.07692
/*2  */ {                                                                        // (11) 0.004049
/*4  */     if (vs->sasl.conn) {                                                 // (9) 0.05668
/*6  */         vs->sasl.runSSF = vs->sasl.waitWriteSSF = vs->sasl.wantSSF = 0;  // (0) 0.1619
/*8  */         vs->sasl.encodedLength = vs->sasl.encodedOffset = 0;             // (1) 0.1174
/*10 */         vs->sasl.encoded = NULL;                                         // (7) 0.07287
/*12 */         g_free(vs->sasl.username);                                       // (5) 0.07692
/*14 */         free(vs->sasl.mechlist);                                         // (6) 0.07692
/*16 */         vs->sasl.username = vs->sasl.mechlist = NULL;                    // (2) 0.1093
/*18 */         sasl_dispose(&vs->sasl.conn);                                    // (3) 0.08907
/*20 */         vs->sasl.conn = NULL;                                            // (8) 0.06883
/*22 */     }                                                                    // (10) 0.01619
/*24 */ }                                                                        // (12) 0.004049
