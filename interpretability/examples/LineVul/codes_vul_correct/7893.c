// commit message qemu@0b8b8753e4 (target=1, prob=0.6610894, correct=True): coroutine: move entry argument to qemu_coroutine_create
/*0  */ static void fd_coroutine_enter(void *opaque)          // (2) 0.1852
/*2  */ {                                                     // (4) 0.01235
/*4  */     FDYieldUntilData *data = opaque;                  // (3) 0.1605
/*6  */     qemu_set_fd_handler(data->fd, NULL, NULL, NULL);  // (0) 0.284
/*8  */     qemu_coroutine_enter(data->co, NULL);             // (1) 0.2222
/*10 */ }                                                     // (5) 0.01235
