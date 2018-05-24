#define ANN_cxx
#include "ANN.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void ANN::Loop()
{
//   In a ROOT session, you can do:
//      root> .L ANN.C
//      root> ANN t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

  if (fChain == 0) return;

//create_bottles(hist&vector)**********************************************************************
  int k =0;
  int j =0;
 
  std::vector<TH1D*> vhwidth1;
  std::vector<TH1D*> vhwidth2;
  std::vector<TH1D*> vhgpt1;   
  std::vector<TH1D*> vhgpt2;
  
  for (int i=0;i<15;i++) { 
    TH1D* hlead = new TH1D(Form("hp1_eb_%d",i),"",100,-0.2,0.2); 
    vhwidth1.push_back(hlead);   
  } 
  for (int i=0;i<10;i++) { 
    TH1D* hsub= new TH1D(Form("hp2_eb_%d",i),"",100,-0.2,0.2); 
    vhwidth2.push_back(hsub);
  } 
  for (int i=0;i<15;i++) {      
    TH1D* hgpt1 = new TH1D(Form("hgpt1_%d",i),"",150,0,1500); 
    hgpt1->GetXaxis()->SetTitle("Pt (GeV)");
    vhgpt1.push_back(hgpt1);
  }
  for (int i=0;i<10;i++) {      
    TH1D* hgpt2 = new TH1D(Form("hgp2_%d",i),"",150,0,1500); 
    hgpt2->GetXaxis()->SetTitle("Pt (GeV)");
    vhgpt2.push_back(hgpt2);
  } 
  
  
  TH1D* photon1_pt= new TH1D("photon1_pt","",150,0,1500);
  TH1D* photon2_pt= new TH1D("photon2_pt","",150,0,1500);
  TH1D* diphoton_Minv= new TH1D("diphoton_Minv","",150,0,1500);
  TH1D* genPhoton1_pt= new TH1D("genPhoton1_pt","",150,0,1500);
  TH1D* genPhoton2_pt= new TH1D("genPhoton2_pt","",150,0,1500);

//create_tree&branch*******************************************************************************
  //TFile hfile("Event.root","RECREATE");
  //gROOT->cd();
  TTree* mytree = new TTree("photontree","photontree");

  struct event_info_struct{
    Int_t RunNumber;
    Int_t EventNumber;
  };
 
  event_info_struct this_event_info;
  
 
  struct traits_struct{

    Double_t pt;
    Double_t eta;
    Double_t phi;
    Double_t scEta;
    Double_t scPhi;
    Double_t rho;
    Double_t chargedHadIso03; 
          
  };


  traits_struct event_traits;
   
  mytree->Branch("eventtraits",&event_traits,"pt/D:eta:phi:scEta:scPhi:rho:chargedHadIso03");

//  tree->Branch("good",&good,"pt/D:eta:phi:scEta:scPhi:rho:chargedHadIso03");
//  tree->Branch("bad",&bad,"pt/D:eta:phi:scEta:scPhi:rho:chargedHadIso03"); 
   
   
//******below_is_loop_over***************************************************************************
//have to initialize the variables in the struct

   Long64_t nentries =fChain->GetEntriesFast();//****test change

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;
     // if (jentry % 100000 == 0)
     cout << "Event: " << jentry << endl;
     j++;
     if (isGood){
       photon1_pt->Fill(Photon1_pt);
       photon2_pt->Fill(Photon2_pt);
       genPhoton1_pt->Fill(GenPhoton1_pt);
       genPhoton2_pt->Fill(GenPhoton2_pt);	 
     }       
      for (int i= 0; i<15;i++){
	if(isGood && Photon1_isEB && i*100<=Photon1_pt && Photon1_pt<(i+1)*100) {        
	  vhwidth1.at(i)->Fill((Photon1_pt-GenPhoton1_pt)/ GenPhoton1_pt); 
	  vhgpt1.at(i)->Fill(Photon1_pt);   
	}
      }
      for (int i= 0; i<10;i++){
	if(isGood && Photon2_isEB && i*100<=Photon2_pt && Photon2_pt<(i+1)*100) {        
	  vhwidth2.at(i)->Fill((Photon2_pt-GenPhoton2_pt)/ GenPhoton2_pt); 
	  vhgpt2.at(i)->Fill(Photon2_pt);   
	}
      }
      for (int i= 0; i<15;i++){
	if(isGood && Photon1_isEE && i*100<=Photon1_pt && Photon1_pt<(i+1)*100) {        
	  vhwidth1.at(i)->Fill((Photon1_pt-GenPhoton1_pt)/ GenPhoton1_pt); 
	  vhgpt1.at(i)->Fill(Photon1_pt);   
	}
      }
      for (int i= 0; i<10;i++){
	if(isGood && Photon2_isEE && i*100<=Photon2_pt && Photon2_pt<(i+1)*100) {        
	  vhwidth2.at(i)->Fill((Photon2_pt-GenPhoton2_pt)/ GenPhoton2_pt); 
	  vhgpt2.at(i)->Fill(Photon2_pt);   
	}
      }
      
      
      this_event_info.RunNumber=0;
      this_event_info.EventNumber=0;
      event_traits.pt = -1.1;//-99999.99;
      event_traits.eta= -1.1;
      event_traits.phi= -1.1;//}  
      event_traits.scEta= -1.1; //Photon1_scEta;
      event_traits.scPhi= -1.1;//Photon1_scPhi;
      event_traits.rho= -1.1;//Photon1_rho;
      event_traits.chargedHadIso03= -1.1;// Photon1_chargedHadIso03;
      
      mytree->Fill();

     
   }//end of loop

//write_tree_to_the_file**************************************************************

   cout << "tree1 before" << endl;
   TFile *f = new TFile("tree1.root","recreate"); 
   cout << "tree1 after" << endl;
   
//cout << "bincenter: "<< vhwidth1.at(1)->GetBinCenter(89) <<endl; 
   mytree->Write();

           
   f->Close(); 


   std::vector<double> vmean1;
   std::vector<double> vmean2;
   std::vector<double> vrms1;
   std::vector<double> vrms2;

   for (int i=0;i<15;i++){ 
     vmean1.push_back(vhgpt1.at(i)->GetMean());
     vrms1.push_back(vhwidth1.at(i)->GetRMS());
   }
   
   for (int i=0;i<10;i++){
     vrms2.push_back(vhwidth2.at(i)->GetRMS()); //store rms    
   }
   for (int i=0;i<6;i++){
     vmean2.push_back(vhgpt2.at(i)->GetMean()); //store mean
   }

   vmean2.push_back(650.0);
   vmean2.push_back(750.0);
   vmean2.push_back(850.0);
   vmean2.push_back(950.0);


   **************************************************************************************   

   cout << "file2 start" << endl;
   TFile f_out("histogram_DiPhoton_EB_ANNTree.root","RECREATE");
   cout << "file2 after" <<endl;

   photon1_pt->Write();
   photon2_pt->Write();
   genPhoton1_pt->Write();
   genPhoton2_pt->Write();

   for (int i=0;i<15;i++){ 
     vhwidth1 .at(i)->Write(); 
     cout<< "mean1:"<< vhgpt1.at(i)->GetMean() <<";"<<endl;}

   for (int i=0;i<10;i++){    
     vhwidth2.at(i)->Write();
     cout<< "mean2:"<< vmean2.at(i)<<";"<<endl;}
   
   TGraphErrors *g1= new TGraphErrors(15,&vmean1[0],&vrms1[0],0,0); 
   g1->SetMarkerStyle(21);
   g1->SetMarkerSize(1);
   g1->SetLineColor(2);
   g1->SetMarkerColor(2);
   g1->SetTitle("Photon_pt_isEB;Pt(GeV);Resolution");
   g1->SetName("pt1");
 
   TGraphErrors *g2= new TGraphErrors(10,&vmean2[0],&vrms2[0],0,0); 
   g2->SetMarkerStyle(21);
   g2->SetMarkerSize(1);
   g2->SetLineColor(1);
   g2->SetMarkerColor(1);
   //g2->SetTitle("Photon2_pt_isEB;Pt(GeV);Resolution");
   g2->SetName("pt2");
 
 
   g1->Write(); 
   g2->Write(); 
 
 

   TCanvas *c2= new TCanvas("c2","resolution_pt1_isEE");
   c2->Divide(4,4);

   for (int i=0; i<15; i++){  
     c2->cd(i+1);
     gPad->SetLogy();
     gStyle->SetStatW(0.3);
     gStyle->SetStatH(0.3);
     //gStyle->SetOptFit(0001);
     //vhwidth1.at(i)->Fit("gaus");
     vhwidth1.at(i)->Draw();
   }

   TCanvas *c3= new TCanvas("c3","resolution_pt2_isEE");
   c3->Divide(4,3);

   for (int i=0; i<10 ; i++){  
     c3->cd(i+1);
     gPad->SetLogy();
     gStyle->SetStatW(0.3);
     gStyle->SetStatH(0.3); 
     //vhwidth2.at(i)->Fit("gaus");
     vhwidth2.at(i)->Draw();
   }


   c2->Write();
   c3->Write();


   tree->Write();

 

   f_out.ls();
   f_out.Close();

  
   cout << "Total number of entries: " << j << endl;
   cout << "nentries: " << nentries << endl;




}
