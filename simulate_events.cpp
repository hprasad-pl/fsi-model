#include "lib/event.h"
#include <iostream>
#include <stdio.h>
#include <TFile.h>
#include <TTree.h>
#include <TRandom3.h>
#include <sstream>

using namespace std;

const int progressBarWidth = 40;

void monte_carlo_binomial(int* arr, double p, int& number_of_interaction_points, int& number_of_non_interaction_points) {
    TRandom3 randGen(0); // Seed with 0 for reproducibility

    for (int i = 0; i < 50; i++) {
        double randNum = randGen.Rndm(); // Generates a uniform [0,1] random number
        arr[i] = (randNum < p) ? 1 : 0; // Assign 1 with probability p, else 0
        number_of_interaction_points = arr[i] ? number_of_interaction_points+1 : number_of_interaction_points;
        number_of_non_interaction_points = arr[i] ? number_of_non_interaction_points-1 : number_of_non_interaction_points;
    }
}

int main()
{
  double probability_of_interaction = 0.01;
  double fractional_increase = 1;

  cout << "probability of Interaction = " << probability_of_interaction << "\n";
  cout << "Fractional increase f * p : f = ";
  cin >> fractional_increase;

  Int_t nr_events = 100000;
  std::ostringstream filename;

  filename << "events_p=" << fractional_increase*probability_of_interaction << ".root";
  
  TFile *file = new TFile( (filename.str()).c_str(), "RECREATE");
  TTree *tree = new TTree("treeout", "tree of events");
  event *e = new event();

  tree->Branch("e","event", &e);
  delete e;

  for(int event_index=0; event_index<nr_events; event_index++) {
  e = new event;
  monte_carlo_binomial(e->trajectory, fractional_increase*probability_of_interaction, e->number_of_interaction_points, e->number_of_non_interaction_points);
 

  // Calculate the percentage
  double percentage = static_cast<double>(event_index+1) / nr_events * 100.0;
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
  tree->Fill();
  
  }

  tree->Write();
  delete tree;
  file->Close();
  delete file;


  return 0;
}
