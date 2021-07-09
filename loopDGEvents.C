#include "DGBuffers.h"
//
// usage:
// auto fnins = TObjArray()
// fnins.Add(new TObjString("LHC17_18_AnalysisTree_2_2_2_2pi000_A.root"));
// fnins.Add(new TObjString("LHC17_18_AnalysisTree_2_2_2_2pi001_A.root"));
// .
// . add more files to fnins
// .
// eventLooper (fnins)
//
// ---------------------------------------------------------------------------
void eventLooper (TObjArray fnins)
{
  // DGEvent contains the full information of an event.
  // see DGBuffers.[h,C] for details.
  DGEvent *dgevent = new DGEvent();

  // The events are contained in the tree "CEPTree" and branch "event".
  TChain *ch = new TChain("CEPTree");
  for (auto fn : fnins) {
    ch->Add(((TObjString*)fn)->GetString().Data());
  }
  ch->SetBranchAddress("event", &dgevent);

  //TFile *ftr = new TFile(fnin,"READ");
  //TTree *tr = (TTree*)ftr->Get("CEPTree");
  //if (tr == NULL) return;
  //tr->SetBranchAddress("event", &dgevent);
  
  // Now loop over all events
  Long64_t nev = ch->GetEntries();
  printf("Number of events: %lli\n", nev);
  for (auto ii=0; ii<nev; ii++) {
    // fill dgevent with the next event
    ch->GetEntry(ii);
    
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
    printf("Number of tracks: %i\n", ntrks);
    
    // loop over the tracks
    for (auto jj=0; jj<ntrks; jj++) {
      printf("Particle %i \n", jj);
      
      // get the ii track of type DGTrack (see DGBuffers.[h,C])
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
  //ftr->Close();

}

// ---------------------------------------------------------------------------
