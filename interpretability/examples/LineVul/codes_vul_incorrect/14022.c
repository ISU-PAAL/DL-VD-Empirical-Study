// commit message qemu@01b05c66a3 (target=1, prob=0.36147895, correct=False): nbd/client: Don't hard-disconnect on ESHUTDOWN from server
/*0  */ int nbd_receive_reply(QIOChannel *ioc, NBDReply *reply, Error **errp)             // (4) 0.05273
/*2  */ {                                                                                 // (24) 0.001953
/*4  */     int ret;                                                                      // (22) 0.01172
/*6  */     const char *type;                                                             // (19) 0.01563
/*10 */     ret = nbd_read_eof(ioc, &reply->magic, sizeof(reply->magic), errp);           // (2) 0.05859
/*12 */     if (ret <= 0) {                                                               // (16) 0.01953
/*14 */         return ret;                                                               // (17) 0.01953
/*16 */     }                                                                             // (23) 0.007812
/*20 */     be32_to_cpus(&reply->magic);                                                  // (12) 0.0293
/*24 */     switch (reply->magic) {                                                       // (15) 0.01953
/*26 */     case NBD_SIMPLE_REPLY_MAGIC:                                                  // (10) 0.0332
/*28 */         ret = nbd_receive_simple_reply(ioc, &reply->simple, errp);                // (3) 0.05859
/*30 */         if (ret < 0) {                                                            // (13) 0.02734
/*32 */             break;                                                                // (14) 0.02539
/*34 */         }                                                                         // (20) 0.01562
/*38 */         trace_nbd_receive_simple_reply(reply->simple.error,                       // (6) 0.04883
/*40 */                                        nbd_err_lookup(reply->simple.error),       // (0) 0.1016
/*42 */                                        reply->handle);                            // (1) 0.08203
/*44 */         if (reply->simple.error == NBD_ESHUTDOWN) {                               // (8) 0.04492
/*46 */             /* This works even on mingw which lacks a native ESHUTDOWN */         // (5) 0.05273
/*48 */             error_setg(errp, "server shutting down");                             // (7) 0.04687
/*50 */             return -EINVAL;                                                       // (11) 0.0332
/*52 */         }                                                                         // (21) 0.01562
/*54 */         break;                                                                    // (18) 0.01758
/*56 */     case NBD_STRUCTURED_REPLY_MAGIC:                                              // (9) 0.03516
/*58 */         ret = nbd_receive_structured_reply_chunk(ioc, &reply->structured, errp);  // 0.0
/*60 */         if (ret < 0) {                                                            // 0.0
/*62 */             break;                                                                // 0.0
/*64 */         }                                                                         // 0.0
/*66 */         type = nbd_reply_type_lookup(reply->structured.type);                     // 0.0
/*68 */         trace_nbd_receive_structured_reply_chunk(reply->structured.flags,         // 0.0
/*70 */                                                  reply->structured.type, type,    // 0.0
/*72 */                                                  reply->structured.handle,        // 0.0
/*74 */                                                  reply->structured.length);       // 0.0
/*76 */         break;                                                                    // 0.0
/*78 */     default:                                                                      // 0.0
/*80 */         error_setg(errp, "invalid magic (got 0x%" PRIx32 ")", reply->magic);      // 0.0
/*82 */         return -EINVAL;                                                           // 0.0
/*84 */     }                                                                             // 0.0
/*86 */     if (ret < 0) {                                                                // 0.0
/*88 */         return ret;                                                               // 0.0
/*90 */     }                                                                             // 0.0
/*94 */     return 1;                                                                     // 0.0
/*96 */ }                                                                                 // 0.0
