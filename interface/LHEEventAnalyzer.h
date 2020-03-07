#ifndef LHEEventAnalyzer_H
#define LHEEventAnalyzer_H
#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"

// forward declarations
class TFile;
class TH2D;

class LHEEventAnalyzer : public edm::EDAnalyzer
{

   public:
   
      //
      explicit LHEEventAnalyzer( const edm::ParameterSet& ) ;
      virtual ~LHEEventAnalyzer(); // no need to delete ROOT stuff
                               // as it'll be deleted upon closing TFile
      
      virtual void analyze( const edm::Event&, const edm::EventSetup& ) ;
      virtual void beginJob() ;
      virtual void endJob() ;

   private:
   
     //
     std::string fOutputFileName ;
     std::string theSrc ;
     int         whichWeight;
     TFile*      fOutputFile ;
     TH1D*       mult;
     TH1D*       uQuarkMult;
     TH1F*       h_higgsPt;
     TH1F*       h_higgsRap;
     TH1F*       h_WbosonPt;
     TH1F*       h_WbosonRap;
     int nevent;
     edm::EDGetTokenT< LHEEventProduct > lhep_token;
     std::vector<lhef::HEPEUP::FiveVector> lheParticles;
     std::vector<ROOT::Math::PxPyPzEVector> higCands;
     // edm::EDGetTokenT<std::vector<reco::GenParticle> > genp_token;
     
};

#endif
