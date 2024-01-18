// commit message FFmpeg@62c3c8ca78 (target=1, prob=0.45456317, correct=False): rtsp: Don't use uninitialized data if there are no streams
/*0   */ int ff_rtsp_make_setup_request(AVFormatContext *s, const char *host, int port,     // (3) 0.05273
/*2   */                               int lower_transport, const char *real_challenge)     // (0) 0.08398
/*4   */ {                                                                                  // (26) 0.001953
/*6   */     RTSPState *rt = s->priv_data;                                                  // (13) 0.0293
/*8   */     int rtx = 0, j, i, err, interleave = 0, port_off;                              // (4) 0.04688
/*10  */     RTSPStream *rtsp_st;                                                           // (17) 0.02539
/*12  */     RTSPMessageHeader reply1, *reply = &reply1;                                    // (10) 0.0332
/*14  */     char cmd[2048];                                                                // (21) 0.01758
/*16  */     const char *trans_pref;                                                        // (18) 0.02148
/*20  */     if (rt->transport == RTSP_TRANSPORT_RDT)                                       // (5) 0.04102
/*22  */         trans_pref = "x-pn-tng";                                                   // (7) 0.03906
/*24  */     else                                                                           // (25) 0.007812
/*26  */         trans_pref = "RTP/AVP";                                                    // (8) 0.03711
/*30  */     /* default timeout: 1 minute */                                                // (19) 0.01953
/*32  */     rt->timeout = 60;                                                              // (20) 0.01953
/*36  */     /* for each stream, make the setup request */                                  // (16) 0.02539
/*38  */     /* XXX: we assume the same server is used for the control of each              // (9) 0.03516
/*40  */      * RTSP stream */                                                              // (22) 0.01758
/*44  */     /* Choose a random starting offset within the first half of the                // (12) 0.0293
/*46  */      * port range, to allow for a number of ports to try even if the offset        // (6) 0.04102
/*48  */      * happens to be at the end of the random range. */                            // (11) 0.0332
/*50  */     port_off = av_get_random_seed() % ((rt->rtp_port_max - rt->rtp_port_min)/2);   // (2) 0.07422
/*52  */     /* even random offset */                                                       // (24) 0.01562
/*54  */     port_off -= port_off & 0x01;                                                   // (14) 0.0293
/*58  */     for (j = rt->rtp_port_min + port_off, i = 0; i < rt->nb_rtsp_streams; ++i) {   // (1) 0.08398
/*60  */         char transport[2048];                                                      // (15) 0.02539
/*64  */         /*                                                                         // (23) 0.01562
/*66  */          * WMS serves all UDP data over a single connection, the RTX, which        // 0.0
/*68  */          * isn't necessarily the first in the SDP but has to be the first          // 0.0
/*70  */          * to be set up, else the second/third SETUP will fail with a 461.         // 0.0
/*72  */          */                                                                        // 0.0
/*74  */         if (lower_transport == RTSP_LOWER_TRANSPORT_UDP &&                         // 0.0
/*76  */              rt->server_type == RTSP_SERVER_WMS) {                                 // 0.0
/*78  */             if (i == 0) {                                                          // 0.0
/*80  */                 /* rtx first */                                                    // 0.0
/*82  */                 for (rtx = 0; rtx < rt->nb_rtsp_streams; rtx++) {                  // 0.0
/*84  */                     int len = strlen(rt->rtsp_streams[rtx]->control_url);          // 0.0
/*86  */                     if (len >= 4 &&                                                // 0.0
/*88  */                         !strcmp(rt->rtsp_streams[rtx]->control_url + len - 4,      // 0.0
/*90  */                                 "/rtx"))                                           // 0.0
/*92  */                         break;                                                     // 0.0
/*94  */                 }                                                                  // 0.0
/*96  */                 if (rtx == rt->nb_rtsp_streams)                                    // 0.0
/*98  */                     return -1; /* no RTX found */                                  // 0.0
/*100 */                 rtsp_st = rt->rtsp_streams[rtx];                                   // 0.0
/*102 */             } else                                                                 // 0.0
/*104 */                 rtsp_st = rt->rtsp_streams[i > rtx ? i : i - 1];                   // 0.0
/*106 */         } else                                                                     // 0.0
/*108 */             rtsp_st = rt->rtsp_streams[i];                                         // 0.0
/*112 */         /* RTP/UDP */                                                              // 0.0
/*114 */         if (lower_transport == RTSP_LOWER_TRANSPORT_UDP) {                         // 0.0
/*116 */             char buf[256];                                                         // 0.0
/*120 */             if (rt->server_type == RTSP_SERVER_WMS && i > 1) {                     // 0.0
/*122 */                 port = reply->transports[0].client_port_min;                       // 0.0
/*124 */                 goto have_port;                                                    // 0.0
/*126 */             }                                                                      // 0.0
/*130 */             /* first try in specified port range */                                // 0.0
/*132 */             while (j <= rt->rtp_port_max) {                                        // 0.0
/*134 */                 ff_url_join(buf, sizeof(buf), "rtp", NULL, host, -1,               // 0.0
/*136 */                             "?localport=%d", j);                                   // 0.0
/*138 */                 /* we will use two ports per rtp stream (rtp and rtcp) */          // 0.0
/*140 */                 j += 2;                                                            // 0.0
/*142 */                 if (!ffurl_open(&rtsp_st->rtp_handle, buf, AVIO_FLAG_READ_WRITE,   // 0.0
/*144 */                                &s->interrupt_callback, NULL))                      // 0.0
/*146 */                     goto rtp_opened;                                               // 0.0
/*148 */             }                                                                      // 0.0
/*152 */             av_log(s, AV_LOG_ERROR, "Unable to open an input RTP port\n");         // 0.0
/*154 */             err = AVERROR(EIO);                                                    // 0.0
/*156 */             goto fail;                                                             // 0.0
/*160 */         rtp_opened:                                                                // 0.0
/*162 */             port = ff_rtp_get_local_rtp_port(rtsp_st->rtp_handle);                 // 0.0
/*164 */         have_port:                                                                 // 0.0
/*166 */             snprintf(transport, sizeof(transport) - 1,                             // 0.0
/*168 */                      "%s/UDP;", trans_pref);                                       // 0.0
/*170 */             if (rt->server_type != RTSP_SERVER_REAL)                               // 0.0
/*172 */                 av_strlcat(transport, "unicast;", sizeof(transport));              // 0.0
/*174 */             av_strlcatf(transport, sizeof(transport),                              // 0.0
/*176 */                      "client_port=%d", port);                                      // 0.0
/*178 */             if (rt->transport == RTSP_TRANSPORT_RTP &&                             // 0.0
/*180 */                 !(rt->server_type == RTSP_SERVER_WMS && i > 0))                    // 0.0
/*182 */                 av_strlcatf(transport, sizeof(transport), "-%d", port + 1);        // 0.0
/*184 */         }                                                                          // 0.0
/*188 */         /* RTP/TCP */                                                              // 0.0
/*190 */         else if (lower_transport == RTSP_LOWER_TRANSPORT_TCP) {                    // 0.0
/*192 */             /* For WMS streams, the application streams are only used for          // 0.0
/*194 */              * UDP. When trying to set it up for TCP streams, the server           // 0.0
/*196 */              * will return an error. Therefore, we skip those streams. */          // 0.0
/*198 */             if (rt->server_type == RTSP_SERVER_WMS &&                              // 0.0
/*200 */                 (rtsp_st->stream_index < 0 ||                                      // 0.0
/*202 */                  s->streams[rtsp_st->stream_index]->codec->codec_type ==           // 0.0
/*204 */                     AVMEDIA_TYPE_DATA))                                            // 0.0
/*206 */                 continue;                                                          // 0.0
/*208 */             snprintf(transport, sizeof(transport) - 1,                             // 0.0
/*210 */                      "%s/TCP;", trans_pref);                                       // 0.0
/*212 */             if (rt->transport != RTSP_TRANSPORT_RDT)                               // 0.0
/*214 */                 av_strlcat(transport, "unicast;", sizeof(transport));              // 0.0
/*216 */             av_strlcatf(transport, sizeof(transport),                              // 0.0
/*218 */                         "interleaved=%d-%d",                                       // 0.0
/*220 */                         interleave, interleave + 1);                               // 0.0
/*222 */             interleave += 2;                                                       // 0.0
/*224 */         }                                                                          // 0.0
/*228 */         else if (lower_transport == RTSP_LOWER_TRANSPORT_UDP_MULTICAST) {          // 0.0
/*230 */             snprintf(transport, sizeof(transport) - 1,                             // 0.0
/*232 */                      "%s/UDP;multicast", trans_pref);                              // 0.0
/*234 */         }                                                                          // 0.0
/*236 */         if (s->oformat) {                                                          // 0.0
/*238 */             av_strlcat(transport, ";mode=receive", sizeof(transport));             // 0.0
/*240 */         } else if (rt->server_type == RTSP_SERVER_REAL ||                          // 0.0
/*242 */                    rt->server_type == RTSP_SERVER_WMS)                             // 0.0
/*244 */             av_strlcat(transport, ";mode=play", sizeof(transport));                // 0.0
/*246 */         snprintf(cmd, sizeof(cmd),                                                 // 0.0
/*248 */                  "Transport: %s\r\n",                                              // 0.0
/*250 */                  transport);                                                       // 0.0
/*252 */         if (rt->accept_dynamic_rate)                                               // 0.0
/*254 */             av_strlcat(cmd, "x-Dynamic-Rate: 0\r\n", sizeof(cmd));                 // 0.0
/*256 */         if (i == 0 && rt->server_type == RTSP_SERVER_REAL && CONFIG_RTPDEC) {      // 0.0
/*258 */             char real_res[41], real_csum[9];                                       // 0.0
/*260 */             ff_rdt_calc_response_and_checksum(real_res, real_csum,                 // 0.0
/*262 */                                               real_challenge);                     // 0.0
/*264 */             av_strlcatf(cmd, sizeof(cmd),                                          // 0.0
/*266 */                         "If-Match: %s\r\n"                                         // 0.0
/*268 */                         "RealChallenge2: %s, sd=%s\r\n",                           // 0.0
/*270 */                         rt->session_id, real_res, real_csum);                      // 0.0
/*272 */         }                                                                          // 0.0
/*274 */         ff_rtsp_send_cmd(s, "SETUP", rtsp_st->control_url, cmd, reply, NULL);      // 0.0
/*276 */         if (reply->status_code == 461 /* Unsupported protocol */ && i == 0) {      // 0.0
/*278 */             err = 1;                                                               // 0.0
/*280 */             goto fail;                                                             // 0.0
/*282 */         } else if (reply->status_code != RTSP_STATUS_OK ||                         // 0.0
/*284 */                    reply->nb_transports != 1) {                                    // 0.0
/*286 */             err = AVERROR_INVALIDDATA;                                             // 0.0
/*288 */             goto fail;                                                             // 0.0
/*290 */         }                                                                          // 0.0
/*294 */         /* XXX: same protocol for all streams is required */                       // 0.0
/*296 */         if (i > 0) {                                                               // 0.0
/*298 */             if (reply->transports[0].lower_transport != rt->lower_transport ||     // 0.0
/*300 */                 reply->transports[0].transport != rt->transport) {                 // 0.0
/*302 */                 err = AVERROR_INVALIDDATA;                                         // 0.0
/*304 */                 goto fail;                                                         // 0.0
/*306 */             }                                                                      // 0.0
/*308 */         } else {                                                                   // 0.0
/*310 */             rt->lower_transport = reply->transports[0].lower_transport;            // 0.0
/*312 */             rt->transport = reply->transports[0].transport;                        // 0.0
/*314 */         }                                                                          // 0.0
/*318 */         /* Fail if the server responded with another lower transport mode          // 0.0
/*320 */          * than what we requested. */                                              // 0.0
/*322 */         if (reply->transports[0].lower_transport != lower_transport) {             // 0.0
/*324 */             av_log(s, AV_LOG_ERROR, "Nonmatching transport in server reply\n");    // 0.0
/*326 */             err = AVERROR_INVALIDDATA;                                             // 0.0
/*328 */             goto fail;                                                             // 0.0
/*330 */         }                                                                          // 0.0
/*334 */         switch(reply->transports[0].lower_transport) {                             // 0.0
/*336 */         case RTSP_LOWER_TRANSPORT_TCP:                                             // 0.0
/*338 */             rtsp_st->interleaved_min = reply->transports[0].interleaved_min;       // 0.0
/*340 */             rtsp_st->interleaved_max = reply->transports[0].interleaved_max;       // 0.0
/*342 */             break;                                                                 // 0.0
/*346 */         case RTSP_LOWER_TRANSPORT_UDP: {                                           // 0.0
/*348 */             char url[1024], options[30] = "";                                      // 0.0
/*352 */             if (rt->rtsp_flags & RTSP_FLAG_FILTER_SRC)                             // 0.0
/*354 */                 av_strlcpy(options, "?connect=1", sizeof(options));                // 0.0
/*356 */             /* Use source address if specified */                                  // 0.0
/*358 */             if (reply->transports[0].source[0]) {                                  // 0.0
/*360 */                 ff_url_join(url, sizeof(url), "rtp", NULL,                         // 0.0
/*362 */                             reply->transports[0].source,                           // 0.0
/*364 */                             reply->transports[0].server_port_min, "%s", options);  // 0.0
/*366 */             } else {                                                               // 0.0
/*368 */                 ff_url_join(url, sizeof(url), "rtp", NULL, host,                   // 0.0
/*370 */                             reply->transports[0].server_port_min, "%s", options);  // 0.0
/*372 */             }                                                                      // 0.0
/*374 */             if (!(rt->server_type == RTSP_SERVER_WMS && i > 1) &&                  // 0.0
/*376 */                 ff_rtp_set_remote_url(rtsp_st->rtp_handle, url) < 0) {             // 0.0
/*378 */                 err = AVERROR_INVALIDDATA;                                         // 0.0
/*380 */                 goto fail;                                                         // 0.0
/*382 */             }                                                                      // 0.0
/*384 */             /* Try to initialize the connection state in a                         // 0.0
/*386 */              * potential NAT router by sending dummy packets.                      // 0.0
/*388 */              * RTP/RTCP dummy packets are used for RDT, too.                       // 0.0
/*390 */              */                                                                    // 0.0
/*392 */             if (!(rt->server_type == RTSP_SERVER_WMS && i > 1) && s->iformat &&    // 0.0
/*394 */                 CONFIG_RTPDEC)                                                     // 0.0
/*396 */                 ff_rtp_send_punch_packets(rtsp_st->rtp_handle);                    // 0.0
/*398 */             break;                                                                 // 0.0
/*400 */         }                                                                          // 0.0
/*402 */         case RTSP_LOWER_TRANSPORT_UDP_MULTICAST: {                                 // 0.0
/*404 */             char url[1024], namebuf[50], optbuf[20] = "";                          // 0.0
/*406 */             struct sockaddr_storage addr;                                          // 0.0
/*408 */             int port, ttl;                                                         // 0.0
/*412 */             if (reply->transports[0].destination.ss_family) {                      // 0.0
/*414 */                 addr      = reply->transports[0].destination;                      // 0.0
/*416 */                 port      = reply->transports[0].port_min;                         // 0.0
/*418 */                 ttl       = reply->transports[0].ttl;                              // 0.0
/*420 */             } else {                                                               // 0.0
/*422 */                 addr      = rtsp_st->sdp_ip;                                       // 0.0
/*424 */                 port      = rtsp_st->sdp_port;                                     // 0.0
/*426 */                 ttl       = rtsp_st->sdp_ttl;                                      // 0.0
/*428 */             }                                                                      // 0.0
/*430 */             if (ttl > 0)                                                           // 0.0
/*432 */                 snprintf(optbuf, sizeof(optbuf), "?ttl=%d", ttl);                  // 0.0
/*434 */             getnameinfo((struct sockaddr*) &addr, sizeof(addr),                    // 0.0
/*436 */                         namebuf, sizeof(namebuf), NULL, 0, NI_NUMERICHOST);        // 0.0
/*438 */             ff_url_join(url, sizeof(url), "rtp", NULL, namebuf,                    // 0.0
/*440 */                         port, "%s", optbuf);                                       // 0.0
/*442 */             if (ffurl_open(&rtsp_st->rtp_handle, url, AVIO_FLAG_READ_WRITE,        // 0.0
/*444 */                            &s->interrupt_callback, NULL) < 0) {                    // 0.0
/*446 */                 err = AVERROR_INVALIDDATA;                                         // 0.0
/*448 */                 goto fail;                                                         // 0.0
/*450 */             }                                                                      // 0.0
/*452 */             break;                                                                 // 0.0
/*454 */         }                                                                          // 0.0
/*456 */         }                                                                          // 0.0
/*460 */         if ((err = rtsp_open_transport_ctx(s, rtsp_st)))                           // 0.0
/*462 */             goto fail;                                                             // 0.0
/*464 */     }                                                                              // 0.0
/*468 */     if (reply->timeout > 0)                                                        // 0.0
/*470 */         rt->timeout = reply->timeout;                                              // 0.0
/*474 */     if (rt->server_type == RTSP_SERVER_REAL)                                       // 0.0
/*476 */         rt->need_subscription = 1;                                                 // 0.0
/*480 */     return 0;                                                                      // 0.0
/*484 */ fail:                                                                              // 0.0
/*486 */     ff_rtsp_undo_setup(s);                                                         // 0.0
/*488 */     return err;                                                                    // 0.0
/*490 */ }                                                                                  // 0.0
