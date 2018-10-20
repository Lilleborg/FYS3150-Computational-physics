#include "celestialbody.h"

CelestialBody::CelestialBody(vec3 pos, vec3 vel, double mass_) {
    position = pos;
    velocity = vel;
    mass = mass_;
}

void CelestialBody::resetForce() {
    force.zeros();
}
