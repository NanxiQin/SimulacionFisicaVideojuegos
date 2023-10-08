#include "Scene.h"

Scene::~Scene() {
	for (auto s : systems)delete s;
	systems.clear();
}
void Scene::update(double t) {
	for (auto s : systems)s->update(t);

}
void Scene::addSystem(System* s) {
	systems.push_back(s);
}
void Scene::keyPress(unsigned char key, const PxTransform& camera) {
	for (auto s : systems)s->keyPress(key,camera);
 }