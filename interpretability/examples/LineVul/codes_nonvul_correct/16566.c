// commit message qemu@6c7565028c (target=0, prob=0.22499155, correct=True): qxl: Only emit QXL_INTERRUPT_CLIENT_MONITORS_CONFIG on config changes
/*0   */ static int interface_client_monitors_config(QXLInstance *sin,                    // (12) 0.0332
/*2   */                                         VDAgentMonitorsConfig *monitors_config)  // (1) 0.09961
/*4   */ {                                                                                // (20) 0.001953
/*6   */     PCIQXLDevice *qxl = container_of(sin, PCIQXLDevice, ssd.qxl);                // (3) 0.06641
/*8   */     QXLRom *rom = memory_region_get_ram_ptr(&qxl->rom_bar);                      // (7) 0.05273
/*10  */     int i;                                                                       // (16) 0.01172
/*12  */     unsigned max_outputs = ARRAY_SIZE(rom->client_monitors_config.heads);        // (8) 0.04883
/*16  */     if (qxl->revision < 4) {                                                     // (13) 0.0293
/*18  */         trace_qxl_client_monitors_config_unsupported_by_device(qxl->id,          // (5) 0.06445
/*20  */                                                                qxl->revision);   // (0) 0.1348
/*22  */         return 0;                                                                // (14) 0.01953
/*24  */     }                                                                            // (18) 0.007812
/*26  */     /*                                                                           // (19) 0.007812
/*28  */      * Older windows drivers set int_mask to 0 when their ISR is called,         // (10) 0.04102
/*30  */      * then later set it to ~0. So it doesn't relate to the actual interrupts    // (9) 0.04297
/*32  */      * handled. However, they are old, so clearly they don't support this        // (11) 0.03906
/*34  */      * interrupt                                                                 // (15) 0.01172
/*36  */      */                                                                          // (17) 0.009766
/*38  */     if (qxl->ram->int_mask == 0 || qxl->ram->int_mask == ~0 ||                   // (6) 0.05859
/*40  */         !(qxl->ram->int_mask & QXL_INTERRUPT_CLIENT_MONITORS_CONFIG)) {          // (2) 0.07422
/*42  */         trace_qxl_client_monitors_config_unsupported_by_guest(qxl->id,           // (4) 0.06641
/*44  */                                                             qxl->ram->int_mask,  // 0.0
/*46  */                                                             monitors_config);    // 0.0
/*48  */         return 0;                                                                // 0.0
/*50  */     }                                                                            // 0.0
/*52  */     if (!monitors_config) {                                                      // 0.0
/*54  */         return 1;                                                                // 0.0
/*56  */     }                                                                            // 0.0
/*60  */ #if SPICE_SERVER_VERSION >= 0x000c06 /* release 0.12.6 */                        // 0.0
/*62  */     /* limit number of outputs based on setting limit */                         // 0.0
/*64  */     if (qxl->max_outputs && qxl->max_outputs <= max_outputs) {                   // 0.0
/*66  */         max_outputs = qxl->max_outputs;                                          // 0.0
/*68  */     }                                                                            // 0.0
/*70  */ #endif                                                                           // 0.0
/*74  */     memset(&rom->client_monitors_config, 0,                                      // 0.0
/*76  */            sizeof(rom->client_monitors_config));                                 // 0.0
/*78  */     rom->client_monitors_config.count = monitors_config->num_of_monitors;        // 0.0
/*80  */     /* monitors_config->flags ignored */                                         // 0.0
/*82  */     if (rom->client_monitors_config.count >= max_outputs) {                      // 0.0
/*84  */         trace_qxl_client_monitors_config_capped(qxl->id,                         // 0.0
/*86  */                                 monitors_config->num_of_monitors,                // 0.0
/*88  */                                 max_outputs);                                    // 0.0
/*90  */         rom->client_monitors_config.count = max_outputs;                         // 0.0
/*92  */     }                                                                            // 0.0
/*94  */     for (i = 0 ; i < rom->client_monitors_config.count ; ++i) {                  // 0.0
/*96  */         VDAgentMonConfig *monitor = &monitors_config->monitors[i];               // 0.0
/*98  */         QXLURect *rect = &rom->client_monitors_config.heads[i];                  // 0.0
/*100 */         /* monitor->depth ignored */                                             // 0.0
/*102 */         rect->left = monitor->x;                                                 // 0.0
/*104 */         rect->top = monitor->y;                                                  // 0.0
/*106 */         rect->right = monitor->x + monitor->width;                               // 0.0
/*108 */         rect->bottom = monitor->y + monitor->height;                             // 0.0
/*110 */     }                                                                            // 0.0
/*112 */     rom->client_monitors_config_crc = qxl_crc32(                                 // 0.0
/*114 */             (const uint8_t *)&rom->client_monitors_config,                       // 0.0
/*116 */             sizeof(rom->client_monitors_config));                                // 0.0
/*118 */     trace_qxl_client_monitors_config_crc(qxl->id,                                // 0.0
/*120 */             sizeof(rom->client_monitors_config),                                 // 0.0
/*122 */             rom->client_monitors_config_crc);                                    // 0.0
/*126 */     trace_qxl_interrupt_client_monitors_config(qxl->id,                          // 0.0
/*128 */                         rom->client_monitors_config.count,                       // 0.0
/*130 */                         rom->client_monitors_config.heads);                      // 0.0
/*132 */     qxl_send_events(qxl, QXL_INTERRUPT_CLIENT_MONITORS_CONFIG);                  // 0.0
/*134 */     return 1;                                                                    // 0.0
/*136 */ }                                                                                // 0.0
