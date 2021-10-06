#include<iostream>
#include<fstream>
#include<iomanip>
#include<windows.h>
using namespace std;

class student
{
	int rollno;
	char name[50];
	int p_marks, c_marks, m_marks, e_marks, cs_marks;
	double per;
	char grade;
	void calculate();	
public:
	void getdata();	
	void showdata() const;	
	void show_tabular() const;
	int retrollno() const;
}; 


void student::calculate()
{
	per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
	if(per>=60)
		grade='A';
	else if(per>=50)
		grade='B';
	else if(per>=33)
		grade='C';
	else
		grade='F';
}

void student::getdata()
{
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The first Name of student ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in AP out of 100 : ";
	cin>>p_marks;
	cout<<"\nEnter The marks in AC out of 100 : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in PF out of 100 : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in FE out of 100 : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in ICT out of 100 : ";
	cin>>cs_marks;
	calculate();
}

void student::showdata() const
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in AP : "<<p_marks;
	cout<<"\nMarks in AC : "<<c_marks;
	cout<<"\nMarks in PF : "<<m_marks;
	cout<<"\nMarks in FE : "<<e_marks;
	cout<<"\nMarks in ICT :"<<cs_marks;
	cout<<"\nPercentage of student is  :"<<per;
	cout<<"\nGrade of student is :"<<grade;
}

void student::show_tabular() const
{
	cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<p_marks<<setw(4)<<c_marks<<setw(4)<<m_marks<<setw(4)<<e_marks<<setw(4)<<cs_marks<<setw(8)<<per<<setw(6)<<grade<<endl;
}
	 
int  student::retrollno() const
{
	return rollno;
}

void write_student();	//write the record in binary file
void display_all();		//read all records from binary file
void display_sp(int);	//accept rollno and read record from binary file
void modify_student(int);	//accept rollno and update record of binary file
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();	//display all records in tabular format from binary file
void result();	//display result menu
void loading();	//display welcome screen
void entry_menu();	//display entry menu on screen

int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); 
    loading();
	do
	{
		system("color 06");
		system("cls");
		cout<<"\n          ***********************************Student report card managment**********************************\n";
		cout<<"\n\t                   *********************************************************************";
		cout<<"\n\t                   |                             MAIN MENU                             |";
    	cout<<"\n\t                   *********************************************************************";
		cout<<"\n\n\t                   |                    Press R for   ||    RESULT                     |";
		cout<<"\n\n\t                   |                    Press E for   ||    ENTRY                      |";
		cout<<"\n\n\t                   |                    Press X for   ||    EXIT                       |";
	    cout<<"\n\n\t                   *********************************************************************";
		cout<<"\n\t                   |                    Please Select the option                       |\n";
      	cout<<"\t                   *********************************************************************\n";
		cin>>ch;
		switch(ch)
		{
			case 'r': result();
			cout<<"\a";
				break;
			case 'e': entry_menu();
				break;
			case 'x':
				break;
			default :cout<<"\a";
		}
    }while(ch!='x');
	return 0;
}

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}


void display_all()
{

	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}


void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}

	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    int pos=(-1)*static_cast<int>(sizeof(st));
		    File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    cout<<"\n\n\t Record Updated";
		    found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();

}

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}


void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"==========================================================\n";
	cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}



void result()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\t                 **********************************************************************";
	cout<<"\n\t                 |                             RESULT MENU                            |\n";                          
	cout<<"\t                 **********************************************************************\n";
	cout<<"\n\t                 |                          1. Class Result                           |";
	cout<<"\n\n\t                 |                          2. Student Report Card                    |";
	cout<<"\n\n\t                 |                          3. Back to Main Menu                      | \n\n";
	cout<<"\t                 **********************************************************************";
	cout<<"\n\t                 |                         Enter Choice (1/2/3)?                      |\n";
	cout<<"\t                 **********************************************************************\n";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}



void loading()
{
 system("cls");
  system("color 06");
  char a = 177, b = 219;
  cout<<"\n\n\n\t\t\t\t\t\tLoading......";
  cout<<"\n\n\n";
  cout<<"\t\t\t\t\t";
  for (int i = 10; i <= 30; i++)
  {
      cout<<a;
      Sleep(30);
  }
  for (int i = 0; i <=10; i++)
  {
      cout<<a;
      Sleep(120);
  }
  cout<<"\r";
  cout<<"\t\t\t\t\t";
  
  system("cls");
}

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\t                 **********************************************************************\n";
	cout<<"\t                 |                             ENTRY MENU                             |\n";
	cout<<"\t                 **********************************************************************";
	cout<<"\n\n\t                 |                      1.CREATE STUDENT RECORD                       |";
	cout<<"\n\n\t                 |                      2.DISPLAY ALL STUDENTS RECORDS                |";
	cout<<"\n\n\t                 |                      3.SEARCH STUDENT RECORD                       |";
	cout<<"\n\n\t                 |                      4.MODIFY STUDENT RECORD                       |";
	cout<<"\n\n\t                 |                      5.DELETE STUDENT RECORD                       |";
	cout<<"\n\n\t                 |                      6.BACK TO MAIN MENU                           |\n\n";
	cout<<"\t                 **********************************************************************\n";
	cout<<"\t                 |                    Please Enter Your Choice (1-6)                  |\n";
	cout<<"\t                 **********************************************************************\n";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}


