// commit message FFmpeg@5e2202d6f3 (target=1, prob=0.25738594, correct=False): In mov demuxer, check that gmtime returns a valid value, fix crash, issue #2490
/*0  */ static void mov_metadata_creation_time(AVMetadata **metadata, time_t time)     // (3) 0.1429
/*2  */ {                                                                              // (7) 0.006803
/*4  */     char buffer[32];                                                           // (4) 0.05442
/*6  */     if (time) {                                                                // (5) 0.05442
/*8  */         time -= 2082844800;  /* seconds between 1904-01-01 and Epoch */        // (1) 0.1837
/*10 */         strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", gmtime(&time));  // (0) 0.2653
/*12 */         av_metadata_set2(metadata, "creation_time", buffer, 0);                // (2) 0.1701
/*14 */     }                                                                          // (6) 0.02721
/*16 */ }                                                                              // (8) 0.006803
