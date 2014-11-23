CHE::CHE(double D, double ke,double ks){
	this->gama=roAgua(this->T)*__G;
	this->D=D;
	this->A=__PI*std::pow(this->D,2)/4;

	this->ke=ke;
	this->ks=ks;
	this->vetorY.push_back(this->y);

	this->QCHE=0;
	this->HCHE=0;

}

void CHE::novaIteracao(double t){
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

		this->QDnovo=(this->HD-CM)/BM;
		this->QEnovo=(CP-this->HE)/BP;

		double QU=this->QEnovo-this->QDnovo;

		this->y+=QU/this->A*this->dt;
		this->vetorY.push_back(this->y);

		this->HEnovo=this->Z+this->y;
		this->HDnovo=this->Z+this->y;

		// ks e ke nao implementados
	}
}

void CHE::calculosCHE(double CP, double CM, double BP, double BM,bool saindo){


}

void CHE::grita(){
	for(int i=0;i<this->vetorY.size();i++){
		std::cout << this->vetorY[i] << ",";
	}
}

void CHE::ajustesPerfilInicial(double H){
	this->y=H-this->Z;
}
