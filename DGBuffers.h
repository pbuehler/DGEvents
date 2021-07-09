#ifndef DGBUFFERS
#define DGBUFFERS

#include "TVector3.h"
#include "TArrayF.h"
#include "TObjArray.h"
#include <AliPID.h>

// -----------------------------------------------------------------------------
// structures to hold analysis CEP events
class DGTrack : public TObject
{
  
  public:
    DGTrack ();
    DGTrack (TVector3 mom, const Float_t* nSigmas);
    ~DGTrack () = default;
    
    void setnSigmas(Float_t* nSigmas);
    
    TVector3 mom() { return mMomentum; };
    Float_t nSigma(Int_t ind);

  private:
    TVector3 mMomentum;
    TArrayF mnSigmas;

  ClassDef(DGTrack, 1);

};


class DGEvent : public TObject
{

  public:
    DGEvent ();
    ~DGEvent () { delete mTracks; };
    
    void reset();
    void setVertex(TVector3 vertex) { mVertex = vertex; };
    void addTrack(DGTrack* track);
    
    TObjArray* tracks() { return mTracks; };
    TVector3 vertex() { return mVertex; };
    
  private:
    TVector3 mVertex;
    TObjArray* mTracks;

  ClassDef(DGEvent, 1);
  
};

// -----------------------------------------------------------------------------

#endif
