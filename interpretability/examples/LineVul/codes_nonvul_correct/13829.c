// commit message qemu@6a2a5aae02 (target=0, prob=0.01969281, correct=True): sm501: Fix hardware cursor
/*0   */ static void sm501_disp_ctrl_write(void *opaque, hwaddr addr,                 // (9) 0.04297
/*2   */                                   uint64_t value, unsigned size)             // (0) 0.08203
/*4   */ {                                                                            // (24) 0.001953
/*6   */     SM501State *s = (SM501State *)opaque;                                    // (15) 0.0332
/*8   */     SM501_DPRINTF("sm501 disp ctrl regs : write addr=%x, val=%x\n",          // (1) 0.0625
/*10  */                   (unsigned)addr, (unsigned)value);                          // (5) 0.05273
/*14  */     switch (addr) {                                                          // (23) 0.01562
/*16  */     case SM501_DC_PANEL_CONTROL:                                             // (16) 0.0332
/*18  */         s->dc_panel_control = value & 0x0FFF73FF;                            // (8) 0.04883
/*20  */         break;                                                               // (17) 0.01758
/*22  */     case SM501_DC_PANEL_PANNING_CONTROL:                                     // (10) 0.04102
/*24  */         s->dc_panel_panning_control = value & 0xFF3FFF3F;                    // (2) 0.05664
/*26  */         break;                                                               // (18) 0.01758
/*28  */     case SM501_DC_PANEL_FB_ADDR:                                             // (12) 0.03516
/*30  */         s->dc_panel_fb_addr = value & 0x8FFFFFF0;                            // (7) 0.05078
/*32  */         break;                                                               // (19) 0.01758
/*34  */     case SM501_DC_PANEL_FB_OFFSET:                                           // (13) 0.03516
/*36  */         s->dc_panel_fb_offset = value & 0x3FF03FF0;                          // (6) 0.05273
/*38  */         break;                                                               // (20) 0.01758
/*40  */     case SM501_DC_PANEL_FB_WIDTH:                                            // (11) 0.03711
/*42  */         s->dc_panel_fb_width = value & 0x0FFF0FFF;                           // (3) 0.05469
/*44  */         break;                                                               // (21) 0.01758
/*46  */     case SM501_DC_PANEL_FB_HEIGHT:                                           // (14) 0.03516
/*48  */         s->dc_panel_fb_height = value & 0x0FFF0FFF;                          // (4) 0.05469
/*50  */         break;                                                               // (22) 0.01758
/*52  */     case SM501_DC_PANEL_TL_LOC:                                              // 0.0
/*54  */         s->dc_panel_tl_location = value & 0x07FF07FF;                        // 0.0
/*56  */         break;                                                               // 0.0
/*58  */     case SM501_DC_PANEL_BR_LOC:                                              // 0.0
/*60  */         s->dc_panel_br_location = value & 0x07FF07FF;                        // 0.0
/*62  */         break;                                                               // 0.0
/*66  */     case SM501_DC_PANEL_H_TOT:                                               // 0.0
/*68  */         s->dc_panel_h_total = value & 0x0FFF0FFF;                            // 0.0
/*70  */         break;                                                               // 0.0
/*72  */     case SM501_DC_PANEL_H_SYNC:                                              // 0.0
/*74  */         s->dc_panel_h_sync = value & 0x00FF0FFF;                             // 0.0
/*76  */         break;                                                               // 0.0
/*78  */     case SM501_DC_PANEL_V_TOT:                                               // 0.0
/*80  */         s->dc_panel_v_total = value & 0x0FFF0FFF;                            // 0.0
/*82  */         break;                                                               // 0.0
/*84  */     case SM501_DC_PANEL_V_SYNC:                                              // 0.0
/*86  */         s->dc_panel_v_sync = value & 0x003F0FFF;                             // 0.0
/*88  */         break;                                                               // 0.0
/*92  */     case SM501_DC_PANEL_HWC_ADDR:                                            // 0.0
/*94  */         s->dc_panel_hwc_addr = value & 0x8FFFFFF0;                           // 0.0
/*96  */         break;                                                               // 0.0
/*98  */     case SM501_DC_PANEL_HWC_LOC:                                             // 0.0
/*100 */         s->dc_panel_hwc_location = value & 0x0FFF0FFF;                       // 0.0
/*102 */         break;                                                               // 0.0
/*104 */     case SM501_DC_PANEL_HWC_COLOR_1_2:                                       // 0.0
/*106 */         s->dc_panel_hwc_color_1_2 = value;                                   // 0.0
/*108 */         break;                                                               // 0.0
/*110 */     case SM501_DC_PANEL_HWC_COLOR_3:                                         // 0.0
/*112 */         s->dc_panel_hwc_color_3 = value & 0x0000FFFF;                        // 0.0
/*114 */         break;                                                               // 0.0
/*118 */     case SM501_DC_CRT_CONTROL:                                               // 0.0
/*120 */         s->dc_crt_control = value & 0x0003FFFF;                              // 0.0
/*122 */         break;                                                               // 0.0
/*124 */     case SM501_DC_CRT_FB_ADDR:                                               // 0.0
/*126 */         s->dc_crt_fb_addr = value & 0x8FFFFFF0;                              // 0.0
/*128 */         break;                                                               // 0.0
/*130 */     case SM501_DC_CRT_FB_OFFSET:                                             // 0.0
/*132 */         s->dc_crt_fb_offset = value & 0x3FF03FF0;                            // 0.0
/*134 */         break;                                                               // 0.0
/*136 */     case SM501_DC_CRT_H_TOT:                                                 // 0.0
/*138 */         s->dc_crt_h_total = value & 0x0FFF0FFF;                              // 0.0
/*140 */         break;                                                               // 0.0
/*142 */     case SM501_DC_CRT_H_SYNC:                                                // 0.0
/*144 */         s->dc_crt_h_sync = value & 0x00FF0FFF;                               // 0.0
/*146 */         break;                                                               // 0.0
/*148 */     case SM501_DC_CRT_V_TOT:                                                 // 0.0
/*150 */         s->dc_crt_v_total = value & 0x0FFF0FFF;                              // 0.0
/*152 */         break;                                                               // 0.0
/*154 */     case SM501_DC_CRT_V_SYNC:                                                // 0.0
/*156 */         s->dc_crt_v_sync = value & 0x003F0FFF;                               // 0.0
/*158 */         break;                                                               // 0.0
/*162 */     case SM501_DC_CRT_HWC_ADDR:                                              // 0.0
/*164 */         s->dc_crt_hwc_addr = value & 0x8FFFFFF0;                             // 0.0
/*166 */         break;                                                               // 0.0
/*168 */     case SM501_DC_CRT_HWC_LOC:                                               // 0.0
/*170 */         s->dc_crt_hwc_location = value & 0x0FFF0FFF;                         // 0.0
/*172 */         break;                                                               // 0.0
/*174 */     case SM501_DC_CRT_HWC_COLOR_1_2:                                         // 0.0
/*176 */         s->dc_crt_hwc_color_1_2 = value;                                     // 0.0
/*178 */         break;                                                               // 0.0
/*180 */     case SM501_DC_CRT_HWC_COLOR_3:                                           // 0.0
/*182 */         s->dc_crt_hwc_color_3 = value & 0x0000FFFF;                          // 0.0
/*184 */         break;                                                               // 0.0
/*188 */     case SM501_DC_PANEL_PALETTE ... SM501_DC_PANEL_PALETTE + 0x400 * 3 - 4:  // 0.0
/*190 */         sm501_palette_write(opaque, addr - SM501_DC_PANEL_PALETTE, value);   // 0.0
/*192 */         break;                                                               // 0.0
/*196 */     default:                                                                 // 0.0
/*198 */         printf("sm501 disp ctrl : not implemented register write."           // 0.0
/*200 */                " addr=%x, val=%x\n", (int)addr, (unsigned)value);            // 0.0
/*202 */         abort();                                                             // 0.0
/*204 */     }                                                                        // 0.0
/*206 */ }                                                                            // 0.0
