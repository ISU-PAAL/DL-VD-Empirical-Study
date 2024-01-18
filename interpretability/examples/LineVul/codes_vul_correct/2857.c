// commit message FFmpeg@8bdba1092f (target=1, prob=0.9459865, correct=True): tools/target_dec_fuzzer: Only audio uses the return value to decode packets in pieces, correct the code to match that
/*0   */ int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {                          // (2) 0.04701
/*2   */     const uint64_t fuzz_tag = FUZZ_TAG;                                                 // (8) 0.03512
/*4   */     FuzzDataBuffer buffer;                                                              // (23) 0.01756
/*6   */     const uint8_t *last = data;                                                         // (16) 0.02536
/*8   */     const uint8_t *end = data + size;                                                   // (11) 0.02926
/*10  */     uint32_t it = 0;                                                                    // (19) 0.02151
/*14  */     if (!c)                                                                             // (28) 0.01377
/*16  */         c = AVCodecInitialize(FFMPEG_CODEC);  // Done once.                             // (1) 0.05508
/*20  */     AVCodecContext* ctx = avcodec_alloc_context3(NULL);                                 // (4) 0.04293
/*22  */     if (!ctx)                                                                           // (30) 0.01365
/*24  */         error("Failed memory allocation");                                              // (15) 0.02731
/*28  */     ctx->max_pixels = 4096 * 4096; //To reduce false positive OOM and hangs             // (3) 0.04684
/*32  */     int res = avcodec_open2(ctx, c, NULL);                                              // (7) 0.03707
/*34  */     if (res < 0)                                                                        // (24) 0.01755
/*36  */         return res;                                                                     // (22) 0.0195
/*40  */     FDBCreate(&buffer);                                                                 // (21) 0.01952
/*42  */     int got_frame;                                                                      // (26) 0.01562
/*44  */     AVFrame *frame = av_frame_alloc();                                                  // (13) 0.02732
/*46  */     if (!frame)                                                                         // (29) 0.01366
/*48  */         error("Failed memory allocation");                                              // (14) 0.02731
/*52  */     // Read very simple container                                                       // (25) 0.01571
/*54  */     AVPacket avpkt;                                                                     // (20) 0.01955
/*56  */     while (data < end && it < maxiteration) {                                           // (10) 0.03124
/*58  */         // Search for the TAG                                                           // (18) 0.02342
/*60  */         while (data + sizeof(fuzz_tag) < end) {                                         // (5) 0.04291
/*62  */             if (data[0] == (fuzz_tag & 0xFF) && *(const uint64_t *)(data) == fuzz_tag)  // (0) 0.08777
/*64  */                 break;                                                                  // (9) 0.03316
/*66  */             data++;                                                                     // (17) 0.02536
/*68  */         }                                                                               // (27) 0.0156
/*70  */         if (data + sizeof(fuzz_tag) > end)                                              // (6) 0.04096
/*72  */             data = end;                                                                 // (12) 0.02926
/*76  */         FDBPrepare(&buffer, &avpkt, last, data - last);                                 // 0.0
/*78  */         data += sizeof(fuzz_tag);                                                       // 0.0
/*80  */         last = data;                                                                    // 0.0
/*84  */         // Iterate through all data                                                     // 0.0
/*86  */         while (avpkt.size > 0 && it++ < maxiteration) {                                 // 0.0
/*88  */             av_frame_unref(frame);                                                      // 0.0
/*90  */             int ret = decode_handler(ctx, frame, &got_frame, &avpkt);                   // 0.0
/*94  */             if (it > 20)                                                                // 0.0
/*96  */                 ctx->error_concealment = 0;                                             // 0.0
/*100 */             if (ret <= 0 || ret > avpkt.size)                                           // 0.0
/*102 */                break;                                                                   // 0.0
/*106 */             avpkt.data += ret;                                                          // 0.0
/*108 */             avpkt.size -= ret;                                                          // 0.0
/*110 */         }                                                                               // 0.0
/*112 */     }                                                                                   // 0.0
/*116 */     av_init_packet(&avpkt);                                                             // 0.0
/*118 */     avpkt.data = NULL;                                                                  // 0.0
/*120 */     avpkt.size = 0;                                                                     // 0.0
/*124 */     do {                                                                                // 0.0
/*126 */         got_frame = 0;                                                                  // 0.0
/*128 */         decode_handler(ctx, frame, &got_frame, &avpkt);                                 // 0.0
/*130 */     } while (got_frame == 1 && it++ < maxiteration);                                    // 0.0
/*134 */     av_frame_free(&frame);                                                              // 0.0
/*136 */     avcodec_free_context(&ctx);                                                         // 0.0
/*138 */     av_freep(&ctx);                                                                     // 0.0
/*140 */     FDBDesroy(&buffer);                                                                 // 0.0
/*142 */     return 0;                                                                           // 0.0
/*144 */ }                                                                                       // 0.0
