class Ponto{
private:
	int indice;
	Ponto* E;
	Ponto* D;
	bool temE;
	bool temD;	
public:
	Ponto();
	virtual ~Ponto();
	void setIndice(int i);
	void setEsquerda(Ponto* E);
	void setDireita(Ponto* D);
	Ponto* getEsquerda();
	Ponto* getDireita();
	int getIndice();
	bool temEsquerda();
	bool temDireita();
};
