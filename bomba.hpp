class Bomba : public PontoHQ{
private:
	double alfa;
	double beta;
	double v;
	double h;

	double WR2;
	double NR;
	double etaR;
	double ENAPS;

	double A;
	double B;
	double C;

	void atualizaParametros();
public:
	Bomba(double A, double B, double C,double WR2,double NR,double etaR,double ENAPS);
	void setHR();
	void novaIteracao(double t);
};
