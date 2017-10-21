#ifndef _CombatSystem_
#define _CombatSystem_

#include <time.h>

/* class Enemy;
class Player; */

enum class CombatDirectionType
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class CommandListener;

class CombatSystem
{
	public:

		CombatSystem(/* Player* player, Enemy* enemy, */ int rows, int columns, int playerRow, int playerColumn, CombatDirectionType playerDirection, int enemyRow, int enemyColumn, CombatDirectionType enemyDirection, int cellWidth = 4, int cellHeight = 4);

		~CombatSystem();

		void setCommandListener(CommandListener* commandListener);

		bool canMovePlayer(int rowIncrement, int columnIncrement) const;

		bool canMoveEnemy(int rowIncrement, int columnIncrement) const;

		void movePlayer(int rowIncrement, int columnIncrement);

		void moveEnemy(int rowIncrement, int columnIncrement);

		bool canRotatePlayer(CombatDirectionType playerDirection) const;

		bool canRotateEnemy(CombatDirectionType enemyDirection) const;

		void rotatePlayer(CombatDirectionType playerDirection);

		void rotateEnemy(CombatDirectionType enemyDirection);

		void update(clock_t msDeltaTime);

	private:

		void printBattlefield() const;

	private:

		/* Player* player;

		Enemy* enemy; */

		int playerRow = 2;

		int playerColumn = 1;

		CombatDirectionType playerDirection = CombatDirectionType::UP;

		int enemyRow = 0;

		int enemyColumn = 1;

		CombatDirectionType enemyDirection = CombatDirectionType::DOWN;

		int rows = 3;

		int columns = 3;

		int cellWidth = 4;

		int cellHeight = 4;

		CommandListener* commandListener = nullptr;
};

#endif