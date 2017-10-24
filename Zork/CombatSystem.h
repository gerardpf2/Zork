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

		bool canMovePlayer(CombatDirectionType combatDirectionType) const;

		bool canMoveEnemy(CombatDirectionType combatDirectionType) const;

		void movePlayer(CombatDirectionType combatDirectionType);

		void moveEnemy(CombatDirectionType combatDirectionType);

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

		CombatDirectionType enemyFindMove() const;

		bool playerFacingEnemy() const;

		bool enemyFacingPlayer() const;

		CombatDirectionType enemyFindRotation() const;

		bool enemyRotationSame() const;

		void printBattlefield() const;

	private:

		void getRowColumnIncrement(CombatDirectionType combatDirectionType, int& rowIncrement, int& columnIncrement) const;

		CombatDirectionType getCombatDirectionType(int rowIncrement, int columnIncrement) const;

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