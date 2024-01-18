// commit message qemu@4be746345f (target=0, prob=0.2087233, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static void n8x0_nand_setup(struct n800_s *s)                                  // (10) 0.03906
/*2  */ {                                                                              // (19) 0.001953
/*4  */     char *otp_region;                                                          // (15) 0.01953
/*6  */     DriveInfo *dinfo;                                                          // (16) 0.01758
/*10 */     s->nand = qdev_create(NULL, "onenand");                                    // (11) 0.03711
/*12 */     qdev_prop_set_uint16(s->nand, "manufacturer_id", NAND_MFR_SAMSUNG);        // (3) 0.06836
/*14 */     /* Either 0x40 or 0x48 are OK for the device ID */                         // (13) 0.03711
/*16 */     qdev_prop_set_uint16(s->nand, "device_id", 0x48);                          // (6) 0.05273
/*18 */     qdev_prop_set_uint16(s->nand, "version_id", 0);                            // (8) 0.04883
/*20 */     qdev_prop_set_int32(s->nand, "shift", 1);                                  // (9) 0.04492
/*22 */     dinfo = drive_get(IF_MTD, 0, 0);                                           // (12) 0.03711
/*24 */     if (dinfo) {                                                               // (17) 0.01758
/*26 */         qdev_prop_set_drive_nofail(s->nand, "drive",                           // (5) 0.05469
/*28 */                                    blk_bs(blk_by_legacy_dinfo(dinfo)));        // (0) 0.1055
/*30 */     }                                                                          // (18) 0.007812
/*32 */     qdev_init_nofail(s->nand);                                                 // (14) 0.0332
/*34 */     sysbus_connect_irq(SYS_BUS_DEVICE(s->nand), 0,                             // (7) 0.05078
/*36 */                        qdev_get_gpio_in(s->mpu->gpio, N8X0_ONENAND_GPIO));     // (1) 0.1016
/*38 */     omap_gpmc_attach(s->mpu->gpmc, N8X0_ONENAND_CS,                            // (4) 0.0625
/*40 */                      sysbus_mmio_get_region(SYS_BUS_DEVICE(s->nand), 0));      // (2) 0.08789
/*42 */     otp_region = onenand_raw_otp(s->nand);                                     // 0.0
/*46 */     memcpy(otp_region + 0x000, n8x0_cal_wlan_mac, sizeof(n8x0_cal_wlan_mac));  // 0.0
/*48 */     memcpy(otp_region + 0x800, n8x0_cal_bt_id, sizeof(n8x0_cal_bt_id));        // 0.0
/*50 */     /* XXX: in theory should also update the OOB for both pages */             // 0.0
/*52 */ }                                                                              // 0.0
