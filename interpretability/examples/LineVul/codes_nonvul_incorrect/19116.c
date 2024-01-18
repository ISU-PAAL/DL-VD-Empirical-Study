// commit message qemu@5fb6c7a8b2 (target=0, prob=0.85269374, correct=False): Move TLS auth into separate file ("Daniel P. Berrange")
/*0  */ static gnutls_anon_server_credentials vnc_tls_initialize_anon_cred(void)    // (1) 0.1609
/*2  */ {                                                                           // (9) 0.005747
/*4  */     gnutls_anon_server_credentials anon_cred;                               // (4) 0.1149
/*6  */     int ret;                                                                // (6) 0.03448
/*10 */     if ((ret = gnutls_anon_allocate_server_credentials(&anon_cred)) < 0) {  // (0) 0.1782
/*12 */ 	VNC_DEBUG("Cannot allocate credentials %s\n", gnutls_strerror(ret));       // (3) 0.1437
/*14 */ 	return NULL;                                                               // (7) 0.02299
/*16 */     }                                                                       // (8) 0.02299
/*20 */     gnutls_anon_set_server_dh_params(anon_cred, dh_params);                 // (2) 0.1494
/*24 */     return anon_cred;                                                       // (5) 0.05747
/*26 */ }                                                                           // (10) 0.005747
