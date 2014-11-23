class ValvulaDeRetencao : public PontoHQ{
private:
	bool fechada;
public:
	ValvulaDeRetencao();
	void novaIteracao(double dt);
};
