// commit message qemu@0b8b8753e4 (target=1, prob=0.6424535, correct=True): coroutine: move entry argument to qemu_coroutine_create
/*0 */ static void coroutine_fn c1_fn(void *opaque)  // (1) 0.2909
/*2 */ {                                             // (3) 0.01818
/*4 */     Coroutine *c2 = opaque;                   // (2) 0.2
/*6 */     qemu_coroutine_enter(c2, NULL);           // (0) 0.3091
/*8 */ }                                             // (4) 0.01818
