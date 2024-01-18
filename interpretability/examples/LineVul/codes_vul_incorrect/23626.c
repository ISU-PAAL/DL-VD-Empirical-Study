// commit message qemu@4abf12f4ea (target=1, prob=0.20778713, correct=False): rtl8139: Fix invalid IO access alignment
/*0   */ static void rtl8139_io_writeb(void *opaque, uint8_t addr, uint32_t val)             // (0) 0.05664
/*2   */ {                                                                                   // (29) 0.001953
/*4   */     RTL8139State *s = opaque;                                                       // (13) 0.02539
/*8   */     addr &= 0xff;                                                                   // (26) 0.01758
/*12  */     switch (addr)                                                                   // (27) 0.01367
/*14  */     {                                                                               // (28) 0.007812
/*16  */         case MAC0 ... MAC0+5:                                                       // (10) 0.03125
/*18  */             s->phys[addr - MAC0] = val;                                             // (7) 0.04492
/*20  */             break;                                                                  // (14) 0.02539
/*22  */         case MAC0+6 ... MAC0+7:                                                     // (9) 0.03516
/*24  */             /* reserved */                                                          // (12) 0.02734
/*26  */             break;                                                                  // (15) 0.02539
/*28  */         case MAR0 ... MAR0+7:                                                       // (11) 0.03125
/*30  */             s->mult[addr - MAR0] = val;                                             // (8) 0.04492
/*32  */             break;                                                                  // (16) 0.02539
/*34  */         case ChipCmd:                                                               // (23) 0.02148
/*36  */             rtl8139_ChipCmd_write(s, val);                                          // (3) 0.04883
/*38  */             break;                                                                  // (17) 0.02539
/*40  */         case Cfg9346:                                                               // (18) 0.02539
/*42  */             rtl8139_Cfg9346_write(s, val);                                          // (1) 0.05273
/*44  */             break;                                                                  // (19) 0.02539
/*46  */         case TxConfig: /* windows driver sometimes writes using byte-lenth call */  // (6) 0.04688
/*48  */             rtl8139_TxConfig_writeb(s, val);                                        // (2) 0.05078
/*50  */             break;                                                                  // (20) 0.02539
/*52  */         case Config0:                                                               // (24) 0.02148
/*54  */             rtl8139_Config0_write(s, val);                                          // (4) 0.04883
/*56  */             break;                                                                  // (21) 0.02539
/*58  */         case Config1:                                                               // (25) 0.02148
/*60  */             rtl8139_Config1_write(s, val);                                          // (5) 0.04883
/*62  */             break;                                                                  // (22) 0.02539
/*64  */         case Config3:                                                               // 0.0
/*66  */             rtl8139_Config3_write(s, val);                                          // 0.0
/*68  */             break;                                                                  // 0.0
/*70  */         case Config4:                                                               // 0.0
/*72  */             rtl8139_Config4_write(s, val);                                          // 0.0
/*74  */             break;                                                                  // 0.0
/*76  */         case Config5:                                                               // 0.0
/*78  */             rtl8139_Config5_write(s, val);                                          // 0.0
/*80  */             break;                                                                  // 0.0
/*82  */         case MediaStatus:                                                           // 0.0
/*84  */             /* ignore */                                                            // 0.0
/*86  */             DPRINTF("not implemented write(b) to MediaStatus val=0x%02x\n",         // 0.0
/*88  */                 val);                                                               // 0.0
/*90  */             break;                                                                  // 0.0
/*94  */         case HltClk:                                                                // 0.0
/*96  */             DPRINTF("HltClk write val=0x%08x\n", val);                              // 0.0
/*98  */             if (val == 'R')                                                         // 0.0
/*100 */             {                                                                       // 0.0
/*102 */                 s->clock_enabled = 1;                                               // 0.0
/*104 */             }                                                                       // 0.0
/*106 */             else if (val == 'H')                                                    // 0.0
/*108 */             {                                                                       // 0.0
/*110 */                 s->clock_enabled = 0;                                               // 0.0
/*112 */             }                                                                       // 0.0
/*114 */             break;                                                                  // 0.0
/*118 */         case TxThresh:                                                              // 0.0
/*120 */             DPRINTF("C+ TxThresh write(b) val=0x%02x\n", val);                      // 0.0
/*122 */             s->TxThresh = val;                                                      // 0.0
/*124 */             break;                                                                  // 0.0
/*128 */         case TxPoll:                                                                // 0.0
/*130 */             DPRINTF("C+ TxPoll write(b) val=0x%02x\n", val);                        // 0.0
/*132 */             if (val & (1 << 7))                                                     // 0.0
/*134 */             {                                                                       // 0.0
/*136 */                 DPRINTF("C+ TxPoll high priority transmission (not "                // 0.0
/*138 */                     "implemented)\n");                                              // 0.0
/*140 */                 //rtl8139_cplus_transmit(s);                                        // 0.0
/*142 */             }                                                                       // 0.0
/*144 */             if (val & (1 << 6))                                                     // 0.0
/*146 */             {                                                                       // 0.0
/*148 */                 DPRINTF("C+ TxPoll normal priority transmission\n");                // 0.0
/*150 */                 rtl8139_cplus_transmit(s);                                          // 0.0
/*152 */             }                                                                       // 0.0
/*156 */             break;                                                                  // 0.0
/*160 */         default:                                                                    // 0.0
/*162 */             DPRINTF("not implemented write(b) addr=0x%x val=0x%02x\n", addr,        // 0.0
/*164 */                 val);                                                               // 0.0
/*166 */             break;                                                                  // 0.0
/*168 */     }                                                                               // 0.0
/*170 */ }                                                                                   // 0.0
