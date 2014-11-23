double Material::getE(){
	return this->E;
}
double Material::getu(){
	return this->u;
}
double Material::getc1(){
	return this->c1;
}

PVC::PVC(){
	this->E=3.5e9;
	this->u=0.45;
	this->c1=1-this->u/2;
}

Aco::Aco(){
	this->E=210e9;
	this->u=0.27;
	this->c1=1-this->u/2;
}

FerroFundido::FerroFundido(){
	this->E=100e9;
	this->u=0.25;
	this->c1=1-this->u/2;
}

FerroDuctil::FerroDuctil(){
	this->E=172e9;
	this->u=0.25;
	this->c1=1-this->u/2;
}

