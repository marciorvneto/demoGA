PontoHQ::PontoHQ(){}
void PontoHQ::setZ(double Z){
	this->Z=Z;
}
void PontoHQ::setHE(double H){
	this->HE=H;
}
void PontoHQ::setQE(double Q){
	this->QE=Q;
}
void PontoHQ::setB(double B){
	this->B=B;
}
void PontoHQ::setR(double R){
	this->R=R;
}
void PontoHQ::seta(double a){
	this->a=a;
}
void PontoHQ::setdt(double dt){
	this->dt=dt;
}
void PontoHQ::setT(double T){
	this->T=T;
}
void PontoHQ::setHR(){
	this->HE=0;
	this->HD=0;
	this->HR=0;
}
void PontoHQ::setQR(double Q){
	this->QE=Q;
	this->QD=Q;
	this->QR=Q;
}
void PontoHQ::setUR(double U){
	this->UR=U;
}
double PontoHQ::getHE(){
	return this->HE;
}
double PontoHQ::getQE(){
	return this->QE;
}
void PontoHQ::setHD(double H){
	this->HD=H;
}
void PontoHQ::setQD(double Q){
	this->QD=Q;
}
double PontoHQ::getHD(){
	return this->HD;
}
double PontoHQ::getQD(){
	return this->QD;
}
double PontoHQ::getZ(){
	return this->Z;
}
void PontoHQ::novaIteracao(double t){
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

		this->QEnovo=((CP-CM)/(BP+BM));
		this->QDnovo=((CP-CM)/(BP+BM));
		this->HEnovo=((CP*BM+CM*BP)/(BP+BM));
		this->HDnovo=((CP*BM+CM*BP)/(BP+BM));
	}
}
void PontoHQ::substituiValores(){
		this->setQE(this->QEnovo);
		this->setQD(this->QDnovo);
		this->setHE(this->HEnovo);
		this->setHD(this->HDnovo);
}

void PontoHQ::ajustesPerfilInicial(double H){

}
