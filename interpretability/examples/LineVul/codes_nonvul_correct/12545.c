// commit message qemu@d4c430a80f (target=0, prob=0.024103204, correct=True): Large page TLB flush
/*0   */ static int get_phys_addr_v5(CPUState *env, uint32_t address, int access_type,  // (2) 0.05273
/*2   */ 			    int is_user, uint32_t *phys_ptr, int *prot)                             // (3) 0.04688
/*4   */ {                                                                              // (36) 0.001953
/*6   */     int code;                                                                  // (29) 0.01172
/*8   */     uint32_t table;                                                            // (25) 0.01758
/*10  */     uint32_t desc;                                                             // (26) 0.01758
/*12  */     int type;                                                                  // (32) 0.01172
/*14  */     int ap;                                                                    // (30) 0.01172
/*16  */     int domain;                                                                // (31) 0.01172
/*18  */     uint32_t phys_addr;                                                        // (19) 0.02148
/*22  */     /* Pagetable walk.  */                                                     // (18) 0.02148
/*24  */     /* Lookup l1 descriptor.  */                                               // (17) 0.02344
/*26  */     table = get_level1_table_address(env, address);                            // (6) 0.03516
/*28  */     desc = ldl_phys(table);                                                    // (16) 0.02344
/*30  */     type = (desc & 3);                                                         // (22) 0.01953
/*32  */     domain = (env->cp15.c3 >> ((desc >> 4) & 0x1e)) & 3;                       // (1) 0.05469
/*34  */     if (type == 0) {                                                           // (23) 0.01953
/*36  */         /* Section translation fault.  */                                      // (10) 0.02734
/*38  */         code = 5;                                                              // (20) 0.02148
/*40  */         goto do_fault;                                                         // (13) 0.02539
/*42  */     }                                                                          // (34) 0.007812
/*44  */     if (domain == 0 || domain == 2) {                                          // (11) 0.02734
/*46  */         if (type == 2)                                                         // (14) 0.02539
/*48  */             code = 9; /* Section domain fault.  */                             // (5) 0.04297
/*50  */         else                                                                   // (28) 0.01562
/*52  */             code = 11; /* Page domain fault.  */                               // (4) 0.04297
/*54  */         goto do_fault;                                                         // (15) 0.02539
/*56  */     }                                                                          // (35) 0.007812
/*58  */     if (type == 2) {                                                           // (24) 0.01953
/*60  */         /* 1Mb section.  */                                                    // (9) 0.0293
/*62  */         phys_addr = (desc & 0xfff00000) | (address & 0x000fffff);              // (0) 0.05664
/*64  */         ap = (desc >> 10) & 3;                                                 // (7) 0.0332
/*66  */         code = 13;                                                             // (21) 0.02148
/*68  */     } else {                                                                   // (33) 0.01172
/*70  */         /* Lookup l2 entry.  */                                                // (8) 0.03125
/*72  */ 	if (type == 1) {                                                              // (27) 0.01563
/*74  */ 	    /* Coarse pagetable.  */                                                  // (12) 0.02539
/*76  */ 	    table = (desc & 0xfffffc00) | ((address >> 10) & 0x3fc);                  // 0.0
/*78  */ 	} else {                                                                      // 0.0
/*80  */ 	    /* Fine pagetable.  */                                                    // 0.0
/*82  */ 	    table = (desc & 0xfffff000) | ((address >> 8) & 0xffc);                   // 0.0
/*84  */ 	}                                                                             // 0.0
/*86  */         desc = ldl_phys(table);                                                // 0.0
/*88  */         switch (desc & 3) {                                                    // 0.0
/*90  */         case 0: /* Page translation fault.  */                                 // 0.0
/*92  */             code = 7;                                                          // 0.0
/*94  */             goto do_fault;                                                     // 0.0
/*96  */         case 1: /* 64k page.  */                                               // 0.0
/*98  */             phys_addr = (desc & 0xffff0000) | (address & 0xffff);              // 0.0
/*100 */             ap = (desc >> (4 + ((address >> 13) & 6))) & 3;                    // 0.0
/*102 */             break;                                                             // 0.0
/*104 */         case 2: /* 4k page.  */                                                // 0.0
/*106 */             phys_addr = (desc & 0xfffff000) | (address & 0xfff);               // 0.0
/*108 */             ap = (desc >> (4 + ((address >> 13) & 6))) & 3;                    // 0.0
/*110 */             break;                                                             // 0.0
/*112 */         case 3: /* 1k page.  */                                                // 0.0
/*114 */ 	    if (type == 1) {                                                          // 0.0
/*116 */ 		if (arm_feature(env, ARM_FEATURE_XSCALE)) {                                  // 0.0
/*118 */ 		    phys_addr = (desc & 0xfffff000) | (address & 0xfff);                     // 0.0
/*120 */ 		} else {                                                                     // 0.0
/*122 */ 		    /* Page translation fault.  */                                           // 0.0
/*124 */ 		    code = 7;                                                                // 0.0
/*126 */ 		    goto do_fault;                                                           // 0.0
/*128 */ 		}                                                                            // 0.0
/*130 */ 	    } else {                                                                  // 0.0
/*132 */ 		phys_addr = (desc & 0xfffffc00) | (address & 0x3ff);                         // 0.0
/*134 */ 	    }                                                                         // 0.0
/*136 */             ap = (desc >> 4) & 3;                                              // 0.0
/*138 */             break;                                                             // 0.0
/*140 */         default:                                                               // 0.0
/*142 */             /* Never happens, but compiler isn't smart enough to tell.  */     // 0.0
/*144 */             abort();                                                           // 0.0
/*146 */         }                                                                      // 0.0
/*148 */         code = 15;                                                             // 0.0
/*150 */     }                                                                          // 0.0
/*152 */     *prot = check_ap(env, ap, domain, access_type, is_user);                   // 0.0
/*154 */     if (!*prot) {                                                              // 0.0
/*156 */         /* Access permission fault.  */                                        // 0.0
/*158 */         goto do_fault;                                                         // 0.0
/*160 */     }                                                                          // 0.0
/*162 */     *phys_ptr = phys_addr;                                                     // 0.0
/*164 */     return 0;                                                                  // 0.0
/*166 */ do_fault:                                                                      // 0.0
/*168 */     return code | (domain << 4);                                               // 0.0
/*170 */ }                                                                              // 0.0
