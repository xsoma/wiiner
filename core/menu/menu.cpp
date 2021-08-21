#include "menu.hpp"
#include "../../config.h"

namespace variables
{
	namespace menu
	{
		inline int x = 200, y = 200;
		inline int w = 825, h = 500;
	}
}

void menu::render()
{
	if (!variables::menu::opened)
		return;

	render::draw_filled_rect(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h, color(30, 30, 30));
	render::draw_rect(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h, color(10, 10, 10));
	render::draw_rect(variables::menu::x + 1, variables::menu::y + 1, variables::menu::w - 2, variables::menu::h - 2, color(10, 10, 10));
	render::draw_rect(variables::menu::x + 2, variables::menu::y + 2, variables::menu::w - 4, variables::menu::h - 4, color(10, 10, 10));
	render::draw_filled_rect(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h - 495, color(51, 153, 255));
	render::draw_rect(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h - 495, color(10, 10, 10));
	render::draw_filled_rect(variables::menu::x + 3, variables::menu::y + 7, variables::menu::w - 650, variables::menu::h - 10, color(25, 25, 25));
	
	if (variables::menu::footer)
	{
		render::draw_filled_rect(variables::menu::x, variables::menu::y + 525, variables::menu::w, variables::menu::h - 475, color(30, 30, 30));
		render::draw_rect(variables::menu::x, variables::menu::y + 525, variables::menu::w, variables::menu::h - 475, color(10, 10, 10));
	}
	
	menu::quotes(variables::menu::x + 5, variables::menu::y + 525, render::fonts::menucontent);
	
	menu::tab(variables::menu::x, variables::menu::y + 3, 45, 35, render::fonts::bodyfont, "Legit", "a", menu::current_tab, 0, false);
	menu::tab(variables::menu::x, variables::menu::y + 38, 45, 35, render::fonts::bodyfont, "Rage", "a", menu::current_tab, 4, false);
	menu::tab(variables::menu::x + 10, variables::menu::y + 73, 45, 35, render::fonts::bodyfont, "Visuals", "b", menu::current_tab, 1, false);
	menu::tab(variables::menu::x, variables::menu::y + 108, 45, 35, render::fonts::bodyfont, "Misc", "c", menu::current_tab, 2, false);
	menu::tab(variables::menu::x, variables::menu::y + 143, 45, 35, render::fonts::bodyfont, "Skins", "d", menu::current_tab, 3, false);

	switch(current_tab)
	{
	case 0:

		render::draw_filled_rect(variables::menu::x + 225, variables::menu::y + 35, 550, 5, color(50, 50, 50));

		menu::textbutton(variables::menu::x + 225, variables::menu::y + 15, 65, variables::menu::x + 225, render::fonts::headerfont, "Pistols", menu::weapon_current_tab, 0);
		menu::textbutton(variables::menu::x + 305, variables::menu::y + 15, 35, variables::menu::x + 305, render::fonts::headerfont, "SMGS", menu::weapon_current_tab, 1);
		menu::textbutton(variables::menu::x + 355, variables::menu::y + 15, 55, variables::menu::x + 355, render::fonts::headerfont, "Rifles", menu::weapon_current_tab, 2);
		menu::textbutton(variables::menu::x + 425, variables::menu::y + 15, 65, variables::menu::x + 425, render::fonts::headerfont, "Snipers", menu::weapon_current_tab, 3);
		menu::textbutton(variables::menu::x + 505, variables::menu::y + 15, 45, variables::menu::x + 505, render::fonts::headerfont, "Other", menu::weapon_current_tab, 4);

		switch (weapon_current_tab)
		{
		case 0:

			render::draw_text_string(variables::menu::x + 230, variables::menu::y + 60, render::fonts::headerfont, "Aimbot", false, color(255, 255, 255));

			menu::check_box(variables::menu::x + 230, variables::menu::y + 90, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::aimbots::legit::pistols::aimbotToggle);

			menu::keybind(variables::menu::x + 375, variables::menu::y + 90, variables::menu::x + 355, render::fonts::menucontent, variables::aimbots::legit::pistols::keybindings::aimbotbind, variables::menu::binds::pistolbind, variables::menu::binds::otherpistolbind);
			
			menu::check_box(variables::menu::x + 230, variables::menu::y + 110, variables::menu::x + 225, render::fonts::menucontent, "Dynamic Bone Selection", variables::aimbots::legit::pistols::randombones);

			menu::slider(variables::menu::x + 225, variables::menu::y + 140, 150, render::fonts::menucontent, "Smoothing", variables::aimbots::legit::pistols::smoothing, 0, 5);
			
			menu::combo(variables::menu::x + 225, variables::menu::y + 170, variables::menu::x + 225, 30, render::fonts::menucontent, "Bone Priority", variables::menu::combos::pistol_priority, true, std::vector< multi_select_item >{ { "Head", & variables::aimbots::legit::pistols::headprioirtybone }, { "Body", &variables::aimbots::legit::pistols::bodyprioritybone }, { "Stomach", &variables::aimbots::legit::pistols::stomachprioritybone }});

			render::draw_text_string(variables::menu::x + 525, variables::menu::y + 60, render::fonts::headerfont, "Trigger", false, color(255, 255, 255));
			
			menu::check_box(variables::menu::x + 525, variables::menu::y + 90, variables::menu::x + 520, render::fonts::menucontent, "Enabled", variables::aimbots::trigger::pistols::enabled);

			menu::keybind(variables::menu::x + 670, variables::menu::y + 90, variables::menu::x + 650, render::fonts::menucontent, variables::aimbots::legit::pistols::keybindings::triggerbind, variables::menu::binds::pistoltriggerbind, variables::menu::binds::othertriggerpistolbind);

			menu::slider(variables::menu::x + 520, variables::menu::y + 180, 150, render::fonts::menucontent, "Delay", variables::aimbots::trigger::pistols::delay, 0, 1000);

			menu::slider(variables::menu::x + 520, variables::menu::y + 210, 150, render::fonts::menucontent, "Hitchance", variables::aimbots::trigger::pistols::hitchance, 0, 100);

			menu::combo(variables::menu::x + 520, variables::menu::y + 120, variables::menu::x + 525, 30, render::fonts::menucontent, "Hitbox Selection", variables::menu::combos::pistol_trigger_slection, false,std::vector< multi_select_item >{ { "Head", & variables::aimbots::trigger::pistols::head }, { "Body", &variables::aimbots::trigger::pistols::chest }, { "Stomach", &variables::aimbots::trigger::pistols::stomach }});
			
			break;

		case 1:

			render::draw_text_string(variables::menu::x + 230, variables::menu::y + 60, render::fonts::headerfont, "Aimbot", false, color(255, 255, 255));

			menu::check_box(variables::menu::x + 230, variables::menu::y + 90, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::aimbots::legit::smgs::aimbotToggle);

			menu::keybind(variables::menu::x + 375, variables::menu::y + 90, variables::menu::x + 355, render::fonts::menucontent, variables::aimbots::legit::smgs::keybindings::aimbotbind, variables::menu::binds::smgbind, variables::menu::binds::othersmgbind);

			menu::check_box(variables::menu::x + 230, variables::menu::y + 110, variables::menu::x + 225, render::fonts::menucontent, "Dynamic Bone Selection", variables::aimbots::legit::smgs::randombones);

			menu::slider(variables::menu::x + 225, variables::menu::y + 140, 150, render::fonts::menucontent, "Smoothing", variables::aimbots::legit::smgs::smoothing, 0, 5);

			menu::combo(variables::menu::x + 225, variables::menu::y + 170, variables::menu::x + 225, 30, render::fonts::menucontent, "Bone Priority", variables::menu::combos::smg_priority, true, std::vector< multi_select_item >{ { "Head", & variables::aimbots::legit::smgs::headprioirtybone }, { "Body", &variables::aimbots::legit::smgs::bodyprioritybone }, { "Stomach", &variables::aimbots::legit::smgs::stomachprioritybone }});

			render::draw_text_string(variables::menu::x + 525, variables::menu::y + 60, render::fonts::headerfont, "Trigger", false, color(255, 255, 255));

			menu::check_box(variables::menu::x + 525, variables::menu::y + 90, variables::menu::x + 520, render::fonts::menucontent, "Enabled", variables::aimbots::trigger::smgs::enabled);

			menu::keybind(variables::menu::x + 670, variables::menu::y + 90, variables::menu::x + 650, render::fonts::menucontent, variables::aimbots::legit::smgs::keybindings::triggerbind, variables::menu::binds::smgtriggerbind, variables::menu::binds::othertriggersmgbind);

			menu::slider(variables::menu::x + 520, variables::menu::y + 180, 150, render::fonts::menucontent, "Delay", variables::aimbots::trigger::smgs::delay, 0, 1000);

			menu::slider(variables::menu::x + 520, variables::menu::y + 210, 150, render::fonts::menucontent, "Hitchance", variables::aimbots::trigger::smgs::hitchance, 0, 100);

			menu::combo(variables::menu::x + 520, variables::menu::y + 120, variables::menu::x + 525, 30, render::fonts::menucontent, "Hitbox Selection", variables::menu::combos::smg_trigger_slection, false, std::vector< multi_select_item >{ { "Head", & variables::aimbots::trigger::smgs::head }, { "Body", &variables::aimbots::trigger::smgs::chest }, { "Stomach", &variables::aimbots::trigger::smgs::stomach }});

			break;

		case 2:

			render::draw_text_string(variables::menu::x + 230, variables::menu::y + 60, render::fonts::headerfont, "Aimbot", false, color(255, 255, 255));

			menu::check_box(variables::menu::x + 230, variables::menu::y + 90, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::aimbots::legit::rifles::aimbotToggle);

			menu::keybind(variables::menu::x + 375, variables::menu::y + 90, variables::menu::x + 355, render::fonts::menucontent, variables::aimbots::legit::rifles::keybindings::aimbotbind, variables::menu::binds::riflebind, variables::menu::binds::otherriflebind);

			menu::check_box(variables::menu::x + 230, variables::menu::y + 110, variables::menu::x + 225, render::fonts::menucontent, "Dynamic Bone Selection", variables::aimbots::legit::rifles::randombones);

			menu::slider(variables::menu::x + 225, variables::menu::y + 140, 150, render::fonts::menucontent, "Smoothing", variables::aimbots::legit::rifles::smoothing, 0, 5);

			menu::combo(variables::menu::x + 225, variables::menu::y + 170, variables::menu::x + 225, 30, render::fonts::menucontent, "Bone Priority", variables::menu::combos::rifle_priority, true, std::vector< multi_select_item >{ { "Head", & variables::aimbots::legit::rifles::headprioirtybone }, { "Body", &variables::aimbots::legit::rifles::bodyprioritybone }, { "Stomach", &variables::aimbots::legit::rifles::stomachprioritybone }});

			render::draw_text_string(variables::menu::x + 525, variables::menu::y + 60, render::fonts::headerfont, "Trigger", false, color(255, 255, 255));

			menu::check_box(variables::menu::x + 525, variables::menu::y + 90, variables::menu::x + 520, render::fonts::menucontent, "Enabled", variables::aimbots::trigger::rifles::enabled);

			menu::keybind(variables::menu::x + 670, variables::menu::y + 90, variables::menu::x + 650, render::fonts::menucontent, variables::aimbots::legit::rifles::keybindings::triggerbind, variables::menu::binds::rifletriggerbind, variables::menu::binds::othertriggerriflebind);

			menu::slider(variables::menu::x + 520, variables::menu::y + 180, 150, render::fonts::menucontent, "Delay", variables::aimbots::trigger::rifles::delay, 0, 1000);

			menu::slider(variables::menu::x + 520, variables::menu::y + 210, 150, render::fonts::menucontent, "Hitchance", variables::aimbots::trigger::rifles::hitchance, 0, 100);

			menu::combo(variables::menu::x + 520, variables::menu::y + 120, variables::menu::x + 525, 30, render::fonts::menucontent, "Hitbox Selection", variables::menu::combos::rifle_trigger_slection, false, std::vector< multi_select_item >{ { "Head", & variables::aimbots::trigger::rifles::head }, { "Body", &variables::aimbots::trigger::rifles::chest }, { "Stomach", &variables::aimbots::trigger::rifles::stomach }});

			break;

		case 3:

			render::draw_text_string(variables::menu::x + 230, variables::menu::y + 60, render::fonts::headerfont, "Aimbot", false, color(255, 255, 255));

			menu::check_box(variables::menu::x + 230, variables::menu::y + 90, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::aimbots::legit::snipers::aimbotToggle);

			menu::keybind(variables::menu::x + 375, variables::menu::y + 90, variables::menu::x + 355, render::fonts::menucontent, variables::aimbots::legit::snipers::keybindings::aimbotbind, variables::menu::binds::sniperbind, variables::menu::binds::othersniperbind);

			menu::check_box(variables::menu::x + 230, variables::menu::y + 110, variables::menu::x + 225, render::fonts::menucontent, "Dynamic Bone Selection", variables::aimbots::legit::snipers::randombones);

			menu::slider(variables::menu::x + 225, variables::menu::y + 140, 150, render::fonts::menucontent, "Smoothing", variables::aimbots::legit::snipers::smoothing, 0, 5);

			menu::check_box(variables::menu::x + 230, variables::menu::y + 220, variables::menu::x + 225, render::fonts::menucontent, "Scope Check", variables::aimbots::legit::snipers::aimcheck);
			
			menu::combo(variables::menu::x + 225, variables::menu::y + 170, variables::menu::x + 225, 30, render::fonts::menucontent, "Bone Priority", variables::menu::combos::sniper_priority, true, std::vector< multi_select_item >{ { "Head", & variables::aimbots::legit::snipers::headprioirtybone }, { "Body", &variables::aimbots::legit::snipers::bodyprioritybone }, { "Stomach", &variables::aimbots::legit::snipers::stomachprioritybone }});

			render::draw_text_string(variables::menu::x + 525, variables::menu::y + 60, render::fonts::headerfont, "Trigger", false, color(255, 255, 255));

			menu::check_box(variables::menu::x + 525, variables::menu::y + 90, variables::menu::x + 520, render::fonts::menucontent, "Enabled", variables::aimbots::trigger::snipers::enabled);

			menu::keybind(variables::menu::x + 670, variables::menu::y + 90, variables::menu::x + 650, render::fonts::menucontent, variables::aimbots::legit::snipers::keybindings::triggerbind, variables::menu::binds::smgtriggerbind, variables::menu::binds::othertriggersmgbind);

			menu::slider(variables::menu::x + 520, variables::menu::y + 180, 150, render::fonts::menucontent, "Delay", variables::aimbots::trigger::snipers::delay, 0, 1000);

			menu::slider(variables::menu::x + 520, variables::menu::y + 210, 150, render::fonts::menucontent, "Hitchance", variables::aimbots::trigger::snipers::hitchance, 0,100);

			menu::check_box(variables::menu::x + 525, variables::menu::y + 240, variables::menu::x + 520, render::fonts::menucontent, "Scope Check", variables::aimbots::trigger::snipers::scopeCheck);
			
			menu::combo(variables::menu::x + 520, variables::menu::y + 120, variables::menu::x + 525, 30, render::fonts::menucontent, "Hitbox Selection", variables::menu::combos::sniper_trigger_slection, false, std::vector< multi_select_item >{ { "Head", & variables::aimbots::trigger::snipers::head }, { "Body", &variables::aimbots::trigger::snipers::chest }, { "Stomach", &variables::aimbots::trigger::snipers::stomach }});

			break;

		case 4:

			menu::check_box(variables::menu::x + 230, variables::menu::y + 70, variables::menu::x + 225, render::fonts::menucontent, "Backtrack", variables::aimbots::backtrack);
			menu::check_box(variables::menu::x + 230, variables::menu::y + 90, variables::menu::x + 225, render::fonts::menucontent, "Recoil Crosshair", variables::aimbots::legit::crosshair);
			menu::check_box(variables::menu::x + 230, variables::menu::y + 110, variables::menu::x + 225, render::fonts::menucontent, "Recoil Control", variables::aimbots::legit::rcs);
			menu::slider(variables::menu::x + 225, variables::menu::y + 140, 150, render::fonts::menucontent, "Recoil Control X", variables::aimbots::legit::rcs_x, 0, 1);
			menu::slider(variables::menu::x + 225, variables::menu::y + 170, 150, render::fonts::menucontent, "Recoil Control Y", variables::aimbots::legit::rcs_y, 0, 1);

			break;
		}
		
		break;

	case 1:

		render::draw_filled_rect(variables::menu::x + 225, variables::menu::y + 35, 550, 5, color(50, 50, 50));

		menu::textbutton(variables::menu::x + 225, variables::menu::y + 15, 25, variables::menu::x + 225, render::fonts::headerfont, "ESP", menu::visuals_current_tab, 0);
		menu::textbutton(variables::menu::x + 265, variables::menu::y + 15, 35, variables::menu::x + 265, render::fonts::headerfont, "Glow", menu::visuals_current_tab, 1);
		menu::textbutton(variables::menu::x + 315, variables::menu::y + 15, 115, variables::menu::x + 315, render::fonts::headerfont, "Chams Visible", menu::visuals_current_tab, 2);
		menu::textbutton(variables::menu::x + 445, variables::menu::y + 15, 80, variables::menu::x + 445, render::fonts::headerfont, "Chams XQZ", menu::visuals_current_tab, 3);
		menu::textbutton(variables::menu::x + 540, variables::menu::y + 15, 45, variables::menu::x + 540, render::fonts::headerfont, "World", menu::visuals_current_tab, 4);
		menu::textbutton(variables::menu::x + 600, variables::menu::y + 15, 95, variables::menu::x + 600, render::fonts::headerfont, "Localplayer", menu::visuals_current_tab, 5);

		switch (visuals_current_tab)
		{
		case 0:

			menu::check_box(variables::menu::x + 230, variables::menu::y + 70, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::Visuals::esp::espToggle);
			menu::check_box(variables::menu::x + 230, variables::menu::y + 90, variables::menu::x + 225, render::fonts::menucontent, "Name", variables::Visuals::esp::name);
			menu::check_box(variables::menu::x + 230, variables::menu::y + 110, variables::menu::x + 225, render::fonts::menucontent, "Box", variables::Visuals::esp::box);
			menu::check_box(variables::menu::x + 230, variables::menu::y + 130, variables::menu::x + 225, render::fonts::menucontent, "Health Bar", variables::Visuals::esp::healthbar);
			menu::check_box(variables::menu::x + 230, variables::menu::y + 150, variables::menu::x + 225, render::fonts::menucontent, "Shield Bar", variables::Visuals::esp::shieldbar);
			menu::check_box(variables::menu::x + 230, variables::menu::y + 170, variables::menu::x + 225, render::fonts::menucontent, "Hitmarkers", variables::Visuals::esp::hitmarkers);
			menu::check_box(variables::menu::x + 230, variables::menu::y + 190, variables::menu::x + 225, render::fonts::menucontent, "Health Override", variables::Visuals::esp::hpoverridecheck);
			menu::color_picker(variables::menu::x + 365, variables::menu::y + 192, variables::menu::x + 365, render::fonts::menucontent, "", variables::menu::colorpickers::espoverrideopened, variables::colors::esp::o_red, variables::colors::esp::o_green, variables::colors::esp::o_blue);
			
			menu::slider(variables::menu::x + 225, variables::menu::y + 220, 150, render::fonts::menucontent, "Override Health", variables::colors::esp::hpoverride, 1, 100);
			
			
			menu::combo(variables::menu::x + 225, variables::menu::y + 250, variables::menu::x + 225, 85, render::fonts::menucontent, "Flags", variables::menu::combos::flag_selection, false, std::vector< multi_select_item >{ { "Defusing", &variables::Visuals::esp::flag_defusing}, { "Money", &variables::Visuals::esp::flag_money }, { "Armor", &variables::Visuals::esp::flag_armor }, { "Scoped", &variables::Visuals::esp::flag_scoped }, { "Flashed", &variables::Visuals::esp::flag_flashed }, { "Defuse Kit", &variables::Visuals::esp::flag_defusekit }, { "Weapon", &variables::Visuals::esp::weaponesp } });

			
			break;

		case 1:



			break;

		case 2:

			menu::check_box(variables::menu::x + 230, variables::menu::y + 70, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::Visuals::chams::chamsvisible);
			menu::color_picker(variables::menu::x + 320, variables::menu::y + 71, variables::menu::x + 320, render::fonts::menucontent, "", variables::menu::colorpickers::visibleopened, variables::colors::cFloats::c_red, variables::colors::cFloats::c_green, variables::colors::cFloats::c_blue);
			
			menu::check_box(variables::menu::x + 230, variables::menu::y + 90, variables::menu::x + 225, render::fonts::menucontent, "Wireframe", variables::Visuals::chams::wireframe);

			menu::combo(variables::menu::x + 225, variables::menu::y + 120, variables::menu::x + 225, 30, render::fonts::menucontent, "Material", variables::menu::combos::visible_material_selection, true, std::vector< multi_select_item >{ { "Normal", & variables::colors::cMats::m_normal}, { "Flat", &variables::colors::cMats::m_flat }, { "Blue Uber", &variables::colors::cMats::m_ghost }});
			
			break;

		case 3:

			menu::check_box(variables::menu::x + 230, variables::menu::y + 70, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::Visuals::chams::chamsxqz);
			menu::color_picker(variables::menu::x + 320, variables::menu::y + 71, variables::menu::x + 320, render::fonts::menucontent, "", variables::menu::colorpickers::xqzopened, variables::colors::cFloats::xqz_c_red, variables::colors::cFloats::xqz_c_green, variables::colors::cFloats::xqz_c_blue);
			menu::check_box(variables::menu::x + 230, variables::menu::y + 90, variables::menu::x + 225, render::fonts::menucontent, "Wireframe", variables::Visuals::chams::xqz_wireframe);
			menu::check_box(variables::menu::x + 230, variables::menu::y + 110, variables::menu::x + 225, render::fonts::menucontent, "Backtrack", variables::Visuals::chams::backtrackchams);
			menu::color_picker(variables::menu::x + 330, variables::menu::y + 111, variables::menu::x + 330, render::fonts::menucontent, "", variables::menu::colorpickers::backtrackopen, variables::colors::cFloats::b_red, variables::colors::cFloats::b_green, variables::colors::cFloats::b_blue);
			
			menu::combo(variables::menu::x + 225, variables::menu::y + 140, variables::menu::x + 225, 30, render::fonts::menucontent, "Material", variables::menu::combos::xqz_material_selection, true, std::vector< multi_select_item >{ { "Normal", & variables::colors::cMats::xqz_m_normal}, { "Flat", &variables::colors::cMats::xqz_m_flat }, { "Blue Uber", &variables::colors::cMats::xqz_m_ghost }});
			
			break;

		case 4:



			break;

		case 5:



			break;
		}
		
		break;

	case 2:

		render::draw_filled_rect(variables::menu::x + 225, variables::menu::y + 35, 550, 5, color(50, 50, 50));

		menu::textbutton(variables::menu::x + 220, variables::menu::y + 15, 60, variables::menu::x + 225, render::fonts::headerfont, "General", menu::misc_current_tab, 0);

		menu::textbutton(variables::menu::x + 300, variables::menu::y + 15, 55, variables::menu::x + 305, render::fonts::headerfont, "Config", menu::misc_current_tab, 1);

		switch (misc_current_tab)
		{
		case 0:

			menu::check_box(variables::menu::x + 225, variables::menu::y + 70, variables::menu::x + 220, render::fonts::menucontent, "Antiflash", variables::misc::antiflash);
			menu::check_box(variables::menu::x + 225, variables::menu::y + 90, variables::menu::x + 220, render::fonts::menucontent, "Auto Strafe", variables::misc::autostrafe);
			menu::check_box(variables::menu::x + 225, variables::menu::y + 110, variables::menu::x + 220, render::fonts::menucontent, "Spread Circle", variables::misc::spreadCircle);
			menu::check_box(variables::menu::x + 225, variables::menu::y + 130, variables::menu::x + 220, render::fonts::menucontent, "Thirdperson", variables::misc::thirdperson);

			menu::keybind(variables::menu::x + 400, variables::menu::y + 130, variables::menu::x + 400, render::fonts::menucontent, variables::misc::thirdpersonbind, variables::menu::binds::thirdpersonbind, variables::menu::binds::otherthirdpersonbind);
			
			menu::check_box(variables::menu::x + 225, variables::menu::y + 150, variables::menu::x + 220, render::fonts::menucontent, "Watermark", variables::misc::watermark);

			menu::check_box(variables::menu::x + 225, variables::menu::y + 240, variables::menu::x + 220, render::fonts::menucontent, "Viewmodel Fov Override", variables::fov::fovOveride);

			menu::slider(variables::menu::x + 220, variables::menu::y + 270, 150, render::fonts::menucontent, "Viewmodel Fov Override Amount", variables::fov::fovamount, 0, 180);
			
			menu::combo(variables::menu::x + 220, variables::menu::y + 180, variables::menu::x + 220, 15, render::fonts::menucontent, "Bunny Hop", variables::menu::combos::bhop_selection, true, std::vector< multi_select_item >{ { "Perfect Hop", & variables::misc::pbunny }, { "Legit Hop", &variables::misc::lbunny }});

			menu::check_box(variables::menu::x + 225, variables::menu::y + 360, variables::menu::x + 220, render::fonts::menucontent, "Keystroke Display", variables::misc::keystroke_display);

			menu::check_box(variables::menu::x + 225, variables::menu::y + 380, variables::menu::x + 220, render::fonts::menucontent, "Info Footer", variables::menu::footer);
			
			menu::combo(variables::menu::x + 220, variables::menu::y + 300, variables::menu::x + 220, 15, render::fonts::menucontent, "Clantag", variables::menu::combos::clantag_selection, true, std::vector< multi_select_item >{ { "Static", & variables::misc::stag }, { "Dynamic", &variables::misc::dtag }});

			
			break;

		case 1:
			
			menu::button(variables::menu::x + 220, variables::menu::y + 130, variables::menu::x + 220, render::fonts::menucontent, "Save Config", [&](bool& holder)
			{
					C::Save("");
					holder = !holder;
			});

			menu::button(variables::menu::x + 220, variables::menu::y + 180, variables::menu::x + 220, render::fonts::menucontent, "Load Config", [&](bool& holder)
			{
					C::Load("");
					holder = !holder;
			});

			break;
		}
		
		break;

	case 3:

		render::draw_filled_rect(variables::menu::x + 225, variables::menu::y + 35, 550, 5, color(50, 50, 50));
		
		break;

	case 4:

		render::draw_filled_rect(variables::menu::x + 225, variables::menu::y + 35, 550, 5, color(50, 50, 50));

		menu::textbutton(variables::menu::x + 225, variables::menu::y + 15, 55, variables::menu::x + 225, render::fonts::headerfont, "Pistol", menu::rage_weapon_current_tab, 0);
		menu::textbutton(variables::menu::x + 295, variables::menu::y + 15, 110, variables::menu::x + 295, render::fonts::headerfont, "Heavy Pistol", menu::rage_weapon_current_tab, 1);
		menu::textbutton(variables::menu::x + 420, variables::menu::y + 15, 45, variables::menu::x + 420, render::fonts::headerfont, "Scout", menu::rage_weapon_current_tab, 2);
		menu::textbutton(variables::menu::x + 480, variables::menu::y + 15, 35, variables::menu::x + 480, render::fonts::headerfont, "Auto", menu::rage_weapon_current_tab, 3);
		menu::textbutton(variables::menu::x + 530, variables::menu::y + 15, 25, variables::menu::x + 530, render::fonts::headerfont, "AWP", menu::rage_weapon_current_tab, 4);
		menu::textbutton(variables::menu::x + 570, variables::menu::y + 15, 65, variables::menu::x + 570, render::fonts::headerfont, "Antiaim", menu::rage_weapon_current_tab, 5);
		menu::textbutton(variables::menu::x + 650, variables::menu::y + 15, 45, variables::menu::x + 650, render::fonts::headerfont, "Other", menu::rage_weapon_current_tab, 6);

		switch (rage_weapon_current_tab)
		{
		case 0:

			menu::check_box(variables::menu::x + 230, variables::menu::y + 70, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::aimbots::rage::pistols::ragebot);

			menu::slider(variables::menu::x + 225, variables::menu::y + 160, 150, render::fonts::menucontent, "Hitchance", variables::aimbots::rage::pistols::hitchance, 0, 100);

			menu::check_box(variables::menu::x + 230, variables::menu::y + 190, variables::menu::x + 225, render::fonts::menucontent, "Lethal BAIM", variables::aimbots::rage::pistols::lethal_baim);

			menu::check_box(variables::menu::x + 230, variables::menu::y + 210, variables::menu::x + 225, render::fonts::menucontent, "Prefer BAIM", variables::aimbots::rage::pistols::prefer_baim);

			menu::slider(variables::menu::x + 225, variables::menu::y + 240, 150, render::fonts::menucontent, "Min Damage", variables::aimbots::rage::pistols::mindmg, 0, 100);
			
			menu::combo(variables::menu::x + 225, variables::menu::y + 100, variables::menu::x + 225, 62, render::fonts::menucontent, "Hitbox Selection", variables::menu::combos::bhop_selection, false, std::vector< multi_select_item >{ { "Head", & variables::aimbots::rage::pistols::head }, { "Chest", &variables::aimbots::rage::pistols::chest }, { "Stomach", &variables::aimbots::rage::pistols::stomach }, { "Arms", &variables::aimbots::rage::pistols::arms }, { "Legs", &variables::aimbots::rage::pistols::legs }});
			
			break;
			
		case 1:

			menu::check_box(variables::menu::x + 230, variables::menu::y + 70, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::aimbots::rage::h_pistols::ragebot);

			break;
			
		case 2:

			menu::check_box(variables::menu::x + 230, variables::menu::y + 70, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::aimbots::rage::scout::ragebot);

			break;
			
		case 3:

			menu::check_box(variables::menu::x + 230, variables::menu::y + 70, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::aimbots::rage::autos::ragebot);

			break;
			
		case 4:

			menu::check_box(variables::menu::x + 230, variables::menu::y + 70, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::aimbots::rage::awp::ragebot);

			break;
			
		case 5:

			menu::check_box(variables::menu::x + 230, variables::menu::y + 70, variables::menu::x + 225, render::fonts::menucontent, "Enabled", variables::antiaim::enabled);

			break;
			
		case 6:

			break;
		}
		
		break;
	}
	
	menu_framework::menu_movement(variables::menu::x, variables::menu::y, variables::menu::w, 30);
}

void menu::toggle()
{
	if (GetAsyncKeyState(VK_F6) & 1)
		variables::menu::opened = !variables::menu::opened;
}