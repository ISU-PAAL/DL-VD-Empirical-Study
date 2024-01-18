// commit message qemu@a52b2cbf21 (target=1, prob=0.21985003, correct=False): qxl: Fix new function name for spice-server library
/*0  */ static void qxl_spice_monitors_config_async(PCIQXLDevice *qxl, int replay)  // (4) 0.06055
/*2  */ {                                                                           // (20) 0.001953
/*4  */     trace_qxl_spice_monitors_config(qxl->id);                               // (11) 0.04492
/*6  */     if (replay) {                                                           // (16) 0.01758
/*8  */         /*                                                                  // (18) 0.01562
/*10 */          * don't use QXL_COOKIE_TYPE_IO:                                    // (12) 0.04492
/*12 */          *  - we are not running yet (post_load), we will assert            // (8) 0.04688
/*14 */          *    in send_events                                                // (15) 0.03125
/*16 */          *  - this is not a guest io, but a reply, so async_io isn't set.   // (5) 0.05859
/*18 */          */                                                                 // (17) 0.01758
/*20 */         spice_qxl_monitors_config_async(&qxl->ssd.qxl,                      // (3) 0.0625
/*22 */                 qxl->guest_monitors_config,                                 // (7) 0.05273
/*24 */                 MEMSLOT_GROUP_GUEST,                                        // (9) 0.04688
/*26 */                 (uintptr_t)qxl_cookie_new(                                  // (6) 0.05664
/*28 */                     QXL_COOKIE_TYPE_POST_LOAD_MONITORS_CONFIG,              // (1) 0.07617
/*30 */                     0));                                                    // (13) 0.04102
/*32 */     } else {                                                                // (19) 0.01172
/*34 */ #if SPICE_SERVER_VERSION >= 0x000c06 /* release 0.12.6 */                   // (10) 0.04492
/*36 */         if (qxl->max_outputs) {                                             // (14) 0.03711
/*38 */             spice_qxl_set_monitors_config_limit(&qxl->ssd.qxl,              // (2) 0.07227
/*40 */                                                 qxl->max_outputs);          // (0) 0.1094
/*42 */         }                                                                   // 0.0
/*44 */ #endif                                                                      // 0.0
/*46 */         qxl->guest_monitors_config = qxl->ram->monitors_config;             // 0.0
/*48 */         spice_qxl_monitors_config_async(&qxl->ssd.qxl,                      // 0.0
/*50 */                 qxl->ram->monitors_config,                                  // 0.0
/*52 */                 MEMSLOT_GROUP_GUEST,                                        // 0.0
/*54 */                 (uintptr_t)qxl_cookie_new(QXL_COOKIE_TYPE_IO,               // 0.0
/*56 */                                           QXL_IO_MONITORS_CONFIG_ASYNC));   // 0.0
/*58 */     }                                                                       // 0.0
/*60 */ }                                                                           // 0.0
