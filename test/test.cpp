#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../classes/Equipment.h"
#include "../classes/Treadmill.h"
#include "../classes/Bowflex.h"
#include "../classes/EquipmentManager.h"

TEST_CASE( "Initialize concrete implementation", "[Treadmill]" ) {
    SECTION( "Can create Treadmill without brand" ) {
		Treadmill* treadmill = new Treadmill();
        REQUIRE( treadmill->getBrand() == "" );
    }
    SECTION( "Can create Treadmill with brand" ) {
		Treadmill* treadmill = new Treadmill("Example");
        REQUIRE( treadmill->getBrand() == "Example" );
    }
}

TEST_CASE( "Prototypes", "[Prototype]" ) {
	EquipmentManager* equipmentManager = new EquipmentManager();
	REQUIRE( equipmentManager->prototypeCount() == 0);

	SECTION("Can register Treadmill prototype with no brand") {
		equipmentManager->registerPrototype("Treadmill", new Treadmill());
		REQUIRE( equipmentManager->prototypeCount() == 1);
	}

	SECTION("Can clone Bowflex prototype with brand") {
		equipmentManager->registerPrototype("Bowflex", new Bowflex("Example Brand"));
		REQUIRE( equipmentManager->prototypeCount() == 1);

		Bowflex* bowflex = dynamic_cast<Bowflex*>(equipmentManager->getPrototype("Bowflex"));
		REQUIRE( bowflex->getBrand() == "Example Brand");
	}
}