#include "lib/event.h"
#include <iostream>
#include <stdio.h>
#include <TRandom3.h>

using namespace std;

const double org_probability_of_interaction = 0.01;
const int progressBarWidth = 40;

void Copy(event *e_copy, event *e_org)
{
  e_copy->number_of_interaction_points = e_org->number_of_interaction_points;
  e_copy->number_of_non_interaction_points = e_org->number_of_non_interaction_points;

  int total_interaction_points = e_org->number_of_non_interaction_points + e_org->number_of_interaction_points;

  for(int index=0; index<total_interaction_points; index++)
  {
    e_copy->trajectory[index] = e_org->trajectory[index];
  }
}

double reweighting_function(double p, double p_prime, int n_interactions, int n_non_interactions)
{
  return ( std::pow( p_prime/p , n_interactions)*std::pow( (1-p_prime)/(1-p) , n_non_interactions)  );
}

void analyze3()
{
  TRandom3 rand(0);

  TFile *file = new TFile("events_p=0.01.root");
  TTree *tree = (TTree*)file->Get("treeout");
  event *e = new event();
  tree->SetBranchAddress("e", &e);
  Int_t nentries = (Int_t)tree->GetEntries();

  double probability_of_interaction = 1;
  cout << "probability_of_interaction (new) : " ;
  cin >> probability_of_interaction;

  std::ostringstream filename;
  filename << "reweighted_events_p="<<org_probability_of_interaction<<"_to_p="<<probability_of_interaction<<".root";

  TFile *outfile = new TFile( (filename.str()).c_str(), "RECREATE");
  outfile->cd();
  TTree *tf = new TTree("treeout", "tree of events");
  event *ev = new event();
  tf->Branch("e", "event", &ev);
  delete ev;

  for(Int_t event_index=0; event_index<nentries; event_index++) {
    ev = new event();
    tree->GetEntry(event_index);
    double R = reweighting_function(org_probability_of_interaction, probability_of_interaction, e->number_of_interaction_points, e->number_of_non_interaction_points);
    Copy(ev, e);

    if (R < 1) {
      if( rand.Rndm() < (1-R) ) {
        continue;
      } else {
        tf->Fill();
      }
    } else if (R > 1) {
      if (rand.Rndm() < R-1 ) {
        tf->Fill();
        tf->Fill();     //Dublicate the trajectory
      } else {
        tf->Fill();
      }
    }
 
    // Calculate the percentage
    double percentage = static_cast<double>(event_index+1) / nentries * 100.0;
    // Calculate the number of progress bar characters
    int progressBarCount = static_cast<int>(percentage / 100.0 * progressBarWidth);

    // Print the progress bar
    std::cout << "Events generated : " << " [";
    for (int k = 0; k < progressBarCount; ++k)
    {
      std::cout << "=";
    }
    for (int k = progressBarCount; k < progressBarWidth; ++k)
    {
      std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(percentage) << "%" << "\r";
    std::cout.flush();

  }
  cout << std::endl;

  tf->Write();
  delete tf;
  outfile->Close();

  cout << "Reweighted events  stored in : " << filename.str() << "\n"; 
  
}
