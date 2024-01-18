// commit message FFmpeg@da048c6d24 (target=1, prob=0.37069756, correct=False): avformat/movenc: Check failure of allocation of ctts_entries and propagate error
/*0  */ static int mov_write_stbl_tag(AVIOContext *pb, MOVTrack *track)       // (6) 0.05288
/*2  */ {                                                                     // (19) 0.002404
/*4  */     int64_t pos = avio_tell(pb);                                      // (11) 0.03846
/*6  */     avio_wb32(pb, 0); /* size */                                      // (12) 0.03846
/*8  */     ffio_wfourcc(pb, "stbl");                                         // (10) 0.03846
/*10 */     mov_write_stsd_tag(pb, track);                                    // (13) 0.03846
/*12 */     mov_write_stts_tag(pb, track);                                    // (14) 0.03846
/*14 */     if ((track->enc->codec_type == AVMEDIA_TYPE_VIDEO ||              // (8) 0.05288
/*16 */          track->enc->codec_tag == MKTAG('r','t','p',' ')) &&          // (1) 0.06971
/*18 */         track->has_keyframes && track->has_keyframes < track->entry)  // (4) 0.0601
/*20 */         mov_write_stss_tag(pb, track, MOV_SYNC_SAMPLE);               // (2) 0.06731
/*22 */     if (track->mode == MODE_MOV && track->flags & MOV_TRACK_STPS)     // (3) 0.0649
/*24 */         mov_write_stss_tag(pb, track, MOV_PARTIAL_SYNC_SAMPLE);       // (0) 0.07452
/*26 */     if (track->enc->codec_type == AVMEDIA_TYPE_VIDEO &&               // (7) 0.05288
/*28 */         track->flags & MOV_TRACK_CTTS && track->entry)                // (5) 0.05529
/*30 */         mov_write_ctts_tag(pb, track);                                // (9) 0.04808
/*32 */     mov_write_stsc_tag(pb, track);                                    // (15) 0.03846
/*34 */     mov_write_stsz_tag(pb, track);                                    // (16) 0.03846
/*36 */     mov_write_stco_tag(pb, track);                                    // (17) 0.03846
/*38 */     return update_size(pb, pos);                                      // (18) 0.02885
/*40 */ }                                                                     // (20) 0.002404
