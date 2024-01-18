// commit message FFmpeg@0ecca7a49f (target=1, prob=0.99913955, correct=True): various security fixes and precautionary checks
/*0  */ static unsigned long iv_decode_frame(Indeo3DecodeContext *s,                 // (6) 0.04102
/*1  */                                      unsigned char *buf, int buf_size)       // (0) 0.0918
/*2  */ {                                                                            // (30) 0.001953
/*3  */   unsigned int hdr_width, hdr_height,                                        // (16) 0.02539
/*4  */     chroma_width, chroma_height;                                             // (17) 0.02539
/*5  */   unsigned long fflags1, fflags2, fflags3, offs1, offs2, offs3, offs;        // (1) 0.05859
/*6  */   unsigned char *hdr_pos, *buf_pos;                                          // (14) 0.02734
/*7  */   buf_pos = buf;                                                             // (21) 0.01367
/*8  */   buf_pos += 18;                                                             // (23) 0.01367
/*9  */   fflags1 = le2me_16(*(uint16_t *)buf_pos);                                  // (11) 0.04102
/*10 */   buf_pos += 2;                                                              // (27) 0.01367
/*11 */   fflags3 = le2me_32(*(uint32_t *)buf_pos);                                  // (10) 0.04102
/*12 */   buf_pos += 4;                                                              // (20) 0.01367
/*13 */   fflags2 = *buf_pos++;                                                      // (19) 0.01953
/*14 */   buf_pos += 3;                                                              // (25) 0.01367
/*15 */   hdr_height = le2me_16(*(uint16_t *)buf_pos);                               // (4) 0.04297
/*16 */   buf_pos += 2;                                                              // (28) 0.01367
/*17 */   hdr_width = le2me_16(*(uint16_t *)buf_pos);                                // (5) 0.04297
/*18 */   buf_pos += 2;                                                              // (29) 0.01367
/*19 */   chroma_height = ((hdr_height >> 2) + 3) & 0x7ffc;                          // (2) 0.04687
/*20 */   chroma_width = ((hdr_width >> 2) + 3) & 0x7ffc;                            // (3) 0.04687
/*21 */   offs1 = le2me_32(*(uint32_t *)buf_pos);                                    // (8) 0.04102
/*22 */   buf_pos += 4;                                                              // (26) 0.01367
/*23 */   offs2 = le2me_32(*(uint32_t *)buf_pos);                                    // (9) 0.04102
/*24 */   buf_pos += 4;                                                              // (24) 0.01367
/*25 */   offs3 = le2me_32(*(uint32_t *)buf_pos);                                    // (7) 0.04102
/*26 */   buf_pos += 8;                                                              // (22) 0.01367
/*27 */   hdr_pos = buf_pos;                                                         // (18) 0.01953
/*28 */   if(fflags3 == 0x80) return 4;                                              // (13) 0.0293
/*29 */   if(fflags1 & 0x200) {                                                      // (15) 0.02539
/*30 */     s->cur_frame = s->iv_frame + 1;                                          // (12) 0.0332
/*31 */     s->ref_frame = s->iv_frame;                                              // 0.0
/*32 */   } else {                                                                   // 0.0
/*33 */     s->cur_frame = s->iv_frame;                                              // 0.0
/*34 */     s->ref_frame = s->iv_frame + 1;                                          // 0.0
/*35 */   }                                                                          // 0.0
/*36 */   buf_pos = buf + 16 + offs1;                                                // 0.0
/*37 */   offs = le2me_32(*(uint32_t *)buf_pos);                                     // 0.0
/*38 */   buf_pos += 4;                                                              // 0.0
/*39 */   iv_Decode_Chunk(s, s->cur_frame->Ybuf, s->ref_frame->Ybuf, hdr_width,      // 0.0
/*40 */     hdr_height, buf_pos + offs * 2, fflags2, hdr_pos, buf_pos,               // 0.0
/*41 */     min(hdr_width, 160));                                                    // 0.0
/*42 */   if (!(s->avctx->flags & CODEC_FLAG_GRAY))                                  // 0.0
/*43 */   {                                                                          // 0.0
/*44 */   buf_pos = buf + 16 + offs2;                                                // 0.0
/*45 */   offs = le2me_32(*(uint32_t *)buf_pos);                                     // 0.0
/*46 */   buf_pos += 4;                                                              // 0.0
/*47 */   iv_Decode_Chunk(s, s->cur_frame->Vbuf, s->ref_frame->Vbuf, chroma_width,   // 0.0
/*48 */     chroma_height, buf_pos + offs * 2, fflags2, hdr_pos, buf_pos,            // 0.0
/*49 */     min(chroma_width, 40));                                                  // 0.0
/*50 */   buf_pos = buf + 16 + offs3;                                                // 0.0
/*51 */   offs = le2me_32(*(uint32_t *)buf_pos);                                     // 0.0
/*52 */   buf_pos += 4;                                                              // 0.0
/*53 */   iv_Decode_Chunk(s, s->cur_frame->Ubuf, s->ref_frame->Ubuf, chroma_width,   // 0.0
/*54 */     chroma_height, buf_pos + offs * 2, fflags2, hdr_pos, buf_pos,            // 0.0
/*55 */     min(chroma_width, 40));                                                  // 0.0
/*56 */   }                                                                          // 0.0
/*57 */   return 8;                                                                  // 0.0
/*58 */ }                                                                            // 0.0
