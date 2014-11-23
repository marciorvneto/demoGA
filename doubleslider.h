#ifndef DOUBLESLIDER_H
#define DOUBLESLIDER_H

#include <QWidget>
#include <QSlider>

class DoubleSlider : public QSlider
{
    Q_OBJECT
public:

    explicit DoubleSlider(QWidget *parent = 0){
        connect(this, SIGNAL(valueChanged(int)),this, SLOT(notifyDoubleValueChanged(int)));
    }
    double valor;
    double xU;
    double xL;
    void calculaValor(int v);
signals:
    void doubleValueChanged(double value);
public slots:
    void notifyDoubleValueChanged(int value);

};

#endif // DOUBLESLIDER_H
