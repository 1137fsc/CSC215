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
#include <algorithm>  // for sorting of the rows
using namespace std;
// I will be keeping main at the top of my program, so I will prototype my functions so that they can come below main

// I am not sure where to put the struct??

// Define a structure for pin mapping entries... I read up on the struct... and I am just going to call it "getting struct" because this is how I am going to get my structure from the CSVs
struct PinMapping {
	int row=0;            //kept getting a compiler error here, basicially saying its uninitialized. of course it is, I havent done anything with it yet! do I need ot initilize to zero?
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
//week2
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

// functions, with reference and parameter passthrough  declarations for the pin mapping
//week 3&4

void pinMappingMenu();
void handleComponentSelection(string filename);                    // so I need to be able to select the components
void enterPinData(vector<PinMapping>& pinData, string filename);
void editPinData(vector<PinMapping>& pinData, string filename);
void loadCSV(vector<PinMapping>& pinData, string filename);
void saveCSV(vector<PinMapping>& pinData, string filename);
void displayPinData(vector<PinMapping>& pinData, string filename);   //if you forget your parameter here and you make your function with a parameter that is not declared, you get the wildest error ever. That was fun. 
bool rowExists(const vector<PinMapping>& pinData, int row);
int findRowIndex(vector<PinMapping>& pinData, int row);





int main(){
	int mainMenuChoice;
	do {                                                     //This is going to be my do-while loop for the main menu. I think I need on for each menu.
		cout << "\n ----ECU Pinout & Conversion Tools---- \n";
		cout << "\n Enter the number to make a choice \n";
		cout << "1. Conversion Tools - Convert pressures, flows, temps and more!\n"; // week 2
		cout << "2. ECU Pin Mapping tools - Enter ECU, Vehicle, and Engine wiring data. \n"; ///week 3 (okay and week 4)
		cout << "3. ECU Programming Tools... Coming Soon!!.\n";                              //week 4
		cout << "4. Physics Calculators - Effective Cam Duration, Ideal Gas Law, Helmholtz Resonator Tuning, and more! \n"; //week 5
		cout << "5. Exit.\n";   // final

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
//////////////////////////////////////////////////////////
//conversions and math stuff//////////// week 2///////////
/////////////////////////////////////////////////////////

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
		case 12: injectorFlowAtNewPressure(); 
			break;
		case 13: globalVarFunc(0); 
			break;
		case 14: injectorFlowRateByDutyCycle(); 
			break;
		case 15: turboPressureRatio(); 
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

		ccMIN = (lbHR * 10.5f);                 //actual math with an f after the value so we know it is a float. 

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

		lbHR = (ccMIN / 10.5f);                 //actual math with an f after the value so we know it is a float. 

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

		cels = ((fahr - 32.0f) * (5.0f/9.0f));                //aparently you cant divide integers? this made 0 //actual math with an f after the value so we know it is a float. 

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
		
		fahr = ((cels * (9.0f/5.0f))+ 32.0f);               // same thing happened here. not sure why you cant divide integers??  //actual math  

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
//---------------------------------**********************---------------------------------**************************-------------****************
//*********************************______________________*********************************__________________________*************________________
//                                                    this starts the pin mapping  functions
//---------------------------------**********************---------------------------------**************************-------------****************
//*********************************______________________*********************************__________________________*************________________


void pinMappingMenu() {                  // my menu for going through pin mapping. basiically another set of functions that will read/write, temp store and update my csv pin mapping and harness mapping
	int choice;

	do {                                          //my do-while for the switch case. prompt user, get instructions to run a specific case. handle stupid entries. 
		
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
		case 1: handleComponentSelection("engine.csv"); break;           //so if they chose any of the cases, I need to call which CSV to open AND call that function. 9
		case 2: handleComponentSelection("car_harness.csv"); break;      //if I have the parameter declared, when I call the function and pass the csv they called, it will correspond to a function and only call that one. So calling the function calls it with a string (actually the filename) . and I can use that string to call a specifc function. at least thats the plan
		case 3: handleComponentSelection("ecu.csv"); break;
		case 4: cout << "Returning to Main Menu...\n"; break;            // a way back
		default: cout << "Invalid choice! Enter 1-4.\n";                 // a way out
		}
	} while (choice != 4);               // the while... so while a choice is not 4... basically if it is anything else acceptable. if its a 4... well see above. 
}

//okay this is loading the CSV section. Each row in the csv gets "struct"... so I have declared this struct. 
// the vector is basically an array that can grow and shrink at runtime, so not limited at designtime. think "live array". this is because I have no idea how big or small the array will be. an array without bounds

void handleComponentSelection(string filename) 
{  	vector<PinMapping> pinData; 
loadCSV(pinData, filename);                  // cont. from above... create a list "vector", called <myVariable> that holds "myData". vector is the property/object, pinData will be its name. pinMapping holds the entries. I think I have that straight... 

	int choice;
	do {                                              // another do-while-switch case to select with csv/function they are going to call/select. Same as all the others
		cout << "\n      Pin Mapping Options     \n";
		cout << "1. Enter New Pin Data\n";
		cout << "2. Edit Existing Data\n";
		cout << "3. Display Current Data\n";
		cout << "4. Save & Exit\n";
		cout << "5. Exit\n";
		cout << "Enter choice: ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input! Enter a number.\n";
			continue;
		}

		// okay so this is where the passing magic happens. up top when they select the case, which selects whch section they are goig to work on
		// it calls handlecomponenet selection which has the parameter for the csv, then
		// when they chose to enter, edit or display the info, the CSV is already called/opened, and this calls the function of what we are going to do. 
		//so call "enter harness" it calls handle component select parameter harness csv, then they go to the menu to select what they want to do with it
		//where they chose say enter new data, and it calls the function with parameter of "pindata", and returns whatever filename from handle component selection
		switch (choice) {
		case 1: // enterPinData(pinData, filename); 
			// Pass pinData by reference, no need to reload CSV here
		{
			PinMapping entry;
			cout << "\n Enter Row Number: ";
			if (!(cin >> entry.row)) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Invalid row number! Please enter a number.\n";
				continue;
			}

			// Check if row exists
			if (rowExists(pinData, entry.row)) {
				cout << "Row " << entry.row << " already exists. Use Edit option instead.\n";
				continue;
			}
			cin.ignore(); // Clear the newline

			cout << "Enter Device Name: ";
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
			break;          
		case 2: editPinData(pinData, filename); 
			break;
		case 3: //displayPinData(pinData, filename); 
			if (pinData.empty()) {
				cout << "\n No data in " << filename << ".\n";
			}
			else {
				cout << "\n Row | Device | Wire Color | Signal Type | Direction | Destination \n";
				cout << "---------------------------------------------------------------------\n";
				for (const auto& entry : pinData) {
					cout << entry.row << " | "
						<< entry.device << " | "
						<< entry.wireColor << " | "
						<< entry.signalType << " | "
						<< entry.direction << " | "
						<< entry.destination << "\n";
				}
			}
			break;
			break;
		case 4: saveCSV(pinData, filename); 
			cout << "Data saved.\n";
			break;
		case 5: 
			cout << "exiting\n";
			break;
		default: cout << "Invalid choice! Enter 1-4.\n";
		}
	} while (choice != 4 && choice != 5); // while (choice != 4 || 5);
}

//enter data. This is where we will enter the pin data. So this needs to be the vector for pin mapping
// okay from class, we talked about using references. This is my reference. I am refencing the data from the table. that way
//a change here is a change in the table. not jus a copy (alias or pointer) of the info/data. so pass the vector as a reference, edit in the function
//also passing the string filename that came from uptop so we are editting the correct csv. 

void enterPinData(vector<PinMapping>& pinData, string filename) {    //pass the vector pin mapping as a reference, pass the name of the csv. 
	loadCSV(pinData, filename);  // Added this line to keep previously saved entries

	PinMapping entry;												//create a row by nymber
	cout << "\n Enter Row Number: ";
	cin >> entry.row;

	//so what happens if you call a row that already exists? is this going to wipe it?
	//need a way to handle this
	if (rowExists(pinData, entry.row)) {                                
		//so if row exists in pin data, then tell them they cant use this, and they need to use the edit funtion. 
		cout << "Row " << entry.row << " already exists. Use Edit option instead.\n";
		return;
	}

	cout << "Enter Device Name: ";
	cin.ignore();						//ignore nulls
	getline(cin, entry.device);

	cout << "Enter Wire Color: ";
	getline(cin, entry.wireColor);

	cout << "Enter Signal Type: ";
	getline(cin, entry.signalType);

	cout << "Enter Direction (Input/Output/Power): ";
	getline(cin, entry.direction);

	cout << "Enter Destination: ";
	getline(cin, entry.destination);

	// so how is this written to the csv? need to google. 
	// okay looks like a push? https://www.geeksforgeeks.org/csv-file-management-using-c/ kinda shows fout and row.pushback. so pindata is my vector, victor. so pinData.pushback?
	//no pop.back. 
	//no no no. PUSH_BACK
	//pinData.pushback(entry);	
	//pinData.pop_back(entry);
	pinData.push_back(entry);
	cout << "Data added successfully!\n";
}

// for editing pin data... same thing as above. except find the row and edit it. 
//might need to display the data first. 
void editPinData(vector<PinMapping>& pinData, string filename) {     //im using the same as above, because its editing a vector still.
	int row;
	cout << "Enter Row Number to Edit: ";
	cin >> row;

	int index = findRowIndex(pinData, row); //row has to be an int... need to change this for abbove.. this will be the index. again from https://www.geeksforgeeks.org/csv-file-management-using-c/
	if (index == -1) {
		cout << "Row not found! Use 'Enter New Data' instead.\n";
		return;
	}

	cout << "Editing row " << row << ". Press Enter to keep existing values.\n";

	// so enter new device for index (row #).device. each ".something" is from my struct. 
	//much like a UDT in rockwell, the .something is a memeber of the struct. since this is one dimensional, we only have one .something. so it wont be pindata[index].device/whatever.something else... 
	//as we only have one dimension in the vector (array). same for all the rest. 

	cout << "Enter new Device Name [" << pinData[index].device << "]: ";  
	cin.ignore();
	string input;    //declare my strings
	//string input1;
	//string input2;
	//string input3;
	//string input4;

	getline(cin, input);    //get input from user
	if (!input.empty()) pinData[index].device = input;   //if input is not empty then vector .device is what they put for input... basically, handle nothing lol. in the event its nothing. 

	cout << "Enter new Wire Color [" << pinData[index].wireColor << "]: ";  // now lets change to the next element of struct.

	getline(cin, input);
	if (!input.empty()) pinData[index].wireColor = input;                   //can I use the same string input? If i just have the next cin = the input, then I can just overwrite the input each cin...
																			//so long as everything goes in order, it will overwrite cin each time. i think it will work. 

	cout << "Enter new Signal Type [" << pinData[index].signalType << "]: ";
	getline(cin, input);
	if (!input.empty()) pinData[index].signalType = input;

	cout << "Enter new Direction [" << pinData[index].direction << "]: ";
	getline(cin, input);

	if (!input.empty()) pinData[index].direction = input;

	cout << "Enter new Destination [" << pinData[index].destination << "]: ";
	getline(cin, input);
	if (!input.empty()) pinData[index].destination = input;

	//pinData.push_back(entry);                                // okay dont actually need this, its already editing the row. pushback adds entries to the vector. duplicated everything. 
	cout << "Row updated successfully!\n";
}

// need to load the csv into the vector. 
// also need to clear the vector when new data is loaded, because the enw data may have nulls which wont write over whatever is in the vector. 
void loadCSV(vector<PinMapping>& pinData, string filename) {
	pinData.clear();
	ifstream file(filename);                                      //this is how we read from the files, covered this in class. 
	//if (!file) return;  // If file doesn't exist, end without crashing. its a void so its not looking for a value to be returned. so just return... or be done with it if the file doesnt exist. 
	//wont open the files, says its blank, need to know if its actually trying 
	if (!file) {
		cout << "ERROR cant open the file. the programmer is trying to finish this at 02:26 and has to be at work at 07:30 " << filename << endl;
		return;
	}
	// okay so we got the file, now we gotta move the data in. 
	//since this is a CSV, its delimated by commas. so comma?
	// back to https://www.geeksforgeeks.org/csv-file-management-using-c/
	/*Read a particular record:
In reading a CSV file, the following approach is implemented:-
Using getline(), file pointer and ‘\n’ as the delimiter, read an entire row and store it in a string variable.
Using stringstream, separate the row into words.
Now using getline(), the stringstream pointer and ‘, ‘ as the delimiter, read every word in the row, store it in a string variable and push that variable to a string vector.
Retrieve a required column data through row[index]. 
Here, row[0] always stores the roll number of a student, so compare row[0] with the roll number input by the user, and if it matches, 
display the details of the student and break from the loop.*/
	string line;

	getline(file, line);       
	
	// Skip header if it exists
	if (getline(file, line)) {
		// If the first line contains header info, skip it
		// Otherwise, parse it as data
		if (line.find("row") != string::npos ||
			line.find("device") != string::npos ||
			line.find("Row") != string::npos) {
			// This was a header line, continue to the data
		}
		else {
			// This was data, process it
			stringstream ss(line);
			PinMapping entry;
			string temp;

			getline(ss, temp, ',');
			try {
				entry.row = stoi(temp); // Convert only the row part to integer
			}
			catch (const exception& e) {
				cout << "Error parsing row number: " << temp << endl;
				entry.row = 0;
			}
			getline(ss, entry.device, ',');
			getline(ss, entry.wireColor, ',');
			getline(ss, entry.signalType, ',');
			getline(ss, entry.direction, ',');
			getline(ss, entry.destination);  // Get the rest of the line

			pinData.push_back(entry);
		}
	}

	// Process the rest of the file
	while (getline(file, line)) {
		stringstream ss(line);
		PinMapping entry;
		string temp;

		getline(ss, temp, ',');
		try {
			entry.row = stoi(temp); // Convert only the row part to integer
		}
		catch (const exception& e) {
			cout << "Error parsing row number: " << temp << endl;
			entry.row = 0;
		}
		getline(ss, entry.device, ',');
		getline(ss, entry.wireColor, ',');
		getline(ss, entry.signalType, ',');
		getline(ss, entry.direction, ',');
		getline(ss, entry.destination);  // Get the rest of the line

		pinData.push_back(entry);
	}

	file.close();
}

//kept crashing because of the header row. so lets cheat and get the first line first and do nothing with it. ha. 
	//string word;   //didnt use this from the example 
	//string temp;

	/*while (getline(file, line)) {
		stringstream s(line);
		PinMapping entry;
		getline(s, word, ',');
	}
	

	// so if they type in "map sensor" for the decive, then I need to seperate the words, not just seperate by comma. so the s(line) thing doesnt work
	// I found this https://cppscripts.com/getline-delimiter-cpp... so each word goes on a new line.... so I can make my whole struct  "split sentence" or is it string sentence. dunno. 
	while (getline(file, line)) {
		stringstream ss(line);
		PinMapping entry;
		string temp;
		//okay if the row is a string when I pull it in, how do I make it an int so we know what row this is?

		//bullshiiii doesnt work. it overwrites the whole thing getline(ss, line, ','); entry.row = stoi(line);   //ah ha!! https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/?ref=ml_lbp
		getline(ss, temp, ','); entry.row = stoi(temp);
		getline(ss, entry.device, ',');
		getline(ss, entry.wireColor, ',');
		getline(ss, entry.signalType, ',');
		getline(ss, entry.direction, ',');
		getline(ss, entry.destination, ',');
		pinData.push_back(entry);
	}
	cout << " \n";

	file.close();                                // close the file after i get the info. or it hangs everything up. 
}

//save the csv... use the vector reference and the file
//write to the file. 
/*https://www.geeksforgeeks.org/file-handling-c-classes/ says 
ofstream:-

This class provides output operations.
It contains open() function with default output mode.
Inherits the functions put(),  write(), seekp() and tellp() functions from the ostream.*/

// so loop trhough each and write it. 

void saveCSV(vector<PinMapping>& pinData, string filename) {
	// Reload the file again to get all current entries
	/*vector<PinMapping> existingData;
	loadCSV(existingData, filename);

	// Merge new data by row number (overwrite if same row, append otherwise)
	for (const auto& newRow : pinData) {
		auto it = std::find_if(existingData.begin(), existingData.end(), [&](const PinMapping& p) {
			return p.row == newRow.row;
			});

		if (it != existingData.end()) {
			*it = newRow; // Overwrite existing row
		}
		else {
			existingData.push_back(newRow); // Add new row
		}
	}

	// this overwrites all entries. so neeed to load all first, then add the file on the bottom
	//ifstream file(filename);
	
	ofstream file(filename);

	//ofstream file(filename, ios::trunc); // make it overwrite with the full dataset

	if (!file.is_open()) {
		cout << "Failed to open file for saving: " << filename << "\n";
		return;
	}

	//for (size_t i = 0; i < pinData.size(); ++i) {
	//	PinMapping& entry = pinData[i];
	//}
	//https://www.geeksforgeeks.org/range-based-loop-c/
	// so this seems to be the better way to do it
	// Iterating through vector
	//for (auto& i : v)
		//cout << i << " ";

	for (const auto& entry : pinData) {
		file << entry.row << "," << entry.device << "," << entry.wireColor << ","
			<< entry.signalType << "," << entry.direction << "," << entry.destination << "\n";
	}
	file.close();
	//the only thing I see here is if there are two words in the entry... i dunno how its going to work. 
}*/
	ofstream file(filename);

	if (!file.is_open()) {
		cout << "Failed to open file for saving: " << filename << "\n";
		return;
	}

	// Sort data by row number
	sort(pinData.begin(), pinData.end(), [](const PinMapping& a, const PinMapping& b) {
		return a.row < b.row;
		});

	// Write header
	file << "row,device,wireColor,signalType,direction,destination\n";

	// Write data
	for (const auto& entry : pinData) {
		file << entry.row << ","
			<< entry.device << ","
			<< entry.wireColor << ","
			<< entry.signalType << ","
			<< entry.direction << ","
			<< entry.destination << "\n";
	}

	file.close();
	cout << "Data saved to " << filename << " successfully!\n";
}

//and last, display the file. should be able to just reference the vector and get the passed through file name.
//use another do-while switch case. promp with choice, let them chose which file they want to view. give an exit. same as all the others. 
// then open the csv and display it. 
void displayPinData(vector<PinMapping>& pinData, string filename) {
	int choice;
	do {

		cout << "\n Select which File You Want to See \n";
		cout << "1. Engine Harness Pins\n";
		cout << "2. Car Harness Pins \n";
		cout << "3. ECU Pins\n";
		cout << "4. Exit \n";
		cout << "Enter choice: ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input! Enter a number.\n";
			continue;
		}
		switch (choice) {
		case 1: filename = "engine.csv";
			break;
		case 2: filename = "car_harness.csv";
			break;
		case 3: filename = "ecu.csv";
			break;
		case 4: cout << "Back to main menu. \n";
			break;
		default: cout << "Invalid choice! Enter 1-4.\n";

		}

		//load whichever they chose

		loadCSV(pinData, filename);
		if (pinData.empty()) {
			cout << "\n No data in " << filename << ".\n";
		}

		else {

			cout << "\n Row - Device - Wire Color - Signal Type - Direction - Destination \n";
			cout << "---------------------------------------------------------------------\n";
			for (const auto& entry : pinData) {
				cout << entry.row << " | " << entry.device << " | " << entry.wireColor << " | "
					<< entry.signalType << " | " << entry.direction << " | " << entry.destination << "\n";

			}
		}


	} while (choice != 4);
}

	// check if the row is there.loop and read all the rows, if its  there (row==row), then true, else false
	bool rowExists(const vector<PinMapping>&pinData, int row) {
	for (const auto& entry : pinData) {
		if (entry.row == row) return true;
	}
//	else {                                   //ha.. only checked the first entry and returned false. its a loop dumbass. 
    	return false;
}

	// find the row. oass the vector reference, and the integer row
	// for int i=0; i<int; ++i fot the int i (set to zero), if I is less than the riw we are looking for, incremebt up.  /// size() reuturns an unsigned int... size_t
	// if the row == row, return 
int findRowIndex(vector<PinMapping>& pinData, int row) {
	for (size_t i = 0; i < pinData.size(); ++i) {
		if (pinData[i].row == row)
			//because size() returns an unsigned integer we need to convert size t to int. okay so digging... this conversion is somthing called a typecast, and
			// a static-cast is basically happening at compile. it basically forces the conversion into whatever you call it. so you could static cast from a string
			//to an int if you wanted. implicity casting means it is implied, so kinda happens automatically. Explicitly means you are forcing this. so instead of just 
			//int i = 0;
		    //unsigned j = i; //i is implicitly casted from signed to unsigned
		    //i = j; //j is implicitly casted from unsigned to signed 
			// instead, you can use static_cast<int>(my/variable)
			return static_cast<int>(i); 
	}
	return -1; // Return -1 if not found
}

//inherent problem... the dropbear ecu doesnt have wire colors. these should be pins. but this jacks up the whole schema. for now, ecu will have
//pin designation as wire numner. 