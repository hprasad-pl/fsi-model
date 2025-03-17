#include "lib/event.h"
#include "lib/LineStyles.h"
#include "lib/FillStyles.h"
#include "lib/Colors.h"
#include <iostream>
#include <stdio.h>

void Generate_poisson_samples(TH1D *hist) 
{
  TRandom rand;
  double p = 0.01;
  double K = 50;
  double lambda = K * p;
    // Generate 100,000 samples from the Poisson distribution
    Int_t numSamples = 100000;
    for (Int_t i = 0; i < numSamples; i++) {
        Int_t sample = rand.Poisson(lambda); // Generate a Poisson-distributed random number
        hist->Fill(sample); // Fill the histogram
    }

}
void SetHistAttributes(TH1D *h, TString xlabel, TString ylabel, int linestyle, int linecolor, int linewidth);
void SetCanvasAttributes(TCanvas *c);
TLegend* CreateLegendAutoPosition(TH1* hist, const char* header = "");

void analyze()
{
  TFile *file = new TFile("events_p=0.01.root");
  TTree *tree = (TTree*)file->Get("treeout");
  event *e = new event();
  tree->SetBranchAddress("e", &e);
  Int_t nentries = (Int_t)tree->GetEntries();

  TH1D *h = new TH1D("h", "; No. of interactions; entries", 10, 0, 10);
  TH1D *poisson = new TH1D("poisson", "; No. of interactions; P(x)", 10, 0, 10);
  TH1D *interaction_dist = new TH1D("interaction_dist", "; Point of interaction; entries", 50, 0, 50);

  for(Int_t event_index=0; event_index<nentries; event_index++){
    tree->GetEntry(event_index);
    
    int count_interactions=0;
    for(int i=0; i<50; i++) {
      count_interactions = e->trajectory[i] ? count_interactions+1 : count_interactions;
      if (e->trajectory[i]) {
        interaction_dist->Fill(i);
      }
    }
    h->Fill(count_interactions);
  }

  h->Scale(1/h->Integral());
  Generate_poisson_samples(poisson);
  poisson->Scale(1/poisson->Integral());

  TString xlabel = "Number of interactions";
  TString ylabel = "event (normalized)";
  
  SetHistAttributes(h, xlabel, ylabel, LineStyles::Dashed, Colors::kOrange1, 2);
  SetHistAttributes(poisson, xlabel, ylabel, LineStyles::Custom4, Colors::kNavy1, 2);

  TString xlabel2 = "Point of interaction";
  TString ylabel2 = "Entries (normalized)";
  SetHistAttributes(interaction_dist, xlabel2, ylabel2, LineStyles::Solid, Colors::kTeal1, 2);

  TCanvas *c = new TCanvas("c", "Dist of number of interaction", 1000, 1000);
  SetCanvasAttributes(c);  
  h->Draw("HIST");
  poisson->Draw("HIST, SAME");
  // Create a legend using the function
    TLegend* legend = CreateLegendAutoPosition(h, "Legend");

    // Add entries to the legend
    legend->AddEntry(h, "Simulation", "l"); // "l" for line
    legend->AddEntry(poisson, "Poisson Distribution", "l");

    // Draw the legend
    legend->Draw();

  TCanvas *c2 = new TCanvas("c2", "Dist  of interaction points", 900, 900);
  SetCanvasAttributes(c2);
  interaction_dist->SetMinimum(0);
  interaction_dist->SetMaximum( interaction_dist->GetMaximum() + nentries/100);
  interaction_dist->Draw("HIST");
  // Create a legend using the function
    TLegend* legend2 = CreateLegendAutoPosition(interaction_dist, "Legend");

    // Add entries to the legend
    legend2->AddEntry(interaction_dist, "Simulation", "l"); // "l" for line
    
    // Draw the legend
    legend2->Draw();

}

void SetHistAttributes(TH1D *h, TString xlabel, TString ylabel, int linestyle, int linecolor, int linewidth)
{
  h->SetStats(0);
  TAxis *xaxis = (TAxis*)h->GetXaxis();
  TAxis *yaxis = (TAxis*)h->GetYaxis();

  //yaxis->SetNdimension(510);
  xaxis->SetTickLength(0.03);
  xaxis->SetTitle(xlabel);
  xaxis->SetTitleSize(0.08);
  xaxis->SetTitleFont(132);
  xaxis->CenterTitle(true);
  xaxis->SetLabelSize(0.06);
  xaxis->SetLabelFont(132);

  //yaxis->SetNdimension(510);
  yaxis->SetTickLength(0.03);
  yaxis->SetTitle(ylabel);
  yaxis->SetTitleSize(0.08);
  yaxis->SetTitleFont(132);
  yaxis->CenterTitle(true);
  yaxis->SetLabelSize(0.06);
  yaxis->SetLabelFont(132);

  h->SetLineStyle(linestyle);
  h->SetLineColor(linecolor);
  h->SetLineWidth(linewidth);
}

void SetCanvasAttributes(TCanvas *c)
{
  c->SetLeftMargin(0.2);
  c->SetRightMargin(0.2);
  c->SetTopMargin(0.2);
  c->SetBottomMargin(0.2);
}

TLegend* CreateLegendAutoPosition(TH1* hist, const char* header = "") {
    // Get the current pad (canvas)
    TPad* pad = (TPad*)gPad;
    if (!pad) {
        std::cerr << "Error: No active pad found!" << std::endl;
        return nullptr;
    }

    // Get the coordinates of the plot box (frame)
    Double_t x1 = pad->GetUxmin(); // Left edge of the plot box
    Double_t x2 = pad->GetUxmax(); // Right edge of the plot box
    Double_t y1 = pad->GetUymin(); // Bottom edge of the plot box
    Double_t y2 = pad->GetUymax(); // Top edge of the plot box

    // Define the legend position (top-right corner)
    Double_t legendWidth = 0.2 * (x2 - x1); // Width of the legend (20% of plot width)
    Double_t legendHeight = 0.15 * (y2 - y1); // Height of the legend (15% of plot height)
    Double_t legendX1 = x2 - legendWidth - 0.05 * (x2 - x1); // X1 position (5% padding from right)
    Double_t legendY1 = y2 - legendHeight - 0.05 * (y2 - y1); // Y1 position (5% padding from top)
    Double_t legendX2 = x2 - 0.05 * (x2 - x1); // X2 position (5% padding from right)
    Double_t legendY2 = y2 - 0.05 * (y2 - y1); // Y2 position (5% padding from top)

    // Create a TLegend object with the calculated coordinates
    TLegend* legend = new TLegend(legendX1, legendY1, legendX2, legendY2);

    // Set the font to "132" (bold, italic, Times)
    legend->SetTextFont(132);

    // Set the legend header (optional)
    if (strlen(header) > 0) {
        legend->SetHeader(header, "C"); // "C" for centered header
    }

    // Set the legend border size (0 = no border, 1 = thin border, 2 = thick border)
    legend->SetBorderSize(1);

    // Set the legend fill style (0 = hollow, 1001 = solid)
    legend->SetFillStyle(0); // Hollow fill

    // Set the legend text size
    legend->SetTextSize(0.04); // Adjust as needed

    // Set the legend text alignment (left, center, right)
    legend->SetTextAlign(12); // Centered and vertically aligned

    // Set the legend margin (space between text and box border)
    legend->SetMargin(0.15); // Adjust as needed

    // Set the legend entry spacing (space between entries)
    legend->SetEntrySeparation(0.5); // Adjust as needed

    // Set the legend fill color (if fill style is not hollow)
    legend->SetFillColor(kWhite); // White background

    // Set the legend line color (border color)
    legend->SetLineColor(kBlack); // Black border

    // Set the legend line width (border thickness)
    legend->SetLineWidth(1); // Adjust as needed

    return legend;
}
