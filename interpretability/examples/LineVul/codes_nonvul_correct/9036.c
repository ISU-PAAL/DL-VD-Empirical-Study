// commit message FFmpeg@93c04e095d (target=0, prob=0.48461607, correct=True): Expose metadata found in onCuePoint events in .flv files.
/*0  */ static int flv_read_metabody(AVFormatContext *s, int64_t next_pos)       // (3) 0.04854
/*2  */ {                                                                        // (30) 0.001925
/*4  */     AMFDataType type;                                                    // (24) 0.01707
/*6  */     AVStream *stream, *astream, *vstream;                                // (10) 0.03041
/*8  */     AVIOContext *ioc;                                                    // (22) 0.01912
/*10 */     int i;                                                               // (28) 0.01145
/*12 */     // only needs to hold the string "onMetaData".                       // (8) 0.03154
/*14 */     // Anything longer is something we don't want.                       // (6) 0.03476
/*16 */     char buffer[11];                                                     // (25) 0.01669
/*20 */     astream = NULL;                                                      // (26) 0.01519
/*22 */     vstream = NULL;                                                      // (27) 0.01516
/*24 */     ioc     = s->pb;                                                     // (19) 0.02654
/*28 */     // first object needs to be "onMetaData" string                      // (14) 0.02917
/*30 */     type = avio_r8(ioc);                                                 // (18) 0.02655
/*32 */     if (type != AMF_DATA_TYPE_STRING ||                                  // (7) 0.03221
/*34 */         amf_get_string(ioc, buffer, sizeof(buffer)) < 0)                 // (2) 0.04933
/*36 */         return -1;                                                       // (21) 0.02086
/*40 */     if (!strcmp(buffer, "onTextData"))                                   // (15) 0.02843
/*42 */         return 1;                                                        // (23) 0.01892
/*46 */     if (strcmp(buffer, "onMetaData"))                                    // (16) 0.02841
/*48 */         return -1;                                                       // (20) 0.02086
/*52 */     // find the streams now so that amf_parse_object doesn't need to do  // (4) 0.04155
/*54 */     // the lookup every time it is called.                               // (17) 0.02708
/*56 */     for (i = 0; i < s->nb_streams; i++) {                                // (5) 0.04006
/*58 */         stream = s->streams[i];                                          // (12) 0.03028
/*60 */         if (stream->codec->codec_type == AVMEDIA_TYPE_AUDIO)             // (1) 0.05299
/*62 */             astream = stream;                                            // (13) 0.03026
/*64 */         else if (stream->codec->codec_type == AVMEDIA_TYPE_VIDEO)        // (0) 0.05303
/*66 */             vstream = stream;                                            // (11) 0.0303
/*68 */     }                                                                    // (29) 0.00791
/*72 */     // parse the second object (we want a mixed array)                   // (9) 0.03076
/*74 */     if (amf_parse_object(s, astream, vstream, buffer, next_pos, 0) < 0)  // 0.0
/*76 */         return -1;                                                       // 0.0
/*80 */     return 0;                                                            // 0.0
/*82 */ }                                                                        // 0.0
