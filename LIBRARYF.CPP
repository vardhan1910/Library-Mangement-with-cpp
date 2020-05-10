#include<stdio.h>
#include<conio.h>
#include<iostream.h>
#include<process.h>
#include<fstream.h>
#include<string.h>

class book
{
char bno[10];
char bname[50];
char author[50];
char publisher[50];
public:
void create()
{
cout<<"\nNew Book";
cout<<"\nEnter the name book no=";
cin>>bno;
cout<<"\nEnter the book name=";
cin>>bname;
cout<<"\nEnter the author name=";
cin>>author;
cout<<"\nEnter the publication name=";
cin>>publisher;
cout<<"\n\tBOOK CREATED\n";
}

void show()
{
cout<<"\nBook no="<<bno;
cout<<"\nBook name="<<bname;
cout<<"\nAuthor name="<<author;
cout<<"\nPublication name="<<publisher;
}

void modify()
{
cout<<"\n ENTER NEW RECORD\n";
cout<<"\nbook no=";
cin>>bno;
cout<<"\nbook name=";
cin>>bname;
cout<<"\nAuthor name=";
cin>>author;
cout<<"\nPublication name=";
cin>>publisher;
cout<<"\nBOOK DATA UPDATED\n";
}

char *retbno()
{
	return bno;
}
char *retbname()
{
	return bname;
}
char *retauthor()
{
	return author;
}
char *retpublisher()
{
	return publisher;
}

};

class student
{
char no[10];
char name[50],stbno[10];
int token;

public:
void create_student()
{
clrscr();
cout<<"\nNEW STUDENT\n";
cout<<"\nEnter the admission no=";
cin>>no;
cout<<"\nEnter the student name=";
cin>>name;
token=0;
stbno[0]='/0';
cout<<"\nRECORD CREATED\n";
}

void show_student()
{
cout<<"\nAdmission no="<<no;
cout<<"\nstudent name="<<name;
cout<<"\n No of issued books="<<token;
if(token==1)
cout<<"\nBook no"<<stbno;
}

void modify_student()
{
cout<<"\nEnter new record\n";
cout<<"\nAdmission no=";
cin>>no;
cout<<"\nStudent name=";
cin>>name;
}
char *retno()
{ return no;
}
char *retname()
{ return name;
}
char* retstbno()
{return stbno;
}
int rettoken()
{ return token;
}

void addtoken()
{ token=1;
}
void resettoken()
{
token=0;
}
void getstbno(char t[])
{
strcpy(stbno,t);
}
};
fstream f1,f2;
book b1;
student s1;

void writebook()
{
char c;
f1.open("book.txt",ios::out|ios::app);
do
{
clrscr();
b1.create();
f1.write((char*)&b1,sizeof(book));
cout<<"\nWant add more record y or n?";
cin>>c;
}while(c=='y'||c=='Y');
f1.close();
}

void writestudent()
{
char c;
f1.open("student.txt",ios::out|ios::app);
do
{
s1.create_student();
f1.write((char*)&s1,sizeof(student));
cout<<"\nWant add more record y or n?";
cin>>c;
}while(c=='y'||c=='Y');
f1.close();
}

void display_spb(char n[])
{
cout<<"\nBOOK DETAILS\n";
int flag=0;
f1.open("book.txt",ios::in);
while(f1.read((char*)&b1,sizeof(book)))
{
if(strcmpi(b1.retbno(),n)==0)
{
b1.show();
flag=1;
}
}
f1.close();
if(flag==0)
cout<<"\n book does not exist";
getch();
}

void display_sps(char n[])
{
cout<<"\nSTUDENT DETAILS\n";
int flag=0;
f1.open("student.txt",ios::in);
while(f1.read((char*)&s1,sizeof(student)))
{
if(strcmpi(s1.retno(),n)==0)
{
s1.show_student();
flag=1;
}
}
f1.close();
if(flag==0)
cout<<"\n student does not exist";
getch();
}

void modify_book()
{
char n[10];
int found=0;
clrscr();
cout<<"\nMODIFY BOOK RECORD\n";
cout<<"\nEnter the book no=";
cin>>n;
f1.open("book.txt",ios::in|ios::out);
while(f1.read((char*)&b1,sizeof(book)) && found==0)
{
if(strcmpi(b1.retbno(),n)==0)
{
b1.show();
cout<<"\nEnter the new details for book\n";
b1.modify();
int pos=-1*sizeof(b1);
f1.seekp(pos,ios::cur);
f1.write((char*)&b1,sizeof(book));
cout<<"\n\tRocord updated";
found=1;
}
}
f1.close();
if(found==0)
cout<<"\n\tRecord not found";
getch();
}

void modify_student()
{
char n[10];
int found=0;
clrscr();
cout<<"\nMODIFY STUDENT RECORD\n";
cout<<"\nEnter the admission no=";
cin>>n;
f1.open("student.txt",ios::in|ios::out);
while(f1.read((char*)&s1,sizeof(student)) && found==0)
{
if(strcmpi(s1.retno(),n)==0)
{
s1.show_student();
cout<<"\nEnter the new details of student\n";
s1.modify_student();
int pos=-1*sizeof(s1);
f1.seekp(pos,ios::cur);
f1.write((char*)&s1,sizeof(student));
cout<<"\n\tRocord updated";
found=1;
}
}
f1.close();
if(found==0)
cout<<"\n\tRecord not found";
getch();
}

void delete_student()
{
char n[10];
int flag=0;
clrscr();
cout<<"\n DELETE STUDENT";
cout<<"\nEnter the admission no which for delete=";
cin>>n;
f1.open("student.txt",ios::in||ios::out);
fstream f3;
f3.open("temp.txt",ios::out);
f1.seekg(0,ios::beg);
while(f1.read((char*)&s1,sizeof(student)))
{
if(strcmpi(s1.retno(),n)!=0)
f3.write((char*)&s1,sizeof(student));
else
flag=1;
}
f3.close();
f1.close();
remove("student.txt");
rename("temp.txt","student.txt");
if(flag==1)
cout<<"\n\tRecord Deleted";
else
cout<<"\nRecord not found";
getch();
}

void delete_book()
{
char n[10];
clrscr();
cout<<"\n DELETE BOOK";
cout<<"\nEnter the book no which for delete=";
cin>>n;
f1.open("book.txt",ios::in||ios::out);
fstream f3;
f3.open("temp.txt",ios::out);
f1.seekg(0,ios::beg);
while(f1.read((char*)&b1,sizeof(book)))
{
if(strcmpi(b1.retbno(),n)!=0)
f3.write((char*)&b1,sizeof(book));
}
f3.close();
f1.close();
remove("book.txt");
rename("temp.txt","book.txt");
cout<<"\n\tRecord Deleted";
getch();
}

//issue book
void issue()
{
char s[6],b[6];
int found=0,flag=0;
clrscr();
cout<<"\nEnter the admission no=";
cin>>s;
f1.open("student.txt",ios::in|ios::out);
f2.open("book.txt",ios::in|ios::out);

while(f1.read((char*)&s1,sizeof(student)) && found==0)
{
if(strcmpi(s1.retno(),s)==0)
{
found=1;
if(s1.rettoken()==0)
{
cout<<"\nEnter the book no=";
cin>>b;
while(f2.read((char*)&b1,sizeof(book)) && flag==0)
{
if(strcmpi(b1.retbno(),b)==0)
{
b1.show();
flag=1;
s1.addtoken();
s1.getstbno(b1.retbno());
int pos=-1*sizeof(s1);
f1.seekp(pos,ios::cur);
f1.write((char*)&s1,sizeof(student));
cout<<"\n\tBook issued successfully\n";
cout<<"fine will be 1 Rs. for each day after 15 days\n";
}
}
if(flag==0)
cout<<"\nBook no does not exist";
}
else
cout<<"\nYou have not return the last book";
}
}
if(found==0)
cout<<"\nStudent record not exist";
getch();
f1.close();
f2.close();
}

void deposite()
{
char s[6],b[6];
int found=0,flag=0,day,fine;
clrscr();
cout<<"\nEnter the admission no=";
cin>>s;
f1.open("student.txt",ios::in|ios::out);
f2.open("book.txt",ios::in|ios::out);

while(f1.read((char*)&s1,sizeof(student)) && found==0)
{
if(strcmpi(s1.retno(),s)==0)
{
found=1;
if(s1.rettoken()==1)
{
while(f2.read((char*)&b1,sizeof(book)) && flag==0)
{
if(strcmpi(b1.retbno(),s1.retstbno())==0)
{
b1.show();
flag=1;
cout<<"\nBook deposite in number of days=";
cin>>day;
if(day>15)
{
	fine=(day-15)*1;
	cout<<"\n fine is="<<fine<<"rs.";
}
s1.resettoken();
int pos=-1*sizeof(s1);
f1.seekp(pos,ios::cur);
f1.write((char*)&s1,sizeof(student));
cout<<"\n\tBook deposite successfully\n";
}
}
if(flag==0)
cout<<"\nBook no does not exist";
}
else
cout<<"\nNo book is issued";
}
}
if(found==0)
cout<<"\nStudent record not exist";
getch();
f1.close();
f2.close();
}

void admin_menu()
{
clrscr();
int ch;
cout<<"\n\tADMINISTRATOR MENU";
cout<<"\n\t1.CREATE STUDENT RECORD";
cout<<"\n\t2.DISPLAY SPECIFIC STUDENT RECORD";
cout<<"\n\t3.MODIFY STUDENT RECORD";
cout<<"\n\t4.DELETE STUDENT RECORD";
cout<<"\n\t5.CREATE BOOK";

cout<<"\n\t6.DISPLAY SPECIFIC BOOK";
cout<<"\n\t7.MODIFY BOOK";
cout<<"\n\t8.DELETE BOOK";
cout<<"\n\t9.BACK";
cout<<"\n\tENTER BETWEEN 1 TO 09\n";
cin>>ch;
switch(ch)
{
	case 1: clrscr();
		cout<<"\ncreate new student record";
		writestudent();
		break;

	case 2: char num[10];
		clrscr();
		cout<<"\nEnter the admission no=";
		cin>>num;
		display_sps(num);
		break;
	case 3: modify_student();
		break;
	case 4: delete_student();
		break;
	case 5: clrscr();
		cout<<"\ncreate new book record";
		writebook();
		break;

	case 6: char number[6];
		clrscr();
		cout<<"\nEnter the book no=";
		cin>>number;
		display_spb(number);
		break;
	case 7: modify_book();
		break;
	case 8: delete_book();
		 break;
	case 9: return;
	default:cout<<"\a";
	}
	admin_menu();
	}

void main()
{
clrscr();
int ch;
void admin_menu();
void issue();
void deposite();
void modify_student();
void writestudent();
void writebook();
void delete_student();
void delete_book();
void modify_book();
void display_allb();

do
{
cout<<"\n\tMAIN MENU";
cout<<"\n\t1.ADMINISTRATOR MENU";
cout<<"\n\t2.BOOK ISSUE";
cout<<"\n\t3.BOOK DEPOSITE";
cout<<"\n\t4.EXIT";
cout<<"\n\tENTER BETWEEN 1 TO 4\n";
cin>>ch;
switch(ch)
{	case 1: clrscr();
		admin_menu();
		break;
	case 2: issue();
		break;
	case 3: deposite();
		break;
	case 4: exit(0);
	default:cout<<"\a";
}
}while(ch!=4);
}