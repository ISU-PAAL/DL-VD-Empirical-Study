// commit message FFmpeg@4f90688b6e (target=1, prob=0.999124, correct=True): matroskadec: fix integer overflow patch from reimar
/*0  */ static int matroska_decode_buffer(uint8_t** buf, int* buf_size,               // (4) 0.04692
/*1  */                                   MatroskaTrack *track)                       // (1) 0.07814
/*2  */ {                                                                             // (25) 0.001953
/*3  */     MatroskaTrackEncoding *encodings = track->encodings.elem;                 // (6) 0.04494
/*4  */     uint8_t* data = *buf;                                                     // (16) 0.02539
/*5  */     int isize = *buf_size;                                                    // (17) 0.02343
/*6  */     uint8_t* pkt_data = NULL;                                                 // (14) 0.02929
/*7  */     int pkt_size = isize;                                                     // (18) 0.02343
/*8  */     int result = 0;                                                           // (22) 0.01562
/*9  */     int olen;                                                                 // (23) 0.01367
/*10 */     switch (encodings[0].compression.algo) {                                  // (11) 0.03515
/*11 */     case MATROSKA_TRACK_ENCODING_COMP_HEADERSTRIP:                            // (5) 0.04687
/*12 */         return encodings[0].compression.settings.size;                        // (10) 0.04101
/*13 */     case MATROSKA_TRACK_ENCODING_COMP_LZO:                                    // (8) 0.04491
/*14 */         do {                                                                  // (21) 0.01758
/*15 */             olen = pkt_size *= 3;                                             // (9) 0.04296
/*16 */             pkt_data = av_realloc(pkt_data, pkt_size+AV_LZO_OUTPUT_PADDING);  // (0) 0.08787
/*17 */             result = av_lzo1x_decode(pkt_data, &olen, data, &isize);          // (2) 0.07226
/*18 */         } while (result==AV_LZO_OUTPUT_FULL && pkt_size<10000000);            // (3) 0.06444
/*19 */         if (result)                                                           // (19) 0.02148
/*20 */             goto failed;                                                      // (15) 0.02737
/*21 */         pkt_size -= olen;                                                     // (13) 0.02929
/*22 */         break;                                                                // (20) 0.01758
/*23 */ #if CONFIG_ZLIB                                                               // (24) 0.01172
/*24 */     case MATROSKA_TRACK_ENCODING_COMP_ZLIB: {                                 // (7) 0.04492
/*25 */         z_stream zstream = {0};                                               // (12) 0.03125
/*26 */         if (inflateInit(&zstream) != Z_OK)                                    // 0.0
/*27 */         zstream.next_in = data;                                               // 0.0
/*28 */         zstream.avail_in = isize;                                             // 0.0
/*29 */         do {                                                                  // 0.0
/*30 */             pkt_size *= 3;                                                    // 0.0
/*31 */             pkt_data = av_realloc(pkt_data, pkt_size);                        // 0.0
/*32 */             zstream.avail_out = pkt_size - zstream.total_out;                 // 0.0
/*33 */             zstream.next_out = pkt_data + zstream.total_out;                  // 0.0
/*34 */             result = inflate(&zstream, Z_NO_FLUSH);                           // 0.0
/*35 */         } while (result==Z_OK && pkt_size<10000000);                          // 0.0
/*36 */         pkt_size = zstream.total_out;                                         // 0.0
/*37 */         inflateEnd(&zstream);                                                 // 0.0
/*38 */         if (result != Z_STREAM_END)                                           // 0.0
/*39 */             goto failed;                                                      // 0.0
/*40 */         break;                                                                // 0.0
/*41 */     }                                                                         // 0.0
/*42 */ #endif                                                                        // 0.0
/*43 */ #if CONFIG_BZLIB                                                              // 0.0
/*44 */     case MATROSKA_TRACK_ENCODING_COMP_BZLIB: {                                // 0.0
/*45 */         bz_stream bzstream = {0};                                             // 0.0
/*46 */         if (BZ2_bzDecompressInit(&bzstream, 0, 0) != BZ_OK)                   // 0.0
/*47 */         bzstream.next_in = data;                                              // 0.0
/*48 */         bzstream.avail_in = isize;                                            // 0.0
/*49 */         do {                                                                  // 0.0
/*50 */             pkt_size *= 3;                                                    // 0.0
/*51 */             pkt_data = av_realloc(pkt_data, pkt_size);                        // 0.0
/*52 */             bzstream.avail_out = pkt_size - bzstream.total_out_lo32;          // 0.0
/*53 */             bzstream.next_out = pkt_data + bzstream.total_out_lo32;           // 0.0
/*54 */             result = BZ2_bzDecompress(&bzstream);                             // 0.0
/*55 */         } while (result==BZ_OK && pkt_size<10000000);                         // 0.0
/*56 */         pkt_size = bzstream.total_out_lo32;                                   // 0.0
/*57 */         BZ2_bzDecompressEnd(&bzstream);                                       // 0.0
/*58 */         if (result != BZ_STREAM_END)                                          // 0.0
/*59 */             goto failed;                                                      // 0.0
/*60 */         break;                                                                // 0.0
/*61 */     }                                                                         // 0.0
/*62 */ #endif                                                                        // 0.0
/*63 */     default:                                                                  // 0.0
/*64 */     }                                                                         // 0.0
/*65 */     *buf = pkt_data;                                                          // 0.0
/*66 */     *buf_size = pkt_size;                                                     // 0.0
/*67 */     return 0;                                                                 // 0.0
/*68 */  failed:                                                                      // 0.0
/*69 */     av_free(pkt_data);                                                        // 0.0
/*70 */ }                                                                             // 0.0
