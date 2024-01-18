// commit message qemu@8dc7a7725b (target=1, prob=0.32303637, correct=False): curl: Handle failure for potentially large allocations
/*0   */ static void curl_readv_bh_cb(void *p)                                       // (11) 0.02928
/*2   */ {                                                                           // (32) 0.001954
/*4   */     CURLState *state;                                                       // (24) 0.01756
/*6   */     int running;                                                            // (29) 0.0117
/*10  */     CURLAIOCB *acb = p;                                                     // (13) 0.02926
/*12  */     BDRVCURLState *s = acb->common.bs->opaque;                              // (6) 0.04096
/*16  */     qemu_bh_delete(acb->bh);                                                // (8) 0.03121
/*18  */     acb->bh = NULL;                                                         // (22) 0.01951
/*22  */     size_t start = acb->sector_num * SECTOR_SIZE;                           // (5) 0.04096
/*24  */     size_t end;                                                             // (27) 0.01563
/*28  */     // In case we have the requested data already (e.g. read-ahead),        // (4) 0.04161
/*30  */     // we can just call the callback and be done.                           // (14) 0.0278
/*32  */     switch (curl_find_buf(s, start, acb->nb_sectors * SECTOR_SIZE, acb)) {  // (0) 0.06635
/*34  */         case FIND_RET_OK:                                                   // (12) 0.02926
/*36  */             qemu_aio_release(acb);                                          // (3) 0.04485
/*38  */             // fall through                                                 // (15) 0.02733
/*40  */         case FIND_RET_WAIT:                                                 // (9) 0.03121
/*42  */             return;                                                         // (19) 0.02535
/*44  */         default:                                                            // (25) 0.01755
/*46  */             break;                                                          // (18) 0.02535
/*48  */     }                                                                       // (30) 0.007809
/*52  */     // No cache found, so let's start a new request                         // (10) 0.02928
/*54  */     state = curl_init_state(s);                                             // (16) 0.02535
/*56  */     if (!state) {                                                           // (28) 0.0156
/*58  */         acb->common.cb(acb->common.opaque, -EIO);                           // (1) 0.05071
/*60  */         qemu_aio_release(acb);                                              // (7) 0.03705
/*62  */         return;                                                             // (26) 0.01755
/*64  */     }                                                                       // (31) 0.007803
/*68  */     acb->start = 0;                                                         // (23) 0.0195
/*70  */     acb->end = (acb->nb_sectors * SECTOR_SIZE);                             // (2) 0.04485
/*74  */     state->buf_off = 0;                                                     // (20) 0.02145
/*76  */     g_free(state->orig_buf);                                                // (17) 0.02535
/*78  */     state->buf_start = start;                                               // (21) 0.02145
/*80  */     state->buf_len = acb->end + s->readahead_size;                          // 0.0
/*82  */     end = MIN(start + state->buf_len, s->len) - 1;                          // 0.0
/*84  */     state->orig_buf = g_malloc(state->buf_len);                             // 0.0
/*86  */     state->acb[0] = acb;                                                    // 0.0
/*90  */     snprintf(state->range, 127, "%zd-%zd", start, end);                     // 0.0
/*92  */     DPRINTF("CURL (AIO): Reading %d at %zd (%s)\n",                         // 0.0
/*94  */             (acb->nb_sectors * SECTOR_SIZE), start, state->range);          // 0.0
/*96  */     curl_easy_setopt(state->curl, CURLOPT_RANGE, state->range);             // 0.0
/*100 */     curl_multi_add_handle(s->multi, state->curl);                           // 0.0
/*104 */     /* Tell curl it needs to kick things off */                             // 0.0
/*106 */     curl_multi_socket_action(s->multi, CURL_SOCKET_TIMEOUT, 0, &running);   // 0.0
/*108 */ }                                                                           // 0.0
