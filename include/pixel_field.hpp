#ifndef PIXEL_FIELD_HPP
#define PIXEL_FIELD_HPP

#include <stdint-gcc.h>
#include <iostream>
#include <vector>

#include "cell_field.hpp"

// ����� ��������� ����, ��������� �� ��������
class pixel_field_c {
	public:
		// ����������� �������� � ��������� ����
		pixel_field_c( sf::Vector2i field_size );
		~pixel_field_c( void );

		// ����� ���������� ������ ����
		sf::Vector2i get_size( void );

		// ����� ���������� ���������� ��������� � ����
		unsigned get_count( void );

		// ����� ��������� ����� ����
		sf::Color get( sf::Vector2i pos );

		// ����� ��������� ����� ����
		bool set( sf::Vector2i pos, sf::Color col );

		// ����� ������������ ���� ������ � ���� �����
		// ��������� ��������� �� ���� ����� � ��������� �������� ���������������
		// ���������� true ���� ��� �������
		// ����� ����� �������� ���������� ��� ������ ��������
		bool convert_to_cellfield( cell_field_c *cell_field, settings_s *settings, unsigned up_lines_ignored = 0 );

	private:
		// ���� = ������
		std::vector< sf::Color > _field;

		// ������� ����
		sf::Vector2i _field_size;
};

#endif // PIXEL_FIELD_HPP
