#include "TCanvas.h"
#include "TPad.h"

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

void test() {

    TCanvas* canvas = CreateCanvasWithResidualPad("myCanvas", "My Canvas Title", 800, 600, 0.3, kWhite);
    
    // Access the pads from the canvas
    TPad* mainPad = (TPad*)canvas->GetListOfPrimitives()->FindObject("mainPad");
    TPad* residualPad = (TPad*)canvas->GetListOfPrimitives()->FindObject("residualPad");

    // Create histograms for the main plot and residual plot
    TH1D* mainHist = new TH1D("mainHist", "Main Histogram", 100, 0, 100);
    TH1D* residualHist = new TH1D("residualHist", "Residual Histogram", 100, 0, 100);

    // Fill the histograms with some data
    for (Int_t i = 0; i < 100; i++) {
        mainHist->Fill(i);
        residualHist->Fill(i, i % 10 - 5); // Example residual data
    }

    // Draw the main plot on the top pad
    mainPad->cd(); // Switch to the main pad
    mainHist->Draw();

    // Draw the residual plot on the bottom pad
    residualPad->cd(); // Switch to the residual pad
    residualHist->Draw();

}
