#include "celestialbody.h"

CelestialBody::CelestialBody(vec3 pos, vec3 vel, double mass_, string obname) {
    position = pos;
    velocity = vel;
    mass = mass_;
    name = obname;
}

void CelestialBody::resetForce() {
    force.zeros();
}
