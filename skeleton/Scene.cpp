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
void Scene::keyPress(unsigned char key) {
	for (auto s : systems)s->keyPress(key);
 }

void Scene::keyRelease(unsigned char key)
{
	for (auto s : systems)s->keyRelease(key);
}

void Scene::handleMouse(int button, int state, int x, int y)
{
	for (auto s : systems)s->handleMouse(button,state, x,y);
}

void Scene::handleMotion(int x, int y)
{
	for (auto s : systems)s->handleMotion(x,y);
}

