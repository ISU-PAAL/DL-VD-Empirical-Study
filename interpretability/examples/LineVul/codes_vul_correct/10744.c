// commit message qemu@60fe637bf0 (target=1, prob=0.6763765, correct=True): Start migrating migration code into a migration directory
/*0  */ static inline uint8_t *ram_chunk_start(const RDMALocalBlock *rdma_ram_block,  // (3) 0.1687
/*2  */                                        uint64_t i)                            // (1) 0.2651
/*4  */ {                                                                             // (4) 0.006024
/*6  */     return (uint8_t *) (((uintptr_t) rdma_ram_block->local_host_addr)         // (2) 0.1867
/*8  */                                     + (i << RDMA_REG_CHUNK_SHIFT));           // (0) 0.3072
/*10 */ }                                                                             // (5) 0.006024
