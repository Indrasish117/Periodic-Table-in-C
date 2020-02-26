#include<conio.h>
#include<fstream.h>
#include<iostream.h>
#include<string.h>
#include<process.h>
#include<stdio.h>
#include<dos.h>
#include<ctype.h>


void check()
{
	cout<<"OK";
	getch();
}

void cls(int j=3)
{
	 for(int i=j;i<26;i++)
	 {     gotoxy(1,i);
	   clreol();
	 }
	 gotoxy(1,2);
}
void music()
{
   sound(329.6);
   delay(900);
   sound(293.6);
   delay(300);
   sound(277.2);
   delay(300);
   sound(261.6);
   delay(300);
   nosound();
}
void  warn(char str[])
{
	 cls();
	 textcolor(RED);
	 for(int i=1;i<2;i++)
	 {
	gotoxy(25,12);
	cprintf(str);  cout<<"\a";

	music();
	delay(500);
	cls();
	delay(200);

	 }
	 textcolor(WHITE);
}



class element
{
	  int atno,msn;
	  char nm[15] ,smb[5],val[5];
	  float atms;
	  char founder[35],el_con[100];

   public :
	  friend   void add_elm();
	  friend   void disp_elm(int,int,int);
} elm ;


struct elm_list
{
   char nam[20],smb[5];
   int atno;
};


class group
{
   elm_list elm[9];
   int grp_no,no_elm;
   char el_con[20],vals[5];
   char oxdn[5],grpnm[25];
  public:
    friend void add_grp();
    friend void disp_grp();
}gr;


class period
{
  elm_list elm[32];
  int prd_no,no_elm;
	public :
  friend void add_prd();
  friend void disp_prd();
}pr;


class block
{
   char blc_nm,grp_nm[12][80];
   int grp_nos[10],no_grps;
	  public:
   friend void add_blc();
   friend void disp_blc();
}bl;


void add_elm()
{
     cls();
     fstream  fin;
     fin.open("elmnt.dat",ios::in|ios::out|ios::binary) ;
      cout<<"\n\t\t ENTER  THE  FOLLOWING  DETAILS    :- \n"
	  <<"    ******************************************************\n"
	  <<"\n\t  NAME OF  ELEMENT           :   \n    "
	  <<"\n\t  ATOMIC  NUMBER             :   \n    "
	  <<"\n\t  MASS NUMBER                :   \n    "
	  <<"\n\t  SYMBOL                     :   \n    "
	  <<"\n\t  ELECTRONIC  CONFIGURATION  :   \n    "
	  <<"\n\t  EXACT  ATOMIC  MASS        :   \n    "
	  <<"\n\t  VALENCIES                  :   \n    "
	  <<"\n\t  NAME OF FOUNDER            :   \n    "
	  <<"  *********************************************************";

      name_again:
      elm.nm[0]='\0';
      gotoxy(40,6);
	  gets(elm.nm);
      if(!strlen(elm.nm))
	  goto name_again;
	  gotoxy(40,8);cin>>elm.atno;
      gotoxy(40,10); cin>>elm.msn;
      gotoxy(40,12); cin>>elm.smb;
      gotoxy(40,14); cin>>elm.el_con;
      gotoxy(40,16); cin>>elm.atms;
      gotoxy(40,18); cin>>elm.val;
      gotoxy(40,20); gets(elm.founder);
      fin.seekp(elm.atno*sizeof(elm), ios::beg);

      fin.write((char*)&elm,sizeof(elm));
	  cls();
      gotoxy(15,12); cout<<"\ELEMENT ENTRY SUCSESSFUL";
      delay(500);
	  getch();
	  fin.close();
	  cls();
}

void add_grp()
{
   cls();
   fstream f;
   f.open("group.dat",ios::binary|ios::in|ios::out) ;
   cout<<"\n\n\t\tENTER FOLLOWING DETAILS :-\n"
	   <<"\n\n\t  GROUP NUMBER                           :          "
	   <<"\n\n\t  GROUP  NAME                            :          "
	   <<"\n\n\t  COMMON GROUP VALENCIES                 :          "
	   <<"\n\n\t  COMMON  ELECTRONIC CONFIGURATION       :          "
	   <<"\n\n\t  NUMBER  OF ELEMENTS                    :          ";
   gotoxy(60,7);cin>>gr.grp_no;
   gotoxy(60,9);gets(gr.grpnm);
   gotoxy(60,11);cin>>gr.vals;
   gotoxy(60,13);gets(gr.el_con);
   gotoxy(60,15);cin>>gr.no_elm;

   cls();
   gotoxy(10,6);cout<<"ENTER ELEMENT  LIST :-     ";
   gotoxy(5,7) ;cout<<"**************************************************";
   gotoxy(10,8);cout<<"NAME";
   gotoxy(25,8);cout<<"ATOMIC  NUMBER ";
   gotoxy(45,8);cout<<"SYMBOL";
   gotoxy(8,9) ;cout<<"__________________________________________________";
   for(int i=0;i<gr.no_elm;i++)
   {
	  gotoxy(1,11+i);cout<<i+1<<">";
	  gotoxy(8,11+i);cin>>gr.elm[i].nam;
	  gotoxy(32,11+i);cin>>gr.elm[i].atno;
	  gotoxy(48,11+i);cin>>gr.elm[i].smb;
   }
   gotoxy(5,11+i);cout<<"************************************************";
   cout<<"\n\t\tEnter this GROUP  ?(y/n)   :";
   char chk;
   cin>>chk;
   cls();

   if(chk=='y'||chk=='Y')
   {
	  f.seekp(gr.grp_no*sizeof(gr));
	  f.write((char*)&gr,sizeof(gr));
	  f.close();
	  gotoxy(25,12);cout<<"G R O U P    E N T E R E D     !!!!!";
   }
   else
   {
	   cls();
	   gotoxy(25,12);
	   cout<<"GROUP NOT ENTERED   !!!!!!";
   }
  getch();
  cls();
}

void add_blc()
{  fstream fin;
   cls();
   cout<<"\n\n\t\t ENTER FOLLOWING DETAILS  :-\n"
	   <<"\t  _________________________________________\n\n"
	   <<"\n\tBLOCK                      :"
	   <<"\n\tNUMBER OF GROUPS           :"
	   <<"\n\n\tENTER  GROUPS  :-\n";
   gotoxy(40,8);cin>>bl.blc_nm;
   gotoxy(40,9);cin>>bl.no_grps;
   cout<<"\n\n\n";
   for(int i=0;i<bl.no_grps;i++)
   {
	  cout<<i+1<<">\t"<<" GROUP NUMBER : ";
	  cin>>bl.grp_nos[i];
	  cout<<"\t GROUP NAME :  ";
	  gets(bl.grp_nm[i]);
	  cout<<endl;
   }
   fin.open("block.dat",ios::binary|ios::in|ios::app);
   fin.write((char*)&bl,sizeof(bl));
   fin.close();
   cls();
   gotoxy(25,12);cout<<"GROUP SAVED    !!!";
   gotoxy(60,23);cout<<"press any key....  ";
   cls();
}

void disp_blc()
{
  char bloc,chk;   int i=1;   fstream  f;
  cls();

  start  :
  f.open("block.dat",ios::in|ios::binary);
  textcolor(YELLOW);
  gotoxy(25,8);  cprintf("B L O C K   D I S P L A Y");
  gotoxy(25,9);cout<<"_________________________";
  gotoxy(15,12); cprintf("BLOCK TO BE DISPLAYED   : ");
  bloc=getche();  getch();

  f.seekg(0,ios::beg);
  while(f.read((char*)&bl,sizeof(bl)))
  {
	 if(bl.blc_nm==bloc)
	 {    i=-1;  break;    }
	 i++;
  }
  if(i>0)
  {
	warn("INVALID  BLOCK  NAME   !!!");
	if(i<20)
	{
	gotoxy(25,12);  cprintf("ENTER  BLOCK  NAME  AGAIN");
	delay(1000);
	i=20;
	cls();
	f.close();
	goto start;
	}
  }
  else
  {
	cls();
	cout<<"\n\n\n\n\t\tB L O C K   D A T A ";
	cout<<"\n\t\t___________________" ;
	cout<<"\n\n\t\t     BLOCK : "<<(char)toupper(bloc);
	cout<<"\n\n\t\tLIST OF GROUPS OF THIS BLOCK  :-";
	gotoxy(10,13);  cout<<"______________________________________________" ;
	gotoxy(15,14);cout<<"GROUP NO.";  gotoxy(30,14);cout<<"GROUP NAME";
	gotoxy(10,15);  cout<<"______________________________________________"  ;
	gotoxy(10,22);  cout<<"______________________________________________"  ;

	for(i=1;i<=bl.no_grps;i++)
	{
		 gotoxy(2,16+i);  cout<<i<<">\t\t ";
		 gotoxy(20,16+i);cout<<bl.grp_nos[i-1]  ;
		 gotoxy(30,16+i); cout<<bl.grp_nm[i-1];
		 if(i%5==0)
		 {  gotoxy(20,23);
		cout<<"MORE  ?(Y/N)  ";
		chk=getche();getch();
		gotoxy(20,23);clreol();
		if(toupper(chk)!='Y') break;
		 }

	}
  }
  gotoxy(60,24);cout<<"press any key......" ;
  getch();
  cls();
  f.close();
  textcolor(WHITE);
}

void disp_grp ()
{
  fstream  f;
  int  i=0,grp;
  cls();
  start  :
  f.open("group.dat",ios::in|ios::binary);
  textcolor(YELLOW);
  gotoxy(25,8);  cprintf("G R O U P   D I S P L A Y");
  gotoxy(25,9);cout<<"_________________________";
  gotoxy(15,12); cprintf("GROUP TO BE DISPLAYED   : ");
  cin>>grp;

  f.seekg(0,ios::beg);
  while(f.read((char*)&gr,sizeof(gr)))
  {
	 if(gr.grp_no==grp)
	 {    i=-1;  break;    }
	 i++;
  }
  if(i>0)
  {
	warn("INVALID  GROUP  NUMBER   !!!");
	if(i<20)
	{
	gotoxy(25,12);  cprintf("ENTER  GROUP NUMBER  AGAIN");
	delay(1000);
	i=20;
	cls();
	f.close();
	goto start;
    }
  }
  else
  {
	char chk;
	fstream  f;
	cls();
	cout<<"\n\n\n\n\t\tG R O U P   D A T A ";
	cout<<"\n\t\t___________________" ;
	cout<<"\n\n\tGROUP NUMBER : "<<grp;
	cout<<"\n\tGROUP NAME :     "<<gr.grpnm;
	cout<<"\n\n\t  COMMON GROUP VALENCIES            :  "<<gr.vals;
	cout<<"\n\n\t  COMMON  ELECTRONIC CONFIGURATION  :  "<<gr.el_con;
	gotoxy(20,23);
	cout<<"MORE  ?  ";getch();

	cls(10);
	cout<<"\n\n\t\tLIST OF GROUPS OF THIS BLOCK  :-";
	gotoxy(15,14);cout<<"SYMBOL";
	gotoxy(30,14);cout<<"ELEMENT NAME";
	gotoxy(50,14);cout<<"ATOMIC NO.";
	gotoxy(10,15);  cout<<"_______________________________________________________________"  ;
	gotoxy(10,22);  cout<<"_______________________________________________________________"  ;

	for(i=1;i<=gr.no_elm;i++)
	{
	     gotoxy(2,16+i);  cout<<i<<">\t\t ";
	     gotoxy(18,16+i); cout<<gr.elm[i-1].smb;
	     gotoxy(30,16+i); cout<<gr.elm[i-1].nam;
	     gotoxy(55,16+i); cout<<gr.elm[i-1].atno;
	     if(i%5==0)
	     {  gotoxy(20,23);
		cout<<"MORE  ?(Y/N)  ";
		chk=getche();getch();
		gotoxy(20,23);clreol();
		if(toupper(chk)!='Y') break;
		 }

	}
  }
  gotoxy(60,24);cout<<"press any key......" ;
  getch();
  cls();
  f.close();
  textcolor(WHITE);

}


void disp_elm(int ch,int  funct=1,int atno=0)
{
   fstream  f;  int i=1;  char  name[30],smb[5];
   start  :
   f.open("elmnt.dat",ios::binary|ios::in);
   f.seekg(sizeof(elm));
   cls();
   textcolor(YELLOW);
   cout<<"\n\n\n\t\t\t D I S P L A Y    E L E M E N T "
	   <<"\n\t\t\t--------------------------------" ;
   switch(ch)
   {
       case  1 :    cout<<"\n\n\n\t\t ELEMENT   NAME   :  " ;
			gets(name);
		    break;

       case  2 :    cout<<"\n\n\n\t\t SYMBOL :   " ;
		    cin>>smb;
		    break;

       case  3 :    if(funct==1)
		    {
		       cout<<"\n\n\n\t\t ATOMIC  NUMBER  :   ";
			   cin>>atno ;
		    }
   }

   while(f.read((char *)&elm,sizeof(elm)))
   {

	 //gotoxy(70,2); cout<<i;
	 switch(ch)
	 {
	    case 1 :  if(!strcmpi(elm.nm,name))  i=0;  break;

	    case 2 :  if(!(strcmpi(smb,elm.smb)))  i=0;  break;

	    case 3 :  if(elm.atno==atno)  i=0;
	 }
	 if(!i) break;
	 i++;
   }

   if(i>0)
   {
     if(funct==1)
     {
	 warn("WRONG  DATA  ENTRY  !!!");
	 if(i<1000)
	 {
	     gotoxy(25,12);
	     textcolor(WHITE);
		 cprintf("TRY  AGAIN  !!!");
	     delay(2000);
	     i=1000;
	     f.close();
	     goto start;
	 }

     }
     else
	    warn("INFORMATION  UNAVAILABLE  !!!  ");
   }
   else
   {
	   cls();
       cout<<"\n\n\t\t\t E L E M E N T   D A T A "
	       <<"\n\t\t\t-------------------------";
       gotoxy(1,7);
       cout<<"    ************************************************************\n";
       cout<<"\n\t  NAME OF  ELEMENT           :       "<<elm.nm<<endl;
       cout<<"\n\t  ATOMIC  NUMBER             :       "<<elm.atno<<endl;
       cout<<"\n\t  MASS NUMBER                :       "<<elm.msn<<endl;
       cout<<"\n\t  SYMBOL                     :       "<<elm.smb<<endl;
       cout<<"\n\t  ELECTRONIC  CONFIGURATION  :       "<<elm.el_con<<endl;
	   cout<<"\n\t  EXACT  ATOMIC  MASS        :       "<<elm.atms<<endl;
       cout<<"\n\t  VALENCIES                  :       "<<elm.val<<endl;
       cout<<"\n\t  NAME OF FOUNDER            :       "<<elm.founder<<endl;
	   cout<<"     ************************************************************";
       gotoxy(60,25);cout<<"press any key ...." ;
       getch();
       textcolor(WHITE);
       f.close();
   }
}

void add_prd()
{
   int i;
   cls();
   fstream f;
   f.open("period.dat",ios::binary|ios::in|ios::out) ;
   cout<<"\n\n\t\tENTER FOLLOWING DETAILS :-\n"
       <<"\n\n\t  PERIOD NUMBE        :    "
       <<"\n\n\t  NUMBER OF ELEMENTS    :    ";
   gotoxy(60,7); cin>>pr.prd_no;
   gotoxy(60,9); cin>>pr.no_elm;
   cls();
   gotoxy(10,6); cout<<"ENTER ELMENT LIST:-   ";
   gotoxy(10,7); cout<<"*************************************";
   gotoxy(10,8); cout<<"NAME";
   gotoxy(25,8); cout<<"ATOMIC NUMBER";
   gotoxy(45,8); cout<<"SYMBOL";
   gotoxy(8,9); cout<<"__________________________________________";
   gotoxy(5,13+pr.no_elm);cout<<"************************************************";
   for(i=0;i<pr.no_elm;i++)
   {
      gotoxy(1,11+i);cout<<i+1<<">";
      gotoxy(8,11+i);cin>>pr.elm[i].nam;
      gotoxy(32,11+i);cin>>pr.elm[i].atno;
      gotoxy(48,11+i);cin>>pr.elm[i].smb;
   }

   cout<<"\n\t\tEnter this PERIOD  ?(y/n)";
   char chk;
   cin>>chk;
   cls();
   if(chk=='y'||chk=='Y')
   {
      f.seekp(pr.prd_no*sizeof(pr));
      f.write((char*)&pr,sizeof(pr));
      f.close();
      gotoxy(25,12);cout<<"P E R I O D     E N T E R E D     !!!!!";
   }
   else
   {
       cls();
	   gotoxy(25,12);
       cout<<"PERIOD NOT ENTERED   !!!!!!";
   }
  getch();
  cls();
}


void disp_prd ()
{
  fstream  f;
  int  i=0,prd;
  cls();
  start  :
  f.open("period.dat",ios::in|ios::binary);
  textcolor(YELLOW);
  gotoxy(25,8);  cprintf("P E R I O D    D I S P L A Y");
  gotoxy(25,9);    cout<<"____________________________";
  gotoxy(15,12); cprintf("PERIOD TO BE DISPLAYED   : ");
  cin>>prd;

  f.seekg(sizeof(pr));
  while(f.read((char*)&pr,sizeof(pr)))
  {
	 if(pr.prd_no==prd)
	 {    i=-1;  break;    }
	 i++;
  }
  if(i>0)
  {
	warn("INVALID  PERIOD  NUMBER   !!!");
	if(i<20)
	{
	gotoxy(25,12);  cprintf("ENTER  PERIOD NUMBER  AGAIN");
	delay(2000);
	i=20;
	cls();
	f.close();
	goto start;
	}
  }
  else
  {
	char chk;
	fstream  f;
	cls();
	cout<<"\n\n\n\n\t\tP E R I O D    D A T A ";
	cout<<"\n\t\t______________________" ;
	cout<<"\n\n\tPERIOD NUMBER : "<<prd;



	cout<<"\n\n\t\tLIST OF PERIOD OF THIS BLOCK  :-";
	gotoxy(15,14);cout<<"SYMBOL";
	gotoxy(30,14);cout<<"ELEMENT NAME";
	gotoxy(50,14);cout<<"ATOMIC NO.";
	gotoxy(10,15);  cout<<"_______________________________________________________________"  ;
	gotoxy(10,22);  cout<<"_______________________________________________________________"  ;

	for(i=1;i<=pr.no_elm;i++)
	{
		 gotoxy(2,16+i);  cout<<i<<">\t\t ";
		 gotoxy(18,16+i); cout<<pr.elm[i-1].smb;
		 gotoxy(30,16+i); cout<<pr.elm[i-1].nam;
		 gotoxy(55,16+i); cout<<pr.elm[i-1].atno;
		 if(i%5==0)
		 {  gotoxy(20,23);
		cout<<"MORE  ?(Y/N)  ";
		chk=getche();getch();
		gotoxy(20,23);clreol();
		if(toupper(chk)!='Y') break;
		 }

	}
  }
  gotoxy(60,24);cout<<"press any key......" ;
  getch();
  cls();
  f.close();
  textcolor(WHITE);

}
void page1()
{
   textbackground(WHITE);

   clrscr();
   cls();
   fstream f;
   f.open("C:\TURBOC3\Projects\Page1.txt",ios::in);
   f.seekg(0);
   char c;


   while(!f.eof())
   {
	 c=f.get();
	 if(c=='\n')
	   cout<<"\n";
	 else if(c==' ')
	 {
	   cprintf(" ");
	 }
	 else
	 {
	   textcolor(BLACK);
	   delay(50);
	   cprintf("%c",c);
	 }

   }
   f.close();
   getch();
}

char ch2,chk2,ch;
int  ch3,ch1,ch4,i,chk1;


void main()
{
clrscr();
page1();

textbackground(BLACK);
textcolor(WHITE);
clrscr();
while(1)
{
 clrscr();

 gotoxy(30,2);
 cout<<"PERIODIC TABLE";

 gotoxy(25,7);cout<<"* *U S E R   M E N U* *";
 gotoxy(25,8);cout<<"_______________________";
 gotoxy(18,10);cout<<"**********************************";

 for(i=1;i<6;i++)
 {
	gotoxy(18,10+i);
	cout<<"*                                *";
 }
 gotoxy(18,16);cout<<"**********************************";
 ch1=1 ;
 do
     {
	if(ch1==1) textcolor(BLUE); else textcolor(WHITE);
	gotoxy(20,12); cprintf("<1> VIEW INFORMATION    ");
	if(ch1==2) textcolor(BLUE); else textcolor(WHITE);
	gotoxy(20,13); cprintf("<2> MODIFY RECORDS    ");
	if(ch1==3) textcolor(BLUE); else textcolor(WHITE);
	gotoxy(20,14); cprintf("<3> EXIT    ");
	textcolor(RED);
	gotoxy(45,11+ch1); cprintf("<<--");


	ch=getch();
	if((int)ch==72)   ch1=(ch1>1)?ch1-1:3;
	if((int)ch==80)   ch1=(ch1<3)?ch1+1:1;
     }while((int)ch!=13);
     textcolor(WHITE);

 cls();


 if(ch1==3)
 {
    gotoxy(30,12); cout<<"EXITING  FROM PROGRAM  !!!  ";
    delay(2000);
    clrscr();
    break ;

 }
 gotoxy(60,1);cout<<"section : "<<ch1;
 if (ch1==2)
 {


	while(1)
	{
	  gotoxy(25,8);   cout<<"**  MODIFY  MENU  **" ;
	  gotoxy(20,9);   cout<<"________________________________________";
	  gotoxy(20,12);  cout<<"* ADD ELEMENT -----------------------<1>";
	  gotoxy(20,13);  cout<<"* ADD GROUP -------------------------<2>";
	  gotoxy(20,14);  cout<<"* ADD PERIOD ------------------------<3>";
	  gotoxy(20,15);  cout<<"* ADD BLOCK -------------------------<4>";
	  gotoxy(20,18);  cout<<"To exit  type '0' ! ";
	  gotoxy(20,19);  cout<<"****************************************" ;
	  gotoxy(25,22);  cout<<" Enter choice   : " ;

	  do
	  {   gotoxy(50,22);cout<<"  ";
	  gotoxy(50,22); ch2=getche();
	  }while(ch2<'0'||ch2>'4');
	  getch();
	  cls();

	  if(ch2=='0')
	  break;
	  gotoxy(71,1);cout<<"/-"<<ch2;

	  do
	  {
	 switch(ch2)
	 {
		   case '1' :  add_elm();
			   gotoxy(25,12);  cout<<"WANT  TO  ENTER  ANOTHER  ELEMENT  ?(y/n) " ;
			   break;

		   case '2' :  add_grp();
			   gotoxy(25,12);  cout<<"WANT  TO  ENTER  ANOTHER  GROUP  ?(y/n) " ;
			   break;
		   case '3' :  add_prd();
			   gotoxy(25,12);  cout<<"WANT  TO  ENTER  ANOTHER  PERIOD  ?(y/n) " ;
			   break;
		   case '4' :  add_blc();
			   gotoxy(25,12);  cout<<"WANT  TO  ENTER  ANOTHER  BLOCK  ?(y/n) " ;

	 }
	 chk2=getche();  getch();
	 cls();
	  }while(chk2=='y'||chk2=='Y');

	  gotoxy(20,12);  cout<<"RETURNING  TO  MODIFY  MENU  !!! ";
	  delay(2000)   ;
	  cls();
	  gotoxy(70,1);cout<<"1         ";
   }
 }
 else if(ch1==1)
 {
  while(1)
  {
	 cls();
	 gotoxy(25,7);cout<<"**INFORMATION MENU**";
	 gotoxy(25,8);cout<<"____________________";
	 gotoxy(18,10);cout<<"**********************************";

	 for(i=1;i<8;i++)
	 {
	gotoxy(18,10+i);
	       cout<<"*                                *";
     }

     gotoxy(18,18);cout<<"**********************************";
     ch3=1 ;

     do
     {  if(ch3==1) textcolor(GREEN);  else   textcolor(WHITE);
	gotoxy(20,12);  cprintf("<1> ELEMENT   INFO .          ");
	if(ch3==2) textcolor(GREEN);  else   textcolor(WHITE);
	gotoxy(20,13);   cprintf("<2> GROUP  INFO .             ");
	if(ch3==3) textcolor(GREEN);  else   textcolor(WHITE);
	gotoxy(20,14);   cprintf("<3> PERIOD  INFO .            ");
	if(ch3==4) textcolor(GREEN);  else   textcolor(WHITE);
	gotoxy(20,15);   cprintf("<4> BLOCK  INFO .             ");
	if(ch3==5) textcolor(GREEN);  else   textcolor(WHITE);
	gotoxy(20,16);   cprintf("<5> EXIT                      ");
	textcolor(RED);
	gotoxy(45,11+ch3);  cprintf("<<--");
	ch=getch();
	if(ch==(char)72)   ch3=(ch3>1)?ch3-1:5;
	if(ch==(char)80)   ch3=(ch3<5)?ch3+1:1;
     }while((int)ch!=13);
     textcolor(WHITE);
     gotoxy(70,1);  cout<<"1/-"<<ch3;
     if(ch3==4)  disp_blc();
     if(ch3==3)  disp_prd();
     if(ch3==2)  disp_grp();
     if(ch3==1)
     {
	while(1)
	{
	    cls();
	    gotoxy(25,7);cout<<"**ELEMENT SEARCH MENU**";
	    gotoxy(25,8);cout<<"____________________";
	    gotoxy(18,10);cout<<"**********************************";
	
	    for(i=1;i<8;i++)
	    {
		gotoxy(18,10+i);
		cout<<"*                                *";
	    }
	    gotoxy(18,17);cout<<"**********************************";
	    ch4=1 ;

	    do
	    {   if(ch4==1) textcolor(GREEN);  else   textcolor(WHITE);
		gotoxy(20,12);  cprintf("<3> SEARCH BY NAME            ");
		if(ch4==2) textcolor(GREEN);  else   textcolor(WHITE);
		gotoxy(20,13);   cprintf("<2> SEARCH BY SYMBOL         ");
		if(ch4==3) textcolor(GREEN);  else   textcolor(WHITE);
		gotoxy(20,14);   cprintf("<1> SEARCH BY ATOMIC NO.      ");
		if(ch4==4) textcolor(GREEN);  else   textcolor(WHITE);
		gotoxy(20,15);   cprintf("<4> EXIT                      ");
		textcolor(RED);
		gotoxy(45,11+ch4);  cprintf("<<--");
		ch=getch();
		if(ch==(char)72)   ch4=(ch4>1)?ch4-1:4;
		if(ch==(char)80)   ch4=(ch4<4)?ch4+1:1;
	    }while((int)ch!=13);
	    textcolor(WHITE);
	    if(ch4==4)  break;
	    gotoxy(70,1); cout<<"1/-1/-"<<ch4;
	    disp_elm(ch4);
	    cls();
	    gotoxy(25,12);cout<<"RETURNING TO  'S E A R C H'  MENU  !!!";
	}
     }
     if(ch3==5)  break;
     cls();
     gotoxy(25,12);  cout<<"RETURNING  TO  INFORMATION  MENU   !!!"   ;
     delay(1000);
  }
 }
 cls();
 gotoxy(20,12);  cout<<"RETURNING  TO  USER  MENU  !!! ";
 delay(2000);
 cls();
}
}

