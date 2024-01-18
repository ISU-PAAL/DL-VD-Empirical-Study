// commit message FFmpeg@9f36ea57ae (target=1, prob=0.87877035, correct=True): avcodec/avpacket: Fix off by 5 error
/*0  */ int av_packet_split_side_data(AVPacket *pkt){                                                              // (11) 0.03711
/*2  */     if (!pkt->side_data_elems && pkt->size >12 && AV_RB64(pkt->data + pkt->size - 8) == FF_MERGE_MARKER){  // (0) 0.0957
/*4  */         int i;                                                                                             // (20) 0.01953
/*6  */         unsigned int size;                                                                                 // (19) 0.02148
/*8  */         uint8_t *p;                                                                                        // (18) 0.02734
/*12 */         p = pkt->data + pkt->size - 8 - 5;                                                                 // (5) 0.04492
/*14 */         for (i=1; ; i++){                                                                                  // (14) 0.0332
/*16 */             size = AV_RB32(p);                                                                             // (8) 0.03906
/*18 */             if (size>INT_MAX || p - pkt->data < size)                                                      // (4) 0.05469
/*20 */                 return 0;                                                                                  // (13) 0.03516
/*22 */             if (p[4]&128)                                                                                  // (10) 0.03906
/*24 */                 break;                                                                                     // (16) 0.0332
/*26 */             p-= size+5;                                                                                    // (12) 0.03516
/*28 */         }                                                                                                  // (21) 0.01562
/*32 */         pkt->side_data = av_malloc_array(i, sizeof(*pkt->side_data));                                      // (2) 0.0625
/*34 */         if (!pkt->side_data)                                                                               // (17) 0.03125
/*36 */             return AVERROR(ENOMEM);                                                                        // (7) 0.03906
/*40 */         p= pkt->data + pkt->size - 8 - 5;                                                                  // (6) 0.04492
/*42 */         for (i=0; ; i++){                                                                                  // (15) 0.0332
/*44 */             size= AV_RB32(p);                                                                              // (9) 0.03906
/*46 */             av_assert0(size<=INT_MAX && p - pkt->data >= size);                                            // (3) 0.0625
/*48 */             pkt->side_data[i].data = av_mallocz(size + AV_INPUT_BUFFER_PADDING_SIZE);                      // (1) 0.08594
/*50 */             pkt->side_data[i].size = size;                                                                 // 0.0
/*52 */             pkt->side_data[i].type = p[4]&127;                                                             // 0.0
/*54 */             if (!pkt->side_data[i].data)                                                                   // 0.0
/*56 */                 return AVERROR(ENOMEM);                                                                    // 0.0
/*58 */             memcpy(pkt->side_data[i].data, p-size, size);                                                  // 0.0
/*60 */             pkt->size -= size + 5;                                                                         // 0.0
/*62 */             if(p[4]&128)                                                                                   // 0.0
/*64 */                 break;                                                                                     // 0.0
/*66 */             p-= size+5;                                                                                    // 0.0
/*68 */         }                                                                                                  // 0.0
/*70 */         pkt->size -= 8;                                                                                    // 0.0
/*72 */         pkt->side_data_elems = i+1;                                                                        // 0.0
/*74 */         return 1;                                                                                          // 0.0
/*76 */     }                                                                                                      // 0.0
/*78 */     return 0;                                                                                              // 0.0
/*80 */ }                                                                                                          // 0.0
