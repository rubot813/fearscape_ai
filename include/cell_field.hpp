#ifndef CELL_FIELD_HPP
#define CELL_FIELD_HPP

#include <stdint-gcc.h>
#include <iostream>
#include <vector>

#include "global.hpp"

// ����� ����������� ���� ����� ( bool ������ / �������� )
class cell_field_c {
	public:
		// ����������� �������� � ��������� ����
		cell_field_c( sf::Vector2i field_size );
		~cell_field_c( void );

		// ����� ���������� ������ ����
		sf::Vector2i get_size( void );

		// ����� ���������� ���������� ��������� � ����
		unsigned get_count( void );

		// ����� ��������� �������� ������
		cell_t get( sf::Vector2i pos );

		// ����� ��������� �������� ������
		bool set( sf::Vector2i pos, cell_t val );

		// ����� ��������������� �������� ���� � ���������� � ���� 16-������� ��������
		// �������� ������ ���� ���� ������� 4x4, ����� ������ false
		bool convert_to_16bit( uint16_t *val );

	private:

		// ���� = ������
		std::vector< cell_t > _field;

		// ������� ����
		sf::Vector2i _field_size;
};

#endif // CELL_FIELD_HPP
