#include "TryTetris.h"
#include<stdio.h>
TetrisSystem::TetrisSystem() : m_board(), m_brick(), waitingTime(2000), iMarginX(2), iMarginY(1), oldTime() , boardCol(20), boardRow(15)
{
	m_board = new Board(boardCol,boardRow);
	m_brick = new Brick();
	m_draw = new Draw(iMarginX, iMarginY);
}

TetrisSystem::~TetrisSystem()
{
	if (m_board)
		delete m_board;
	if (m_brick)
		delete m_brick;
	if (m_draw)
		delete m_draw;
}

void TetrisSystem::Run()
{
	oldTime = timeGetTime();

	// First Draw.
	m_draw->Paint(m_board->GetBoardArray(),Point(0,0));

	// First Brick Set.
	m_brick->SetPosition(Point(boardCol / 2, 0));
	m_brick->SetType(rand() % 7);
	m_brick->SetRotate(0);
	// Play
	while (!m_board->IsGameOver())
	{
		// Key Event.
		if (_kbhit())
		{
			MessageProc();
		}
		// WaitingTime Event.
		if (timeGetTime() - oldTime >= waitingTime)
		{
			m_brick->Move(0, 1);
		}
		// 움직인후 충돌체크, 충돌 일시 충돌 처리를 한다.
		while (m_board->IsCollision(m_brick->GetShapeArray(), m_brick->GetPosition()))
		{
			CollisionSolve();
		}
		m_draw->Clear();
		TetrisDraw();
	}
}

void TetrisSystem::MessageProc()
{
	input = (KeyBoard)_getch();
	switch (input) {
	case UP:
		m_brick->Rotate();
		break;
	case DOWN:
		m_brick->Move(0, 1);
		oldTime = timeGetTime();
		break;
	case RIGHT:
		m_brick->Move(-1, 0);
		break;
	case LEFT:
		m_brick->Move(1, 0);
		break;
	case SPACEBAR:
		while (!m_board->IsCollision(m_brick->GetShapeArray(), m_brick->GetPosition()))
			m_brick->Move(0, 1);
		oldTime = timeGetTime();
		break;
	}
}

void TetrisSystem::CollisionSolve()
{
	switch (input)
	{
	case UP:
		m_brick->Move(1, 0);
		if (m_board->IsCollision(m_brick->GetShapeArray(), m_brick->GetPosition()))
			m_brick->Move(-2, 0);
		break;
	case RIGHT:
		m_brick->Move(1, 0);
		break;
	case LEFT:
		m_brick->Move(-1, 0);
		break;
	case DOWN: case SPACEBAR: // 위로 한칸 올린 후, 스텍을 쌓고 라인을 체크한다.
		m_brick->Move(0, 1);
		m_board->StackBrick(m_brick->GetShapeArray(), m_brick->GetPosition());
		m_board->IsLineFull();
		break;
	}
}

void TetrisSystem::TetrisDraw()
{
	m_draw->Paint(m_board->GetBoardArray(),Point(0,0));
	m_draw->Paint(m_brick->GetShapeArray(),m_brick->GetPosition());
}
