#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "framework.hpp"
#include "../variables.hpp"

namespace menu {
	inline int current_tab{ 0 };
	inline int weapon_current_tab{ 0 };
	inline int rage_weapon_current_tab{ 0 };
	inline int visuals_current_tab{ 0 };
	inline int misc_current_tab{ 0 };
	void render();
	void toggle();
};

void featureToggle();