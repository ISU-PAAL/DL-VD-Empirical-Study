// commit message qemu@375092332e (target=0, prob=0.034740787, correct=True): crypto: Make errp the last parameter of functions
/*0   */ qcrypto_block_luks_create(QCryptoBlock *block,                                    // (7) 0.03516
/*2   */                           QCryptoBlockCreateOptions *options,                     // (2) 0.06641
/*4   */                           QCryptoBlockInitFunc initfunc,                          // (0) 0.06836
/*6   */                           QCryptoBlockWriteFunc writefunc,                        // (1) 0.06836
/*8   */                           void *opaque,                                           // (3) 0.05859
/*10  */                           Error **errp)                                           // (4) 0.05859
/*12  */ {                                                                                 // (27) 0.001953
/*14  */     QCryptoBlockLUKS *luks;                                                       // (11) 0.02734
/*16  */     QCryptoBlockCreateOptionsLUKS luks_opts;                                      // (6) 0.03711
/*18  */     Error *local_err = NULL;                                                      // (19) 0.02148
/*20  */     uint8_t *masterkey = NULL;                                                    // (16) 0.02539
/*22  */     uint8_t *slotkey = NULL;                                                      // (15) 0.02539
/*24  */     uint8_t *splitkey = NULL;                                                     // (17) 0.02539
/*26  */     size_t splitkeylen = 0;                                                       // (18) 0.02344
/*28  */     size_t i;                                                                     // (25) 0.01562
/*30  */     QCryptoCipher *cipher = NULL;                                                 // (14) 0.02734
/*32  */     QCryptoIVGen *ivgen = NULL;                                                   // (12) 0.02734
/*34  */     char *password;                                                               // (26) 0.01367
/*36  */     const char *cipher_alg;                                                       // (20) 0.02148
/*38  */     const char *cipher_mode;                                                      // (21) 0.02148
/*40  */     const char *ivgen_alg;                                                        // (22) 0.02148
/*42  */     const char *ivgen_hash_alg = NULL;                                            // (10) 0.0293
/*44  */     const char *hash_alg;                                                         // (24) 0.01953
/*46  */     char *cipher_mode_spec = NULL;                                                // (13) 0.02734
/*48  */     QCryptoCipherAlgorithm ivcipheralg = 0;                                       // (9) 0.0332
/*50  */     uint64_t iters;                                                               // (23) 0.01953
/*54  */     memcpy(&luks_opts, &options->u.luks, sizeof(luks_opts));                      // (5) 0.05664
/*56  */     if (!luks_opts.has_iter_time) {                                               // (8) 0.03516
/*58  */         luks_opts.iter_time = 2000;                                               // 0.0
/*60  */     }                                                                             // 0.0
/*62  */     if (!luks_opts.has_cipher_alg) {                                              // 0.0
/*64  */         luks_opts.cipher_alg = QCRYPTO_CIPHER_ALG_AES_256;                        // 0.0
/*66  */     }                                                                             // 0.0
/*68  */     if (!luks_opts.has_cipher_mode) {                                             // 0.0
/*70  */         luks_opts.cipher_mode = QCRYPTO_CIPHER_MODE_XTS;                          // 0.0
/*72  */     }                                                                             // 0.0
/*74  */     if (!luks_opts.has_ivgen_alg) {                                               // 0.0
/*76  */         luks_opts.ivgen_alg = QCRYPTO_IVGEN_ALG_PLAIN64;                          // 0.0
/*78  */     }                                                                             // 0.0
/*80  */     if (!luks_opts.has_hash_alg) {                                                // 0.0
/*82  */         luks_opts.hash_alg = QCRYPTO_HASH_ALG_SHA256;                             // 0.0
/*84  */     }                                                                             // 0.0
/*86  */     if (luks_opts.ivgen_alg == QCRYPTO_IVGEN_ALG_ESSIV) {                         // 0.0
/*88  */         if (!luks_opts.has_ivgen_hash_alg) {                                      // 0.0
/*90  */             luks_opts.ivgen_hash_alg = QCRYPTO_HASH_ALG_SHA256;                   // 0.0
/*92  */             luks_opts.has_ivgen_hash_alg = true;                                  // 0.0
/*94  */         }                                                                         // 0.0
/*96  */     }                                                                             // 0.0
/*98  */     /* Note we're allowing ivgen_hash_alg to be set even for                      // 0.0
/*100 */      * non-essiv iv generators that don't need a hash. It will                    // 0.0
/*102 */      * be silently ignored, for compatibility with dm-crypt */                    // 0.0
/*106 */     if (!options->u.luks.key_secret) {                                            // 0.0
/*108 */         error_setg(errp, "Parameter 'key-secret' is required for cipher");        // 0.0
/*110 */         return -1;                                                                // 0.0
/*112 */     }                                                                             // 0.0
/*114 */     password = qcrypto_secret_lookup_as_utf8(luks_opts.key_secret, errp);         // 0.0
/*116 */     if (!password) {                                                              // 0.0
/*118 */         return -1;                                                                // 0.0
/*120 */     }                                                                             // 0.0
/*124 */     luks = g_new0(QCryptoBlockLUKS, 1);                                           // 0.0
/*126 */     block->opaque = luks;                                                         // 0.0
/*130 */     memcpy(luks->header.magic, qcrypto_block_luks_magic,                          // 0.0
/*132 */            QCRYPTO_BLOCK_LUKS_MAGIC_LEN);                                         // 0.0
/*136 */     /* We populate the header in native endianness initially and                  // 0.0
/*138 */      * then convert everything to big endian just before writing                  // 0.0
/*140 */      * it out to disk                                                             // 0.0
/*142 */      */                                                                           // 0.0
/*144 */     luks->header.version = QCRYPTO_BLOCK_LUKS_VERSION;                            // 0.0
/*146 */     qcrypto_block_luks_uuid_gen(luks->header.uuid);                               // 0.0
/*150 */     cipher_alg = qcrypto_block_luks_cipher_alg_lookup(luks_opts.cipher_alg,       // 0.0
/*152 */                                                       errp);                      // 0.0
/*154 */     if (!cipher_alg) {                                                            // 0.0
/*156 */         goto error;                                                               // 0.0
/*158 */     }                                                                             // 0.0
/*162 */     cipher_mode = QCryptoCipherMode_lookup[luks_opts.cipher_mode];                // 0.0
/*164 */     ivgen_alg = QCryptoIVGenAlgorithm_lookup[luks_opts.ivgen_alg];                // 0.0
/*166 */     if (luks_opts.has_ivgen_hash_alg) {                                           // 0.0
/*168 */         ivgen_hash_alg = QCryptoHashAlgorithm_lookup[luks_opts.ivgen_hash_alg];   // 0.0
/*170 */         cipher_mode_spec = g_strdup_printf("%s-%s:%s", cipher_mode, ivgen_alg,    // 0.0
/*172 */                                            ivgen_hash_alg);                       // 0.0
/*174 */     } else {                                                                      // 0.0
/*176 */         cipher_mode_spec = g_strdup_printf("%s-%s", cipher_mode, ivgen_alg);      // 0.0
/*178 */     }                                                                             // 0.0
/*180 */     hash_alg = QCryptoHashAlgorithm_lookup[luks_opts.hash_alg];                   // 0.0
/*186 */     if (strlen(cipher_alg) >= QCRYPTO_BLOCK_LUKS_CIPHER_NAME_LEN) {               // 0.0
/*188 */         error_setg(errp, "Cipher name '%s' is too long for LUKS header",          // 0.0
/*190 */                    cipher_alg);                                                   // 0.0
/*192 */         goto error;                                                               // 0.0
/*194 */     }                                                                             // 0.0
/*196 */     if (strlen(cipher_mode_spec) >= QCRYPTO_BLOCK_LUKS_CIPHER_MODE_LEN) {         // 0.0
/*198 */         error_setg(errp, "Cipher mode '%s' is too long for LUKS header",          // 0.0
/*200 */                    cipher_mode_spec);                                             // 0.0
/*202 */         goto error;                                                               // 0.0
/*204 */     }                                                                             // 0.0
/*206 */     if (strlen(hash_alg) >= QCRYPTO_BLOCK_LUKS_HASH_SPEC_LEN) {                   // 0.0
/*208 */         error_setg(errp, "Hash name '%s' is too long for LUKS header",            // 0.0
/*210 */                    hash_alg);                                                     // 0.0
/*212 */         goto error;                                                               // 0.0
/*214 */     }                                                                             // 0.0
/*218 */     if (luks_opts.ivgen_alg == QCRYPTO_IVGEN_ALG_ESSIV) {                         // 0.0
/*220 */         ivcipheralg = qcrypto_block_luks_essiv_cipher(luks_opts.cipher_alg,       // 0.0
/*222 */                                                       luks_opts.ivgen_hash_alg,   // 0.0
/*224 */                                                       &local_err);                // 0.0
/*226 */         if (local_err) {                                                          // 0.0
/*228 */             error_propagate(errp, local_err);                                     // 0.0
/*230 */             goto error;                                                           // 0.0
/*232 */         }                                                                         // 0.0
/*234 */     } else {                                                                      // 0.0
/*236 */         ivcipheralg = luks_opts.cipher_alg;                                       // 0.0
/*238 */     }                                                                             // 0.0
/*242 */     strcpy(luks->header.cipher_name, cipher_alg);                                 // 0.0
/*244 */     strcpy(luks->header.cipher_mode, cipher_mode_spec);                           // 0.0
/*246 */     strcpy(luks->header.hash_spec, hash_alg);                                     // 0.0
/*250 */     luks->header.key_bytes = qcrypto_cipher_get_key_len(luks_opts.cipher_alg);    // 0.0
/*252 */     if (luks_opts.cipher_mode == QCRYPTO_CIPHER_MODE_XTS) {                       // 0.0
/*254 */         luks->header.key_bytes *= 2;                                              // 0.0
/*256 */     }                                                                             // 0.0
/*260 */     /* Generate the salt used for hashing the master key                          // 0.0
/*262 */      * with PBKDF later                                                           // 0.0
/*264 */      */                                                                           // 0.0
/*266 */     if (qcrypto_random_bytes(luks->header.master_key_salt,                        // 0.0
/*268 */                              QCRYPTO_BLOCK_LUKS_SALT_LEN,                         // 0.0
/*270 */                              errp) < 0) {                                         // 0.0
/*272 */         goto error;                                                               // 0.0
/*274 */     }                                                                             // 0.0
/*278 */     /* Generate random master key */                                              // 0.0
/*280 */     masterkey = g_new0(uint8_t, luks->header.key_bytes);                          // 0.0
/*282 */     if (qcrypto_random_bytes(masterkey,                                           // 0.0
/*284 */                              luks->header.key_bytes, errp) < 0) {                 // 0.0
/*286 */         goto error;                                                               // 0.0
/*288 */     }                                                                             // 0.0
/*294 */     /* Setup the block device payload encryption objects */                       // 0.0
/*296 */     block->cipher = qcrypto_cipher_new(luks_opts.cipher_alg,                      // 0.0
/*298 */                                        luks_opts.cipher_mode,                     // 0.0
/*300 */                                        masterkey, luks->header.key_bytes,         // 0.0
/*302 */                                        errp);                                     // 0.0
/*304 */     if (!block->cipher) {                                                         // 0.0
/*306 */         goto error;                                                               // 0.0
/*308 */     }                                                                             // 0.0
/*312 */     block->kdfhash = luks_opts.hash_alg;                                          // 0.0
/*314 */     block->niv = qcrypto_cipher_get_iv_len(luks_opts.cipher_alg,                  // 0.0
/*316 */                                            luks_opts.cipher_mode);                // 0.0
/*318 */     block->ivgen = qcrypto_ivgen_new(luks_opts.ivgen_alg,                         // 0.0
/*320 */                                      ivcipheralg,                                 // 0.0
/*322 */                                      luks_opts.ivgen_hash_alg,                    // 0.0
/*324 */                                      masterkey, luks->header.key_bytes,           // 0.0
/*326 */                                      errp);                                       // 0.0
/*330 */     if (!block->ivgen) {                                                          // 0.0
/*332 */         goto error;                                                               // 0.0
/*334 */     }                                                                             // 0.0
/*340 */     /* Determine how many iterations we need to hash the master                   // 0.0
/*342 */      * key, in order to have 1 second of compute time used                        // 0.0
/*344 */      */                                                                           // 0.0
/*346 */     iters = qcrypto_pbkdf2_count_iters(luks_opts.hash_alg,                        // 0.0
/*348 */                                        masterkey, luks->header.key_bytes,         // 0.0
/*350 */                                        luks->header.master_key_salt,              // 0.0
/*352 */                                        QCRYPTO_BLOCK_LUKS_SALT_LEN,               // 0.0
/*354 */                                        QCRYPTO_BLOCK_LUKS_DIGEST_LEN,             // 0.0
/*356 */                                        &local_err);                               // 0.0
/*358 */     if (local_err) {                                                              // 0.0
/*360 */         error_propagate(errp, local_err);                                         // 0.0
/*362 */         goto error;                                                               // 0.0
/*364 */     }                                                                             // 0.0
/*368 */     if (iters > (ULLONG_MAX / luks_opts.iter_time)) {                             // 0.0
/*370 */         error_setg_errno(errp, ERANGE,                                            // 0.0
/*372 */                          "PBKDF iterations %llu too large to scale",              // 0.0
/*374 */                          (unsigned long long)iters);                              // 0.0
/*376 */         goto error;                                                               // 0.0
/*378 */     }                                                                             // 0.0
/*382 */     /* iter_time was in millis, but count_iters reported for secs */              // 0.0
/*384 */     iters = iters * luks_opts.iter_time / 1000;                                   // 0.0
/*388 */     /* Why /= 8 ?  That matches cryptsetup, but there's no                        // 0.0
/*390 */      * explanation why they chose /= 8... Probably so that                        // 0.0
/*392 */      * if all 8 keyslots are active we only spend 1 second                        // 0.0
/*394 */      * in total time to check all keys */                                         // 0.0
/*396 */     iters /= 8;                                                                   // 0.0
/*398 */     if (iters > UINT32_MAX) {                                                     // 0.0
/*400 */         error_setg_errno(errp, ERANGE,                                            // 0.0
/*402 */                          "PBKDF iterations %llu larger than %u",                  // 0.0
/*404 */                          (unsigned long long)iters, UINT32_MAX);                  // 0.0
/*406 */         goto error;                                                               // 0.0
/*408 */     }                                                                             // 0.0
/*410 */     iters = MAX(iters, QCRYPTO_BLOCK_LUKS_MIN_MASTER_KEY_ITERS);                  // 0.0
/*412 */     luks->header.master_key_iterations = iters;                                   // 0.0
/*416 */     /* Hash the master key, saving the result in the LUKS                         // 0.0
/*418 */      * header. This hash is used when opening the encrypted                       // 0.0
/*420 */      * device to verify that the user password unlocked a                         // 0.0
/*422 */      * valid master key                                                           // 0.0
/*424 */      */                                                                           // 0.0
/*426 */     if (qcrypto_pbkdf2(luks_opts.hash_alg,                                        // 0.0
/*428 */                        masterkey, luks->header.key_bytes,                         // 0.0
/*430 */                        luks->header.master_key_salt,                              // 0.0
/*432 */                        QCRYPTO_BLOCK_LUKS_SALT_LEN,                               // 0.0
/*434 */                        luks->header.master_key_iterations,                        // 0.0
/*436 */                        luks->header.master_key_digest,                            // 0.0
/*438 */                        QCRYPTO_BLOCK_LUKS_DIGEST_LEN,                             // 0.0
/*440 */                        errp) < 0) {                                               // 0.0
/*442 */         goto error;                                                               // 0.0
/*444 */     }                                                                             // 0.0
/*450 */     /* Although LUKS has multiple key slots, we're just going                     // 0.0
/*452 */      * to use the first key slot */                                               // 0.0
/*454 */     splitkeylen = luks->header.key_bytes * QCRYPTO_BLOCK_LUKS_STRIPES;            // 0.0
/*456 */     for (i = 0; i < QCRYPTO_BLOCK_LUKS_NUM_KEY_SLOTS; i++) {                      // 0.0
/*458 */         luks->header.key_slots[i].active = i == 0 ?                               // 0.0
/*460 */             QCRYPTO_BLOCK_LUKS_KEY_SLOT_ENABLED :                                 // 0.0
/*462 */             QCRYPTO_BLOCK_LUKS_KEY_SLOT_DISABLED;                                 // 0.0
/*464 */         luks->header.key_slots[i].stripes = QCRYPTO_BLOCK_LUKS_STRIPES;           // 0.0
/*468 */         /* This calculation doesn't match that shown in the spec,                 // 0.0
/*470 */          * but instead follows the cryptsetup implementation.                     // 0.0
/*472 */          */                                                                       // 0.0
/*474 */         luks->header.key_slots[i].key_offset =                                    // 0.0
/*476 */             (QCRYPTO_BLOCK_LUKS_KEY_SLOT_OFFSET /                                 // 0.0
/*478 */              QCRYPTO_BLOCK_LUKS_SECTOR_SIZE) +                                    // 0.0
/*480 */             (ROUND_UP(DIV_ROUND_UP(splitkeylen, QCRYPTO_BLOCK_LUKS_SECTOR_SIZE),  // 0.0
/*482 */                       (QCRYPTO_BLOCK_LUKS_KEY_SLOT_OFFSET /                       // 0.0
/*484 */                        QCRYPTO_BLOCK_LUKS_SECTOR_SIZE)) * i);                     // 0.0
/*486 */     }                                                                             // 0.0
/*490 */     if (qcrypto_random_bytes(luks->header.key_slots[0].salt,                      // 0.0
/*492 */                              QCRYPTO_BLOCK_LUKS_SALT_LEN,                         // 0.0
/*494 */                              errp) < 0) {                                         // 0.0
/*496 */         goto error;                                                               // 0.0
/*498 */     }                                                                             // 0.0
/*502 */     /* Again we determine how many iterations are required to                     // 0.0
/*504 */      * hash the user password while consuming 1 second of compute                 // 0.0
/*506 */      * time */                                                                    // 0.0
/*508 */     iters = qcrypto_pbkdf2_count_iters(luks_opts.hash_alg,                        // 0.0
/*510 */                                        (uint8_t *)password, strlen(password),     // 0.0
/*512 */                                        luks->header.key_slots[0].salt,            // 0.0
/*514 */                                        QCRYPTO_BLOCK_LUKS_SALT_LEN,               // 0.0
/*516 */                                        luks->header.key_bytes,                    // 0.0
/*518 */                                        &local_err);                               // 0.0
/*520 */     if (local_err) {                                                              // 0.0
/*522 */         error_propagate(errp, local_err);                                         // 0.0
/*524 */         goto error;                                                               // 0.0
/*526 */     }                                                                             // 0.0
/*530 */     if (iters > (ULLONG_MAX / luks_opts.iter_time)) {                             // 0.0
/*532 */         error_setg_errno(errp, ERANGE,                                            // 0.0
/*534 */                          "PBKDF iterations %llu too large to scale",              // 0.0
/*536 */                          (unsigned long long)iters);                              // 0.0
/*538 */         goto error;                                                               // 0.0
/*540 */     }                                                                             // 0.0
/*544 */     /* iter_time was in millis, but count_iters reported for secs */              // 0.0
/*546 */     iters = iters * luks_opts.iter_time / 1000;                                   // 0.0
/*550 */     if (iters > UINT32_MAX) {                                                     // 0.0
/*552 */         error_setg_errno(errp, ERANGE,                                            // 0.0
/*554 */                          "PBKDF iterations %llu larger than %u",                  // 0.0
/*556 */                          (unsigned long long)iters, UINT32_MAX);                  // 0.0
/*558 */         goto error;                                                               // 0.0
/*560 */     }                                                                             // 0.0
/*564 */     luks->header.key_slots[0].iterations =                                        // 0.0
/*566 */         MAX(iters, QCRYPTO_BLOCK_LUKS_MIN_SLOT_KEY_ITERS);                        // 0.0
/*572 */     /* Generate a key that we'll use to encrypt the master                        // 0.0
/*574 */      * key, from the user's password                                              // 0.0
/*576 */      */                                                                           // 0.0
/*578 */     slotkey = g_new0(uint8_t, luks->header.key_bytes);                            // 0.0
/*580 */     if (qcrypto_pbkdf2(luks_opts.hash_alg,                                        // 0.0
/*582 */                        (uint8_t *)password, strlen(password),                     // 0.0
/*584 */                        luks->header.key_slots[0].salt,                            // 0.0
/*586 */                        QCRYPTO_BLOCK_LUKS_SALT_LEN,                               // 0.0
/*588 */                        luks->header.key_slots[0].iterations,                      // 0.0
/*590 */                        slotkey, luks->header.key_bytes,                           // 0.0
/*592 */                        errp) < 0) {                                               // 0.0
/*594 */         goto error;                                                               // 0.0
/*596 */     }                                                                             // 0.0
/*602 */     /* Setup the encryption objects needed to encrypt the                         // 0.0
/*604 */      * master key material                                                        // 0.0
/*606 */      */                                                                           // 0.0
/*608 */     cipher = qcrypto_cipher_new(luks_opts.cipher_alg,                             // 0.0
/*610 */                                 luks_opts.cipher_mode,                            // 0.0
/*612 */                                 slotkey, luks->header.key_bytes,                  // 0.0
/*614 */                                 errp);                                            // 0.0
/*616 */     if (!cipher) {                                                                // 0.0
/*618 */         goto error;                                                               // 0.0
/*620 */     }                                                                             // 0.0
/*624 */     ivgen = qcrypto_ivgen_new(luks_opts.ivgen_alg,                                // 0.0
/*626 */                               ivcipheralg,                                        // 0.0
/*628 */                               luks_opts.ivgen_hash_alg,                           // 0.0
/*630 */                               slotkey, luks->header.key_bytes,                    // 0.0
/*632 */                               errp);                                              // 0.0
/*634 */     if (!ivgen) {                                                                 // 0.0
/*636 */         goto error;                                                               // 0.0
/*638 */     }                                                                             // 0.0
/*642 */     /* Before storing the master key, we need to vastly                           // 0.0
/*644 */      * increase its size, as protection against forensic                          // 0.0
/*646 */      * disk data recovery */                                                      // 0.0
/*648 */     splitkey = g_new0(uint8_t, splitkeylen);                                      // 0.0
/*652 */     if (qcrypto_afsplit_encode(luks_opts.hash_alg,                                // 0.0
/*654 */                                luks->header.key_bytes,                            // 0.0
/*656 */                                luks->header.key_slots[0].stripes,                 // 0.0
/*658 */                                masterkey,                                         // 0.0
/*660 */                                splitkey,                                          // 0.0
/*662 */                                errp) < 0) {                                       // 0.0
/*664 */         goto error;                                                               // 0.0
/*666 */     }                                                                             // 0.0
/*670 */     /* Now we encrypt the split master key with the key generated                 // 0.0
/*672 */      * from the user's password, before storing it */                             // 0.0
/*674 */     if (qcrypto_block_encrypt_helper(cipher, block->niv, ivgen,                   // 0.0
/*676 */                                      QCRYPTO_BLOCK_LUKS_SECTOR_SIZE,              // 0.0
/*678 */                                      0,                                           // 0.0
/*680 */                                      splitkey,                                    // 0.0
/*682 */                                      splitkeylen,                                 // 0.0
/*684 */                                      errp) < 0) {                                 // 0.0
/*686 */         goto error;                                                               // 0.0
/*688 */     }                                                                             // 0.0
/*694 */     /* The total size of the LUKS headers is the partition header + key           // 0.0
/*696 */      * slot headers, rounded up to the nearest sector, combined with              // 0.0
/*698 */      * the size of each master key material region, also rounded up               // 0.0
/*700 */      * to the nearest sector */                                                   // 0.0
/*702 */     luks->header.payload_offset =                                                 // 0.0
/*704 */         (QCRYPTO_BLOCK_LUKS_KEY_SLOT_OFFSET /                                     // 0.0
/*706 */          QCRYPTO_BLOCK_LUKS_SECTOR_SIZE) +                                        // 0.0
/*708 */         (ROUND_UP(DIV_ROUND_UP(splitkeylen, QCRYPTO_BLOCK_LUKS_SECTOR_SIZE),      // 0.0
/*710 */                   (QCRYPTO_BLOCK_LUKS_KEY_SLOT_OFFSET /                           // 0.0
/*712 */                    QCRYPTO_BLOCK_LUKS_SECTOR_SIZE)) *                             // 0.0
/*714 */          QCRYPTO_BLOCK_LUKS_NUM_KEY_SLOTS);                                       // 0.0
/*718 */     block->payload_offset = luks->header.payload_offset *                         // 0.0
/*720 */         QCRYPTO_BLOCK_LUKS_SECTOR_SIZE;                                           // 0.0
/*724 */     /* Reserve header space to match payload offset */                            // 0.0
/*726 */     initfunc(block, block->payload_offset, &local_err, opaque);                   // 0.0
/*728 */     if (local_err) {                                                              // 0.0
/*730 */         error_propagate(errp, local_err);                                         // 0.0
/*732 */         goto error;                                                               // 0.0
/*734 */     }                                                                             // 0.0
/*738 */     /* Everything on disk uses Big Endian, so flip header fields                  // 0.0
/*740 */      * before writing them */                                                     // 0.0
/*742 */     cpu_to_be16s(&luks->header.version);                                          // 0.0
/*744 */     cpu_to_be32s(&luks->header.payload_offset);                                   // 0.0
/*746 */     cpu_to_be32s(&luks->header.key_bytes);                                        // 0.0
/*748 */     cpu_to_be32s(&luks->header.master_key_iterations);                            // 0.0
/*752 */     for (i = 0; i < QCRYPTO_BLOCK_LUKS_NUM_KEY_SLOTS; i++) {                      // 0.0
/*754 */         cpu_to_be32s(&luks->header.key_slots[i].active);                          // 0.0
/*756 */         cpu_to_be32s(&luks->header.key_slots[i].iterations);                      // 0.0
/*758 */         cpu_to_be32s(&luks->header.key_slots[i].key_offset);                      // 0.0
/*760 */         cpu_to_be32s(&luks->header.key_slots[i].stripes);                         // 0.0
/*762 */     }                                                                             // 0.0
/*768 */     /* Write out the partition header and key slot headers */                     // 0.0
/*770 */     writefunc(block, 0,                                                           // 0.0
/*772 */               (const uint8_t *)&luks->header,                                     // 0.0
/*774 */               sizeof(luks->header),                                               // 0.0
/*776 */               &local_err,                                                         // 0.0
/*778 */               opaque);                                                            // 0.0
/*782 */     /* Delay checking local_err until we've byte-swapped */                       // 0.0
/*786 */     /* Byte swap the header back to native, in case we need                       // 0.0
/*788 */      * to read it again later */                                                  // 0.0
/*790 */     be16_to_cpus(&luks->header.version);                                          // 0.0
/*792 */     be32_to_cpus(&luks->header.payload_offset);                                   // 0.0
/*794 */     be32_to_cpus(&luks->header.key_bytes);                                        // 0.0
/*796 */     be32_to_cpus(&luks->header.master_key_iterations);                            // 0.0
/*800 */     for (i = 0; i < QCRYPTO_BLOCK_LUKS_NUM_KEY_SLOTS; i++) {                      // 0.0
/*802 */         be32_to_cpus(&luks->header.key_slots[i].active);                          // 0.0
/*804 */         be32_to_cpus(&luks->header.key_slots[i].iterations);                      // 0.0
/*806 */         be32_to_cpus(&luks->header.key_slots[i].key_offset);                      // 0.0
/*808 */         be32_to_cpus(&luks->header.key_slots[i].stripes);                         // 0.0
/*810 */     }                                                                             // 0.0
/*814 */     if (local_err) {                                                              // 0.0
/*816 */         error_propagate(errp, local_err);                                         // 0.0
/*818 */         goto error;                                                               // 0.0
/*820 */     }                                                                             // 0.0
/*824 */     /* Write out the master key material, starting at the                         // 0.0
/*826 */      * sector immediately following the partition header. */                      // 0.0
/*828 */     if (writefunc(block,                                                          // 0.0
/*830 */                   luks->header.key_slots[0].key_offset *                          // 0.0
/*832 */                   QCRYPTO_BLOCK_LUKS_SECTOR_SIZE,                                 // 0.0
/*834 */                   splitkey, splitkeylen,                                          // 0.0
/*836 */                   errp,                                                           // 0.0
/*838 */                   opaque) != splitkeylen) {                                       // 0.0
/*840 */         goto error;                                                               // 0.0
/*842 */     }                                                                             // 0.0
/*846 */     luks->cipher_alg = luks_opts.cipher_alg;                                      // 0.0
/*848 */     luks->cipher_mode = luks_opts.cipher_mode;                                    // 0.0
/*850 */     luks->ivgen_alg = luks_opts.ivgen_alg;                                        // 0.0
/*852 */     luks->ivgen_hash_alg = luks_opts.ivgen_hash_alg;                              // 0.0
/*854 */     luks->hash_alg = luks_opts.hash_alg;                                          // 0.0
/*858 */     memset(masterkey, 0, luks->header.key_bytes);                                 // 0.0
/*860 */     g_free(masterkey);                                                            // 0.0
/*862 */     memset(slotkey, 0, luks->header.key_bytes);                                   // 0.0
/*864 */     g_free(slotkey);                                                              // 0.0
/*866 */     g_free(splitkey);                                                             // 0.0
/*868 */     g_free(password);                                                             // 0.0
/*870 */     g_free(cipher_mode_spec);                                                     // 0.0
/*874 */     qcrypto_ivgen_free(ivgen);                                                    // 0.0
/*876 */     qcrypto_cipher_free(cipher);                                                  // 0.0
/*880 */     return 0;                                                                     // 0.0
/*884 */  error:                                                                           // 0.0
/*886 */     if (masterkey) {                                                              // 0.0
/*888 */         memset(masterkey, 0, luks->header.key_bytes);                             // 0.0
/*890 */     }                                                                             // 0.0
/*892 */     g_free(masterkey);                                                            // 0.0
/*894 */     if (slotkey) {                                                                // 0.0
/*896 */         memset(slotkey, 0, luks->header.key_bytes);                               // 0.0
/*898 */     }                                                                             // 0.0
/*900 */     g_free(slotkey);                                                              // 0.0
/*902 */     g_free(splitkey);                                                             // 0.0
/*904 */     g_free(password);                                                             // 0.0
/*906 */     g_free(cipher_mode_spec);                                                     // 0.0
/*910 */     qcrypto_ivgen_free(ivgen);                                                    // 0.0
/*912 */     qcrypto_cipher_free(cipher);                                                  // 0.0
/*916 */     g_free(luks);                                                                 // 0.0
/*918 */     return -1;                                                                    // 0.0
/*920 */ }                                                                                 // 0.0
