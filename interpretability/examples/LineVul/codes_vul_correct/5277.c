// commit message FFmpeg@77d2ef13a8 (target=1, prob=0.7695935, correct=True): Fix memory (re)allocation in matroskadec.c, related to MSVR-11-0080.
/*0   */ static int matroska_decode_buffer(uint8_t** buf, int* buf_size,               // (4) 0.04688
/*2   */                                   MatroskaTrack *track)                       // (1) 0.07813
/*4   */ {                                                                             // (25) 0.001953
/*6   */     MatroskaTrackEncoding *encodings = track->encodings.elem;                 // (6) 0.04492
/*8   */     uint8_t* data = *buf;                                                     // (15) 0.02539
/*10  */     int isize = *buf_size;                                                    // (16) 0.02344
/*12  */     uint8_t* pkt_data = NULL;                                                 // (12) 0.0293
/*14  */     int pkt_size = isize;                                                     // (17) 0.02344
/*16  */     int result = 0;                                                           // (22) 0.01562
/*18  */     int olen;                                                                 // (23) 0.01367
/*22  */     if (pkt_size >= 10000000)                                                 // (14) 0.02539
/*24  */         return -1;                                                            // (18) 0.02148
/*28  */     switch (encodings[0].compression.algo) {                                  // (10) 0.03516
/*30  */     case MATROSKA_TRACK_ENCODING_COMP_HEADERSTRIP:                            // (5) 0.04687
/*32  */         return encodings[0].compression.settings.size;                        // (9) 0.04102
/*34  */     case MATROSKA_TRACK_ENCODING_COMP_LZO:                                    // (7) 0.04492
/*36  */         do {                                                                  // (21) 0.01758
/*38  */             olen = pkt_size *= 3;                                             // (8) 0.04297
/*40  */             pkt_data = av_realloc(pkt_data, pkt_size+AV_LZO_OUTPUT_PADDING);  // (0) 0.08789
/*42  */             result = av_lzo1x_decode(pkt_data, &olen, data, &isize);          // (2) 0.07227
/*44  */         } while (result==AV_LZO_OUTPUT_FULL && pkt_size<10000000);            // (3) 0.06445
/*46  */         if (result)                                                           // (19) 0.02148
/*48  */             goto failed;                                                      // (13) 0.02734
/*50  */         pkt_size -= olen;                                                     // (11) 0.0293
/*52  */         break;                                                                // (20) 0.01758
/*54  */ #if CONFIG_ZLIB                                                               // (24) 0.01172
/*56  */     case MATROSKA_TRACK_ENCODING_COMP_ZLIB: {                                 // 0.0
/*58  */         z_stream zstream = {0};                                               // 0.0
/*60  */         if (inflateInit(&zstream) != Z_OK)                                    // 0.0
/*62  */             return -1;                                                        // 0.0
/*64  */         zstream.next_in = data;                                               // 0.0
/*66  */         zstream.avail_in = isize;                                             // 0.0
/*68  */         do {                                                                  // 0.0
/*70  */             pkt_size *= 3;                                                    // 0.0
/*72  */             pkt_data = av_realloc(pkt_data, pkt_size);                        // 0.0
/*74  */             zstream.avail_out = pkt_size - zstream.total_out;                 // 0.0
/*76  */             zstream.next_out = pkt_data + zstream.total_out;                  // 0.0
/*78  */             result = inflate(&zstream, Z_NO_FLUSH);                           // 0.0
/*80  */         } while (result==Z_OK && pkt_size<10000000);                          // 0.0
/*82  */         pkt_size = zstream.total_out;                                         // 0.0
/*84  */         inflateEnd(&zstream);                                                 // 0.0
/*86  */         if (result != Z_STREAM_END)                                           // 0.0
/*88  */             goto failed;                                                      // 0.0
/*90  */         break;                                                                // 0.0
/*92  */     }                                                                         // 0.0
/*94  */ #endif                                                                        // 0.0
/*96  */ #if CONFIG_BZLIB                                                              // 0.0
/*98  */     case MATROSKA_TRACK_ENCODING_COMP_BZLIB: {                                // 0.0
/*100 */         bz_stream bzstream = {0};                                             // 0.0
/*102 */         if (BZ2_bzDecompressInit(&bzstream, 0, 0) != BZ_OK)                   // 0.0
/*104 */             return -1;                                                        // 0.0
/*106 */         bzstream.next_in = data;                                              // 0.0
/*108 */         bzstream.avail_in = isize;                                            // 0.0
/*110 */         do {                                                                  // 0.0
/*112 */             pkt_size *= 3;                                                    // 0.0
/*114 */             pkt_data = av_realloc(pkt_data, pkt_size);                        // 0.0
/*116 */             bzstream.avail_out = pkt_size - bzstream.total_out_lo32;          // 0.0
/*118 */             bzstream.next_out = pkt_data + bzstream.total_out_lo32;           // 0.0
/*120 */             result = BZ2_bzDecompress(&bzstream);                             // 0.0
/*122 */         } while (result==BZ_OK && pkt_size<10000000);                         // 0.0
/*124 */         pkt_size = bzstream.total_out_lo32;                                   // 0.0
/*126 */         BZ2_bzDecompressEnd(&bzstream);                                       // 0.0
/*128 */         if (result != BZ_STREAM_END)                                          // 0.0
/*130 */             goto failed;                                                      // 0.0
/*132 */         break;                                                                // 0.0
/*134 */     }                                                                         // 0.0
/*136 */ #endif                                                                        // 0.0
/*138 */     default:                                                                  // 0.0
/*140 */         return -1;                                                            // 0.0
/*142 */     }                                                                         // 0.0
/*146 */     *buf = pkt_data;                                                          // 0.0
/*148 */     *buf_size = pkt_size;                                                     // 0.0
/*150 */     return 0;                                                                 // 0.0
/*152 */  failed:                                                                      // 0.0
/*154 */     av_free(pkt_data);                                                        // 0.0
/*156 */     return -1;                                                                // 0.0
/*158 */ }                                                                             // 0.0
