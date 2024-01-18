// commit message qemu@e95ead32ef (target=0, prob=0.0046617785, correct=True): virtio-9p: Security model for chmod
/*0 */ static int v9fs_do_chmod(V9fsState *s, V9fsString *path, mode_t mode)  // (0) 0.4918
/*2 */ {                                                                      // (2) 0.01639
/*4 */     return s->ops->chmod(&s->ctx, path->data, mode);                   // (1) 0.3443
/*6 */ }                                                                      // (3) 0.01639
