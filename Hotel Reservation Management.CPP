//Author: Taniya S. Kulkarni


#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<process.h>
#include<ctype.h>

class restaurant
{
protected:
    int no_of_ppl;
    char name[40];
    int hour;
    int table;
public:
    void inputmain();
    void outputmain();
    void time();
    void assigntable();
};

void restaurant::time()
{
	time:
		int no;
		while(!(cin>>no))
		{
			cout<<"INVALID! \nENTER A VALID NUMERIC VALUE \n";
			cin.clear();
			cin.ignore();
		}
		if((no<=8)&&(no>=2))
			hour=no;
		else
		{
			cout<<"INVALID RESERVATION TIME!(RESTAURANT OPENING TIMES:2PM TO 8PM--> ENTER NUMBERIC VALUE ONLY)"<<endl;
			cout<<"Enter another Reservation Time Slot"<<endl;
			goto time;
		}
}

void restaurant::assigntable()
{
    table= no_of_ppl/4;
    if((no_of_ppl%4)!=0)
		table++;
}

void restaurant::inputmain()
{
    cout<<"\nEnter Name: ";
    gets(name);
    cout<<"Enter number of people: ";
	while(!(cin>>no_of_ppl))
    {
        cout<<"INVALID! \nENTER A VALID NUMERIC VALUE \n";
        cin.clear();
        cin.ignore();
    }
    cout<<"Enter time according to 12hr system(Restaurant timings- 2PM to 8PM) : ";
    time();
}
void restaurant ::outputmain()
{
    cout<<"\nNAME: "<<name;
    cout<<"\nNUMBER OF TABLES BOOKED: "<<table<<endl;
    cout<<"TIME: "<<hour<<" PM"<<endl;
}

class AC:public restaurant
{
	protected:
		int maxtable;
		char ambience[20];
	public:
		AC()
		{
			maxtable=10;
		}
		//Functions for AC
		void GET_AC_r();
		void INPUT_AC_r();
		void OUTPUT_AC_r();
		void ADD_AC_r();
		void VIEWP_AC_r();
		void MODIFYP_AC_r();
		void DELETEP_AC_r();
};

class nonAC:public restaurant
{
	protected:
		int maxtable;
		char drink[20];
	public:
		nonAC()
		{
			maxtable=10;
		}
		//Functions for NON AC
		void Get_NAC_r();
		void Input_N_AC_R();
		void Output_N_AC_R();
		void AddN_AC_R();
		void ModifyP_N_AC_R();
		void DeleteP_N_AC_R();
		void ViewP_N_AC_R();
};

int AC_atable = 10;
int nonAC_atable =10;

void AC::INPUT_AC_r()
{
	inputmain();
	assigntable();
	AC_atable= AC_atable-table;
	if(AC_atable<0)
		cout<<"RESERVATION NOT POSSIBLE DUE TO LACK OF SEATING!!";
	char ch;
	cout<<"\n WHICH AMBIENCE WOULD YOU LIKE?";
	cout<<endl<<" a.Candlelit \n b.Floral Display \n       ENTER 'a' OR 'b': ";
	cin>>ch;
	check:
		if(tolower(ch)=='a')
			strcpy(ambience,"Candlelit Setting");
		else if(tolower(ch)=='b')
			strcpy(ambience,"Floral Display");
		else
		{
			cout<<"Invalid Option Entered\nEnter a valid option: ";
			cin>>ch;
			goto check;
		}
}

void AC::OUTPUT_AC_r()
{
	outputmain();
	cout<<"AMBIENCE CHOSEN: "<<ambience<<endl;
}

void AC::GET_AC_r()
{
    char ch;
    fstream file;
    file.open("AC.dat", ios::out|ios::app|ios::binary);
    do
    {
		INPUT_AC_r();
		file.write((char*) this,sizeof(AC));
		cout<<"\nDo you wish to book another table?(Y-Yes/Any alphabet-No):";
		cin>>ch;
    }while(ch=='y'||ch=='Y');
    file.close();
}



void AC::ADD_AC_r()
{
    char ch;
    fstream file;
    file.open("AC.dat",ios::app|ios::binary);
    do
    {
		INPUT_AC_r();
		file.write((char*)this,sizeof(AC));
		cout<<"DO YOU WISH TO BOOK ANOTHER TABLE?(Y-Yes/Any alphabet-No):";
		cin>>ch;
    }while(ch=='y'|ch=='Y');
    file.close();
}
void AC::VIEWP_AC_r()
{
    fstream file;
    int flag=0;
    file.open("AC.DAT", ios::in|ios::binary);
    if(!file)
    {
		cout<<"\nFile not found!"<<endl;
		exit(0);
    }
    else
    {
		char checkname[40];
		cout<<"\nENTER NAME UNDER WHICH RESERVATION WAS MADE: ";
		gets(checkname);
		file.read((char*)this,sizeof(AC));
		while(!file.eof())
		{
			if(strcmpi(checkname,name)==0) 
			{
				cout<<"RESERVATION DETAILS:"<<endl;
				OUTPUT_AC_r();
				flag=1;
			}
			file.read((char*)this,sizeof(AC));
		}
		if(flag==0)
			cout<<"\nSORRY RESERVATION NOT FOUND!"<<endl;
		cout<<"\t\tPRESS ANY KEY TO CONTINUE!!";
		getch();
	}
    file.close();
}
void AC::MODIFYP_AC_r()
{
	fstream file;
	file.open("AC.DAT", ios::in| ios::out|ios::binary);
	if(!file)
	{
	    cout<<"\nFILE NOT FOUND"<<endl;
	    exit(0);
	}
	else
	{
	    char checkname[40];
	    long pos;
		int flag=0;
	    cout<<"\nENTER NAME UNDER WHICH RESERVATION WAS MADE: ";
	    gets(checkname);
	    file.read((char*)this,sizeof(AC));
	    while(!file.eof())
	    {
			if(strcmpi(checkname,name)==0)//strcmpi
			{
				file.seekg(0,ios::cur);
				INPUT_AC_r();
				file.seekp(file.tellg()-sizeof(AC));
				file.write((char*)this,sizeof(AC));
				flag =1;
			}
			else
			{
				cout<<"\t\tPRESS ANY KEY TO CONTINUE!!";
				getch();
			}
			file.read((char*)this,sizeof(AC));
		}
			if(flag==0)
				cout<<"\nSORRY RESERVATION NOT FOUND"<<endl;
			getch();
	}
	file.close();
}

void AC::DELETEP_AC_r()
{
	char delname[50];
	fstream del,file;
	cout<<"\nENTER NAME OF PERSON UNDER WHOM THE TABLE WAS RESERVED: ";
	gets(delname);
	del.open("delete_r.dat",ios::out|ios::binary);
	file.open("AC.dat",ios::in|ios::binary);
	if(!file)
	{
	    cout<<"\nFILE NOT FOUND!!";
	    exit(0);
	}
	else
	{
	    file.read((char*)this,sizeof(AC));
	    while(!file.eof())
	    {
			if(strcmpi(delname,name)!=0)
			{
				del.write((char*)this,sizeof(AC));
			}
			else
			{
				cout<<"\tRESERVATION DELETED!"<<endl;
				getch();
			}
			file.read((char*)this,sizeof(AC));
	    }
		getch();
	}
	del.close();
	file.close();
	remove("AC.dat");
	rename("delete_r.dat","AC.dat");
	getch();
}

void nonAC::Get_NAC_r()
{
    char ch;
    fstream file;
    file.open("nonAC.dat", ios::out|ios::app|ios::binary);
    do
    {
		Input_N_AC_R();
		file.write((char*)this,sizeof(nonAC));
		cout<<"\nDo you wish to book another table?(Y-Yes/Any alphabet-No):";
		cin>>ch;
    }while(ch=='y'||ch=='Y');
    file.close();
}

void nonAC::Input_N_AC_R()
{
	inputmain();
	assigntable();
	nonAC_atable= nonAC_atable-table;
	if(nonAC_atable<0)
		cout<<"RESERVATION NOT POSSIBLE DUE TO LACK OF SEATING!!";
	char ch;
	cout<<"\nWould you like to upgrade to bottomless drink?";
	cout<<endl<<" a.Yes \n b.No \n    Enter 'a' or 'b': ";
	cin>>ch;
	checkNAC:
		if(tolower(ch)=='a')									 
			strcpy(drink,"Bottomless Drinks");
		else if(tolower(ch)=='b')
			strcpy(drink,"Complementary Welcome Drink");
		else
		{
			cout<<"Invalid Option Entered\nEnter a valid option: ";
			cin>>ch;
			goto checkNAC;
		}
		
}

void nonAC::Output_N_AC_R()
{
	outputmain();
	cout<<"DRINKS CHOSEN: "<<drink<<endl;
}

void nonAC::ViewP_N_AC_R()
{
    fstream Vfile;
    char vname[50];
	int flag=0;
    cout<<"ENTER NAME UNDER WHICH TABLE WAS RESERVED: ";
    gets(vname);
    Vfile.open("nonAC.dat",ios::in|ios::binary);
    if(!Vfile)
    {
		cout<<"\nFILE NOT FOUND";
		exit(0);
    }
    else
    {
		Vfile.read((char*)this,sizeof(nonAC));
		while(!Vfile.eof())
		{
			if(strcmpi(vname,name)==0)
			{
				Output_N_AC_R();
				flag=1;
			}
			Vfile.read((char*)this,sizeof(nonAC));
		}
		if(flag==0)
			cout<<"RESERVATION NOT FOUND!!"<<endl;
		cout<<"\t\tPRESS ANY KEY TO CONTINUE!!";
		getch();
    }
   Vfile.close();
}

void nonAC::DeleteP_N_AC_R()
{
	char delname[50];
	fstream del,Vfile;
	cout<<"\nENTER NAME OF PERSON UNDER WHOM THE TABLE WAS RESERVED: ";
	gets(delname);
	del.open("delete_non.dat",ios::out|ios::binary);
	Vfile.open("nonAC.dat",ios::in|ios::binary);
	if(!Vfile)
	{
	    cout<<"\nFILE NOT FOUND!!";
	    exit(0);
	}

	else
	{
	    Vfile.read((char*)this,sizeof(nonAC));
	    while(!Vfile.eof())
	    {
			if(strcmpi(delname,name)!=0)
			{
				del.write((char*)this,sizeof(nonAC));
			}
			else
			{
				cout<<"\t\tReservation deleted"<<endl;
				getch();
			}
			Vfile.read((char*)this,sizeof(AC));
	    }
		getch();
	}
	del.close();
	Vfile.close();
	remove("nonAC.dat");
	rename("delete_non.dat","nonAC.dat");
	getch();
}


void nonAC::ModifyP_N_AC_R()
{
	fstream Vfile;
	Vfile.open("nonAC.DAT", ios::in| ios::out|ios::binary);
	if(!Vfile)
	{
	    cout<<"\nFILE NOT FOUND"<<endl;
	    exit(0);
	}
	else
	{
	    char checkname[40];
	    long pos;
		int flag=0;
	    cout<<"\nENTER NAME UNDER WHICH RESERVATION WAS MADE: ";
	    gets(checkname);
	    Vfile.read((char*)this,sizeof(nonAC));
	    while(!Vfile.eof())
	    {
			if(strcmpi(checkname,name)==0)//strcmpi
			{
				Vfile.seekg(0,ios::cur);
				Input_N_AC_R();
				Vfile.seekp(Vfile.tellg()-sizeof(nonAC));
				Vfile.write((char*)this,sizeof(nonAC));
				flag =1;
			}
			else
			{
				cout<<"\t\tPRESS ANY KEY TO CONTINUE!!";
				getch();
			}
			Vfile.read((char*)this,sizeof(nonAC));
		}
			if(flag==0)
				cout<<"\nSORRY RESERVATION NOT FOUND!"<<endl;
			getch();
	}
	Vfile.close();
}

void nonAC::AddN_AC_R()
{
	char ch;
	fstream Vfile;
	Vfile.open("nonAC.dat",ios::app|ios::binary);
	do
	{
	    Input_N_AC_R();
	    Vfile.write((char*)this,sizeof(nonAC));
	    cout<<"DO YOU WISH TO BOOK ANOTHER TABLE?(Y-Yes/Any alphabet-No):";
	    cin>>ch;
	}while(ch=='y'|ch=='Y');
	Vfile.close();
}


void main()  //Main
{
	clrscr();
	int choice, choice_AC, choice_NAC;
	char ch;
	do{
		cout<<"\t\t\t WELCOME TO THE RESTAURANT"<<endl;
		cout<<"\n\n~CHOOSE SECTION TO DINE IN~ \n  1.AC SECTION \n  2.NON AC SECTION"<<endl;
		cout<<"ENTER YOUR CHOICE(1/2): ";
		while(!(cin>>choice))
		{
			cout<<"IINVALID! \nENTER A VALID NUMERIC VALUE \n";
			cin.clear();
			cin.ignore();
		}
		switch(choice)
		{
			case 1:
			{
				AC ACobj;
				cout<<"YOU HAVE CHOSEN THE AC SECTION. \n WHAT DO YOU WISH TO DO?"<<endl;
				cout<<"\n  1.NEW RESERVATION \n  2.VIEW YOUR RESERVATION\n  3.MODIFY RESERVATIONS\n  4.ADD ANOTHER RESERVATION\n  5.DELETE RESERVATION \n    ENTER CHOICE: "<<endl;
				while(!(cin>>choice_AC))
				{
					cout<<"INVALID! \nENTER A VALID NUMERIC VALUE \n";
					cin.clear();
					cin.ignore();
				}
				switch(choice_AC)
				{
					case 1:
					{
						cout<<"\n\t\t\t\tNEW RESERVATION"<<endl;
						ACobj.GET_AC_r();
						break;
					}
					case 2:
					{
						cout<<"\n\t\t\tVIEW YOUR RESERVATION"<<endl;
						ACobj.VIEWP_AC_r();
						break;
					}
					case 3:
					{
						cout<<"\n\t\t\tMODIFY RESERVATIONS"<<endl;
						ACobj.MODIFYP_AC_r();
						break;
					}
					case 4:
					{
						cout<<"\n\t\t\tADD ANOTHER RESERVATION"<<endl;
						ACobj.ADD_AC_r();
						break;
					}
					case 5:
					{
						cout<<"\n\t\t\tDELETE RESERVATION"<<endl;
						ACobj.DELETEP_AC_r();
						break;
					}
					default:
							cout<<"\t\tWRONG CHOICE! "<<endl;
				}
				break;
			}

			case 2:
			{
				nonAC NACobj;
				cout<<"YOU HAVE CHOSEN THE NON-AC SECTION. \n WHAT DO YOU WISH TO DO?"<<endl;
				cout<<"\n  1.NEW RESERVATION \n  2.VIEW YOUR RESERVATION\n  3.MODIFY RESERVATIONS\n  4.ADD ANOTHER RESERVATION\n  5.DELETE RESERVATION \n    ENTER CHOICE: "<<endl;
				while(!(cin>>choice_NAC))
				{
					cout<<"INVALID! \nENTER A VALID NUMERIC VALUE \n";
					cin.clear();
					cin.ignore();
				}
				switch(choice_NAC)
				{
					case 1:
					{
						cout<<"\n\t\t\tNEW RESERVATION"<<endl;
						NACobj.Get_NAC_r();
						break;
					}
					case 2:
					{
						cout<<"\n\t\t\tVIEW YOUR RESERVATION"<<endl;
						NACobj.ViewP_N_AC_R();
						break;
					}
					case 3:
					{
						cout<<"\n\t\t\tMODIFY RESERVATIONS"<<endl;
						NACobj.ModifyP_N_AC_R();
						break;
					}
					case 4:
					{
						cout<<"\n\t\t\tADD ANOTHER RESERVATION"<<endl;
						NACobj.AddN_AC_R();
						break;
					}
					case 5:
					{
						cout<<"\n\t\t\tDELETE RESERVATION"<<endl;
						NACobj.DeleteP_N_AC_R();
						break;
					}
					default:
							cout<<"\t\tWRONG CHOICE! "<<endl;
				}
				break;
			}
			default:
				cout<<"\nWRONG CHOICE!"<<endl;
		}
		cout<<"\n DO YOU WISH TO CONTINUE?(Y-YES/ ANY ALPHABET-NO): ";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	getch();
}
