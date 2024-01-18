// commit message qemu@ad96090a01 (target=0, prob=0.094972394, correct=True): Refactor target specific handling, compile vl.c only once
/*0 */ uint64_t ram_bytes_remaining(void)                   // (1) 0.3026
/*2 */ {                                                    // (2) 0.02324
/*4 */     return ram_save_remaining() * TARGET_PAGE_SIZE;  // (0) 0.465
/*6 */ }                                                    // (3) 0.02324
