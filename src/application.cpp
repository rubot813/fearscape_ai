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
}

application::~application( void ) {
	delete _sf_font;
	delete _sf_text;
	delete _sf_rect_shape;
	delete _sf_event;
	delete _sf_render_window;
	delete _pf;
	delete _cf;
	delete _current_figure_pf;
	delete _previous_figure_cf;
	delete _previous_figure_pf;
	delete _tetris_ai;
	delete _keypress_emulator;
}

bool application::_init( void ) {
	// Флаг успешной инициализации
	bool ok_flag = 1;

	// Чтение конфигов
	if ( !config_reader_c::get_instance( )->read( ) ) {
		std::cout << __FUNCTION__ << " -> cannot open config files!\n";
		return 0;
	}

	std::cout << "Searching for application..." << "\n";
	// Поиск окна по имени
	_window_hwnd = NULL;
	while( !_window_hwnd )
		_window_hwnd = FindWindow( 0, config->window_name.c_str( ) );	// from global
	std::cout << "Application found!\n";

	// Разворачивание окна на передний план
	SetForegroundWindow( _window_hwnd );

	// Создание и запуск класса эмуляции нажатия на кнопки
	_keypress_emulator = new keypress_emulator_c( std::chrono::milliseconds( config->kp_time ), _window_hwnd );

	// SFML
	_sf_font		= new sf::Font;
	_sf_text		= new sf::Text;
	_sf_rect_shape	= new sf::RectangleShape;
	_sf_event		= new sf::Event;

	if ( _sf_font->loadFromFile( "resource/Anonymous_Pro_B.ttf" ) ) {
		_sf_text->setFont( *_sf_font );
		_sf_text->setFillColor( sf::Color::White );
		_sf_text->setCharacterSize( 14 );
	} else
		ok_flag = 0;

	// Создание своего окна
	_sf_render_window = new sf::RenderWindow( sf::VideoMode( 215, 400 ), "Fearscape AI gen 3", sf::Style::Titlebar | sf::Style::Close );
	_sf_render_window->setFramerateLimit( 15 );

	// Цвет фона

	// Инициализация внутренних классов
	_pf = new pixel_field_c( sf::Vector2i( config->field_size.x, config->field_size.y ) );
	_cf = new cell_field_c( sf::Vector2i( config->field_size.x, config->field_size.y ) );

	_current_figure_pf = new pixel_field_c( sf::Vector2i( config->figure_cell_size.x, config->figure_cell_size.y ) );

	_previous_figure_pf = new pixel_field_c( sf::Vector2i( config->figure_cell_size.x, config->figure_cell_size.y ) );
	_previous_figure_cf = new cell_field_c( sf::Vector2i( config->figure_cell_size.x, config->figure_cell_size.y ) );

	// Оставляю в _previous_figure_pf мусор, чтобы не срабатывало сравнение
	_previous_figure_pf->set( sf::Vector2i( 0, 0 ), sf::Color::Blue );

	// Инициализация ИИ
	_tetris_ai		= new tetris_ai_c;
	_placed_figure_counter = 0;

	return ok_flag;
}

void application::_logic( void ) {

	// Взятие игрового поля с экрана и конвертирование в поле ячеек с игнорированием трех линий сверху
	// ====
	_fill_pixel_field_from_screen( _pf,	sf::Vector2i( config->screen_start_field.x, config->screen_start_field.y ),
	                               sf::Vector2i( config->screen_figure_size, config->screen_figure_size ) );
	bool field_convert = _pf->convert_to_cellfield( _cf, 3 );
	// ====

	// Взятие поля следующей фигуры с экрана
	// ====
	_fill_pixel_field_from_screen( _current_figure_pf,	sf::Vector2i( config->screen_start_figure.x, config->screen_start_figure.y ),
	                               sf::Vector2i( config->screen_figure_size, config->screen_figure_size ) );

	// Если изменилась следующая фигура и успешно конвертировали поле,
	//  значит нужно делать ход по предыдущей
	if ( *_current_figure_pf != *_previous_figure_pf && field_convert && !_keypress_emulator->get_keyqueue_count( ) ) {

		// Получение поля ячеек
		_previous_figure_pf->convert_to_cellfield( _previous_figure_cf );	// bool

		// Если фигура успешно определена по полю ячеек
		if ( _figure->create_from_cell_field( _previous_figure_cf ) ) {

			// Определение перемещения и вращения фигуры по одному из алгоритмов AI
			_move_variant	= _tetris_ai->ai_alg_bm( _cf, _figure, &_ai_debug_data );

			// Эмуляция нажатия кнопок
			_keypress_emulator->add_keypress_to_queue( &_move_variant );

			// Счетчик скинутых фигур
			_placed_figure_counter++;
		}

		*_previous_figure_pf = *_current_figure_pf;
	}
	// ====
}

void application::_render( void ) {
	// Clear
	_sf_render_window->clear( sf::Color::Black );
	std::string buf_str;

	// Render pixel field
	_render_text( sf::Vector2f( 0.0f, 0.0f ), "raw pix field:" );
	_sf_rect_shape->setSize( sf::Vector2f( 10.0f, 10.0f ) );
	for ( int x = 0; x < config->field_size.x; x++ )
		for ( int y = 0; y < config->field_size.y; y++ ) {
			_sf_rect_shape->setPosition( sf::Vector2f( x * 10.0f + 5.0f, y * 10.0f + 15.0f ) );
			_sf_rect_shape->setFillColor( _pf->get( sf::Vector2i( x, y ) ) );
			_sf_render_window->draw( *_sf_rect_shape );
		}

	// Render cell field
	_render_text( sf::Vector2f( 118.0f, 0.0f ), "cell field:" );
	uint8_t color_id;
	for ( int x = 0; x < config->field_size.x; x++ )
		for ( int y = 0; y < config->field_size.y; y++ ) {
			_sf_rect_shape->setPosition( sf::Vector2f( x * 10.0f + 110.0f, y * 10.0f + 15.0f ) );
			if ( _cf->get( sf::Vector2i( x, y ) ) )
				color_id = 245;
			else
				color_id = 55;
			_sf_rect_shape->setFillColor( sf::Color( color_id, color_id, color_id ) );
			_sf_render_window->draw( *_sf_rect_shape );
		}

	// Render figure value
	buf_str = "prev fig: ";
	buf_str += _figure->get_type_char( );
	_render_text( sf::Vector2f( 9.0f, 212.0f ), buf_str );

	// Render previous figure
	_render_text( sf::Vector2f( 9.0f, 225.0f ), "curr figure:" );
	_sf_rect_shape->setSize( sf::Vector2f( 10.0f, 10.0f ) );
	for ( int x = 0; x < config->figure_cell_size.x; x++ )
		for ( int y = 0; y < config->figure_cell_size.y; y++ ) {
			_sf_rect_shape->setPosition( sf::Vector2f( x * 10.0f + 35.0f, y * 10.0f + 245.0f ) );
			_sf_rect_shape->setFillColor( _previous_figure_pf->get( sf::Vector2i( x, y ) ) );
			_sf_render_window->draw( *_sf_rect_shape );
		}

	// Render field size
	buf_str.clear( );
	buf_str += "x size: " + std::to_string( config->field_size.x );
	_render_text( sf::Vector2f( 120.0f, 225.0f ), buf_str );

	buf_str.clear( );
	buf_str += "y size: " + std::to_string( config->field_size.y );
	_render_text( sf::Vector2f( 120.0f, 237.0f ), buf_str );

	// Render count of holes
	buf_str.clear( );
	buf_str += "holes: " + std::to_string( _ai_debug_data.holes_count );
	_render_text( sf::Vector2f( 120.0f, 249.0f ), buf_str );

	// Render figure counter
	buf_str.clear( );
	buf_str += "fig ctr: " + std::to_string( _placed_figure_counter );
	_render_text( sf::Vector2f( 120.0f, 261.0f ), buf_str );

	// Render height line
	_render_text( sf::Vector2f( 78.0f, 285.0f ), "height:" );
	buf_str.clear( );
	_sf_text->setPosition( sf::Vector2f( 0.0f, 300.0f ) );
	if ( _ai_debug_data.height.data.size( ) ) {
		for ( unsigned i = 0; i < _ai_debug_data.height.data.size( ); i++ )
			buf_str += std::to_string( _ai_debug_data.height.data.at( i ) ) + ",";
		if ( buf_str.size( ) )
			buf_str.erase( buf_str.size( ) - 1 );
		_sf_text->setString( buf_str );
	} else
		_sf_text->setString( "height is empty" );
	_sf_render_window->draw( *_sf_text );

	// Render move variant
	buf_str.clear( );
	buf_str = "move variant: ";
	_render_text( sf::Vector2f( 52.0f, 315.0f ), buf_str );

	buf_str.clear( );
	buf_str += "pos: ";
	if ( _ai_debug_data.height.data.size( ) )	// Если высота получена, значит и _move_variant заполнен
		buf_str += std::to_string( _move_variant.position );
	else
		buf_str += "n/a";
	_render_text( sf::Vector2f( 25.0f, 330.0f ), buf_str );

	buf_str.clear( );
	buf_str += "rot: ";
	if ( _ai_debug_data.height.data.size( ) )	// Если высота получена, значит и _move_variant заполнен
		buf_str += std::to_string( _move_variant.rotation );
	else
		buf_str += "n/a";
	_render_text( sf::Vector2f( 118.0f, 330.0f ), buf_str );

	// Render key queue size
	buf_str.clear( );
	buf_str = "key queue count: " + std::to_string( _keypress_emulator->get_keyqueue_count( ) );
	_render_text( sf::Vector2f( 25.0f, 345.0f ), buf_str );

	// Render AI algorithm name
	buf_str.clear( );
	buf_str = "ai: ";
	if ( _ai_debug_data.alg_name.size( ) )
		buf_str += _ai_debug_data.alg_name;
	else
		buf_str += "n/a";
	_render_text( sf::Vector2f( 10.0f, 360.0f ), buf_str );

	// Render AI calculation time
	buf_str.clear( );
	buf_str = "calc time: ";
	buf_str += std::to_string( _ai_debug_data.calc_time.count( ) ) + " ms";
	_render_text( sf::Vector2f( 10.0f, 375.0f ), buf_str );

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
