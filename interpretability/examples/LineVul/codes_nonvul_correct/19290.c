// commit message qemu@df8002103c (target=0, prob=0.41431043, correct=True): Revert "vga: add some optional CGA compatibility hacks"
/*0   */ void vga_ioport_write(void *opaque, uint32_t addr, uint32_t val)                  // (4) 0.05078
/*2   */ {                                                                                 // (27) 0.001953
/*4   */     VGACommonState *s = opaque;                                                   // (18) 0.02539
/*6   */     int index;                                                                    // (24) 0.01172
/*10  */     /* check port range access depending on color/monochrome mode */              // (13) 0.0332
/*12  */     if (vga_ioport_invalid(s, addr)) {                                            // (10) 0.03711
/*14  */         return;                                                                   // (21) 0.01758
/*16  */     }                                                                             // (25) 0.007812
/*18  */ #ifdef DEBUG_VGA                                                                  // (23) 0.01367
/*20  */     printf("VGA: write addr=0x%04x data=0x%02x\n", addr, val);                    // (1) 0.05859
/*22  */ #endif                                                                            // (26) 0.003906
/*26  */     switch(addr) {                                                                // (22) 0.01562
/*28  */     case VGA_ATT_W:                                                               // (19) 0.02148
/*30  */         if (s->ar_flip_flop == 0) {                                               // (7) 0.04297
/*32  */             val &= 0x3f;                                                          // (11) 0.03711
/*34  */             s->ar_index = val;                                                    // (12) 0.03711
/*36  */         } else {                                                                  // (20) 0.01953
/*38  */             index = s->ar_index & 0x1f;                                           // (5) 0.04688
/*40  */             switch(index) {                                                       // (17) 0.03125
/*42  */             case VGA_ATC_PALETTE0 ... VGA_ATC_PALETTEF:                           // (0) 0.07031
/*44  */                 s->ar[index] = val & 0x3f;                                        // (2) 0.05664
/*46  */                 break;                                                            // (14) 0.0332
/*48  */             case VGA_ATC_MODE:                                                    // (9) 0.03906
/*50  */                 s->ar[index] = val & ~0x10;                                       // (3) 0.05664
/*52  */                 break;                                                            // (15) 0.0332
/*54  */             case VGA_ATC_OVERSCAN:                                                // (8) 0.04297
/*56  */                 s->ar[index] = val;                                               // (6) 0.04688
/*58  */                 break;                                                            // (16) 0.0332
/*60  */             case VGA_ATC_PLANE_ENABLE:                                            // 0.0
/*62  */                 s->ar[index] = val & ~0xc0;                                       // 0.0
/*64  */                 break;                                                            // 0.0
/*66  */             case VGA_ATC_PEL:                                                     // 0.0
/*68  */                 s->ar[index] = val & ~0xf0;                                       // 0.0
/*70  */                 break;                                                            // 0.0
/*72  */             case VGA_ATC_COLOR_PAGE:                                              // 0.0
/*74  */                 s->ar[index] = val & ~0xf0;                                       // 0.0
/*76  */                 break;                                                            // 0.0
/*78  */             default:                                                              // 0.0
/*80  */                 break;                                                            // 0.0
/*82  */             }                                                                     // 0.0
/*84  */         }                                                                         // 0.0
/*86  */         s->ar_flip_flop ^= 1;                                                     // 0.0
/*88  */         break;                                                                    // 0.0
/*90  */     case VGA_MIS_W:                                                               // 0.0
/*92  */         s->msr = val & ~0x10;                                                     // 0.0
/*94  */         s->update_retrace_info(s);                                                // 0.0
/*96  */         break;                                                                    // 0.0
/*98  */     case VGA_SEQ_I:                                                               // 0.0
/*100 */         s->sr_index = val & 7;                                                    // 0.0
/*102 */         break;                                                                    // 0.0
/*104 */     case VGA_SEQ_D:                                                               // 0.0
/*106 */ #ifdef DEBUG_VGA_REG                                                              // 0.0
/*108 */         printf("vga: write SR%x = 0x%02x\n", s->sr_index, val);                   // 0.0
/*110 */ #endif                                                                            // 0.0
/*112 */         s->sr[s->sr_index] = val & sr_mask[s->sr_index];                          // 0.0
/*114 */         if (s->sr_index == VGA_SEQ_CLOCK_MODE) {                                  // 0.0
/*116 */             s->update_retrace_info(s);                                            // 0.0
/*118 */         }                                                                         // 0.0
/*120 */         vga_update_memory_access(s);                                              // 0.0
/*122 */         break;                                                                    // 0.0
/*124 */     case VGA_PEL_IR:                                                              // 0.0
/*126 */         s->dac_read_index = val;                                                  // 0.0
/*128 */         s->dac_sub_index = 0;                                                     // 0.0
/*130 */         s->dac_state = 3;                                                         // 0.0
/*132 */         break;                                                                    // 0.0
/*134 */     case VGA_PEL_IW:                                                              // 0.0
/*136 */         s->dac_write_index = val;                                                 // 0.0
/*138 */         s->dac_sub_index = 0;                                                     // 0.0
/*140 */         s->dac_state = 0;                                                         // 0.0
/*142 */         break;                                                                    // 0.0
/*144 */     case VGA_PEL_D:                                                               // 0.0
/*146 */         s->dac_cache[s->dac_sub_index] = val;                                     // 0.0
/*148 */         if (++s->dac_sub_index == 3) {                                            // 0.0
/*150 */             memcpy(&s->palette[s->dac_write_index * 3], s->dac_cache, 3);         // 0.0
/*152 */             s->dac_sub_index = 0;                                                 // 0.0
/*154 */             s->dac_write_index++;                                                 // 0.0
/*156 */         }                                                                         // 0.0
/*158 */         break;                                                                    // 0.0
/*160 */     case VGA_GFX_I:                                                               // 0.0
/*162 */         s->gr_index = val & 0x0f;                                                 // 0.0
/*164 */         break;                                                                    // 0.0
/*166 */     case VGA_GFX_D:                                                               // 0.0
/*168 */ #ifdef DEBUG_VGA_REG                                                              // 0.0
/*170 */         printf("vga: write GR%x = 0x%02x\n", s->gr_index, val);                   // 0.0
/*172 */ #endif                                                                            // 0.0
/*174 */         s->gr[s->gr_index] = val & gr_mask[s->gr_index];                          // 0.0
/*176 */         vga_update_memory_access(s);                                              // 0.0
/*178 */         break;                                                                    // 0.0
/*180 */     case VGA_CRT_IM:                                                              // 0.0
/*182 */     case VGA_CRT_IC:                                                              // 0.0
/*184 */         s->cr_index = val;                                                        // 0.0
/*186 */         break;                                                                    // 0.0
/*188 */     case VGA_CRT_DM:                                                              // 0.0
/*190 */     case VGA_CRT_DC:                                                              // 0.0
/*192 */ #ifdef DEBUG_VGA_REG                                                              // 0.0
/*194 */         printf("vga: write CR%x = 0x%02x\n", s->cr_index, val);                   // 0.0
/*196 */ #endif                                                                            // 0.0
/*198 */         /* handle CR0-7 protection */                                             // 0.0
/*200 */         if (s->cr[VGA_CRTC_V_SYNC_END] & VGA_CR11_LOCK_CR0_CR7) {                 // 0.0
/*202 */             if (s->cr_index <= VGA_CRTC_OVERFLOW) {                               // 0.0
/*204 */                 /* can always write bit 4 of CR7 */                               // 0.0
/*206 */                 if (s->cr_index == VGA_CRTC_OVERFLOW) {                           // 0.0
/*208 */                     s->cr[VGA_CRTC_OVERFLOW] =                                    // 0.0
/*210 */                         (s->cr[VGA_CRTC_OVERFLOW] & ~0x10) | (val & 0x10);        // 0.0
/*212 */                 }                                                                 // 0.0
/*214 */                 return;                                                           // 0.0
/*216 */             } else if ((vga_cga_hacks & VGA_CGA_HACK_FONT_HEIGHT) &&              // 0.0
/*218 */                        !(s->sr[VGA_SEQ_CLOCK_MODE] & VGA_SR01_CHAR_CLK_8DOTS)) {  // 0.0
/*220 */                 /* extra CGA compatibility hacks (not in standard VGA) */         // 0.0
/*222 */                 if (s->cr_index == VGA_CRTC_MAX_SCAN &&                           // 0.0
/*224 */                     val == 7 &&                                                   // 0.0
/*226 */                     (s->cr[VGA_CRTC_MAX_SCAN] & 0xf) == 0xf) {                    // 0.0
/*228 */                     return;                                                       // 0.0
/*230 */                 } else if (s->cr_index == VGA_CRTC_CURSOR_START &&                // 0.0
/*232 */                            val == 6 &&                                            // 0.0
/*234 */                            (s->cr[VGA_CRTC_MAX_SCAN] & 0xf) == 0xf) {             // 0.0
/*236 */                     val = 0xd;                                                    // 0.0
/*238 */                 } else if (s->cr_index == VGA_CRTC_CURSOR_END &&                  // 0.0
/*240 */                            val == 7 &&                                            // 0.0
/*242 */                            (s->cr[VGA_CRTC_MAX_SCAN] & 0xf) == 0xf) {             // 0.0
/*244 */                     val = 0xe;                                                    // 0.0
/*246 */                 }                                                                 // 0.0
/*248 */             }                                                                     // 0.0
/*250 */         }                                                                         // 0.0
/*252 */         s->cr[s->cr_index] = val;                                                 // 0.0
/*256 */         switch(s->cr_index) {                                                     // 0.0
/*258 */         case VGA_CRTC_H_TOTAL:                                                    // 0.0
/*260 */         case VGA_CRTC_H_SYNC_START:                                               // 0.0
/*262 */         case VGA_CRTC_H_SYNC_END:                                                 // 0.0
/*264 */         case VGA_CRTC_V_TOTAL:                                                    // 0.0
/*266 */         case VGA_CRTC_OVERFLOW:                                                   // 0.0
/*268 */         case VGA_CRTC_V_SYNC_END:                                                 // 0.0
/*270 */         case VGA_CRTC_MODE:                                                       // 0.0
/*272 */             s->update_retrace_info(s);                                            // 0.0
/*274 */             break;                                                                // 0.0
/*276 */         }                                                                         // 0.0
/*278 */         break;                                                                    // 0.0
/*280 */     case VGA_IS1_RM:                                                              // 0.0
/*282 */     case VGA_IS1_RC:                                                              // 0.0
/*284 */         s->fcr = val & 0x10;                                                      // 0.0
/*286 */         break;                                                                    // 0.0
/*288 */     }                                                                             // 0.0
/*290 */ }                                                                                 // 0.0
