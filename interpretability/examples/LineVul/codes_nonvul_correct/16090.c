// commit message qemu@a7824a886e (target=0, prob=0.032405954, correct=True): qemu-io: Rework alloc command
/*0  */ alloc_f(int argc, char **argv)                                // (8) 0.04235
/*2  */ {                                                             // (26) 0.003257
/*4  */ 	int64_t offset;                                              // (16) 0.0228
/*6  */ 	int nb_sectors;                                              // (14) 0.02606
/*8  */ 	char s1[64];                                                 // (17) 0.0228
/*10 */ 	int num;                                                     // (20) 0.01303
/*12 */ 	int ret;                                                     // (21) 0.01303
/*14 */ 	const char *retstr;                                          // (18) 0.0228
/*18 */ 	offset = cvtnum(argv[1]);                                    // (9) 0.03909
/*20 */ 	if (offset & 0x1ff) {                                        // (10) 0.03583
/*22 */ 		printf("offset %lld is not sector aligned\n",               // (5) 0.04886
/*24 */ 			(long long)offset);                                        // (12) 0.02932
/*26 */ 		return 0;                                                   // (19) 0.01629
/*28 */ 	}                                                            // (23) 0.006515
/*32 */ 	if (argc == 3)                                               // (15) 0.02606
/*34 */ 		nb_sectors = cvtnum(argv[2]);                               // (4) 0.05212
/*36 */ 	else                                                         // (24) 0.006515
/*38 */ 		nb_sectors = 1;                                             // (13) 0.02932
/*42 */ 	ret = bdrv_is_allocated(bs, offset >> 9, nb_sectors, &num);  // (0) 0.08795
/*46 */ 	cvtstr(offset, s1, sizeof(s1));                              // (6) 0.04886
/*50 */ 	retstr = ret ? "allocated" : "not allocated";                // (7) 0.04886
/*52 */ 	if (nb_sectors == 1)                                         // (11) 0.03257
/*54 */ 		printf("sector %s at offset %s\n", retstr, s1);             // (1) 0.06515
/*56 */ 	else                                                         // (25) 0.006515
/*58 */ 		printf("%d/%d sectors %s at offset %s\n",                   // (2) 0.06189
/*60 */ 			num, nb_sectors, retstr, s1);                              // (3) 0.05537
/*62 */ 	return 0;                                                    // (22) 0.01303
/*64 */ }                                                             // (27) 0.003257
