#include "pixel_field.hpp"


pixel_field_c::pixel_field_c( sf::Vector2i field_size ) {
	if ( field_size.x > 0 && field_size.y > 0 ) {
		_field_size = field_size;
		_field.resize( field_size.x * field_size.y );
	} else
		std::cout << "FATAL ERROR on pixel_field_c\n";
}

pixel_field_c::~pixel_field_c( void ) {
	_field.clear( );
}

bool operator==( const pixel_field_c &pf_0, const pixel_field_c &pf_1 ) {
	return ( pf_0._field == pf_1._field );
}

bool operator !=( const pixel_field_c &pf_0, const pixel_field_c &pf_1 ) {
	return ( pf_0._field != pf_1._field );
}

pixel_field_c& pixel_field_c::operator=( const pixel_field_c &pf ) {
	_field		= pf._field;
	_field_size	= pf._field_size;
	return *this;
}

sf::Vector2i pixel_field_c::get_size( void ) {
	return _field_size;
}

std::size_t pixel_field_c::get_count( void ) {
	return _field_size.x * _field_size.y;
}

sf::Color pixel_field_c::get( sf::Vector2i pos ) {
	sf::Color col = sf::Color::Black;
	if ( pos.x < _field_size.x ||
	        pos.y < _field_size.y )
		col = _field.at( pos.x + pos.y * _field_size.x );
	else
		std::cout << __PRETTY_FUNCTION__ << " -> error\n";
	return col;
}

bool pixel_field_c::set( sf::Vector2i pos, sf::Color col ) {
	if ( pos.x < _field_size.x ||
	        pos.y < _field_size.y ) {
		_field.at( pos.x + pos.y * _field_size.x ) = col;
		return true;
	} else
		std::cout << __PRETTY_FUNCTION__ << " -> error\n";
	return false;
}

bool pixel_field_c::convert_to_cellfield( cell_field_c *cell_field, unsigned up_lines_ignored ) {
	if ( !cell_field ) {
		std::cout << __PRETTY_FUNCTION__ << " -> nullptr error\n";
		return 0;
	}
	// Размер cell_field
	sf::Vector2i cf_size = cell_field->get_size( );

	// Размеры CF и PF должны совпадать
	if ( cf_size.x != _field_size.x ||
	        cf_size.y != _field_size.y ) {
		std::cout << __PRETTY_FUNCTION__ << " -> size error\n";
		return 0;
	}

	for ( int x = 0; x < _field_size.x; x++ ) {
		for ( int y = 0; y < _field_size.y; y++ ) {
			// Беру значение из pixel_field
			sf::Color pfc = get( sf::Vector2i( x, y ) );

			// Определяю, чем цвет будет в cell_field
			bool contains = 0;	// Флаг, что тип ячейки найден по цвету
			bool cfv = 0;	// Все неопределенные ячейки по умолчанию пусты

			// Проверка по цветам фигуры
			auto iter = config->figure_colors->begin( );
			while( iter != config->figure_colors->end( ) ) {
				if ( *iter == pfc ) {
					contains = 1;
					cfv = 1;
					break;
				}
				++iter;
			}	// while figure_colors

			// Если не нашли в figure_colors
			if ( !contains ) {
				// Проверка по цветам фона
				auto iter =  config->back_colors->begin( );
				while( iter !=  config->back_colors->end( ) ) {
					if ( *iter == pfc ) {
						contains = 1;
						break;
					}
					++iter;
				}	// while back_colors
			}	// ifn contains

			/*
			if ( !contains )
				std::cout << "Cannot convert color " << ( unsigned )pfc.r << " " <<
														( unsigned )pfc.g << " " <<
													( unsigned )pfc.b << "\n";
			*/

			// Установка типа ячейки
			cell_field->set( sf::Vector2i( x, y ), cfv );
		}	// for y
	}	// for x

	// Удаление линий сверху
	for ( unsigned i = 0; i < up_lines_ignored; i++ ) {
		for ( int x = 0; x < _field_size.x; x++ )
			cell_field->set( sf::Vector2i( x, i ), 0 );
	}

	return cell_field;
}
