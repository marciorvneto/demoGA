#include "doubleslider.h"

/*DoubleSlider::DoubleSlider(QWidget *parent) :
    QSlider(parent)
{

}*/
void DoubleSlider::notifyDoubleValueChanged(int v)
{
    double value=this->xL+(v-1)*(this->xU-this->xL)/100;
    this->valor=value;
    emit doubleValueChanged(value);
}
void DoubleSlider::calculaValor(int v){
    double value=this->xL+(v-1)*(this->xU-this->xL)/100;
    this->valor=value;
}
