// commit message qemu@f5babeacc4 (target=0, prob=0.6280583, correct=False): spapr_drc: use g_strdup_printf() instead of snprintf()
/*0  */ sPAPRDRConnector *spapr_drc_by_index(uint32_t index)                   // (1) 0.1983
/*2  */ {                                                                      // (7) 0.008264
/*4  */     Object *obj;                                                       // (5) 0.05785
/*6  */     char name[256];                                                    // (4) 0.06611
/*10 */     snprintf(name, sizeof(name), "%s/%x", DRC_CONTAINER_PATH, index);  // (0) 0.2397
/*12 */     obj = object_resolve_path(name, NULL);                             // (3) 0.1322
/*16 */     return !obj ? NULL : SPAPR_DR_CONNECTOR(obj);                      // (2) 0.1736
/*18 */ }                                                                      // (6) 0.008264
