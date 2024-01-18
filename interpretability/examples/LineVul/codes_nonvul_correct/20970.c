// commit message qemu@a659979328 (target=0, prob=0.06265011, correct=True): block: clarify the meaning of BDRV_O_NOCACHE
/*0  */ open_f(int argc, char **argv)                       // (5) 0.04348
/*2  */ {                                                   // (29) 0.003344
/*4  */ 	int flags = 0;                                     // (16) 0.02007
/*6  */ 	int readonly = 0;                                  // (12) 0.02341
/*8  */ 	int growable = 0;                                  // (13) 0.02341
/*10 */ 	int c;                                             // (25) 0.01338
/*14 */ 	while ((c = getopt(argc, argv, "snrg")) != EOF) {  // (0) 0.07692
/*16 */ 		switch (c) {                                      // (14) 0.02341
/*18 */ 		case 's':                                         // (17) 0.02007
/*20 */ 			flags |= BDRV_O_SNAPSHOT;                        // (2) 0.05686
/*22 */ 			break;                                           // (21) 0.01672
/*24 */ 		case 'n':                                         // (18) 0.02007
/*26 */ 			flags |= BDRV_O_NOCACHE;                         // (3) 0.05686
/*28 */ 			break;                                           // (22) 0.01672
/*30 */ 		case 'r':                                         // (19) 0.02007
/*32 */ 			readonly = 1;                                    // (9) 0.02676
/*34 */ 			break;                                           // (23) 0.01672
/*36 */ 		case 'g':                                         // (20) 0.02007
/*38 */ 			growable = 1;                                    // (10) 0.02676
/*40 */ 			break;                                           // (24) 0.01672
/*42 */ 		default:                                          // (26) 0.01338
/*44 */ 			return command_usage(&open_cmd);                 // (6) 0.04013
/*46 */ 		}                                                 // (27) 0.01003
/*48 */ 	}                                                  // (28) 0.006689
/*52 */ 	if (!readonly) {                                   // (15) 0.02341
/*54 */             flags |= BDRV_O_RDWR;                   // (1) 0.07692
/*56 */         }                                           // (11) 0.02676
/*60 */ 	if (optind != argc - 1)                            // (7) 0.03679
/*62 */ 		return command_usage(&open_cmd);                  // (8) 0.03679
/*66 */ 	return openfile(argv[optind], flags, growable);    // (4) 0.05351
/*68 */ }                                                   // (30) 0.003344
