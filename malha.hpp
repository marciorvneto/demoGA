template <typename T> class Malha{
private:
	std::vector<T*> pontos;
	Tubo* Tub;
	double dL;
	double dt;
	double QR;
	double t;
	int N;
public:
	Malha(){}
	T* operator[](int i){
		return this->pontos[i];
	}
	~Malha(){
		int n = this->pontos.size();
		for(int i=0;i<n;i++){
			delete this->pontos[i];
		}
	}
	void substituiPonto(T* ponto, int i){
		if(pontos[i]->temEsquerda()){
			ponto->setEsquerda(this->pontos[i-1]);
			this->pontos[i-1]->setDireita(ponto);
		}
		if(pontos[i]->temDireita()){
			ponto->setDireita(this->pontos[i+1]);
			this->pontos[i+1]->setEsquerda(ponto);
		}
		ponto->setZ(this->pontos[i]->getZ());
		this->pontos[i] = ponto;
	}
	void fazMalha(int n){
		for(int i=0;i<n;i++){
			T* novoPonto = new T;
			novoPonto->setIndice(i);
			this->pontos.push_back(novoPonto);
		}
		this->ordena();
		this->N=n;
	}
	void setPerfil(std::vector<double> Perfil){
		for(int i=0;i<Perfil.size();i++){
			this->pontos[i]->setZ(Perfil[i]);
		}		
	}
	void setTubo(Tubo* Tub){
		this->Tub=Tub;
		this->dL=this->Tub->getL()/(this->N-1);
	}
	void setQR(double Q){
		this->QR=Q;
	}
	void ordena(){
		int n = this->pontos.size();
		this->pontos[0]->setDireita(this->pontos[1]);
		for(int i=1;i<n-1;i++){
			this->pontos[i]->setEsquerda(this->pontos[i-1]);
			this->pontos[i]->setDireita(this->pontos[i+1]);
		}
		this->pontos[n-1]->setEsquerda(this->pontos[n-2]);
	}
	void inicializaMalha(){
		//Perfil inicial - H e Q
		this->pontos[0]->setQR(this->QR);
		this->pontos[this->pontos.size()-1]->setQR(this->QR);
		this->pontos[0]->setHR();
		this->pontos[this->pontos.size()-1]->setHR();
		this->pontos[0]->setUR(this->QR/this->Tub->getA());
		this->pontos[this->pontos.size()-1]->setUR(this->QR/this->Tub->getA());
		this->pontos[0]->seta(this->Tub->geta());
		this->pontos[this->pontos.size()-1]->seta(this->Tub->geta());
		double Hinicio=pontos[0]->getHE();
		double Hfim=pontos[this->pontos.size()-1]->getHE();
		double deltaH = Hinicio-Hfim;
		double dH = deltaH/(this->N-1);
		//Calculo de B e R
		double D=this->Tub->getD();
		double L=this->Tub->getL();
		double A=this->Tub->getA();
		double f=deltaH*__G*std::pow(__PI,2)*std::pow(D,5)/(8*std::pow(this->QR,2)*L);
		double a=this->Tub->geta();
		double B=a/(__G*A);
		double R=f*this->dL/(2*__G*D*std::pow(A,2));

		this->pontos[0]->setB(B);
		this->pontos[0]->setR(R);
		this->pontos[0]->setT(this->Tub->getT());
		this->pontos[this->pontos.size()-1]->setB(B);
		this->pontos[this->pontos.size()-1]->setR(R);
		this->pontos[this->pontos.size()-1]->setT(this->Tub->getT());


		//Inicializa t e dt
		this->t=0;
		this->dt=this->dL/a;
		this->pontos[0]->setdt(this->dt);
		this->pontos[this->pontos.size()-1]->setdt(this->dt);

		for(int i=1;i<this->pontos.size()-1;i++){
			this->pontos[i]->setHE(Hinicio-i*dH);
			this->pontos[i]->setHD(Hinicio-i*dH);
			this->pontos[i]->ajustesPerfilInicial(Hinicio-i*dH);
			this->pontos[i]->setQE(this->QR);
			this->pontos[i]->setQD(this->QR);
			this->pontos[i]->setQR(this->QR);
			this->pontos[i]->setUR(this->QR/A);
			this->pontos[i]->setB(B);
			this->pontos[i]->setR(R);
			this->pontos[i]->setdt(this->dt);
			this->pontos[i]->setT(this->Tub->getT());
			this->pontos[i]->seta(a);
		}
	}
	void grita(){
		int n = this->pontos.size();
		for(int i=0;i<n;i++){
			std::cout << "======" << "\n";
			std::cout << "Ponto: " << this->pontos[i]->getIndice() << "\n";
			if(this->pontos[i]->temEsquerda()){
				std::cout << "Esquerda: " << this->pontos[i-1]->getIndice() << "\n";
			}
			if(this->pontos[i]->temDireita()){
				std::cout << "Direita: " << this->pontos[i+1]->getIndice() << "\n";
			}
		}		
	}
	void itera(){
		this->t+=this->dt;
		for(int i=0;i<this->pontos.size();i++){
			this->pontos[i]->novaIteracao(this->t);
		}
		for(int i=0;i<this->pontos.size();i++){
			this->pontos[i]->substituiValores();
		}
	}
	void resultado(){
		for(int i=0;i<this->pontos.size();i++){			
			if(i==this->pontos.size()-1){
				std::cout << this->pontos[i]->getHE();
			}else{
				std::cout << this->pontos[i]->getHE() << " , ";
			}
		}
		std::cout << "\n";
	}
	void gritaItera(double Tmax){
		int Niter=std::floor(Tmax/this->dt);
		for(int i=0;i<Niter;i++){
			this->resultado();
			this->itera();	
		}
		this->resultado();
	}
	std::vector<std::vector<double> > salvaItera(double Tmax){
		int Niter=std::floor(Tmax/this->dt);
		std::vector<std::vector<double> > todas;
		std::vector<double> iterAtual;
		for(int j=0;j<Niter;j++){
			for(int i=0;i<this->pontos.size();i++){			
				iterAtual.push_back(this->pontos[i]->getHE());
			}
			todas.push_back(iterAtual);
			iterAtual.clear();
			this->itera();
		}
		return todas;
	}
	void gritaVetor(std::vector<std::vector<double> > vetor){
		std::vector<double> vetorAtual;
		for(int j=0;j<vetor.size();j++){
			vetorAtual=vetor[j];
			for(int i=0;i<vetorAtual.size();i++){			
				if(i==vetorAtual.size()-1){
					std::cout << vetorAtual[i];
				}else{
					std::cout << vetorAtual[i] << " , ";
				}
			}
			std::cout << "\n";
		}
	}
};
