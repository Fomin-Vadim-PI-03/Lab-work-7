#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



class LoadType {       //Абстрактный класс - Типы груза
protected:
    std::string ID;     //ID Груза
    int weight;         //Вес

public:
    LoadType(std::string ID, int weight);
    LoadType();

    int GetWeight();              //Получить значение weight
    std::string GetContentID();   //Получить значение ID

    virtual ~LoadType() = 0;   //Чисто виртуальный деструктор
};

LoadType::LoadType(std::string ID, int weight) {
    this->ID = ID;
    this->weight = weight;
}

LoadType::LoadType() {
    this->ID = "none";
    this->weight = 0;
}

int LoadType::GetWeight() {
    return weight;
}

std::string LoadType::GetContentID() {
    return ID;
}

LoadType::~LoadType()
{ }


class LoadFish : public LoadType {         //Груз: Рыба
protected:
    std::string fishName;        //Наименование рыбы (Лосось, карп...)
private:
    int count;              //Кол-во рыбы
public:
    LoadFish(std::string ID, int weight, std::string fishName, int count);
    LoadFish(std::string ID, int weight, std::string fishName);
    LoadFish();

    void ShowImportantMessages();     //Вывод важных примечаний о типе груза

    virtual void NoteTransfer();      //Виртуальная функция - Примечание о перевозке

    friend std::ostream& operator<<(std::ostream& os, const LoadFish& object);
    ~LoadFish();
};

LoadFish::LoadFish(std::string ID, int weight, std::string fishName, int count) :
    LoadType(ID, weight) {
    this->fishName = fishName;
    this->count = count;
}

LoadFish::LoadFish(std::string ID, int weight, std::string fishName) :
    LoadType(ID, weight) {
    this->fishName = fishName;
    this->count = 0;
}

LoadFish::LoadFish() :
    LoadType() {
    this->fishName = "none";
    this->count = 0;
}

void LoadFish::ShowImportantMessages() {
    NoteTransfer();
}

void LoadFish::NoteTransfer() {
    std::cout << "Рыбному грузу \'" << fishName << "\' необходима низкая температура при перевозке.\n";
};

std::ostream& operator<<(std::ostream& os, const LoadFish& object) {
    os << "Fish{"
        << "ID='" << object.ID << '\''
        << ", fishName='" << object.fishName << '\''
        << ", weight=" << object.weight
        << ", count=" << object.count
        << '}';
    return os;
}

LoadFish::~LoadFish() {};


class LoadWhale : public LoadFish {         //Груз: Кит
protected:
    std::string dimensions;          //Размер кита (Д x Ш x В)

public:
    LoadWhale(std::string ID, int weight, std::string fishName, std::string dimensions);
    LoadWhale();

    void NoteTransfer();      //Примечание о перевозке

    friend std::ostream& operator<<(std::ostream& os, const LoadWhale& object);
    ~LoadWhale();
};

LoadWhale::LoadWhale(std::string ID, int weight, std::string fishName, std::string dimensions) :
    LoadFish(ID, weight, fishName) {
    this->dimensions = dimensions;
}

LoadWhale::LoadWhale() {
    this->ID = "none";
    this->weight = 0;
    this->fishName = "none";
    this->dimensions = "none";
}

void LoadWhale::NoteTransfer() {
    std::cout << "Грузу типа Кит \'" << fishName << "\' необходимы доп. крепительные ремни при перевозке.\n";
}

std::ostream& operator<<(std::ostream& os, const LoadWhale& object) {
    os << "Whale{"
        << "ID='" << object.ID << '\''
        << ", fishName='" << object.fishName << '\''
        << ", weight=" << object.weight
        << '}';
    return os;
}

LoadWhale::~LoadWhale() {};


class LoadFurniture : public LoadType {         //Груз: Мебель
protected:
    std::string furnitureName;                //Наименование мебели
    int count;                                //Кол-во мебели

public:
    LoadFurniture(std::string ID, int weight, std::string furnitureName, int count);
    LoadFurniture();

    int GetOneItemWeight();             //Получение веса одного предмета
    int GetOneItemWeightSpecial();      //Получение веса одного предмета марки 'Special' (без упаковки)

    LoadFurniture& operator=(const LoadFurniture& obj);    //Перегрузка оператора присваивания

    friend std::ostream& operator<<(std::ostream& os, const LoadFurniture& object);
    ~LoadFurniture();
};

LoadFurniture::LoadFurniture(std::string ID, int weight, std::string furnitureName, int count) :
    LoadType(ID, weight) {
    this->furnitureName = furnitureName;
    this->count = count;
}

LoadFurniture::LoadFurniture() :
    LoadType() {
    this->furnitureName = "none";
    this->count = 0;
}

int LoadFurniture::GetOneItemWeight() {
    return weight / count;
}

int LoadFurniture::GetOneItemWeightSpecial() {
    return weight / count * 0.85;
}

LoadFurniture& LoadFurniture::operator=(const LoadFurniture& obj)
{
    this->ID = obj.ID;
    this->weight = obj.weight;
    this->furnitureName = obj.furnitureName;
    this->count = obj.count;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const LoadFurniture& object) {
    os << "Furniture{"
        << "ID='" << object.ID << '\''
        << ", furnitureName='" << object.furnitureName << '\''
        << ", weight=" << object.weight
        << ", count=" << object.count
        << '}';
    return os;
}

LoadFurniture::~LoadFurniture() {};

class LoadChairsInBoxes : public LoadFurniture {         //Груз: Стулья в коробках
public:
    LoadChairsInBoxes(std::string ID, int weight, std::string furnitureName, int count);
    LoadChairsInBoxes();

    int GetOneItemWeight();              //Перегрузка с вызовом метода базового класса (Получение веса одного предмета без коробки)
    int GetOneItemWeightSpecial();       //Перегрузка без вызова метода базового класса (Получение веса одного предмета марки 'Special' без коробки)

    LoadChairsInBoxes& operator=(const LoadFurniture& obj);          //Перегрузка - Присваивание объекту производного класса объекта базового класса

    friend std::ostream& operator<<(std::ostream& os, const LoadChairsInBoxes& object);
    ~LoadChairsInBoxes();
};

LoadChairsInBoxes::LoadChairsInBoxes(std::string ID, int weight, std::string furnitureName, int count) :
    LoadFurniture(ID, weight, furnitureName, count) {
}

LoadChairsInBoxes::LoadChairsInBoxes() :
    LoadFurniture() {
}

int LoadChairsInBoxes::GetOneItemWeight() {
    return (LoadFurniture::GetOneItemWeight() * 0.9);
}

int LoadChairsInBoxes::GetOneItemWeightSpecial() {
    return weight / count * 0.9 * 0.85;
}


LoadChairsInBoxes& LoadChairsInBoxes::operator=(const LoadFurniture& obj)
{
    if (this != &obj) {
        LoadFurniture::operator=(obj);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const LoadChairsInBoxes& object) {
    os << "ChairsInBoxes{"
        << "ID='" << object.ID << '\''
        << ", furnitureName='" << object.furnitureName << '\''
        << ", weight=" << object.weight
        << ", count=" << object.count
        << '}';
    return os;
}

LoadChairsInBoxes::~LoadChairsInBoxes() {};


template<class T = int>
class LoadMoney : public LoadType {        //Груз: Деньги
private:
    T sum;       //Сумма денег
public:
    LoadMoney(std::string ID, int weight, T sum);
    LoadMoney();

    T GetSum();    //Получить значение sum

    ~LoadMoney();
};
template<class T>
LoadMoney<T>::LoadMoney(std::string ID, int weight, T sum) :
    LoadType(ID, weight) {
    this->sum = sum;
}
template<class T>
LoadMoney<T>::LoadMoney() :
    LoadType() {
    this->sum = 0;
}
template<class T>
T LoadMoney<T>::GetSum() {
    return sum;
}
template<class T>
LoadMoney<T>::~LoadMoney() {};



class Container {    //Контейнер
private:
    std::string destinationAddress;    //Адрес назначения
    std::string IDNumber;              //Идентификационный номер
    LoadType* load;                   //Груз в контейнере

public:
    Container(std::string DestinationAddress, std::string IDNumber, LoadType* Load);    //Инициализация контейнера (конструктор)
    Container();
    LoadType* GetLoad();
    void correctContainerID(std::string B);    //Скорректировать ID контейнера
    
    friend std::ostream& operator<<(std::ostream& os, const Container& L);
};

Container::Container(std::string DestinationAddress, std::string IDNumber, LoadType* Load) {
    this->destinationAddress = DestinationAddress;
    this->IDNumber = IDNumber;
    this->load = Load;
}
Container::Container() {
    destinationAddress = "none";
    IDNumber = "none";
    load = nullptr;
}
LoadType* Container::GetLoad() {
    return load;
}
void Container::correctContainerID(std::string newIDNumber) {
    IDNumber = newIDNumber;
}

std::ostream& operator<<(std::ostream& os, const Container& object) {
    os << "Container{" 
        << "destinationAddress='" << object.destinationAddress << '\''
        << ", IDNumber='" << object.IDNumber << '\''
        << ", Load='" << "Load" << '\''
        << '}';
    return os;
}



class Team{     //Команда
private:
    int numberOfPeople;           //Кол-во членов команды
    std::string foremanName;      //Имя бригадира

public:
    Team(int NumberOfPeople, std::string ForemanName);    //Инициализация команды (конструктор)
    Team();
    int GetNumberOfPeople();

    friend std::ostream& operator<<(std::ostream& os, const Team& object);
};

Team::Team(int NumberOfPeople, std::string ForemanName) {
    this->numberOfPeople = NumberOfPeople;
    this->foremanName = ForemanName;
}
Team::Team() {
    numberOfPeople = 0;
    foremanName = "none";
}
int Team::GetNumberOfPeople() {
    return numberOfPeople;
}

std::ostream& operator<<(std::ostream& os, const Team& object) {
    os << "Team{" 
        << "foremanName='" << object.foremanName << '\''
        << ", numberOfPeople=" << object.numberOfPeople
        << '}';
    return os;
}



class Captain{     //Капитан
private:
    std::string name;             //Имя
    std::string licenseNumber;    //№ лицензии
    Team team;                    //Команда капитана

public:
    Captain(std::string Name, std::string LicenseNumber, Team Team);    //Инициализация капитана (конструктор)
    Captain();
    Team GetTeam();
    std::string GetLicense();

    friend std::ostream& operator<<(std::ostream& os, const Captain& object);
};

Captain::Captain(std::string Name, std::string LicenseNumber, Team Team) {
    this->name = Name;
    this->licenseNumber = LicenseNumber;
    this->team = Team;
}
Captain::Captain() {
    name = "none";
    licenseNumber = "none";
}
Team Captain::GetTeam() {
    return team;
}
std::string Captain::GetLicense() {
    return licenseNumber;
}

std::ostream& operator<<(std::ostream& os, const Captain& object) {
    os << "Captain{" 
        << "name='" << object.name << '\''
        << ", licenseNumber='" << object.licenseNumber << '\''
        << ", team=" << object.team
        << '}';
    return os;
}



class CaptainDatabase {   //База доступных капитанов (вспомог. класс)
private:
    Captain* Database[5];
    int arrayCounter;

public:
    CaptainDatabase() {
        arrayCounter = 0;
        *Database = {};
    }

    void AddEntry(Captain &newCaptain) {
        if (arrayCounter < 5) {
            Database[arrayCounter] = &newCaptain;
            arrayCounter++;
        }
    }

    Captain* GetCaptain(std::string licenseNumber) {
        for (int i = 0; i < arrayCounter; i++) {
            if (Database[i]->GetLicense() == licenseNumber) {
                return Database[i];
            }
        }
        return nullptr;
    }

}Database1;    //Объявление базы данных капитанов



class Ship {               //Корабль
private:
    Container container;       //Тип контейнеров, которые перевозит корабль
    int numberOfContainers;    //Кол-во контейнеров на корабле
    Captain* captain;          //Капитан корабля
    bool condition;            //Состояние корабля (приемлемое/нет)
    static int shipsTotal;     //Всего кораблей [static]

public:
    Ship(Container Container, int NumberOfContainers, std::string AssignedCaptainLicense, bool Condition);    //Инициализация корабля (конструктор)
    Ship();
    ~Ship();
    void AddLoad(int additionalLoad);    //Добавить груз
    void ChangeShipContainers(Container newContainer, int newNumberOfContainers);    //Перезагрузить корабль (другими контейнерами)
    void ChangeShipContainers(int newNumberOfContainers);                            //Перезагрузить корабль (только кол-во)

    static void OutTotalShips();      //Вывод shipsTotal

    friend std::ostream& operator<<(std::ostream& os, const Ship& object);

    friend int CalcFee(Ship& currShip);
    friend bool CheckViolations(Ship& currShip);

    Ship operator + (Ship Ship2)      //Перегрузка оператора '+'
    {
        if (this->container.GetLoad()->GetContentID() == Ship2.container.GetLoad()->GetContentID()) {
            return Ship(Ship2.container, (this->numberOfContainers + Ship2.numberOfContainers), Ship2.captain->GetLicense(), Ship2.condition);
        }
    }

    Ship& operator++ ()         //Перегрузка инкремента (префиксный)
    {
        numberOfContainers += 1;
        return *this;
    }

    Ship operator++ (int)       //Перегрузка инкремента (постфиксный)
    {
        Ship copy = *this;
        ++(*this);
        return copy;
    }

};

int Ship::shipsTotal = 0;      //Инициализация static переменной
void Ship::OutTotalShips() {   //Инициализация static метода
    std::cout << "Всего кораблей: " << shipsTotal << std::endl;
}

Ship::Ship(Container Container, int NumberOfContainers, std::string AssignedCaptainLicense, bool Condition) {
    try {
        if (NumberOfContainers < 0) {
            throw 1;
        }
    }
    catch (...) {
        std::cout << "Ошибка: Число контейнеров не должно быть меньше нуля.\n";
    }

    this->container = Container;
    this->numberOfContainers = NumberOfContainers;
    this->captain = Database1.GetCaptain(AssignedCaptainLicense);
    this->condition = Condition;
    shipsTotal++;
}
Ship::Ship() {
    numberOfContainers = 0;
    condition = false;
    captain = nullptr;
    shipsTotal++;
}
Ship::~Ship() {
    shipsTotal--;
}
void Ship::AddLoad(int additionalLoad) {
    numberOfContainers += additionalLoad;
}
void Ship::ChangeShipContainers(Container newContainer, int newNumberOfContainers) {
    container = newContainer;
    numberOfContainers = newNumberOfContainers;
}
void Ship::ChangeShipContainers(int newNumberOfContainers) {
    numberOfContainers = newNumberOfContainers;
}

std::ostream& operator<<(std::ostream& os, const Ship& object) {
    os << "Ship{" 
        << "container=" << object.container
        << ", numberOfContainers=" << object.numberOfContainers
        << ", captain=" << *object.captain
        << ", condition=" << object.condition
        << '}';
    return os;
}



bool MinToMaxWeightPredicate(LoadType* obj1, LoadType* obj2) {   //Предикат для сортировки по весу 1
    return (obj1->GetWeight() < obj2->GetWeight());
}

bool MaxToMinWeightPredicate(LoadType* obj1, LoadType* obj2) {   //Предикат для сортировки по весу 2
    return (obj1->GetWeight() > obj2->GetWeight());
}

struct IDSearchPredicate    //Предикат - условие поиска (Функтор)
{
    IDSearchPredicate(const std::string& a_wanted) : wanted(a_wanted) {}
    std::string wanted;
    bool operator()(LoadType* obj)
    {
        return obj->GetContentID().compare(wanted) == 0;
    }
};

class LoadRegistry {       //Класс реестра грузов
private:
    std::vector<LoadType*> vec;    //Реестр грузов
public:
    void AddElement(LoadType* obj);  //Добавление нового элемента
    void SortRegistryMinToMax();     //Сортировка вектора по весу от меньшего к большему
    void SortRegistryMaxToMin();     //Сортировка вектора по весу от большего к меньшему
    int SearhByID(std::string ID);   //Поиск элемента вектора с совпадающим ID

    friend std::ostream& operator<<(std::ostream& os, const LoadRegistry& obj);
    
}globalLoadRegistry;

void LoadRegistry::AddElement(LoadType* obj) {
    vec.push_back(obj);
}

void LoadRegistry::SortRegistryMinToMax() {
    sort(vec.begin(), vec.end(), MinToMaxWeightPredicate);
}

void LoadRegistry::SortRegistryMaxToMin() {
    sort(vec.begin(), vec.end(), MaxToMinWeightPredicate);
}

int LoadRegistry::SearhByID(std::string ID) {
    std::vector<LoadType*>::iterator it;
    it = find_if(vec.begin(), vec.end(), IDSearchPredicate(ID));
    if (it != vec.end()) {
        return std::distance(vec.begin(), it);
    }
    return -1;
}

std::ostream& operator<<(std::ostream& os, const LoadRegistry& obj) {
    for (int i = 0; i != obj.vec.size(); i++) {
        os << i << ". {ID=" << obj.vec[i]->GetContentID() << ", weight=" << obj.vec[i]->GetWeight() << "}\n";
    }
    return os;
}



bool CheckViolations(Ship& currShip) {     //Проверить нарушения
    if (!currShip.condition || currShip.captain->GetTeam().GetNumberOfPeople() > 20 || (currShip.numberOfContainers * currShip.container.GetLoad()->GetWeight() > 500)) {
        return true;
    }
    else {
        return false;
    }
}
int CalcFee(Ship& currShip) {          //Рассчитать плату за проход
    int fine = 0;
    if (CheckViolations(currShip)) {
        fine = 5000;
    }

    return (currShip.numberOfContainers * currShip.container.GetLoad()->GetWeight() + fine);
}


int main()
{
    setlocale(0, "");

    LoadType* Salmon = new LoadFish("1", 1000, "Salmon", 500);
    LoadType* Tables = new LoadFurniture("2", 100, "Tables", 50);
    Container contOne("-15 20 150", "1234567", Salmon);
    Container contTwo("-150 70 -10", "7654321", Tables);
    Team teamOne(10, "Joe");
    Team teamTwo(5, "Mark");
    Captain captainOne("Josh", "1234567", teamOne);
    Captain captainTwo("Jon", "7654321", teamTwo);

    Database1.AddEntry(captainOne);
    Database1.AddEntry(captainTwo);

    Ship shipOne(contOne, 10, "1234567", true);

    shipOne.OutTotalShips();

    std::cout << "Плата за проход 1: " << CalcFee(shipOne) << std::endl;

    shipOne.ChangeShipContainers(contTwo, 20);

    std::cout << "Плата за проход 2: " << CalcFee(shipOne) << std::endl;

    shipOne.AddLoad(10);

    std::cout << "Плата за проход 3: " << CalcFee(shipOne) << std::endl;

    Ship* shipTwo = new Ship (contTwo, 10, "7654321", false);

    shipOne.OutTotalShips();

    std::cout << "Плата за проход 4: " << CalcFee(*shipTwo) << std::endl;

    std::cout << "Корабль 2: " << *shipTwo << std::endl << std::endl;

    std::cout << "Работа с динамическим массивом объектов: \n";    ///
    Ship* shipArray = new Ship[3]{{contOne, 10, "1234567", true}, {contTwo, 15, "7654321", true}, {contOne, 20, "1234567", true}};

    std::cout << "Плата за проход 5: " << CalcFee(shipArray[2]) << std::endl;

    std::cout << "Корабль shipArray[0]: " << shipArray[0] << std::endl << std::endl;

    delete[] shipArray;

    std::cout << "Работа с массивом динамических объектов: \n";    ///

    Ship** shipArray2 = new Ship* [2] {&shipOne, shipTwo};

    shipArray2[0]->AddLoad(10);

    std::cout << "Плата за проход 6: " << CalcFee(*shipArray2[0]) << std::endl;

    Ship shipThree(contTwo, 15, "1234567", true);

    shipThree = shipOne + shipOne;
    std::cout << "Корабль 3: " << shipThree << std::endl << std::endl;

    shipOne++;
    ++shipOne;

    std::cout << "Корабль 1: " << shipOne << std::endl;

    Ship shipFour(contOne, -10, "1234567", true);

    Ship shipArrayDouble[2][2] = { {shipOne, {contOne, 20, "1234567", true}}, {{contTwo, 19, "7654321", true}, shipThree }};  //Работа с двойным массивом

    shipArrayDouble[1][0].AddLoad(19);

    delete[] shipArray2;
    delete shipTwo;

    std::cout << std::endl;

    LoadWhale BlueWhale("3", 3000, "Blue Whale", "2 x 1 x 1");
    LoadChairsInBoxes ChairsFour("4", 100, "Chairs 4", 50);
    LoadFurniture ChairsThree("5", 400, "Chairs 3", 10);

    ChairsFour = ChairsThree;

    std::cout << ChairsFour << std::endl;

    BlueWhale.ShowImportantMessages();

    std::cout << std::endl;

    LoadFish Carp("6", 1500, "Carp", 500);

    LoadFish* pTest = &Carp;
    pTest->NoteTransfer();
    pTest = &BlueWhale;
    pTest->NoteTransfer();

    LoadMoney<int> Dollars("7", 500, 500000);
    std::cout << std::endl << Dollars.GetSum() << std::endl;
    LoadMoney<std::string> Rubles("8", 100, "р1,000,000,000");
    std::cout << Rubles.GetSum() << std::endl;


////
    globalLoadRegistry.AddElement(Salmon);
    globalLoadRegistry.AddElement(Tables);
    globalLoadRegistry.AddElement(&Carp);
    globalLoadRegistry.AddElement(&BlueWhale);
    globalLoadRegistry.AddElement(&ChairsThree);
    globalLoadRegistry.AddElement(&Dollars);
    globalLoadRegistry.AddElement(&Rubles);

    std::cout << "\nИзначальное состояние реестра: \n" << globalLoadRegistry;
    std::cout << "Элемент с ID '1': " << globalLoadRegistry.SearhByID("1") << std::endl;

    globalLoadRegistry.SortRegistryMaxToMin();
    std::cout << "\nРеестр после сортировки max to min: \n" << globalLoadRegistry;
    std::cout << "Элемент с ID '1': " << globalLoadRegistry.SearhByID("1") << std::endl;

    globalLoadRegistry.SortRegistryMinToMax();
    std::cout << "\nРеестр после сортировки min to max: \n" << globalLoadRegistry;
    std::cout << "Элемент с ID '1': " << globalLoadRegistry.SearhByID("1") << std::endl;
    
    return 0;
}
