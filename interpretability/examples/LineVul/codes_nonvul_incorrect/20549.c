// commit message qemu@465f2fedd2 (target=0, prob=0.63924444, correct=False): cryptodev: fix the check of aes algorithm
/*0   */ static int cryptodev_builtin_create_cipher_session(                      // (11) 0.03125
/*2   */                     CryptoDevBackendBuiltin *builtin,                    // (5) 0.05664
/*4   */                     CryptoDevBackendSymSessionInfo *sess_info,           // (4) 0.0625
/*6   */                     Error **errp)                                        // (8) 0.04688
/*8   */ {                                                                        // (24) 0.001953
/*10  */     int algo;                                                            // (19) 0.01367
/*12  */     int mode;                                                            // (21) 0.01172
/*14  */     QCryptoCipher *cipher;                                               // (15) 0.02344
/*16  */     int index;                                                           // (20) 0.01172
/*18  */     CryptoDevBackendBuiltinSession *sess;                                // (14) 0.02734
/*22  */     if (sess_info->op_type != VIRTIO_CRYPTO_SYM_OP_CIPHER) {             // (3) 0.0625
/*24  */         error_setg(errp, "Unsupported optype :%u", sess_info->op_type);  // (2) 0.06445
/*26  */         return -1;                                                       // (16) 0.02148
/*28  */     }                                                                    // (22) 0.007812
/*32  */     index = cryptodev_builtin_get_unused_session_index(builtin);         // (9) 0.04687
/*34  */     if (index < 0) {                                                     // (18) 0.01953
/*36  */         error_setg(errp, "Total number of sessions created exceeds %u",  // (6) 0.04883
/*38  */                   MAX_NUM_SESSIONS);                                     // (7) 0.04883
/*40  */         return -1;                                                       // (17) 0.02148
/*42  */     }                                                                    // (23) 0.007812
/*46  */     switch (sess_info->cipher_alg) {                                     // (12) 0.03125
/*48  */     case VIRTIO_CRYPTO_CIPHER_AES_ECB:                                   // (10) 0.04297
/*50  */         algo = cryptodev_builtin_get_aes_algo(sess_info->key_len,        // (1) 0.06641
/*52  */                                                           errp);         // (0) 0.1172
/*54  */         if (algo < 0)  {                                                 // (13) 0.03125
/*56  */             return -1;                                                   // 0.0
/*58  */         }                                                                // 0.0
/*60  */         mode = QCRYPTO_CIPHER_MODE_ECB;                                  // 0.0
/*62  */         break;                                                           // 0.0
/*64  */     case VIRTIO_CRYPTO_CIPHER_AES_CBC:                                   // 0.0
/*66  */         algo = cryptodev_builtin_get_aes_algo(sess_info->key_len,        // 0.0
/*68  */                                                           errp);         // 0.0
/*70  */         if (algo < 0)  {                                                 // 0.0
/*72  */             return -1;                                                   // 0.0
/*74  */         }                                                                // 0.0
/*76  */         mode = QCRYPTO_CIPHER_MODE_CBC;                                  // 0.0
/*78  */         break;                                                           // 0.0
/*80  */     case VIRTIO_CRYPTO_CIPHER_AES_CTR:                                   // 0.0
/*82  */         algo = cryptodev_builtin_get_aes_algo(sess_info->key_len,        // 0.0
/*84  */                                                           errp);         // 0.0
/*86  */         if (algo < 0)  {                                                 // 0.0
/*88  */             return -1;                                                   // 0.0
/*90  */         }                                                                // 0.0
/*92  */         mode = QCRYPTO_CIPHER_MODE_CTR;                                  // 0.0
/*94  */         break;                                                           // 0.0
/*96  */     case VIRTIO_CRYPTO_CIPHER_DES_ECB:                                   // 0.0
/*98  */         algo = QCRYPTO_CIPHER_ALG_DES_RFB;                               // 0.0
/*100 */         mode = QCRYPTO_CIPHER_MODE_ECB;                                  // 0.0
/*102 */         break;                                                           // 0.0
/*104 */     default:                                                             // 0.0
/*106 */         error_setg(errp, "Unsupported cipher alg :%u",                   // 0.0
/*108 */                    sess_info->cipher_alg);                               // 0.0
/*110 */         return -1;                                                       // 0.0
/*112 */     }                                                                    // 0.0
/*116 */     cipher = qcrypto_cipher_new(algo, mode,                              // 0.0
/*118 */                                sess_info->cipher_key,                    // 0.0
/*120 */                                sess_info->key_len,                       // 0.0
/*122 */                                errp);                                    // 0.0
/*124 */     if (!cipher) {                                                       // 0.0
/*126 */         return -1;                                                       // 0.0
/*128 */     }                                                                    // 0.0
/*132 */     sess = g_new0(CryptoDevBackendBuiltinSession, 1);                    // 0.0
/*134 */     sess->cipher = cipher;                                               // 0.0
/*136 */     sess->direction = sess_info->direction;                              // 0.0
/*138 */     sess->type = sess_info->op_type;                                     // 0.0
/*142 */     builtin->sessions[index] = sess;                                     // 0.0
/*146 */     return index;                                                        // 0.0
/*148 */ }                                                                        // 0.0
