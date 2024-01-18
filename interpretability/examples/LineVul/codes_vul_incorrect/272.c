// commit message qemu@09cd058a2c (target=1, prob=0.02010272, correct=False): intel_iommu: get rid of {0} initializers
/*0  */ static MemTxResult vtd_mem_ir_write(void *opaque, hwaddr addr,      // (10) 0.04492
/*2  */                                     uint64_t value, unsigned size,  // (0) 0.08594
/*4  */                                     MemTxAttrs attrs)               // (1) 0.08203
/*6  */ {                                                                   // (20) 0.001953
/*8  */     int ret = 0;                                                    // (17) 0.01562
/*10 */     MSIMessage from = {0}, to = {0};                                // (12) 0.03125
/*14 */     from.address = (uint64_t) addr + VTD_INTERRUPT_ADDR_FIRST;      // (6) 0.05664
/*16 */     from.data = (uint32_t) value;                                   // (13) 0.0293
/*20 */     ret = vtd_interrupt_remap_msi(opaque, &from, &to);              // (7) 0.05078
/*22 */     if (ret) {                                                      // (18) 0.01562
/*24 */         /* TODO: report error */                                    // (14) 0.02734
/*26 */         VTD_DPRINTF(GENERAL, "int remap fail for addr 0x%"PRIx64    // (4) 0.0625
/*28 */                     " data 0x%"PRIx32, from.address, from.data);    // (2) 0.07227
/*30 */         /* Drop this interrupt */                                   // (16) 0.02344
/*32 */         return MEMTX_ERROR;                                         // (15) 0.02539
/*34 */     }                                                               // (19) 0.007812
/*38 */     VTD_DPRINTF(IR, "delivering MSI 0x%"PRIx64":0x%"PRIx32          // (3) 0.0625
/*40 */                 " for device sid 0x%04x",                           // (8) 0.04883
/*42 */                 to.address, to.data, sid);                          // (9) 0.04883
/*46 */     if (dma_memory_write(&address_space_memory, to.address,         // (11) 0.04297
/*48 */                          &to.data, size)) {                         // (5) 0.0625
/*50 */         VTD_DPRINTF(GENERAL, "error: fail to write 0x%"PRIx64       // 0.0
/*52 */                     " value 0x%"PRIx32, to.address, to.data);       // 0.0
/*54 */     }                                                               // 0.0
/*58 */     return MEMTX_OK;                                                // 0.0
/*60 */ }                                                                   // 0.0
