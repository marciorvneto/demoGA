Ventosa::Ventosa(){
	this->fechada=true;
	this->Var=0;
}

void Ventosa::novaIteracao(double t){
	double B=this->B;
	double R=this->R;
	if(this->temEsquerda() && this->temDireita()){
		PontoHQ* E = dynamic_cast<PontoHQ*>(this->getEsquerda());
		PontoHQ* D = dynamic_cast<PontoHQ*>(this->getDireita());
		PontoHQ* X = dynamic_cast<PontoHQ*>(this);

		double A = this->QR/this->UR;

		//std::cout << "A: " << A << "\n";

		double HE=E->getHD();
		double QE=E->getQD();
		double HD=D->getHE();
		double QD=D->getQE();

		double CP=HE+B*QE;
		double CM=HD-B*QD;
		double BP=B+R*std::abs(QE);
		double BM=B+R*std::abs(QD); 

		if(this->fechada){

			this->QEnovo=((CP-CM)/(BP+BM));
			this->QDnovo=((CP-CM)/(BP+BM));
			this->HEnovo=((CP*BM+CM*BP)/(BP+BM));
			this->HDnovo=((CP*BM+CM*BP)/(BP+BM));
			
			if(this->HEnovo<=this->Z){
				this->HEnovo=this->Z;
				this->HDnovo=this->Z;
				this->QDnovo=(this->HDnovo-CM)/BM;
				this->QEnovo=(CP-this->HEnovo)/BP;
				this->fechada=false;
			/*std::cout << "====="  << "\n";
			std::cout << "Z: " << this->Z << "\n";
			std::cout << "H: " << this->HEnovo << "\n";*/
			}
		}else{
			//std::cout << "******"  << "\n";
			this->QDnovo=(this->HE-CM)/BM;
			this->QEnovo=(CP-this->HD)/BP;
			this->Var+=(this->QDnovo-this->QEnovo)*this->dt;
			if(this->Var<=0){
				this->Var=0;
				this->HEnovo=this->HE+this->a/__G*std::abs(this->QDnovo-this->QEnovo)/A;
				this->HDnovo=this->HE+this->a/__G*std::abs(this->QDnovo-this->QEnovo)/A;
				this->QEnovo=(this->QE+this->QD)/2;
				this->QDnovo=(this->QE+this->QD)/2;
				this->fechada=true;
			}else{
				this->Var=0;
				this->HEnovo=this->Z;
				this->HDnovo=this->Z;
			}
		}
	}
}
