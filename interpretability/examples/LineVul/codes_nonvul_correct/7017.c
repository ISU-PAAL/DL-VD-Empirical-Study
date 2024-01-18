// commit message qemu@a818a4b69d (target=0, prob=0.031885564, correct=True): scsi-bus: Convert DeviceClass init to realize
/*0  */ static int scsi_device_init(SCSIDevice *s)           // (1) 0.191
/*2  */ {                                                    // (6) 0.01124
/*4  */     SCSIDeviceClass *sc = SCSI_DEVICE_GET_CLASS(s);  // (0) 0.2697
/*6  */     if (sc->init) {                                  // (3) 0.1124
/*8  */         return sc->init(s);                          // (2) 0.1573
/*10 */     }                                                // (5) 0.04494
/*12 */     return 0;                                        // (4) 0.06742
/*14 */ }                                                    // (7) 0.01124
