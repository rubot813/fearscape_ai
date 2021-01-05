#include "figure.hpp"

// Инициализация таблицы битовых полей матрицы вращения фигуры
// Первый столбец - без вращения
// Далее по 90 градусов по часовой
const uint16_t figure_c::_cf_bitfield_rotation[ 7 ][ 4 ] = {
	{ 240, 17476, 3840, 8738 },		// I
	{ 1808, 8800, 18176, 12832 },	// J
	{ 1856, 25120, 5888, 8752 },	// L
	{ 1632, 1632, 1632, 1632 },		// O
	{ 864, 1122, 54, 1122 },		// S	check
	{ 114, 610, 624, 562 },			// T
	{ 1584, 306, 99, 612 }			// Z	check
};

figure_c::figure_c( void ) {
	_type = figure_c::unknown;
	_rotation = figure_c::rt_standart;
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

void figure_c::set_rotation( figure_c::rotation_e rot ) {
	_rotation = rot;
}

figure_c::rotation_e figure_c::get_rotation( void ) {
	return _rotation;
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
	_rotation = figure_c::rt_standart;
	if ( cell_field->convert_to_16bit( &bit_figure ) ) {
		for ( uint8_t i = 0; i < figure_count; i++ )
			if ( bit_figure == _cf_bitfield_rotation[ i ][ 0 ] ) {
				_type = static_cast< type_e >( i );
				break;
			}
	}

	return ( _type != figure_c::unknown );
}

cell_field_c figure_c::get_cellfield( void ) {
	cell_field_c cell_field( sf::Vector2i( global_figure_size_x, global_figure_size_y ) );	// 4x4 by default
	uint16_t bitfield = get_bitfield( );
	if ( bitfield ) {
		for ( unsigned id = 0; id < ( global_figure_size_x * global_figure_size_y ); id++ )
			cell_field.set( id, ( ( bitfield ) & ( 1 << id ) ) );
	} else
		std::cout << __PRETTY_FUNCTION__ << " -> error\n";
	return cell_field;
}

uint16_t figure_c::get_bitfield( void ) {
	uint16_t ret = 0;
	std::cout << "get bf type = " << _type;
	std::cout << "get bf rotat = " << _rotation;

	if (	_type >= 0 &&
	        _type <= figure_count ) {
		ret = _cf_bitfield_rotation[ _type ][ _rotation ];
	} else
		std::cout << __PRETTY_FUNCTION__ << " -> error\n";
	return ret;
}

std::vector< bool > figure_c::get_horizontal_projection( void ) {
	cell_field_c cf = get_cellfield( );
	std::vector< bool > res_vec;
	bool val;
	if ( cf.get_count( ) ) {
		for ( uint8_t x = 0; x < global_figure_size_x; x++ ) {
			val = 0;
			for ( uint8_t y = global_figure_size_y - 1; y > 0; y-- )
				if ( cf.get( sf::Vector2i( x, y ) ) ) {
					val = 1;
					break;
				}
			res_vec.push_back( val );
		}	// for
	}	// if
	return res_vec;
}

