#include "janela.h"
#include "ui_janela.h"

#include "tubo.cpp"
#include "material.cpp"

#include "ponto.cpp"
#include "pontohq.cpp"
#include "che.cpp"
#include "rho.cpp"
#include "tau.cpp"
#include "valvuladeretencao.cpp"
#include "ventosa.cpp"

#include "bomba.cpp"
#include "reservatorio.cpp"

Janela::Janela(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Janela)
{
    ui->setupUi(this);

    cena = new QGraphicsScene(this);
    ui->graphicsView->setScene(cena);
    ui->graphicsView->setStyleSheet("background: transparent");

    timer = new QTimer(this);

    //Inicializacao

    //connect(timer,SIGNAL(timeout()),this->ui->graphicsView,SLOT(atualizaGrafico()));

    connect(ui->slider_WR2,SIGNAL(doubleValueChanged(double)),this,SLOT(atualizaParametros()));
    connect(ui->slider_Vazao,SIGNAL(doubleValueChanged(double)),this,SLOT(atualizaParametros()));
    connect(ui->slider_Tempo,SIGNAL(doubleValueChanged(double)),this,SLOT(atualizaParametros()));
    connect(ui->spinBox_Posicao,SIGNAL(valueChanged(int)),this,SLOT(atualizaParametros()));
    connect(ui->comboBox_Dispositivos,SIGNAL(currentIndexChanged(int)),this,SLOT(atualizaParametros()));
    connect(ui->comboBox_Material,SIGNAL(currentIndexChanged(int)),this,SLOT(atualizaParametros()));

    connect(ui->pushButton_Rodar,SIGNAL(clicked()),this,SLOT(rodaSimulacao()));
    connect(ui->pushButton_Parar,SIGNAL(clicked()),this,SLOT(paraSimulacao()));

    //Etiquetas

    ui->slider_WR2->xU=1.0;
    ui->slider_WR2->xL=0.01;
    connect(ui->slider_WR2,SIGNAL(doubleValueChanged(double)),ui->label_valor_WR2,SLOT(setNum(double)));

    ui->slider_Vazao->xU=2;
    ui->slider_Vazao->xL=0.1;
    connect(ui->slider_Vazao,SIGNAL(doubleValueChanged(double)),ui->label_valor_Q,SLOT(setNum(double)));

    ui->slider_Tempo->xU=600;
    ui->slider_Tempo->xL=20;
    connect(ui->slider_Tempo,SIGNAL(doubleValueChanged(double)),ui->label_valor_Tempo,SLOT(setNum(double)));

    //Valores

    ui->slider_WR2->calculaValor(50);
    ui->slider_Vazao->calculaValor(50);
    ui->slider_Tempo->calculaValor(50);

    WR2 = ui->slider_WR2->valor;
    tempoSimulacao = ui->slider_Tempo->valor;
    QR = ui->slider_Vazao->valor;

    pontoDispositivo=ui->spinBox_Posicao->value();
    dispositivo=ui->comboBox_Dispositivos->currentIndex();
    material=ui->comboBox_Material->currentIndex();

    ui->label_valor_WR2->setNum(WR2);
    ui->label_valor_Q->setNum(QR);
    ui->label_valor_Tempo->setNum(tempoSimulacao);

    this->atualizaParametros();

    vetor.push_back(QPoint(0,0));
    vetor.push_back(QPoint(12000,0));

    todosVetores.push_back(vetor);
    this->ui->graphicsView->setTodosVetores(todosVetores);

    this->ui->graphicsView->setVetorAtual();
    this->ui->graphicsView->setEscala();
    this->ui->graphicsView->setPerfil(vetor);

}

void Janela::atualizaParametros(){
    this->WR2=this->ui->slider_WR2->valor;
    this->QR=this->ui->slider_Vazao->valor;
    this->tempoSimulacao=this->ui->slider_Tempo->valor;
    this->material=this->ui->comboBox_Material->currentIndex();
    this->dispositivo=this->ui->comboBox_Dispositivos->currentIndex();
    this->pontoDispositivo=this->ui->spinBox_Posicao->value();
}

void Janela::rodaSimulacao(){
    int Niter;
    double D=0.6;
    double L=12000;

    std::vector<double> x;
    std::vector<double> z;
    std::vector<std::vector<double> > todasIteracoes;
    std::vector<std::vector<QPoint> > todasIteracoesQPoint;
    std::vector<QPoint> perfil;


    switch(this->material){
    case 0:
        T=new Tubo(Aco(),L,7.7e-3,D);
    case 1:
        T=new Tubo(FerroFundido(),L,7.7e-3,D);
    case 2:
        T=new Tubo(FerroDuctil(),L,7.7e-3,D);
    case 3:
        T=new Tubo(PVC(),L,7.7e-3,D);
    }

    for(int i=0;i<20;i++){
        //x.push_back(i*L/20);
        x.push_back(i);
    }

    z.push_back(647);
    z.push_back(647);
    z.push_back(650);
    z.push_back(630);
    z.push_back(660);
    z.push_back(658);
    z.push_back(687);
    z.push_back(674);
    z.push_back(682);
    z.push_back(669);
    z.push_back(673);
    z.push_back(667);
    z.push_back(685);
    z.push_back(680);
    z.push_back(697);
    z.push_back(692);
    z.push_back(712);
    z.push_back(677);
    z.push_back(703);
    z.push_back(698);
//    z.push_back(711);
//    z.push_back(712);
//    z.push_back(711);
//    z.push_back(714);
//    z.push_back(717);

    perfil=converteDoubleQPoint(x,z);

    Bomba* Bom = new Bomba(-168.0,63.0,245.0,this->WR2,1750,0.75,647);
    Reservatorio* Res = new Reservatorio(5);

    Malha<PontoHQ> M;
    M.fazMalha(20);
    M.setPerfil(z);
    M.setTubo(T);

    M.substituiPonto(Bom,0);
    M.substituiPonto(Res,19);

    if(this->dispositivo!=0){
        if(this->dispositivo==1){
            CHE* C = new CHE(2,100,100);
            M.substituiPonto(C,this->pontoDispositivo);
        }
        if(this->dispositivo==2){
            RHO* R = new RHO(2,5,5,100,100);
            M.substituiPonto(R,this->pontoDispositivo);
        }
        if(this->dispositivo==3){
            TAU* T = new TAU(2,5,100,100);
            M.substituiPonto(T,this->pontoDispositivo);
        }
        if(this->dispositivo==4){
            ValvulaDeRetencao* VR = new ValvulaDeRetencao();
            M.substituiPonto(VR,this->pontoDispositivo);
        }
        if(this->dispositivo==5){
            Ventosa* V = new Ventosa();
            M.substituiPonto(V,this->pontoDispositivo);

        }        
    }

    M.setQR(this->QR);
    M.inicializaMalha();
    todasIteracoes=M.salvaItera(this->tempoSimulacao);

    todasIteracoesQPoint=this->converteTodasIteracoes(x,todasIteracoes);
    this->ui->graphicsView->setTodosVetores(todasIteracoesQPoint);

    this->ui->graphicsView->setEscala();
    this->ui->graphicsView->setPerfil(perfil);
    this->ui->graphicsView->setVetorAtual();


    timer->setInterval(100);
    connect(timer,SIGNAL(timeout()),this->ui->graphicsView,SLOT(novoVetorEDesenha()));
    /*for(int i=0;i<todasIteracoesQPoint.size()-50;i++){
        timer
        this->ui->graphicsView->proximoVetor();
        this->ui->graphicsView->repaint();
        //sleep_for(50);
        //QTimer::singleShot(500,this->ui->graphicsView,SLOT(repaint()));


    }*/
    timer->start();

}

void Janela::paraSimulacao(){
    timer->stop();
}

std::vector<QPoint> Janela::converteDoubleQPoint(std::vector<double> x,std::vector<double> y){
    std::vector<QPoint> convertido;
    for(int i=0;i<x.size();i++){
        QPoint novoQPoint = QPoint(x[i],y[i]);
        convertido.push_back(novoQPoint);
    }
    return convertido;

}

std::vector<std::vector<QPoint> > Janela::converteTodasIteracoes(std::vector<double> x,std::vector<std::vector<double> > y){
    std::vector<std::vector<QPoint> > todas;
    std::vector<QPoint> atual;
    for(int i=0;i<y.size();i++){
        atual=converteDoubleQPoint(x,y[i]);
        todas.push_back(atual);
    }
    return todas;
}

Janela::~Janela()
{
    delete ui;
}
