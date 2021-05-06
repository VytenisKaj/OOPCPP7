#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include<string>

namespace MyCar{

    /** This is a class that save information about a car object */
    class Car{

        private:

            class CarPrivate;
            CarPrivate *info;
            /** Counting instances of the object */
            unsigned static int instanceCount;

        public:
            /** Lazy initialization. Creates an empty object that need to be initialized with setters >> operator or full constructor to be usable */
            Car();
            /** Creates full object that can be used */
            Car(const std::string& manufacturer, const std::string& model, unsigned int manufactureYear, const std::string& color,
                const std::string& plate, const std::string& vin, unsigned int enginePower, unsigned int weight);
            Car(const Car& object);
            ~Car();

            // Getters
            /** Returns color of initialized Car object */
            std::string getColor() const;
            /** Returns VIN of initialized Car object */
            std::string getVin() const;
            /** Returns plate of initialized Car object */
            std::string getPlate() const;
            /** Returns engine power of initialized Car object */
            unsigned int getEnginePower() const;
            /** Returns weight of initialized Car object */
            unsigned int getWeight() const;
            /** Returns manufacturer of initialized Car object */
            std::string getManufacturer() const;
            /** Returns model of initialized Car object */
            std::string getModel() const;
            /** Returns manufacture year of initialized Car object */
            unsigned int getManufactureYear() const;
            /** Returns ID of initialized Car object */
            unsigned int getID() const;
            static unsigned int getInstanceCount();

            // Setters
            /** Sets color of a Car object */
            void setColor(const std::string& color);
            /** Sets VIN of a Car object */
            void setVin(const std::string& vin);
            /** Sets plate of a Car object */
            void setPlate(const std::string& plate);
            /** Sets engine power of a Car object */
            void setEnginePower(unsigned int enginePower);
            /** Sets weight of a Car object */
            void setWeight(unsigned int weight);
            /** Sets manufacturer of a Car object */
            void setManufacturer(const std::string& manufacturer);
            /** model of a Car object */
            void setModel(const std::string& model);
            /** Sets manufacture year of a Car object */
            void setManufactureYear(unsigned int manufactureYear);
        private:
            void setID(unsigned int id);

        public:
            /** Creates output format of Car object */
            std::string toString() const;

            // Comparison operators (compares IDs)
            /** Compares IDs of 2 objects */
            bool operator==(const Car& object) const;
            bool operator!=(const Car& object) const;
            bool operator<(const Car& object) const;
            bool operator<=(const Car& object) const;
            bool operator>(const Car& object) const;
            bool operator>=(const Car& object) const;

            // Gives new unused ID
            /** Gives an object new unused ID*/
            Car& operator++();
            /** Gives an object new unused ID, returns copy of old object */
            Car operator++(int);

            // Copies objects
            /** Copies object*/
            void operator=(const Car& object);

            /** Compares if objects are EXACTLY the same*/
            bool equals(const Car& object);

            void upgradeEngine(unsigned int value);

            /** Outputs Car object into stream using toString() format */
            friend std::ostream& operator<<(std::ostream& stream, const Car& object);
            /** Reads input from stream, strong safety guaranteed*/
            friend std::istream& operator>>(std::istream& stream, Car& object);

            friend class CarChecker;
            friend class CarPrivate;
    };

    // Exception if object is incomplete
    /** Exception class that is thrown, when not initialized object is being used*/
    class incomplete_object: public std::exception{
        private:
            std::string msg;
        public:
            incomplete_object(const std::string &msg){
                this->msg = msg;
            }
            virtual const char* what() const noexcept{
                return msg.c_str();
            }
    };
}
#endif // CAR_H_INCLUDED
