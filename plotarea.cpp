#include "plotarea.h"

PlotArea::PlotArea(QWidget *parent) :
    QGraphicsView(parent)    
{
    this->contador=0;
}

void PlotArea::novoVetorEDesenha(){
    if(contador<this->todosVetores.size()){
        this->vetorAtual=todosVetores.at(contador);
        this->contador++;
        update();
    }

}

void PlotArea::setEscala(){
    int Nvetores = this->todosVetores.size();
    std::vector<QPoint> atual;

    double xLi=this->todosVetores.at(0).at(0).x();
    double xUi=this->todosVetores.at(0).at(0).x();
    double yLi=this->todosVetores.at(0).at(0).y();
    double yUi=this->todosVetores.at(0).at(0).y();

    for(int j=0;j<Nvetores;j++){
        atual=this->todosVetores.at(j);
        for(int i=0;i<atual.size();i++){
           if(atual.at(i).x()<xLi){
               xLi=atual.at(i).x();
           }
           if(atual.at(i).x()>xUi){
               xUi=atual.at(i).x();
           }
           if(atual.at(i).y()<yLi){
               yLi=atual.at(i).y();
           }
           if(atual.at(i).y()>yUi){
               yUi=atual.at(i).y();
           }
        }
    }

    for(int i=0;i<this->perfil.size();i++){
       if(this->perfil.at(i).x()<xLi){
           xLi=this->perfil.at(i).x();
       }
       if(this->perfil.at(i).x()>xUi){
           xUi=this->perfil.at(i).x();
       }
       if(this->perfil.at(i).y()<yLi){
           yLi=this->perfil.at(i).y();
       }
       if(this->perfil.at(i).y()>yUi){
           yUi=this->perfil.at(i).y();
       }
    }

    this->dX = niceTicks(xLi,xUi,6);
    this->xL = dX*floor(xLi/dX);
    this->xU = dX*round(xUi/dX);

    this->dY = niceTicks(yLi,yUi,6);
    this->yL = dY*floor(yLi/dY);
    this->yU = dY*round(yUi/dY);
}

void PlotArea::setTodosVetores(std::vector<std::vector<QPoint> > todosVetores){
    this->contador=0;
    this->todosVetores=todosVetores;
    this->vetorAtual=todosVetores.at(0);
}
void PlotArea::setVetorAtual(){
    if (todosVetores.size()>1){
        this->vetorAtual=todosVetores.at(1);
    }else{
        this->vetorAtual=todosVetores.at(0);
    }
}

void PlotArea::proximoVetor(){
    this->contador++;
    this->vetorAtual=todosVetores.at(contador);

}

void PlotArea::setPerfil(std::vector<QPoint> perfil){
    this->perfil=perfil;
}

double PlotArea::niceTicks(double xL, double xU, int N){
    double range = (xU-xL)/(N-1);
    double expoente = ceil(log10(range)-1);
    double potencia = pow(10,expoente);
    double arredondado = ceil(range/potencia)*potencia;
    return arredondado;
}

void desenhaEtiqueta(QPainter* painter, QPointF, QString texto, QRectF retangulo){
    painter->drawText(retangulo,texto,Qt::AlignHCenter | Qt::AlignVCenter);
}

void desenhaEtiquetaVertical(QPainter* painter, QPointF ponto, QString texto, QRectF retangulo){
    painter->translate(ponto);
    painter->rotate(-90);
    painter->drawText(retangulo,texto,Qt::AlignHCenter | Qt::AlignVCenter);
    painter->rotate(90);
    painter->restore();
}

QPointF traduzPonto(QPointF P, QPointF O,double pixelsX,double pixelsY,double xL, double yL,double rangeX, double rangeY){
    double fatorX=pixelsX/rangeX;
    double fatorY=pixelsY/rangeY;
    return QPointF(O.x()+(P.x()-xL)*fatorX,O.y()-(P.y()-yL)*fatorY);
}

void drawRotatedText(QPainter *painter, float degrees, int x, int y, const QString &text)
  {
    painter->save();
    painter->translate(x, y);
    painter->rotate(degrees);
    painter->drawText(0, 0, text);
    painter->restore();
  }


void PlotArea::paintEvent(QPaintEvent *event){

    //Janela

    int tamanhoJanelaX = this->size().width();
    int tamanhoJanelaY = this->size().height();

    int folgaX_E=80;
    int folgaX_D=30;
    int folgaY_C=30;
    int folgaY_B=60;

    int tamanhoAreaX = tamanhoJanelaX-folgaX_E-folgaX_D;
    int tamanhoAreaY = tamanhoJanelaY-folgaY_C-folgaY_B;

    int deltaX = ceil(tamanhoAreaX/5);
    int deltaY = ceil(tamanhoAreaY/5);

    QPointF origem(folgaX_E,folgaY_C+tamanhoAreaY);
    QPointF marcaHorizontal1;
    QPointF marcaHorizontal2;
    QPointF marcaVertical1;
    QPointF marcaVertical2;
    QPointF etiquetaHorizontal;
    QPointF etiquetaVertical;
    QPointF legendaX(folgaX_E+tamanhoAreaX/2,tamanhoJanelaY-10);
    QPointF legendaY(0,folgaY_C+(tamanhoAreaY+folgaY_C+folgaY_B)/2);


    QPainter Painter(this->viewport());
    QBrush pincelBranco(Qt::white);
    QPen canetaCinza(Qt::lightGray);
    canetaCinza.setStyle(Qt::DotLine);
    QPen canetaPreta(Qt::black);
    QPen canetaAzul(Qt::blue);

    Painter.setPen(canetaPreta);

    QRectF eixos(folgaX_E,folgaY_C,tamanhoAreaX,tamanhoAreaY);

    Painter.drawRect(eixos);
    Painter.fillRect(QRectF(folgaX_E+1,folgaY_C+1,tamanhoAreaX-1,tamanhoAreaY-1),pincelBranco);

    //Escala e eixos

    setEscala();

    double dX = this->dX;
    double xL = this->xL;
    double xU = this->xU;

    double dY = this->dY;
    double yL = this->yL;
    double yU = this->yU;

    //Plotagem

    QRectF retanguloEtiquetasH;
    QRectF retanguloEtiquetasV;
    QRectF retanguloLegendaX;
    QRectF retanguloLegendaY;

    for (int i=0;i<6;i++){

        //Linhas
        Painter.setPen(canetaCinza);

        if(i!=0 && i!=5){
            marcaHorizontal1.setX(origem.x()+deltaX*i);
            marcaHorizontal1.setY(origem.y());
            marcaHorizontal2.setX(origem.x()+deltaX*i);
            marcaHorizontal2.setY(origem.y()-tamanhoAreaY+1);

            marcaVertical1.setX(origem.x());
            marcaVertical1.setY(origem.y()-deltaY*i);
            marcaVertical2.setX(origem.x()+tamanhoAreaX-1);
            marcaVertical2.setY(origem.y()-deltaY*i);

            Painter.drawLine(QLineF(marcaHorizontal1,marcaHorizontal2));
            Painter.drawLine(QLineF(marcaVertical1,marcaVertical2));
        }

        //Marcas

        Painter.setPen(canetaPreta);

        marcaHorizontal1.setX(origem.x()+deltaX*i);
        marcaHorizontal1.setY(origem.y());
        marcaHorizontal2.setX(origem.x()+deltaX*i);
        marcaHorizontal2.setY(origem.y()+10);

        marcaVertical1.setX(origem.x());
        marcaVertical1.setY(origem.y()-deltaY*i);
        marcaVertical2.setX(origem.x()-10);
        marcaVertical2.setY(origem.y()-deltaY*i);

        Painter.drawLine(QLineF(marcaHorizontal1,marcaHorizontal2));
        Painter.drawLine(QLineF(marcaVertical1,marcaVertical2));

        //Etiquetas

        etiquetaHorizontal.setX(marcaHorizontal1.x());
        etiquetaHorizontal.setY(marcaHorizontal1.y()+25);
        etiquetaVertical.setX(marcaVertical2.x()-15);
        etiquetaVertical.setY(marcaVertical2.y());

        retanguloEtiquetasH.setCoords(etiquetaHorizontal.x()-tamanhoAreaX/2,etiquetaHorizontal.y()-tamanhoAreaY/2,etiquetaHorizontal.x()+tamanhoAreaX/2,etiquetaHorizontal.y()+tamanhoAreaY/2);
        retanguloEtiquetasV.setCoords(etiquetaVertical.x()-tamanhoAreaX/2,etiquetaVertical.y()-tamanhoAreaY/2,etiquetaVertical.x()+tamanhoAreaX/2,etiquetaVertical.y()+tamanhoAreaY/2);

        desenhaEtiqueta(&Painter, etiquetaHorizontal, QString::number(xL+i*dX), retanguloEtiquetasH);
        desenhaEtiqueta(&Painter, etiquetaVertical, QString::number(yL+i*dY), retanguloEtiquetasV);
        //Painter.drawText(etiquetaHorizontal,QString::number(xL+i*dX));
        //Painter.drawText(etiquetaVertical,QString::number(yL+i*dY));


    }
    Painter.save();
    retanguloLegendaX.setCoords(legendaX.x()-tamanhoAreaX/2,legendaX.y()-tamanhoAreaY/2,legendaX.x()+tamanhoAreaX/2,legendaX.y()+tamanhoAreaY/2);
    desenhaEtiqueta(&Painter,legendaX,"Pontos do trecho",retanguloLegendaX);
    retanguloLegendaY.setCoords(legendaY.x()-tamanhoAreaX/2,legendaY.y()-tamanhoAreaY/2,legendaY.x()+tamanhoAreaX/2,legendaY.y()+tamanhoAreaY/2);
    drawRotatedText(&Painter,-90,legendaY.x()+20,legendaY.y(),"Linha piezométrica (m)");
    Painter.drawEllipse(origem,10,10);

    //Pontos do grafico

    QPointF P1;
    QPointF P2;

    double rangeX = xU-xL;
    double rangeY = yU-yL;

    Painter.setPen(canetaAzul);

    for(int i=1;i<this->vetorAtual.size();i++){
        P1 = traduzPonto(this->vetorAtual.at(i-1),origem,tamanhoAreaX,tamanhoAreaY,xL,yL,rangeX,rangeY);
        if(i>0){
            P2 = traduzPonto(this->vetorAtual.at(i),origem,tamanhoAreaX,tamanhoAreaY,xL,yL,rangeX,rangeY);
        }
        Painter.drawLine(P1,P2);
    }

    Painter.setPen(canetaPreta);

    for(int i=1;i<this->vetorAtual.size();i++){
        P1 = traduzPonto(this->perfil.at(i-1),origem,tamanhoAreaX,tamanhoAreaY,xL,yL,rangeX,rangeY);
        if(i>0){
            P2 = traduzPonto(this->perfil.at(i),origem,tamanhoAreaX,tamanhoAreaY,xL,yL,rangeX,rangeY);
        }
        Painter.drawLine(P1,P2);
    }


}
