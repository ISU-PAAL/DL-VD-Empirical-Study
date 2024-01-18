// commit message FFmpeg@465e1dadbe (target=0, prob=0.15139666, correct=True): 10l (bytes_left() -> url_feof()) 10l (updating LRU delta pts for type 1/2 frames) ensure that checksumming isnt enabled if its not needed search for next startcode and then search backward to the next valid frame if an inconsistancy is detected deal with non-frame startcodes in the middle of the stream
/*0  */ static int get_packetheader(NUTContext *nut, ByteIOContext *bc, int prefix_length, int calculate_checksum)                         // (2) 0.08378
/*2  */ {                                                                                                                                  // (20) 0.002703
/*4  */     int64_t start, size, last_size;                                                                                                // (8) 0.04054
/*6  */     start= url_ftell(bc) - prefix_length;                                                                                          // (7) 0.04595
/*10 */     if(start != nut->packet_start + nut->written_packet_size){                                                                     // (3) 0.06216
/*12 */         av_log(nut->avf, AV_LOG_ERROR, "get_packetheader called at weird position\n");                                             // (1) 0.09459
/*14 */         return -1;                                                                                                                 // (13) 0.02973
/*16 */     }                                                                                                                              // (17) 0.01081
/*18 */                                                                                                                                    // (18) 0.01081
/*20 */     if(calculate_checksum)                                                                                                         // (11) 0.03243
/*22 */         init_checksum(bc, update_adler32, 0);                                                                                      // (4) 0.05946
/*26 */     size= get_v(bc);                                                                                                               // (14) 0.02973
/*28 */     last_size= get_v(bc);                                                                                                          // (10) 0.03514
/*30 */     if(nut->written_packet_size != last_size){                                                                                     // (6) 0.04865
/*32 */         av_log(nut->avf, AV_LOG_ERROR, "packet size missmatch %d != %lld at %lld\n", nut->written_packet_size, last_size, start);  // (0) 0.1514
/*34 */         return -1;                                                                                                                 // (15) 0.02973
/*36 */     }                                                                                                                              // (19) 0.01081
/*40 */     nut->last_packet_start = nut->packet_start;                                                                                    // (5) 0.05135
/*42 */     nut->packet_start = start;                                                                                                     // (12) 0.03243
/*44 */     nut->written_packet_size= size;                                                                                                // (9) 0.03784
/*48 */     return size;                                                                                                                   // (16) 0.01622
/*50 */ }                                                                                                                                  // (21) 0.002703
