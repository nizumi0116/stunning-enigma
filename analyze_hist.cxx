
#include <iostream>
#include <vector>
#include "TString.h"

  using namespace std;

  Double_t GetFWHM(TF1* tfunc);
  void GetParameters(TFile* file, int xstart, int xstop, int ystart, int ystop);

//Choose the root file you are going to analyze
  TFile* file1 = new TFile("run_671_analysis_fr.root");

//measurement points along x-axis, y-axis
int xnum=9;
int ynum=8;
int all=72;
  
TCanvas *npeC, *TTSC;
TH1D *chargeHist, *chargeHistX;
TCanvas* npec = new TCanvas("npec","", 500, 500);
TF1 *qfunc, *tfunc;
Int_t xbin, ybin;
Int_t i;
  Double_t Max;
Double_t par4, par4e;
Double_t par0,  par6;
  Double_t mean;
  Double_t meanX;
  Double_t meane;
Double_t xPos, yPos;
Double_t centerx, centery, centerz;
Double_t tts;
  vector<double> MAX;
  vector<double> Maxcut;
vector<double> XPosMax,  YPosMax;
vector<double> XPos, YPos;
  vector<double> Mean;
  vector<double> MeanX;
  vector<double> Ratio;
vector<double> Par0, Par4, Par4e, Par6;
vector<double> nper, npercut;
vector<double> TTS, TTScut;
vector<double> gain, gaincut;

  TGraph2D* TTG;
TH2D *TTcutH, *TTH;
TH2D *par4rH, *par4rcutH;
TH2D *gainH, *gaincutH;
TH2D *TTScutH;
TH1D *par41DH, *par41DHy;

 //*********************************************

//create histograms
void analyze_hist(){
  cout << "Enter center x\n";
  cin >> centerx;
  cout << "Enter center y\n";
  cin >> centery;
  cout << "Enter center z\n";
  cin >> centerz;
 
  cout << "center position: " << centerx << " " << centery << " " << centerz << "\n";

    GetParameters(file1, 90, 170, 0, 70);

    //prepare histograms
    par4rH = new TH2D("", "",  xnum, XPos[0], XPos[0]+90, ynum, YPos[0], YPos[0]+80);
    par4rcutH = new TH2D("", "",  xnum, XPos[0], XPos[0]+90, ynum, YPos[0], YPos[0]+80);
    TTcutH = new TH2D("", "",  xnum, XPos[0], XPos[0]+90, ynum, YPos[0], YPos[0]+80);
    TTScutH = new TH2D("", "",  xnum, XPos[0], XPos[0]+90, ynum, YPos[0], YPos[0]+80);
    gainH = new TH2D("", "",  xnum, XPos[0], XPos[0]+90, ynum, YPos[0], YPos[0]+80);
    gaincutH = new TH2D("", "",  xnum, XPos[0], XPos[0]+90, ynum, YPos[0], YPos[0]+80);
TTH = new TH2D("", "",  xnum, XPos[0], XPos[0]+90, ynum, YPos[0], YPos[0]+80);
  par41DH = new TH1D("", "", xnum, XPos[0], XPos[0]+90);
  par41DHy = new TH1D("", "", ynum, XPos[0], XPos[0]+80);

  //Fill each histogram
    for(int i=0; i<all; i++){
    xbin=par4rH->GetXaxis()->FindBin(XPos[i]+2.5);
    ybin=par4rH->GetYaxis()->FindBin(YPos[i]+2.5);
    par4rH->SetBinContent(xbin, ybin, nper[i]);
    par4rcutH->SetBinContent(xbin, ybin, npercut[i]);
    TTcutH->SetBinContent(xbin, ybin, Maxcut[i]);
    TTH->SetBinContent(xbin, ybin, MAX[i]);
    TTScutH->SetBinContent(xbin, ybin, TTS[i]);
    gainH->SetBinContent(xbin, ybin, gain[i]);
    gaincutH->SetBinContent(xbin, ybin, gaincut[i]);

    if(YPos[i]<5 && YPos[i]>-5){
      par41DH->SetBinContent(xbin, nper[i]);
      par41DH->SetBinError(xbin, Par4e[i]/MeanX[i]);
    }
    if(XPos[i]<3 && YPos[i]>-3){
      par41DHy->SetBinContent(ybin, nper[i]);
      par41DHy->SetBinError(ybin, Par4e[i]/MeanX[i]);
      cout << nper[i] << "\n";
    }
    }

    //Set titles to each histogram
    par4rH->SetTitle("; x-axis [mm]; y-axis [mm]; number of photoelectrons/monitor mean");
    par4rcutH->SetTitle("; x-axis [mm]; y-axis [mm]; number of photoelectrons/monitor mean");
    par41DH->SetTitle("; x-axis [mm]; number of photoelectrons/monitor mean");
    par41DHy->SetTitle("; y-axis [mm]; number of photoelectrons/monitor mean");
    gainH->SetTitle("; x-axis [mm]; y-axis [mm]; gain");
    gaincutH->SetTitle("; x-axis [mm]; y-axis [mm]; gain");
    TTcutH->SetTitle("; x-axis [mm]; y-axis [mm];TT");
    TTH->SetTitle("; x-axis [mm]; y-axis [mm];TT");
    TTScutH->SetTitle("; x-axis [mm]; y-axis [mm];TTS");

    par4rH->SetLabelSize(0.04, "XY");
    par4rcutH->SetLabelSize(0.04, "XY");
    par41DH->SetLabelSize(0.04, "XY");
    par41DHy->SetLabelSize(0.04, "XY");
    TTcutH->SetLabelSize(0.04, "XY");
    TTH->SetLabelSize(0.04, "XY");
    TTScutH->SetLabelSize(0.04, "XY");
    gainH->SetLabelSize(0.04, "XY");
    gaincutH->SetLabelSize(0.04, "XY");
    par4rH->SetTitleSize(0.04, "XY");
    par4rcutH->SetTitleSize(0.04, "XY");
    par41DH->SetTitleSize(0.04, "XY");
    par41DHy->SetTitleSize(0.04, "XY");
    TTcutH->SetTitleSize(0.04, "XY");
    gaincutH->SetTitleSize(0.04, "XY");
TTH->SetTitleSize(0.04, "XY");
     TTScutH->SetTitleSize(0.04, "XY");
     gainH->SetTitleSize(0.04, "XY");
     gaincutH->SetTitleSize(0.04, "XY");
}


 void GetParameters(TFile* file, Int_t xstart, int xstop, int ystart, int ystop){ 
 for(int xpos=xstart; xpos<=xstop; xpos=xpos+10){
   for(int ypos=ystart; ypos<=ystop; ypos=ypos+10){
    npeC = (TCanvas*)file->Get(Form("chargeCanvas_%d_%d;1", xpos, ypos));
    TTSC = (TCanvas*)file->Get(Form("timeCanvas_%d_%d", xpos, ypos));
    chargeHist = (TH1D*)file->Get(Form("chargeHist_ch0_%d_%d", xpos, ypos));
    chargeHistX = (TH1D*)file->Get(Form("chargeHist_ch1_%d_%d", xpos, ypos));
    qfunc = (TF1*)npeC->GetPrimitive("qFunction");
    tfunc = (TF1*)TTSC->GetPrimitive("tFunction");

    par4 = qfunc->GetParameter(4);
    par0 = qfunc->GetParameter(0);
    par6 = qfunc->GetParameter(6);
    par4e = qfunc->GetParError(4);
    mean = chargeHist->GetMean();
    meane = chargeHist->GetMeanError();

    meanX = chargeHistX->GetMean();

    Max = tfunc->GetMaximumX();

    
    if(Max > 0 && par4/meanX >0.3){
      Maxcut.push_back(Max);
      i=i+1;
    }
    
    else{
      Maxcut.push_back(0);
    }
    
    if(Max > 0){
    MAX.push_back(Max);
    XPosMax.push_back(xpos-centerx);
     YPosMax.push_back(ypos-centery);
    }

    if(par4/meanX > 0.3){
      npercut.push_back(par4/meanX);
    }
    else{
      npercut.push_back(0);
    }
    
    
    Mean.push_back(mean);
    MeanX.push_back(meanX);
    Ratio.push_back(mean/meanX);
    nper.push_back(par4/meanX);
    XPos.push_back(xpos-centerx);
    YPos.push_back(ypos-centery);
    Par4.push_back(par4);
    Par4e.push_back(par4e);
    Par0.push_back(par0);
    Par6.push_back(par6);

    if(par4/meanX > 0.3){
    TTS.push_back(GetFWHM(tfunc));
    }
    else{
      TTS.push_back(0);
    }
      
    gain.push_back(par6-par0);

    if(par4/meanX > 0.3 && par6-par0 > 0){
      gaincut.push_back(par6-par0);
    }
    else{
      gaincut.push_back(0);
    }
    
  }
  }


}



Double_t GetFWHM(TF1* tfunc){
return
 tfunc->GetX(tfunc->GetMaximum()*0.5, tfunc->GetMaximumX(), tfunc->GetXaxis()->GetXmax())
 -
  tfunc->GetX(tfunc->GetMaximum()*0.5, tfunc->GetXaxis()->GetXmin(), tfunc->GetMaximumX());
  }
