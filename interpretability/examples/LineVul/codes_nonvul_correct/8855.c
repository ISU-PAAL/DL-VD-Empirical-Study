// commit message qemu@4981bdec0d (target=0, prob=0.012001255, correct=True): block: Fix BB AIOCB AioContext without BDS
/*0 */ AioContext *blk_get_aio_context(BlockBackend *blk)  // (0) 0.4118
/*2 */ {                                                   // (2) 0.01961
/*4 */     return bdrv_get_aio_context(blk->bs);           // (1) 0.3922
/*6 */ }                                                   // (3) 0.01961
