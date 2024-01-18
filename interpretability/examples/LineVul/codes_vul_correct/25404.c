// commit message FFmpeg@9e1c55cfde (target=1, prob=0.72643334, correct=True): oggdec: check stream index before using it in ogg_get_length()
/*0   */ static int ogg_get_length(AVFormatContext *s)                                                                     // (12) 0.0293
/*2   */ {                                                                                                                 // (25) 0.001953
/*4   */     struct ogg *ogg = s->priv_data;                                                                               // (13) 0.0293
/*6   */     int i;                                                                                                        // (23) 0.01172
/*8   */     int64_t size, end;                                                                                            // (16) 0.02148
/*10  */     int streams_left=0;                                                                                           // (18) 0.01953
/*14  */     if(!s->pb->seekable)                                                                                          // (15) 0.02539
/*16  */         return 0;                                                                                                 // (17) 0.01953
/*20  */ // already set                                                                                                    // (24) 0.005859
/*22  */     if (s->duration != AV_NOPTS_VALUE)                                                                            // (11) 0.0332
/*24  */         return 0;                                                                                                 // (20) 0.01953
/*28  */     size = avio_size(s->pb);                                                                                      // (14) 0.02734
/*30  */     if(size < 0)                                                                                                  // (22) 0.01758
/*32  */         return 0;                                                                                                 // (21) 0.01953
/*34  */     end = size > MAX_PAGE_SIZE? size - MAX_PAGE_SIZE: 0;                                                          // (6) 0.04883
/*38  */     ogg_save (s);                                                                                                 // (19) 0.01953
/*40  */     avio_seek (s->pb, end, SEEK_SET);                                                                             // (9) 0.03711
/*44  */     while (!ogg_read_page (s, &i)){                                                                               // (10) 0.0332
/*46  */         if (ogg->streams[i].granule != -1 && ogg->streams[i].granule != 0 &&                                      // (3) 0.06836
/*48  */             ogg->streams[i].codec) {                                                                              // (7) 0.04492
/*50  */             s->streams[i]->duration =                                                                             // (8) 0.04102
/*52  */                 ogg_gptopts (s, i, ogg->streams[i].granule, NULL);                                                // (0) 0.07812
/*54  */             if (s->streams[i]->start_time != AV_NOPTS_VALUE){                                                     // (4) 0.06445
/*56  */                 s->streams[i]->duration -= s->streams[i]->start_time;                                             // (1) 0.07227
/*58  */                 streams_left-= (ogg->streams[i].got_start==-1);                                                   // (2) 0.06836
/*60  */                 ogg->streams[i].got_start= 1;                                                                     // (5) 0.05664
/*62  */             }else if(!ogg->streams[i].got_start){                                                                 // 0.0
/*64  */                 ogg->streams[i].got_start= -1;                                                                    // 0.0
/*66  */                 streams_left++;                                                                                   // 0.0
/*68  */             }                                                                                                     // 0.0
/*70  */         }                                                                                                         // 0.0
/*72  */     }                                                                                                             // 0.0
/*76  */     ogg_restore (s, 0);                                                                                           // 0.0
/*80  */     ogg_save (s);                                                                                                 // 0.0
/*82  */     avio_seek (s->pb, s->data_offset, SEEK_SET);                                                                  // 0.0
/*84  */     ogg_reset(s);                                                                                                 // 0.0
/*87  */     while (!ogg_packet(s, &i, NULL, NULL, NULL)) {                                                                // 0.0
/*90  */         int64_t pts = ogg_calc_pts(s, i, NULL);                                                                   // 0.0
/*92  */         if (pts != AV_NOPTS_VALUE && s->streams[i]->start_time == AV_NOPTS_VALUE && !ogg->streams[i].got_start){  // 0.0
/*94  */             s->streams[i]->duration -= pts;                                                                       // 0.0
/*96  */             ogg->streams[i].got_start= 1;                                                                         // 0.0
/*98  */             streams_left--;                                                                                       // 0.0
/*100 */         }else if(s->streams[i]->start_time != AV_NOPTS_VALUE && !ogg->streams[i].got_start){                      // 0.0
/*102 */             ogg->streams[i].got_start= 1;                                                                         // 0.0
/*104 */             streams_left--;                                                                                       // 0.0
/*106 */         }                                                                                                         // 0.0
/*108 */         }                                                                                                         // 0.0
/*110 */             if(streams_left<=0)                                                                                   // 0.0
/*112 */                 break;                                                                                            // 0.0
/*114 */     }                                                                                                             // 0.0
/*116 */     ogg_restore (s, 0);                                                                                           // 0.0
/*120 */     return 0;                                                                                                     // 0.0
/*122 */ }                                                                                                                 // 0.0
