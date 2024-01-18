// commit message FFmpeg@5952b8da0b (target=1, prob=0.4181539, correct=False): tests/api/api-seek-test: Silence compiler warnings about uninitialized variables
/*0   */ static int seek_test(const char *input_filename, const char *start, const char *end)   // (5) 0.005814
/*2   */ {                                                                                      // (32) 0.0002664
/*4   */     AVCodec *codec = NULL;                                                             // (4) 0.0067
/*6   */     AVCodecContext *ctx= NULL;                                                         // (16) 0.002022
/*8   */     AVCodecParameters *origin_par = NULL;                                              // (11) 0.002823
/*10  */     AVFrame *fr = NULL;                                                                // (14) 0.002506
/*12  */     AVFormatContext *fmt_ctx = NULL;                                                   // (6) 0.005347
/*14  */     int video_stream;                                                                  // (21) 0.001241
/*16  */     int result;                                                                        // (25) 0.0007915
/*18  */     int i, j;                                                                          // (30) 0.0004235
/*20  */     long int start_ts, end_ts;                                                         // (28) 0.0005691
/*24  */     size_of_array = 0;                                                                 // (31) 0.0003421
/*26  */     number_of_elements = 0;                                                            // (27) 0.0006256
/*28  */     crc_array = pts_array = NULL;                                                      // (26) 0.000663
/*32  */     result = avformat_open_input(&fmt_ctx, input_filename, NULL, NULL);                // (10) 0.002828
/*34  */     if (result < 0) {                                                                  // (20) 0.00134
/*36  */         av_log(NULL, AV_LOG_ERROR, "Can't open file\n");                               // (18) 0.001732
/*38  */         return result;                                                                 // (24) 0.0008431
/*40  */     }                                                                                  // (29) 0.0004684
/*44  */     result = avformat_find_stream_info(fmt_ctx, NULL);                                 // (12) 0.002812
/*46  */     if (result < 0) {                                                                  // (23) 0.0008721
/*48  */         av_log(NULL, AV_LOG_ERROR, "Can't get stream info\n");                         // (13) 0.002679
/*50  */         return result;                                                                 // (22) 0.001158
/*52  */     }                                                                                  // (19) 0.001535
/*56  */     start_ts = read_seek_range(start);                                                 // (9) 0.002948
/*58  */     end_ts = read_seek_range(end);                                                     // (17) 0.001771
/*60  */     if ((start_ts < 0) || (end_ts < 0))                                                // (3) 0.01265
/*62  */         return -1;                                                                     // (2) 0.06554
/*66  */     //TODO: add ability to work with audio format                                      // (0) 0.6952
/*68  */     video_stream = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);  // (1) 0.07918
/*70  */     if (video_stream < 0) {                                                            // (15) 0.002383
/*72  */       av_log(NULL, AV_LOG_ERROR, "Can't find video stream in input file\n");           // (7) 0.004941
/*74  */       return -1;                                                                       // (8) 0.004434
/*76  */     }                                                                                  // 0.0
/*80  */     origin_par = fmt_ctx->streams[video_stream]->codecpar;                             // 0.0
/*84  */     codec = avcodec_find_decoder(origin_par->codec_id);                                // 0.0
/*86  */     if (!codec) {                                                                      // 0.0
/*88  */         av_log(NULL, AV_LOG_ERROR, "Can't find decoder\n");                            // 0.0
/*90  */         return -1;                                                                     // 0.0
/*92  */     }                                                                                  // 0.0
/*96  */     ctx = avcodec_alloc_context3(codec);                                               // 0.0
/*98  */     if (!ctx) {                                                                        // 0.0
/*100 */         av_log(NULL, AV_LOG_ERROR, "Can't allocate decoder context\n");                // 0.0
/*102 */         return AVERROR(ENOMEM);                                                        // 0.0
/*104 */     }                                                                                  // 0.0
/*108 */     result = avcodec_parameters_to_context(ctx, origin_par);                           // 0.0
/*110 */     if (result) {                                                                      // 0.0
/*112 */         av_log(NULL, AV_LOG_ERROR, "Can't copy decoder context\n");                    // 0.0
/*114 */         return result;                                                                 // 0.0
/*116 */     }                                                                                  // 0.0
/*120 */     result = avcodec_open2(ctx, codec, NULL);                                          // 0.0
/*122 */     if (result < 0) {                                                                  // 0.0
/*124 */         av_log(ctx, AV_LOG_ERROR, "Can't open decoder\n");                             // 0.0
/*126 */         return result;                                                                 // 0.0
/*128 */     }                                                                                  // 0.0
/*132 */     fr = av_frame_alloc();                                                             // 0.0
/*134 */     if (!fr) {                                                                         // 0.0
/*136 */         av_log(NULL, AV_LOG_ERROR, "Can't allocate frame\n");                          // 0.0
/*138 */         return AVERROR(ENOMEM);                                                        // 0.0
/*140 */     }                                                                                  // 0.0
/*144 */     result = compute_crc_of_packets(fmt_ctx, video_stream, ctx, fr, i, j, 1);          // 0.0
/*146 */     if (result != 0)                                                                   // 0.0
/*148 */         return -1;                                                                     // 0.0
/*152 */     for (i = start_ts; i < end_ts; i += 100) {                                         // 0.0
/*154 */         for (j = i + 100; j < end_ts; j += 100)                                        // 0.0
/*156 */         result = compute_crc_of_packets(fmt_ctx, video_stream, ctx, fr, i, j, 0);      // 0.0
/*158 */         if (result != 0)                                                               // 0.0
/*160 */             return -1;                                                                 // 0.0
/*162 */     }                                                                                  // 0.0
/*166 */     av_freep(&crc_array);                                                              // 0.0
/*168 */     av_freep(&pts_array);                                                              // 0.0
/*170 */     av_frame_free(&fr);                                                                // 0.0
/*172 */     avcodec_close(ctx);                                                                // 0.0
/*174 */     avformat_close_input(&fmt_ctx);                                                    // 0.0
/*176 */     avcodec_free_context(&ctx);                                                        // 0.0
/*178 */     return 0;                                                                          // 0.0
/*180 */ }                                                                                      // 0.0
