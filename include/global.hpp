#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

// Размеры поля
const unsigned	global_field_size_x		= 10;
const unsigned	global_field_size_y		= 20;

// Размеры превью фигуры ( не менять, описаны в вики )
const unsigned	global_figure_size_x	= 4;
const unsigned	global_figure_size_y	= 4;

// Координаты начала поля на экране в пикселях
const unsigned	screen_start_field_x	= 800;
const unsigned	screen_start_field_y	= 143;

// Координаты начала фигуры на экране в пикселях
const unsigned	screen_start_figure_x	= 1050;
const unsigned	screen_start_figure_y	= 167;

// Размер блока на экране в пикселях
const unsigned	screen_block_size		= 24;

// Размеры отладочного окна
const unsigned	window_size_x			= 215;
const unsigned	window_size_y			= 500;

// Общее количество фигур
const uint8_t	figure_count			= 7;

// Время удержания кнопки при эмуляции нажатия,
// а также время между нажатиями кнопок
const unsigned	key_press_timeout_msec	= 50;

// Название окна, с которым взаимодействует AI
const std::string working_app_name = "Тетрис классический - играть онлайн, без регистрации и без рекламы, реальная таблица результатов - Google Chrome";

// Тип ячейки
typedef	bool	cell_t;
const bool		USED_CELL = true;
const bool		FREE_CELL = false;

#endif // GLOBAL_HPP_INCLUDED
