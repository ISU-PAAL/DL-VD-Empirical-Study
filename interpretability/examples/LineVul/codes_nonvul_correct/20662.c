// commit message FFmpeg@3c895fc098 (target=0, prob=0.33817306, correct=True): correctly interleave packets during encoding dts/pts fixed for streamcopy dont use coded_frame->key_frame hack in muxers, use AVPacket.flags instead
/*0  */ static void put_payload_header(                                             // (7) 0.0048
/*2  */                                 AVFormatContext *s,                         // (4) 0.006304
/*4  */                                 ASFStream       *stream,                    // (8) 0.004396
/*6  */                                 int             presentation_time,          // (12) 0.002381
/*8  */                                 int             m_obj_size,                 // (18) 0.0005807
/*10 */                                 int             m_obj_offset,               // (17) 0.0006732
/*12 */                                 int             payload_len                 // (10) 0.003072
/*14 */             )                                                               // (19) 0.0003612
/*16 */ {                                                                           // (16) 0.0006995
/*18 */     ASFContext *asf = s->priv_data;                                         // (5) 0.00524
/*20 */     ByteIOContext *pb = &asf->pb;                                           // (13) 0.002128
/*22 */     int val;                                                                // (15) 0.0007816
/*24 */                                                                             // (21) 0.0001091
/*26 */     val = stream->num;                                                      // (14) 0.001814
/*28 */     if (s->streams[val - 1]->codec.coded_frame->key_frame)                  // (3) 0.01016
/*30 */         val |= ASF_PL_FLAG_KEY_FRAME;                                       // (9) 0.003995
/*32 */     put_byte(pb, val);                                                      // (6) 0.004973
/*34 */                                                                             // (20) 0.0002502
/*36 */     put_byte(pb, stream->seq);  //Media object number                       // (2) 0.03158
/*38 */     put_le32(pb, m_obj_offset); //Offset Into Media Object                  // (1) 0.03859
/*40 */                                                                             // (11) 0.00267
/*42 */     // Replicated Data shall be at least 8 bytes long.                      // (0) 0.1944
/*44 */     // The first 4 bytes of data shall contain the                          // 0.0
/*46 */     // Size of the Media Object that the payload belongs to.                // 0.0
/*48 */     // The next 4 bytes of data shall contain the                           // 0.0
/*50 */     // Presentation Time for the media object that the payload belongs to.  // 0.0
/*52 */     put_byte(pb, ASF_PAYLOAD_REPLICATED_DATA_LENGTH);                       // 0.0
/*56 */     put_le32(pb, m_obj_size);       //Replicated Data - Media Object Size   // 0.0
/*58 */     put_le32(pb, presentation_time);//Replicated Data - Presentation Time   // 0.0
/*60 */                                                                             // 0.0
/*62 */     if (asf->multi_payloads_present){                                       // 0.0
/*64 */         put_le16(pb, payload_len);   //payload length                       // 0.0
/*66 */     }                                                                       // 0.0
/*68 */ }                                                                           // 0.0
