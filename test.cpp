#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Car.h"
#include<sstream>

    using namespace MyCar;

TEST_CASE("#SET") {

    Car test("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    REQUIRE(test.getManufacturer() == "Porsche");
    REQUIRE(test.getModel() == "Panamera");
    REQUIRE(test.getManufactureYear() == 2020);
    REQUIRE(test.getColor() == "Black");
    REQUIRE(test.getPlate() == "CCC222");
    REQUIRE(test.getVin() == "jbsajbc2211s");
    REQUIRE(test.getEnginePower() == 350);
    REQUIRE(test.getWeight() == 2000);
    test.setManufacturer("Audi");
    test.setModel("R8");
    test.setManufactureYear(2015);
    test.setColor("Blue");
    test.setPlate("AAA325");
    test.setVin("vinvin2255");
    test.setEnginePower(500);
    test.setWeight(1500);
    REQUIRE(test.getManufacturer() == "Audi");
    REQUIRE(test.getModel() == "R8");
    REQUIRE(test.getManufactureYear() == 2015);
    REQUIRE(test.getColor() == "Blue");
    REQUIRE(test.getPlate() == "AAA325");
    REQUIRE(test.getVin() == "vinvin2255");
    REQUIRE(test.getEnginePower() == 500);
    REQUIRE(test.getWeight() == 1500);

}

TEST_CASE("#AUTO_ID"){

    Car test1("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    REQUIRE(test1.getID() == 2); // ID is 2, because object was created previously in other TEST_CASE
    Car test2("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    Car test3("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    REQUIRE(test2.getID() == test1.getID() + 1);
    REQUIRE(test3.getID() == test2.getID() + 1);
    REQUIRE(test3.getID() == test1.getID() + 2);

}

TEST_CASE("#CMP"){

    Car test1("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    Car test2("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    REQUIRE(test1 < test2);
    REQUIRE_FALSE(test1 == test2);
    REQUIRE( (test1 != test2) != (test1 == test2) );
    REQUIRE( (test1 <= test2) == ( (test1 < test2) || (test1 == test2) ) );
    REQUIRE( (test1 > test2) != ( (test1 < test2) || (test1 == test2) ) );
    REQUIRE( (test1 >= test2) == ( (test1 == test2) || (test1 > test2) ) );
    REQUIRE( ( (test1 <= test2) && (test1 >= test2) ) == (test1 == test2) );

}

TEST_CASE("#STREAM"){
    Car test("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    Car test2;
    std::stringstream ss;
    ss << test;
    ss >> test2;
    REQUIRE(test2.toString() == test.toString());

}

TEST_CASE("#PRE_POST"){
    Car test1("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    Car test1Copy;// = test1;
    test1Copy = test1;
    Car testPost;
    testPost = test1++;
    Car testPre;
    testPre = ++test1;
    REQUIRE(testPre.equals(test1));
    REQUIRE(testPost.equals(test1Copy));

}

TEST_CASE("#THROW"){

    Car test("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    Car testCopy = test;
    REQUIRE_THROWS(test.setPlate("This is not a valid plate"));
    REQUIRE_THROWS_AS(test.setPlate("This is not a valid plate"), std::invalid_argument);
    REQUIRE_THROWS_AS_MESSAGE(test.setPlate("This is not a valid plate"), std::invalid_argument, "Not a valid plate (plate has to have only 3 capital letters followed by 3 numbers)");
    REQUIRE(test.equals(testCopy));

}

TEST_CASE("#COPY"){
    Car test1("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    Car test2 = test1;
    REQUIRE(test1.getColor() == test2.getColor());
    test1.setColor("Blue");
    REQUIRE(test1.getColor() != test2.getColor());
    test2.setColor("Blue");
    REQUIRE(test1.getColor() == test2.getColor());
    test1.setColor("Black");
    REQUIRE(test1.getColor() != test2.getColor());

}



TEST_CASE("#LEAK"){
    REQUIRE(Car::getInstanceCount() == 0);
    {
        Car test1("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
        Car test2 = test1;
        REQUIRE(Car::getInstanceCount() == 2);
        Car test3;
        REQUIRE(Car::getInstanceCount() == 2);
    }
    REQUIRE(Car::getInstanceCount() == 0);

}

TEST_CASE("#CUSTOM"){

    int value = 50;
    Car test1("Porsche","Panamera",2020,"Black","CCC222","jbsajbc2211s",350,2000);
    int power = test1.getEnginePower();
    test1.upgradeEngine(value);
    REQUIRE(test1.getEnginePower() == power + value);

}
