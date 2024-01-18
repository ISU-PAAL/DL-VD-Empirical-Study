// commit message FFmpeg@b7b8fc3406 (target=0, prob=0.7216793, correct=False): suppressed RTSP abort hack - added PLAY/PAUSE
/*0   */ static int rtsp_read_header(AVFormatContext *s,                                                 // (9) 0.03125
/*2   */                             AVFormatParameters *ap)                                             // (0) 0.06445
/*4   */ {                                                                                               // (30) 0.001953
/*6   */     RTSPState *rt = s->priv_data;                                                               // (12) 0.0293
/*8   */     char host[1024], path[1024], tcpname[1024], cmd[2048];                                      // (6) 0.04297
/*10  */     URLContext *rtsp_hd;                                                                        // (18) 0.02344
/*12  */     int port, i, ret, err;                                                                      // (17) 0.02344
/*14  */     RTSPHeader reply1, *reply = &reply1;                                                        // (10) 0.03125
/*16  */     unsigned char *content = NULL;                                                              // (21) 0.01953
/*18  */     AVStream *st;                                                                               // (25) 0.01563
/*20  */     RTSPStream *rtsp_st;                                                                        // (16) 0.02539
/*22  */     int protocol_mask;                                                                          // (26) 0.01562
/*26  */     rtsp_abort_req = 0;                                                                         // (13) 0.02734
/*28  */                                                                                                 // (28) 0.007812
/*30  */     /* extract hostname and port */                                                             // (22) 0.01953
/*32  */     url_split(NULL, 0,                                                                          // (20) 0.02148
/*34  */               host, sizeof(host), &port, path, sizeof(path), s->filename);                      // (1) 0.0625
/*36  */     if (port < 0)                                                                               // (24) 0.01758
/*38  */         port = RTSP_DEFAULT_PORT;                                                               // (8) 0.0332
/*42  */     /* open the tcp connexion */                                                                // (19) 0.02148
/*44  */     snprintf(tcpname, sizeof(tcpname), "tcp://%s:%d", host, port);                              // (2) 0.05859
/*46  */     if (url_open(&rtsp_hd, tcpname, URL_RDWR) < 0)                                              // (4) 0.05078
/*48  */         return AVERROR_IO;                                                                      // (14) 0.02734
/*50  */     rt->rtsp_hd = rtsp_hd;                                                                      // (7) 0.03516
/*52  */     rt->seq = 0;                                                                                // (23) 0.01953
/*54  */                                                                                                 // (29) 0.007812
/*56  */     /* describe the stream */                                                                   // (27) 0.01562
/*58  */     snprintf(cmd, sizeof(cmd),                                                                  // (15) 0.02539
/*60  */              "DESCRIBE %s RTSP/1.0\r\n"                                                         // (3) 0.05859
/*62  */              "Accept: application/sdp\r\n",                                                     // (5) 0.04688
/*64  */              s->filename);                                                                      // (11) 0.03125
/*66  */     rtsp_send_cmd(s, cmd, reply, &content);                                                     // 0.0
/*68  */     if (!content) {                                                                             // 0.0
/*70  */         err = AVERROR_INVALIDDATA;                                                              // 0.0
/*72  */         goto fail;                                                                              // 0.0
/*74  */     }                                                                                           // 0.0
/*76  */     if (reply->status_code != RTSP_STATUS_OK) {                                                 // 0.0
/*78  */         err = AVERROR_INVALIDDATA;                                                              // 0.0
/*80  */         goto fail;                                                                              // 0.0
/*82  */     }                                                                                           // 0.0
/*84  */                                                                                                 // 0.0
/*86  */     /* now we got the SDP description, we parse it */                                           // 0.0
/*88  */     ret = sdp_parse(s, (const char *)content);                                                  // 0.0
/*90  */     av_freep(&content);                                                                         // 0.0
/*92  */     if (ret < 0) {                                                                              // 0.0
/*94  */         err = AVERROR_INVALIDDATA;                                                              // 0.0
/*96  */         goto fail;                                                                              // 0.0
/*98  */     }                                                                                           // 0.0
/*100 */                                                                                                 // 0.0
/*102 */     protocol_mask = rtsp_default_protocols;                                                     // 0.0
/*106 */     /* for each stream, make the setup request */                                               // 0.0
/*108 */     /* XXX: we assume the same server is used for the control of each                           // 0.0
/*110 */        RTSP stream */                                                                           // 0.0
/*112 */     for(i=0;i<s->nb_streams;i++) {                                                              // 0.0
/*114 */         char transport[2048];                                                                   // 0.0
/*116 */         AVInputFormat *fmt;                                                                     // 0.0
/*120 */         st = s->streams[i];                                                                     // 0.0
/*122 */         rtsp_st = st->priv_data;                                                                // 0.0
/*126 */         /* compute available transports */                                                      // 0.0
/*128 */         transport[0] = '\0';                                                                    // 0.0
/*132 */         /* RTP/UDP */                                                                           // 0.0
/*134 */         if (protocol_mask & (1 << RTSP_PROTOCOL_RTP_UDP)) {                                     // 0.0
/*136 */             char buf[256];                                                                      // 0.0
/*138 */             int j;                                                                              // 0.0
/*142 */             /* first try in specified port range */                                             // 0.0
/*144 */             if (rtsp_rtp_port_min != 0) {                                                       // 0.0
/*146 */                 for(j=rtsp_rtp_port_min;j<=rtsp_rtp_port_max;j++) {                             // 0.0
/*148 */                     snprintf(buf, sizeof(buf), "rtp://?localport=%d", j);                       // 0.0
/*150 */                     if (!av_open_input_file(&rtsp_st->ic, buf,                                  // 0.0
/*152 */                                             &rtp_demux, 0, NULL))                               // 0.0
/*154 */                         goto rtp_opened;                                                        // 0.0
/*156 */                 }                                                                               // 0.0
/*158 */             }                                                                                   // 0.0
/*162 */             /* then try on any port */                                                          // 0.0
/*164 */             if (av_open_input_file(&rtsp_st->ic, "rtp://",                                      // 0.0
/*166 */                                        &rtp_demux, 0, NULL) < 0) {                              // 0.0
/*168 */                     err = AVERROR_INVALIDDATA;                                                  // 0.0
/*170 */                     goto fail;                                                                  // 0.0
/*172 */             }                                                                                   // 0.0
/*176 */         rtp_opened:                                                                             // 0.0
/*178 */             port = rtp_get_local_port(url_fileno(&rtsp_st->ic->pb));                            // 0.0
/*180 */             if (transport[0] != '\0')                                                           // 0.0
/*182 */                 pstrcat(transport, sizeof(transport), ",");                                     // 0.0
/*184 */             snprintf(transport + strlen(transport), sizeof(transport) - strlen(transport) - 1,  // 0.0
/*186 */                      "RTP/AVP/UDP;unicast;client_port=%d-%d",                                   // 0.0
/*188 */                      port, port + 1);                                                           // 0.0
/*190 */         }                                                                                       // 0.0
/*194 */         /* RTP/TCP */                                                                           // 0.0
/*196 */         if (protocol_mask & (1 << RTSP_PROTOCOL_RTP_TCP)) {                                     // 0.0
/*198 */             if (transport[0] != '\0')                                                           // 0.0
/*200 */                 pstrcat(transport, sizeof(transport), ",");                                     // 0.0
/*202 */             snprintf(transport + strlen(transport), sizeof(transport) - strlen(transport) - 1,  // 0.0
/*204 */                      "RTP/AVP/TCP");                                                            // 0.0
/*206 */         }                                                                                       // 0.0
/*210 */         if (protocol_mask & (1 << RTSP_PROTOCOL_RTP_UDP_MULTICAST)) {                           // 0.0
/*212 */             if (transport[0] != '\0')                                                           // 0.0
/*214 */                 pstrcat(transport, sizeof(transport), ",");                                     // 0.0
/*216 */             snprintf(transport + strlen(transport),                                             // 0.0
/*218 */                      sizeof(transport) - strlen(transport) - 1,                                 // 0.0
/*220 */                      "RTP/AVP/UDP;multicast");                                                  // 0.0
/*222 */         }                                                                                       // 0.0
/*224 */         snprintf(cmd, sizeof(cmd),                                                              // 0.0
/*226 */                  "SETUP %s RTSP/1.0\r\n"                                                        // 0.0
/*228 */                  "Transport: %s\r\n",                                                           // 0.0
/*230 */                  rtsp_st->control_url, transport);                                              // 0.0
/*232 */         rtsp_send_cmd(s, cmd, reply, NULL);                                                     // 0.0
/*234 */         if (reply->status_code != RTSP_STATUS_OK ||                                             // 0.0
/*236 */             reply->nb_transports != 1) {                                                        // 0.0
/*238 */             err = AVERROR_INVALIDDATA;                                                          // 0.0
/*240 */             goto fail;                                                                          // 0.0
/*242 */         }                                                                                       // 0.0
/*246 */         /* XXX: same protocol for all streams is required */                                    // 0.0
/*248 */         if (i > 0) {                                                                            // 0.0
/*250 */             if (reply->transports[0].protocol != rt->protocol) {                                // 0.0
/*252 */                 err = AVERROR_INVALIDDATA;                                                      // 0.0
/*254 */                 goto fail;                                                                      // 0.0
/*256 */             }                                                                                   // 0.0
/*258 */         } else {                                                                                // 0.0
/*260 */             rt->protocol = reply->transports[0].protocol;                                       // 0.0
/*262 */         }                                                                                       // 0.0
/*266 */         /* close RTP connection if not choosen */                                               // 0.0
/*268 */         if (reply->transports[0].protocol != RTSP_PROTOCOL_RTP_UDP &&                           // 0.0
/*270 */             (protocol_mask & (1 << RTSP_PROTOCOL_RTP_UDP))) {                                   // 0.0
/*272 */             av_close_input_file(rtsp_st->ic);                                                   // 0.0
/*274 */             rtsp_st->ic = NULL;                                                                 // 0.0
/*276 */         }                                                                                       // 0.0
/*280 */         switch(reply->transports[0].protocol) {                                                 // 0.0
/*282 */         case RTSP_PROTOCOL_RTP_TCP:                                                             // 0.0
/*284 */             fmt = &rtp_demux;                                                                   // 0.0
/*286 */             if (av_open_input_file(&rtsp_st->ic, "null", fmt, 0, NULL) < 0) {                   // 0.0
/*288 */                 err = AVERROR_INVALIDDATA;                                                      // 0.0
/*290 */                 goto fail;                                                                      // 0.0
/*292 */             }                                                                                   // 0.0
/*294 */             rtsp_st->interleaved_min = reply->transports[0].interleaved_min;                    // 0.0
/*296 */             rtsp_st->interleaved_max = reply->transports[0].interleaved_max;                    // 0.0
/*298 */             break;                                                                              // 0.0
/*300 */                                                                                                 // 0.0
/*302 */         case RTSP_PROTOCOL_RTP_UDP:                                                             // 0.0
/*304 */             {                                                                                   // 0.0
/*306 */                 char url[1024];                                                                 // 0.0
/*308 */                                                                                                 // 0.0
/*310 */                 /* XXX: also use address if specified */                                        // 0.0
/*312 */                 snprintf(url, sizeof(url), "rtp://%s:%d",                                       // 0.0
/*314 */                          host, reply->transports[0].server_port_min);                           // 0.0
/*316 */                 if (rtp_set_remote_url(url_fileno(&rtsp_st->ic->pb), url) < 0) {                // 0.0
/*318 */                     err = AVERROR_INVALIDDATA;                                                  // 0.0
/*320 */                     goto fail;                                                                  // 0.0
/*322 */                 }                                                                               // 0.0
/*324 */             }                                                                                   // 0.0
/*326 */             break;                                                                              // 0.0
/*328 */         case RTSP_PROTOCOL_RTP_UDP_MULTICAST:                                                   // 0.0
/*330 */             {                                                                                   // 0.0
/*332 */                 char url[1024];                                                                 // 0.0
/*334 */                 int ttl;                                                                        // 0.0
/*338 */                 fmt = &rtp_demux;                                                               // 0.0
/*340 */                 ttl = reply->transports[0].ttl;                                                 // 0.0
/*342 */                 if (!ttl)                                                                       // 0.0
/*344 */                     ttl = 16;                                                                   // 0.0
/*346 */                 snprintf(url, sizeof(url), "rtp://%s:%d?multicast=1&ttl=%d",                    // 0.0
/*348 */                          host,                                                                  // 0.0
/*350 */                          reply->transports[0].server_port_min,                                  // 0.0
/*352 */                          ttl);                                                                  // 0.0
/*354 */                 if (av_open_input_file(&rtsp_st->ic, url, fmt, 0, NULL) < 0) {                  // 0.0
/*356 */                     err = AVERROR_INVALIDDATA;                                                  // 0.0
/*358 */                     goto fail;                                                                  // 0.0
/*360 */                 }                                                                               // 0.0
/*362 */             }                                                                                   // 0.0
/*364 */             break;                                                                              // 0.0
/*366 */         }                                                                                       // 0.0
/*368 */     }                                                                                           // 0.0
/*372 */     /* use callback if available to extend setup */                                             // 0.0
/*374 */     if (ff_rtsp_callback) {                                                                     // 0.0
/*376 */         if (ff_rtsp_callback(RTSP_ACTION_CLIENT_SETUP, rt->session_id,                          // 0.0
/*378 */                              NULL, 0, rt->last_reply) < 0) {                                    // 0.0
/*380 */             err = AVERROR_INVALIDDATA;                                                          // 0.0
/*382 */             goto fail;                                                                          // 0.0
/*384 */         }                                                                                       // 0.0
/*386 */     }                                                                                           // 0.0
/*388 */                                                                                                 // 0.0
/*390 */     /* start playing */                                                                         // 0.0
/*392 */     snprintf(cmd, sizeof(cmd),                                                                  // 0.0
/*394 */              "PLAY %s RTSP/1.0\r\n"                                                             // 0.0
/*396 */              "Range: npt=0-\r\n",                                                               // 0.0
/*398 */              s->filename);                                                                      // 0.0
/*400 */     rtsp_send_cmd(s, cmd, reply, NULL);                                                         // 0.0
/*402 */     if (reply->status_code != RTSP_STATUS_OK) {                                                 // 0.0
/*404 */         err = AVERROR_INVALIDDATA;                                                              // 0.0
/*406 */         goto fail;                                                                              // 0.0
/*408 */     }                                                                                           // 0.0
/*412 */ #if 0                                                                                           // 0.0
/*414 */     /* open TCP with bufferized input */                                                        // 0.0
/*416 */     if (rt->protocol == RTSP_PROTOCOL_RTP_TCP) {                                                // 0.0
/*418 */         if (url_fdopen(&rt->rtsp_gb, rt->rtsp_hd) < 0) {                                        // 0.0
/*420 */             err = AVERROR_NOMEM;                                                                // 0.0
/*422 */             goto fail;                                                                          // 0.0
/*424 */         }                                                                                       // 0.0
/*426 */     }                                                                                           // 0.0
/*428 */ #endif                                                                                          // 0.0
/*432 */     return 0;                                                                                   // 0.0
/*434 */  fail:                                                                                          // 0.0
/*436 */     for(i=0;i<s->nb_streams;i++) {                                                              // 0.0
/*438 */         st = s->streams[i];                                                                     // 0.0
/*440 */         rtsp_st = st->priv_data;                                                                // 0.0
/*442 */         if (rtsp_st) {                                                                          // 0.0
/*444 */             if (rtsp_st->ic)                                                                    // 0.0
/*446 */                 av_close_input_file(rtsp_st->ic);                                               // 0.0
/*448 */         }                                                                                       // 0.0
/*450 */         av_free(rtsp_st);                                                                       // 0.0
/*452 */     }                                                                                           // 0.0
/*454 */     av_freep(&content);                                                                         // 0.0
/*456 */     url_close(rt->rtsp_hd);                                                                     // 0.0
/*458 */     return err;                                                                                 // 0.0
/*460 */ }                                                                                               // 0.0
