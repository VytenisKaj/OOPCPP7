#include <iostream>
#include "Car.h"

using namespace MyCar;
using namespace std;

int main()
{
    try{
        cout << Car::getInstanceCount() << endl;
        Car car1("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
        Car car2("Subaru","Impreza",2013,"Grey","ABC123","JPKSKD12612",110,1950);
        Car car4;
        cout << Car::getInstanceCount() << endl;
        {
            Car temp("Audi","100",1998,"Red","AGH354","VWksadjasf222151",128,2500);
            cout << Car::getInstanceCount() << endl;
            cout << temp.getID() <<endl;
            car4 = temp;
            cout << Car::getInstanceCount() << endl;
        }

        cout << "Car 2 color " << car2.getColor() << endl;
        cout << "Car 2 engine power " << car2.getEnginePower() << " KW" << endl;
        cout << "Car 2 manufacturer " << car2.getManufacturer() << endl;
        cout << "Car 2 manufacture year " << car2.getManufactureYear() << endl;
        cout << "Car 4 model " << car4.getModel() << endl;
        cout << "Car 4 plate " << car4.getPlate() << endl;
        cout << "Car 4 vin " << car4.getVin() << endl;
        cout << "Car 4 weight " << car4.getWeight() << " KG" << endl;
        cout << "Car 4 ID " << car4.getID() << endl;

        cout << Car::getInstanceCount() << endl;

        cout << car1 << endl;
        cout << "manufacturer model year color plate vin power weight" << endl;
        //cin >> car1;
        //cout << car1 << endl;
        cout << car2 << endl;
        cout << car4 << endl;
        car1.setManufacturer("Ferrari");
        car1.setColor("Red");
        car1.setVin("bifhdksom256482");
        car1.setManufactureYear(2018);
        car1.setEnginePower(460);
        car1.setModel("458");
        car1.setWeight(1800);
        cout << car1 << endl; // ID has not changed, because car1 object did not change
        car1.setPlate("BBB222");
        car1++; // gives new unused ID
        cout << car1.getID() << endl;
        Car car6;
       // cout << "manufacturer model year color plate vin power weight" << endl;
       // cin >> car6;
        car6.setManufacturer("Audi");
        car6.setColor("Blue");
        car6.setVin("asdfsf222fasf");
        car6.setManufactureYear(2015);
        car6.setEnginePower(500);
        car6.setModel("R8");
        car6.setWeight(1750);
        car6.setPlate("VVV555");
        cout << car6 << endl;
        cout << Car::getInstanceCount() << endl;



    }
    catch(invalid_argument& err){
        cerr << "Invalid argument: " << err.what() << endl;
    }
    catch(logic_error& err){
        cerr << "Logic error: " << err.what() <<endl;
    }
    catch(incomplete_object& err){
        cerr << err.what() << endl;;
    }
    catch(...){
        cerr << "Unknown exception detected" << endl;
    }
    cout << Car::getInstanceCount() << endl;
    return 0;
}
