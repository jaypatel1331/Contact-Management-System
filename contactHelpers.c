#define _CRT_SECURE_NO_WARNINGS

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        contents below...                        |
// +-------------------------------------------------+


#include <stdio.h>
#include <string.h>

#include "contactHelpers.h"
#include "contacts.h"

#define MAXCONTACTS 5


// Clear the standard input buffer
void clearKeyboard(void)
{
    while (getchar() != '\n'); // empty execution code block on purpose
}

// pause function definition goes here:
void pause(void)
{
    printf("(Press Enter to Continue)");
    clearKeyboard();
}

// getInt function definition goes here:
int getInt(void)
{
    int value = 0, true = 1;
    char valid = '\0';

    while (true)
    {
        scanf(" %d%c", &value, &valid);
        if (valid == '\n')
        {
            true = 0;
        }
        else
        {
            printf("*** INVALID INTEGER *** <Please enter an integer>: ");
            clearKeyboard();
        }
    }

    return value;
}

// getIntInRange function definition goes here:
int getIntInRange(int min, int max)
{
    int valid, correct = 1;

    while (correct)
    {
        valid = getInt();
        if (min <= valid && valid <= max)
        {
            correct = 0;
        }
        else
        {
            printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
        }
    }

    return valid;
}

// yes function definition goes here:
int yes(void)
{

    char lChar = 'x';
    char lChar2 = 'x';
    int response = -1;

    scanf(" %c%c", &lChar, &lChar2);

    while (!((lChar2 == '\n') && ((lChar == 'Y') || (lChar == 'y') ||
        (lChar == 'n') || (lChar == 'N'))))
    {
        clearKeyboard();
        printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
        scanf(" %c%c", &lChar, &lChar2);
       
    }

    if ((lChar == 'Y') || (lChar == 'y')) {
        response = 1;
    }
    else if ((lChar == 'N') || (lChar == 'n')) {
        response = 0;
    }

    return response;
}

// menu function definition goes here:
int menu(void)
{
    printf("Contact Management System\n");
    printf("-------------------------\n");
    printf("1. Display contacts\n");
    printf("2. Add a contact\n");
    printf("3. Update a contact\n");
    printf("4. Delete a contact\n");
    printf("5. Search contacts by cell phone number\n");
    printf("6. Sort contacts by cell phone number\n");
    printf("0. Exit\n");
    printf("\n");
    printf("Select an option:> ");
    return getIntInRange(0, 6);
}

// contactManagerSystem function definition goes here:
void contactManagerSystem(void)
{

    struct Contact contact[MAXCONTACTS] =
    { { { "Rick", {'\0'}, "Grimes" },
 { 11, "Trailer Park", 0, "A7A 2J2", "King City" },
 { "4161112222", "4162223333", "4163334444" } },
 {
 { "Maggie", "R.", "Greene" },
 { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
 { "9051112222", "9052223333", "9053334444" } },
 {
 { "Morgan", "A.", "Jones" },
 { 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
 { "7051112222", "7052223333", "7053334444" } },
 {
 { "Sasha", {'\0'}, "Williams" },
 { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
 { "9052223333", "9052223333", "9054445555" } },
    };


    int iSelection;

    do {
        iSelection = menu();
        switch (iSelection)
        {
        
        case 1:
            printf("\n");
            displayContacts(contact, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        case 2:
            printf("\n");
            addContact(contact, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        case 3:
            printf("\n");
            updateContact(contact, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        case 4:
            printf("\n");
            deleteContact(contact, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        case 5:
            printf("\n");
            searchContacts(contact, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        case 6:
            printf("\n");
            sortContacts(contact, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        default:
            printf("*** OUT OF RANGE *** <Enter a number between 0 and 6> ");
            break;

        case 0:
            printf("\nExit the program? (Y)es/(N)o: ");
            if (yes() == 1)
            {
                printf("\nContact Management System: terminated\n");
                iSelection = 0;
            }
            else
            {
                printf("\n");
                iSelection = 1;
            }
            break;

        }

    } while (iSelection);

    return;
}


// Generic function to get a ten-digit phone number (ensures 10-digit chars entered)
// ---------------------------------------------------------------------------------
// NOTE: Modify this function to validate only numeric character digits are entered
// ---------------------------------------------------------------------------------
void getTenDigitPhone(char phoneNum[])
{
    int valid = 1;

    while (valid == 1) 
    {
        scanf("%10s", phoneNum);
        clearKeyboard();

        // (String Length Function: validate entry of 10 characters)
        int done = 0;
        if (strlen(phoneNum) == 10)
        {
            int i;
            for (i = 0; i < 10; i++)
            {
                if (phoneNum[i] < '0' || phoneNum[i] > '9')
                {
                    done = 1;
                }
             }
        }
        else
        {
            done = 1;
        }

        if (!done)
        {
            valid = 0;
        }
        else
        { 
            printf("Enter a 10-digit phone number: ");
        }
    }

}

// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
    int i;
    int indexFound = -1;

    for (i = 0; indexFound == -1 && i < size; i++) 
    {
        if (strcmp(contacts->numbers.cell, cellNum) == 0)
        {
            indexFound = i;
        }
        else 
        {
            contacts++;
        }
    }

    return indexFound;
}


// displayContactHeader
// Put empty function definition below:
void displayContactHeader(void)
{
    printf("+-----------------------------------------------------------------------------+\n");
    printf("|                              Contacts Listing                               |\n");
    printf("+-----------------------------------------------------------------------------+\n");

}


// displayContactFooter
// Put empty function definition below:
void displayContactFooter(int count)
{
    printf("+-----------------------------------------------------------------------------+\n");
    printf("Total contacts: %d\n\n", count);

}


// displayContact:
// Put empty function definition below:
void displayContact(const struct Contact *contact)
{
    
    if (contact->name.middleInitial[0] != '\0') 
    {
        printf(" %s %s %s\n", contact->name.firstName,
            contact->name.middleInitial, contact->name.lastName);
    }
    else
    {
        printf(" %s %s\n", contact->name.firstName, contact->name.lastName);
    }

    printf("    C: %-10s   H: %-10s   B: %-10s\n",
            contact->numbers.cell, contact->numbers.home, contact->numbers.business);


    printf("       %d %s, ", contact->address.streetNumber, contact->address.street);


    if (contact->address.apartmentNumber > 0)
        {
            printf("Apt# %d, ", contact->address.apartmentNumber);
        }
    
    printf("%s, %s\n", contact->address.city, contact->address.postalCode);

   
}


// displayContacts:
// Put empty function definition below:
void displayContacts(const struct Contact contacts[], int size)
{
    int i;
    int valid = 0;

    displayContactHeader();

    for (i = 0; i < size; i++) 
    {
        
        if (strlen(contacts[i].numbers.cell) > 0)
        {
            displayContact(&contacts[i]);
            valid++;
        }
    }
    displayContactFooter(valid);

}


// searchContacts:
// Put empty function definition below:
void searchContacts(const struct Contact contacts[], int size)
{
    char phoneNum[11];
    int list = 0;

    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(phoneNum);

    list = findContactIndex(contacts, size, phoneNum);

    if (list == -1) 
    {
        printf("*** Contact NOT FOUND ***\n\n");
    }
    else
    {
        printf("\n");
        displayContact(&contacts[list]);
        printf("\n");
    }
}


// addContact:
// Put empty function definition below:
void addContact(struct Contact contacts[], int size)
{
    char emptyIndex[11] = { '\0' };
    struct Contact newContact = { { { 0 } } };
    int slot = findContactIndex(contacts, size, emptyIndex);

    if (slot != -1) 
    {
        getContact(&newContact);
        contacts[slot] = newContact;
        printf("--- New contact added! ---\n\n");
    }
    else 
    {
        printf("*** ERROR: The contact list is full! ***\n\n");
    }
}


// updateContact:
// Put empty function definition below:
void updateContact(struct Contact contacts[], int size)
{
    char getContact[11] = { '\0' };

    int list;

    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(getContact);

    list = findContactIndex(contacts, size, getContact);

    if (list == -1) 
    {
        printf("*** Contact NOT FOUND ***\n\n");
    }
    else
    {
        printf("\nContact found:\n");
        displayContact(&contacts[list]);
        printf("\n");
        printf("Do you want to update the name? (y or n): ");

        if (yes() == 1) 
        {
            getName(&contacts[list].name);
        }

        printf("Do you want to update the address? (y or n): ");

        if (yes() == 1)
        {
            getAddress(&contacts[list].address);
        }

        printf("Do you want to update the numbers? (y or n): ");

        if (yes() == 1) 
        {
            *contacts[list].numbers.cell = '\0';
            *contacts[list].numbers.home = '\0';
            *contacts[list].numbers.business = '\0';
            getNumbers(&contacts[list].numbers);
        }
        printf("--- Contact Updated! ---\n\n");
    }

}


// deleteContact:
// Put empty function definition below:
void deleteContact(struct Contact contacts[], int size)
{
    char getContact[11] = { '\0' };
    int list;

    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(getContact);
    list = findContactIndex(contacts, size, getContact);

    if (list == -1)
    {
        printf("*** Contact NOT FOUND ***\n\n");
    }
    else
    {
        printf("\nContact found:\n");
        displayContact(&contacts[list]);
        printf("\n");
        printf("CONFIRM: Delete this contact? (y or n): ");
        
        if (yes() == 1) 
        {
            contacts[list].numbers.cell[0] = '\0';
            printf("--- Contact deleted! ---\n");
        }

        printf("\n");
    }
}


// sortContacts:
// Put empty function definition below:
void sortContacts(struct Contact contacts[], int size)
{
    int i, j;
    struct Contact sortNumbers;

    for (i = size - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++) 
        {
            if (strcmp(contacts[j].numbers.cell, contacts[j + 1].numbers.cell) > 0)
            {
                sortNumbers = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = sortNumbers;
            }
        }
    }
    printf("--- Contacts sorted! ---\n\n");
}