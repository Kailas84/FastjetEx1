// -*- C++ -*-
//
// Package:    FastJetEx/FastJetEx1
// Class:      FastJetEx1
//
/**\class FastJetEx1 FastJetEx1.cc FastJetEx/FastJetEx1/plugins/FastJetEx1.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Balashangar Kailasapathy
//         Created:  Mon, 06 Jul 2020 13:18:20 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

// Header file for FastJet Analysis
#include "DataFormats/PatCandidates/interface/IsolatedTrack.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "fastjet/ClusterSequence.hh"

using reco::TrackCollection;

class FastJetEx1 : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit FastJetEx1(const edm::ParameterSet&);
      ~FastJetEx1();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<std::vector<pat::IsolatedTrack>> tracksToken;  //used to select what tracks to read from configuration file

};


FastJetEx1::FastJetEx1(const edm::ParameterSet& iConfig)
:
tracksToken(consumes<std::vector<pat::IsolatedTrack>>(edm::InputTag("isolatedTracks")))

{
        //now do what ever initialization is needed

}








FastJetEx1::~FastJetEx1()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

// ------------ method called for each event  ------------
void
FastJetEx1::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   Handle<std::vector<pat::IsolatedTrack>> tracks;

        iEvent.getByToken(tracksToken, tracks);

//      std::vector<fastjet::PseudoJet> input_particles;

        for(std::vector<pat::IsolatedTrack>::const_iterator itTrack = tracks->begin();
        //for(std::vector<pat::Jet>::const_iterator itTrack = tracks->begin();
        itTrack != tracks->end();
        ++itTrack) {
      // do something with track parameters, e.g, plot the charge.
        int charge = itTrack->charge();
        std::cout<<charge<<std::endl;

//      input_particles.push_back(fastjet::PseudoJet(itTrack->px(),itTrack->py(),itTrack->pz(),itTrack->energy()));

    }
/*      double R = 0.6;
        fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, R);
    fastjet::ClusterSequence clust_seq(input_particles, jet_def);

        //double ptmin = 5.0;
        std::vector<fastjet::PseudoJet> inclusive_jets = clust_seq.inclusive_jets();

        std::cout<< "Number  of jets = "<<inclusive_jets.size()<<std::endl;
        for (unsigned int i = 0; i < inclusive_jets.size(); i++) {
     printf("%5u %15.8f %15.8f %15.8f\n",
            i, inclusive_jets[i].rap(), inclusive_jets[i].phi(),
            inclusive_jets[i].perp());

   }


*/

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
FastJetEx1::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
FastJetEx1::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
FastJetEx1::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(FastJetEx1);


