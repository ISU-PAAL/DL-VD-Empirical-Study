// commit message qemu@b2b012afdd (target=1, prob=0.43419886, correct=False): imx_fec: Change queue flushing heuristics
/*0   */ static ssize_t imx_fec_receive(NetClientState *nc, const uint8_t *buf,       // (4) 0.05469
/*2   */                                size_t len)                                   // (0) 0.06836
/*4   */ {                                                                            // (27) 0.001953
/*6   */     IMXFECState *s = IMX_FEC(qemu_get_nic_opaque(nc));                       // (3) 0.05859
/*8   */     IMXFECBufDesc bd;                                                        // (13) 0.02539
/*10  */     uint32_t flags = 0;                                                      // (17) 0.02148
/*12  */     uint32_t addr;                                                           // (22) 0.01758
/*14  */     uint32_t crc;                                                            // (20) 0.01953
/*16  */     uint32_t buf_addr;                                                       // (18) 0.02148
/*18  */     uint8_t *crc_ptr;                                                        // (14) 0.02539
/*20  */     unsigned int buf_len;                                                    // (23) 0.01758
/*22  */     size_t size = len;                                                       // (21) 0.01953
/*26  */     FEC_PRINTF("len %d\n", (int)size);                                       // (7) 0.03906
/*30  */     if (!s->regs[ENET_RDAR]) {                                               // (12) 0.0332
/*32  */         qemu_log_mask(LOG_GUEST_ERROR, "[%s]%s: Unexpected packet\n",        // (1) 0.06836
/*34  */                       TYPE_IMX_FEC, __func__);                               // (2) 0.06445
/*36  */         return 0;                                                            // (19) 0.01953
/*38  */     }                                                                        // (25) 0.007813
/*42  */     /* 4 bytes for the CRC.  */                                              // (16) 0.02344
/*44  */     size += 4;                                                               // (24) 0.01367
/*46  */     crc = cpu_to_be32(crc32(~0, buf, size));                                 // (6) 0.04688
/*48  */     crc_ptr = (uint8_t *) &crc;                                              // (9) 0.03516
/*52  */     /* Huge frames are truncated.  */                                        // (15) 0.02344
/*54  */     if (size > ENET_MAX_FRAME_SIZE) {                                        // (10) 0.03516
/*56  */         size = ENET_MAX_FRAME_SIZE;                                          // (8) 0.03711
/*58  */         flags |= ENET_BD_TR | ENET_BD_LG;                                    // (5) 0.04688
/*60  */     }                                                                        // (26) 0.007812
/*64  */     /* Frames larger than the user limit just set error flags.  */           // (11) 0.0332
/*66  */     if (size > (s->regs[ENET_RCR] >> 16)) {                                  // 0.0
/*68  */         flags |= ENET_BD_LG;                                                 // 0.0
/*70  */     }                                                                        // 0.0
/*74  */     addr = s->rx_descriptor;                                                 // 0.0
/*76  */     while (size > 0) {                                                       // 0.0
/*78  */         imx_fec_read_bd(&bd, addr);                                          // 0.0
/*80  */         if ((bd.flags & ENET_BD_E) == 0) {                                   // 0.0
/*82  */             /* No descriptors available.  Bail out.  */                      // 0.0
/*84  */             /*                                                               // 0.0
/*86  */              * FIXME: This is wrong. We should probably either               // 0.0
/*88  */              * save the remainder for when more RX buffers are               // 0.0
/*90  */              * available, or flag an error.                                  // 0.0
/*92  */              */                                                              // 0.0
/*94  */             qemu_log_mask(LOG_GUEST_ERROR, "[%s]%s: Lost end of frame\n",    // 0.0
/*96  */                           TYPE_IMX_FEC, __func__);                           // 0.0
/*98  */             break;                                                           // 0.0
/*100 */         }                                                                    // 0.0
/*102 */         buf_len = (size <= s->regs[ENET_MRBR]) ? size : s->regs[ENET_MRBR];  // 0.0
/*104 */         bd.length = buf_len;                                                 // 0.0
/*106 */         size -= buf_len;                                                     // 0.0
/*110 */         FEC_PRINTF("rx_bd 0x%x length %d\n", addr, bd.length);               // 0.0
/*114 */         /* The last 4 bytes are the CRC.  */                                 // 0.0
/*116 */         if (size < 4) {                                                      // 0.0
/*118 */             buf_len += size - 4;                                             // 0.0
/*120 */         }                                                                    // 0.0
/*122 */         buf_addr = bd.data;                                                  // 0.0
/*124 */         dma_memory_write(&address_space_memory, buf_addr, buf, buf_len);     // 0.0
/*126 */         buf += buf_len;                                                      // 0.0
/*128 */         if (size < 4) {                                                      // 0.0
/*130 */             dma_memory_write(&address_space_memory, buf_addr + buf_len,      // 0.0
/*132 */                              crc_ptr, 4 - size);                             // 0.0
/*134 */             crc_ptr += 4 - size;                                             // 0.0
/*136 */         }                                                                    // 0.0
/*138 */         bd.flags &= ~ENET_BD_E;                                              // 0.0
/*140 */         if (size == 0) {                                                     // 0.0
/*142 */             /* Last buffer in frame.  */                                     // 0.0
/*144 */             bd.flags |= flags | ENET_BD_L;                                   // 0.0
/*146 */             FEC_PRINTF("rx frame flags %04x\n", bd.flags);                   // 0.0
/*148 */             s->regs[ENET_EIR] |= ENET_INT_RXF;                               // 0.0
/*150 */         } else {                                                             // 0.0
/*152 */             s->regs[ENET_EIR] |= ENET_INT_RXB;                               // 0.0
/*154 */         }                                                                    // 0.0
/*156 */         imx_fec_write_bd(&bd, addr);                                         // 0.0
/*158 */         /* Advance to the next descriptor.  */                               // 0.0
/*160 */         if ((bd.flags & ENET_BD_W) != 0) {                                   // 0.0
/*162 */             addr = s->regs[ENET_RDSR];                                       // 0.0
/*164 */         } else {                                                             // 0.0
/*166 */             addr += sizeof(bd);                                              // 0.0
/*168 */         }                                                                    // 0.0
/*170 */     }                                                                        // 0.0
/*172 */     s->rx_descriptor = addr;                                                 // 0.0
/*174 */     imx_eth_enable_rx(s);                                                    // 0.0
/*176 */     imx_eth_update(s);                                                       // 0.0
/*178 */     return len;                                                              // 0.0
/*180 */ }                                                                            // 0.0
