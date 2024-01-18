// commit message qemu@5fb6c7a8b2 (target=0, prob=0.5781271, correct=False): Move TLS auth into separate file ("Daniel P. Berrange")
/*0 */ static void vnc_flush(VncState *vs)  // (0) 0.2889
/*2 */ {                                    // (3) 0.02222
/*4 */     if (vs->output.offset)           // (1) 0.2444
/*6 */ 	vnc_client_write(vs);               // (2) 0.2222
/*8 */ }                                    // (4) 0.02222
