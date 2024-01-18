// commit message qemu@40ff6d7e8d (target=1, prob=0.4314764, correct=False): Don't leak file descriptors
/*0  */ udp_listen(Slirp *slirp, u_int32_t haddr, u_int hport, u_int32_t laddr,  // (0) 0.07422
/*2  */            u_int lport, int flags)                                       // (7) 0.03711
/*4  */ {                                                                        // (33) 0.001953
/*6  */ 	struct sockaddr_in addr;                                                // (24) 0.01563
/*8  */ 	struct socket *so;                                                      // (26) 0.01172
/*10 */ 	socklen_t addrlen = sizeof(struct sockaddr_in), opt = 1;                // (5) 0.04102
/*14 */ 	so = socreate(slirp);                                                   // (20) 0.02148
/*16 */ 	if (!so) {                                                              // (27) 0.01172
/*18 */ 	    return NULL;                                                        // (25) 0.01367
/*20 */ 	}                                                                       // (31) 0.003906
/*22 */ 	so->s = socket(AF_INET,SOCK_DGRAM,0);                                   // (4) 0.04102
/*24 */ 	so->so_expire = curtime + SO_EXPIRE;                                    // (10) 0.0332
/*26 */ 	insque(so, &slirp->udb);                                                // (15) 0.02734
/*30 */ 	addr.sin_family = AF_INET;                                              // (18) 0.02344
/*32 */ 	addr.sin_addr.s_addr = haddr;                                           // (16) 0.02734
/*34 */ 	addr.sin_port = hport;                                                  // (22) 0.01953
/*38 */ 	if (bind(so->s,(struct sockaddr *)&addr, addrlen) < 0) {                // (2) 0.04687
/*40 */ 		udp_detach(so);                                                        // (23) 0.01953
/*42 */ 		return NULL;                                                           // (28) 0.009766
/*44 */ 	}                                                                       // (30) 0.003906
/*46 */ 	setsockopt(so->s,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,sizeof(int));     // (1) 0.06641
/*50 */ 	getsockname(so->s,(struct sockaddr *)&addr,&addrlen);                   // (6) 0.04102
/*52 */ 	so->so_fport = addr.sin_port;                                           // (17) 0.02734
/*54 */ 	if (addr.sin_addr.s_addr == 0 ||                                        // (12) 0.0293
/*56 */ 	    addr.sin_addr.s_addr == loopback_addr.s_addr) {                     // (3) 0.04687
/*58 */ 	   so->so_faddr = slirp->vhost_addr;                                    // (8) 0.03711
/*60 */ 	} else {                                                                // (29) 0.007812
/*62 */ 	   so->so_faddr = addr.sin_addr;                                        // (11) 0.03125
/*64 */ 	}                                                                       // (32) 0.003906
/*66 */ 	so->so_lport = lport;                                                   // (21) 0.02148
/*68 */ 	so->so_laddr.s_addr = laddr;                                            // (13) 0.0293
/*70 */ 	if (flags != SS_FACCEPTONCE)                                            // (14) 0.02734
/*72 */ 	   so->so_expire = 0;                                                   // (19) 0.02344
/*76 */ 	so->so_state &= SS_PERSISTENT_MASK;                                     // (9) 0.03516
/*78 */ 	so->so_state |= SS_ISFCONNECTED | flags;                                // 0.0
/*82 */ 	return so;                                                              // 0.0
/*84 */ }                                                                        // 0.0
