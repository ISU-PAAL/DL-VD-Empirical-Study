// commit message qemu@af01492755 (target=1, prob=0.07434473, correct=False): usb-bot: Drop not needed "allow_hotplug = 0"
/*0  */ static void usb_msd_realize_bot(USBDevice *dev, Error **errp)  // (3) 0.1272
/*2  */ {                                                              // (8) 0.00578
/*4  */     MSDState *s = DO_UPCAST(MSDState, dev, dev);               // (2) 0.1329
/*8  */     usb_desc_create_serial(dev);                               // (6) 0.07514
/*10 */     usb_desc_init(dev);                                        // (7) 0.06358
/*12 */     scsi_bus_new(&s->bus, sizeof(s->bus), DEVICE(dev),         // (1) 0.1445
/*14 */                  &usb_msd_scsi_info_bot, NULL);                // (0) 0.1792
/*16 */     s->bus.qbus.allow_hotplug = 0;                             // (4) 0.09827
/*18 */     usb_msd_handle_reset(dev);                                 // (5) 0.08092
/*20 */ }                                                              // (9) 0.00578
