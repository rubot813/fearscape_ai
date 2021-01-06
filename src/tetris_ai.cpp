#include "tetris_ai.hpp"

tetris_ai_c::tetris_ai_c( void ) {
	_height.data.clear( );
	srand( static_cast< std::size_t >( time( NULL ) ) );
}

tetris_ai_c::~tetris_ai_c( void ) {
	// np
}

tetris_ai_c::height_s* tetris_ai_c::get_height( void ) {
	return &_height;
}

std::size_t	tetris_ai_c::get_height_sum( void ) {
	std::size_t value = 0;
	auto iter = _height.data.begin( );
	while( iter != _height.data.end( ) ) {
		value += *iter;
		iter++;
	}
	return value;
}

uint8_t	tetris_ai_c::get_holes_count( void ) {
	return _holes;
}

std::string* tetris_ai_c::get_ai_alg_name( void ) {
	return &_ai_alg_name;
}

tetris_ai_c::move_variant_s tetris_ai_c::ai_calc_simple_placer( cell_field_c *cell_field, figure_c *figure ) {

	// Расчет высот столбцов поля
	_height = _calculate_height( cell_field );

	// Расчет количества отверстий
	_holes = _calculate_holes( cell_field );

	// Итоговый вариант хода
	move_variant_s move_variant;

	// = = = = =
	move_variant.position = 0;
	move_variant.rotation = figure_c::rt_standart;
	// = = = = =

	_ai_alg_name = __FUNCTION__;
	return move_variant;
}

tetris_ai_c::move_variant_s tetris_ai_c::ai_calc_random( cell_field_c *cell_field, figure_c *figure ) {
	// Расчет высот столбцов поля
	_height = _calculate_height( cell_field );

	// Расчет количества отверстий
	_holes = _calculate_holes( cell_field );

	// Итоговый вариант хода
	move_variant_s move_variant;

	// = = = = =
	move_variant.position = rand( ) % 7 - 3;									// -3 .. 4
	move_variant.rotation = static_cast< figure_c::rotation_e >( rand( ) % 3 );	// 0 .. 3
	// = = = = =

	_ai_alg_name = __FUNCTION__;
	return move_variant;
}

tetris_ai_c::move_variant_s tetris_ai_c::ai_calc_bm_noholes( cell_field_c *cell_field, figure_c *figure ) {
	// Расчет высот столбцов поля
	_height = _calculate_height( cell_field );

	// Расчет количества отверстий
	_holes = _calculate_holes( cell_field );

	// Итоговый вариант хода
	move_variant_s move_variant;

	// = = = = =
	// if ( figure->is_can_place( global_field_size_x, 5 ) )
	// 	std::cout << "CAN PLACE\n";
	if ( figure->is_can_place( cell_field, sf::Vector2i( 0, 16 ) ) )
		std::cout << "CAN PLACE\n";
	// = = = = =

	_ai_alg_name = __FUNCTION__;
	return move_variant;
}

tetris_ai_c::height_s tetris_ai_c::_calculate_height( cell_field_c *cell_field ) {
	// Создание поля и задание размера исходя из ширины поля
	height_s height;
	sf::Vector2i field_size = cell_field->get_size( );
	height.data.resize( field_size.x, 0 );
	height.valid = 1;

	// Проход по полю
	// Слева направо 0 .. n
	for ( uint8_t x = 0; x < field_size.x; x++ ) {
		// Сверху вниз 0 .. n
		for ( uint8_t y = 0; y < field_size.y; y++ ) {
			if ( cell_field->get( sf::Vector2i( x, y ) ) ) {
				height.data.at( x ) = field_size.y - y;
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
				get_used = 1;
			else {
				if ( get_used )
					holes++;
			}
		}
	}
	return holes;
}

