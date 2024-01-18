// commit message FFmpeg@f929ab0569 (target=0, prob=0.3975318, correct=True): cosmetics: Write NULL pointer equality checks more compactly
/*0   */ static int get_last_needed_nal(H264Context *h, const uint8_t *buf, int buf_size)  // (4) 0.05859
/*2   */ {                                                                                 // (23) 0.001953
/*4   */     int next_avc    = h->is_avc ? 0 : buf_size;                                   // (5) 0.04883
/*6   */     int nal_index   = 0;                                                          // (17) 0.02539
/*8   */     int buf_index   = 0;                                                          // (18) 0.02344
/*10  */     int nals_needed = 0;                                                          // (19) 0.02148
/*14  */     while(1) {                                                                    // (21) 0.01563
/*16  */         int nalsize = 0;                                                          // (16) 0.02734
/*18  */         int dst_length, bit_length, consumed;                                     // (12) 0.03516
/*20  */         const uint8_t *ptr;                                                       // (15) 0.0293
/*24  */         if (buf_index >= next_avc) {                                              // (10) 0.03711
/*26  */             nalsize = get_avc_nalsize(h, buf, buf_size, &buf_index);              // (2) 0.07227
/*28  */             if (nalsize < 0)                                                      // (11) 0.03711
/*30  */                 break;                                                            // (13) 0.0332
/*32  */             next_avc = buf_index + nalsize;                                       // (6) 0.04687
/*34  */         } else {                                                                  // (20) 0.01953
/*36  */             buf_index = find_start_code(buf, buf_size, buf_index, next_avc);      // (3) 0.07031
/*38  */             if (buf_index >= buf_size)                                            // (8) 0.04102
/*40  */                 break;                                                            // (14) 0.0332
/*42  */         }                                                                         // (22) 0.01562
/*46  */         ptr = ff_h264_decode_nal(h, buf + buf_index, &dst_length, &consumed,      // (1) 0.07422
/*48  */                                  next_avc - buf_index);                           // (0) 0.08008
/*52  */         if (ptr == NULL || dst_length < 0)                                        // (9) 0.03711
/*54  */             return AVERROR_INVALIDDATA;                                           // (7) 0.04102
/*58  */         buf_index += consumed;                                                    // 0.0
/*62  */         bit_length = get_bit_length(h, buf, ptr, dst_length,                      // 0.0
/*64  */                                     buf_index, next_avc);                         // 0.0
/*66  */         nal_index++;                                                              // 0.0
/*70  */         /* packets can sometimes contain multiple PPS/SPS,                        // 0.0
/*72  */          * e.g. two PAFF field pictures in one packet, or a demuxer               // 0.0
/*74  */          * which splits NALs strangely if so, when frame threading we             // 0.0
/*76  */          * can't start the next thread until we've read all of them */            // 0.0
/*78  */         switch (h->nal_unit_type) {                                               // 0.0
/*80  */         case NAL_SPS:                                                             // 0.0
/*82  */         case NAL_PPS:                                                             // 0.0
/*84  */             nals_needed = nal_index;                                              // 0.0
/*86  */             break;                                                                // 0.0
/*88  */         case NAL_DPA:                                                             // 0.0
/*90  */         case NAL_IDR_SLICE:                                                       // 0.0
/*92  */         case NAL_SLICE:                                                           // 0.0
/*94  */             init_get_bits(&h->gb, ptr, bit_length);                               // 0.0
/*96  */             if (!get_ue_golomb(&h->gb))                                           // 0.0
/*98  */                 nals_needed = nal_index;                                          // 0.0
/*100 */         }                                                                         // 0.0
/*102 */     }                                                                             // 0.0
/*106 */     return nals_needed;                                                           // 0.0
/*108 */ }                                                                                 // 0.0
