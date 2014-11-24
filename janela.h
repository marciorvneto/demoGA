#ifndef JANELA_H
#define JANELA_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <cmath>
#include <iostream>

#include "headers.hpp"

namespace Ui {
class Janela;
}

class Janela : public QMainWindow
{
    Q_OBJECT

public:
    explicit Janela(QWidget *parent = 0);
    ~Janela();
    std::vector<QPoint> converteDoubleQPoint(std::vector<double> x,std::vector<double> y);
    std::vector<std::vector<QPoint> > converteTodasIteracoes(std::vector<double> x,std::vector<std::vector<double> > y);

private:
    Ui::Janela *ui;
    QGraphicsScene *cena;

    double WR2;
    double QR;
    double tempoSimulacao;

    int dispositivo;
    int material;
    int pontoDispositivo;

    QTimer* timer;
    std::vector<std::vector<QPoint> > todosVetores;
    std::vector<QPoint> vetor;

    Reservatorio* R;
    Bomba* B;
    PontoHQ* D;
    Tubo* T;

public slots:
    void atualizaParametros();
    void rodaSimulacao();
    void paraSimulacao();
    void abreAjuda();

};

#endif // JANELA_H
