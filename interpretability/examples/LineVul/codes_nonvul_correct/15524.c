// commit message qemu@4be746345f (target=0, prob=0.050729655, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ BlockAIOCB *dma_bdrv_write(BlockDriverState *bs,                             // (4) 0.1081
/*2  */                            QEMUSGList *sg, uint64_t sector,                  // (1) 0.2162
/*4  */                            void (*cb)(void *opaque, int ret), void *opaque)  // (0) 0.2324
/*6  */ {                                                                            // (5) 0.005405
/*8  */     return dma_bdrv_io(bs, sg, sector, bdrv_aio_writev, cb, opaque,          // (2) 0.1892
/*10 */                        DMA_DIRECTION_TO_DEVICE);                             // (3) 0.1838
/*12 */ }                                                                            // (6) 0.005405
