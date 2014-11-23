class Valvula : public PontoHQ{
private:
	double m;
	double tc;
	double Hv;
	bool fechando;
public:
	Valvula(double tc, double m,double Hv,bool fechando);
	void setHR();
	void novaIteracao(double t);
};
