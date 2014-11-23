class TAU : public PontoHQ{
private:
	double D;
	double A;
	double y;
	double ke;
	double ks;

	double QTAU;
	double HTAU;

	std::vector<double> vetorY;
public:
	TAU(double D, double y,double ke,double ks);
	void novaIteracao(double t);
	void calculosTAU(double CP, double CM, double BP, double BM);
	void grita();
	void ajustesPerfilInicial(double H);
};
