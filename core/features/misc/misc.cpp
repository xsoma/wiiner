#include "../features.hpp"

void mouseStrafer(c_usercmd* cmd)
{
	if (variables::misc::autostrafe == true)
	{
		static bool flip = true;

		if (!csgo::local_player || !csgo::local_player->is_alive())
			return;

		if (csgo::local_player->flags() & fl_onground)
			return;

		cmd->forwardmove = 0.0f;
		cmd->sidemove = 0.0f;

		if (cmd->mousedx < 0)
		{
			cmd->sidemove = -450.0f;
		}
		else if (cmd->mousedx > 0)
		{
			cmd->sidemove = 450.0f;
		}
		else
		{
			if (flip)
			{
				cmd->viewangles = math::normalize(vec3_t(cmd->viewangles.x, cmd->viewangles.y - 1.0f, 0.0f));
				cmd->sidemove = -450.0f;
				flip = false;
			}
			else
			{
				cmd->viewangles = math::normalize(vec3_t(cmd->viewangles.x, cmd->viewangles.y + 1.0f, 0.0f));
				cmd->sidemove = 450.0f;
				flip = true;
			}
		}
	}
}

void misc::movement::bunny_hop(c_usercmd* cmd) {

	mouseStrafer(cmd);

	if (variables::misc::pbunny == true)
	{
		const int move_type = csgo::local_player->move_type();

		if (move_type == movetype_ladder || move_type == movetype_noclip || move_type == movetype_observer)
			return;

		if (!(csgo::local_player->flags() & fl_onground))
			cmd->buttons &= ~in_jump;
	}

	if (variables::misc::lbunny == true) // legit bhop
	{
		srand(time(0));
		int random = rand() % 4 + 1;
		int jumpamount = 0;

		const int move_type = csgo::local_player->move_type();

		if (move_type == movetype_ladder || move_type == movetype_noclip || move_type == movetype_observer)
			return;

		if (!(csgo::local_player->flags() & fl_onground))
		{
			if (jumpamount <= 1)
			{
				random == 1;
			}

			if (random == 1 || random == 2 && jumpamount < 3)
			{
				cmd->buttons &= ~in_jump;
				jumpamount++;

				if (jumpamount > 3)
				{
					jumpamount = 0;
				}

			}
			jumpamount = 0;
		}

	}

};

void antiflash()
{
	if (variables::misc::antiflash == true)
	{
		if (csgo::local_player->is_flashed() == true)
		{
			csgo::local_player->flash_duration() = 0;
		}
	}
}

void thirdperson()
{
	if (variables::misc::thirdperson)
	{
		if (variables::misc::thirdpersonbind != 256 && GetAsyncKeyState(variables::misc::thirdpersonbind) & 1)
		{
			variables::misc::canrun = !variables::misc::canrun;
		}

		if (variables::misc::thirdpersonbind == 256)
		{
			variables::misc::canrun = true;
		}

		if (interfaces::input->camera_in_third_person = variables::misc::canrun)
		{
			interfaces::input->camera_offset.z = 100;
			interfaces::input->camera_offset.x = 0;
		}
	}
}

void set_clantag(std::string clantag)
{
	static auto clantag_original = (int(__fastcall*)(const char*, const char*))utilities::pattern_scan("engine.dll", "53 56 57 8B DA 8B F9 FF 15");
	clantag_original(clantag.c_str(), clantag.c_str());
}

void clantag()
{
	if (variables::misc::dtag == true)
	{
		static float last_change = 0.f;
		if (interfaces::globals->realtime - last_change >= 0.25f) {
			std::string clantag = "";
			switch (int(interfaces::globals->cur_time * 4.f) % 38) { //add latency for better sync
			case 0:  clantag = "               "; break;
			case 1:  clantag = "              W"; break;
			case 2:  clantag = "             Wi"; break;
			case 3:  clantag = "            Wii"; break;
			case 4:  clantag = "           Wiin"; break;
			case 5:  clantag = "          Wiine"; break;
			case 6:  clantag = "         Wiiner"; break;
			case 7:  clantag = "         WiinerH"; break;
			case 8:  clantag = "         WiinerHa"; break;
			case 9:  clantag = "         WiinerHac"; break;
			case 10:  clantag = "        WiinerHack"; break;
			case 11:  clantag = "        WiinerHac k"; break;
			case 12:  clantag = "        WiinerHa c k"; break;
			case 14:  clantag = "        WiinerH a c k"; break;
			case 15:  clantag = "        Wiiner H a c k"; break;
			case 16:  clantag = "        Wiine r H a c k"; break;
			case 17:  clantag = "        Wiin e r H a c k"; break;
			case 18:  clantag = "        Wii n e r H a c k"; break;
			case 19:  clantag = "        Wi i n e r H a c k"; break;
			case 20:  clantag = "        W i i n e r H a c k"; break;
			case 21:  clantag = "        Wi i n e r H a c k"; break;
			case 22:  clantag = "        Wii n e r H a c k"; break;
			case 23:  clantag = "        Wiin e r H a c k"; break;
			case 24:  clantag = "        Wiine r H a c k"; break;
			case 25:  clantag = "        Wiiner H a c k"; break;
			case 26:  clantag = "        WiinerH a c k"; break;
			case 27:  clantag = "        WiinerHa c k"; break;
			case 28:  clantag = "        WiinerHac k"; break;
			case 29:  clantag = "        WiinerHack"; break;
			}
			set_clantag(clantag);
			last_change = interfaces::globals->realtime;
		}
	}

	if (variables::misc::stag == true)
	{
		set_clantag("WiinerHack");
	}

	if (variables::misc::dtag == false && variables::misc::stag == false)
	{
		set_clantag("");
	}

}

void crosshair()
{
	if (variables::aimbots::legit::crosshair == true && variables::aimbots::legit::rcs == false && interfaces::engine->is_in_game())
	{
		if (!csgo::local_player || !csgo::local_player->is_alive())
			return;

		interfaces::console->get_convar("crosshair")->set_value(0);

		std::pair<int, int> screen_size;

		interfaces::surface->get_screen_size(screen_size.first, screen_size.second);
		int x = screen_size.first / 2;
		int y = screen_size.second / 2;

		if (variables::aimbots::legit::crosshair == 1) {
			vec3_t punch = csgo::local_player->aim_punch_angle();
			if (csgo::local_player->is_scoped())
				punch /= .5f;

			// subtract the punch from the position
			x -= (screen_size.first / 90) * punch.y;
			y += (screen_size.second / 90) * punch.x;
		}

		render::draw_xhair(x, y, true, color::white());

	}

	if (variables::aimbots::legit::crosshair == true && variables::aimbots::legit::rcs == true && interfaces::engine->is_in_game())
	{
		interfaces::console->get_convar("crosshair")->set_value(0);

		if (!csgo::local_player || !csgo::local_player->is_alive())
			return;

		std::pair<int, int> screen_size;

		interfaces::surface->get_screen_size(screen_size.first, screen_size.second);
		int x = screen_size.first / 2;
		int y = screen_size.second / 2;
		render::draw_xhair(x, y, true, color::white());
	}

	if (variables::aimbots::legit::crosshair == false)
	{
		interfaces::console->get_convar("crosshair")->set_value(1);
	}

}

void log(c_usercmd* cmd)
{
	if (interfaces::engine->is_in_game() == true)
	{
		std::string viewangles = std::to_string(cmd->viewangles.x);

	}
}

void Fov()
{
	if (csgo::local_player == nullptr)
		return;

	if (!csgo::local_player->is_alive())
		return;


}

void watermark()
{
	if (variables::misc::watermark == true)
	{
		if (interfaces::engine->is_in_game() == true)
		{
			for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++)
			{
				player_info_t playerinfo;
				interfaces::engine->get_player_info(iPlayer, &playerinfo);

				auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));

				if (pCSPlayer == csgo::local_player)
				{
					if (csgo::local_player == nullptr)
						return;

					std::string name = playerinfo.name;
					std::string weapon = csgo::local_player->active_weapon()->get_weapon_data()->weapon_name_alt;

					render::draw_filled_rect(1600, 30, 500, 20, color(45, 45, 45, 120));
					render::draw_text_string(1720, 33, render::fonts::watermark_font, name + " | ", true, color(255, 255, 255));
					render::draw_text_string(1840, 33, render::fonts::watermark_font, weapon + " | ", true, color(255, 255, 255));
				}
			}
		}
	}
}

void knifehandFlip()
{
	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	if (csgo::local_player == nullptr)
		return;

	if (variables::misc::knifehandflip)
	{
		if (csgo::local_player->active_weapon()->get_weapon_data()->weapon_type == WEAPONTYPE_KNIFE)
		{
			interfaces::console->get_convar("cl_righthand")->set_value(0);
		}
		else
		{
			interfaces::console->get_convar("cl_righthand")->set_value(1);
		}
	}
}

void spreadxhair()
{
	if (variables::misc::spreadCircle)
	{
		if (!csgo::local_player || !csgo::local_player->is_alive())
			return;

		if (csgo::local_player == nullptr)
			return;

		std::pair<int, int> screen_size;

		interfaces::surface->get_screen_size(screen_size.first, screen_size.second);
		int x = screen_size.first / 2;
		int y = screen_size.second / 2;

		float spread = csgo::local_player->active_weapon()->get_weapon_data()->weapon_spread;

		float inaccuracy = csgo::local_player->active_weapon()->get_weapon_data()->weapon_inaccuracy_stand;
		float spreaddist = ((inaccuracy + spread) * 320.0f / tanf(DEG2RAD(6) / 2));

		spreaddist = (int)(spreaddist * ((float)(screen_size.second) / 480.0f));

		render::draw_circle(x, y, spreaddist, 3, color(75, 75, 75));
	}
}

void hitlogs(i_game_event* event)
{

}

void dispatch_logs()
{
	if (interfaces::engine->is_in_game())
	{
		if (csgo::local_player == nullptr)
			return;

		if (GetAsyncKeyState(VK_F8) & 1)
		{
			interfaces::client->dispatch_user_message(cs_um_hudmsg, 0, 0, "\"x0C\"[WIINER] Test Message");
		}

	}
}

void keystroke_display()
{
	if (interfaces::engine->is_in_game() && variables::misc::keystroke_display)
	{
		color wclr = color(255, 255, 255);
		color aclr = color(255, 255, 255);
		color sclr = color(255, 255, 255);
		color dclr = color(255, 255, 255);
		color shftclr = color(255, 255, 255);
		color spaceclr = color(255, 255, 255);
		
		if (GetAsyncKeyState(0x57)) // W
		{
			wclr = color(52, 134, 235);
		}

		if (GetAsyncKeyState(0x41)) // A
		{
			aclr = color(52, 134, 235);
		}

		if (GetAsyncKeyState(0x53)) // S
		{
			sclr = color(52, 134, 235);
		}

		if (GetAsyncKeyState(0x44)) // D
		{
			dclr = color(52, 134, 235);
		}

		if (GetAsyncKeyState(VK_SHIFT)) // SHFT
		{
			shftclr = color(52, 134, 235);
		}

		if (GetAsyncKeyState(VK_SPACE)) // SPACE
		{
			spaceclr = color(52, 134, 235);
		}
		
		render::draw_filled_rect(150, 450, 40, 40, color(35, 35, 35));
		render::draw_rect(150, 450, 40, 40, wclr);
		render::draw_text_string(163, 460, render::fonts::menucontent, "W", false, wclr);
		
		render::draw_filled_rect(150, 490, 40, 40, color(35, 35, 35));
		render::draw_rect(150, 490, 40, 40, sclr);
		render::draw_text_string(165, 500, render::fonts::menucontent, "S", false, sclr);
		
		render::draw_filled_rect(110, 490, 40, 40, color(35, 35, 35));
		render::draw_rect(110, 490, 40, 40, aclr);
		render::draw_text_string(125, 500, render::fonts::menucontent, "A", false, aclr);

		render::draw_filled_rect(190, 490, 40, 40, color(35, 35, 35));
		render::draw_rect(190, 490, 40, 40, dclr);
		render::draw_text_string(205, 500, render::fonts::menucontent, "D", false, dclr);
		
		render::draw_filled_rect(40, 490, 70, 40, color(35, 35, 35));
		render::draw_rect(40, 490, 70, 40, shftclr);
		render::draw_text_string(55, 500, render::fonts::menucontent, "SHIFT", false, shftclr);

		render::draw_filled_rect(40, 530, 190, 40, color(35, 35, 35));
		render::draw_rect(40, 530, 190, 40, spaceclr);
		render::draw_text_string(115, 540, render::fonts::menucontent, "SPACE", false, spaceclr);
		
	}
}