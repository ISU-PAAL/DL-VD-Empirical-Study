// commit message qemu@07caea315a (target=1, prob=0.94285476, correct=True): Fix pci_add nic not to exit on bad model
/*0  */ int qemu_check_nic_model_list(NICInfo *nd, const char * const *models,    // (4) 0.07471
/*2  */                               const char *default_model)                  // (1) 0.1034
/*4  */ {                                                                         // (16) 0.002874
/*6  */     int i, exit_status = 0;                                               // (12) 0.03448
/*10 */     if (!nd->model)                                                       // (13) 0.02586
/*12 */         nd->model = strdup(default_model);                                // (6) 0.05747
/*16 */     if (strcmp(nd->model, "?") != 0) {                                    // (7) 0.0546
/*18 */         for (i = 0 ; models[i]; i++)                                      // (8) 0.0546
/*20 */             if (strcmp(nd->model, models[i]) == 0)                        // (3) 0.07759
/*22 */                 return i;                                                 // (9) 0.05172
/*26 */         fprintf(stderr, "qemu: Unsupported NIC model: %s\n", nd->model);  // (2) 0.0977
/*28 */         exit_status = 1;                                                  // (11) 0.03736
/*30 */     }                                                                     // (15) 0.01149
/*34 */     fprintf(stderr, "qemu: Supported NIC models: ");                      // (5) 0.06034
/*36 */     for (i = 0 ; models[i]; i++)                                          // (10) 0.0431
/*38 */         fprintf(stderr, "%s%c", models[i], models[i+1] ? ',' : '\n');     // (0) 0.1063
/*42 */     exit(exit_status);                                                    // (14) 0.02586
/*44 */ }                                                                         // (17) 0.002874
