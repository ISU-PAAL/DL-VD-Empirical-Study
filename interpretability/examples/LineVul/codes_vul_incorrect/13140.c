// commit message qemu@afcf905cff (target=1, prob=0.33275327, correct=False): hw/acpi/aml-build: Fix memory leak
/*0 */ static void aml_free(gpointer data, gpointer user_data)  // (0) 0.34
/*2 */ {                                                        // (3) 0.02
/*4 */     Aml *var = data;                                     // (2) 0.2
/*6 */     build_free_array(var->buf);                          // (1) 0.26
/*9 */ }                                                        // (4) 0.02
