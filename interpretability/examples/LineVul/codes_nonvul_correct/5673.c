// commit message qemu@46321d6b5f (target=0, prob=0.48803997, correct=True): nbd/server: fix nbd_negotiate_handle_info
/*0   */ static int nbd_negotiate_handle_info(NBDClient *client, uint32_t length,         // (4) 0.04883
/*2   */                                      uint32_t opt, uint16_t myflags,             // (0) 0.0957
/*4   */                                      Error **errp)                               // (1) 0.08008
/*6   */ {                                                                                // (30) 0.001953
/*8   */     int rc;                                                                      // (26) 0.01172
/*10  */     char name[NBD_MAX_NAME_SIZE + 1];                                            // (9) 0.0332
/*12  */     NBDExport *exp;                                                              // (21) 0.01758
/*14  */     uint16_t requests;                                                           // (22) 0.01758
/*16  */     uint16_t request;                                                            // (23) 0.01758
/*18  */     uint32_t namelen;                                                            // (16) 0.02148
/*20  */     bool sendname = false;                                                       // (19) 0.01758
/*22  */     bool blocksize = false;                                                      // (20) 0.01758
/*24  */     uint32_t sizes[3];                                                           // (15) 0.02148
/*26  */     char buf[sizeof(uint64_t) + sizeof(uint16_t)];                               // (5) 0.04492
/*28  */     const char *msg;                                                             // (24) 0.01563
/*32  */     /* Client sends:                                                             // (25) 0.01367
/*34  */         4 bytes: L, name length (can be 0)                                       // (8) 0.03711
/*36  */         L bytes: export name                                                     // (13) 0.02344
/*38  */         2 bytes: N, number of requests (can be 0)                                // (6) 0.03906
/*40  */         N * 2 bytes: N requests                                                  // (12) 0.02734
/*42  */     */                                                                           // (27) 0.007812
/*44  */     if (length < sizeof(namelen) + sizeof(requests)) {                           // (7) 0.03906
/*46  */         msg = "overall request too short";                                       // (10) 0.03125
/*48  */         goto invalid;                                                            // (18) 0.01953
/*50  */     }                                                                            // (28) 0.007812
/*52  */     if (nbd_read(client->ioc, &namelen, sizeof(namelen), errp) < 0) {            // (2) 0.06445
/*54  */         return -EIO;                                                             // (14) 0.02344
/*56  */     }                                                                            // (29) 0.007812
/*58  */     be32_to_cpus(&namelen);                                                      // (11) 0.0293
/*60  */     length -= sizeof(namelen);                                                   // (17) 0.02148
/*62  */     if (namelen > length - sizeof(requests) || (length - namelen) % 2) {         // (3) 0.05469
/*64  */         msg = "name length is incorrect";                                        // 0.0
/*66  */         goto invalid;                                                            // 0.0
/*68  */     }                                                                            // 0.0
/*70  */     if (nbd_read(client->ioc, name, namelen, errp) < 0) {                        // 0.0
/*72  */         return -EIO;                                                             // 0.0
/*74  */     }                                                                            // 0.0
/*76  */     name[namelen] = '\0';                                                        // 0.0
/*78  */     length -= namelen;                                                           // 0.0
/*80  */     trace_nbd_negotiate_handle_export_name_request(name);                        // 0.0
/*84  */     if (nbd_read(client->ioc, &requests, sizeof(requests), errp) < 0) {          // 0.0
/*86  */         return -EIO;                                                             // 0.0
/*88  */     }                                                                            // 0.0
/*90  */     be16_to_cpus(&requests);                                                     // 0.0
/*92  */     length -= sizeof(requests);                                                  // 0.0
/*94  */     trace_nbd_negotiate_handle_info_requests(requests);                          // 0.0
/*96  */     if (requests != length / sizeof(request)) {                                  // 0.0
/*98  */         msg = "incorrect number of  requests for overall length";                // 0.0
/*100 */         goto invalid;                                                            // 0.0
/*102 */     }                                                                            // 0.0
/*104 */     while (requests--) {                                                         // 0.0
/*106 */         if (nbd_read(client->ioc, &request, sizeof(request), errp) < 0) {        // 0.0
/*108 */             return -EIO;                                                         // 0.0
/*110 */         }                                                                        // 0.0
/*112 */         be16_to_cpus(&request);                                                  // 0.0
/*114 */         length -= sizeof(request);                                               // 0.0
/*116 */         trace_nbd_negotiate_handle_info_request(request,                         // 0.0
/*118 */                                                 nbd_info_lookup(request));       // 0.0
/*120 */         /* We care about NBD_INFO_NAME and NBD_INFO_BLOCK_SIZE;                  // 0.0
/*122 */          * everything else is either a request we don't know or                  // 0.0
/*124 */          * something we send regardless of request */                            // 0.0
/*126 */         switch (request) {                                                       // 0.0
/*128 */         case NBD_INFO_NAME:                                                      // 0.0
/*130 */             sendname = true;                                                     // 0.0
/*132 */             break;                                                               // 0.0
/*134 */         case NBD_INFO_BLOCK_SIZE:                                                // 0.0
/*136 */             blocksize = true;                                                    // 0.0
/*138 */             break;                                                               // 0.0
/*140 */         }                                                                        // 0.0
/*142 */     }                                                                            // 0.0
/*146 */     exp = nbd_export_find(name);                                                 // 0.0
/*148 */     if (!exp) {                                                                  // 0.0
/*150 */         return nbd_negotiate_send_rep_err(client->ioc, NBD_REP_ERR_UNKNOWN,      // 0.0
/*152 */                                           opt, errp, "export '%s' not present",  // 0.0
/*154 */                                           name);                                 // 0.0
/*156 */     }                                                                            // 0.0
/*160 */     /* Don't bother sending NBD_INFO_NAME unless client requested it */          // 0.0
/*162 */     if (sendname) {                                                              // 0.0
/*164 */         rc = nbd_negotiate_send_info(client, opt, NBD_INFO_NAME, length, name,   // 0.0
/*166 */                                      errp);                                      // 0.0
/*168 */         if (rc < 0) {                                                            // 0.0
/*170 */             return rc;                                                           // 0.0
/*172 */         }                                                                        // 0.0
/*174 */     }                                                                            // 0.0
/*178 */     /* Send NBD_INFO_DESCRIPTION only if available, regardless of                // 0.0
/*180 */      * client request */                                                         // 0.0
/*182 */     if (exp->description) {                                                      // 0.0
/*184 */         size_t len = strlen(exp->description);                                   // 0.0
/*188 */         rc = nbd_negotiate_send_info(client, opt, NBD_INFO_DESCRIPTION,          // 0.0
/*190 */                                      len, exp->description, errp);               // 0.0
/*192 */         if (rc < 0) {                                                            // 0.0
/*194 */             return rc;                                                           // 0.0
/*196 */         }                                                                        // 0.0
/*198 */     }                                                                            // 0.0
/*202 */     /* Send NBD_INFO_BLOCK_SIZE always, but tweak the minimum size               // 0.0
/*204 */      * according to whether the client requested it, and according to            // 0.0
/*206 */      * whether this is OPT_INFO or OPT_GO. */                                    // 0.0
/*208 */     /* minimum - 1 for back-compat, or 512 if client is new enough.              // 0.0
/*210 */      * TODO: consult blk_bs(blk)->bl.request_alignment? */                       // 0.0
/*212 */     sizes[0] = (opt == NBD_OPT_INFO || blocksize) ? BDRV_SECTOR_SIZE : 1;        // 0.0
/*214 */     /* preferred - Hard-code to 4096 for now.                                    // 0.0
/*216 */      * TODO: is blk_bs(blk)->bl.opt_transfer appropriate? */                     // 0.0
/*218 */     sizes[1] = 4096;                                                             // 0.0
/*220 */     /* maximum - At most 32M, but smaller as appropriate. */                     // 0.0
/*222 */     sizes[2] = MIN(blk_get_max_transfer(exp->blk), NBD_MAX_BUFFER_SIZE);         // 0.0
/*224 */     trace_nbd_negotiate_handle_info_block_size(sizes[0], sizes[1], sizes[2]);    // 0.0
/*226 */     cpu_to_be32s(&sizes[0]);                                                     // 0.0
/*228 */     cpu_to_be32s(&sizes[1]);                                                     // 0.0
/*230 */     cpu_to_be32s(&sizes[2]);                                                     // 0.0
/*232 */     rc = nbd_negotiate_send_info(client, opt, NBD_INFO_BLOCK_SIZE,               // 0.0
/*234 */                                  sizeof(sizes), sizes, errp);                    // 0.0
/*236 */     if (rc < 0) {                                                                // 0.0
/*238 */         return rc;                                                               // 0.0
/*240 */     }                                                                            // 0.0
/*244 */     /* Send NBD_INFO_EXPORT always */                                            // 0.0
/*246 */     trace_nbd_negotiate_new_style_size_flags(exp->size,                          // 0.0
/*248 */                                              exp->nbdflags | myflags);           // 0.0
/*250 */     stq_be_p(buf, exp->size);                                                    // 0.0
/*252 */     stw_be_p(buf + 8, exp->nbdflags | myflags);                                  // 0.0
/*254 */     rc = nbd_negotiate_send_info(client, opt, NBD_INFO_EXPORT,                   // 0.0
/*256 */                                  sizeof(buf), buf, errp);                        // 0.0
/*258 */     if (rc < 0) {                                                                // 0.0
/*260 */         return rc;                                                               // 0.0
/*262 */     }                                                                            // 0.0
/*266 */     /* If the client is just asking for NBD_OPT_INFO, but forgot to              // 0.0
/*268 */      * request block sizes, return an error.                                     // 0.0
/*270 */      * TODO: consult blk_bs(blk)->request_align, and only error if it            // 0.0
/*272 */      * is not 1? */                                                              // 0.0
/*274 */     if (opt == NBD_OPT_INFO && !blocksize) {                                     // 0.0
/*276 */         return nbd_negotiate_send_rep_err(client->ioc,                           // 0.0
/*278 */                                           NBD_REP_ERR_BLOCK_SIZE_REQD, opt,      // 0.0
/*280 */                                           errp,                                  // 0.0
/*282 */                                           "request NBD_INFO_BLOCK_SIZE to "      // 0.0
/*284 */                                           "use this export");                    // 0.0
/*286 */     }                                                                            // 0.0
/*290 */     /* Final reply */                                                            // 0.0
/*292 */     rc = nbd_negotiate_send_rep(client->ioc, NBD_REP_ACK, opt, errp);            // 0.0
/*294 */     if (rc < 0) {                                                                // 0.0
/*296 */         return rc;                                                               // 0.0
/*298 */     }                                                                            // 0.0
/*302 */     if (opt == NBD_OPT_GO) {                                                     // 0.0
/*304 */         client->exp = exp;                                                       // 0.0
/*306 */         QTAILQ_INSERT_TAIL(&client->exp->clients, client, next);                 // 0.0
/*308 */         nbd_export_get(client->exp);                                             // 0.0
/*310 */         rc = 1;                                                                  // 0.0
/*312 */     }                                                                            // 0.0
/*314 */     return rc;                                                                   // 0.0
/*318 */  invalid:                                                                        // 0.0
/*320 */     if (nbd_drop(client->ioc, length, errp) < 0) {                               // 0.0
/*322 */         return -EIO;                                                             // 0.0
/*324 */     }                                                                            // 0.0
/*326 */     return nbd_negotiate_send_rep_err(client->ioc, NBD_REP_ERR_INVALID, opt,     // 0.0
/*328 */                                       errp, "%s", msg);                          // 0.0
/*330 */ }                                                                                // 0.0
