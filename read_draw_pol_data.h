TGraph *gr_Bi[10];
TGraph *gr_Du[15];
TGraph *gr_F_SC_B;
TGraph *gr_F_SC_R;

double pol_factor;
double y_fac,z_fac,plot_Q;
string graph_title;
double max_range;
string conversion_To_duane;
Int_t num_tot_factorized;
// GIVES POL FACTOR FOR COLLINS 
double Get_pol_factor(double y_term);
void leakage_factorized(string lab,string kine);
// GIVES CORRESPONDING DUANE FILE TO GIVEN BISHNU FILE + Y VAL
void Get_y(string kine); 

// 
void plot_factorized(string lab,string kine);

//READ FILE FROM Duane AND PLOT THE GRAPH
void plot_traditional(string lab,string kine);//,double pol_col);

void Get_title(int num);

void Get_title(int num)
{
  if(num==0)
    {
      graph_title="#int #int sin(^{}#phi_{h} + #phi_{S})d#sigma";
      max_range=1e-6;

    }
  else if (num==1)
    {
      graph_title="#int #int sin(^{}#phi_{h} - #phi_{S})d#sigma ";
      max_range=5e-6;
    }
  else cout<<"Not a good file number "<<endl;
}


void Get_y(std::string kine)
{
  if(strcmp(kine.c_str(),"2")==0)
    {
      y_fac=0.70;
      z_fac=0.55;
      plot_Q=1.52;
      conversion_To_duane="1";
      num_tot_factorized=23;
    }
  else if  (strcmp(kine.c_str(),"8")==0)
    {
      y_fac=0.74; 
      z_fac=0.375;
      plot_Q=2.83;
      conversion_To_duane="2";
      num_tot_factorized=23;

    }
  else if  (strcmp(kine.c_str(),"15")==0)
    {
      y_fac=0.69; 
      z_fac=0.375;
      plot_Q=3.87;
      conversion_To_duane="3";
      num_tot_factorized=23;
    }
  else if  (strcmp(kine.c_str(),"9")==0)
    {
      y_fac=0.4;
      z_fac=0.50;
      plot_Q=3;
      conversion_To_duane="1";
      num_tot_factorized=23;
    } 
  else if  (strcmp(kine.c_str(),"25")==0)
    {
      y_fac=0.127;
      z_fac=0.50; 
      plot_Q=5;
      conversion_To_duane="3";
      num_tot_factorized=19;
    }
  else if  (strcmp(kine.c_str(),"100")==0)
    {
      y_fac=0.4;
      z_fac=0.50;
      plot_Q=10;
      conversion_To_duane="2";
      num_tot_factorized=33;
    }
  else cout<<"Kinematics is wrong "<<endl;

}



double Get_pol_factor(double y_term)

{
  double term1=1-y_term;
  pol_factor=2*term1/(1+ pow(term1,2.0));
  cout<<"   "<<pol_factor<<  "   "<<y_term<<endl;
  return pol_factor;
}
void leakage_factorized(string lab,string kine)
{

 gr_F_SC_B= new TGraph();
 gr_F_SC_R= new TGraph();

 string path_to_file="/w/halla-scshelf2102/solid/bishnu/RC_plots/pol_Bishnu";
 string file_name_sToC;
 file_name_sToC=Form("%s/leakage_S_to_C_%s_%s.txt",path_to_file.c_str(),lab.c_str(),kine.c_str());
 ifstream file_to_read;
 double qT_Q_single,qT_Q_singleF,sigma_noRC_single,sigma_RC_single,Esigma_noRC_single;
 double temp_noRC,temp_RC;
 file_to_read.open(file_name_sToC);
 if(file_to_read)cout<<"Leakage file loaded"<<endl;
 for(int i=0;i<17;i++)
   {
     //   file_to_read >> qT_Q_single >> sigma_noRC_single >>   sigma_RC_single >> Esigma_noRC_single;
     file_to_read >> qT_Q_singleF >> temp_noRC >> temp_RC >> Esigma_noRC_single;
     qT_Q_single=qT_Q_singleF*plot_Q*z_fac;

     // cout<<"Check this "<<temp_noRC<<endl;//0.0;
     if(temp_noRC<0) temp_noRC=0.0;    


     gr_F_SC_B->SetPoint(i,qT_Q_single,temp_noRC);
     gr_F_SC_R->SetPoint(i,qT_Q_single,temp_RC);
   }
 file_to_read.close();
 file_to_read.clear();
}


void plot_factorized(string lab,string kine)
{
  string path_to_file="/w/halla-scshelf2102/solid/bishnu/RC_plots/pol_Bishnu";
  string file_name_Col, file_name_Siv, file_name_double_mphis, file_name_double_phis;
  //Int_t num_tot=17;
  //Int_t num_tot=33;
  // if(

  // file 1
  file_name_Col=Form("%s/Pol_%s_%s_Col_constAlpha.txt",path_to_file.c_str(),lab.c_str(),kine.c_str());

  // file 2
  file_name_Siv=Form("%s/Pol_%s_%s_Siv_constAlpha.txt",path_to_file.c_str(),lab.c_str(),kine.c_str());

  // file 3

  file_name_double_mphis=Form("%s/Pol_%s_%s_Col_Siv_mphis_constAlpha.txt",path_to_file.c_str(),lab.c_str(),kine.c_str());

  //// file 4
  file_name_double_phis=Form("%s/Pol_%s_%s_Col_Siv_pphis_constAlpha.txt",path_to_file.c_str(),lab.c_str(),kine.c_str());



  const int file_num=4;
  string file_name[file_num]={file_name_Col, file_name_Siv, file_name_double_mphis,file_name_double_phis };

  double qT_Q_single,qT_Q_singleF,sigma_noRC_single,sigma_RC_single,Esigma_noRC_single;
  double temp_noRC,temp_RC;
 
  // TGraph *gr_bi[10];
  TCanvas *c[10];
 
 
  ifstream file_to_read;
  int id_gr=0;
  int id_gr_num;
  for(int i_file =0;i_file<file_num-2;i_file++)
    {
      id_gr_num=i_file+id_gr;
      //c[i_file]= new TCanvas(Form("c%d",i_file),"");
      gr_Bi[id_gr_num]= new TGraph();
      gr_Bi[id_gr_num+1]= new TGraph();
      // cout<<"   "<<file_name[i_file].c_str()<<endl;

      file_to_read.open(file_name[i_file]);
      if(!file_to_read)
	{
	  cout<<" FILE IS NOT AVAILABLE "<<i_file<< endl;
	  exit(-1);
	}
      else 
	{
	  //cout<<"PROCEEDING TO FILE "<<i_file<< endl;
	  for(int i=0;i<num_tot_factorized;i++)
	    {
	      //   file_to_read >> qT_Q_single >> sigma_noRC_single >>   sigma_RC_single >> Esigma_noRC_single;
	      file_to_read >> qT_Q_singleF >> temp_noRC >> temp_RC >> Esigma_noRC_single;
	      qT_Q_single=qT_Q_singleF*plot_Q*z_fac;
	      sigma_noRC_single=temp_noRC;
	      sigma_RC_single=temp_RC;
	      // cout<<qT_Q_single<<"  Born   "<<sigma_noRC_single<<endl;
	      gr_Bi[id_gr_num]->SetPoint(i,qT_Q_single, sigma_noRC_single);
	      gr_Bi[id_gr_num+1]->SetPoint(i,qT_Q_single, sigma_RC_single);
	    }

	  /*
	    gr_bi[id_gr]->Draw("AL");
	    gr_bi[id_gr]->SetLineColor(3);
	    gr_bi[id_gr]->SetLineStyle(2);
	    gr_bi[id_gr+1]->Draw("LSAME");
	    gr_bi[id_gr+1]->SetLineColor(3);
	    gr_bi[id_gr+1]->SetLineStyle(3);
	  */
	  file_to_read.close();
	  file_to_read.clear();

	  //cout<<id_gr_num<<" Total graph filled      "<<id_gr_num+1<<endl;
	  id_gr++;
	  // if(i_file>2)id_gr=id_gr-1;
	  //cout<<id_gr<<endl;
	}// number of file loop
    }// else loop
 
  //int color[file_num-1]={4,4,2};


  // gr_bi[col]->SetLineColor(
} // program loop











void plot_traditional(string lab,string kine)//,double pol_col)
{

  string path_to_file="/w/halla-scshelf2102/solid/bishnu/RC_plots/pol_Duane";
  // 
  double qt_to_Q,qt_to_QF,unpol_bn, err1,	unpol_rc2, err2,   sivers_bn,     err3;
  double sivers_rc, err4,  collins_bn,	   err5,	   collins_rc,	err6;

  double sivers_bn_temp, sivers_rc_temp,collins_bn_temp,collins_rc_temp;

  string file_name_Siv,file_name_Col,file_name_Full;
  Int_t num_tot=82;

  file_name_Siv=Form("%s/PolSiv_%s%s.txt",path_to_file.c_str(),lab.c_str(),kine.c_str());

  file_name_Col=Form("%s/PolCol_%s%s.txt",path_to_file.c_str(),lab.c_str(),kine.c_str());

  file_name_Full=Form("%s/PolFull_%s%s.txt",path_to_file.c_str(),lab.c_str(),kine.c_str());


   
  const int tot_file_traditional=3;
  cout<<"I am inside traditional "<<endl;
  string file_name[tot_file_traditional]={ file_name_Col,file_name_Siv, file_name_Full };
  //string file_name[tot_file_traditional]={file_name_Col};//, file_name_Siv, file_name_Full };
 
  // TGraph *gr_Du[15];
  TCanvas *c[tot_file_traditional];
  TGraph*gr_Du_tot;

  ifstream file_to_read;
  int id_gr=0;
  int id_gr_num;
 
  string heading;//[tot_file_traditional];

  for (int ifile=0;ifile<tot_file_traditional-1;ifile++)
    {
     
      id_gr_num=ifile+id_gr;
      // cout<<id_gr_num<<" Total graph filled  "<<id_gr_num+3<<endl;
      c[ifile]= new TCanvas(Form("c%d",ifile),Form("Traditional File %d",ifile));
      gr_Du[id_gr_num]= new TGraph();
      gr_Du[id_gr_num+1]= new TGraph();
      gr_Du[id_gr_num+2]= new TGraph();
      gr_Du[id_gr_num+3]= new TGraph();
  
      file_to_read.open(file_name[ifile]);
      if(!file_to_read)
	{
	  cout<<" FILE IS NOT AVAILABLE "<<endl;
	  exit(-1);
	}
      else
	{
	  cout<<"PROCEEDING TO FILE   "<<ifile<<endl;
	  getline(file_to_read,heading);
	  // cout<<"-----------------------"<<endl;
	  // cout<<heading <<endl;
	 	 	 
	  for(int i=0;i<num_tot;i++)
	    {
	      file_to_read>> qt_to_QF>>unpol_bn>> err1>>unpol_rc2>> err2>>sivers_bn_temp>> err3>> sivers_rc_temp>> err4>>  collins_bn_temp>>  err5>> collins_rc_temp>>err6;
 
	      qt_to_Q=qt_to_QF*plot_Q*z_fac;
	    
	      sivers_bn=sivers_bn_temp*0.5*unpol_bn;
	      sivers_rc=sivers_rc_temp*0.5*unpol_rc2;
	      collins_bn= 0.5*collins_bn_temp*unpol_bn;//*pol_factor;
	      collins_rc=0.5*collins_rc_temp*unpol_rc2;//*pol_factor;
	    
	      if(sivers_bn<0) sivers_bn=0.0;
	      if(collins_bn<0) collins_bn=0.0;
	      if(sivers_rc<0) sivers_rc=0.0;
	      if(collins_rc<0) collins_rc=0.0;

	      //sivers_born= sivers *0.5*unpol_bn
	      //sivers_rc= sivers_rc *0.5*unpol_rc
	      if(collins_rc>0.20e-6 && qt_to_Q>0.4)
		cout<<qt_to_QF<<"   "<<collins_bn<<"  "<<collins_rc<<endl;
	      // cout<<ifile<<"   "<<i<<"   "<<qt_to_Q<<" Collins_bn "<<collins_bn<<" Siv Born "<<sivers_bn<<endl;//"  Colins RC"<<collins_rc<<" Siv_RC "<<sivers_rc<<endl;
	      //cout<<" sivers born   "<<collins_bn<<"    "<<pol_factor<<endl;	     
	      gr_Du[id_gr_num]->SetPoint(i,qt_to_Q, collins_bn);
	      gr_Du[id_gr_num+1]->SetPoint(i,qt_to_Q, sivers_bn);
	      gr_Du[id_gr_num+2]->SetPoint(i,qt_to_Q, collins_rc);
	      gr_Du[id_gr_num+3]->SetPoint(i,qt_to_Q, sivers_rc);
	      if(ifile==2)
		{
		  gr_Du_tot= new TGraph();
		  double total=collins_rc+sivers_rc;
		  gr_Du_tot->SetPoint(i,qt_to_Q,total);

		}

	    } // total number of points 
	 
	  Get_title(ifile);
 
	  gr_Du[id_gr_num]->Draw("AL");
	  gr_Du[id_gr_num]->GetYaxis()->SetRangeUser(-0.02e-6,max_range);
	  gr_Du[id_gr_num]->GetXaxis()->SetRangeUser(0,1.3);
	  gr_Du[id_gr_num]->GetYaxis()->SetTitle(graph_title.c_str());
	  gr_Du[id_gr_num]->SetLineColor(4);
	  gr_Du[id_gr_num]->SetLineStyle(7);
	  gr_Du[id_gr_num]->SetLineWidth(3);
	  //gr_Du[id_gr_num]->GetXaxis()->SetTitle("q_{T}/Q");
	  gr_Du[id_gr_num]->GetXaxis()->SetTitle("Ph_{T} (GeV/c)");

	  gr_Du[id_gr_num+1]->Draw("LSAME");
	  // gr_Du[id_gr_num+1]->Draw("AL");
	  gr_Du[id_gr_num+1]->SetLineColor(3);
	  gr_Du[id_gr_num+1]->SetLineStyle(7);
	  gr_Du[id_gr_num+1]->SetLineWidth(3);
  
	  gr_Du[id_gr_num+2]->Draw("LSAME");
	  gr_Du[id_gr_num+2]->SetLineColor(4);
	  gr_Du[id_gr_num+2]->SetLineStyle(9);
	  gr_Du[id_gr_num+2]->SetLineWidth(3);
  
	  gr_Du[id_gr_num+3]->Draw("LSAME");
	  gr_Du[id_gr_num+3]->SetLineColor(3);
	  gr_Du[id_gr_num+3]->SetLineStyle(9);
	  gr_Du[id_gr_num+3]->SetLineWidth(3);

	  /*
	    if(ifile==2)
	    {
	    gr_Du_tot->Draw("LSAME");
	    gr_Du_tot->SetLineColor(2);
	    gr_Du_tot->SetLineWidth(3);
	    }
	  */
	  TLegend *legend=new TLegend(0.6,0.65,0.88,0.85);// from(x1,y1) to (x2,y2)
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.04);
	  legend->AddEntry(gr_Du[id_gr_num],"LO Collins","l");
	  legend->AddEntry(gr_Du[id_gr_num+1],"LO Sivers","l");
	  legend->AddEntry(gr_Du[id_gr_num+2],"RES Collins","l");                     
	  legend->AddEntry(gr_Du[id_gr_num+3],"RES Sivers","l");                       
	  legend->Draw();
	  cout<<id_gr_num<<"   "<<id_gr_num+3<<endl;
 
	  file_to_read.close();
	  file_to_read.clear();
	  id_gr=3*(ifile+1);
      
	}// else loop 
    } // File loop  

}



















void merger()
{
  cout<<"This is good"<<endl;
}
