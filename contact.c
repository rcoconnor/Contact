//project 6
//by: Rory O'Connor
//this program works by using nine funcitons, which each
//have their own function.  The user types which 
//function of the contact app they would like to use and
//the program will update the information the user 
//provides.  the data is structured as a series of 
//lists


#include "contact.h" 
#include <stdbool.h>

/////////////////////////////////////////////////////////////////////////////////////////////
// add a new contact to your list of contacts
//	   1. Make sure a contact by that name does not exist (print an error message and exit if it exists)
//	   2. Add a new contact with that name (add-at-front)




Contact* addContact(Contact *myContacts, char *contactName) {
	//search if the name exists
	Contact* curContact; 
	curContact = myContacts; 
	while (curContact != NULL) {
		if (strcmp(curContact->name, contactName) == 0) {
			printf("\tError: name already exists\n"); 
			return myContacts; 
		}
		curContact = curContact->next; 
	}

	//create the new contact
	Contact* newContact; 

	//allocate memory
	newContact = malloc(sizeof(Contact)); 
	newContact->name = malloc(strlen(contactName) * sizeof(char));
	newContact->information = malloc(sizeof(Info)); 
	
	//copy the information into the contact
	strcpy(newContact->name, contactName); 
	newContact->next = myContacts; 
	newContact->information = NULL; 

	return newContact; 
}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a new piece of information to the specified contact
//   1. Make sure a contact by that name exists (so you can add information to it)
//   2. If the informational item already exists, update the information's value to the new value
//   3. Otherwise, add the piece of information to the end of the contact's information list (add-at-end)

void addInformation(Contact *myContacts, char *contactName, char *infoName, char *infoValue) {
	Contact* curContact;
	Contact* newContact;  
	Info *curInfo; 
	bool nameExists = false; 
	

	//check if the contact exists
	for (curContact = myContacts; curContact != NULL; curContact = curContact->next) {
		if (strcmp(curContact->name, contactName) == 0) {
			nameExists = true; 
			newContact = curContact; 
			curInfo = curContact->information; 
		}
	}
	if (nameExists == false) {
		printf("\tError %s doesn't exist\n", contactName); 
		return; 
	}

	//the contact exists, check if the info exists
	if (curInfo != NULL) {
		Info* newInfo; 
		for (newInfo = curInfo; newInfo != NULL; newInfo = newInfo->next) {
			//if it exists, update the value
			if (strcmp(newInfo->name, infoName) == 0) {
				printf("\t%s already exists, updataing value\n", newInfo->name); 
				newInfo->value = infoValue; 
				return; 
			} 
		}
	}

	//the info doesn't exist, create a new one
	Info* newInfo; 
	newInfo = malloc(sizeof(Info)); 
	newInfo->name = malloc(strlen(infoName) * sizeof(char)); 
	newInfo->value = malloc(strlen(infoValue) * sizeof(char)); 

	strcpy(newInfo->name, infoName); 
	strcpy(newInfo->value, infoValue);  
	newInfo->next = NULL; 


	//add it to the end
	if (newContact->information == NULL) {
		newContact->information = newInfo; 
		return; 
	}

	//search for the last term
	for (curInfo = newContact->information; curInfo != NULL; curInfo = curInfo->next) {
		if (curInfo->next == NULL) {
			curInfo->next = newInfo; 
			return; 
		}
	}

	//unreachable
	return; 
}




/////////////////////////////////////////////////////////////////////////////////////////////
// prints all the information for a given contact
//	1. Make sure a contact with that name exists
//	2. Print the name of the contact
//	3. print all the informational items <name|value> associated with that contact
void printContact(Contact *myContacts, char *contactName) {
	for (Contact* curContact = myContacts; curContact != NULL; curContact = curContact->next) {
		if (strcmp(curContact->name, contactName) == 0) {
			printf("\tContact name: %s\n", curContact->name); 
			if (curContact->information == NULL) {
				//information == null, exit the program
				return; 
			} 
			Info *curInfo = curContact->information; 
			while (curInfo != NULL) {
				printf("\t\t%s: %s\n", curInfo->name, curInfo->value); 
				curInfo = curInfo->next; 
			}
		}
	}
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// returns the size of a given contact list
//	Iterate through the contact list to count the number of contacts, return that count
int count(Contact *myContacts) {
	int counter = 0; 
	Contact* curContact; 

	for (curContact = myContacts; curContact != NULL; curContact = curContact->next) {
		counter += 1; 
	}

	return counter;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// prints all your contacts
//	For each contact
//	   a.  Print the name of the contact
//	   b.  Print all the <information name|information value> pairs in that contact
//	Note: this code can call other functions as needed
void print(Contact *myContacts) {
	
	Contact* curContact; 
	//Info* curInfo; 

	//iterate through the contact list
	for (curContact = myContacts; curContact != NULL; curContact = curContact->next) {
		printContact(curContact, curContact->name); 
	}

	return;
}




/////////////////////////////////////////////////////////////////////////////////////////////
// add a new contact (in alphabetical order)
//	1. Make sure a contact by that name does not exist 
//	2. Add a new contact with that name (add-in-order)
Contact *addContactOrdered(Contact *myContacts, char *contactName) {
	//search if the name exists
	Contact* curContact; 
	for (curContact = myContacts; curContact != NULL; curContact = curContact->next) {
		if (strcmp(contactName, curContact->name) == 0) {
			printf("\tError: name already exists\n"); 
			return myContacts; 
		}
	}

	//create a new contact by allocating memory
	Contact* newContact; 
	newContact = malloc(sizeof(Contact)); 
	newContact->name = malloc(strlen(contactName) * sizeof(char)); 
	newContact->information = malloc(sizeof(Info)); 

	//copy the information into the contact
	strcpy(newContact->name, contactName); 
	newContact->information = NULL; 

	//case 1: empty list
	if (myContacts == NULL) {
		newContact->next = NULL; 
		return newContact; 
	}

	//case 2: the letter has a lower value 
	//if (newContact->name[0] < myContacts->name[0]) {
	if(strcmp(newContact->name, myContacts->name) < 0) {
		newContact->next = myContacts; 
		return newContact; 
	}

	//case 4: search for the right position
	for (curContact = myContacts; curContact->next != NULL; curContact = curContact->next) {
		//case 3: highest value, insert at the end
		if (curContact->next == NULL) {
			curContact->next = newContact; 
			return myContacts; 
		}
	
		//if (newContact->name[i] < curContact->next->name[i]) {
		if (strcmp(newContact->name, curContact->next->name) < 0) {
			newContact->next = curContact->next; 
			curContact->next = newContact; 
			return myContacts; 
		}
		
	}
	curContact->next = newContact;
	newContact->next = NULL;
	return myContacts;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a new info to the specified contact (in alphabetical order)
//	1. Make sure a contact by that name exists (so you can add an info to it)
//	2. If the informational item already exists, update the item (replace its value with the new value)
//	3. Otherwise, add the new info to the contact (add-in-order)
void addInformationOrdered(Contact *myContacts, char *contactName, char *infoName, char *infoValue) {
	Contact* curContact; 
	//Make sure a contact with the name exists
	for (curContact = myContacts; curContact != NULL; curContact = curContact->next) {
		if (strcmp(curContact->name, contactName) == 0) {
			//the contact exists, check if the information exists
			Info* curInfo; 
			for(curInfo = curContact->information; curInfo != NULL; curInfo = curInfo->next) {
				if (strcmp(curInfo->name, infoName) == 0) {
					printf("\t%s already exists, updating value\n", curInfo->name); 
					strcpy(curInfo->value, infoValue); 
					return; 
				}
			}
			//it doesn't exist, create a new one by allocating memory
			Info* newInfo; 
			newInfo = malloc(sizeof(Info)); 
			newInfo->name = malloc(sizeof(char) * strlen(infoName)); 
			newInfo->value = malloc(sizeof(char) * strlen(infoValue)); 

			//copy the information into the contact
			strcpy(newInfo->name, infoName); 
			strcpy(newInfo->value, infoValue); 

			//case 1: empty list
			if (curContact->information == NULL) {
				curContact->information = newInfo; 
				newInfo->next = NULL; 
				return; 
			}
			//case 2: the letter goes before the first value 
			if (strcmp(infoName, curContact->information->name) < 0) {
				newInfo->next = curContact->information;
				curContact->information = newInfo;  
				return; 
			}
			//case 4: search for the right position
			for(Info* curInfo = curContact->information; curInfo != NULL; curInfo = curInfo->next) {
				//case 3: highest value, insert at end
				if (curInfo->next == NULL) {
					curInfo->next = newInfo;
					return; 
				}
				if(strcmp(newInfo->name, curInfo->next->name) < 0) {
					newInfo->next = curInfo->next; 
					curInfo->next = newInfo; 
					return; 
				}
			}

		}
	}
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// remove information from a contact
//	1. Make sure a contact with that name exists
//	2. Make sure the informational item exists in that contact
//	3. Remove that piece of information from the contact
void removeInformation(Contact* myContacts, char* contactName, char* infoName) {
	Contact* curContact = myContacts; 
	for (; curContact != NULL; curContact = curContact->next) {
		if (strcmp(curContact->name, contactName) == 0) {
			//if the info is at the head
			if(curContact->information == NULL) {
				return; 
			}

			//case 2: 
			if(strcmp(curContact->information->name, infoName) == 0) {
				Info* tempInfo = curContact->information->next;  
				curContact->information = tempInfo; 
				return; 
			}

			Info* previousInfo = curContact->information; 
			Info* currentInfo = curContact->information->next; 
			while (currentInfo && strcmp(currentInfo->name, infoName) != 0) {
				previousInfo = currentInfo; 
				currentInfo = currentInfo->next; 
			}
			
			previousInfo->next = currentInfo->next; 
			free(currentInfo); 
		}
	}
	
	return; 
}


/////////////////////////////////////////////////////////////////////////////////////////////
// remove a contact (and all the informational items for that contact)
//	1. Make sure a contact with that name exists
//	2. Remove that contact 
Contact *removeContact(Contact *myContacts, char *contactName) {
	//if its the contact with the first name; 
	if(strcmp(myContacts->name, contactName) == 0) {
		Contact* tempContact = myContacts; 
		myContacts = myContacts->next; 
		free(tempContact); 
		return myContacts; 
	}

	Contact* curContact = myContacts; 
	for (; curContact->next != NULL; curContact = curContact->next) {
		if (strcmp(curContact->next->name, contactName) == 0) {
			Contact* freeContact = curContact->next; 
			curContact->next = curContact->next->next;
			free(freeContact);  
			return myContacts; 
		}
	}
	printf("\tError: contact with that name does not exist\n"); 
	return myContacts;
}
