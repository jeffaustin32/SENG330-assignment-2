# SENG330-assignment-2

For this assignment scenario I chose to use the Gym example from the previous assignment. 

I have a base class for Equipment, and two derived classes: Treadmill and Bowflex.  There is a Equipment Manager to handle registering and producing prototypes.  Lastly, a Gym class to facilitate all gym related functionality: creating/removing equipment, importing/exporting equipment, and printing current equipment.

Version Control:
https://github.com/jeffaustin32/SENG330-assignment-2

Disclaimer: I have used MinGW on a Windows machine for all development.

Install application:
To install the application run “mingw32-make –f MakeFile all clean”.  This will link all the classes together and export the application as “main.exe”.  

Serialization:
I decided to try and roll my own which is capable of exporting and importing JSON.  The application will import/export to equipment.JSON in standard JSON format.

Testing:
I used a lightweight unit testing suite called Catch to test my application.
https://github.com/philsquared/Catch

Test install:
Navigate to the test folder and run “mingw32-make –f MakeFile all clean”.  This will link all the required classes in and export the test as “test.exe”.

