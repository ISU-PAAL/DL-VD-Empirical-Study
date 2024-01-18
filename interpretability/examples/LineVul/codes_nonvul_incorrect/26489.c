// commit message qemu@2d26512b45 (target=0, prob=0.9867191, correct=False): slirp: Fix compiler warning for w64
/*0   */ int cksum(struct mbuf *m, int len)                            // (7) 0.02734
/*2   */ {                                                             // (46) 0.001953
/*4   */ 	register uint16_t *w;                                        // (17) 0.01758
/*6   */ 	register int sum = 0;                                        // (25) 0.01367
/*8   */ 	register int mlen = 0;                                       // (22) 0.01563
/*10  */ 	int byte_swapped = 0;                                        // (16) 0.01758
/*14  */ 	union {                                                      // (37) 0.005859
/*16  */ 		uint8_t  c[2];                                              // (12) 0.02148
/*18  */ 		uint16_t s;                                                 // (23) 0.01562
/*20  */ 	} s_util;                                                    // (30) 0.01172
/*22  */ 	union {                                                      // (38) 0.005859
/*24  */ 		uint16_t s[2];                                              // (15) 0.01953
/*26  */ 		uint32_t l;                                                 // (21) 0.01563
/*28  */ 	} l_util;                                                    // (29) 0.01172
/*32  */ 	if (m->m_len == 0)                                           // (11) 0.02148
/*34  */ 	   goto cont;                                                // (28) 0.01172
/*36  */ 	w = mtod(m, uint16_t *);                                     // (8) 0.02734
/*40  */ 	mlen = m->m_len;                                             // (14) 0.01953
/*44  */ 	if (len < mlen)                                              // (19) 0.01563
/*46  */ 	   mlen = len;                                               // (20) 0.01563
/*48  */ #ifdef DEBUG                                                  // (36) 0.007813
/*50  */ 	len -= mlen;                                                 // (31) 0.01172
/*52  */ #endif                                                        // (40) 0.003906
/*54  */ 	/*                                                           // (43) 0.003906
/*56  */ 	 * Force to even boundary.                                   // (26) 0.01367
/*58  */ 	 */                                                          // (44) 0.003906
/*60  */ 	if ((1 & (long) w) && (mlen > 0)) {                          // (6) 0.03516
/*62  */ 		REDUCE;                                                     // (32) 0.01172
/*64  */ 		sum <<= 8;                                                  // (27) 0.01367
/*66  */ 		s_util.c[0] = *(uint8_t *)w;                                // (5) 0.03906
/*68  */ 		w = (uint16_t *)((int8_t *)w + 1);                          // (4) 0.04102
/*70  */ 		mlen--;                                                     // (33) 0.01172
/*72  */ 		byte_swapped = 1;                                           // (18) 0.01758
/*74  */ 	}                                                            // (39) 0.003906
/*76  */ 	/*                                                           // (41) 0.003906
/*78  */ 	 * Unroll the loop to make overhead from                     // (13) 0.01953
/*80  */ 	 * branches &c small.                                        // (24) 0.01367
/*82  */ 	 */                                                          // (42) 0.003906
/*84  */ 	while ((mlen -= 32) >= 0) {                                  // (9) 0.02344
/*86  */ 		sum += w[0]; sum += w[1]; sum += w[2]; sum += w[3];         // (0) 0.05078
/*88  */ 		sum += w[4]; sum += w[5]; sum += w[6]; sum += w[7];         // (1) 0.05078
/*90  */ 		sum += w[8]; sum += w[9]; sum += w[10]; sum += w[11];       // (2) 0.05078
/*92  */ 		sum += w[12]; sum += w[13]; sum += w[14]; sum += w[15];     // (3) 0.05078
/*94  */ 		w += 16;                                                    // (34) 0.01172
/*96  */ 	}                                                            // (45) 0.003906
/*98  */ 	mlen += 32;                                                  // (35) 0.01172
/*100 */ 	while ((mlen -= 8) >= 0) {                                   // (10) 0.02344
/*102 */ 		sum += w[0]; sum += w[1]; sum += w[2]; sum += w[3];         // 0.0
/*104 */ 		w += 4;                                                     // 0.0
/*106 */ 	}                                                            // 0.0
/*108 */ 	mlen += 8;                                                   // 0.0
/*110 */ 	if (mlen == 0 && byte_swapped == 0)                          // 0.0
/*112 */ 	   goto cont;                                                // 0.0
/*114 */ 	REDUCE;                                                      // 0.0
/*116 */ 	while ((mlen -= 2) >= 0) {                                   // 0.0
/*118 */ 		sum += *w++;                                                // 0.0
/*120 */ 	}                                                            // 0.0
/*124 */ 	if (byte_swapped) {                                          // 0.0
/*126 */ 		REDUCE;                                                     // 0.0
/*128 */ 		sum <<= 8;                                                  // 0.0
/*130 */ 		if (mlen == -1) {                                           // 0.0
/*132 */ 			s_util.c[1] = *(uint8_t *)w;                               // 0.0
/*134 */ 			sum += s_util.s;                                           // 0.0
/*136 */ 			mlen = 0;                                                  // 0.0
/*138 */ 		} else                                                      // 0.0
/*142 */ 		   mlen = -1;                                               // 0.0
/*144 */ 	} else if (mlen == -1)                                       // 0.0
/*146 */ 	   s_util.c[0] = *(uint8_t *)w;                              // 0.0
/*150 */ cont:                                                         // 0.0
/*152 */ #ifdef DEBUG                                                  // 0.0
/*154 */ 	if (len) {                                                   // 0.0
/*156 */ 		DEBUG_ERROR((dfd, "cksum: out of data\n"));                 // 0.0
/*158 */ 		DEBUG_ERROR((dfd, " len = %d\n", len));                     // 0.0
/*160 */ 	}                                                            // 0.0
/*162 */ #endif                                                        // 0.0
/*164 */ 	if (mlen == -1) {                                            // 0.0
/*166 */ 		/* The last mbuf has odd # of bytes. Follow the             // 0.0
/*168 */ 		 standard (the odd byte may be shifted left by 8 bits       // 0.0
/*170 */ 			   or not as determined by endian-ness of the machine) */  // 0.0
/*172 */ 		s_util.c[1] = 0;                                            // 0.0
/*174 */ 		sum += s_util.s;                                            // 0.0
/*176 */ 	}                                                            // 0.0
/*178 */ 	REDUCE;                                                      // 0.0
/*180 */ 	return (~sum & 0xffff);                                      // 0.0
/*182 */ }                                                             // 0.0
