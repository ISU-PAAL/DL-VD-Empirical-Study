// commit message qemu@75f19f8c30 (target=0, prob=0.037186995, correct=True): megasas: do not call pci_dma_unmap after having freed the frame once
/*0  */ static void megasas_unmap_frame(MegasasState *s, MegasasCmd *cmd)  // (1) 0.2101
/*2  */ {                                                                  // (6) 0.008403
/*4  */     PCIDevice *p = PCI_DEVICE(s);                                  // (2) 0.1429
/*8  */     pci_dma_unmap(p, cmd->frame, cmd->pa_size, 0, 0);              // (0) 0.2269
/*10 */     cmd->frame = NULL;                                             // (4) 0.07563
/*12 */     cmd->pa = 0;                                                   // (5) 0.07563
/*14 */     clear_bit(cmd->index, s->frame_map);                           // (3) 0.1429
/*16 */ }                                                                  // (7) 0.008403
