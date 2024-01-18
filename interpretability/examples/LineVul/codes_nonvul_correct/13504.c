// commit message qemu@353ab96973 (target=0, prob=0.3216411, correct=True): nbd: Don't trim unrequested bytes
/*0   */ static void nbd_trip(void *opaque)                                              // (12) 0.02344
/*2   */ {                                                                               // (33) 0.001953
/*4   */     NBDClient *client = opaque;                                                 // (15) 0.02148
/*6   */     NBDExport *exp = client->exp;                                               // (10) 0.02539
/*8   */     NBDRequest *req;                                                            // (24) 0.01758
/*10  */     struct nbd_request request;                                                 // (19) 0.01953
/*12  */     struct nbd_reply reply;                                                     // (20) 0.01953
/*14  */     ssize_t ret;                                                                // (27) 0.01758
/*16  */     uint32_t command;                                                           // (26) 0.01758
/*20  */     TRACE("Reading request.");                                                  // (18) 0.01953
/*22  */     if (client->closing) {                                                      // (16) 0.02148
/*24  */         return;                                                                 // (28) 0.01758
/*26  */     }                                                                           // (29) 0.007812
/*30  */     req = nbd_request_get(client);                                              // (8) 0.02734
/*32  */     ret = nbd_co_receive_request(req, &request);                                // (7) 0.03906
/*34  */     if (ret == -EAGAIN) {                                                       // (11) 0.02539
/*36  */         goto done;                                                              // (22) 0.01953
/*38  */     }                                                                           // (30) 0.007812
/*40  */     if (ret == -EIO) {                                                          // (13) 0.02344
/*42  */         goto out;                                                               // (21) 0.01953
/*44  */     }                                                                           // (32) 0.007812
/*48  */     reply.handle = request.handle;                                              // (17) 0.02148
/*50  */     reply.error = 0;                                                            // (25) 0.01758
/*54  */     if (ret < 0) {                                                              // (23) 0.01953
/*56  */         reply.error = -ret;                                                     // (9) 0.02734
/*58  */         goto error_reply;                                                       // (14) 0.02344
/*60  */     }                                                                           // (31) 0.007812
/*62  */     command = request.type & NBD_CMD_MASK_COMMAND;                              // (5) 0.04297
/*64  */     if (command != NBD_CMD_DISC && (request.from + request.len) > exp->size) {  // (2) 0.06055
/*66  */             LOG("From: %" PRIu64 ", Len: %u, Size: %" PRIu64                    // (1) 0.06836
/*68  */             ", Offset: %" PRIu64 "\n",                                          // (4) 0.04687
/*70  */                     request.from, request.len,                                  // (3) 0.05273
/*72  */                     (uint64_t)exp->size, (uint64_t)exp->dev_offset);            // (0) 0.08008
/*74  */         LOG("requested operation past EOF--bad client?");                       // (6) 0.03906
/*76  */         goto invalid_request;                                                   // 0.0
/*78  */     }                                                                           // 0.0
/*82  */     if (client->closing) {                                                      // 0.0
/*84  */         /*                                                                      // 0.0
/*86  */          * The client may be closed when we are blocked in                      // 0.0
/*88  */          * nbd_co_receive_request()                                             // 0.0
/*90  */          */                                                                     // 0.0
/*92  */         goto done;                                                              // 0.0
/*94  */     }                                                                           // 0.0
/*98  */     switch (command) {                                                          // 0.0
/*100 */     case NBD_CMD_READ:                                                          // 0.0
/*102 */         TRACE("Request type is READ");                                          // 0.0
/*106 */         if (request.type & NBD_CMD_FLAG_FUA) {                                  // 0.0
/*108 */             ret = blk_co_flush(exp->blk);                                       // 0.0
/*110 */             if (ret < 0) {                                                      // 0.0
/*112 */                 LOG("flush failed");                                            // 0.0
/*114 */                 reply.error = -ret;                                             // 0.0
/*116 */                 goto error_reply;                                               // 0.0
/*118 */             }                                                                   // 0.0
/*120 */         }                                                                       // 0.0
/*124 */         ret = blk_pread(exp->blk, request.from + exp->dev_offset,               // 0.0
/*126 */                         req->data, request.len);                                // 0.0
/*128 */         if (ret < 0) {                                                          // 0.0
/*130 */             LOG("reading from file failed");                                    // 0.0
/*132 */             reply.error = -ret;                                                 // 0.0
/*134 */             goto error_reply;                                                   // 0.0
/*136 */         }                                                                       // 0.0
/*140 */         TRACE("Read %u byte(s)", request.len);                                  // 0.0
/*142 */         if (nbd_co_send_reply(req, &reply, request.len) < 0)                    // 0.0
/*144 */             goto out;                                                           // 0.0
/*146 */         break;                                                                  // 0.0
/*148 */     case NBD_CMD_WRITE:                                                         // 0.0
/*150 */         TRACE("Request type is WRITE");                                         // 0.0
/*154 */         if (exp->nbdflags & NBD_FLAG_READ_ONLY) {                               // 0.0
/*156 */             TRACE("Server is read-only, return error");                         // 0.0
/*158 */             reply.error = EROFS;                                                // 0.0
/*160 */             goto error_reply;                                                   // 0.0
/*162 */         }                                                                       // 0.0
/*166 */         TRACE("Writing to device");                                             // 0.0
/*170 */         ret = blk_pwrite(exp->blk, request.from + exp->dev_offset,              // 0.0
/*172 */                          req->data, request.len, 0);                            // 0.0
/*174 */         if (ret < 0) {                                                          // 0.0
/*176 */             LOG("writing to file failed");                                      // 0.0
/*178 */             reply.error = -ret;                                                 // 0.0
/*180 */             goto error_reply;                                                   // 0.0
/*182 */         }                                                                       // 0.0
/*186 */         if (request.type & NBD_CMD_FLAG_FUA) {                                  // 0.0
/*188 */             ret = blk_co_flush(exp->blk);                                       // 0.0
/*190 */             if (ret < 0) {                                                      // 0.0
/*192 */                 LOG("flush failed");                                            // 0.0
/*194 */                 reply.error = -ret;                                             // 0.0
/*196 */                 goto error_reply;                                               // 0.0
/*198 */             }                                                                   // 0.0
/*200 */         }                                                                       // 0.0
/*204 */         if (nbd_co_send_reply(req, &reply, 0) < 0) {                            // 0.0
/*206 */             goto out;                                                           // 0.0
/*208 */         }                                                                       // 0.0
/*210 */         break;                                                                  // 0.0
/*212 */     case NBD_CMD_DISC:                                                          // 0.0
/*214 */         TRACE("Request type is DISCONNECT");                                    // 0.0
/*216 */         errno = 0;                                                              // 0.0
/*218 */         goto out;                                                               // 0.0
/*220 */     case NBD_CMD_FLUSH:                                                         // 0.0
/*222 */         TRACE("Request type is FLUSH");                                         // 0.0
/*226 */         ret = blk_co_flush(exp->blk);                                           // 0.0
/*228 */         if (ret < 0) {                                                          // 0.0
/*230 */             LOG("flush failed");                                                // 0.0
/*232 */             reply.error = -ret;                                                 // 0.0
/*234 */         }                                                                       // 0.0
/*236 */         if (nbd_co_send_reply(req, &reply, 0) < 0) {                            // 0.0
/*238 */             goto out;                                                           // 0.0
/*240 */         }                                                                       // 0.0
/*242 */         break;                                                                  // 0.0
/*244 */     case NBD_CMD_TRIM:                                                          // 0.0
/*246 */         TRACE("Request type is TRIM");                                          // 0.0
/*248 */         ret = blk_co_discard(exp->blk, (request.from + exp->dev_offset)         // 0.0
/*250 */                                        / BDRV_SECTOR_SIZE,                      // 0.0
/*252 */                              request.len / BDRV_SECTOR_SIZE);                   // 0.0
/*254 */         if (ret < 0) {                                                          // 0.0
/*256 */             LOG("discard failed");                                              // 0.0
/*258 */             reply.error = -ret;                                                 // 0.0
/*260 */         }                                                                       // 0.0
/*262 */         if (nbd_co_send_reply(req, &reply, 0) < 0) {                            // 0.0
/*264 */             goto out;                                                           // 0.0
/*266 */         }                                                                       // 0.0
/*268 */         break;                                                                  // 0.0
/*270 */     default:                                                                    // 0.0
/*272 */         LOG("invalid request type (%u) received", request.type);                // 0.0
/*274 */     invalid_request:                                                            // 0.0
/*276 */         reply.error = EINVAL;                                                   // 0.0
/*278 */     error_reply:                                                                // 0.0
/*280 */         if (nbd_co_send_reply(req, &reply, 0) < 0) {                            // 0.0
/*282 */             goto out;                                                           // 0.0
/*284 */         }                                                                       // 0.0
/*286 */         break;                                                                  // 0.0
/*288 */     }                                                                           // 0.0
/*292 */     TRACE("Request/Reply complete");                                            // 0.0
/*296 */ done:                                                                           // 0.0
/*298 */     nbd_request_put(req);                                                       // 0.0
/*300 */     return;                                                                     // 0.0
/*304 */ out:                                                                            // 0.0
/*306 */     nbd_request_put(req);                                                       // 0.0
/*308 */     client_close(client);                                                       // 0.0
/*310 */ }                                                                               // 0.0
