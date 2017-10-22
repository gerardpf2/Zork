#include "CombatSystem.h"

#include <assert.h>
#include "CommandListener.h"

CombatSystem::CombatSystem(int rows, int columns, int playerRow, int playerColumn, CombatDirectionType playerDirection, int enemyRow, int enemyColumn, CombatDirectionType enemyDirection, int cellWidth, int cellHeight) :
	rows(rows), columns(columns), playerRow(playerRow), playerColumn(playerColumn), playerDirection(playerDirection), enemyRow(enemyRow), enemyColumn(enemyColumn), enemyDirection(enemyDirection), cellWidth(cellWidth), cellHeight(cellHeight)
{
	assert(rows > 0);
	assert(columns > 0);
	assert(playerRow >= 0);
	assert(playerColumn >= 0);
	assert(enemyRow >= 0);
	assert(enemyColumn >= 0);
	assert(cellWidth > 0);
	assert(cellHeight > 0);
	assert(enemyRow < rows);
	assert(playerRow < rows);
	assert(enemyColumn < columns);
	assert(playerColumn < columns);
}

CombatSystem::~CombatSystem()
{ }

void CombatSystem::setCommandListener(CommandListener* commandListener)
{
	assert(commandListener);

	this->commandListener = commandListener;
}

bool CombatSystem::canMovePlayer(int rowIncrement, int columnIncrement) const
{
	int playerNextRow = playerRow + rowIncrement;
	int playerNextColumn = playerColumn + columnIncrement;
	
	return abs(rowIncrement) + abs(columnIncrement) == 1 && (playerNextRow != enemyRow || playerNextColumn != enemyColumn) && playerNextRow >= 0 && playerNextRow < rows && playerNextColumn >= 0 && playerNextColumn < columns;
}

bool CombatSystem::canMoveEnemy(int rowIncrement, int columnIncrement) const
{
	int enemyNextRow = enemyRow + rowIncrement;
	int enemyNextColumn = enemyColumn + columnIncrement;

	return abs(rowIncrement) + abs(columnIncrement) == 1 && (enemyNextRow != playerRow || enemyNextColumn != playerColumn) && enemyNextRow >= 0 && enemyNextRow < rows && enemyNextColumn >= 0 && enemyNextColumn < columns;
}

void CombatSystem::movePlayer(int rowIncrement, int columnIncrement)
{
	int playerNextRow = playerRow + rowIncrement;
	int playerNextColumn = playerColumn + columnIncrement;

	assert(playerNextRow >= 0 && playerNextRow < rows);
	assert(abs(rowIncrement) + abs(columnIncrement) == 1);
	assert(playerNextColumn >= 0 && playerNextColumn < columns);
	assert(playerNextRow != enemyRow || playerNextColumn != enemyColumn);

	playerRow = playerNextRow;
	playerColumn = playerNextColumn;

	printBattlefield();
}

void CombatSystem::moveEnemy(int rowIncrement, int columnIncrement)
{
	int enemyNextRow = enemyRow + rowIncrement;
	int enemyNextColumn = enemyColumn + columnIncrement;

	assert(enemyNextRow >= 0 && enemyNextRow < rows);
	assert(abs(rowIncrement) + abs(columnIncrement) == 1);
	assert(enemyNextColumn >= 0 && enemyNextColumn < columns);
	assert(enemyNextRow != playerRow || enemyNextColumn != playerColumn);

	enemyRow = enemyNextRow;
	enemyColumn = enemyNextColumn;

	printBattlefield();
}

bool CombatSystem::canRotatePlayer(CombatDirectionType playerDirection) const
{
	return this->playerDirection != playerDirection;
}

bool CombatSystem::canRotateEnemy(CombatDirectionType enemyDirection) const
{
	return this->enemyDirection != enemyDirection;
}

void CombatSystem::rotatePlayer(CombatDirectionType playerDirection)
{
	assert(this->playerDirection != playerDirection);

	this->playerDirection = playerDirection;

	printBattlefield();
}

void CombatSystem::rotateEnemy(CombatDirectionType enemyDirection)
{
	assert(this->enemyDirection != enemyDirection);

	this->enemyDirection = enemyDirection;

	printBattlefield();
}

void calculateDirectionCharAndPosition(CombatDirectionType combatDirectionType, const char* directionCharUpDown, const char* directionCharLeftRight, int incrementUpDown, int incrementLeftRight, const char*& directionChar, int& directionPosition)
{
	assert(directionCharUpDown);
	assert(directionCharLeftRight);

	switch(combatDirectionType)
	{
		case CombatDirectionType::UP:
			directionChar = directionCharUpDown;
			directionPosition -= incrementUpDown;

			break;
		case CombatDirectionType::DOWN:
			directionChar = directionCharUpDown;
			directionPosition += incrementUpDown;

			break;
		case CombatDirectionType::LEFT:
			directionChar = directionCharLeftRight;
			directionPosition -= incrementLeftRight;

			break;
		case CombatDirectionType::RIGHT:
			directionChar = directionCharLeftRight;
			directionPosition += incrementLeftRight;

			break;
	}
}

bool CombatSystem::playerAttackCanHit() const
{
	return abs(playerRow - enemyRow) + abs(playerColumn - enemyColumn) == 1 && playerFacingEnemy();
}

bool CombatSystem::enemyAttackCanHit() const
{
	return abs(enemyRow - playerRow) + abs(enemyColumn - playerColumn) == 1 && enemyFacingPlayer();
}

bool CombatSystem::playerProjectileCanHit() const
{
	return playerRow == enemyRow || playerColumn == enemyColumn && playerFacingEnemy();
}

bool CombatSystem::playerMissAttack() const
{
	// 20% miss

	return (float)rand() / (float)RAND_MAX <= 0.2f;
}

bool CombatSystem::enemyMissAttack() const
{
	// 20% miss

	return (float)rand() / (float)RAND_MAX <= 0.2f;
}

bool CombatSystem::playerMissProjectile() const
{
	// 40% miss

	return (float)rand() / (float)RAND_MAX <= 0.4f;
}

void CombatSystem::enemyFindMove(int& rowIncrement, int& columnIncrement) const
{
	rowIncrement = 0;
	columnIncrement = 0;

	if(enemyRow == playerRow)
	{
		if(enemyColumn < playerColumn) columnIncrement = 1;
		if(enemyColumn > playerColumn) columnIncrement = -1;
	}
	else if(enemyColumn == playerColumn)
	{
		if(enemyRow < playerRow) rowIncrement = 1;
		if(enemyRow > playerRow) rowIncrement = -1;
	}
	else
	{
		int rowDistance = enemyRow - playerRow;
		int columnDistance = enemyColumn - playerColumn;

		int absRowDistance = abs(rowDistance);
		int absColumnDistance = abs(columnDistance);

		if(absRowDistance > 0 && absRowDistance <= absColumnDistance)
		{
			if(columnDistance > 0) columnIncrement = -1;
			else columnIncrement = 1;

			/* if(rowDistance > 0) rowIncrement = -1;
			else rowIncrement = 1; */
		}
		else if(absColumnDistance > 0)
		{
			if(rowDistance > 0) rowIncrement = -1;
			else rowIncrement = 1;

			/* if(columnDistance > 0) columnIncrement = -1;
			else columnIncrement = 1; */
		}
	}
}

bool CombatSystem::playerFacingEnemy() const
{
	if(playerRow == enemyRow)
	{
		if(playerColumn > enemyColumn && playerDirection == CombatDirectionType::LEFT) return true;
		if(playerColumn < enemyColumn && playerDirection == CombatDirectionType::RIGHT) return true;
	}
	else if(playerColumn == enemyColumn)
	{
		if(playerRow > enemyRow && playerDirection == CombatDirectionType::UP) return true;
		if(playerRow < enemyRow && playerDirection == CombatDirectionType::DOWN) return true;
	}

	return false;
}

bool CombatSystem::enemyFacingPlayer() const
{
	if(enemyRow == playerRow)
	{
		if(enemyColumn > playerColumn && enemyDirection == CombatDirectionType::LEFT) return true;
		if(enemyColumn < playerColumn && enemyDirection == CombatDirectionType::RIGHT) return true;
	}
	else if(enemyColumn == playerColumn)
	{
		if(enemyRow > playerRow && enemyDirection == CombatDirectionType::UP) return true;
		if(enemyRow < playerRow && enemyDirection == CombatDirectionType::DOWN) return true;
	}

	return false;
}

CombatDirectionType CombatSystem::enemyFindRotation() const
{
	if(enemyRow == playerRow)
	{
		if(enemyColumn > playerColumn) return CombatDirectionType::LEFT;
		if(enemyColumn < playerColumn) return CombatDirectionType::RIGHT;
	}
	else if(enemyColumn == playerColumn)
	{
		if(enemyRow > playerRow) return CombatDirectionType::UP;
		if(enemyRow < playerRow) return CombatDirectionType::DOWN;
	}

	int rowDistance = enemyRow - playerRow;
	int columnDistance = enemyColumn - playerColumn;

	int absRowDistance = abs(rowDistance);
	int absColumnDistance = abs(columnDistance);

	if(absRowDistance > 0 && absRowDistance < absColumnDistance)
	{
		if(rowDistance > 0) return CombatDirectionType::UP;
		return CombatDirectionType::DOWN;
	}
	else if(absColumnDistance > 0 && absRowDistance > absColumnDistance)
	{
		if(columnDistance > 0) return CombatDirectionType::LEFT;
		return CombatDirectionType::RIGHT;
	}

	return enemyDirection;
}

bool CombatSystem::enemyRotationSame() const
{
	return enemyFindRotation() == enemyDirection;
}

void CombatSystem::printBattlefield() const
{
	assert(commandListener);
	assert(enemyRow < rows);
	assert(playerRow < rows);
	assert(enemyColumn < columns);
	assert(playerColumn < columns);
	assert(playerRow != enemyRow || playerColumn != enemyColumn);

	string battlefield = "";

	for(int r = 0; r < rows * cellHeight + 1; ++r)
	{
		for(int c = 0; c < columns * cellWidth + 1; ++c)
		{
			if(r % cellHeight == 0 || c % cellWidth == 0) battlefield += "X ";
			else battlefield += "  ";
		}

		battlefield += "\n";
	}

	int rowLength = columns * cellWidth * 2 + 3; // 3 -> "X \n"

	int playerPosition = playerRow * rowLength * cellHeight;
	playerPosition += rowLength * (cellHeight / 2);
	playerPosition += playerColumn * cellWidth * 2 + cellWidth;

	int enemyPosition = enemyRow * rowLength * cellHeight;
	enemyPosition += rowLength * (cellHeight / 2);
	enemyPosition += enemyColumn * cellWidth * 2 + cellWidth;

	const char* directionPlayerChar = "";
	int directionPlayerPosition = playerPosition;

	const char* directionEnemyChar = "";
	int directionEnemyPosition = enemyPosition;

	calculateDirectionCharAndPosition(playerDirection, "|", "_", rowLength, 1, directionPlayerChar, directionPlayerPosition);
	calculateDirectionCharAndPosition(enemyDirection, "|", "_", rowLength, 1, directionEnemyChar, directionEnemyPosition);

	battlefield.replace(playerPosition, 1, "P");
	battlefield.replace(directionPlayerPosition, 1, directionPlayerChar);

	battlefield.replace(enemyPosition, 1, "E");
	battlefield.replace(directionEnemyPosition, 1, directionEnemyChar);

	commandListener->printDynamic(battlefield);
}