#include "figure.hpp"

// Инициализация таблицы битовых полей матрицы вращения фигуры
// Первый столбец - без вращения
// Далее по 90 градусов по часовой
const uint16_t figure_c::_cf_bitfield_rotation[ 7 ][ 4 ] = {
	{ 240, 17476, 3840, 8738 },		// I
	{ 1808, 8800, 18176, 12832 },	// J
	{ 1856, 25120, 5888, 8752 },	// L
	{ 1632, 1632, 1632, 1632 },		// O
	{ 864, 1122, 864, 561 },		// S
	{ 114, 610, 624, 562 },			// T
	{ 1584, 9792, 25344, 4896 }		// Z
};

figure_c::figure_c( void ) {
	_type = figure_c::unknown;
	_rotation = figure_c::rt_standart;
}

figure_c::~figure_c( void ) {
	// np
}

figure_c& figure_c::operator=( const figure_c &f ) {
	_type		= f._type;
	_rotation	= f._rotation;
	return *this;
}

figure_c::type_e figure_c::get_type( void ) {
	return _type;
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
	cell_field_c cell_field( sf::Vector2i( figure_size_x_c, figure_size_y_c ) );	// 4x4 by default
	uint16_t bitfield = get_bitfield( );
	if ( bitfield ) {
		for ( unsigned id = 0; id < ( figure_size_x_c * figure_size_y_c ); id++ )
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
	if ( cf.get_count( ) == ( figure_size_x_c * figure_size_y_c ) ) {
		proj.valid = 1;
		for ( uint8_t x = 0; x < figure_size_x_c; x++ ) {
			buffer_value = 0;
			for ( uint8_t y = figure_size_y_c - 1; y > 0; y-- ) {
				bool value = 0;
				if ( cf.check( sf::Vector2i( x, y ), &value ) ) {
					if ( value ) {
						buffer_value = 1;
						break;
					}
				}	// if check
			}	// for y
			proj.data.push_back( buffer_value );
		}	// for x
	}	// if
	return  proj;
}

figure_c::projection_s figure_c::get_horizontal_projection( cell_field_c *cell_field ) {
	projection_s proj;
	proj.valid = 0;
	bool buffer_value;
	if ( cell_field->get_count( ) == ( figure_size_x_c * figure_size_y_c ) ) {
		proj.valid = 1;
		for ( uint8_t x = 0; x < figure_size_x_c; x++ ) {
			buffer_value = 0;
			for ( uint8_t y = figure_size_y_c - 1; y > 0; y-- ) {
				bool value = 0;
				if ( cell_field->check( sf::Vector2i( x, y ), &value ) ) {
					if ( value ) {
						buffer_value = 1;
						break;
					}
				}	// if check
			}	// for y
			proj.data.push_back( buffer_value );
		}	// for x
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
			if ( proj_value && ( ( proj_pos_x < 0 ) || ( x + 3 > field_size_h ) ) ) {
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

	// Проход по полю фигуры
	for ( uint8_t x = 0; x < figure_size_x_c; x++ ) {
		for ( uint8_t y = 0; y < figure_size_y_c; y++ ) {
			// Проверка, занята ли ячейка фигуры
			bool figure_value = 0;
			if ( figure_cf.check( sf::Vector2i( x, y ), &figure_value ) ) {
				// Ячейка фигуры существует и занята
				if ( figure_value ) {
					sf::Vector2i pos = sf::Vector2i( x + position.x, y + position.y );	// Позиция ячейки на поле
					bool field_value = 0;												// Значение ячейки
					bool field_check = cell_field->check( pos, &field_value );			// Флаг существования ячейки
					// Если ячейка существует
					if ( field_check ) {
						// Если ячейка занята = положить не можем
						if ( field_value ) {
							ok_flag = 0;
							break;
						}
					} else {
						// Если ячейка не существует = положить не можем
						ok_flag = 0;
						break;
					}
				}	// figure check
			} // figure check
		}	// for y
		if ( !ok_flag )
			break;
	}	// for x
	return ok_flag;
}

bool figure_c::place_to_cellfield( cell_field_c *cell_field, int8_t hor_position ) {
	bool ok_flag = 0;	// Флаг, что все успешно

	// Сохраняю поле ячеек
	cell_field_c cf_buffer = *cell_field;

	// Проход по полю сверху вниз
	for ( uint8_t y = 1; y < field_size_y_c + 2; y++ ) {
		// Если не можем расположить фигуру в данном месте
		if ( !is_can_place( cell_field, sf::Vector2i( hor_position, y ) ) ) {
			// std::cout << "Cannot place on " << ( signed )hor_position << ", " << ( unsigned )y << "( try to apply to " << ( unsigned )y - 1 << "\n";
			if ( apply_to_cellfield( cell_field,  sf::Vector2i( hor_position, y - 1 ) ) ) {
				// std::cout << "Apply to cellfield ok!\n";
				ok_flag = 1;
				break;
			}
		} // else field is full
	}	// for
	return ok_flag;
}

bool figure_c::apply_to_cellfield( cell_field_c *cell_field, sf::Vector2i position ) {
	bool ok_flag = 1;	// Флаг, что все успешно
	cell_field_c figure_cf = get_cellfield( );	// Поле фигуры

	// Проход по полю фигуры
	for ( uint8_t x = 0; x < figure_size_x_c; x++ ) {
		for ( uint8_t y = 0; y < figure_size_y_c; y++ ) {
			// Если ячейка фигуры заполнена
			if ( figure_cf.get( sf::Vector2i( x, y ) ) ) {

				// Проверка, пуста ли ячейка на поле
				sf::Vector2i pos = sf::Vector2i( position.x + x, position.y + y );
				bool field_value = 0;
				if ( cell_field->check( pos, &field_value ) ) {
					// Ячейка существует, если она не заполнена
					if ( !field_value )
						// Заполнение, переход к следующей ячейке
						cell_field->set( pos, 1 );
					else {
						// Ячейка существует и заполнена = ошибка, выход
						ok_flag = 0;
						break;
					}
				}	// field check
			}	// get figure
		}	// for y
		if ( !ok_flag )
			break;
	}	// for x

	return ok_flag;
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

// ==== projection_s ====

bool figure_c::projection_s::get_left_offset( int8_t *offset ) {
	bool ok_flag = 0;
	int8_t value = 0;
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

bool figure_c::projection_s::get_right_offset( int8_t *offset ) {
	bool ok_flag = 0;
	int8_t value = 0;
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
