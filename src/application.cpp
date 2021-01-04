#include "application.hpp"

application::application( void ) {
	if ( !_init( ) ) {
		std::cout << "Application init -> error!";
		system( "pause" );
		return;
	} else
		std::cout << "Application init done!\n";

	// Главный цикл
	while( _sf_render_window->isOpen( ) ) {
		while( _sf_render_window->pollEvent( *_sf_event ) ) {
			switch( _sf_event->type ) {
				case sf::Event::Closed : {
					_sf_render_window->close( );
					break;
				}
				default :
					break;
			}	// switch event type

		}	// while poll event

		_logic( );

		_render( );

	}	// while win open

	std::cout << "Application succesfully closed\n";
	system( "pause" );
}

application::~application( void ) {
	// nope
}

bool application::_init( void ) {
	// Флаг успешной инициализации
	bool ok_flag = 1;

	// SFML
	_sf_font = new sf::Font;
	_sf_text = new sf::Text;
	_sf_rect_shape = new sf::RectangleShape;
	_sf_event = new sf::Event;

	if ( _sf_font->loadFromFile( "resource/Anonymous_Pro_B.ttf" ) ) {
		_sf_text->setFont( *_sf_font );
		_sf_text->setFillColor( sf::Color::White );
		_sf_text->setCharacterSize( 14 );
	} else
		ok_flag = 0;

	_sf_render_window = new sf::RenderWindow( sf::VideoMode( window_size_x, window_size_y ), "Fearscape AI" );
	_sf_render_window->setFramerateLimit( 60 );

	// proc
	std::cout << "Searching for application..." << "\n";

	while( !_window_hwnd )
		_window_hwnd = FindWindow( 0, working_app_name.c_str( ) );	// from global
	std::cout << "Application found!\n";

	// Разворачивание окна на передний план
	SetForegroundWindow( _window_hwnd );

	// Цвета блоков
	_online_tetris_settings = new settings_s;
	_online_tetris_settings->used_cells.push_back( { sf::Color( 192, 19, 2 ) } );	// light red
	_online_tetris_settings->used_cells.push_back( { sf::Color( 217, 71, 30 ) } );	// red

	_online_tetris_settings->used_cells.push_back( { sf::Color( 145, 2, 172 ) } );	// purple
	_online_tetris_settings->used_cells.push_back( { sf::Color( 176, 36, 195 ) } );

	_online_tetris_settings->used_cells.push_back( { sf::Color( 0, 223, 223 ) } );	// light blue

	_online_tetris_settings->used_cells.push_back( { sf::Color( 238, 129, 0 ) } );	// orangle
	_online_tetris_settings->used_cells.push_back( { sf::Color( 248, 174, 1 ) } );

	_online_tetris_settings->used_cells.push_back( { sf::Color( 0, 0, 205 ) } );	// blue
	_online_tetris_settings->used_cells.push_back( { sf::Color( 0, 124, 204 ) } );

	_online_tetris_settings->used_cells.push_back( { sf::Color( 39, 144, 0 ) } );	// green
	_online_tetris_settings->used_cells.push_back( { sf::Color( 86, 164, 0 ) } );

	_online_tetris_settings->used_cells.push_back( { sf::Color( 249, 236, 35 ) } );	// yellow
	_online_tetris_settings->used_cells.push_back( { sf::Color( 251, 191, 32 ) } );

	// Цвета фона
	_online_tetris_settings->free_cells.push_back( { sf::Color( 255, 255, 255 ) } );// background
	_online_tetris_settings->free_cells.push_back( { sf::Color( 223, 223, 223 ) } );// shadow

	_online_tetris_settings->free_cells.push_back( { sf::Color( 235, 234, 240 ) } );
	_online_tetris_settings->free_cells.push_back( { sf::Color( 235, 234, 239 ) } );

	// Инициализация внутренних классов
	_pf = new pixel_field_c( sf::Vector2i( global_field_size_x, global_field_size_y ) );
	_cf = new cell_field_c( sf::Vector2i( global_field_size_x, global_field_size_y ) );

	_figure_pf = new pixel_field_c( sf::Vector2i( global_figure_size_x, global_figure_size_x ) );
	_figure_cf = new cell_field_c( sf::Vector2i( global_figure_size_x, global_figure_size_x ) );

	return ok_flag;
}

void application::_logic( void ) {
	// Взятие поля цветов с экрана
	_fill_pixel_field_from_screen( _pf,	sf::Vector2i( screen_start_field_x, screen_start_field_y ),
										sf::Vector2i( screen_block_size, screen_block_size ) );

	// Конвертирование поля цветов в поле ячеек с игнорированием двух линий сверху поля
	if ( !_pf->convert_to_cellfield( _cf, _online_tetris_settings, 2 ) )
		std::cout << "_logic -> convert field error";

	// Взятие поля цветов фигуры с экрана
	_fill_pixel_field_from_screen( _figure_pf,	sf::Vector2i( screen_start_figure_x, screen_start_figure_y ),
												sf::Vector2i( screen_block_size, screen_block_size ) );
	// Конвертирование поля цветов в поле ячеек
	if ( !_figure_pf->convert_to_cellfield( _figure_cf, _online_tetris_settings ) )
		std::cout << "Convert figure error";
	if ( !_figure->set_from_cell_field( _figure_cf, _online_tetris_settings ) )
		std::cout << "Set from cell figure error";
}

void application::_render( void ) {
	// Clear
	_sf_render_window->clear( sf::Color::Black );

	// Render pixel field
	_render_text( sf::Vector2f( 0.0f, 0.0f ), "raw pix field:" );
	_sf_rect_shape->setSize( sf::Vector2f( 10.0f, 10.0f ) );
	for ( unsigned x = 0; x < global_field_size_x; x++ )
		for ( unsigned y = 0; y < global_field_size_y; y++ ) {
			_sf_rect_shape->setPosition( sf::Vector2f( x * 10.0f + 5.0f, y * 10.0f + 15.0f ) );
			_sf_rect_shape->setFillColor( _pf->get( sf::Vector2i( x, y ) ) );
			_sf_render_window->draw( *_sf_rect_shape );
		}

	// Render cell field
	_render_text( sf::Vector2f( 118.0f, 0.0f ), "cell field:" );
	sf::Color cf_color;
	for ( unsigned x = 0; x < global_field_size_x; x++ )
		for ( unsigned y = 0; y < global_field_size_y; y++ ) {
			_sf_rect_shape->setPosition( sf::Vector2f( x * 10.0f + 110.0f, y * 10.0f + 15.0f ) );
			if ( _cf->get( sf::Vector2i( x, y ) ) )
				cf_color = sf::Color::White;
			else
				cf_color = sf::Color( 55, 55, 55 );

			_sf_rect_shape->setFillColor( cf_color );
			_sf_render_window->draw( *_sf_rect_shape );
		}

	// Render figure
	_render_text( sf::Vector2f( 9.0f, 215.0f ), "next figure:" );
	_sf_rect_shape->setSize( sf::Vector2f( 10.0f, 10.0f ) );
	for ( unsigned x = 0; x < global_figure_size_x; x++ )
		for ( unsigned y = 0; y < global_figure_size_y; y++ ) {
			_sf_rect_shape->setPosition( sf::Vector2f( x * 10.0f + 35.0f, y * 10.0f + 235.0f ) );
			_sf_rect_shape->setFillColor( _figure_pf->get( sf::Vector2i( x, y ) ) );
			_sf_render_window->draw( *_sf_rect_shape );
		}

	std::string buf_str = "value: ";
	buf_str += _figure->get_type_char( );
	_render_text( sf::Vector2f( 9.0f, 275.0f ), buf_str );

	// double buff
	_sf_render_window->display( );
}

void application::_fill_pixel_field_from_screen( pixel_field_c *pixel_field, sf::Vector2i start_pos, sf::Vector2i offset ) {

	// Получение контекста устройства экрана
	auto window_dc_space = GetDC( NULL );

	// Получение размера поля
	sf::Vector2i f_size = pixel_field->get_size( );

	// Проход по матрице
	for ( int x = 0; x < f_size.x; x++ ) {
		for ( int y = 0; y < f_size.y; y++ ) {
			// Получение значения цвета пикселя
			uint32_t pixel = GetPixel( window_dc_space, start_pos.x + offset.x * x,
														start_pos.y + offset.y * y );
			// Запись пикселя в поле
			pixel_field->set( sf::Vector2i( x, y ),
							  sf::Color( GetRValue( pixel ),
										 GetGValue( pixel ),
										 GetBValue( pixel ) ) );
		}
	}

	// Закрытие контекста экрана
	ReleaseDC( NULL, window_dc_space );
}

void application::_render_text( sf::Vector2f position, std::string text ) {
	_sf_text->setPosition( position );
	_sf_text->setString( text );
	_sf_render_window->draw( *_sf_text );
}
