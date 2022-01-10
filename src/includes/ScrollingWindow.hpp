#pragma once

class ScrollingWindow {
	public:
		ScrollingWindow(int size);
		void move(int delta);
		void resize(int size);
		void setContentSize(int contentSize);
		int getStart();
		int getEnd();
		int getAbsoluteIndex(int row);
	private:
		void clampPosition();
		int _position;
		int _size;
		int _contentSize;
};