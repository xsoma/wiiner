#include "../features.hpp"
#include "../rage/backtrack.h"
#include <cmath>

std::string clean_item_name(std::string name)
{

	std::string Name = name;

	auto weapon_start = Name.find("weapon");
	if (weapon_start != std::string::npos)
		Name.erase(Name.begin() + weapon_start, Name.begin() + weapon_start + 6);

	if (Name[0] == '_')
		Name.erase(Name.begin());

	if (Name[0] == 'c') //optional for dropped weapons - designer
		Name.erase(Name.begin());

	return Name;
}

void esp(i_game_event* event) noexcept /* I just draw all player esp in this function because why not */
{
	if (variables::Visuals::esp::espToggle == true && interfaces::engine->is_in_game()) /* Where esp is getting drawn */
	{
		if (interfaces::engine->is_in_game() == false)
			return;

		if (csgo::local_player == nullptr)
			return;

		for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++) /* Player loop */
		{

			if (interfaces::engine->is_in_game() == false)
				return;

			if (csgo::local_player == nullptr)
				return;

			auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));
			if (!pCSPlayer)
				continue;
			if (pCSPlayer == csgo::local_player)
				continue;
			if (pCSPlayer->dormant())
				continue;
			if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
				continue;

			vec3_t vecFoot;
			vec2_t vecScreen;
			vec2_t vecHeadScreen;
			vecFoot = pCSPlayer->origin();
			if (!(math::world_to_screen(vecFoot, vecScreen)))
				continue;

			vecFoot.z += 72.f;
			if (!(math::world_to_screen(vecFoot, vecHeadScreen)))
				continue;

			player_info_t playerinfo;
			interfaces::engine->get_player_info(iPlayer, &playerinfo);

			float alpha = pCSPlayer->flash_alpha();
			float time = pCSPlayer->flash_duration(); // need to make these update
			std::string flashtime = std::to_string(time);
			std::string flashAlpha = std::to_string(alpha);

			int h = vecScreen.y - vecHeadScreen.y;
			int w = (h / 2);
			int y = vecHeadScreen.y;
			int x = vecHeadScreen.x - w / 2;

			int healthh = vecScreen.y - vecHeadScreen.y;
			int healthw = 4;
			int healthy = vecHeadScreen.y;
			int healthx = vecHeadScreen.x - (h / 4 + 5);

			int armorh = vecScreen.y - vecHeadScreen.y;
			int armorw = 4;
			int armory = vecHeadScreen.y;
			int armorx = vecHeadScreen.x - (h / 4 + 11);

			int healthheight = h * (math::clamp_value<int>(pCSPlayer->health(), 0, 100) / 100.f) - (pCSPlayer->health() >= 100 ? 0 : -1);
			int armorheight = h * (math::clamp_value<int>(pCSPlayer->armor(), 0, 100) / 100.f) - (pCSPlayer->armor() >= 100 ? 0 : -1);

			color espclr;

			if (variables::Visuals::esp::hpoverridecheck && pCSPlayer->health() <= variables::colors::esp::hpoverride)
			{
				espclr = color(variables::colors::esp::o_red, variables::colors::esp::o_green, variables::colors::esp::o_blue);
			}
			else
			{
				espclr = color::white();
			}

			if (pCSPlayer->team() != csgo::local_player->team())
			{
				if (variables::Visuals::esp::name == true) /* Name esp */
				{
					render::draw_text_string(vecHeadScreen.x, vecHeadScreen.y - 15, render::fonts::espfont, playerinfo.name, true, espclr);
				}

				if (variables::Visuals::esp::box == true) /* Box esp */
				{
					render::draw_rect(x, y, w, h, color::black());
					render::draw_rect(x + 1, y + 1, w - 2, h - 2, espclr);
				}

				if (variables::Visuals::esp::healthbar) /* Health Bar esp */
				{
					if (pCSPlayer->health() > 70)
					{
						render::draw_rect(healthx, healthy, healthw, healthh, color::black());
						render::draw_filled_rect(healthx + 1, healthy + 1, healthw - 2, healthheight - 2, color(0, 0, 0, 100));
						render::draw_filled_rect(healthx + 1, healthy + 1, healthw - 2, healthheight - 2, color::green());
					}

					if (pCSPlayer->health() < 70)
					{
						render::draw_rect(healthx, healthy, healthw, healthh, color::black());
						render::draw_filled_rect(healthx + 1, healthy + 1, healthw - 2, healthheight - 2, color(0, 0, 0, 100));
						render::draw_filled_rect(healthx + 1, healthy + 1, healthw - 2, healthheight - 2, color(255, 165, 0));
					}

					if (pCSPlayer->health() < 35)
					{
						render::draw_rect(healthx, healthy, healthw, healthh, color::black());
						render::draw_filled_rect(healthx + 1, healthy + 1, healthw - 2, healthheight - 2, color(0, 0, 0, 100));
						render::draw_filled_rect(healthx + 1, healthy + 1, healthw - 2, healthheight - 2, color::red());
					}

				}

				if (variables::Visuals::esp::shieldbar == true) /* Armor Bar esp */
				{
					if (pCSPlayer->armor() > 0)
					{
						render::draw_rect(armorx, armory, armorw, armorh, color::black());
						render::draw_filled_rect(armorx + 1, armory + 1, armorw - 1, armorheight - 2, color(0, 0, 0, 100));
						render::draw_filled_rect(armorx + 1, armory + 1, armorw - 1, armorheight - 2, color::blue());
					}
				}

				/* flags */

				std::vector<std::pair<std::string, color>> flags;

				if (variables::Visuals::esp::flag_flashed && pCSPlayer->is_flashed())
					flags.emplace_back(std::pair<std::string, color>("flashed", color(255, 255, 0)));

				if (variables::Visuals::esp::flag_money && pCSPlayer->money())
					flags.emplace_back(std::pair<std::string, color>(std::to_string(pCSPlayer->money()).insert(0, "$"), color(0, 255, 0)));

				if (variables::Visuals::esp::flag_armor && pCSPlayer->has_helmet() && pCSPlayer->armor() > 0)
					flags.emplace_back(std::pair<std::string, color>("HK", color(40, 40, 255)));
				else if (variables::Visuals::esp::flag_armor && !pCSPlayer->has_helmet() && pCSPlayer->armor() > 0)
					flags.emplace_back(std::pair<std::string, color>("K", color(40, 40, 255)));

				if (variables::Visuals::esp::flag_scoped && pCSPlayer->is_scoped())
					flags.emplace_back(std::pair<std::string, color>("scoped", color(255, 255, 0)));

				if (variables::Visuals::esp::flag_defusekit && pCSPlayer->has_defuser())
					flags.emplace_back(std::pair<std::string, color>("defuse kit", color(255, 255, 255)));

				if (variables::Visuals::esp::flag_defusing && pCSPlayer->is_defusing())
					flags.emplace_back(std::pair<std::string, color>("defusing", color(255, 255, 255)));


				if (variables::Visuals::esp::weaponesp == true) /* Weapon name esp */
				{
					if (pCSPlayer->is_alive() == true)
					{
						std::string wep = pCSPlayer->active_weapon()->get_weapon_data()->weapon_name;
						flags.emplace_back(std::pair<std::string, color>(clean_item_name(wep), color(255, 255, 255)));
					}
				}

				auto postion = 0;
				for (auto flag : flags)
				{
					int right, bottom;
					const auto converted_text = std::wstring(flag.first.begin(), flag.first.end());
					interfaces::surface->get_text_size(render::fonts::flagfont, converted_text.c_str(), right, bottom);

					render::draw_text_string(x + w + 10 + (right / 2), y + postion, render::fonts::flagfont, flag.first, true, flag.second);
					postion += 10;
				}


				if (variables::Visuals::esp::hitmarkers)
				{

					float hitmarker_length = 5.0f;
					bool hitmarker_alive = false;

					int attacker = interfaces::engine->get_player_for_user_id(event->get_int("attacker"));
					int victim = interfaces::engine->get_player_for_user_id(event->get_int("userid"));

					if (!strcmp(event->get_name(), "player_hurt"))
					{
						hitmarker_alive = true;
						for (float i = 0; i < hitmarker_length; i++)
						{
							if (i > hitmarker_length)
							{
								hitmarker_alive = false;
								i = 0;
							}

							if (hitmarker_alive)
							{
								if (attacker == interfaces::engine->get_local_player() && victim != interfaces::engine->get_local_player())
								{
									int dmg = event->get_int("dmg_health");
									std::string damage = std::to_string(dmg);

									render::draw_text_string(vecHeadScreen.x, vecHeadScreen.y - 45,		render::fonts::espfont, damage, true, color(255, 0, 0));
								}

							}

						}
					}
				}
			}
		}
	}
}

void boneesp() /* Skeletons */
{
	if (variables::Visuals::esp::bonevisible == true) /* Only draw if player is visible */
	{
		variables::Visuals::esp::bonealways == false;
		for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++)
		{
			auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));
			if (!pCSPlayer)
				continue;
			if (pCSPlayer == csgo::local_player)
				continue;
			if (pCSPlayer->dormant())
				continue;
			if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
				continue;

			if (pCSPlayer->is_visible(pCSPlayer) == true)
			{
				vec3_t vecFoot;
				vec2_t vecScreen;
				vec2_t vecHeadScreen;
				vecFoot = pCSPlayer->origin();
				if (!(math::world_to_screen(vecFoot, vecScreen)))
					continue;

				vecFoot.z += 72.f;
				if (!(math::world_to_screen(vecFoot, vecHeadScreen)))
					continue;

				player_info_t playerinfo;
				interfaces::engine->get_player_info(iPlayer, &playerinfo);

				auto pStudioModel = interfaces::model_info->get_studio_model(pCSPlayer->model());
				if (!pStudioModel)
					return;

				static matrix_t pBoneToWorldOut[128];
				if (pCSPlayer->setup_bones(pBoneToWorldOut, 128, 256, 0))
				{
					for (int i = 0; i < pStudioModel->bones_count; i++)
					{
						if (interfaces::engine->is_in_game() == false)
							return;

						if (csgo::local_player == nullptr)
							return;

						studio_bone_t* pBone = pStudioModel->bone(i);
						if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
							continue;

						vec2_t vBonePos1;
						if (!math::world_to_screen(vec3_t(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
							continue;

						vec2_t vBonePos2;
						if (!math::world_to_screen(vec3_t(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
							continue;

						else if (pCSPlayer->team() != csgo::local_player->team())
						{
							render::draw_line(vBonePos1.x, vBonePos1.y, vBonePos2.x, vBonePos2.y, color::white());
						}
					}

				}
			}
		}
	}
	if (variables::Visuals::esp::bonealways == true) /* Draw bones always */
	{
		variables::Visuals::esp::bonevisible == false;
		for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++)
		{
			auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));
			if (!pCSPlayer)
				continue;
			if (pCSPlayer == csgo::local_player)
				continue;
			if (pCSPlayer->dormant())
				continue;
			if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
				continue;


			vec3_t vecFoot;
			vec2_t vecScreen;
			vec2_t vecHeadScreen;
			vecFoot = pCSPlayer->origin();
			if (!(math::world_to_screen(vecFoot, vecScreen)))
				continue;

			vecFoot.z += 72.f;
			if (!(math::world_to_screen(vecFoot, vecHeadScreen)))
				continue;

			player_info_t playerinfo;
			interfaces::engine->get_player_info(iPlayer, &playerinfo);

			auto pStudioModel = interfaces::model_info->get_studio_model(pCSPlayer->model());
			if (!pStudioModel)
				return;

			static matrix_t pBoneToWorldOut[128];
			if (pCSPlayer->setup_bones(pBoneToWorldOut, 128, 256, 0))
			{
				for (int i = 0; i < pStudioModel->bones_count; i++)
				{
					if (interfaces::engine->is_in_game() == false)
						return;

					if (csgo::local_player == nullptr)
						return;

					studio_bone_t* pBone = pStudioModel->bone(i);
					if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
						continue;

					vec2_t vBonePos1;
					if (!math::world_to_screen(vec3_t(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
						continue;

					vec2_t vBonePos2;
					if (!math::world_to_screen(vec3_t(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
						continue;
					else if (pCSPlayer->team() != csgo::local_player->team())
					{
						render::draw_line(vBonePos1.x, vBonePos1.y, vBonePos2.x, vBonePos2.y, color::white());
					}
				}

			}
		}
	}
	if (variables::Visuals::esp::backtrackskeleton == true) /* Draw bones always */
	{
		for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++)
		{
			auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));

			if (!pCSPlayer)
				continue;
			if (pCSPlayer == csgo::local_player)
				continue;
			if (pCSPlayer->dormant())
				continue;
			if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
				continue;

			vec3_t vecFoot;
			vec2_t vecScreen;
			vec2_t vecHeadScreen;
			vecFoot = pCSPlayer->origin();
			if (!(math::world_to_screen(vecFoot, vecScreen)))
				continue;

			vecFoot.z += 72.f;
			if (!(math::world_to_screen(vecFoot, vecHeadScreen)))
				continue;

			player_info_t playerinfo;
			interfaces::engine->get_player_info(iPlayer, &playerinfo);

			auto pStudioModel = interfaces::model_info->get_studio_model(pCSPlayer->model());
			if (!pStudioModel)
				return;

			static matrix_t pBoneToWorldOut[128];
			if (pCSPlayer->setup_bones(pBoneToWorldOut, 128, 256, 0))
			{
				for (int i = 0; i < pStudioModel->bones_count; i++)
				{
					if (interfaces::engine->is_in_game() == false)
						return;

					if (csgo::local_player == nullptr)
						return;

					studio_bone_t* pBone = pStudioModel->bone(i);
					if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
						continue;

					vec2_t vBonePos1;
					if (!math::world_to_screen(vec3_t(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
						continue;

					vec2_t vBonePos2;

					if (!math::world_to_screen(vec3_t(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
						continue;

					else if (pCSPlayer->team() != csgo::local_player->team() && records[pCSPlayer->index()].size() > 0 && variables::aimbots::backtrack == true)
					{
						for (uint32_t i = 0; i < records[pCSPlayer->index()].size(); i++)
						{
							//render::draw_line(records[vBonePos1.x], vBonePos1.y, vBonePos2.x, vBonePos2.y, color::white());
						}
					}
				}

			}
		}
	}
}

void gernadepredict(c_usercmd* cmd) /* Grenade prediction */
{
	if (variables::Visuals::esp::espToggle == true) /* ??? Why did I ever do this... anyways I need to create a standalone variable for this */
	{
		if (WEAPONTYPE_GRENADE && cmd->buttons & in_attack || in_attack2)
		{

		}
	}
}

void bombesp() /* Bomb timer */
{
	if (variables::Visuals::esp::bomb_info)
	{	
		std::pair<int, int> screen_size;
		interfaces::surface->get_screen_size(screen_size.first, screen_size.second);

		for (int i = 1; i < interfaces::entity_list->get_highest_index(); i++)
		{
			auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

			if (entity == nullptr)
				continue;
			
			if (entity->client_class()->class_id == class_ids::cplantedc4 && entity->c4_is_ticking() && !entity->c4_is_defused())
			{
				if (csgo::local_player == nullptr)
					continue;
				
				auto explode_time = entity->c4_blow_time() - (interfaces::globals->interval_per_tick * csgo::local_player->get_tick_base()); // 40 - 0
				auto defuse_countdown = entity->c4_defuse_countdown() - (interfaces::globals->interval_per_tick * csgo::local_player->get_tick_base()); // 10 - 0 or 5 - 0

				char time_to_explode[64]; sprintf_s(time_to_explode, "%.1f", explode_time);
				char time_to_defuse[64]; sprintf_s(time_to_defuse, "%.1f", defuse_countdown);

				if (explode_time > 0)
				{
					int height = 75;
					auto ratio_explode = (explode_time / entity->c4_timer_length()) * screen_size.first;
					auto length = entity->has_defuser() ? 5 : 10;
					auto ratio_defuse = (float)(defuse_countdown / length) * (float)screen_size.first;

					std::string site = std::to_string(entity->nBombSite());
					
					render::draw_filled_rect(60, 550, 400, height, color(30, 30, 30, 200));
					render::draw_rect(60, 550, 400, height, color(125, 125, 125, 200));
					
					render::draw_text_string(130, 570, render::fonts::menucontent, "Time to Explode: ", true, color(255, 255, 255));
					render::draw_text_string(215, 571, render::fonts::menucontent, time_to_explode, true, color(255, 255, 255));
					
					if (entity->c4_gets_defused() > 0)
					{
						render::draw_text_string(128, 590, render::fonts::menucontent, "Time to Defuse: ", true, color(255, 255, 255));
						render::draw_text_string(215, 591, render::fonts::menucontent, time_to_defuse, true, color(255, 255, 255));
					}
				}
			}
		}
	}
}

void dropped_weapons()
{
	if (variables::Visuals::esp::dropped_wep_names)
	{
		for (int i = 1; i < interfaces::entity_list->get_highest_index(); i++)
		{
			auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

			if (!entity)
				continue;

			if (entity->is_player())
				continue;

			if (!entity->client_class()->class_id)
				continue;

			if (entity->client_class()->class_id == class_ids::cplantedc4)
				continue;
			
			auto mdl = interfaces::model_info->get_model_name(entity->model());

			if (strstr(mdl, "models/weapons/w_") && strstr(mdl, "_dropped.mdl"))
			{
				auto pos = entity->abs_origin();
				vec3_t pos_2d = {};
				if (interfaces::debug_overlay->world_to_screen(pos, pos_2d))
				{
					render::draw_text_string(pos_2d.x, pos_2d.y, render::fonts::flagfont, clean_item_name(reinterpret_cast<weapon_t*>(entity)->get_weapon_data()->weapon_name), true, color(255, 255, 255));
				}
			}
		}
	}
}