// commit message qemu@4058fd98fd (target=0, prob=0.04386522, correct=True): x86: Filter out garbage from segment flags dump
/*0   */ cpu_x86_dump_seg_cache(CPUState *env, FILE *f, fprintf_function cpu_fprintf,    // (9) 0.05859
/*2   */                        const char *name, struct SegmentCache *sc)               // (7) 0.06641
/*4   */ {                                                                               // (19) 0.001953
/*6   */ #ifdef TARGET_X86_64                                                            // (13) 0.01953
/*8   */     if (env->hflags & HF_CS64_MASK) {                                           // (11) 0.03711
/*10  */         cpu_fprintf(f, "%-3s=%04x %016" PRIx64 " %08x %08x", name,              // (2) 0.07617
/*12  */                     sc->selector, sc->base, sc->limit, sc->flags);              // (6) 0.07031
/*14  */     } else                                                                      // (15) 0.009766
/*16  */ #endif                                                                          // (18) 0.003906
/*18  */     {                                                                           // (16) 0.007813
/*20  */         cpu_fprintf(f, "%-3s=%04x %08x %08x %08x", name, sc->selector,          // (3) 0.07617
/*22  */                     (uint32_t)sc->base, sc->limit, sc->flags);                  // (5) 0.07227
/*24  */     }                                                                           // (17) 0.007812
/*28  */     if (!(env->hflags & HF_PE_MASK) || !(sc->flags & DESC_P_MASK))              // (8) 0.06445
/*30  */         goto done;                                                              // (14) 0.01953
/*34  */     cpu_fprintf(f, " DPL=%d ", (sc->flags & DESC_DPL_MASK) >> DESC_DPL_SHIFT);  // (1) 0.08008
/*36  */     if (sc->flags & DESC_S_MASK) {                                              // (12) 0.03516
/*38  */         if (sc->flags & DESC_CS_MASK) {                                         // (10) 0.04297
/*40  */             cpu_fprintf(f, (sc->flags & DESC_L_MASK) ? "CS64" :                 // (4) 0.07227
/*42  */                            ((sc->flags & DESC_B_MASK) ? "CS32" : "CS16"));      // (0) 0.09766
/*44  */             cpu_fprintf(f, " [%c%c", (sc->flags & DESC_C_MASK) ? 'C' : '-',     // 0.0
/*46  */                         (sc->flags & DESC_R_MASK) ? 'R' : '-');                 // 0.0
/*48  */         } else {                                                                // 0.0
/*50  */             cpu_fprintf(f, (sc->flags & DESC_B_MASK) ? "DS  " : "DS16");        // 0.0
/*52  */             cpu_fprintf(f, " [%c%c", (sc->flags & DESC_E_MASK) ? 'E' : '-',     // 0.0
/*54  */                         (sc->flags & DESC_W_MASK) ? 'W' : '-');                 // 0.0
/*56  */         }                                                                       // 0.0
/*58  */         cpu_fprintf(f, "%c]", (sc->flags & DESC_A_MASK) ? 'A' : '-');           // 0.0
/*60  */     } else {                                                                    // 0.0
/*62  */         static const char *sys_type_name[2][16] = {                             // 0.0
/*64  */             { /* 32 bit mode */                                                 // 0.0
/*66  */                 "Reserved", "TSS16-avl", "LDT", "TSS16-busy",                   // 0.0
/*68  */                 "CallGate16", "TaskGate", "IntGate16", "TrapGate16",            // 0.0
/*70  */                 "Reserved", "TSS32-avl", "Reserved", "TSS32-busy",              // 0.0
/*72  */                 "CallGate32", "Reserved", "IntGate32", "TrapGate32"             // 0.0
/*74  */             },                                                                  // 0.0
/*76  */             { /* 64 bit mode */                                                 // 0.0
/*78  */                 "<hiword>", "Reserved", "LDT", "Reserved", "Reserved",          // 0.0
/*80  */                 "Reserved", "Reserved", "Reserved", "Reserved",                 // 0.0
/*82  */                 "TSS64-avl", "Reserved", "TSS64-busy", "CallGate64",            // 0.0
/*84  */                 "Reserved", "IntGate64", "TrapGate64"                           // 0.0
/*86  */             }                                                                   // 0.0
/*88  */         };                                                                      // 0.0
/*90  */         cpu_fprintf(f, "%s",                                                    // 0.0
/*92  */                     sys_type_name[(env->hflags & HF_LMA_MASK) ? 1 : 0]          // 0.0
/*94  */                                  [(sc->flags & DESC_TYPE_MASK)                  // 0.0
/*96  */                                   >> DESC_TYPE_SHIFT]);                         // 0.0
/*98  */     }                                                                           // 0.0
/*100 */ done:                                                                           // 0.0
/*102 */     cpu_fprintf(f, "\n");                                                       // 0.0
/*104 */ }                                                                               // 0.0
