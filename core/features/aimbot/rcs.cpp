#include "../features.hpp"

void rcs(c_usercmd* cmd, vec3_t& angles)
{
	if (variables::aimbots::legit::rcs == true)
	{
		if (!interfaces::engine->is_in_game())
			return;
		
		if (!csgo::local_player->is_alive())
			return;

		if (csgo::local_player == nullptr)
			return;

		const auto weapon_type = csgo::local_player->active_weapon()->get_weapon_data()->weapon_type;

		if (weapon_type == NULL)
			return;

		if (weapon_type == WEAPONTYPE_RIFLE || weapon_type == WEAPONTYPE_SUBMACHINEGUN)
		{
			static vec3_t old_punch{ 0, 0, 0 };
			auto scale = interfaces::console->get_convar("weapon_recoil_scale");
			auto punch = csgo::local_player->aim_punch_angle() * 2;

			punch.x *= variables::aimbots::legit::rcs_x;
			punch.y *= variables::aimbots::legit::rcs_y;

			auto rcs_angle = cmd->viewangles += (old_punch - punch);
			interfaces::engine->set_view_angles(rcs_angle);

			angles.clamp();
			angles.normalize();

			old_punch = punch;
		}
	}
}