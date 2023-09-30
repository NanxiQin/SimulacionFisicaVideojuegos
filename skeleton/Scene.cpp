#include "Scene.h"

Scene::~Scene() {
	for (auto e : entities) delete e;
}
void Scene::update(double t) {

	auto it = entities.begin();
	while (it != entities.end()) {
		auto itAux = it; //hacerlo con un iterador auxiliar, por si se invalida durante el bucle (por borrarlo)
		++it;
		(*itAux)->update(t);
	}
}

void Scene::addEntity(Entity* e) {
	entities.push_back(e);
}