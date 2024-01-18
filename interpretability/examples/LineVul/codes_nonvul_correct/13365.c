// commit message qemu@46181129ea (target=0, prob=0.24321795, correct=True): block: Ignore multiple children in bdrv_check_update_perm()
/*0  */ static int bdrv_check_update_perm(BlockDriverState *bs, uint64_t new_used_perm,   // (7) 0.05469
/*2  */                                   uint64_t new_shared_perm,                       // (2) 0.08398
/*4  */                                   BdrvChild *ignore_child, Error **errp)          // (0) 0.0918
/*6  */ {                                                                                 // (18) 0.001953
/*8  */     BdrvChild *c;                                                                 // (16) 0.01953
/*10 */     uint64_t cumulative_perms = new_used_perm;                                    // (13) 0.03516
/*12 */     uint64_t cumulative_shared_perms = new_shared_perm;                           // (11) 0.03906
/*16 */     /* There is no reason why anyone couldn't tolerate write_unchanged */         // (12) 0.03516
/*18 */     assert(new_shared_perm & BLK_PERM_WRITE_UNCHANGED);                           // (9) 0.04688
/*22 */     QLIST_FOREACH(c, &bs->parents, next_parent) {                                 // (10) 0.04102
/*24 */         if (c == ignore_child) {                                                  // (14) 0.03125
/*26 */             continue;                                                             // (15) 0.02539
/*28 */         }                                                                         // (17) 0.01562
/*32 */         if ((new_used_perm & c->shared_perm) != new_used_perm) {                  // (6) 0.05664
/*34 */             char *user = bdrv_child_user_desc(c);                                 // (8) 0.05273
/*36 */             char *perm_names = bdrv_perm_names(new_used_perm & ~c->shared_perm);  // (3) 0.07422
/*38 */             error_setg(errp, "Conflicts with use by %s as '%s', which does not "  // (5) 0.07031
/*40 */                              "allow '%s' on %s",                                  // (4) 0.07422
/*42 */                        user, c->name, perm_names, bdrv_get_node_name(c->bs));     // (1) 0.08984
/*44 */             g_free(user);                                                         // 0.0
/*46 */             g_free(perm_names);                                                   // 0.0
/*48 */             return -EPERM;                                                        // 0.0
/*50 */         }                                                                         // 0.0
/*54 */         if ((c->perm & new_shared_perm) != c->perm) {                             // 0.0
/*56 */             char *user = bdrv_child_user_desc(c);                                 // 0.0
/*58 */             char *perm_names = bdrv_perm_names(c->perm & ~new_shared_perm);       // 0.0
/*60 */             error_setg(errp, "Conflicts with use by %s as '%s', which uses "      // 0.0
/*62 */                              "'%s' on %s",                                        // 0.0
/*64 */                        user, c->name, perm_names, bdrv_get_node_name(c->bs));     // 0.0
/*66 */             g_free(user);                                                         // 0.0
/*68 */             g_free(perm_names);                                                   // 0.0
/*70 */             return -EPERM;                                                        // 0.0
/*72 */         }                                                                         // 0.0
/*76 */         cumulative_perms |= c->perm;                                              // 0.0
/*78 */         cumulative_shared_perms &= c->shared_perm;                                // 0.0
/*80 */     }                                                                             // 0.0
/*84 */     return bdrv_check_perm(bs, cumulative_perms, cumulative_shared_perms, errp);  // 0.0
/*86 */ }                                                                                 // 0.0
