#ifndef CELL_FIELD_HPP
#define CELL_FIELD_HPP

#include <stdint-gcc.h>
#include <iostream>
#include <vector>

#include "global.hpp"

//  ласс описывающий поле ¤чеек ( bool зан¤та / свободна )
class cell_field_c {
	public:
		// ќб¤зательно создание с размерами пол¤
		cell_field_c( sf::Vector2i field_size );
		~cell_field_c( void );

		// ћетод возвращает размер пол¤
		sf::Vector2i get_size( void );

		// ћетод возвращает количество элементов в поле
		unsigned get_count( void );

		// ћетод получени¤ значени¤ ¤чейки
		cell_t get( sf::Vector2i pos );

		// ћетод установки значени¤ ¤чейки
		bool set( sf::Vector2i pos, cell_t val );

		// ћетод преобразовывает значение пол¤ и возвращает в виде 16-битного значени¤
		// –аботает только если поле размера 4x4, иначе вернет false
		bool convert_to_16bit( uint16_t *val );

	private:

		// ѕоле = вектор
		std::vector< cell_t > _field;

		// –азмеры пол¤
		sf::Vector2i _field_size;
};

#endif // CELL_FIELD_HPP
