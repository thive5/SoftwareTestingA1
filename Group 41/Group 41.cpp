#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

//global variables
const int totalrooms = 16;
string line[totalrooms];
string dummy, g_un[255], g_pwd[255], silver = "Silver", gold = "Gold";
int state = 0, Froom, Chours;
float priceS = 9.00, priceG = 12.00, finalprice;

// global to import into cancelbooking
string Dname;
int Groom = 0, Ghours = 0, GbookingID = 0;
float Gprice = 0;

struct customer   //customer details
{
public:
	char structUN[255];
	char structPWD[255];
	int room_number[255];
	int total_hours[255];
	float total_price[255];
	int bookingID[255];

	void registerstruct()
	{
		cout << "Please enter the details below " << endl;
		getline(cin, dummy);
		cout << "Username : ";
		cin.getline(structUN, 255);
		cout << "Password : ";
		cin.getline(structPWD, 255);
	}
};

void loginaccount();
void Registration();
void registernewaccount();
void Booking();
float calcpayment(int, int);
void choice();
void searchbooking();
void Cancelbooking();

int main()
{
	Registration();

	system("pause");
	return 0;
}


void Cancelbooking()
{
	ifstream fileignore;
	ofstream write, OutputFile, newrite;
	string NAME[255];
	int kr[255], kh[255], kid[255], cc = 0, nr = 0, g = 0;
	float fp[255];

	system("cls");

	fileignore.open("bookingrecord.txt");
	while (!fileignore.eof())
	{
		g++;
		getline(fileignore, NAME[g]);
		fileignore >> kr[g];
		fileignore >> kh[g];
		fileignore >> fp[g];
		fileignore >> kid[g];
		fileignore.ignore();
		fileignore.ignore();

	}
	cout << "============================================" << endl << endl;
	cout << "      Your recent Booking details           " << endl << endl;
	cout << "\t 1. Username    : " << Dname << endl;
	cout << "\t 2. Room Number : " << Groom << endl;
	cout << "\t 3. Total Hours : " << Ghours << endl;
	cout << "\t 4. Final Price : RM " << fixed << setprecision(2) << Gprice << endl;
	cout << "\t 5. Booking ID  : " << GbookingID << endl << endl;
	cout << "============================================" << endl << endl;


	cout << "\n\nAre you sure to cancel the booking?\n If yes, press 1\n If not, press 2" << endl;
	cout << "Your choice: ";
	cin >> cc;

	while (cc > 2)
	{
		cout << "\n\nOh no! You choose the invalid number!\nPlease choose again!" << endl;
		cout << "Your choice: ";
		cin >> cc;
	}
	if (cc == 1)
	{
		newrite.open("newbookingrecord.txt");
		for (int i = 1; i < g; i++)
		{
			newrite << NAME[i] << endl;
			newrite << kr[i] << endl;
			newrite << kh[i] << endl;
			newrite << fp[i] << endl;
			newrite << kid[i];
			newrite << endl;
		}

		fileignore.close();
		newrite.close();
		remove("bookingrecord.txt");
		rename("newbookingrecord.txt", "bookingrecord.txt");

		line[kr[g] - 1] = { "Yes" };
		OutputFile.open("bookingavailable123.txt");
		for (int a = 0; a < totalrooms; a++)
		{
			OutputFile << line[a] << endl; //changes yes to no
		}
		OutputFile.close();

		cout << "Your booking canceled successfuly!!!" << endl;
		cout << "Do you want do new reservation?\nIf want, press 1 \nIf not, press 2" << endl;
		cout << "Your choice: ";
		cin >> nr;
		while (nr > 2)
		{
			cout << "Oh no! You choose the invalid number!\nPlease choose again!" << endl;
			cin >> nr;
		}
		if (nr == 1)
		{
			Booking();
		}
		else if (nr == 2)
		{
			cout << "Let's back to main menu!" << endl;
			choice();
		}
	}
	else if (cc == 2)
	{
		cout << "Let's back to main menu!" << endl;
		choice();
	}
}

float calcpayment(int Froom, int Chours)
{
	if (Froom <= 9 && Chours > 2)
	{
		finalprice = priceS * Chours * 0.9;
	}
	else if (Froom <= 9 && Chours <= 2)
	{
		finalprice = priceS * Chours;
	}
	else if (Froom >= 10 && Chours > 2)
	{
		finalprice = priceG * Chours * 0.8;
	}
	else
	{
		finalprice = priceG * Chours;
	}
	return finalprice;
}

void Booking()
{
	ifstream InputFileBR, InputFile;
	ofstream OutputFileBR, OutputFile;
	string pbN[255], LUsername;
	int pbR[255], pbH[255];
	int BID[255], finalBID = 0, newBID = 0, Croom, LHours = 0;
	float BRprice[255], LFinalPrice = 0;
	int number, b = 0, amount = 0, ch;

	system("cls");

	InputFile.open("bookingavailable123.txt");
	if (InputFile.fail())
	{
		cout << "nofile" << endl;
	}
	else
	{
		while (!InputFile.eof())
		{
			for (int i = 0; i < totalrooms; i++)
			{
				getline(InputFile, line[i]);
			}
			InputFile.ignore();
		}
		InputFile.close();
	}
	InputFile.close();

	cout << "============================================================" << endl;
	cout << "=                                                          =" << endl;
	cout << "=               Welcome to the Booking page                =" << endl;
	cout << "=                                                          =" << endl;
	cout << "=                Booking information below                 =" << endl;
	cout << "=                                                          =" << endl;
	cout << "=                                                          =" << endl;
	cout << "=----------------------------------------------------------=" << endl;
	cout << "=" << setw(16) << "ROOM NAME" << setw(12) << "AVAILABLE" << setw(8) << "TYPE" << setw(15) << "PRICE/HOUR" << setw(8) << "=" << endl;
	cout << "=----------------------------------------------------------=" << endl;

	for (int i = 0; i < totalrooms; i++)
	{
		if (i + 1 <= 9)
		{
			cout << fixed << setprecision(2);
			cout << "=" << setw(10) << "R0" << i + 1 << setw(7) << "|" << setw(7) << line[i] << setw(5) <<
				"|" << setw(7) << silver << setw(2) << "|" << setw(9) << priceS << setw(11) << "=" << endl;
		}
		else
		{
			cout << "=" << setw(9) << "R" << i + 1 << setw(7) << "|" << setw(7) << line[i] << setw(5) <<
				"|" << setw(5) << gold << setw(4) << "|" << setw(9) << priceG << setw(11) << "=" << endl;
		}
		cout << "=----------------------------------------------------------=" << endl;
	}

	cout << "\n\nFor Gold rooms you would get 20% discount for booking of more than 2 hours" << endl;
	cout << "For Silver rooms you would get 10% discount for booking of more than 2 hours" << endl;
	cout << "\nSelect your preferred room" << endl;
	cout << "Room number : "; cin >> Croom; cout << endl;

	while (Croom > 16)
	{
		cout << "\nInvalid Room number please enter correct room number " << endl;
		cout << "Room number : "; cin >> Croom; cout << endl;
	}

	while (line[Croom - 1] == "No")
	{
		cout << "\nThe room is occupied please enter correct room number " << endl;
		cout << "Room number : "; cin >> Croom; cout << endl;
	}

	cout << "Enter the number of hours : "; cin >> Chours; cout << endl;
	Froom = Croom;
	// calculate BID from previous records
	InputFileBR.open("bookingrecord.txt");
	if (InputFileBR.fail())
	{
		cout << "nofile" << endl;
	}
	else
	{
		while (!InputFileBR.eof())
		{
			b++;
			InputFileBR.ignore();
			InputFileBR.ignore();
			getline(InputFileBR, pbN[b]);
			InputFileBR >> pbR[b];
			InputFileBR >> pbH[b];
			InputFileBR >> BRprice[b];
			InputFileBR >> BID[b];
			InputFileBR.ignore();
			InputFileBR.ignore();
			InputFileBR.ignore();
			amount++;
		}
		InputFileBR.close();
	}
	InputFileBR.close();
	// loop for get last booking ID & generate new booking id
	for (int a = 1; a < amount + 1; a++)
	{
		newBID = BID[a] + Croom;//takes the final BID & adds room number
		if (newBID != BID[a])
		{
			finalBID = newBID;
		}
		else
		{
			finalBID = newBID + 1; //adds 1 if got similar previous booking id
		}
	}

	calcpayment(Froom, Chours);

	LFinalPrice = finalprice;
	LHours = Chours;
	LUsername = g_un[1];

	cout << "Your bill is : RM " << fixed << setprecision(2) << finalprice << endl << endl;
	cout << "============================================" << endl << endl;
	cout << "             Booking details                " << endl << endl;
	cout << "\t 1. Username    : " << LUsername << endl;
	cout << "\t 2. Room Number : " << Croom << endl;
	cout << "\t 3. Total Hours : " << LHours << endl;
	cout << "\t 4. Final Price : RM " << fixed << setprecision(2) << LFinalPrice << endl;
	cout << "\t 5. Booking ID  : " << finalBID << endl;

	//updates recent booking availabitlity into txt	
	line[Froom - 1] = { "No" };
	OutputFile.open("bookingavailable123.txt");
	for (int a = 0; a < totalrooms; a++)
	{
		OutputFile << line[a] << endl; //changes yes to no
	}
	OutputFile.close();
	//write new booking record
	OutputFileBR.open("bookingrecord.txt", ios::app);
	OutputFileBR << "\n" << LUsername << endl;
	OutputFileBR << Croom << endl;
	OutputFileBR << LHours << endl;
	OutputFileBR << LFinalPrice << endl;
	OutputFileBR << finalBID << endl;
	OutputFileBR.close();

	cout << "\n\n\nThank You for booking with us" << endl;
	cout << "\n  | To return to booking menu press 1   | "
		"\n  | To return to main menu press 2      | " << endl;
	cout << "\n\nEnter your choice here : ";
	cin >> ch;

	while (ch == 0 || ch > 2)
	{
		cout << "Invalid input enter correct key here : ";
		cin >> ch;
	}
	if (ch == 1)
	{
		choice();
	}
	else
	{
		Registration();
	}
}

void searchbooking()//show the account details and booking details
{
	ifstream inFile;
	char Uname[255];
	char UNAME[255];
	string Dname;
	int BookedRooms[255], BookedID[255], BookedHours[255], UserBID;
	float BookedPrice[255];
	int d = 0, Ch = 0, state = 0, input1 = 0;

	system("cls");

	cout << "============================================================" << endl;
	cout << "=                                                          =" << endl;
	cout << "=            Welcome to the Search Booking page            =" << endl;
	cout << "=                                                          =" << endl;
	cout << "=----------------------------------------------------------=" << endl;

	cout << " To search your booking details using Booking ID press 1 " << endl;
	cout << " To search your booking details using Username press 2   " << endl;
	cout << "\n\nEnter your choice here : ";
	cin >> input1;
	while (input1 == 0 || input1 > 2)
	{
		cout << "Invalid input enter correct key here : ";
		cin >> input1;
	}

	if (input1 == 1)
	{
		cout << "\n\nEnter your Booking id here : "; cin >> UserBID;

		inFile.open("bookingrecord.txt");
		if (inFile.fail())
		{
			cout << "nofile" << endl;
		}
		else
		{
			while (!inFile.eof())
			{
				
				d++;
				inFile.getline(Uname, 255); //string
				inFile >> BookedRooms[d];
				inFile >> BookedHours[d];
				inFile >> BookedPrice[d];
				inFile >> BookedID[d];
				inFile.ignore();
				inFile.ignore();
				//inFile.ignore();

				if ((UserBID == BookedID[d]))
				{
					Dname = Uname;
					Groom = BookedRooms[d];
					Ghours = BookedHours[d];
					Gprice = BookedPrice[d];
					GbookingID = BookedID[d];
					state = 1; //booking id match
				}
				else
				{
					state = 0;
				}

			}
		}
		inFile.close();
	}

	if (input1 == 2)
	{
		getline(cin, dummy);
		cout << "\n\nEnter your Username here : "; cin.getline(UNAME, 255);

		inFile.open("bookingrecord.txt");
		if (inFile.fail())
		{
			cout << "nofile" << endl;
		}
		else
		{
			while (!inFile.eof())
			{
				if (!strcmp(Uname, UNAME))
				{
					Dname = Uname;
					Groom = BookedRooms[d];
					Ghours = BookedHours[d];
					Gprice = BookedPrice[d];
					GbookingID = BookedID[d];
					state = 1; //username match
				}
				else
				{
					state = 2;
				}
				d++;
				inFile.getline(Uname, 255);
				inFile >> BookedRooms[d];
				inFile >> BookedHours[d];
				inFile >> BookedPrice[d];
				inFile >> BookedID[d];
				inFile.ignore();
				inFile.ignore();
				//inFile.ignore();
			
			}
		}
		inFile.close();
	}
	if (state == 1)
	{
		cout << "============================================" << endl << endl;
		cout << "             Booking details                " << endl << endl;
		cout << "\t 1. Username    : " << Dname << endl;
		cout << "\t 2. Room Number : " << Groom << endl;
		cout << "\t 3. Total Hours : " << Ghours << endl;
		cout << "\t 4. Final Price : RM " << fixed << setprecision(2) << Gprice << endl;
		cout << "\t 5. Booking ID  : " << GbookingID << endl << endl;
		cout << "============================================" << endl << endl;
	}
	if (state == 2)
	{
		cout << "\n\nInvalid Username " << endl;
	}

	if (state == 0)
	{
		cout << "\n\nInvalid Booking ID " << endl;
	}

	cout << " \n\n To cancel booking press 1  " << endl;
	cout << " To go to main menu press 2 " << endl;
	cout << " What is your choice? Press button: ";
	cin >> Ch;
	while (Ch == 0 || Ch > 2)
	{
		cout << "Invalid input enter correct key here : ";
		cin >> Ch;
	}
	switch (Ch)
	{
	case 1: Cancelbooking();
		break;
	case 2: Registration();
		break;
	default:
		break;
	}
}

void choice()
{
	system("cls");
	int cho = 0; //cho=choice,the user can choose to booking, search and check the booking

	while (cho != 1, 2, 3)
	{ //use while loop to make sure whole process can go through smoothly when the user type the wrong number
		cout << "==========================================================" << endl;
		cout << "=                                                        =" << endl;
		cout << "=              Welcome to the booking menu               =" << endl;
		cout << "=                                                        =" << endl;
		cout << "=    For account details and booking details press 1     =" << endl;
		cout << "=              To book a new room press 2                =" << endl;
		cout << "=               To return to main menu 3                 =" << endl;
		cout << "=                                                        =" << endl;
		cout << "==========================================================" << endl;
		cout << "\n Where you wanna go? Press the button: ";
		cin >> cho;
		cout << endl;

		if (cho == 1) {
			cout << "\n \n \n \n";
			searchbooking(); // let user go to search the part
		}

		else if (cho == 2) {
			cout << "\n \n \n \n";
			Booking(); //let user go to booking part
		}

		else if (cho == 3) {
			cout << "\n \n \n \n";
			Registration(); //let user go to registeration part
		}
		else
			cout << "Oh no! You pressed the wrong button! Please choose again~ \n \n" << endl;
	}
}

void registernewaccount()
{
	ifstream inputfile;
	ofstream outputfile;
	customer a;
	char Run[255], Rpwd[255];
	int ch;

	system("cls");

	cout << "==========================================================" << endl;
	cout << "=                                                        =" << endl;
	cout << "=             Welcome to registeration page              =" << endl;
	cout << "=                                                        =" << endl;
	cout << "=                 To continue press 1                    =" << endl;
	cout << "=             To go to login page press 2                =" << endl;
	cout << "=              To return to main menu 3                  =" << endl;
	cout << "=                                                        =" << endl;
	cout << "==========================================================" << endl;
	cout << "\n\nEnter your choice here : ";
	cin >> ch;

	while (ch == 0 || ch > 3)
	{
		cout << "Invalid input enter correct key here : ";
		cin >> ch;
	}
	if (ch <= 3)
	{
		switch (ch)
		{
		case 1:
			cout << "\n\n\n" << endl;
			a.registerstruct();
			outputfile.open("logininfo.txt", ios::app | ios::ate);
			outputfile << endl;
			outputfile << endl;
			outputfile << a.structUN << endl;
			outputfile << a.structPWD << endl;
			outputfile.close();

			cout << "Account registered succesfully \n"
				"Thank you for registering with us" << endl;

			cout << "\n  | To go to login page press 1      | "
				"\n  | To return to main menu press 2   | " << endl;

			cout << "\n\nEnter your choice here : ";
			cin >> ch;

			while (ch == 0 || ch > 2)
			{
				cout << "Invalid input enter correct key here : ";
				cin >> ch;
			}
			if (ch == 1)
			{
				loginaccount();
			}
			else
			{
				Registration();
			}
			break;

		case 2:loginaccount();
			break;
		default:Registration();
		}
	}
}

void loginaccount()
{
	ifstream inputFile;
	char registeredUN[255], registeredPWD[255];
	customer a;
	int ch;

	system("cls");

	cout << "==========================================================" << endl;
	cout << "=                                                        =" << endl;
	cout << "=            Welcome to login account page               =" << endl;
	cout << "=                                                        =" << endl;
	cout << "==========================================================" << endl;
	cout << endl << endl;
	a.registerstruct();
	inputFile.open("logininfo.txt"); //opening the booking record file

	while (!inputFile.eof())
	{
		inputFile.getline(registeredUN, 255); // get the username
		inputFile.getline(registeredPWD, 255); //get the booking id

		if (!strcmp(registeredUN, a.structUN))// username
		{
			if (!strcmp(registeredPWD, a.structPWD)) //booking id
			{
				state = 1;
				cout << "\nVerified user!" << endl;   // username and booking id match
				g_un[1] = registeredUN;
				break;
			}
			else
			{
				state = 2;
				break;
			}
		}
	}
	if (state == 1)
	{
		cout << "\n\nVerified user!" << endl;
		cout << "Username and password match" << endl;
		inputFile.close();
		cout << "g_un : " << g_un[1] << endl;
		choice();//to start booking 
	}
	else if (state == 2)
	{
		cout << "\nWrong Password! try again !" << endl;
	}
	else if (state == 0)
	{
		cout << "\n\nNo user found! try again" << endl;
	}

	cout << "\n  | To try again press 1               | "
		"\n  | To register new account press 2    | "
		"\n  | To return to main menu press 3     | " << endl;
	cout << "\n\n Enter your choice here : ";
	cin >> ch;
	while (ch == 0 || ch > 3)
	{
		cout << "Invalid input enter correct key here : ";
		cin >> ch;
	}
	if (ch <= 3)
	{
		switch (ch)
		{
		case 1: ::state = 0; loginaccount();
			break;
		case 2: ::state = 0; registernewaccount();
			break;
		default: ::state = 0; Registration();
		}
	}
}

void Registration()
{
	int chooser = 0;
	system("cls");
	cout << "==========================================================" << endl;
	cout << "=                                                        =" << endl;
	cout << "=             Welcome to JJS Karaoke Kampar              =" << endl;
	cout << "=    Our operating hours are from 11 a.m to 10 p.m       =" << endl;
	cout << "=    Open every weekdays and weekends except Monday      =" << endl;
	cout << "=                                                        =" << endl;
	cout << "=               You are in main menu page                =" << endl;
	cout << "=                                                        =" << endl;
	cout << "=    To login with your registered account press 1       =" << endl;
	cout << "=           To create a new account press 2              =" << endl;
	cout << "=            To search your booking press 3              =" << endl;
	cout << "=             To exit system press any key               =" << endl;
	cout << "=                                                        =" << endl;
	cout << "==========================================================" << endl;

	cout << "\n\nEnter your choice here : ";
	cin >> chooser;

	while (chooser == 0 || chooser > 4)
	{
		cout << "Invalid input enter correct key here : ";
		cin >> chooser;
	}
	if (chooser <= 4)
	{
		switch (chooser)
		{
		case 1:loginaccount();
			break;
		case 2:registernewaccount();
			break;
		case 3:searchbooking();
			break;
		default: exit(0);
		}
	}
}