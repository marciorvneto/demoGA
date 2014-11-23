Ponto::Ponto(){
	this->temE=false;
	this->temD=false;
}
Ponto::~Ponto(){}
void Ponto::setIndice(int i){
	this->indice=i;
}
void Ponto::setEsquerda(Ponto* E){
	this->E=E;
	this->temE=true;
}
void Ponto::setDireita(Ponto* D){
	this->D=D;
	this->temD=true;
}
Ponto* Ponto::getEsquerda(){
	return this->E;
}
Ponto* Ponto::getDireita(){
	return this->D;
}
int Ponto::getIndice(){
	return this->indice;
}
bool Ponto::temEsquerda(){
	return this->temE;
}
bool Ponto::temDireita(){
	return this->temD;
}
