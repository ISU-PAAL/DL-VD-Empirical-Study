// commit message qemu@a8170e5e97 (target=0, prob=0.007416039, correct=True): Rename target_phys_addr_t to hwaddr
/*0   */ static uint64_t exynos4210_mct_read(void *opaque, target_phys_addr_t offset,    // (2) 0.05859
/*2   */         unsigned size)                                                          // (15) 0.01953
/*4   */ {                                                                               // (28) 0.001953
/*6   */     Exynos4210MCTState *s = (Exynos4210MCTState *)opaque;                       // (4) 0.05273
/*8   */     int index;                                                                  // (25) 0.01172
/*10  */     int shift;                                                                  // (26) 0.01172
/*12  */     uint64_t count;                                                             // (18) 0.01758
/*14  */     uint32_t value;                                                             // (19) 0.01758
/*16  */     int lt_i;                                                                   // (17) 0.01758
/*20  */     switch (offset) {                                                           // (24) 0.01563
/*24  */     case MCT_CFG:                                                               // (16) 0.01953
/*26  */         value = s->reg_mct_cfg;                                                 // (10) 0.03516
/*28  */         break;                                                                  // (20) 0.01758
/*32  */     case G_CNT_L: case G_CNT_U:                                                 // (9) 0.03711
/*34  */         shift = 8 * (offset & 0x4);                                             // (11) 0.03516
/*36  */         count = exynos4210_gfrc_get_count(&s->g_timer);                         // (3) 0.05664
/*38  */         value = UINT32_MAX & (count >> shift);                                  // (8) 0.03906
/*40  */         DPRINTF("read FRC=0x%llx\n", count);                                    // (6) 0.04883
/*42  */         break;                                                                  // (21) 0.01758
/*46  */     case G_CNT_WSTAT:                                                           // (14) 0.02344
/*48  */         value = s->g_timer.reg.cnt_wstat;                                       // (7) 0.04492
/*50  */         break;                                                                  // (22) 0.01758
/*54  */     case G_COMP_L(0): case G_COMP_L(1): case G_COMP_L(2): case G_COMP_L(3):     // (0) 0.08398
/*56  */     case G_COMP_U(0): case G_COMP_U(1): case G_COMP_U(2): case G_COMP_U(3):     // (1) 0.08398
/*58  */     index = GET_G_COMP_IDX(offset);                                             // (12) 0.0332
/*60  */     shift = 8 * (offset & 0x4);                                                 // (13) 0.02734
/*62  */     value = UINT32_MAX & (s->g_timer.reg.comp[index] >> shift);                 // (5) 0.05273
/*64  */     break;                                                                      // (27) 0.009766
/*68  */     case G_TCON:                                                                // (23) 0.01758
/*70  */         value = s->g_timer.reg.tcon;                                            // 0.0
/*72  */         break;                                                                  // 0.0
/*76  */     case G_INT_CSTAT:                                                           // 0.0
/*78  */         value = s->g_timer.reg.int_cstat;                                       // 0.0
/*80  */         break;                                                                  // 0.0
/*84  */     case G_INT_ENB:                                                             // 0.0
/*86  */         value = s->g_timer.reg.int_enb;                                         // 0.0
/*88  */         break;                                                                  // 0.0
/*90  */         break;                                                                  // 0.0
/*92  */     case G_WSTAT:                                                               // 0.0
/*94  */         value = s->g_timer.reg.wstat;                                           // 0.0
/*96  */         break;                                                                  // 0.0
/*100 */     case G_COMP0_ADD_INCR: case G_COMP1_ADD_INCR:                               // 0.0
/*102 */     case G_COMP2_ADD_INCR: case G_COMP3_ADD_INCR:                               // 0.0
/*104 */         value = s->g_timer.reg.comp_add_incr[GET_G_COMP_ADD_INCR_IDX(offset)];  // 0.0
/*106 */         break;                                                                  // 0.0
/*110 */         /* Local timers */                                                      // 0.0
/*112 */     case L0_TCNTB: case L0_ICNTB: case L0_FRCNTB:                               // 0.0
/*114 */     case L1_TCNTB: case L1_ICNTB: case L1_FRCNTB:                               // 0.0
/*116 */         lt_i = GET_L_TIMER_IDX(offset);                                         // 0.0
/*118 */         index = GET_L_TIMER_CNT_REG_IDX(offset, lt_i);                          // 0.0
/*120 */         value = s->l_timer[lt_i].reg.cnt[index];                                // 0.0
/*122 */         break;                                                                  // 0.0
/*126 */     case L0_TCNTO: case L1_TCNTO:                                               // 0.0
/*128 */         lt_i = GET_L_TIMER_IDX(offset);                                         // 0.0
/*132 */         value = exynos4210_ltick_cnt_get_cnto(&s->l_timer[lt_i].tick_timer);    // 0.0
/*134 */         DPRINTF("local timer[%d] read TCNTO %x\n", lt_i, value);                // 0.0
/*136 */         break;                                                                  // 0.0
/*140 */     case L0_ICNTO: case L1_ICNTO:                                               // 0.0
/*142 */         lt_i = GET_L_TIMER_IDX(offset);                                         // 0.0
/*146 */         value = exynos4210_ltick_int_get_cnto(&s->l_timer[lt_i].tick_timer);    // 0.0
/*148 */         DPRINTF("local timer[%d] read ICNTO %x\n", lt_i, value);                // 0.0
/*150 */         break;                                                                  // 0.0
/*154 */     case L0_FRCNTO: case L1_FRCNTO:                                             // 0.0
/*156 */         lt_i = GET_L_TIMER_IDX(offset);                                         // 0.0
/*160 */         value = exynos4210_lfrc_get_count(&s->l_timer[lt_i]);                   // 0.0
/*164 */         break;                                                                  // 0.0
/*168 */     case L0_TCON: case L1_TCON:                                                 // 0.0
/*170 */         lt_i = ((offset & 0xF00) - L0_TCNTB) / 0x100;                           // 0.0
/*172 */         value = s->l_timer[lt_i].reg.tcon;                                      // 0.0
/*174 */         break;                                                                  // 0.0
/*178 */     case L0_INT_CSTAT: case L1_INT_CSTAT:                                       // 0.0
/*180 */         lt_i = ((offset & 0xF00) - L0_TCNTB) / 0x100;                           // 0.0
/*182 */         value = s->l_timer[lt_i].reg.int_cstat;                                 // 0.0
/*184 */         break;                                                                  // 0.0
/*188 */     case L0_INT_ENB: case L1_INT_ENB:                                           // 0.0
/*190 */         lt_i = ((offset & 0xF00) - L0_TCNTB) / 0x100;                           // 0.0
/*192 */         value = s->l_timer[lt_i].reg.int_enb;                                   // 0.0
/*194 */         break;                                                                  // 0.0
/*198 */     case L0_WSTAT: case L1_WSTAT:                                               // 0.0
/*200 */         lt_i = ((offset & 0xF00) - L0_TCNTB) / 0x100;                           // 0.0
/*202 */         value = s->l_timer[lt_i].reg.wstat;                                     // 0.0
/*204 */         break;                                                                  // 0.0
/*208 */     default:                                                                    // 0.0
/*210 */         hw_error("exynos4210.mct: bad read offset "                             // 0.0
/*212 */                 TARGET_FMT_plx "\n", offset);                                   // 0.0
/*214 */         break;                                                                  // 0.0
/*216 */     }                                                                           // 0.0
/*218 */     return value;                                                               // 0.0
/*220 */ }                                                                               // 0.0
