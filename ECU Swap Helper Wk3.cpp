//Jonathan Anderson
//CSC 215
//03/03/25
//Assignment 2.1: learning Functions with Interactive Simulation.

//Create an Interactive Simulation Application.
//Create a C++ program that uses 5 or more functions.
//Control all your functions through the main function.
//Pass and return parameters to your functions.
//Your program must do something and be an interactive simulation, it must not just demo functions.
//Have fun!

//As discussed with the Prof... I will be using this C++ class to create a program that helps me design an ECU
// for my project car. In this, I will have a main menu and several sub menus. The main menu will allow the selection
//of a Conversion Program to convert pressures, fuel flows, gear ratios, and other needed conversions/calculations. This will satisfy the
//requirements for the Functions 2.1 assignment. Another menu will allow the entry of an ECU pinout, a vehicle pinout, and an engine pinout
//to include wire gauge, color, signal type, voltage and other parameters for the systems. This program will satisfy the assigment related to arrays, vectors
// and maps. This will alsu utilize pointers to move throught the tables of data and match the values. Lastly, the data will be stored in either
// a CSV or .db for recalling. In the final project, I will tie all of this together. I dont know if I will have enough time to turn this into an
//actual .exe with all of the dependencies inside and a GUI... but I will tie it all into a working program.
// I also intend to load this onto my github under the repo CSC215

//First I will start with the menus and functions for the conversion. First will eb the main menu. I will use case statements for the menus. 

#include <iostream>
#include <fstream> //addint these for lesson 3
#include <vector>
#include <string>
#include <sstream>
using namespace std;
// I will be keeping main at the top of my program, so I will prototype my functions so that they can come below main

// I am not sure where to put the struct??

// Define a structure for pin mapping entries
struct PinMapping {
	int row;
	string device;
	string wireColor;
	string signalType;
	string direction;
	string destination;
};


// maybe read the requirements before finishing the assignment...
int globalVarCounter = 0;

void conversionMenu();
void pinMappingMenu();
//void ecmToolsMenu();
//void physicsCalculators();

//declarations for the conversion functions.
void psiToBar();
void barToPsi();
void psiToKpa();
void kpaToPsi();
void lbHrToCcMin();
void ccMinToLbHr();
void fahrenheitToCelsius();
void celsiusToFahrenheit();
void afrToLambda();
void lambdaToAfr();
void injectorSizeCalculator();
void globalVarFunc(int engineCode);
void injectorFlowAtNewPressure();
void horsepowerByInjectorSize();
void injectorFlowRateByDutyCycle();
void turboPressureRatio();
void returnToMainMenu();

// function prototype declarations for the pin mapping

void pinMappingMenu();
void handleComponentSelection(string filename);                    // so I need to be able to select the components
void enterPinData(vector<PinMapping>& pinData, string filename);
void editPinData(vector<PinMapping>& pinData, string filename);
void loadCSV(vector<PinMapping>& pinData, string filename);
void saveCSV(vector<PinMapping>& pinData, string filename);
void displayPinData(const vector<PinMapping>& pinData);
bool rowExists(const vector<PinMapping>& pinData, int row);
int findRowIndex(vector<PinMapping>& pinData, int row);





int main(){
	int mainMenuChoice;
	do {                                                     //This is going to be my do-while loop for the main menu. I think I need on for each menu.
		cout << "\n ----ECU Pinout & Conversion Tools---- \n";
		cout << "\n Enter the number to make a choice \n";
		cout << "1. Conversion Tools - Convert pressures, flows, temps and more!\n";
		cout << "2. ECU Pin Mapping tools - Enter ECU, Vehicle, and Engine wiring data and match signals. \n";
		cout << "3. profit.\n";
		cout << "4. Physics Calculators - Effective Cam Duration, Ideal Gas Law, Helmholtz Resonator Tuning, and more! \n";
		cout << "5. Exit.\n";

		//need to make sure they only select one of these... 

		if (!(cin >> mainMenuChoice)) {       //if the cin is not one of the menu choices... has to be an integer because the choice is only integers...
			cin.clear();                      // clear the cin input box
			cin.ignore(100, '\n');          //remove this number of characters from the buffer. stop removing when they hit a new line. I hope they dont enter more than 100 char..
			cout << " \n please enter a number \n";
				continue;                   //kinda like an else, its a transition out of the if statement
		}

		switch (mainMenuChoice) {    //the switch for the switch-case. uses the mainMenuChoice as the variable for the case... the number from the cin above
		case 1:
			conversionMenu();
			break;                   //break out of the case after it runs the conversion menu function.
		case 2:
			pinMappingMenu();    //pin mapping will be using CSV files 
			break;
		//case 3:
			//ecmToolsMenu();
			//break;
		//case 4:
			//physicsCalculators();
			//break;
		case 5:
			cout << "Exiting....\n";
			break;

		}

	} while (mainMenuChoice != 5); //so while the menu choice is NOT equal to 5 we will do

	return 0;   //we arent returning anything here. 
}

void conversionMenu() {
	int convMenuChoice;
	
	do {
		cout << "\n -----Conversion Tools----- \n";
		cout << "\n Select A number to Continue...\n";
		cout << "1. PSI to BAR \n";
		cout << "2. BAR to PSI \n";
		cout << "3. PSI to kPa \n";
		cout << "4. kPa to PSI \n";
		cout << "5. lb/hr to cc/min \n";
		cout << "6. cc/min to lb/hr \n";
		cout << "7. Fahrenheit to Celsius \n";
		cout << "8. Celsius to Fahrenheit \n";
		cout << "9. AFR to Lambda \n";
		cout << "10. Lambda to AFT \n";
		cout << "11. Injector Duty Cycle Calculation \n";
		cout << "12. Coming Soon...Injector Flow at New Pressure \n";
		cout << "13. Global Variable Function \n";
		cout << "14. Injector Flow Rate by Duty Cycle and Pressure \n";
		cout << "15. Turbo Pressure Ratio \n";
		cout << "16. Return to Main Menu \n";

		if (!(cin >> convMenuChoice)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\n Please enter a number \n";
			continue;
		}

		switch (convMenuChoice) {
		case 1:
			psiToBar();
			break;
		case 2: 
			barToPsi();
			break;
		case 3:
			psiToKpa();
			break;
		case 4:
			kpaToPsi();
			break;
		case 5:
			lbHrToCcMin();
			break;
		case 6:
		    ccMinToLbHr();
			break;
		case 7:
			fahrenheitToCelsius();
			break;
		case 8:
			celsiusToFahrenheit();
			break;
		case 9:
			afrToLambda();
			break;
		case 10:
			lambdaToAfr();
			break;
		case 11:
			injectorSizeCalculator();
			break;
		case 12:
			cout << "not finished yet";
			break;
		case 13:
			globalVarFunc(0);
			break;
		case 16:
			cout << "Returning to Main Menu...\n";
			break;
		default:
			cout << "1-16 only!!!\n";
		}

	} while (convMenuChoice != 16);
}

//I need to go to bed. I will do all 16 conversion function tomorrow.
// I think they will be easy. My plan is to have it a little scripted and one function per conversion. 
// when the case statement is called, it will call that corresponding function. request info from user. do conversion.
// print out data to user. give them the option to go again or exit to the conversion menu. rinse and repeat for all 15 funciton.s

// no minute like the last.... 
// so I ahve a problem... a ton of my variables errored basically saying they are unintialized. so I guess I have to assign them all values?

void psiToBar() {
	float pressInBar;    //declare my variables. one for PSI on for BAR. one for exiting. Will use the same idea for all functions in conversions
	float pressInPSI;
	char exitChoice;
	exitChoice = 'n';

		do {                                                       //another do while loop. I like these because I understand them
			cout << "\n PSI to BAR Conversion \n";                  //title
			cout << "\n Enter your pressure in PSI\n";              //prompt

			//cin >> pressInPSI;                                      //user entry value
																	// going to use the same I did above for entry checking. it works. might be a better way though
			if (!(cin >> pressInPSI)) {                             // check if input is a float or number... kinda but really just making sure its a float
				cin.clear();                                        // if its not a float, clear ut here
				cin.ignore(100, '\n');                              // ignore 100 char
				cout << "Numbers Only! try again!\n";
				continue;                                          // restart
			}

			pressInBar = (pressInPSI * 0.0689476f);                 //actual math

			cout << pressInPSI << " PSI is " << pressInBar << "BAR\n";        //display answer for user

			cout << "\n Would you like to convert PSI to BAR again? (y/n) \n";    //prompt to play again
			cin >> exitChoice;                                                    //user response

		} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.
	}

void barToPsi() {
	float pressInBAR;    //declare my variables. one for PSI on for BAR. one for exiting. Will use the same idea for all functions in conversions
	float pressInPSI;
	char exitChoice;
	exitChoice = 'n';

	do {                                                       //another do while loop. I like these because I understand them
		cout << "\n BAR to PSI Conversion \n";                  //title
		cout << "\n Enter your pressure in BAR\n";              //prompt

		//cin >> pressInBAR;                                      //user entry value
		if (!(cin >> pressInBAR)) {                             // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                        // if its not a float, clear ut here
			cin.ignore(100, '\n');                              // ignore 100 char
			cout << "Numbers Only! try again!\n";
			continue;                                          // restart
		}

		pressInPSI = (pressInBAR * 14.5038f);                 //actual math with an f after the value so we know it is a float. 

		cout << pressInBAR << " BAR is " << pressInPSI << " PSI\n";        //display answer for user

		cout << "\n Would you like to convert BAR to PSI again? (y/n) \n";    //prompt to play again
		cin >> exitChoice;                                                    //user response

	} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.
}


void psiToKpa() {
	float pressInkPa;    //declare my variables. 
	float pressInPSI;
	char exitChoice;
	exitChoice = 'n';

	do {                                                       //another do while loop. I like these because I understand them
		cout << "\n PSI to kPa Conversion \n";                  //title
		cout << "\n Enter your pressure in PSI\n";              //prompt

		//cin >> pressInPSI;                                      //user entry value
		if (!(cin >> pressInPSI)) {                             // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                        // if its not a float, clear ut here
			cin.ignore(100, '\n');                              // ignore 100 char
			cout << "Numbers Only! try again!\n";
			continue;                                          // restart
		}

		pressInkPa = (pressInPSI * 6.89476f);                 //actual math with an f after the value so we know it is a float. 

		cout << pressInPSI << " PSI is " << pressInkPa << " kPa\n";        //display answer for user

		cout << "\n Would you like to convert PSI to kPa again? (y/n) \n";    //prompt to play again
		cin >> exitChoice;                                                    //user response

	} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.
}
void kpaToPsi() {
	float pressInkPa;    //declare my variables. 
	float pressInPSI;
	char exitChoice;
	exitChoice = 'n';
	pressInPSI = 0;

	do {                                                       //another do while loop. I like these because I understand them
		cout << "\n kPa to PSI Conversion \n";                  //title
		cout << "\n Enter your pressure in kPa\n";              //prompt

		//cin >> pressInkPa;                                      //user entry value
		if (!(cin >> pressInkPa)) {                             // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                        // if its not a float, clear ut here
			cin.ignore(100, '\n');                              // ignore 100 char
			cout << "Numbers Only! try again!\n";
			continue;                                          // restart
		}

		pressInPSI = (pressInkPa * .145038f);                 //actual math with an f after the value so we know it is a float. 

		cout << pressInkPa << " kPa is " << pressInPSI << " PSI\n";        //display answer for user

		cout << "\n Would you like to convert kPa to PSI again? (y/n) \n";    //prompt to play again
		cin >> exitChoice;                                                    //user response

	} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.
}
void lbHrToCcMin() {
	float lbHR; 
	float ccMIN;                                      //declare my variables. 
	char exitChoice;
	exitChoice = 'n';
	ccMIN = 0;

	do {                                                       //another do while loop. I like these because I understand them
		cout << "\n lb/hr to cc/min Conversion \n";                  //title
		cout << "\n Enter your pressure in lb/hr\n";              //prompt

		//cin >> lbHR;                                      //user entry value
		if (!(cin >> lbHR)) {                             // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                        // if its not a float, clear ut here
			cin.ignore(100, '\n');                              // ignore 100 char
			cout << "Numbers Only! try again!\n";
			continue;                                          // restart
		}

		ccMIN = (lbHR * 10.5);                 //actual math with an f after the value so we know it is a float. 

		cout << lbHR << " lb/hr is " << ccMIN << " cc/min\n";        //display answer for user

		cout << "\n Would you like to convert lb/hr to cc/min again? (y/n) \n";    //prompt to play again
		cin >> exitChoice;                                                    //user response

	} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.
}
void ccMinToLbHr() {
	float lbHR;    //declare my variables. 
	float ccMIN;
	char exitChoice;
	exitChoice = 'n';
	lbHR = 0;

	do {                                                       //another do while loop. I like these because I understand them
		cout << "\n cc/min to lb/hr Conversion \n";                  //title
		cout << "\n Enter your pressure in cc/min\n";              //prompt

		//cin >> ccMIN;                                      //user entry value
		if (!(cin >> ccMIN)) {                             // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                        // if its not a float, clear ut here
			cin.ignore(100, '\n');                              // ignore 100 char
			cout << "Numbers Only! try again!\n";
			continue;                                          // restart
		}

		lbHR = (ccMIN / 10.5);                 //actual math with an f after the value so we know it is a float. 

		cout << ccMIN << " cc/min is " << lbHR << " lb/hr \n";        //display answer for user

		cout << "\n Would you like to convert cc/min to lb/hr again? (y/n) \n";    //prompt to play again
		cin >> exitChoice;                                                    //user response

	} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.
}
void fahrenheitToCelsius() {
	float fahr;    //declare my variables. 
	float cels;
	char exitChoice;
	exitChoice = 'n';

	do {                                                       //another do while loop. I like these because I understand them
		cout << "\n Fahrenheit To Celsius Conversion \n";                  //title
		cout << "\n Enter your temperature in Fahrenheit\n";              //prompt

		//cin >> fahr;                                      //user entry value
		if (!(cin >> fahr)) {                             // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                        // if its not a float, clear ut here
			cin.ignore(100, '\n');                              // ignore 100 char
			cout << "Numbers Only! try again!\n";
			continue;                                          // restart
		}

		cels = ((fahr - 32.0) * (5.0/9.0));                //aparently you cant divide integers? this made 0 //actual math with an f after the value so we know it is a float. 

		cout << fahr << " °F is " << cels << " °C \n";        //display answer for user  ALT+0176 for degrees symbol... one day I will remember that

		cout << "\n Would you like to convert Fahrenheit To Celsius again? (y/n) \n";    //prompt to play again
		cin >> exitChoice;                                                    //user response

	} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.
}
void celsiusToFahrenheit() {
	float fahr;    //declare my variables. 
	float cels;
	char exitChoice;
	exitChoice = 'n';

	do {                                                       //another do while loop. I like these because I understand them
		cout << "\n Celsius To Fahrenheit Conversion \n";                  //title
		cout << "\n Enter your temperature in Celsius\n";              //prompt

		//cin >> cels;                                      //user entry value
		if (!(cin >> cels)) {                             // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                        // if its not a float, clear ut here
			cin.ignore(100, '\n');                              // ignore 100 char
			cout << "Numbers Only! try again!\n";
			continue;                                          // restart
		}

		fahr = ((cels * (9.0/5.0))+ 32.0);               // same thing happened here. not sure why you cant divide integers??  //actual math  

		cout << cels << " °C is " << fahr << " °F \n";        //display answer for user  ALT+0176 for degrees symbol... one day I will remember that

		cout << "\n Would you like to convert Celsius To Fahrenheit again? (y/n) \n";    //prompt to play again
		cin >> exitChoice;                                                    //user response

	} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.
}
void afrToLambda() {
	float afr;    //declare my variables. 
	float lambda;
	char exitChoice;
	exitChoice = 'n';

	do {                                                       //another do while loop. I like these because I understand them
		cout << "\n AFR to Lambda Conversion \n";                  //title
		cout << "\n Enter your AFR. Stoichometric value is static at 14.7:1 \n";              //prompt

		//cin >> afr;                                      //user entry value
		if (!(cin >> afr)) {                             // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                        // if its not a float, clear ut here
			cin.ignore(100, '\n');                              // ignore 100 char
			cout << "Numbers Only! try again!\n";
			continue;                                          // restart
		}

		 lambda = afr/14.7f;                 //actual math with an f after the value so we know it is a float. 

		cout << afr << " AFR is " << lambda << " Lambda \n";        //display answer for user  ALT+0176 for degrees symbol... one day I will remember that

		cout << "\n Would you like to convert AFR to Lambda again? (y/n) \n";    //prompt to play again
		cin >> exitChoice;                                                    //user response

	} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.
}
void lambdaToAfr() {
	float afr;    //declare my variables. 
	float lambda;
	char exitChoice;
	exitChoice = 'n';

	do {                                                       //another do while loop. I like these because I understand them
		cout << "\n Lambda to AFR Conversion \n";                  //title
		cout << "\n Enter your Lambda. Stoichometric value is static at 14.7:1 \n";              //prompt

		//cin >> lambda;                                     // this is wrong in every function!!! GRRRRRRR. double entering lambda  //user entry value
		if (!(cin >> lambda)) {                             // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                        // if its not a float, clear ut here
			cin.ignore(100, '\n');                              // ignore 100 char
			cout << "Numbers Only! try again!\n";
			continue;                                          // restart
		}

		afr = lambda * 14.7f;                 //actual math with an f after the value so we know it is a float. 

		cout << lambda << " Lambda is " << afr << " AFR \n";        //display answer for user  ALT+0176 for degrees symbol... one day I will remember that

		cout << "\n Would you like to convert Lambda to AFR again? (y/n) \n";    //prompt to play again
		cin >> exitChoice;                                                    //user response

	} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.
}
void injectorSizeCalculator() {
	//Okay this one is going to be a little differet. Injector size is dependent on the duty cycle, brake specific fuel consumption, the number of 
	//injector and the horsepower that is being aimed for. 

	float horsepower, bsfc, maxDutyCycle, injectorSize;     //just learned I can declare everything delimenated by commas!
	int injectorCount;
	char exitChoice;
	exitChoice = 'n';

	do {
		cout << "\n Fuel Injector Size Calculator \n";

		//prompt hp

		cout << "What is your horsepower goal?\n";
		if (!(cin >> horsepower) || horsepower <=0) {                           //hmmm what happens if they enter 0 for hp?  // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                                      // if its not a float, clear ut here
			cin.ignore(100, '\n');                                       // ignore 100 char
			cout << "Numbers Only And Greater than 0! try again!\n";
			continue;                                                   // restart
		}

		cout << "How Many Cylinders Do You Have?\n";
		if (!(cin >> injectorCount) || injectorCount <= 0) {                           //hmmm what happens if they enter 0 for hp?  // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                               // if its not a float, clear ut here
			cin.ignore(100, '\n');                                     // ignore 100 char
			cout << "Numbers Only And Greater than 0!! try again!\n";
			continue;                                                  // restart
		}

		cout << "What Is Your BSFC? Note NA is 0.5, Turbo/Supercharged 0.6-0.75\n";
		if (!(cin >> bsfc) || bsfc <= 0) {                              // apparently "or" doesnt work in c++   //hmmm what happens if they enter 0 for hp?  // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                               // if its not a float, clear ut here
			cin.ignore(100, '\n');                                     // ignore 100 char
			cout << "Numbers Only And Greater than 0!! try again!\n";
			continue;                                                  // restart
		}
		cout << "What Is Your Max Duty Cycle? Note - 85% is the highest you should go. Enter without % symbol.\n";
		if (!(cin >> maxDutyCycle) || maxDutyCycle <= 0 || maxDutyCycle > 100) {                          //and it has to be less than 100... so if its more... bad //hmmm what happens if they enter 0 for hp?  // check if input is a float or number... kinda but really just making sure its a float
			cin.clear();                                                                                 // if its not a float, clear ut here
			cin.ignore(100, '\n');                                                                       // ignore 100 char
			cout << "Numbers Only, Greater than 0, and less than 100!! try again!\n";
			continue;                                                  // restart
		}
		// okay the duty cycle has to be a decimal
		maxDutyCycle = maxDutyCycle / 100;

		//now the actual calculation... 
		injectorSize = (horsepower * bsfc) / (injectorCount * maxDutyCycle);

		cout << "\n You should use " << injectorSize << " lb / hr \n";

		cout << "\n Would you like to calculate your injecotr size again? (y/n) \n";    //prompt to play again
		cin >> exitChoice;                                                    //user response

	} while (exitChoice == 'y' || exitChoice == 'Y');                         //user response either in lower case or caps.

}

void globalVarFunc(int engineCode) {
	cout << "\n Select an Engine by choosing a number.\n";
	cout << "1. TURBO\n";
	cout << "2. SUPERCHARGED \n";
	cout << "3. Naturally Aspirated \n";

	cin >> engineCode;

	globalVarCounter++;      //add up the global counter

	if (engineCode == 1) {
		cout << "You selected TURBO\n";
	}
	else if (engineCode == 2) {
		cout << "You Selected SUPERCHARGED\n";
	} else if (engineCode == 3) {
		cout << "You Selected Naturally Aspirated\n";
	}
	else {
		cout << "Not an engine code! \n";
	}
}

void injectorFlowAtNewPressure() {                        // they need to enter old fp and new fp then ise old*sqrt(new/old)
	float oldFlow, oldPressure, newPressure, newFlow;
	char exitChoice = 'n';

	do {
		cout << "\n Injector Flow at New Pressure Calculation \n";
		cout << "Enter current injector flow rate (lb/hr): ";
		if (!(cin >> oldFlow) || oldFlow <= 0) {                //ssme handlers as above for incorrect entry
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value greater than 0.\n";
			continue;
		}

		cout << "Enter current fuel pressure (psi): ";
		if (!(cin >> oldPressure) || oldPressure <= 0) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value greater than 0.\n";
			continue;
		}

		cout << "Enter new fuel pressure (psi): ";
		if (!(cin >> newPressure) || newPressure <= 0) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value greater than 0.\n";
			continue;
		}

		newFlow = oldFlow * sqrt(newPressure / oldPressure);
		cout << "At " << newPressure << " psi, the injector flow rate is " << newFlow << " lb/hr\n";  // keep this / and this \ stright lol ||?

		cout << "\n Would you like to calculate again? (y/n) \n";
		cin >> exitChoice;
	} while (exitChoice == 'y' || exitChoice == 'Y');
}
//void horsepowerByInjectorSize();
void horsepowerByInjectorSize() {                   //this could get ugly. let them enter bsfc. okay, it will only be me using this... so whatever
	float injectorSize, bsfc, dutyCycle, cylinderCount, horsepower; 
	char exitChoice = 'n';

	do {
		cout << "\n Horsepower Calculation by Injector Size \n";
		cout << "Enter injector flow rate (lb/hr): ";
		if (!(cin >> injectorSize) || injectorSize <= 0) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value greater than 0.\n";
			continue;
		}

		cout << "Enter BSFC (typical values: NA = 0.5, Turbo = 0.6-0.75): ";
		if (!(cin >> bsfc) || bsfc <= 0) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value greater than 0.\n";
			continue;
		}

		cout << "Enter max duty cycle percentage (suggested max 85%): ";
		if (!(cin >> dutyCycle) || dutyCycle <= 0 || dutyCycle > 100) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value between 1 and 100.\n";
			continue;
		}

		cout << "Enter the number of cylinders: ";
		if (!(cin >> cylinderCount) || cylinderCount <= 0) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value greater than 0.\n";
			continue;
		}

		dutyCycle = dutyCycle / 100.0f;
		horsepower = (injectorSize * cylinderCount * dutyCycle) / bsfc;
		cout << "Estimated horsepower: " << horsepower << " HP\n";

		cout << "\n Would you like to calculate again? (y/n) \n";
		cin >> exitChoice;
	} while (exitChoice == 'y' || exitChoice == 'Y');
}
//void injectorFlowRateByDutyCycle();
void injectorFlowRateByDutyCycle() {
	float injectorSize, dutyCycle, actualFlow;
	char exitChoice = 'n';

	do {
		cout << "\n Injector Flow Rate by Duty Cycle \n";
		cout << "Enter injector flow rate (lb/hr): ";
		if (!(cin >> injectorSize) || injectorSize <= 0) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value greater than 0.\n";
			continue;
		}

		cout << "Enter duty cycle percentage (e.g., 85 for 85%): ";
		if (!(cin >> dutyCycle) || dutyCycle <= 0 || dutyCycle > 100) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value between 1 and 100.\n";
			continue;
		}

		dutyCycle = dutyCycle / 100.0f;
		actualFlow = injectorSize * dutyCycle;
		cout << "Actual flow at " << dutyCycle * 100 << "% duty cycle: " << actualFlow << " lb/hr\n";

		cout << "\n Would you like to calculate again? (y/n) \n";
		cin >> exitChoice;
	} while (exitChoice == 'y' || exitChoice == 'Y');
}
//void turboPressureRatio();
void turboPressureRatio() {
	float ambientPressure, boostPressure, pressureRatio;
	char exitChoice = 'n';

	do {
		cout << "\n Turbo Pressure Ratio Calculation \n";
		cout << "Enter ambient pressure (typically 14.7 psi at sea level): ";
		if (!(cin >> ambientPressure) || ambientPressure <= 0) { // so need to handle if they 
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value greater than 0.\n";
			continue;
		}

		cout << "Enter boost pressure (psi): ";
		if (!(cin >> boostPressure) || boostPressure <= 0) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Numbers only! Enter a value greater than 0.\n";
			continue;
		}

		pressureRatio = (boostPressure + ambientPressure) / ambientPressure;
		cout << "Turbo pressure ratio: " << pressureRatio << "\n";

		cout << "\n Would you like to calculate again? (y/n) \n";
		cin >> exitChoice;
	} while (exitChoice == 'y' || exitChoice == 'Y');
}
void returnToMainMenu() {
	cout << "\n Returning to the Main Menu...\n";
	return;
}

void pinMappingMenu() {
	int choice;

	do {
		cout << "\n---- ECU Pin Mapping ----\n";
		cout << "1. Enter Engine Harness\n";
		cout << "2. Enter Car Harness\n";
		cout << "3. Enter ECU Pinout\n";
		cout << "4. Return to Main Menu\n";
		cout << "Enter your choice: ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input! Enter a number.\n";
			continue;
		}

		switch (choice) {
		case 1: handleComponentSelection("engine.csv"); break;
		case 2: handleComponentSelection("car_harness.csv"); break;
		case 3: handleComponentSelection("ecu.csv"); break;
		case 4: cout << "Returning to Main Menu...\n"; break;
		default: cout << "Invalid choice! Enter 1-4.\n";
		}
	} while (choice != 4);
}

//*********************************______________________*********************************__________________________*************________________
//this starts the pin mapping  functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void handleComponentSelection(string filename) {
	vector<PinMapping> pinData;
	loadCSV(pinData, filename);

	int choice;
	do {
		cout << "\n---- Pin Mapping Options ----\n";
		cout << "1. Enter New Pin Data\n";
		cout << "2. Edit Existing Data\n";
		cout << "3. Display Current Data\n";
		cout << "4. Save & Exit\n";
		cout << "Enter choice: ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input! Enter a number.\n";
			continue;
		}

		switch (choice) {
		case 1: enterPinData(pinData, filename); break;
		case 2: editPinData(pinData, filename); break;
		case 3: displayPinData(pinData); break;
		case 4: saveCSV(pinData, filename); cout << "Data saved.\n"; break;
		default: cout << "Invalid choice! Enter 1-4.\n";
		}
	} while (choice != 4);
}

void enterPinData(vector<PinMapping>& pinData, string filename) {
	PinMapping entry;
	cout << "Enter Row Number: ";
	cin >> entry.row;

	if (rowExists(pinData, entry.row)) {
		cout << "Row " << entry.row << " already exists. Use Edit option instead.\n";
		return;
	}

	cout << "Enter Device Name: ";
	cin.ignore();
	getline(cin, entry.device);

	cout << "Enter Wire Color: ";
	getline(cin, entry.wireColor);

	cout << "Enter Signal Type: ";
	getline(cin, entry.signalType);

	cout << "Enter Direction (Input/Output/Power): ";
	getline(cin, entry.direction);

	cout << "Enter Destination: ";
	getline(cin, entry.destination);

	pinData.push_back(entry);
	cout << "Data added successfully!\n";
}

void editPinData(vector<PinMapping>& pinData, string filename) {
	int row;
	cout << "Enter Row Number to Edit: ";
	cin >> row;

	int index = findRowIndex(pinData, row); //row? has to be an int??
	if (index == -1) {
		cout << "Row not found! Use 'Enter New Data' instead.\n";
		return;
	}

	cout << "Editing row " << row << ". Press Enter to keep existing values.\n";

	cout << "Enter new Device Name [" << pinData[index].device << "]: ";
	cin.ignore();
	string input;
	getline(cin, input);
	if (!input.empty()) pinData[index].device = input;

	cout << "Enter new Wire Color [" << pinData[index].wireColor << "]: ";
	getline(cin, input);
	if (!input.empty()) pinData[index].wireColor = input;

	cout << "Enter new Signal Type [" << pinData[index].signalType << "]: ";
	getline(cin, input);
	if (!input.empty()) pinData[index].signalType = input;

	cout << "Enter new Direction [" << pinData[index].direction << "]: ";
	getline(cin, input);
	if (!input.empty()) pinData[index].direction = input;

	cout << "Enter new Destination [" << pinData[index].destination << "]: ";
	getline(cin, input);
	if (!input.empty()) pinData[index].destination = input;

	cout << "Row updated successfully!\n";
}

void loadCSV(vector<PinMapping>& pinData, string filename) {
	pinData.clear();
	ifstream file(filename);
	if (!file) return;  // If file doesn't exist, return silently

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		PinMapping entry;
		getline(ss, line, ','); entry.row = stoi(line);
		getline(ss, entry.device, ',');
		getline(ss, entry.wireColor, ',');
		getline(ss, entry.signalType, ',');
		getline(ss, entry.direction, ',');
		getline(ss, entry.destination, ',');
		pinData.push_back(entry);
	}
	file.close();
}

void saveCSV(vector<PinMapping>& pinData, string filename) {
	ofstream file(filename);
	for (const auto& entry : pinData) {
		file << entry.row << "," << entry.device << "," << entry.wireColor << ","
			<< entry.signalType << "," << entry.direction << "," << entry.destination << "\n";
	}
	file.close();
}

void displayPinData(const vector<PinMapping>& pinData) {
	if (pinData.empty()) {
		cout << "No data available.\n";
		return;
	}

	cout << "\nRow | Device | Wire Color | Signal Type | Direction | Destination\n";
	cout << "---------------------------------------------------------------\n";
	for (const auto& entry : pinData) {
		cout << entry.row << " | " << entry.device << " | " << entry.wireColor << " | "
			<< entry.signalType << " | " << entry.direction << " | " << entry.destination << "\n";
	}
}

bool rowExists(const vector<PinMapping>& pinData, int row) {
	for (const auto& entry : pinData) {
		if (entry.row == row) return true;
	}
	return false;
}

int findRowIndex(vector<PinMapping>& pinData, int row) {
	for (size_t i = 0; i < pinData.size(); ++i) {
		if (pinData[i].row == row)
			return static_cast<int>(i); // Explicit conversion from size_t to int?? I have no idea what static cast or size_t is.... thank god for google
	}
	return -1; // Return -1 if not found
}