#include "figure.hpp"

// Инициализация таблицы битовых полей матрицы вращения фигуры
// Первый столбец - без вращения
// Далее по 90 градусов по часовой
const uint16_t figure_c::_cf_bitfield_rotation[ 7 ][ 4 ] = {
	{ 240, 0, 0, 0 },	// I
	{ 114, 0, 0, 0 },	// T
	{ 1808, 0, 0, 0 },	// J
	{ 1856, 0, 0, 0 },	// L
	{ 1632, 0, 0, 0 },	// O
	{ 864, 0, 0, 0 },	// S
	{ 1584, 0, 0, 0 }	// Z
};

figure_c::figure_c( void ) {
	// np
}

figure_c::~figure_c( void ) {
	// np
}

figure_c::type_e figure_c::get_type( void ) {
	return _type;
}

char figure_c::get_type_char( void ) {
	char c = 'u';
	switch( _type ) {
		case( I ) : {
			c = 'I';
			break;
		}
		case( J ) : {
			c = 'J';
			break;
		}
		case( L ) : {
			c = 'L';
			break;
		}
		case( O ) : {
			c = 'O';
			break;
		}
		case( S ) : {
			c = 'S';
			break;
		}
		case( T ) : {
			c = 'T';
			break;
		}
		case( Z ) : {
			c = 'Z';
			break;
		}
		case( unknown ) : {
			c = 'u';
			break;
		}
		default :
			std::cout << __PRETTY_FUNCTION__ << " -> switch error";

	}	// switch
	return c;
}

bool figure_c::set_from_cell_field( cell_field_c *cell_field, cell_field_c::settings_s *settings ) {
	if ( !cell_field ) {
		std::cout << __PRETTY_FUNCTION__ << " -> null error";
		return 0;
	}

	sf::Vector2i cf_size = cell_field->get_size( );
	if ( cf_size.x != 4 || cf_size.y != 4 ) {
		std::cout << __PRETTY_FUNCTION__ << " -> wrong size error";
		return 0;
	}

	// Преобразование фигуры в битовое представление
	uint16_t bit_figure;
	_type = figure_c::unknown;
	if ( cell_field->convert_to_16bit( &bit_figure ) ) {
		for ( uint8_t i = 0; i < figure_count; i++ )
			if ( bit_figure == _cf_bitfield_rotation[ i ][ 0 ] ) {
				_type = static_cast< type_e >( i );
				break;
			}
	}

	return ( _type != figure_c::unknown );
}

cell_field_c figure_c::get_cell_field_rotated( uint8_t rotation ) {
	cell_field_c cell_field( sf::Vector2i( global_figure_size_x, global_figure_size_y ) );	// 4x4 by default
	if ( rotation < 4 ) {
		uint16_t bitfield = get_bitfield_rotated( rotation );
		for ( unsigned id = 0; id < ( global_figure_size_x * global_figure_size_y ); id++ )
			cell_field.set( id, ( ( bitfield ) & ( 1 << id ) ) );
	} else
		std::cout << __PRETTY_FUNCTION__ << " -> error";
	return cell_field;

}

uint16_t figure_c::get_bitfield_rotated( uint8_t rotation ) {
	uint16_t ret = 0;
	if (	_type > 0 &&
	        _type <= figure_count &&
	        rotation > 0 &&
	        rotation < 4 ) {
		ret = _cf_bitfield_rotation[ _type ][ rotation ];
	} else
		std::cout << __PRETTY_FUNCTION__ << " -> error";
	return ret;
}
