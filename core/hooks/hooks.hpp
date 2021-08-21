#pragma once

namespace hooks {
	bool initialize();
	void release();

	inline unsigned int get_virtual(void* _class, unsigned int index)
	{
		return static_cast<unsigned int>((*static_cast<int**>(_class))[index]);
	}

	namespace create_move {
		using fn = bool(__stdcall*)(float, c_usercmd*);
		bool __stdcall hook(float input_sample_frametime, c_usercmd* cmd);
	};

	namespace paint_traverse {
		using fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
		void __stdcall hook(unsigned int panel, bool force_repaint, bool allow_force);
	}

	namespace frame_stage_notify {
		using fn = void(__thiscall*)(void*, client_frame_stage_t);
		void __stdcall hook(client_frame_stage_t frame_stage);
	}

	namespace draw_model_execute {
		using fn = void(__fastcall*)(void*, int, i_mat_render_context*, const draw_model_state_t&, const model_render_info_t&, matrix_t*);
		void __fastcall hook(void* _this, int edx, i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& pInfo, matrix_t* pCustomBoneToWorld);
	}

	namespace sv_cheats {
		using fn = bool(__thiscall*)(void*);
		bool __fastcall hook(PVOID convar, int edx);
	}

	namespace viewmodelfov {
		using fn = float(__thiscall*)(void*);
		float __fastcall hook(PVOID convar);
	}

	namespace skipanimation {
		using fn = bool(__fastcall*)(void*, void*);
		bool __fastcall hook(void* this_pointer, void* edx);
	}

	namespace stop_foot_plant {
		using fn = void(__fastcall*)(void*, void*, void*, void*, void*, void*);
		void __fastcall hook(void* this_pointer, void* edx, void* bone_to_world, void* left_foot_chain, void* right_foot_chain, void* pos);
	}

	namespace build_transformations {
		using fn = void(__fastcall*)(void*, void*, void*, void*, void*, const void*, int, void*);
		void __fastcall hook(void* this_pointer, void* edx, void* hdr, void* pos, void* q, const void* camera_transform, int bone_mask, void* bone_computed);
	}

	namespace check_for_sequence_change {
		using fn = void(__fastcall*)(void*, void*, void*, int, bool, bool);
		void __fastcall hook(void* this_pointer, void* edx, void* hdr, int cur_sequence, bool force_new_sequence, bool interpolate);
	}

	namespace is_hltv {
		using fn = bool(__fastcall*)(void*, void*);
		bool __fastcall hook(void* this_pointer, void* edx);
	}

	namespace standard_blending_rules {
		using fn = void(__fastcall*)(void*, void*, void*, void*, void*, float, int);
		void __fastcall hook(void* this_pointer, void* edx, void* hdr, void* pos, void* q, float current_time, int bone_mask);
	}
	
}
