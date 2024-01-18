// commit message qemu@35c648078a (target=0, prob=0.5687671, correct=False): mips_malta: generate SMBUS EEPROM data
/*0   */ static void malta_fpga_write(void *opaque, hwaddr addr,                         // (3) 0.03906
/*2   */                              uint64_t val, unsigned size)                       // (0) 0.07227
/*4   */ {                                                                               // (36) 0.001953
/*6   */     MaltaFPGAState *s = opaque;                                                 // (10) 0.02344
/*8   */     uint32_t saddr;                                                             // (11) 0.01953
/*12  */     saddr = (addr & 0xfffff);                                                   // (8) 0.02734
/*16  */     switch (saddr) {                                                            // (15) 0.01758
/*20  */     /* SWITCH Register */                                                       // (35) 0.01562
/*22  */     case 0x00200:                                                               // (16) 0.01758
/*24  */         break;                                                                  // (17) 0.01758
/*28  */     /* JMPRS Register */                                                        // (14) 0.01758
/*30  */     case 0x00210:                                                               // (18) 0.01758
/*32  */         break;                                                                  // (19) 0.01758
/*36  */     /* LEDBAR Register */                                                       // (13) 0.01758
/*38  */     case 0x00408:                                                               // (20) 0.01758
/*40  */         s->leds = val & 0xff;                                                   // (7) 0.0332
/*42  */         malta_fpga_update_display(s);                                           // (4) 0.03711
/*44  */         break;                                                                  // (21) 0.01758
/*48  */     /* ASCIIWORD Register */                                                    // (22) 0.01758
/*50  */     case 0x00410:                                                               // (23) 0.01758
/*52  */         snprintf(s->display_text, 9, "%08X", (uint32_t)val);                    // (2) 0.05859
/*54  */         malta_fpga_update_display(s);                                           // (6) 0.03711
/*56  */         break;                                                                  // (24) 0.01758
/*60  */     /* ASCIIPOS0 to ASCIIPOS7 Registers */                                      // (9) 0.02734
/*62  */     case 0x00418:                                                               // (25) 0.01758
/*64  */     case 0x00420:                                                               // (26) 0.01758
/*66  */     case 0x00428:                                                               // (27) 0.01758
/*68  */     case 0x00430:                                                               // (28) 0.01758
/*70  */     case 0x00438:                                                               // (29) 0.01758
/*72  */     case 0x00440:                                                               // (30) 0.01758
/*74  */     case 0x00448:                                                               // (31) 0.01758
/*76  */     case 0x00450:                                                               // (32) 0.01758
/*78  */         s->display_text[(saddr - 0x00418) >> 3] = (char) val;                   // (1) 0.06055
/*80  */         malta_fpga_update_display(s);                                           // (5) 0.03711
/*82  */         break;                                                                  // (33) 0.01758
/*86  */     /* SOFTRES Register */                                                      // (12) 0.01953
/*88  */     case 0x00500:                                                               // (34) 0.01758
/*90  */         if (val == 0x42)                                                        // 0.0
/*92  */             qemu_system_reset_request ();                                       // 0.0
/*94  */         break;                                                                  // 0.0
/*98  */     /* BRKRES Register */                                                       // 0.0
/*100 */     case 0x00508:                                                               // 0.0
/*102 */         s->brk = val & 0xff;                                                    // 0.0
/*104 */         break;                                                                  // 0.0
/*108 */     /* UART Registers are handled directly by the serial device */              // 0.0
/*112 */     /* GPOUT Register */                                                        // 0.0
/*114 */     case 0x00a00:                                                               // 0.0
/*116 */         s->gpout = val & 0xff;                                                  // 0.0
/*118 */         break;                                                                  // 0.0
/*122 */     /* I2COE Register */                                                        // 0.0
/*124 */     case 0x00b08:                                                               // 0.0
/*126 */         s->i2coe = val & 0x03;                                                  // 0.0
/*128 */         break;                                                                  // 0.0
/*132 */     /* I2COUT Register */                                                       // 0.0
/*134 */     case 0x00b10:                                                               // 0.0
/*136 */         eeprom24c0x_write(val & 0x02, val & 0x01);                              // 0.0
/*138 */         s->i2cout = val;                                                        // 0.0
/*140 */         break;                                                                  // 0.0
/*144 */     /* I2CSEL Register */                                                       // 0.0
/*146 */     case 0x00b18:                                                               // 0.0
/*148 */         s->i2csel = val & 0x01;                                                 // 0.0
/*150 */         break;                                                                  // 0.0
/*154 */     default:                                                                    // 0.0
/*156 */ #if 0                                                                           // 0.0
/*158 */         printf ("malta_fpga_write: Bad register offset 0x" TARGET_FMT_lx "\n",  // 0.0
/*160 */                 addr);                                                          // 0.0
/*162 */ #endif                                                                          // 0.0
/*164 */         break;                                                                  // 0.0
/*166 */     }                                                                           // 0.0
/*168 */ }                                                                               // 0.0
