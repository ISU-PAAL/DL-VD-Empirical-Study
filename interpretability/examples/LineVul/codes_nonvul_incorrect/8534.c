// commit message FFmpeg@fa2a34cd40 (target=0, prob=0.5470004, correct=False): lavfi: change the filter registering system to match the other libraries
/*0   */ static void exit_program(void)                                                  // (18) 0.01563
/*2   */ {                                                                               // (24) 0.001953
/*4   */     int i, j;                                                                   // (19) 0.01562
/*8   */     for (i = 0; i < nb_filtergraphs; i++) {                                     // (12) 0.04102
/*10  */         avfilter_graph_free(&filtergraphs[i]->graph);                           // (7) 0.04492
/*12  */         for (j = 0; j < filtergraphs[i]->nb_inputs; j++) {                      // (2) 0.05859
/*14  */             av_freep(&filtergraphs[i]->inputs[j]->name);                        // (0) 0.06055
/*16  */             av_freep(&filtergraphs[i]->inputs[j]);                              // (5) 0.05469
/*18  */         }                                                                       // (20) 0.01562
/*20  */         av_freep(&filtergraphs[i]->inputs);                                     // (10) 0.04297
/*22  */         for (j = 0; j < filtergraphs[i]->nb_outputs; j++) {                     // (3) 0.05859
/*24  */             av_freep(&filtergraphs[i]->outputs[j]->name);                       // (1) 0.06055
/*26  */             av_freep(&filtergraphs[i]->outputs[j]);                             // (6) 0.05469
/*28  */         }                                                                       // (21) 0.01562
/*30  */         av_freep(&filtergraphs[i]->outputs);                                    // (11) 0.04297
/*32  */         av_freep(&filtergraphs[i]->graph_desc);                                 // (8) 0.04492
/*34  */         av_freep(&filtergraphs[i]);                                             // (15) 0.03516
/*36  */     }                                                                           // (23) 0.007812
/*38  */     av_freep(&filtergraphs);                                                    // (17) 0.02344
/*42  */     /* close files */                                                           // (22) 0.01367
/*44  */     for (i = 0; i < nb_output_files; i++) {                                     // (13) 0.04102
/*46  */         AVFormatContext *s = output_files[i]->ctx;                              // (9) 0.04297
/*48  */         if (!(s->oformat->flags & AVFMT_NOFILE) && s->pb)                       // (4) 0.05664
/*50  */             avio_close(s->pb);                                                  // (14) 0.03906
/*52  */         avformat_free_context(s);                                               // (16) 0.03125
/*54  */         av_dict_free(&output_files[i]->opts);                                   // 0.0
/*56  */         av_freep(&output_files[i]);                                             // 0.0
/*58  */     }                                                                           // 0.0
/*60  */     for (i = 0; i < nb_output_streams; i++) {                                   // 0.0
/*62  */         AVBitStreamFilterContext *bsfc = output_streams[i]->bitstream_filters;  // 0.0
/*64  */         while (bsfc) {                                                          // 0.0
/*66  */             AVBitStreamFilterContext *next = bsfc->next;                        // 0.0
/*68  */             av_bitstream_filter_close(bsfc);                                    // 0.0
/*70  */             bsfc = next;                                                        // 0.0
/*72  */         }                                                                       // 0.0
/*74  */         output_streams[i]->bitstream_filters = NULL;                            // 0.0
/*76  */         avcodec_free_frame(&output_streams[i]->filtered_frame);                 // 0.0
/*80  */         av_freep(&output_streams[i]->forced_keyframes);                         // 0.0
/*82  */         av_freep(&output_streams[i]->avfilter);                                 // 0.0
/*84  */         av_freep(&output_streams[i]->logfile_prefix);                           // 0.0
/*86  */         av_freep(&output_streams[i]);                                           // 0.0
/*88  */     }                                                                           // 0.0
/*90  */     for (i = 0; i < nb_input_files; i++) {                                      // 0.0
/*92  */         avformat_close_input(&input_files[i]->ctx);                             // 0.0
/*94  */         av_freep(&input_files[i]);                                              // 0.0
/*96  */     }                                                                           // 0.0
/*98  */     for (i = 0; i < nb_input_streams; i++) {                                    // 0.0
/*100 */         av_frame_free(&input_streams[i]->decoded_frame);                        // 0.0
/*102 */         av_frame_free(&input_streams[i]->filter_frame);                         // 0.0
/*104 */         av_dict_free(&input_streams[i]->opts);                                  // 0.0
/*106 */         av_freep(&input_streams[i]->filters);                                   // 0.0
/*108 */         av_freep(&input_streams[i]);                                            // 0.0
/*110 */     }                                                                           // 0.0
/*114 */     if (vstats_file)                                                            // 0.0
/*116 */         fclose(vstats_file);                                                    // 0.0
/*118 */     av_free(vstats_filename);                                                   // 0.0
/*122 */     av_freep(&input_streams);                                                   // 0.0
/*124 */     av_freep(&input_files);                                                     // 0.0
/*126 */     av_freep(&output_streams);                                                  // 0.0
/*128 */     av_freep(&output_files);                                                    // 0.0
/*132 */     uninit_opts();                                                              // 0.0
/*136 */     avfilter_uninit();                                                          // 0.0
/*138 */     avformat_network_deinit();                                                  // 0.0
/*142 */     if (received_sigterm) {                                                     // 0.0
/*144 */         av_log(NULL, AV_LOG_INFO, "Received signal %d: terminating.\n",         // 0.0
/*146 */                (int) received_sigterm);                                         // 0.0
/*148 */         exit (255);                                                             // 0.0
/*150 */     }                                                                           // 0.0
/*152 */ }                                                                               // 0.0
