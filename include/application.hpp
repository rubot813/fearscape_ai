#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <windows.h>	// HANDLE, HWND
#include <winuser.h>	// Window focus

#include "pixel_field.hpp"
#include "figure.hpp"

/*
	����� ��������� ������ ������ ����������
	����� ����������� ������, ���������
*/

class application {
	public:

		// ��� ������ ����������� � ������������
		application( void );
		~application( void );

	private:

		// ����� �������������, ������ true � ������ ������
		bool _init( void );

		// ������ ��������� ������ � �������
		void _logic( void );
		void _render( void );

		void _render_text( sf::Vector2f position, std::string text );

		// ������� ���������� ���� �������� � ������
		// ��������� ��������� �� ����, ���������� ������ ���� � �������� �� ���� x, y
		void _fill_pixel_field_from_screen( pixel_field_c *pixel_field, sf::Vector2i start_pos, sf::Vector2i offset );

		// ���������� SFML
		sf::RenderWindow	*_sf_render_window;
		sf::Event			*_sf_event;
		sf::RectangleShape	*_sf_rect_shape;
		sf::Font			*_sf_font;
		sf::Text			*_sf_text;

		// ���������� ����, ��� �������� ����������
		HWND				_window_hwnd;

		// ���������� ����, � ������� ��������
		// ����������� ������ ��������
		pixel_field_c	*_pf;		// �����
		cell_field_c	*_cf;		// �������� �����

		// * � ������ ���������� AI ����� ������ � ������� ������
		// ���������� ������
		pixel_field_c	*_figure_pf;	// �����
		cell_field_c	*_figure_cf;	// �������� �����
		figure_c		*_figure;		// ��� ������

		// �������� ������ ��� online-tetris.ru
		settings_s 		*_online_tetris_settings;
};

#endif // APPLICATION_HPP
