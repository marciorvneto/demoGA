class Material{
protected:
	double E;
	double u;
	double c1;
public:
	double getE();
	double getu();
	double getc1();	
};

class PVC : public Material{
public:
	PVC();
};

class Aco : public Material{
public:
	Aco();
};

class FerroFundido : public Material{
public:
	FerroFundido();
};

class FerroDuctil : public Material{
public:
	FerroDuctil();
};
