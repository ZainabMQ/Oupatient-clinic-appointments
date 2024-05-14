//  Group 03


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

struct patient {      
	string MRN;			// we will use 4 digits numbers
	string Gender;    	// M for male and F for female
	string DOB;			// format: dd/mm/yyy | 10 chars
	string Name;		// 30 chars
	string City;		// 10 chars
	string Mob;			// 10 chars
};

struct clinic {
	string Code;    	// 4 numbers code
	string Name;		// 20 chars
	string Doctor;		// 30 chars
	string Location;	// 6 chars
};

struct appointment{
	string MRN;			// we will use 4 digits numbers
	string Code;		// 4 numbers code
	string Date;		// format: dd/mm/yyy | 10 chars
	string Time;		// 24hrs format
};

//********  Global System Variables  ********

patient patients[100];
clinic clinics[100];
appointment appointments[100];

int TotalPats = 0;
int TotalClinics = 0;
int TotalAppts = 0;

//********  Functions Listing  ********

void DispMenu();
char MenuOption();
void ReadData();
void WriteData();
void CallService(char MyOption);
bool IsValidDate(string &MyDate);
bool IsValidMRN(string MRN);
bool IsValidMOB(string MOB);
bool IsValidTime(string &MyTime);

void AddPatient();

void AddClinic();
void ListClinics();
void DisplayClinic();
void DeleteClinic();
void ListClinicAppt();

void AddAppt();
void DisplayApptDetails();
void DeleteAppt();


int main() {
	
	char MyOption;
	ReadData();
	DispMenu();			
	
	do {				//Looping to keep the system active until the user enter Q for quitting
		MyOption = MenuOption();
		CallService(MyOption);
	} while(MyOption != 'Q');

	WriteData();
	return 0;
}

void DispMenu()	{		//Displaying the main menu
	system("cls");
	cout << endl;
	cout << "  ---------------------------------------------------------" <<endl;
	cout << "     Outpatient Clinic Appointment Management System" <<endl;
	cout << "                     Main Menu" <<endl;
	cout << "  ---------------------------------------------------------" <<endl;
	cout << "  1. Open a new clinic" <<endl;
	cout << "  2. Display clinic details" <<endl;
	cout << "  3. List all clinics" <<endl;
	cout << "  4. Delete a clinic" <<endl;
	cout << "  5. List a clinic appointments" <<endl;
	cout << "  6. Make a new appointment" <<endl;
	cout << "  7. Show appointment details" <<endl;
	cout << "  8. Delete an appointment" <<endl;	
	cout << "  9. Add a new patient" <<endl;
	cout << "  Q. Quit " <<endl;
	cout << "  M. Display this menu" <<endl;
	cout << "  ---------------------------------------------------------" <<endl;
}

char MenuOption(){		//Accepting and validating the user's choice from the menue
	char MyOption;
	bool retry;
	
	do {				//Looping until a valid choice is entered
		cout<< endl;
		cout <<"  Enter an option (M for menu) >  ";
		cin >> MyOption;
		
		MyOption = toupper(MyOption);	//Convert the choice to uppercasce
		cin.ignore(100,'\n');			//Clearing input buffer
		retry = true;
		
		if (MyOption == 'M') 			//Redisplaying the menu
			DispMenu();
		else if (MyOption == 'Q')		//Quitting option
			retry = false;  	
		else if (MyOption <'1' || MyOption >'9'){	//Validating that choice is within 1-9
			cout << "      Invalid Entry ... \n";	
		}	
		else 
			retry = false;		//Selected choice is a valid choice for the function (CallService)
	
	} while (retry);
	return MyOption;	
}

void CallService(char MyOption){		//Running the correct service based on the user's choice
	switch(MyOption) {
	case '1':
		AddClinic();
		break;
	case '2':
		DisplayClinic();
		break;
	case '3':
		ListClinics();
		break;
	case '4':
		DeleteClinic();
		break;
	case '5':
		ListClinicAppt();
		break;
	case '6':
		AddAppt();
		break;
	case '7':
		DisplayApptDetails();
		break;
	case '8':
		DeleteAppt();
		break;
	case '9':
		AddPatient();
		break;
	}
}

void ReadData() {	// Reading all data files and fill the appropriate arrays
	
	string MyLine;	
	
	ifstream PatFile("ClinSys_patients.dat");		//Reading from patients' data file

	while (getline(PatFile, MyLine)){				//Read a line from the file into MyLine
		stringstream REC(MyLine);		//Creating a string stream to help separating the various fields of each record
			
		getline(REC, patients[TotalPats].MRN, '|');		//Reading first field (MRN) until reaching the bar
		getline(REC, patients[TotalPats].Name, '|');		//Reading next field (Name) until reaching the bar
		getline(REC, patients[TotalPats].Gender, '|');
		getline(REC, patients[TotalPats].DOB, '|');
		getline(REC, patients[TotalPats].City, '|');
		getline(REC, patients[TotalPats].Mob);			//Reading the rest of the line as a mobile number
		TotalPats++;		//Increasing patients count by 1
	}
	PatFile.close();		//Closing the patients data file
		
	ifstream ClinicsFile("ClinSys_clinics.dat");		//Reading from clinics' data file

	while (getline(ClinicsFile, MyLine)){
		stringstream REC(MyLine);		//Creating a string stream to help separating the various fields of each record
			
		getline(REC, clinics[TotalClinics].Code, '|');		//Reading first field (Code) until reaching the bar
		getline(REC, clinics[TotalClinics].Name, '|');		//Reading next field (Name) until reaching the bar
		getline(REC, clinics[TotalClinics].Doctor, '|');
		getline(REC, clinics[TotalClinics].Location);		//Reading the rest of the line as a location	 		
		TotalClinics++;		//Increasing clinics count by 1
	}
	ClinicsFile.close();	//Closing the clinics data file
	
	ifstream ApptsFile("ClinSys_appointments.dat");		//Reading from appointments' data file

	while (getline(ApptsFile, MyLine)){
		stringstream REC(MyLine);		//Creating a string stream to help separating the various fields of each record
			
		getline(REC, appointments[TotalAppts].Code, '|');		//Reading first field (Code) until reaching the bar
		getline(REC, appointments[TotalAppts].MRN, '|');		//Reading next field (MRN) until reaching the bar
		getline(REC, appointments[TotalAppts].Date, '|');
		getline(REC, appointments[TotalAppts].Time);			
		TotalAppts++;		//Increasing appointments count by 1
	}
	ApptsFile.close();		//Closing the appointments data file
}

void WriteData() {		//Writing to patients' data file
	
	ofstream Patfile;	//Creating file stream for output
	Patfile.open("ClinSys_patients.dat");	//Assigning the actuel data file to the file stream
	
	if (Patfile.is_open()){		//Checking if the file is open
		
		for (int i=0; i< TotalPats; i++){		//Looping through the patients' array
			Patfile << patients[i].MRN << "|"	//Writing to the file stream the field followed by a bar
					<< patients[i].Name << "|"
					<< patients[i].Gender << "|"
					<< patients[i].DOB << "|"
					<< patients[i].City << "|" 
					<< patients[i].Mob << endl;
		}
	Patfile.close();		//Closing the datd file
	}
	else cout<< "File access error";
	
	ofstream ClinicsFile;		//Writing to clinics' data file
	ClinicsFile.open("ClinSys_clinics.dat");		//Assigning the actuel data file to the file stream
	
	if (ClinicsFile.is_open()){		//Checking if the file is open
	
		for(int i=0; i<TotalClinics; i++){		//Looping through the clinics' array
		
			ClinicsFile << clinics[i].Code << "|" 		//Writing to the file stream the field followed by a bar
						<< clinics[i].Name << "|" 
						<< clinics[i].Doctor << "|" 
						<< clinics[i].Location << endl;
		}	
	ClinicsFile.close();		//Closing the datd file
	}
	else cout<< "File access error";
	
	ofstream ApptsFile;		//Writing to appointments' data file
	ApptsFile.open("ClinSys_appointments.dat");		//Assigning the actuel data file to the file stream
	
	if (ApptsFile.is_open()){		//Checking if the file is open
		for (int i=0; i< TotalAppts; i++){		//Looping through the appointments' array
			ApptsFile	<< appointments[i].Code << "|"		//Writing to the file stream the field followed by a bar
						<< appointments[i].MRN  << "|" 
						<< appointments[i].Date << "|" 
						<< appointments[i].Time << endl;
		}
	ApptsFile.close();		//Closing the datd file
	}
	else cout<< "File access error";
}

bool IsValidDate(string &MyDate){	// getting the date as a string by reference to allow modification
	int slash1, slash2;
	slash1 = MyDate.find("/"); 			// check if MyDate contains month slash
	slash2 = MyDate.find("/",slash1+1);	// check if MyDate contains year slash

	if (slash1==-1 || slash2==-1)      // if either of the slashes is not found return false
		return false;

	if (MyDate.length()<8)   // checks for minimum date size  1/1/2000   8 chars.
		return false;
	
	for (int i =0; i<MyDate.length();i++){			// loops through MyDate to confirm that each is a number
		if (i == slash1 || i==slash2) continue;		// exclude the slashes
		if (!isdigit(MyDate[i])) return false;
	}
		
	int DateDay = stoi(MyDate.substr(0,slash1));    // convert the day to integer
	if (DateDay<1 || DateDay>31) 					// check for valid day, return false if not
		return false;
	
	int DateMonth = stoi(MyDate.substr(slash1+1,slash2));   // convert the month to integer
	if (DateMonth <1 || DateMonth >12) 						// check for valid month, return false if not
		return false;

    int DateYear = stoi(MyDate.substr(slash2+1));	// convert the year to integer	
    if (DateYear <1000 || DateYear>9999) 			// check for valid year, return false if not
		return false;
	
	if (slash1 == 1){				// if slash1 is 1 then day has 1 digit, so, we prefix it with 0
		MyDate = "0"+MyDate;
		if (slash2 == 3)			// if slash1 is 1 and slash2 is 3 then month is 1 digit, so, we prefix the month with 0 
			MyDate = MyDate.substr(0,3)+"0"+MyDate.substr(3);
	} 
	if (slash2 ==4)  	// if slash2 is 4 then month is 1 digit, so, we prefix the month with 0
		MyDate = MyDate.substr(0,3)+"0"+MyDate.substr(3);
			
	return true;
}

bool IsValidTime(string &MyTime){	// getting the MyTime as a string by reference to allow modification
	int colon1;
	colon1 = MyTime.find(":"); 			// check if MyTime contains a colon

	if (colon1==-1 || colon1 > 2)      // if the colon is not found or not in propper position return false
		return false;
	
	if (MyTime.length()<3)   // checks for minimum time size  0:0   3 chars.
		return false;
	
	for (int i =0; i<MyTime.length();i++){			// loops through MyTime to confirm that each is a number
		if (i == colon1) continue;		// exclude the colon
		if (!isdigit(MyTime[i])) return false;
	}
		
	int TimeHour = stoi(MyTime.substr(0,colon1));    // convert the hours to integer
	if (TimeHour>23) 					// check for valid hours, return false if not
		return false;
	
	int TimeMinute = stoi(MyTime.substr(colon1+1));   // convert the minutes to integer
	if (TimeMinute>59) 						// check for valid minutes, return false if not
		return false;
	
	if (colon1 == 1){				// if colon1 is 1 then hours has 1 digit, so, we prefix it with 0
		MyTime = "0"+MyTime;
	}
	
	if(MyTime.substr(3).length() == 1)		// if minutes is single digit, we prefix the month with 0
		MyTime = MyTime.substr(0,3)+"0"+MyTime.substr(3);
			
	return true;
}

bool IsValidMRN(string MRN){
	if (MRN.length()!=4) return false;
	for (int i=0; i<MRN.length();i++)			// loops through MRN to confirm that each is a number
		if (!isdigit(MRN[i])) return false;
	if (stoi(MRN)<1000) return false;				// confirms that the number is not starting with Zeros
	return true;
}

bool IsValidMOB(string MOB){
	if (MOB.length()!=10) return false;			//Check for valid mobile number length
	for (int i=0; i<MOB.length();i++)			// loops through Mobile number to confirm that each is a number
		if (!isdigit(MOB[i])) return false;
	return true;
}

//1.Oppen a new clinic
void AddClinic(){
	
	cout<< "  Enter the clinic's code (4 digits): ";
	getline(cin, clinics[TotalClinics].Code);
	
		for(int i=0; i<TotalClinics; i++){		//Checking if clinic already exists
			if(clinics[i].Code == clinics[TotalClinics].Code){
			cout<< "  clinic has already been added before";
			return;
		}
	}
	
	cout<< "  Enter the clinic's name (20 letters): ";		//Getting the rest of clinic's information and limiting the entry to a specified size
	getline(cin, clinics[TotalClinics].Name);
	clinics[TotalClinics].Name = clinics[TotalClinics].Name.substr(0,20);
	
	cout<< "  Enter the clinic's doctor (30 letters): ";
	getline(cin, clinics[TotalClinics].Doctor);
	clinics[TotalClinics].Doctor = clinics[TotalClinics].Doctor.substr(0,30);
	
	cout<< "  Enter the clinic's location (6 characters): ";
	getline(cin, clinics[TotalClinics].Location);
	clinics[TotalClinics].Location = clinics[TotalClinics].Location.substr(0,6);
	
	TotalClinics++;		//Increasing Clinics by 1
	cout<< "  Clinic added succefully";
}

//2.Display clinic details
void DisplayClinic(){
	string code;
	int index;
	bool found = false;
	
	cout << "\n  Enter Clinic Code: ";
	cin>> code;
	
		for (int i = 0; i < TotalClinics; i++) {		//Searching for clinic existence
			if (clinics[i].Code == code) {
				index = i;
				found = true;
				break;
			}
		}
		
		if (found){		//Displaying the clinic information 
			cout<< "  ------------------------------------------------------------" <<endl;
			cout<< "  Code  Name                    Doctor              Location" << endl;
			cout<< "  " << setw(6) << left <<clinics[index].Code << setw(22) << left << clinics[index].Name;
			cout<< "  " << setw(20) << left << clinics[index].Doctor.substr(0,18) << clinics[index].Location << endl;
			cout<< "  ------------------------------------------------------------" <<endl;
		}
		else cout<< "  Clinic was not found";
}

//3.Listing all Clinics
void ListClinics(){
	cout << endl << endl;
	cout<< "  ----------------------------------------------------------------------" << endl;
	cout<< "                            All Clinics                         " << endl << endl;
	cout<< "  Code  Clinic Name           Doctor Name                     Loc  " << endl;
	cout<< "  ----------------------------------------------------------------------" << endl;
	
	for (int i=0; i<TotalClinics; i++){		//Looping through clinics' array to list clinics' data
		cout<< "  " << setw(6) << left << clinics[i].Code << setw(22) << clinics[i].Name;	//setw reserves the specified spaces for data display
		cout<< setw(32) << clinics[i].Doctor << setw(8) << clinics[i].Location << endl;
	}
	cout<< "  ----------------------------------------------------------------------" << endl;
}

//4.Delete a clinic
void DeleteClinic(){
	string clinicCode;
    int clinicIndex = -1;

    cout << "  Enter the code of the clinic you want to delete: ";
    cin >> clinicCode;

    for(int i = 0; i < TotalClinics; i++) {		// Search for the clinic with the given code
        if(clinics[i].Code == clinicCode) {
            clinicIndex = i;
            break;
        }
    }
    
    for(int i=0; i<TotalAppts; i++){
    	if(appointments[i].Code == clinicCode){
    		cout<< "  Clinic can not be deleted, it has reserved appointments" << endl;
    		return;
		}
	}

    if(clinicIndex != -1) {
        for(int j = clinicIndex; j < TotalClinics - 1; j++) {		// Shift the remaining clinics one position up in the array
            clinics[j] = clinics[j + 1];
        }

        TotalClinics--;		// Decrease the total number of clinics

        cout << "  Clinic deleted successfully." << endl;
    } else cout << "  Clinic was not found" << endl;
}

//5.List appointments for a specific clinic 
void ListClinicAppt(){
	string code;
	int index, num=1;
	bool found = false, HeaderPrinted = false;
	
	cout<< "\n  Enter Clinic Code: ";
	cin>> code;
	
	for (int i = 0; i < TotalClinics; i++) {		// Search for the clinic with the given code
		if (clinics[i].Code == code) {
			index = i;
			found = true;
			break;
		}
	}
	
	if(!found){
		cout<< "\n  Clinic was not found" << endl;
		return;
	}
	
	cout << "  -------------------------------------------------------------------" <<endl;
	cout<< "  CLinic: " << setw(6) << left << clinics[index].Code << setw(22) << left <<clinics[index].Name << clinics[index].Doctor << endl;
	cout << "  -------------------------------------------------------------------" << endl;
	
	
	for (int i = 0; i < TotalAppts; i++) {	//Looping through appointments' array
		if (appointments[i].Code == code) {	//Getting the appointments reserved by the given clinic code
			for(int a=0; a<TotalPats; a++){	//Looping through patients' array
				if(appointments[i].MRN == patients[a].MRN){ //Getting the patient that reserved the appointment
					if(!HeaderPrinted){
						cout<< "  #    Patient information                      Date        Time" << endl;
						cout << "  -------------------------------------------------------------------" << endl;
						HeaderPrinted = true;
					}
					cout<< "  " << num++ << "    ";
					cout<< setw(6) << left << patients[a].MRN << setw(3) << left << patients[a].Gender << setw(12) << left <<  patients[a].DOB;
					cout<< setw(20) << left << patients[a].Name.substr(0,18) << setw(12) << left << appointments[i].Date << appointments[i].Time << endl;
					
				}
			}
		}	
	}
	if(!HeaderPrinted) cout<< "  This clini has no appointments" << endl;
	//cout << "  -------------------------------------------------------------------" <<endl;
}

//6.Make a new appointment
void AddAppt(){
	
    string mrn, code;
    bool patientFound = false, ValidDate = false, clinicFound = false;
    int patientIndex = -1, clinicIndex = -1;

	do {
		cout << "  Enter Patient MRN: ";
    	cin >> mrn;
    
    	for (int i = 0; i < TotalPats; i++) {	//Check for patient existence
       		if (patients[i].MRN == mrn) {
       	    	patientFound = true;
       	  		break;
      		}
   		}
		if (!patientFound) {
       		cout << "  Patient was not found" << endl;
    	}	
	} while (!patientFound);
    
	do {
		cout << "  Enter Clinic Code: ";
    	cin >> code;
    
    	for (int i = 0; i < TotalClinics; i++) {	//Check for clinic existence
        	if (clinics[i].Code == code) {
            	clinicFound = true;
            	break;
        	}
    	}
    	
    	if (!clinicFound) {
        	cout << "  Clinic was not found" << endl;
    	}	
	} while (!clinicFound);
        
	do {
		cout << "  Enter Date (dd/mm/yyyy): ";		//Getting Date and check for validation
    	cin >> appointments[TotalAppts].Date;
    	
		if(IsValidDate(appointments[TotalAppts].Date))
			break;
		else {
			cout<< "  Invalid date" << endl;
			continue;
			}
		
	} while(true);
	
	do {		
		cout << "  Enter Time (HH:MM): ";		//Getting Time and check for validation
    	cin >> appointments[TotalAppts].Time;
    	
    	if(IsValidTime(appointments[TotalAppts].Time))
    		break;
    		
		cout<< "  Invalid time" << endl;	
	} while (true);
	
	for (int i = 0; i< TotalAppts; i++){		//check if entered appointment is already reserved
		if(appointments[i].Code == code && appointments[i].Date == appointments[TotalAppts].Date && appointments[i].Time == appointments[TotalAppts].Time){
		   	cout<< "  Appintment's time is already reserved";
			return;			
		}
	}
		
    appointments[TotalAppts].MRN = mrn;			
    appointments[TotalAppts].Code = code;
    TotalAppts++;		//Increacing appointments by 1
    cout << "\n  Appointment was added successfully" << endl;
}

//7.Display patient's appointments
void DisplayApptDetails(){
	
	string mrn, code, ClinName, pat;
	int index=-1;
	bool PatFound = false, ClinFound = false, HeaderPrinted = false;
	
	do {		//Getting and Validating MRN
		cout << "\n  Enter patient MRN: ";
		cin >> mrn;
	
		for(int i=0; i<TotalPats;i++){
			if(patients[i].MRN == mrn){
				cout<< "  ----------------------------------------------" << endl;
				cout<< "  patient: " << setw(6) << left << patients[i].MRN << setw(3) << left << patients[i].Gender << patients[i].Name << endl;
				cout<< "  ----------------------------------------------" << endl;
				PatFound = true;
				break;
			}
		}
	if (!PatFound)
     	cout << "  Patient was not found" << endl;	
	
	} while (!PatFound);
	
	for(int i =0; i< TotalAppts; i++){		//Listing patient appointments for the specified patient
		if(appointments[i].MRN == mrn){
			index = 0;
			for(int j = 0; j< TotalClinics; j++){
				if(clinics[j].Code == appointments[i].Code){
					if(!HeaderPrinted){
						cout<< "  Code  Clinic name           Date        Time" << endl;
						cout<< "  ----------------------------------------------" << endl;
						HeaderPrinted = true;
					}
					cout<< "  " << setw(6) << left << clinics[j].Code << setw(22) << left << clinics[j].Name;
					cout<< setw(12) << left << appointments[i].Date << appointments[i].Time << endl;
				}
			}
		}	
	}
	
	if(index == -1){
		cout<< "\n  no available appointments for the above patient" << endl;	
	}
}

//8.Delete an appointment
void DeleteAppt(){
	
	string mrn, code;
	int index = -1;
	bool PatFound = false, ClinFound = false;
	
	do {		//Getting and Validating MRN
		cout << "\n  Enter patient MRN: ";
		cin >> mrn;
	
		for(int i=0; i<TotalPats;i++){
			if(patients[i].MRN == mrn){
				PatFound = true;
				break;
			}
		}
	if (!PatFound)
     	cout << "  Patient was not found" << endl;	
	
	} while (!PatFound);
	
	do {		//Getting and Validating clinic code
		cout << "  Enter Clinic Code: ";
		cin >> code;
		for(int i=0; i<TotalClinics;i++){
			if(clinics[i].Code == code){
				ClinFound = true;
				break;
			}
		}
		if (!ClinFound)
     		cout << "  Clinic was not found" << endl;	
			
	} while (!ClinFound);
	
	for (int i = 0; i < TotalAppts; i++) {		//check for appointment existence
		if (appointments[i].MRN == mrn && appointments[i].Code == code) {
			index = i;
			break;
		}	
	}

	if (index!= -1) {
		if (index != TotalAppts-1) //Switching the last appointment with the deleted appointment
			appointments[index] = appointments[TotalAppts-1];
	
		TotalAppts--;		//Reducing appointments by 1
		cout << "  Appointment was deleted successfully" << endl;
	}
	 
 	else 
 		cout << "  Appointment was not found" << endl;
 	 	
}

//9.Add a patient
void AddPatient(){
		
	do {		//Looping until a valid MRN is entered
		cout << "  Enter the patient Medical Record Number (4 digits): ";
    	cin >> patients[TotalPats].MRN;
    	cin.ignore(100,'\n');
    
  		if(IsValidMRN(patients[TotalPats].MRN))
			break;
			
		cout<< "  MRN is not valid" << endl;
	} while (true);
	
	
	for(int i=0; i<TotalPats; i++){		//Checking if patient already exists
		if(patients[i].MRN == patients[TotalPats].MRN){
			cout<< "  Patient has already been added before";
			return;
		}
	}
    	
    do {		//Looping until a valid gender is entered
    	cout << "  Enter the patient Gender (M/F): ";
    	cin >> patients[TotalPats].Gender;
    	
    	if (patients[TotalPats].Gender == "m") 	//Converting Gender to uppercase
			patients[TotalPats].Gender = "M";
			
    	if (patients[TotalPats].Gender == "f") 
			patients[TotalPats].Gender = "F";
    	
    	if(patients[TotalPats].Gender == "M" || patients[TotalPats].Gender == "F")
    		break;
    		
    	cout<< "  Invalid gender" << endl;
    	
	} while(true);
    
    do {		//Looping until a valid date is entered
    	cout << "  Enter the patient Date of Birth (dd/mm/yyyy): ";
    	cin >> patients[TotalPats].DOB;
    	
    	if(IsValidDate(patients[TotalPats].DOB))
    		break;
    	cout<< "  Invalid Date";
    	
	} while (true);
    
    cout << "  Enter the patient Name (30 letters): ";		//Getting the rest of patient's information and limit entry to the specified size
    cin.ignore(100, '\n');
    getline(cin, patients[TotalPats].Name);
    patients[TotalPats].Name = patients[TotalPats].Name.substr(0,30);
    
    cout << "  Enter the patient City (10 letters): ";
    getline(cin, patients[TotalPats].City);
    patients[TotalPats].City = patients[TotalPats].City.substr(0,10);
    
    do {		//Getting and Validating mobile number
    	cout << "  Enter the patient Mobile Number (10 digits): ";
    	cin >> patients[TotalPats].Mob;
    	if(IsValidMOB(patients[TotalPats].Mob))
    		break;
    	cout<< "  Phone Number is not valid" << endl;		
	} while(true);
    
    TotalPats++;
    cout << "  Patient has been added successfully." << endl;
}
