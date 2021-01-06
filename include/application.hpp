#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <windows.h>	// HANDLE, HWND
#include <winuser.h>	// Window focus
#include <fstream>

#include "keypress_emulator.hpp"
#include "pixel_field.hpp"
#include "tetris_ai.hpp"
#include "figure.hpp"

/*
	Класс описывает логику работы приложения
	здесь реализуется логика, отрисовка
*/

class application {
	public:

		// Вся логика реализована в конструкторе
		application( void );
		~application( void );

	private:

		// Метод инициализации, вернет true в случае успеха
		bool _init( void );

		// Методы обработки логики и рендера
		void _logic( void );
		void _render( void );
		void _render_text( sf::Vector2f position, std::string text );

		// Функция заполнения поля пикселей с экрана
		// Принимает указатель на поле, координаты начала поля и смещение по осям x, y
		void _fill_pixel_field_from_screen( pixel_field_c *pixel_field, sf::Vector2i start_pos, sf::Vector2i offset );

		// Переменные SFML
		sf::RenderWindow	*_sf_render_window;
		sf::Event			*_sf_event;
		sf::RectangleShape	*_sf_rect_shape;
		sf::Font			*_sf_font;
		sf::Text			*_sf_text;

		// Дескриптор окна, сам является указателем
		HWND				_window_hwnd;

		// Указатель на экземпляр класса ИИ
		tetris_ai_c				*_tetris_ai;

		// Значения высот столбцов поля
		tetris_ai_c::height_s	*_field_height;

		// Количество отверстий в поле
		uint8_t					_field_holes;

		// Счетчик фигур
		std::size_t				_figure_counter;

		// Имя алгоритма, который кладет текущую фигуру
		std::string				*_ai_alg_name;

		// Вариант перемещения фигуры
		tetris_ai_c::move_variant_s _move_variant;

		// Переменные поля
		// обновляются каждую итерацию
		pixel_field_c		*_pf;		// Цвета
		cell_field_c		*_cf;		// Значения ячеек

		// Переменные фигуры
		// Текущая фигура
		pixel_field_c		*_current_figure_pf;	// Цвета
		cell_field_c		*_current_figure_cf;	// Значения ячеек

		// Предыдущая фигура
		pixel_field_c		*_previous_figure_pf;	// Цвета
		cell_field_c		*_previous_figure_cf;	// Значения ячеек

		figure_c			*_figure;		// Тип фигуры

		// Указатель на класс эмуляции нажатия кнопок
		keypress_emulator_c	*_keypress_emulator;

		// Настроки цветов для online-tetris.ru
		cell_field_c::settings_s 		*_online_tetris_settings;
};

#endif // APPLICATION_HPP
