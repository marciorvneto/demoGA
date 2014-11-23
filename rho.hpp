class RHO : public PontoHQ{
private:
	double D;
	double A;
	double V;
	double y;
	double ke;
	double ks;
	double P;
	double gama;

	double QRHO;
	double HRHO;

	std::vector<double> vetorY;
public:
	RHO(double D, double V0, double y,double ke,double ks);
	void novaIteracao(double t);
	void calculosRHO(double CP, double CM, double BP, double BM, bool saindo);
	void grita();
	void ajustesPerfilInicial(double H);
};
