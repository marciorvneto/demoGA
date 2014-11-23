RHO::RHO(double D, double V0, double y,double ke,double ks){
	this->gama=roAgua(this->T)*__G;
	this->D=D;
	this->A=__PI*std::pow(this->D,2)/4;
	this->V=V0;
	this->y=y;
	this->ke=ke;
	this->ks=ks;
	this->vetorY.push_back(this->y);

	this->QRHO=0;
	this->HRHO=0;

}

void RHO::novaIteracao(double t){
	if(this->temEsquerda() && this->temDireita()){
		PontoHQ* E = dynamic_cast<PontoHQ*>(this->getEsquerda());
		PontoHQ* D = dynamic_cast<PontoHQ*>(this->getDireita());
		PontoHQ* X = dynamic_cast<PontoHQ*>(this);

		double V0=this->V;

		double B=this->B;
		double R=this->R;

		double HE=E->getHD();
		double QE=E->getQD();
		double HD=D->getHE();
		double QD=D->getQE();

		/*std::cout << "=====" << "\n";
		std::cout << "HE: " << HE << "\n";
		std::cout << "QE: " << QE << "\n";
		std::cout << "HD: " << HD << "\n";
		std::cout << "QD: " << QD << "\n";
		std::cout << "Tem Esquerda?: " << this->temEsquerda() << "\n";
		std::cout << "Tem Direita?: " << this->temDireita() << "\n";*/

		double CP=HE+B*QE;
		double CM=HD-B*QD;
		double BP=B+R*std::abs(QE);
		double BM=B+R*std::abs(QD); 

		this->HEnovo=((CP*BM+CM*BP)/(BP+BM));
		this->HDnovo=((CP*BM+CM*BP)/(BP+BM));

		if(this->HEnovo-this->HE<=1e-6){
			this->calculosRHO(CP,CM,BP,BM,true);
			this->V+=this->dt*this->QRHO;
			this->y-=this->dt*this->QRHO/this->A;
			this->vetorY.push_back(this->y);
		}else{
			this->calculosRHO(CP,CM,BP,BM,false);
			this->V+=this->dt*this->QRHO;
			this->y-=this->dt*this->QRHO/this->A;
			this->vetorY.push_back(this->y);
		}
		this->P=P*std::pow(V0/this->V,1.2);
		this->HEnovo=this->HRHO;
		this->HDnovo=this->HRHO;
		this->QDnovo=(this->HDnovo-CM)/BM;
		this->QEnovo=(CP-this->HEnovo)/BP;
	}
}

void RHO::calculosRHO(double CP, double CM, double BP, double BM,bool saindo){
	double k=-this->ke;
	if(saindo){
		k=this->ks;
	}
	double p_g_rel = this->P/this->gama-pressaoAtmosferica(this->Z);
	double a=1/BP+1/BM;
	double b=CP/BP+CM/BM;
	double c=b/a-p_g_rel-this->y-this->Z;
	/*std::cout << "======" << "\n";
	std::cout << "a: " << a << "\n";
	std::cout << "b: " << b << "\n";
	std::cout << "c: " << c << "\n";
	std::cout << "p_g_rel: " << p_g_rel << "\n";*/
	this->QRHO=(-1/a+std::sqrt(1/std::pow(a,2)-4*k*c))/(2*k);
	this->HRHO=(this->QRHO+b)/a;

}

void RHO::grita(){
	for(int i=0;i<this->vetorY.size();i++){
		std::cout << this->vetorY[i] << ",";
	}
}

void RHO::ajustesPerfilInicial(double H){
	this->P=(pressaoAtmosferica(this->Z)+(H-(this->Z+this->y)))*this->gama;
}
