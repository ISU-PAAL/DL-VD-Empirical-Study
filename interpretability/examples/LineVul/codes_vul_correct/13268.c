// commit message FFmpeg@fd0f45e58b (target=1, prob=0.5001944, correct=True):    * fix for integer overflow
/*0    */ static int av_encode(AVFormatContext **output_files,                                                                                                                      // (14) 0.0293
/*2    */                      int nb_output_files,                                                                                                                                 // (5) 0.05469
/*4    */                      AVFormatContext **input_files,                                                                                                                       // (3) 0.05469
/*6    */                      int nb_input_files,                                                                                                                                  // (4) 0.05469
/*8    */                      AVStreamMap *stream_maps, int nb_stream_maps)                                                                                                        // (0) 0.07031
/*10   */ {                                                                                                                                                                         // (28) 0.001953
/*12   */     int ret, i, j, k, n, nb_istreams = 0, nb_ostreams = 0;                                                                                                                // (1) 0.0625
/*14   */     AVFormatContext *is, *os;                                                                                                                                             // (17) 0.02344
/*16   */     AVCodecContext *codec, *icodec;                                                                                                                                       // (10) 0.03125
/*18   */     AVOutputStream *ost, **ost_table = NULL;                                                                                                                              // (11) 0.03125
/*20   */     AVInputStream *ist, **ist_table = NULL;                                                                                                                               // (12) 0.03125
/*22   */     AVInputFile *file_table;                                                                                                                                              // (19) 0.02148
/*24   */     AVFormatContext *stream_no_data;                                                                                                                                      // (16) 0.02539
/*26   */     int key;                                                                                                                                                              // (25) 0.01172
/*30   */     file_table= (AVInputFile*) av_mallocz(nb_input_files * sizeof(AVInputFile));                                                                                          // (2) 0.05859
/*32   */     if (!file_table)                                                                                                                                                      // (21) 0.01758
/*34   */         goto fail;                                                                                                                                                        // (20) 0.01953
/*38   */     /* input stream init */                                                                                                                                               // (23) 0.01562
/*40   */     j = 0;                                                                                                                                                                // (24) 0.01367
/*42   */     for(i=0;i<nb_input_files;i++) {                                                                                                                                       // (8) 0.03906
/*44   */         is = input_files[i];                                                                                                                                              // (15) 0.0293
/*46   */         file_table[i].ist_index = j;                                                                                                                                      // (9) 0.03711
/*48   */         file_table[i].nb_streams = is->nb_streams;                                                                                                                        // (7) 0.04883
/*50   */         j += is->nb_streams;                                                                                                                                              // (13) 0.03125
/*52   */     }                                                                                                                                                                     // (26) 0.007812
/*54   */     nb_istreams = j;                                                                                                                                                      // (18) 0.02344
/*58   */     ist_table = av_mallocz(nb_istreams * sizeof(AVInputStream *));                                                                                                        // (6) 0.05273
/*60   */     if (!ist_table)                                                                                                                                                       // (22) 0.01758
/*62   */         goto fail;                                                                                                                                                        // 0.0
/*64   */                                                                                                                                                                           // (27) 0.007812
/*66   */     for(i=0;i<nb_istreams;i++) {                                                                                                                                          // 0.0
/*68   */         ist = av_mallocz(sizeof(AVInputStream));                                                                                                                          // 0.0
/*70   */         if (!ist)                                                                                                                                                         // 0.0
/*72   */             goto fail;                                                                                                                                                    // 0.0
/*74   */         ist_table[i] = ist;                                                                                                                                               // 0.0
/*76   */     }                                                                                                                                                                     // 0.0
/*78   */     j = 0;                                                                                                                                                                // 0.0
/*80   */     for(i=0;i<nb_input_files;i++) {                                                                                                                                       // 0.0
/*82   */         is = input_files[i];                                                                                                                                              // 0.0
/*84   */         for(k=0;k<is->nb_streams;k++) {                                                                                                                                   // 0.0
/*86   */             ist = ist_table[j++];                                                                                                                                         // 0.0
/*88   */             ist->st = is->streams[k];                                                                                                                                     // 0.0
/*90   */             ist->file_index = i;                                                                                                                                          // 0.0
/*92   */             ist->index = k;                                                                                                                                               // 0.0
/*94   */             ist->discard = 1; /* the stream is discarded by default                                                                                                       // 0.0
/*96   */                                  (changed later) */                                                                                                                       // 0.0
/*100  */             if (ist->st->codec.rate_emu) {                                                                                                                                // 0.0
/*102  */                 ist->start = av_gettime();                                                                                                                                // 0.0
/*104  */                 ist->frame = 0;                                                                                                                                           // 0.0
/*106  */             }                                                                                                                                                             // 0.0
/*108  */         }                                                                                                                                                                 // 0.0
/*110  */     }                                                                                                                                                                     // 0.0
/*114  */     /* output stream init */                                                                                                                                              // 0.0
/*116  */     nb_ostreams = 0;                                                                                                                                                      // 0.0
/*118  */     for(i=0;i<nb_output_files;i++) {                                                                                                                                      // 0.0
/*120  */         os = output_files[i];                                                                                                                                             // 0.0
/*122  */         nb_ostreams += os->nb_streams;                                                                                                                                    // 0.0
/*124  */     }                                                                                                                                                                     // 0.0
/*126  */     if (nb_stream_maps > 0 && nb_stream_maps != nb_ostreams) {                                                                                                            // 0.0
/*128  */         fprintf(stderr, "Number of stream maps must match number of output streams\n");                                                                                   // 0.0
/*130  */         exit(1);                                                                                                                                                          // 0.0
/*132  */     }                                                                                                                                                                     // 0.0
/*136  */     /* Sanity check the mapping args -- do the input files & streams exist? */                                                                                            // 0.0
/*138  */     for(i=0;i<nb_stream_maps;i++) {                                                                                                                                       // 0.0
/*140  */         int fi = stream_maps[i].file_index;                                                                                                                               // 0.0
/*142  */         int si = stream_maps[i].stream_index;                                                                                                                             // 0.0
/*144  */                                                                                                                                                                           // 0.0
/*146  */         if (fi < 0 || fi > nb_input_files - 1 ||                                                                                                                          // 0.0
/*148  */             si < 0 || si > file_table[fi].nb_streams - 1) {                                                                                                               // 0.0
/*150  */             fprintf(stderr,"Could not find input stream #%d.%d\n", fi, si);                                                                                               // 0.0
/*152  */             exit(1);                                                                                                                                                      // 0.0
/*154  */         }                                                                                                                                                                 // 0.0
/*156  */     }                                                                                                                                                                     // 0.0
/*158  */                                                                                                                                                                           // 0.0
/*160  */     ost_table = av_mallocz(sizeof(AVOutputStream *) * nb_ostreams);                                                                                                       // 0.0
/*162  */     if (!ost_table)                                                                                                                                                       // 0.0
/*164  */         goto fail;                                                                                                                                                        // 0.0
/*166  */     for(i=0;i<nb_ostreams;i++) {                                                                                                                                          // 0.0
/*168  */         ost = av_mallocz(sizeof(AVOutputStream));                                                                                                                         // 0.0
/*170  */         if (!ost)                                                                                                                                                         // 0.0
/*172  */             goto fail;                                                                                                                                                    // 0.0
/*174  */         ost_table[i] = ost;                                                                                                                                               // 0.0
/*176  */     }                                                                                                                                                                     // 0.0
/*178  */                                                                                                                                                                           // 0.0
/*180  */     n = 0;                                                                                                                                                                // 0.0
/*182  */     for(k=0;k<nb_output_files;k++) {                                                                                                                                      // 0.0
/*184  */         os = output_files[k];                                                                                                                                             // 0.0
/*186  */         for(i=0;i<os->nb_streams;i++) {                                                                                                                                   // 0.0
/*188  */             int found;                                                                                                                                                    // 0.0
/*190  */             ost = ost_table[n++];                                                                                                                                         // 0.0
/*192  */             ost->file_index = k;                                                                                                                                          // 0.0
/*194  */             ost->index = i;                                                                                                                                               // 0.0
/*196  */             ost->st = os->streams[i];                                                                                                                                     // 0.0
/*198  */             if (nb_stream_maps > 0) {                                                                                                                                     // 0.0
/*200  */                 ost->source_index = file_table[stream_maps[n-1].file_index].ist_index +                                                                                   // 0.0
/*202  */                     stream_maps[n-1].stream_index;                                                                                                                        // 0.0
/*204  */                                                                                                                                                                           // 0.0
/*206  */                 /* Sanity check that the stream types match */                                                                                                            // 0.0
/*208  */                 if (ist_table[ost->source_index]->st->codec.codec_type != ost->st->codec.codec_type) {                                                                    // 0.0
/*210  */                     fprintf(stderr, "Codec type mismatch for mapping #%d.%d -> #%d.%d\n",                                                                                 // 0.0
/*212  */                         stream_maps[n-1].file_index, stream_maps[n-1].stream_index,                                                                                       // 0.0
/*214  */                         ost->file_index, ost->index);                                                                                                                     // 0.0
/*216  */                     exit(1);                                                                                                                                              // 0.0
/*218  */                 }                                                                                                                                                         // 0.0
/*220  */                                                                                                                                                                           // 0.0
/*222  */             } else {                                                                                                                                                      // 0.0
/*224  */                 /* get corresponding input stream index : we select the first one with the right type */                                                                  // 0.0
/*226  */                 found = 0;                                                                                                                                                // 0.0
/*228  */                 for(j=0;j<nb_istreams;j++) {                                                                                                                              // 0.0
/*230  */                     ist = ist_table[j];                                                                                                                                   // 0.0
/*232  */                     if (ist->discard &&                                                                                                                                   // 0.0
/*234  */                         ist->st->codec.codec_type == ost->st->codec.codec_type) {                                                                                         // 0.0
/*236  */                         ost->source_index = j;                                                                                                                            // 0.0
/*238  */                         found = 1;                                                                                                                                        // 0.0
/*240  */                     }                                                                                                                                                     // 0.0
/*242  */                 }                                                                                                                                                         // 0.0
/*244  */                                                                                                                                                                           // 0.0
/*246  */                 if (!found) {                                                                                                                                             // 0.0
/*248  */                     /* try again and reuse existing stream */                                                                                                             // 0.0
/*250  */                     for(j=0;j<nb_istreams;j++) {                                                                                                                          // 0.0
/*252  */                         ist = ist_table[j];                                                                                                                               // 0.0
/*254  */                         if (ist->st->codec.codec_type == ost->st->codec.codec_type) {                                                                                     // 0.0
/*256  */                             ost->source_index = j;                                                                                                                        // 0.0
/*258  */                             found = 1;                                                                                                                                    // 0.0
/*260  */                         }                                                                                                                                                 // 0.0
/*262  */                     }                                                                                                                                                     // 0.0
/*264  */                     if (!found) {                                                                                                                                         // 0.0
/*266  */                         fprintf(stderr, "Could not find input stream matching output stream #%d.%d\n",                                                                    // 0.0
/*268  */                                 ost->file_index, ost->index);                                                                                                             // 0.0
/*270  */                         exit(1);                                                                                                                                          // 0.0
/*272  */                     }                                                                                                                                                     // 0.0
/*274  */                 }                                                                                                                                                         // 0.0
/*276  */             }                                                                                                                                                             // 0.0
/*278  */             ist = ist_table[ost->source_index];                                                                                                                           // 0.0
/*280  */             ist->discard = 0;                                                                                                                                             // 0.0
/*282  */         }                                                                                                                                                                 // 0.0
/*284  */     }                                                                                                                                                                     // 0.0
/*288  */     /* for each output stream, we compute the right encoding parameters */                                                                                                // 0.0
/*290  */     for(i=0;i<nb_ostreams;i++) {                                                                                                                                          // 0.0
/*292  */         ost = ost_table[i];                                                                                                                                               // 0.0
/*294  */         ist = ist_table[ost->source_index];                                                                                                                               // 0.0
/*298  */         codec = &ost->st->codec;                                                                                                                                          // 0.0
/*300  */         icodec = &ist->st->codec;                                                                                                                                         // 0.0
/*304  */         if (ost->st->stream_copy) {                                                                                                                                       // 0.0
/*306  */             /* if stream_copy is selected, no need to decode or encode */                                                                                                 // 0.0
/*308  */             codec->codec_id = icodec->codec_id;                                                                                                                           // 0.0
/*310  */             codec->codec_type = icodec->codec_type;                                                                                                                       // 0.0
/*312  */             codec->codec_tag = icodec->codec_tag;                                                                                                                         // 0.0
/*314  */             codec->bit_rate = icodec->bit_rate;                                                                                                                           // 0.0
/*316  */             switch(codec->codec_type) {                                                                                                                                   // 0.0
/*318  */             case CODEC_TYPE_AUDIO:                                                                                                                                        // 0.0
/*320  */                 codec->sample_rate = icodec->sample_rate;                                                                                                                 // 0.0
/*322  */                 codec->channels = icodec->channels;                                                                                                                       // 0.0
/*324  */                 break;                                                                                                                                                    // 0.0
/*326  */             case CODEC_TYPE_VIDEO:                                                                                                                                        // 0.0
/*328  */                 codec->frame_rate = icodec->frame_rate;                                                                                                                   // 0.0
/*330  */                 codec->frame_rate_base = icodec->frame_rate_base;                                                                                                         // 0.0
/*332  */                 codec->width = icodec->width;                                                                                                                             // 0.0
/*334  */                 codec->height = icodec->height;                                                                                                                           // 0.0
/*336  */                 break;                                                                                                                                                    // 0.0
/*338  */             default:                                                                                                                                                      // 0.0
/*340  */                 av_abort();                                                                                                                                               // 0.0
/*342  */             }                                                                                                                                                             // 0.0
/*344  */         } else {                                                                                                                                                          // 0.0
/*346  */             switch(codec->codec_type) {                                                                                                                                   // 0.0
/*348  */             case CODEC_TYPE_AUDIO:                                                                                                                                        // 0.0
/*350  */                 if (fifo_init(&ost->fifo, 2 * MAX_AUDIO_PACKET_SIZE))                                                                                                     // 0.0
/*352  */                     goto fail;                                                                                                                                            // 0.0
/*354  */                                                                                                                                                                           // 0.0
/*356  */                 if (codec->channels == icodec->channels &&                                                                                                                // 0.0
/*358  */                     codec->sample_rate == icodec->sample_rate) {                                                                                                          // 0.0
/*360  */                     ost->audio_resample = 0;                                                                                                                              // 0.0
/*362  */                 } else {                                                                                                                                                  // 0.0
/*364  */                     if (codec->channels != icodec->channels &&                                                                                                            // 0.0
/*366  */                         icodec->codec_id == CODEC_ID_AC3) {                                                                                                               // 0.0
/*368  */                         /* Special case for 5:1 AC3 input */                                                                                                              // 0.0
/*370  */                         /* and mono or stereo output      */                                                                                                              // 0.0
/*372  */                         /* Request specific number of channels */                                                                                                         // 0.0
/*374  */                         icodec->channels = codec->channels;                                                                                                               // 0.0
/*376  */                         if (codec->sample_rate == icodec->sample_rate)                                                                                                    // 0.0
/*378  */                             ost->audio_resample = 0;                                                                                                                      // 0.0
/*380  */                         else {                                                                                                                                            // 0.0
/*382  */                             ost->audio_resample = 1;                                                                                                                      // 0.0
/*384  */                             ost->resample = audio_resample_init(codec->channels, icodec->channels,                                                                        // 0.0
/*386  */                                                         codec->sample_rate,                                                                                               // 0.0
/*388  */                                                         icodec->sample_rate);                                                                                             // 0.0
/*390  */ 			    if(!ost->resample)                                                                                                                                                 // 0.0
/*392  */ 			      {                                                                                                                                                                // 0.0
/*394  */ 				printf("Can't resample.  Aborting.\n");                                                                                                                               // 0.0
/*396  */ 				av_abort();                                                                                                                                                           // 0.0
/*398  */ 			      }                                                                                                                                                                // 0.0
/*400  */                         }                                                                                                                                                 // 0.0
/*402  */                         /* Request specific number of channels */                                                                                                         // 0.0
/*404  */                         icodec->channels = codec->channels;                                                                                                               // 0.0
/*406  */                     } else {                                                                                                                                              // 0.0
/*408  */                         ost->audio_resample = 1;                                                                                                                          // 0.0
/*410  */                         ost->resample = audio_resample_init(codec->channels, icodec->channels,                                                                            // 0.0
/*412  */                                                         codec->sample_rate,                                                                                               // 0.0
/*414  */                                                         icodec->sample_rate);                                                                                             // 0.0
/*416  */ 			if(!ost->resample)                                                                                                                                                     // 0.0
/*418  */ 			  {                                                                                                                                                                    // 0.0
/*420  */ 			    printf("Can't resample.  Aborting.\n");                                                                                                                            // 0.0
/*422  */ 			    av_abort();                                                                                                                                                        // 0.0
/*424  */ 			  }                                                                                                                                                                    // 0.0
/*426  */                     }                                                                                                                                                     // 0.0
/*428  */                 }                                                                                                                                                         // 0.0
/*430  */                 ist->decoding_needed = 1;                                                                                                                                 // 0.0
/*432  */                 ost->encoding_needed = 1;                                                                                                                                 // 0.0
/*434  */                 break;                                                                                                                                                    // 0.0
/*436  */             case CODEC_TYPE_VIDEO:                                                                                                                                        // 0.0
/*438  */                 if (codec->width == icodec->width &&                                                                                                                      // 0.0
/*440  */                     codec->height == icodec->height &&                                                                                                                    // 0.0
/*442  */                     frame_topBand == 0 &&                                                                                                                                 // 0.0
/*444  */                     frame_bottomBand == 0 &&                                                                                                                              // 0.0
/*446  */                     frame_leftBand == 0 &&                                                                                                                                // 0.0
/*448  */                     frame_rightBand == 0)                                                                                                                                 // 0.0
/*450  */                 {                                                                                                                                                         // 0.0
/*452  */                     ost->video_resample = 0;                                                                                                                              // 0.0
/*454  */                     ost->video_crop = 0;                                                                                                                                  // 0.0
/*456  */                 } else if ((codec->width == icodec->width -                                                                                                               // 0.0
/*458  */                                 (frame_leftBand + frame_rightBand)) &&                                                                                                    // 0.0
/*460  */                         (codec->height == icodec->height -                                                                                                                // 0.0
/*462  */                                 (frame_topBand  + frame_bottomBand)))                                                                                                     // 0.0
/*464  */                 {                                                                                                                                                         // 0.0
/*466  */                     ost->video_resample = 0;                                                                                                                              // 0.0
/*468  */                     ost->video_crop = 1;                                                                                                                                  // 0.0
/*470  */                     ost->topBand = frame_topBand;                                                                                                                         // 0.0
/*472  */                     ost->leftBand = frame_leftBand;                                                                                                                       // 0.0
/*474  */                 } else {                                                                                                                                                  // 0.0
/*476  */                     uint8_t *buf;                                                                                                                                         // 0.0
/*478  */                     ost->video_resample = 1;                                                                                                                              // 0.0
/*480  */                     ost->video_crop = 0; // cropping is handled as part of resample                                                                                       // 0.0
/*482  */                     buf = av_malloc((codec->width * codec->height * 3) / 2);                                                                                              // 0.0
/*484  */                     if (!buf)                                                                                                                                             // 0.0
/*486  */                         goto fail;                                                                                                                                        // 0.0
/*488  */                     ost->pict_tmp.data[0] = buf;                                                                                                                          // 0.0
/*490  */                     ost->pict_tmp.data[1] = ost->pict_tmp.data[0] + (codec->width * codec->height);                                                                       // 0.0
/*492  */                     ost->pict_tmp.data[2] = ost->pict_tmp.data[1] + (codec->width * codec->height) / 4;                                                                   // 0.0
/*494  */                     ost->pict_tmp.linesize[0] = codec->width;                                                                                                             // 0.0
/*496  */                     ost->pict_tmp.linesize[1] = codec->width / 2;                                                                                                         // 0.0
/*498  */                     ost->pict_tmp.linesize[2] = codec->width / 2;                                                                                                         // 0.0
/*502  */                     ost->img_resample_ctx = img_resample_full_init(                                                                                                       // 0.0
/*504  */                                       ost->st->codec.width, ost->st->codec.height,                                                                                        // 0.0
/*506  */                                       ist->st->codec.width, ist->st->codec.height,                                                                                        // 0.0
/*508  */                                       frame_topBand, frame_bottomBand,                                                                                                    // 0.0
/*510  */                                       frame_leftBand, frame_rightBand);                                                                                                   // 0.0
/*512  */                 }                                                                                                                                                         // 0.0
/*514  */                 ost->encoding_needed = 1;                                                                                                                                 // 0.0
/*516  */                 ist->decoding_needed = 1;                                                                                                                                 // 0.0
/*518  */                 break;                                                                                                                                                    // 0.0
/*520  */             default:                                                                                                                                                      // 0.0
/*522  */                 av_abort();                                                                                                                                               // 0.0
/*524  */             }                                                                                                                                                             // 0.0
/*526  */             /* two pass mode */                                                                                                                                           // 0.0
/*528  */             if (ost->encoding_needed &&                                                                                                                                   // 0.0
/*530  */                 (codec->flags & (CODEC_FLAG_PASS1 | CODEC_FLAG_PASS2))) {                                                                                                 // 0.0
/*532  */                 char logfilename[1024];                                                                                                                                   // 0.0
/*534  */                 FILE *f;                                                                                                                                                  // 0.0
/*536  */                 int size;                                                                                                                                                 // 0.0
/*538  */                 char *logbuffer;                                                                                                                                          // 0.0
/*540  */                                                                                                                                                                           // 0.0
/*542  */                 snprintf(logfilename, sizeof(logfilename), "%s-%d.log",                                                                                                   // 0.0
/*544  */                          pass_logfilename ?                                                                                                                               // 0.0
/*546  */                          pass_logfilename : DEFAULT_PASS_LOGFILENAME, i);                                                                                                 // 0.0
/*548  */                 if (codec->flags & CODEC_FLAG_PASS1) {                                                                                                                    // 0.0
/*550  */                     f = fopen(logfilename, "w");                                                                                                                          // 0.0
/*552  */                     if (!f) {                                                                                                                                             // 0.0
/*554  */                         perror(logfilename);                                                                                                                              // 0.0
/*556  */                         exit(1);                                                                                                                                          // 0.0
/*558  */                     }                                                                                                                                                     // 0.0
/*560  */                     ost->logfile = f;                                                                                                                                     // 0.0
/*562  */                 } else {                                                                                                                                                  // 0.0
/*564  */                     /* read the log file */                                                                                                                               // 0.0
/*566  */                     f = fopen(logfilename, "r");                                                                                                                          // 0.0
/*568  */                     if (!f) {                                                                                                                                             // 0.0
/*570  */                         perror(logfilename);                                                                                                                              // 0.0
/*572  */                         exit(1);                                                                                                                                          // 0.0
/*574  */                     }                                                                                                                                                     // 0.0
/*576  */                     fseek(f, 0, SEEK_END);                                                                                                                                // 0.0
/*578  */                     size = ftell(f);                                                                                                                                      // 0.0
/*580  */                     fseek(f, 0, SEEK_SET);                                                                                                                                // 0.0
/*582  */                     logbuffer = av_malloc(size + 1);                                                                                                                      // 0.0
/*584  */                     if (!logbuffer) {                                                                                                                                     // 0.0
/*586  */                         fprintf(stderr, "Could not allocate log buffer\n");                                                                                               // 0.0
/*588  */                         exit(1);                                                                                                                                          // 0.0
/*590  */                     }                                                                                                                                                     // 0.0
/*592  */                     fread(logbuffer, 1, size, f);                                                                                                                         // 0.0
/*594  */                     fclose(f);                                                                                                                                            // 0.0
/*596  */                     logbuffer[size] = '\0';                                                                                                                               // 0.0
/*598  */                     codec->stats_in = logbuffer;                                                                                                                          // 0.0
/*600  */                 }                                                                                                                                                         // 0.0
/*602  */             }                                                                                                                                                             // 0.0
/*604  */         }                                                                                                                                                                 // 0.0
/*606  */     }                                                                                                                                                                     // 0.0
/*610  */     /* dump the file output parameters - cannot be done before in case                                                                                                    // 0.0
/*612  */        of stream copy */                                                                                                                                                  // 0.0
/*614  */     for(i=0;i<nb_output_files;i++) {                                                                                                                                      // 0.0
/*616  */         dump_format(output_files[i], i, output_files[i]->filename, 1);                                                                                                    // 0.0
/*618  */     }                                                                                                                                                                     // 0.0
/*622  */     /* dump the stream mapping */                                                                                                                                         // 0.0
/*624  */     fprintf(stderr, "Stream mapping:\n");                                                                                                                                 // 0.0
/*626  */     for(i=0;i<nb_ostreams;i++) {                                                                                                                                          // 0.0
/*628  */         ost = ost_table[i];                                                                                                                                               // 0.0
/*630  */         fprintf(stderr, "  Stream #%d.%d -> #%d.%d\n",                                                                                                                    // 0.0
/*632  */                 ist_table[ost->source_index]->file_index,                                                                                                                 // 0.0
/*634  */                 ist_table[ost->source_index]->index,                                                                                                                      // 0.0
/*636  */                 ost->file_index,                                                                                                                                          // 0.0
/*638  */                 ost->index);                                                                                                                                              // 0.0
/*640  */     }                                                                                                                                                                     // 0.0
/*644  */     /* open each encoder */                                                                                                                                               // 0.0
/*646  */     for(i=0;i<nb_ostreams;i++) {                                                                                                                                          // 0.0
/*648  */         ost = ost_table[i];                                                                                                                                               // 0.0
/*650  */         if (ost->encoding_needed) {                                                                                                                                       // 0.0
/*652  */             AVCodec *codec;                                                                                                                                               // 0.0
/*654  */             codec = avcodec_find_encoder(ost->st->codec.codec_id);                                                                                                        // 0.0
/*656  */             if (!codec) {                                                                                                                                                 // 0.0
/*658  */                 fprintf(stderr, "Unsupported codec for output stream #%d.%d\n",                                                                                           // 0.0
/*660  */                         ost->file_index, ost->index);                                                                                                                     // 0.0
/*662  */                 exit(1);                                                                                                                                                  // 0.0
/*664  */             }                                                                                                                                                             // 0.0
/*666  */             if (avcodec_open(&ost->st->codec, codec) < 0) {                                                                                                               // 0.0
/*668  */                 fprintf(stderr, "Error while opening codec for stream #%d.%d - maybe incorrect parameters such as bit_rate, rate, width or height\n",                     // 0.0
/*670  */                         ost->file_index, ost->index);                                                                                                                     // 0.0
/*672  */                 exit(1);                                                                                                                                                  // 0.0
/*674  */             }                                                                                                                                                             // 0.0
/*676  */         }                                                                                                                                                                 // 0.0
/*678  */     }                                                                                                                                                                     // 0.0
/*682  */     /* open each decoder */                                                                                                                                               // 0.0
/*684  */     for(i=0;i<nb_istreams;i++) {                                                                                                                                          // 0.0
/*686  */         ist = ist_table[i];                                                                                                                                               // 0.0
/*688  */         if (ist->decoding_needed) {                                                                                                                                       // 0.0
/*690  */             AVCodec *codec;                                                                                                                                               // 0.0
/*692  */             codec = avcodec_find_decoder(ist->st->codec.codec_id);                                                                                                        // 0.0
/*694  */             if (!codec) {                                                                                                                                                 // 0.0
/*696  */                 fprintf(stderr, "Unsupported codec (id=%d) for input stream #%d.%d\n",                                                                                    // 0.0
/*698  */                         ist->st->codec.codec_id, ist->file_index, ist->index);                                                                                            // 0.0
/*700  */                 exit(1);                                                                                                                                                  // 0.0
/*702  */             }                                                                                                                                                             // 0.0
/*704  */             if (avcodec_open(&ist->st->codec, codec) < 0) {                                                                                                               // 0.0
/*706  */                 fprintf(stderr, "Error while opening codec for input stream #%d.%d\n",                                                                                    // 0.0
/*708  */                         ist->file_index, ist->index);                                                                                                                     // 0.0
/*710  */                 exit(1);                                                                                                                                                  // 0.0
/*712  */             }                                                                                                                                                             // 0.0
/*714  */             //if (ist->st->codec.codec_type == CODEC_TYPE_VIDEO)                                                                                                          // 0.0
/*716  */             //    ist->st->codec.flags |= CODEC_FLAG_REPEAT_FIELD;                                                                                                        // 0.0
/*718  */             ist->frame_decoded = 1;                                                                                                                                       // 0.0
/*720  */         }                                                                                                                                                                 // 0.0
/*722  */     }                                                                                                                                                                     // 0.0
/*726  */     /* init pts */                                                                                                                                                        // 0.0
/*728  */     for(i=0;i<nb_istreams;i++) {                                                                                                                                          // 0.0
/*730  */         ist = ist_table[i];                                                                                                                                               // 0.0
/*732  */ 	is = input_files[ist->file_index];                                                                                                                                       // 0.0
/*734  */         ist->pts = 0;                                                                                                                                                     // 0.0
/*736  */         if (ist->decoding_needed) {                                                                                                                                       // 0.0
/*738  */             switch (ist->st->codec.codec_type) {                                                                                                                          // 0.0
/*740  */             case CODEC_TYPE_AUDIO:                                                                                                                                        // 0.0
/*742  */                 av_frac_init(&ist->next_pts,                                                                                                                              // 0.0
/*744  */                              0, 0, is->pts_num * ist->st->codec.sample_rate);                                                                                             // 0.0
/*746  */                 break;                                                                                                                                                    // 0.0
/*748  */             case CODEC_TYPE_VIDEO:                                                                                                                                        // 0.0
/*750  */                 av_frac_init(&ist->next_pts,                                                                                                                              // 0.0
/*752  */                              0, 0, is->pts_num * ist->st->codec.frame_rate);                                                                                              // 0.0
/*754  */                 break;                                                                                                                                                    // 0.0
/*756  */             default:                                                                                                                                                      // 0.0
/*758  */                 break;                                                                                                                                                    // 0.0
/*760  */             }                                                                                                                                                             // 0.0
/*762  */         }                                                                                                                                                                 // 0.0
/*764  */     }                                                                                                                                                                     // 0.0
/*766  */                                                                                                                                                                           // 0.0
/*768  */     /* compute buffer size max (should use a complete heuristic) */                                                                                                       // 0.0
/*770  */     for(i=0;i<nb_input_files;i++) {                                                                                                                                       // 0.0
/*772  */         file_table[i].buffer_size_max = 2048;                                                                                                                             // 0.0
/*774  */     }                                                                                                                                                                     // 0.0
/*778  */     /* open files and write file headers */                                                                                                                               // 0.0
/*780  */     for(i=0;i<nb_output_files;i++) {                                                                                                                                      // 0.0
/*782  */         os = output_files[i];                                                                                                                                             // 0.0
/*784  */         if (av_write_header(os) < 0) {                                                                                                                                    // 0.0
/*786  */             fprintf(stderr, "Could not write header for output file #%d (incorrect codec paramters ?)\n", i);                                                             // 0.0
/*788  */             ret = -EINVAL;                                                                                                                                                // 0.0
/*790  */             goto fail;                                                                                                                                                    // 0.0
/*792  */         }                                                                                                                                                                 // 0.0
/*794  */     }                                                                                                                                                                     // 0.0
/*798  */ #ifndef CONFIG_WIN32                                                                                                                                                      // 0.0
/*800  */     if ( !using_stdin )                                                                                                                                                   // 0.0
/*802  */         fprintf(stderr, "Press [q] to stop encoding\n");                                                                                                                  // 0.0
/*804  */ #endif                                                                                                                                                                    // 0.0
/*806  */     term_init();                                                                                                                                                          // 0.0
/*810  */     stream_no_data = 0;                                                                                                                                                   // 0.0
/*812  */     key = -1;                                                                                                                                                             // 0.0
/*816  */     for(; received_sigterm == 0;) {                                                                                                                                       // 0.0
/*818  */         int file_index, ist_index;                                                                                                                                        // 0.0
/*820  */         AVPacket pkt;                                                                                                                                                     // 0.0
/*822  */         uint8_t *ptr;                                                                                                                                                     // 0.0
/*824  */         int len;                                                                                                                                                          // 0.0
/*826  */         uint8_t *data_buf;                                                                                                                                                // 0.0
/*828  */         int data_size, got_picture;                                                                                                                                       // 0.0
/*830  */         AVPicture picture;                                                                                                                                                // 0.0
/*832  */         short samples[AVCODEC_MAX_AUDIO_FRAME_SIZE / 2];                                                                                                                  // 0.0
/*834  */         void *buffer_to_free;                                                                                                                                             // 0.0
/*836  */         double pts_min;                                                                                                                                                   // 0.0
/*838  */                                                                                                                                                                           // 0.0
/*840  */     redo:                                                                                                                                                                 // 0.0
/*842  */         /* if 'q' pressed, exits */                                                                                                                                       // 0.0
/*844  */         if (!using_stdin) {                                                                                                                                               // 0.0
/*846  */             /* read_key() returns 0 on EOF */                                                                                                                             // 0.0
/*848  */             key = read_key();                                                                                                                                             // 0.0
/*850  */             if (key == 'q')                                                                                                                                               // 0.0
/*852  */                 break;                                                                                                                                                    // 0.0
/*854  */         }                                                                                                                                                                 // 0.0
/*858  */         /* select the stream that we must read now by looking at the                                                                                                      // 0.0
/*860  */            smallest output pts */                                                                                                                                         // 0.0
/*862  */         file_index = -1;                                                                                                                                                  // 0.0
/*864  */         pts_min = 1e10;                                                                                                                                                   // 0.0
/*866  */         for(i=0;i<nb_ostreams;i++) {                                                                                                                                      // 0.0
/*868  */             double pts;                                                                                                                                                   // 0.0
/*870  */             ost = ost_table[i];                                                                                                                                           // 0.0
/*872  */             os = output_files[ost->file_index];                                                                                                                           // 0.0
/*874  */             ist = ist_table[ost->source_index];                                                                                                                           // 0.0
/*876  */             pts = (double)ost->st->pts.val * os->pts_num / os->pts_den;                                                                                                   // 0.0
/*878  */             if (!file_table[ist->file_index].eof_reached &&                                                                                                               // 0.0
/*880  */                 pts < pts_min) {                                                                                                                                          // 0.0
/*882  */                 pts_min = pts;                                                                                                                                            // 0.0
/*884  */                 file_index = ist->file_index;                                                                                                                             // 0.0
/*886  */             }                                                                                                                                                             // 0.0
/*888  */         }                                                                                                                                                                 // 0.0
/*890  */         /* if none, if is finished */                                                                                                                                     // 0.0
/*892  */         if (file_index < 0) {                                                                                                                                             // 0.0
/*894  */             break;                                                                                                                                                        // 0.0
/*896  */         }                                                                                                                                                                 // 0.0
/*900  */         /* finish if recording time exhausted */                                                                                                                          // 0.0
/*902  */         if (recording_time > 0 && pts_min >= (recording_time / 1000000.0))                                                                                                // 0.0
/*904  */             break;                                                                                                                                                        // 0.0
/*908  */         /* read a packet from it and output it in the fifo */                                                                                                             // 0.0
/*910  */         is = input_files[file_index];                                                                                                                                     // 0.0
/*912  */         if (av_read_packet(is, &pkt) < 0) {                                                                                                                               // 0.0
/*914  */             file_table[file_index].eof_reached = 1;                                                                                                                       // 0.0
/*916  */             continue;                                                                                                                                                     // 0.0
/*918  */         }                                                                                                                                                                 // 0.0
/*920  */         if (!pkt.size) {                                                                                                                                                  // 0.0
/*922  */             stream_no_data = is;                                                                                                                                          // 0.0
/*924  */         } else {                                                                                                                                                          // 0.0
/*926  */             stream_no_data = 0;                                                                                                                                           // 0.0
/*928  */         }                                                                                                                                                                 // 0.0
/*930  */         if (do_hex_dump) {                                                                                                                                                // 0.0
/*932  */             printf("stream #%d, size=%d:\n", pkt.stream_index, pkt.size);                                                                                                 // 0.0
/*934  */             av_hex_dump(pkt.data, pkt.size);                                                                                                                              // 0.0
/*936  */         }                                                                                                                                                                 // 0.0
/*938  */         /* the following test is needed in case new streams appear                                                                                                        // 0.0
/*940  */            dynamically in stream : we ignore them */                                                                                                                      // 0.0
/*942  */         if (pkt.stream_index >= file_table[file_index].nb_streams)                                                                                                        // 0.0
/*944  */             goto discard_packet;                                                                                                                                          // 0.0
/*946  */         ist_index = file_table[file_index].ist_index + pkt.stream_index;                                                                                                  // 0.0
/*948  */         ist = ist_table[ist_index];                                                                                                                                       // 0.0
/*950  */         if (ist->discard)                                                                                                                                                 // 0.0
/*952  */             goto discard_packet;                                                                                                                                          // 0.0
/*956  */         // printf("read #%d.%d size=%d\n", ist->file_index, ist->index, pkt.size);                                                                                        // 0.0
/*960  */         len = pkt.size;                                                                                                                                                   // 0.0
/*962  */         ptr = pkt.data;                                                                                                                                                   // 0.0
/*964  */         while (len > 0) {                                                                                                                                                 // 0.0
/*966  */             /* decode the packet if needed */                                                                                                                             // 0.0
/*968  */             data_buf = NULL; /* fail safe */                                                                                                                              // 0.0
/*970  */             data_size = 0;                                                                                                                                                // 0.0
/*972  */             if (ist->decoding_needed) {                                                                                                                                   // 0.0
/*974  */                 /* NOTE1: we only take into account the PTS if a new                                                                                                      // 0.0
/*976  */                    frame has begun (MPEG semantics) */                                                                                                                    // 0.0
/*978  */                 /* NOTE2: even if the fraction is not initialized,                                                                                                        // 0.0
/*980  */                    av_frac_set can be used to set the integer part */                                                                                                     // 0.0
/*982  */                 if (ist->frame_decoded) {                                                                                                                                 // 0.0
/*984  */                     /* If pts is unavailable -- we have to use synthetic one */                                                                                           // 0.0
/*986  */                     if( pkt.pts != AV_NOPTS_VALUE )                                                                                                                       // 0.0
/*988  */                     {                                                                                                                                                     // 0.0
/*990  */                         ist->pts = ist->next_pts.val = pkt.pts;                                                                                                           // 0.0
/*992  */                     }                                                                                                                                                     // 0.0
/*994  */                     else                                                                                                                                                  // 0.0
/*996  */                     {                                                                                                                                                     // 0.0
/*998  */                         ist->pts = ist->next_pts.val;                                                                                                                     // 0.0
/*1000 */                     }                                                                                                                                                     // 0.0
/*1002 */                     ist->frame_decoded = 0;                                                                                                                               // 0.0
/*1004 */                 }                                                                                                                                                         // 0.0
/*1008 */                 switch(ist->st->codec.codec_type) {                                                                                                                       // 0.0
/*1010 */                 case CODEC_TYPE_AUDIO:                                                                                                                                    // 0.0
/*1012 */                     /* XXX: could avoid copy if PCM 16 bits with same                                                                                                     // 0.0
/*1014 */                        endianness as CPU */                                                                                                                               // 0.0
/*1016 */                     ret = avcodec_decode_audio(&ist->st->codec, samples, &data_size,                                                                                      // 0.0
/*1018 */                                                ptr, len);                                                                                                                 // 0.0
/*1020 */                     if (ret < 0)                                                                                                                                          // 0.0
/*1022 */                         goto fail_decode;                                                                                                                                 // 0.0
/*1024 */                     /* Some bug in mpeg audio decoder gives */                                                                                                            // 0.0
/*1026 */                     /* data_size < 0, it seems they are overflows */                                                                                                      // 0.0
/*1028 */                     if (data_size <= 0) {                                                                                                                                 // 0.0
/*1030 */                         /* no audio frame */                                                                                                                              // 0.0
/*1032 */                         ptr += ret;                                                                                                                                       // 0.0
/*1034 */                         len -= ret;                                                                                                                                       // 0.0
/*1036 */                         continue;                                                                                                                                         // 0.0
/*1038 */                     }                                                                                                                                                     // 0.0
/*1040 */                     data_buf = (uint8_t *)samples;                                                                                                                        // 0.0
/*1042 */ 		    av_frac_add(&ist->next_pts,                                                                                                                                         // 0.0
/*1044 */ 			        is->pts_den * data_size / (2 * ist->st->codec.channels));                                                                                                      // 0.0
/*1046 */                     break;                                                                                                                                                // 0.0
/*1048 */                 case CODEC_TYPE_VIDEO:                                                                                                                                    // 0.0
/*1050 */                     {                                                                                                                                                     // 0.0
/*1052 */                         AVFrame big_picture;                                                                                                                              // 0.0
/*1056 */                         data_size = (ist->st->codec.width * ist->st->codec.height * 3) / 2;                                                                               // 0.0
/*1058 */                         ret = avcodec_decode_video(&ist->st->codec,                                                                                                       // 0.0
/*1060 */                                                    &big_picture, &got_picture, ptr, len);                                                                                 // 0.0
/*1062 */                         picture= *(AVPicture*)&big_picture;                                                                                                               // 0.0
/*1064 */                         ist->st->quality= big_picture.quality;                                                                                                            // 0.0
/*1066 */                         if (ret < 0) {                                                                                                                                    // 0.0
/*1068 */                         fail_decode:                                                                                                                                      // 0.0
/*1070 */                             fprintf(stderr, "Error while decoding stream #%d.%d\n",                                                                                       // 0.0
/*1072 */                                     ist->file_index, ist->index);                                                                                                         // 0.0
/*1074 */                             av_free_packet(&pkt);                                                                                                                         // 0.0
/*1076 */                             goto redo;                                                                                                                                    // 0.0
/*1078 */                         }                                                                                                                                                 // 0.0
/*1080 */                         if (!got_picture) {                                                                                                                               // 0.0
/*1082 */                             /* no picture yet */                                                                                                                          // 0.0
/*1084 */                             ptr += ret;                                                                                                                                   // 0.0
/*1086 */                             len -= ret;                                                                                                                                   // 0.0
/*1088 */                             continue;                                                                                                                                     // 0.0
/*1090 */                         }                                                                                                                                                 // 0.0
/*1092 */                         av_frac_add(&ist->next_pts,                                                                                                                       // 0.0
/*1094 */ 			            is->pts_den * ist->st->codec.frame_rate_base);                                                                                                             // 0.0
/*1096 */                     }                                                                                                                                                     // 0.0
/*1098 */                     break;                                                                                                                                                // 0.0
/*1100 */                 default:                                                                                                                                                  // 0.0
/*1102 */                     goto fail_decode;                                                                                                                                     // 0.0
/*1104 */                 }                                                                                                                                                         // 0.0
/*1106 */             } else {                                                                                                                                                      // 0.0
/*1108 */                 data_buf = ptr;                                                                                                                                           // 0.0
/*1110 */                 data_size = len;                                                                                                                                          // 0.0
/*1112 */                 ret = len;                                                                                                                                                // 0.0
/*1114 */             }                                                                                                                                                             // 0.0
/*1116 */             ptr += ret;                                                                                                                                                   // 0.0
/*1118 */             len -= ret;                                                                                                                                                   // 0.0
/*1122 */             buffer_to_free = 0;                                                                                                                                           // 0.0
/*1124 */             if (ist->st->codec.codec_type == CODEC_TYPE_VIDEO) {                                                                                                          // 0.0
/*1126 */                 pre_process_video_frame(ist, &picture, &buffer_to_free);                                                                                                  // 0.0
/*1128 */             }                                                                                                                                                             // 0.0
/*1132 */             ist->frame_decoded = 1;                                                                                                                                       // 0.0
/*1136 */             /* frame rate emulation */                                                                                                                                    // 0.0
/*1138 */             if (ist->st->codec.rate_emu) {                                                                                                                                // 0.0
/*1140 */                 int64_t pts = av_rescale((int64_t) ist->frame * ist->st->codec.frame_rate_base, 1000000, ist->st->codec.frame_rate);                                      // 0.0
/*1142 */                 int64_t now = av_gettime() - ist->start;                                                                                                                  // 0.0
/*1144 */                 if (pts > now)                                                                                                                                            // 0.0
/*1146 */                     usleep(pts - now);                                                                                                                                    // 0.0
/*1150 */                 ist->frame++;                                                                                                                                             // 0.0
/*1152 */             }                                                                                                                                                             // 0.0
/*1156 */ #if 0                                                                                                                                                                     // 0.0
/*1158 */             /* mpeg PTS deordering : if it is a P or I frame, the PTS                                                                                                     // 0.0
/*1160 */                is the one of the next displayed one */                                                                                                                    // 0.0
/*1162 */             /* XXX: add mpeg4 too ? */                                                                                                                                    // 0.0
/*1164 */             if (ist->st->codec.codec_id == CODEC_ID_MPEG1VIDEO) {                                                                                                         // 0.0
/*1166 */                 if (ist->st->codec.pict_type != B_TYPE) {                                                                                                                 // 0.0
/*1168 */                     int64_t tmp;                                                                                                                                          // 0.0
/*1170 */                     tmp = ist->last_ip_pts;                                                                                                                               // 0.0
/*1172 */                     ist->last_ip_pts  = ist->frac_pts.val;                                                                                                                // 0.0
/*1174 */                     ist->frac_pts.val = tmp;                                                                                                                              // 0.0
/*1176 */                 }                                                                                                                                                         // 0.0
/*1178 */             }                                                                                                                                                             // 0.0
/*1180 */ #endif                                                                                                                                                                    // 0.0
/*1182 */             /* transcode raw format, encode packets and output them */                                                                                                    // 0.0
/*1186 */             for(i=0;i<nb_ostreams;i++) {                                                                                                                                  // 0.0
/*1188 */                 int frame_size;                                                                                                                                           // 0.0
/*1192 */                 ost = ost_table[i];                                                                                                                                       // 0.0
/*1194 */                 if (ost->source_index == ist_index) {                                                                                                                     // 0.0
/*1196 */                     os = output_files[ost->file_index];                                                                                                                   // 0.0
/*1200 */ #if 0                                                                                                                                                                     // 0.0
/*1202 */                     printf("%d: got pts=%f %f\n", i, pkt.pts / 90000.0,                                                                                                   // 0.0
/*1204 */                            (ist->pts - ost->st->pts.val) / 90000.0);                                                                                                      // 0.0
/*1206 */ #endif                                                                                                                                                                    // 0.0
/*1208 */                     /* set the input output pts pairs */                                                                                                                  // 0.0
/*1210 */                     ost->sync_ipts = (double)ist->pts * is->pts_num /                                                                                                     // 0.0
/*1212 */                         is->pts_den;                                                                                                                                      // 0.0
/*1214 */                     /* XXX: take into account the various fifos,                                                                                                          // 0.0
/*1216 */                        in particular for audio */                                                                                                                         // 0.0
/*1218 */                     ost->sync_opts = ost->st->pts.val;                                                                                                                    // 0.0
/*1220 */                     //printf("ipts=%lld sync_ipts=%f sync_opts=%lld pts.val=%lld pkt.pts=%lld\n", ist->pts, ost->sync_ipts, ost->sync_opts, ost->st->pts.val, pkt.pts);   // 0.0
/*1224 */                     if (ost->encoding_needed) {                                                                                                                           // 0.0
/*1226 */                         switch(ost->st->codec.codec_type) {                                                                                                               // 0.0
/*1228 */                         case CODEC_TYPE_AUDIO:                                                                                                                            // 0.0
/*1230 */                             do_audio_out(os, ost, ist, data_buf, data_size);                                                                                              // 0.0
/*1232 */                             break;                                                                                                                                        // 0.0
/*1234 */                         case CODEC_TYPE_VIDEO:                                                                                                                            // 0.0
/*1236 */                             /* find an audio stream for synchro */                                                                                                        // 0.0
/*1238 */                             {                                                                                                                                             // 0.0
/*1240 */                                 int i;                                                                                                                                    // 0.0
/*1242 */                                 AVOutputStream *audio_sync, *ost1;                                                                                                        // 0.0
/*1244 */                                 audio_sync = NULL;                                                                                                                        // 0.0
/*1246 */                                 for(i=0;i<nb_ostreams;i++) {                                                                                                              // 0.0
/*1248 */                                     ost1 = ost_table[i];                                                                                                                  // 0.0
/*1250 */                                     if (ost1->file_index == ost->file_index &&                                                                                            // 0.0
/*1252 */                                         ost1->st->codec.codec_type == CODEC_TYPE_AUDIO) {                                                                                 // 0.0
/*1254 */                                         audio_sync = ost1;                                                                                                                // 0.0
/*1256 */                                         break;                                                                                                                            // 0.0
/*1258 */                                     }                                                                                                                                     // 0.0
/*1260 */                                 }                                                                                                                                         // 0.0
/*1264 */                                 do_video_out(os, ost, ist, &picture, &frame_size, audio_sync);                                                                            // 0.0
/*1266 */                                 if (do_vstats && frame_size)                                                                                                              // 0.0
/*1268 */                                     do_video_stats(os, ost, frame_size);                                                                                                  // 0.0
/*1270 */                             }                                                                                                                                             // 0.0
/*1272 */                             break;                                                                                                                                        // 0.0
/*1274 */                         default:                                                                                                                                          // 0.0
/*1276 */                             av_abort();                                                                                                                                   // 0.0
/*1278 */                         }                                                                                                                                                 // 0.0
/*1280 */                     } else {                                                                                                                                              // 0.0
/*1282 */                         AVFrame avframe;                                                                                                                                  // 0.0
/*1284 */                                                                                                                                                                           // 0.0
/*1286 */                         /* no reencoding needed : output the packet directly */                                                                                           // 0.0
/*1288 */                         /* force the input stream PTS */                                                                                                                  // 0.0
/*1290 */                                                                                                                                                                           // 0.0
/*1292 */                         memset(&avframe, 0, sizeof(AVFrame));                                                                                                             // 0.0
/*1294 */                         ost->st->codec.coded_frame= &avframe;                                                                                                             // 0.0
/*1296 */ 			avframe.key_frame = pkt.flags & PKT_FLAG_KEY;                                                                                                                          // 0.0
/*1298 */                                                                                                                                                                           // 0.0
/*1300 */                         av_write_frame(os, ost->index, data_buf, data_size);                                                                                              // 0.0
/*1302 */ 			ost->st->codec.frame_number++;                                                                                                                                         // 0.0
/*1304 */ 			ost->frame_number++;                                                                                                                                                   // 0.0
/*1306 */                     }                                                                                                                                                     // 0.0
/*1308 */                 }                                                                                                                                                         // 0.0
/*1310 */             }                                                                                                                                                             // 0.0
/*1312 */             av_free(buffer_to_free);                                                                                                                                      // 0.0
/*1314 */         }                                                                                                                                                                 // 0.0
/*1316 */     discard_packet:                                                                                                                                                       // 0.0
/*1318 */         av_free_packet(&pkt);                                                                                                                                             // 0.0
/*1320 */                                                                                                                                                                           // 0.0
/*1322 */         /* dump report by using the output first video and audio streams */                                                                                               // 0.0
/*1324 */         print_report(output_files, ost_table, nb_ostreams, 0);                                                                                                            // 0.0
/*1326 */     }                                                                                                                                                                     // 0.0
/*1328 */     term_exit();                                                                                                                                                          // 0.0
/*1332 */     /* dump report by using the first video and audio streams */                                                                                                          // 0.0
/*1334 */     print_report(output_files, ost_table, nb_ostreams, 1);                                                                                                                // 0.0
/*1338 */     /* close each encoder */                                                                                                                                              // 0.0
/*1340 */     for(i=0;i<nb_ostreams;i++) {                                                                                                                                          // 0.0
/*1342 */         ost = ost_table[i];                                                                                                                                               // 0.0
/*1344 */         if (ost->encoding_needed) {                                                                                                                                       // 0.0
/*1346 */             av_freep(&ost->st->codec.stats_in);                                                                                                                           // 0.0
/*1348 */             avcodec_close(&ost->st->codec);                                                                                                                               // 0.0
/*1350 */         }                                                                                                                                                                 // 0.0
/*1352 */     }                                                                                                                                                                     // 0.0
/*1354 */                                                                                                                                                                           // 0.0
/*1356 */     /* close each decoder */                                                                                                                                              // 0.0
/*1358 */     for(i=0;i<nb_istreams;i++) {                                                                                                                                          // 0.0
/*1360 */         ist = ist_table[i];                                                                                                                                               // 0.0
/*1362 */         if (ist->decoding_needed) {                                                                                                                                       // 0.0
/*1364 */             avcodec_close(&ist->st->codec);                                                                                                                               // 0.0
/*1366 */         }                                                                                                                                                                 // 0.0
/*1368 */     }                                                                                                                                                                     // 0.0
/*1370 */                                                                                                                                                                           // 0.0
/*1374 */     /* write the trailer if needed and close file */                                                                                                                      // 0.0
/*1376 */     for(i=0;i<nb_output_files;i++) {                                                                                                                                      // 0.0
/*1378 */         os = output_files[i];                                                                                                                                             // 0.0
/*1380 */         av_write_trailer(os);                                                                                                                                             // 0.0
/*1382 */     }                                                                                                                                                                     // 0.0
/*1384 */     /* finished ! */                                                                                                                                                      // 0.0
/*1386 */                                                                                                                                                                           // 0.0
/*1388 */     ret = 0;                                                                                                                                                              // 0.0
/*1390 */  fail1:                                                                                                                                                                   // 0.0
/*1392 */     av_free(file_table);                                                                                                                                                  // 0.0
/*1396 */     if (ist_table) {                                                                                                                                                      // 0.0
/*1398 */         for(i=0;i<nb_istreams;i++) {                                                                                                                                      // 0.0
/*1400 */             ist = ist_table[i];                                                                                                                                           // 0.0
/*1402 */             av_free(ist);                                                                                                                                                 // 0.0
/*1404 */         }                                                                                                                                                                 // 0.0
/*1406 */         av_free(ist_table);                                                                                                                                               // 0.0
/*1408 */     }                                                                                                                                                                     // 0.0
/*1410 */     if (ost_table) {                                                                                                                                                      // 0.0
/*1412 */         for(i=0;i<nb_ostreams;i++) {                                                                                                                                      // 0.0
/*1414 */             ost = ost_table[i];                                                                                                                                           // 0.0
/*1416 */             if (ost) {                                                                                                                                                    // 0.0
/*1418 */                 if (ost->logfile) {                                                                                                                                       // 0.0
/*1420 */                     fclose(ost->logfile);                                                                                                                                 // 0.0
/*1422 */                     ost->logfile = NULL;                                                                                                                                  // 0.0
/*1424 */                 }                                                                                                                                                         // 0.0
/*1426 */                 fifo_free(&ost->fifo); /* works even if fifo is not                                                                                                       // 0.0
/*1428 */                                           initialized but set to zero */                                                                                                  // 0.0
/*1430 */                 av_free(ost->pict_tmp.data[0]);                                                                                                                           // 0.0
/*1432 */                 if (ost->video_resample)                                                                                                                                  // 0.0
/*1434 */                     img_resample_close(ost->img_resample_ctx);                                                                                                            // 0.0
/*1436 */                 if (ost->audio_resample)                                                                                                                                  // 0.0
/*1438 */                     audio_resample_close(ost->resample);                                                                                                                  // 0.0
/*1440 */                 av_free(ost);                                                                                                                                             // 0.0
/*1442 */             }                                                                                                                                                             // 0.0
/*1444 */         }                                                                                                                                                                 // 0.0
/*1446 */         av_free(ost_table);                                                                                                                                               // 0.0
/*1448 */     }                                                                                                                                                                     // 0.0
/*1450 */     return ret;                                                                                                                                                           // 0.0
/*1452 */  fail:                                                                                                                                                                    // 0.0
/*1454 */     ret = -ENOMEM;                                                                                                                                                        // 0.0
/*1456 */     goto fail1;                                                                                                                                                           // 0.0
/*1458 */ }                                                                                                                                                                         // 0.0
