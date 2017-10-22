#ifndef _CombatSystem_
#define _CombatSystem_

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

		CombatSystem(int rows, int columns, int playerRow, int playerColumn, CombatDirectionType playerDirection, int enemyRow, int enemyColumn, CombatDirectionType enemyDirection, int cellWidth, int cellHeight);

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

		bool playerAttackCanHit() const;

		bool enemyAttackCanHit() const;

		bool playerProjectileCanHit() const;

		bool playerMissAttack() const;

		bool enemyMissAttack() const;

		bool playerMissProjectile() const;

		void enemyFindMove(int& rowIncrement, int& columnIncrement) const;

		bool playerFacingEnemy() const;

		bool enemyFacingPlayer() const;

		CombatDirectionType enemyFindRotation() const;

		bool enemyRotationSame() const;

		void printBattlefield() const;

	private:

		int playerRow = -1;

		int playerColumn = -1;

		CombatDirectionType playerDirection = CombatDirectionType::UP;

		int enemyRow = -1;

		int enemyColumn = -1;

		CombatDirectionType enemyDirection = CombatDirectionType::UP;

		int rows = -1;

		int columns = -1;

		int cellWidth = -1;

		int cellHeight = -1;

		CommandListener* commandListener = nullptr;
};

#endif