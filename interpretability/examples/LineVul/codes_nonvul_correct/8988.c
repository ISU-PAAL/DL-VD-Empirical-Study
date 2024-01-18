// commit message qemu@3736cc5be3 (target=0, prob=0.2780244, correct=True): nbd: Expose and debug more NBD constants
/*0   */ static int nbd_negotiate_options(NBDClient *client, Error **errp)                // (6) 0.04297
/*2   */ {                                                                                // (28) 0.001953
/*4   */     uint32_t flags;                                                              // (23) 0.01758
/*6   */     bool fixedNewstyle = false;                                                  // (22) 0.01953
/*10  */     /* Client sends:                                                             // (24) 0.01367
/*12  */         [ 0 ..   3]   client flags                                               // (13) 0.03516
/*16  */         [ 0 ..   7]   NBD_OPTS_MAGIC                                             // (2) 0.04688
/*18  */         [ 8 ..  11]   NBD option                                                 // (14) 0.03516
/*20  */         [12 ..  15]   Data length                                                // (15) 0.0332
/*22  */         ...           Rest of request                                            // (7) 0.04102
/*26  */         [ 0 ..   7]   NBD_OPTS_MAGIC                                             // (3) 0.04688
/*28  */         [ 8 ..  11]   Second NBD option                                          // (12) 0.03711
/*30  */         [12 ..  15]   Data length                                                // (16) 0.0332
/*32  */         ...           Rest of request                                            // (8) 0.04102
/*34  */     */                                                                           // (25) 0.007812
/*38  */     if (nbd_read(client->ioc, &flags, sizeof(flags), errp) < 0) {                // (0) 0.05664
/*40  */         error_prepend(errp, "read failed: ");                                    // (9) 0.04102
/*42  */         return -EIO;                                                             // (21) 0.02344
/*44  */     }                                                                            // (26) 0.007812
/*46  */     trace_nbd_negotiate_options_flags();                                         // (17) 0.03125
/*48  */     be32_to_cpus(&flags);                                                        // (19) 0.02539
/*50  */     if (flags & NBD_FLAG_C_FIXED_NEWSTYLE) {                                     // (4) 0.04492
/*52  */         trace_nbd_negotiate_options_newstyle();                                  // (10) 0.04102
/*54  */         fixedNewstyle = true;                                                    // (20) 0.02539
/*56  */         flags &= ~NBD_FLAG_C_FIXED_NEWSTYLE;                                     // (1) 0.05078
/*58  */     }                                                                            // (27) 0.007812
/*60  */     if (flags & NBD_FLAG_C_NO_ZEROES) {                                          // (11) 0.04102
/*62  */         trace_nbd_negotiate_options_no_zeroes();                                 // (5) 0.04492
/*64  */         client->no_zeroes = true;                                                // (18) 0.03125
/*66  */         flags &= ~NBD_FLAG_C_NO_ZEROES;                                          // 0.0
/*68  */     }                                                                            // 0.0
/*70  */     if (flags != 0) {                                                            // 0.0
/*72  */         error_setg(errp, "Unknown client flags 0x%" PRIx32 " received", flags);  // 0.0
/*74  */         return -EIO;                                                             // 0.0
/*76  */     }                                                                            // 0.0
/*80  */     while (1) {                                                                  // 0.0
/*82  */         int ret;                                                                 // 0.0
/*84  */         uint32_t option, length;                                                 // 0.0
/*86  */         uint64_t magic;                                                          // 0.0
/*90  */         if (nbd_read(client->ioc, &magic, sizeof(magic), errp) < 0) {            // 0.0
/*92  */             error_prepend(errp, "read failed: ");                                // 0.0
/*94  */             return -EINVAL;                                                      // 0.0
/*96  */         }                                                                        // 0.0
/*98  */         magic = be64_to_cpu(magic);                                              // 0.0
/*100 */         trace_nbd_negotiate_options_check_magic(magic);                          // 0.0
/*102 */         if (magic != NBD_OPTS_MAGIC) {                                           // 0.0
/*104 */             error_setg(errp, "Bad magic received");                              // 0.0
/*106 */             return -EINVAL;                                                      // 0.0
/*108 */         }                                                                        // 0.0
/*112 */         if (nbd_read(client->ioc, &option,                                       // 0.0
/*114 */                      sizeof(option), errp) < 0) {                                // 0.0
/*116 */             error_prepend(errp, "read failed: ");                                // 0.0
/*118 */             return -EINVAL;                                                      // 0.0
/*120 */         }                                                                        // 0.0
/*122 */         option = be32_to_cpu(option);                                            // 0.0
/*126 */         if (nbd_read(client->ioc, &length, sizeof(length), errp) < 0) {          // 0.0
/*128 */             error_prepend(errp, "read failed: ");                                // 0.0
/*130 */             return -EINVAL;                                                      // 0.0
/*132 */         }                                                                        // 0.0
/*134 */         length = be32_to_cpu(length);                                            // 0.0
/*138 */         trace_nbd_negotiate_options_check_option(option);                        // 0.0
/*140 */         if (client->tlscreds &&                                                  // 0.0
/*142 */             client->ioc == (QIOChannel *)client->sioc) {                         // 0.0
/*144 */             QIOChannel *tioc;                                                    // 0.0
/*146 */             if (!fixedNewstyle) {                                                // 0.0
/*148 */                 error_setg(errp, "Unsupported option 0x%" PRIx32, option);       // 0.0
/*150 */                 return -EINVAL;                                                  // 0.0
/*152 */             }                                                                    // 0.0
/*154 */             switch (option) {                                                    // 0.0
/*156 */             case NBD_OPT_STARTTLS:                                               // 0.0
/*158 */                 tioc = nbd_negotiate_handle_starttls(client, length, errp);      // 0.0
/*160 */                 if (!tioc) {                                                     // 0.0
/*162 */                     return -EIO;                                                 // 0.0
/*164 */                 }                                                                // 0.0
/*166 */                 object_unref(OBJECT(client->ioc));                               // 0.0
/*168 */                 client->ioc = QIO_CHANNEL(tioc);                                 // 0.0
/*170 */                 break;                                                           // 0.0
/*174 */             case NBD_OPT_EXPORT_NAME:                                            // 0.0
/*176 */                 /* No way to return an error to client, so drop connection */    // 0.0
/*178 */                 error_setg(errp, "Option 0x%x not permitted before TLS",         // 0.0
/*180 */                            option);                                              // 0.0
/*182 */                 return -EINVAL;                                                  // 0.0
/*186 */             default:                                                             // 0.0
/*188 */                 if (nbd_drop(client->ioc, length, errp) < 0) {                   // 0.0
/*190 */                     return -EIO;                                                 // 0.0
/*192 */                 }                                                                // 0.0
/*194 */                 ret = nbd_negotiate_send_rep_err(client->ioc,                    // 0.0
/*196 */                                                  NBD_REP_ERR_TLS_REQD,           // 0.0
/*198 */                                                  option, errp,                   // 0.0
/*200 */                                                  "Option 0x%" PRIx32             // 0.0
/*202 */                                                  "not permitted before TLS",     // 0.0
/*204 */                                                  option);                        // 0.0
/*206 */                 if (ret < 0) {                                                   // 0.0
/*208 */                     return ret;                                                  // 0.0
/*210 */                 }                                                                // 0.0
/*212 */                 /* Let the client keep trying, unless they asked to              // 0.0
/*214 */                  * quit. In this mode, we've already sent an error, so           // 0.0
/*216 */                  * we can't ack the abort.  */                                   // 0.0
/*218 */                 if (option == NBD_OPT_ABORT) {                                   // 0.0
/*220 */                     return 1;                                                    // 0.0
/*222 */                 }                                                                // 0.0
/*224 */                 break;                                                           // 0.0
/*226 */             }                                                                    // 0.0
/*228 */         } else if (fixedNewstyle) {                                              // 0.0
/*230 */             switch (option) {                                                    // 0.0
/*232 */             case NBD_OPT_LIST:                                                   // 0.0
/*234 */                 ret = nbd_negotiate_handle_list(client, length, errp);           // 0.0
/*236 */                 if (ret < 0) {                                                   // 0.0
/*238 */                     return ret;                                                  // 0.0
/*240 */                 }                                                                // 0.0
/*242 */                 break;                                                           // 0.0
/*246 */             case NBD_OPT_ABORT:                                                  // 0.0
/*248 */                 /* NBD spec says we must try to reply before                     // 0.0
/*250 */                  * disconnecting, but that we must also tolerate                 // 0.0
/*252 */                  * guests that don't wait for our reply. */                      // 0.0
/*254 */                 nbd_negotiate_send_rep(client->ioc, NBD_REP_ACK, option, NULL);  // 0.0
/*256 */                 return 1;                                                        // 0.0
/*260 */             case NBD_OPT_EXPORT_NAME:                                            // 0.0
/*262 */                 return nbd_negotiate_handle_export_name(client, length, errp);   // 0.0
/*266 */             case NBD_OPT_STARTTLS:                                               // 0.0
/*268 */                 if (nbd_drop(client->ioc, length, errp) < 0) {                   // 0.0
/*270 */                     return -EIO;                                                 // 0.0
/*272 */                 }                                                                // 0.0
/*274 */                 if (client->tlscreds) {                                          // 0.0
/*276 */                     ret = nbd_negotiate_send_rep_err(client->ioc,                // 0.0
/*278 */                                                      NBD_REP_ERR_INVALID,        // 0.0
/*280 */                                                      option, errp,               // 0.0
/*282 */                                                      "TLS already enabled");     // 0.0
/*284 */                 } else {                                                         // 0.0
/*286 */                     ret = nbd_negotiate_send_rep_err(client->ioc,                // 0.0
/*288 */                                                      NBD_REP_ERR_POLICY,         // 0.0
/*290 */                                                      option, errp,               // 0.0
/*292 */                                                      "TLS not configured");      // 0.0
/*294 */                 }                                                                // 0.0
/*296 */                 if (ret < 0) {                                                   // 0.0
/*298 */                     return ret;                                                  // 0.0
/*300 */                 }                                                                // 0.0
/*302 */                 break;                                                           // 0.0
/*304 */             default:                                                             // 0.0
/*306 */                 if (nbd_drop(client->ioc, length, errp) < 0) {                   // 0.0
/*308 */                     return -EIO;                                                 // 0.0
/*310 */                 }                                                                // 0.0
/*312 */                 ret = nbd_negotiate_send_rep_err(client->ioc,                    // 0.0
/*314 */                                                  NBD_REP_ERR_UNSUP,              // 0.0
/*316 */                                                  option, errp,                   // 0.0
/*318 */                                                  "Unsupported option 0x%"        // 0.0
/*320 */                                                  PRIx32,                         // 0.0
/*322 */                                                  option);                        // 0.0
/*324 */                 if (ret < 0) {                                                   // 0.0
/*326 */                     return ret;                                                  // 0.0
/*328 */                 }                                                                // 0.0
/*330 */                 break;                                                           // 0.0
/*332 */             }                                                                    // 0.0
/*334 */         } else {                                                                 // 0.0
/*336 */             /*                                                                   // 0.0
/*338 */              * If broken new-style we should drop the connection                 // 0.0
/*340 */              * for anything except NBD_OPT_EXPORT_NAME                           // 0.0
/*342 */              */                                                                  // 0.0
/*344 */             switch (option) {                                                    // 0.0
/*346 */             case NBD_OPT_EXPORT_NAME:                                            // 0.0
/*348 */                 return nbd_negotiate_handle_export_name(client, length, errp);   // 0.0
/*352 */             default:                                                             // 0.0
/*354 */                 error_setg(errp, "Unsupported option 0x%" PRIx32, option);       // 0.0
/*356 */                 return -EINVAL;                                                  // 0.0
/*358 */             }                                                                    // 0.0
/*360 */         }                                                                        // 0.0
/*362 */     }                                                                            // 0.0
/*364 */ }                                                                                // 0.0
