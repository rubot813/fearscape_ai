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
			std::cout << __FUNCTION__ << " -> switch error\n";

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
		std::cout << __FUNCTION__ << " -> null error\n";
		return 0;
	}

	sf::Vector2i cf_size = cell_field->get_size( );
	if ( cf_size.x != 4 || cf_size.y != 4 ) {
		std::cout << __FUNCTION__ << " -> wrong size error\n";
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
		std::cout << __FUNCTION__ << " -> error\n";
	return cell_field;
}

uint16_t figure_c::get_bitfield( void ) {
	uint16_t ret = 0;
	if (	_type >= 0 &&
	        _type <= figure_count ) {
		ret = _cf_bitfield_rotation[ _type ][ _rotation ];
	} else
		std::cout << __FUNCTION__ << " -> error\n";
	return ret;
}

figure_c::projection_s figure_c::get_horizontal_projection( void ) {
	cell_field_c cf = get_cellfield( );
	projection_s proj;
	proj.valid = 0;
	bool buffer_value;
	if ( cf.get_count( ) == ( global_figure_size_x * global_figure_size_y ) ) {
		proj.valid = 1;
		for ( uint8_t x = 0; x < global_figure_size_x; x++ ) {
			buffer_value = 0;
			for ( uint8_t y = global_figure_size_y - 1; y > 0; y-- )
				if ( cf.get( sf::Vector2i( x, y ) ) ) {
					buffer_value = 1;
					break;
				}
			proj.data.push_back( buffer_value );
		}	// for
	}	// if
	return  proj;
}

figure_c::projection_s figure_c::get_horizontal_projection( cell_field_c *cell_field ) {
	projection_s proj;
	proj.valid = 0;
	bool buffer_value;
	if ( cell_field->get_count( ) == ( global_figure_size_x * global_figure_size_y ) ) {
		proj.valid = 1;
		for ( uint8_t x = 0; x < global_figure_size_x; x++ ) {
			buffer_value = 0;
			for ( uint8_t y = global_figure_size_y - 1; y > 0; y-- )
				if ( cell_field->get( sf::Vector2i( x, y ) ) ) {
					buffer_value = 1;
					break;
				}
			proj.data.push_back( buffer_value );
		}	// for
	}	// if
	return  proj;
}

bool figure_c::is_can_place( uint8_t field_size_h, int8_t hor_position ) {
	bool ok_flag = 0;	// Флаг, что все успешно

	// Получаю поле фигуры и проекцию фигуры
	cell_field_c figure_cf		= get_cellfield( );
	projection_s fig_hor_proj	= get_horizontal_projection( &figure_cf );

	// Если проекция верна
	if ( fig_hor_proj.valid ) {
		ok_flag = 1;
		// Проход по проекции фигуры
		for ( uint8_t x = 0; x < fig_hor_proj.data.size( ); x++ ) {
			bool proj_value		= fig_hor_proj.data.at( x );				// Значение проекции фигуры 0 .. n
			int8_t proj_pos_x	= hor_position + x + 3;						// Горизонтальное положение текущей ячейки на поле

			// Проверка, будет ли часть фигуры находиться за полем
			if ( proj_value && ( ( proj_pos_x < 0 ) || ( proj_pos_x > field_size_h ) ) ) {
				ok_flag = 0;
				break;
			}
		}	// for
	}	// is valid

	return ok_flag;
}

bool figure_c::is_can_place( cell_field_c *cell_field, sf::Vector2i position ) {
	bool ok_flag = 1;	// Флаг, что все успешно
	cell_field_c figure_cf = get_cellfield( );	// Поле фигуры
	for ( uint8_t x = 0; x < global_figure_size_x; x++ ) {
		for ( uint8_t y = 0; y < global_figure_size_y; y++ ) {
			if (	figure_cf.get( sf::Vector2i( x, y ) ) &&
			        cell_field->get(  sf::Vector2i( x, y ) + position ) ) {
				ok_flag = 0;
				break;
			}
		}
		if ( !ok_flag )
			break;
	}

	return ok_flag;
}

bool figure_c::place_on_cellfield( cell_field_c *cell_field, int8_t hor_position ) {
	bool ok_flag = 1;	// Флаг, что все успешно

	// Сохраняю поле ячеек
	cell_field_c cf_buffer = *cell_field;




	return ok_flag;
}

// ==== projection_s ====

bool figure_c::projection_s::get_left_offset( uint8_t *offset ) {
	bool ok_flag = 0;
	uint8_t value = 0;
	if ( valid && data.size( ) && offset ) {
		ok_flag = 1;
		for ( uint8_t i = 0; i < data.size( ); i++ )
			if ( !data.at( i ) )
				value++;
			else
				break;
		*offset = value;
	}
	return ok_flag;
}

bool figure_c::projection_s::get_right_offset( uint8_t *offset ) {
	bool ok_flag = 0;
	uint8_t value = 0;
	if ( valid && data.size( ) && offset ) {
		ok_flag = 1;
		for ( uint8_t i = data.size( ) - 1; i >= 0; i-- )
			if ( !data.at( i ) )
				value++;
			else
				break;
		*offset = value;
	}
	return ok_flag;
}

// ==== projection_s ====
