// commit message FFmpeg@2f9ca64556 (target=0, prob=0.3991488, correct=True): avformat/hls: remove repeated http proto_name checks in open_url()
/*0   */ static int open_url(AVFormatContext *s, AVIOContext **pb, const char *url,                                                                 // (6) 0.04492
/*2   */                     AVDictionary *opts, AVDictionary *opts2, int *is_http)                                                                 // (1) 0.07812
/*4   */ {                                                                                                                                          // (23) 0.001954
/*6   */     HLSContext *c = s->priv_data;                                                                                                          // (15) 0.0293
/*8   */     AVDictionary *tmp = NULL;                                                                                                              // (18) 0.02148
/*10  */     const char *proto_name = NULL;                                                                                                         // (17) 0.02539
/*12  */     int ret;                                                                                                                               // (21) 0.01172
/*16  */     av_dict_copy(&tmp, opts, 0);                                                                                                           // (14) 0.03125
/*18  */     av_dict_copy(&tmp, opts2, 0);                                                                                                          // (12) 0.0332
/*22  */     if (av_strstart(url, "crypto", NULL)) {                                                                                                // (10) 0.03711
/*24  */         if (url[6] == '+' || url[6] == ':')                                                                                                // (5) 0.05078
/*26  */             proto_name = avio_find_protocol_name(url + 7);                                                                                 // (4) 0.05664
/*28  */     }                                                                                                                                      // (22) 0.007812
/*32  */     if (!proto_name)                                                                                                                       // (19) 0.01953
/*34  */         proto_name = avio_find_protocol_name(url);                                                                                         // (8) 0.04492
/*38  */     if (!proto_name)                                                                                                                       // (20) 0.01953
/*40  */         return AVERROR_INVALIDDATA;                                                                                                        // (11) 0.0332
/*44  */     // only http(s) & file are allowed                                                                                                     // (16) 0.02539
/*46  */     if (av_strstart(proto_name, "file", NULL)) {                                                                                           // (9) 0.04102
/*48  */         if (strcmp(c->allowed_extensions, "ALL") && !av_match_ext(url, c->allowed_extensions)) {                                           // (2) 0.07812
/*50  */             av_log(s, AV_LOG_ERROR,                                                                                                        // (7) 0.04492
/*52  */                 "Filename extension of \'%s\' is not a common multimedia extension, blocked for security reasons.\n"                       // (3) 0.07422
/*54  */                 "If you wish to override this adjust allowed_extensions, you can set it to \'ALL\' to allow all\n",                        // (0) 0.08203
/*56  */                 url);                                                                                                                      // (13) 0.0332
/*58  */             return AVERROR_INVALIDDATA;                                                                                                    // 0.0
/*60  */         }                                                                                                                                  // 0.0
/*62  */     } else if (av_strstart(proto_name, "http", NULL)) {                                                                                    // 0.0
/*64  */         ;                                                                                                                                  // 0.0
/*66  */     } else                                                                                                                                 // 0.0
/*68  */         return AVERROR_INVALIDDATA;                                                                                                        // 0.0
/*72  */     if (!strncmp(proto_name, url, strlen(proto_name)) && url[strlen(proto_name)] == ':')                                                   // 0.0
/*74  */         ;                                                                                                                                  // 0.0
/*76  */     else if (av_strstart(url, "crypto", NULL) && !strncmp(proto_name, url + 7, strlen(proto_name)) && url[7 + strlen(proto_name)] == ':')  // 0.0
/*78  */         ;                                                                                                                                  // 0.0
/*80  */     else if (strcmp(proto_name, "file") || !strncmp(url, "file,", 5))                                                                      // 0.0
/*82  */         return AVERROR_INVALIDDATA;                                                                                                        // 0.0
/*86  */     if (c->http_persistent && *pb && av_strstart(proto_name, "http", NULL)) {                                                              // 0.0
/*88  */         ret = open_url_keepalive(c->ctx, pb, url);                                                                                         // 0.0
/*90  */         if (ret == AVERROR_EXIT) {                                                                                                         // 0.0
/*92  */             return ret;                                                                                                                    // 0.0
/*94  */         } else if (ret < 0) {                                                                                                              // 0.0
/*96  */             if (ret != AVERROR_EOF)                                                                                                        // 0.0
/*98  */                 av_log(s, AV_LOG_WARNING,                                                                                                  // 0.0
/*100 */                     "keepalive request failed for '%s', retrying with new connection: %s\n",                                               // 0.0
/*102 */                     url, av_err2str(ret));                                                                                                 // 0.0
/*104 */             ret = s->io_open(s, pb, url, AVIO_FLAG_READ, &tmp);                                                                            // 0.0
/*106 */         }                                                                                                                                  // 0.0
/*108 */     } else {                                                                                                                               // 0.0
/*110 */         ret = s->io_open(s, pb, url, AVIO_FLAG_READ, &tmp);                                                                                // 0.0
/*112 */     }                                                                                                                                      // 0.0
/*114 */     if (ret >= 0) {                                                                                                                        // 0.0
/*116 */         // update cookies on http response with setcookies.                                                                                // 0.0
/*118 */         char *new_cookies = NULL;                                                                                                          // 0.0
/*122 */         if (!(s->flags & AVFMT_FLAG_CUSTOM_IO))                                                                                            // 0.0
/*124 */             av_opt_get(*pb, "cookies", AV_OPT_SEARCH_CHILDREN, (uint8_t**)&new_cookies);                                                   // 0.0
/*128 */         if (new_cookies) {                                                                                                                 // 0.0
/*130 */             av_free(c->cookies);                                                                                                           // 0.0
/*132 */             c->cookies = new_cookies;                                                                                                      // 0.0
/*134 */         }                                                                                                                                  // 0.0
/*138 */         av_dict_set(&opts, "cookies", c->cookies, 0);                                                                                      // 0.0
/*140 */     }                                                                                                                                      // 0.0
/*144 */     av_dict_free(&tmp);                                                                                                                    // 0.0
/*148 */     if (is_http)                                                                                                                           // 0.0
/*150 */         *is_http = av_strstart(proto_name, "http", NULL);                                                                                  // 0.0
/*154 */     return ret;                                                                                                                            // 0.0
/*156 */ }                                                                                                                                          // 0.0
