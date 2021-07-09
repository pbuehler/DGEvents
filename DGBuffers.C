#include "DGBuffers.h"

// DGTrack
DGTrack::DGTrack ()
{
  mMomentum = TVector3(0., 0., 0.);
  mnSigmas = TArrayF(AliPID::kSPECIES);
}

DGTrack::DGTrack (TVector3 mom, const Float_t* nSigmas)
{
  mMomentum = TVector3(mom);
  mnSigmas = TArrayF(AliPID::kSPECIES, nSigmas);
}

void DGTrack::setnSigmas(Float_t* nSigmas)
{
  mnSigmas.Set(AliPID::kSPECIES, nSigmas);
}

Float_t DGTrack::nSigma(Int_t ind)
{
  if (ind < AliPID::kSPECIES) {
  return mnSigmas.At(ind);
  } else {
    return -999.9;
  }
}

// DGEvent
DGEvent::DGEvent ()
{
  mVertex = TVector3(0., 0., 0.);
  mTracks = new TObjArray();
}

void DGEvent::reset()
{
  mTracks->Clear();
  mVertex = TVector3(0., 0., 0.);
}

void DGEvent::addTrack(DGTrack* track)
{
  mTracks->Add((TObject*)track);
}
