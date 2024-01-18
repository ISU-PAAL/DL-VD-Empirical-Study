// commit message FFmpeg@2e5195646d (target=1, prob=0.6446071, correct=True): Do not leave uninitialized data in the packet in MPC demuxer. Should allow for adding a demuxer test to FATE.
/*0   */ static int mpc_read_packet(AVFormatContext *s, AVPacket *pkt)                    // (5) 0.04492
/*2   */ {                                                                                // (28) 0.001953
/*4   */     MPCContext *c = s->priv_data;                                                // (13) 0.0293
/*6   */     int ret, size, size2, curbits, cur = c->curframe;                            // (6) 0.04102
/*8   */     int64_t tmp, pos;                                                            // (21) 0.02148
/*12  */     if (c->curframe >= c->fcount)                                                // (14) 0.0293
/*14  */         return -1;                                                               // (22) 0.02148
/*18  */     if(c->curframe != c->lastframe + 1){                                         // (10) 0.0332
/*20  */         url_fseek(s->pb, c->frames[c->curframe].pos, SEEK_SET);                  // (0) 0.0625
/*22  */         c->curbits = c->frames[c->curframe].skip;                                // (3) 0.04688
/*24  */     }                                                                            // (26) 0.007812
/*26  */     c->lastframe = c->curframe;                                                  // (18) 0.02539
/*28  */     c->curframe++;                                                               // (23) 0.01562
/*30  */     curbits = c->curbits;                                                        // (19) 0.02344
/*32  */     pos = url_ftell(s->pb);                                                      // (15) 0.02734
/*34  */     tmp = get_le32(s->pb);                                                       // (16) 0.02734
/*36  */     if(curbits <= 12){                                                           // (20) 0.02148
/*38  */         size2 = (tmp >> (12 - curbits)) & 0xFFFFF;                               // (1) 0.04883
/*40  */     }else{                                                                       // (25) 0.01172
/*42  */         tmp = (tmp << 32) | get_le32(s->pb);                                     // (4) 0.04688
/*44  */         size2 = (tmp >> (44 - curbits)) & 0xFFFFF;                               // (2) 0.04883
/*46  */     }                                                                            // (27) 0.007812
/*48  */     curbits += 20;                                                               // (24) 0.01562
/*50  */     url_fseek(s->pb, pos, SEEK_SET);                                             // (9) 0.03711
/*54  */     size = ((size2 + curbits + 31) & ~31) >> 3;                                  // (7) 0.04102
/*56  */     if(cur == c->frames_noted){                                                  // (17) 0.02734
/*58  */         c->frames[cur].pos = pos;                                                // (11) 0.0332
/*60  */         c->frames[cur].size = size;                                              // (12) 0.0332
/*62  */         c->frames[cur].skip = curbits - 20;                                      // (8) 0.03906
/*64  */         av_add_index_entry(s->streams[0], cur, cur, size, 0, AVINDEX_KEYFRAME);  // 0.0
/*66  */         c->frames_noted++;                                                       // 0.0
/*68  */     }                                                                            // 0.0
/*70  */     c->curbits = (curbits + size2) & 0x1F;                                       // 0.0
/*74  */     if (av_new_packet(pkt, size) < 0)                                            // 0.0
/*76  */         return AVERROR(EIO);                                                     // 0.0
/*80  */     pkt->data[0] = curbits;                                                      // 0.0
/*82  */     pkt->data[1] = (c->curframe > c->fcount);                                    // 0.0
/*88  */     pkt->stream_index = 0;                                                       // 0.0
/*90  */     pkt->pts = cur;                                                              // 0.0
/*92  */     ret = get_buffer(s->pb, pkt->data + 4, size);                                // 0.0
/*94  */     if(c->curbits)                                                               // 0.0
/*96  */         url_fseek(s->pb, -4, SEEK_CUR);                                          // 0.0
/*98  */     if(ret < size){                                                              // 0.0
/*100 */         av_free_packet(pkt);                                                     // 0.0
/*102 */         return AVERROR(EIO);                                                     // 0.0
/*104 */     }                                                                            // 0.0
/*106 */     pkt->size = ret + 4;                                                         // 0.0
/*110 */     return 0;                                                                    // 0.0
/*112 */ }                                                                                // 0.0
