// commit message qemu@cf57298af5 (target=0, prob=0.26664895, correct=True): qemu-io: better input validation for vector-based commands
/*0   */ aio_write_f(int argc, char **argv)                              // (4) 0.03125
/*2   */ {                                                               // (48) 0.001953
/*4   */ 	char *p;                                                       // (32) 0.009766
/*6   */ 	int count = 0;                                                 // (28) 0.01172
/*8   */ 	int nr_iov, i, c;                                              // (14) 0.02148
/*10  */ 	int pattern = 0xcd;                                            // (24) 0.01562
/*12  */ 	struct aio_ctx *ctx = calloc(1, sizeof(struct aio_ctx));       // (1) 0.04297
/*14  */ 	BlockDriverAIOCB *acb;                                         // (19) 0.01953
/*18  */ 	while ((c = getopt(argc, argv, "CqP:")) != EOF) {              // (0) 0.04883
/*20  */ 		switch (c) {                                                  // (25) 0.01367
/*22  */ 		case 'C':                                                     // (31) 0.01172
/*24  */ 			ctx->Cflag = 1;                                              // (21) 0.01953
/*26  */ 			break;                                                       // (39) 0.009766
/*28  */ 		case 'q':                                                     // (29) 0.01172
/*30  */ 			ctx->qflag = 1;                                              // (20) 0.01953
/*32  */ 			break;                                                       // (36) 0.009766
/*34  */ 		case 'P':                                                     // (30) 0.01172
/*36  */ 			pattern = atoi(optarg);                                      // (15) 0.02148
/*38  */ 			break;                                                       // (37) 0.009766
/*40  */ 		default:                                                      // (41) 0.007812
/*42  */ 			return command_usage(&aio_write_cmd);                        // (6) 0.0293
/*44  */ 		}                                                             // (43) 0.005859
/*46  */ 	}                                                              // (44) 0.003906
/*50  */ 	if (optind > argc - 2)                                         // (16) 0.02148
/*52  */ 		return command_usage(&aio_write_cmd);                         // (9) 0.02734
/*56  */ 	ctx->offset = cvtnum(argv[optind]);                            // (8) 0.0293
/*58  */ 	if (ctx->offset < 0) {                                         // (22) 0.01953
/*60  */ 		printf("non-numeric length argument -- %s\n", argv[optind]);  // (3) 0.04297
/*62  */ 		return 0;                                                     // (33) 0.009766
/*64  */ 	}                                                              // (47) 0.003906
/*66  */ 	optind++;                                                      // (40) 0.007812
/*70  */ 	if (ctx->offset & 0x1ff) {                                     // (13) 0.02539
/*72  */ 		printf("offset %lld is not sector aligned\n",                 // (7) 0.0293
/*74  */ 			(long long)ctx->offset);                                     // (18) 0.02148
/*76  */ 		return 0;                                                     // (35) 0.009766
/*78  */ 	}                                                              // (45) 0.003906
/*82  */ 	if (count & 0x1ff) {                                           // (17) 0.02148
/*84  */ 		printf("count %d is not sector aligned\n",                    // (11) 0.02734
/*86  */ 			count);                                                      // (38) 0.009766
/*88  */ 		return 0;                                                     // (34) 0.009766
/*90  */ 	}                                                              // (46) 0.003906
/*94  */ 	for (i = optind; i < argc; i++) {                              // (5) 0.03125
/*96  */ 	        size_t len;                                            // (12) 0.02539
/*100 */ 		len = cvtnum(argv[optind]);                                   // (10) 0.02734
/*102 */ 		if (len < 0) {                                                // (23) 0.01758
/*104 */ 			printf("non-numeric length argument -- %s\n", argv[i]);      // (2) 0.04297
/*106 */ 			return 0;                                                    // (27) 0.01172
/*108 */ 		}                                                             // (42) 0.005859
/*110 */ 		count += len;                                                 // (26) 0.01172
/*112 */ 	}                                                              // 0.0
/*116 */ 	nr_iov = argc - optind;                                        // 0.0
/*118 */ 	qemu_iovec_init(&ctx->qiov, nr_iov);                           // 0.0
/*120 */ 	ctx->buf = p = qemu_io_alloc(count, pattern);                  // 0.0
/*122 */ 	for (i = 0; i < nr_iov; i++) {                                 // 0.0
/*124 */ 	        size_t len;                                            // 0.0
/*128 */ 		len = cvtnum(argv[optind]);                                   // 0.0
/*130 */ 		if (len < 0) {                                                // 0.0
/*132 */ 			printf("non-numeric length argument -- %s\n",                // 0.0
/*134 */ 				argv[optind]);                                              // 0.0
/*136 */ 			return 0;                                                    // 0.0
/*138 */ 		}                                                             // 0.0
/*142 */ 		qemu_iovec_add(&ctx->qiov, p, len);                           // 0.0
/*144 */ 		p += len;                                                     // 0.0
/*146 */ 		optind++;                                                     // 0.0
/*148 */ 	}                                                              // 0.0
/*152 */ 	gettimeofday(&ctx->t1, NULL);                                  // 0.0
/*154 */ 	acb = bdrv_aio_writev(bs, ctx->offset >> 9, &ctx->qiov,        // 0.0
/*156 */ 			      ctx->qiov.size >> 9, aio_write_done, ctx);             // 0.0
/*158 */ 	if (!acb)                                                      // 0.0
/*160 */ 		return -EIO;                                                  // 0.0
/*164 */ 	return 0;                                                      // 0.0
/*166 */ }                                                               // 0.0
