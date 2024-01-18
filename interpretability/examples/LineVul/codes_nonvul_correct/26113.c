// commit message qemu@871d2f0796 (target=0, prob=0.05258179, correct=True): Fix some issues with QEMUFile
/*0  */ static void bdrv_put_buffer(void *opaque, const uint8_t *buf,  // (2) 0.2054
/*2  */                             int64_t pos, int size)             // (0) 0.3214
/*4  */ {                                                              // (4) 0.008929
/*6  */     QEMUFileBdrv *s = opaque;                                  // (3) 0.1339
/*8  */     bdrv_pwrite(s->bs, s->base_offset + pos, buf, size);       // (1) 0.2321
/*10 */ }                                                              // (5) 0.008929
