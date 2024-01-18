// commit message qemu@447b0d0b9e (target=1, prob=0.78215855, correct=True): memory: avoid "resurrection" of dead FlatViews
/*0 */ static void flatview_ref(FlatView *view)  // (0) 0.3824
/*2 */ {                                         // (2) 0.02941
/*4 */     atomic_inc(&view->ref);               // (1) 0.3235
/*6 */ }                                         // (3) 0.02941
