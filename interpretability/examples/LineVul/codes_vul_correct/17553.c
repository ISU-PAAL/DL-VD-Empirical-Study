// commit message qemu@9217e26f43 (target=1, prob=0.68461776, correct=True): vvfat: Fix double free for opening the image rw
/*0 */ static int write_target_commit(BlockDriverState *bs, int64_t sector_num,  // (0) 0.2821
/*2 */ 	const uint8_t* buffer, int nb_sectors) {                                 // (2) 0.2179
/*4 */     BDRVVVFATState* s = bs->opaque;                                       // (1) 0.2564
/*6 */     return try_commit(s);                                                 // (3) 0.1282
/*8 */ }                                                                         // (4) 0.01282
