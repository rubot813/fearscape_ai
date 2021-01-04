#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

// Константы
const unsigned	global_field_size_x		= 10;
const unsigned	global_field_size_y		= 20;
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

// Название окна, с которым взаимодействует AI
const std::string working_app_name = "Тетрис классический - играть онлайн, без регистрации и без рекламы, реальная таблица результатов - Google Chrome";

// Тип ячейки
typedef	bool	cell_t;
const bool		USED_CELL = true;
const bool		FREE_CELL = false;

// Структура настроек для поля ячеек
struct settings_s {
	// Набор цветов заполненных ячеек
	std::vector< sf::Color > used_cells;

	// Набор цветов пустых ячеек
	std::vector< sf::Color > free_cells;
};

// Структура варианта перемещения фигуры
struct move_variant_s {
	// Позиция относительно начального положения фигуры ( на верху экрана и по центру )
	// Положительное значение - перемещение направо, отрицательное значение - перемещение налево
	// >0 перемещение на pos клеток направо
	// <0 перемешение на -pos клеток налево
	int8_t	position;

	// 0 - без вращения
	// 1 - 90 градусов по часовой
	// 2 - 180 градусов по часовой
	// 3 - 270 градусов по часовой
	uint8_t rotation;
};

#endif // GLOBAL_HPP_INCLUDED
