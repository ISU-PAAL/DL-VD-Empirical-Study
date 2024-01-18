// commit message FFmpeg@ec4c483976 (target=1, prob=0.44686186, correct=False): lavf: add a protocol whitelist/blacklist for file opened internally
/*0   */ static int sap_write_header(AVFormatContext *s)                                    // (13) 0.02734
/*2   */ {                                                                                  // (28) 0.001953
/*4   */     struct SAPState *sap = s->priv_data;                                           // (10) 0.03125
/*6   */     char host[1024], path[1024], url[1024], announce_addr[50] = "";                // (6) 0.04883
/*8   */     char *option_list;                                                             // (22) 0.01758
/*10  */     int port = 9875, base_port = 5004, i, pos = 0, same_port = 0, ttl = 255;       // (1) 0.06445
/*12  */     AVFormatContext **contexts = NULL;                                             // (15) 0.02344
/*14  */     int ret = 0;                                                                   // (25) 0.01562
/*16  */     struct sockaddr_storage localaddr;                                             // (17) 0.02148
/*18  */     socklen_t addrlen = sizeof(localaddr);                                         // (11) 0.0293
/*20  */     int udp_fd;                                                                    // (23) 0.01758
/*22  */     AVDictionaryEntry* title = av_dict_get(s->metadata, "title", NULL, 0);         // (4) 0.05273
/*26  */     if (!ff_network_init())                                                        // (18) 0.02148
/*28  */         return AVERROR(EIO);                                                       // (12) 0.0293
/*32  */     /* extract hostname and port */                                                // (20) 0.01953
/*34  */     av_url_split(NULL, 0, NULL, 0, host, sizeof(host), &base_port,                 // (3) 0.05469
/*36  */                  path, sizeof(path), s->filename);                                 // (5) 0.05078
/*38  */     if (base_port < 0)                                                             // (19) 0.02148
/*40  */         base_port = 5004;                                                          // (14) 0.02734
/*44  */     /* search for options */                                                       // (24) 0.01562
/*46  */     option_list = strrchr(path, '?');                                              // (9) 0.0332
/*48  */     if (option_list) {                                                             // (21) 0.01953
/*50  */         char buf[50];                                                              // (16) 0.02344
/*52  */         if (av_find_info_tag(buf, sizeof(buf), "announce_port", option_list)) {    // (0) 0.06641
/*54  */             port = strtol(buf, NULL, 10);                                          // (8) 0.04492
/*56  */         }                                                                          // (27) 0.01562
/*58  */         if (av_find_info_tag(buf, sizeof(buf), "same_port", option_list)) {        // (2) 0.06445
/*60  */             same_port = strtol(buf, NULL, 10);                                     // (7) 0.04883
/*62  */         }                                                                          // (26) 0.01562
/*64  */         if (av_find_info_tag(buf, sizeof(buf), "ttl", option_list)) {              // 0.0
/*66  */             ttl = strtol(buf, NULL, 10);                                           // 0.0
/*68  */         }                                                                          // 0.0
/*70  */         if (av_find_info_tag(buf, sizeof(buf), "announce_addr", option_list)) {    // 0.0
/*72  */             av_strlcpy(announce_addr, buf, sizeof(announce_addr));                 // 0.0
/*74  */         }                                                                          // 0.0
/*76  */     }                                                                              // 0.0
/*80  */     if (!announce_addr[0]) {                                                       // 0.0
/*82  */         struct addrinfo hints = { 0 }, *ai = NULL;                                 // 0.0
/*84  */         hints.ai_family = AF_UNSPEC;                                               // 0.0
/*86  */         if (getaddrinfo(host, NULL, &hints, &ai)) {                                // 0.0
/*88  */             av_log(s, AV_LOG_ERROR, "Unable to resolve %s\n", host);               // 0.0
/*90  */             ret = AVERROR(EIO);                                                    // 0.0
/*92  */             goto fail;                                                             // 0.0
/*94  */         }                                                                          // 0.0
/*96  */         if (ai->ai_family == AF_INET) {                                            // 0.0
/*98  */             /* Also known as sap.mcast.net */                                      // 0.0
/*100 */             av_strlcpy(announce_addr, "224.2.127.254", sizeof(announce_addr));     // 0.0
/*102 */ #if HAVE_STRUCT_SOCKADDR_IN6                                                       // 0.0
/*104 */         } else if (ai->ai_family == AF_INET6) {                                    // 0.0
/*106 */             /* With IPv6, you can use the same destination in many different       // 0.0
/*108 */              * multicast subnets, to choose how far you want it routed.            // 0.0
/*110 */              * This one is intended to be routed globally. */                      // 0.0
/*112 */             av_strlcpy(announce_addr, "ff0e::2:7ffe", sizeof(announce_addr));      // 0.0
/*114 */ #endif                                                                             // 0.0
/*116 */         } else {                                                                   // 0.0
/*118 */             freeaddrinfo(ai);                                                      // 0.0
/*120 */             av_log(s, AV_LOG_ERROR, "Host %s resolved to unsupported "             // 0.0
/*122 */                                     "address family\n", host);                     // 0.0
/*124 */             ret = AVERROR(EIO);                                                    // 0.0
/*126 */             goto fail;                                                             // 0.0
/*128 */         }                                                                          // 0.0
/*130 */         freeaddrinfo(ai);                                                          // 0.0
/*132 */     }                                                                              // 0.0
/*136 */     sap->protocols = ffurl_get_protocols(NULL, NULL);                              // 0.0
/*138 */     if (!sap->protocols) {                                                         // 0.0
/*140 */         ret = AVERROR(ENOMEM);                                                     // 0.0
/*142 */         goto fail;                                                                 // 0.0
/*144 */     }                                                                              // 0.0
/*148 */     contexts = av_mallocz(sizeof(AVFormatContext*) * s->nb_streams);               // 0.0
/*150 */     if (!contexts) {                                                               // 0.0
/*152 */         ret = AVERROR(ENOMEM);                                                     // 0.0
/*154 */         goto fail;                                                                 // 0.0
/*156 */     }                                                                              // 0.0
/*160 */     s->start_time_realtime = av_gettime();                                         // 0.0
/*162 */     for (i = 0; i < s->nb_streams; i++) {                                          // 0.0
/*164 */         URLContext *fd;                                                            // 0.0
/*168 */         ff_url_join(url, sizeof(url), "rtp", NULL, host, base_port,                // 0.0
/*170 */                     "?ttl=%d", ttl);                                               // 0.0
/*172 */         if (!same_port)                                                            // 0.0
/*174 */             base_port += 2;                                                        // 0.0
/*176 */         ret = ffurl_open(&fd, url, AVIO_FLAG_WRITE, &s->interrupt_callback, NULL,  // 0.0
/*178 */                          sap->protocols);                                          // 0.0
/*180 */         if (ret) {                                                                 // 0.0
/*182 */             ret = AVERROR(EIO);                                                    // 0.0
/*184 */             goto fail;                                                             // 0.0
/*186 */         }                                                                          // 0.0
/*188 */         ret = ff_rtp_chain_mux_open(&contexts[i], s, s->streams[i], fd, 0, i);     // 0.0
/*190 */         if (ret < 0)                                                               // 0.0
/*192 */             goto fail;                                                             // 0.0
/*194 */         s->streams[i]->priv_data = contexts[i];                                    // 0.0
/*196 */         s->streams[i]->time_base = contexts[i]->streams[0]->time_base;             // 0.0
/*198 */         av_strlcpy(contexts[i]->filename, url, sizeof(contexts[i]->filename));     // 0.0
/*200 */     }                                                                              // 0.0
/*204 */     if (s->nb_streams > 0 && title)                                                // 0.0
/*206 */         av_dict_set(&contexts[0]->metadata, "title", title->value, 0);             // 0.0
/*210 */     ff_url_join(url, sizeof(url), "udp", NULL, announce_addr, port,                // 0.0
/*212 */                 "?ttl=%d&connect=1", ttl);                                         // 0.0
/*214 */     ret = ffurl_open(&sap->ann_fd, url, AVIO_FLAG_WRITE,                           // 0.0
/*216 */                      &s->interrupt_callback, NULL, sap->protocols);                // 0.0
/*218 */     if (ret) {                                                                     // 0.0
/*220 */         ret = AVERROR(EIO);                                                        // 0.0
/*222 */         goto fail;                                                                 // 0.0
/*224 */     }                                                                              // 0.0
/*228 */     udp_fd = ffurl_get_file_handle(sap->ann_fd);                                   // 0.0
/*230 */     if (getsockname(udp_fd, (struct sockaddr*) &localaddr, &addrlen)) {            // 0.0
/*232 */         ret = AVERROR(EIO);                                                        // 0.0
/*234 */         goto fail;                                                                 // 0.0
/*236 */     }                                                                              // 0.0
/*238 */     if (localaddr.ss_family != AF_INET                                             // 0.0
/*240 */ #if HAVE_STRUCT_SOCKADDR_IN6                                                       // 0.0
/*242 */         && localaddr.ss_family != AF_INET6                                         // 0.0
/*244 */ #endif                                                                             // 0.0
/*246 */         ) {                                                                        // 0.0
/*248 */         av_log(s, AV_LOG_ERROR, "Unsupported protocol family\n");                  // 0.0
/*250 */         ret = AVERROR(EIO);                                                        // 0.0
/*252 */         goto fail;                                                                 // 0.0
/*254 */     }                                                                              // 0.0
/*256 */     sap->ann_size = 8192;                                                          // 0.0
/*258 */     sap->ann = av_mallocz(sap->ann_size);                                          // 0.0
/*260 */     if (!sap->ann) {                                                               // 0.0
/*262 */         ret = AVERROR(EIO);                                                        // 0.0
/*264 */         goto fail;                                                                 // 0.0
/*266 */     }                                                                              // 0.0
/*268 */     sap->ann[pos] = (1 << 5);                                                      // 0.0
/*270 */ #if HAVE_STRUCT_SOCKADDR_IN6                                                       // 0.0
/*272 */     if (localaddr.ss_family == AF_INET6)                                           // 0.0
/*274 */         sap->ann[pos] |= 0x10;                                                     // 0.0
/*276 */ #endif                                                                             // 0.0
/*278 */     pos++;                                                                         // 0.0
/*280 */     sap->ann[pos++] = 0; /* Authentication length */                               // 0.0
/*282 */     AV_WB16(&sap->ann[pos], av_get_random_seed());                                 // 0.0
/*284 */     pos += 2;                                                                      // 0.0
/*286 */     if (localaddr.ss_family == AF_INET) {                                          // 0.0
/*288 */         memcpy(&sap->ann[pos], &((struct sockaddr_in*)&localaddr)->sin_addr,       // 0.0
/*290 */                sizeof(struct in_addr));                                            // 0.0
/*292 */         pos += sizeof(struct in_addr);                                             // 0.0
/*294 */ #if HAVE_STRUCT_SOCKADDR_IN6                                                       // 0.0
/*296 */     } else {                                                                       // 0.0
/*298 */         memcpy(&sap->ann[pos], &((struct sockaddr_in6*)&localaddr)->sin6_addr,     // 0.0
/*300 */                sizeof(struct in6_addr));                                           // 0.0
/*302 */         pos += sizeof(struct in6_addr);                                            // 0.0
/*304 */ #endif                                                                             // 0.0
/*306 */     }                                                                              // 0.0
/*310 */     av_strlcpy(&sap->ann[pos], "application/sdp", sap->ann_size - pos);            // 0.0
/*312 */     pos += strlen(&sap->ann[pos]) + 1;                                             // 0.0
/*316 */     if (av_sdp_create(contexts, s->nb_streams, &sap->ann[pos],                     // 0.0
/*318 */                       sap->ann_size - pos)) {                                      // 0.0
/*320 */         ret = AVERROR_INVALIDDATA;                                                 // 0.0
/*322 */         goto fail;                                                                 // 0.0
/*324 */     }                                                                              // 0.0
/*326 */     av_freep(&contexts);                                                           // 0.0
/*328 */     av_log(s, AV_LOG_VERBOSE, "SDP:\n%s\n", &sap->ann[pos]);                       // 0.0
/*330 */     pos += strlen(&sap->ann[pos]);                                                 // 0.0
/*332 */     sap->ann_size = pos;                                                           // 0.0
/*336 */     if (sap->ann_size > sap->ann_fd->max_packet_size) {                            // 0.0
/*338 */         av_log(s, AV_LOG_ERROR, "Announcement too large to send in one "           // 0.0
/*340 */                                 "packet\n");                                       // 0.0
/*342 */         goto fail;                                                                 // 0.0
/*344 */     }                                                                              // 0.0
/*348 */     return 0;                                                                      // 0.0
/*352 */ fail:                                                                              // 0.0
/*354 */     av_free(contexts);                                                             // 0.0
/*356 */     sap_write_close(s);                                                            // 0.0
/*358 */     return ret;                                                                    // 0.0
/*360 */ }                                                                                  // 0.0
