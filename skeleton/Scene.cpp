#include "Scene.h"


Scene::Scene() {
	mngr_ = new Manager();
};
Scene::~Scene() {
	for (auto e : entities) delete e;

	delete mngr_;
	systems.clear();
}

void Scene::addSystem(System* s) {
	systems.push_back(s);
}


void Scene::update(double t) {
	for (auto s : systems)s->update(t);

	//auto it = entities.begin();
	//while (it != entities.end()) {
	//	auto itAux = it; //hacerlo con un iterador auxiliar, por si se invalida durante el bucle (por borrarlo)
	//	++it;
	//	(*itAux)->update(t);
	//}
}

void Scene::addEntity(Entity* e) {
	entities.push_back(e);
}