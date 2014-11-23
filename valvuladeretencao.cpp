ValvulaDeRetencao::ValvulaDeRetencao(){
	this->fechada=false;
}

void ValvulaDeRetencao::novaIteracao(double dt){
	double B=this->B;
	double R=this->R;
	if(this->temEsquerda() && this->temDireita()){
		PontoHQ* E = dynamic_cast<PontoHQ*>(this->getEsquerda());
		PontoHQ* D = dynamic_cast<PontoHQ*>(this->getDireita());
		PontoHQ* X = dynamic_cast<PontoHQ*>(this);

		double HE=E->getHD();
		double QE=E->getQD();
		double HD=D->getHE();
		double QD=D->getQE();

		double CP=HE+B*QE;
		double CM=HD-B*QD;
		double BP=B+R*std::abs(QE);
		double BM=B+R*std::abs(QD); 

		if(!this->fechada){

			this->QEnovo=((CP-CM)/(BP+BM));
			this->QDnovo=((CP-CM)/(BP+BM));
			this->HEnovo=((CP*BM+CM*BP)/(BP+BM));
			this->HDnovo=((CP*BM+CM*BP)/(BP+BM));
			
			if(this->QDnovo<0){
				this->QDnovo=0;
				this->QEnovo=0;
				this->HEnovo=CP-B*QE;
				this->HDnovo=CP-B*QE; //<-- confeir
				this->fechada=true;
			}
		}else{
			if(this->HE>=this->HD){
				this->QEnovo=(this->QE+this->QD)/2;
				this->QDnovo=(this->QE+this->QD)/2;
				this->HEnovo=(this->HE+this->HD)/2;
				this->HDnovo=(this->HE+this->HD)/2;
				this->fechada=false;
			}else{
				this->QDnovo=0;
				this->QEnovo=0;
				this->HEnovo=CP-B*QE;
				this->HDnovo=CP-B*QE; //<-- confeir
			}
		}
	}
}
