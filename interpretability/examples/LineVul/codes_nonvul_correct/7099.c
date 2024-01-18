// commit message qemu@b2bedb2144 (target=0, prob=0.4585046, correct=True): Remove blanks before \n in output strings
/*0   */ unsigned long setup_arg_pages(void * mh, char ** argv, char ** env)                                                                                // (5) 0.04297
/*2   */ {                                                                                                                                                  // (32) 0.001953
/*4   */     unsigned long stack_base, error, size;                                                                                                         // (12) 0.02539
/*6   */     int i;                                                                                                                                         // (30) 0.01172
/*8   */     int * stack;                                                                                                                                   // (23) 0.01367
/*10  */     int argc, envc;                                                                                                                                // (19) 0.01953
/*14  */     /* Create enough stack to hold everything.  If we don't use                                                                                    // (7) 0.0332
/*16  */      * it for args, we'll use it for something else...                                                                                             // (8) 0.0332
/*18  */      */                                                                                                                                            // (31) 0.009766
/*20  */     size = stack_size;                                                                                                                             // (22) 0.01758
/*24  */     error = target_mmap(0,                                                                                                                         // (17) 0.02344
/*26  */                         size + qemu_host_page_size,                                                                                                // (1) 0.06836
/*28  */                         PROT_READ | PROT_WRITE,                                                                                                    // (2) 0.0625
/*30  */                         MAP_PRIVATE | MAP_ANONYMOUS,                                                                                               // (0) 0.07031
/*32  */                         -1, 0);                                                                                                                    // (3) 0.05469
/*34  */     if (error == -1)                                                                                                                               // (21) 0.01953
/*36  */         qerror("stk mmap");                                                                                                                        // (11) 0.0293
/*40  */     /* we reserve one extra page at the top of the stack as guard */                                                                               // (6) 0.03516
/*42  */     target_mprotect(error + size, qemu_host_page_size, PROT_NONE);                                                                                 // (4) 0.05273
/*46  */     stack_base = error + size;                                                                                                                     // (18) 0.02148
/*48  */     stack = (void*)stack_base;                                                                                                                     // (15) 0.02344
/*50  */ /*                                                                                                                                                 // (33) 0.001953
/*52  */  *    | STRING AREA |                                                                                                                              // (20) 0.01953
/*54  */  *    +-------------+                                                                                                                              // (28) 0.01367
/*56  */  *    |      0      |                                                                                                                              // (9) 0.0332
/*58  */ *    +-------------+                                                                                                                               // (24) 0.01367
/*60  */  *    |  apple[n]   |                                                                                                                              // (13) 0.02539
/*62  */  *    +-------------+                                                                                                                              // (26) 0.01367
/*64  */  *           :                                                                                                                                     // (16) 0.02344
/*66  */  *    +-------------+                                                                                                                              // (25) 0.01367
/*68  */  *    |  apple[0]   |                                                                                                                              // (14) 0.02539
/*70  */  *    +-------------+                                                                                                                              // (29) 0.01367
/*72  */  *    |      0      |                                                                                                                              // (10) 0.0332
/*74  */  *    +-------------+                                                                                                                              // (27) 0.01367
/*76  */  *    |    env[n]   |                                                                                                                              // 0.0
/*78  */  *    +-------------+                                                                                                                              // 0.0
/*80  */  *           :                                                                                                                                     // 0.0
/*82  */  *           :                                                                                                                                     // 0.0
/*84  */  *    +-------------+                                                                                                                              // 0.0
/*86  */  *    |    env[0]   |                                                                                                                              // 0.0
/*88  */  *    +-------------+                                                                                                                              // 0.0
/*90  */  *    |      0      |                                                                                                                              // 0.0
/*92  */  *    +-------------+                                                                                                                              // 0.0
/*94  */  *    | arg[argc-1] |                                                                                                                              // 0.0
/*96  */  *    +-------------+                                                                                                                              // 0.0
/*98  */  *           :                                                                                                                                     // 0.0
/*100 */  *           :                                                                                                                                     // 0.0
/*102 */  *    +-------------+                                                                                                                              // 0.0
/*104 */  *    |    arg[0]   |                                                                                                                              // 0.0
/*106 */  *    +-------------+                                                                                                                              // 0.0
/*108 */  *    |     argc    |                                                                                                                              // 0.0
/*110 */  *    +-------------+                                                                                                                              // 0.0
/*112 */  * sp->    |      mh     | address of where the a.out's file offset 0 is in memory                                                                 // 0.0
/*114 */  *    +-------------+                                                                                                                              // 0.0
/*116 */ */                                                                                                                                                 // 0.0
/*118 */     /* Construct the stack Stack grows down */                                                                                                     // 0.0
/*120 */     stack--;                                                                                                                                       // 0.0
/*124 */     /* XXX: string should go up there */                                                                                                           // 0.0
/*128 */     *stack = 0;                                                                                                                                    // 0.0
/*130 */     stack--;                                                                                                                                       // 0.0
/*134 */     /* Push the absolute path of our executable */                                                                                                 // 0.0
/*136 */     DPRINTF("pushing apple %s (0x%x)\n", (char*)argv[0], (int)argv[0]);                                                                            // 0.0
/*138 */     stl(stack, (int) argv[0]);                                                                                                                     // 0.0
/*142 */     stack--;                                                                                                                                       // 0.0
/*146 */     stl(stack, 0);                                                                                                                                 // 0.0
/*148 */     stack--;                                                                                                                                       // 0.0
/*152 */     /* Get envc */                                                                                                                                 // 0.0
/*154 */     for(envc = 0; env[envc]; envc++);                                                                                                              // 0.0
/*158 */     for(i = envc-1; i >= 0; i--)                                                                                                                   // 0.0
/*160 */     {                                                                                                                                              // 0.0
/*162 */         DPRINTF("pushing env %s (0x%x)\n", (char*)env[i], (int)env[i]);                                                                            // 0.0
/*164 */         stl(stack, (int)env[i]);                                                                                                                   // 0.0
/*166 */         stack--;                                                                                                                                   // 0.0
/*170 */         /* XXX: remove that when string will be on top of the stack */                                                                             // 0.0
/*172 */         page_set_flags((int)env[i], (int)(env[i]+strlen(env[i])), PROT_READ | PAGE_VALID);                                                         // 0.0
/*174 */     }                                                                                                                                              // 0.0
/*178 */     /* Add on the stack the interp_prefix choosen if so */                                                                                         // 0.0
/*180 */     if(interp_prefix[0])                                                                                                                           // 0.0
/*182 */     {                                                                                                                                              // 0.0
/*184 */         char *dyld_root;                                                                                                                           // 0.0
/*186 */         asprintf(&dyld_root, "DYLD_ROOT_PATH=%s", interp_prefix);                                                                                  // 0.0
/*188 */         page_set_flags((int)dyld_root, (int)(dyld_root+strlen(interp_prefix)+1), PROT_READ | PAGE_VALID);                                          // 0.0
/*192 */         stl(stack, (int)dyld_root);                                                                                                                // 0.0
/*194 */         stack--;                                                                                                                                   // 0.0
/*196 */     }                                                                                                                                              // 0.0
/*200 */ #ifdef DONT_USE_DYLD_SHARED_MAP                                                                                                                    // 0.0
/*202 */     {                                                                                                                                              // 0.0
/*204 */         char *shared_map_mode;                                                                                                                     // 0.0
/*206 */         asprintf(&shared_map_mode, "DYLD_SHARED_REGION=avoid");                                                                                    // 0.0
/*208 */         page_set_flags((int)shared_map_mode, (int)(shared_map_mode+strlen(shared_map_mode)+1), PROT_READ | PAGE_VALID);                            // 0.0
/*212 */         stl(stack, (int)shared_map_mode);                                                                                                          // 0.0
/*214 */         stack--;                                                                                                                                   // 0.0
/*216 */     }                                                                                                                                              // 0.0
/*218 */ #endif                                                                                                                                             // 0.0
/*222 */ #ifdef ACTIVATE_DYLD_TRACE                                                                                                                         // 0.0
/*224 */     char * extra_env_static[] = {"DYLD_DEBUG_TRACE=yes",                                                                                           // 0.0
/*226 */     "DYLD_PREBIND_DEBUG=3", "DYLD_UNKNOW_TRACE=yes",                                                                                               // 0.0
/*228 */     "DYLD_PRINT_INITIALIZERS=yes",                                                                                                                 // 0.0
/*230 */     "DYLD_PRINT_SEGMENTS=yes", "DYLD_PRINT_REBASINGS=yes", "DYLD_PRINT_BINDINGS=yes", "DYLD_PRINT_INITIALIZERS=yes", "DYLD_PRINT_WARNINGS=yes" };  // 0.0
/*234 */     char ** extra_env = malloc(sizeof(extra_env_static));                                                                                          // 0.0
/*236 */     bcopy(extra_env_static, extra_env, sizeof(extra_env_static));                                                                                  // 0.0
/*238 */     page_set_flags((int)extra_env, (int)((void*)extra_env+sizeof(extra_env_static)), PROT_READ | PAGE_VALID);                                      // 0.0
/*242 */     for(i = 0; i<9; i++)                                                                                                                           // 0.0
/*244 */     {                                                                                                                                              // 0.0
/*246 */         DPRINTF("pushing (extra) env %s (0x%x)\n", (char*)extra_env[i], (int)extra_env[i]);                                                        // 0.0
/*248 */         stl(stack, (int) extra_env[i]);                                                                                                            // 0.0
/*250 */         stack--;                                                                                                                                   // 0.0
/*252 */     }                                                                                                                                              // 0.0
/*254 */ #endif                                                                                                                                             // 0.0
/*258 */     stl(stack, 0);                                                                                                                                 // 0.0
/*260 */     stack--;                                                                                                                                       // 0.0
/*264 */     /* Get argc */                                                                                                                                 // 0.0
/*266 */     for(argc = 0; argv[argc]; argc++);                                                                                                             // 0.0
/*270 */     for(i = argc-1; i >= 0; i--)                                                                                                                   // 0.0
/*272 */     {                                                                                                                                              // 0.0
/*274 */         DPRINTF("pushing arg %s (0x%x)\n", (char*)argv[i], (int)argv[i]);                                                                          // 0.0
/*276 */         stl(stack, (int) argv[i]);                                                                                                                 // 0.0
/*278 */         stack--;                                                                                                                                   // 0.0
/*282 */         /* XXX: remove that when string will be on top of the stack */                                                                             // 0.0
/*284 */         page_set_flags((int)argv[i], (int)(argv[i]+strlen(argv[i])), PROT_READ | PAGE_VALID);                                                      // 0.0
/*286 */     }                                                                                                                                              // 0.0
/*290 */     DPRINTF("pushing argc %d \n", argc);                                                                                                           // 0.0
/*292 */     stl(stack, argc);                                                                                                                              // 0.0
/*294 */     stack--;                                                                                                                                       // 0.0
/*298 */     DPRINTF("pushing mh 0x%x \n", (int)mh);                                                                                                        // 0.0
/*300 */     stl(stack, (int) mh);                                                                                                                          // 0.0
/*304 */     /* Stack points on the mh */                                                                                                                   // 0.0
/*306 */     return (unsigned long)stack;                                                                                                                   // 0.0
/*308 */ }                                                                                                                                                  // 0.0
