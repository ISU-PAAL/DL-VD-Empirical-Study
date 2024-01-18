// commit message FFmpeg@86dfcfd0e3 (target=1, prob=0.56103367, correct=True): mov: Drop unused parameter from ff_mov_read_esds()
/*0   */ static int read_kuki_chunk(AVFormatContext *s, int64_t size)                            // (9) 0.04301
/*2   */ {                                                                                       // (24) 0.001953
/*4   */     AVIOContext *pb = s->pb;                                                            // (16) 0.02538
/*6   */     AVStream *st      = s->streams[0];                                                  // (12) 0.03905
/*10  */     if (size < 0 || size > INT_MAX - FF_INPUT_BUFFER_PADDING_SIZE)                      // (2) 0.05662
/*12  */         return -1;                                                                      // (20) 0.02148
/*16  */     if (st->codec->codec_id == AV_CODEC_ID_AAC) {                                       // (4) 0.05272
/*18  */         /* The magic cookie format for AAC is an mp4 esds atom.                         // (10) 0.04295
/*20  */            The lavc AAC decoder requires the data from the codec specific               // (7) 0.0449
/*22  */            description as extradata input. */                                           // (14) 0.03319
/*24  */         int strt, skip;                                                                 // (17) 0.02538
/*26  */         MOVAtom atom;                                                                   // (18) 0.02343
/*30  */         strt = avio_tell(pb);                                                           // (13) 0.03319
/*32  */         ff_mov_read_esds(s, pb, atom);                                                  // (5) 0.04686
/*34  */         skip = size - (avio_tell(pb) - strt);                                           // (8) 0.0449
/*36  */         if (skip < 0 || !st->codec->extradata ||                                        // (6) 0.04491
/*38  */             st->codec->codec_id != AV_CODEC_ID_AAC) {                                   // (0) 0.06443
/*40  */             av_log(s, AV_LOG_ERROR, "invalid AAC magic cookie\n");                      // (1) 0.06248
/*42  */             return AVERROR_INVALIDDATA;                                                 // (11) 0.041
/*44  */         }                                                                               // (23) 0.01562
/*46  */         avio_skip(pb, skip);                                                            // (15) 0.03124
/*48  */     } else if (st->codec->codec_id == AV_CODEC_ID_ALAC) {                               // (3) 0.05662
/*50  */ #define ALAC_PREAMBLE 12                                                                // (22) 0.01758
/*52  */ #define ALAC_HEADER   36                                                                // (21) 0.01963
/*54  */ #define ALAC_NEW_KUKI 24                                                                // (19) 0.02151
/*56  */         uint8_t preamble[12];                                                           // 0.0
/*58  */         if (size < ALAC_NEW_KUKI) {                                                     // 0.0
/*60  */             av_log(s, AV_LOG_ERROR, "invalid ALAC magic cookie\n");                     // 0.0
/*62  */             avio_skip(pb, size);                                                        // 0.0
/*64  */             return AVERROR_INVALIDDATA;                                                 // 0.0
/*66  */         }                                                                               // 0.0
/*68  */         avio_read(pb, preamble, ALAC_PREAMBLE);                                         // 0.0
/*72  */         st->codec->extradata = av_mallocz(ALAC_HEADER + FF_INPUT_BUFFER_PADDING_SIZE);  // 0.0
/*74  */         if (!st->codec->extradata)                                                      // 0.0
/*76  */             return AVERROR(ENOMEM);                                                     // 0.0
/*80  */         /* For the old style cookie, we skip 12 bytes, then read 36 bytes.              // 0.0
/*82  */          * The new style cookie only contains the last 24 bytes of what was             // 0.0
/*84  */          * 36 bytes in the old style cookie, so we fabricate the first 12 bytes         // 0.0
/*86  */          * in that case to maintain compatibility. */                                   // 0.0
/*88  */         if (!memcmp(&preamble[4], "frmaalac", 8)) {                                     // 0.0
/*90  */             if (size < ALAC_PREAMBLE + ALAC_HEADER) {                                   // 0.0
/*92  */                 av_log(s, AV_LOG_ERROR, "invalid ALAC magic cookie\n");                 // 0.0
/*94  */                 av_freep(&st->codec->extradata);                                        // 0.0
/*96  */                 return AVERROR_INVALIDDATA;                                             // 0.0
/*98  */             }                                                                           // 0.0
/*100 */             avio_read(pb, st->codec->extradata, ALAC_HEADER);                           // 0.0
/*102 */             avio_skip(pb, size - ALAC_PREAMBLE - ALAC_HEADER);                          // 0.0
/*104 */         } else {                                                                        // 0.0
/*106 */             AV_WB32(st->codec->extradata, 36);                                          // 0.0
/*108 */             memcpy(&st->codec->extradata[4], "alac", 4);                                // 0.0
/*110 */             AV_WB32(&st->codec->extradata[8], 0);                                       // 0.0
/*112 */             memcpy(&st->codec->extradata[12], preamble, 12);                            // 0.0
/*114 */             avio_read(pb, &st->codec->extradata[24], ALAC_NEW_KUKI - 12);               // 0.0
/*116 */             avio_skip(pb, size - ALAC_NEW_KUKI);                                        // 0.0
/*118 */         }                                                                               // 0.0
/*120 */         st->codec->extradata_size = ALAC_HEADER;                                        // 0.0
/*122 */     } else {                                                                            // 0.0
/*124 */         st->codec->extradata = av_mallocz(size + FF_INPUT_BUFFER_PADDING_SIZE);         // 0.0
/*126 */         if (!st->codec->extradata)                                                      // 0.0
/*128 */             return AVERROR(ENOMEM);                                                     // 0.0
/*130 */         avio_read(pb, st->codec->extradata, size);                                      // 0.0
/*132 */         st->codec->extradata_size = size;                                               // 0.0
/*134 */     }                                                                                   // 0.0
/*138 */     return 0;                                                                           // 0.0
/*140 */ }                                                                                       // 0.0
