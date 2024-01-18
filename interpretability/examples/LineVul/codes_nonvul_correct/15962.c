// commit message qemu@6e0d8677cb (target=0, prob=0.0050241807, correct=True): converted string OPs and LOOP insns to TCG
/*0 */ void OPPROTO op_addq_EDI_T0(void)  // (0) 0.4229
/*2 */ {                                  // (3) 0.02488
/*4 */     EDI = (EDI + T0);              // (1) 0.3233
/*6 */ }                                  // (2) 0.0249
