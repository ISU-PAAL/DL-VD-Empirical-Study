// commit message qemu@d7cd369402 (target=1, prob=0.94399303, correct=True): migration: restrict scope of incoming fd read handler
/*0 */ static void enter_migration_coroutine(void *opaque)  // (1) 0.2885
/*2 */ {                                                    // (3) 0.01923
/*4 */     Coroutine *co = opaque;                          // (2) 0.1923
/*6 */     qemu_coroutine_enter(co, NULL);                  // (0) 0.3077
/*8 */ }                                                    // (4) 0.01923
