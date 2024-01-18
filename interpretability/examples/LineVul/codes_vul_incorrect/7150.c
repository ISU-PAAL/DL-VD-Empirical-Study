// commit message FFmpeg@0efb610611 (target=1, prob=0.2815821, correct=False): mxfdec: fix NULL pointer dereference
/*0  */ static int mxf_get_stream_index(AVFormatContext *s, KLVPacket *klv)                                                 // (2) 0.1132
/*2  */ {                                                                                                                   // (10) 0.004717
/*4  */     int i;                                                                                                          // (8) 0.0283
/*8  */     for (i = 0; i < s->nb_streams; i++) {                                                                           // (4) 0.09906
/*10 */         MXFTrack *track = s->streams[i]->priv_data;                                                                 // (1) 0.1179
/*12 */         /* SMPTE 379M 7.3 */                                                                                        // (6) 0.08019
/*14 */         if (!memcmp(klv->key + sizeof(mxf_essence_element_key), track->track_number, sizeof(track->track_number)))  // (0) 0.2028
/*16 */             return i;                                                                                               // (7) 0.06604
/*18 */     }                                                                                                               // (9) 0.01887
/*20 */     /* return 0 if only one stream, for OP Atom files with 0 as track number */                                     // (3) 0.09906
/*22 */     return s->nb_streams == 1 ? 0 : -1;                                                                             // (5) 0.08491
/*24 */ }                                                                                                                   // (11) 0.004717
