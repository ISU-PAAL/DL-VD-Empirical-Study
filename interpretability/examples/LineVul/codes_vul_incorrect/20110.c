// commit message qemu@f3d8b1eb10 (target=1, prob=0.44389626, correct=False): array overflow in hw/stellaris.c and hw/omap_dss.c
/*0   */ static void stellaris_init(const char *kernel_filename, const char *cpu_model,  // (9) 0.04102
/*2   */                            DisplayState *ds, stellaris_board_info *board)       // (0) 0.07813
/*4   */ {                                                                               // (26) 0.001953
/*6   */     static const int uart_irq[] = {5, 6, 33, 34};                               // (7) 0.04297
/*8   */     static const int timer_irq[] = {19, 21, 23, 35};                            // (10) 0.04102
/*10  */     static const uint32_t gpio_addr[7] =                                        // (12) 0.0332
/*12  */       { 0x40004000, 0x40005000, 0x40006000, 0x40007000,                         // (4) 0.05273
/*14  */         0x40024000, 0x40025000, 0x40026000};                                    // (5) 0.04883
/*16  */     static const int gpio_irq[7] = {0, 1, 2, 3, 4, 30, 31};                     // (1) 0.05859
/*20  */     qemu_irq *pic;                                                              // (18) 0.02344
/*22  */     qemu_irq *gpio_in[5];                                                       // (13) 0.0332
/*24  */     qemu_irq *gpio_out[5];                                                      // (14) 0.0332
/*26  */     qemu_irq adc;                                                               // (19) 0.02344
/*28  */     int sram_size;                                                              // (21) 0.01758
/*30  */     int flash_size;                                                             // (22) 0.01562
/*32  */     i2c_bus *i2c;                                                               // (17) 0.02539
/*34  */     int i;                                                                      // (23) 0.01172
/*38  */     flash_size = ((board->dc0 & 0xffff) + 1) << 1;                              // (6) 0.04492
/*40  */     sram_size = (board->dc0 >> 18) + 1;                                         // (11) 0.03711
/*42  */     pic = armv7m_init(flash_size, sram_size, kernel_filename, cpu_model);       // (2) 0.05664
/*46  */     if (board->dc1 & (1 << 16)) {                                               // (15) 0.03125
/*48  */         adc = stellaris_adc_init(0x40038000, pic[14]);                          // (3) 0.05469
/*50  */     } else {                                                                    // (24) 0.01172
/*52  */         adc = NULL;                                                             // (20) 0.02344
/*54  */     }                                                                           // (25) 0.007812
/*56  */     for (i = 0; i < 4; i++) {                                                   // (16) 0.03125
/*58  */         if (board->dc2 & (0x10000 << i)) {                                      // (8) 0.04297
/*60  */             stellaris_gptm_init(0x40030000 + i * 0x1000,                        // 0.0
/*62  */                                 pic[timer_irq[i]], adc);                        // 0.0
/*64  */         }                                                                       // 0.0
/*66  */     }                                                                           // 0.0
/*70  */     stellaris_sys_init(0x400fe000, pic[28], board, nd_table[0].macaddr);        // 0.0
/*74  */     for (i = 0; i < 7; i++) {                                                   // 0.0
/*76  */         if (board->dc4 & (1 << i)) {                                            // 0.0
/*78  */             gpio_in[i] = pl061_init(gpio_addr[i], pic[gpio_irq[i]],             // 0.0
/*80  */                                     &gpio_out[i]);                              // 0.0
/*82  */         }                                                                       // 0.0
/*84  */     }                                                                           // 0.0
/*88  */     if (board->dc2 & (1 << 12)) {                                               // 0.0
/*90  */         i2c = i2c_init_bus();                                                   // 0.0
/*92  */         stellaris_i2c_init(0x40020000, pic[8], i2c);                            // 0.0
/*94  */         if (board->peripherals & BP_OLED_I2C) {                                 // 0.0
/*96  */             ssd0303_init(ds, i2c, 0x3d);                                        // 0.0
/*98  */         }                                                                       // 0.0
/*100 */     }                                                                           // 0.0
/*104 */     for (i = 0; i < 4; i++) {                                                   // 0.0
/*106 */         if (board->dc2 & (1 << i)) {                                            // 0.0
/*108 */             pl011_init(0x4000c000 + i * 0x1000, pic[uart_irq[i]],               // 0.0
/*110 */                        serial_hds[i], PL011_LUMINARY);                          // 0.0
/*112 */         }                                                                       // 0.0
/*114 */     }                                                                           // 0.0
/*116 */     if (board->dc2 & (1 << 4)) {                                                // 0.0
/*118 */         if (board->peripherals & BP_OLED_SSI) {                                 // 0.0
/*120 */             void * oled;                                                        // 0.0
/*122 */             void * sd;                                                          // 0.0
/*124 */             void *ssi_bus;                                                      // 0.0
/*126 */             int index;                                                          // 0.0
/*130 */             oled = ssd0323_init(ds, &gpio_out[GPIO_C][7]);                      // 0.0
/*132 */             index = drive_get_index(IF_SD, 0, 0);                               // 0.0
/*134 */             sd = ssi_sd_init(drives_table[index].bdrv);                         // 0.0
/*138 */             ssi_bus = stellaris_ssi_bus_init(&gpio_out[GPIO_D][0],              // 0.0
/*140 */                                              ssi_sd_xfer, sd,                   // 0.0
/*142 */                                              ssd0323_xfer_ssi, oled);           // 0.0
/*146 */             pl022_init(0x40008000, pic[7], stellaris_ssi_bus_xfer, ssi_bus);    // 0.0
/*148 */             /* Make sure the select pin is high.  */                            // 0.0
/*150 */             qemu_irq_raise(gpio_out[GPIO_D][0]);                                // 0.0
/*152 */         } else {                                                                // 0.0
/*154 */             pl022_init(0x40008000, pic[7], NULL, NULL);                         // 0.0
/*156 */         }                                                                       // 0.0
/*158 */     }                                                                           // 0.0
/*160 */     if (board->dc4 & (1 << 28)) {                                               // 0.0
/*162 */         /* FIXME: Obey network model.  */                                       // 0.0
/*164 */         stellaris_enet_init(&nd_table[0], 0x40048000, pic[42]);                 // 0.0
/*166 */     }                                                                           // 0.0
/*168 */     if (board->peripherals & BP_GAMEPAD) {                                      // 0.0
/*170 */         qemu_irq gpad_irq[5];                                                   // 0.0
/*172 */         static const int gpad_keycode[5] = { 0xc8, 0xd0, 0xcb, 0xcd, 0x1d };    // 0.0
/*176 */         gpad_irq[0] = qemu_irq_invert(gpio_in[GPIO_E][0]); /* up */             // 0.0
/*178 */         gpad_irq[1] = qemu_irq_invert(gpio_in[GPIO_E][1]); /* down */           // 0.0
/*180 */         gpad_irq[2] = qemu_irq_invert(gpio_in[GPIO_E][2]); /* left */           // 0.0
/*182 */         gpad_irq[3] = qemu_irq_invert(gpio_in[GPIO_E][3]); /* right */          // 0.0
/*184 */         gpad_irq[4] = qemu_irq_invert(gpio_in[GPIO_F][1]); /* select */         // 0.0
/*188 */         stellaris_gamepad_init(5, gpad_irq, gpad_keycode);                      // 0.0
/*190 */     }                                                                           // 0.0
/*192 */ }                                                                               // 0.0
