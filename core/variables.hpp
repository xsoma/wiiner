#pragma once
#include "../features/features.hpp"

static bool in_thirdperson = false;

namespace variables {

	///////////////////////////////////////////


	inline bool get_input = false;
	
	inline bool chamopened = false;
	inline bool bchamsopened = false;
	inline bool canshoot = false;
	
	namespace misc
	{
		inline bool pbunny = true;
		inline bool lbunny = false;
		inline bool antiflash = false;
		inline bool thirdperson = false;
		inline bool canrun = false;
		inline bool dtag = false;
		inline bool stag = false;
		inline bool backtrack = true;
		inline bool airstuck = false;
		inline bool watermark = true;
		inline bool autostrafe = false;
		inline bool nosmoke = false;
		inline bool knifehandflip = false;
		inline bool spreadCircle = false;
		inline bool classicmenu = true;
		inline bool keystroke_display = true;

		inline int thirdpersonbind = 256;
		
	}

	///////////////////////////////////////////

	namespace Visuals
	{
		namespace esp
		{
			inline bool espToggle = true;
			inline bool box = true;
			inline bool healthbar = true;
			inline bool shieldbar = false;
			inline bool name = true;
			inline bool bonevisible = false;
			inline bool bonealways = false;
			inline bool weaponesp = true;
			inline bool hpoverridecheck = true;
			inline bool backtrackskeleton = false;
			inline bool hitmarkers = false;
			inline bool flag_flashed = true;
			inline bool flag_money = true;
			inline bool flag_armor = true;
			inline bool flag_scoped = true;
			inline bool flag_defusekit = true;
			inline bool flag_defusing = true;
			inline bool dropped_wep_names = true;
			inline bool bomb_info = true;
		}

		namespace chams
		{
			inline bool chams = true;
			inline bool chamsxqz = true;
			inline bool chamsvisible = true;
			inline bool chamsalways = false;
			inline bool nohands = false;
			inline bool armschams = false;

			inline bool hands_wireframe = false;
			inline bool wireframe = false;
			inline bool xqz_wireframe = false;
			inline bool backtrackchams = true;
		}

	}

	///////////////////////////////////////////

	namespace aimbots
	{
		inline bool backtrack = true;
		namespace trigger
		{
			namespace pistols
			{
				inline bool enabled = false;
				inline float delay = 0.f;
				inline bool head = true;
				inline bool chest = true;
				inline bool stomach = true;
				inline float hitchance;
			}

			namespace smgs
			{
				inline bool enabled = false;
				inline float delay = 0.f;
				inline bool head = true;
				inline bool chest = true;
				inline bool stomach = true;
				inline float hitchance;
			}

			namespace rifles
			{
				inline bool enabled = false;
				inline float delay = 0.f;
				inline bool head = true;
				inline bool chest = true;
				inline bool stomach = true;
				inline float hitchance;
			}
				
			namespace snipers
			{
				inline bool enabled = false;
				inline float delay = 0.f;
				inline bool head = true;
				inline bool chest = true;
				inline bool stomach = true;
				inline float hitchance;
				inline bool scopeCheck = true;
			}
			
			namespace bones
			{
				inline bool head = false;
				inline bool neck = true;
				inline bool chest = true;
				inline bool legs = false;
			}

		}

		namespace legit
		{
			inline float legit_fov = 30.0f;
			namespace pistols
			{
				namespace keybindings
				{
					inline int aimbotbind = 256;
					inline int triggerbind = 256;
				}
				
				inline bool aimbotToggle = true;
				inline bool crosshair = true;
				inline bool rcs = false;
				inline float smoothing = 2.0f;
				inline bool silentaim = false;
				inline bool randombones = false;
				inline bool ahead = false;
				inline bool achest = false;
				inline bool astomach = false;
				inline bool yisopened = false;
				inline float fov;
				inline bool oof = false;
				inline bool headprioirtybone = false;
				inline bool bodyprioritybone = true;
				inline bool stomachprioritybone = false;
			}

			namespace smgs
			{
				namespace keybindings
				{
					inline int aimbotbind = 256;
					inline int triggerbind = 256;
				}
				
				inline bool aimbotToggle = true;
				inline bool crosshair = true;
				inline bool rcs = false;
				inline float smoothing = 2.0f;
				inline bool silentaim = false;
				inline bool randombones = false;
				inline bool ahead = false;
				inline bool achest = false;
				inline bool astomach = false;
				inline bool yisopened = false;
				inline float fov;
				inline bool oof = false;
				inline bool headprioirtybone = false;
				inline bool bodyprioritybone = true;
				inline bool stomachprioritybone = false;
			}

			namespace rifles
			{
				namespace keybindings
				{
					inline int aimbotbind = 256;
					inline int triggerbind = 256;
				}
				
				inline bool aimbotToggle = true;
				inline bool crosshair = true;
				inline bool rcs = false;
				inline float smoothing = 2.0f;
				inline bool silentaim = false;
				inline bool randombones = false;
				inline bool ahead = false;
				inline bool achest = false;
				inline bool astomach = false;
				inline bool yisopened = false;
				inline float fov;
				inline bool oof = false;
				inline bool headprioirtybone = false;
				inline bool bodyprioritybone = true;
				inline bool stomachprioritybone = false;
			}

			namespace snipers
			{
				namespace keybindings
				{
					inline int aimbotbind = 256;
					inline int triggerbind = 256;
				}
				
				inline bool aimbotToggle = true;
				inline bool crosshair = true;
				inline bool rcs = false;
				inline float smoothing = 2.0f;
				inline bool silentaim = false;
				inline bool randombones = false;
				inline bool ahead = false;
				inline bool achest = false;
				inline bool astomach = false;
				inline bool yisopened = false;
				inline float fov;
				inline bool aimcheck = true;
				inline bool oof = false;
				inline bool headprioirtybone = false;
				inline bool bodyprioritybone = true;
				inline bool stomachprioritybone = false;
				
			}

			inline bool aimbotToggle = true;
			inline bool crosshair = true;
			inline bool rcs = true;
			inline float rcs_x = 0.85f;
			inline float rcs_y = 0.85f;
			inline float smoothing = 2.0f;
			inline bool silentaim = false;
			
		}

		namespace rage
		{
			inline bool autowalling;
			namespace pistols
			{
				inline bool prefer_baim = false;
				inline bool lethal_baim = false;

				////////////////////////////////////

				inline bool head = false;
				inline bool chest = false;
				inline bool stomach = false;
				inline bool pelvis = false;
				inline bool arms = false;
				inline bool legs = false;
				
				////////////////////////////////////
				
				inline bool ragebot = false;
				inline bool ctarget = false;
				inline bool chealth = false;
				inline bool cdistance = false;
				inline float hitchance = 0.0f;
				inline float mindmg = 0.0f;
			}

			namespace h_pistols
			{
				inline bool prefer_baim = false;
				inline bool lethal_baim = false;
				
				////////////////////////////////////

				inline bool head = false;
				inline bool chest = false;
				inline bool stomach = false;
				inline bool pelvis = false;
				inline bool arms = false;
				inline bool legs = false;

				////////////////////////////////////

				inline bool ragebot = false;
				inline bool ctarget = false;
				inline bool chealth = false;
				inline bool cdistance = false;
				inline float hitchance = 0.0f;
				inline float mindmg = 0.0f;
			}

			namespace scout
			{
				inline bool prefer_baim = false;
				inline bool lethal_baim = false;

				////////////////////////////////////

				inline bool head = false;
				inline bool chest = false;
				inline bool stomach = false;
				inline bool pelvis = false;
				inline bool arms = false;
				inline bool legs = false;

				////////////////////////////////////
				
				inline bool ragebot = false;
				inline bool ctarget = false;
				inline bool chealth = false;
				inline bool cdistance = false;
				inline float hitchance = 0.0f;
				inline float mindmg = 0.0f;
			}

			namespace autos
			{
				inline bool prefer_baim = false;
				inline bool lethal_baim = false;

				////////////////////////////////////

				inline bool head = false;
				inline bool chest = false;
				inline bool stomach = false;
				inline bool pelvis = false;
				inline bool arms = false;
				inline bool legs = false;

				////////////////////////////////////
				
				inline bool ragebot = false;
				inline bool ctarget = false;
				inline bool chealth = false;
				inline bool cdistance = false;
				inline float hitchance = 0.0f;
				inline float mindmg = 0.0f;
			}

			namespace awp
			{
				inline bool prefer_baim = false;
				inline bool lethal_baim = false;

				////////////////////////////////////

				inline bool head = false;
				inline bool chest = false;
				inline bool stomach = false;
				inline bool pelvis = false;
				inline bool arms = false;
				inline bool legs = false;

				////////////////////////////////////
				
				inline bool ragebot = false;
				inline bool ctarget = false;
				inline bool chealth = false;
				inline bool cdistance = false;
				inline float hitchance = 0.0f;
				inline float mindmg = 0.0f;
			}
			
		}

		
	}
	///////////////////////////////////////////

	inline bool randombones = true;
	
	namespace fov
	{
		inline bool fovOveride = true;
		inline float fovamount = 36.0f;
	}

	///////////////////////////////////////////

	namespace colors
	{
		namespace menu
		{
			namespace floats
			{
				inline float r = 52.0f;
				inline float g = 134.0f;
				inline float b = 235.0f;
			}
			
			// color(52, 134, 235, 255);
			// 33, 156, 67
			inline color c_menu = color(floats::r, floats::g, floats::b, 255);
		}

		namespace esp
		{
			inline float o_red = 255.0f;
			inline float o_green = 0.0f;
			inline float o_blue = 0.0f;
			inline float hpoverride = 50.0f;
		}
		
		namespace cFloats
		{
			inline float c_red = 255.0f;
			inline float c_green = 180.0f;
			inline float c_blue = 0.0f;
			inline float xqz_c_red = 255.0f;
			inline float xqz_c_green = 255.0f;
			inline float xqz_c_blue = 0.0f;
			inline float b_red = 100.0f;
			inline float b_green = 100.0f;
			inline float b_blue = 255.0f;
		}

		namespace cMats
		{

			namespace arms
			{
				inline bool m_normal = true;
				inline bool m_flat = false;
				inline bool m_crystal = false;
				inline float c_red = 255.0f;
				inline float c_green = 0.0f;
				inline float c_blue = 0.0f;
			}
			
			inline bool m_normal = true;
			inline bool m_flat = false;
			inline bool m_ghost = false;
			inline bool xqz_m_normal = true;
			inline bool xqz_m_flat = false;
			inline bool xqz_m_ghost = false;
		}
		
		inline color chamcolor = color::red();

	}

	///////////////////////////////////////////

	inline bool ahead = false;
	inline bool aneck = false;
	inline bool achest = false;
	inline bool apelvis = false;
	inline bool afeet = false;
	inline bool yisopened = false;

	///////////////////////////////////////////

	namespace antiaim
	{
		inline bool enabled = false;
		inline bool pUp = false;
		inline bool pDown = false;
		inline bool yStatic = false;
		inline bool yJitter = false;
	}

	///////////////////////////////////////////

	namespace weapontypes
	{
		inline bool rifles = false;
		inline bool lmg = false;
		inline bool pistol = false;
		inline bool smg = false;
		inline bool sniper = false;
	}

	///////////////////////////////////////////

	namespace menu
	{

		namespace buttons
		{
			inline bool testbutton = false;
		}
		
		namespace colorpickers
		{
			inline bool espoverrideopened = false;
			
			inline bool visibleopened = false;
			inline bool xqzopened = false;

			inline bool backtrackopen = false;
			
		}
		
		namespace binds
		{
			inline bool pistolbind = false;
			inline bool otherpistolbind = false;
			inline bool pistoltriggerbind = false;
			inline bool othertriggerpistolbind = false;
			inline bool smgbind = false;
			inline bool othersmgbind = false;
			inline bool smgtriggerbind = false;
			inline bool othertriggersmgbind = false;
			inline bool riflebind = false;
			inline bool otherriflebind = false;
			inline bool rifletriggerbind = false;
			inline bool othertriggerriflebind = false;
			inline bool sniperbind = false;
			inline bool othersniperbind = false;
			inline bool snipertriggerbind = false;
			inline bool othertriggersniperbind = false;

			inline bool thirdpersonbind = false;
			inline bool otherthirdpersonbind = false;
		}
		
		namespace tabs
		{
			inline bool legit_pistols = true;
			inline bool legit_smgs = false;
			inline bool legit_rifles = false;
			inline bool legit_snipers = false;
		}
		
		namespace combos
		{
			inline bool pistol_priority = false;
			inline bool smg_priority = false;
			inline bool rifle_priority = false;
			inline bool sniper_priority = false;
			inline bool pistol_trigger_slection = false;
			inline bool smg_trigger_slection = false;
			inline bool rifle_trigger_slection = false;
			inline bool sniper_trigger_slection = false;

			inline bool flag_selection = false;
			inline bool visible_material_selection = false;
			inline bool xqz_material_selection = false;
			
			inline bool clantag_selection = false;
			inline bool bhop_selection = false;

			inline bool config_selection = false;
			
		}

		inline bool opened = true;
		inline bool footer = false;
		
	}

	///////////////////////////////////////////

}