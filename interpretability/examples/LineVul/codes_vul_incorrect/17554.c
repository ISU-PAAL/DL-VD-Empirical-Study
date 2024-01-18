// commit message FFmpeg@f0ca6ffa0a (target=1, prob=0.11056408, correct=False): avprobe: Unref the packet once it is used
/*0  */ static void show_packets(AVFormatContext *fmt_ctx)  // (2) 0.129
/*2  */ {                                                   // (7) 0.008065
/*4  */     AVPacket pkt;                                   // (6) 0.07258
/*8  */     av_init_packet(&pkt);                           // (5) 0.1048
/*10 */     probe_array_header("packets", 0);               // (4) 0.1129
/*12 */     while (!av_read_frame(fmt_ctx, &pkt))           // (1) 0.1613
/*14 */         show_packet(fmt_ctx, &pkt);                 // (0) 0.1694
/*16 */     probe_array_footer("packets", 0);               // (3) 0.121
/*18 */ }                                                   // (8) 0.008065
