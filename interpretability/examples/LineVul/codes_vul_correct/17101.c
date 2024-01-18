// commit message qemu@0072d2a9fc (target=1, prob=0.99925464, correct=True): crypto: fix leak in ivgen essiv init
/*0  */ static int qcrypto_ivgen_essiv_init(QCryptoIVGen *ivgen,              // (9) 0.04492
/*2  */                                     const uint8_t *key, size_t nkey,  // (1) 0.0957
/*4  */                                     Error **errp)                     // (2) 0.07813
/*6  */ {                                                                     // (21) 0.001953
/*8  */     uint8_t *salt;                                                    // (16) 0.02148
/*10 */     size_t nhash;                                                     // (18) 0.01758
/*12 */     size_t nsalt;                                                     // (19) 0.01758
/*14 */     QCryptoIVGenESSIV *essiv = g_new0(QCryptoIVGenESSIV, 1);          // (5) 0.05664
/*18 */     /* Not necessarily the same as nkey */                            // (15) 0.02344
/*20 */     nsalt = qcrypto_cipher_get_key_len(ivgen->cipher);                // (7) 0.04883
/*24 */     nhash = qcrypto_hash_digest_len(ivgen->hash);                     // (11) 0.04297
/*26 */     /* Salt must be larger of hash size or key size */                // (12) 0.0293
/*28 */     salt = g_new0(uint8_t, MAX(nhash, nsalt));                        // (10) 0.04492
/*32 */     if (qcrypto_hash_bytes(ivgen->hash, (const gchar *)key, nkey,     // (6) 0.05469
/*34 */                            &salt, &nhash,                             // (3) 0.06641
/*36 */                            errp) < 0) {                               // (4) 0.06445
/*38 */         g_free(essiv);                                                // (14) 0.02734
/*41 */         return -1;                                                    // (17) 0.02148
/*43 */     }                                                                 // (20) 0.007812
/*47 */     /* Now potentially truncate salt to match cipher key len */       // (13) 0.0293
/*49 */     essiv->cipher = qcrypto_cipher_new(ivgen->cipher,                 // (8) 0.04688
/*51 */                                        QCRYPTO_CIPHER_MODE_ECB,       // (0) 0.1016
/*53 */                                        salt, MIN(nhash, nsalt),       // 0.0
/*55 */                                        errp);                         // 0.0
/*57 */     if (!essiv->cipher) {                                             // 0.0
/*59 */         g_free(essiv);                                                // 0.0
/*62 */         return -1;                                                    // 0.0
/*64 */     }                                                                 // 0.0
/*69 */     ivgen->private = essiv;                                           // 0.0
/*73 */     return 0;                                                         // 0.0
/*75 */ }                                                                     // 0.0
