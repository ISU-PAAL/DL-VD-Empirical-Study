// commit message qemu@a8170e5e97 (target=0, prob=0.013639067, correct=True): Rename target_phys_addr_t to hwaddr
/*0   */ static void exynos4210_combiner_write(void *opaque, target_phys_addr_t offset,    // (7) 0.05273
/*2   */         uint64_t val, unsigned size)                                              // (14) 0.03125
/*4   */ {                                                                                 // (22) 0.001953
/*6   */     struct Exynos4210CombinerState *s =                                           // (15) 0.0293
/*8   */             (struct Exynos4210CombinerState *)opaque;                             // (8) 0.04883
/*10  */     uint32_t req_quad_base_n;    /* Base of registers quad. Multiply it by 4 and  // (2) 0.06055
/*12  */                                    get a start of corresponding group quad */     // (0) 0.08203
/*14  */     uint32_t grp_quad_base_n;    /* Base of group quad */                         // (9) 0.04883
/*16  */     uint32_t reg_n;              /* Register number inside the quad */            // (1) 0.06055
/*20  */     req_quad_base_n = offset >> 4;                                                // (16) 0.0293
/*22  */     grp_quad_base_n = req_quad_base_n << 2;                                       // (11) 0.04297
/*24  */     reg_n = (offset - (req_quad_base_n << 4)) >> 2;                               // (10) 0.04688
/*28  */     if (req_quad_base_n >= IIC_NGRP) {                                            // (12) 0.03906
/*30  */         hw_error("exynos4210.combiner: unallowed write access at offset 0x"       // (4) 0.05859
/*32  */                 TARGET_FMT_plx "\n", offset);                                     // (6) 0.05469
/*34  */         return;                                                                   // (18) 0.01758
/*36  */     }                                                                             // (20) 0.007812
/*40  */     if (reg_n > 1) {                                                              // (17) 0.02344
/*42  */         hw_error("exynos4210.combiner: unallowed write access at offset 0x"       // (3) 0.05859
/*44  */                 TARGET_FMT_plx "\n", offset);                                     // (5) 0.05469
/*46  */         return;                                                                   // (19) 0.01758
/*48  */     }                                                                             // (21) 0.007812
/*52  */     if (offset >> 2 >= IIC_REGSET_SIZE) {                                         // (13) 0.03711
/*54  */         hw_error("exynos4210.combiner: overflow of reg_set by 0x"                 // 0.0
/*56  */                 TARGET_FMT_plx "offset\n", offset);                               // 0.0
/*58  */     }                                                                             // 0.0
/*60  */     s->reg_set[offset >> 2] = val;                                                // 0.0
/*64  */     switch (reg_n) {                                                              // 0.0
/*66  */     /* IIESR */                                                                   // 0.0
/*68  */     case 0:                                                                       // 0.0
/*70  */         /* FIXME: what if irq is pending, allowed by mask, and we allow it        // 0.0
/*72  */          * again. Interrupt will rise again! */                                   // 0.0
/*76  */         DPRINTF("%s enable IRQ for groups %d, %d, %d, %d\n",                      // 0.0
/*78  */                 s->external ? "EXT" : "INT",                                      // 0.0
/*80  */                 grp_quad_base_n,                                                  // 0.0
/*82  */                 grp_quad_base_n + 1,                                              // 0.0
/*84  */                 grp_quad_base_n + 2,                                              // 0.0
/*86  */                 grp_quad_base_n + 3);                                             // 0.0
/*90  */         /* Enable interrupt sources */                                            // 0.0
/*92  */         s->group[grp_quad_base_n].src_mask |= val & 0xFF;                         // 0.0
/*94  */         s->group[grp_quad_base_n + 1].src_mask |= (val & 0xFF00) >> 8;            // 0.0
/*96  */         s->group[grp_quad_base_n + 2].src_mask |= (val & 0xFF0000) >> 16;         // 0.0
/*98  */         s->group[grp_quad_base_n + 3].src_mask |= (val & 0xFF000000) >> 24;       // 0.0
/*102 */         exynos4210_combiner_update(s, grp_quad_base_n);                           // 0.0
/*104 */         exynos4210_combiner_update(s, grp_quad_base_n + 1);                       // 0.0
/*106 */         exynos4210_combiner_update(s, grp_quad_base_n + 2);                       // 0.0
/*108 */         exynos4210_combiner_update(s, grp_quad_base_n + 3);                       // 0.0
/*110 */         break;                                                                    // 0.0
/*112 */         /* IIECR */                                                               // 0.0
/*114 */     case 1:                                                                       // 0.0
/*116 */         DPRINTF("%s disable IRQ for groups %d, %d, %d, %d\n",                     // 0.0
/*118 */                 s->external ? "EXT" : "INT",                                      // 0.0
/*120 */                 grp_quad_base_n,                                                  // 0.0
/*122 */                 grp_quad_base_n + 1,                                              // 0.0
/*124 */                 grp_quad_base_n + 2,                                              // 0.0
/*126 */                 grp_quad_base_n + 3);                                             // 0.0
/*130 */         /* Disable interrupt sources */                                           // 0.0
/*132 */         s->group[grp_quad_base_n].src_mask &= ~(val & 0xFF);                      // 0.0
/*134 */         s->group[grp_quad_base_n + 1].src_mask &= ~((val & 0xFF00) >> 8);         // 0.0
/*136 */         s->group[grp_quad_base_n + 2].src_mask &= ~((val & 0xFF0000) >> 16);      // 0.0
/*138 */         s->group[grp_quad_base_n + 3].src_mask &= ~((val & 0xFF000000) >> 24);    // 0.0
/*142 */         exynos4210_combiner_update(s, grp_quad_base_n);                           // 0.0
/*144 */         exynos4210_combiner_update(s, grp_quad_base_n + 1);                       // 0.0
/*146 */         exynos4210_combiner_update(s, grp_quad_base_n + 2);                       // 0.0
/*148 */         exynos4210_combiner_update(s, grp_quad_base_n + 3);                       // 0.0
/*150 */         break;                                                                    // 0.0
/*152 */     default:                                                                      // 0.0
/*154 */         hw_error("exynos4210.combiner: unallowed write access at offset 0x"       // 0.0
/*156 */                 TARGET_FMT_plx "\n", offset);                                     // 0.0
/*158 */         break;                                                                    // 0.0
/*160 */     }                                                                             // 0.0
/*162 */ }                                                                                 // 0.0
