class Reservatorio : public PontoHQ{
private:
	double yLam; //Altura relativa ao chao
public:
	Reservatorio(double yLam);
	void setHR();
	void novaIteracao(double t);
};
