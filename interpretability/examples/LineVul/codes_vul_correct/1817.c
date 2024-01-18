// commit message qemu@97f1c45c6f (target=1, prob=0.64133, correct=True): vpc/vhd: add bounds check for max_table_entries and block_size (CVE-2014-0144)
/*0  */ static void vpc_close(BlockDriverState *bs)     // (5) 0.1083
/*2  */ {                                               // (8) 0.008333
/*4  */     BDRVVPCState *s = bs->opaque;               // (0) 0.15
/*6  */     g_free(s->pagetable);                       // (4) 0.1167
/*8  */ #ifdef CACHE                                    // (6) 0.05
/*10 */     g_free(s->pageentry_u8);                    // (2) 0.125
/*12 */ #endif                                          // (7) 0.01667
/*16 */     migrate_del_blocker(s->migration_blocker);  // (1) 0.15
/*18 */     error_free(s->migration_blocker);           // (3) 0.125
/*20 */ }                                               // (9) 0.008333
