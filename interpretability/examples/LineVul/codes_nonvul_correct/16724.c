// commit message qemu@f8b6cc0070 (target=0, prob=0.022073584, correct=True): qdev: Decouple qdev_prop_drive from DriveInfo
/*0  */ static int virtio_blk_exit_pci(PCIDevice *pci_dev)                        // (1) 0.213
/*2  */ {                                                                         // (4) 0.009259
/*4  */     VirtIOPCIProxy *proxy = DO_UPCAST(VirtIOPCIProxy, pci_dev, pci_dev);  // (0) 0.2963
/*8  */     blockdev_mark_auto_del(proxy->block.dinfo->bdrv);                     // (2) 0.213
/*10 */     return virtio_exit_pci(pci_dev);                                      // (3) 0.1574
/*12 */ }                                                                         // (5) 0.009259
