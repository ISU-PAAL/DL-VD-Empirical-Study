// commit message FFmpeg@d1a58afb95 (target=1, prob=0.30162826, correct=False): latmenc: validate extradata size.
/*0   */ static int latm_write_packet(AVFormatContext *s, AVPacket *pkt)                                            // (5) 0.04492
/*2   */ {                                                                                                          // (26) 0.001953
/*4   */     AVIOContext *pb = s->pb;                                                                               // (16) 0.02539
/*6   */     PutBitContext bs;                                                                                      // (22) 0.01758
/*8   */     int i, len;                                                                                            // (23) 0.01562
/*10  */     uint8_t loas_header[] = "\x56\xe0\x00";                                                                // (4) 0.04492
/*12  */     uint8_t *buf = NULL;                                                                                   // (18) 0.02344
/*16  */     if (s->streams[0]->codec->codec_id == CODEC_ID_AAC_LATM)                                               // (2) 0.06641
/*18  */         return ff_raw_write_packet(s, pkt);                                                                // (7) 0.04297
/*22  */     if (pkt->size > 2 && pkt->data[0] == 0xff && (pkt->data[1] >> 4) == 0xf) {                             // (1) 0.07617
/*24  */         av_log(s, AV_LOG_ERROR, "ADTS header detected - ADTS will not be incorrectly muxed into LATM\n");  // (0) 0.07812
/*26  */         return AVERROR_INVALIDDATA;                                                                        // (13) 0.0332
/*28  */     }                                                                                                      // (25) 0.007812
/*30  */     if (pkt->size > 0x1fff)                                                                                // (15) 0.0293
/*32  */         goto too_large;                                                                                    // (19) 0.02344
/*36  */     buf = av_malloc(pkt->size+1024);                                                                       // (11) 0.0332
/*38  */     if (!buf)                                                                                              // (24) 0.01367
/*40  */         return AVERROR(ENOMEM);                                                                            // (14) 0.03125
/*44  */     init_put_bits(&bs, buf, pkt->size+1024);                                                               // (8) 0.03906
/*48  */     latm_write_frame_header(s, &bs);                                                                       // (10) 0.0332
/*52  */     /* PayloadLengthInfo() */                                                                              // (21) 0.01953
/*54  */     for (i = 0; i <= pkt->size-255; i+=255)                                                                // (6) 0.04297
/*56  */         put_bits(&bs, 8, 255);                                                                             // (12) 0.0332
/*60  */     put_bits(&bs, 8, pkt->size-i);                                                                         // (9) 0.03516
/*64  */     /* The LATM payload is written unaligned */                                                            // (17) 0.02539
/*68  */     /* PayloadMux() */                                                                                     // (20) 0.01953
/*70  */     if (pkt->size && (pkt->data[0] & 0xe1) == 0x81) {                                                      // (3) 0.05664
/*72  */         // Convert byte-aligned DSE to non-aligned.                                                        // 0.0
/*74  */         // Due to the input format encoding we know that                                                   // 0.0
/*76  */         // it is naturally byte-aligned in the input stream,                                               // 0.0
/*78  */         // so there are no padding bits to account for.                                                    // 0.0
/*80  */         // To avoid having to add padding bits and rearrange                                               // 0.0
/*82  */         // the whole stream we just remove the byte-align flag.                                            // 0.0
/*84  */         // This allows us to remux our FATE AAC samples into latm                                          // 0.0
/*86  */         // files that are still playable with minimal effort.                                              // 0.0
/*88  */         put_bits(&bs, 8, pkt->data[0] & 0xfe);                                                             // 0.0
/*90  */         avpriv_copy_bits(&bs, pkt->data + 1, 8*pkt->size - 8);                                             // 0.0
/*92  */     } else                                                                                                 // 0.0
/*94  */         avpriv_copy_bits(&bs, pkt->data, 8*pkt->size);                                                     // 0.0
/*98  */     avpriv_align_put_bits(&bs);                                                                            // 0.0
/*100 */     flush_put_bits(&bs);                                                                                   // 0.0
/*104 */     len = put_bits_count(&bs) >> 3;                                                                        // 0.0
/*108 */     if (len > 0x1fff)                                                                                      // 0.0
/*110 */         goto too_large;                                                                                    // 0.0
/*114 */     loas_header[1] |= (len >> 8) & 0x1f;                                                                   // 0.0
/*116 */     loas_header[2] |= len & 0xff;                                                                          // 0.0
/*120 */     avio_write(pb, loas_header, 3);                                                                        // 0.0
/*122 */     avio_write(pb, buf, len);                                                                              // 0.0
/*126 */     av_free(buf);                                                                                          // 0.0
/*130 */     return 0;                                                                                              // 0.0
/*134 */ too_large:                                                                                                 // 0.0
/*136 */     av_log(s, AV_LOG_ERROR, "LATM packet size larger than maximum size 0x1fff\n");                         // 0.0
/*138 */     av_free(buf);                                                                                          // 0.0
/*140 */     return AVERROR_INVALIDDATA;                                                                            // 0.0
/*142 */ }                                                                                                          // 0.0
