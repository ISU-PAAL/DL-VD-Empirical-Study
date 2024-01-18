// commit message qemu@02acedf93d (target=0, prob=0.9662091, correct=False): target-arm: Move Neon VUZP to helper functions
/*0  */ static void gen_neon_unzip(int reg, int q, int tmp, int size)                        // (4) 0.0756
/*2  */ {                                                                                    // (15) 0.003436
/*4  */     int n;                                                                           // (13) 0.02062
/*6  */     TCGv t0, t1;                                                                     // (9) 0.04124
/*10 */     for (n = 0; n < q + 1; n += 2) {                                                 // (7) 0.06873
/*12 */         t0 = neon_load_reg(reg, n);                                                  // (6) 0.06873
/*14 */         t1 = neon_load_reg(reg, n + 1);                                              // (3) 0.0756
/*16 */         switch (size) {                                                              // (10) 0.04124
/*18 */         case 0: gen_neon_unzip_u8(t0, t1); break;                                    // (1) 0.09966
/*20 */         case 1: gen_neon_zip_u16(t0, t1); break; /* zip and unzip are the same.  */  // (0) 0.134
/*22 */         case 2: /* no-op */; break;                                                  // (8) 0.06186
/*24 */         default: abort();                                                            // (11) 0.0378
/*26 */         }                                                                            // (12) 0.02749
/*28 */         neon_store_scratch(tmp + n, t0);                                             // (5) 0.07216
/*30 */         neon_store_scratch(tmp + n + 1, t1);                                         // (2) 0.07904
/*32 */     }                                                                                // (14) 0.01375
/*34 */ }                                                                                    // (16) 0.003436
