// commit message FFmpeg@170870b77c (target=1, prob=0.4348193, correct=False): Don't forget to set known audio parameters (samplerate, etc.) if the codec is not supported in FFmpeg. This will cause crashes later because the samplerate is used to initialize the timebase.
/*0   */ static int sdp_parse_rtpmap(AVFormatContext *s,                              // (13) 0.0332
/*2   */                             AVCodecContext *codec, RTSPStream *rtsp_st,      // (0) 0.08789
/*4   */                             int payload_type, const char *p)                 // (2) 0.07227
/*6   */ {                                                                            // (22) 0.001953
/*8   */     char buf[256];                                                           // (20) 0.01563
/*10  */     int i;                                                                   // (21) 0.01172
/*12  */     AVCodec *c;                                                              // (19) 0.01758
/*14  */     const char *c_name;                                                      // (18) 0.01953
/*18  */     /* Loop into AVRtpDynamicPayloadTypes[] and AVRtpPayloadTypes[] and      // (7) 0.04492
/*20  */      * see if we can handle this kind of payload.                            // (16) 0.0293
/*22  */      * The space should normally not be there but some Real streams or       // (14) 0.0332
/*24  */      * particular servers ("RealServer Version 6.1.3.970", see issue 1658)   // (6) 0.04688
/*26  */      * have a trailing space. */                                             // (17) 0.02148
/*28  */     get_word_sep(buf, sizeof(buf), "/ ", &p);                                // (8) 0.04102
/*30  */     if (payload_type >= RTP_PT_PRIVATE) {                                    // (11) 0.03906
/*32  */         RTPDynamicProtocolHandler *handler;                                  // (15) 0.03125
/*34  */         for (handler = RTPFirstDynamicPayloadHandler;                        // (12) 0.03711
/*36  */              handler; handler = handler->next) {                             // (9) 0.04102
/*38  */             if (!strcasecmp(buf, handler->enc_name) &&                       // (5) 0.05078
/*40  */                 codec->codec_type == handler->codec_type) {                  // (3) 0.05859
/*42  */                 codec->codec_id          = handler->codec_id;                // (1) 0.07422
/*44  */                 rtsp_st->dynamic_handler = handler;                          // (4) 0.05469
/*46  */                 if (handler->open)                                           // (10) 0.04102
/*48  */                     rtsp_st->dynamic_protocol_context = handler->open();     // 0.0
/*50  */                 break;                                                       // 0.0
/*52  */             }                                                                // 0.0
/*54  */         }                                                                    // 0.0
/*56  */     } else {                                                                 // 0.0
/*58  */         /* We are in a standard case                                         // 0.0
/*60  */          * (from http://www.iana.org/assignments/rtp-parameters). */         // 0.0
/*62  */         /* search into AVRtpPayloadTypes[] */                                // 0.0
/*64  */         codec->codec_id = ff_rtp_codec_id(buf, codec->codec_type);           // 0.0
/*66  */     }                                                                        // 0.0
/*70  */     c = avcodec_find_decoder(codec->codec_id);                               // 0.0
/*72  */     if (c && c->name)                                                        // 0.0
/*74  */         c_name = c->name;                                                    // 0.0
/*76  */     else                                                                     // 0.0
/*78  */         c_name = (char *) NULL;                                              // 0.0
/*82  */     if (c_name) {                                                            // 0.0
/*84  */         get_word_sep(buf, sizeof(buf), "/", &p);                             // 0.0
/*86  */         i = atoi(buf);                                                       // 0.0
/*88  */         switch (codec->codec_type) {                                         // 0.0
/*90  */         case CODEC_TYPE_AUDIO:                                               // 0.0
/*92  */             av_log(s, AV_LOG_DEBUG, "audio codec set to: %s\n", c_name);     // 0.0
/*94  */             codec->sample_rate = RTSP_DEFAULT_AUDIO_SAMPLERATE;              // 0.0
/*96  */             codec->channels = RTSP_DEFAULT_NB_AUDIO_CHANNELS;                // 0.0
/*98  */             if (i > 0) {                                                     // 0.0
/*100 */                 codec->sample_rate = i;                                      // 0.0
/*102 */                 get_word_sep(buf, sizeof(buf), "/", &p);                     // 0.0
/*104 */                 i = atoi(buf);                                               // 0.0
/*106 */                 if (i > 0)                                                   // 0.0
/*108 */                     codec->channels = i;                                     // 0.0
/*110 */                 // TODO: there is a bug here; if it is a mono stream, and    // 0.0
/*112 */                 // less than 22000Hz, faad upconverts to stereo and twice    // 0.0
/*114 */                 // the frequency.  No problem, but the sample rate is being  // 0.0
/*116 */                 // set here by the sdp line. Patch on its way. (rdm)         // 0.0
/*118 */             }                                                                // 0.0
/*120 */             av_log(s, AV_LOG_DEBUG, "audio samplerate set to: %i\n",         // 0.0
/*122 */                    codec->sample_rate);                                      // 0.0
/*124 */             av_log(s, AV_LOG_DEBUG, "audio channels set to: %i\n",           // 0.0
/*126 */                    codec->channels);                                         // 0.0
/*128 */             break;                                                           // 0.0
/*130 */         case CODEC_TYPE_VIDEO:                                               // 0.0
/*132 */             av_log(s, AV_LOG_DEBUG, "video codec set to: %s\n", c_name);     // 0.0
/*134 */             break;                                                           // 0.0
/*136 */         default:                                                             // 0.0
/*138 */             break;                                                           // 0.0
/*140 */         }                                                                    // 0.0
/*142 */         return 0;                                                            // 0.0
/*144 */     }                                                                        // 0.0
/*148 */     return -1;                                                               // 0.0
/*150 */ }                                                                            // 0.0
