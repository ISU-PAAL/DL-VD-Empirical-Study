// commit message FFmpeg@465e1dadbe (target=0, prob=0.36904374, correct=True): 10l (bytes_left() -> url_feof()) 10l (updating LRU delta pts for type 1/2 frames) ensure that checksumming isnt enabled if its not needed search for next startcode and then search backward to the next valid frame if an inconsistancy is detected deal with non-frame startcodes in the middle of the stream
/*0   */ static int nut_read_header(AVFormatContext *s, AVFormatParameters *ap)     // (9) 0.03906
/*2   */ {                                                                          // (32) 0.001953
/*4   */     NUTContext *nut = s->priv_data;                                        // (12) 0.0293
/*6   */     ByteIOContext *bc = &s->pb;                                            // (15) 0.02734
/*8   */     int64_t pos;                                                           // (20) 0.01758
/*10  */     int inited_stream_count;                                               // (18) 0.02148
/*14  */     nut->avf= s;                                                           // (19) 0.01953
/*16  */                                                                            // (28) 0.007812
/*18  */     av_set_pts_info(s, 60, 1, AV_TIME_BASE);                               // (5) 0.04883
/*22  */     /* main header */                                                      // (24) 0.01367
/*24  */     pos=0;                                                                 // (25) 0.01367
/*26  */     for(;;){                                                               // (26) 0.01367
/*28  */         if (find_startcode(bc, MAIN_STARTCODE, pos)<0){                    // (3) 0.05469
/*30  */             av_log(s, AV_LOG_ERROR, "no main startcode found\n");          // (0) 0.0625
/*32  */             return -1;                                                     // (13) 0.0293
/*34  */         }                                                                  // (21) 0.01562
/*36  */         pos= url_ftell(bc);                                                // (10) 0.03125
/*38  */         if(decode_main_header(nut) >= 0)                                   // (7) 0.04102
/*40  */             break;                                                         // (16) 0.02539
/*42  */     }                                                                      // (29) 0.007812
/*44  */                                                                            // (30) 0.007812
/*46  */                                                                            // (31) 0.007812
/*48  */     s->bit_rate = 0;                                                       // (17) 0.02148
/*52  */     nut->stream = av_malloc(sizeof(StreamContext)*nut->stream_count);      // (6) 0.04688
/*56  */     /* stream headers */                                                   // (23) 0.01367
/*58  */     pos=0;                                                                 // (27) 0.01367
/*60  */     for(inited_stream_count=0; inited_stream_count < nut->stream_count;){  // (2) 0.05469
/*62  */         if (find_startcode(bc, STREAM_STARTCODE, pos)<0){                  // (4) 0.05469
/*64  */             av_log(s, AV_LOG_ERROR, "not all stream headers found\n");     // (1) 0.0625
/*66  */             return -1;                                                     // (14) 0.0293
/*68  */         }                                                                  // (22) 0.01562
/*70  */         pos= url_ftell(bc);                                                // (11) 0.03125
/*72  */         if(decode_stream_header(nut) >= 0)                                 // (8) 0.04102
/*74  */             inited_stream_count++;                                         // 0.0
/*76  */     }                                                                      // 0.0
/*80  */     /* info headers */                                                     // 0.0
/*82  */     pos=0;                                                                 // 0.0
/*84  */     for(;;){                                                               // 0.0
/*86  */         uint64_t startcode= find_any_startcode(bc, pos);                   // 0.0
/*88  */         pos= url_ftell(bc);                                                // 0.0
/*92  */         if(startcode==0){                                                  // 0.0
/*94  */             av_log(s, AV_LOG_ERROR, "EOF before video frames\n");          // 0.0
/*96  */             return -1;                                                     // 0.0
/*98  */         }else if(startcode == KEYFRAME_STARTCODE){                         // 0.0
/*100 */             url_fseek(bc, -8, SEEK_CUR); //FIXME                           // 0.0
/*102 */             break;                                                         // 0.0
/*104 */         }else if(startcode != INFO_STARTCODE){                             // 0.0
/*106 */             continue;                                                      // 0.0
/*108 */         }                                                                  // 0.0
/*112 */         decode_info_header(nut);                                           // 0.0
/*114 */     }                                                                      // 0.0
/*118 */     return 0;                                                              // 0.0
/*120 */ }                                                                          // 0.0
