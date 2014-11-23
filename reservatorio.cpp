Reservatorio::Reservatorio(double yLam){
	this->yLam=yLam;
}
void Reservatorio::setHR(){
	this->HE=this->Z+this->yLam;
	this->HD=this->Z+this->yLam;
	this->HR=this->Z+this->yLam;
}
void Reservatorio::novaIteracao(double t){
	double B=this->B;
	double R=this->R;
	if(this->temEsquerda()){
		PontoHQ* E = dynamic_cast<PontoHQ*>(this->getEsquerda());
		PontoHQ* X = dynamic_cast<PontoHQ*>(this);

		double Hres=this->yLam+this->Z;		
		double HE=E->getHD();
		double QE=E->getQD();

		double CP=HE+B*QE;
		double BP=B+R*std::abs(QE);

		this->QEnovo=((CP-Hres)/BP);
		this->HEnovo=(Hres);

		if(this->temDireita()){
			this->QDnovo=((CP-Hres)/BP);
			this->HDnovo=(Hres);
		}

		/*std::cout<<"QEnovo: "<<this->QEnovo << "\n";
		std::cout<<"HEnovo: "<<this->HEnovo << "\n";*/

	}
	if(this->temDireita()){
		PontoHQ* D = dynamic_cast<PontoHQ*>(this->getDireita());		
		PontoHQ* X = dynamic_cast<PontoHQ*>(this);

		double Hres=this->yLam+this->Z;		
		double HD=D->getHE();
		double QD=D->getQE();

		double CM=HD-B*QD;
		double BM=B+R*std::abs(QD);

		this->QDnovo=((Hres-CM)/BM);
		this->HDnovo=(Hres);

		if(!this->temEsquerda()){
			this->QEnovo=((Hres-CM)/BM);
			this->HEnovo=(Hres);
		}

		/*std::cout<<"QDnovo: "<<this->QDnovo << "\n";
		std::cout<<"HDnovo: "<<this->HDnovo << "\n";
		std::cout<<"QD: "<<this->QD << "\n";
		std::cout<<"HD: "<<this->HD << "\n";*/

	}
}
