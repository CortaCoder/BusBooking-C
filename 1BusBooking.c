#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct mem
{
	char mname[10];
	int mage;
	int mcost;
	char seat[3];
};
struct bill
{ char name[20];
  int age;
  int cost;
  char contact[10];
  int seats;
  
};
void seat(char *ptr)
{
    int j;
        printf("\t");
        for(j=0;j<20;j++)
            printf("%c",*(ptr+j));
        printf("\n");
}
void tinput(struct bill *p)
{  
	int a;
	fflush(stdin);
	printf("Enter Your Details Below To Book\n");
	printf("Name: ");
	gets(p-> name);
	printf("Age: ");
	scanf("%d",&p->age);
	printf("Contact: ");
	for(a=1;a!=0;a++)
	{	
		scanf("%s",&p->contact);
		if (strlen(p->contact)!=10)
		{
			printf("Invalid Contact Enter again");
	   		continue;
   		}
		printf("No. Of Seat : ");
		label:
		{
			scanf("%d",&p->seats);
			if(p->seats>5)
			{
				printf("No.of Seats are limited to 5 for each user\n");	
				goto label;
			}
			else 
	       		break;
		}
   	}
   	
}
void tminput(struct mem *q)
{
	fflush(stdin);
	printf("\nEnter Name : ");
	gets(q->mname);
	printf("Enter Age : ");
	qbell:
	{
	scanf("%d",&q->mage);
	if(q->mage!=0){
	if(q->mage<5)
		q->mcost=1500;
	else
		q->mcost=2500;
	}
	else
	{ 
		printf("Please enter valid age !!");
		goto qbell;
	}
	}
}
int main()
{
    
    int i,j,l,k,cnt=0;
    char m;
    FILE *fp;
    printf("   WELCOME TO ONLINE BOOKING\nThe Seating arrangement is given \n\t\tbelow\n\n");
    char S[15][20]={"01A 01B 01C  01D 01E","02A 02B 02C  02D 02E","03A 03B 03C  03D 03E","04A 04B 04C  04D 04E","05A 05B 05C  05D 05E","06A 06B 06C  06D 06E","07A 07B 07C  07D 07E","08A 08B 08C  08D 08E","09A 09B 09C  09D 09E","10A 10B 10C  10D 10E","11A 11B 11C  11D 11E","12A 12B 12C  12D 12E","13A 13B 13C  13D 13E","14A 14B 14C  14D 14E","15A 15B 15C  15D 15E"};
	for(i=0;i<15;i++)
        seat(S[i]);
    char Str[3];
    ex:
    {
    	fp=fopen("traveller1.dat","a");
    	//taking input struct
    	struct bill B;
    	tinput(&B);
    	fwrite(&B,sizeof(struct bill),1,fp);
    	fclose(fp);
    	struct mem A[B.seats];
    	//taking seat no.
   	 	for(k=0,B.cost=0;k<B.seats;k++)
    	{
    		printf("Enter details of %d Passenger",k+1);
    		tminput(&A[k]);
    		B.cost=B.cost+A[k].mcost;
     		ls:
			{
				printf("Enter your Seat");
	     		scanf("%s",Str);
			    for(i=0;i<15;i++)
			    {
			    	if(atoi(Str)==(i+1) && strlen(Str)==3)	
						break;
					else if(Str[0]>'1' || Str[1]>'5' || Str[2]>'E' || Str[2]<'A' || Str[0]<'0' || Str[1]<'0')
					{
						printf("Seat is not available\nEnter valid seat");
						goto ls;
			    	}
					else
						continue;
				}
			}
			for(j=0;S[i][j]!='\0';j++)
			{
				
				if(S[i][j]==Str[2])
				{
					printf("hot seat\n");
					S[i][j]='-';
					S[i][j-2]='-';
					S[i][j-1]='X';
					break;
				}
				else if(S[i][j]=='-')
				{
					printf("Seat already occupied.Pls select valid seat\n");
					goto ls;
				}
				else
					continue;
			}
			for(i=0;Str[i]!='\0';i++)
				A[k].seat[i]=Str[i];
    	}
    	printf("-------------Your Bill-------------");
   		printf("\nName: %s\tAge: %d\nContact: %s\tSeats: %d\n\tCost: %d\n",B.name,B.age,B.contact,B.seats,B.cost);
   		printf("\t Passenger List\nName\tAge\tSeat\tCost\n");
   		for(k=0;k<B.seats;k++)
   		{
   			printf("%s\t%d\t%s\t%d\n",A[k].mname,A[k].mage,A[k].seat,A[k].mcost);	
		}
	}
    printf("Your seat is shown with X\n");
    for(i=0;i<15;i++)
       seat(S[i]);
    for(i=0;i<15;i++)
        for(j=0;j<20;j++)
        {
            if(S[i][j]=='X')
                S[i][j]='O';
        }
    ++cnt;
    //Proceeding with booker's option
    for(j=1;j!=0;j++)
    {
    	printf("\nPress \n '1':To show the Recent Bookings\n'2':To View Bus Occupancy\n'3':To book another Ticket\n press any other key to EXIT\n");
		scanf(" %c",&m);
		switch(m)
	    {
	    	case '1':{
						fp=fopen("traveller1.dat","r");			
						printf("\n\tLIST OF RECENT BOOKINGS\n");
	    				printf("S.No.\tName\tAge\tCost\tContact\t\tNo.of Seats");
	        			for(i=0;i<cnt;i++)
	        			{
	        				struct bill s;
							fread(&s,sizeof(struct bill),1,fp);
							printf("\n%d\t%s\t%d\t%d\t%s\t%d",i+1,s.name,s.age,s.cost,s.contact,s.seats);
						}
						fclose(fp);
						
					 }
						continue;
			case '2': {
						printf("\nThe Status of Bus Occupancy Shown Below\n");
						for(i=0;i<15;i++)
	            			seat(S[i]);
	            	  }continue;
	        case '3': {fflush(stdin);
						}goto ex;
	        default:printf("\nThank you for Booking");
		}
		if(m>3)
			break;
	}
}
