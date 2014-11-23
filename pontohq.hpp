class PontoHQ: public Ponto{
protected:
	double HR;
	double QR;
	double UR;
	double HE;
	double QE;
	double HD;
	double QD;
	double Z;
	// Geometria
	double dL;
	double D;
	// Físicos
	double f;
	double a;
	double T;
	// Método numérico
	double dt;
	double B;
	double R;
	double HEnovo;
	double QEnovo;
	double HDnovo;
	double QDnovo;
public:
	PontoHQ();
	void setZ(double Z);
	void setHE(double H);
	void setQE(double Q);
	void setB(double B);
	void setR(double R);
	void seta(double a);
	void setdt(double dt);
	void setT(double T);
	virtual void setHR();
	void setQR(double Q);
	void setUR(double U);
	double getHE();
	double getQE();
	void setHD(double H);
	void setQD(double Q);
	double getHD();
	double getQD();
	double getZ();
	virtual void novaIteracao(double t);
	virtual void ajustesPerfilInicial(double H);
	void substituiValores();
};
