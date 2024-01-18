// commit message qemu@947858b0ba (target=0, prob=0.021934675, correct=True): ide: abort TRIM operation for invalid range
/*0  */ static void ide_trim_bh_cb(void *opaque)              // (3) 0.1356
/*2  */ {                                                     // (6) 0.008475
/*4  */     TrimAIOCB *iocb = opaque;                         // (4) 0.1271
/*8  */     iocb->common.cb(iocb->common.opaque, iocb->ret);  // (0) 0.2203
/*12 */     qemu_bh_delete(iocb->bh);                         // (2) 0.1441
/*14 */     iocb->bh = NULL;                                  // (5) 0.09322
/*16 */     qemu_aio_unref(iocb);                             // (1) 0.1441
/*18 */ }                                                     // (7) 0.008475
