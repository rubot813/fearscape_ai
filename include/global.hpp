#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

// Размеры поля
const unsigned	field_size_x_c		= 10;	// Горизонтальное
const unsigned	field_size_y_c		= 20;	// Вертикальное

// Размеры превью фигуры ( не менять, описаны в вики )
const unsigned	figure_size_x_c	= 4;
const unsigned	figure_size_y_c	= 4;

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
const unsigned	window_size_y			= 405;

// Общее количество фигур
const uint8_t	figure_count			= 7;

// Начальная позиция фигур на поле по горизонтали ( левый верхний угол == 0 )
const uint8_t	figure_start_position_y	= 3;

// Время удержания кнопки при эмуляции нажатия,
// а также время между нажатиями кнопок
const unsigned	key_press_timeout_msec	= 75;

// Имя конфиг - файла, обязательно в кодировке CP-1251 ( Windows-1251 )
const std::string config_file_name = "config.txt";

// Тип ячейки
typedef	bool	cell_t;

#endif // GLOBAL_HPP_INCLUDED
