// commit message FFmpeg@c6bdc90890 (target=1, prob=0.3676077, correct=False): Remove illegal call to exit(). patch by Marc Hoffman, mmh pleasantst com
/*0  */ void help(void)                                                   // (7) 0.02513
/*2  */ {                                                                 // (9) 0.005025
/*4  */     printf("dct-test [-i] [<test-number>]\n"                      // (5) 0.1055
/*6  */            "test-number 0 -> test with random matrixes\n"         // (4) 0.1206
/*8  */            "            1 -> test with random sparse matrixes\n"  // (1) 0.1658
/*10 */            "            2 -> do 3. test from mpeg4 std\n"         // (0) 0.1809
/*12 */            "-i          test IDCT implementations\n"              // (3) 0.1407
/*14 */            "-4          test IDCT248 implementations\n");         // (2) 0.1457
/*16 */     exit(1);                                                      // (6) 0.03518
/*18 */ }                                                                 // (8) 0.005025
