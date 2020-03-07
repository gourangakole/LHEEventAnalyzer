// -*- C++ -*-
//
// Package:    GeneratorInterface
// Class:      LHEEventAnalyzer
// 
//
// Description: Module to analyze Pythia-EvtGen HepMCproducts
//
//
// Original Author:  Roberto Covarelli
//         Created:  April 26, 2007
// added featchers by Gouranga Kole, UCY
// ref: https://gitlab.cern.ch/cms-sw/cmssw/blob/f7ad0b6982d8a2ee349a3e67fef302363ca5d3d8/GeneratorInterface/GenFilters/src/LHEVpTFilter.cc

#include <iostream>
#include <fstream>
 
// #include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

// essentials !!!
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
 
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TObjArray.h"
 
#include "FWCore/Framework/interface/MakerMacros.h"

#include "Demo/LHEEventAnalyzer/interface/LHEEventAnalyzer.h"

using namespace edm;
using namespace std;
// using namespace HepMC;
 
LHEEventAnalyzer::LHEEventAnalyzer( const ParameterSet& pset )
   : fOutputFileName( pset.getUntrackedParameter<string>("HistOutFile",std::string("HPTRapidity.root")) ),
     theSrc( pset.getUntrackedParameter<string>("theSrc",std::string("source")) ), 
     whichWeight( pset.getUntrackedParameter<int>("whichWeight",-1)),
     fOutputFile(0)
{

   nevent = 0;
   lhep_token = consumes< LHEEventProduct >(InputTag(theSrc));
   
   fOutputFile   = new TFile( fOutputFileName.c_str(), "RECREATE" ) ;
   // fHist2muMass  = new TH1D(  "Hist2muMass", "2-mu inv. mass", 100,  60., 120. ) ;  
   uQuarkMult = new TH1D( "uQuarkMult", "uQuarkMult multiplicity" , 5, -0.5 , 4.5 ) ;
   mult = new TH1D( "mult", "Parton multiplicity" , 5, -0.5 , 4.5 ) ; 
   h_higgsPt = new TH1F("h_higgsPt", "Higgs Pt", 100,0.0,200.0);
   h_higgsRap = new TH1F("h_higgsRap", "higgsRap", 40, -10,10);
   h_WbosonPt = new TH1F("h_WbosonPt", "W Pt", 100,0.0,200.0);
   h_WbosonRap = new TH1F("h_WbosonRap", "WbosonRap", 40, -10,10);
   mult->Sumw2();
   uQuarkMult->Sumw2();
}

LHEEventAnalyzer::~LHEEventAnalyzer()
{
  TObjArray Hlist(0);
  Hlist.Add(mult);
  Hlist.Add(uQuarkMult);
  Hlist.Add(h_higgsPt);
  Hlist.Add(h_higgsRap);
  Hlist.Add(h_WbosonPt);
  Hlist.Add(h_WbosonRap);

  fOutputFile->cd() ;
  Hlist.Write() ;
  fOutputFile->Close() ;
  cout << "N_events = " << nevent << "\n";  
}

void LHEEventAnalyzer::beginJob()
{
}
 
void LHEEventAnalyzer::analyze( const Event& e, const EventSetup& )
{
   nevent++;
   int npart = 0;
   int nuQuarkMult = 0;
   double higPt = 0.0;
   double higRap = 0.0;
   double WbosonPt = 0.0;
   double WbosonRap = 0.0;

   Handle< LHEEventProduct > EvtHandle ;
   e.getByToken( lhep_token , EvtHandle ) ;

   float weight = EvtHandle->hepeup().XWGTUP;
   lheParticles = EvtHandle->hepeup().PUP;
   
   if (whichWeight >= 0) weight *= EvtHandle->weights()[whichWeight].wgt/EvtHandle->originalXWGTUP(); 

   for (int i = 0; i < EvtHandle->hepeup().NUP; ++i) {
     if (EvtHandle->hepeup().ISTUP[i] != 1) { // keep only outgoing particles
       //cout << reader->hepeup.ISTUP[i] << ", " << reader->hepeup.IDUP[i] << endl;
       continue;
     }
     unsigned absPdgId = std::abs(EvtHandle->hepeup().IDUP[i]);
     if(absPdgId == 25){
       //std::cout << "lheParticles[i][0]= " << lheParticles[i][0] << std::endl;
       higPt = sqrt(lheParticles[i][0]*lheParticles[i][0] + lheParticles[i][1]*lheParticles[i][1]);
       higRap = 0.5*log((lheParticles[i][3]+lheParticles[i][2])/(lheParticles[i][3]-lheParticles[i][2]));
       //std::cout << "PDG id LHE inside loop = " << EvtHandle->hepeup().IDUP[i] << std::endl;
       h_higgsPt->Fill(higPt,weight);
       h_higgsRap->Fill(higRap,weight);
	 //higCands.push_back(ROOT::Math::PxPyPzEVector(lheParticles[i][0],lheParticles[i][1],lheParticles[i][2],lheParticles[i][3]));
     }
     if(absPdgId == 24){
       //std::cout << "lheParticles[i][0]= " << lheParticles[i][0] << std::endl;
       WbosonPt = sqrt(lheParticles[i][0]*lheParticles[i][0] + lheParticles[i][1]*lheParticles[i][1]);
       WbosonRap = 0.5*log((lheParticles[i][3]+lheParticles[i][2])/(lheParticles[i][3]-lheParticles[i][2]));
       //std::cout << "PDG id LHE inside loop = " << EvtHandle->hepeup().IDUP[i] << std::endl;
       h_WbosonPt->Fill(WbosonPt,weight);
       h_WbosonRap->Fill(WbosonRap,weight);
	 //higCands.push_back(ROOT::Math::PxPyPzEVector(lheParticles[i][0],lheParticles[i][1],lheParticles[i][2],lheParticles[i][3]));
     }
     //cout << "higCands.size()=  " << higCands.size() << " & " << "higgs pt= higCands[0].Pt() " << higCands[0].Pt()  <<  std::endl;
     //     if (higCands.size()==1) higPt = higCands[0].pt();
     //h_higgsPt->Fill(higPt,weight);
     //std::cout  << "higPt= " << higPt << std::endl; 
     //std::cout << "PDG id LHE = " << EvtHandle->hepeup().IDUP[i] << std::endl;
     if (EvtHandle->hepeup().IDUP[i] == 21 || abs(EvtHandle->hepeup().IDUP[i]) < 6) npart++;

     mult->Fill(npart,weight);
     if (EvtHandle->hepeup().IDUP[i] ==2 ) nuQuarkMult++;
     uQuarkMult->Fill(nuQuarkMult,weight);
       
   }
   
   return ;   
}

void LHEEventAnalyzer::endJob()
{
}
 
DEFINE_FWK_MODULE(LHEEventAnalyzer);
