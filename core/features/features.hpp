#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../variables.hpp"
#include "../features/features.hpp"
#pragma once
#include <windows.h>
#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <array>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <intrin.h>
#include <filesystem>

#include "../dependencies/"

#include "../dependencies/utilities/singleton.hpp"
#include "../dependencies/utilities/fnv.hpp"
#include "../dependencies/utilities/utilities.hpp"
#include "../dependencies/minhook/minhook.h"
#include "../dependencies/interfaces/interfaces.hpp"
#include "../source-sdk/sdk.hpp"
#include "../../core/hooks/hooks.hpp"
#include "../dependencies/math/math.hpp"
#include "../dependencies/utilities/renderer/renderer.hpp"
#include "../dependencies/utilities/console/console.hpp"
#include "../dependencies/utilities/csgo.hpp"

namespace misc {
	namespace movement {
		void bunny_hop(c_usercmd* cmd);
	};
}

class WRAGEBOT
{	
public:
	static bool ragebot(c_usercmd* cmd);
	static void doaim(c_usercmd* cmd);
	static void antiaim(c_usercmd* cmd);
	static void safepoint(c_usercmd* cmd);
	static bool hitchance(player_t* player, weapon_t* weapon, vec3_t angle, int chance);
	static void mindmg(c_usercmd* cmd);
	static void fixpvs();
	static void animfix();
	static bool bone_visible(player_t* player, int bone);
	static void autopistol(c_usercmd* cmd);
	static vec3_t hitbox(player_t* player, int mode, c_usercmd* cmd);
	static void Run(c_usercmd* cmd);
};

void hitlogs(i_game_event* event);

void antiflash();

void rcs(c_usercmd* cmd, vec3_t& angles);

void esp(i_game_event* event = nullptr) noexcept;

void boneesp();

void aimbot(c_usercmd* cmd);

void bombesp();

void chams(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix);

void thirdperson();

void bombesp();

void clantag();

void crosshair();

void antiaim(c_usercmd* cmd);

void Fov();

void log(c_usercmd* cmd);

void ragebot(c_usercmd* user_cmd);

void watermark();

void triggerbot(c_usercmd* cmd);

void knifehandFlip();

void spreadxhair();

namespace cfg
{
	void run(const char* name);

	void load(size_t id);

	void save(size_t id);

	bool add(const char* name);

	void remove(size_t id);

	void rename(size_t item, const char* newName);

	void reset();
	
}

void dropped_weapons();

void dispatch_logs();

void keystroke_display();