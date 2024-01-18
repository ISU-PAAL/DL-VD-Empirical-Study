// commit message FFmpeg@4b1f5e5090 (target=0, prob=0.56904095, correct=False): cosmetics: Write NULL pointer inequality checks more compactly
/*0   */ static void qdm2_decode_super_block(QDM2Context *q)                                      // (12) 0.03906
/*2   */ {                                                                                        // (22) 0.001954
/*4   */     GetBitContext gb;                                                                    // (19) 0.01758
/*6   */     QDM2SubPacket header, *packet;                                                       // (14) 0.0293
/*8   */     int i, packet_bytes, sub_packet_size, sub_packets_D;                                 // (8) 0.04687
/*10  */     unsigned int next_index = 0;                                                         // (18) 0.02149
/*14  */     memset(q->tone_level_idx_hi1, 0, sizeof(q->tone_level_idx_hi1));                     // (1) 0.06641
/*16  */     memset(q->tone_level_idx_mid, 0, sizeof(q->tone_level_idx_mid));                     // (4) 0.0625
/*18  */     memset(q->tone_level_idx_hi2, 0, sizeof(q->tone_level_idx_hi2));                     // (2) 0.06641
/*22  */     q->sub_packets_B = 0;                                                                // (17) 0.02734
/*24  */     sub_packets_D    = 0;                                                                // (15) 0.0293
/*28  */     average_quantized_coeffs(q); // average elements in quantized_coeffs[max_ch][10][8]  // (3) 0.06445
/*32  */     init_get_bits(&gb, q->compressed_data, q->compressed_size * 8);                      // (6) 0.05273
/*34  */     qdm2_decode_sub_packet_header(&gb, &header);                                         // (10) 0.04297
/*38  */     if (header.type < 2 || header.type >= 8) {                                           // (13) 0.03516
/*40  */         q->has_errors = 1;                                                               // (16) 0.0293
/*42  */         av_log(NULL, AV_LOG_ERROR, "bad superblock type\n");                             // (5) 0.05273
/*44  */         return;                                                                          // (20) 0.01758
/*46  */     }                                                                                    // (21) 0.007812
/*50  */     q->superblocktype_2_3 = (header.type == 2 || header.type == 3);                      // (7) 0.05078
/*52  */     packet_bytes          = (q->compressed_size - get_bits_count(&gb) / 8);              // (0) 0.06836
/*56  */     init_get_bits(&gb, header.data, header.size * 8);                                    // (11) 0.04102
/*60  */     if (header.type == 2 || header.type == 4 || header.type == 5) {                      // (9) 0.04687
/*62  */         int csum = 257 * get_bits(&gb, 8);                                               // 0.0
/*64  */         csum += 2 * get_bits(&gb, 8);                                                    // 0.0
/*68  */         csum = qdm2_packet_checksum(q->compressed_data, q->checksum_size, csum);         // 0.0
/*72  */         if (csum != 0) {                                                                 // 0.0
/*74  */             q->has_errors = 1;                                                           // 0.0
/*76  */             av_log(NULL, AV_LOG_ERROR, "bad packet checksum\n");                         // 0.0
/*78  */             return;                                                                      // 0.0
/*80  */         }                                                                                // 0.0
/*82  */     }                                                                                    // 0.0
/*86  */     q->sub_packet_list_B[0].packet = NULL;                                               // 0.0
/*88  */     q->sub_packet_list_D[0].packet = NULL;                                               // 0.0
/*92  */     for (i = 0; i < 6; i++)                                                              // 0.0
/*94  */         if (--q->fft_level_exp[i] < 0)                                                   // 0.0
/*96  */             q->fft_level_exp[i] = 0;                                                     // 0.0
/*100 */     for (i = 0; packet_bytes > 0; i++) {                                                 // 0.0
/*102 */         int j;                                                                           // 0.0
/*106 */         if (i >= FF_ARRAY_ELEMS(q->sub_packet_list_A)) {                                 // 0.0
/*108 */             SAMPLES_NEEDED_2("too many packet bytes");                                   // 0.0
/*110 */             return;                                                                      // 0.0
/*112 */         }                                                                                // 0.0
/*116 */         q->sub_packet_list_A[i].next = NULL;                                             // 0.0
/*120 */         if (i > 0) {                                                                     // 0.0
/*122 */             q->sub_packet_list_A[i - 1].next = &q->sub_packet_list_A[i];                 // 0.0
/*126 */             /* seek to next block */                                                     // 0.0
/*128 */             init_get_bits(&gb, header.data, header.size * 8);                            // 0.0
/*130 */             skip_bits(&gb, next_index * 8);                                              // 0.0
/*134 */             if (next_index >= header.size)                                               // 0.0
/*136 */                 break;                                                                   // 0.0
/*138 */         }                                                                                // 0.0
/*142 */         /* decode subpacket */                                                           // 0.0
/*144 */         packet = &q->sub_packets[i];                                                     // 0.0
/*146 */         qdm2_decode_sub_packet_header(&gb, packet);                                      // 0.0
/*148 */         next_index      = packet->size + get_bits_count(&gb) / 8;                        // 0.0
/*150 */         sub_packet_size = ((packet->size > 0xff) ? 1 : 0) + packet->size + 2;            // 0.0
/*154 */         if (packet->type == 0)                                                           // 0.0
/*156 */             break;                                                                       // 0.0
/*160 */         if (sub_packet_size > packet_bytes) {                                            // 0.0
/*162 */             if (packet->type != 10 && packet->type != 11 && packet->type != 12)          // 0.0
/*164 */                 break;                                                                   // 0.0
/*166 */             packet->size += packet_bytes - sub_packet_size;                              // 0.0
/*168 */         }                                                                                // 0.0
/*172 */         packet_bytes -= sub_packet_size;                                                 // 0.0
/*176 */         /* add subpacket to 'all subpackets' list */                                     // 0.0
/*178 */         q->sub_packet_list_A[i].packet = packet;                                         // 0.0
/*182 */         /* add subpacket to related list */                                              // 0.0
/*184 */         if (packet->type == 8) {                                                         // 0.0
/*186 */             SAMPLES_NEEDED_2("packet type 8");                                           // 0.0
/*188 */             return;                                                                      // 0.0
/*190 */         } else if (packet->type >= 9 && packet->type <= 12) {                            // 0.0
/*192 */             /* packets for MPEG Audio like Synthesis Filter */                           // 0.0
/*194 */             QDM2_LIST_ADD(q->sub_packet_list_D, sub_packets_D, packet);                  // 0.0
/*196 */         } else if (packet->type == 13) {                                                 // 0.0
/*198 */             for (j = 0; j < 6; j++)                                                      // 0.0
/*200 */                 q->fft_level_exp[j] = get_bits(&gb, 6);                                  // 0.0
/*202 */         } else if (packet->type == 14) {                                                 // 0.0
/*204 */             for (j = 0; j < 6; j++)                                                      // 0.0
/*206 */                 q->fft_level_exp[j] = qdm2_get_vlc(&gb, &fft_level_exp_vlc, 0, 2);       // 0.0
/*208 */         } else if (packet->type == 15) {                                                 // 0.0
/*210 */             SAMPLES_NEEDED_2("packet type 15")                                           // 0.0
/*212 */             return;                                                                      // 0.0
/*214 */         } else if (packet->type >= 16 && packet->type < 48 &&                            // 0.0
/*216 */                    !fft_subpackets[packet->type - 16]) {                                 // 0.0
/*218 */             /* packets for FFT */                                                        // 0.0
/*220 */             QDM2_LIST_ADD(q->sub_packet_list_B, q->sub_packets_B, packet);               // 0.0
/*222 */         }                                                                                // 0.0
/*224 */     } // Packet bytes loop                                                               // 0.0
/*228 */     if (q->sub_packet_list_D[0].packet != NULL) {                                        // 0.0
/*230 */         process_synthesis_subpackets(q, q->sub_packet_list_D);                           // 0.0
/*232 */         q->do_synth_filter = 1;                                                          // 0.0
/*234 */     } else if (q->do_synth_filter) {                                                     // 0.0
/*236 */         process_subpacket_10(q, NULL);                                                   // 0.0
/*238 */         process_subpacket_11(q, NULL);                                                   // 0.0
/*240 */         process_subpacket_12(q, NULL);                                                   // 0.0
/*242 */     }                                                                                    // 0.0
/*244 */ }                                                                                        // 0.0
