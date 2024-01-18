// commit message FFmpeg@5c720657c2 (target=1, prob=0.64885896, correct=True): mov: always check avio_read return value
/*0  */ static int mov_read_strf(MOVContext *c, AVIOContext *pb, MOVAtom atom)                 // (1) 0.08254
/*2  */ {                                                                                      // (17) 0.003175
/*4  */     AVStream *st;                                                                      // (15) 0.0254
/*8  */     if (c->fc->nb_streams < 1)                                                         // (7) 0.05079
/*10 */         return 0;                                                                      // (13) 0.03175
/*12 */     if (atom.size <= 40)                                                               // (12) 0.03492
/*14 */         return 0;                                                                      // (14) 0.03175
/*16 */     st = c->fc->streams[c->fc->nb_streams-1];                                          // (3) 0.07302
/*20 */     if ((uint64_t)atom.size > (1<<30))                                                 // (5) 0.06032
/*22 */         return AVERROR_INVALIDDATA;                                                    // (6) 0.05397
/*26 */     av_free(st->codec->extradata);                                                     // (8) 0.05079
/*28 */     st->codec->extradata = av_mallocz(atom.size - 40 + FF_INPUT_BUFFER_PADDING_SIZE);  // (0) 0.1206
/*30 */     if (!st->codec->extradata)                                                         // (10) 0.04444
/*32 */         return AVERROR(ENOMEM);                                                        // (9) 0.05079
/*34 */     st->codec->extradata_size = atom.size - 40;                                        // (4) 0.06349
/*36 */     avio_skip(pb, 40);                                                                 // (11) 0.0381
/*38 */     avio_read(pb, st->codec->extradata, atom.size - 40);                               // (2) 0.07937
/*40 */     return 0;                                                                          // (16) 0.01905
/*42 */ }                                                                                      // (18) 0.003175
