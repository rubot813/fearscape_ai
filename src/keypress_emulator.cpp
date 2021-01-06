#include "keypress_emulator.hpp"

keypress_emulator_c::keypress_emulator_c( std::chrono::milliseconds key_press_delay, HWND window_handle ) {
	_key_press_delay = key_press_delay;
	_window_handle = window_handle;

	// Создание потока и его запуск отдельно от потока программы
	_thread = new std::thread( &keypress_emulator_c::_task, this );
	_thread->detach( );
}

keypress_emulator_c::~keypress_emulator_c( void ) {
	delete _thread;	// check later for safe terminating of the thread
}

void keypress_emulator_c::add_keypress_to_queue( tetris_ai_c::move_variant_s *move_variant ) {
	_thread_mutex.lock( );

	// Вращение блока
    for ( uint8_t i = 0; i < move_variant->rotation; i++ )
		_key_queue.push( VK_UP );

	// Перемещение блока
	if ( move_variant->position < 0 ) {
		for ( int8_t i = move_variant->position; i < 0; i++ )
			_key_queue.push( VK_LEFT );
	} else {
		for ( int8_t i = move_variant->position; i > 0; i-- )
			_key_queue.push( VK_RIGHT );
	}

	// Опускание блока на поле
	_key_queue.push( VK_SPACE );

	_thread_mutex.unlock( );
}

std::size_t keypress_emulator_c::get_keyqueue_count( void ) {
	std::size_t kq_size;
	_thread_mutex.lock( );
	kq_size = _key_queue.size( );
	_thread_mutex.unlock( );
	return kq_size;
}

void keypress_emulator_c::_task( void ) {
	while( 1 ) {
		// Если есть кнопки
		if ( _key_queue.size( ) ) {
			// Беру код кнопки из очереди и удаляю ее
			WPARAM key = _key_queue.front( );
			_key_queue.pop( );

			// Эмуляция нажатия и отпускания кнопок
			SendMessage( _window_handle, WM_KEYDOWN, key, 0 );
			std::this_thread::sleep_for( std::chrono::milliseconds( _key_press_delay ) );
			SendMessage( _window_handle, WM_KEYUP, key, 0 );
		}

		// Задержка между эмуляцией нажатия кнопок
		std::this_thread::sleep_for( std::chrono::milliseconds( _key_press_delay ) );
	}
}
