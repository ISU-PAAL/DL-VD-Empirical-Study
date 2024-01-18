// commit message FFmpeg@a7f27453f6 (target=0, prob=0.11445574, correct=True): avformat/mov: Check that we have a stream before accessing it in mov_read_ares()
/*0  */ static int mov_read_ares(MOVContext *c, AVIOContext *pb, MOVAtom atom)                           // (3) 0.09434
/*2  */ {                                                                                                // (12) 0.003774
/*4  */     AVCodecContext *codec = c->fc->streams[c->fc->nb_streams-1]->codec;                          // (0) 0.1245
/*6  */     if (codec->codec_tag == MKTAG('A', 'V', 'i', 'n') &&                                         // (2) 0.1057
/*8  */         codec->codec_id == AV_CODEC_ID_H264 &&                                                   // (4) 0.09434
/*10 */         atom.size > 11) {                                                                        // (9) 0.05283
/*12 */         avio_skip(pb, 10);                                                                       // (8) 0.06038
/*14 */         /* For AVID AVCI50, force width of 1440 to be able to select the correct SPS and PPS */  // (1) 0.1208
/*16 */         if (avio_rb16(pb) == 0xd4d)                                                              // (5) 0.08679
/*18 */             codec->width = 1440;                                                                 // (6) 0.06415
/*20 */         return 0;                                                                                // (10) 0.03774
/*22 */     }                                                                                            // (11) 0.01509
/*26 */     return mov_read_avid(c, pb, atom);                                                           // (7) 0.06415
/*28 */ }                                                                                                // (13) 0.003774
