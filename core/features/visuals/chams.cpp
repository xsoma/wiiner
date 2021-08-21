#include "../features.hpp"
#include "../rage/backtrack.h"

extern hooks::draw_model_execute::fn draw_model_execute_original;

////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Smoke Shit */
std::vector<const char*> vistasmoke_mats = 
{
		"particle/vistasmokev1/vistasmokev1_fire",
		"particle/vistasmokev1/vistasmokev1_smokegrenade",
		"particle/vistasmokev1/vistasmokev1_emods",
		"particle/vistasmokev1/vistasmokev1_emods_impactdust",
};

void override_material(bool ignorez, bool wireframe, const color& rgba) {
	auto material = interfaces::material_system->find_material("debug/debugambientcube", TEXTURE_GROUP_MODEL);
	material->set_material_var_flag(material_var_ignorez, ignorez);
	material->set_material_var_flag(material_var_wireframe, wireframe);
	material->alpha_modulate(rgba.a / 255.f);
	material->color_modulate(rgba.r / 255.f, rgba.g / 255.f, rgba.b / 255.f);
	interfaces::model_render->override_material(material);
}

void override_material_smoke(bool ignorez, bool wireframe, bool draw, const color& rgba) {
	auto material = interfaces::material_system->find_material("debug/debugambientcube", TEXTURE_GROUP_MODEL);
	material->set_material_var_flag(material_var_ignorez, ignorez);
	material->set_material_var_flag(material_var_wireframe, wireframe);
	material->set_material_var_flag(material_var_no_draw, draw);
	material->alpha_modulate(rgba.a / 255.f);
	material->color_modulate(rgba.r / 255.f, rgba.g / 255.f, rgba.b / 255.f);
	interfaces::model_render->override_material(material);
}

void override_material_flat(bool ignorez, bool wireframe, bool flat, const color& rgba) {
	auto material = interfaces::material_system->find_material("debug/debugdrawflat", TEXTURE_GROUP_MODEL);
	material->set_material_var_flag(material_var_ignorez, ignorez);
	material->set_material_var_flag(material_var_wireframe, wireframe);
	material->set_material_var_flag(material_var_flat, flat);
	material->alpha_modulate(rgba.a / 255.f);
	material->color_modulate(rgba.r / 255.f, rgba.g / 255.f, rgba.b / 255.f);
	interfaces::model_render->override_material(material);
}

void override_material_gloss(bool ignorez, bool wireframe, const color& rgba) {
	auto material = interfaces::material_system->find_material("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_MODEL);
	material->set_material_var_flag(material_var_ignorez, ignorez);
	material->set_material_var_flag(material_var_wireframe, wireframe);
	material->alpha_modulate(rgba.a / 255.f);
	material->color_modulate(rgba.r / 255.f, rgba.g / 255.f, rgba.b / 255.f);
	interfaces::model_render->override_material(material);
}

void override_material_crystal(bool ignorez, bool wireframe, const color& rgba) {
	auto material = interfaces::material_system->find_material("debug/debugtranslucentvertexcolor", TEXTURE_GROUP_MODEL);
	material->set_material_var_flag(material_var_ignorez, ignorez);
	material->set_material_var_flag(material_var_wireframe, wireframe);
	material->alpha_modulate(rgba.a / 255.f);
	material->color_modulate(rgba.r / 255.f, rgba.g / 255.f, rgba.b / 255.f);
	interfaces::model_render->override_material(material);
}

void noarms(bool ignorez, bool wireframe, const color& rgba) {
	auto material = interfaces::material_system->find_material("models/inventory_items/trophy_majors/crystal_clear.vmt", TEXTURE_GROUP_MODEL);
	material->set_material_var_flag(material_var_ignorez, ignorez);
	material->set_material_var_flag(material_var_wireframe, wireframe);
	material->alpha_modulate(rgba.a / 255.f);
	material->color_modulate(rgba.r / 255.f, rgba.g / 255.f, rgba.b / 255.f);
	interfaces::model_render->override_material(material);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////


void chams(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix)
{

	if (interfaces::engine->is_in_game() == false)
		return;

	if (csgo::local_player == nullptr)
		return;
	
	const auto mdl = info.model;

	if (!mdl)
		return;

	bool is_player = strstr(mdl->name, "models/player") != nullptr; /* Check if model is player */

	if (variables::misc::nosmoke == true)
	{
		if (!csgo::local_player->is_alive())
			return;

		bool smoke = strstr(mdl->name, "particle/vistasmokev1/vistasmokev1_fire") != nullptr;

		bool smokea = strstr(mdl->name, "vistasmokev1/vistasmokev1_smokegrenade") != nullptr;

		bool smokeb = strstr(mdl->name, "particle/vistasmokev1/vistasmokev1_emods") != nullptr;

		bool smokec = strstr(mdl->name, "particle/vistasmokev1/vistasmokev1_emods_impactdust") != nullptr;
		
		if (smoke)
		{
			override_material_smoke(true, true, true, color(70, 70, 70, 255));
		}

		if (smokea)
		{
			override_material_smoke(true, true, true, color(70, 70, 70, 255));
		}

		if (smokeb)
		{
			override_material_smoke(true, true, true, color(70, 70, 70, 255));
		}

		if (smokec)
		{
			override_material_smoke(true, true, true, color(70, 70, 70, 150));
		}

	}

	if (!csgo::local_player)
		return;

	if (csgo::local_player == nullptr)
		return;
	
	if (variables::Visuals::chams::backtrackchams == true)
	{
		player_t* player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(info.entity_index));

		if (player == nullptr)
			return; 
		
		if (is_player && records[player->index()].size() > 0 && variables::aimbots::backtrack == true)
		{
			if (!player || !player->is_alive() || player->dormant())
				return;

			if (player->team() != csgo::local_player->team())
			{
				for (uint32_t i = 0; i < records[player->index()].size(); i++) 
				{
					if (!backtrack.valid_tick(records[player->index()][i].simulation_time, 0.2f) || records[player->index()][i].matrix == nullptr)
						continue;
					
					override_material(false, false, color(variables::colors::cFloats::b_red - (i * (255 / records[player->index()].size())), i * (variables::colors::cFloats::b_green / records[player->index()].size()), variables::colors::cFloats::b_blue, 150));
					draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, records[player->index()][i].matrix);
				}
			}
		}
	}
	
	if (variables::Visuals::chams::chams == true) /* Chams run here */
	{
		if (variables::Visuals::chams::chamsalways == true)
		{
			variables::Visuals::chams::chamsvisible  = false; /* Saves cheat from having a stroke */
			variables::Visuals::chams::chamsxqz = false;

			if (is_player)
			{
				player_t* player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(info.entity_index));

				if (!player || !player->is_alive() || player->dormant())
					return;


				if (player->team() != csgo::local_player->team())
				{
					if (variables::colors::cMats::m_normal == true)
					{
						override_material(true, variables::Visuals::chams::wireframe, color(variables::colors::cFloats::c_red, variables::colors::cFloats::c_green, variables::colors::cFloats::c_blue, 255));
						draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
					}

					if (variables::colors::cMats::m_flat)
					{
						override_material_flat(true, variables::Visuals::chams::wireframe, true, color(variables::colors::cFloats::c_red, variables::colors::cFloats::c_green, variables::colors::cFloats::c_blue, 255));
						draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
					}

					if (variables::colors::cMats::m_ghost)
					{
						override_material_crystal(false, variables::Visuals::chams::wireframe, color(variables::colors::cFloats::c_red, variables::colors::cFloats::c_green, variables::colors::cFloats::c_blue, 255));
						draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
					}

				}

			}
		}

		if (variables::Visuals::chams::chamsxqz == true)
		{
			if (is_player)
			{
				player_t* player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(info.entity_index));

				if (!player || !player->is_alive() || player->dormant())
					return;

				if (player->team() != csgo::local_player->team())
				{
					if (variables::colors::cMats::xqz_m_normal == true)
					{
						if (variables::Visuals::chams::chamsvisible == true)
						{
							override_material(false, variables::Visuals::chams::xqz_wireframe, color(variables::colors::cFloats::c_red, variables::colors::cFloats::c_green, variables::colors::cFloats::c_blue, 255));
							draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
						}				
						override_material(true, variables::Visuals::chams::xqz_wireframe, color(variables::colors::cFloats::xqz_c_red, variables::colors::cFloats::xqz_c_green, variables::colors::cFloats::xqz_c_blue, 255));
						draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
					}

					if (variables::colors::cMats::xqz_m_flat)
					{
						if (variables::Visuals::chams::chamsvisible == true)
						{
							override_material(false, variables::Visuals::chams::xqz_wireframe, color(variables::colors::cFloats::c_red, variables::colors::cFloats::c_green, variables::colors::cFloats::c_blue, 255));
							draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
						}
						override_material_flat(true, variables::Visuals::chams::xqz_wireframe, true, color(variables::colors::cFloats::xqz_c_red, variables::colors::cFloats::xqz_c_green, variables::colors::cFloats::xqz_c_blue, 255));
						draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
					}

					if (variables::colors::cMats::xqz_m_ghost)
					{
						if (variables::Visuals::chams::chamsvisible == true)
						{
							override_material(false, variables::Visuals::chams::xqz_wireframe, color(variables::colors::cFloats::c_red, variables::colors::cFloats::c_green, variables::colors::cFloats::c_blue, 255));
							draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
						}		
						override_material_crystal(true, variables::Visuals::chams::xqz_wireframe, color(variables::colors::cFloats::xqz_c_red, variables::colors::cFloats::xqz_c_green, variables::colors::cFloats::xqz_c_blue, 255));
						draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
					}
				}

			}
		}

		if (variables::Visuals::chams::chamsvisible == true)
		{
			if (is_player)
			{
				player_t* player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(info.entity_index));

				if (!player || !player->is_alive() || player->dormant())
					return;

				if (player->team() != csgo::local_player->team())
				{
					if (variables::colors::cMats::m_normal == true)
					{
						override_material(false, variables::Visuals::chams::wireframe, color(variables::colors::cFloats::c_red, variables::colors::cFloats::c_green, variables::colors::cFloats::c_blue, 255));
						draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
					}

					if (variables::colors::cMats::m_flat == true)
					{
						override_material_flat(false, variables::Visuals::chams::wireframe, true, color(variables::colors::cFloats::c_red, variables::colors::cFloats::c_green, variables::colors::cFloats::c_blue, 255));
						draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
					}

					if (variables::colors::cMats::m_ghost == true)
					{
						override_material_crystal(false, variables::Visuals::chams::wireframe, color(variables::colors::cFloats::c_red, variables::colors::cFloats::c_green, variables::colors::cFloats::c_blue, 255));
						draw_model_execute_original(interfaces::model_render, 0, ctx, state, info, matrix);
					}

				}
			}
		}

	}

	if (variables::Visuals::chams::armschams == true) /* Chams for arms */
	{
		bool arms = strstr(mdl->name, "models/arms") != nullptr; /* Check model is arms */

		if (arms)
		{
			if (csgo::local_player && csgo::local_player->is_alive())  /* Only overide localplayers arms */
			{
				if (variables::colors::cMats::arms::m_normal == true)
				{
					override_material(true, variables::Visuals::chams::hands_wireframe, color(variables::colors::cMats::arms::c_red, variables::colors::cMats::arms::c_green, variables::colors::cMats::arms::c_blue, 255));
				}

				if (variables::colors::cMats::arms::m_flat == true)
				{
					override_material_flat(true, variables::Visuals::chams::hands_wireframe, true, color(variables::colors::cMats::arms::c_red, variables::colors::cMats::arms::c_green, variables::colors::cMats::arms::c_blue, 255));
				}

				if (variables::colors::cMats::arms::m_crystal == true)
				{
					override_material_crystal(true, variables::Visuals::chams::hands_wireframe, color(variables::colors::cMats::arms::c_red, variables::colors::cMats::arms::c_green, variables::colors::cMats::arms::c_blue, 255));
				}

			}
		}

	}

	if (variables::Visuals::chams::nohands == true) /* No hands, pretty self explanitory */
	{
		bool arms = strstr(mdl->name, "models/arms") != nullptr; /* Same thing arms chams does */

		if (arms)
		{
			if (csgo::local_player && csgo::local_player->is_alive())
			{
				override_material(true, false, color(255, 255, 255, 0));
			}
		}

	}

}