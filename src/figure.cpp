#include "figure.hpp"

figure_c::figure_c( void ) {
	// np
}

figure_c::~figure_c( void ) {
	// np
}

bool figure_c::set_from_cell_field( cell_field_c *cell_field, settings_s *settings ) {
	if ( !cell_field ) {
		std::cout << "Error: figure_s::set_from_cell_field is null";
		return 0;
	}

	sf::Vector2i cf_size = cell_field->get_size( );
	if ( cf_size.x != 4 ||
		 cf_size.y != 4 ) {
		std::cout << "Error: figure_s::set_from_cell_field wrong size";
		return 0;
	}

	// ѕреобразование фигуры в битовое представление
	uint16_t bit_figure;
	if ( cell_field->convert_to_16bit( &bit_figure ) ) {
		switch ( bit_figure ) {
			case ( 240 ) : {
				_type = I;
				break;
			}

			case ( 114 ) : {
				_type = T;
				break;
			}

			case ( 1808 ) : {
				_type = J;
				break;
			}

			case ( 1856 ) : {
				_type = L;
				break;
			}

			case ( 1632 ) : {
				_type = O;
				break;
			}

			case ( 864 ) : {
				_type = S;
				break;
			}

			case ( 1584 ) : {
				_type = Z;
				break;
			}

			default : {
				_type = unknown;
				break;
			}
		}	// switch
	} else {
		std::cout << "Error: figure_s::set_from_cell_field cannot convert to 16bit";
		return 0;
	}

	return 1;
}

figure_c::type_e figure_c::get_type( void ) {
	return _type;
}

char figure_c::get_type_char( void ) {
	char c = 'u';
	switch( _type ) {
		case( unknown ) : {
			c = 'u';
			break;
		}

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

		default :
			break;
	}	// switch
	return c;
}
