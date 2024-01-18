// commit message qemu@7e84c2498f (target=0, prob=0.011599439, correct=True): full TSS support - IO map check support - conforming segment check fixes - iret in vm86 mode fix
/*0 */ void helper_iret_protected(int shift)   // (1) 0.3056
/*2 */ {                                       // (2) 0.02778
/*4 */     helper_ret_protected(shift, 1, 0);  // (0) 0.4167
/*6 */ }                                       // (3) 0.02778
