TAU::TAU(double D, double y,double ke,double ks){

	this->D=D;
	this->A=__PI*std::pow(this->D,2)/4;

	this->y=y;
	this->ke=ke;
	this->ks=ks;
	this->vetorY.push_back(this->y);

	this->QTAU=0;
	this->HTAU=0;

}

void TAU::novaIteracao(double t){
	if(this->temEsquerda() && this->temDireita()){
		PontoHQ* E = dynamic_cast<PontoHQ*>(this->getEsquerda());
		PontoHQ* D = dynamic_cast<PontoHQ*>(this->getDireita());
		PontoHQ* X = dynamic_cast<PontoHQ*>(this);

		double B=this->B;
		double R=this->R;

		double HE=E->getHD();
		double QE=E->getQD();
		double HD=D->getHE();
		double QD=D->getQE();

		double CP=HE+B*QE;
		double CM=HD-B*QD;
		double BP=B+R*std::abs(QE);
		double BM=B+R*std::abs(QD); 

		this->QEnovo=((CP-CM)/(BP+BM));
		this->QDnovo=((CP-CM)/(BP+BM));
		this->HEnovo=((CP*BM+CM*BP)/(BP+BM));
		this->HDnovo=((CP*BM+CM*BP)/(BP+BM));

		if(this->HEnovo < this->Z+this->y){


			this->calculosTAU(CP,CM,BP,BM);
			this->HEnovo=this->HTAU;
			this->HDnovo=this->HTAU;
			this->QDnovo=(this->HDnovo-CM)/BM;
			this->QEnovo=(CP-this->HEnovo)/BP;
			if(this->QDnovo >= this->QEnovo){
				this->y+=(this->QEnovo-this->QDnovo)*this->dt/this->A;
			}
		}
		this->vetorY.push_back(this->y);
	}
}

void TAU::calculosTAU(double CP, double CM, double BP, double BM){
	double K=this->ke+this->ks;

	double a=1/BP+1/BM;
	double b=-(CP/BP+CM/BM);
	double A=K*std::pow(a,2);
	double B=1+2*K*a*b;
	double C=K*std::pow(b,2)-(this->y+this->Z);

			/*std::cout << "=====" << "\n";
			std::cout << "K: " << K << "\n";
			std::cout << "a: " << a << "\n";
			std::cout << "b: " << b << "\n";
			std::cout << "A: " << A << "\n";
			std::cout << "B: " << B << "\n";
			std::cout << "C: " << C << "\n";*/

	this->HTAU=(-B+std::sqrt(std::pow(B,2)-4*A*C))/(2*A);
	
			//std::cout << "HTAU: " << this->HTAU << "\n";

}

void TAU::grita(){
	for(int i=0;i<this->vetorY.size();i++){
		std::cout << this->vetorY[i] << ",";
	}
}

void TAU::ajustesPerfilInicial(double H){
	
}
