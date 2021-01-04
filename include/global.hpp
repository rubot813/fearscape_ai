#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

// ���������
const unsigned	global_field_size_x		= 10;
const unsigned	global_field_size_y		= 20;
const unsigned	global_figure_size_x	= 4;
const unsigned	global_figure_size_y	= 4;

// ���������� ������ ���� �� ������ � ��������
const unsigned	screen_start_field_x	= 800;
const unsigned	screen_start_field_y	= 143;

// ���������� ������ ������ �� ������ � ��������
const unsigned	screen_start_figure_x	= 1050;
const unsigned	screen_start_figure_y	= 167;

// ������ ����� �� ������ � ��������
const unsigned	screen_block_size		= 24;

// ������� ����������� ����
const unsigned	window_size_x			= 215;
const unsigned	window_size_y			= 500;

// �������� ����, � ������� ��������������� AI
const std::string working_app_name = "������ ������������ - ������ ������, ��� ����������� � ��� �������, �������� ������� ����������� - Google Chrome";

// ��� ������
typedef	bool	cell_t;
const bool		USED_CELL = true;
const bool		FREE_CELL = false;

// ��������� �������� ��� ���� �����
struct settings_s {
	// ����� ������ ����������� �����
	std::vector< sf::Color > used_cells;

	// ����� ������ ������ �����
	std::vector< sf::Color > free_cells;
};

// ��������� �������� ����������� ������
struct move_variant_s {
	// ������� ������������ ���������� ��������� ������ ( �� ����� ������ � �� ������ )
	// ������������� �������� - ����������� �������, ������������� �������� - ����������� ������
	// >0 ����������� �� pos ������ �������
	// <0 ����������� �� -pos ������ ������
	int8_t	position;

	// 0 - ��� ��������
	// 1 - 90 �������� �� �������
	// 2 - 180 �������� �� �������
	// 3 - 270 �������� �� �������
	uint8_t rotation;
};

#endif // GLOBAL_HPP_INCLUDED
