// commit message qemu@1ac157da77 (target=0, prob=0.00975556, correct=True): more precise TLB invalidation - init cleanup
/*0  */ void cpu_x86_init_mmu(CPUX86State *env)  // (0) 0.2195
/*2  */ {                                        // (5) 0.0122
/*4  */     a20_enabled = 1;                     // (4) 0.122
/*6  */     a20_mask = 0xffffffff;               // (2) 0.1585
/*10 */     last_pg_state = -1;                  // (3) 0.1463
/*12 */     cpu_x86_update_cr0(env);             // (1) 0.1829
/*14 */ }                                        // (6) 0.0122
