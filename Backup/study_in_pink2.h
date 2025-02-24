﻿/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 02.02.2023
 */

 // The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"
////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;
// addition
class Character;
class Watson;
class Sherlock;

class TestStudyInPink;

enum ItemType
{
	MAGIC_BOOK,
	ENERGY_DRINK,
	FIRST_AID,
	EXCEMPTION_CARD,
	PASSING_CARD
};
enum ElementType
{
	PATH,
	WALL,
	FAKE_WALL
};
enum RobotType
{
	C = 0,
	S,
	W,
	SW
};
// addition
enum MovingObjectType
{
	SHERLOCK,
	WATSON,
	CRIMINAL,
	ROBOT
};

class MapElement
{
	friend class TestStudyInPink;

protected:
	ElementType type;

public:
	MapElement(ElementType in_type);

	virtual ElementType getType() const;
};

class Path : public MapElement
{
	friend class TestStudyInPink;

public:
	Path();
};

class Wall : public MapElement
{
	friend class TestStudyInPink;

public:
	Wall();
};

class FakeWall : public MapElement
{
	friend class TestStudyInPink;

private:
	int req_exp;

public:
	FakeWall(int in_req_exp);
	int getReqExp() const;
	void setReqExp(int x) {
		this->req_exp = x;
	}
};

class Map
{
	friend class TestStudyInPink;

private:
	int num_rows, num_cols;
	// addition
	MapElement*** map;

public:
	Map(int num_rows, int num_cols, int num_walls, Position* array_walls, int num_fake_walls, Position* array_fake_walls);
	~Map();
	bool isValid(const Position& pos, MovingObject* mv_obj) const;
	int getNumRows() const;
	int getNumCols() const;
	ElementType getElementType(int i, int j) const;
};

class Position
{
	friend class TestStudyInPink;

private:
	int r, c;

public:
	static const Position npos;
	Position(int r = 0, int c = 0);
	Position(const string& str_pos);
	int getRow() const;
	int getCol() const;
	void setRow(int r);
	void setCol(int c);
	string str() const;
	bool isEqual(const Position& other) const {
		return (r == other.getRow() && c == other.getCol());
	}

	// Hàm isEqual thứ hai: So sánh với 2 số nguyên (hàng và cột)
	bool isEqual(int row, int col) const {
		return (r == row && c == col);
	}
};

class MovingObject
{
	friend class TestStudyInPink;

protected:
	int index;
	Position pos;
	Map* map;
	string name;

public:
	MovingObject(int index, const Position pos, Map* map, const string& name = "");

	virtual Position getNextPosition() = 0;
	Position getCurrentPosition() const;
	virtual void move() = 0;
	virtual string str() const = 0;
	// addition
	virtual MovingObjectType getObjectType() const = 0;
};

class Character : public MovingObject
{
	friend class TestStudyInPink;
protected:
	int hp;
	int exp;

public:
	Character(int index, const Position pos, Map* map, const string& name = "");
	// addition
	virtual Position getNextPosition() = 0;
	virtual void move() = 0;
	virtual string str() const = 0;
	virtual MovingObjectType getObjectType() const = 0;
	int getHP() const;
	int getEXP() const;

	void setHP(int hp);
	void setEXP(int exp);
};

class Sherlock : public Character
{
	friend class TestStudyInPink;

private:
	// TODO
	int hp, exp;
	// addition
	string moving_rule;
	int index_moving_rule;
	BaseBag* bag;

public:
	Sherlock(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp);
	Position getNextPosition();
	void move();
	string str() const;
	// addition
	MovingObjectType getObjectType() const;
	BaseBag* getBag() const;
	int getHP() const;
	int getEXP() const;
	void setHP(int hp);
	void setEXP(int exp);
	void setPos(Position pos);
	bool meet(RobotS* robotS);
	bool meet(RobotW* robotW);
	bool meet(RobotSW* robotSW);
	bool meet(RobotC* robotC);
	bool meet(Watson* watson);

};

class Watson : public Character
{
	friend class TestStudyInPink;

private:
	// TODO
	int hp, exp;
	// addition
	string moving_rule;
	int index_moving_rule;
	BaseBag* bag;

public:
	Watson(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp);
	Position getNextPosition();
	void move();
	string str() const;
	// addition
	MovingObjectType getObjectType() const;
	BaseBag* getBag() const;
	int getHP() const;
	int getEXP() const;
	void setHP(int hp);
	void setEXP(int exp);
	bool meet(RobotS* robotS);
	bool meet(RobotW* robotW);
	bool meet(RobotSW* robotSW);
	bool meet(RobotC* robotC);
	bool meet(Sherlock* sherlock);

};

class Criminal : public Character
{
	friend class TestStudyInPink;

private:
	// TODO
	Sherlock* sherlock;
	Watson* watson;
	// addition
	int count;
	Position prev_pos;
	int move_count;

public:
	Criminal(int index, const Position& init_pos, Map* map, Sherlock* sherlock, Watson* watson);
	Position getNextPosition();
	void move();
	string str() const;
	// addition

	int manhattanDistance(const Position& pos1, const Position& pos2) const;
	MovingObjectType getObjectType() const;
	int getCount() const;
	bool isCreatedRobotNext() const;
	Position getPrevPosition() const;
};

class ArrayMovingObject
{
	friend class TestStudyInPink;
	friend class StudyPinkProgram;

private:
	// TODO
	MovingObject** arr_mv_objs;
	int count;
	int capacity;

public:
	ArrayMovingObject(int capacity);

	bool isFull() const;
	bool add(MovingObject* mv_obj);
	string str() const;
	// addition
	bool checkMeet(int index);
	MovingObject* get(int index) const;
	int size() const;
	int getCount() {
		return count;
	}
	int getCapacity() {
		return capacity;
	}

};

class Configuration
{
	friend class TestStudyInPink;
	friend class StudyPinkProgram;

private:
	// TODO
	int map_num_rows;
	int map_num_cols;
	int max_num_moving_objects;
	int num_walls;
	Position* arr_walls;
	int num_fake_walls;
	Position* arr_fake_walls;
	string sherlock_moving_rule;
	Position sherlock_init_pos;
	int sherlock_init_hp;
	int sherlock_init_exp;
	string watson_moving_rule;
	Position watson_init_pos;
	int watson_init_hp;
	int watson_init_exp;
	Position criminal_init_pos;
	int num_steps;

public:
	Configuration(const string& filepath);

	string str() const;
	void xuLyMangViTri(const string& line, Position* arr, int numElements);
	void xuLyViTri(const string& line, Position& pos);
	string formatPositionArray(const Position* arr, int numElements) const;
};

// Robot, BaseItem, BaseBag,...
class Robot : public MovingObject
{
	friend class TestStudyInPink;

protected:
	RobotType robot_type;
	BaseItem* item;
	Criminal* criminal;
	ItemType duong;



public:
	Robot(int index,
		const Position& pos,
		Map* map,
		Criminal* criminal,
		const string& name = "");
	MovingObjectType getObjectType() const;
	virtual Position getNextPosition() = 0;
	virtual void move() = 0;
	virtual string str() const = 0;
	virtual RobotType getType();
	// addition
	static Robot* create(int index, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson);
	virtual int getDistance() const = 0;
	BaseItem* NewItem();

	friend class Sherlock;
	friend class PassingCard;
	friend class Map;
	RobotType getRobotType();
	void setCriminal(Criminal* criminal) { this->criminal = criminal; }
};

class RobotC : public Robot
{
	friend class TestStudyInPink;

private:
	Position nextPosition;
public:
	RobotC(int index,
		const Position& init_pos,
		Map* map,
		Criminal* criminal);
	Position getNextPosition();
	void move();
	int getDistance(Sherlock* sherlock);
	int getDistance(Watson* watson);
	string str() const;
	// addition
	RobotType getType() const;
	int getDistance() const override;
};

class RobotS : public Robot
{
	friend class TestStudyInPink;

private:
	Sherlock* sherlock;

public:
	RobotS(int index,
		const Position& init_pos,
		Map* map,
		Criminal* criminal,
		Sherlock* sherlock);

	Position getNextPosition();
	void move();
	int getDistance() const;
	string str() const;
	// addition
	RobotType getType() const;
};

class RobotW : public Robot
{
	friend class TestStudyInPink;

private:
	Watson* watson;

public:
	RobotW(int index,
		const Position& init_pos,
		Map* map,
		Criminal* criminal,
		Watson* watson);
	Position getNextPosition();
	void move();
	int getDistance() const;
	string str() const;
	// addition
	RobotType getType() const;
};

class RobotSW : public Robot
{
	friend class TestStudyInPink;

private:
	Sherlock* sherlock;
	Watson* watson;

public:
	RobotSW(int index,
		const Position& init_pos,
		Map* map,
		Criminal* criminal,
		Sherlock* sherlock,
		Watson* watson);

	Position getNextPosition();
	string str() const;
	int getDistance() const;
	void move();
	// addition
	RobotType getType() const;
};

class BaseItem
{
	friend class TestStudyInPink;

public:
	virtual bool canUse(Character* obj, Robot* robot) = 0;
	virtual void use(Character* obj, Robot* robot) = 0;
	// addition
	BaseItem();
	virtual ItemType getType() const = 0;
	virtual string str() const = 0;

};

class MagicBook : public BaseItem
{
	friend class TestStudyInPink;

public:
	bool canUse(Character* obj, Robot* robot);
	void use(Character* obj, Robot* robot);
	// addition
	ItemType getType() const;
	string str() const;
};

class EnergyDrink : public BaseItem
{
	friend class TestStudyInPink;

public:
	bool canUse(Character* obj, Robot* robot);
	void use(Character* obj, Robot* robot);
	// addition
	ItemType getType() const;
	string str() const;
};

class FirstAid : public BaseItem
{
	friend class TestStudyInPink;

public:
	bool canUse(Character* obj, Robot* robot);
	void use(Character* obj, Robot* robot);
	// addition
	ItemType getType() const;
	string str() const;
};

class ExcemptionCard : public BaseItem
{
	friend class TestStudyInPink;

public:
	bool canUse(Character* obj, Robot* robot);
	void use(Character* obj, Robot* robot);
	// addition
	ItemType getType() const;
	string str() const;
};

class PassingCard : public BaseItem
{
	friend class TestStudyInPink;

private:
	string challenge;

public:
	PassingCard(int i, int j);
	PassingCard(string challenge);
	bool canUse(Character* obj, Robot* robot);
	void use(Character* obj, Robot* robot);
	// addition
	ItemType getType() const;
	string str() const;
	string getChallenge() {
		return challenge;
	}
};

class BaseBag
{
	friend class TestStudyInPink;

protected:
	// addition
	struct Node {
		BaseItem* item;
		Node* next;

		// Constructor cho Node
		Node(BaseItem* item, Node* next = nullptr) : item(item), next(next) {}
	};


protected:
	Character* obj;
	// addition
	int size;
	int capacity;
	int count;
	Node* head;

public:
	virtual bool insert(BaseItem* item);
	virtual BaseItem* get();
	virtual BaseItem* get(ItemType itemType);
	virtual string str() const;

	// addition
	BaseBag(int capacity);
	virtual ~BaseBag()=0;
	bool checkItem(ItemType itemType);
	bool isFull() const;
};
// addition
class SherlockBag : public BaseBag
{
	friend class TestStudyInPink;

private:
	Sherlock* sherlock;

public:
	SherlockBag(Sherlock* character);
	BaseItem* get();
};
// addition
class WatsonBag : public BaseBag
{
	friend class TestStudyInPink;

private:
	Watson* watson;

public:
	WatsonBag(Watson* character);
	BaseItem* get();
};

class StudyPinkProgram
{
	friend class TestStudyInPink;

private:
	// Sample attributes
	Configuration* config;
	Sherlock* sherlock;
	Watson* watson;
	Criminal* criminal;
	Map* map;
	ArrayMovingObject* arr_mv_objs;
	// addition
	string outputFile;
	bool stopChecker;

public:
	StudyPinkProgram(const string& config_file_path)
	{
		config = new Configuration(config_file_path);
		map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
		arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
		sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
		watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
		criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);

		// Thêm criminal, sherlock, watson vào arr_mv_objs
		arr_mv_objs->add(criminal);
		arr_mv_objs->add(sherlock);
		arr_mv_objs->add(watson);


	}
	bool isStop() const
	{
		return sherlock->getHP() <= 1 ||
			watson->getHP() <= 1 ||
			sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()) ||
			watson->getCurrentPosition().isEqual(criminal->getCurrentPosition());
	}
	void printResult() const {
		if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
			cout << "Sherlock caught the criminal" << endl;
		}
		else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
			cout << "Watson caught the criminal" << endl;
		}
		else {
			cout << "The criminal escaped" << endl;
		}
	}

	void printStep(int si) const {
		cout << "Step: " << setw(4) << setfill('0') << si
			<< "--"
			<< sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
	}

	// Note: This is a sample code. You can change the implementation as you like.
			// TODO
	void run(bool verbose) {
		for (int istep = 0; istep < config->num_steps; ++istep) {
			for (int i = 0; i < arr_mv_objs->size(); ++i) {
				arr_mv_objs->get(i)->move();
				arr_mv_objs->checkMeet(i);
				MovingObject* robot = nullptr;
				if (arr_mv_objs->get(i)->getObjectType() == MovingObjectType::CRIMINAL)
				{
					robot = Robot::create(arr_mv_objs->size(), map, criminal, sherlock, watson);
				}
				if (isStop()) {
					printStep(istep);
					break;
				}
				if (verbose) {
					printStep(istep);

				}
				if (robot != nullptr)
				{
					if (criminal != nullptr) {
						if (criminal->isCreatedRobotNext()) {
							arr_mv_objs->add(robot);
						}
					}
				}
			}

		}
		printResult();
	}

	// addition

	~StudyPinkProgram()
	{

	}
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
