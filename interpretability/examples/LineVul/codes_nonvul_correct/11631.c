// commit message qemu@b2bedb2144 (target=0, prob=0.0071843844, correct=True): Remove blanks before \n in output strings
/*0  */ mst_fpga_readb(void *opaque, target_phys_addr_t addr)        // (0) 0.0615
/*2  */ {                                                            // (32) 0.002674
/*4  */ 	mst_irq_state *s = (mst_irq_state *) opaque;                // (1) 0.05882
/*8  */ 	switch (addr) {                                             // (28) 0.01604
/*10 */ 	case MST_LEDDAT1:                                           // (5) 0.02674
/*12 */ 		return s->leddat1;                                         // (20) 0.02406
/*14 */ 	case MST_LEDDAT2:                                           // (6) 0.02674
/*16 */ 		return s->leddat2;                                         // (21) 0.02406
/*18 */ 	case MST_LEDCTRL:                                           // (22) 0.02406
/*20 */ 		return s->ledctrl;                                         // (27) 0.02139
/*22 */ 	case MST_GPSWR:                                             // (23) 0.02406
/*24 */ 		return s->gpswr;                                           // (24) 0.02406
/*26 */ 	case MST_MSCWR1:                                            // (7) 0.02674
/*28 */ 		return s->mscwr1;                                          // (8) 0.02674
/*30 */ 	case MST_MSCWR2:                                            // (9) 0.02674
/*32 */ 		return s->mscwr2;                                          // (10) 0.02674
/*34 */ 	case MST_MSCWR3:                                            // (11) 0.02674
/*36 */ 		return s->mscwr3;                                          // (12) 0.02674
/*38 */ 	case MST_MSCRD:                                             // (25) 0.02406
/*40 */ 		return s->mscrd;                                           // (26) 0.02406
/*42 */ 	case MST_INTMSKENA:                                         // (13) 0.02674
/*44 */ 		return s->intmskena;                                       // (14) 0.02674
/*46 */ 	case MST_INTSETCLR:                                         // (4) 0.02941
/*48 */ 		return s->intsetclr;                                       // (15) 0.02674
/*50 */ 	case MST_PCMCIA0:                                           // (16) 0.02674
/*52 */ 		return s->pcmcia0;                                         // (17) 0.02674
/*54 */ 	case MST_PCMCIA1:                                           // (18) 0.02674
/*56 */ 		return s->pcmcia1;                                         // (19) 0.02674
/*58 */ 	default:                                                    // (30) 0.008021
/*60 */ 		printf("Mainstone - mst_fpga_readb: Bad register offset "  // (3) 0.05348
/*62 */ 			"0x" TARGET_FMT_plx " \n", addr);                         // (2) 0.05615
/*64 */ 	}                                                           // (31) 0.005348
/*66 */ 	return 0;                                                   // (29) 0.0107
/*68 */ }                                                            // (33) 0.002674
