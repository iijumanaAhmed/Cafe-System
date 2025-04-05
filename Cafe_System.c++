	#include <iostream>
	#include <fstream>
	#include <ctime>
	#include <string>
	using namespace std;
	int arrSize = 0;
	int itemNo = 0;

	struct Details {
		string name;
		string component;
		int number;
		double price;
	};

	void menuList() {
		cout<<endl<<"\t\t\t\t\t"<<"-------------------------------------"<<endl<<"\t\t\t\t\t\t"<<"-- Operations Menu -- "<<endl<<"\t\t\t\t\t"<<"-------------------------------------"<<endl;
		cout<<"\t\t1. Add item"<<"\t\t\t"; // Add new item with its price
		cout<<"  2. Delete item"<<"\t\t"; // Delete an item with its price
		cout<<"  3. Update item"<<endl; // Update item with its price
		cout<<"\t\t4. Display the current menu"<<"\t"; // Display current menu
		cout<<"  5. Search about specefic item"<<"\t"; // Search an item
		cout<<"  6. Sort the menu"<<endl; // Sort menu by (price or letter)
		cout<<"\t\t7. Calculating the total bill whith tax for the customer"<<endl;
	}

	void addItem(Details items[], int arrSize)
	{         
		ofstream sendData;
		sendData.open("Items.txt", ios::app);
		if(sendData.is_open()) 
		{
			for(int i=0; i<arrSize; i++)
			{
				items[i].number = ++itemNo;
				cin.ignore();
				cout<<endl<<"\nEnter No."<< i+1 <<" item name: ";
				getline(cin, items[i].name);
				cout << "\nEnter its ingredients:\n";
				getline(cin,items[i].component);
				cout<<"\nEnter its price: ";
				cin>> items[i].price;
		
				sendData << "\t";
				sendData << items[i].number;
				sendData << " | ";
				sendData << items[i].name;		
				sendData << " - ";
				sendData << items[i].component;	
				sendData << "     ";
				sendData << items[i].price;					
				sendData << " SR" ;
				sendData << endl << endl;
				}
			cout<<endl<<endl<<"\t\t\t\t\t"<<"    --- Item added to the menu ---    "<<endl<<endl;
			sendData.close();
			}	
			else
				cout << "\nFile could not be opend" << endl;
			
	}

	void deleteItem(Details items[], int arrSize) 
	{    
		int num;
		bool found = false;
		
		cout<<"Enter item's name to delete it from the menu: ";
		cin>>num;

		for(int i=0; i<arrSize; i++)
		{
			if(items[i].number == num)
			{
				for(int j=i; j<arrSize-1; j++)
					items[j] = items[j + 1];
				
				arrSize--;
				cout << "**item deleted**\n";
				found = true;
				break;		
			}
		}
		
		if (!found)
			cout << "item not found\n";
		
		cout<<endl;	
	}


	void updat(Details items[], int size, int number)
	{
		bool found = false;
		for (int i = 0 ; i <= size ; i++)
		{
			if(number == items[i].number)
			{
				cout << "Enter new item name: ";
				cin >> items[i].name;
				cout << "**item name updated**\n";
				found = true;
				break;
			}
		}
		if (!found)
		cout << "item not found\n";
	}

	void displayMenu(Details items[], int arrSize) 
	{         		
		char ch;
		ifstream getData;
		getData.open("Items.txt", ios::in);
		
		while(!getData.eof()) //read till end-of-file
		{
			getData.get(ch); //read data from file
			cout<<ch; //display data on screen
		}
		cout<<endl;
		
		getData.close();
	}

	void searchItem(Details items[], int arrSize, int first, int last, int key) 
	{
		if (first>last)
			cout<<"\t\tThe item not exist";
		
		else
		{
			int mid=(first+last)/2;
			if (key==items[mid].number)
			{
			cout<<endl<<endl<<"--- Item found in the menu ---"<<endl<<endl;
			cout<<endl<<endl<<items[mid].number<<"  "<<items[mid].name<<" --- " <<endl<<endl;
			
			}
			else if (key<items[mid].number)
			{
			searchItem(items, arrSize, first, mid-1, key);
			}
			else if (key>items[mid].number)
			{
			searchItem(items, arrSize,  mid+1, last, key);
			}
		}
	}

	void sort(Details items[], int size)
	{
		double ordered = false;
		for(int i = 0 ; i < size && ordered == false ; i++)
		{
			ordered = true;
			Details Temp;
			for(int j = 0 ; j < size ; j++)
			{
				if(items[j].price > items[j+1].price)
				{
				ordered = false;
				Temp = items[j];
				items[j] = items[j+1];
				items[j+1] = Temp;
				}
			}
		}
		cout<<"\n menu after sorting by price :\n";
		displayMenu(items,size);
	}

	double calcBill(double total)
	{
		double total_bill;
		
		total_bill=total*0.15+total;
		return total_bill;
			
	}

	void statReport()
	{        
		time_t timeNow = time(0);
		//time(0) = function returns the current time in seconds.  EXTERNAL
		tm* localtm = localtime(&timeNow);
		//localtime = Convert time_t to tm as local time  EXTERNAL
		//Uses the value pointed by timer to fill a tm structure with the values that represent the corresponding time, expressed for the local timezone.

		ofstream report;
		report.open("Report.txt", ios::out);
		if(report.is_open()) 
		{	
		report <<"The last access was: "	<<"\n";
		report <<"   At Date & Time: "<<asctime(localtm); //asctime = Convert tm structure to string  EXTERNAL
		report <<"   The Number of items added to the menu is: " <<itemNo <<"\n";
		}
		else
		cout << "\nFile could not be opend" << endl;
		
		report.close();		
	}

	int main() {
	
		int choice, press;
		int *p;
		p=&arrSize;
		
		cout<<"\n\n\t\t\t\t           WELCOME TO THE CAFE MENU SYSTEM\n";
		
		do{	
			cout<<"\n\tGo To The Menu or Do Any Other Opreations? Please Press (1) and To Close The System Press (0): ";
			cin>>press;
			
			if(press == 0)
			{
				cout<<endl<<endl<<"\t\t\t\t\t\t    System closed...  "<<endl<<endl;	
				break;
			}
			else if(press == 1)
			{
				menuList(); //calling menu			
				cout<<endl<<"\tPress the number of the operation you want to do OR press (0) to close the system press: ";
				cin>>choice;
				
				if(choice == 0)
				{
					cout<<endl<<endl<<"\t\t\t\t\t\t    System closed...  "<<endl<<endl;	
					break;
				}
				
				else if ((choice == 1)||(choice == 2)||(choice == 3)||(choice == 5)||(choice == 6)||(choice == 7))
				{
					if (choice == 1)
					{
						cout<<endl<<"\tEnter the number of items: ";
						cin >>arrSize;
						
						cout<<"The menu will have "<< *p<<" items";
					}
					
					if((choice == 1)||(choice == 2)||(choice == 3)||(choice == 5)||(choice == 6)||(choice == 7))
					{
						Details items[arrSize];
						switch(choice) 
						{					
							case 1:
							{
								addItem(items, arrSize);
								break;
							}
							
							case 2:
							{
								if (arrSize >= 0)	                
									deleteItem(items, arrSize);
								else
									cout<< "There are no item. " << "You can't delete\n";
			
								break;
							}
		
							case 3:
							{
								if (arrSize >= 0)
								{
									int item_number;
									cout << "Enter item number to update: ";
									cin >>item_number;
								
									updat(items, arrSize,item_number);
								}
								else
									cout<< "There are no item . "<< "You can't update\n";	
								
								break;
							}
						
							case 5:
							{	
								double first=0;
								double last=arrSize;  
								int key;
								
								cout<<"\n\t\tEnter the number of the item you are looking for  "   ;
								cin>> key;
								searchItem(items, arrSize,first,last,key);
								
								break;
							}
							
							case 6:
							{
								if (arrSize >= 2)
									sort(items,arrSize);
								
								else if (arrSize >= 1)
									cout << "There is only one item. "<< "Nothing to sort!\n";
								
								else
									cout<< "There are no items. " << "Nothing to sort !!\n";
		
								break;
							}
						
							case 7:
							{
								double total;
								cout<<"\n\t\tEnter the total bill befor adding tax:  ";
								cin>>total;
		
								cout<<"\t\ttotal bill after adding tax= "<<calcBill(total)<<endl;
		
								break;
							}
		
							default:
							cout << "Invalid choice!!\n\n";
						}
					}
				}
				
				else if (choice == 4)
				{	 
					Details items[arrSize];
					displayMenu(items, arrSize);
				}
				
				else
					cout<<endl<<endl<<"\t\t\t\t\t   The choice is not in the list!!"<<endl<<endl;
			}
			
			else if(press > 1)
				cout<<endl<<endl<<"\t\t\t\t\t\t   Wrong input!!"<<endl<<endl;

		} while((press=1) && (choice!=0));

		statReport();	

	return 0;
	}
