#pragma once
#include<Windows.h>
class Mode {
private:
	bool isNewState;
	int afterState;
public:
	Mode() :isNewState(false) {	}
	virtual void Initialization() =0;
	virtual void Update(float dt) = 0;
	virtual void Draw(HWND hWnd,HDC hdc) = 0;
	virtual void Shutdown() = 0;
	virtual void KeyEvent(WPARAM wParam) { /*empty*/ };

	inline int IsNewState() { 
		if (isNewState) {
			isNewState = false;
			return afterState;
		}
		return -1;
	}
	inline void ChangeState(int idx) { 
		isNewState = true;
		afterState = idx;
	}
};