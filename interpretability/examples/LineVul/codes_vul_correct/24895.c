// commit message qemu@0b8b8753e4 (target=1, prob=0.50074345, correct=True): coroutine: move entry argument to qemu_coroutine_create
/*0  */ static void co_write_request(void *opaque)   // (2) 0.2167
/*2  */ {                                            // (3) 0.01667
/*4  */     BDRVSheepdogState *s = opaque;           // (1) 0.25
/*8  */     qemu_coroutine_enter(s->co_send, NULL);  // (0) 0.3333
/*10 */ }                                            // (4) 0.01667
