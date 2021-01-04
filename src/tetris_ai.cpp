#include "tetris_ai.hpp"

tetris_ai_c::tetris_ai_c( void ) {
	_height.clear( );
}

tetris_ai_c::~tetris_ai_c( void ) {
	// np
}

std::vector< uint8_t >* tetris_ai_c::get_current_height( void ) {
	return &_height;
}

tetris_ai_c::move_variant_s tetris_ai_c::ai_calc_bm_noholes( cell_field_c *cell_field, figure_c *figure ) {
	// Расчет высоты поля
}

std::vector< uint8_t > tetris_ai_c::_calculate_height( cell_field_c *cell_field ) {
	// Создание поля и задание размера исходя из ширины поля
	std::vector< uint8_t > height;
	sf::Vector2i field_size = cell_field->get_size( );
	height.resize( field_size.x, 0 );

	// Проход по полю
	// Слева направо 0 .. n
	for ( uint8_t x = 0; x < field_size.x; x++ ) {
		// Сверху вниз 0 .. n
		for ( uint8_t y = 0; y < field_size.y; y++ ) {
			if ( cell_field->get( sf::Vector2i( x, y ) ) ) {
				height.at( x ) = field_size.y - y;
				break;
			}
		}
	}
	return height;
}

uint8_t tetris_ai_c::_calculate_holes( cell_field_c *cell_field ) {
	uint8_t holes = 0;	// Счетчик отверстий
	bool get_used;	// Флаг - встретили ли заполненную ячейку

	sf::Vector2i field_size = cell_field->get_size( );

	// Проход по полю
	// Слева направо 0 .. n
	for ( uint8_t x = 0; x < field_size.x; x++ ) {
		get_used = 0;
		// Сверху вниз 0 .. n
		for ( uint8_t y = 0; y < field_size.y; y++ ) {
			if ( cell_field->get( sf::Vector2i( x, y ) ) )
				// Встретили заполненную ячейку
				get_used = 1;
			else {
				// Встретили пустую ячейку
				if ( get_used )
					holes++;
			}
		}
	}
	return holes;

}

