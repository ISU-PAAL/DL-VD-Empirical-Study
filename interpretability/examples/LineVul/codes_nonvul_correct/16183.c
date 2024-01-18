// commit message FFmpeg@b926b6282d (target=0, prob=0.11414135, correct=True): av_assert() system. With this the developer can now choose if he wants an assert always enabled or at which compile time assert level. This can thus replace the #define NDEBUG hacks
/*0  */ static void opt_new_stream(const char *opt, const char *arg)              // (4) 0.08333
/*2  */ {                                                                         // (11) 0.00463
/*4  */     AVFormatContext *oc;                                                  // (8) 0.04167
/*6  */     if (nb_output_files <= 0) {                                           // (7) 0.06481
/*8  */         fprintf(stderr, "At least one output file must be specified\n");  // (2) 0.1204
/*10 */         ffmpeg_exit(1);                                                   // (6) 0.06481
/*12 */     }                                                                     // (10) 0.01852
/*14 */     oc = output_files[nb_output_files - 1];                               // (5) 0.08333
/*18 */     if      (!strcmp(opt, "newvideo"   )) new_video_stream   (oc);        // (0) 0.1481
/*20 */     else if (!strcmp(opt, "newaudio"   )) new_audio_stream   (oc);        // (1) 0.1296
/*22 */     else if (!strcmp(opt, "newsubtitle")) new_subtitle_stream(oc);        // (3) 0.1157
/*24 */     else assert(0);                                                       // (9) 0.03704
/*26 */ }                                                                         // (12) 0.00463
