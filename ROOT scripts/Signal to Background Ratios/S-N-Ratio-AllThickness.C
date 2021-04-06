{
gStyle->SetOptStat(0);
gStyle->SetOptFit(1111111);
gStyle->SetOptStat(00000);
gStyle->SetPadTickX(1);
gStyle->SetPadTickY(1);
gStyle->SetStatY(0.50);
gStyle->SetStatX(0.95);
gStyle->SetStatW(0.25);
gStyle->SetStatH(0.2);
gStyle->SetLabelSize(0.05, "X");
gStyle->SetTitleSize(0.06, "X");
//gStyle->SetTitleOffset(1.2,"X");
gStyle->SetTitleOffset(0.85, "X");
gStyle->SetNdivisions(606, "Y");
gStyle->SetNdivisions(612, "X");

gStyle->SetLabelSize(0.05, "Y");
gStyle->SetTitleSize(0.06, "Y");
//gStyle->SetTitleOffset(1.2,"Y");
gStyle->SetTitleOffset(0.85, "Y");

int nbins = 200;

TCanvas *Backgrounds1mm = new TCanvas("Backgrounds1mm", "Backgrounds1mm", 100, 10, 1500, 800);
Backgrounds1mm->Divide(2, 2);

TCanvas *BackgroundTotal1mm = new TCanvas("BackgroundTotal1mm", "BackgroundTotal1mm", 100, 10, 1500, 800);

TCanvas *Signal1mm = new TCanvas("Signal1mm", "Signal1mm", 100, 10, 1500, 800);

//First file
//Create a filereader
TFile f11mm("photons-1M-1mm.root");

//Create a Tree filled by the filereader
TTree *t11mm = (TTree*)f11mm.Get("Dibaryon_Modeller");

//Second file
//Create a filereader
TFile f21mm("protons-1M-1mm.root");

//Create a Tree filled by the filereader
TTree *t21mm = (TTree*)f21mm.Get("Dibaryon_Modeller");

//Third File Input
//Create a filereader
TFile f31mm("deuterons-1M-1mm.root");

//Create a Tree filled by the filereader
TTree *t31mm = (TTree*)f31mm.Get("Dibaryon_Modeller");

//This is where I make a histogram to determine the background contamination as a function of the incident energy. 
//I take all the cuts I've made previously for each stopping case, and apply them here.

TH1F *BackgroundL51mm = new TH1F("BackgroundL51mm", "BackgroundL51mm", nbins, 0, 190);
TH1F *BackgroundL41mm = new TH1F("BackgroundL41mm", "BackgroundL41mm", nbins, 0, 190);
TH1F *BackgroundL31mm = new TH1F("BackgroundL31mm", "BackgroundL31mm", nbins, 0, 190);
TH1F *BackgroundL21mm = new TH1F("BackgroundL21mm", "BackgroundL21mm", nbins, 0, 190);

t11mm.Draw("Incident_Energy>>+BackgroundL51mm", "Layer_1 > -0.625*Layer_2 + 5 && Layer_2 > -0.67*Layer_3 + 6 && Layer_3 > -0.375*Layer_4 + 6 && Layer_4 > -0.26*Layer_5 + 9 && Layer_1 + Layer_2 > -0.83*Layer_3 + 10 && Layer_1 + Layer_2 + Layer_3 >  -0.84*Layer_4 + 16 && Layer_1 + Layer_2 + Layer_3 + Layer_4 > -0.33*Layer_5 + 20 &&  Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t11mm.Draw("Incident_Energy>>+BackgroundL41mm", "Layer_1 < 4.33*Layer_2 - 13 && Layer_3 > 5 && Layer_3 > -0.23*Layer_4 + 7 && Layer_1+Layer_2+Layer_3 > -1.5*Layer_4 + 24 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t11mm.Draw("Incident_Energy>>+BackgroundL31mm", "Layer_1 < 5*Layer_2 -20 && Layer_2 >  -0.9375*Layer_3 + 15 && Layer_1+Layer_2 >  -1.07*Layer_3 + 16 && Layer_1>0  && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t11mm.Draw("Incident_Energy>>+BackgroundL21mm", "Layer_1 > -1.64*Layer_2 + 18 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double photon_background1mm = (BackgroundL51mm->Integral()+BackgroundL41mm->Integral() + BackgroundL31mm->Integral() + BackgroundL21mm->Integral())*1000.0;

t21mm.Draw("Incident_Energy>>+BackgroundL51mm", "Layer_1 > -0.625*Layer_2 + 5 && Layer_2 > -0.67*Layer_3 + 6 && Layer_3 > -0.375*Layer_4 + 6 && Layer_4 > -0.26*Layer_5 + 9 && Layer_1 + Layer_2 > -0.83*Layer_3 + 10 && Layer_1 + Layer_2 + Layer_3 >  -0.84*Layer_4 + 16 && Layer_1 + Layer_2 + Layer_3 + Layer_4 > -0.33*Layer_5 + 20 &&  Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t21mm.Draw("Incident_Energy>>+BackgroundL41mm", "Layer_1 < 4.33*Layer_2 - 13 && Layer_3 > 5 && Layer_3 > -0.23*Layer_4 + 7 && Layer_1+Layer_2+Layer_3 > -1.5*Layer_4 + 24 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t21mm.Draw("Incident_Energy>>+BackgroundL31mm", "Layer_1 < 5*Layer_2 -20 && Layer_2 >  -0.9375*Layer_3 + 15 && Layer_1+Layer_2 >  -1.07*Layer_3 + 16 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t21mm.Draw("Incident_Energy>>+BackgroundL21mm", "Layer_1 > -1.64*Layer_2 + 18 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double proton_background1mm = (BackgroundL51mm->Integral() + BackgroundL41mm->Integral() + BackgroundL31mm->Integral() + BackgroundL21mm->Integral() - (photon_background1mm / 1000))*100.0;

Backgrounds1mm->cd(1);
BackgroundL21mm->Draw("");
Backgrounds1mm->cd(2);
BackgroundL31mm->Draw("");
Backgrounds1mm->cd(3);
BackgroundL41mm->Draw("");
Backgrounds1mm->cd(4);
BackgroundL51mm->Draw("");

cout << "photon count for 1mm: " << photon_background1mm << endl;
cout << "proton count for 1mm: " << proton_background1mm << endl;

BackgroundTotal1mm->cd();

TH1F *BackgroundHist1mm = new TH1F("BackgroundHist1mm", "BackgroundHist1mm", nbins, 0, 190);
t11mm.Draw("Incident_Energy>>+BackgroundHist1mm", "Layer_1 > -0.625*Layer_2 + 5 && Layer_2 > -0.67*Layer_3 + 6 && Layer_3 > -0.375*Layer_4 + 6 && Layer_4 > -0.26*Layer_5 + 9 && Layer_1 + Layer_2 > -0.83*Layer_3 + 10 && Layer_1 + Layer_2 + Layer_3 >  -0.84*Layer_4 + 16 && Layer_1 + Layer_2 + Layer_3 + Layer_4 > -0.33*Layer_5 + 20 &&  Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t11mm.Draw("Incident_Energy>>+BackgroundHist1mm", "Layer_1 < 4.33*Layer_2 - 13 && Layer_3 > 5 && Layer_3 > -0.23*Layer_4 + 7 && Layer_1+Layer_2+Layer_3 > -1.5*Layer_4 + 24 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t11mm.Draw("Incident_Energy>>+BackgroundHist1mm", "Layer_1 < 5*Layer_2 -20 && Layer_2 >  -0.9375*Layer_3 + 15 && Layer_1+Layer_2 >  -1.07*Layer_3 + 16 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t11mm.Draw("Incident_Energy>>+BackgroundHist1mm", "Layer_1 > -1.64*Layer_2 + 18 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

t21mm.Draw("Incident_Energy>>+BackgroundHist1mm", "Layer_1 > -0.625*Layer_2 + 5 && Layer_2 > -0.67*Layer_3 + 6 && Layer_3 > -0.375*Layer_4 + 6 && Layer_4 > -0.26*Layer_5 + 9 && Layer_1 + Layer_2 > -0.83*Layer_3 + 10 && Layer_1 + Layer_2 + Layer_3 >  -0.84*Layer_4 + 16 && Layer_1 + Layer_2 + Layer_3 + Layer_4 > -0.33*Layer_5 + 20 &&  Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t21mm.Draw("Incident_Energy>>+BackgroundHist1mm", "Layer_1 < 4.33*Layer_2 - 13 && Layer_3 > 5 && Layer_3 > -0.23*Layer_4 + 7 && Layer_1+Layer_2+Layer_3 > -1.5*Layer_4 + 24 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t21mm.Draw("Incident_Energy>>+BackgroundHist1mm", "Layer_1 < 5*Layer_2 -20 && Layer_2 >  -0.9375*Layer_3 + 15 && Layer_1+Layer_2 >  -1.07*Layer_3 + 16 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t21mm.Draw("Incident_Energy>>+BackgroundHist1mm", "Layer_1 > -1.64*Layer_2 + 18 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

BackgroundHist1mm->GetYaxis()->SetTitle("Background Count");
BackgroundHist1mm->GetXaxis()->SetTitle("Deuteron and Photon Incident Energy [MeV]");
BackgroundHist1mm->SetTitle("Background Count against Incident Energy - 1mm");
BackgroundHist1mm->SetLineColor(kRed);
BackgroundHist1mm->SetOption("C");

BackgroundHist1mm->Draw("");
BackgroundTotal1mm->SaveAs("Background Contamination v Incident Energy - 1mm.gif");

Signal1mm->cd();
TH1F *SignalHist1mm = new TH1F("SignalHist1mm", "SignalHist1mm", nbins, 0, 190);

t31mm.Draw("Incident_Energy>>+SignalHist1mm", "Layer_1 > -0.625*Layer_2 + 5 && Layer_2 > -0.67*Layer_3 + 6 && Layer_3 > -0.375*Layer_4 + 6 && Layer_4 > -0.26*Layer_5 + 9 && Layer_1 + Layer_2 > -0.83*Layer_3 + 10 && Layer_1 + Layer_2 + Layer_3 >  -0.84*Layer_4 + 16 && Layer_1 + Layer_2 + Layer_3 + Layer_4 > -0.33*Layer_5 + 20 &&  Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t31mm.Draw("Incident_Energy>>+SignalHist1mm", "Layer_1 < 4.33*Layer_2 - 13 && Layer_3 > 5 && Layer_3 > -0.23*Layer_4 + 7 && Layer_1+Layer_2+Layer_3 > -1.5*Layer_4 + 24 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t31mm.Draw("Incident_Energy>>+SignalHist1mm", "Layer_1 < 5*Layer_2 -20 && Layer_2 >  -0.9375*Layer_3 + 15 && Layer_1+Layer_2 >  -1.07*Layer_3 + 16 &&Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t31mm.Draw("Incident_Energy>>+SignalHist1mm", "Layer_1 > -1.64*Layer_2 + 18 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double signal_count1mm = SignalHist1mm->Integral();
cout << "signal count for 1mm: " << signal_count1mm << endl;
cout << "signal/noise ratio for 1mm: " << signal_count1mm / (photon_background1mm + proton_background1mm) << endl;

SignalHist1mm->GetYaxis()->SetTitle("Deuteron Count");
SignalHist1mm->GetXaxis()->SetTitle("Deuteron Incident Energy [MeV]");
SignalHist1mm->SetTitle("Signal Count against Incident Energy - 1mm");
SignalHist1mm->SetLineColor(kRed);
SignalHist1mm->SetOption("C");

SignalHist1mm->Draw("");
Signal1mm->SaveAs("Signal Count v Incident Energy - 1mm.gif");

TCanvas *SNRatio1mm = new TCanvas("SNRatio1mm", "SNRatio1mm", 100, 10, 1500, 800);
SNRatio1mm->cd();

TH1F *Addition1 = new TH1F("Addition1", "Addition1", nbins, 0, 190);
Addition1->Add(SignalHist1mm, BackgroundHist1mm, 1, 100);

TH1F *SN1mm = new TH1F("SN1mm", "SN1mm", nbins, 0, 190);

SN1mm->Divide(SignalHist1mm, Addition1, 1, 1);

SN1mm->GetYaxis()->SetTitle("S/(S + B)");
SN1mm->GetXaxis()->SetTitle("Incident Energy [MeV]");
SN1mm->SetTitle("Signal/(Signal+Background) against Incident Energy - 1mm");
SN1mm->SetLineColor(kRed);
SN1mm->SetOption("");

SN1mm->Draw("");
SNRatio1mm->SaveAs("Signal-Noise against Incident Energy - 1mm.gif");

//-------------------------------------------------------------------------------------------------------------
//
//Thickness = 2mm
//
//-------------------------------------------------------------------------------------------------------------


TCanvas *Backgrounds2mm = new TCanvas("Backgrounds2mm", "Backgrounds2mm", 100, 10, 1500, 800);
Backgrounds2mm->Divide(2, 2);

TCanvas *BackgroundTotal2mm = new TCanvas("BackgroundTotal2mm", "BackgroundTotal2mm", 100, 10, 1500, 800);

TCanvas *Signal2mm = new TCanvas("Signal2mm", "Signal2mm", 100, 10, 1500, 800);

//First file
//Create a filereader
TFile f12mm("photons-1M-2mm.root");

//Create a Tree filled by the filereader
TTree *t12mm = (TTree*)f12mm.Get("Dibaryon_Modeller");

//Second file
//Create a filereader
TFile f22mm("protons-1M-2mm.root");

//Create a Tree filled by the filereader
TTree *t22mm = (TTree*)f22mm.Get("Dibaryon_Modeller");

//Third File Input
//Create a filereader
TFile f32mm("deuterons-1M-2mm.root");

//Create a Tree filled by the filereader
TTree *t32mm = (TTree*)f32mm.Get("Dibaryon_Modeller");

//This is where I make a histogram to determine the background contamination as a function of the incident energy. 
//I take all the cuts I've made previously for each stopping case, and apply them here.

TH1F *BackgroundL52mm = new TH1F("BackgroundL52mm", "BackgroundL52mm", nbins, 0, 190);
TH1F *BackgroundL42mm = new TH1F("BackgroundL42mm", "BackgroundL42mm", nbins, 0, 190);
TH1F *BackgroundL32mm = new TH1F("BackgroundL32mm", "BackgroundL32mm", nbins, 0, 190);
TH1F *BackgroundL22mm = new TH1F("BackgroundL22mm", "BackgroundL22mm", nbins, 0, 190);

t12mm.Draw("Incident_Energy>>+BackgroundL52mm", "Layer_1 > -Layer_2 + 10 && Layer_2 > -0.67*Layer_3 + 10 && Layer_3 > -0.65*Layer_4 + 13 && Layer_4 > -0.26*Layer_5 + 13 && Layer_1+Layer_2 > -0.75*Layer_3 + 15 && Layer_1+Layer_2+Layer_3 >  -0.81*Layer_4 + 25 && Layer_1+Layer_2+Layer_3+Layer_4 > -0.55*Layer_5 + 33 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t12mm.Draw("Incident_Energy>>+BackgroundL42mm", "Layer_1 < 5*Layer_2 - 30 && Layer_2 > -1.13*Layer_3 + 17 && Layer_3 > -0.43*Layer_4 + 13 && Layer_1+Layer_2+Layer_3 > -0.67*Layer_4 + 30 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t12mm.Draw("Incident_Energy>>+BackgroundL32mm", "Layer_1+Layer_2 >  -0.58*Layer_3 + 23 && Layer_2 >  -0.48*Layer_3 + 15 && Layer_1 > -1.13*Layer_2 + 17 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t12mm.Draw("Incident_Energy>>+BackgroundL22mm", "Layer_1 > -0.5*Layer_2 + 15 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double photon_background2mm = (BackgroundL52mm->Integral() + BackgroundL42mm->Integral() + BackgroundL32mm->Integral() + BackgroundL22mm->Integral())*1000.0;

t22mm.Draw("Incident_Energy>>+BackgroundL52mm", "Layer_1 > -Layer_2 + 10 && Layer_2 > -0.67*Layer_3 + 10 && Layer_3 > -0.65*Layer_4 + 13 && Layer_4 > -0.26*Layer_5 + 13 && Layer_1+Layer_2 > -0.75*Layer_3 + 15 && Layer_1+Layer_2+Layer_3 >  -0.81*Layer_4 + 25 && Layer_1+Layer_2+Layer_3+Layer_4 > -0.55*Layer_5 + 33 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t22mm.Draw("Incident_Energy>>+BackgroundL42mm", "Layer_1 < 5*Layer_2 - 30 && Layer_2 > -1.13*Layer_3 + 17 && Layer_3 > -0.43*Layer_4 + 13 && Layer_1+Layer_2+Layer_3 > -0.67*Layer_4 + 30 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t22mm.Draw("Incident_Energy>>+BackgroundL32mm", "Layer_1+Layer_2 >  -0.58*Layer_3 + 23 && Layer_2 >  -0.48*Layer_3 + 15 && Layer_1 > -1.13*Layer_2 + 17 && Layer_1>0 &&Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t22mm.Draw("Incident_Energy>>+BackgroundL22mm", "Layer_1 > -0.5*Layer_2 + 15 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double proton_background2mm = (BackgroundL52mm->Integral() + BackgroundL42mm->Integral() + BackgroundL32mm->Integral() + BackgroundL22mm->Integral() - (photon_background2mm / 1000))*100.0;

Backgrounds2mm->cd(1);
BackgroundL22mm->Draw("");
Backgrounds2mm->cd(2);
BackgroundL32mm->Draw("");
Backgrounds2mm->cd(3);
BackgroundL42mm->Draw("");
Backgrounds2mm->cd(4);
BackgroundL52mm->Draw("");

cout << "photon count for 2mm: " << photon_background2mm << endl;
cout << "proton count for 2mm: " << proton_background2mm << endl;

BackgroundTotal2mm->cd();

TH1F *BackgroundHist2mm = new TH1F("BackgroundHist2mm", "BackgroundHist2mm", nbins, 0, 190);
t12mm.Draw("Incident_Energy>>+BackgroundHist2mm", "Layer_1 > -Layer_2 + 10 && Layer_2 > -0.67*Layer_3 + 10 && Layer_3 > -0.65*Layer_4 + 13 && Layer_4 > -0.26*Layer_5 + 13 && Layer_1+Layer_2 > -0.75*Layer_3 + 15 && Layer_1+Layer_2+Layer_3 >  -0.81*Layer_4 + 25 && Layer_1+Layer_2+Layer_3+Layer_4 > -0.55*Layer_5 + 33 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t12mm.Draw("Incident_Energy>>+BackgroundHist2mm", "Layer_1 < 5*Layer_2 - 30 && Layer_2 > -1.13*Layer_3 + 17 && Layer_3 > -0.43*Layer_4 + 13 && Layer_1+Layer_2+Layer_3 > -0.67*Layer_4 + 30 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t12mm.Draw("Incident_Energy>>+BackgroundHist2mm", "Layer_1+Layer_2 >  -0.58*Layer_3 + 23 && Layer_2 >  -0.48*Layer_3 + 15 && Layer_1 > -1.13*Layer_2 + 17 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t12mm.Draw("Incident_Energy>>+BackgroundHist2mm", "Layer_1 > -0.5*Layer_2 + 15 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

t22mm.Draw("Incident_Energy>>+BackgroundHist2mm", "Layer_1 > -Layer_2 + 10 && Layer_2 > -0.67*Layer_3 + 10 && Layer_3 > -0.65*Layer_4 + 13 && Layer_4 > -0.26*Layer_5 + 13 && Layer_1+Layer_2 > -0.75*Layer_3 + 15 && Layer_1+Layer_2+Layer_3 >  -0.81*Layer_4 + 25 && Layer_1+Layer_2+Layer_3+Layer_4 > -0.55*Layer_5 + 33 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t22mm.Draw("Incident_Energy>>+BackgroundHist2mm", "Layer_1 < 5*Layer_2 - 30 && Layer_2 > -1.13*Layer_3 + 17 && Layer_3 > -0.43*Layer_4 + 13 && Layer_1+Layer_2+Layer_3 > -0.67*Layer_4 + 30 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t22mm.Draw("Incident_Energy>>+BackgroundHist2mm", "Layer_1+Layer_2 >  -0.58*Layer_3 + 23 && Layer_2 >  -0.48*Layer_3 + 15 && Layer_1 > -1.13*Layer_2 + 17 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t22mm.Draw("Incident_Energy>>+BackgroundHist2mm", "Layer_1 > -0.5*Layer_2 + 15 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");


BackgroundHist2mm->GetYaxis()->SetTitle("Background Count");
BackgroundHist2mm->GetXaxis()->SetTitle("Proton and Photon Incident Energy [MeV]");
BackgroundHist2mm->SetTitle("Background Count against Incident Energy - 2mm");
BackgroundHist2mm->SetLineColor(kGreen);
BackgroundHist2mm->SetOption("C");

BackgroundHist2mm->Draw("");
BackgroundTotal2mm->SaveAs("Background Contamination v Incident Energy-2mm.gif");

Signal2mm->cd();
TH1F *SignalHist2mm = new TH1F("SignalHist2mm", "SignalHist2mm", nbins, 0, 190);

t32mm.Draw("Incident_Energy>>+SignalHist2mm", "Layer_1 > -Layer_2 + 10 && Layer_2 > -0.67*Layer_3 + 10 && Layer_3 > -0.65*Layer_4 + 13 && Layer_4 > -0.26*Layer_5 + 13 && Layer_1+Layer_2 > -0.75*Layer_3 + 15 && Layer_1+Layer_2+Layer_3 >  -0.81*Layer_4 + 25 && Layer_1+Layer_2+Layer_3+Layer_4 > -0.55*Layer_5 + 33 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t32mm.Draw("Incident_Energy>>+SignalHist2mm", "Layer_1 < 5*Layer_2 - 30 && Layer_2 > -1.13*Layer_3 + 17 && Layer_3 > -0.43*Layer_4 + 13 && Layer_1+Layer_2+Layer_3 > -0.67*Layer_4 + 30 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t32mm.Draw("Incident_Energy>>+SignalHist2mm", "Layer_1+Layer_2 >  -0.58*Layer_3 + 23 && Layer_2 >  -0.48*Layer_3 + 15 && Layer_1 > -1.13*Layer_2 + 17 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t32mm.Draw("Incident_Energy>>+SignalHist2mm", "Layer_1 > -0.5*Layer_2 + 15 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double signal_count2mm = SignalHist2mm->Integral();
cout << "signal count for 2mm: " << signal_count2mm << endl;
cout << "signal/noise ratio for 2mm: " << signal_count2mm / (photon_background2mm + proton_background2mm) << endl;

SignalHist2mm->GetYaxis()->SetTitle("Deuteron Count");
SignalHist2mm->GetXaxis()->SetTitle("Deuteron Incident Energy [MeV]");
SignalHist2mm->SetTitle("Signal Count against Incident Energy - 2mm");
SignalHist2mm->SetLineColor(kGreen);
SignalHist2mm->SetOption("C");

SignalHist2mm->Draw("");
Signal2mm->SaveAs("Signal Count v Incident Energy - 2mm.gif");

TCanvas *SNRatio2mm = new TCanvas("SNRatio2mm", "SNRatio2mm", 100, 10, 1500, 800);
SNRatio2mm->cd();

TH1F *Addition2 = new TH1F("Addition2", "Addition2", nbins, 0, 190);
Addition2->Add(SignalHist2mm, BackgroundHist2mm, 1, 100);

TH1F *SN2mm = new TH1F("SN2mm", "SN2mm", nbins, 0, 190);

SN2mm->Divide(SignalHist2mm, Addition2, 1, 1);

SN2mm->GetYaxis()->SetTitle("S/(S + B)");
SN2mm->GetXaxis()->SetTitle("Incident Energy [MeV]");
SN2mm->SetTitle("Signal/(Signal+Background) against Incident Energy - 2mm");
SN2mm->SetLineColor(kGreen);
SN2mm->SetOption("");

SN2mm->Draw("");
SNRatio2mm->SaveAs("Signal-Noise against Incident Energy - 2mm.gif");

//-------------------------------------------------------------------------------------------------------------
//
//Thickness = 3mm
//
//-------------------------------------------------------------------------------------------------------------

TCanvas *Backgrounds3mm = new TCanvas("Backgrounds3mm", "Backgrounds3mm", 100, 10, 1500, 800);
Backgrounds3mm->Divide(2, 2);

TCanvas *BackgroundTotal3mm = new TCanvas("BackgroundTotal3mm", "BackgroundTotal3mm", 100, 10, 1500, 800);

TCanvas *Signal3mm = new TCanvas("Signal3mm", "Signal3mm", 100, 10, 1500, 800);

//First file
//Create a filereader
TFile f13mm("photons-1M-3mm.root");

//Create a Tree filled by the filereader
TTree *t13mm = (TTree*)f13mm.Get("Dibaryon_Modeller");

//Second file
//Create a filereader
TFile f23mm("protons-1M-3mm.root");

//Create a Tree filled by the filereader
TTree *t23mm = (TTree*)f23mm.Get("Dibaryon_Modeller");

//Third File Input
//Create a filereader
TFile f33mm("deuterons-1M-3mm.root");

//Create a Tree filled by the filereader
TTree *t33mm = (TTree*)f33mm.Get("Dibaryon_Modeller");

//This is where I make a histogram to determine the background contamination as a function of the incident energy. 
//I take all the cuts I've made previously for each stopping case, and apply them here.

TH1F *BackgroundL53mm = new TH1F("BackgroundL53mm", "BackgroundL53mm", nbins, 0, 190);
TH1F *BackgroundL43mm = new TH1F("BackgroundL43mm", "BackgroundL43mm", nbins, 0, 190);
TH1F *BackgroundL33mm = new TH1F("BackgroundL33mm", "BackgroundL33mm", nbins, 0, 190);
TH1F *BackgroundL23mm = new TH1F("BackgroundL23mm", "BackgroundL23mm", nbins, 0, 190);

t13mm.Draw("Incident_Energy>>+BackgroundL53mm", "Layer_1+Layer_2+Layer_3+Layer_4 > -0.64*Layer_5 + 45 && Layer_1+Layer_2+Layer_3 >  -0.6*Layer_4 + 30 && Layer_1+Layer_2 > -1.25*Layer_3 + 25 && Layer_4 > -0.28*Layer_5 + 17 && Layer_3 > -0.5*Layer_4 + 15 && Layer_2 > -0.9375*Layer_3 + 15 && Layer_1 > -2*Layer_2 + 20 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t13mm.Draw("Incident_Energy>>+BackgroundL43mm", "Layer_2 > 8 && Layer_2 > -1.875*Layer_3 + 30 && Layer_3 > -0.45*Layer_4 + 18 && Layer_1+Layer_2+Layer_3 > -0.77*Layer_4 + 40 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t13mm.Draw("Incident_Energy>>+BackgroundL33mm", "Layer_1 > -2.86*Layer_2 + 40 && Layer_2 >  -0.42*Layer_3 + 19 && Layer_1+Layer_2 >  -0.57*Layer_3 + 30 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t13mm.Draw("Incident_Energy>>+BackgroundL23mm", "Layer_1 > -0.46*Layer_2 + 20 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double photon_background3mm = (BackgroundL53mm->Integral() + BackgroundL43mm->Integral() + BackgroundL33mm->Integral() + BackgroundL23mm->Integral())*1000.0;

t23mm.Draw("Incident_Energy>>+BackgroundL53mm", "Layer_1+Layer_2+Layer_3+Layer_4 > -0.64*Layer_5 + 45 && Layer_1+Layer_2+Layer_3 >  -0.6*Layer_4 + 30 && Layer_1+Layer_2 > -1.25*Layer_3 + 25 && Layer_4 > -0.28*Layer_5 + 17 && Layer_3 > -0.5*Layer_4 + 15 && Layer_2 > -0.9375*Layer_3 + 15 && Layer_1 > -2*Layer_2 + 20 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t23mm.Draw("Incident_Energy>>+BackgroundL43mm", "Layer_2 > 8 && Layer_2 > -1.875*Layer_3 + 30 && Layer_3 > -0.45*Layer_4 + 18 && Layer_1+Layer_2+Layer_3 > -0.77*Layer_4 + 40 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t23mm.Draw("Incident_Energy>>+BackgroundL33mm", "Layer_1 > -2.86*Layer_2 + 40 && Layer_2 >  -0.42*Layer_3 + 19 && Layer_1+Layer_2 >  -0.57*Layer_3 + 30 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t23mm.Draw("Incident_Energy>>+BackgroundL23mm", "Layer_1 > -0.46*Layer_2 + 20 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double proton_background3mm = (BackgroundL53mm->Integral() + BackgroundL43mm->Integral() + BackgroundL33mm->Integral() + BackgroundL23mm->Integral() - (photon_background3mm / 1000))*100.0;

Backgrounds3mm->cd(1);
BackgroundL23mm->Draw("");
Backgrounds3mm->cd(2);
BackgroundL33mm->Draw("");
Backgrounds3mm->cd(3);
BackgroundL43mm->Draw("");
Backgrounds3mm->cd(4);
BackgroundL53mm->Draw("");

cout << "photon count for 3mm: " << photon_background3mm << endl;
cout << "proton count for 3mm: " << proton_background3mm << endl;

BackgroundTotal3mm->cd();

TH1F *BackgroundHist3mm = new TH1F("BackgroundHist3mm", "BackgroundHist3mm", nbins, 0, 190);
t13mm.Draw("Incident_Energy>>+BackgroundHist3mm", "Layer_1+Layer_2+Layer_3+Layer_4 > -0.64*Layer_5 + 45 && Layer_1+Layer_2+Layer_3 >  -0.6*Layer_4 + 30 && Layer_1+Layer_2 > -1.25*Layer_3 + 25 && Layer_4 > -0.28*Layer_5 + 17 && Layer_3 > -0.5*Layer_4 + 15 && Layer_2 > -0.9375*Layer_3 + 15 && Layer_1 > -2*Layer_2 + 20 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t13mm.Draw("Incident_Energy>>+BackgroundHist3mm", "Layer_2 > 8 && Layer_2 > -1.875*Layer_3 + 30 && Layer_3 > -0.45*Layer_4 + 18 && Layer_1+Layer_2+Layer_3 > -0.77*Layer_4 + 40 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t13mm.Draw("Incident_Energy>>+BackgroundHist3mm", "Layer_1 > -2.86*Layer_2 + 40 && Layer_2 >  -0.42*Layer_3 + 19 && Layer_1+Layer_2 >  -0.57*Layer_3 + 30 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t13mm.Draw("Incident_Energy>>+BackgroundHist3mm", "Layer_1 > -0.46*Layer_2 + 20 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

t23mm.Draw("Incident_Energy>>+BackgroundHist3mm", "Layer_1+Layer_2+Layer_3+Layer_4 > -0.64*Layer_5 + 45 && Layer_1+Layer_2+Layer_3 >  -0.6*Layer_4 + 30 && Layer_1+Layer_2 > -1.25*Layer_3 + 25 && Layer_4 > -0.28*Layer_5 + 17 && Layer_3 > -0.5*Layer_4 + 15 && Layer_2 > -0.9375*Layer_3 + 15 && Layer_1 > -2*Layer_2 + 20 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t23mm.Draw("Incident_Energy>>+BackgroundHist3mm", "Layer_2 > 8 && Layer_2 > -1.875*Layer_3 + 30 && Layer_3 > -0.45*Layer_4 + 18 && Layer_1+Layer_2+Layer_3 > -0.77*Layer_4 + 40 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t23mm.Draw("Incident_Energy>>+BackgroundHist3mm", "Layer_1 > -2.86*Layer_2 + 40 && Layer_2 >  -0.42*Layer_3 + 19 && Layer_1+Layer_2 >  -0.57*Layer_3 + 30 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t23mm.Draw("Incident_Energy>>+BackgroundHist3mm", "Layer_1 > -0.46*Layer_2 + 20 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");


BackgroundHist3mm->GetYaxis()->SetTitle("Background Count");
BackgroundHist3mm->GetXaxis()->SetTitle("Proton and Photon Incident Energy [MeV]");
BackgroundHist3mm->SetTitle("Background Count against Incident Energy - 3mm");
BackgroundHist3mm->SetLineColor(kBlue);
BackgroundHist3mm->SetOption("C");

BackgroundHist3mm->Draw("");
BackgroundTotal3mm->SaveAs("Background Contamination v Incident Energy - 3mm.gif");

Signal3mm->cd();
TH1F *SignalHist3mm = new TH1F("SignalHist3mm", "SignalHist3mm", nbins, 0, 190);

t33mm.Draw("Incident_Energy>>+SignalHist3mm", "Layer_1+Layer_2+Layer_3+Layer_4 > -0.64*Layer_5 + 45 && Layer_1+Layer_2+Layer_3 >  -0.6*Layer_4 + 30 && Layer_1+Layer_2 > -1.25*Layer_3 + 25 && Layer_4 > -0.28*Layer_5 + 17 && Layer_3 > -0.5*Layer_4 + 15 && Layer_2 > -0.9375*Layer_3 + 15 && Layer_1 > -2*Layer_2 + 20 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t33mm.Draw("Incident_Energy>>+SignalHist3mm", "Layer_2 > 8 && Layer_2 > -1.875*Layer_3 + 30 && Layer_3 > -0.45*Layer_4 + 18 && Layer_1+Layer_2+Layer_3 > -0.77*Layer_4 + 40 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t33mm.Draw("Incident_Energy>>+SignalHist3mm", "Layer_1 > -2.86*Layer_2 + 40 && Layer_2 >  -0.42*Layer_3 + 19 && Layer_1+Layer_2 >  -0.57*Layer_3 + 30 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t33mm.Draw("Incident_Energy>>+SignalHist3mm", "Layer_1 > -0.46*Layer_2 + 20 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double signal_count3mm = SignalHist3mm->Integral();
cout << "signal count for 3mm: " << signal_count3mm << endl;
cout << "signal/noise ratio for 3mm: " << signal_count3mm / (photon_background3mm + proton_background3mm) << endl;

SignalHist3mm->GetYaxis()->SetTitle("Deuteron Count");
SignalHist3mm->GetXaxis()->SetTitle("Deuteron Incident Energy [MeV]");
SignalHist3mm->SetTitle("Signal Count against Incident Energy");
SignalHist3mm->SetLineColor(kBlue);
SignalHist3mm->SetOption("C");

SignalHist3mm->Draw("");
Signal3mm->SaveAs("Signal Count v Incident Energy - 3mm.gif");

TCanvas *SNRatio3mm = new TCanvas("SNRatio3mm", "SNRatio3mm", 100, 10, 1500, 800);
SNRatio3mm->cd();

TH1F *Addition3 = new TH1F("Addition3", "Addition3", nbins, 0, 190);
Addition3->Add(SignalHist3mm, BackgroundHist3mm, 1, 100);

TH1F *SN3mm = new TH1F("SN3mm", "SN3mm", nbins, 0, 190);

SN3mm->Divide(SignalHist3mm, Addition3, 1, 1);

SN3mm->GetYaxis()->SetTitle("S/(S + B)");
SN3mm->GetXaxis()->SetTitle("Incident Energy [MeV]");
SN3mm->SetTitle("Signal/(Signal+Background) against Incident Energy - 3mm");
SN3mm->SetLineColor(kBlue);
SN3mm->SetOption("");

SN3mm->Draw("");
SNRatio3mm->SaveAs("Signal-Noise against Incident Energy - 3mm.gif");
//-------------------------------------------------------------------------------------------------------------
//
//Thickness = 4mm
//
//-------------------------------------------------------------------------------------------------------------


TCanvas *Backgrounds4mm = new TCanvas("Backgrounds4mm", "Backgrounds4mm", 100, 10, 1500, 800);
Backgrounds4mm->Divide(2, 2);

TCanvas *BackgroundTotal4mm = new TCanvas("BackgroundTotal4mm", "BackgroundTotal4mm", 100, 10, 1500, 800);

TCanvas *Signal4mm = new TCanvas("Signal4mm", "Signal4mm", 100, 10, 1500, 800);

//First file
//Create a filereader
TFile f14mm("photons-1M-4mm.root");

//Create a Tree filled by the filereader
TTree *t14mm = (TTree*)f14mm.Get("Dibaryon_Modeller");

//Second file
//Create a filereader
TFile f24mm("protons-1M-4mm.root");

//Create a Tree filled by the filereader
TTree *t24mm = (TTree*)f24mm.Get("Dibaryon_Modeller");

//Third File Input
//Create a filereader
TFile f34mm("deuterons-1M-4mm.root");

//Create a Tree filled by the filereader
TTree *t34mm = (TTree*)f34mm.Get("Dibaryon_Modeller");

//This is where I make a histogram to determine the background contamination as a function of the incident energy. 
//I take all the cuts I've made previously for each stopping case, and apply them here.

TH1F *BackgroundL54mm = new TH1F("BackgroundL54mm", "BackgroundL54mm", nbins, 0, 190);
TH1F *BackgroundL44mm = new TH1F("BackgroundL44mm", "BackgroundL44mm", nbins, 0, 190);
TH1F *BackgroundL34mm = new TH1F("BackgroundL34mm", "BackgroundL34mm", nbins, 0, 190);
TH1F *BackgroundL24mm = new TH1F("BackgroundL24mm", "BackgroundL24mm", nbins, 0, 190);

t14mm.Draw("Incident_Energy>>+BackgroundL54mm", "Layer_1 > -0.5*Layer_2 + 10 && Layer_2 > -0.44*Layer_3 + 11 && Layer_3 > -0.8*Layer_4 + 16 && Layer_4 > -0.4*Layer_5 + 20 && Layer_1+Layer_2 > -1.24*Layer_3 + 26 && Layer_1+Layer_2+Layer_3 > -2.05*Layer_4 + 45  && Layer_1+Layer_2+Layer_3+Layer_4 > -Layer_5 + 50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t14mm.Draw("Incident_Energy>>+BackgroundL44mm", "Layer_1 > -1.053*Layer_2 + 20 && Layer_2 > -0.8*Layer_3 + 20 && Layer_3 > -0.47*Layer_4 + 22 && Layer_1+Layer_2+Layer_3 > -0.61*Layer_4 + 46 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t14mm.Draw("Incident_Energy>>+BackgroundL34mm", "Layer_1 > -0.375*Layer_2 + 15 && Layer_2 >  -0.48*Layer_3 + 24 && Layer_1+Layer_2 >  -0.6*Layer_3 + 36 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t14mm.Draw("Incident_Energy>>+BackgroundL24mm", "Layer_1 > -0.5*Layer_2 + 25 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double photon_background4mm = (BackgroundL54mm->Integral() + BackgroundL44mm->Integral() + BackgroundL34mm->Integral() + BackgroundL24mm->Integral())*1000.0;

t24mm.Draw("Incident_Energy>>+BackgroundL54mm", "Layer_1 > -0.5*Layer_2 + 10 && Layer_2 > -0.44*Layer_3 + 11 && Layer_3 > -0.8*Layer_4 + 16 && Layer_4 > -0.4*Layer_5 + 20 && Layer_1+Layer_2 > -1.24*Layer_3 + 26 && Layer_1+Layer_2+Layer_3 > -2.05*Layer_4 + 45  && Layer_1+Layer_2+Layer_3+Layer_4 > -Layer_5 + 50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t24mm.Draw("Incident_Energy>>+BackgroundL44mm", "Layer_1 > -1.053*Layer_2 + 20 && Layer_2 > -0.8*Layer_3 + 20 && Layer_3 > -0.47*Layer_4 + 22 && Layer_1+Layer_2+Layer_3 > -0.61*Layer_4 + 46 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t24mm.Draw("Incident_Energy>>+BackgroundL34mm", "Layer_1 > -0.375*Layer_2 + 15 && Layer_2 >  -0.48*Layer_3 + 24 && Layer_1+Layer_2 >  -0.6*Layer_3 + 36 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t24mm.Draw("Incident_Energy>>+BackgroundL24mm", "Layer_1 > -0.5*Layer_2 + 25 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double proton_background4mm = (BackgroundL54mm->Integral() + BackgroundL44mm->Integral() + BackgroundL34mm->Integral() + BackgroundL24mm->Integral() - (photon_background4mm / 1000))*100.0;

Backgrounds4mm->cd(1);
BackgroundL24mm->Draw("");
Backgrounds4mm->cd(2);
BackgroundL34mm->Draw("");
Backgrounds4mm->cd(3);
BackgroundL44mm->Draw("");
Backgrounds4mm->cd(4);
BackgroundL54mm->Draw("");

cout << "photon count for 4mm: " << photon_background4mm << endl;
cout << "proton count for 4mm: " << proton_background4mm << endl;

BackgroundTotal4mm->cd();

TH1F *BackgroundHist4mm = new TH1F("BackgroundHist4mm", "BackgroundHist4mm", nbins, 0, 190);
t14mm.Draw("Incident_Energy>>+BackgroundHist4mm", "Layer_1 > -0.5*Layer_2 + 10 && Layer_2 > -0.44*Layer_3 + 11 && Layer_3 > -0.8*Layer_4 + 16 && Layer_4 > -0.4*Layer_5 + 20 && Layer_1+Layer_2 > -1.24*Layer_3 + 26 && Layer_1+Layer_2+Layer_3 > -2.05*Layer_4 + 45  && Layer_1+Layer_2+Layer_3+Layer_4 > -Layer_5 + 50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t14mm.Draw("Incident_Energy>>+BackgroundHist4mm", "Layer_1 > -1.053*Layer_2 + 20 && Layer_2 > -0.8*Layer_3 + 20 && Layer_3 > -0.47*Layer_4 + 22 && Layer_1+Layer_2+Layer_3 > -0.61*Layer_4 + 46 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t14mm.Draw("Incident_Energy>>+BackgroundHist4mm", "Layer_1 > -0.375*Layer_2 + 15 && Layer_2 >  -0.48*Layer_3 + 24 && Layer_1+Layer_2 >  -0.6*Layer_3 + 36 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t14mm.Draw("Incident_Energy>>+BackgroundHist4mm", "Layer_1 > -0.5*Layer_2 + 25 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

t24mm.Draw("Incident_Energy>>+BackgroundHist4mm", "Layer_1 > -0.5*Layer_2 + 10 && Layer_2 > -0.44*Layer_3 + 11 && Layer_3 > -0.8*Layer_4 + 16 && Layer_4 > -0.4*Layer_5 + 20 && Layer_1+Layer_2 > -1.24*Layer_3 + 26 && Layer_1+Layer_2+Layer_3 > -2.05*Layer_4 + 45  && Layer_1+Layer_2+Layer_3+Layer_4 > -Layer_5 + 50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t24mm.Draw("Incident_Energy>>+BackgroundHist4mm", "Layer_1 > -1.053*Layer_2 + 20 && Layer_2 > -0.8*Layer_3 + 20 && Layer_3 > -0.47*Layer_4 + 22 && Layer_1+Layer_2+Layer_3 > -0.61*Layer_4 + 46 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t24mm.Draw("Incident_Energy>>+BackgroundHist4mm", "Layer_1 > -0.375*Layer_2 + 15 && Layer_2 >  -0.48*Layer_3 + 24 && Layer_1+Layer_2 >  -0.6*Layer_3 + 36 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t24mm.Draw("Incident_Energy>>+BackgroundHist4mm", "Layer_1 > -0.5*Layer_2 + 25 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");


BackgroundHist4mm->GetYaxis()->SetTitle("Background Count");
BackgroundHist4mm->GetXaxis()->SetTitle("Proton and Photon Incident Energy [MeV]");
BackgroundHist4mm->SetTitle("Background Count against Incident Energy - 4mm");
BackgroundHist4mm->SetLineColor(kMagenta);
BackgroundHist4mm->SetOption("C");

BackgroundHist4mm->Draw("");
BackgroundTotal4mm->SaveAs("Background Contamination v Incident Energy - 4mm.gif");

Signal4mm->cd();
TH1F *SignalHist4mm = new TH1F("SignalHist4mm", "SignalHist4mm", nbins, 0, 190);

t34mm.Draw("Incident_Energy>>+SignalHist4mm", "Layer_1 > -0.5*Layer_2 + 10 && Layer_2 > -0.44*Layer_3 + 11 && Layer_3 > -0.8*Layer_4 + 16 && Layer_4 > -0.4*Layer_5 + 20 && Layer_1+Layer_2 > -1.24*Layer_3 + 26 && Layer_1+Layer_2+Layer_3 > -2.05*Layer_4 + 45  && Layer_1+Layer_2+Layer_3+Layer_4 > -Layer_5 + 50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4 > 0 && (Layer_5>0)");
t34mm.Draw("Incident_Energy>>+SignalHist4mm", "Layer_1 > -1.053*Layer_2 + 20 && Layer_2 > -0.8*Layer_3 + 20 && Layer_3 > -0.47*Layer_4 + 22 && Layer_1+Layer_2+Layer_3 > -0.61*Layer_4 + 46 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");
t34mm.Draw("Incident_Energy>>+SignalHist4mm", "Layer_1 > -0.375*Layer_2 + 15 && Layer_2 >  -0.48*Layer_3 + 24 && Layer_1+Layer_2 >  -0.6*Layer_3 + 36 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");
t34mm.Draw("Incident_Energy>>+SignalHist4mm", "Layer_1 > -0.5*Layer_2 + 25 && Layer_1 > 0 && Layer_2 > 0 && Layer_3 == 0 && Layer_4 == 0 && Layer_5 == 0");

double signal_count4mm = SignalHist4mm->Integral();
cout << "signal count for 4mm: " << signal_count4mm << endl;
cout << "signal/noise ratio for 4mm: " << signal_count4mm / (photon_background4mm + proton_background4mm) << endl;
SignalHist4mm->GetYaxis()->SetTitle("Deuteron Count");
SignalHist4mm->GetXaxis()->SetTitle("Deuteron Incident Energy [MeV]");
SignalHist4mm->SetTitle("Signal Count against Incident Energy - 4mm");
SignalHist4mm->SetLineColor(kMagenta);
SignalHist4mm->SetOption("C");

SignalHist4mm->Draw("");
Signal4mm->SaveAs("Signal Count v Incident Energy - 4mm.gif");

TCanvas *SNRatio4mm = new TCanvas("SNRatio4mm", "SNRatio4mm", 100, 10, 1500, 800);
SNRatio4mm->cd();

TH1F *Addition = new TH1F("Addition", "Addition", nbins, 0, 190);
Addition->Add(SignalHist4mm, BackgroundHist4mm, 1, 100);

TH1F *SN4mm = new TH1F("SN4mm", "SN4mm", nbins, 0, 190);

SN4mm->Divide(SignalHist4mm, Addition, 1, 1);

SN4mm->GetYaxis()->SetTitle("S/(S + B)");
SN4mm->GetXaxis()->SetTitle("Incident Energy [MeV]");
SN4mm->SetTitle("Signal/(Signal+Background) against Incident Energy - 4mm");
SN4mm->SetLineColor(kMagenta);
SN4mm->SetOption("");

SN4mm->Draw("");
SNRatio4mm->SaveAs("Signal-Noise against Incident Energy - 4mm.gif");

//---------------------------------------------------------------------------------------------------------------
//
//
//Combining the background, signals plots for each thickness into 1 plot. 
//
//
//---------------------------------------------------------------------------------------------------------------
TCanvas *CombinedBack = new TCanvas("CombinedBack", "CombinedBack", 100, 10, 1500, 800);

CombinedBack->cd();

BackgroundHist1mm->GetYaxis()->SetTitle("Background Count");
BackgroundHist1mm->GetXaxis()->SetTitle("Proton and Photon Incident Energy [MeV]");
BackgroundHist1mm->SetTitle("Background Count against Incident Energy");
BackgroundHist1mm->GetXaxis()->SetLimits(19, 65);

BackgroundHist1mm->Scale(100);
BackgroundHist2mm->Scale(75);
BackgroundHist3mm->Scale(50);
BackgroundHist4mm->Scale(25);

BackgroundHist1mm->Draw("");
BackgroundHist2mm->Draw("C same");
BackgroundHist3mm->Draw("C same");
BackgroundHist4mm->Draw("C same");

BackgroundLegend = new TLegend(0.8, 0.7, 0.9, 0.85);
BackgroundLegend->SetTextSize(0.03);
BackgroundLegend->SetBorderSize(0);
BackgroundLegend->AddEntry(BackgroundHist1mm, "1mm");
BackgroundLegend->AddEntry(BackgroundHist2mm, "2mm");
BackgroundLegend->AddEntry(BackgroundHist3mm, "3mm");
BackgroundLegend->AddEntry(BackgroundHist4mm, "4mm");

BackgroundLegend->Draw();

CombinedBack->SaveAs("Combined Backgrounds.gif");

TCanvas *CombinedSig = new TCanvas("CombinedSig", "CombinedSig", 100, 10, 1500, 800);

CombinedSig->cd();

SignalHist1mm->GetYaxis()->SetTitle("Background Count");
SignalHist1mm->GetXaxis()->SetTitle("Deuteron Incident Energy [MeV]");
SignalHist1mm->SetTitle("Signal Count against Incident Energy");
SignalHist1mm->GetXaxis()->SetLimits(25, 90);

SignalHist1mm->Scale(1);
SignalHist2mm->Scale(0.8);
SignalHist3mm->Scale(0.6);
SignalHist4mm->Scale(0.4);

SignalHist1mm->Draw("");
SignalHist2mm->Draw("C same");
SignalHist3mm->Draw("C same");
SignalHist4mm->Draw("C same");

SignalLegend = new TLegend(0.8, 0.7, 0.9, 0.85);
SignalLegend->SetTextSize(0.03);
SignalLegend->SetBorderSize(0);
SignalLegend->AddEntry(SignalHist1mm, "1mm");
SignalLegend->AddEntry(SignalHist2mm, "2mm");
SignalLegend->AddEntry(SignalHist3mm, "3mm ");
SignalLegend->AddEntry(SignalHist4mm, "4mm");
SignalLegend->Draw();

CombinedSig->SaveAs("Combined Signals.gif");

TCanvas *CombinedSNR = new TCanvas("CombinedSNR", "CombinedSNR", 100, 10, 1500, 800);

CombinedSNR->cd();

SN4mm->GetYaxis()->SetTitle("Signal/(Background+Signal)");
SN4mm->GetXaxis()->SetTitle("Incident Energy [MeV]");
SN4mm->SetTitle("Signal/(Background+Signal) against Incident Energy");
SN4mm->GetXaxis()->SetLimits(0, 190);
SN4mm->GetYaxis()->SetLimits(0, 10);

//SN1mm->Scale(1);
//SN2mm->Scale(1);
//SN3mm->Scale(1);
//SN4mm->Scale(1);

SN4mm->Draw("");
//SN2mm->Draw("C same");
//SN1mm->Draw("C same");
//SN4mm->Draw("C same");
//
//SNLegend = new TLegend(0.8, 0.7, 0.9, 0.85);
//SNLegend->SetTextSize(0.03);
//SNLegend->SetBorderSize(0);
//SNLegend->AddEntry(SN1mm, "1mm");
//SNLegend->AddEntry(SN2mm, "2mm");
//SNLegend->AddEntry(SN3mm, "3mm ");
//SNLegend->AddEntry(SN4mm, "4mm");
//SNLegend->Draw();

CombinedSNR->SaveAs("Combined SN Ratios.gif");

}