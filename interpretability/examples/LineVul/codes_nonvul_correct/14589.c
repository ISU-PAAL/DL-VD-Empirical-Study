// commit message qemu@9c4bab2668 (target=0, prob=0.07159675, correct=True): qemu-io: add flag to mark files growable
/*0  */ static int openfile(char *name, int flags)                        // (3) 0.07643
/*2  */ {                                                                 // (14) 0.006369
/*4  */ 	if (bs) {                                                        // (5) 0.03822
/*6  */ 		fprintf(stderr, "file open already, try 'help close'\n");       // (1) 0.1401
/*8  */ 		return 1;                                                       // (7) 0.03185
/*10 */ 	}                                                                // (12) 0.01274
/*14 */ 	bs = bdrv_new("hda");                                            // (4) 0.07643
/*16 */ 	if (!bs)                                                         // (8) 0.03185
/*18 */ 		return 1;                                                       // (9) 0.03185
/*22 */ 	if (bdrv_open(bs, name, flags) == -1) {                          // (2) 0.1274
/*24 */ 		fprintf(stderr, "%s: can't open device %s\n", progname, name);  // (0) 0.1656
/*26 */ 		bs = NULL;                                                      // (6) 0.03822
/*28 */ 		return 1;                                                       // (10) 0.03185
/*30 */ 	}                                                                // (13) 0.01274
/*34 */ 	return 0;                                                        // (11) 0.02548
/*36 */ }                                                                 // (15) 0.006369
