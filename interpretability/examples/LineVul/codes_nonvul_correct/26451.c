// commit message qemu@a8170e5e97 (target=0, prob=0.010532256, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ dma_read(void *opaque, target_phys_addr_t addr, unsigned int size)  // (1) 0.07591
/*2  */ {                                                                   // (25) 0.0033
/*4  */         struct fs_dma_ctrl *ctrl = opaque;                          // (3) 0.06271
/*6  */ 	int c;                                                             // (19) 0.0132
/*8  */ 	uint32_t r = 0;                                                    // (10) 0.0297
/*12 */ 	if (size != 4) {                                                   // (12) 0.0264
/*14 */ 		dma_rinvalid(opaque, addr);                                       // (8) 0.0429
/*16 */ 	}                                                                  // (22) 0.006601
/*20 */ 	/* Make addr relative to this channel and bounded to nr regs.  */  // (5) 0.05941
/*22 */ 	c = fs_channel(addr);                                              // (11) 0.0297
/*24 */ 	addr &= 0xff;                                                      // (13) 0.0231
/*26 */ 	addr >>= 2;                                                        // (15) 0.0198
/*28 */ 	switch (addr)                                                      // (16) 0.0165
/*30 */ 	{                                                                  // (23) 0.006601
/*32 */ 		case RW_STAT:                                                     // (14) 0.0231
/*34 */ 			r = ctrl->channels[c].state & 7;                                 // (7) 0.05611
/*36 */ 			r |= ctrl->channels[c].eol << 5;                                 // (4) 0.06271
/*38 */ 			r |= ctrl->channels[c].stream_cmd_src << 8;                      // (2) 0.07261
/*40 */ 			break;                                                           // (17) 0.0165
/*44 */ 		default:                                                          // (20) 0.0132
/*46 */ 			r = ctrl->channels[c].regs[addr];                                // (6) 0.05941
/*48 */ 			D(printf ("%s c=%d addr=" TARGET_FMT_plx "\n",                   // (0) 0.08581
/*50 */ 				  __func__, c, addr));                                          // (9) 0.0429
/*52 */ 			break;                                                           // (18) 0.0165
/*54 */ 	}                                                                  // (24) 0.006601
/*56 */ 	return r;                                                          // (21) 0.0132
/*58 */ }                                                                   // (26) 0.0033
