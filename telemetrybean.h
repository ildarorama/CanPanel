#ifndef MAINWINDOWSTATE_H
#define MAINWINDOWSTATE_H


class TelemetryBean
{
public:
    TelemetryBean(double x,double y,double z,double a,double b,double c);
    double a();
    double b();
    double c();
    double x();
    double y();
    double z();
private:
    double _x,_y,_z,_a,_b,_c;
};

#endif // MAINWINDOWSTATE_H
