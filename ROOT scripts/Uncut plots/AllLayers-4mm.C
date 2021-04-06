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

TCanvas *Layer1 = new TCanvas("Layer1", "Layer1", 100, 10, 1500, 800);

TCanvas *Layer2 = new TCanvas("Layer2", "Layer2", 100, 10, 1500, 800);

//Create a canvas divided into 2 - This canvas deals with Layer 2 : Layer x
TCanvas *Layer3 = new TCanvas("Layer3", "Layer3", 100, 10, 1500, 800);
Layer3->Divide(2, 2);

TCanvas *Layer4 = new TCanvas("Layer4", "Layer4", 100, 10, 1500, 800);
Layer4->Divide(2, 2);

//Create a canvas divided into 2 - This canvas deals with Layer 3 : Layer x
TCanvas *Layer5 = new TCanvas("Layer5", "Layer5", 100, 10, 1500, 800);
Layer5->Divide(2, 2);

//Create a canvas divided into 2 - This canvas deals with Layer 3 : Layer x
TCanvas *Combos = new TCanvas("Combos", "Combos", 100, 10, 1500, 800);
Combos->Divide(2, 2);

TCanvas *Nostop = new TCanvas("Nostop", "Nostop", 100, 10, 1500, 800);
Nostop->Divide(2, 2);

TCanvas *NostopCombo = new TCanvas("NostopCombo", "NostopCombo", 100, 10, 1500, 800);
NostopCombo->Divide(2);

TCanvas *ReportPlots = new TCanvas("ReportPlots", "ReportPlots", 100, 10, 1500, 800);

//First file

//Create a filereader
TFile f1("photons-1M-4mm.root");

//Create a Tree filled by the filereader
TTree *t1 = (TTree*)f1.Get("Dibaryon_Modeller");

//Create the 2d histograms
Layer1->cd();

TH2F *h0a = new TH2F("h0a", "Layer_0:Layer_1", 100, 0, 50, 100, 0, 50);
h0a->SetMarkerColor(kRed);
t1.Draw("Layer_0:Layer_1>>h0a", "Layer_0>0 && Layer_1 <50 && Layer_2<50 && Layer_1>0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0");

Layer2->cd();
Layer2->cd(1);

//Layer 1 v x
TH2F *h1a = new TH2F("h1a", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h1a->SetMarkerColor(kRed);
t1.Draw("Layer_1:Layer_2>>h1a", "Layer_1 <50 && Layer_2<50 && Layer_1 >0 && Layer_2>0 && Layer_3==0 && Layer_4==0 && Layer_5==0");

Layer3->cd();
Layer3->cd(1);

//Layer 1 v 2
TH2F *h2a = new TH2F("h2a", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h2a->SetMarkerColor(kRed);
t1.Draw("Layer_1:Layer_2>>h2a", "Layer_1 <50 && Layer_2<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");

//Create the 2d histograms
Layer3->cd();
Layer3->cd(2);

TH2F *h3a = new TH2F("h3a", "Layer_1+Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h3a->SetMarkerColor(kRed);
t1.Draw("Layer_1+Layer_2:Layer_3>>h3a", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0 ");

Layer3->cd();
Layer3->cd(3);

//Layer 2 v 3
TH2F *h4a = new TH2F("h4a", "Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h4a->SetMarkerColor(kRed);
t1.Draw("Layer_2:Layer_3>>h4a", "Layer_2<50 && Layer_3<50 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");

Layer4->cd();
Layer4->cd(1);

//Layer 1 v x
TH2F *h5a = new TH2F("h5a", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h5a->SetMarkerColor(kRed);
t1.Draw("Layer_1:Layer_2>>h5a", "Layer_1 <50 && Layer_2<50 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");

Layer4->cd(2);

//Layer 2 v x
TH2F *h6a = new TH2F("h6a", "Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h6a->SetMarkerColor(kRed);
t1.Draw("Layer_2:Layer_3>>h6a", "Layer_2<50 && Layer_3<50 && Layer_2>0 && Layer_3>0 && Layer_1>0 && Layer_4>0 && Layer_5==0");

Layer4->cd(3);

TH2F *h7a = new TH2F("h7a", "Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h7a->SetMarkerColor(kRed);
t1.Draw("Layer_3:Layer_4>>h7a", " Layer_3<50 && Layer_4<50 && Layer_4<50 &&Layer_3>0 && Layer_4>0 && Layer_1>0 && Layer_2>0 && Layer_5==0");

Layer4->cd(4);

TH2F *h8a = new TH2F("h8a", "Layer_1+Layer_2+Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h8a->SetMarkerColor(kRed);
t1.Draw("Layer_1+Layer_2+Layer_3:Layer_4>>h8a", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_4<50 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");

Layer5->cd();
Layer5->cd(1);

//Layer 1 v x
TH2F *h9a = new TH2F("h9a", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h9a->SetMarkerColor(kRed);
t1.Draw("Layer_1:Layer_2>>h9a", "Layer_1 <50 && Layer_2<50 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Layer5->cd(2);

//Layer 2 v x
TH2F *h10a = new TH2F("h10a", "Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h10a->SetMarkerColor(kRed);
t1.Draw("Layer_2:Layer_3>>h10a", "Layer_2<50 && Layer_3<50 && Layer_2>0 && Layer_3>0 && Layer_1>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Layer5->cd(3);

TH2F *h11a = new TH2F("h11a", "Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h11a->SetMarkerColor(kRed);
t1.Draw("Layer_3:Layer_4>>h11a", " Layer_3<50 && Layer_4<50 && Layer_4<50 &&Layer_3>0 && Layer_4>0 && Layer_1>0 && Layer_2>0 && Layer_5>0 && Layer_6==0");


Layer5->cd(4);

//Layer 4 v x
TH2F *h12a = new TH2F("h12a", "Layer_4:Layer_5", 100, 0, 50, 100, 0, 50);
h12a->SetMarkerColor(kRed);
t1.Draw("Layer_4:Layer_5>>h12a", "Layer_4<50 && Layer_5<50 && Layer_4>0 && Layer_5>0 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Combos->cd(1);

TH2F *h13a = new TH2F("h13a", "Layer_1+Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h13a->SetMarkerColor(kRed);
t1.Draw("Layer_1+Layer_2:Layer_3>>h13a", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0 ");

Combos->cd(2);

TH2F *h14a = new TH2F("h14a", "Layer_1+Layer_2+Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h14a->SetMarkerColor(kRed);
t1.Draw("Layer_1+Layer_2+Layer_3:Layer_4>>h14a", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_4<50 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Combos->cd(3);

TH2F *h15a = new TH2F("h15a", "Layer_1:Layer_2+Layer_3+Layer_4+Layer_5", 100, 0, 50, 100, 0, 50);
h15a->SetMarkerColor(kRed);
t1.Draw("Layer_1+Layer_2+Layer_3+Layer_4:Layer_5>>h15a", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_4<50 && Layer_5<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Nostop->cd();
Nostop->cd(1);

//Layer 1 v x
TH2F *h16a = new TH2F("h16a", "Layer_6:Layer_7", 100, 0, 50, 100, 0, 50);
h16a->SetMarkerColor(kRed);
t1.Draw("Layer_6:Layer_7>>h16a", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

Nostop->cd(2);

//Layer 2 v x
TH2F *h17a = new TH2F("h17a", "Layer_7:Layer_8", 100, 0, 50, 100, 0, 50);
h17a->SetMarkerColor(kRed);
t1.Draw("Layer_7:Layer_8>>h17a", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

Nostop->cd(3);

TH2F *h18a = new TH2F("h18a", "Layer_8:Layer_9", 100, 0, 50, 100, 0, 50);
h18a->SetMarkerColor(kRed);
t1.Draw("Layer_8:Layer_9>>h18a", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

NostopCombo->cd(1);

TH2F *h19a = new TH2F("h19a", "Layer_6+Layer_7:Layer_8", 100, 0, 50, 100, 0, 50);
h19a->SetMarkerColor(kRed);
t1.Draw("Layer_6+Layer_7:Layer_8>>h19a", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

NostopCombo->cd(2);

TH2F *h20a = new TH2F("h20a", "Layer_6+Layer_7+Layer_8:Layer_9", 100, 0, 50, 100, 0, 50);
h20a->SetMarkerColor(kRed);
t1.Draw("Layer_6+Layer_7+Layer_8:Layer_9>>h20a", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0 ");


//Second file

//Create a filereader
TFile f2("protons-1M-4mm.root");

//Create a Tree filled by the filereader
TTree *t2 = (TTree*)f2.Get("Dibaryon_Modeller");

Layer1->cd();

TH2F *h0b = new TH2F("h0b", "Layer_0:Layer_1", 100, 0, 50, 100, 0, 50);
h0b->SetMarkerColor(kBlue);
t2.Draw("Layer_0:Layer_1>>h0b", "Layer_0>0 && Layer_1 <50 && Layer_1>0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0");

Layer2->cd();
Layer2->cd(1);

//Create the 2d histograms
TH2F *h1b = new TH2F("h1b", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h1b->SetMarkerColor(kBlue);
t2.Draw("Layer_1:Layer_2>>h1b", "Layer_1<50 && Layer_2<50 &&  Layer_1 >0 && Layer_2>0 && Layer_3==0 && Layer_4==0 && Layer_5==0 ");

Layer3->cd();
Layer3->cd(1);

//Create the 2d histograms
TH2F *h2b = new TH2F("h2b", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h2b->SetMarkerColor(kBlue);
t2.Draw("Layer_1:Layer_2>>h2b", "Layer_1<50 && Layer_2<50 &&  Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0 ");

Layer3->cd();
Layer3->cd(2);

TH2F *h3b = new TH2F("h3b", "Layer_1+Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h3b->SetMarkerColor(kBlue);
t2.Draw("Layer_1+Layer_2:Layer_3>>h3b", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");

Layer3->cd();
Layer3->cd(3);

//Layer 2 v 3
TH2F *h4b = new TH2F("h4b", "Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h4b->SetMarkerColor(kBlue);
t2.Draw("Layer_2:Layer_3>>h4b", "Layer_2<50 && Layer_3<50 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");

Layer4->cd();
Layer4->cd(1);

//Create the 2d histograms
TH2F *h5b = new TH2F("h5b", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h5b->SetMarkerColor(kBlue);
t2.Draw("Layer_1:Layer_2>>h5b", "Layer_1<50 && Layer_2<50 &&  Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0 ");

Layer4->cd(2);

//Layer 2 v x
TH2F *h6b = new TH2F("h6b", "Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h6b->SetMarkerColor(kBlue);
t2.Draw("Layer_2:Layer_3>>h6b", "Layer_2<50 && Layer_3<50 && Layer_2>0 && Layer_3>0 && Layer_1>0 && Layer_4>0 && Layer_5==0");

Layer4->cd(3);

//Layer 3 v x
TH2F *h7b = new TH2F("h7b", "Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h7b->SetMarkerColor(kBlue);
t2.Draw("Layer_3:Layer_4>>h7b", "Layer_3<50 && Layer_4<50&& Layer_3>0 && Layer_4>0 && Layer_1>0 && Layer_2>0 && Layer_5==0");

Layer4->cd(4);

TH2F *h8b = new TH2F("h8b", "Layer_1+Layer_2+Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h8b->SetMarkerColor(kBlue);
t2.Draw("Layer_1+Layer_2+Layer_3:Layer_4>>h8b", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_4<50 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");

Layer5->cd();
Layer5->cd(1);

//Create the 2d histograms
TH2F *h9b = new TH2F("h9b", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h9b->SetMarkerColor(kBlue);
t2.Draw("Layer_1:Layer_2>>h9b", "Layer_1<50 && Layer_2<50 &&  Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0 ");

Layer5->cd(2);

//Layer 2 v x
TH2F *h10b = new TH2F("h10b", "Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h10b->SetMarkerColor(kBlue);
t2.Draw("Layer_2:Layer_3>>h10b", "Layer_2<50 && Layer_3<50 && Layer_2>0 && Layer_3>0 && Layer_1>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Layer5->cd(3);

//Layer 3 v x
TH2F *h11b = new TH2F("h11b", "Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h11b->SetMarkerColor(kBlue);
t2.Draw("Layer_3:Layer_4>>h11b", "Layer_3<50 && Layer_4<50&& Layer_3>0 && Layer_4>0 && Layer_1>0 && Layer_2>0 && Layer_5>0 && Layer_6==0");

Layer5->cd(4);

//Layer 4 v x
TH2F *h12b = new TH2F("h12b", "Layer_4:Layer_5", 100, 0, 50, 100, 0, 50);
h12b->SetMarkerColor(kBlue);
t2.Draw("Layer_4:Layer_5>>h12b", "Layer_4<50 && Layer_5<50 && Layer_4>0 && Layer_5>0 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Combos->cd(1);

TH2F *h13b = new TH2F("h13b", "Layer_1+Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h13b->SetMarkerColor(kBlue);
t2.Draw("Layer_1+Layer_2:Layer_3>>h13b", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Combos->cd(2);

TH2F *h14b = new TH2F("h14b", "Layer_1+Layer_2+Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h14b->SetMarkerColor(kBlue);
t2.Draw("Layer_1+Layer_2+Layer_3:Layer_4>>h14b", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_4<50 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Combos->cd(3);

TH2F *h15b = new TH2F("h15b", "Layer_1+Layer_2+Layer_3+Layer_4:Layer_5", 100, 0, 50, 100, 0, 50);
h15b->SetMarkerColor(kBlue);
t2.Draw("Layer_1+Layer_2+Layer_3+Layer_4:Layer_5>>h15b", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_4<50 && Layer_5<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Nostop->cd();
Nostop->cd(1);

//Layer 1 v x
TH2F *h16b = new TH2F("h16b", "Layer_6:Layer_7", 100, 0, 50, 100, 0, 50);
h16b->SetMarkerColor(kBlue);
t2.Draw("Layer_6:Layer_7>>h16b", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

Nostop->cd(2);

//Layer 2 v x
TH2F *h17b = new TH2F("h17b", "Layer_7:Layer_8", 100, 0, 50, 100, 0, 50);
h17b->SetMarkerColor(kBlue);
t2.Draw("Layer_7:Layer_8>>h17b", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

Nostop->cd(3);

TH2F *h18b = new TH2F("h18b", "Layer_8:Layer_9", 100, 0, 50, 100, 0, 50);
h18b->SetMarkerColor(kBlue);
t2.Draw("Layer_8:Layer_9>>h18b", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

NostopCombo->cd(1);

TH2F *h19b = new TH2F("h19b", "Layer_6+Layer_7:Layer_8", 100, 0, 50, 100, 0, 50);
h19b->SetMarkerColor(kBlue);
t2.Draw("Layer_6+Layer_7:Layer_8>>h19b", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

NostopCombo->cd(2);

TH2F *h20b= new TH2F("h20b", "Layer_6+Layer_7+Layer_8:Layer_9", 100, 0, 50, 100, 0, 50);
h20b->SetMarkerColor(kBlue);
t2.Draw("Layer_6+Layer_7+Layer_8:Layer_9>>h20b", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

//Third File Input

//Create a filereader
TFile f3("deuterons-1M-4mm.root");

//Create a Tree filled by the filereader
TTree *t3 = (TTree*)f3.Get("Dibaryon_Modeller");

Layer1->cd();

TH2F *h0c = new TH2F("h0c", "Layer_0:Layer_1", 100, 0, 50, 100, 0, 50);
h0c->SetMarkerColor(kGreen);
t3.Draw("Layer_0:Layer_1>>h0c", "Layer_0>0 && Layer_1 <50 && Layer_1>0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0");

Layer2->cd();
Layer2->cd(1);

//Create the 2d histograms
TH2F *h1c = new TH2F("h1c", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h1c->SetMarkerColor(kGreen);
t3.Draw("Layer_1:Layer_2>>h1c", "Layer_1<50 && Layer_2<50 && Layer_1 >0 && Layer_2>0 && Layer_3==0 && Layer_4==0 && Layer_5==0 ");

Layer3->cd();
Layer3->cd(1);

//Create the 2d histograms
TH2F *h2c = new TH2F("h2c", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h2c->SetMarkerColor(kGreen);
t3.Draw("Layer_1:Layer_2>>h2c", "Layer_1<50 && Layer_2<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0 ");

Layer3->cd();
Layer3->cd(2);

TH2F *h3c = new TH2F("h3c", "Layer_1+Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h3c->SetMarkerColor(kGreen);
t3.Draw("Layer_1+Layer_2:Layer_3>>h3c", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");

Layer3->cd();
Layer3->cd(3);

//Layer 2 v 3
TH2F *h4c = new TH2F("h4c", "Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h4c->SetMarkerColor(kGreen);
t3.Draw("Layer_2:Layer_3>>h4c", "Layer_2<50 && Layer_3<50 && Layer_2>0 && Layer_3>0 && Layer_4==0 && Layer_5==0");

Layer4->cd();
Layer4->cd(1);

//Create the 2d histograms
TH2F *h5c = new TH2F("h5c", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h5c->SetMarkerColor(kGreen);
t3.Draw("Layer_1:Layer_2>>h5c", "Layer_1<50 && Layer_2<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0 ");

Layer4->cd(2);

//Layer 2 v x
TH2F *h6c = new TH2F("h6c", "Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h6c->SetMarkerColor(kGreen);
t3.Draw("Layer_2:Layer_3>>h6c", "Layer_2<50 && Layer_3<50 && Layer_2>0 && Layer_3>0 && Layer_1>0 && Layer_4>0 && Layer_5==0");

Layer4->cd(3);

//Layer 3 v x
TH2F *h7c = new TH2F("h7c", "Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h7c->SetMarkerColor(kGreen);
t3.Draw("Layer_3:Layer_4>>h7c", " Layer_3<50 && Layer_4<50 && Layer_3>0 && Layer_4>0 && Layer_1>0 && Layer_2>0 && Layer_5==0");

Layer4->cd(4);

TH2F *h8c = new TH2F("h8c", "Layer_1+Layer_2+Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h8c->SetMarkerColor(kGreen);
t3.Draw("Layer_1+Layer_2+Layer_3:Layer_4>>h8c", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_4<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5==0");

Layer5->cd();
Layer5->cd(1);

//Create the 2d histograms
TH2F *h9c = new TH2F("h9c", "Layer_1:Layer_2", 100, 0, 50, 100, 0, 50);
h9c->SetMarkerColor(kGreen);
t3.Draw("Layer_1:Layer_2>>h9c", "Layer_1<50 && Layer_2<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Layer5->cd(2);

//Layer 2 v x
TH2F *h10c = new TH2F("h10c", "Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h10c->SetMarkerColor(kGreen);
t3.Draw("Layer_2:Layer_3>>h10c", "Layer_2<50 && Layer_3<50 && Layer_2>0 && Layer_3>0 && Layer_1>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Layer5->cd(3);

//Layer 3 v x
TH2F *h11c = new TH2F("h11c", "Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h11c->SetMarkerColor(kGreen);
t3.Draw("Layer_3:Layer_4>>h11c", " Layer_3<50 && Layer_4<50 && Layer_3>0 && Layer_4>0 && Layer_1>0 && Layer_2>0 && Layer_5>0 && Layer_6==0");

Layer5->cd(4);

//Layer 4 v x
TH2F *h12c = new TH2F("h12c", "Layer_4:Layer_5", 100, 0, 50, 100, 0, 50);
h12c->SetMarkerColor(kGreen);
t3.Draw("Layer_4:Layer_5>>h12c", "Layer_4<50 && Layer_5<50 && Layer_4>0 && Layer_5>0 && Layer_1>0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Combos->cd(1);

TH2F *h13c = new TH2F("h13c", "Layer_1+Layer_2:Layer_3", 100, 0, 50, 100, 0, 50);
h13c->SetMarkerColor(kGreen);
t3.Draw("Layer_1+Layer_2:Layer_3>>h13c", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Combos->cd(2);

TH2F *h14c = new TH2F("h14c", "Layer_1+Layer_2+Layer_3:Layer_4", 100, 0, 50, 100, 0, 50);
h14c->SetMarkerColor(kGreen);
t3.Draw("Layer_1+Layer_2+Layer_3:Layer_4>>h14c", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_4<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Combos->cd(3);

TH2F *h15c = new TH2F("h15c", "Layer_1+Layer_2+Layer_3+Layer_4:Layer_5", 100, 0, 50, 100, 0, 50);
h15c->SetMarkerColor(kGreen);
t3.Draw("Layer_1+Layer_2+Layer_3+Layer_4:Layer_5>>h15c", "Layer_1<50 && Layer_2<50 && Layer_3<50 && Layer_4<50 && Layer_5<50 && Layer_1 >0 && Layer_2>0 && Layer_3>0 && Layer_4>0 && Layer_5>0 && Layer_6==0");

Nostop->cd();
Nostop->cd(1);

//Layer 1 v x
TH2F *h16c = new TH2F("h16c", "Layer_6:Layer_7", 100, 0, 50, 100, 0, 50);
h16c->SetMarkerColor(kGreen);
t3.Draw("Layer_6:Layer_7>>h16c", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

Nostop->cd(2);

//Layer 2 v x
TH2F *h17c = new TH2F("h17c", "Layer_7:Layer_8", 100, 0, 50, 100, 0, 50);
h17c->SetMarkerColor(kGreen);
t3.Draw("Layer_7:Layer_8>>h17c", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

Nostop->cd(3);

TH2F *h18c = new TH2F("h18c", "Layer_8:Layer_9", 100, 0, 50, 100, 0, 50);
h18c->SetMarkerColor(kGreen);
t3.Draw("Layer_8:Layer_9>>h18c", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");


NostopCombo->cd(1);

TH2F *h19c = new TH2F("h19c", "Layer_6+Layer_7:Layer_8", 100, 0, 50, 100, 0, 50);
h19c->SetMarkerColor(kGreen);
t3.Draw("Layer_6+Layer_7:Layer_8>>h19c", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

NostopCombo->cd(2);

TH2F *h20c = new TH2F("h20c", "Layer_6+Layer_7+Layer_8:Layer_9", 100, 0, 50, 100, 0, 50);
h20c->SetMarkerColor(kGreen);
t3.Draw("Layer_6+Layer_7+Layer_8:Layer_9>>h20c", "Layer_1==0 && Layer_2==0 && Layer_3==0 && Layer_4==0 && Layer_5==0 && Layer_6>0 && Layer_7>0 && Layer_8>0 && Layer_9>0");

Layer1->cd();
Layer1->cd(1);

h0a->GetYaxis()->SetTitle("Layer_0");
h0a->GetXaxis()->SetTitle("Layer_1");
h0a->SetTitle("Energy Deposited Layer_0:Layer_1");

h0a->Draw("");
h0b->Draw("same");
h0c->Draw("same");

Layer2->cd();
Layer2->cd(1);

h1a->GetYaxis()->SetTitle("Layer_1");
h1a->GetXaxis()->SetTitle("Layer_2");
h1a->SetTitle("Energy Deposited Layer_1:Layer_2");

h1a->Draw("");
h1b->Draw("same");
h1c->Draw("same");

Layer2->SaveAs("StopsL2.gif");

Layer3->cd();
Layer3->cd(1);

h2a->GetYaxis()->SetTitle("E-Dep Layer 1 [MeV]");
h2a->GetXaxis()->SetTitle("E-Dep Layer 2 [MeV]");
h2a->SetTitle("Energy Deposited in Layer 1 against Layer 2");
h2a->GetXaxis()->SetLimits(0, 25);
h2a->GetYaxis()->SetLimits(0, 25);

h2a->Draw("");
h2b->Draw("same");
h2c->Draw("same");

Layer3->cd(2);

h3a->GetYaxis()->SetTitle("E-Dep Layer 1+Layer 2 [MeV]");
h3a->GetXaxis()->SetTitle("E-Dep Layer 3 [MeV]");
h3a->SetTitle("Energy Deposited in Layer 1+Layer 2 against Layer 3");
h3a->GetXaxis()->SetLimits(0, 37);
h3a->GetYaxis()->SetLimits(0, 40);

h3a->Draw("");
h3b->Draw("same");
h3c->Draw("same");

Layer3->cd(3);

h4a->GetYaxis()->SetTitle("E-Dep Layer 2 [MeV]");
h4a->GetXaxis()->SetTitle("E-Dep Layer 3 [MeV]");
h4a->SetTitle("Energy Deposited, Layer 2 against Layer 3");
h4a->GetXaxis()->SetLimits(0, 37);
h4a->GetYaxis()->SetLimits(0, 30);

h4a->Draw("");
h4b->Draw("same");
h4c->Draw("same");

Layer3->SaveAs("StopsL3.gif");

Layer4->cd();
Layer4->cd(1);

h5a->GetYaxis()->SetTitle("Layer_1");
h5a->GetXaxis()->SetTitle("Layer_2");
h5a->SetTitle("Energy Deposited Layer_1:Layer_2");

h5a->Draw("");
h5b->Draw("same");
h5c->Draw("same");

Layer4->cd(2);

h6a->GetYaxis()->SetTitle("Layer_2");
h6a->GetXaxis()->SetTitle("Layer_3");
h6a->SetTitle("Energy Deposited Layer_2:Layer_3");

h6a->Draw("");
h6b->Draw("same");
h6c->Draw("same");

Layer4->cd(3);

h7a->GetYaxis()->SetTitle("Layer_3");
h7a->GetXaxis()->SetTitle("Layer_4");
h7a->SetTitle("Energy Deposited Layer_3:Layer_4");

h7a->Draw("");
h7b->Draw("same");
h7c->Draw("same");

Layer4->cd(4);

h8a->GetYaxis()->SetTitle("Layer_1+Layer_2+Layer_3");
h8a->GetXaxis()->SetTitle("Layer_4");
h8a->SetTitle("Energy Deposited Layer_1+Layer_2+Layer_3:Layer_4");

h8a->Draw("");
h8b->Draw("same");
h8c->Draw("same");

Layer4->SaveAs("StopsL4.gif");

Layer5->cd();
Layer5->cd(1);

h9a->GetYaxis()->SetTitle("Layer_1");
h9a->GetXaxis()->SetTitle("Layer_2");
h9a->SetTitle("Energy Deposited Layer_1:Layer_2");

h9a->Draw("");
h9b->Draw("same");
h9c->Draw("same");

Layer5->cd(2);

h10a->GetYaxis()->SetTitle("Layer_2");
h10a->GetXaxis()->SetTitle("Layer_3");
h10a->SetTitle("Energy Deposited Layer_2:Layer_3");

h10a->Draw("");
h10b->Draw("same");
h10c->Draw("same");

Layer5->cd(3);

h11a->GetYaxis()->SetTitle("Layer_3");
h11a->GetXaxis()->SetTitle("Layer_4");
h11a->SetTitle("Energy Deposited Layer_3:Layer_4");

h11a->Draw("");
h11b->Draw("same");
h11c->Draw("same");

Layer5->cd();
Layer5->cd(4);

h12a->GetYaxis()->SetTitle("Layer_4");
h12a->GetXaxis()->SetTitle("Layer_5");
h12a->SetTitle("Energy Deposited Layer_4:Layer_5");

h12a->Draw("");
h12b->Draw("same");
h12c->Draw("same");

Layer5->SaveAs("StopsL5.gif");

Combos->cd(1);

h13a->GetYaxis()->SetTitle("Layer_1+Layer_2");
h13a->GetXaxis()->SetTitle("Layer_3");
h13a->SetTitle("Energy Deposited Layer_1+Layer_2:Layer_3");

h13a->Draw("");
h13b->Draw("same");
h13c->Draw("same");

Combos->cd(2);

h14a->GetYaxis()->SetTitle("Layer_1+Layer_2+Layer_3");
h14a->GetXaxis()->SetTitle("Layer_4");
h14a->SetTitle("Energy Deposited Layer_1+Layer_2+Layer_3:Layer_4");

h14a->Draw("");
h14b->Draw("same");
h14c->Draw("same");

Combos->cd(3);

h15a->GetYaxis()->SetTitle("Layer_1+Layer_2+Layer_3+Layer_4");
h15a->GetXaxis()->SetTitle("Layer_5");
h15a->SetTitle("Energy Deposited Layer_1+Layer_2+Layer_3+Layer_4:Layer_5");

h15a->Draw("");
h15b->Draw("same");
h15c->Draw("same");

Combos->SaveAs("L5Combos.gif");

Nostop->cd();
Nostop->cd(1);

h16a->GetYaxis()->SetTitle("Layer_6");
h16a->GetXaxis()->SetTitle("Layer_7");
h16a->SetTitle("Energy Deposited Layer_6:Layer_7");

h16a->Draw("");
h16b->Draw("same");
h16c->Draw("same");

Nostop->cd(2);

h17a->GetYaxis()->SetTitle("Layer_7");
h17a->GetXaxis()->SetTitle("Layer_8");
h17a->SetTitle("Energy Deposited Layer_7:Layer_8");

h17a->Draw("");
h17b->Draw("same");
h17c->Draw("same");

Nostop->cd(3);

h18a->GetYaxis()->SetTitle("Layer_8");
h18a->GetXaxis()->SetTitle("Layer_9");
h18a->SetTitle("Energy Deposited Layer_8:Layer_9");

h18a->Draw("");
h18b->Draw("same");
h18c->Draw("same");

Nostop->SaveAs("Nostop.gif");

NostopCombo->cd(1);

h19a->GetYaxis()->SetTitle("Layer_6+Layer_7");
h19a->GetXaxis()->SetTitle("Layer_8");
h19a->SetTitle("Energy Deposited Layer_6+Layer_7:Layer_8");

h19a->Draw("");
h19b->Draw("same");
h19c->Draw("same");

NostopCombo->cd(2);

h20a->GetYaxis()->SetTitle("Layer_6+Layer_7+Layer_8");
h20a->GetXaxis()->SetTitle("Layer_9");
h20a->SetTitle("Energy Deposited Layer_6+Layer_7+Layer_8:Layer_9");

h20a->Draw("");
h20b->Draw("same");
h20c->Draw("same");

NostopCombo->SaveAs("NostopCombos.gif");

ReportPlots->cd();
h4a->GetYaxis()->SetTitle("E-Dep Layer 2 [MeV]");
h4a->GetXaxis()->SetTitle("E-Dep Layer 3 [MeV]");
h4a->SetTitle("Energy Deposited, Layer 2 against Layer 3");
h4a->GetXaxis()->SetLimits(0, 37);
h4a->GetYaxis()->SetLimits(0, 30);

h4a->Draw("");
h4b->Draw("same");
h4c->Draw("same");
}