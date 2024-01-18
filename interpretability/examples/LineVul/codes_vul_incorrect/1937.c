// commit message FFmpeg@ec4c483976 (target=1, prob=0.4095068, correct=False): lavf: add a protocol whitelist/blacklist for file opened internally
/*0   */ static int rtsp_listen(AVFormatContext *s)                                      // (13) 0.0293
/*2   */ {                                                                               // (31) 0.001955
/*4   */     RTSPState *rt = s->priv_data;                                               // (12) 0.0293
/*6   */     char proto[128], host[128], path[512], auth[128];                           // (7) 0.03906
/*8   */     char uri[500];                                                              // (25) 0.01758
/*10  */     int port;                                                                   // (28) 0.01172
/*12  */     int default_port = RTSP_DEFAULT_PORT;                                       // (11) 0.03125
/*14  */     char tcpname[500];                                                          // (22) 0.01758
/*16  */     const char *lower_proto = "tcp";                                            // (14) 0.0293
/*18  */     unsigned char rbuf[4096];                                                   // (18) 0.02148
/*20  */     unsigned char method[10];                                                   // (24) 0.01758
/*22  */     int rbuflen = 0;                                                            // (19) 0.02148
/*24  */     int ret;                                                                    // (27) 0.01172
/*26  */     enum RTSPMethod methodcode;                                                 // (21) 0.01953
/*30  */     if (!rt->protocols) {                                                       // (17) 0.02344
/*32  */         rt->protocols = ffurl_get_protocols(NULL, NULL);                        // (3) 0.05273
/*34  */         if (!rt->protocols)                                                     // (15) 0.0293
/*36  */             return AVERROR(ENOMEM);                                             // (5) 0.03906
/*38  */     }                                                                           // (29) 0.007812
/*42  */     /* extract hostname and port */                                             // (20) 0.01953
/*44  */     av_url_split(proto, sizeof(proto), auth, sizeof(auth), host, sizeof(host),  // (0) 0.05664
/*46  */                  &port, path, sizeof(path), s->filename);                       // (1) 0.05664
/*50  */     /* ff_url_join. No authorization by now (NULL) */                           // (8) 0.03516
/*52  */     ff_url_join(rt->control_uri, sizeof(rt->control_uri), proto, NULL, host,    // (2) 0.05664
/*54  */                 port, "%s", path);                                              // (4) 0.04297
/*58  */     if (!strcmp(proto, "rtsps")) {                                              // (9) 0.0332
/*60  */         lower_proto  = "tls";                                                   // (10) 0.0332
/*62  */         default_port = RTSPS_DEFAULT_PORT;                                      // (6) 0.03906
/*64  */     }                                                                           // (30) 0.007812
/*68  */     if (port < 0)                                                               // (23) 0.01758
/*70  */         port = default_port;                                                    // (16) 0.02539
/*74  */     /* Create TCP connection */                                                 // (26) 0.01562
/*76  */     ff_url_join(tcpname, sizeof(tcpname), lower_proto, NULL, host, port,        // 0.0
/*78  */                 "?listen&listen_timeout=%d", rt->initial_timeout * 1000);       // 0.0
/*82  */     if (ret = ffurl_open(&rt->rtsp_hd, tcpname, AVIO_FLAG_READ_WRITE,           // 0.0
/*84  */                          &s->interrupt_callback, NULL, rt->protocols)) {        // 0.0
/*86  */         av_log(s, AV_LOG_ERROR, "Unable to open RTSP for listening\n");         // 0.0
/*88  */         return ret;                                                             // 0.0
/*90  */     }                                                                           // 0.0
/*92  */     rt->state       = RTSP_STATE_IDLE;                                          // 0.0
/*94  */     rt->rtsp_hd_out = rt->rtsp_hd;                                              // 0.0
/*96  */     for (;;) { /* Wait for incoming RTSP messages */                            // 0.0
/*98  */         ret = read_line(s, rbuf, sizeof(rbuf), &rbuflen);                       // 0.0
/*100 */         if (ret < 0)                                                            // 0.0
/*102 */             return ret;                                                         // 0.0
/*104 */         ret = parse_command_line(s, rbuf, rbuflen, uri, sizeof(uri), method,    // 0.0
/*106 */                                  sizeof(method), &methodcode);                  // 0.0
/*108 */         if (ret) {                                                              // 0.0
/*110 */             av_log(s, AV_LOG_ERROR, "RTSP: Unexpected Command\n");              // 0.0
/*112 */             return ret;                                                         // 0.0
/*114 */         }                                                                       // 0.0
/*118 */         if (methodcode == ANNOUNCE) {                                           // 0.0
/*120 */             ret       = rtsp_read_announce(s);                                  // 0.0
/*122 */             rt->state = RTSP_STATE_PAUSED;                                      // 0.0
/*124 */         } else if (methodcode == OPTIONS) {                                     // 0.0
/*126 */             ret = rtsp_read_options(s);                                         // 0.0
/*128 */         } else if (methodcode == RECORD) {                                      // 0.0
/*130 */             ret = rtsp_read_record(s);                                          // 0.0
/*132 */             if (!ret)                                                           // 0.0
/*134 */                 return 0; // We are ready for streaming                         // 0.0
/*136 */         } else if (methodcode == SETUP)                                         // 0.0
/*138 */             ret = rtsp_read_setup(s, host, uri);                                // 0.0
/*140 */         if (ret) {                                                              // 0.0
/*142 */             ffurl_close(rt->rtsp_hd);                                           // 0.0
/*144 */             return AVERROR_INVALIDDATA;                                         // 0.0
/*146 */         }                                                                       // 0.0
/*148 */     }                                                                           // 0.0
/*150 */     return 0;                                                                   // 0.0
/*152 */ }                                                                               // 0.0
