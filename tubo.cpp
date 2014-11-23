Tubo::Tubo(Material M, double L, double e, double D){
	this->L=L;
	this->e=e;
	this->M=M;
	this->D=D;
	this->T=20;
}

void Tubo::setT(double T){
	this->T=T;
}

double Tubo::getL(){
	return this->L;
}

double Tubo::gete(){
	return this->e;
}

double Tubo::getD(){
	return this->D;
}

double Tubo::getA(){
	return __PI*pow(this->D,2)/4;
}

double Tubo::getT(){
	return this->T;
}

double Tubo::geta(){
	double c1=this->M.getc1();
	double D=this->D;
	double e=this->e;
	double E=this->M.getE();
	double T=this->T;
	double ro=roAgua(T);
	double eps=epsAgua(T);
	
	return std::sqrt(eps/ro)/std::sqrt(1+eps*D*c1/(E*e));
}
