// commit message qemu@3a661f1eab (target=1, prob=0.99922776, correct=True): crypto: add sanity checking of plaintext/ciphertext length
/*0  */ static int qcrypto_cipher_init_des_rfb(QCryptoCipher *cipher,            // (4) 0.05774
/*2  */                                        const uint8_t *key, size_t nkey,  // (0) 0.1201
/*4  */                                        Error **errp)                     // (1) 0.09931
/*6  */ {                                                                        // (18) 0.002309
/*8  */     QCryptoCipherBuiltin *ctxt;                                          // (13) 0.03233
/*12 */     if (cipher->mode != QCRYPTO_CIPHER_MODE_ECB) {                       // (5) 0.05774
/*14 */         error_setg(errp, "Unsupported cipher mode %d", cipher->mode);    // (2) 0.06236
/*16 */         return -1;                                                       // (15) 0.0254
/*18 */     }                                                                    // (17) 0.009238
/*22 */     ctxt = g_new0(QCryptoCipherBuiltin, 1);                              // (11) 0.0485
/*26 */     ctxt->state.desrfb.key = g_new0(uint8_t, nkey);                      // (3) 0.06236
/*28 */     memcpy(ctxt->state.desrfb.key, key, nkey);                           // (9) 0.05312
/*30 */     ctxt->state.desrfb.nkey = nkey;                                      // (12) 0.04157
/*35 */     ctxt->free = qcrypto_cipher_free_des_rfb;                            // (10) 0.05081
/*37 */     ctxt->setiv = qcrypto_cipher_setiv_des_rfb;                          // (6) 0.05543
/*39 */     ctxt->encrypt = qcrypto_cipher_encrypt_des_rfb;                      // (7) 0.05543
/*41 */     ctxt->decrypt = qcrypto_cipher_decrypt_des_rfb;                      // (8) 0.05543
/*45 */     cipher->opaque = ctxt;                                               // (14) 0.0254
/*49 */     return 0;                                                            // (16) 0.01386
/*51 */ }                                                                        // (19) 0.002309
