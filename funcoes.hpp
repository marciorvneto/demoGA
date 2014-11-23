#ifndef FUNCOES_HPP
#define FUNCOES_HPP

inline double roAgua(double T){
    return -0.0049*std::pow(T,2)+0.0045*T+999.99;
}

inline double epsAgua(double T){
    return 1e9*(-0.0001*std::pow(T,2)+0.0125*T+2.0329);
}

inline double tauValvula(double t,double tc,double m,bool fechando){
    if(fechando){
        return std::max(0.0,std::pow(1-t/tc,m));
    }else{
        return std::min(1.0,std::pow(t/tc,m));
    }
}

inline double pressaoAtmosferica(double Z){
    return 10.33-0.0012*Z;
}

#endif
