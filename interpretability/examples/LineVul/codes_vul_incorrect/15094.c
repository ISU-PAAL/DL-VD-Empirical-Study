// commit message FFmpeg@a443a2530d (target=1, prob=0.4229341, correct=False): sanity checks some might have been exploitable
/*0   */ static int vmd_read_header(AVFormatContext *s,                                                       // (14) 0.0293
/*2   */                            AVFormatParameters *ap)                                                   // (1) 0.0625
/*4   */ {                                                                                                    // (30) 0.001954
/*6   */     VmdDemuxContext *vmd = (VmdDemuxContext *)s->priv_data;                                          // (2) 0.04883
/*8   */     ByteIOContext *pb = &s->pb;                                                                      // (16) 0.02734
/*10  */     AVStream *st;                                                                                    // (28) 0.01563
/*12  */     unsigned int toc_offset;                                                                         // (23) 0.01953
/*14  */     unsigned char *raw_frame_table;                                                                  // (21) 0.02344
/*16  */     int raw_frame_table_size;                                                                        // (20) 0.02344
/*18  */     offset_t current_offset;                                                                         // (24) 0.01953
/*20  */     int i, j;                                                                                        // (27) 0.01563
/*22  */     unsigned int total_frames;                                                                       // (25) 0.01758
/*24  */     int64_t video_pts_inc = 0;                                                                       // (10) 0.03125
/*26  */     int64_t current_video_pts = 0;                                                                   // (9) 0.03125
/*28  */     unsigned char chunk[BYTES_PER_FRAME_RECORD];                                                     // (6) 0.03711
/*30  */     int lastframe = 0;                                                                               // (26) 0.01758
/*34  */     /* fetch the main header, including the 2 header length bytes */                                 // (8) 0.03125
/*36  */     url_fseek(pb, 0, SEEK_SET);                                                                      // (7) 0.0332
/*38  */     if (get_buffer(pb, vmd->vmd_header, VMD_HEADER_SIZE) != VMD_HEADER_SIZE)                         // (0) 0.07031
/*40  */         return AVERROR_IO;                                                                           // (19) 0.02734
/*44  */     vmd->audio_sample_counter = 0;                                                                   // (18) 0.02734
/*46  */     vmd->audio_frame_divisor = 1;                                                                    // (11) 0.03125
/*48  */     vmd->audio_block_align = 1;                                                                      // (17) 0.02734
/*52  */     /* start up the decoders */                                                                      // (22) 0.02148
/*54  */     st = av_new_stream(s, 0);                                                                        // (15) 0.0293
/*56  */     if (!st)                                                                                         // (29) 0.01367
/*58  */         return AVERROR_NOMEM;                                                                        // (13) 0.03125
/*60  */     av_set_pts_info(st, 33, 1, 90000);                                                               // (4) 0.04102
/*62  */     vmd->video_stream_index = st->index;                                                             // (12) 0.03125
/*64  */     st->codec->codec_type = CODEC_TYPE_VIDEO;                                                        // (5) 0.04102
/*66  */     st->codec->codec_id = CODEC_ID_VMDVIDEO;                                                         // (3) 0.04492
/*68  */     st->codec->codec_tag = 0;  /* no fourcc */                                                       // 0.0
/*70  */     st->codec->width = LE_16(&vmd->vmd_header[12]);                                                  // 0.0
/*72  */     st->codec->height = LE_16(&vmd->vmd_header[14]);                                                 // 0.0
/*74  */     st->codec->time_base.num = 1;                                                                    // 0.0
/*76  */     st->codec->time_base.den = 10;                                                                   // 0.0
/*78  */     st->codec->extradata_size = VMD_HEADER_SIZE;                                                     // 0.0
/*80  */     st->codec->extradata = av_mallocz(VMD_HEADER_SIZE + FF_INPUT_BUFFER_PADDING_SIZE);               // 0.0
/*82  */     memcpy(st->codec->extradata, vmd->vmd_header, VMD_HEADER_SIZE);                                  // 0.0
/*86  */     /* if sample rate is 0, assume no audio */                                                       // 0.0
/*88  */     vmd->sample_rate = LE_16(&vmd->vmd_header[804]);                                                 // 0.0
/*90  */     if (vmd->sample_rate) {                                                                          // 0.0
/*92  */         st = av_new_stream(s, 0);                                                                    // 0.0
/*94  */         if (!st)                                                                                     // 0.0
/*96  */             return AVERROR_NOMEM;                                                                    // 0.0
/*98  */         av_set_pts_info(st, 33, 1, 90000);                                                           // 0.0
/*100 */         vmd->audio_stream_index = st->index;                                                         // 0.0
/*102 */         st->codec->codec_type = CODEC_TYPE_AUDIO;                                                    // 0.0
/*104 */         st->codec->codec_id = CODEC_ID_VMDAUDIO;                                                     // 0.0
/*106 */         st->codec->codec_tag = 0;  /* no fourcc */                                                   // 0.0
/*108 */         st->codec->channels = vmd->audio_channels = (vmd->vmd_header[811] & 0x80) ? 2 : 1;           // 0.0
/*110 */         st->codec->sample_rate = vmd->sample_rate;                                                   // 0.0
/*112 */         st->codec->block_align = vmd->audio_block_align =                                            // 0.0
/*114 */             LE_16(&vmd->vmd_header[806]);                                                            // 0.0
/*116 */         if (st->codec->block_align & 0x8000) {                                                       // 0.0
/*118 */             st->codec->bits_per_sample = 16;                                                         // 0.0
/*120 */             st->codec->block_align = -(st->codec->block_align - 0x10000);                            // 0.0
/*122 */             vmd->audio_block_align = -(vmd->audio_block_align - 0x10000);                            // 0.0
/*124 */         } else {                                                                                     // 0.0
/*126 */             st->codec->bits_per_sample = 8;                                                          // 0.0
/*129 */         st->codec->bit_rate = st->codec->sample_rate *                                               // 0.0
/*131 */             st->codec->bits_per_sample * st->codec->channels;                                        // 0.0
/*135 */         /* for calculating pts */                                                                    // 0.0
/*137 */         vmd->audio_frame_divisor = st->codec->channels;                                              // 0.0
/*141 */         video_pts_inc = 90000;                                                                       // 0.0
/*143 */         video_pts_inc *= st->codec->block_align;                                                     // 0.0
/*145 */         video_pts_inc /= st->codec->sample_rate;                                                     // 0.0
/*147 */         video_pts_inc /= st->codec->channels;                                                        // 0.0
/*149 */     } else {                                                                                         // 0.0
/*151 */         /* if no audio, assume 10 frames/second */                                                   // 0.0
/*153 */         video_pts_inc = 90000 / 10;                                                                  // 0.0
/*158 */     toc_offset = LE_32(&vmd->vmd_header[812]);                                                       // 0.0
/*160 */     vmd->frame_count = LE_16(&vmd->vmd_header[6]);                                                   // 0.0
/*162 */     vmd->frames_per_block = LE_16(&vmd->vmd_header[18]);                                             // 0.0
/*164 */     url_fseek(pb, toc_offset, SEEK_SET);                                                             // 0.0
/*168 */     raw_frame_table = NULL;                                                                          // 0.0
/*170 */     vmd->frame_table = NULL;                                                                         // 0.0
/*172 */     raw_frame_table_size = vmd->frame_count * 6;                                                     // 0.0
/*174 */     raw_frame_table = av_malloc(raw_frame_table_size);                                               // 0.0
/*180 */     vmd->frame_table = av_malloc(vmd->frame_count * vmd->frames_per_block * sizeof(vmd_frame_t));    // 0.0
/*182 */     if (!raw_frame_table || !vmd->frame_table) {                                                     // 0.0
/*184 */         av_free(raw_frame_table);                                                                    // 0.0
/*186 */         av_free(vmd->frame_table);                                                                   // 0.0
/*188 */         return AVERROR_NOMEM;                                                                        // 0.0
/*191 */     if (get_buffer(pb, raw_frame_table, raw_frame_table_size) !=                                     // 0.0
/*193 */         raw_frame_table_size) {                                                                      // 0.0
/*195 */         av_free(raw_frame_table);                                                                    // 0.0
/*197 */         av_free(vmd->frame_table);                                                                   // 0.0
/*199 */         return AVERROR_IO;                                                                           // 0.0
/*204 */     total_frames = 0;                                                                                // 0.0
/*206 */     for (i = 0; i < vmd->frame_count; i++) {                                                         // 0.0
/*210 */         current_offset = LE_32(&raw_frame_table[6 * i + 2]);                                         // 0.0
/*214 */         /* handle each entry in index block */                                                       // 0.0
/*216 */         for (j = 0; j < vmd->frames_per_block; j++) {                                                // 0.0
/*218 */             int type;                                                                                // 0.0
/*220 */             uint32_t size;                                                                           // 0.0
/*224 */             get_buffer(pb, chunk, BYTES_PER_FRAME_RECORD);                                           // 0.0
/*226 */             type = chunk[0];                                                                         // 0.0
/*228 */             size = LE_32(&chunk[2]);                                                                 // 0.0
/*230 */             if(!size)                                                                                // 0.0
/*232 */                 continue;                                                                            // 0.0
/*234 */             switch(type) {                                                                           // 0.0
/*236 */             case 1: /* Audio Chunk */                                                                // 0.0
/*238 */                 vmd->frame_table[total_frames].frame_offset = current_offset;                        // 0.0
/*240 */                 vmd->frame_table[total_frames].stream_index = vmd->audio_stream_index;               // 0.0
/*242 */                 vmd->frame_table[total_frames].frame_size = size;                                    // 0.0
/*244 */                 memcpy(vmd->frame_table[total_frames].frame_record, chunk, BYTES_PER_FRAME_RECORD);  // 0.0
/*246 */                 total_frames++;                                                                      // 0.0
/*248 */                 break;                                                                               // 0.0
/*250 */             case 2: /* Video Chunk */                                                                // 0.0
/*252 */                 vmd->frame_table[total_frames].frame_offset = current_offset;                        // 0.0
/*254 */                 vmd->frame_table[total_frames].frame_size = size;                                    // 0.0
/*256 */                 vmd->frame_table[total_frames].stream_index = vmd->video_stream_index;               // 0.0
/*258 */                 memcpy(vmd->frame_table[total_frames].frame_record, chunk, BYTES_PER_FRAME_RECORD);  // 0.0
/*260 */                 vmd->frame_table[total_frames].pts = current_video_pts;                              // 0.0
/*262 */                 if (lastframe) {                                                                     // 0.0
/*264 */                     vmd->frame_table[lastframe].pts = current_video_pts - video_pts_inc;             // 0.0
/*267 */                 lastframe = total_frames;                                                            // 0.0
/*269 */                 total_frames++;                                                                      // 0.0
/*271 */                 break;                                                                               // 0.0
/*274 */             current_offset += size;                                                                  // 0.0
/*277 */         current_video_pts += video_pts_inc;                                                          // 0.0
/*282 */     av_free(raw_frame_table);                                                                        // 0.0
/*286 */     vmd->current_frame = 0;                                                                          // 0.0
/*288 */     vmd->frame_count = total_frames;                                                                 // 0.0
/*292 */     return 0;                                                                                        // 0.0
