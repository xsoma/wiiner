#include "../../dependencies/utilities/csgo.hpp"
#include "../features/features.hpp"
#include "../features/misc/engine_prediction.hpp"
#include "../menu/menu.hpp"
#include "../features/rage/backtrack.h"

hooks::create_move::fn create_move_original = nullptr;
hooks::paint_traverse::fn paint_traverse_original = nullptr;
hooks::frame_stage_notify::fn frame_stage_notify_original = nullptr;
hooks::draw_model_execute::fn draw_model_execute_original = nullptr;
hooks::sv_cheats::fn sv_cheats_original = nullptr;
hooks::viewmodelfov::fn viewmodelfovorginal = nullptr;
hooks::skipanimation::fn animation_frame_original = nullptr;
hooks::stop_foot_plant::fn foot_plant_original = nullptr;
hooks::build_transformations::fn build_transformations_original = nullptr;
hooks::check_for_sequence_change::fn check_for_sequence_original = nullptr;
hooks::is_hltv::fn htlv_original = nullptr;
hooks::standard_blending_rules::fn standard_blending_rules_original = nullptr;

void FixMovement(c_usercmd* cmd, vec3_t& wishangle)
{
	vec3_t view_fwd, view_right, view_up, cmd_fwd, cmd_right, cmd_up;
	math::angle_vectors(wishangle, &view_fwd, &view_right, &view_up);
	math::angle_vectors(cmd->viewangles, &cmd_fwd, &cmd_right, &cmd_up);

	const auto v8 = sqrtf((view_fwd.x * view_fwd.x) + (view_fwd.y * view_fwd.y));
	const auto v10 = sqrtf((view_right.x * view_right.x) + (view_right.y * view_right.y));
	const auto v12 = sqrtf(view_up.z * view_up.z);

	const vec3_t norm_view_fwd((1.f / v8) * view_fwd.x, (1.f / v8) * view_fwd.y, 0.f);
	const vec3_t norm_view_right((1.f / v10) * view_right.x, (1.f / v10) * view_right.y, 0.f);
	const vec3_t norm_view_up(0.f, 0.f, (1.f / v12) * view_up.z);

	const auto v14 = sqrtf((cmd_fwd.x * cmd_fwd.x) + (cmd_fwd.y * cmd_fwd.y));
	const auto v16 = sqrtf((cmd_right.x * cmd_right.x) + (cmd_right.y * cmd_right.y));
	const auto v18 = sqrtf(cmd_up.z * cmd_up.z);

	const vec3_t norm_cmd_fwd((1.f / v14) * cmd_fwd.x, (1.f / v14) * cmd_fwd.y, 0.f);
	const vec3_t norm_cmd_right((1.f / v16) * cmd_right.x, (1.f / v16) * cmd_right.y, 0.f);
	const vec3_t norm_cmd_up(0.f, 0.f, (1.f / v18) * cmd_up.z);

	const auto v22 = norm_view_fwd.x * cmd->forwardmove;
	const auto v26 = norm_view_fwd.y * cmd->forwardmove;
	const auto v28 = norm_view_fwd.z * cmd->forwardmove;
	const auto v24 = norm_view_right.x * cmd->sidemove;
	const auto v23 = norm_view_right.y * cmd->sidemove;
	const auto v25 = norm_view_right.z * cmd->sidemove;
	const auto v30 = norm_view_up.x * cmd->upmove;
	const auto v27 = norm_view_up.z * cmd->upmove;
	const auto v29 = norm_view_up.y * cmd->upmove;

	cmd->forwardmove = ((((norm_cmd_fwd.x * v24) + (norm_cmd_fwd.y * v23)) + (norm_cmd_fwd.z * v25))
		+ (((norm_cmd_fwd.x * v22) + (norm_cmd_fwd.y * v26)) + (norm_cmd_fwd.z * v28)))
		+ (((norm_cmd_fwd.y * v30) + (norm_cmd_fwd.x * v29)) + (norm_cmd_fwd.z * v27));
	cmd->sidemove = ((((norm_cmd_right.x * v24) + (norm_cmd_right.y * v23)) + (norm_cmd_right.z * v25))
		+ (((norm_cmd_right.x * v22) + (norm_cmd_right.y * v26)) + (norm_cmd_right.z * v28)))
		+ (((norm_cmd_right.x * v29) + (norm_cmd_right.y * v30)) + (norm_cmd_right.z * v27));
	cmd->upmove = ((((norm_cmd_up.x * v23) + (norm_cmd_up.y * v24)) + (norm_cmd_up.z * v25))
		+ (((norm_cmd_up.x * v26) + (norm_cmd_up.y * v22)) + (norm_cmd_up.z * v28)))
		+ (((norm_cmd_up.x * v30) + (norm_cmd_up.y * v29)) + (norm_cmd_up.z * v27));

	const auto ratio = 2.f - fmaxf(fabsf(cmd->sidemove), fabsf(cmd->forwardmove)) / 450.f;
	cmd->forwardmove *= ratio;
	cmd->sidemove *= ratio;

	wishangle = cmd->viewangles;
}

bool hooks::initialize() {
	const auto create_move_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 24));
	const auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(interfaces::panel, 41));
	const auto scene_end = reinterpret_cast<void*>(get_virtual(interfaces::render_view, 41));
	const auto frame_stage_notify = reinterpret_cast<void*>(get_virtual(interfaces::client, 37));
	const auto draw_model_execute = reinterpret_cast<void*>(get_virtual(interfaces::model_render, 21));
	const auto sv_cheats = reinterpret_cast<void*>(get_virtual(interfaces::console->get_convar("sv_cheats"), 13));
	const auto viewmodelfov = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 35));
	const auto animationframe = reinterpret_cast<void*>(utilities::pattern_scan("client.dll", "57 8B F9 8B 07 8B 80 ? ? ? ? FF D0 84 C0 75 02 5F C3"));
	const auto foot_plant = reinterpret_cast<void*>(utilities::pattern_scan("client.dll", "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 57 8B 56 60"));
	const auto build_transformations = reinterpret_cast<void*>(utilities::pattern_scan("client.dll", "55 8B EC 56 8B 75 18 57"));
	const auto check_for_sequence = reinterpret_cast<void*>(utilities::pattern_scan("client.dll", "55 8B EC 51 53 8B 5D 08 56 8B F1 57 85"));
	const auto hltv_target = reinterpret_cast<void*>(get_virtual(interfaces::engine, 93));
	const auto standard_blending_rules_target = reinterpret_cast<void*>(utilities::pattern_scan("client.dll", "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 8B 75 08 57 8B F9 85 F6"));
	
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("failed to initialize MH_Initialize.");

	if (MH_CreateHook(create_move_target, &create_move::hook, reinterpret_cast<void**>(&create_move_original)) != MH_OK)
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");

	if (MH_CreateHook(paint_traverse_target, &paint_traverse::hook, reinterpret_cast<void**>(&paint_traverse_original)) != MH_OK)
		throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");

	if (MH_CreateHook(frame_stage_notify, &frame_stage_notify::hook, reinterpret_cast<void**>(&frame_stage_notify_original)) != MH_OK)
		throw std::runtime_error("failed to initialize frame_stage_notify. (outdated index?)");

	if (MH_CreateHook(draw_model_execute, &draw_model_execute::hook, reinterpret_cast<void**>(&draw_model_execute_original)) != MH_OK)
		throw std::runtime_error("failed to initialize draw_model_execute. (outdated index?)");

	if (MH_CreateHook(sv_cheats, &sv_cheats::hook, reinterpret_cast<void**>(&sv_cheats_original)) != MH_OK)
		throw std::runtime_error("failed to initialize sv_cheats. (outdated index?)");

	if (MH_CreateHook(viewmodelfov, &viewmodelfov::hook, reinterpret_cast<void**>(&viewmodelfovorginal)) != MH_OK)
		throw std::runtime_error("failed to initialize view model fov. (outdated index?)");

	if (MH_CreateHook(animationframe, &skipanimation::hook, reinterpret_cast<void**>(&animation_frame_original)) != MH_OK)
		throw std::runtime_error("failed to initialize skip animation frame. (outdated index?)");

	if (MH_CreateHook(foot_plant, &stop_foot_plant::hook, reinterpret_cast<void**>(&foot_plant_original)) != MH_OK)
		throw std::runtime_error("failed to initialize do procedural foot plant. (outdated index?)");

	if (MH_CreateHook(build_transformations, &build_transformations::hook, reinterpret_cast<void**>(&build_transformations_original)) != MH_OK)
		throw std::runtime_error("failed to initialize build transformations. (outdated index?)");

	if (MH_CreateHook(check_for_sequence, &check_for_sequence_change::hook, reinterpret_cast<void**>(&check_for_sequence_original)) != MH_OK)
		throw std::runtime_error("failed to initialize check for sequence change. (outdated index?)");

	if (MH_CreateHook(hltv_target, &is_hltv::hook, reinterpret_cast<void**>(&htlv_original)) != MH_OK)
		throw std::runtime_error("failed to initialize is_hltv. (outdated index?)");

	if (MH_CreateHook(standard_blending_rules_target, &standard_blending_rules::hook, reinterpret_cast<void**>(&standard_blending_rules_original)) != MH_OK)
		throw std::runtime_error("failed to initialize standard blending rules. (outdated index?)");
	
	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error("failed to enable hooks.");
	
	console::log("[setup] hooks initialized!\n");

	return true;
}

void hooks::release() {
	MH_Uninitialize();

	MH_DisableHook(MH_ALL_HOOKS);
}

bool __stdcall hooks::create_move::hook(float input_sample_frametime, c_usercmd* cmd) {
	create_move_original(input_sample_frametime, cmd);

	if (!cmd || !cmd->command_number)
		return false;

	csgo::local_player = static_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	uintptr_t* frame_pointer;
	__asm mov frame_pointer, ebp;
	bool& send_packet = *reinterpret_cast<bool*>(*frame_pointer - 0x1C);

	auto old_viewangles = cmd->viewangles;
	auto old_forwardmove = cmd->forwardmove;
	auto old_sidemove = cmd->sidemove;

	static bool once = []() {
		backtrack.init();
		return true;
	} ();

	backtrack.update();
	
	misc::movement::bunny_hop(cmd);
	rcs(cmd, cmd->viewangles);
	aimbot(cmd);
	clantag();
	triggerbot(cmd);
	knifehandFlip();
	
	player_t* entity;
	
	prediction::start(cmd); {

		backtrack.run(cmd);

		WRAGEBOT::Run(cmd);
		
		
	} prediction::end();

	WRAGEBOT::antiaim(cmd);
	//FixMovement(cmd, cmd->viewangles);
	// math::correct_movement(old_viewangles, cmd, old_forwardmove, old_sidemove);
	
	cmd->forwardmove = std::clamp(cmd->forwardmove, -450.0f, 450.0f);
	cmd->sidemove = std::clamp(cmd->sidemove, -450.0f, 450.0f);
	cmd->upmove = std::clamp(cmd->upmove, -320.0f, 320.0f);

	cmd->viewangles.normalize();
	cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
	cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
	cmd->viewangles.z = 0.0f;
	
	return false;
}

void __stdcall hooks::paint_traverse::hook(unsigned int panel, bool force_repaint, bool allow_force) {
	auto panel_to_draw = fnv::hash(interfaces::panel->get_panel_name(panel));
	
	switch (panel_to_draw) {
	case fnv::hash("MatSystemTopPanel"):

		antiflash();
		esp();
		boneesp();
		crosshair();
		spreadxhair();
		dropped_weapons();
		bombesp();
		keystroke_display();
		// watermark();
		menu::toggle();
 		menu::render();

		
		break;

	case fnv::hash("FocusOverlayPanel"):
		
		interfaces::panel->set_keyboard_input_enabled(panel, variables::menu::opened);
		interfaces::panel->set_mouse_input_enabled(panel, variables::menu::opened);

		break;
	}

	paint_traverse_original(interfaces::panel, panel, force_repaint, allow_force);
}

void __stdcall hooks::frame_stage_notify::hook(client_frame_stage_t frame_stage) {
	const auto local = static_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	static auto set_interpolation_flags = [](player_t* e, int flag) {
		const auto var_map = (uintptr_t)e + 36;
		const auto sz_var_map = *(int*)(var_map + 20);
		for (auto index = 0; index < sz_var_map; index++)
			*(uintptr_t*)((*(uintptr_t*)var_map) + index * 12) = flag;
	};
	
	switch (frame_stage) {
	case FRAME_UNDEFINED:
		break;
	case FRAME_START:
		break;
	case FRAME_NET_UPDATE_START:
		break;
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		break;
	case FRAME_NET_UPDATE_POSTDATAUPDATE_END:
		break;
	case FRAME_NET_UPDATE_END:
		break;
	case FRAME_RENDER_START:

		if (interfaces::engine->is_in_game())
		{
			WRAGEBOT::fixpvs();
		}

		if (local)
		{
			thirdperson();
			dispatch_logs();
		}
		
		break;
	case FRAME_RENDER_END:
		break;
	default: break;
	}
	frame_stage_notify_original(interfaces::client, frame_stage);
}
void __fastcall hooks::draw_model_execute::hook(void* _this, int edx, i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix) {
	if (interfaces::engine->is_in_game() && interfaces::engine->is_connected() && csgo::local_player) {
		const auto mdl = info.model;
		if (!mdl)
			return;

		bool is_player = strstr(mdl->name, "models/player") != nullptr;

		if (!interfaces::studio_render->is_forced() && is_player) {
			chams(ctx, state, info, matrix);
			draw_model_execute_original(_this, edx, ctx, state, info, matrix);
			interfaces::model_render->override_material(nullptr);
		}
		else if (!interfaces::model_render->is_forced() && !is_player) {
			chams(ctx, state, info, matrix);
			draw_model_execute_original(_this, edx, ctx, state, info, matrix);
			interfaces::model_render->override_material(nullptr);
		}
		else {
			draw_model_execute_original(_this, edx, ctx, state, info, matrix);
		}
	}
}

bool __fastcall hooks::sv_cheats::hook(PVOID convar, int edx) {
	static auto cam_think = utilities::pattern_scan("client.dll", sig_cam_think);

	if (!convar)
		return false;

	if ((_ReturnAddress()) == cam_think)
		return true;
	else
		return sv_cheats_original(convar);
}

float __fastcall hooks::viewmodelfov::hook(PVOID convar)
{
	if (variables::fov::fovOveride)
	{
		return viewmodelfovorginal(convar) + variables::fov::fovamount;
	}
	else
	{
		return viewmodelfovorginal(convar);
	}
}

bool __fastcall hooks::skipanimation::hook(void* this_pointer, void* edx)
{
	/*
	 Prevent copying cached bone data	 
	*/
	
	return false;
}

void __fastcall hooks::stop_foot_plant::hook(void* this_pointer, void* edx, void* bone_to_world, void* left_foot_chain, void* right_foot_chain, void* pos)
{

	/*
	returning nothing prevents leg shuffling 
	*/
	
	return;
}

void __fastcall hooks::build_transformations::hook(void* this_pointer, void* edx, void* hdr, void* pos, void* q, const void* camera_transform, int bone_mask, void* bone_computed)
{

	const auto player = reinterpret_cast<player_t*>(this_pointer);

	/*
	 Stops jiggle physics maybe
	 */
	
	player->jiggle_bones_enabled();

	return build_transformations_original(this_pointer, edx, hdr, pos, q, camera_transform, bone_mask, bone_computed);
}

void __fastcall hooks::check_for_sequence_change::hook(void* this_pointer, void* edx, void* hdr, int cur_sequence, bool force_new_sequence, bool interpolate)
{
	/* Disable nasty ol interpolation */

	return check_for_sequence_original(this_pointer, edx, hdr, cur_sequence, force_new_sequence, false);
}

bool __fastcall hooks::is_hltv::hook(void* this_pointer, void* edx)
{

	return htlv_original(this_pointer, edx);
}

void __fastcall hooks::standard_blending_rules::hook(void* this_pointer, void* edx, void* hdr, void* pos, void* q, float current_time, int bone_mask)
{

	standard_blending_rules_original(this_pointer, edx, hdr, pos, q, current_time, bone_mask);
}
