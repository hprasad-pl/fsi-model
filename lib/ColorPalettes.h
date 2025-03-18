#ifndef COLORPALETTES_H
#define COLORPALETTES_H

#include "TColor.h"
#include "TStyle.h"
#include "TROOT.h"

class ColorPalettes {
public:
    // Predefined ROOT color palettes
    static const Int_t kRainBow;
    static const Int_t kInvertedDarkBodyRadiator;
    static const Int_t kBird;
    static const Int_t kCubehelix;
    static const Int_t kViridis;
    static const Int_t kCividis;
    static const Int_t kThermal;
    static const Int_t kOcean;
    static const Int_t kDeepSea;
    static const Int_t kTemperatureMap;

    // Mono-color palettes (5 levels)
    static const Int_t kMonoRed[5];
    static const Int_t kMonoBlue[5];
    static const Int_t kMonoGreen[5];
    static const Int_t kMonoYellow[5];
    static const Int_t kMonoMagenta[5];
    static const Int_t kMonoCyan[5];
    static const Int_t kMonoOrange[5];
    static const Int_t kMonoPink[5];
    static const Int_t kMonoViolet[5];
    static const Int_t kMonoTeal[5];
    static const Int_t kMonoPurple[7];

    // Multi-color palettes (4, 5, and 6 levels)
    static const Int_t kMultiColor1[6];
    static const Int_t kMultiColor2[5];
    static const Int_t kMultiColor3[4];
    static const Int_t kMultiColor4[6];
    static const Int_t kMultiColor5[5];
    static const Int_t kMultiColor6[6];
    static const Int_t kMultiColor7[4];
    static const Int_t kMultiColor8[5];
    static const Int_t kMultiColor9[6];
    static const Int_t kMultiColor10[4];
    static const Int_t kMuyu[4];

    static const Int_t BUFu[7];
    static const Int_t Random1[6];
    static const Int_t Random2[5];
    static const Int_t Troy[5];
    static const Int_t OkeeffeCategorical[7];
    static const Int_t Morgenstern[6];

    // Function to set a custom color palette
    static void SetCustomPalette(const Int_t* colors, Int_t nColors);

    // Function to set a mono-color palette
    static void SetMonoColorPalette(const Int_t* colors, Int_t nColors);

    // Function to set a multi-color palette
    static void SetMultiColorPalette(const Int_t* colors, Int_t nColors);
};

// Initialize static members
const Int_t ColorPalettes::kRainBow = 1;
const Int_t ColorPalettes::kInvertedDarkBodyRadiator = 2;
const Int_t ColorPalettes::kBird = 3;
const Int_t ColorPalettes::kCubehelix = 4;
const Int_t ColorPalettes::kViridis = 5;
const Int_t ColorPalettes::kCividis = 6;
const Int_t ColorPalettes::kThermal = 7;
const Int_t ColorPalettes::kOcean = 8;
const Int_t ColorPalettes::kDeepSea = 9;
const Int_t ColorPalettes::kTemperatureMap = 10;

const Int_t ColorPalettes::kMonoRed[5] = {kRed - 9, kRed - 7, kRed - 5, kRed - 3, kRed};
const Int_t ColorPalettes::kMonoBlue[5] = {kBlue - 9, kBlue - 7, kBlue - 5, kBlue - 3, kBlue};
const Int_t ColorPalettes::kMonoGreen[5] = {kGreen - 9, kGreen - 7, kGreen - 5, kGreen - 3, kGreen};
const Int_t ColorPalettes::kMonoYellow[5] = {kYellow - 9, kYellow - 7, kYellow - 5, kYellow - 3, kYellow};
const Int_t ColorPalettes::kMonoMagenta[5] = {kMagenta - 9, kMagenta - 7, kMagenta - 5, kMagenta - 3, kMagenta};
const Int_t ColorPalettes::kMonoCyan[5] = {kCyan - 9, kCyan - 7, kCyan - 5, kCyan - 3, kCyan};
const Int_t ColorPalettes::kMonoOrange[5] = {kOrange - 9, kOrange - 7, kOrange - 5, kOrange - 3, kOrange};
const Int_t ColorPalettes::kMonoPink[5] = {kPink - 9, kPink - 7, kPink - 5, kPink - 3, kPink};
const Int_t ColorPalettes::kMonoViolet[5] = {kViolet - 9, kViolet - 7, kViolet - 5, kViolet - 3, kViolet};
const Int_t ColorPalettes::kMonoTeal[5] = {kTeal - 9, kTeal - 7, kTeal - 5, kTeal - 3, kTeal};
const Int_t ColorPalettes::kMonoPurple[7] = {TColor::GetColor("#ECE1F9"), TColor::GetColor("#D7BFF2"), TColor::GetColor("#B584F6"), TColor::GetColor("#8E68C2"), TColor::GetColor("#674C8D"), TColor::GetColor("#37284B")};

const Int_t ColorPalettes::kMultiColor1[6] = {kBlue, kCyan, kGreen, kYellow, kOrange, kRed};
const Int_t ColorPalettes::kMultiColor2[5] = {kBlue, kCyan, kGreen, kOrange, kRed};
const Int_t ColorPalettes::kMultiColor3[4] = {kBlue, kGreen, kOrange, kRed};
const Int_t ColorPalettes::kMultiColor4[6] = {kMagenta, kViolet, kBlue, kGreen, kYellow, kOrange};
const Int_t ColorPalettes::kMultiColor5[5] = {kTeal, kGreen, kYellow, kOrange, kRed};
const Int_t ColorPalettes::kMultiColor6[6] = {kPink, kMagenta, kViolet, kBlue, kCyan, kGreen};
const Int_t ColorPalettes::kMultiColor7[4] = {kBlue, kCyan, kYellow, kRed};
const Int_t ColorPalettes::kMultiColor8[5] = {kGreen, kYellow, kOrange, kRed, kViolet};
const Int_t ColorPalettes::kMultiColor9[6] = {kBlue, kCyan, kGreen, kYellow, kOrange, kMagenta};
const Int_t ColorPalettes::kMultiColor10[4] = {kTeal, kGreen, kYellow, kOrange};
const Int_t ColorPalettes::kMuyu[4] = {TColor::GetColor("#2066B0"), TColor::GetColor("#439BD4"), TColor::GetColor("#E96D71"), TColor::GetColor("#E4262C")};

// BUFu Palette

const Int_t ColorPalettes::BUFu[7] = {
    TColor::GetColor("#FFFDFD"),
    TColor::GetColor("#E6ECFA"),
    TColor::GetColor("#D5D8F0"),
    TColor::GetColor("#BCB5E6"),
    TColor::GetColor("#9C85B1"),
    TColor::GetColor("#8E5B8D"),
    TColor::GetColor("#4D004B")
};

// Random 1 Palette
const Int_t ColorPalettes::Random1[6] = {
    TColor::GetColor("#D13434"),
    TColor::GetColor("#F08048"),
    TColor::GetColor("#F9AE6A"),
    TColor::GetColor("#B6CBA1"),
    TColor::GetColor("#008585"),
    TColor::GetColor("#002954")
};

// Random 2 Palette
const Int_t ColorPalettes::Random2[5] = {
    TColor::GetColor("#D36B73"),
    TColor::GetColor("#F5C780"),
    TColor::GetColor("#BFBA94"),
    TColor::GetColor("#0054A5"),
    TColor::GetColor("#4565A0")
};

// Troy Palette
const Int_t ColorPalettes::Troy[5] = {
    TColor::GetColor("#D18364"),
    TColor::GetColor("#A05264"),
    TColor::GetColor("#544657"),
    TColor::GetColor("#EEB842"),
    TColor::GetColor("#008585")
};

// Okeeffe Categorical Palette
const Int_t ColorPalettes::OkeeffeCategorical[7] = {
    TColor::GetColor("#682C0C"),
    TColor::GetColor("#9F3A21"),
    TColor::GetColor("#DAC342"),
    TColor::GetColor("#E6B55A"),
    TColor::GetColor("#FBC248"),
    TColor::GetColor("#7D86BA"),
    TColor::GetColor("#133E7E")
};

// Morgenstern Palette

const Int_t ColorPalettes::Morgenstern[6] = {
    TColor::GetColor("#7C5A56"),
    TColor::GetColor("#B08585"),
    TColor::GetColor("#FBC248"),
    TColor::GetColor("#F1B71B"),
    TColor::GetColor("#DB8727"),
    TColor::GetColor("#A55A57")
};






// Function to set a custom color palette
void ColorPalettes::SetCustomPalette(const Int_t* colors, Int_t nColors) {
    Int_t nLevels = nColors;
    Double_t stops[nLevels];
    Double_t red[nLevels];
    Double_t green[nLevels];
    Double_t blue[nLevels];

    for (Int_t i = 0; i < nLevels; i++) {
        TColor* color = gROOT->GetColor(colors[i]);
        stops[i] = Double_t(i) / (nLevels - 1);
        red[i] = color->GetRed();
        green[i] = color->GetGreen();
        blue[i] = color->GetBlue();
    }

    TColor::CreateGradientColorTable(nLevels, stops, red, green, blue, 255);
    gStyle->SetNumberContours(255);
}

// Function to set a mono-color palette
void ColorPalettes::SetMonoColorPalette(const Int_t* colors, Int_t nColors) {
    SetCustomPalette(colors, nColors);
}

// Function to set a multi-color palette
void ColorPalettes::SetMultiColorPalette(const Int_t* colors, Int_t nColors) {
    SetCustomPalette(colors, nColors);
}

#endif // COLORPALETTES_H
