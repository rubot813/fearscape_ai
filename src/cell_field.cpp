#include "cell_field.hpp"

cell_field_c::cell_field_c( sf::Vector2i field_size ) {
	if ( field_size.x > 0 && field_size.y > 0 ) {
		_field_size = field_size;
		_field.resize( field_size.x * field_size.y );
	} else
		std::cout << "FATAL ERROR on cell_field_c\n";
}

cell_field_c::~cell_field_c( void ) {
	_field.clear( );
}

bool operator==( const cell_field_c &cf_0, const cell_field_c &cf_1 ) {
	return ( cf_0._field == cf_1._field );
}

bool operator !=( const cell_field_c &cf_0, const cell_field_c &cf_1 ) {
	return ( cf_0._field != cf_1._field );
}

cell_field_c& cell_field_c::operator=( const cell_field_c &cf ) {
	_field		= cf._field;
	_field_size	= cf._field_size;
	return *this;
}

sf::Vector2i cell_field_c::get_size( void ) {
	return _field_size;
}

std::size_t cell_field_c::get_count( void ) {
	return _field_size.x * _field_size.y;
}

cell_t cell_field_c::get( sf::Vector2i pos ) {
	bool val = false;
	if ( pos.x < _field_size.x && pos.y < _field_size.y &&
	        pos.x >= 0 && pos.y >= 0 )
		val = _field.at( pos.x + pos.y * _field_size.x );
	else
		std::cout << __PRETTY_FUNCTION__ << " -> error\n";
	return val;
}

bool cell_field_c::set( sf::Vector2i pos, cell_t val ) {
	if ( pos.x < _field_size.x && pos.y < _field_size.y &&
	        pos.x >= 0 && pos.y >= 0 ) {
		_field.at( pos.x + pos.y * _field_size.x ) = val;
		return true;
	} else
		std::cout << __PRETTY_FUNCTION__ << " -> error";
	return false;
}

bool cell_field_c::set( uint8_t id, cell_t val ) {
	if ( id < _field.size( ) ) {
		_field.at( id ) = val;
		return true;
	} else
		std::cout << __PRETTY_FUNCTION__ << " -> error\n";
	return false;
}

bool cell_field_c::convert_to_16bit( uint16_t *val ) {

	// Поле должно быть размером 4 x 4
	if ( _field_size.x != 4 ||
	        _field_size.y != 4 ) {
		std::cout << __PRETTY_FUNCTION__ << " -> error\n";
		return false;
	}

	// Проход по битам числа
	for ( unsigned i = 0; i < 16; i++ )
		*val ^= ( -( _field[ i ] ) ^ *val ) & ( 1UL << i );

	return true;
}
