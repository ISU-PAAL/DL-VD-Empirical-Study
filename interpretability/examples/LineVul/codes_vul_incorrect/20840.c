// commit message qemu@95c3df5a24 (target=1, prob=0.0790083, correct=False): crypto: Avoid memory leak on failure
/*0  */ block_crypto_create_opts_init(QCryptoBlockFormat format,                // (8) 0.03711
/*2  */                               QemuOpts *opts,                           // (0) 0.07422
/*4  */                               Error **errp)                             // (1) 0.06641
/*6  */ {                                                                       // (29) 0.001953
/*8  */     OptsVisitor *ov;                                                    // (16) 0.01953
/*10 */     QCryptoBlockCreateOptions *ret = NULL;                              // (14) 0.02734
/*12 */     Error *local_err = NULL;                                            // (15) 0.02148
/*16 */     ret = g_new0(QCryptoBlockCreateOptions, 1);                         // (9) 0.03711
/*18 */     ret->format = format;                                               // (20) 0.01758
/*22 */     ov = opts_visitor_new(opts);                                        // (12) 0.03125
/*26 */     visit_start_struct(opts_get_visitor(ov),                            // (10) 0.03711
/*28 */                        NULL, NULL, 0, &local_err);                      // (3) 0.06445
/*30 */     if (local_err) {                                                    // (18) 0.01953
/*32 */         goto out;                                                       // (17) 0.01953
/*34 */     }                                                                   // (26) 0.007813
/*38 */     switch (format) {                                                   // (24) 0.01562
/*40 */     case Q_CRYPTO_BLOCK_FORMAT_LUKS:                                    // (7) 0.03906
/*42 */         visit_type_QCryptoBlockCreateOptionsLUKS_members(               // (6) 0.04492
/*44 */             opts_get_visitor(ov), &ret->u.luks, &local_err);            // (2) 0.06641
/*46 */         break;                                                          // (21) 0.01758
/*50 */     default:                                                            // (25) 0.009766
/*52 */         error_setg(&local_err, "Unsupported block format %d", format);  // (4) 0.05078
/*54 */         break;                                                          // (22) 0.01758
/*56 */     }                                                                   // (27) 0.007812
/*58 */     error_propagate(errp, local_err);                                   // (13) 0.0293
/*60 */     local_err = NULL;                                                   // (23) 0.01758
/*64 */     visit_end_struct(opts_get_visitor(ov), &local_err);                 // (5) 0.04688
/*68 */  out:                                                                   // (28) 0.003906
/*70 */     if (local_err) {                                                    // (19) 0.01953
/*72 */         error_propagate(errp, local_err);                               // (11) 0.03711
/*74 */         qapi_free_QCryptoBlockCreateOptions(ret);                       // 0.0
/*76 */         ret = NULL;                                                     // 0.0
/*78 */     }                                                                   // 0.0
/*80 */     opts_visitor_cleanup(ov);                                           // 0.0
/*82 */     return ret;                                                         // 0.0
/*84 */ }                                                                       // 0.0
