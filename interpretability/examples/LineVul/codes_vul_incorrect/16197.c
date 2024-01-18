// commit message FFmpeg@80b1e1c03d (target=1, prob=0.48602688, correct=False): avcodec/exr: fix null pointer dereference
/*0   */ static int huf_uncompress(GetByteContext *gb,                    // (15) 0.0293
/*2   */                           uint16_t *dst, int dst_size)           // (0) 0.07422
/*4   */ {                                                                // (29) 0.001953
/*6   */     int32_t src_size, im, iM;                                    // (14) 0.03125
/*8   */     uint32_t nBits;                                              // (21) 0.02148
/*10  */     uint64_t *freq;                                              // (20) 0.02148
/*12  */     HufDec *hdec;                                                // (22) 0.01953
/*14  */     int ret, i;                                                  // (26) 0.01563
/*18  */     src_size = bytestream2_get_le32(gb);                         // (6) 0.03711
/*20  */     im = bytestream2_get_le32(gb);                               // (12) 0.0332
/*22  */     iM = bytestream2_get_le32(gb);                               // (10) 0.03516
/*24  */     bytestream2_skip(gb, 4);                                     // (17) 0.02734
/*26  */     nBits = bytestream2_get_le32(gb);                            // (7) 0.03711
/*28  */     if (im < 0 || im >= HUF_ENCSIZE ||                           // (9) 0.03516
/*30  */         iM < 0 || iM >= HUF_ENCSIZE ||                           // (5) 0.04297
/*32  */         src_size < 0)                                            // (19) 0.02539
/*34  */         return AVERROR_INVALIDDATA;                              // (11) 0.0332
/*38  */     bytestream2_skip(gb, 4);                                     // (16) 0.02734
/*42  */     freq = av_calloc(HUF_ENCSIZE, sizeof(*freq));                // (3) 0.04492
/*44  */     hdec = av_calloc(HUF_DECSIZE, sizeof(*hdec));                // (4) 0.04297
/*46  */     if (!freq || !hdec) {                                        // (18) 0.02539
/*48  */         ret = AVERROR(ENOMEM);                                   // (13) 0.0332
/*50  */         goto fail;                                               // (25) 0.01953
/*52  */     }                                                            // (27) 0.007812
/*56  */     if ((ret = huf_unpack_enc_table(gb, im, iM, freq)) < 0)      // (1) 0.05859
/*58  */         goto fail;                                               // (23) 0.01953
/*62  */     if (nBits > 8 * bytestream2_get_bytes_left(gb)) {            // (2) 0.04883
/*64  */         ret = AVERROR_INVALIDDATA;                               // (8) 0.03516
/*66  */         goto fail;                                               // (24) 0.01953
/*68  */     }                                                            // (28) 0.007812
/*72  */     if ((ret = huf_build_dec_table(freq, im, iM, hdec)) < 0)     // 0.0
/*74  */         goto fail;                                               // 0.0
/*76  */     ret = huf_decode(freq, hdec, gb, nBits, iM, dst_size, dst);  // 0.0
/*80  */ fail:                                                            // 0.0
/*82  */     for (i = 0; i < HUF_DECSIZE; i++) {                          // 0.0
/*84  */         if (hdec[i].p)                                           // 0.0
/*86  */             av_freep(&hdec[i].p);                                // 0.0
/*88  */     }                                                            // 0.0
/*92  */     av_free(freq);                                               // 0.0
/*94  */     av_free(hdec);                                               // 0.0
/*98  */     return ret;                                                  // 0.0
/*100 */ }                                                                // 0.0
