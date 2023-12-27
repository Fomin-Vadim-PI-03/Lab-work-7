import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;


class HelperClass{      //Вспомогательный класс
	private HelperClass() throws Exception {
		throw new Exception("Ошибка: Класс не должен иметь экземпляров.");
	}
	public static int IntegerValidation(int value) {    //Метод для корректировки значений int в случае ошибки
		if(value < 0) {
			return 0;
		}else {
			return value;
		}
	}
}

interface SensitiveLoad{       //Интерфейс - Хрупкий груз
	void ShowImportantMessages();     //Вывод важных примечаний о типе груза
    void NoteTransfer();              //Примечание о перевозке
}

abstract class LoadType {       //Абстрактный класс - Типы груза
    protected String ID;          //ID Груза
    protected int weight;         //Вес

    public LoadType(String ID, int weight) {
        this.ID = ID;
        this.weight = weight;
    }

    public LoadType() {
        this.ID = "none";
        this.weight = 0;
    }

    public int GetWeight() {              //Получить значение weight
        return weight;
    }

    public String GetContentID() {        //Получить значение ID
        return ID;
    }
}


class LoadFish extends LoadType {         //Груз: Рыба
    protected String fishName;        //Наименование рыбы (Лосось, карп...)
    private int count;                //Кол-во рыбы

    public LoadFish(String ID, int weight, String fishName, int count) {
        super(ID, weight);
        this.fishName = fishName;
        this.count = count;
    }

    public LoadFish(String ID, int weight, String fishName) {
        super(ID, weight);
        this.fishName = fishName;
        this.count = 0;
    }

    public LoadFish() {
        super();
        this.fishName = "none";
        this.count = 0;
    }

    @Override
    public String toString() {
        return "Fish{" +
                "ID='" + ID + '\'' +
                ", fishName='" + fishName + '\'' +
                ", weight=" + weight +
                ", count=" + count +
                '}';
    }
}


class LoadWhale extends LoadFish implements SensitiveLoad {         //Груз: Кит
    protected String dimensions;        //Размер кита (Д x Ш x В)

    public LoadWhale(String ID, int weight, String fishName, String dimensions) {
        super(ID, weight, fishName);
        this.dimensions = dimensions;
    }

    public LoadWhale() {
        this.ID = "none";
        this.weight = 0;
        this.fishName = "none";
        this.dimensions = "none";
    }
    
    @Override
    public void ShowImportantMessages() {     //Вывод важных примечаний о типе груза
    	NoteTransfer();
    }

    @Override
    public void NoteTransfer() {      //Примечания о перевозке
        System.out.println("Грузу типа Кит \'" + fishName + "\' необходимы доп. крепительные ремни при перевозке.");
        System.out.println("Грузу \'" + fishName + "\' необходима низкая температура при перевозке.");
    }

    @Override
    public String toString() {
        return "Whale{" +
                "ID='" + ID + '\'' +
                ", fishName='" + fishName + '\'' +
                ", weight=" + weight +
                '}';
    }
}


class LoadFurniture extends LoadType {         //Груз: Мебель
    protected String furnitureName;                //Наименование мебели
    protected int count;                           //Кол-во мебели

    public LoadFurniture(String ID, int weight, String furnitureName, int count) {
        super(ID, weight);
        this.furnitureName = furnitureName;
        this.count = count;
    }

    public LoadFurniture() {
        super();
        this.furnitureName = "none";
        this.count = 0;
    }

    public int GetOneItemWeight() {             //Получение веса одного предмета
        return weight / count;
    }

    public int GetOneItemWeightSpecial() {      //Получение веса одного предмета марки 'Special' (без упаковки)
        return (int) (weight / count * 0.85);
    }

    @Override
    public String toString() {
        return "Furniture{" +
                "ID='" + ID + '\'' +
                ", furnitureName='" + furnitureName + '\'' +
                ", weight=" + weight +
                ", count=" + count +
                '}';
    }
}

class LoadChairsInBoxes extends LoadFurniture {         //Груз: Стулья в коробках
    public LoadChairsInBoxes(String ID, int weight, String furnitureName, int count) {
        super(ID, weight, furnitureName, count);
    }
    
    public LoadChairsInBoxes() {
        super();
    }
    
    @Override
    public int GetOneItemWeight() {              //Перегрузка с вызовом метода базового класса (Получение веса одного предмета без коробки)
        return (int)(super.GetOneItemWeight() * 0.9);
    }
    
    @Override
    public int GetOneItemWeightSpecial() {       //Перегрузка без вызова метода базового класса (Получение веса одного предмета марки 'Special' без коробки)
        return (int)(weight / count * 0.9 * 0.85);
    }
    
	@Override
    public String toString() {
        return "ChairsInBoxes{" +
            "ID='" + ID + '\'' +
            ", furnitureName='" + furnitureName + '\'' +
            ", weight=" + weight +
            ", count=" + count +
            '}';
    }
}


class LoadMoney<T> extends LoadType implements SensitiveLoad {        //Груз: Деньги
    private T sum;       //Сумма денег

    public LoadMoney(String ID, int weight, T sum) {
        super(ID, weight);
        this.sum = sum;
    }

    public LoadMoney() {
        super();
        this.sum = null;
    }

    public T GetSum() {    //Получить значение sum
        return sum;
    }
    
    @Override
    public void ShowImportantMessages() {     //Вывод важных примечаний о типе груза
    	NoteTransfer();
    	System.out.println("Состояние груза отслеживается в реальном времени.");
    }

    @Override
    public void NoteTransfer() {      //Примечание о перевозке
        System.out.println("Данному грузу необходима низкая влажность.");
    }
    
    @Override
    public String toString() {
        return "ChairsInBoxes{" +
            "ID='" + ID + '\'' +
            ", weight=" + weight +
            ", sum=" + sum +
            '}';
    }
}


class Container {    //Контейнер
    private String destinationAddress;    //Адрес назначения
    private String IDNumber;              //Идентификационный номер
    private LoadType load;                    //Груз в контейнере

    public Container(String destinationAddress, String IDNumber, LoadType load) {    //Инициализация контейнера (конструктор)
        this.destinationAddress = destinationAddress;
        this.IDNumber = IDNumber;
        this.load = load;
    }

    public Container() {
        destinationAddress = "none";
        IDNumber = "none";
    }

    public LoadType GetLoad() {
        return load;
    }

    public void CorrectContainerID(String newIDNumber) {    //Скорректировать ID контейнера
        IDNumber = newIDNumber;
    }

    @Override
    public String toString() {
   	return "Container{" 
            + "destinationAddress='" + destinationAddress + '\''
            + ", IDNumber='" + IDNumber + '\''
   			+ ", load=" + load.toString()
   			+ '}';
   }
}

class Team implements Cloneable{     //Команда
    private int numberOfPeople;           //Кол-во членов команды
    private String foremanName;           //Имя бригадира

    public Team(int numberOfPeople, String foremanName) {    //Инициализация команды (конструктор)
    	this.numberOfPeople = numberOfPeople;
    	this.foremanName = foremanName;
    }

    public Team() {
        numberOfPeople = 0;
        foremanName = "none";
    }

    public int GetNumberOfPeople() {
        return numberOfPeople;
    }
    
    @Override
    public Team clone() {     //Поверхностное клонирование
        try {
            return (Team) super.clone();
        } catch (CloneNotSupportedException e) {
            throw new AssertionError();
        }
    }

    @Override
    public String toString() {
   	return "Team{" 
            + "foremanName='" + foremanName + '\''
   			+ ", numberOfPeople=" + numberOfPeople
   			+ '}';
   }
}

class Captain implements Cloneable{     //Капитан
    private String name;             //Имя
    private String licenseNumber;    //№ лицензии
    private Team team;               //Команда капитана

    public Captain(String name, String licenseNumber, Team team) {    //Инициализация капитана (конструктор)
    	this.name = name;
    	this.licenseNumber = licenseNumber;
    	this.team = team;
    }

    public Captain() {
        name = "none";
        licenseNumber = "none";
    }

    public Team GetTeam() {
        return team;
    }

    public String GetLicense() {
        return licenseNumber;
    }
    
    @Override
    public Captain clone() {    //Глубокое клонирование
        Captain cloned;
        try {
            cloned = (Captain) super.clone();
        } catch (CloneNotSupportedException e) {
            throw new AssertionError();
        }
        cloned.team = this.team.clone();
        return cloned;
    }

    @Override
    public String toString() {
   	return "Captain{" 
            + "name='" + name + '\''
            + ", licenseNumber='" + licenseNumber + '\''
   			+ ", team=" + team.toString()
   			+ '}';
   }
}

class CaptainDatabase {       //База доступных капитанов (вспомог. класс)
    private List<Captain> Database;
    private int arrayCounter;

    public CaptainDatabase() {
        Database = new ArrayList<>();
        arrayCounter = 0;
    }

    public void AddEntry(Captain newCaptain) {
        Database.add(newCaptain);
        arrayCounter++;
    }

    public Captain GetCaptain(String licenseNumber) {
        for (int i = 0; i < arrayCounter; i++) {
            if (Database.get(i).GetLicense().equals(licenseNumber)) {
                return Database.get(i);
            }
        }
        return null;
    }
}

class Ship {               //Корабль
    private Container container;         //Тип контейнеров, которые перевозит корабль
    private int numberOfContainers;      //Кол-во контейнеров на корабле
    private Captain captain;             //Капитан корабля
    private boolean condition;           //Состояние корабля (приемлемое/нет)
    private static int shipsTotal = 0;   //Всего кораблей [static]

    public Ship(Container container, int numberOfContainers, String assignedCaptainLicense, boolean condition, CaptainDatabase Database1) {    //Инициализация корабля (конструктор)
    	try {
    	    if (numberOfContainers < 0) {
    	        throw new Exception();
    	    }
    	} catch (Exception e) {
    	    System.out.println("Ошибка: Число контейнеров не должно быть меньше нуля.");
    	}
    	
    	this.container = container;
    	this.numberOfContainers = numberOfContainers;
    	this.captain = Database1.GetCaptain(assignedCaptainLicense);
        this.condition = condition;
        shipsTotal++;
    }

    public Ship() {
        numberOfContainers = 0;
        condition = false;
        captain = null;
        shipsTotal++;
    }
    
    public void AddLoad(int additionalLoad) {    //Добавить груз
        numberOfContainers += additionalLoad;
    }

    public void ChangeShipContainers(Container newContainer, int newNumberOfContainers) {    //Перезагрузить корабль (другими контейнерами)
        container = newContainer;
        numberOfContainers = newNumberOfContainers;
    }
    
    public void ChangeShipContainers(int newNumberOfContainers) {                            //Перезагрузить корабль (только кол-во)
        numberOfContainers = newNumberOfContainers;
    }

    public boolean CheckViolations() {     //Проверить нарушения
        if (!condition || captain.GetTeam().GetNumberOfPeople() > 20 || (numberOfContainers * container.GetLoad().GetWeight() > 500)) {
            return true;
        } else {
            return false;
        }
    }

    public int CalcFee() {       //Рассчитать плату за проход
        int fine = 0;
        if (CheckViolations()) {
            fine = 5000;
        }
        return (HelperClass.IntegerValidation(numberOfContainers * container.GetLoad().GetWeight() + fine));
    }
    
    public static void OutTotalShips() {      //Вывод shipsTotal
    	System.out.printf("Всего кораблей: %d\n", shipsTotal);
    }
    
    @Override
    public String toString() {
   	return "Ship{" 
   			+ "container=" + container.toString()
            + ", numberOfContainers=" + numberOfContainers
   			+ ", captain=" + captain.toString()
   			+ ", condition=" + condition
   			+ '}';
   }
}


class LoadRegistry {       //Класс реестра грузов
    private List<LoadType> list = new ArrayList<>();    //Реестр грузов

    public void AddElement(LoadType obj) {   //Добавление нового элемента
        list.add(obj);
    }

    public void SortRegistryMinToMax() {     //Сортировка вектора по весу от меньшего к большему
        list.sort(Comparator.comparing(LoadType::GetWeight));
    }

    public void SortRegistryMaxToMin() {     //Сортировка вектора по весу от большего к меньшему
        list.sort(Comparator.comparing(LoadType::GetWeight).reversed());
    }

    public int SearchByID(String ID) {       //Поиск элемента вектора с совпадающим ID
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i).GetContentID().equals(ID)) {
                return i;
            }
        }
        return -1;
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < list.size(); i++) {
            sb.append(i)
              .append(". {ID=")
              .append(list.get(i).GetContentID())
              .append(", weight=")
              .append(list.get(i).GetWeight())
              .append("}\n");
        }
    return sb.toString();
    }
}



public class HelloWorld {
	public static void main(String[] args) {
        CaptainDatabase globalDatabase1 = new CaptainDatabase();
        LoadRegistry globalLoadRegistry = new LoadRegistry();
        
        LoadType Salmon = new LoadFish("1", 1000, "Salmon", 500);
        LoadType Tables = new LoadFurniture("2", 100, "Tables", 50);
        Container contOne = new Container("-15 20 150", "1234567", Salmon);
        Container contTwo = new Container("-150 70 -10", "7654321", Tables);
        Team teamOne = new Team(10, "Joe");
        Team teamTwo = new Team(5, "Mark");
        Captain captainOne = new Captain("Josh", "1234567", teamOne);
        Captain captainTwo = new Captain("Jon", "7654321", teamTwo);
        globalDatabase1.AddEntry(captainOne);
        globalDatabase1.AddEntry(captainTwo);
        
        Ship.OutTotalShips();
        
        Ship shipOne = new Ship(contOne, 10, "1234567", true, globalDatabase1);
        
        System.out.print(shipOne + "\n\n");
        
        Ship.OutTotalShips();
        
        System.out.printf("Плата за проход 1: %d\n", shipOne.CalcFee());
        
        shipOne.ChangeShipContainers(contTwo, 20);
        System.out.printf("Плата за проход 2: %d\n", shipOne.CalcFee());
        
        shipOne.AddLoad(10);
        System.out.printf("Плата за проход 3: %d\n", shipOne.CalcFee());
        
        Ship shipTwo = new Ship(contTwo, 10, "7654321", false, globalDatabase1);
        System.out.printf("Плата за проход 4: %d\n", shipTwo.CalcFee());
        
        System.out.print(shipTwo + "\n\n");
        
        Ship[] shipArray = new Ship[]{new Ship(contOne, 10, "1234567", true, globalDatabase1), shipTwo, new Ship(contOne, 20, "1234567", true, globalDatabase1)};
        System.out.printf("Плата за проход 5: %d\n", shipArray[2].CalcFee());
        
        System.out.print(shipArray[0] + "\n\n");
        
        Ship.OutTotalShips();
        
        Ship shipThree = new Ship(contOne, -10, "1234567", true, globalDatabase1);
        
        Ship[][] shipArrayDouble = {
                {shipOne, new Ship(contOne, 20, "1234567", true, globalDatabase1)},
                {new Ship(contTwo, 19, "7654321", true, globalDatabase1), shipThree}
        };

        shipArrayDouble[0][1].AddLoad(19);
        System.out.print(shipArrayDouble[0][1] + "\n\n");
        
////
        LoadWhale BlueWhale = new LoadWhale("3", 3000, "Blue Whale", "2 x 1 x 1");
        LoadChairsInBoxes ChairsFour = new LoadChairsInBoxes("4", 100, "Chairs 4", 50);

        System.out.print(ChairsFour + "\n");

        BlueWhale.ShowImportantMessages();

        System.out.print("\n");

        LoadMoney<Integer> Dollars = new LoadMoney<>("5", 500, 500000);
        System.out.println(Dollars.GetSum());

        LoadMoney<String> Rubles = new LoadMoney<>("6", 100, "р1,000,000,000");
        System.out.println(Rubles.GetSum());
        
////
        globalLoadRegistry.AddElement(Salmon);
        globalLoadRegistry.AddElement(Tables);
        globalLoadRegistry.AddElement(BlueWhale);
        globalLoadRegistry.AddElement(ChairsFour);
        globalLoadRegistry.AddElement(Dollars);
        globalLoadRegistry.AddElement(Rubles);
        
        System.out.println("\nИзначальное состояние реестра: \n" + globalLoadRegistry);
        System.out.println("Элемент с ID '1': " + globalLoadRegistry.SearchByID("1"));
        
        globalLoadRegistry.SortRegistryMaxToMin();
        System.out.println("\nРеестр после сортировки max to min: \n" + globalLoadRegistry);
        System.out.println("Элемент с ID '1': " + globalLoadRegistry.SearchByID("1"));
        
        globalLoadRegistry.SortRegistryMinToMax();
        System.out.println("\nРеестр после сортировки min to max: \n" + globalLoadRegistry);
        System.out.println("Элемент с ID '1': " + globalLoadRegistry.SearchByID("1"));
        
        System.out.println("Завершение работы.");
    }
}
