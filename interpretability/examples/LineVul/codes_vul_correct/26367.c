// commit message FFmpeg@b97d21e4d6 (target=1, prob=0.6220094, correct=True): rtpdec_h264: Free old extradata before clearing the pointer
/*0   */ static int sdp_parse_fmtp_config_h264(AVStream *stream,                            // (11) 0.04102
/*2   */                                       PayloadContext *h264_data,                   // (0) 0.08984
/*4   */                                       char *attr, char *value)                     // (1) 0.08789
/*6   */ {                                                                                  // (18) 0.001953
/*8   */     AVCodecContext *codec = stream->codec;                                         // (13) 0.03125
/*10  */     assert(codec->codec_id == CODEC_ID_H264);                                      // (9) 0.04297
/*12  */     assert(h264_data != NULL);                                                     // (15) 0.02344
/*16  */     if (!strcmp(attr, "packetization-mode")) {                                     // (12) 0.03516
/*18  */         av_log(codec, AV_LOG_DEBUG, "RTP Packetization Mode: %d\n", atoi(value));  // (4) 0.07422
/*20  */         h264_data->packetization_mode = atoi(value);                               // (8) 0.04492
/*22  */         /*                                                                         // (17) 0.01562
/*24  */          * Packetization Mode:                                                     // (14) 0.02734
/*26  */          * 0 or not present: Single NAL mode (Only nals from 1-23 are allowed)     // (6) 0.05664
/*28  */          * 1: Non-interleaved Mode: 1-23, 24 (STAP-A), 28 (FU-A) are allowed.      // (5) 0.07422
/*30  */          * 2: Interleaved Mode: 25 (STAP-B), 26 (MTAP16), 27 (MTAP24), 28 (FU-A),  // (2) 0.08008
/*32  */          *                      and 29 (FU-B) are allowed.                         // (3) 0.07812
/*34  */          */                                                                        // (16) 0.01758
/*36  */         if (h264_data->packetization_mode > 1)                                     // (10) 0.04297
/*38  */             av_log(codec, AV_LOG_ERROR,                                            // (7) 0.04688
/*40  */                    "Interleaved RTP mode is not supported yet.");                  // 0.0
/*42  */     } else if (!strcmp(attr, "profile-level-id")) {                                // 0.0
/*44  */         if (strlen(value) == 6) {                                                  // 0.0
/*46  */             char buffer[3];                                                        // 0.0
/*48  */             // 6 characters=3 bytes, in hex.                                       // 0.0
/*50  */             uint8_t profile_idc;                                                   // 0.0
/*52  */             uint8_t profile_iop;                                                   // 0.0
/*54  */             uint8_t level_idc;                                                     // 0.0
/*58  */             buffer[0]   = value[0];                                                // 0.0
/*60  */             buffer[1]   = value[1];                                                // 0.0
/*62  */             buffer[2]   = '\0';                                                    // 0.0
/*64  */             profile_idc = strtol(buffer, NULL, 16);                                // 0.0
/*66  */             buffer[0]   = value[2];                                                // 0.0
/*68  */             buffer[1]   = value[3];                                                // 0.0
/*70  */             profile_iop = strtol(buffer, NULL, 16);                                // 0.0
/*72  */             buffer[0]   = value[4];                                                // 0.0
/*74  */             buffer[1]   = value[5];                                                // 0.0
/*76  */             level_idc   = strtol(buffer, NULL, 16);                                // 0.0
/*80  */             av_log(codec, AV_LOG_DEBUG,                                            // 0.0
/*82  */                    "RTP Profile IDC: %x Profile IOP: %x Level: %x\n",              // 0.0
/*84  */                    profile_idc, profile_iop, level_idc);                           // 0.0
/*86  */             h264_data->profile_idc = profile_idc;                                  // 0.0
/*88  */             h264_data->profile_iop = profile_iop;                                  // 0.0
/*90  */             h264_data->level_idc   = level_idc;                                    // 0.0
/*92  */         }                                                                          // 0.0
/*94  */     } else if (!strcmp(attr, "sprop-parameter-sets")) {                            // 0.0
/*96  */         codec->extradata_size = 0;                                                 // 0.0
/*98  */         codec->extradata      = NULL;                                              // 0.0
/*102 */         while (*value) {                                                           // 0.0
/*104 */             char base64packet[1024];                                               // 0.0
/*106 */             uint8_t decoded_packet[1024];                                          // 0.0
/*108 */             int packet_size;                                                       // 0.0
/*110 */             char *dst = base64packet;                                              // 0.0
/*114 */             while (*value && *value != ','                                         // 0.0
/*116 */                    && (dst - base64packet) < sizeof(base64packet) - 1) {           // 0.0
/*118 */                 *dst++ = *value++;                                                 // 0.0
/*120 */             }                                                                      // 0.0
/*122 */             *dst++ = '\0';                                                         // 0.0
/*126 */             if (*value == ',')                                                     // 0.0
/*128 */                 value++;                                                           // 0.0
/*132 */             packet_size = av_base64_decode(decoded_packet, base64packet,           // 0.0
/*134 */                                            sizeof(decoded_packet));                // 0.0
/*136 */             if (packet_size > 0) {                                                 // 0.0
/*138 */                 uint8_t *dest = av_malloc(packet_size + sizeof(start_sequence) +   // 0.0
/*140 */                                           codec->extradata_size +                  // 0.0
/*142 */                                           FF_INPUT_BUFFER_PADDING_SIZE);           // 0.0
/*144 */                 if (!dest) {                                                       // 0.0
/*146 */                     av_log(codec, AV_LOG_ERROR,                                    // 0.0
/*148 */                            "Unable to allocate memory for extradata!");            // 0.0
/*150 */                     return AVERROR(ENOMEM);                                        // 0.0
/*152 */                 }                                                                  // 0.0
/*154 */                 if (codec->extradata_size) {                                       // 0.0
/*156 */                     memcpy(dest, codec->extradata, codec->extradata_size);         // 0.0
/*158 */                     av_free(codec->extradata);                                     // 0.0
/*160 */                 }                                                                  // 0.0
/*164 */                 memcpy(dest + codec->extradata_size, start_sequence,               // 0.0
/*166 */                        sizeof(start_sequence));                                    // 0.0
/*168 */                 memcpy(dest + codec->extradata_size + sizeof(start_sequence),      // 0.0
/*170 */                        decoded_packet, packet_size);                               // 0.0
/*172 */                 memset(dest + codec->extradata_size + sizeof(start_sequence) +     // 0.0
/*174 */                        packet_size, 0, FF_INPUT_BUFFER_PADDING_SIZE);              // 0.0
/*178 */                 codec->extradata       = dest;                                     // 0.0
/*180 */                 codec->extradata_size += sizeof(start_sequence) + packet_size;     // 0.0
/*182 */             }                                                                      // 0.0
/*184 */         }                                                                          // 0.0
/*186 */         av_log(codec, AV_LOG_DEBUG, "Extradata set to %p (size: %d)!",             // 0.0
/*188 */                codec->extradata, codec->extradata_size);                           // 0.0
/*190 */     }                                                                              // 0.0
/*192 */     return 0;                                                                      // 0.0
/*194 */ }                                                                                  // 0.0
