// commit message qemu@5fb6c7a8b2 (target=0, prob=0.4788116, correct=True): Move TLS auth into separate file ("Daniel P. Berrange")
/*0   */ static int vnc_validate_certificate(struct VncState *vs)                            // (8) 0.03516
/*2   */ {                                                                                   // (32) 0.001953
/*4   */     int ret;                                                                        // (22) 0.01172
/*6   */     unsigned int status;                                                            // (21) 0.01367
/*8   */     const gnutls_datum_t *certs;                                                    // (13) 0.03125
/*10  */     unsigned int nCerts, i;                                                         // (17) 0.02148
/*12  */     time_t now;                                                                     // (20) 0.01562
/*16  */     VNC_DEBUG("Validating client certificate\n");                                   // (15) 0.0293
/*18  */     if ((ret = gnutls_certificate_verify_peers2 (vs->tls_session, &status)) < 0) {  // (0) 0.06836
/*20  */ 	VNC_DEBUG("Verify failed %s\n", gnutls_strerror(ret));                             // (3) 0.04688
/*22  */ 	return -1;                                                                         // (25) 0.009766
/*24  */     }                                                                               // (30) 0.007812
/*28  */     if ((now = time(NULL)) == ((time_t)-1)) {                                       // (6) 0.03906
/*30  */ 	return -1;                                                                         // (26) 0.009766
/*32  */     }                                                                               // (29) 0.007813
/*36  */     if (status != 0) {                                                              // (19) 0.01953
/*38  */ 	if (status & GNUTLS_CERT_INVALID)                                                  // (14) 0.03125
/*40  */ 	    VNC_DEBUG("The certificate is not trusted.\n");                                // (10) 0.03516
/*44  */ 	if (status & GNUTLS_CERT_SIGNER_NOT_FOUND)                                         // (7) 0.03906
/*46  */ 	    VNC_DEBUG("The certificate hasn't got a known issuer.\n");                     // (5) 0.04102
/*50  */ 	if (status & GNUTLS_CERT_REVOKED)                                                  // (12) 0.0332
/*52  */ 	    VNC_DEBUG("The certificate has been revoked.\n");                              // (9) 0.03516
/*56  */ 	if (status & GNUTLS_CERT_INSECURE_ALGORITHM)                                       // (4) 0.04297
/*58  */ 	    VNC_DEBUG("The certificate uses an insecure algorithm\n");                     // (11) 0.03516
/*62  */ 	return -1;                                                                         // (27) 0.009766
/*64  */     } else {                                                                        // (23) 0.01172
/*66  */ 	VNC_DEBUG("Certificate is valid!\n");                                              // (16) 0.02734
/*68  */     }                                                                               // (31) 0.007812
/*72  */     /* Only support x509 for now */                                                 // (18) 0.02148
/*74  */     if (gnutls_certificate_type_get(vs->tls_session) != GNUTLS_CRT_X509)            // (1) 0.06641
/*76  */ 	return -1;                                                                         // (28) 0.009766
/*80  */     if (!(certs = gnutls_certificate_get_peers(vs->tls_session, &nCerts)))          // (2) 0.06445
/*82  */ 	return -1;                                                                         // (24) 0.009766
/*86  */     for (i = 0 ; i < nCerts ; i++) {                                                // 0.0
/*88  */ 	gnutls_x509_crt_t cert;                                                            // 0.0
/*90  */ 	VNC_DEBUG ("Checking certificate chain %d\n", i);                                  // 0.0
/*92  */ 	if (gnutls_x509_crt_init (&cert) < 0)                                              // 0.0
/*94  */ 	    return -1;                                                                     // 0.0
/*98  */ 	if (gnutls_x509_crt_import(cert, &certs[i], GNUTLS_X509_FMT_DER) < 0) {            // 0.0
/*100 */ 	    gnutls_x509_crt_deinit (cert);                                                 // 0.0
/*102 */ 	    return -1;                                                                     // 0.0
/*104 */ 	}                                                                                  // 0.0
/*108 */ 	if (gnutls_x509_crt_get_expiration_time (cert) < now) {                            // 0.0
/*110 */ 	    VNC_DEBUG("The certificate has expired\n");                                    // 0.0
/*112 */ 	    gnutls_x509_crt_deinit (cert);                                                 // 0.0
/*114 */ 	    return -1;                                                                     // 0.0
/*116 */ 	}                                                                                  // 0.0
/*120 */ 	if (gnutls_x509_crt_get_activation_time (cert) > now) {                            // 0.0
/*122 */ 	    VNC_DEBUG("The certificate is not yet activated\n");                           // 0.0
/*124 */ 	    gnutls_x509_crt_deinit (cert);                                                 // 0.0
/*126 */ 	    return -1;                                                                     // 0.0
/*128 */ 	}                                                                                  // 0.0
/*132 */ 	if (gnutls_x509_crt_get_activation_time (cert) > now) {                            // 0.0
/*134 */ 	    VNC_DEBUG("The certificate is not yet activated\n");                           // 0.0
/*136 */ 	    gnutls_x509_crt_deinit (cert);                                                 // 0.0
/*138 */ 	    return -1;                                                                     // 0.0
/*140 */ 	}                                                                                  // 0.0
/*144 */ 	gnutls_x509_crt_deinit (cert);                                                     // 0.0
/*146 */     }                                                                               // 0.0
/*150 */     return 0;                                                                       // 0.0
/*152 */ }                                                                                   // 0.0
