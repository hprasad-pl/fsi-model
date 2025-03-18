#include "lib/event.h"
#include "lib/Colors.h"
#include "lib/LineStyles.h"
#include "lib/FillStyles.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <TCanvas.h>
#include <TPad.h>
#include <TString.h>



void SetHistAttributes(TH1D *h, TString xlabel, TString ylabel, int linestyle, int linecolor, int linewidth);
void SetCanvasAttributes(TCanvas *c);
TLegend* CreateLegendAutoPosition(TH1* hist, const char* header = "");
TCanvas* CreateCanvas(const char* name, const char* title, Int_t width, Int_t height, Color_t backgroundColor = kWhite);
TCanvas* CreateCanvas(const char* name, const char* title, Int_t width, Int_t height, Int_t nPads = 1, const char* divisionMode = "tile", Double_t padSpacing = 0.01, Color_t backgroundColor = kWhite);


void analyze4()
{
  std::vector<std::string> filenames {"events_p=0.008.root", "reweighted_events_p=0.01_to_p=0.008.root"};
  TH1D *h[(const int)filenames.size()];

  for(int file_index=0; file_index<filenames.size(); file_index++) {
    TFile *file = new TFile(filenames.at(file_index).c_str());
    TTree *tree = (TTree*)file->Get("treeout");
    event *e = new event();
    tree->SetBranchAddress("e", &e);
    Int_t nentries = (Int_t)tree->GetEntries();

    h[file_index] = new TH1D(filenames.at(file_index).c_str(), "; No. of interactions; entries", 10, 0, 10);
   
    for(Int_t event_index=0; event_index<nentries; event_index++){
      tree->GetEntry(event_index);
      h[file_index]->Fill(e->number_of_interaction_points);
    }

    h[file_index]->Scale(1/h[file_index]->Integral());
  }

  TString xlabel = "Number of interaction";
  TString ylabel = "Events (normalized)";

  SetHistAttributes(h[0], xlabel, ylabel, LineStyles::Solid, Colors::kBlack1, 3);
  SetHistAttributes(h[1], xlabel, ylabel, LineStyles::Dashed, Colors::kMagenta1, 3);

  TCanvas *c = CreateCanvas("c", "Distribution", 1000, 1000, kGray);

  SetCanvasAttributes(c);
  h[0]->Draw("HIST");
  h[1]->Draw("HIST, SAME");


  // Create a legend using the function
    TLegend* legend = CreateLegendAutoPosition(h[0], "Legend");

    // Add entries to the legend
    legend->AddEntry(h[0], "Simulation", "l"); // "l" for line
    legend->AddEntry(h[1], "Reweighted to p=0.08", "l");

    // Draw the legend
    legend->Draw();
  
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

    // Define the legend position in NDC coordinates (top-right corner)
    Double_t legendWidth = 0.2; // Width of the legend (20% of canvas width)
    Double_t legendHeight = 0.15; // Height of the legend (15% of canvas height)
    Double_t legendX1 = 0.75; // X1 position (75% from left)
    Double_t legendY1 = 0.75; // Y1 position (75% from bottom)
    Double_t legendX2 = legendX1 + legendWidth; // X2 position
    Double_t legendY2 = legendY1 + legendHeight; // Y2 position

    // Create a TLegend object with the calculated NDC coordinates
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

// Function to create and return a TCanvas pointer
TCanvas* CreateCanvas(const char* name, const char* title, Int_t width, Int_t height, Color_t backgroundColor = kWhite) {
    // Create a new TCanvas object with the specified parameters
    TCanvas* canvas = new TCanvas(name, title, width, height);

    // Set the background color
    canvas->SetFillColor(backgroundColor);

    // Customize the canvas (optional)
    canvas->SetGrid(); // Enable grid
    canvas->SetRightMargin(0.05); // Adjust margins
    canvas->SetLeftMargin(0.10);
    canvas->SetTopMargin(0.05);
    canvas->SetBottomMargin(0.10);

    // Return the pointer to the created canvas
    return canvas;
}

TCanvas* CreateCanvas(const char* name, const char* title, Int_t width, Int_t height, Int_t nPads = 1, const char* divisionMode = "tile", Double_t padSpacing = 0.0, Color_t backgroundColor = kWhite) {
    // Create a new TCanvas object with the specified parameters
    TCanvas* canvas = new TCanvas(name, title, width, height);

    // Set the background color
    canvas->SetFillColor(backgroundColor);

    // Divide the canvas into pads based on the number of pads and division mode
    if (nPads > 1) {
        Int_t nRows = 1, nCols = 1;

        // Determine the number of rows and columns based on the division mode
        if (TString(divisionMode) == "horizontal") {
            nRows = 1;
            nCols = nPads;
        } else if (TString(divisionMode) == "vertical") {
            nRows = nPads;
            nCols = 1;
        } else if (TString(divisionMode) == "tile") {
            nRows = TMath::CeilNint(TMath::Sqrt(nPads)); // Square root for tiling
            nCols = TMath::CeilNint((Double_t)nPads / nRows);
        } else {
            std::cerr << "Error: Invalid division mode. Using 'tile' as default." << std::endl;
            nRows = TMath::CeilNint(TMath::Sqrt(nPads));
            nCols = TMath::CeilNint((Double_t)nPads / nRows);
        }

        // Divide the canvas into sub-pads
        canvas->Divide(nCols, nRows, padSpacing, padSpacing);

        // Customize the sub-pads (optional)
        for (Int_t i = 1; i <= nPads; i++) {
            TPad* pad = (TPad*)canvas->cd(i); // Get the i-th pad
            pad->SetFillColor(backgroundColor); // Set the background color
            pad->SetGrid(); // Enable grid
            pad->SetRightMargin(0.05); // Adjust margins
            pad->SetLeftMargin(0.10);
            pad->SetTopMargin(0.05);
            pad->SetBottomMargin(0.10);
        }
    } else {
        // Customize the single pad (optional)
        canvas->SetGrid(); // Enable grid
        canvas->SetRightMargin(0.05); // Adjust margins
        canvas->SetLeftMargin(0.10);
        canvas->SetTopMargin(0.05);
        canvas->SetBottomMargin(0.10);
    }

    // Return the pointer to the created canvas
    return canvas;
}
