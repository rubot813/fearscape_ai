#include "pixel_field.hpp"


pixel_field_c::pixel_field_c( sf::Vector2i field_size ) {
	if ( field_size.x > 0 && field_size.y > 0 ) {
		_field_size = field_size;
		_field.resize( field_size.x * field_size.y );
	}
	else
		std::cout << "FATAL ERROR on pixel_field_c";
}

pixel_field_c::~pixel_field_c( void ) {
	_field.clear( );
}

sf::Vector2i pixel_field_c::get_size( void ) {
	return _field_size;
}

unsigned pixel_field_c::get_count( void ) {
	return _field_size.x * _field_size.y;
}

sf::Color pixel_field_c::get( sf::Vector2i pos ) {
	sf::Color col = sf::Color::Black;
	if ( pos.x < _field_size.x ||
		 pos.y < _field_size.y )
		col = _field.at( pos.x + pos.y * _field_size.x );
	return col;
}

bool pixel_field_c::set( sf::Vector2i pos, sf::Color col ) {
	if ( pos.x < _field_size.x ||
		 pos.y < _field_size.y ) {
		_field.at( pos.x + pos.y * _field_size.x ) = col;
		return true;
	}
	return false;
}

bool pixel_field_c::convert_to_cellfield( cell_field_c *cell_field, settings_s *settings, unsigned up_lines_ignored ) {
	if ( !cell_field ) {
		std::cout << "pixel_field_c::convert_to_cellfield -> received nullptr!";
		return 0;
	}
	// ������ cell_field
	sf::Vector2i cf_size = cell_field->get_size( );

	// ������� CF � PF ������ ���������
	if ( cf_size.x != _field_size.x ||
		 cf_size.y != _field_size.y ) {
		std::cout << "pixel_field_c::convert_to_cellfield -> cf size != pf size!";
		return 0;
	}

	for ( int x = 0; x < _field_size.x; x++ ) {
		for ( int y = 0; y < _field_size.y; y++ ) {
			// ���� �������� �� pixel_field
			sf::Color pfc = get( sf::Vector2i( x, y ) );

			// ���������, ��� ���� ����� � cell_field
			bool contatins = 0;	// ����, ��� ��� ������ ������ �� �����
			cell_t cfv = FREE_CELL;	// ��� �������������� ������ �� ��������� �����

			// �������� ����������� �����
			auto iter = settings->used_cells.begin( );
			while( iter != settings->used_cells.end( ) ) {
				if ( *iter == pfc ) {
					contatins = 1;
					cfv = USED_CELL;
					break;
				}
				++iter;
			}	// while used cells

			// ���� �� ����� � used_cells
			if ( !contatins ) {
				// �������� ������ �����
				auto iter = settings->free_cells.begin( );
				while( iter != settings->free_cells.end( ) ) {
					if ( *iter == pfc ) {
						contatins = 1;
						break;
					}
					++iter;
				}	// while free cells
			}	// ifn contains

			// �� ���������� ��� �� ���� �����������
			if ( !contatins )
				std::cout << "cannot found cell type with color " << ( unsigned )pfc.r << ", " << ( unsigned )pfc.g << ", " << ( unsigned )pfc.b << "\n";

			// ��������� ���� ������
			cell_field->set( sf::Vector2i( x, y ), cfv );
		}	// for y
	}	// for x

	// �������� ����� ������
	for ( unsigned i = 0; i < up_lines_ignored; i++ ) {
		for ( int x = 0; x < _field_size.x; x++ )
			cell_field->set( sf::Vector2i( x, i ), 0 );
	}

	return cell_field;
}
