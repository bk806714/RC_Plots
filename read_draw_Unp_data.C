int get_number_oflines(ifstream file_input);

// This
void compare_born(Int_t Q=0)
{
  cout<<"Enter 1 for JLAB FILE 6GeV "<<endl;

  cout<<"Enter 8 for JLAB FILE 12 GeV "<<endl;

  cout<<"Enter 15 for JLAB FILE 24 GeV "<<endl;

  cout<<"Enter 3 for EIC Q=3 FILE "<<endl;
  cout<<"Enter 10 for EIC Q=10 FILE "<<endl;
  cout<<"Enter 25 For Sivers at Q=5 "<<endl;
  cout<<"Enter 10 For Sivers at Q=10 "<<endl;
  cin>>Q;
  string lab;
 if(Q==3 || Q==10 || Q==5)
   {
     lab="EIC";
   }
 else lab="JLab";
  gStyle->SetTitleYSize(0.065);
  gStyle->SetTitleYOffset(0.9); 
  gStyle->SetLabelSize(0.045,"Y");
  gStyle->SetLabelFont(62,"Y");
  gStyle->SetLabelOffset(0.010,"Y");
  TGraph *gunpB, *gbornD;
 
  string file_nameB,file_nameD, file_name_noROT;
  int QSiv;
  string path_B,path_D;
  int total_lines;
  double yrange_max,yrange_min;
  double plot_Q,plot_qT,plot_pt,plot_z;
  yrange_min=1.0;
  path_B= "/w/halla-scshelf2102/solid/bishnu/RC_plots/pol_Bishnu";
  path_D= "/w/halla-scshelf2102/solid/bishnu/RC_plots/pol_Duane";
  if(Q==1)// This is JLAB 6 GEV kinematics
    {
      file_nameB=Form("%s/Unp_JLAB1_const_alpha.txt",path_B.c_str());
      file_nameD=Form("%s/Unp_JLAB1_Rot_QED.txt",path_D.c_str());
      file_name_noROT=Form("%s/Unp_Q%d_JLAB_const_alpha_QED_noROT.txt",path_B.c_str(),Q);
     
      total_lines=33;
      yrange_max=1.20;
      yrange_min=0.90;
      plot_Q=1.52;
      plot_z=0.55;
    }


  else if(Q==8)// This is JLAB 12 GEV kinematics
    {
      file_nameB=Form("%s/Unp_JLAB2_const_alpha.txt",path_B.c_str());
      file_nameD=Form("%s/Unp_JLAB2_Rot_QED.txt",path_D.c_str());
      file_name_noROT=Form("%s/Unp_Q%d_JLAB_const_alpha_QED_noROT.txt",path_B.c_str(),Q);
      total_lines=40;
      yrange_max=1.20;
      plot_Q=2.83;
      plot_z=0.375;
    }


  else if(Q==15)// This is JLAB 24 GEV kinematics
    {
      file_nameB=Form("%s/Unp_JLAB3_const_alpha.txt",path_B.c_str());
      file_nameD=Form("%s/Unp_JLAB3_Rot_QED.txt",path_D.c_str());
      file_name_noROT=Form("%s/Unp_Q%d_JLAB_const_alpha_QED_noROT.txt",path_B.c_str(),Q);
      total_lines=39;
      yrange_max=1.20;
      plot_Q=3.87;
      plot_z=0.375;
    }


  else if (Q==3)
    {
      file_nameB=Form("%s/Unp_EIC1_const_alpha.txt",path_B.c_str());
      file_nameD=Form("%s/Unp_EIC1_Rot_QED.txt",path_D.c_str());
      file_name_noROT=Form("%s/Unp_Q%d_rs140_const_alpha_QED_noROT.txt",path_B.c_str(),Q);
      total_lines=40;
      yrange_max=1.20;
      plot_Q=3;
      plot_z=0.5;
    }


  else if (Q==5)
    {
      file_nameB=Form("%s/Unp_EIC3_const_alpha.txt",path_B.c_str());
      file_nameD=Form("%s/Unp_EIC3_Rot_QED.txt",path_D.c_str());
      file_name_noROT=Form("%s/Unp_Q%d_rs140_const_alpha_QED_noROT.txt",path_B.c_str(),Q);
      total_lines=33;
      yrange_max=1.20;
      plot_Q=5;
      plot_z=0.5;
    }


    

  else if (Q==10)
    {
      file_nameB=Form("%s/Unp_EIC2_const_alpha.txt",path_B.c_str());
      file_nameD=Form("%s/Unp_EIC2_Rot_QED.txt",path_D.c_str());
      file_name_noROT=Form("%s/Unp_Q%d_rs140_const_alpha_QED_noROT.txt",path_B.c_str(),Q);
      total_lines=49;
      yrange_max=1.20;
      plot_Q=10;
      plot_z=0.5;

    }
  else cout<<"Check you file "<<endl;
  const int num_tot=100;
  ifstream file_RCB, file_RCD,file_noROT;
  file_RCB.open(file_nameB);
  file_RCD.open(file_nameD);
  file_noROT.open(file_name_noROT);
  if(!file_RCB) 
    {
      cout<<"There is not Factorized file "<<endl;
      exit(-1);
    }
  if( !file_RCD   )
    {
cout<<"Check your Traditional RC  input file "<<endl;
      exit(-1);
    }

 string titlelineTraditional;
 getline(file_RCD,titlelineTraditional);
 cout<<titlelineTraditional<<endl;
 TGraph *gborn= new TGraph();
 TGraph *gRC= new TGraph();
 TGraph *gRCB= new TGraph();
 TGraph *gRCD= new TGraph();
 TGraph *gRC_noROT= new TGraph();

 Double_t qT_QB,sigma_noRCB,sigma_RCB,Esigma_noRCB, qT_QBF;
 Double_t qT_Q_noROT,sigma_noRC_noROT,sigma_RC_noROT,Esigma_noRC_noROT,RC_noROT;
 Double_t RCB,E_RCB, born;

 Double_t qT_QD,sigma_noRCD,sigma_RCD,Esigma_noRCD,qT_QDF;
 Double_t RCD,E_RCD;
 Double_t  Actual_RC_B,Actual_RC_D, RC_ratio;
  //int line_B= get_number_oflines(file_RCB);
  // int line_D= get_number_oflines(file_RCD);
  int j=0;
  //cout<<"   "<<line_B<<"     "<<line_B<<endl;
  
  for(int i=0;i<total_lines;i++)
    {
      file_RCB>> qT_QBF >> sigma_noRCB >>   sigma_RCB >> Esigma_noRCB;
      file_RCD>> qT_QDF >> sigma_noRCD >>   sigma_RCD >> Esigma_noRCD;
      
      //plot_qT=qT_QB*plot_Q;
      //plot_pt=plot_qT*plot_z;

      qT_QB=qT_QBF*plot_Q*plot_z;
      qT_QD=qT_QDF*plot_Q*plot_z;
      
      born=sigma_noRCB/sigma_noRCD;

      Actual_RC_B=sigma_noRCB/sigma_RCB;
      Actual_RC_D=sigma_noRCD/sigma_RCD;
      RC_ratio=Actual_RC_B/Actual_RC_D;
      cout<<qT_QB<< "    "<<sigma_noRCB<<"  RC ratio "<<RC_ratio <<" "<<qT_QB/qT_QD<<endl;
      // cout<<i<<"     "<<qT_QDF<<"   "<<qT_QBF<<endl;
      //  cout<<i<<"     "<<qT_QD<<"   "<<born<<"  rc ration  "<<RC_ratio<<endl;
      //  gborn->SetPoint(i,qT_QB,RC);

      // This is the ratio of Born cross-section
      gborn->SetPoint(i,qT_QB,born);

      // This si the ratio of RC from two approach
      gRC->SetPoint(i,qT_QB,RC_ratio);

      // These are the RC's from each of the approach
      gRCD->SetPoint(i,qT_QD, Actual_RC_D);
      gRCB->SetPoint(i,qT_QB, Actual_RC_B);


    }
  /*
  if(!file_noROT)cout<<"File without rotation is absent"<<endl;
  else
    {
      cout<<"Found file and now reading it"<<endl;
      while(file_noROT>> qT_Q_noROT>>sigma_noRC_noROT>>sigma_RC_noROT>>Esigma_noRC_noROT)
	{
	  RC_noROT=sigma_noRC_noROT/sigma_RC_noROT;
	  // cout<<j<<"    "<<RC_noROT<<"       "<<sigma_RC_noROT<<endl;
	   gRC_noROT->SetPoint(j,qT_Q_noROT,RC_noROT);
	  j++;
	}
    }

  */
  TCanvas *c1 = new TCanvas("born","born", 10,10,700,500);
  
  //c1->SetGrid();
  gborn->SetMarkerStyle(20);
  gborn->GetYaxis()->SetRangeUser(0.98,1.02);
  gborn->GetXaxis()->SetRangeUser(0.,1.9);
  gborn->SetMarkerColor(1);
  gRC->SetMarkerColor(4);
  gRC->SetMarkerStyle(22);
  gborn->SetLineColor(4);
  gborn->SetLineWidth(3);
  gborn->Draw("AL");
  gborn->GetYaxis()->SetNdivisions(-204); 
  gborn->GetXaxis()->SetNdivisions(-407); 
  gborn->GetXaxis()->SetMaxDigits(2);
  // gborn->GetXaxis()->SetTitle("q_{T}/Q");
  gborn->GetXaxis()->SetTitle("P_{hT} (GeV/c)");
  // gborn->GetYaxis()->SetTitle("#frac{#sigma_{B_{1}}}{#sigma_{B_{2}}}");
  //gborn->GetYaxis()->SetTitle("#sigma_{B_{1}}/#sigma_{B_{2}}");
  gborn->GetYaxis()->SetTitle("R_{Born}");
  //gborn->GetYaxis()->SetTitle("frac{d#sigma_{Born}}{d#sigma_{}}");
  c1->Print(Form("./plots/Unp_%s%d_born_ratio.pdf",lab.c_str(),Q));
  //gborn->GetYaxis()->SetRangeUser(1.0,1.05);



  TCanvas *c = new TCanvas("RC","RC",10,10,700,500);
  // c->SetGrid();
  gRC->SetMarkerStyle(20);
  gRC->GetYaxis()->SetRangeUser(yrange_min,yrange_max);
  gRC->GetXaxis()->SetRangeUser(0,1.5);
  gRC->SetMarkerColor(1);
  gRC->SetLineColor(4);
  gRC->SetMarkerColor(4);
  gRC->SetMarkerStyle(22);
  gRC->GetYaxis()->SetNdivisions(-405); 
  gRC->GetYaxis()->SetMaxDigits(2);

  gRC->GetXaxis()->SetNdivisions(-407); 
  gRC->GetXaxis()->SetMaxDigits(2);
  gRC->SetLineWidth(4);
  gRC->Draw("AP");
  //gRC->GetXaxis()->SetTitle("q_{T}/Q");
  gRC->GetXaxis()->SetTitle("P_{hT} (GeV/c)");
  //gRC->GetYaxis()->SetTitle("#frac{#sigma_{B_{1}}}{#sigma_{B_{2}}}");
  gRC->GetYaxis()->SetTitle("RC_{F}/RC_{T}");
  c->Print(Form("./plots/Unp_%s%d_RC_ratio.pdf",lab.c_str(),Q));

  TCanvas *crc = new TCanvas("RC_","RC_");
  crc->SetGrid();
 
  gRCB->Draw("AL");
  gRCB->GetXaxis()->SetRangeUser(0,1.60);
  gRCB->SetLineWidth(3);
  //gRCB->GetYaxis()->SetTitle("#frac{d#sigma_{Born}{2};//{d#sigma_{RC}}");
  gRCB->GetYaxis()->SetTitle("#frac{d#sigma_{Born}}{d#sigma_{RC}}");
  gRCB->GetXaxis()->SetNdivisions(-407); 
  gRCB->GetXaxis()->SetMaxDigits(2);
  // gRCB->GetXaxis()->SetTitle("q_{T}/Q");
  gRCB->GetXaxis()->SetTitle("P_{hT} (GeV/c)");
  gRCB->GetYaxis()->SetRangeUser(0.4,2.0);
  gRCB->SetLineColor(2);

  gRCD->Draw("LSAME");
  gRCD->SetLineWidth(3);
  gRCD->SetLineColor(4);
  
  // gRC_noROT->Draw("LSAME");
  // gRC_noROT->SetLineWidth(3);
  // gRC_noROT->SetLineColor(1);
  // gRC_noROT->SetLineColor(1);

  TLegend *legend=new TLegend(0.59,0.65,0.95,0.89);// from(x1,y1) to (x2,y2)
  legend->SetTextFont(72);
  legend->SetTextSize(0.04);
  legend->AddEntry(gRCD,"Traditional","l");
  // legend->AddEntry(gRC_noROT,"Factorized ","l");
  legend->AddEntry(gRCB,"Factorized ","l");


  // legend->AddEntry(signalFcn,"Signal fit","l");                              
  // legend->AddEntry(fitFcn,"Global Fit","l");                                 
  legend->Draw();
crc->Print(Form("./plots/Unp_%s%d_rc.pdf",lab.c_str(),Q));
}
int get_number_oflines(ifstream file_input)
{
  std::string line;
  int tot_lines=0;
 
  while (std::getline(file_input, line))
    ++tot_lines;
  std::cout << "Number of lines in text file: " << tot_lines<<endl;
  return tot_lines;
}

void pol_rc(int Q)
{
 string file_nameB,file_nameD, file_name_noROT;
   string path_B;
  int total_lines;
double scaleB ;
  double scaleD;
  double yrange_max,yrange_min;
  yrange_min=1.0;
  path_B= "/w/halla-scifs17exp/dvcs/disk1/bishnu/ForDuane";
 
  if(Q==1)// This is JLAB 6 GEV kinematics
    {
      file_nameB=Form("%s/Pol_JLab_%d.txt",path_B.c_str(),Q);
      file_nameD=Form("%s/Pol_JLAB1_Rot_QED.txt",path_B.c_str());
      total_lines=33;
      yrange_max=1.20;
      yrange_min=0.90;
    }


  else if(Q==8)// This is JLAB 12 GEV kinematics
    {
file_nameB=Form("%s/Pol_JLAB_%d.txt",path_B.c_str(),Q);
      file_nameD=Form("%s/Pol_JLAB2_Rot_QED.txt",path_B.c_str());
     
      total_lines=33;
      yrange_max=1.20;
scaleB =1e5;
scaleD=1e4;
    }


  else if(Q==15)// This is JLAB 24 GEV kinematics
    {

file_nameB=Form("%s/Pol_JLAB_%d.txt",path_B.c_str(),Q);
      file_nameD=Form("%s/Pol_JLAB1_Rot_QED.txt",path_B.c_str());
      
      total_lines=33;
      yrange_max=1.20;
    }


  else if (Q==3)
    {
      file_nameB=Form("%s/Pol_EIC__%d.txt",path_B.c_str(),Q);
      file_nameD=Form("%s/Pol_EIC1_Rot_QED.txt",path_B.c_str());
     
      total_lines=33;
      yrange_max=1.20;
 scaleB =1e5;
scaleD=1e3;
    }


  else if (Q==5)
    {
      file_nameB=Form("%s/Pol_EIC_%d.txt",path_B.c_str(),Q);
      file_nameD=Form("%s/Pol_EIC3_Rot_QED.txt",path_B.c_str());
      
      total_lines=20;
      yrange_max=1.20;
    }


    

  else if (Q==10)
    {
      file_nameB=Form("%s/Pol_JLab_%d.txt",path_B.c_str(),Q);
      file_nameD=Form("%s/Pol_EIC2_Rot_QED.txt",path_B.c_str());
      total_lines=49;
      yrange_max=1.3;

    }
  else cout<<"Check you file "<<endl;




 ifstream file_RCB, file_RCD,file_noROT;
  file_RCB.open(file_nameB);
  file_RCD.open(file_nameD);


if(!file_RCB) 
    {
      
    }
  if( !file_RCD   )
    {
cout<<"Check your Traditional RC  input file "<<endl;
      exit(-1);
    }


  TGraph *gbornB= new TGraph();
  TGraph *gbornD= new TGraph();
  TGraph *gRC= new TGraph();
  TGraph *gRCB= new TGraph();
  TGraph *gRCD= new TGraph();
 

  Double_t qT_QB,sigma_noRCB,sigma_RCB,Esigma_noRCB;
  Double_t qT_Q_noROT,sigma_noRC_noROT,sigma_RC_noROT,Esigma_noRC_noROT,RC_noROT;
  Double_t RCB,E_RCB, born;

  Double_t qT_QD,sigma_noRCD,sigma_RCD,Esigma_noRCD;
  Double_t RCD,E_RCD;
  Double_t  Actual_RC_B,Actual_RC_D, RC_ratio;
  
  int j=0;
  Double_t bornB,bornD;
  
  for(int i=0;i<total_lines;i++)
    {
      file_RCB>> qT_QB >> sigma_noRCB >>   sigma_RCB >> Esigma_noRCB;
      file_RCD>> qT_QD >> sigma_noRCD >>   sigma_RCD >> Esigma_noRCD;
      
      bornB=sigma_noRCB*scaleB;
      bornD=sigma_noRCD*scaleD;

      //Actual_RC_B=sigma_noRCB/sigma_RCB;
      //Actual_RC_D=sigma_noRCD/sigma_RCD;
       Actual_RC_B=sigma_RCB*scaleB;
       Actual_RC_D=sigma_RCD*scaleD;
      RC_ratio=Actual_RC_B/Actual_RC_D;

       cout<<i<<"     "<<bornD<<"   "<<bornB<<"  rc ration  "<<RC_ratio<<endl;
      //  gborn->SetPoint(i,qT_QB,RC);
      gbornB->SetPoint(i,qT_QB,bornB);
      gbornD->SetPoint(i,qT_QD,bornD);
      gRC->SetPoint(i,qT_QB,RC_ratio);

      gRCD->SetPoint(i,qT_QD, Actual_RC_D);
      gRCB->SetPoint(i,qT_QB, Actual_RC_B);


    }

  TCanvas *c1 = new TCanvas("born","born",10,10,700,500);
  c1->SetGrid();
  gbornD->SetMarkerStyle(20);
  //gbornD->GetYaxis()->SetRangeUser(0.95,1.05);
  // gbornD->GetXaxis()->SetRangeUser(0.,1.0);
  gbornD->SetMarkerColor(1);
  gbornD->SetLineColor(4);
  gbornD->SetLineWidth(3);
  gbornD->Draw("AL");
  gbornD->GetXaxis()->SetTitle("q_{T}/Q");
  // gbornD->GetYaxis()->SetTitle("#frac{#sigma_{B_{1}}}{#sigma_{B_{2}}}");
  gbornD->GetYaxis()->SetTitle("#sigma_{B_{1}}/#sigma_{B_{2}}");
  //gbornD->GetYaxis()->SetTitle("#frac{RC_{F}}{RC_{T}}");


  gbornB->SetMarkerStyle(20);
  gbornB->SetMarkerColor(1);
  gbornB->SetLineColor(2);
  gbornB->SetLineWidth(3);
  gbornB->Draw("LSAME");


  //gbornD->GetYaxis()->SetRangeUser(1.0,1.05);
  TCanvas *c = new TCanvas("RC","RC",10,10,700,500);
  //c->SetGrid();
  gRC->SetMarkerStyle(20);
  gRC->GetYaxis()->SetRangeUser(yrange_min,yrange_max);
  gRC->GetXaxis()->SetRangeUser(0,1.0);
  gRC->SetMarkerColor(1);
  gRC->SetLineColor(4);
  gRC->SetLineWidth(4);
  gRC->Draw("AL");
  gRC->GetXaxis()->SetTitle("q_{T}/Q");
  //gRC->GetYaxis()->SetTitle("#frac{#sigma_{B_{1}}}{#sigma_{B_{2}}}");
  gRC->GetYaxis()->SetTitle("RC_{F}/RC_{T}");


  TCanvas *crc = new TCanvas("RC_","RC_");
  crc->SetGrid();
  gRCB->Draw("AL");
  gRCB->GetXaxis()->SetRangeUser(0,1.0);
  gRCB->SetLineWidth(3);
  gRCB->GetYaxis()->SetTitle("Siv + Col");
  gRCB->GetXaxis()->SetTitle("q_{T}/Q");
  gRCB->GetYaxis()->SetRangeUser(0,0.1);
  gRCB->SetLineColor(2);

  gRCD->Draw("LSAME");
  gRCD->SetLineWidth(3);
  gRCD->SetLineColor(4);


  gbornB->SetLineColor(2);
  gbornB->SetLineWidth(3);
  gbornB->SetLineStyle(2);
  gbornB->Draw("LSAME");

  gbornD->SetLineColor(4);
  gbornD->SetLineWidth(3);
  gbornD->SetLineStyle(2);
  gbornD->Draw("LSAME");

  TLegend *legend=new TLegend(0.5,0.65,0.88,0.85);// from(x1,y1) to (x2,y2)
  legend->SetTextFont(72);
  legend->SetTextSize(0.04);
  legend->AddEntry(gRCD,"Traditional with RC","l");
  legend->AddEntry(gbornD,"Traditional without RC ","l");
  legend->AddEntry(gRCB,"Factorized with RC","l");
  legend->AddEntry(gbornB,"Factorized without RC ","l");
 
  legend->Draw();


 
}
