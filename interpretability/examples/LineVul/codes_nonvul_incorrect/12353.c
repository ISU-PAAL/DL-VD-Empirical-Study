// commit message FFmpeg@59c6178a54 (target=0, prob=0.5136473, correct=False): Use a shared function to validate FLAC extradata.
/*0  */ static int ogg_build_flac_headers(const uint8_t *extradata, int extradata_size,  // (1) 0.05469
/*2  */                                   OGGStreamContext *oggstream, int bitexact)     // (0) 0.08984
/*4  */ {                                                                                // (23) 0.001953
/*6  */     const char *vendor = bitexact ? "ffmpeg" : LIBAVFORMAT_IDENT;                // (7) 0.05078
/*8  */     uint8_t *p;                                                                  // (22) 0.01953
/*10 */     if (extradata_size != 34)                                                    // (18) 0.02539
/*12 */         return -1;                                                               // (21) 0.02148
/*14 */     oggstream->header_len[0] = 51;                                               // (16) 0.03125
/*16 */     oggstream->header[0] = av_mallocz(51); // per ogg flac specs                 // (3) 0.05273
/*18 */     p = oggstream->header[0];                                                    // (19) 0.02539
/*20 */     bytestream_put_byte(&p, 0x7F);                                               // (15) 0.03516
/*22 */     bytestream_put_buffer(&p, "FLAC", 4);                                        // (11) 0.03711
/*24 */     bytestream_put_byte(&p, 1); // major version                                 // (14) 0.03516
/*26 */     bytestream_put_byte(&p, 0); // minor version                                 // (12) 0.03516
/*28 */     bytestream_put_be16(&p, 1); // headers packets without this one              // (8) 0.04297
/*30 */     bytestream_put_buffer(&p, "fLaC", 4);                                        // (10) 0.03906
/*32 */     bytestream_put_byte(&p, 0x00); // streaminfo                                 // (9) 0.03906
/*34 */     bytestream_put_be24(&p, 34);                                                 // (17) 0.03125
/*36 */     bytestream_put_buffer(&p, extradata, 34);                                    // (13) 0.03516
/*38 */     oggstream->header_len[1] = 1+3+4+strlen(vendor)+4;                           // (2) 0.05469
/*40 */     oggstream->header[1] = av_mallocz(oggstream->header_len[1]);                 // (5) 0.05273
/*42 */     p = oggstream->header[1];                                                    // (20) 0.02539
/*44 */     bytestream_put_byte(&p, 0x84); // last metadata block and vorbis comment     // (6) 0.05078
/*46 */     bytestream_put_be24(&p, oggstream->header_len[1] - 4);                       // (4) 0.05273
/*48 */     bytestream_put_le32(&p, strlen(vendor));                                     // 0.0
/*50 */     bytestream_put_buffer(&p, vendor, strlen(vendor));                           // 0.0
/*52 */     bytestream_put_le32(&p, 0); // user comment list length                      // 0.0
/*54 */     return 0;                                                                    // 0.0
/*56 */ }                                                                                // 0.0
