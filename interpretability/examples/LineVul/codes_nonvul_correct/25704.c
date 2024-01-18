// commit message qemu@a8170e5e97 (target=0, prob=0.062379453, correct=True): Rename target_phys_addr_t to hwaddr
/*0   */ static uint32_t apic_mem_readl(void *opaque, target_phys_addr_t addr)  // (3) 0.05273
/*2   */ {                                                                      // (35) 0.001953
/*4   */     DeviceState *d;                                                    // (27) 0.01563
/*6   */     APICCommonState *s;                                                // (16) 0.01953
/*8   */     uint32_t val;                                                      // (19) 0.01758
/*10  */     int index;                                                         // (33) 0.01172
/*14  */     d = cpu_get_current_apic();                                        // (9) 0.02734
/*16  */     if (!d) {                                                          // (28) 0.01562
/*18  */         return 0;                                                      // (17) 0.01953
/*20  */     }                                                                  // (34) 0.007812
/*22  */     s = DO_UPCAST(APICCommonState, busdev.qdev, d);                    // (4) 0.04688
/*26  */     index = (addr >> 4) & 0xff;                                        // (10) 0.02734
/*28  */     switch(index) {                                                    // (29) 0.01562
/*30  */     case 0x02: /* id */                                                // (12) 0.02148
/*32  */         val = s->id << 24;                                             // (8) 0.0293
/*34  */         break;                                                         // (20) 0.01758
/*36  */     case 0x03: /* version */                                           // (13) 0.02148
/*38  */         val = 0x11 | ((APIC_LVT_NB - 1) << 16); /* version 0x11 */     // (1) 0.06445
/*40  */         break;                                                         // (21) 0.01758
/*42  */     case 0x08:                                                         // (30) 0.01562
/*44  */         apic_sync_vapic(s, SYNC_FROM_VAPIC);                           // (2) 0.05469
/*46  */         if (apic_report_tpr_access) {                                  // (6) 0.03906
/*48  */             cpu_report_tpr_access(s->cpu_env, TPR_ACCESS_READ);        // (0) 0.06641
/*50  */         }                                                              // (31) 0.01562
/*52  */         val = s->tpr;                                                  // (11) 0.02734
/*54  */         break;                                                         // (22) 0.01758
/*56  */     case 0x09:                                                         // (32) 0.01562
/*58  */         val = apic_get_arb_pri(s);                                     // (5) 0.03906
/*60  */         break;                                                         // (18) 0.01758
/*62  */     case 0x0a:                                                         // (23) 0.01758
/*64  */         /* ppr */                                                      // (14) 0.02148
/*66  */         val = apic_get_ppr(s);                                         // (7) 0.03711
/*68  */         break;                                                         // (24) 0.01758
/*70  */     case 0x0b:                                                         // (25) 0.01758
/*72  */         val = 0;                                                       // (15) 0.02148
/*74  */         break;                                                         // (26) 0.01758
/*76  */     case 0x0d:                                                         // 0.0
/*78  */         val = s->log_dest << 24;                                       // 0.0
/*80  */         break;                                                         // 0.0
/*82  */     case 0x0e:                                                         // 0.0
/*84  */         val = s->dest_mode << 28;                                      // 0.0
/*86  */         break;                                                         // 0.0
/*88  */     case 0x0f:                                                         // 0.0
/*90  */         val = s->spurious_vec;                                         // 0.0
/*92  */         break;                                                         // 0.0
/*94  */     case 0x10 ... 0x17:                                                // 0.0
/*96  */         val = s->isr[index & 7];                                       // 0.0
/*98  */         break;                                                         // 0.0
/*100 */     case 0x18 ... 0x1f:                                                // 0.0
/*102 */         val = s->tmr[index & 7];                                       // 0.0
/*104 */         break;                                                         // 0.0
/*106 */     case 0x20 ... 0x27:                                                // 0.0
/*108 */         val = s->irr[index & 7];                                       // 0.0
/*110 */         break;                                                         // 0.0
/*112 */     case 0x28:                                                         // 0.0
/*114 */         val = s->esr;                                                  // 0.0
/*116 */         break;                                                         // 0.0
/*118 */     case 0x30:                                                         // 0.0
/*120 */     case 0x31:                                                         // 0.0
/*122 */         val = s->icr[index & 1];                                       // 0.0
/*124 */         break;                                                         // 0.0
/*126 */     case 0x32 ... 0x37:                                                // 0.0
/*128 */         val = s->lvt[index - 0x32];                                    // 0.0
/*130 */         break;                                                         // 0.0
/*132 */     case 0x38:                                                         // 0.0
/*134 */         val = s->initial_count;                                        // 0.0
/*136 */         break;                                                         // 0.0
/*138 */     case 0x39:                                                         // 0.0
/*140 */         val = apic_get_current_count(s);                               // 0.0
/*142 */         break;                                                         // 0.0
/*144 */     case 0x3e:                                                         // 0.0
/*146 */         val = s->divide_conf;                                          // 0.0
/*148 */         break;                                                         // 0.0
/*150 */     default:                                                           // 0.0
/*152 */         s->esr |= ESR_ILLEGAL_ADDRESS;                                 // 0.0
/*154 */         val = 0;                                                       // 0.0
/*156 */         break;                                                         // 0.0
/*158 */     }                                                                  // 0.0
/*160 */     trace_apic_mem_readl(addr, val);                                   // 0.0
/*162 */     return val;                                                        // 0.0
/*164 */ }                                                                      // 0.0
