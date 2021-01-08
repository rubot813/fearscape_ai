#include "config_reader.hpp"


bool config_reader_c::read( void ) {
	bool is_ok = 1;

	// Чтение config_windowname.txt
	std::ifstream *_file = new std::ifstream;
	_file->open( "config_windowname.txt", std::ios::in );
	if ( _file->is_open( ) ) {
		std::getline( *_file, _config.window_name );
		_file->close( );
	} else {
		std::cout << __FUNCTION__ << "-> error, cannot open config_windowname.txt";
		is_ok = 0;
	}

	// Чтение config.txt
	_file->open( "config.txt", std::ios::in );
	if ( _file->is_open( ) ) {
		*_file >> _config.screen_start_field.x;
		*_file >> _config.screen_start_field.y;
		*_file >> _config.field_size.x;
		*_file >> _config.field_size.y;
		*_file >> _config.screen_start_figure.x;
		*_file >> _config.screen_start_figure.y;
		*_file >> _config.figure_cell_size.x;
		*_file >> _config.figure_cell_size.y;
		*_file >> _config.screen_figure_size;
		*_file >> _config.figure_start_pos;
		*_file >> _config.figure_count;
		*_file >> _config.kp_time;
		_file->close( );
	} else {
		std::cout << __FUNCTION__ << "-> error, cannot open config.txt";
		is_ok = 0;
	}

	// Чтение config_figure_colors.txt
	_config.figure_colors = &_figure_colors;
	_file->open( "config_figure_colors.txt", std::ios::in );
	if ( _file->is_open( ) ) {
		sf::Color buffer_color;
		unsigned value;
		while( *_file >> value ) {	// because r/g/b -> uint
			buffer_color.r = value;
			*_file >> value;
			buffer_color.g = value;
			*_file >> value;
			buffer_color.b = value;
			_figure_colors.push_back( buffer_color );
		}
		_file->close( );
	} else {
		std::cout << __FUNCTION__ << "-> error, cannot open config_figure_colors.txt";
		is_ok = 0;
	}

	// Чтение config_back_colors.txt
	_config.back_colors = &_back_colors;
	_file->open( "config_back_colors.txt", std::ios::in );
	if ( _file->is_open( ) ) {
		sf::Color buffer_color;
		unsigned value;
		while( *_file >> value ) { // because r/g/b -> uint
			buffer_color.r = value;
			*_file >> value;
			buffer_color.g = value;
			*_file >> value;
			buffer_color.b = value;
			_back_colors.push_back( buffer_color );
		}
		_file->close( );
	} else {
		std::cout << __FUNCTION__ << "-> error, cannot open config_back_colors.txt";
		is_ok = 0;
	}

	delete _file;
	return is_ok;
}

config_reader_c::config_s* config_reader_c::get( void ) {
	return &_config;
}
