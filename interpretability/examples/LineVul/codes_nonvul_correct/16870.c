// commit message qemu@3b2e934463 (target=0, prob=0.057701062, correct=True): nvic: Implement AIRCR changes for v8M
/*0 */ static inline uint32_t nvic_gprio_mask(NVICState *s)  // (0) 0.4468
/*2 */ {                                                     // (2) 0.02128
/*4 */     return ~0U << (s->prigroup + 1);                  // (1) 0.3404
/*6 */ }                                                     // (3) 0.02128
