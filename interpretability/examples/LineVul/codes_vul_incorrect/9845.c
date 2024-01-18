// commit message qemu@f51074cdc6 (target=1, prob=0.4939383, correct=False): pci-hotplug-old: Has been dead for five major releases, bury
/*0  */ int pci_drive_hot_add(Monitor *mon, const QDict *qdict, DriveInfo *dinfo)  // (1) 0.2967
/*2  */ {                                                                          // (4) 0.01099
/*4  */     /* On non-x86 we don't do PCI hotplug */                               // (2) 0.1868
/*6  */     monitor_printf(mon, "Can't hot-add drive to type %d\n", dinfo->type);  // (0) 0.3077
/*8  */     return -1;                                                             // (3) 0.07692
/*10 */ }                                                                          // (5) 0.01099
