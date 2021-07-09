#include "DGBuffers.h"
//
// usage:
// eventLooper ("LHC17_18_AnalysisTree_2_2_10_2pi_A.root")
//
// ---------------------------------------------------------------------------
void eventLooper (char* fnin)
{
  // DGEvent contains the full information of an event.
  // see DGBuffers.[h,C] for details.
  DGEvent *dgevent = new DGEvent();

  // The events are contained in the tree "CEPTree" and branch "event".
  TFile *ftr = new TFile(fnin,"READ");
  TTree *tr = (TTree*)ftr->Get("CEPTree");
  if (tr == NULL) return;
  tr->SetBranchAddress("event", &dgevent);
  
  // Now loop over all events
  Long64_t nev = tr->GetEntries();
  printf("Number of events: %lli\n", nev);
  for (auto ii=0; ii<nev; ii++) {
    // fill dgevent with the next event
    tr->GetEntry(ii);
    
    printf("\n");
    printf("Event %i\n", ii);
    
    // get the vertex position
    auto vrtx = dgevent->vertex();
    printf("Vertex \n");
    vrtx.Print();
    
    // access the tracks
    // the resulting trks is a TObjArray*
    auto trks = dgevent->tracks();
    auto ntrks = trks->GetEntries();
    printf("Number of tracks: %lli\n", ntrks);
    
    // loop over the tracks
    for (auto jj=0; jj<ntrks; jj++) {
      printf("Particle %i \n", jj);
      
      // get the ii track of type DDTrack (see DGBuffers.[h,C])
      auto trk = (DGTrack*) (trks->At(jj));
      
      // track momentum is a TVector3 (see DGBuffers.[h,C])
      auto mom = trk->mom();
      printf("  Momentum\n");
      mom.Print();
      
      // nSigma values for different particles (el, mu, pi, K, pr) 
      printf("  nSigmas\n");
      for (auto jj=0; jj<AliPID::kSPECIES; jj++) {
        printf("    %i %f\n", jj, trk->nSigma(jj));
      }
    }
  }
  
  // clean up
  ftr->Close();

}

// ---------------------------------------------------------------------------
