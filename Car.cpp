#include"Car.h"
#include<exception>
#include<stdexcept>
#include<sstream>
#include<chrono>
#include<iostream>

#define NOT_INITIALISED_ERROR "Car object is not fully initialized"

#define MAX_ENGINE_POWER 5000
#define MAX_WEIGHT 100000
#define FIRST_CAR_DATE 1886
#define CURRENT_YEAR 2021

#define COLOR_AMOUNT 7
#define LETTER_AMOUNT 3
#define PLATE_LENGTH 5

#define INFO_AMOUNT 8

namespace MyCar{

    using std::string;

    /** Class that checks if Car information is valid or if the object is initialized */
    class CarChecker{

        private:

            static const string possibleColors[COLOR_AMOUNT];

        public:

            // Checkers

            static bool checkColor(const string& color);
            static bool checkPlate(const string& plate);
            static bool checkEnginePower(unsigned int enginePower);
            static bool checkWeight(unsigned int weight);
            static bool checkManufactureYear(unsigned int manufactureYear);
            /** Checks if Car is initialized */
            static void checkInit(const Car &object, const string& file, int line);


    };

    // Private Car variables
    /** Lazy implementation of Car object. Holds all private information of Car object */
    class Car::CarPrivate{
        string manufacturer;
        string model;
        unsigned int manufactureYear;
        string color;
        string plate;
        string vin;
        unsigned int enginePower;
        unsigned int weight;

        unsigned int objectID;
        unsigned int fieldCount;

        unsigned static int id;

        friend class Car;
        friend std::ostream& operator<<(std::ostream& stream, const Car& object);
        friend std::istream& operator>>(std::istream& stream, Car& object);
        friend void CarChecker::checkInit(const Car &object, const string& file, int line);
    };

    unsigned int Car::CarPrivate::id = 0;
    unsigned int Car::instanceCount = 0;

    const string CarChecker::possibleColors[] = {

            "Red",
            "Blue",
            "Green",
            "Yellow",
            "Black",
            "White",
            "Grey"

    };

    // Checkers

    bool CarChecker::checkColor(const string& color){

        for(int i = 0; i < COLOR_AMOUNT; ++i){
            if(color == possibleColors[i]){
                return true;
            }
        }
        return false;

    }

    bool CarChecker::checkPlate(const string& plate){

        for(int i = 0; i < (int) plate.length(); ++i){
            if(i < LETTER_AMOUNT){
                if(!isupper(plate[i])){
                    return false;
                }
            }
            else{
                if(!isdigit(plate[i])){
                    return false;
                }
            }
            if(i > PLATE_LENGTH){
                return false;
            }
        }
        return true;
    }

    bool CarChecker::checkEnginePower(unsigned int enginePower){

        if(enginePower <= MAX_ENGINE_POWER){
            return true;
        }
        else{
            return false;
        }

    }

    bool CarChecker::checkWeight(unsigned int weight){

        if(weight <= MAX_WEIGHT){
            return true;
        }
        else{
            return false;
        }
    }

    bool CarChecker::checkManufactureYear(unsigned int manufactureYear){

        if(manufactureYear >= FIRST_CAR_DATE && manufactureYear <= CURRENT_YEAR){
            return true;
        }
        else{
            return false;
        }
    }

    void CarChecker::checkInit(const Car &object, const string& file, int line){ // const Car& is used, because field "fieldCount" needs to be checked
        if( (object.info == NULL) || (object.info->fieldCount != INFO_AMOUNT) ){
            std::stringstream ss;
            ss << NOT_INITIALISED_ERROR << " File: " << file<< " Line: " << line;
            throw incomplete_object(ss.str());
        }
    }

    // class Car methods

    Car::Car(){
        info = NULL;
    }

    Car::Car(const string& manufacturer, const string& model, unsigned int manufactureYear, const string& color,
             const string& plate, const string& vin, unsigned int enginePower, unsigned int weight)
    {
        info = new CarPrivate;
        setColor(color);
        setVin(vin);
        setPlate(plate);
        setEnginePower(enginePower);
        setWeight(weight);
        setManufacturer(manufacturer);
        setModel(model);
        setManufactureYear(manufactureYear);
        info->objectID = ++info->id;
        info->fieldCount = INFO_AMOUNT;
        ++instanceCount;
    }

    Car::Car(const Car& object){
        if(object.info == NULL){
            return;
        }
        info = new CarPrivate;
        this->setManufacturer(object.getManufacturer());
        this->setModel(object.getModel());
        this->setManufactureYear(object.getManufactureYear());
        this->setColor(object.getColor());
        this->setPlate(object.getPlate());
        this->setVin(object.getVin());
        this->setEnginePower(object.getEnginePower());
        this->setWeight(object.getWeight());
        this->setID(object.getID());
        this->info->fieldCount = object.info->fieldCount;
        ++instanceCount;
    }
    Car::~Car(){
        if(info != NULL){
            --instanceCount;
        }
        delete info;
    }

    string Car::toString() const{

        CarChecker::checkInit(*this, __FILE__, __LINE__);

        std::stringstream ss;
        ss << info->manufacturer << " " << info->model << " " << info->manufactureYear << " " << info->color << " " << info->plate << " "
         << info->vin << " " << info->enginePower << " " << info->weight;
        return ss.str();
    }

    // Getters

    string Car::getColor() const{
        CarChecker::checkInit(*this, __FILE__, __LINE__);
        return info->color;
    }

    string Car::getVin() const{
        CarChecker::checkInit(*this, __FILE__, __LINE__);
        return info->vin;
    }

    string Car::getPlate() const{
        CarChecker::checkInit(*this, __FILE__, __LINE__);
        return info->plate;
    }

    unsigned int Car::getEnginePower() const{
        CarChecker::checkInit(*this, __FILE__, __LINE__);
        return info->enginePower;
    }

    string Car::getModel() const{
        CarChecker::checkInit(*this, __FILE__, __LINE__);
        return info->model;
    }

    unsigned int Car::getWeight() const{
        CarChecker::checkInit(*this, __FILE__, __LINE__);
        return info->weight;
    }

    string Car::getManufacturer() const{
        CarChecker::checkInit(*this, __FILE__, __LINE__);
        return info->manufacturer;
    }

    unsigned int Car::getManufactureYear() const{
        CarChecker::checkInit(*this, __FILE__, __LINE__);
        return info->manufactureYear;
    }

    unsigned int Car::getID() const{
        CarChecker::checkInit(*this, __FILE__, __LINE__);
        return info->objectID;
    }

    unsigned int Car::getInstanceCount(){
        return instanceCount;
    }

    // Setters

    void Car::setColor(const string& color){
        if(CarChecker::checkColor(color)){
            if(info == NULL){
                info = new CarPrivate;
                info->fieldCount = 0;
                info->objectID = ++info->id;
                ++instanceCount;
            }
            if(info->fieldCount < INFO_AMOUNT){
                ++info->fieldCount;
            }
            this->info->color = color;
        }
        else{
            throw std::invalid_argument("Not available color");
        }
    }

    void Car::setVin(const string& vin){
        if(info == NULL){
            info = new CarPrivate;
            info->fieldCount = 0;
            info->objectID = ++info->id;
            ++instanceCount;
        }
        if(info->fieldCount < INFO_AMOUNT){
            ++info->fieldCount;
        }
        this->info->vin = vin;
    }

    void Car::setPlate(const string& plate){

        if(CarChecker::checkPlate(plate)){
            if(info == NULL){
                info = new CarPrivate;
                info->fieldCount = 0;
                info->objectID = ++info->id;
                ++instanceCount;
            }
            if(info->fieldCount < INFO_AMOUNT){
                ++info->fieldCount;
            }
            this->info->plate = plate;
        }
        else{
            throw std::invalid_argument("Not a valid plate (plate has to have only 3 capital letters followed by 3 numbers)");
        }
    }

    void Car::setEnginePower(unsigned int enginePower){

        if(CarChecker::checkEnginePower(enginePower)){
            if(info == NULL){
                info = new CarPrivate;
                info->fieldCount = 0;
                info->objectID = ++info->id;
                ++instanceCount;
            }
            if(info->fieldCount < INFO_AMOUNT){
                ++info->fieldCount;
            }
            this->info->enginePower = enginePower;
        }
        else{
            throw std::invalid_argument("Engine power out of range");
        }

    }
    void Car::setWeight(unsigned int weight){

        if(CarChecker::checkWeight(weight)){
            if(info == NULL){
                info = new CarPrivate;
                info->fieldCount = 0;
                info->objectID = ++info->id;
                ++instanceCount;
            }
            if(info->fieldCount < INFO_AMOUNT){
                ++info->fieldCount;
            }
            this->info->weight = weight;
        }
        else{
            throw std::invalid_argument("Weight out of range");
        }

    }

    void Car::setManufacturer(const string& manufacturer){
        if(info == NULL){
            info = new CarPrivate;
            info->fieldCount = 0;
            info->objectID = ++info->id;
            ++instanceCount;
        }
        if(info->fieldCount < INFO_AMOUNT){
            ++info->fieldCount;
        }
        this->info->manufacturer = manufacturer;
    }

    void Car::setModel(const string& model){
        if(info == NULL){
            info = new CarPrivate;
            info->fieldCount = 0;
            info->objectID = ++info->id;
            ++instanceCount;
        }
        if(info->fieldCount < INFO_AMOUNT){
            ++info->fieldCount;
        }
        this->info->model = model;
    }

    void Car::setManufactureYear(unsigned int manufactureYear){

        if(CarChecker::checkManufactureYear(manufactureYear)){
            if(info == NULL){
                info = new CarPrivate;
                info->fieldCount = 0;
                info->objectID = ++info->id;
                ++instanceCount;
            }
            if(info->fieldCount < INFO_AMOUNT){
                ++info->fieldCount;
            }
            this->info->manufactureYear = manufactureYear;
        }
        else{
            throw std::invalid_argument("Manufacture year out of range");
        }
    }

    void Car::setID(unsigned int id){
        if(info == NULL){
                info = new CarPrivate;
                info->fieldCount = 0;
                ++instanceCount;
        }
        this->info->objectID = id;
    }

    bool Car::operator==(const Car& object) const{

        CarChecker::checkInit(*this, __FILE__, __LINE__);

        if(info->objectID == object.getID()){
            return true;
        }
        else{
            return false;
        }

    }

    bool Car::operator!=(const Car& object) const{

        return !(*this == object);
    }

    bool Car::operator<(const Car& object) const{

        CarChecker::checkInit(*this, __FILE__, __LINE__);

        if(info->objectID < object.getID()){
            return true;
        }
        else{
            return false;
        }

    }

    bool Car::operator<=(const Car& object) const{

        CarChecker::checkInit(*this, __FILE__, __LINE__);

        if(info->objectID <= object.getID()){
            return true;
        }
        else{
            return false;
        }

    }

    bool Car::operator>(const Car& object) const{

        CarChecker::checkInit(*this, __FILE__, __LINE__);

        if(info->objectID > object.getID()){
            return true;
        }
        else{
            return false;
        }

    }

    bool Car::operator>=(const Car& object) const{

        CarChecker::checkInit(*this, __FILE__, __LINE__);

        if(info->objectID >= object.getID()){
            return true;
        }
        else{
            return false;
        }

    }

    Car& Car::operator++(){
        if(info == NULL){
            info = new CarPrivate;
            info->fieldCount = 0;
        }
        this->info->objectID = ++info->id;
        return *this;
    }

    Car Car::operator++(int){
        if(info == NULL){
            info = new CarPrivate;
            info->fieldCount = 0;
        }
        Car temp = *this;
        //temp = *this;
        this->info->objectID = ++info->id;
        return temp;
    }

    void Car::operator=(const Car &object){
        CarChecker::checkInit(object, __FILE__, __LINE__);
        if(this->info == NULL){
            info = new CarPrivate;
        }
        this->setManufacturer(object.getManufacturer());
        this->setModel(object.getModel());
        this->setManufactureYear(object.getManufactureYear());
        this->setColor(object.getColor());
        this->setPlate(object.getPlate());
        this->setVin(object.getVin());
        this->setEnginePower(object.getEnginePower());
        this->setWeight(object.getWeight());
        this->setID(object.getID());
        this->info->fieldCount = object.info->fieldCount;
        ++instanceCount;

    }

    bool Car::equals(const Car& object){
        if(this->getManufacturer() == object.getManufacturer() && this->getModel() == object.getModel() && this->getManufactureYear() == object.getManufactureYear() &&
           this->getColor() == object.getColor() && this->getPlate() == object.getPlate() && this->getVin() == object.getVin() && this->getEnginePower() == object.getEnginePower() &&
           this->getWeight() == object.getWeight() && this->getID() == object.getID()){
            return true;
        }else{
            return false;
        }

    }

    void Car::upgradeEngine(unsigned int value){
        if(CarChecker::checkEnginePower(value)){
            setEnginePower(getEnginePower() + value);
        }
    }
    // << and >> operators
    std::ostream& operator<<(std::ostream& stream, const Car& object){
        CarChecker::checkInit(object, __FILE__, __LINE__);
        stream << object.toString();
        return stream;
    }

    std::istream& operator>>(std::istream& stream, Car& object){
        Car temp;
        temp.info = new Car::CarPrivate;
        stream >> temp.info->manufacturer >> temp.info->model >> temp.info->manufactureYear >> temp.info->color >> temp.info->plate >> temp.info->vin >> temp.info->enginePower >> temp.info->weight;
        ++Car::instanceCount;
        Car temp2;
        temp2.info = new Car::CarPrivate;
        temp2.info->fieldCount = 0;

        if(object.info != NULL){
            temp2.info->objectID = object.info->objectID;
        }else{
            object.info = new Car::CarPrivate;
            temp2.info->objectID = ++Car::CarPrivate::id;
        }

        temp2.setManufacturer(temp.info->manufacturer);
        temp2.setModel(temp.info->model);
        temp2.setManufactureYear(temp.info->manufactureYear);
        temp2.setColor(temp.info->color);
        temp2.setPlate(temp.info->plate);
        temp2.setVin(temp.info->vin);
        temp2.setEnginePower(temp.info->enginePower);
        temp2.setWeight(temp.info->weight);
        object = temp2;
        ++Car::instanceCount;

        return stream;

    }

}
