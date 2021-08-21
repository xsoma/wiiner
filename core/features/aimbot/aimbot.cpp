#include "../features.hpp"

void smooth(vec3_t& ViewAngle, vec3_t& Angle, float SmoothValue) /* Useless? */
{
	// Angle = (ViewAngle + Angle - ViewAngle.clamp() / SmoothValue).clamp();
}

player_t* closest_to_crosshair(c_usercmd* user_cmd) /* Target closest to crosshair */
{
	player_t* best_entity = nullptr;
	float delta;
	float best_delta = FLT_MAX;

	for (int i = 1; i <= interfaces::globals->max_clients; i++)
	{
		auto view_angles = user_cmd->viewangles;
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		if (!entity || entity == csgo::local_player)
			continue;

		if (entity->has_gun_game_immunity() || entity->dormant() || !entity->is_alive() || !entity->is_player() || entity->health() <= 0)
			continue;

		if (entity->team() == csgo::local_player->team())
			continue;

		if (!entity->is_visible(entity))
			continue;

		if (csgo::local_player->is_flashed() == true)
			continue;

		delta = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_eye_pos(), view_angles).length();
		if (delta < best_delta && delta < 40)
		{
			best_entity = entity;
			best_delta = delta;
		}
	}
	return best_entity;
}

player_t* closest_distance(c_usercmd* user_cmd) /* Target closest to localplayer */
{
	player_t* best_entity = nullptr;
	float distance;
	float best_distance = FLT_MAX;

	for (int i = 1; i <= interfaces::globals->max_clients; i++)
	{
		auto view_angles = user_cmd->viewangles;
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		if (!entity || entity == csgo::local_player)
			continue;

		if (entity->has_gun_game_immunity() || entity->dormant() || !entity->is_alive() || !entity->is_player() || entity->health() <= 0)
			continue;

		if (entity->team() == csgo::local_player->team())
			continue;

		if (!entity->is_visible(entity))
			continue;

		if (csgo::local_player->is_flashed() == true)
			continue;

		auto delta = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_eye_pos(), view_angles).length();
		distance = entity->abs_origin().distance_to(csgo::local_player->abs_origin());
		if (distance < best_distance && delta < variables::aimbots::legit::legit_fov)
		{
			best_entity = entity;
		}
	}
	return best_entity;
}

player_t* lowest_health(c_usercmd* user_cmd) /* Target with lowest health */
{
	player_t* best_entity = nullptr;
	int health;
	int best_health = 1000.f;

	for (int i = 1; i <= interfaces::globals->max_clients; i++)
	{
		auto view_angles = user_cmd->viewangles;
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		if (!entity || entity == csgo::local_player)
			continue;

		if (entity->has_gun_game_immunity() || entity->dormant() || !entity->is_alive() || !entity->is_player() || entity->health() <= 0)
			continue;

		if (!entity->is_visible(entity))
			continue;

		if (csgo::local_player->is_flashed() == true)
			continue;

		if (entity->team() == csgo::local_player->team())
			continue;

		auto delta = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_eye_pos(), view_angles).length();
		health = entity->health();
		if (health < best_health && delta < variables::aimbots::legit::legit_fov)
		{
			best_entity = entity;
			best_health = health;
		}
	}
	return best_entity;
}

void aimbot(c_usercmd* user_cmd) /* Where legit aimbot runs */
{

	if (!csgo::local_player->is_alive()) /* No reason to run aimbot if you are dead */
		return;

	const auto weapon_type = csgo::local_player->active_weapon()->get_weapon_data()->weapon_type;

	if (weapon_type == NULL)
		return;

	if (weapon_type == WEAPONTYPE_PISTOL)
	{

		bool can_run = false;

		if (variables::aimbots::legit::pistols::keybindings::aimbotbind != 256 && GetAsyncKeyState(variables::aimbots::legit::pistols::keybindings::aimbotbind))
		{
			can_run = true;
		}

		if (variables::aimbots::legit::pistols::keybindings::aimbotbind == 256)
		{
			can_run = true;
		}

		if (can_run)
		{
			if (variables::aimbots::legit::pistols::aimbotToggle == true)
			{
				if (variables::aimbots::legit::pistols::randombones == true)
				{
					if (!csgo::local_player->is_alive()) /* No reason to run aimbot if you are dead */
						return;

					srand(time(0)); /* psudeo random number generator */
					int random = rand() % 5 + 1;  /* Only randomize from 1-5 */

					if (weapon_type == WEAPONTYPE_GRENADE || weapon_type == WEAPONTYPE_C4 || weapon_type == WEAPONTYPE_KNIFE)
						return; /* Don't aimbot with grenade, c4, or knife */

					player_t* entity = nullptr;
					int bone = 0;
					entity = closest_to_crosshair(user_cmd); /* I should make it so you can pick diffrent modes  */

					if (!entity)
						return;

					if (random == 1)
					{
						bone = 7;
					}
					if (random == 2 || random == 3) /* Bone selection */
					{
						bone = 8;
					}
					if (random == 4 || random == 5)
					{
						bone = 6;
					}

					auto angle = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_bone_position(bone), user_cmd->viewangles);

					angle.clamp();

					angle /= (variables::aimbots::legit::pistols::smoothing * 4);

					angle = math::normalize(angle);

					user_cmd->viewangles += angle;

					if (variables::aimbots::legit::pistols::silentaim == false) /* If silent aim isn't enabled set viewangles */
					{
						interfaces::engine->set_view_angles(user_cmd->viewangles);
					}
				}

				if (variables::aimbots::legit::pistols::randombones == false)
				{
					if (!csgo::local_player->is_alive()) /* No reason to run aimbot if you are dead */
						return;

					if (weapon_type == WEAPONTYPE_GRENADE || weapon_type == WEAPONTYPE_C4 || weapon_type == WEAPONTYPE_KNIFE)
						return; /* Don't aimbot with grenade, c4, or knife */

					ray_t ray;
					trace_filter filter;
					trace_t trace;
					vec3_t start, end, forward;

					math::angle_vectors_alternative(user_cmd->viewangles, &forward);

					forward *= csgo::local_player->active_weapon()->get_weapon_data()->weapon_range;
					start = csgo::local_player->get_eye_pos();
					end = start + forward;
					filter.skip = csgo::local_player;
					ray.initialize(start, end);

					interfaces::trace_ray->trace_ray(ray, 0x46004003, &filter, &trace);

					auto player = trace.entity;
					if (!player)
						return;

					if (player->client_class()->class_id != ccsplayer)
						return;

					if (trace.entity->team() == csgo::local_player->team())
						return;

					player_t* entity = nullptr;
					int bone = 0;
					entity = closest_to_crosshair(user_cmd); /* I should make it so you can pick diffrent modes  */

					if (!entity)
						return;

					if (variables::aimbots::legit::pistols::headprioirtybone)
						bone = 8;

					if (variables::aimbots::legit::pistols::bodyprioritybone)
						bone = 6;

					if (variables::aimbots::legit::pistols::stomachprioritybone)
						bone = 4;

					if (variables::aimbots::legit::pistols::ahead && trace.hitGroup == hitgroup_head)
					{
						bone = 8;
					}

					if (variables::aimbots::legit::pistols::ahead && trace.hitGroup == hitgroup_generic || variables::aimbots::legit::pistols::ahead && trace.hitGroup == 7)
					{
						bone = 8;
					}

					if (variables::aimbots::legit::pistols::achest && trace.hitGroup == hitgroup_chest || variables::aimbots::legit::pistols::ahead && trace.hitGroup == 5)
					{
						bone = 6;
					}

					if (variables::aimbots::legit::pistols::astomach && trace.hitGroup == hitgroup_stomach)
					{
						bone = 4;
					}

					auto angle = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_bone_position(bone), user_cmd->viewangles);

					angle.clamp();

					angle /= (variables::aimbots::legit::pistols::smoothing * 4);

					angle = math::normalize(angle);

					user_cmd->viewangles += angle;

					if (variables::aimbots::legit::pistols::silentaim == false) /* If silent aim isn't enabled set viewangles */
					{
						interfaces::engine->set_view_angles(user_cmd->viewangles);
					}
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////


	if (weapon_type == WEAPONTYPE_SUBMACHINEGUN)
	{
		bool can_run = false;

		if (variables::aimbots::legit::smgs::keybindings::aimbotbind != 256 && GetAsyncKeyState(variables::aimbots::legit::smgs::keybindings::aimbotbind))
		{
			can_run = true;
		}

		if (variables::aimbots::legit::smgs::keybindings::aimbotbind == 256)
		{
			can_run = true;
		}

		if (can_run)
		{
			if (variables::aimbots::legit::smgs::aimbotToggle == true)
			{
				if (variables::aimbots::legit::smgs::randombones == true)
				{
					if (!csgo::local_player->is_alive()) /* No reason to run aimbot if you are dead */
						return;

					srand(time(0)); /* psudeo random number generator */
					int random = rand() % 5 + 1;  /* Only randomize from 1-5 */

					if (weapon_type == WEAPONTYPE_GRENADE || weapon_type == WEAPONTYPE_C4 || weapon_type == WEAPONTYPE_KNIFE)
						return; /* Don't aimbot with grenade, c4, or knife */

					player_t* entity = nullptr;
					int bone = 0;
					entity = closest_to_crosshair(user_cmd); /* I should make it so you can pick diffrent modes  */

					if (!entity)
						return;

					if (random == 1)
					{
						bone = 7;
					}
					if (random == 2 || random == 3) /* Bone selection */
					{
						bone = 8;
					}
					if (random == 4 || random == 5)
					{
						bone = 6;
					}

					auto angle = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_bone_position(bone), user_cmd->viewangles);

					angle.clamp();

					angle /= (variables::aimbots::legit::smgs::smoothing * 4);

					angle = math::normalize(angle);

					user_cmd->viewangles += angle;

					if (variables::aimbots::legit::smgs::silentaim == false) /* If silent aim isn't enabled set viewangles */
					{
						interfaces::engine->set_view_angles(user_cmd->viewangles);
					}
				}

				if (variables::aimbots::legit::smgs::randombones == false)
				{
					if (!csgo::local_player->is_alive()) /* No reason to run aimbot if you are dead */
						return;

					if (weapon_type == WEAPONTYPE_GRENADE || weapon_type == WEAPONTYPE_C4 || weapon_type == WEAPONTYPE_KNIFE)
						return; /* Don't aimbot with grenade, c4, or knife */

					ray_t ray;
					trace_filter filter;
					trace_t trace;
					vec3_t start, end, forward;

					math::angle_vectors_alternative(user_cmd->viewangles, &forward);

					forward *= csgo::local_player->active_weapon()->get_weapon_data()->weapon_range;
					start = csgo::local_player->get_eye_pos();
					end = start + forward;
					filter.skip = csgo::local_player;
					ray.initialize(start, end);

					interfaces::trace_ray->trace_ray(ray, 0x46004003, &filter, &trace);

					auto player = trace.entity;
					if (!player)
						return;

					if (player->client_class()->class_id != ccsplayer)
						return;

					if (trace.entity->team() == csgo::local_player->team())
						return;

					player_t* entity = nullptr;
					int bone = 0;
					entity = closest_to_crosshair(user_cmd); /* I should make it so you can pick diffrent modes  */

					if (!entity)
						return;

					if (variables::aimbots::legit::smgs::headprioirtybone)
						bone = 8;

					if (variables::aimbots::legit::smgs::bodyprioritybone)
						bone = 6;

					if (variables::aimbots::legit::smgs::stomachprioritybone)
						bone = 4;

					if (variables::aimbots::legit::smgs::ahead && trace.hitGroup == hitgroup_head)
					{
						bone = 8;
					}

					if (variables::aimbots::legit::smgs::ahead && trace.hitGroup == hitgroup_generic || variables::aimbots::legit::smgs::ahead && trace.hitGroup == 7)
					{
						bone = 8;
					}

					if (variables::aimbots::legit::smgs::achest && trace.hitGroup == hitgroup_chest || variables::aimbots::legit::smgs::ahead && trace.hitGroup == 5)
					{
						bone = 6;
					}

					if (variables::aimbots::legit::smgs::astomach && trace.hitGroup == hitgroup_stomach)
					{
						bone = 4;
					}

					auto angle = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_bone_position(bone), user_cmd->viewangles);

					angle.clamp();

					angle /= (variables::aimbots::legit::smgs::smoothing * 4);

					angle = math::normalize(angle);

					user_cmd->viewangles += angle;

					if (variables::aimbots::legit::smgs::silentaim == false) /* If silent aim isn't enabled set viewangles */
					{
						interfaces::engine->set_view_angles(user_cmd->viewangles);
					}
				}
			}
		}
	}

	if (weapon_type == WEAPONTYPE_RIFLE)
	{
		bool can_run = false;

		if (variables::aimbots::legit::rifles::keybindings::aimbotbind != 256 && GetAsyncKeyState(variables::aimbots::legit::rifles::keybindings::aimbotbind))
		{
			can_run = true;
		}

		if (variables::aimbots::legit::rifles::keybindings::aimbotbind == 256)
		{
			can_run = true;
		}

		if (can_run)
		{
			if (variables::aimbots::legit::rifles::aimbotToggle == true)
			{

				if (variables::aimbots::legit::rifles::randombones == true)
				{
					if (!csgo::local_player->is_alive()) /* No reason to run aimbot if you are dead */
						return;

					srand(time(0)); /* psudeo random number generator */
					int random = rand() % 5 + 1;  /* Only randomize from 1-5 */

					if (weapon_type == WEAPONTYPE_GRENADE || weapon_type == WEAPONTYPE_C4 || weapon_type == WEAPONTYPE_KNIFE)
						return; /* Don't aimbot with grenade, c4, or knife */

					player_t* entity = nullptr;
					int bone = 0;
					entity = closest_to_crosshair(user_cmd); /* I should make it so you can pick diffrent modes  */

					if (!entity)
						return;

					if (random == 1)
					{
						bone = 7;
					}
					if (random == 2 || random == 3) /* Bone selection */
					{
						bone = 8;
					}
					if (random == 4 || random == 5)
					{
						bone = 6;
					}

					auto angle = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_bone_position(bone), user_cmd->viewangles);

					angle.clamp();

					angle /= (variables::aimbots::legit::rifles::smoothing * 4);

					angle = math::normalize(angle);

					user_cmd->viewangles += angle;

					if (variables::aimbots::legit::rifles::silentaim == false) /* If silent aim isn't enabled set viewangles */
					{
						interfaces::engine->set_view_angles(user_cmd->viewangles);
					}
				}

				if (variables::aimbots::legit::rifles::randombones == false)
				{
					if (!csgo::local_player->is_alive()) /* No reason to run aimbot if you are dead */
						return;

					if (weapon_type == WEAPONTYPE_GRENADE || weapon_type == WEAPONTYPE_C4 || weapon_type == WEAPONTYPE_KNIFE)
						return; /* Don't aimbot with grenade, c4, or knife */

					ray_t ray;
					trace_filter filter;
					trace_t trace;
					vec3_t start, end, forward;

					math::angle_vectors_alternative(user_cmd->viewangles, &forward);

					forward *= csgo::local_player->active_weapon()->get_weapon_data()->weapon_range;
					start = csgo::local_player->get_eye_pos();
					end = start + forward;
					filter.skip = csgo::local_player;
					ray.initialize(start, end);

					interfaces::trace_ray->trace_ray(ray, 0x46004003, &filter, &trace);

					auto player = trace.entity;
					if (!player)
						return;

					if (player->client_class()->class_id != ccsplayer)
						return;

					if (trace.entity->team() == csgo::local_player->team())
						return;

					player_t* entity = nullptr;
					int bone = 0;
					entity = closest_to_crosshair(user_cmd); /* I should make it so you can pick diffrent modes  */

					if (!entity)
						return;

					if (variables::aimbots::legit::rifles::headprioirtybone)
						bone = 8;

					if (variables::aimbots::legit::rifles::bodyprioritybone)
						bone = 6;

					if (variables::aimbots::legit::rifles::stomachprioritybone)
						bone = 4;

					if (variables::aimbots::legit::rifles::ahead && trace.hitGroup == hitgroup_head)
					{
						bone = 8;
					}

					if (variables::aimbots::legit::rifles::ahead && trace.hitGroup == hitgroup_generic || variables::aimbots::legit::rifles::ahead && trace.hitGroup == 7)
					{
						bone = 8;
					}

					if (variables::aimbots::legit::rifles::achest && trace.hitGroup == hitgroup_chest || variables::aimbots::legit::rifles::ahead && trace.hitGroup == 5)
					{
						bone = 6;
					}

					if (variables::aimbots::legit::rifles::astomach && trace.hitGroup == hitgroup_stomach)
					{
						bone = 4;
					}

					auto angle = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_bone_position(bone), user_cmd->viewangles);

					angle.clamp();

					angle /= (variables::aimbots::legit::rifles::smoothing * 4);

					angle = math::normalize(angle);

					user_cmd->viewangles += angle;

					if (variables::aimbots::legit::rifles::silentaim == false) /* If silent aim isn't enabled set viewangles */
					{
						interfaces::engine->set_view_angles(user_cmd->viewangles);
					}
				}
			}
		}
	}

	if (weapon_type == WEAPONTYPE_SNIPER_RIFLE)
	{
		bool can_run = false;

		if (variables::aimbots::legit::snipers::keybindings::aimbotbind != 256 && GetAsyncKeyState(variables::aimbots::legit::snipers::keybindings::aimbotbind))
		{
			can_run = true;
		}

		if (variables::aimbots::legit::snipers::keybindings::aimbotbind == 256)
		{
			can_run = true;
		}

		if (can_run)
		{
			if (variables::aimbots::legit::snipers::aimbotToggle == true)
			{

				if (variables::aimbots::legit::snipers::randombones == true)
				{
					if (!csgo::local_player->is_alive()) /* No reason to run aimbot if you are dead */
						return;

					if (variables::aimbots::legit::snipers::aimcheck == true && csgo::local_player->is_scoped() == false)
						return;

					srand(time(0)); /* psudeo random number generator */
					int random = rand() % 5 + 1;  /* Only randomize from 1-5 */

					if (weapon_type == WEAPONTYPE_GRENADE || weapon_type == WEAPONTYPE_C4 || weapon_type == WEAPONTYPE_KNIFE)
						return; /* Don't aimbot with grenade, c4, or knife */

					player_t* entity = nullptr;
					int bone = 0;
					entity = closest_to_crosshair(user_cmd); /* I should make it so you can pick diffrent modes  */

					if (!entity)
						return;

					if (random == 1)
					{
						bone = 7;
					}
					if (random == 2 || random == 3) /* Bone selection */
					{
						bone = 8;
					}
					if (random == 4 || random == 5)
					{
						bone = 6;
					}

					auto angle = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_bone_position(bone), user_cmd->viewangles);

					angle.clamp();

					angle /= (variables::aimbots::legit::snipers::smoothing * 4);

					angle = math::normalize(angle);

					user_cmd->viewangles += angle;

					if (variables::aimbots::legit::snipers::silentaim == false) /* If silent aim isn't enabled set viewangles */
					{
						interfaces::engine->set_view_angles(user_cmd->viewangles);
					}
				}

				if (variables::aimbots::legit::snipers::randombones == false)
				{

					if (!csgo::local_player->is_alive()) /* No reason to run aimbot if you are dead */
						return;

					if (variables::aimbots::legit::snipers::aimcheck == true && csgo::local_player->is_scoped() == false)
						return;

					if (weapon_type == WEAPONTYPE_GRENADE || weapon_type == WEAPONTYPE_C4 || weapon_type == WEAPONTYPE_KNIFE)
						return; /* Don't aimbot with grenade, c4, or knife */

					ray_t ray;
					trace_filter filter;
					trace_t trace;
					vec3_t start, end, forward;

					math::angle_vectors_alternative(user_cmd->viewangles, &forward);

					forward *= csgo::local_player->active_weapon()->get_weapon_data()->weapon_range;
					start = csgo::local_player->get_eye_pos();
					end = start + forward;
					filter.skip = csgo::local_player;
					ray.initialize(start, end);

					interfaces::trace_ray->trace_ray(ray, 0x46004003, &filter, &trace);

					auto player = trace.entity;
					if (!player)
						return;

					if (player->client_class()->class_id != ccsplayer)
						return;

					if (trace.entity->team() == csgo::local_player->team())
						return;

					player_t* entity = nullptr;
					int bone = 0;
					entity = closest_to_crosshair(user_cmd); /* I should make it so you can pick diffrent modes  */

					if (!entity)
						return;

					if (variables::aimbots::legit::snipers::headprioirtybone)
						bone = 8;

					if (variables::aimbots::legit::snipers::bodyprioritybone)
						bone = 6;

					if (variables::aimbots::legit::snipers::stomachprioritybone)
						bone = 4;

					if (variables::aimbots::legit::snipers::ahead && trace.hitGroup == hitgroup_head)
					{
						bone = 8;
					}

					if (variables::aimbots::legit::snipers::ahead && trace.hitGroup == hitgroup_generic || variables::aimbots::legit::snipers::ahead && trace.hitGroup == 7)
					{
						bone = 8;
					}

					if (variables::aimbots::legit::snipers::achest && trace.hitGroup == hitgroup_chest || variables::aimbots::legit::snipers::ahead && trace.hitGroup == 5)
					{
						bone = 6;
					}

					if (variables::aimbots::legit::snipers::astomach && trace.hitGroup == hitgroup_stomach)
					{
						bone = 4;
					}

					auto angle = math::calculate_angle(csgo::local_player->get_eye_pos(), entity->get_bone_position(bone), user_cmd->viewangles);

					angle.clamp();

					angle /= (variables::aimbots::legit::snipers::smoothing * 4);

					angle = math::normalize(angle);

					user_cmd->viewangles += angle;

					if (variables::aimbots::legit::snipers::silentaim == false) /* If silent aim isn't enabled set viewangles */
					{
						interfaces::engine->set_view_angles(user_cmd->viewangles);
					}
				}
			}
		}
	}
}

void triggerbot(c_usercmd* user_cmd)
{
	if (!csgo::local_player->is_alive()) /* No reason to run triggerbot if you are dead */
		return;

	const auto weapon_type = csgo::local_player->active_weapon()->get_weapon_data()->weapon_type;

	if (weapon_type == WEAPONTYPE_GRENADE || weapon_type == WEAPONTYPE_KNIFE)
		return;

	if (!csgo::local_player)
		return;

	if (weapon_type == WEAPONTYPE_PISTOL)
	{
		bool can_run = false;

		if (variables::aimbots::legit::pistols::keybindings::triggerbind != 256 && GetAsyncKeyState(variables::aimbots::legit::pistols::keybindings::triggerbind))
		{
			can_run = true;
		}

		if (variables::aimbots::legit::pistols::keybindings::triggerbind == 256)
		{
			can_run = true;
		}

		if (can_run)
		{
			if (variables::aimbots::trigger::pistols::enabled == true)
			{
				ray_t ray;
				trace_filter filter;
				trace_t trace;
				vec3_t start, end, forward;

				math::angle_vectors_alternative(user_cmd->viewangles, &forward);

				forward *= csgo::local_player->active_weapon()->get_weapon_data()->weapon_range;
				start = csgo::local_player->get_eye_pos();
				end = start + forward;
				filter.skip = csgo::local_player;
				ray.initialize(start, end);

				interfaces::trace_ray->trace_ray(ray, 0x46004003, &filter, &trace);

				auto player = trace.entity;
				if (!player)
					return;

				if (player->client_class()->class_id != ccsplayer)
					return;

				if (trace.entity->team() == csgo::local_player->team())
					return;

				if (variables::aimbots::trigger::pistols::head && trace.hitGroup == hitgroup_head)
				{
					user_cmd->buttons |= in_attack;
				}

				if (variables::aimbots::trigger::pistols::chest && trace.hitGroup == hitgroup_chest || variables::aimbots::trigger::pistols::chest && trace.hitGroup == hitgroup_rightarm || variables::aimbots::trigger::pistols::chest && trace.hitGroup == hitgroup_leftarm)
				{
					user_cmd->buttons |= in_attack;
				}

				if (variables::aimbots::trigger::pistols::chest && trace.hitGroup == hitgroup_stomach || variables::aimbots::trigger::pistols::chest && trace.hitGroup == hitgroup_rightarm || variables::aimbots::trigger::pistols::chest && trace.hitGroup == hitgroup_leftarm)
				{
					user_cmd->buttons |= in_attack;
				}
			}
		}
	}

	if (weapon_type == WEAPONTYPE_SUBMACHINEGUN)
	{
		bool can_run = false;

		if (variables::aimbots::legit::smgs::keybindings::triggerbind != 256 && GetAsyncKeyState(variables::aimbots::legit::smgs::keybindings::triggerbind))
		{
			can_run = true;
		}

		if (variables::aimbots::legit::smgs::keybindings::triggerbind == 256)
		{
			can_run = true;
		}

		if (can_run)
		{
			if (variables::aimbots::trigger::smgs::enabled == true)
			{
				ray_t ray;
				trace_filter filter;
				trace_t trace;
				vec3_t start, end, forward;

				math::angle_vectors_alternative(user_cmd->viewangles, &forward);

				forward *= csgo::local_player->active_weapon()->get_weapon_data()->weapon_range;
				start = csgo::local_player->get_eye_pos();
				end = start + forward;
				filter.skip = csgo::local_player;
				ray.initialize(start, end);

				interfaces::trace_ray->trace_ray(ray, 0x46004003, &filter, &trace);

				auto player = trace.entity;
				if (!player)
					return;

				if (player->client_class()->class_id != ccsplayer)
					return;

				if (trace.entity->team() == csgo::local_player->team())
					return;

				if (variables::aimbots::trigger::smgs::head && trace.hitGroup == hitgroup_head)
				{
					user_cmd->buttons |= in_attack;
				}

				if (variables::aimbots::trigger::smgs::chest && trace.hitGroup == hitgroup_chest || variables::aimbots::trigger::smgs::chest && trace.hitGroup == hitgroup_rightarm || variables::aimbots::trigger::smgs::chest && trace.hitGroup == hitgroup_leftarm)
				{
					user_cmd->buttons |= in_attack;
				}

				if (variables::aimbots::trigger::smgs::chest && trace.hitGroup == hitgroup_stomach || variables::aimbots::trigger::smgs::chest && trace.hitGroup == hitgroup_rightarm || variables::aimbots::trigger::smgs::chest && trace.hitGroup == hitgroup_leftarm)
				{
					user_cmd->buttons |= in_attack;
				}
			}
		}
	}

	if (weapon_type == WEAPONTYPE_RIFLE)
	{
		bool can_run = false;

		if (variables::aimbots::legit::rifles::keybindings::triggerbind != 256 && GetAsyncKeyState(variables::aimbots::legit::rifles::keybindings::triggerbind))
		{
			can_run = true;
		}

		if (variables::aimbots::legit::rifles::keybindings::triggerbind == 256)
		{
			can_run = true;
		}

		if (can_run)
		{
			if (variables::aimbots::trigger::rifles::enabled == true)
			{
				ray_t ray;
				trace_filter filter;
				trace_t trace;
				vec3_t start, end, forward;

				math::angle_vectors_alternative(user_cmd->viewangles, &forward);

				forward *= csgo::local_player->active_weapon()->get_weapon_data()->weapon_range;
				start = csgo::local_player->get_eye_pos();
				end = start + forward;
				filter.skip = csgo::local_player;
				ray.initialize(start, end);

				interfaces::trace_ray->trace_ray(ray, 0x46004003, &filter, &trace);

				auto player = trace.entity;
				if (!player)
					return;

				if (player->client_class()->class_id != ccsplayer)
					return;

				if (trace.entity->team() == csgo::local_player->team())
					return;

				if (variables::aimbots::trigger::rifles::head && trace.hitGroup == hitgroup_head)
				{
					user_cmd->buttons |= in_attack;
				}

				if (variables::aimbots::trigger::rifles::chest && trace.hitGroup == hitgroup_chest || variables::aimbots::trigger::rifles::chest && trace.hitGroup == hitgroup_rightarm || variables::aimbots::trigger::rifles::chest && trace.hitGroup == hitgroup_leftarm)
				{
					user_cmd->buttons |= in_attack;
				}

				if (variables::aimbots::trigger::rifles::chest && trace.hitGroup == hitgroup_stomach || variables::aimbots::trigger::rifles::chest && trace.hitGroup == hitgroup_rightarm || variables::aimbots::trigger::rifles::chest && trace.hitGroup == hitgroup_leftarm)
				{
					user_cmd->buttons |= in_attack;
				}
			}
		}
	}

	if (weapon_type == WEAPONTYPE_SNIPER_RIFLE)
	{
		bool can_run = false;

		if (variables::aimbots::legit::snipers::keybindings::triggerbind != 256 && GetAsyncKeyState(variables::aimbots::legit::snipers::keybindings::triggerbind))
		{
			can_run = true;
		}

		if (variables::aimbots::legit::snipers::keybindings::triggerbind == 256)
		{
			can_run = true;
		}

		if (can_run)
		{
			if (variables::aimbots::trigger::snipers::enabled == true)
			{

				if (variables::aimbots::trigger::snipers::scopeCheck == true && csgo::local_player->is_scoped() == false)
					return;

				int trigger_bone[] = { 0, hitgroup_head, hitgroup_chest, hitgroup_stomach };

				ray_t ray;
				trace_filter filter;
				trace_t trace;
				vec3_t start, end, forward;

				math::angle_vectors_alternative(user_cmd->viewangles, &forward);

				forward *= csgo::local_player->active_weapon()->get_weapon_data()->weapon_range;
				start = csgo::local_player->get_eye_pos();
				end = start + forward;
				filter.skip = csgo::local_player;
				ray.initialize(start, end);

				interfaces::trace_ray->trace_ray(ray, 0x46004003, &filter, &trace);

				auto player = trace.entity;

				if (!player)
					return;

				if (player->client_class()->class_id != ccsplayer)
					return;

				if (trace.entity->team() == csgo::local_player->team())
					return;

				if (variables::aimbots::trigger::snipers::head && trace.hitGroup == hitgroup_head)
				{
					user_cmd->buttons |= in_attack;
				}

				if (variables::aimbots::trigger::snipers::chest && trace.hitGroup == hitgroup_chest || variables::aimbots::trigger::snipers::chest && trace.hitGroup == hitgroup_rightarm || variables::aimbots::trigger::snipers::chest && trace.hitGroup == hitgroup_leftarm)
				{
					user_cmd->buttons |= in_attack;
				}

				if (variables::aimbots::trigger::snipers::chest && trace.hitGroup == hitgroup_stomach || variables::aimbots::trigger::snipers::chest && trace.hitGroup == hitgroup_rightarm || variables::aimbots::trigger::snipers::chest && trace.hitGroup == hitgroup_leftarm)
				{
					user_cmd->buttons |= in_attack;
				}

			}
		}
	}
}
