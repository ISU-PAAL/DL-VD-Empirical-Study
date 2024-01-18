// commit message qemu@a8170e5e97 (target=0, prob=0.009771365, correct=True): Rename target_phys_addr_t to hwaddr
/*0   */ static uint64_t exynos4210_fimd_read(void *opaque, target_phys_addr_t offset,    // (1) 0.06055
/*2   */                                   unsigned size)                                 // (0) 0.07031
/*4   */ {                                                                                // (22) 0.001953
/*6   */     Exynos4210fimdState *s = (Exynos4210fimdState *)opaque;                      // (5) 0.05664
/*8   */     int w, i;                                                                    // (20) 0.01562
/*10  */     uint32_t ret = 0;                                                            // (18) 0.02148
/*14  */     DPRINT_L2("read offset 0x%08x\n", offset);                                   // (11) 0.04102
/*18  */     switch (offset) {                                                            // (21) 0.01562
/*20  */     case FIMD_VIDCON0 ... FIMD_VIDCON3:                                          // (12) 0.03906
/*22  */         return s->vidcon[(offset - FIMD_VIDCON0) >> 2];                          // (6) 0.05273
/*24  */     case FIMD_VIDTCON_START ... FIMD_VIDTCON_END:                                // (8) 0.04883
/*26  */         return s->vidtcon[(offset - FIMD_VIDTCON_START) >> 2];                   // (2) 0.06055
/*28  */     case FIMD_WINCON_START ... FIMD_WINCON_END:                                  // (10) 0.04492
/*30  */         return s->window[(offset - FIMD_WINCON_START) >> 2].wincon;              // (3) 0.06055
/*32  */     case FIMD_SHADOWCON:                                                         // (14) 0.02539
/*34  */         return s->shadowcon;                                                     // (15) 0.02539
/*36  */     case FIMD_WINCHMAP:                                                          // (16) 0.02344
/*38  */         return s->winchmap;                                                      // (13) 0.02734
/*40  */     case FIMD_VIDOSD_START ... FIMD_VIDOSD_END:                                  // (9) 0.04883
/*42  */         w = (offset - FIMD_VIDOSD_START) >> 4;                                   // (7) 0.05078
/*44  */         i = ((offset - FIMD_VIDOSD_START) & 0xF) >> 2;                           // (4) 0.06055
/*46  */         switch (i) {                                                             // (17) 0.02344
/*48  */         case 0:                                                                  // (19) 0.01953
/*50  */             ret = ((s->window[w].lefttop_x & FIMD_VIDOSD_COORD_MASK) <<          // 0.0
/*52  */             FIMD_VIDOSD_HOR_SHIFT) |                                             // 0.0
/*54  */             (s->window[w].lefttop_y & FIMD_VIDOSD_COORD_MASK);                   // 0.0
/*56  */             break;                                                               // 0.0
/*58  */         case 1:                                                                  // 0.0
/*60  */             ret = ((s->window[w].rightbot_x & FIMD_VIDOSD_COORD_MASK) <<         // 0.0
/*62  */                 FIMD_VIDOSD_HOR_SHIFT) |                                         // 0.0
/*64  */                 (s->window[w].rightbot_y & FIMD_VIDOSD_COORD_MASK);              // 0.0
/*66  */             break;                                                               // 0.0
/*68  */         case 2:                                                                  // 0.0
/*70  */             if (w == 0) {                                                        // 0.0
/*72  */                 ret = s->window[w].osdsize;                                      // 0.0
/*74  */             } else {                                                             // 0.0
/*76  */                 ret = (pack_upper_4(s->window[w].alpha_val[0]) <<                // 0.0
/*78  */                     FIMD_VIDOSD_AEN0_SHIFT) |                                    // 0.0
/*80  */                     pack_upper_4(s->window[w].alpha_val[1]);                     // 0.0
/*82  */             }                                                                    // 0.0
/*84  */             break;                                                               // 0.0
/*86  */         case 3:                                                                  // 0.0
/*88  */             if (w != 1 && w != 2) {                                              // 0.0
/*90  */                 DPRINT_ERROR("bad read offset 0x%08x\n", offset);                // 0.0
/*92  */                 return 0xBAADBAAD;                                               // 0.0
/*94  */             }                                                                    // 0.0
/*96  */             ret = s->window[w].osdsize;                                          // 0.0
/*98  */             break;                                                               // 0.0
/*100 */         }                                                                        // 0.0
/*102 */         return ret;                                                              // 0.0
/*104 */     case FIMD_VIDWADD0_START ... FIMD_VIDWADD0_END:                              // 0.0
/*106 */         w = (offset - FIMD_VIDWADD0_START) >> 3;                                 // 0.0
/*108 */         i = ((offset - FIMD_VIDWADD0_START) >> 2) & 1;                           // 0.0
/*110 */         return s->window[w].buf_start[i];                                        // 0.0
/*112 */     case FIMD_VIDWADD1_START ... FIMD_VIDWADD1_END:                              // 0.0
/*114 */         w = (offset - FIMD_VIDWADD1_START) >> 3;                                 // 0.0
/*116 */         i = ((offset - FIMD_VIDWADD1_START) >> 2) & 1;                           // 0.0
/*118 */         return s->window[w].buf_end[i];                                          // 0.0
/*120 */     case FIMD_VIDWADD2_START ... FIMD_VIDWADD2_END:                              // 0.0
/*122 */         w = (offset - FIMD_VIDWADD2_START) >> 2;                                 // 0.0
/*124 */         return s->window[w].virtpage_width | (s->window[w].virtpage_offsize <<   // 0.0
/*126 */             FIMD_VIDWADD2_OFFSIZE_SHIFT);                                        // 0.0
/*128 */     case FIMD_VIDINTCON0 ... FIMD_VIDINTCON1:                                    // 0.0
/*130 */         return s->vidintcon[(offset - FIMD_VIDINTCON0) >> 2];                    // 0.0
/*132 */     case FIMD_WKEYCON_START ... FIMD_WKEYCON_END:                                // 0.0
/*134 */         w = ((offset - FIMD_WKEYCON_START) >> 3) + 1;                            // 0.0
/*136 */         i = ((offset - FIMD_WKEYCON_START) >> 2) & 1;                            // 0.0
/*138 */         return s->window[w].keycon[i];                                           // 0.0
/*140 */     case FIMD_WKEYALPHA_START ... FIMD_WKEYALPHA_END:                            // 0.0
/*142 */         w = ((offset - FIMD_WKEYALPHA_START) >> 2) + 1;                          // 0.0
/*144 */         return s->window[w].keyalpha;                                            // 0.0
/*146 */     case FIMD_DITHMODE:                                                          // 0.0
/*148 */         return s->dithmode;                                                      // 0.0
/*150 */     case FIMD_WINMAP_START ... FIMD_WINMAP_END:                                  // 0.0
/*152 */         return s->window[(offset - FIMD_WINMAP_START) >> 2].winmap;              // 0.0
/*154 */     case FIMD_WPALCON_HIGH ... FIMD_WPALCON_LOW:                                 // 0.0
/*156 */         return s->wpalcon[(offset - FIMD_WPALCON_HIGH) >> 2];                    // 0.0
/*158 */     case FIMD_TRIGCON:                                                           // 0.0
/*160 */         return s->trigcon;                                                       // 0.0
/*162 */     case FIMD_I80IFCON_START ... FIMD_I80IFCON_END:                              // 0.0
/*164 */         return s->i80ifcon[(offset - FIMD_I80IFCON_START) >> 2];                 // 0.0
/*166 */     case FIMD_COLORGAINCON:                                                      // 0.0
/*168 */         return s->colorgaincon;                                                  // 0.0
/*170 */     case FIMD_LDI_CMDCON0 ... FIMD_LDI_CMDCON1:                                  // 0.0
/*172 */         return s->ldi_cmdcon[(offset - FIMD_LDI_CMDCON0) >> 2];                  // 0.0
/*174 */     case FIMD_SIFCCON0 ... FIMD_SIFCCON2:                                        // 0.0
/*176 */         i = (offset - FIMD_SIFCCON0) >> 2;                                       // 0.0
/*178 */         return s->sifccon[i];                                                    // 0.0
/*180 */     case FIMD_HUECOEFCR_START ... FIMD_HUECOEFCR_END:                            // 0.0
/*182 */         i = (offset - FIMD_HUECOEFCR_START) >> 2;                                // 0.0
/*184 */         return s->huecoef_cr[i];                                                 // 0.0
/*186 */     case FIMD_HUECOEFCB_START ... FIMD_HUECOEFCB_END:                            // 0.0
/*188 */         i = (offset - FIMD_HUECOEFCB_START) >> 2;                                // 0.0
/*190 */         return s->huecoef_cb[i];                                                 // 0.0
/*192 */     case FIMD_HUEOFFSET:                                                         // 0.0
/*194 */         return s->hueoffset;                                                     // 0.0
/*196 */     case FIMD_VIDWALPHA_START ... FIMD_VIDWALPHA_END:                            // 0.0
/*198 */         w = ((offset - FIMD_VIDWALPHA_START) >> 3);                              // 0.0
/*200 */         i = ((offset - FIMD_VIDWALPHA_START) >> 2) & 1;                          // 0.0
/*202 */         return s->window[w].alpha_val[i] &                                       // 0.0
/*204 */                 (w == 0 ? 0xFFFFFF : FIMD_VIDALPHA_ALPHA_LOWER);                 // 0.0
/*206 */     case FIMD_BLENDEQ_START ... FIMD_BLENDEQ_END:                                // 0.0
/*208 */         return s->window[(offset - FIMD_BLENDEQ_START) >> 2].blendeq;            // 0.0
/*210 */     case FIMD_BLENDCON:                                                          // 0.0
/*212 */         return s->blendcon;                                                      // 0.0
/*214 */     case FIMD_WRTQOSCON_START ... FIMD_WRTQOSCON_END:                            // 0.0
/*216 */         return s->window[(offset - FIMD_WRTQOSCON_START) >> 2].rtqoscon;         // 0.0
/*218 */     case FIMD_I80IFCMD_START ... FIMD_I80IFCMD_END:                              // 0.0
/*220 */         return s->i80ifcmd[(offset - FIMD_I80IFCMD_START) >> 2];                 // 0.0
/*222 */     case FIMD_VIDW0ADD0_B2 ... FIMD_VIDW4ADD0_B2:                                // 0.0
/*224 */         if (offset & 0x0004) {                                                   // 0.0
/*226 */             break;                                                               // 0.0
/*228 */         }                                                                        // 0.0
/*230 */         return s->window[(offset - FIMD_VIDW0ADD0_B2) >> 3].buf_start[2];        // 0.0
/*232 */     case FIMD_SHD_ADD0_START ... FIMD_SHD_ADD0_END:                              // 0.0
/*234 */         if (offset & 0x0004) {                                                   // 0.0
/*236 */             break;                                                               // 0.0
/*238 */         }                                                                        // 0.0
/*240 */         return s->window[(offset - FIMD_SHD_ADD0_START) >> 3].shadow_buf_start;  // 0.0
/*242 */     case FIMD_SHD_ADD1_START ... FIMD_SHD_ADD1_END:                              // 0.0
/*244 */         if (offset & 0x0004) {                                                   // 0.0
/*246 */             break;                                                               // 0.0
/*248 */         }                                                                        // 0.0
/*250 */         return s->window[(offset - FIMD_SHD_ADD1_START) >> 3].shadow_buf_end;    // 0.0
/*252 */     case FIMD_SHD_ADD2_START ... FIMD_SHD_ADD2_END:                              // 0.0
/*254 */         return s->window[(offset - FIMD_SHD_ADD2_START) >> 2].shadow_buf_size;   // 0.0
/*256 */     case FIMD_PAL_MEM_START ... FIMD_PAL_MEM_END:                                // 0.0
/*258 */         w = (offset - FIMD_PAL_MEM_START) >> 10;                                 // 0.0
/*260 */         i = ((offset - FIMD_PAL_MEM_START) >> 2) & 0xFF;                         // 0.0
/*262 */         return s->window[w].palette[i];                                          // 0.0
/*264 */     case FIMD_PALMEM_AL_START ... FIMD_PALMEM_AL_END:                            // 0.0
/*266 */         /* Palette aliases for win 0,1 */                                        // 0.0
/*268 */         w = (offset - FIMD_PALMEM_AL_START) >> 10;                               // 0.0
/*270 */         i = ((offset - FIMD_PALMEM_AL_START) >> 2) & 0xFF;                       // 0.0
/*272 */         return s->window[w].palette[i];                                          // 0.0
/*274 */     }                                                                            // 0.0
/*278 */     DPRINT_ERROR("bad read offset 0x%08x\n", offset);                            // 0.0
/*280 */     return 0xBAADBAAD;                                                           // 0.0
/*282 */ }                                                                                // 0.0
