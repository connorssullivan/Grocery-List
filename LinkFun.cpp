#include "Link.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//         Insert Node         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Node* insertNode(Node* &head, int itemNumber, char name[], char u, char t, double price, double subTotal){
	//Create new Node
	Node* newNode = new Node;
	newNode->next = nullptr;

	//set newNodes item number
	newNode->itemNum = itemNumber;

	//Set newNodes itemName
	strncpy(newNode->itemName, name, sizeof(newNode->itemName) - 1); //Copy the name over to newNode
    	newNode->itemName[sizeof(newNode->itemName) - 1] = '\0'; //Put in the null charecter

	//Set the newNodes price
	newNode->unitPrice = price;

	//Set new Nodes unit
	//If u==p then the unit is pounds
	if(u == 'p'){
		//Validate user input
		cout << "Enter number of pounds: ";
		while(!(cin>>newNode->unit)){
			cout << "Invalid input\nEnter a Number: ";
			cin.clear();
			cin.ignore();
		}
	}

	//If u==n then it is in units
	else if(u == 'n'){
		cout << "Enter number of units: ";
		//Validate user input
		while(!(cin >> newNode->unit)){
			cout << "Invalid input\nEnter a Number: ";
			cin.clear();
	 		cin.ignore();
		}
		newNode->unit = floor(newNode->unit);		
	}
	//If u==s then its a single unit
	else if(u == 's'){
		newNode->unit = 1;	
	}
	
	//There is an error validating the unit
	else{
		cout << "Error finding item unit" << endl;
		newNode = nullptr;
		delete newNode;
		return head;
	}

	//Get the price of the unitPrice x units
	double itemPrice = newNode->unitPrice * newNode->unit;

	//Get the item tax
	//If t==t then there is tax
	if(t=='t'){
		newNode->tax = itemPrice * 0.06; 
	}

	//If t==n then there is no tax
	else if(t=='n'){
		newNode->tax = 0;
	}

	//There is a problem getting the tax
	else{
		cout << "There was and error finding the tax status" <<endl;
		newNode = nullptr;
		delete newNode;
		return head;
	}

	//Get the subTotal
	newNode->subTotal = itemPrice + newNode->tax;


	//Put the newNode in the list
	//Case 1:If there is no head or the head is less then the newNode item number
	if(!head || head->itemNum >= itemNumber){
		newNode->next = head;
		head = newNode;
		cout <<newNode->itemName  << "Is now the head"<<endl; 
		return head;
	}
	
	//Case 2: Find out where the newNode needs to go
	Node* curr = head;
	while(curr->next && curr->next->itemNum <= newNode->itemNum){
		curr=curr->next;
	}

	//Add the node in the list
	newNode->next = curr->next;
	curr->next = newNode;

	cout <<newNode->itemName <<endl; 
		
	//Return head;
	return head;
		

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//         Print List         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printList(Node* head){
	double subtotal = 0.0;//Sub total of whole recibt
    	
		//Print header of recibt
		cout << right << setw(5) << "Item Number" << setw(15) << "Item Name" << setw(16) << "Unit" << setw(15) << "Unit Price" << setw(7) << "Tax" << setw(9) << "Total" << endl;
		cout << "------------- " << "---------------------- " << "------ " << "--------------- " << "------ " << "---------" << endl;

    	//Go through every node
	Node* curr = head;
    	while(curr){
		//Output item
		cout << right << setw(5) << curr->itemNum << setw(22) << curr->itemName << setw(14) <<curr->unit << setw(12) << fixed << setprecision(2)
            << curr->unitPrice << setw(12) << fixed << setprecision(2) << curr->tax << setw(9) << fixed << setprecision(2) << curr->subTotal << endl;
		
		//Add to subtotal
		subtotal += curr->subTotal;

		//Update pointer to next node
		curr = curr->next;
	}
	
	//Print out subTotal
	cout << "\n-----------------------------------------------------------------------------\nSubTotal "<< right << setw(68) << subtotal << endl; 
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//         Search Node         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Node* searchNode(Node *head, int id){
	//Case 1: If the head==id return head
	if(!head || head->itemNum == id)
	       return NULL;	

	//Assign curr to head
	Node* curr = head;

	//Go through list until curr->next->itemNum == id
	while(curr->next && curr->next->itemNum != id){
		curr = curr->next; 
	} 

	//Case 2: If some node == id
	if(curr->next)
		return curr;

	//Case 3: Node not it list o
	return nullptr;

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//         Delete Item         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Node* deleteItem(Node* &head, int id){
	//If theres no head then no need to run this function
	if(!head){
		cout << "\nItem " << id << " is not in your list " << endl;
		return head;
	}

	//Get the Node previous to the node to be deleted
	Node* prev = searchNode(head,id);

	//Handler will be used later to go through all duplicate items in a list
	Node* handler = nullptr;

	//Case 1: If prev is null and the head head is not the id, then print an error
	if(!prev && head->itemNum != id){
		cout << "\nItem " << id << " is not in your list " <<endl;
	}

	//Case 2: Prev is NULL but the head == id
	else if(!prev && head->itemNum == id){

		//Set handler to thee start of the items
		handler = head;

		//number of items with itemNum id
		int index = 0;
		
		//Print out all the items with id;
		cout << "\n";
		while(handler && handler->itemNum==id){
			//Print out the handeler information
			cout << index+1 << " : " << handler->itemName << " Subtotal " << handler->subTotal << endl;

			//Update handler
			handler = handler->next;
			
			//Update index
			++index;
		}


		//Option for user input
		int option = -1;

		//Get user input 
		while(!(cin >> option) || option < 1-1 || option > index){
			cout << "Enter a valid input between " << 1 << " and " << index << ":";
			cin.clear();
			cin.ignore();	
		}

		//Set handler back to head
		handler = head;

		//Set the prev = NULL
		prev = NULL;

		//go to the correct node
		for(int i = 0; i < option-1;i++){
			//Updatee prev to handler
			prev = handler;
			//Update handler to next
			handler = handler->next;
		}

		//Case 1: Ifdeleting the head
		if(!prev){
			//Ask user to confirm that they want to delete the item
			int choice = -1;
			cout << "\nAre you sure you wamt to delete\n1: Yes\n2: No\nEnter: ";
			while((cin >> choice) && choice != 1 && choice != 2){
				cout << "Choose a number: ";
				cin.clear();
				cin.ignore();
			}

			//If user does not want to delete break out
			if(choice == 2)
				return head;

			//Assign head to the second node
			head = handler->next;

			//Output that the noode is deleted
		    cout << "\nItem " << handler->itemName << " with a cost of " << handler->subTotal << " Is being removed from the list " << endl;

			//Delete handler
			handler = nullptr;
		}

		//Case 2: Handler is in the middle or end of the list
		else{
			//Ask user to confirm that they want to delete the item
			int choice = -1;
			cout << "\nAre you sure you wamt to delete\n1: Yes\n2: No\nEnter: ";
			while((cin >> choice) && choice != 1 && choice != 2){
				cout << "Choose a number: ";
				cin.clear();
				cin.ignore();
			}

			//If user does not want to delete break out
			if(choice == 2)
				return head;

			//Repair the list
			prev->next = handler->next;

			//Output a message that the node is deleted
			cout << "\nItem " << handler->itemName << " with a cost of " << handler->subTotal << " is being removed from the list " << endl;

			//delete handler
			delete handler;
			handler = nullptr;
		}

	}
	
	//Case 3: There is a prev
	else{
		//Ask user to confirm that they want to delete the item
		int choice = -1;
		cout << "\nAre you sure you wamt to delete\n1: Yes\n2: No\nEnter: ";
		while((cin >> choice) && choice != 1 && choice != 2){
			cout << "Choose a number: ";
			cin.clear();
			cin.ignore();
		}

		//If user does not want to delete break out
		if(choice == 2)
			return head;		

		//Set handler to prev->next
		handler = prev->next;

		//Index used to track how many of item id there are
		int index = 0;

		//Print the items
		while(handler && handler->itemNum==id){
			//Print out the handeler information
			cout << index+1 << " : " << handler->itemName << " Subtotal " << handler->subTotal << endl;

			//Update handler
			handler = handler->next;
			
			//Update index
			++index;
		}

		//Set handler back to the item
		handler = prev->next;

		//Option for user input
		int option = -1;

		//Get user input 
		while(!(cin >> option) || option < 1 || option > index){
			cout << "Enter a valid input between " << 1 << " and " << index << ":";
			cin.clear();
			cin.ignore();	
		}

		//Update the handler
		for(int i = 0; i < option-1;i++){
			prev = handler;
			handler = handler->next;
		}

		//update the nodes
		prev->next = handler->next;

		//Delete handler
		delete handler;
		handler = nullptr;
		
	}
	return head;
}	


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//         Destroy List        //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void destroyList(Node* head){
	Node* del = head;//Used to delete node
	Node* next = head->next; //Next node

	//Iterate through list
	while(next){
		//Delete del
		delete del;
		del = nullptr;

		//Update del
		del = next;

		//Update next
		next = next->next;
	}

	//Delete last node
	delete del;
	del = nullptr;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//         Save List         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void saveList(Node* head){
	//Open File
	ofstream output;
	output.open("Sullivan_Connor.txt",ios::out);

	//Output the chart
	output << right << setw(5) << "Item Number" << setw(15) << "Item Name" << setw(16) << "Unit" << setw(15) << "Unit Price" << setw(7) << "Tax" << setw(9) << "Total" << endl;
	output << "------------- " << "---------------------- " << "------ " << "--------------- " << "------ " << "---------" << endl;
	

	if(!head){
		output << "\n-----------------------------------------------------------------------------\nSubTotal "<< right << setw(68) << 0.00 << endl;
	       	output.close();
		return;	
	}
	

	//Iterate through nodes
	double subtotal = 0.0;
	Node* curr = head;
	while(curr){
		//Print out the node
		output << right << setw(5) << curr->itemNum << setw(22) << curr->itemName << setw(14) <<curr->unit << setw(12) << fixed << setprecision(2)
        	<< curr->unitPrice << setw(12) << fixed << setprecision(2) << curr->tax << setw(9) << fixed << setprecision(2) << curr->subTotal << endl;

		//Update to subTotal
		subtotal += curr->subTotal; 

		//Iterate curr
		curr = curr->next;
	}

	//Output subTotal
	output << "\n-----------------------------------------------------------------------------\nSubTotal "<< right << setw(68) << subtotal << endl; 

	//Close ofstream
	output.close();

	//Delete list
	destroyList(head);

}
