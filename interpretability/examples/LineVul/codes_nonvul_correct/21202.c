// commit message qemu@f373431977 (target=0, prob=0.23397881, correct=True): slirp: Remove unneeded if_queued
/*0   */ void slirp_select_poll(fd_set *readfds, fd_set *writefds, fd_set *xfds,  // (0) 0.06641
/*2   */                        int select_error)                                 // (2) 0.05273
/*4   */ {                                                                        // (39) 0.001953
/*6   */     Slirp *slirp;                                                        // (20) 0.02148
/*8   */     struct socket *so, *so_next;                                         // (11) 0.02539
/*10  */     int ret;                                                             // (26) 0.01172
/*14  */     if (QTAILQ_EMPTY(&slirp_instances)) {                                // (6) 0.04102
/*16  */         return;                                                          // (22) 0.01758
/*18  */     }                                                                    // (30) 0.007812
/*22  */     global_readfds = readfds;                                            // (16) 0.02539
/*24  */     global_writefds = writefds;                                          // (13) 0.02539
/*26  */     global_xfds = xfds;                                                  // (18) 0.02344
/*30  */     curtime = qemu_get_clock_ms(rt_clock);                               // (7) 0.03906
/*34  */     QTAILQ_FOREACH(slirp, &slirp_instances, entry) {                     // (3) 0.05078
/*36  */ 	/*                                                                      // (37) 0.003906
/*38  */ 	 * See if anything has timed out                                        // (24) 0.01562
/*40  */ 	 */                                                                     // (36) 0.003906
/*42  */ 		if (time_fasttimo && ((curtime - time_fasttimo) >= 2)) {               // (5) 0.04687
/*44  */ 			tcp_fasttimo(slirp);                                                  // (8) 0.02734
/*46  */ 			time_fasttimo = 0;                                                    // (21) 0.02148
/*48  */ 		}                                                                      // (33) 0.005859
/*50  */ 		if (do_slowtimo && ((curtime - last_slowtimo) >= 499)) {               // (4) 0.04687
/*52  */ 			ip_slowtimo(slirp);                                                   // (14) 0.02539
/*54  */ 			tcp_slowtimo(slirp);                                                  // (9) 0.02734
/*56  */ 			last_slowtimo = curtime;                                              // (19) 0.02344
/*58  */ 		}                                                                      // (34) 0.005859
/*62  */ 	/*                                                                      // (35) 0.003906
/*64  */ 	 * Check sockets                                                        // (29) 0.007812
/*66  */ 	 */                                                                     // (38) 0.003906
/*68  */ 	if (!select_error) {                                                    // (23) 0.01562
/*70  */ 		/*                                                                     // (32) 0.005859
/*72  */ 		 * Check TCP sockets                                                   // (25) 0.01172
/*74  */ 		 */                                                                    // (31) 0.005859
/*76  */ 		for (so = slirp->tcb.so_next; so != &slirp->tcb;                       // (1) 0.05273
/*78  */ 		     so = so_next) {                                                   // (15) 0.02539
/*80  */ 			so_next = so->so_next;                                                // (12) 0.02539
/*84  */ 			/*                                                                    // (27) 0.007812
/*86  */ 			 * FD_ISSET is meaningless on these sockets                           // (10) 0.02539
/*88  */ 			 * (and they can crash the program)                                   // (17) 0.02344
/*90  */ 			 */                                                                   // (28) 0.007812
/*92  */ 			if (so->so_state & SS_NOFDREF || so->s == -1)                         // 0.0
/*94  */ 			   continue;                                                          // 0.0
/*98  */ 			/*                                                                    // 0.0
/*100 */ 			 * Check for URG data                                                 // 0.0
/*102 */ 			 * This will soread as well, so no need to                            // 0.0
/*104 */ 			 * test for readfds below if this succeeds                            // 0.0
/*106 */ 			 */                                                                   // 0.0
/*108 */ 			if (FD_ISSET(so->s, xfds))                                            // 0.0
/*110 */ 			   sorecvoob(so);                                                     // 0.0
/*112 */ 			/*                                                                    // 0.0
/*114 */ 			 * Check sockets for reading                                          // 0.0
/*116 */ 			 */                                                                   // 0.0
/*118 */ 			else if (FD_ISSET(so->s, readfds)) {                                  // 0.0
/*120 */ 				/*                                                                   // 0.0
/*122 */ 				 * Check for incoming connections                                    // 0.0
/*124 */ 				 */                                                                  // 0.0
/*126 */ 				if (so->so_state & SS_FACCEPTCONN) {                                 // 0.0
/*128 */ 					tcp_connect(so);                                                    // 0.0
/*130 */ 					continue;                                                           // 0.0
/*132 */ 				} /* else */                                                         // 0.0
/*134 */ 				ret = soread(so);                                                    // 0.0
/*138 */ 				/* Output it if we read something */                                 // 0.0
/*140 */ 				if (ret > 0)                                                         // 0.0
/*142 */ 				   tcp_output(sototcpcb(so));                                        // 0.0
/*144 */ 			}                                                                     // 0.0
/*148 */ 			/*                                                                    // 0.0
/*150 */ 			 * Check sockets for writing                                          // 0.0
/*152 */ 			 */                                                                   // 0.0
/*154 */ 			if (FD_ISSET(so->s, writefds)) {                                      // 0.0
/*156 */ 			  /*                                                                  // 0.0
/*158 */ 			   * Check for non-blocking, still-connecting sockets                 // 0.0
/*160 */ 			   */                                                                 // 0.0
/*162 */ 			  if (so->so_state & SS_ISFCONNECTING) {                              // 0.0
/*164 */ 			    /* Connected */                                                   // 0.0
/*166 */ 			    so->so_state &= ~SS_ISFCONNECTING;                                // 0.0
/*170 */ 			    ret = send(so->s, (const void *) &ret, 0, 0);                     // 0.0
/*172 */ 			    if (ret < 0) {                                                    // 0.0
/*174 */ 			      /* XXXXX Must fix, zero bytes is a NOP */                       // 0.0
/*176 */ 			      if (errno == EAGAIN || errno == EWOULDBLOCK ||                  // 0.0
/*178 */ 				  errno == EINPROGRESS || errno == ENOTCONN)                         // 0.0
/*180 */ 				continue;                                                            // 0.0
/*184 */ 			      /* else failed */                                               // 0.0
/*186 */ 			      so->so_state &= SS_PERSISTENT_MASK;                             // 0.0
/*188 */ 			      so->so_state |= SS_NOFDREF;                                     // 0.0
/*190 */ 			    }                                                                 // 0.0
/*192 */ 			    /* else so->so_state &= ~SS_ISFCONNECTING; */                     // 0.0
/*196 */ 			    /*                                                                // 0.0
/*198 */ 			     * Continue tcp_input                                             // 0.0
/*200 */ 			     */                                                               // 0.0
/*202 */ 			    tcp_input((struct mbuf *)NULL, sizeof(struct ip), so);            // 0.0
/*204 */ 			    /* continue; */                                                   // 0.0
/*206 */ 			  } else                                                              // 0.0
/*208 */ 			    ret = sowrite(so);                                                // 0.0
/*210 */ 			  /*                                                                  // 0.0
/*212 */ 			   * XXXXX If we wrote something (a lot), there                       // 0.0
/*214 */ 			   * could be a need for a window update.                             // 0.0
/*216 */ 			   * In the worst case, the remote will send                          // 0.0
/*218 */ 			   * a window probe to get things going again                         // 0.0
/*220 */ 			   */                                                                 // 0.0
/*222 */ 			}                                                                     // 0.0
/*226 */ 			/*                                                                    // 0.0
/*228 */ 			 * Probe a still-connecting, non-blocking socket                      // 0.0
/*230 */ 			 * to check if it's still alive                                       // 0.0
/*232 */ 	 	 	 */                                                                 // 0.0
/*234 */ #ifdef PROBE_CONN                                                        // 0.0
/*236 */ 			if (so->so_state & SS_ISFCONNECTING) {                                // 0.0
/*238 */                           ret = qemu_recv(so->s, &ret, 0,0);             // 0.0
/*242 */ 			  if (ret < 0) {                                                      // 0.0
/*244 */ 			    /* XXX */                                                         // 0.0
/*246 */ 			    if (errno == EAGAIN || errno == EWOULDBLOCK ||                    // 0.0
/*248 */ 				errno == EINPROGRESS || errno == ENOTCONN)                           // 0.0
/*250 */ 			      continue; /* Still connecting, continue */                      // 0.0
/*254 */ 			    /* else failed */                                                 // 0.0
/*256 */ 			    so->so_state &= SS_PERSISTENT_MASK;                               // 0.0
/*258 */ 			    so->so_state |= SS_NOFDREF;                                       // 0.0
/*262 */ 			    /* tcp_input will take care of it */                              // 0.0
/*264 */ 			  } else {                                                            // 0.0
/*266 */ 			    ret = send(so->s, &ret, 0,0);                                     // 0.0
/*268 */ 			    if (ret < 0) {                                                    // 0.0
/*270 */ 			      /* XXX */                                                       // 0.0
/*272 */ 			      if (errno == EAGAIN || errno == EWOULDBLOCK ||                  // 0.0
/*274 */ 				  errno == EINPROGRESS || errno == ENOTCONN)                         // 0.0
/*276 */ 				continue;                                                            // 0.0
/*278 */ 			      /* else failed */                                               // 0.0
/*280 */ 			      so->so_state &= SS_PERSISTENT_MASK;                             // 0.0
/*282 */ 			      so->so_state |= SS_NOFDREF;                                     // 0.0
/*284 */ 			    } else                                                            // 0.0
/*286 */ 			      so->so_state &= ~SS_ISFCONNECTING;                              // 0.0
/*290 */ 			  }                                                                   // 0.0
/*292 */ 			  tcp_input((struct mbuf *)NULL, sizeof(struct ip),so);               // 0.0
/*294 */ 			} /* SS_ISFCONNECTING */                                              // 0.0
/*296 */ #endif                                                                   // 0.0
/*298 */ 		}                                                                      // 0.0
/*302 */ 		/*                                                                     // 0.0
/*304 */ 		 * Now UDP sockets.                                                    // 0.0
/*306 */ 		 * Incoming packets are sent straight away, they're not buffered.      // 0.0
/*308 */ 		 * Incoming UDP data isn't buffered either.                            // 0.0
/*310 */ 		 */                                                                    // 0.0
/*312 */ 		for (so = slirp->udb.so_next; so != &slirp->udb;                       // 0.0
/*314 */ 		     so = so_next) {                                                   // 0.0
/*316 */ 			so_next = so->so_next;                                                // 0.0
/*320 */ 			if (so->s != -1 && FD_ISSET(so->s, readfds)) {                        // 0.0
/*322 */                             sorecvfrom(so);                              // 0.0
/*324 */                         }                                                // 0.0
/*326 */ 		}                                                                      // 0.0
/*330 */                 /*                                                       // 0.0
/*332 */                  * Check incoming ICMP relies.                           // 0.0
/*334 */                  */                                                      // 0.0
/*336 */                 for (so = slirp->icmp.so_next; so != &slirp->icmp;       // 0.0
/*338 */                      so = so_next) {                                     // 0.0
/*340 */                      so_next = so->so_next;                              // 0.0
/*344 */                     if (so->s != -1 && FD_ISSET(so->s, readfds)) {       // 0.0
/*346 */                         icmp_receive(so);                                // 0.0
/*348 */                     }                                                    // 0.0
/*350 */                 }                                                        // 0.0
/*352 */ 	}                                                                       // 0.0
/*356 */ 	/*                                                                      // 0.0
/*358 */ 	 * See if we can start outputting                                       // 0.0
/*360 */ 	 */                                                                     // 0.0
/*362 */ 	if (slirp->if_queued) {                                                 // 0.0
/*364 */ 	    if_start(slirp);                                                    // 0.0
/*366 */ 	}                                                                       // 0.0
/*368 */     }                                                                    // 0.0
/*372 */ 	/* clear global file descriptor sets.                                   // 0.0
/*374 */ 	 * these reside on the stack in vl.c                                    // 0.0
/*376 */ 	 * so they're unusable if we're not in                                  // 0.0
/*378 */ 	 * slirp_select_fill or slirp_select_poll.                              // 0.0
/*380 */ 	 */                                                                     // 0.0
/*382 */ 	 global_readfds = NULL;                                                 // 0.0
/*384 */ 	 global_writefds = NULL;                                                // 0.0
/*386 */ 	 global_xfds = NULL;                                                    // 0.0
/*388 */ }                                                                        // 0.0
