#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include <../boost/test/unit_test.hpp>

#include "../classes/Gym.h"
 
// Testing fixture 
struct gymFixture{
	Gym* gym;
	// setup function
	gymFixture(){
		gym = new Gym();
	};      

	// teardown function
	~gymFixture();    
};

int add(int i, int j)
{
    return i + j;
}
 

BOOST_AUTO_TEST_SUITE(Gym);
 
	BOOST_FIXTURE_TEST_CASE(Initialize)
	{
	    // Initialized

	}
 
BOOST_AUTO_TEST_SUITE_END();
 


BOOST_AUTO_TEST_SUITE(EquipmentManager);
 
	BOOST_FIXTURE_TEST_CASE()
	{
	    
	}
 
BOOST_AUTO_TEST_SUITE_END();