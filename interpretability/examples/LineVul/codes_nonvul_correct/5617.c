// commit message FFmpeg@fc9b22dd2e (target=0, prob=0.4337812, correct=True): Expose max_packet_size from the rtp protocol
/*0   */ static int rtp_open(URLContext *h, const char *uri, int flags)          // (9) 0.03906
/*2   */ {                                                                       // (31) 0.001953
/*4   */     RTPContext *s;                                                      // (19) 0.01758
/*6   */     int port, is_output, ttl, local_port;                               // (11) 0.0332
/*8   */     char hostname[256];                                                 // (21) 0.01758
/*10  */     char buf[1024];                                                     // (22) 0.01562
/*12  */     char path[1024];                                                    // (23) 0.01562
/*14  */     const char *p;                                                      // (24) 0.01562
/*18  */     is_output = (flags & URL_WRONLY);                                   // (12) 0.03125
/*22  */     s = av_mallocz(sizeof(RTPContext));                                 // (10) 0.03516
/*24  */     if (!s)                                                             // (29) 0.01367
/*26  */         return AVERROR(ENOMEM);                                         // (14) 0.03125
/*28  */     h->priv_data = s;                                                   // (16) 0.02148
/*32  */     url_split(NULL, 0, NULL, 0, hostname, sizeof(hostname), &port,      // (3) 0.05078
/*34  */               path, sizeof(path), uri);                                 // (8) 0.04297
/*36  */     /* extract parameters */                                            // (28) 0.01367
/*38  */     ttl = -1;                                                           // (20) 0.01758
/*40  */     local_port = -1;                                                    // (18) 0.01953
/*42  */     p = strchr(uri, '?');                                               // (15) 0.02734
/*44  */     if (p) {                                                            // (25) 0.01562
/*46  */         if (find_info_tag(buf, sizeof(buf), "ttl", p)) {                // (1) 0.05469
/*48  */             ttl = strtol(buf, NULL, 10);                                // (5) 0.04687
/*50  */         }                                                               // (26) 0.01562
/*52  */         if (find_info_tag(buf, sizeof(buf), "localport", p)) {          // (2) 0.05469
/*54  */             local_port = strtol(buf, NULL, 10);                         // (4) 0.04883
/*56  */         }                                                               // (27) 0.01562
/*58  */     }                                                                   // (30) 0.007812
/*62  */     build_udp_url(buf, sizeof(buf),                                     // (13) 0.03125
/*64  */                   hostname, port, local_port, ttl);                     // (0) 0.05664
/*66  */     if (url_open(&s->rtp_hd, buf, flags) < 0)                           // (6) 0.04492
/*68  */         goto fail;                                                      // (17) 0.01953
/*70  */     local_port = udp_get_local_port(s->rtp_hd);                         // (7) 0.04492
/*72  */     /* XXX: need to open another connection if the port is not even */  // 0.0
/*76  */     /* well, should suppress localport in path */                       // 0.0
/*80  */     build_udp_url(buf, sizeof(buf),                                     // 0.0
/*82  */                   hostname, port + 1, local_port + 1, ttl);             // 0.0
/*84  */     if (url_open(&s->rtcp_hd, buf, flags) < 0)                          // 0.0
/*86  */         goto fail;                                                      // 0.0
/*90  */     /* just to ease handle access. XXX: need to suppress direct handle  // 0.0
/*92  */        access */                                                        // 0.0
/*94  */     s->rtp_fd = udp_get_file_handle(s->rtp_hd);                         // 0.0
/*96  */     s->rtcp_fd = udp_get_file_handle(s->rtcp_hd);                       // 0.0
/*100 */     h->max_packet_size = url_get_max_packet_size(s->rtp_hd);            // 0.0
/*102 */     h->is_streamed = 1;                                                 // 0.0
/*104 */     return 0;                                                           // 0.0
/*108 */  fail:                                                                  // 0.0
/*110 */     if (s->rtp_hd)                                                      // 0.0
/*112 */         url_close(s->rtp_hd);                                           // 0.0
/*114 */     if (s->rtcp_hd)                                                     // 0.0
/*116 */         url_close(s->rtcp_hd);                                          // 0.0
/*118 */     av_free(s);                                                         // 0.0
/*120 */     return AVERROR(EIO);                                                // 0.0
/*122 */ }                                                                       // 0.0
