Valvula::Valvula(double tc, double m,double Hv,bool fechando=true){
	this->tc=tc;
	this->m=m;
	this->fechando=fechando;
	this->Hv=Hv;
}

void Valvula::setHR(){
	this->HE=Hv;
	this->HD=Hv;
	this->HR=Hv;
}

void Valvula::novaIteracao(double t){
	double B=this->B;
	double R=this->R;
	if(this->temEsquerda()){
		PontoHQ* E = dynamic_cast<PontoHQ*>(this->getEsquerda());
		PontoHQ* X = dynamic_cast<PontoHQ*>(this);

		double tau=tauValvula(t,this->tc,this->m,this->fechando);
		double Cv=std::pow(this->QR*tau,2)/(2*this->HR);

		double HE=E->getHD();
		double QE=E->getQD();

		double CP=HE+B*QE;
		double BP=B+R*std::abs(QE);

		this->QEnovo=(-BP*Cv+std::sqrt(std::pow(BP*Cv,2)+2*Cv*CP));
		this->HEnovo=(CP-BP*this->QE);

	}
	if(this->temDireita()){
/*		PontoHQ* D = dynamic_cast<PontoHQ*>(this->getDireita());		
		PontoHQ* X = dynamic_cast<PontoHQ*>(this);


		double HD=D->getHE();
		double QD=D->getQE();

		double CM=HD-B*QD;
		double BM=B+R*std::abs(QD);

		this->setQD((Hres-CM)/BM);
		this->setHD(Hres);		*/

	}
}
