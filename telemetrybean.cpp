#include "telemetrybean.h"

TelemetryBean::TelemetryBean(double x,double y,double z,double a,double b,double c) :
    _a(a),
    _b(b),
    _c(c),
    _x(x),
    _y(y),
    _z(z)
{

}

double TelemetryBean::x() {
    return _x;
}

double TelemetryBean::y() {
    return _y;
}

double TelemetryBean::z() {
    return _z;
}

double TelemetryBean::a() {
    return _a;
}

double TelemetryBean::b() {
    return _b;
}

double TelemetryBean::c() {
    return _c;
}
