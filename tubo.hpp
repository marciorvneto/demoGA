//#include "material.cpp"
class Tubo{
private:
	Material M;
	double e;
	double L;
	double D;
	double T;
public:
	Tubo(Material M ,double L ,double e,double D);
	void setT(double T);
	double getL();
	double gete();
	double getD();
	double getA();
	double geta();
	double getT();
};
