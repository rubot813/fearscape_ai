#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <windows.h>	// HANDLE, HWND
#include <winuser.h>	// Window focus

#include "pixel_field.hpp"
#include "figure.hpp"

/*
	 ласс описывает логику работы приложени¤
	«десь реализуетс¤ логика, отрисовка
*/

class application {
	public:

		// ¬с¤ логика реализована в конструкторе
		application( void );
		~application( void );

	private:

		// ћетод инициализации, вернет true в случае успеха
		bool _init( void );

		// ћетоды обработки логики и рендера
		void _logic( void );
		void _render( void );

		void _render_text( sf::Vector2f position, std::string text );

		// ‘ункци¤ заполнени¤ пол¤ пикселей с экрана
		// ѕринимает указатель на поле, координаты начала пол¤ и смещение по ос¤м x, y
		void _fill_pixel_field_from_screen( pixel_field_c *pixel_field, sf::Vector2i start_pos, sf::Vector2i offset );

		// ѕеременные SFML
		sf::RenderWindow	*_sf_render_window;
		sf::Event			*_sf_event;
		sf::RectangleShape	*_sf_rect_shape;
		sf::Font			*_sf_font;
		sf::Text			*_sf_text;

		// ƒескриптор окна, сам ¤вл¤етс¤ указателем
		HWND				_window_hwnd;

		// ѕеременные пол¤, с которым работаем
		// ќбновл¤ютс¤ каждую итерацию
		pixel_field_c	*_pf;		// ÷вета
		cell_field_c	*_cf;		// «начени¤ ¤чеек

		// * ¬ данной реализации AI знает только о текущей фигуре
		// ѕеременные фигуры
		pixel_field_c	*_figure_pf;	// ÷вета
		cell_field_c	*_figure_cf;	// «начени¤ ¤чеек
		figure_c		*_figure;		// “ип фигуры

		// Ќастроки цветов дл¤ online-tetris.ru
		settings_s 		*_online_tetris_settings;
};

#endif // APPLICATION_HPP
