// commit message FFmpeg@1bfb4587a2 (target=1, prob=0.27104685, correct=False): avutil/tests/audio_fifo.c: Memory leak and tab space fixes
/*0   */ static void test_function(const TestStruct test_sample)                                    // (14) 0.02539
/*2   */ {                                                                                          // (25) 0.001953
/*4   */     int ret, i;                                                                            // (20) 0.01563
/*6   */     void **output_data  = NULL;                                                            // (15) 0.02344
/*8   */     AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample.format, test_sample.nb_ch,       // (3) 0.07422
/*10  */                                             test_sample.nb_samples_pch);                   // (0) 0.1074
/*12  */     if (!afifo) {                                                                          // (16) 0.01953
/*14  */         ERROR("ERROR: av_audio_fifo_alloc returned NULL!");                                // (6) 0.04492
/*16  */     }                                                                                      // (21) 0.007812
/*18  */     ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample.nb_samples_pch, 0);  // (1) 0.07617
/*20  */     if (ret < 0){                                                                          // (17) 0.01758
/*22  */         ERROR("ERROR: av_audio_fifo_write failed!");                                       // (8) 0.04297
/*24  */     }                                                                                      // (22) 0.007812
/*26  */     printf("written: %d\n", ret);                                                          // (13) 0.02734
/*30  */     ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample.nb_samples_pch, 0);  // (2) 0.07617
/*32  */     if (ret < 0){                                                                          // (18) 0.01758
/*34  */         ERROR("ERROR: av_audio_fifo_write failed!");                                       // (7) 0.04297
/*36  */     }                                                                                      // (23) 0.007812
/*38  */     printf("written: %d\n", ret);                                                          // (11) 0.02734
/*40  */     printf("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));          // (5) 0.06641
/*44  */     ret = read_samples_from_audio_fifo(afifo, &output_data, test_sample.nb_samples_pch);   // (4) 0.07422
/*46  */     if (ret < 0){                                                                          // (19) 0.01758
/*48  */         ERROR("ERROR: av_audio_fifo_read failed!");                                        // (9) 0.04297
/*50  */     }                                                                                      // (24) 0.007812
/*52  */     printf("read: %d\n", ret);                                                             // (12) 0.02734
/*54  */     print_audio_bytes(&test_sample, output_data, ret);                                     // (10) 0.03711
/*56  */     printf("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));          // 0.0
/*60  */     /* test av_audio_fifo_peek */                                                          // 0.0
/*62  */     ret = av_audio_fifo_peek(afifo, output_data, afifo->nb_samples);                       // 0.0
/*64  */     if (ret < 0){                                                                          // 0.0
/*66  */         ERROR("ERROR: av_audio_fifo_peek failed!");                                        // 0.0
/*68  */     }                                                                                      // 0.0
/*70  */     printf("peek:\n");                                                                     // 0.0
/*72  */     print_audio_bytes(&test_sample, output_data, ret);                                     // 0.0
/*74  */     printf("\n");                                                                          // 0.0
/*78  */     /* test av_audio_fifo_peek_at */                                                       // 0.0
/*80  */     printf("peek_at:\n");                                                                  // 0.0
/*82  */     for (i = 0; i < afifo->nb_samples; ++i){                                               // 0.0
/*84  */         ret = av_audio_fifo_peek_at(afifo, output_data, 1, i);                             // 0.0
/*86  */         if (ret < 0){                                                                      // 0.0
/*88  */             ERROR("ERROR: av_audio_fifo_peek_at failed!");                                 // 0.0
/*90  */         }                                                                                  // 0.0
/*92  */         printf("%d:\n", i);                                                                // 0.0
/*94  */         print_audio_bytes(&test_sample, output_data, ret);                                 // 0.0
/*96  */     }                                                                                      // 0.0
/*98  */     printf("\n");                                                                          // 0.0
/*102 */     /* test av_audio_fifo_drain */                                                         // 0.0
/*104 */     ret = av_audio_fifo_drain(afifo, afifo->nb_samples);                                   // 0.0
/*106 */     if (ret < 0){                                                                          // 0.0
/*108 */         ERROR("ERROR: av_audio_fifo_drain failed!");                                       // 0.0
/*110 */     }                                                                                      // 0.0
/*112 */     if (afifo->nb_samples){                                                                // 0.0
/*114 */         ERROR("drain failed to flush all samples in audio_fifo!");                         // 0.0
/*116 */     }                                                                                      // 0.0
/*120 */     /* deallocate */                                                                       // 0.0
/*122 */     for (i = 0; i < afifo->nb_buffers; ++i){                                               // 0.0
/*124 */         av_freep(&output_data[i]);                                                         // 0.0
/*126 */     }                                                                                      // 0.0
/*128 */     av_freep(&output_data);                                                                // 0.0
/*130 */     av_audio_fifo_free(afifo);                                                             // 0.0
/*132 */ }                                                                                          // 0.0
