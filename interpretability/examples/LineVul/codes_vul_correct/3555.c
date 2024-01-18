// commit message qemu@58d479786b (target=1, prob=0.999057, correct=True): hw/pci-host/bonito: Avoid buffer overrun for bad LDMA/COP accesses
/*0 */ static void bonito_ldma_writel(void *opaque, hwaddr addr,                   // (2) 0.181
/*1 */                                uint64_t val, unsigned size)                 // (0) 0.3362
/*2 */ {                                                                           // (4) 0.008621
/*3 */     PCIBonitoState *s = opaque;                                             // (3) 0.1121
/*4 */     ((uint32_t *)(&s->bonldma))[addr/sizeof(uint32_t)] = val & 0xffffffff;  // (1) 0.3103
