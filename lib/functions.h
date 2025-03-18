#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <stdio.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TPad.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TLegend.h>

#include "FillStyles.h"
#include "ColorPalettes.h"
#include "Colors.h"
#include "LineStyles.h"


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


TCanvas* CreateCanvasWithResidualPad(const char* name, const char* title, Int_t width, Int_t height, Double_t residualPadFraction = 0.3, Color_t backgroundColor = kWhite) {
    // Create a new TCanvas object with the specified parameters
    TCanvas* canvas = new TCanvas(name, title, width, height);

    // Set the background color
    canvas->SetFillColor(backgroundColor);

    // Divide the canvas into two pads: main plot (top) and residual plot (bottom)
    TPad* mainPad = new TPad("mainPad", "Main Pad", 0.0, residualPadFraction, 1.0, 1.0); // Top pad
    TPad* residualPad = new TPad("residualPad", "Residual Pad", 0.0, 0.0, 1.0, residualPadFraction); // Bottom pad

    // Customize the main pad
    mainPad->SetFillColor(backgroundColor);
    mainPad->SetGrid();
    mainPad->SetRightMargin(0.05);
    mainPad->SetLeftMargin(0.10);
    mainPad->SetTopMargin(0.05);
    mainPad->SetBottomMargin(0.0); // No bottom margin to align with the residual pad

    // Customize the residual pad
    residualPad->SetFillColor(backgroundColor);
    residualPad->SetGrid();
    residualPad->SetRightMargin(0.05);
    residualPad->SetLeftMargin(0.10);
    residualPad->SetTopMargin(0.0); // No top margin to align with the main pad
    residualPad->SetBottomMargin(0.15); // Extra space for the x-axis label

    // Add the pads to the canvas
    canvas->cd();
    mainPad->Draw();
    residualPad->Draw();

    // Return the pointer to the created canvas
    return canvas;
}

#endif
