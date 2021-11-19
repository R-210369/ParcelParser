#pragma once

#include "fmt/core.h"
#include "fmt/color.h"
#include "macros.hpp"
#include <Windows.h>
#include <string>
#include <string_view>
#include <optional>
//#include "utils.h"
#include "../singleton.hpp"
typedef enum printa_e : uint32_t
{
	ok = 0,
	input = 1,
	loading = 2,
	fail = 3,
	yahoo = 4,
	loading_violet = 5,
	loading_salmon = 6,

};
inline void remove_scrollbar() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size = {
		info.srWindow.Right - info.srWindow.Left + 1,info.srWindow.Bottom - info.srWindow.Top + 1
	};

	SetConsoleScreenBufferSize(handle, new_size);

}

class printa_c : public singleton<printa_c>
{
public:

	inline printa_c()
	{	 
		


		const auto console_handle = GetConsoleWindow();
		const auto stream_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		//size
		RECT r;
		GetWindowRect(console_handle, &r); //stores the console's current dimensions

		MoveWindow(console_handle, r.left, r.top, 600, 500, TRUE);

		remove_scrollbar();

		SetWindowPos(console_handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

		SetWindowLong(console_handle, GWL_STYLE, GetWindowLong(console_handle, GWL_STYLE) & ~WS_MINIMIZEBOX);
		 
		SetWindowLong(console_handle, GWL_STYLE, GetWindowLong(console_handle, GWL_STYLE) & ~WS_SYSMENU);

		// colours
		SetConsoleMode(stream_handle, 0x7);

		// transparency
		SetLayeredWindowAttributes(console_handle, 0, 205, LWA_ALPHA);

		// name
		SetConsoleTitleA( "" );
		 
		CloseHandle(console_handle);
	}
	inline ~printa_c() = default;

	// --

	template <printa_e type = printa_e::ok, typename ...args_t>
	constexpr __forceinline auto print(const std::string_view format, args_t... args) -> void
	{
		PRINTA_PRE();

		const auto [fmt_style, fmt_str] = this->get_format<type>();
		fmt::print(fmt_style, fmt_str);

		PRINTA_POST();

		fmt::print(format.data(), args...);
		//endl();
	}
	template <printa_e type = printa_e::ok, typename ...args_t>
	constexpr __forceinline auto print(const std::wstring_view format, args_t... args) -> void
	{
		PRINTA_PRE();

		const auto [fmt_style, fmt_str] = this->get_format<type>();
		fmt::print(fmt_style, fmt_str);

		PRINTA_POST();

		fmt::print(format.data(), args...);
	}


	// --

	template <uint32_t indentation>
	constexpr __forceinline auto project(const std::string_view project_name) -> void
	{
		std::string pre{ "\n" }; for (auto idx = 0u; idx < indentation; idx++) { pre += std::string{ " " }; }

		fmt::print(pre);
		//fmt::print(fg(fmt::color::cadet_blue) | fmt::emphasis::underline | fmt::emphasis::bold, project_name.data());
		fmt::print(fg(fmt::color::cadet_blue)  | fmt::emphasis::bold, project_name.data());
		fmt::print("\n\n");
	}

private:

	template <printa_e type>
	constexpr __forceinline auto get_format() -> std::pair<fmt::v7::text_style, std::string_view>
	{
		std::pair<fmt::v7::text_style, std::string_view> values = {};

		switch (type)
		{
		case ok:
		{
			values.first = fg(fmt::color::lime_green);

			values.second = " ok ";
			break;
		}
		case input:
		{
			values.first = fg(fmt::color::sky_blue);
			values.second = " -> ";
			break;
		}
		case loading:
		{
			//
			values.first = fg(fmt::color::cornflower_blue);
			values.second = "<-->";
			break;
		}
		case fail:
		{
			values.first = fg(fmt::color::orange_red);
			values.second = "fail";
			break;
		}
		case yahoo:
		{
			//values.first = fg(fmt::color::rebecca_purple);
			values.first = fg(fmt::color::hot_pink);
			values.second = "YAHOO";
			break;
		}
		case loading_violet:
		{
			//values.first = fg(fmt::color::rebecca_purple);
			values.first = fg(fmt::color::blue_violet);
			values.second = "<-->";
			break;
		}
		case loading_salmon:
		{
			//values.first = fg(fmt::color::rebecca_purple);
			values.first = fg(fmt::color::salmon);//
			values.second = "<-->";
			break;
		}


		}

		return values;
	}
};

inline auto printa = printa_c::instance();
