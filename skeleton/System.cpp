#include "System.h"
System::System(Scene* scene) : scene(scene) {}
System::~System() {
	auto it = entities.begin();
	while (it != entities.end()) {
		auto itAux = it; //hacerlo con un iterador auxiliar, por si se invalida durante el bucle (por borrarlo)
		++it;
		(*itAux)->die();
	}
}
void System::update(double t) {
	refresh();
	auto it = entities.begin();
	while (it != entities.end()) {
		auto itAux = it; //hacerlo con un iterador auxiliar, por si se invalida durante el bucle (por borrarlo)
		++it;
		(*itAux)->update(t);
	}
}


void System::refresh() {
	entities.erase(
		std::remove_if(entities.begin(), entities.end(),
			[](Entity* e) {
				if (e->isAlive()) {
					return false;
				}
				else {
					e->die();
					return true;
				}
			}),
		entities.end());
}

void System::addEntity(Entity* e) {
	entities.push_back(e);
}