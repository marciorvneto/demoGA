#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QWidget>
#include <QGraphicsView>
#include <cmath>

class PlotArea : public QGraphicsView
{
    Q_OBJECT
private:
    double dX;
    double xL;
    double xU;
    double dY;
    double yL;
    double yU;
    std::vector<std::vector<QPoint> > todosVetores;
    std::vector<QPoint> vetorAtual;
    std::vector<QPoint> perfil;
    std::vector<QPoint> envoltoriaMax;
    std::vector<QPoint> envoltoriaMin;
    int contador;
public:
    explicit PlotArea(QWidget *parent = 0);
    void setTodosVetores(std::vector<std::vector<QPoint> > todosVetores);
    void setVetorAtual();
    void proximoVetor();
    void setPerfil(std::vector<QPoint>);
    void setEscala();
    void envoltorias(std::vector<double>);
    double niceTicks(double xL, double xU, int N);
    bool desenhaEnvoltorias;

signals:

public slots:
    void novoVetorEDesenha();
    void desenharEnvoltorias();

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // PLOTAREA_H
