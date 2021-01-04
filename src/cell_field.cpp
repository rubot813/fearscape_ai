#include "cell_field.hpp"

cell_field_c::cell_field_c( sf::Vector2i field_size ) {
	if ( field_size.x > 0 && field_size.y > 0 ) {
		_field_size = field_size;
		_field.resize( field_size.x * field_size.y );
	}
	else
		std::cout << "FATAL ERROR on cell_field_c";
}

cell_field_c::~cell_field_c( void ) {
	_field.clear( );
}

sf::Vector2i cell_field_c::get_size( void ) {
	return _field_size;
}

unsigned cell_field_c::get_count( void ) {
	return _field_size.x * _field_size.y;
}

cell_t cell_field_c::get( sf::Vector2i pos ) {
	bool val = false;
	if ( pos.x < _field_size.x ||
		 pos.y < _field_size.y )
		val = _field.at( pos.x + pos.y * _field_size.x );
	return val;
}

bool cell_field_c::set( sf::Vector2i pos, cell_t val ) {
	if ( pos.x < _field_size.x ||
		 pos.y < _field_size.y ) {
		_field.at( pos.x + pos.y * _field_size.x ) = val;
		return true;
	}
	return false;
}

bool cell_field_c::convert_to_16bit( uint16_t *val ) {

	// Поле должно быть размером 4 x 4
	if ( _field_size.x != 4 ||
		 _field_size.y != 4 ) {
		std::cout << "Error at cell_field_c::convert_to_16bit";
		return 0;
	}

	// Проход по битам числа
	for ( unsigned i = 0; i < 16; i++ ) {
		*val ^= ( -( _field[ i ] ) ^ *val ) & ( 1UL << i );
	}

	return 1;
}
