#include "framework.hpp"

POINT cursor;
POINT cursor_corrected;

void menu_framework::menu_movement(std::int32_t& x, std::int32_t& y, std::int32_t w, std::int32_t h)
{

	GetCursorPos(&cursor);

	if (GetAsyncKeyState(VK_LBUTTON) < 0 && (cursor.x > x && cursor.x < x + w && cursor.y > y && cursor.y < y + h)) {
		should_drag = true;

		if (!should_move) {
			cursor_corrected.x = cursor.x - x;
			cursor_corrected.y = cursor.y - y;
			should_move = true;
		}
	}

	if (should_drag) {
		x = cursor.x - cursor_corrected.x;
		y = cursor.y - cursor_corrected.y;
	}

	if (GetAsyncKeyState(VK_LBUTTON) == 0) {
		should_drag = false;
		should_move = false;
	}
}

void menu_framework::keybind(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, int& value)
{
	GetCursorPos(&cursor);

	int w = 15, h = 10;

	bool activate = true;

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h) && GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		activate = !activate;
	}

	if (activate == true) /* Where we run our code */
	{
		w = 60;
		render::draw_filled_rect(position, y, w, h, color(36, 36, 36, 255));
		render::draw_rect(position - 1, y - 1, w + 1, h + 1, variables::colors::menu::c_menu);

		for (int i = 0; i < 256; i++)
		{
			if (GetAsyncKeyState(i))
			{
				if (menu_framework::keys_list[i] != "Error")
				{
					value = i;
					std::string key = std::to_string(GetAsyncKeyState(i));
					render::text(x + 6, y - 1, font, key, false, value ? color(255, 255, 255, 255) : color::white());
					activate = false;
				}
			}
		}
	}
}

/*
	else
	{
		render::draw_filled_rect(position, y, w, h, color(36, 36, 36, 255));
		render::draw_rect(position - 1, y - 1, w + 1, h + 1, color(52, 134, 235, 255));
		render::text(x + 6, y - 1, font, "-", false, value ? color(255, 255, 255, 255) : color::white());
	}
 */

void menu::create(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, color bg, color header_text, color header_line, const std::string& name) {
	render::draw_filled_rect(x, y, w, h, bg);
	render::draw_rect(x + .5, y - 1, w - .5, h + .5, color(125, 125, 125));
}

void menu::tab(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, std::string icon, std::int32_t& tab, std::int32_t count, bool show_outline)
{
	GetCursorPos(&cursor);

	if ((cursor.x > x) && (cursor.x < x + w + 75) && (cursor.y > y) && (cursor.y < y + h) && (GetAsyncKeyState(VK_LBUTTON) & 1))
	{
		tab = count;
	}
	//tab background
	if (show_outline)
		render::draw_rect(x, y, w, h, tab == count ? variables::colors::menu::c_menu : color(25, 25, 25, 255));

	//tab label
	if (count == 2)
	{
		render::text(x - render::get_text_size(font, string).x / 2 + 30 - 8, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
		render::text(x - render::get_text_size(font, string).x / 2 + 55, y + h / 2 - 8, font, string, false, color::white());
	}
	else
	{
		if (count == 4)
		{
			render::text(x - render::get_text_size(font, string).x / 2 + 26, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 56, y + h / 2 - 8, font, string, false, color::white());
		}
		else
		{
			render::text(x - render::get_text_size(font, string).x / 2 + 30, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 60, y + h / 2 - 8, font, string, false, color::white());;
		}
	}


	if ((cursor.x > x) && (cursor.x < x + w + 130) && (cursor.y > y) && (cursor.y < y + h))
	{

		if (count == 1)
		{
			render::draw_filled_rect(x - 10, y + 2, w + 130, h, color(52, 134, 235, 255));
			render::text(x - render::get_text_size(font, string).x / 2 + 30, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 60, y + h / 2 - 8, font, string, false, color::white());
		}

		else
		{
			render::draw_filled_rect(x, y + 2, w + 130, h, color(52, 134, 235, 255));
			render::text(x - render::get_text_size(font, string).x / 2 + 30, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 60, y + h / 2 - 8, font, string, false, color::white());
		}

		if (count == 2)
		{
			render::draw_filled_rect(x, y + 2, w + 130, h, color(52, 134, 235, 255));
			render::text(x - render::get_text_size(font, string).x / 2 + 30 - 8, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 55, y + h / 2 - 8, font, string, false, color::white());
		}

		if (count == 5)
		{
			render::draw_filled_rect(x - 30, y + 2, w + 130, h, color(52, 134, 235, 255));
			render::text(x - render::get_text_size(font, string).x / 2 + 30, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 60, y + h / 2 - 8, font, string, false, color::white());
		}

		if (count == 4)
		{
			render::draw_filled_rect(x, y + 2, w + 130, h, color(52, 134, 235, 255));
			render::text(x - render::get_text_size(font, string).x / 2 + 26, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 56, y + h / 2 - 8, font, string, false, color::white());
		}
	}

	if (tab == count)
	{

		if (count == 1)
		{
			render::draw_filled_rect(x - 10, y + 2, w + 130, h, color(52, 134, 235, 255));
			render::text(x - render::get_text_size(font, string).x / 2 + 30, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 60, y + h / 2 - 8, font, string, false, color::white());
		}

		else
		{
			render::draw_filled_rect(x, y + 2, w + 130, h, color(52, 134, 235, 255));
			render::text(x - render::get_text_size(font, string).x / 2 + 30, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 60, y + h / 2 - 8, font, string, false, color::white());
		}

		if (count == 2)
		{
			render::draw_filled_rect(x, y + 2, w + 130, h, color(52, 134, 235, 255));
			render::text(x - render::get_text_size(font, string).x / 2 + 30 - 8, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 55, y + h / 2 - 8, font, string, false, color::white());
		}

		if (count == 5)
		{
			render::draw_filled_rect(x - 30, y + 2, w + 130, h, color(52, 134, 235, 255));
			render::text(x - render::get_text_size(font, string).x / 2 + 30, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 60, y + h / 2 - 8, font, string, false, color::white());
		}

		if (count == 4)
		{
			render::draw_filled_rect(x, y + 2, w + 130, h, color(52, 134, 235, 255));
			render::text(x - render::get_text_size(font, string).x / 2 + 26, y + h / 2 - 8, render::fonts::tabicons, icon, false, color::white());
			render::text(x - render::get_text_size(font, string).x / 2 + 56, y + h / 2 - 8, font, string, false, color::white());
		}
	}

}

void menu::group_box(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, bool show_label, bool outline)
{
	render::draw_filled_rect(x, y, w, h, color(25, 25, 25, 255));

	//groupbox outline

	if (outline)
	{
		render::draw_rect(x, y, w, h, color(125, 125, 125));
	}

	//groupbox label
	if (show_label)
	{
		render::draw_filled_rect(x, y, w, 35, color(25, 25, 25, 255));
		render::draw_rect(x, y, w, 35, color(125, 125, 125));
		render::text(x + 14, y + 8, font, string, false, color::white());
	}
}

void menu::textbutton(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t position, unsigned long font, const std::string string, std::int32_t& section, std::int32_t count)
{
	GetCursorPos(&cursor);

	int h = 10;

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h) && GetAsyncKeyState(VK_LBUTTON) & 1)
		section = count;

	// label
	render::text(x, y, font, string, false, color::white());

	if (section == count)
	{
		render::draw_filled_rect(x, y + 20, w, 5, color(52, 134, 235));
	}

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h))
	{
		render::draw_filled_rect(x, y + 20, w, 5, color(52, 134, 235));
	}

}

void menu::check_box(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, bool& value)
{
	GetCursorPos(&cursor);

	int w = 15, h = 15;

	color checkbox_outline = color(25, 25, 25, 255);

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h))
	{
		checkbox_outline = color(52, 134, 235, 255);
	}

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h) && GetAsyncKeyState(VK_LBUTTON) & 1)
		value = !value;

	if (value == false)
	{
		render::draw_filled_rect(position, y, w, h, color(36, 36, 36, 255));
		render::draw_rect(position, y, w, h, checkbox_outline);
	}
	else
	{
		render::draw_filled_rect(position, y, w, h, color(52, 134, 235));
		render::draw_rect(position, y, w, h, checkbox_outline);
	}

	//checkbox label
	render::text(x + 19, y - 2, font, string, false, color::white());
}

void menu::slider(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, float& value, float min_value, float max_value)
{
	GetCursorPos(&cursor);

	int ix = x;
	int yi = y + 9;

	color outlinecolor = color(45, 45, 45);

	if ((cursor.x > ix) && (cursor.x < ix + position) && (cursor.y > yi) && (cursor.y < yi + 6) && (GetAsyncKeyState(VK_LBUTTON)))
		value = (cursor.x - ix) / (float(position) / float(max_value));

	//slider background
	render::draw_filled_rect(ix, yi, position, 12, color(36, 36, 36, 255));
	render::draw_filled_rect(ix, yi, value * (float(position) / float(max_value)), 12, variables::colors::menu::c_menu);
	render::draw_rect(ix, yi, value * (float(position) / float(max_value)), 12, outlinecolor);

	render::text(x + 165, yi - 3, font, (std::stringstream{ } << std::setprecision(3) << value).str(), false, color::white());

	render::draw_filled_rect(ix + value * (float(position) / float(max_value)), yi, 15, 12, color(255, 255, 255));

	//slider label
	render::text(x - 1, y - 8, font, string, false, color::white());
}

void menu::color_picker(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, bool& opened, float& r, float& g, float& b)
{
	GetCursorPos(&cursor);

	int w = 15, h = 10;

	render::draw_filled_rect(x, y + 2, w, h, color(r, g, b));
	render::draw_rect(x, y + 2, w, h, color(25, 25, 25, 255));

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h) && GetAsyncKeyState(VK_LBUTTON) & 1)
		opened = !opened;

	if (opened == true)
	{
		render::draw_filled_rect(x + 250, y + 20, 150, 150, color(r, g, b, 255));
		render::draw_rect(x + 250, y + 20, 150, 150, color(25, 25, 25, 255));

		menu::slider(x + 250, y + 180, 120, render::fonts::menucontent, "R", r, 0, 255);
		menu::slider(x + 250, y + 210, 120, render::fonts::menucontent, "G", g, 0, 255);
		menu::slider(x + 250, y + 240, 120, render::fonts::menucontent, "B", b, 0, 255);

		if ((cursor.x < position) && (cursor.x > position + w) && (cursor.y < y) && (cursor.y > y + h) && GetAsyncKeyState(VK_LBUTTON) & 1)
		{
			opened = false;
		}

	}

	else
	{

	}

}

void menu::combo(std::int32_t x, std::int32_t y, std::int32_t position, std::int32_t height, unsigned long font, std::string label, bool& opened, bool single, std::vector<multi_select_item> items)
{

	GetCursorPos(&cursor);

	int w = 175, h = 20;
	int adaptive_height = 0;

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h + 20) && GetAsyncKeyState(VK_LBUTTON) & 1)
		opened = !opened;

	render::draw_text_string(x, y, font, label, false, color(255, 255, 255));
	render::draw_filled_rect(x, y + 20, w, h, color(25, 25, 25));
	render::draw_rect(x, y + 20, w, h, color(52, 134, 235));

	if (opened)
	{
		render::draw_text_string(x + 165, y + 20, font, "-", true, color(255, 255, 255));

		render::draw_filled_rect(x, y + 50, w, h + height, color(25, 25, 25));
		render::draw_rect(x, y + 50, w, h + height, color(52, 134, 235));

		auto postion = 0;
		for (int i = 1; i <= items.size(); i++)
		{
			int textheight = y + 35;
			postion += 15;
			textheight = textheight + postion;

			bool hovered = (cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < textheight + 20);

			if (hovered && GetAsyncKeyState(VK_LBUTTON) & 1)
			{
				if (single) /* NOTE: Bug has to do with something in this if statment */
				{

					for (int i = 1; i <= items.size(); i++)
					{
						*items[i - 1].value = false;
					}

					*items[i - 1].value = !*items[i - 1].value;
				}
				else
				{
					*items[i - 1].value = !*items[i - 1].value;
				}
			}

			bool selected = *items[i - 1].value >= 1;

			render::draw_text_string(x + 2, textheight, font, items[i - 1].name.data(), false, selected ? color(52, 134, 235) : color::white());

		}
	}
	else
	{
		render::draw_text_string(x + 165, y + 20, font, "+", true, color(255, 255, 255));
	}
	/*
	auto postion = 0;
	std::string name;
	for (int i = 1; i <= items.size(); i++)
	{
		bool selected = *items[i - 1].value >= 1;
		if (selected)
		{
			int text_x = x - 33;
			postion += 35;
			text_x = text_x + postion;
			std::string name = items[i - 1].name + ",";
			render::draw_text_string(text_x, y + 20, font, name, false, color(255, 255, 255));
		}
	}*/

	std::string value_str;
	int text_width;

	for (auto& item_t : items)
	{
		if (*item_t.value)
		{
			if (value_str.length() > 0)
			{
				value_str += ", ";
			}
			value_str += item_t.name;
		}
	}

	text_width = render::get_text_size(font, value_str.c_str()).length();
	if (text_width > w - 18)
	{
		value_str.resize(w / 10);
		value_str += " ...";
	}
	if (!value_str.length())
	{
		value_str += "None";
	}

	render::draw_text_string(x + 2, y + 20, font, value_str, false, color(255, 255, 255));

}

void menu::keybind(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, int& var, bool& opened, bool& otheropened)
{
	GetCursorPos(&cursor);

	int w = 120, h = 20;

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h + 20) && GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		opened = !opened;
	}
	else
	{
		opened = false;
	}

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h + 20) && GetAsyncKeyState(VK_RBUTTON) & 1)
	{
		otheropened = !otheropened;
	}

	if (opened)
	{
		for (int i = 0; i < 256; i++)
		{
			if (GetAsyncKeyState(i))
			{
				if (menu_framework::keys_list[i] != "Error")
				{
					var = i;
				}
			}
		}
		if (GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_BACK))
		{
			var = 256;
		}
	}

	if (otheropened)
	{
		render::draw_filled_rect(x + 100, y, 150, 150, color(40, 40, 40));
		render::draw_rect(x + 100, y, 150, 150, color(52, 134, 235));
	}

	std::string key;

	if (var == 256)
	{
		key = "None";
	}
	else
	{
		key = menu_framework::keys_list[var].data();
	}

	render::draw_text_string(x - 37, y - 2, font, "{ ", true, color(52, 134, 235));
	render::draw_text_string(x, y - 2, font, key, true, color(255, 255, 255));
	render::draw_text_string(x + 37, y - 2, font, " }", true, color(52, 134, 235));

}

void menu::quotes(std::int32_t x, std::int32_t y, unsigned long font)
{
	/*
	 std::vector<std::string> quotes =
	{
		"Welcome to Wiiner",
		"Have a nice day (:",
		"Please visit our website for support",
		"Brought to you by GrandmaSocks",
		"Version: 0.5",
		"Updated regularly",
		"Ragebot in the works",
		"Menu has been remodeled",
		"Have fun"
	};

	bool should = (int)std::floor((interfaces::globals->cur_time * 0.0001) / interfaces::globals->interval_per_tick) % 150;

	srand(time(NULL));

	if (should)
	{

		render::draw_text_string(x, y + 3, font, quotes[rand() % quotes.size()], false, color(255, 255, 255));

	}
	 */

	 /*  Above is a dynamic version of our info footer, I like static more but might as well save this to look back at
	  */

	if (variables::menu::footer)
	{
		render::draw_text_string(x, y + 3, font, "Welcome to Wiiner | Version: 0.5 | Ragebot in the Works | Menu has been remodeled", false, color(255, 255, 255));
	}
}

void menu::button(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, std::string label, const std::function<void(bool&)>& func)
{
	GetCursorPos(&cursor);

	int w = 175, h = 30;

	static bool holder = false;

	color txtcolor = color(255, 255, 255);

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h) && GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		txtcolor = color(52, 134, 235);
		func(holder);
	}

	render::draw_filled_rect(x, y, w, h, color(25, 25, 25));
	render::draw_rect(x, y, w, h, color(52, 134, 235));
	render::draw_text_string(x + 45, y + 5, font, label, false, txtcolor);
}

void menu::config_combo(std::int32_t x, std::int32_t y, std::int32_t height, std::int32_t position, unsigned long font, std::string label, bool& opened, const std::vector<std::string> items, int* value)
{
	GetCursorPos(&cursor);

	int w = 175, h = 20;
	int adaptive_height = 0;

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h + 20) && GetAsyncKeyState(VK_LBUTTON) & 1)
		opened = !opened;

	render::draw_text_string(x, y, font, label, false, color(255, 255, 255));
	render::draw_filled_rect(x, y + 20, w, h, color(25, 25, 25));
	render::draw_rect(x, y + 20, w, h, color(52, 134, 235));

	if (opened)
	{
		render::draw_text_string(x + 165, y + 20, font, "-", true, color(255, 255, 255));

		render::draw_filled_rect(x, y + 50, w, h + height, color(25, 25, 25));
		render::draw_rect(x, y + 50, w, h + height, color(52, 134, 235));

		auto postion = 0;
		for (int i = 1; i <= items.size(); i++)
		{
			int textheight = y + 35;
			postion += 15;
			textheight = textheight + postion;

			bool hovered = (cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < textheight + 20);

			if (hovered && GetAsyncKeyState(VK_LBUTTON) & 1)
			{			
				*value = i;			
			}

		}
	}
	else
	{
		render::draw_text_string(x + 165, y + 20, font, "+", true, color(255, 255, 255));
	}

	render::draw_text_string(x + 2, y + 2, render::fonts::menucontent, items.at(*value), false, color(255, 255, 255, 255));
	
}