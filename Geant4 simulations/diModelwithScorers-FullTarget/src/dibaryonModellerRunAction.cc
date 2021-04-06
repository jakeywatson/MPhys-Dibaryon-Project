/// \file dibaryonModellerRunAction.cc
/// \brief Implementation of the dibaryonModellerRunAction class

#include "dibaryonModellerRunAction.hh"
#include "dibaryonModellerPrimaryGeneratorAction.hh"
#include "dibaryonModellerDetectorConstruction.hh"

#include "dibaryonModellerAnalysis.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4ParameterManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerRunAction::dibaryonModellerRunAction(dibaryonModellerDetectorConstruction* detCon)
	: G4UserRunAction(),
	fDet(detCon)
{
	// set printing event number per each event
	G4RunManager::GetRunManager()->SetPrintProgress(1);

	// Create analysis manager
	// The choice of analysis technology is done via selectin of a namespace
	// in B4Analysis.hh
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	G4cout << "Using " << analysisManager->GetType() << G4endl;

	// Create directories 
	//analysisManager->SetHistoDirectoryName("histograms");
	//analysisManager->SetNtupleDirectoryName("ntuple");
	analysisManager->SetVerboseLevel(1);

	// Book histograms, ntuple
	//

	// Creating ntuple
	//
	analysisManager->CreateNtuple("Dibaryon_Modeller", "E_Dep");
	analysisManager->CreateNtupleDColumn("Incident_Angle");
	analysisManager->CreateNtupleDColumn("Incident_Energy");

	for (G4int i = 2; i < 12; i++) {
		G4String col_name = "Layer_" + std::to_string(i-2);
		analysisManager->CreateNtupleDColumn(col_name);
	}
	analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerRunAction::~dibaryonModellerRunAction()
{ 
	delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void dibaryonModellerRunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
  
  // reset parameters to their initial values
  G4ParameterManager* parameterManager = G4ParameterManager::Instance();
  parameterManager->Reset();
  
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4String fileName = "dibaryonModeller";
  analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void dibaryonModellerRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // Merge parameters 
  G4ParameterManager* parameterManager = G4ParameterManager::Instance();
  parameterManager->Merge();

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const dibaryonModellerPrimaryGeneratorAction* generatorAction
    = static_cast<const dibaryonModellerPrimaryGeneratorAction*>(
        G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());

  G4String partName;
  if (generatorAction) 
  {
    G4ParticleDefinition* particle 
      = generatorAction->GetParticleGun()->GetParticleDefinition();
    partName = particle->GetParticleName();
  }  
          
  // Print results
  //
  analysisManager->Write();
  analysisManager->CloseFile();

  if (IsMaster())
  {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------"
     << G4endl
     << "  The run was " << nofEvents << " events ";
  }
  else
  {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------"
     << G4endl
     << "  The run was " << nofEvents << " "<< partName;
  }      
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
