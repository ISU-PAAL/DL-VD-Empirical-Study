// commit message qemu@54f254f973 (target=0, prob=0.13067892, correct=True): uhci: rewrite UHCI emulator, fully async operation with multiple outstanding transactions (Max Krasnyansky)
/*0   */ static void uhci_async_complete_packet(USBPacket * packet, void *opaque)    // (4) 0.04688
/*2   */ {                                                                           // (25) 0.001953
/*4   */     UHCIState *s = opaque;                                                  // (17) 0.02344
/*6   */     UHCI_QH qh;                                                             // (18) 0.02344
/*8   */     UHCI_TD td;                                                             // (20) 0.01953
/*10  */     uint32_t link;                                                          // (22) 0.01758
/*12  */     uint32_t old_td_ctrl;                                                   // (16) 0.02539
/*14  */     uint32_t val;                                                           // (23) 0.01758
/*16  */     uint32_t frame_addr;                                                    // (19) 0.02148
/*18  */     int ret;                                                                // (24) 0.01172
/*22  */     /* Handle async isochronous packet completion */                        // (15) 0.02539
/*24  */     frame_addr = s->async_frame_addr;                                       // (14) 0.03125
/*26  */     if (frame_addr) {                                                       // (21) 0.01953
/*28  */         cpu_physical_memory_read(frame_addr, (uint8_t *)&link, 4);          // (2) 0.05859
/*30  */         le32_to_cpus(&link);                                                // (11) 0.0332
/*34  */         cpu_physical_memory_read(link & ~0xf, (uint8_t *)&td, sizeof(td));  // (0) 0.06641
/*36  */         le32_to_cpus(&td.link);                                             // (9) 0.03711
/*38  */         le32_to_cpus(&td.ctrl);                                             // (8) 0.03711
/*40  */         le32_to_cpus(&td.token);                                            // (10) 0.03711
/*42  */         le32_to_cpus(&td.buffer);                                           // (7) 0.03711
/*44  */         old_td_ctrl = td.ctrl;                                              // (12) 0.0332
/*46  */         ret = uhci_handle_td(s, &td, &s->pending_int_mask, 1);              // (1) 0.06445
/*50  */         /* update the status bits of the TD */                              // (13) 0.03125
/*52  */         if (old_td_ctrl != td.ctrl) {                                       // (6) 0.03906
/*54  */             val = cpu_to_le32(td.ctrl);                                     // (5) 0.04688
/*56  */             cpu_physical_memory_write((link & ~0xf) + 4,                    // (3) 0.05469
/*58  */                                       (const uint8_t *)&val,                // 0.0
/*60  */                                       sizeof(val));                         // 0.0
/*62  */         }                                                                   // 0.0
/*64  */         if (ret == 2) {                                                     // 0.0
/*66  */             s->async_frame_addr = frame_addr;                               // 0.0
/*68  */         } else if (ret == 0) {                                              // 0.0
/*70  */             /* update qh element link */                                    // 0.0
/*72  */             val = cpu_to_le32(td.link);                                     // 0.0
/*74  */             cpu_physical_memory_write(frame_addr,                           // 0.0
/*76  */                                       (const uint8_t *)&val,                // 0.0
/*78  */                                       sizeof(val));                         // 0.0
/*80  */         }                                                                   // 0.0
/*82  */         return;                                                             // 0.0
/*84  */     }                                                                       // 0.0
/*88  */     link = s->async_qh;                                                     // 0.0
/*90  */     if (!link) {                                                            // 0.0
/*92  */         /* This should never happen. It means a TD somehow got removed      // 0.0
/*94  */            without cancelling the associated async IO request.  */          // 0.0
/*96  */         return;                                                             // 0.0
/*98  */     }                                                                       // 0.0
/*100 */     cpu_physical_memory_read(link & ~0xf, (uint8_t *)&qh, sizeof(qh));      // 0.0
/*102 */     le32_to_cpus(&qh.link);                                                 // 0.0
/*104 */     le32_to_cpus(&qh.el_link);                                              // 0.0
/*106 */     /* Re-process the queue containing the async packet.  */                // 0.0
/*108 */     while (1) {                                                             // 0.0
/*110 */         cpu_physical_memory_read(qh.el_link & ~0xf,                         // 0.0
/*112 */                                  (uint8_t *)&td, sizeof(td));               // 0.0
/*114 */         le32_to_cpus(&td.link);                                             // 0.0
/*116 */         le32_to_cpus(&td.ctrl);                                             // 0.0
/*118 */         le32_to_cpus(&td.token);                                            // 0.0
/*120 */         le32_to_cpus(&td.buffer);                                           // 0.0
/*122 */         old_td_ctrl = td.ctrl;                                              // 0.0
/*124 */         ret = uhci_handle_td(s, &td, &s->pending_int_mask, 1);              // 0.0
/*128 */         /* update the status bits of the TD */                              // 0.0
/*130 */         if (old_td_ctrl != td.ctrl) {                                       // 0.0
/*132 */             val = cpu_to_le32(td.ctrl);                                     // 0.0
/*134 */             cpu_physical_memory_write((qh.el_link & ~0xf) + 4,              // 0.0
/*136 */                                       (const uint8_t *)&val,                // 0.0
/*138 */                                       sizeof(val));                         // 0.0
/*140 */         }                                                                   // 0.0
/*142 */         if (ret < 0)                                                        // 0.0
/*144 */             break; /* interrupted frame */                                  // 0.0
/*146 */         if (ret == 2) {                                                     // 0.0
/*148 */             s->async_qh = link;                                             // 0.0
/*150 */             break;                                                          // 0.0
/*152 */         } else if (ret == 0) {                                              // 0.0
/*154 */             /* update qh element link */                                    // 0.0
/*156 */             qh.el_link = td.link;                                           // 0.0
/*158 */             val = cpu_to_le32(qh.el_link);                                  // 0.0
/*160 */             cpu_physical_memory_write((link & ~0xf) + 4,                    // 0.0
/*162 */                                       (const uint8_t *)&val,                // 0.0
/*164 */                                       sizeof(val));                         // 0.0
/*166 */             if (!(qh.el_link & 4))                                          // 0.0
/*168 */                 break;                                                      // 0.0
/*170 */         }                                                                   // 0.0
/*172 */         break;                                                              // 0.0
/*174 */     }                                                                       // 0.0
/*176 */ }                                                                           // 0.0
