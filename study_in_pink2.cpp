// Map xét điều kiện col row = 0 tránh cấp phát lỗi
// getCount của BaseBag theo test của thầy là trả về chuỗi "Bag[count="+<size>+";]"


// TODO:
// Chỉnh lại di chuyển của RobotC (gợi ý: thực hiện hàm getPrevPosition cho Criminal)
// Mô tả về các meet thay đổi (đã được confirm 90%)
// File study_in_pink2.h những phần trước "addition" là gốc của đề (không thay đổi)
// Chỉnh tên thuộc tính hp và exp của Sherlock và Watson
// Position có nạp chồng 2 hàm isEqual
// isStop kiểm tra vị trí Sherlock, Watson với Criminal và hp của Sherlock, Watson
// Hàm run chú ý chỉnh từ hàm run() gốc (vị trí gọi printResult và printStep)
// Hàm move của Sherlock và Watson khi exp == 0 sẽ không thực hiện gì
// NOTE:
// chú ý các phần addition nên sửa đổi để tránh đạo code
// nộp Bkel cần xóa đổi lại 2 hàm printResult và printStep gốc, xóa thuộc tính outputFile
#include "study_in_pink2.h"

string thuThach(Position a) {
	string challenge;
	int t = (a.getRow() * 11 + a.getCol()) % 4;
	if (t == 0) {
		challenge = "RobotS";
	}
	else if (t == 1) {
		challenge = "RobotC";
	}
	else if (t == 2) {
		challenge = "RobotSW";
	}
	else if (t == 3) {
		challenge = "all";
	}
	return challenge;
}
int soChuDao(int n) {
	while (n >= 10) {
		int sum = 0;
		while (n > 0) {
			sum += n % 10;
			n /= 10;
		}
		n = sum;
	}
	return n;
}
int demChuoi(string chuoi) {// dem tu dau bang ve sau
	int c = 0;
	for (int i = 0; i < chuoi.length(); i++) {
		if (chuoi[i] == '=') {
			for (int a = i; a < chuoi.length(); a++) {
				c++;
			}
		}
	}
	return c - 1;
}
int countElements(const string& line)
{
	int count = 0;
	size_t pos = 0;
	while ((pos = line.find(",", pos)) != string::npos)
	{
		count++;
		pos++;
	}
	return count; // Số lượng phần tử là số lần phân tách bằng dấu phẩy 
}


const Position Position::npos = Position(-1, -1);
/*
 * CLASS: MapElement
 */
MapElement::MapElement(ElementType in_type) : type(in_type)
{
	// TODO: constructor
}



ElementType MapElement::getType() const
{
	// TODO: get
	return type;
}
/*
 * CLASS: Path
 */
Path::Path()
	: MapElement(PATH) {}
/*
 * CLASS: Wallb
 */
Wall::Wall()
	: MapElement(WALL) {}
/*
 * CLASS: FakeWall
 */
FakeWall::FakeWall(int in_req_exp)
	: MapElement(ElementType::FAKE_WALL)
{
	this->req_exp = in_req_exp;
	// TODO: constructor
}
int FakeWall::getReqExp() const
{
	// TODO: get
	return req_exp;
}
/*
 * CLASS: Position
 */

Position::Position(int r, int c)
{
	this->r = r;
	this->c = c;
	// TODO: constructor
}
Position::Position(const string& str_pos)
{
	// TODO: constructor

	string a = str_pos.substr(str_pos.find("(") + 1, str_pos.find(",") - str_pos.find("(") - 1); //trích xuất hàng
	string b = str_pos.substr(str_pos.find(",") + 1, str_pos.find(")") - str_pos.find(",") - 1); //trích xuất cột
	int numRow = stoi(a);
	int numCol = stoi(b);
	this->r = numRow;
	this->c = numCol;
}
int Position::getRow() const
{
	// TODO: get
	return r;
}
int Position::getCol() const
{
	// TODO: get
	return c;
}
void Position::setRow(int r)
{
	// TODO: set
	this->r = r;
}
void Position::setCol(int c)
{
	// TODO: set
	this->c = c;
}
string Position::str() const
{
	// TODO: trả về chuỗi "(<r>,<c>)"
	char target[100];
	string r1 = to_string(r);
	string c1 = to_string(c);
	sprintf(target, "%s%s%s%s%s", "(", r1.c_str(), ",", c1.c_str(), ")");
	return string(target);
}



/*
 * CLASS: MovingObject
 */
MovingObject::MovingObject(int index, const Position pos, Map* map, const string& name)
	:index(index), pos(pos), map(map), name(name)
{
	// TODO: constructor

}
Position MovingObject::getCurrentPosition() const
{
	// TODO: get
	return pos;
}
/*
 * CLASS: Character kế thừa class MovingObject
 */
Character::Character(int index, const Position pos, Map* map, const string& name)
	: MovingObject(index, pos, map, name)
	// TODO: constructor class cha

{
	this->hp = hp;
	this->exp = exp;
	// TODO: constructor
}
int Character::getHP() const {
	return hp;
}

int Character::getEXP() const {
	return exp;
}

void Character::setHP(int hp) {
	hp = hp;
}

void Character::setEXP(int exp) {
	exp = exp;
}

/*
 * CLASS: Sherlock kế thừa class Character
 */

Sherlock::Sherlock(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp)
	: Character(index, init_pos, map, "Sherlock"),
	moving_rule(moving_rule),
	hp(init_hp),
	exp(init_exp),
	index_moving_rule(0)
{
	bag = new SherlockBag(this);
}

Position Sherlock::getNextPosition() {
	if (exp > 900) {
		setEXP(900);
	}
	else if (exp < 0) {
		setEXP(0);
	}

	if (exp == 0 || hp == 0) {
		return pos;
	}
	char huong = moving_rule[index_moving_rule];
	index_moving_rule = (index_moving_rule + 1) % moving_rule.length();

	int hangTiepTheo = pos.getRow();
	int cotTiepTheo = pos.getCol();

	switch (huong) {
	case 'U':
		hangTiepTheo--;
		break;
	case 'L':
		cotTiepTheo--;
		break;
	case 'D':
		hangTiepTheo++;
		break;
	case 'R':
		cotTiepTheo++;
		break;
	}

	Position viTriTiepTheo(hangTiepTheo, cotTiepTheo);

	if (map->isValid(viTriTiepTheo, this)) {
		return viTriTiepTheo;
	}
	else {
		return Position::npos; // Trả về npos nếu vị trí không hợp lệ
	}
}

void Sherlock::move() {
	Position viTriTiepTheo = getNextPosition();
	if (map->isValid(viTriTiepTheo, this)) {
		pos = viTriTiepTheo;
	}
}


string Sherlock::str() const {
	return "Sherlock[index=" + to_string(index) +
		";pos=" + pos.str() +
		";moving_rule=" + moving_rule + "]";
}

MovingObjectType Sherlock::getObjectType() const {
	return SHERLOCK;
}

int Sherlock::getHP() const {
	return hp;
}

int Sherlock::getEXP() const {
	return exp;
}

void Sherlock::setHP(int hp) {
	hp = max(0, min(hp, 500)); // Giới hạn hp trong khoảng 0-500
}

void Sherlock::setEXP(int exp) {
	exp = max(0, min(exp, 900)); // Giới hạn exp trong khoảng 0-900 
}
/*
 * CLASS: Watson kế thừa class Character
 */


 /*
  * CLASS: Watson kế thừa class Character
  */

Watson::Watson(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp)
	: Character(index, init_pos, map, "Watson"),
	moving_rule(moving_rule),
	hp(init_hp),
	exp(init_exp),
	index_moving_rule(0)
{
	bag = new WatsonBag(this);
}


Position Watson::getNextPosition() {

	if (exp > 900) {
		setEXP(900);
	}
	else if (exp < 0) {
		setEXP(0);
	}

	if (exp == 0 || hp == 0) {
		return pos;
	}
	char huong = moving_rule[index_moving_rule];
	index_moving_rule = (index_moving_rule + 1) % moving_rule.length();

	int hangTiepTheo = pos.getRow();
	int cotTiepTheo = pos.getCol();

	switch (huong) {
	case 'U':
		hangTiepTheo--;
		break;
	case 'L':
		cotTiepTheo--;
		break;
	case 'D':
		hangTiepTheo++;
		break;
	case 'R':
		cotTiepTheo++;
		break;
	}

	Position viTriTiepTheo(hangTiepTheo, cotTiepTheo);

	if (map->isValid(viTriTiepTheo, this)) {
		return viTriTiepTheo;
	}
	else {
		return Position::npos; // Trả về npos nếu vị trí không hợp lệ
	}
}

void Watson::move() {
	Position nextPos = getNextPosition();
	if (map->isValid(nextPos, this)) {
		pos = nextPos;
	}
}

string Watson::str() const {
	return "Watson[index=" + to_string(index) +
		";pos=" + pos.str() +
		";moving_rule=" + moving_rule + "]";
}

MovingObjectType Watson::getObjectType() const {
	return WATSON;
}

int Watson::getHP() const {
	return hp;
}

int Watson::getEXP() const {
	return exp;
}

void Watson::setHP(int hp) {
	hp = max(0, min(hp, 500));
}

void Watson::setEXP(int exp) {
	exp = max(0, min(exp, 900));
}
/*
 * CLASS: Map
 */
int reqExp;
Map::Map(int num_rows, int num_cols, int num_walls, Position* array_walls, int num_fake_walls, Position* array_fake_walls)
{
	// TODO: constructor
	if (num_cols == 0 || num_rows == 0) {
		return;
	}

	this->num_rows = num_rows;
	this->num_cols = num_cols;

	// Tạo map
	map = new MapElement * *[num_rows];
	for (int i = 0; i < num_rows; i++) {
		map[i] = new MapElement * [num_cols];
		for (int j = 0; j < num_cols; j++) {
			map[i][j] = new Path();
		}
	}


	// Đặt Fake_wall trên Map
	for (int i = 0; i < num_fake_walls; i++) {
		int fake_wall_row = array_fake_walls[i].getRow();
		int fake_wall_col = array_fake_walls[i].getCol();
		if (fake_wall_row >= 0 && fake_wall_row < num_rows && fake_wall_col >= 0 && fake_wall_col < num_cols) {
			delete map[fake_wall_row][fake_wall_col]; // xóa phần map để ghi đè
			int req_exp = (fake_wall_row * 257 + fake_wall_col * 139 + 89) % 900 + 1;
			reqExp = req_exp;
			map[fake_wall_row][fake_wall_col] = new FakeWall(req_exp);

		}
	}
	// Đặt walls trên map
	for (int i = 0; i < num_walls; i++) {
		int wall_row = array_walls[i].getRow();
		int wall_col = array_walls[i].getCol();
		if (wall_row >= 0 && wall_row < num_rows && wall_col >= 0 && wall_col < num_cols) {
			delete map[wall_row][wall_col]; //Xóa map để ghi đè
			map[wall_row][wall_col] = new Wall();
		}
	}

}
Map::~Map()
{
	// TODO: destructor
	if (num_rows == 0 || num_cols == 0)
		return;
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			delete map[i][j];
		}
		delete[] map[i];
	}
	delete[] map;
}

int Map::getNumRows() const
{
	// TODO: get
	return num_rows;
}
int Map::getNumCols() const
{
	// TODO: get
	return num_cols;
}
ElementType Map::getElementType(int i, int j) const
{
	// TODO: get
	if (i >= 0 && i < num_rows && j >= 0 && j < num_cols) {
		return map[i][j]->getType();
	}
	return PATH;
}
bool Map::isValid(const Position& pos, MovingObject* mv_obj) const {
	int i = pos.getRow();
	int j = pos.getCol();

	// Kiểm tra giới hạn bản đồ
	if (i < 0 || i >= num_rows || j < 0 || j >= num_cols) {
		return false;
	}

	ElementType type = map[pos.getRow()][pos.getCol()]->getType();

	if (type == PATH) {
		return true;
	}
	// Tất cả đối tượng đều không thể vượt qua WALL
	if (type == WALL) {
		return false;
	}


	// Sherlock, Criminal và Robot có thể vượt qua FakeWall
	if ((mv_obj->getObjectType() == SHERLOCK || mv_obj->getObjectType() == ROBOT || mv_obj->getObjectType() == CRIMINAL) && type == FAKE_WALL) {
		return true;
	}

	// Watson cần đủ exp để vượt qua FakeWall

	if (mv_obj->getObjectType() == WATSON && type == FAKE_WALL) {
		// Ép kiểu con trỏ MapElement về FakeWall*
		FakeWall* fakeWall = dynamic_cast<FakeWall*>(map[pos.getRow()][pos.getCol()]);

		// Kiểm tra con trỏ fakeWall có hợp lệ không trước khi truy cập req_exp
		if (fakeWall != nullptr) {
			if (dynamic_cast<Watson*>(mv_obj)->getEXP() > fakeWall->getReqExp()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			// Xử lý lỗi khi ép kiểu không thành công (không phải FakeWall)
			return false;
		}
	}

	// Robot, Sherlock, Watson, Criminal có thể đi lên nhau (và các vị trí PATH)


	return false;
}

/*
 * CLASS: Criminal kế thừa class Character
 */
Criminal::Criminal(int index, const Position& init_pos, Map* map, Sherlock* sherlock, Watson* watson)
	: Character(index, init_pos, map, "Criminal"),
	sherlock(sherlock),
	watson(watson),
	move_count(0),
	count(0)
	
{ // Khởi tạo move_count trong constructor
	// ... 
	this->prev_pos = Position::npos;
}
int Criminal::manhattanDistance(const Position& pos1, const Position& pos2) const {
	int n = abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
	return n;
}
int pointDistance(const Position& pos1, const Position& pos2) {
	int n = abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
	return n;
}

// Hàm getNextPosition của Criminal
Position oldPos;
Position Criminal::getNextPosition() {

	Position sherPos = sherlock->getCurrentPosition();
	Position watPos = watson->getCurrentPosition();
	oldPos = pos;
	int maxDistance = -1;
	Position bestPos = Position::npos;
	int bestDirection = -1; // Biến đại diện cho hướng di chuyển (0: U, 1: L, 2: D, 3: R)

	// Xác định các hướng di chuyển
	Position up(pos.getRow() - 1, pos.getCol());
	Position left(pos.getRow(), pos.getCol() - 1);
	Position down(pos.getRow() + 1, pos.getCol());
	Position right(pos.getRow(), pos.getCol() + 1);

	// Kiểm tra hướng 'U'
	if (map->isValid(up, this)) {
		int distance = manhattanDistance(up, sherPos) + manhattanDistance(up, watPos);
		if (distance > maxDistance) {
			maxDistance = distance;
			bestPos = up;
			bestDirection = 0;
		}
	}

	// Kiểm tra hướng 'L'
	if (map->isValid(left, this)) {
		int distance = manhattanDistance(left, sherPos) + manhattanDistance(left, watPos);
		if (distance > maxDistance) {
			maxDistance = distance;
			bestPos = left;
			bestDirection = 1;
		}
		else if (distance == maxDistance && bestDirection > 1) { // 'L' chỉ được ưu tiên nếu 'U' không được chọn
			bestPos = left;
			bestDirection = 1;
		}
	}

	// Kiểm tra hướng 'D'
	if (map->isValid(down, this)) {
		int distance = manhattanDistance(down, sherPos) + manhattanDistance(down, watPos);
		if (distance > maxDistance) {
			maxDistance = distance;
			bestPos = down;
			bestDirection = 2;
		}
		else if (distance == maxDistance && bestDirection > 2) { // 'D' chỉ được ưu tiên nếu 'U' và 'L' không được chọn
			bestPos = down;
			bestDirection = 2;
		}
	}

	// Kiểm tra hướng 'R'
	if (map->isValid(right, this)) {
		int distance = manhattanDistance(right, sherPos) + manhattanDistance(right, watPos);
		if (distance > maxDistance) {
			maxDistance = distance;
			bestPos = right;
			bestDirection = 3;
		}
	}
	return bestPos;
}
Position Criminal::getPrevPosition() const {

	return prev_pos;
}
void Criminal::move()
{
	prev_pos = pos;
	// TODO: di chuyển đến vị trí tiếp theo và cập nhật nước đi tiếp theo
	Position nextPos = getNextPosition();
	if (nextPos.getCol() != Position::npos.getCol()) {
		pos = nextPos;
		move_count++;
	}
	this->count = move_count;
}
bool Criminal::isCreatedRobotNext() const {
	return getCount() % 3 == 0; // Kiểm tra xem bước tiếp theo có tạo robot hay không
}

string Criminal::str() const
{
	// TODO: trả về chuỗi "Watson[index=<index>;pos=<pos>]"
	return "Criminal[index=" + to_string(index) + ";pos=(" + to_string(pos.getRow()) + "," + to_string(pos.getCol()) + ")]";
}

MovingObjectType Criminal::getObjectType() const
{
	// TODO: get
	return CRIMINAL;
}
int Criminal::getCount() const
{
	// TODO: get
	return count;
}

/*
 * CLASS: Robot kế thừa class MovingObject
 */
Robot::Robot(int index, const Position& pos, Map* map, Criminal* criminal, const string& name)
	: MovingObject(index, pos, map, name),
	criminal(criminal),
	robot_type(robot_type) // Khởi tạo robot_type
{

	int i = pos.getRow();
	int j = pos.getCol();
	int p = i * j;
	int s = soChuDao(p); // Giả sử bạn đã có hàm soChuDao()
	if (s >= 0 && s <= 1) {
		duong = MAGIC_BOOK;
		item = new MagicBook;
	}
	else if (s >= 2 && s <= 3) {
		duong = ENERGY_DRINK;
		item = new EnergyDrink;
	}
	else if (s >= 4 && s <= 5) {
		duong = FIRST_AID;
		item = new FirstAid;
	}
	else if (s >= 6 && s <= 7) {
		duong = EXCEMPTION_CARD;
		item = new ExcemptionCard;
	}
	else { // s >= 8 && s <= 9
		duong = PASSING_CARD;
		item = new PassingCard(pos.getRow(), pos.getCol());
	}
	// Constructor of the base class MovingObject is called.
	// _type and criminal attributes are initialized. 
}

Robot* Robot::create(int index, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson) {
	Position pos = criminal->getCurrentPosition();
	int count = criminal->getCount();

	if (count % 3 == 0 && count < 4) {
		return new RobotC(index, pos, map, criminal);
	}
	else {
		// Tính khoảng cách đến Sherlock và Watson
		int distS = abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
		int distW = abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());

		if (distS < distW) {
			return new RobotS(index, pos, map, criminal, sherlock);
		}
		else if (distW < distS) {
			return new RobotW(index, pos, map, criminal, watson);
		}
		else {
			return new RobotSW(index, pos, map, criminal, sherlock, watson);
		}
	}
}
MovingObjectType Robot::getObjectType() const
{
	// TODO: get
	return ROBOT;
}
/*
 *CLASS: RobotC kế thừa class Robot
 */
RobotC::RobotC(int index, const Position& init_pos, Map* map, Criminal* criminal)
	: Robot(index, init_pos, map, criminal, "RobotC"),
	nextPosition(criminal->getNextPosition()) {
	this->robot_type = C;

}

int RobotC::getDistance(Sherlock* sherlock) {
	return pointDistance(pos, sherlock->getCurrentPosition());
}

int RobotC::getDistance(Watson* watson) {
	return pointDistance(pos, watson->getCurrentPosition());
}

Position RobotC::getNextPosition() {
	// Lấy vị trí trước đó của Criminal
	Position prevPos = criminal->getPrevPosition();

	// Kiểm tra xem vị trí trước đó có hợp lệ hay không
	if (map->isValid(prevPos, this)) {
		return prevPos; // Trả về vị trí trước đó nếu hợp lệ
	}

	// Nếu vị trí trước đó không hợp lệ, trả về npos
	return Position::npos;
}
void RobotC::move() {
	// Cập nhật nextPosition bằng vị trí trước đó của Criminal trước khi di chuyển
	pos = criminal->getPrevPosition();
}

string RobotC::str() const {
	return "Robot[pos=(" + to_string(pos.getRow()) + "," + to_string(pos.getCol()) + ");type=C;dist=]";
}

int RobotC::getDistance() const {
	// Not used for RobotC as it has separate methods for Sherlock and Watson
	return 0;
}

RobotType RobotC::getType() const {
	return C;
}
/*
 * CLASS: RobotW kế thừa class Robot
 */

RobotW::RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal, Watson* watson)
	: Robot(index, init_pos, map, criminal)
{
	// TODO: constructor implementation for RobotW
	this->watson = watson;
	this->robot_type = W;
	// Additional initialization or code
}

Position RobotW::getNextPosition() {
	Position watsonNextPos = watson->getCurrentPosition(); // Lấy vị trí tiếp theo của Watson
	int minDistance = 99999;
	Position nearestPos = Position::npos;

	// Xác định các hướng di chuyển tiềm năng (Lên, Phải, Xuống, Trái)
	Position directions[] = {
		Position(-1, 0),//Lên
		Position(0, 1),//Phải
		Position(1, 0),//Xuống
		Position(0, -1)//Trái
	};

	// Khám phá các vị trí có thể xung quanh RobotW
	for (const Position& dir : directions) {
		Position potentialPos(pos.getRow() + dir.getRow(), pos.getCol() + dir.getCol());
		if (map->isValid(potentialPos, this)) {
			int distance = pointDistance(potentialPos, watsonNextPos);
			if (distance < minDistance) {
				minDistance = distance;
				nearestPos = potentialPos;
			}
		}
	}

	return nearestPos;
}

void RobotW::move()
{
	// TODO: di chuyển về phía Watson
	Position nextPos = getNextPosition();
	if (nextPos.getCol() != Position::npos.getCol()) {
		pos = nextPos;
	}
}

string RobotW::str() const
{
	// TODO: trả về chuỗi "Robot[pos=<pos>;type=W;dist=<distance>]"
	return "Robot[pos=(" + to_string(pos.getRow()) + "," + to_string(pos.getCol()) + ");type=W;dist=" + to_string(getDistance()) + "]";
}

RobotType RobotW::getType() const
{
	// TODO: get
	return robot_type;
}

int RobotW::getDistance() const {
	Position watsonPos = watson->getCurrentPosition();
	return pointDistance(pos, watsonPos);
}
/*
 * CLASS: RobotS kế thừa class Robot
 */
RobotS::RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock)
	: Robot(index, init_pos, map, criminal)
	// TODO: constructor class cha
{
	// TODO: constructor
	this->sherlock = sherlock;
	this->robot_type = S;
}

Position RobotS::getNextPosition()
{
	// TODO: tìm vị trí tiếp theo gần Sherlock nhất
	Position sherlockNextPos = sherlock->getCurrentPosition(); // Lấy vị trí tiếp theo của Watson
	int minDistance = 99999;
	Position nearestPos = Position::npos;

	// Xác định các hướng di chuyển tiềm năng (Lên, Phải, Xuống, Trái)
	Position directions[] = {
		Position(-1, 0),//Lên
		Position(0, 1),//Phải
		Position(1, 0),//Xuống
		Position(0, -1)//Trái
	};

	// Khám phá các vị trí có thể xung quanh RobotW
	for (const Position& dir : directions) {
		Position potentialPos(pos.getRow() + dir.getRow(), pos.getCol() + dir.getCol());
		if (map->isValid(potentialPos, this)) {
			int distance = pointDistance(potentialPos, sherlockNextPos);
			if (distance < minDistance) {
				minDistance = distance;
				nearestPos = potentialPos;
			}
		}
	}

	return nearestPos;
}
void RobotS::move()
{

	// TODO: di chuyển về phía Sherlock
	Position nextPos = getNextPosition();
	if (nextPos.getCol() != Position::npos.getCol()) {
		pos = nextPos;
	}
}

string RobotS::str() const
{
	// TODO: trả về chuỗi "Robot[pos=<pos>;type=S;dist=<distance>]"
	return "Robot[pos=(" + to_string(pos.getRow()) + "," + to_string(pos.getCol()) + ");type=S;dist=" + to_string(getDistance()) + "]";


}

RobotType RobotS::getType() const
{
	// TODO: get
	return robot_type;
}

int RobotS::getDistance() const
{
	// TODO: get
	Position sherlockPos = sherlock->getCurrentPosition();
	return pointDistance(pos, sherlockPos);
}
/*
 * CLASS: RobotSW kế thừa class Robot
 */
RobotSW::RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson)
	: Robot(index, init_pos, map, criminal)
	// TODO: constructor class cha

{
	// TODO: constructor
	this->sherlock = sherlock;
	this->watson = watson;
	this->robot_type = SW;
}

// TODO implement các phương thức getNextPosition, move, str, getType, getDistance
Position RobotSW::getNextPosition() {
	Position sherlockPos = sherlock->getCurrentPosition();
	Position watsonPos = watson->getCurrentPosition();
	int minTotalDist = 99999;
	Position nearestPos = Position::npos;

	// Xác định các hướng di chuyển tiềm năng (2 đơn vị)
	Position directions[] = {
		Position(-2, 0),  // Lên 2
		Position(-1, 1),   // Lên 1, Phải 1
		Position(0, 2),   // Phải 2
		Position(1, 1),   // Xuống 1, Phải 1
		Position(2, 0),   // Xuống 2
		Position(1, -1),  // Xuống 1, Trái 1
		Position(0, -2),  // Trái 2
		Position(-1, -1), // Lên 1, Trái 1
	};

	// Duyệt qua các hướng di chuyển tiềm năng
	for (const Position& dir : directions) {
		Position potentialPos(pos.getRow() + dir.getRow(), pos.getCol() + dir.getCol());

		// Kiểm tra vị trí hợp lệ và khoảng cách Manhattan từ vị trí ban đầu là 2
		if (map->isValid(potentialPos, this) &&
			pointDistance(pos, potentialPos) == 2) {

			int distToS = pointDistance(potentialPos, sherlockPos);
			int distToW = pointDistance(potentialPos, watsonPos);
			int totalDist = distToS + distToW;

			// Tìm vị trí có tổng khoảng cách gần nhất
			if (totalDist < minTotalDist) {
				minTotalDist = totalDist;
				nearestPos = potentialPos;
			}
		}
	}

	return nearestPos;
}
string RobotSW::str() const
{
	// TODO: trả về chuỗi "Robot[pos=<pos>;type=S;dist=<distance>]"
	return "Robot[pos=(" + to_string(pos.getRow()) + "," + to_string(pos.getCol()) + ");type=SW;dist=" + to_string(getDistance()) + "]";
}
RobotType RobotSW::getType() const
{
	// TODO: get
	return robot_type;
}
int RobotSW::getDistance() const {
	Position sherlockPos = sherlock->getCurrentPosition();
	Position watsonPos = watson->getCurrentPosition();
	return pointDistance(pos, sherlockPos) + pointDistance(pos, watsonPos);
}
void RobotSW::move() {
	Position nextPos = getNextPosition();
	if (nextPos.getCol() != Position::npos.getCol()) {
		pos = nextPos;
	}
}
/*
 * CLASS: ArrayMovingObject
 */

ArrayMovingObject::ArrayMovingObject(int capacity) : capacity(capacity), count(0) {
	arr_mv_objs = new MovingObject * [capacity]; // Allocate memory for the array
}



bool ArrayMovingObject::isFull() const {
	return count == capacity; // Check if the array is full
}

bool ArrayMovingObject::add(MovingObject* mv_obj) {
	if (isFull()) {
		return true; // Cannot add if the array is full
	}

	// Thêm đối tượng vào mảng chỉ khi mảng chưa đầy
	arr_mv_objs[count] = mv_obj;
	count++; // Tăng count sau khi thêm
	return true;
}

MovingObject* ArrayMovingObject::get(int index) const {
	if (index < 0 || index >= count) {
		return nullptr; // Invalid index
	}
	return arr_mv_objs[index]; // Return the object at the given index
}

int ArrayMovingObject::size() const {
	return count; // Return the number of objects in the array
}

string ArrayMovingObject::str() const {
	stringstream ss;
	if (count == 0) {
		ss << "ArrayMovingObject[count=" << count << ";capacity=" << capacity;
	}
	else {
		ss << "ArrayMovingObject[count=" << count << ";capacity=" << capacity << ";";
		for (int i = 0; i < count; i++) {
			ss << arr_mv_objs[i]->str();
			if (i < count - 1) { // Thêm dấu chấm phẩy nếu chưa phải phần tử cuối cùng
				ss << ";";
			}
		}
	}

	ss << "]";
	return ss.str();
}
/*
 * CLASS: Configuration
 */
string duong;
void Configuration::xuLyMangViTri(const string& line, Position* arr, int numElements) {
	int index = 0;
	size_t start = line.find("[") + 1;
	size_t end = line.find("]");
	string arrString = line.substr(start, end - start);

	size_t pos = 0;
	while (pos < arrString.length() && index < numElements) { // Add index check
		size_t moNgoac = arrString.find("(", pos);
		size_t dongNgoac = arrString.find(")", moNgoac);
		size_t phay = arrString.find(",", moNgoac);

		int x = stoi(arrString.substr(moNgoac + 1, phay - moNgoac - 1));
		int y = stoi(arrString.substr(phay + 1, dongNgoac - phay - 1));

		arr[index].setRow(x);
		arr[index].setCol(y);
		index++;

		pos = dongNgoac + 2; // Di chuyển đến vị trí sau dấu chấm phẩy 
	}
}
void Configuration::xuLyViTri(const string& line, Position& pos) {
	size_t moNgoac = line.find("(") + 1;
	size_t phay = line.find(",", moNgoac);

	int x = stoi(line.substr(moNgoac, phay - moNgoac));
	int y = stoi(line.substr(phay + 1, line.length() - phay - 2));

	pos.setRow(x);
	pos.setCol(y);
}
string Configuration::formatPositionArray(const Position* arr, int numElements) const {
	stringstream ss;
	ss << "[";
	for (int i = 0; i < numElements; ++i) {
		ss << arr[i].str();
		if (i < numElements - 1) {
			ss << ";";
		}
	}
	ss << "]";
	return ss.str();
}
Configuration::Configuration(const string& filepath) {
	ifstream file(filepath);
	string line;

	// Khởi tạo mảng động
	arr_walls = nullptr;
	arr_fake_walls = nullptr;

	while (getline(file, line)) {

		if (line.find("MAP_NUM_ROWS") == 0) {
			map_num_rows = stoi(line.substr(line.find("=") + 1));
		}


		else if (line.find("MAP_NUM_COLS") == 0) {
			map_num_cols = stoi(line.substr(line.find("=") + 1));
		}


		else if (line.find("MAX_NUM_MOVING_OBJECTS") == 0) {
			max_num_moving_objects = stoi(line.substr(line.find("=") + 1));
		}


		else if (line.find("ARRAY_WALLS") == 0) {
			num_walls = countElements(line);
			arr_walls = new Position[num_walls];
			xuLyMangViTri(line, arr_walls, num_walls);
		}

		else if (line.find("ARRAY_FAKE_WALLS") == 0) {
			num_fake_walls = countElements(line);
			arr_fake_walls = new Position[num_fake_walls];
			xuLyMangViTri(line, arr_fake_walls, num_fake_walls);
		}

		else if (line.find("SHERLOCK_MOVING_RULE") == 0) {
			sherlock_moving_rule = line.substr(line.find("=") + 1);
		}
		else if (line.find("SHERLOCK_INIT_POS") == 0) {
			xuLyViTri(line, sherlock_init_pos);
		}
		else if (line.find("SHERLOCK_INIT_HP") == 0) {
			sherlock_init_hp = stoi(line.substr(line.find("=") + 1));
		}
		else if (line.find("SHERLOCK_INIT_EXP") == 0) {
			sherlock_init_exp = stoi(line.substr(line.find("=") + 1));
		}
		else if (line.find("WATSON_MOVING_RULE") == 0) {
			watson_moving_rule = line.substr(line.find("=") + 1);
		}
		else if (line.find("WATSON_INIT_POS") == 0) {
			xuLyViTri(line, watson_init_pos);
		}
		else if (line.find("WATSON_INIT_HP") == 0) {
			watson_init_hp = stoi(line.substr(line.find("=") + 1));
		}
		else if (line.find("WATSON_INIT_EXP") == 0) {
			watson_init_exp = stoi(line.substr(line.find("=") + 1));
		}
		else if (line.find("CRIMINAL_INIT_POS") == 0) {
			xuLyViTri(line, criminal_init_pos);
		}
		else if (line.find("NUM_STEPS") == 0) {
			num_steps = stoi(line.substr(line.find("=") + 1));
		}
	}
	file.close();
}



string Configuration::str() const {
	stringstream ss;
	ss << "Configuration[\n"
		<< "MAP_NUM_ROWS=" << map_num_rows << "\n"
		<< "MAP_NUM_COLS=" << map_num_cols << "\n"
		<< "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << "\n"
		<< "NUM_WALLS=" << num_walls << "\n"
		<< "ARRAY_WALLS=" << formatPositionArray(arr_walls, num_walls) << "\n"
		<< "NUM_FAKE_WALLS=" << num_fake_walls << "\n"
		<< "ARRAY_FAKE_WALLS=" << formatPositionArray(arr_fake_walls, num_fake_walls) << "\n"
		<< "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << "\n"
		<< "SHERLOCK_INIT_POS=" << sherlock_init_pos.str() << "\n"
		<< "SHERLOCK_INIT_HP=" << sherlock_init_hp << "\n"
		<< "SHERLOCK_INIT_EXP=" << sherlock_init_exp << "\n"
		<< "WATSON_MOVING_RULE=" << watson_moving_rule << "\n"
		<< "WATSON_INIT_POS=" << watson_init_pos.str() << "\n"
		<< "WATSON_INIT_HP=" << watson_init_hp << "\n"
		<< "WATSON_INIT_EXP=" << watson_init_exp << "\n"
		<< "CRIMINAL_INIT_POS=" << criminal_init_pos.str() << "\n"
		<< "NUM_STEPS=" << num_steps << "\n"
		<< "]";
	return ss.str();
}
ItemType MagicBook::getType() const
{
	return MAGIC_BOOK; // TODO: get (1 dòng)
}
string MagicBook::str() const
{
	return "MagicBook"; // TODO: trả về chuỗi biểu diễn (1 dòng)
}
bool MagicBook::canUse(Character* obj, Robot* robot)
{
	// TODO: điều kiện sử dụng
	// *Sau khi đấm Robot, exp

	Sherlock* sherlock = dynamic_cast<Sherlock*>(obj);
	Watson* watson = dynamic_cast<Watson*>(obj);
	if (sherlock != nullptr) {
		return (sherlock->getEXP() <= 350 && robot == nullptr);
	}
	else if (watson != nullptr) {
		return (watson->getEXP() <= 350 && robot == nullptr);
	}
	return false;
}
void MagicBook::use(Character* obj, Robot* robot) {
	if (dynamic_cast<Sherlock*>(obj) != nullptr) {
		// obj là Sherlock
		Sherlock* sherlock = dynamic_cast<Sherlock*>(obj);
		int currentexp = sherlock->getEXP();
		sherlock->setEXP(currentexp + currentexp * 0.25 + 0.99);
	}
	else if (dynamic_cast<Watson*>(obj) != nullptr) {
		// obj là Watson
		Watson* watson = dynamic_cast<Watson*>(obj);
		int currentexp = watson->getEXP();
		watson->setEXP(currentexp + currentexp * 0.25 + 0.99);
	}
}
// *CLASS: EnergyDrink
ItemType EnergyDrink::getType() const
{
	return ENERGY_DRINK; // TODO: get (1 dòng)
}
string EnergyDrink::str() const
{
	return "EnergyDrink"; // TODO: trả về chuỗi biển diễn (1 dòng)
}
bool EnergyDrink::canUse(Character* obj, Robot* robot)
{
	// TODO: điều kiện sử dụng
	// *Sau khi đấm Robot, hp
	Sherlock* sherlock = dynamic_cast<Sherlock*>(obj);
	Watson* watson = dynamic_cast<Watson*>(obj);
	if (sherlock != nullptr) {
		return (sherlock->getHP() <= 100 && robot == nullptr);
	}
	else if (watson != nullptr) {
		return (watson->getHP() <= 100 && robot == nullptr);
	}
	return false;
}
void EnergyDrink::use(Character* obj, Robot* robot) {
	if (dynamic_cast<Sherlock*>(obj) != nullptr) {
		// Sherlock sử dụng EnergyDrink
		Sherlock* sherlock = dynamic_cast<Sherlock*>(obj);
		int hp = sherlock->getHP();
		hp = hp + hp * 0.2 + 0.99;
		sherlock->setHP(hp);
	}
	else if (dynamic_cast<Watson*>(obj) != nullptr) {
		// Watson sử dụng EnergyDrink
		Watson* watson = dynamic_cast<Watson*>(obj);
		int hp = watson->getHP();// thay obj=watson  
		hp = hp + hp * 0.2 + 0.99;
		watson->setHP(hp);
	}
}
// *CLASS: FirstAid
ItemType FirstAid::getType() const
{
	return FIRST_AID; // TODO: get (1 dòng)
}
string FirstAid::str() const
{
	return "FirstAid"; // TODO: trả về chuỗi biểu diễn (1 dòng)
}
bool FirstAid::canUse(Character* obj, Robot* robot)
{
	// TODO: điều kiện sử dụng
	// *Sau khi đấm Robot, exp || hp
	Sherlock* sherlock = dynamic_cast<Sherlock*>(obj);
	Watson* watson = dynamic_cast<Watson*>(obj);
	if (sherlock != nullptr) {
		return (sherlock->getHP() <= 100 || sherlock->getEXP() <= 350) && robot == nullptr;
	}
	else if (watson != nullptr) {
		return (watson->getHP() <= 100 || watson->getEXP() <= 350) && robot == nullptr;
	}
	return false;
}
void FirstAid::use(Character* obj, Robot* robot) {
	if (dynamic_cast<Sherlock*>(obj) != nullptr) {
		// Sherlock sử dụng FirstAid
		Sherlock* sherlock = dynamic_cast<Sherlock*>(obj);
		int hp = sherlock->getHP();
		hp = hp + hp * 0.5 + 0.99;
		sherlock->setHP(hp);
	}
	else if (dynamic_cast<Watson*>(obj) != nullptr) {
		// Watson sử dụng FirstAid
		Watson* watson = dynamic_cast<Watson*>(obj);
		int hp = watson->getHP();
		hp = hp + hp * 0.5 + 0.99;
		watson->setHP(hp);
	}
}
// *CLASS: ExcemptionCard
ItemType ExcemptionCard::getType() const
{
	return EXCEMPTION_CARD; // TODO: get (1 dòng)
}
string ExcemptionCard::str() const
{
	return "ExcemptionCard"; // TODO: trả về chuỗi biểu diễn (1 dòng)
}
bool ExcemptionCard::canUse(Character* obj, Robot* robot) {
	Sherlock* sherlock = dynamic_cast<Sherlock*>(obj);
	if (sherlock != nullptr) {
		return sherlock->getHP() % 2 != 0 && robot != nullptr;
	}
	return false;
}

void ExcemptionCard::use(Character* obj, Robot* robot)
{
	// TODO: sinh viên hiện thực theo tư duy code của mình (hàm có thể rỗng)

}
// *CLASS: PassingCard
PassingCard::PassingCard(int i, int j)
{
	// TODO: constructor gán giá trị cho thuộc tính challenge (i,j là tọa độ)
	int t = (i * 11 + j) % 4;
	if (t == 0) {
		this->challenge = "RobotS";
	}
	else if (t == 1) {
		this->challenge = "RobotC";
	}
	else if (t == 2) {
		this->challenge = "RobotSW";
	}
	else if (t == 3) {
		this->challenge = "all";
	}
}
PassingCard::PassingCard(string challenge) {
	this->challenge=challenge;
}
ItemType PassingCard::getType() const
{
	return PASSING_CARD; // TODO: get (1 dòng)
}
string PassingCard::str() const
{
	return "PassingCard"; // TODO: trả về chuỗi biểu diễn (1 dòng)
}
RobotType Robot::getRobotType() {
	return robot_type;
}
bool PassingCard::canUse(Character* obj, Robot* robot) {
	Watson* watson = dynamic_cast<Watson*>(obj);
	if (watson != nullptr) {
		return watson->getHP() % 2 == 0 && robot != nullptr;
	}
	return false;
}
void PassingCard::use(Character* obj, Robot* robot) {
	Watson* watson = dynamic_cast<Watson*>(obj);
	if (challenge == "all") {
		return; // Không cần kiểm tra gì thêm nếu thẻ là "all"
	}


	if (robot != nullptr) {

		switch (robot->getRobotType()) {
		case C:
			if (challenge != "RobotC") {
				watson->setEXP(watson->getEXP() - 50);
				if (watson->getEXP() == 0) {
					watson->setEXP(0);
				}
			}
			break;
		case S:
			if (challenge != "RobotS") {
				watson->setEXP(watson->getEXP() - 50);
				if (watson->getEXP() == 0) {
					watson->setEXP(0);
				}
			}
			break;
		case W:
			if (challenge != "RobotW") {
				watson->setEXP(watson->getEXP() - 50);
				if (watson->getEXP() == 0) {
					watson->setEXP(0);
				}
			}
			break;
		case SW:
			if (challenge != "RobotSW") {
				watson->setEXP(watson->getEXP() - 50);
				if (watson->getEXP() == 0) {
					watson->setEXP(0);
				}
			}
			break;
		}
	}
}
// *CLASS: BaseBag
BaseBag::BaseBag(int capacity) : capacity(capacity), count(0), head(nullptr)
{
	// TODO: constructor gán giá trị cho CÁC THUỘC TÍNH
}
BaseBag::~BaseBag()
{
	// TODO: destructor xóa các Node (Lưu ý phải xóa cả item trong Node đó)
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}
bool BaseBag::insert(BaseItem* item)
{
	// TODO: thêm Node chứa item vào đầu Linked List
	if (count == capacity)
		return false;
	Node* newNode = new Node(item);
	newNode->next = head;
	head = newNode;
	count++;
	return true;
}
BaseItem* BaseBag::get(ItemType itemType) {
	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr) {
		if (current->item->getType() == itemType) {
			// Tìm thấy item có loại itemType
			if (previous != nullptr) {
				// Hoán đổi item với head
				BaseItem* temp = head->item;
				head->item = current->item;
				current->item = temp;
			}

			// Xóa item (lúc này đã ở head)
			BaseItem* itemToReturn = head->item;
			head = head->next; // Cập nhật head TRƯỚC khi xóa
			size--;
			count--;
			return itemToReturn;
		}

		previous = current;
		current = current->next;
	}

	return nullptr; // Không tìm thấy item phù hợp
}

string BaseBag::str() const {
	string s = "Bag[count=" + to_string(count) + ";";

	Node* current = head;
	while (current != nullptr) {
		s += current->item->str(); // Thêm tên kiểu của vật phẩm
		if (current->next != nullptr) {
			s += ","; // Thêm dấu phẩy nếu chưa phải node cuối cùng
		}
		current = current->next;
	}

	s += "]";
	return s;
}
// *CLASS: SherlockBag
SherlockBag::SherlockBag(Sherlock* character)
	: BaseBag(13) // TODO: constructor class cha
{
	// TODO: constructor class con
	this->obj = character;
	this->sherlock = character; // Khởi tạo sherlock
}

// SherlockBag::get()
BaseItem* SherlockBag::get() {
	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr) {
		if (current->item->canUse(sherlock, nullptr)) {
			// Tìm thấy item Sherlock có thể sử dụng

			if (previous != nullptr) {
				// Nếu item không phải là head, đảo item lên đầu
				BaseItem* temp = head->item;
				head->item = current->item;
				current->item = temp;
			}

			// Xóa head (item cần xóa đã ở head)
			BaseItem* itemToReturn = head->item;
			head = head->next;
			count--;
			size--;
			return itemToReturn;
		}

		previous = current;
		current = current->next;
	}

	return nullptr; // Không tìm thấy item phù hợp
}

// *CLASS: WatsonBag
WatsonBag::WatsonBag(Watson* character) : BaseBag(15) {
	this->obj = character;
	this->watson = character; // Khởi tạo watson
}

BaseItem* WatsonBag::get() {
	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr) {
		if (current->item->canUse(watson, nullptr)) {
			// Tìm thấy item Watson có thể sử dụng

			if (previous != nullptr) {
				// Nếu item không phải là head, đảo item lên đầu
				BaseItem* temp = head->item;
				head->item = current->item;
				current->item = temp;
			}

			// Xóa head (item cần xóa đã ở head)
			BaseItem* itemToReturn = head->item;
			head = head->next;
			count--;
			size--;
			return itemToReturn;
		}

		previous = current;
		current = current->next;
	}

	return nullptr;
}

BaseItem* Robot::NewItem() {
	switch (duong) {
	case MAGIC_BOOK:
		return new MagicBook();
	case ENERGY_DRINK:
		return new EnergyDrink();
	case FIRST_AID:
		return new FirstAid();
	case EXCEMPTION_CARD:
		return new ExcemptionCard();
	case PASSING_CARD:
		return new PassingCard(pos.getRow(), pos.getCol()); // Truyền tọa độ của Robot
	default:
		return nullptr;
	}
}
bool BaseBag::checkItem(ItemType itemType) {
	Node* current = head;
	while (current != nullptr) {
		if (current->item->getType() == itemType) {
			return true; // Tìm thấy item
		}
		current = current->next;
	}
	return false; // Không tìm thấy
}

// *------------------------------------------------------------------
// *
// *------------------------------------------------------------------
// !-----------------------------------
// ! Lưu ý về việc xét thông số khi tăng giảm
// ! Các thay đổi thông số là dựa trên thông số hiện tại
// ! Các thông số không phải số nguyên THỰC HIỆN LÀM TRÒN LÊN -> NHÂN VẬT CHỈ HI SINH KHI INIT hp = 0
// !-----------------------------------
// *CLASS: ArrayMovingObject
bool operator==(const Position& lhs, const Position& rhs) {
	return (lhs.getRow() == rhs.getRow() && lhs.getCol() == rhs.getCol());
}

bool ArrayMovingObject::checkMeet(int index) {
	// TODO: Xét va chạm của nhân vật (theo index) với các nhân vật khác trong array
	// TODO: Thực hiện xử lý các sự kiện xảy ra (thử thách, thêm item, bắt Criminal)
	for (int i = 0; i < count; ++i) {
		if (arr_mv_objs[i]->getCurrentPosition() == arr_mv_objs[index]->getCurrentPosition() && index != i) {
			//1. index là sherLock
			if (arr_mv_objs[index]->getObjectType() == SHERLOCK) { // Vị trí index là Sherlock
				Sherlock* sher = dynamic_cast<Sherlock*>(arr_mv_objs[index]);

				// Gọi meet cho từng loại đối tượng va chạm
				if (arr_mv_objs[i]->getObjectType() == ROBOT) { // Neu trung Robot thi chien dau va tra ve false(neu thang robotC tra ve true)
					Robot* robot = dynamic_cast<Robot*>(arr_mv_objs[i]);
					if (robot->getRobotType() == C) {
						RobotC* robotC = dynamic_cast<RobotC*>(robot);
						if (sher->meet(robotC)) {
							return true;

						}
					}
					if (robot->getRobotType() == S) {
						RobotS* robotS = dynamic_cast<RobotS*>(robot);
						sher->meet(robotS);
					}
					if (robot->getRobotType() == W) {
						RobotW* robotW = dynamic_cast<RobotW*>(robot);
						sher->meet(robotW);
					}
					if (robot->getRobotType() == SW) {
						RobotSW* robotSW = dynamic_cast<RobotSW*>(robot);
						sher->meet(robotSW);
					}
				}
				if (arr_mv_objs[i]->getObjectType() == WATSON) { // Neu trung Waston thi trao doi vat pham tui va tra ve false
					Watson* watson = dynamic_cast<Watson*>(arr_mv_objs[i]);
					sher->meet(watson);
				}
				if (arr_mv_objs[i]->getObjectType() == CRIMINAL) { // Neu trung voi ten trom thi tra ve true
					return true;
				}
			}
			//2. index là Watson
			else if (arr_mv_objs[index]->getObjectType() == WATSON) { // // Vi tri index la Waston
				Watson* watson = dynamic_cast<Watson*>(arr_mv_objs[index]);

				// Gọi meet cho từng loại đối tượng va chạm
				if (arr_mv_objs[i]->getObjectType() == ROBOT) {
					Robot* robot = dynamic_cast<Robot*>(arr_mv_objs[i]);
					if (robot->getRobotType() == C) {
						RobotC* robotC = dynamic_cast<RobotC*>(robot);
						watson->meet(robotC);
					}
					if (robot->getRobotType() == S) {
						RobotS* robotS = dynamic_cast<RobotS*>(robot);
						watson->meet(robotS);
					}
					if (robot->getRobotType() == W) {
						RobotW* robotW = dynamic_cast<RobotW*>(robot);
						watson->meet(robotW);
					}
					if (robot->getRobotType() == SW) {
						RobotSW* robotSW = dynamic_cast<RobotSW*>(robot);
						watson->meet(robotSW);
					}
				}
				if (arr_mv_objs[i]->getObjectType() == SHERLOCK) {
					Sherlock* sherlock = dynamic_cast<Sherlock*>(arr_mv_objs[i]);
					watson->meet(sherlock);
				}
				if (arr_mv_objs[i]->getObjectType() == CRIMINAL) { // Neu trung voi ten trom thi tra ve true
					return true;
				}
			}
			//3.Index là criminal
			else if (arr_mv_objs[index]->getObjectType() == CRIMINAL) { // Vi tri index la ten trom
				// Nếu tên trộm gặp Sherlock hoặc Watson -> Bị bắt
				if (arr_mv_objs[i]->getObjectType() == SHERLOCK || arr_mv_objs[i]->getObjectType() == WATSON) {
					return true;
				}
			}

			// Trường hợp 4: Vị trí index là Robot
			else if (arr_mv_objs[index]->getObjectType() == ROBOT) {
				Robot* robot = dynamic_cast<Robot*>(arr_mv_objs[index]);

				// Gọi meet cho từng loại đối tượng va chạm
				if (arr_mv_objs[i]->getObjectType() == SHERLOCK) {
					Sherlock* sher = dynamic_cast<Sherlock*>(arr_mv_objs[i]);
					if (robot->getRobotType() == C) {
						RobotC* robotC = dynamic_cast<RobotC*>(robot);
						if (sher->meet(robotC)) {
							return true;
						}

					}
					if (robot->getRobotType() == S) {
						RobotS* robotS = dynamic_cast<RobotS*>(robot);
						sher->meet(robotS);
					}
					if (robot->getRobotType() == W) {
						RobotW* robotW = dynamic_cast<RobotW*>(robot);
						sher->meet(robotW);
					}
					if (robot->getRobotType() == SW) {
						RobotSW* robotSW = dynamic_cast<RobotSW*>(robot);
						sher->meet(robotSW);
					}
				}
				if (arr_mv_objs[i]->getObjectType() == WATSON) {
					Watson* wat = dynamic_cast<Watson*>(arr_mv_objs[i]);
					if (robot->getRobotType() == C) {
						RobotC* robotC = dynamic_cast<RobotC*>(robot);
						wat->meet(robotC);
					}
					if (robot->getRobotType() == S) {
						RobotS* robotS = dynamic_cast<RobotS*>(robot);
						wat->meet(robotS);
					}
					if (robot->getRobotType() == W) {
						RobotW* robotW = dynamic_cast<RobotW*>(robot);
						wat->meet(robotW);
					}
					if (robot->getRobotType() == SW) {
						RobotSW* robotSW = dynamic_cast<RobotSW*>(robot);
						wat->meet(robotSW);
					}
				}
			}
		}
	}
	return false;
}

// ... (Các hàm khác) ...
// *CLASS: Sherlock
// ! Lưu ý: ExcemptionCard được dùng để BỎ QUA nếu THỬ THÁCH THẤT BẠI -> xem như không thực hiện thử thách -> không gọi get lần 2
// ! Thực hiện get từ bag sau khi insert item
void Sherlock::setPos(Position pos)
{
	// TODO: Sử dụng trong trường hợp thắng RobotC sẽ dịch chuyển đến vị trí Criminal
	this->pos = pos;
}
bool Sherlock::meet(RobotS* robotS) {
	bool passedChallenge = false; // Biến đánh dấu kết quả thử thách

	// 1. Sử dụng ExcemptionCard trước khi thực hiện thử thách
	if (getHP() % 2 != 0 && getBag()->get(EXCEMPTION_CARD) != nullptr) {
		return false; // Bỏ qua thử thách
	}



	// 2. Thực hiện thử thách 
	if (exp > 400) {
		passedChallenge = true;
	}
	else {
		setEXP(int(exp * 0.9 + 0.99));
	}

	// 3. Nhận item nếu thắng thử thách 
	if (passedChallenge) {
		BaseItem* robotItem = robotS->NewItem();
		if (robotItem != nullptr) {
			// Thêm item vào túi đồ SAU khi kiểm tra exp
			getBag()->insert(robotItem);
			// Sử dụng item ngay sau khi nhận (nếu có)
			BaseItem* usableItem = getBag()->get();
			if (usableItem != nullptr) {
				usableItem->use(this, nullptr);
				delete usableItem;
			}
		}
	}

	return false;
}
bool Sherlock::meet(RobotW* robotW) {
	// 1. Không có thử thách, nhận item luôn
	BaseItem* robotItem = robotW->NewItem();
	if (robotItem != nullptr) {
		getBag()->insert(robotItem);
	}

	// 2. Sử dụng item hồi phục 
	BaseItem* usableItem = getBag()->get();
	if (usableItem != nullptr) {
		usableItem->use(this, nullptr);
		delete usableItem;
	}

	return false;
}
bool Sherlock::meet(RobotSW* robotSW) {
	// 1. Sử dụng ExcemptionCard trước khi thực hiện thử thách
	if (getHP() % 2 != 0 && getBag()->get(EXCEMPTION_CARD) != nullptr) {
		return false; // Bỏ qua thử thách
	}

	bool passedChallenge = false; // Biến đánh dấu kết quả thử thách

	// 2. Thực hiện thử thách
	if (exp > 300 && hp > 335) {
		passedChallenge = true;
	}
	else {
		setHP(int(hp * 0.85 + 0.99)); // Giảm hp 15%
		setEXP(int(exp * 0.85 + 0.99)); // Giảm exp 15%
		BaseItem* usableItem = getBag()->get();
		if (usableItem != nullptr) {
			usableItem->use(this, nullptr);
			delete usableItem;

		}
	}

	// 3. Nhận item nếu thắng thử thách
	if (passedChallenge) {
		BaseItem* robotItem = robotSW->NewItem();
		if (robotItem != nullptr) {
			// Thêm item vào túi đồ SAU khi kiểm tra exp và hp
			getBag()->insert(robotItem);
			// Sử dụng item ngay sau khi nhận (nếu có)
			BaseItem* usableItem = getBag()->get();
			if (usableItem != nullptr) {
				usableItem->use(this, nullptr);
				delete usableItem;
			}
		}
	}

	return false;
}

bool Sherlock::meet(RobotC* robotC) {
	bool passedChallenge = false;
	if (exp > 500) {
		passedChallenge = true;
		// Gán vị trí của Criminal cho Sherlock
		this->pos = robotC->criminal->getCurrentPosition();
		return true;
	}

	// 1. Sử dụng ExcemptionCard trước khi thực hiện thử thách
	if (getHP() % 2 != 0 && getBag()->get(EXCEMPTION_CARD) != nullptr) {
		passedChallenge = false; // Không bắt được tội phạm, nhưng tránh bị trừ exp
	}

	// 3. Nhận item (luôn nhận)
	BaseItem* robotItem = robotC->NewItem();
	if (robotItem != nullptr) {
		getBag()->insert(robotItem);
		// Sử dụng item ngay sau khi nhận (nếu có)
		BaseItem* usableItem = getBag()->get();
		if (usableItem != nullptr) {
			usableItem->use(this, nullptr);
			delete usableItem;
		}
	}

	return passedChallenge;
}
bool Sherlock::meet(Watson* watson) {
	bool sherlockHasPassingCard = getBag()->checkItem(PASSING_CARD);
	bool watsonHasExcemptionCard = watson->getBag()->checkItem(EXCEMPTION_CARD);

	// Trao đổi PassingCard từ Sherlock sang Watson
	// Chỉ trao đổi nếu Watson có ExcemptionCard
	if (sherlockHasPassingCard && watsonHasExcemptionCard) {
		while (getBag()->checkItem(PASSING_CARD)) {
			BaseItem* passingCard = getBag()->get(PASSING_CARD);
			if (passingCard != nullptr) {
				watson->getBag()->insert(passingCard);
			}
		}
	}

	// Trao đổi ExcemptionCard từ Watson sang Sherlock
	// Chỉ trao đổi nếu Sherlock có PassingCard và hp của Sherlock là số lẻ
	if (watsonHasExcemptionCard && sherlockHasPassingCard && getHP() % 2 != 0) {
		while (watson->getBag()->checkItem(EXCEMPTION_CARD)) {
			BaseItem* excemptionCard = watson->getBag()->get(EXCEMPTION_CARD);
			if (excemptionCard != nullptr) {
				getBag()->insert(excemptionCard);
			}
		}
	}

	return false; // Trả về true vì đã trao đổi thẻ
}
// *CLASS: Watson
// ! Lưu ý: PassingCard được dùng khi GẶP ROBOT để bỏ qua thử thách nếu đúng loại thẻ
// ! Thực hiện get từ bag sau khi insert item
bool Watson::meet(RobotS* robotS)
{
	BaseItem* usableItem = getBag()->get();
	if (usableItem != nullptr) {
		usableItem->use(this, nullptr);
		delete usableItem;

	}
	return false;
	// TODO: Xử lý trao đổi khi gặp robot S
}
bool Watson::meet(RobotW* robotW) {
	// 1. Sử dụng PassingCard trước khi thực hiện thử thách
	bool passedChallenge = false; // Biến đánh dấu kết quả thử thách

	if (getHP() % 2 == 0 && getBag()->get(PASSING_CARD) != nullptr) {
		passedChallenge = true; // Bỏ qua thử thách
	}


	// 2. Thực hiện thử thách
	if (hp > 350) {
		passedChallenge = true;
	}
	else {
		setHP(int(hp * 0.95 + 0.99));
		BaseItem* usableItem = getBag()->get();
		if (usableItem != nullptr) {
			usableItem->use(this, nullptr);
			delete usableItem;

		}
	}

	// 3. Nhận item nếu thắng thử thách
	if (passedChallenge) {
		BaseItem* robotItem = robotW->NewItem();
		if (robotItem != nullptr) {
			// Thêm item vào túi đồ SAU khi kiểm tra hp
			getBag()->insert(robotItem);
			// Sử dụng item ngay sau khi nhận (nếu có)
			BaseItem* usableItem = getBag()->get();
			if (usableItem != nullptr) {
				usableItem->use(this, nullptr);
				delete usableItem;

			}
		}
	}

	return false;
}
bool Watson::meet(RobotSW* robotSW) {
	// 1. Sử dụng PassingCard trước khi thực hiện thử thách
	if (getHP() % 2 == 0 && getBag()->get(PASSING_CARD) != nullptr) {
		return false; // Bỏ qua thử thách
	}

	bool passedChallenge = false; // Biến đánh dấu kết quả thử thách

	// 2. Thực hiện thử thách
	if (exp > 600 && hp > 165) {
		passedChallenge = true;
	}
	else {
		setHP(int(hp * 0.85 + 0.99));
		setEXP(int(exp * 0.85 + 0.99));
		BaseItem* usableItem = getBag()->get();
		if (usableItem != nullptr) {
			usableItem->use(this, nullptr);
			delete usableItem;

		}
	}

	// 3. Nhận item nếu thắng thử thách
	if (passedChallenge) {
		BaseItem* robotItem = robotSW->NewItem();
		if (robotItem != nullptr) {
			// Thêm item vào túi đồ SAU khi kiểm tra exp và hp
			getBag()->insert(robotItem);
			// Sử dụng item ngay sau khi nhận (nếu có)
			BaseItem* usableItem = getBag()->get();
			if (usableItem != nullptr) {
				usableItem->use(this, nullptr);
				delete usableItem;

			}
		}
	}

	return false;
}

bool Watson::meet(RobotC* robotC) {
	// 1. Sử dụng PassingCard trước khi thực hiện thử thách
	if (getHP() % 2 == 0 && getBag()->get(PASSING_CARD) != nullptr) {

		if (thuThach(robotC->getCurrentPosition()) != "RobotC" || thuThach(robotC->getCurrentPosition()) != "all") {
			setEXP(exp - 50);
			if (exp < 0) {
				setEXP(0);
			}
		}
		BaseItem* robotItem = robotC->NewItem();
		if (robotItem != nullptr) {
			getBag()->insert(robotItem); // Thêm item vào túi đồ

			// 3. Sử dụng item hồi phục (nếu có)
			BaseItem* usableItem = getBag()->get(); // Lấy item hồi phục (bất kỳ)
			if (usableItem != nullptr) {
				usableItem->use(this, nullptr);
				delete usableItem;
			}
		}
		return false; // Bỏ qua thử thách
	}

	// 2. Nhận item từ RobotC
	BaseItem* robotItem = robotC->NewItem();
	if (robotItem != nullptr) {
		getBag()->insert(robotItem); // Thêm item vào túi đồ

		// 3. Sử dụng item hồi phục (nếu có)
		BaseItem* usableItem = getBag()->get(); // Lấy item hồi phục (bất kỳ)
		if (usableItem != nullptr) {
			usableItem->use(this, nullptr);
			delete usableItem;
		}
	}

	return false; // Watson luôn có lợi khi gặp RobotC
}
bool Watson::meet(Sherlock* sherlock)
{
	// TODO: Xử lý trao đổi khi gặp Sherlock
	return sherlock->meet(this);
}

BaseBag* Sherlock::getBag() const
{
	// TODO: get bag
	return bag;
}
BaseBag* Watson::getBag() const
{
	return bag;
	// TODO: get bag
}


BaseItem::BaseItem() {} // Hàm tạo mặc định
// Hàm hủy mặc định

// study_in_pink2.cpp
 // Hàm hủy mặc định





BaseItem* BaseBag::get() {
	// Implementation of the get function
	return 0;
}

RobotType Robot::getType() {
	return robot_type;
}
