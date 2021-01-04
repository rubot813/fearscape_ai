#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <windows.h>	// HANDLE, HWND
#include <winuser.h>	// Window focus

#include "pixel_field.hpp"
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
		// Принимает указатель на поле, координаты начала пол¤ и смещение по осям x, y
		void _fill_pixel_field_from_screen( pixel_field_c *pixel_field, sf::Vector2i start_pos, sf::Vector2i offset );

		// Переменные SFML
		sf::RenderWindow	*_sf_render_window;
		sf::Event			*_sf_event;
		sf::RectangleShape	*_sf_rect_shape;
		sf::Font			*_sf_font;
		sf::Text			*_sf_text;

		// Дескриптор окна, сам является указателем
		HWND				_window_hwnd;

		// Переменные поля, с которым работаем
		// обновляются каждую итерацию
		pixel_field_c	*_pf;		// Цвета
		cell_field_c	*_cf;		// Значения ячеек

		// В данной реализации AI знает только о текущей фигуре
		// Переменные фигуры
		pixel_field_c	*_figure_pf;	// Цвета
		cell_field_c	*_figure_cf;	// Значения ячеек
		figure_c		*_figure;		// Тип фигуры

		// Настроки цветов для online-tetris.ru
		settings_s 		*_online_tetris_settings;
};

#endif // APPLICATION_HPP
