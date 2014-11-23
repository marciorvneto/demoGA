Bomba::Bomba(double A, double B, double C,double WR2,double NR,double etaR,double ENAPS){
	this->A=A;
	this->B=B;
	this->C=C;

	this->h=1;
	this->v=1;
	this->alfa=1;
	this->beta=1;

	this->WR2=WR2;
	this->NR=NR;
	this->etaR=etaR;
	this->ENAPS=ENAPS;
}

void Bomba::setHR(){
	this->HR=this->A*std::pow(this->QR,2)+this->B*this->QR+this->C+this->ENAPS;
	this->HE=this->A*std::pow(this->QR,2)+this->B*this->QR+this->C+this->ENAPS;
	this->HD=this->A*std::pow(this->QR,2)+this->B*this->QR+this->C+this->ENAPS;
}

void Bomba::atualizaParametros(){

	double v1=this->v;
	double h1=this->h;
	double a1=this->alfa;
	double b1=this->beta;

	double h2_min=0;
	double v2_min=v1+(__G*this->HR/(this->a*this->UR))*(h2_min-h1);
	if(v2_min<0){
		v2_min=0;
		h2_min=h1+(this->a*this->UR/(__G*this->HR))*(v2_min-v1);
	}

	double u=h1;
	double l=h2_min;
	int cont=0;
	double h2_est=(h1+h2_min)/2;
	double v2_est=v1+(__G*this->HR/(this->a*this->UR))*(h2_est-h1);
	double H2=h2_est*this->HR;
	double Q2=v2_est*this->QR;
	double N2_est=this->NR*Q2/this->QR;
	double a2_est=N2_est/this->NR;
	double b2_est=Q2*H2/(this->QR*this->HR);
	
	double k1=0;

	while(cont<1000){
		k1=446826*this->QR*this->HR/(this->WR2*this->etaR*std::pow(this->NR,2));
		if(std::abs(a1-a2_est-k1*this->dt*(b1+b2_est))<=1e-6){
			break;
		}else if(a1-a2_est-k1*this->dt*(b1+b2_est)>1e-6){
			l=h2_est;
			h2_est=(l+u)/2;
		}else{
			u=h2_est;
			h2_est=(l+u)/2;
		}
		v2_est=v1+(__G*this->HR/(this->a*this->UR))*(h2_est-h1);
		H2=h2_est*this->HR;
		Q2=v2_est*this->QR;
		N2_est=this->NR*Q2/this->QR;
		a2_est=N2_est/this->NR;
	  b2_est=Q2*H2/(this->QR*this->HR);
		cont++;
	}

	this->alfa=a2_est;
	this->beta=b2_est;
	this->h=h2_est;
	this->v=v2_est;
	//std::cout << "alfa: " << alfa << "\n";
	//std::cout << "beta: " << beta << "\n";
	if(std::abs(a1-a2_est-k1*this->dt*(b1+b2_est))>1e-6){
		std::cout << "Calculos da bomba nao convergiram" << "\n";
	}
}

void Bomba::novaIteracao(double t){
	double B=this->B;
	double R=this->R;
	if(this->temEsquerda()){
/*		PontoHQ* E = dynamic_cast<PontoHQ*>(this->getEsquerda());
		PontoHQ* X = dynamic_cast<PontoHQ*>(this);

		double HE=E->getHD();
		double QE=E->getQD();

		double CP=HE+B*QE;
		double BP=B+R*std::abs(QE);

		void atualizaParametros();

		this->setQE(this->v*this->QR);
		this->setHE(this->h*this->HR);*/

	}
	if(this->temDireita()){
		PontoHQ* D = dynamic_cast<PontoHQ*>(this->getDireita());		
		PontoHQ* X = dynamic_cast<PontoHQ*>(this);

		double HD=D->getHE();
		double QD=D->getQE();

		double CM=HD-B*QD;
		double BM=B+R*std::abs(QD);

		this->atualizaParametros();

		this->QDnovo=(this->v*this->QR);
		this->QEnovo=(this->v*this->QR); //<-- ver

		if(this->Z<this->ENAPS){
			this->HDnovo=(std::max(CM+BM*this->QD,this->Z));	
			this->HEnovo=(std::max(CM+BM*this->QD,this->Z)); //<-- ver
		}else{
			this->HDnovo=(CM+BM*this->QD);
			this->HEnovo=(CM+BM*this->QD); //<-- ver
		}
	}
}
