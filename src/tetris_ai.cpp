#include "tetris_ai.hpp"

tetris_ai_c::tetris_ai_c( void ) {
	_height = new height_s;
}

tetris_ai_c::~tetris_ai_c( void ) {
	delete _height;
}

tetris_ai_c::height_s* tetris_ai_c::get_current_height( void ) {
	return _height;
}

tetris_ai_c::move_variant_s tetris_ai_c::ai_calc_bm_noholes( cell_field_c *cell_field, figure_c *figure ) {

}
