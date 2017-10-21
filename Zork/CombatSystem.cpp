#include "CombatSystem.h"

#include <assert.h>
#include "CommandListener.h"

CombatSystem::CombatSystem(/* Player* player, Enemy* enemy, */ int rows, int columns, int playerRow, int playerColumn, CombatDirectionType playerDirection, int enemyRow, int enemyColumn, CombatDirectionType enemyDirection, int cellWidth, int cellHeight) :
	/* player(player), enemy(enemy), */ rows(rows), columns(columns), playerRow(playerRow), playerColumn(playerColumn), playerDirection(playerDirection), enemyRow(enemyRow), enemyColumn(enemyColumn), enemyDirection(enemyDirection), cellWidth(cellWidth), cellHeight(cellHeight)
{
	/* assert(enemy);
	assert(player); */
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
	return abs(rowIncrement) + abs(columnIncrement) == 1 && (playerRow + rowIncrement != enemyRow || playerColumn + columnIncrement != enemyColumn) && playerRow + rowIncrement >= 0 && playerRow + rowIncrement < rows && playerColumn + columnIncrement >= 0 && playerColumn + columnIncrement < columns;
}

bool CombatSystem::canMoveEnemy(int rowIncrement, int columnIncrement) const
{
	return abs(rowIncrement) + abs(columnIncrement) == 1 && (enemyRow + rowIncrement != playerRow || enemyColumn + columnIncrement != playerColumn) && enemyRow + rowIncrement >= 0 && enemyRow + rowIncrement < rows && enemyColumn + columnIncrement >= 0 && enemyColumn + columnIncrement < columns;
}

void CombatSystem::movePlayer(int rowIncrement, int columnIncrement)
{
	assert(abs(rowIncrement) + abs(columnIncrement) == 1);
	assert(playerRow + rowIncrement != enemyRow || playerColumn + columnIncrement != enemyColumn);
	assert(playerRow + rowIncrement >= 0 && playerRow + rowIncrement < rows);
	assert(playerColumn + columnIncrement >= 0 && playerColumn + columnIncrement < columns);

	playerRow += rowIncrement;
	playerColumn += columnIncrement;

	printBattlefield();
}

void CombatSystem::moveEnemy(int rowIncrement, int columnIncrement)
{
	assert(abs(rowIncrement) + abs(columnIncrement) == 1);
	assert(enemyRow + rowIncrement != playerRow || enemyColumn + columnIncrement != playerColumn);
	assert(enemyRow + rowIncrement >= 0 && enemyRow + rowIncrement < rows);
	assert(enemyColumn + columnIncrement >= 0 && enemyColumn + columnIncrement < columns);

	enemyRow += rowIncrement;
	enemyColumn += columnIncrement;

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

void CombatSystem::update(clock_t msDeltaTime)
{
	// system("CLS");
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