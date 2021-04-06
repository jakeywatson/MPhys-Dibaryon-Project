
{
TCanvas *can1 = new TCanvas("can1", "can1", 100, 10, 1100, 700);
can1->Divide(2, 1);
can1->cd(1);
TF1 *fi1 = new TF1("fi1","(x*(0.26**2-0.0456**2)/(x**2+0.0456**2)/(x**2+0.26**2))**2",0.0,0.4);
fi1->Draw();
can1->cd(2);
fi1->DrawIntegral();

}