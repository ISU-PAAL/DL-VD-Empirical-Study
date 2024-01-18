// commit message qemu@a9c0183059 (target=0, prob=0.25795937, correct=True): hw/sd.c: convert wp_groups in SDState to bitfield
/*0  */ static void sd_reset(SDState *sd, BlockDriverState *bdrv)                 // (5) 0.04069
/*2  */ {                                                                         // (30) 0.002141
/*4  */     uint64_t size;                                                        // (24) 0.01927
/*6  */     uint64_t sect;                                                        // (25) 0.01927
/*10 */     if (bdrv) {                                                           // (23) 0.02141
/*12 */         bdrv_get_geometry(bdrv, &sect);                                   // (3) 0.04925
/*14 */     } else {                                                              // (28) 0.01285
/*16 */         sect = 0;                                                         // (20) 0.02355
/*18 */     }                                                                     // (29) 0.008565
/*20 */     size = sect << 9;                                                     // (26) 0.01927
/*24 */     sect = (size >> (HWBLOCK_SHIFT + SECTOR_SHIFT + WPGROUP_SHIFT)) + 1;  // (0) 0.07495
/*28 */     sd->state = sd_idle_state;                                            // (7) 0.02998
/*30 */     sd->rca = 0x0000;                                                     // (12) 0.0257
/*32 */     sd_set_ocr(sd);                                                       // (21) 0.02355
/*34 */     sd_set_scr(sd);                                                       // (13) 0.0257
/*36 */     sd_set_cid(sd);                                                       // (14) 0.0257
/*38 */     sd_set_csd(sd, size);                                                 // (8) 0.02998
/*40 */     sd_set_cardstatus(sd);                                                // (15) 0.0257
/*42 */     sd_set_sdstatus(sd);                                                  // (16) 0.0257
/*46 */     sd->bdrv = bdrv;                                                      // (10) 0.02784
/*50 */     if (sd->wp_groups)                                                    // (22) 0.02355
/*52 */         g_free(sd->wp_groups);                                            // (6) 0.0364
/*54 */     sd->wp_switch = bdrv ? bdrv_is_read_only(bdrv) : 0;                   // (1) 0.06424
/*56 */     sd->wp_groups = (int *) g_malloc0(sizeof(int) * sect);                // (2) 0.05567
/*58 */     memset(sd->function_group, 0, sizeof(int) * 6);                       // (4) 0.04497
/*60 */     sd->erase_start = 0;                                                  // (17) 0.0257
/*62 */     sd->erase_end = 0;                                                    // (18) 0.0257
/*64 */     sd->size = size;                                                      // (27) 0.01927
/*66 */     sd->blk_len = 0x200;                                                  // (9) 0.02998
/*68 */     sd->pwd_len = 0;                                                      // (19) 0.0257
/*70 */     sd->expecting_acmd = 0;                                               // (11) 0.02784
/*72 */ }                                                                         // (31) 0.002141
