#include "keypress_emulator.hpp"

keypress_emulator::keypress_emulator( std::chrono::milliseconds key_press_delay, HWND window_handler ) {
	_key_press_delay = key_press_delay;
	_window_handler = window_handler;

	// Создание потока и его запуск отдельно от потока программы
	_thread = new std::thread( &keypress_emulator::_task, this );
	_thread->detach( );
}

keypress_emulator::~keypress_emulator( void ) {
	delete _thread;	// check later for safe terminating of the thread
}

void keypress_emulator::add_keypress_to_queue( tetris_ai_c::move_variant_s move_variant ) {

}

std::size_t keypress_emulator::get_keyqueue_count( void ) {
	std::size_t kq_size;
	_thread_mutex.lock( );
	kq_size = _key_queue.size( );
	_thread_mutex.unlock( );
	return kq_size;
}

void keypress_emulator::_task( void ) {
	while( 1 ) {


	}
}
