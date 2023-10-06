#pragma once

#include "Entity.h"
#include "System.h"
#include "game_def.h"
#include <array>

using namespace std;
using namespace game_def;
class Manager {
private:
	array<Entity*, maxHdlrId> hdlrs_;
	array<System*, maxSystemId> sys_;
	array<vector<Entity*>, maxGroupId> entsByGroup_;
public:
	Manager();
	virtual ~Manager();


#pragma region ENTIDAD
	inline void removeAllEntities() {
		for (auto& ents : entsByGroup_) {
			for (auto e : ents)
				e->setAlive(false);
		}
	}
	Entity* addEntity(grpId gId = _grp_GENERAL);
	const auto& getEntities(grpId gId = _grp_GENERAL);
	void refresh();

	inline void setHandler(hdlrId_type hId, Entity* e) {
		hdlrs_[hId] = e;
	}
	inline Entity* getHandler(hdlrId_type hId) {
		return hdlrs_[hId];
	}
	inline std::vector<Entity*>* getGroup(grpId grp) { return &entsByGroup_[grp]; }
#pragma endregion

#pragma region SISTEMA
	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&... args) {
		constexpr sysId_type sId = T::id;
		removeSystem<T>();
		System* s = new T(std::forward<Ts>(args)...);
		s->setContext(this);
		s->initSystem();
		sys_[sId] = s;
		return static_cast<T*>(s);
	}
	template<typename T>
	inline T* getSystem() {
		constexpr sysId_type sId = T::id;
		return static_cast<T*>(sys_[sId]);
	}
	template<typename T>
	inline void removeSystem() {
		constexpr sysId_type sId = T::id;
		if (sys_[sId] != nullptr) {
			delete sys_[sId];
			sys_[sId] = nullptr;
		}
	}

#pragma endregion



};
