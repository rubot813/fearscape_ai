#include "tetris_ai.hpp"

tetris_ai_c::tetris_ai_c( void ) {
	srand( static_cast< std::size_t >( time( NULL ) ) );	// ai_random
}

tetris_ai_c::~tetris_ai_c( void ) {
	// np
}

tetris_ai_c::move_variant_s tetris_ai_c::ai_alg_simple_placer( cell_field_c *cell_field, figure_c *figure, ai_debug_data_s *debug ) {

	auto start_time = std::chrono::steady_clock::now( );

	// Расчет высот столбцов поля
	debug->height = _calculate_height( cell_field );

	// Расчет суммы высот
	debug->height_sum = _calculate_height_sum( &debug->height );

	// Расчет количества отверстий
	debug->holes_count = _calculate_holes( cell_field );

	// Итоговый вариант хода
	move_variant_s move_variant;

	// = = = = =
	move_variant.position = 0;
	move_variant.rotation = figure_c::rt_standart;
	// = = = = =

	debug->alg_name = __FUNCTION__;
	auto end_time = std::chrono::steady_clock::now( );
	debug->calc_time = std::chrono::duration_cast< std::chrono::milliseconds >( end_time - start_time );
	return move_variant;
}

tetris_ai_c::move_variant_s tetris_ai_c::ai_alg_random( cell_field_c *cell_field, figure_c *figure, ai_debug_data_s *debug ) {

	auto start_time = std::chrono::steady_clock::now( );

	// Расчет высот столбцов поля
	debug->height = _calculate_height( cell_field );

	// Расчет суммы высот
	debug->height_sum = _calculate_height_sum( &debug->height );

	// Расчет количества отверстий
	debug->holes_count = _calculate_holes( cell_field );

	// Итоговый вариант хода
	move_variant_s move_variant;

	// = = = = =
	move_variant.position = rand( ) % 7 - 3;									// -3 .. 4
	move_variant.rotation = static_cast< figure_c::rotation_e >( rand( ) % 3 );	// 0 .. 3
	// = = = = =

	debug->alg_name = __FUNCTION__;
	auto end_time = std::chrono::steady_clock::now( );
	debug->calc_time = std::chrono::duration_cast< std::chrono::milliseconds >( end_time - start_time );
	return move_variant;
}

tetris_ai_c::move_variant_s tetris_ai_c::ai_alg_bm( cell_field_c *cell_field, figure_c *figure, ai_debug_data_s *debug ) {

	auto start_time = std::chrono::steady_clock::now( );

	// Контейнер очков
	std::vector< _score_s > scores;

	// Расчет высот столбцов поля
	debug->height = _calculate_height( cell_field );

	// Расчет суммы высот
	debug->height_sum = _calculate_height_sum( &debug->height );

	// Расчет количества отверстий
	debug->holes_count = _calculate_holes( cell_field );

	// Копия фигуры
	figure_c fg = *figure;

	// Цикл по вращениям фигуры
	for ( uint8_t rt = 0; rt < 4; rt++ ) {

		// Установка поворота фигуры
		fg.set_rotation( static_cast< figure_c::rotation_e >( rt ) );

		// Получение проекции фигуры
		figure_c::projection_s f_projection = fg.get_horizontal_projection( );

		// Получение количества пустых горизонтальных линий с краев фигуры
		int8_t left_offset = 0;
		if ( !f_projection.get_left_offset( &left_offset ) )
			std::cout << __FUNCTION__ << " -> get left offset error\n";

		int8_t right_offset = 0;
		if ( !f_projection.get_right_offset( &right_offset ) )
			std::cout << __FUNCTION__ << " -> get right offset error\n";

		// Цикл по всем вариантам постановки фигуры с данным вращением
		for ( int8_t hor_pos = -left_offset; hor_pos <= ( field_size_x_c - figure_size_x_c + right_offset ); hor_pos++ ) {

			// Копия поля, чтобы не испортить указатель
			cell_field_c cf = *cell_field;

			// Метод кладет фигуру на поле
			if ( fg.place_to_cellfield( &cf, hor_pos ) ) {
				// Расчет параметров для поля с фигурой:

				// Высоты столбцов поля
				height_s he = _calculate_height( &cf );

				// Сумма высот столбцов поля
				uint16_t hs = _calculate_height_sum( &he );

				// Количество отверстий
				uint8_t ho = _calculate_holes( &cf );

				// Количество линий
				uint8_t li = _calculate_lines( &cf );

				// Количество очков
				_score_s current_score;

				// Формула расчета очков хода
				current_score.score	= -ho;

				// Заполнение хода
				current_score.move_variant.position = hor_pos - 3;
				current_score.move_variant.rotation = static_cast< figure_c::rotation_e >( rt );
				*current_score.cf = cf;

				// Добавление хода с его весом в контейнер
				scores.push_back( current_score );

			} else
				std::cout << __FUNCTION__ << " -> error, cannot place figure\n";
		}	// for horizontal position
	}	// for rotation

	std::cout << __FUNCTION__ << " move variants = " << scores.size( ) << "\n";

	// Сортировка контейнера по наибольшему весу
	std::sort( scores.begin( ), scores.end( ),
			[ ]( const _score_s &s0, const _score_s &s1 ) {
				return ( s0.score > s1.score );
			} );

	debug->alg_name = __FUNCTION__;
	auto end_time = std::chrono::steady_clock::now( );
	debug->calc_time = std::chrono::duration_cast< std::chrono::milliseconds >( end_time - start_time );

	// Пока костыль
	move_variant_s var;
	if ( !scores.size( ) ) {
		return var;
	} else {
		cell_field_c *cf = scores.front( ).cf;
		sf::Vector2i cf_size = cf->get_size( );
		std::cout << "Best move:\n";
		for ( uint8_t y = 0; y < cf_size.y; y++ ) {
			for ( uint8_t x = 0; x < cf_size.x; x++ ) {
				std::cout << cf->get( sf::Vector2i( x, y ) ) << " ";
			}
			std::cout << "\n";
		}

		// Возврат наилучшего результата хода
		return scores.front( ).move_variant;
	}
}

tetris_ai_c::height_s tetris_ai_c::_calculate_height( cell_field_c *cell_field ) {
	// Создание высоты и задание размера исходя из ширины поля
	height_s height;
	sf::Vector2i field_size = cell_field->get_size( );		// Размер поля
	height.data.resize( field_size.x, 0 );
	height.valid = 1;

	// Проход по полю
	// Слева направо 0 .. n
	for ( uint8_t x = 0; x < field_size.x; x++ ) {
		// Сверху вниз 0 .. n
		for ( uint8_t y = 0; y < field_size.y; y++ ) {
			if ( cell_field->get( sf::Vector2i( x, y ) ) ) {
				height.data.at( x ) = field_size.y - y;
				break;
			}
		}
	}
	return height;
}

uint8_t tetris_ai_c::_calculate_holes( cell_field_c *cell_field ) {
	uint8_t holes = 0;	// Счетчик отверстий
	bool get_used;	// Флаг - встретили ли заполненную ячейку
	sf::Vector2i field_size = cell_field->get_size( );	// Размер поля

	// Проход по полю
	// Слева направо 0 .. n
	for ( uint8_t x = 0; x < field_size.x; x++ ) {
		get_used = 0;
		// Сверху вниз 0 .. n
		for ( uint8_t y = 0; y < field_size.y; y++ ) {
			if ( cell_field->get( sf::Vector2i( x, y ) ) )
				get_used = 1;
			else {
				if ( get_used )
					holes++;
			}
		}
	}
	return holes;
}

uint8_t tetris_ai_c::_calculate_lines( cell_field_c *cell_field ) {
	uint8_t lines = 0;	// Счетчик линий
	sf::Vector2i field_size = cell_field->get_size( );	// Размер поля

	// Проход по полю
	// Сверху вниз 0 .. n
	for ( uint8_t y = 0; y < field_size.x; y++ ) {
		// Слева направо 0 .. n
		for ( uint8_t x = 0; x < field_size.x; x++ ) {
			if ( !cell_field->get( sf::Vector2i( x, y ) ) )
				break;
			else if ( x == field_size.x - 1 )
				lines++;
		}	// for x
	}	// for y
	return lines;
}

std::size_t	tetris_ai_c::_calculate_height_sum( height_s *height ) {
	std::size_t value = 0;
	auto iter = height->data.begin( );
	while( iter != height->data.end( ) ) {
		value += *iter;
		iter++;
	}
	return value;
}

