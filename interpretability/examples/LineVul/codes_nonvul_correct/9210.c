// commit message qemu@679aa175e8 (target=0, prob=0.35486543, correct=True): hw/intc/arm_gic: Make ICDDCR/GICD_CTLR banked
/*0   */ static uint32_t gic_dist_readb(void *opaque, hwaddr offset, MemTxAttrs attrs)  // (2) 0.05859
/*2   */ {                                                                              // (27) 0.001953
/*4   */     GICState *s = (GICState *)opaque;                                          // (9) 0.0332
/*6   */     uint32_t res;                                                              // (21) 0.01758
/*8   */     int irq;                                                                   // (22) 0.01367
/*10  */     int i;                                                                     // (24) 0.01172
/*12  */     int cpu;                                                                   // (25) 0.01172
/*14  */     int cm;                                                                    // (26) 0.01172
/*16  */     int mask;                                                                  // (23) 0.01172
/*20  */     cpu = gic_get_current_cpu(s);                                              // (10) 0.03125
/*22  */     cm = 1 << cpu;                                                             // (20) 0.01758
/*24  */     if (offset < 0x100) {                                                      // (19) 0.02344
/*26  */         if (offset == 0)                                                       // (16) 0.02539
/*28  */             return s->enabled;                                                 // (11) 0.03125
/*30  */         if (offset == 4)                                                       // (17) 0.02539
/*32  */             /* Interrupt Controller Type Register */                           // (8) 0.03516
/*34  */             return ((s->num_irq / 32) - 1)                                     // (6) 0.04883
/*36  */                     | ((NUM_CPU(s) - 1) << 5)                                  // (1) 0.06445
/*38  */                     | (s->security_extn << 10);                                // (3) 0.05859
/*40  */         if (offset < 0x08)                                                     // (13) 0.0293
/*42  */             return 0;                                                          // (15) 0.02734
/*44  */         if (offset >= 0x80) {                                                  // (12) 0.03125
/*46  */             /* Interrupt Group Registers: these RAZ/WI if this is an NS        // (4) 0.05469
/*48  */              * access to a GIC with the security extensions, or if the GIC     // (5) 0.05469
/*50  */              * doesn't have groups at all.                                     // (7) 0.03906
/*52  */              */                                                                // (18) 0.02539
/*54  */             res = 0;                                                           // (14) 0.0293
/*56  */             if (!(s->security_extn && !attrs.secure) && gic_has_groups(s)) {   // (0) 0.07422
/*58  */                 /* Every byte offset holds 8 group status bits */              // 0.0
/*60  */                 irq = (offset - 0x080) * 8 + GIC_BASE_IRQ;                     // 0.0
/*62  */                 if (irq >= s->num_irq) {                                       // 0.0
/*64  */                     goto bad_reg;                                              // 0.0
/*66  */                 }                                                              // 0.0
/*68  */                 for (i = 0; i < 8; i++) {                                      // 0.0
/*70  */                     if (GIC_TEST_GROUP(irq + i, cm)) {                         // 0.0
/*72  */                         res |= (1 << i);                                       // 0.0
/*74  */                     }                                                          // 0.0
/*76  */                 }                                                              // 0.0
/*78  */             }                                                                  // 0.0
/*80  */             return res;                                                        // 0.0
/*82  */         }                                                                      // 0.0
/*84  */         goto bad_reg;                                                          // 0.0
/*86  */     } else if (offset < 0x200) {                                               // 0.0
/*88  */         /* Interrupt Set/Clear Enable.  */                                     // 0.0
/*90  */         if (offset < 0x180)                                                    // 0.0
/*92  */             irq = (offset - 0x100) * 8;                                        // 0.0
/*94  */         else                                                                   // 0.0
/*96  */             irq = (offset - 0x180) * 8;                                        // 0.0
/*98  */         irq += GIC_BASE_IRQ;                                                   // 0.0
/*100 */         if (irq >= s->num_irq)                                                 // 0.0
/*102 */             goto bad_reg;                                                      // 0.0
/*104 */         res = 0;                                                               // 0.0
/*106 */         for (i = 0; i < 8; i++) {                                              // 0.0
/*108 */             if (GIC_TEST_ENABLED(irq + i, cm)) {                               // 0.0
/*110 */                 res |= (1 << i);                                               // 0.0
/*112 */             }                                                                  // 0.0
/*114 */         }                                                                      // 0.0
/*116 */     } else if (offset < 0x300) {                                               // 0.0
/*118 */         /* Interrupt Set/Clear Pending.  */                                    // 0.0
/*120 */         if (offset < 0x280)                                                    // 0.0
/*122 */             irq = (offset - 0x200) * 8;                                        // 0.0
/*124 */         else                                                                   // 0.0
/*126 */             irq = (offset - 0x280) * 8;                                        // 0.0
/*128 */         irq += GIC_BASE_IRQ;                                                   // 0.0
/*130 */         if (irq >= s->num_irq)                                                 // 0.0
/*132 */             goto bad_reg;                                                      // 0.0
/*134 */         res = 0;                                                               // 0.0
/*136 */         mask = (irq < GIC_INTERNAL) ?  cm : ALL_CPU_MASK;                      // 0.0
/*138 */         for (i = 0; i < 8; i++) {                                              // 0.0
/*140 */             if (gic_test_pending(s, irq + i, mask)) {                          // 0.0
/*142 */                 res |= (1 << i);                                               // 0.0
/*144 */             }                                                                  // 0.0
/*146 */         }                                                                      // 0.0
/*148 */     } else if (offset < 0x400) {                                               // 0.0
/*150 */         /* Interrupt Active.  */                                               // 0.0
/*152 */         irq = (offset - 0x300) * 8 + GIC_BASE_IRQ;                             // 0.0
/*154 */         if (irq >= s->num_irq)                                                 // 0.0
/*156 */             goto bad_reg;                                                      // 0.0
/*158 */         res = 0;                                                               // 0.0
/*160 */         mask = (irq < GIC_INTERNAL) ?  cm : ALL_CPU_MASK;                      // 0.0
/*162 */         for (i = 0; i < 8; i++) {                                              // 0.0
/*164 */             if (GIC_TEST_ACTIVE(irq + i, mask)) {                              // 0.0
/*166 */                 res |= (1 << i);                                               // 0.0
/*168 */             }                                                                  // 0.0
/*170 */         }                                                                      // 0.0
/*172 */     } else if (offset < 0x800) {                                               // 0.0
/*174 */         /* Interrupt Priority.  */                                             // 0.0
/*176 */         irq = (offset - 0x400) + GIC_BASE_IRQ;                                 // 0.0
/*178 */         if (irq >= s->num_irq)                                                 // 0.0
/*180 */             goto bad_reg;                                                      // 0.0
/*182 */         res = GIC_GET_PRIORITY(irq, cpu);                                      // 0.0
/*184 */     } else if (offset < 0xc00) {                                               // 0.0
/*186 */         /* Interrupt CPU Target.  */                                           // 0.0
/*188 */         if (s->num_cpu == 1 && s->revision != REV_11MPCORE) {                  // 0.0
/*190 */             /* For uniprocessor GICs these RAZ/WI */                           // 0.0
/*192 */             res = 0;                                                           // 0.0
/*194 */         } else {                                                               // 0.0
/*196 */             irq = (offset - 0x800) + GIC_BASE_IRQ;                             // 0.0
/*198 */             if (irq >= s->num_irq) {                                           // 0.0
/*200 */                 goto bad_reg;                                                  // 0.0
/*202 */             }                                                                  // 0.0
/*204 */             if (irq >= 29 && irq <= 31) {                                      // 0.0
/*206 */                 res = cm;                                                      // 0.0
/*208 */             } else {                                                           // 0.0
/*210 */                 res = GIC_TARGET(irq);                                         // 0.0
/*212 */             }                                                                  // 0.0
/*214 */         }                                                                      // 0.0
/*216 */     } else if (offset < 0xf00) {                                               // 0.0
/*218 */         /* Interrupt Configuration.  */                                        // 0.0
/*220 */         irq = (offset - 0xc00) * 4 + GIC_BASE_IRQ;                             // 0.0
/*222 */         if (irq >= s->num_irq)                                                 // 0.0
/*224 */             goto bad_reg;                                                      // 0.0
/*226 */         res = 0;                                                               // 0.0
/*228 */         for (i = 0; i < 4; i++) {                                              // 0.0
/*230 */             if (GIC_TEST_MODEL(irq + i))                                       // 0.0
/*232 */                 res |= (1 << (i * 2));                                         // 0.0
/*234 */             if (GIC_TEST_EDGE_TRIGGER(irq + i))                                // 0.0
/*236 */                 res |= (2 << (i * 2));                                         // 0.0
/*238 */         }                                                                      // 0.0
/*240 */     } else if (offset < 0xf10) {                                               // 0.0
/*242 */         goto bad_reg;                                                          // 0.0
/*244 */     } else if (offset < 0xf30) {                                               // 0.0
/*246 */         if (s->revision == REV_11MPCORE || s->revision == REV_NVIC) {          // 0.0
/*248 */             goto bad_reg;                                                      // 0.0
/*250 */         }                                                                      // 0.0
/*254 */         if (offset < 0xf20) {                                                  // 0.0
/*256 */             /* GICD_CPENDSGIRn */                                              // 0.0
/*258 */             irq = (offset - 0xf10);                                            // 0.0
/*260 */         } else {                                                               // 0.0
/*262 */             irq = (offset - 0xf20);                                            // 0.0
/*264 */             /* GICD_SPENDSGIRn */                                              // 0.0
/*266 */         }                                                                      // 0.0
/*270 */         res = s->sgi_pending[irq][cpu];                                        // 0.0
/*272 */     } else if (offset < 0xfe0) {                                               // 0.0
/*274 */         goto bad_reg;                                                          // 0.0
/*276 */     } else /* offset >= 0xfe0 */ {                                             // 0.0
/*278 */         if (offset & 3) {                                                      // 0.0
/*280 */             res = 0;                                                           // 0.0
/*282 */         } else {                                                               // 0.0
/*284 */             res = gic_id[(offset - 0xfe0) >> 2];                               // 0.0
/*286 */         }                                                                      // 0.0
/*288 */     }                                                                          // 0.0
/*290 */     return res;                                                                // 0.0
/*292 */ bad_reg:                                                                       // 0.0
/*294 */     qemu_log_mask(LOG_GUEST_ERROR,                                             // 0.0
/*296 */                   "gic_dist_readb: Bad offset %x\n", (int)offset);             // 0.0
/*298 */     return 0;                                                                  // 0.0
/*300 */ }                                                                              // 0.0
