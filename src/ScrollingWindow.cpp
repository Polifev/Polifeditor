#include "ScrollingWindow.hpp"

ScrollingWindow::ScrollingWindow(int size): _size {size}, _position {0}, _contentSize{0}{
}

void ScrollingWindow::move(int delta){
	_position += delta;
	clampPosition();
}

void ScrollingWindow::resize(int size){
	_size = size;
	clampPosition();
}

void ScrollingWindow::setContentSize(int contentSize){
	_contentSize = contentSize;
	clampPosition();
}

int ScrollingWindow::getStart(){
	return _position;
}

int ScrollingWindow::getEnd(){
	if(_size > _contentSize){
		return _position + _contentSize;
	}
	return _position + _size;
}

int ScrollingWindow::getAbsoluteIndex(int row){
	return _position + row;
}

void ScrollingWindow::clampPosition(){
	// recompute position
	int hiddenSize = _contentSize - _size;
	_position = _position > hiddenSize ? hiddenSize : _position;
	_position = _position < 0 ? 0 : _position;
}