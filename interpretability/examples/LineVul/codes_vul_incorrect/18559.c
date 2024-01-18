// commit message qemu@ff472a5bad (target=1, prob=0.49684137, correct=False): cuda.c: return error for unknown commands
/*0   */ static void cuda_receive_packet(CUDAState *s,                                                                   // (12) 0.0332
/*2   */                                 const uint8_t *data, int len)                                                   // (2) 0.08203
/*4   */ {                                                                                                               // (23) 0.001953
/*6   */     uint8_t obuf[16] = { CUDA_PACKET, 0, data[0] };                                                             // (3) 0.05469
/*8   */     int autopoll;                                                                                               // (22) 0.01367
/*10  */     uint32_t ti;                                                                                                // (18) 0.01758
/*14  */     switch(data[0]) {                                                                                           // (17) 0.01953
/*16  */     case CUDA_AUTOPOLL:                                                                                         // (15) 0.02344
/*18  */         autopoll = (data[1] != 0);                                                                              // (10) 0.03516
/*20  */         if (autopoll != s->autopoll) {                                                                          // (9) 0.03906
/*22  */             s->autopoll = autopoll;                                                                             // (8) 0.03906
/*24  */             if (autopoll) {                                                                                     // (11) 0.03516
/*26  */                 timer_mod(s->adb_poll_timer,                                                                    // (5) 0.05469
/*28  */                                qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) +                                          // (1) 0.1016
/*30  */                                (get_ticks_per_sec() / CUDA_ADB_POLL_FREQ));                                     // (0) 0.1055
/*32  */             } else {                                                                                            // (14) 0.02734
/*34  */                 timer_del(s->adb_poll_timer);                                                                   // (4) 0.05469
/*36  */             }                                                                                                   // (16) 0.02344
/*38  */         }                                                                                                       // (21) 0.01562
/*40  */         cuda_send_packet_to_host(s, obuf, 3);                                                                   // (6) 0.05078
/*42  */         break;                                                                                                  // (19) 0.01758
/*44  */     case CUDA_GET_6805_ADDR:                                                                                    // (13) 0.0293
/*46  */         cuda_send_packet_to_host(s, obuf, 3);                                                                   // (7) 0.05078
/*48  */         break;                                                                                                  // (20) 0.01758
/*50  */     case CUDA_SET_TIME:                                                                                         // 0.0
/*52  */         ti = (((uint32_t)data[1]) << 24) + (((uint32_t)data[2]) << 16) + (((uint32_t)data[3]) << 8) + data[4];  // 0.0
/*54  */         s->tick_offset = ti - (qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) / get_ticks_per_sec());                    // 0.0
/*56  */         cuda_send_packet_to_host(s, obuf, 3);                                                                   // 0.0
/*58  */         break;                                                                                                  // 0.0
/*60  */     case CUDA_GET_TIME:                                                                                         // 0.0
/*62  */         ti = s->tick_offset + (qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) / get_ticks_per_sec());                    // 0.0
/*64  */         obuf[3] = ti >> 24;                                                                                     // 0.0
/*66  */         obuf[4] = ti >> 16;                                                                                     // 0.0
/*68  */         obuf[5] = ti >> 8;                                                                                      // 0.0
/*70  */         obuf[6] = ti;                                                                                           // 0.0
/*72  */         cuda_send_packet_to_host(s, obuf, 7);                                                                   // 0.0
/*74  */         break;                                                                                                  // 0.0
/*76  */     case CUDA_FILE_SERVER_FLAG:                                                                                 // 0.0
/*78  */     case CUDA_SET_DEVICE_LIST:                                                                                  // 0.0
/*80  */     case CUDA_SET_AUTO_RATE:                                                                                    // 0.0
/*82  */     case CUDA_SET_POWER_MESSAGES:                                                                               // 0.0
/*84  */         cuda_send_packet_to_host(s, obuf, 3);                                                                   // 0.0
/*86  */         break;                                                                                                  // 0.0
/*88  */     case CUDA_POWERDOWN:                                                                                        // 0.0
/*90  */         cuda_send_packet_to_host(s, obuf, 3);                                                                   // 0.0
/*92  */         qemu_system_shutdown_request();                                                                         // 0.0
/*94  */         break;                                                                                                  // 0.0
/*96  */     case CUDA_RESET_SYSTEM:                                                                                     // 0.0
/*98  */         cuda_send_packet_to_host(s, obuf, 3);                                                                   // 0.0
/*100 */         qemu_system_reset_request();                                                                            // 0.0
/*102 */         break;                                                                                                  // 0.0
/*104 */     case CUDA_COMBINED_FORMAT_IIC:                                                                              // 0.0
/*107 */         obuf[1] = 0x5;                                                                                          // 0.0
/*112 */         break;                                                                                                  // 0.0
/*114 */     case CUDA_GET_SET_IIC:                                                                                      // 0.0
/*116 */         if (len == 4) {                                                                                         // 0.0
/*118 */             cuda_send_packet_to_host(s, obuf, 3);                                                               // 0.0
/*120 */         } else {                                                                                                // 0.0
/*127 */         }                                                                                                       // 0.0
/*129 */         break;                                                                                                  // 0.0
/*131 */     default:                                                                                                    // 0.0
/*138 */         break;                                                                                                  // 0.0
/*140 */     }                                                                                                           // 0.0
/*142 */ }                                                                                                               // 0.0
