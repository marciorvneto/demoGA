class CHE : public PontoHQ{
// ks e ke nao implementados
private:
	double D;
	double A;
	double y;
	double ke;
	double ks;

	double gama;

	double QCHE;
	double HCHE;

	std::vector<double> vetorY;
public:
	CHE(double D, double ke,double ks);
	void novaIteracao(double t);
	void calculosCHE(double CP, double CM, double BP, double BM, bool saindo);
	void grita();
	void ajustesPerfilInicial(double H);
};
