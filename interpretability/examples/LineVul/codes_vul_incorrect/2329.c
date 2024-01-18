// commit message qemu@f8ed85ac99 (target=1, prob=0.37364995, correct=False): Fix bad error handling after memory_region_init_ram()
/*0   */ static void stellaris_init(const char *kernel_filename, const char *cpu_model,    // (8) 0.04102
/*2   */                            stellaris_board_info *board)                           // (0) 0.06836
/*4   */ {                                                                                 // (26) 0.001953
/*6   */     static const int uart_irq[] = {5, 6, 33, 34};                                 // (6) 0.04297
/*8   */     static const int timer_irq[] = {19, 21, 23, 35};                              // (10) 0.04102
/*10  */     static const uint32_t gpio_addr[7] =                                          // (15) 0.0332
/*12  */       { 0x40004000, 0x40005000, 0x40006000, 0x40007000,                           // (3) 0.05273
/*14  */         0x40024000, 0x40025000, 0x40026000};                                      // (5) 0.04883
/*16  */     static const int gpio_irq[7] = {0, 1, 2, 3, 4, 30, 31};                       // (1) 0.05859
/*20  */     qemu_irq *pic;                                                                // (19) 0.02344
/*22  */     DeviceState *gpio_dev[7];                                                     // (17) 0.02539
/*24  */     qemu_irq gpio_in[7][8];                                                       // (13) 0.03516
/*26  */     qemu_irq gpio_out[7][8];                                                      // (12) 0.03516
/*28  */     qemu_irq adc;                                                                 // (20) 0.02344
/*30  */     int sram_size;                                                                // (21) 0.01758
/*32  */     int flash_size;                                                               // (23) 0.01562
/*34  */     I2CBus *i2c;                                                                  // (18) 0.02344
/*36  */     DeviceState *dev;                                                             // (22) 0.01563
/*38  */     int i;                                                                        // (24) 0.01172
/*40  */     int j;                                                                        // (25) 0.01172
/*44  */     MemoryRegion *sram = g_new(MemoryRegion, 1);                                  // (11) 0.03516
/*46  */     MemoryRegion *flash = g_new(MemoryRegion, 1);                                 // (14) 0.0332
/*48  */     MemoryRegion *system_memory = get_system_memory();                            // (16) 0.03125
/*52  */     flash_size = (((board->dc0 & 0xffff) + 1) << 1) * 1024;                       // (2) 0.05273
/*54  */     sram_size = ((board->dc0 >> 18) + 1) * 1024;                                  // (7) 0.04297
/*58  */     /* Flash programming is done via the SCU, so pretend it is ROM.  */           // (9) 0.04102
/*60  */     memory_region_init_ram(flash, NULL, "stellaris.flash", flash_size,            // (4) 0.04883
/*62  */                            &error_abort);                                         // 0.0
/*64  */     vmstate_register_ram_global(flash);                                           // 0.0
/*66  */     memory_region_set_readonly(flash, true);                                      // 0.0
/*68  */     memory_region_add_subregion(system_memory, 0, flash);                         // 0.0
/*72  */     memory_region_init_ram(sram, NULL, "stellaris.sram", sram_size,               // 0.0
/*74  */                            &error_abort);                                         // 0.0
/*76  */     vmstate_register_ram_global(sram);                                            // 0.0
/*78  */     memory_region_add_subregion(system_memory, 0x20000000, sram);                 // 0.0
/*82  */     pic = armv7m_init(system_memory, flash_size, NUM_IRQ_LINES,                   // 0.0
/*84  */                       kernel_filename, cpu_model);                                // 0.0
/*88  */     if (board->dc1 & (1 << 16)) {                                                 // 0.0
/*90  */         dev = sysbus_create_varargs(TYPE_STELLARIS_ADC, 0x40038000,               // 0.0
/*92  */                                     pic[14], pic[15], pic[16], pic[17], NULL);    // 0.0
/*94  */         adc = qdev_get_gpio_in(dev, 0);                                           // 0.0
/*96  */     } else {                                                                      // 0.0
/*98  */         adc = NULL;                                                               // 0.0
/*100 */     }                                                                             // 0.0
/*102 */     for (i = 0; i < 4; i++) {                                                     // 0.0
/*104 */         if (board->dc2 & (0x10000 << i)) {                                        // 0.0
/*106 */             dev = sysbus_create_simple(TYPE_STELLARIS_GPTM,                       // 0.0
/*108 */                                        0x40030000 + i * 0x1000,                   // 0.0
/*110 */                                        pic[timer_irq[i]]);                        // 0.0
/*112 */             /* TODO: This is incorrect, but we get away with it because           // 0.0
/*114 */                the ADC output is only ever pulsed.  */                            // 0.0
/*116 */             qdev_connect_gpio_out(dev, 0, adc);                                   // 0.0
/*118 */         }                                                                         // 0.0
/*120 */     }                                                                             // 0.0
/*124 */     stellaris_sys_init(0x400fe000, pic[28], board, nd_table[0].macaddr.a);        // 0.0
/*128 */     for (i = 0; i < 7; i++) {                                                     // 0.0
/*130 */         if (board->dc4 & (1 << i)) {                                              // 0.0
/*132 */             gpio_dev[i] = sysbus_create_simple("pl061_luminary", gpio_addr[i],    // 0.0
/*134 */                                                pic[gpio_irq[i]]);                 // 0.0
/*136 */             for (j = 0; j < 8; j++) {                                             // 0.0
/*138 */                 gpio_in[i][j] = qdev_get_gpio_in(gpio_dev[i], j);                 // 0.0
/*140 */                 gpio_out[i][j] = NULL;                                            // 0.0
/*142 */             }                                                                     // 0.0
/*144 */         }                                                                         // 0.0
/*146 */     }                                                                             // 0.0
/*150 */     if (board->dc2 & (1 << 12)) {                                                 // 0.0
/*152 */         dev = sysbus_create_simple(TYPE_STELLARIS_I2C, 0x40020000, pic[8]);       // 0.0
/*154 */         i2c = (I2CBus *)qdev_get_child_bus(dev, "i2c");                           // 0.0
/*156 */         if (board->peripherals & BP_OLED_I2C) {                                   // 0.0
/*158 */             i2c_create_slave(i2c, "ssd0303", 0x3d);                               // 0.0
/*160 */         }                                                                         // 0.0
/*162 */     }                                                                             // 0.0
/*166 */     for (i = 0; i < 4; i++) {                                                     // 0.0
/*168 */         if (board->dc2 & (1 << i)) {                                              // 0.0
/*170 */             sysbus_create_simple("pl011_luminary", 0x4000c000 + i * 0x1000,       // 0.0
/*172 */                                  pic[uart_irq[i]]);                               // 0.0
/*174 */         }                                                                         // 0.0
/*176 */     }                                                                             // 0.0
/*178 */     if (board->dc2 & (1 << 4)) {                                                  // 0.0
/*180 */         dev = sysbus_create_simple("pl022", 0x40008000, pic[7]);                  // 0.0
/*182 */         if (board->peripherals & BP_OLED_SSI) {                                   // 0.0
/*184 */             void *bus;                                                            // 0.0
/*186 */             DeviceState *sddev;                                                   // 0.0
/*188 */             DeviceState *ssddev;                                                  // 0.0
/*192 */             /* Some boards have both an OLED controller and SD card connected to  // 0.0
/*194 */              * the same SSI port, with the SD card chip select connected to a     // 0.0
/*196 */              * GPIO pin.  Technically the OLED chip select is connected to the    // 0.0
/*198 */              * SSI Fss pin.  We do not bother emulating that as both devices      // 0.0
/*200 */              * should never be selected simultaneously, and our OLED controller   // 0.0
/*202 */              * ignores stray 0xff commands that occur when deselecting the SD     // 0.0
/*204 */              * card.                                                              // 0.0
/*206 */              */                                                                   // 0.0
/*208 */             bus = qdev_get_child_bus(dev, "ssi");                                 // 0.0
/*212 */             sddev = ssi_create_slave(bus, "ssi-sd");                              // 0.0
/*214 */             ssddev = ssi_create_slave(bus, "ssd0323");                            // 0.0
/*216 */             gpio_out[GPIO_D][0] = qemu_irq_split(                                 // 0.0
/*218 */                     qdev_get_gpio_in_named(sddev, SSI_GPIO_CS, 0),                // 0.0
/*220 */                     qdev_get_gpio_in_named(ssddev, SSI_GPIO_CS, 0));              // 0.0
/*222 */             gpio_out[GPIO_C][7] = qdev_get_gpio_in(ssddev, 0);                    // 0.0
/*226 */             /* Make sure the select pin is high.  */                              // 0.0
/*228 */             qemu_irq_raise(gpio_out[GPIO_D][0]);                                  // 0.0
/*230 */         }                                                                         // 0.0
/*232 */     }                                                                             // 0.0
/*234 */     if (board->dc4 & (1 << 28)) {                                                 // 0.0
/*236 */         DeviceState *enet;                                                        // 0.0
/*240 */         qemu_check_nic_model(&nd_table[0], "stellaris");                          // 0.0
/*244 */         enet = qdev_create(NULL, "stellaris_enet");                               // 0.0
/*246 */         qdev_set_nic_properties(enet, &nd_table[0]);                              // 0.0
/*248 */         qdev_init_nofail(enet);                                                   // 0.0
/*250 */         sysbus_mmio_map(SYS_BUS_DEVICE(enet), 0, 0x40048000);                     // 0.0
/*252 */         sysbus_connect_irq(SYS_BUS_DEVICE(enet), 0, pic[42]);                     // 0.0
/*254 */     }                                                                             // 0.0
/*256 */     if (board->peripherals & BP_GAMEPAD) {                                        // 0.0
/*258 */         qemu_irq gpad_irq[5];                                                     // 0.0
/*260 */         static const int gpad_keycode[5] = { 0xc8, 0xd0, 0xcb, 0xcd, 0x1d };      // 0.0
/*264 */         gpad_irq[0] = qemu_irq_invert(gpio_in[GPIO_E][0]); /* up */               // 0.0
/*266 */         gpad_irq[1] = qemu_irq_invert(gpio_in[GPIO_E][1]); /* down */             // 0.0
/*268 */         gpad_irq[2] = qemu_irq_invert(gpio_in[GPIO_E][2]); /* left */             // 0.0
/*270 */         gpad_irq[3] = qemu_irq_invert(gpio_in[GPIO_E][3]); /* right */            // 0.0
/*272 */         gpad_irq[4] = qemu_irq_invert(gpio_in[GPIO_F][1]); /* select */           // 0.0
/*276 */         stellaris_gamepad_init(5, gpad_irq, gpad_keycode);                        // 0.0
/*278 */     }                                                                             // 0.0
/*280 */     for (i = 0; i < 7; i++) {                                                     // 0.0
/*282 */         if (board->dc4 & (1 << i)) {                                              // 0.0
/*284 */             for (j = 0; j < 8; j++) {                                             // 0.0
/*286 */                 if (gpio_out[i][j]) {                                             // 0.0
/*288 */                     qdev_connect_gpio_out(gpio_dev[i], j, gpio_out[i][j]);        // 0.0
/*290 */                 }                                                                 // 0.0
/*292 */             }                                                                     // 0.0
/*294 */         }                                                                         // 0.0
/*296 */     }                                                                             // 0.0
/*298 */ }                                                                                 // 0.0
