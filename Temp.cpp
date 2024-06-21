#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#define N 50
#define M 30

using namespace std;

double currentincome = 0;
double currentexpense = 0;

struct node
{
  char date[M];
  double amount;
  char category[N];
  struct node *next;
} ;

struct node *income = NULL;

struct node *expense = NULL;

struct reportNode
{
  char date[30];
  double amount;
  char category[50];
  struct reportNode *next;
};


struct reportQueue
{
  struct reportNode *front;
  struct reportNode *rear;
};


struct record
{
  double x, y;
} *point = NULL;


void create(char x[], double y, char z[], struct node **temp);
void display(int a3);
void setTextColor(int color);
void resetTextColor();
void animateIntro();
struct node *readnext(struct node *ptr, FILE *fpointer);
void writeincome(struct node *ptr);
void writeexpense(struct node *ptr);
void deleterecord(struct node **ptr, const char *fileName);
void deleteIncome(struct node **head, double *currentIncome);
void deleteExpense(struct node **head, double *currentExpense);
void undoOperation(struct node **income, struct node **expense, double *currentIncome, double *currentExpense);
void redoOperation(struct node **income, struct node **expense, double *currentIncome, double *currentExpense);
void generateReport(struct node *income, struct node *expense);
struct node *readincome(struct node *ptr);
struct node *readexpense(struct node *ptr);
void write(struct record *point);
struct record *readrecord();

int main()
{
  int option, value;

  double b;
  char c[N], a[M];
  char s1[15], s2[15], s3[15];
  
  animateIntro();

  if (fopen("Record.bin", "rb") != NULL)                                                                             
  {
    point = readrecord();
    currentincome = point->x;
    currentexpense = point->y;
  }

  if (fopen("myincome.bin", "rb") != NULL) 
  {
    income = readincome(income);
  }

  if (fopen("myexpense.bin", "rb") != NULL)
  {
    expense = readexpense(expense);
  }

  do
  {
    setTextColor(14);
    printf("                                                           __DASHBOARD__                                               ");
    setTextColor(15);
    printf("                                    _______________________________________________\n  ");
    printf("                                                  YOUR INCOME   =      %.2lf BDT      \n ",currentincome );
    setTextColor(4);
    printf("                                                   YOUR EXPENSE  =      %.2lf BDT     \n ", currentexpense);
    setTextColor(9);
    printf("                                                   YOUR BALANCE  =      %.2lf BDT     \n ", currentincome - currentexpense);
    setTextColor(15);
    printf("                                           _______________________________________________\n");
    setTextColor(14);
    printf("   ***MENU***  \n\n");
    setTextColor(9);
    printf("1. INSERT INCOME\n");
    printf("2. INSERT EXPENSE\n");
    setTextColor(8);
    printf("3. VIEW INCOME RECORD\n");
    printf("4. VIEW EXPENSE RECORD\n");
    setTextColor(4);
    printf("5. DELETE INCOME\n");
    printf("6. DELETE EXPENSE\n");
    printf("7. DELETE RECORDS\n");
    setTextColor(10);
    printf("8. UNDO\n");
    printf("9. REDO\n");
    setTextColor(15);
    printf("10. GENERATE/SAVE REPORT\n");
    printf("11.EXIT\n");
    printf("\n");
    setTextColor(15);
    printf("ENTER THE OPTION FROM THE ABOVE -");

    scanf("%d", &option);
    printf("\n\n\n");

    switch (option)
    {
    case 1:
      setTextColor(14);
      printf("**************   ADD INCOME   *****************\n\n");
      setTextColor(15);
      printf("Enter The Date(e.g day month year)\n");
      scanf("%s %s %s", s1, s2, s3);                    // gets,fgets and other functions are not working thats why these stepes have done
      strcpy(a, " ");
      strcat(a, s1);
      strcat(a, "-");
      strcat(a, s2);
      strcat(a, "-");
      strcat(a, s3);

      printf("Enter The Amount:\n");
      scanf("%lf", &b);

      printf("Enter the Category:\n");
      scanf("%s", &c);

      currentincome = currentincome + b;
      create(a, b, c, &income);
      writeincome(income);

      break;
    case 2:
      setTextColor(14);
      printf("**************    ADD EXPENSE   *****************\n\n");
      setTextColor(15);
      printf("Enter The Date(e.g day month year)\n");

      scanf("%s %s %s", s1, s2, s3);
      strcpy(a, "");
      strcat(a, s1);
      strcat(a, "-");
      strcat(a, s2);
      strcat(a, "-");
      strcat(a, s3);

      printf("Enter The Amount\n");
      scanf("%lf", &b);
      printf("Enter The Category\n");
      scanf("%s", &c); 
 
      currentexpense = currentexpense + b;
      create(a, b, c, &expense);
      writeexpense(expense);

      break;
    case 3:
      setTextColor(14);
      printf("*********   YOUR INCOME RECORD IS   *******\n\n");
      display(3);
      break;
    case 4:
      setTextColor(4);
      printf("*********   YOUR EXPENSE RECORD IS   *******\n\n");
      display(4);
      break;
    case 5: 
      deleteIncome(&income, &currentincome);
      break;

    case 6: 
      deleteExpense(&expense, &currentexpense);
      break;
      case 7:
  setTextColor(14);
  printf("************** DELETE ALL RECORDS *****************\n");
  setTextColor(4);
  printf("Are you sure you want to delete all records? (1 for Yes / 0 for No): ");
  scanf("%d", &value);
  if (value == 1)
  {
    
    deleterecord(&income, "myincome.bin");
    deleterecord(&expense, "myexpense.bin");
    currentincome = 0;
    currentexpense = 0;
    setTextColor(15);
    printf("All records deleted successfully.\n");
  }
  break;

    case 8: 
      undoOperation(&income, &expense, &currentincome, &currentexpense);
      break;
    case 9: 
      redoOperation(&income, &expense, &currentincome, &currentexpense);
      break;
    case 10: 
      generateReport(income, expense);
      break;
    case 11:
    point = (struct record *)malloc(sizeof(struct record));
    point->x = currentincome;
    point->y = currentexpense;
    write(point);
    printf("                                                  Exiting the program. Thank you!!            \n");
    break; 
    }
  } 
  while (option != 11);

  return 0;
}

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor() {
    setTextColor(7); 
}



void animateIntro() {
    system("CLS");

    setTextColor(9);

    cout << "\t\t\t\t**************\n";
    setTextColor(15);
    cout << "\t\t\t\tEXPENSE TRACKER\n";
    setTextColor(9);
    cout << "\t\t\t\t**************";

    for (int i = 0; i < 3; ++i) {
        Sleep(500);
        system("CLS");
        Sleep(500);
        cout<< "                                        \n ";
        cout<< "                                        \n ";
        cout<< "                                        \n ";
        cout<< "                                        \n ";
        setTextColor(9);
        cout << "\t\t\t\t\t\t\t************************\n";
        setTextColor(15);
        cout << "\t\t\t\t\t\t\t    EXPENSE TRACKER\n";
        setTextColor(9);
        cout << "\t\t\t\t\t\t\t************************";
    }
    setTextColor(14);
    cout << "\n\t\t\t\t                      -- Press SPACE to continue--";
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ')
                break;
        }
    }
    system("CLS");
}

void create(char x[], double y, char z[], struct node **temp) 
{
  struct node *newnode, *ptr;
  newnode = (struct node *)malloc(sizeof(struct node));
  if (*temp == NULL)
  {
    strcpy(newnode->date, x);
    newnode->amount = y;
    strcpy(newnode->category, z);
    newnode->next = NULL;
    *temp = newnode;
  }
  else
  {
    ptr = *temp;
    while (ptr->next != NULL)
    {
      ptr = ptr->next;
    }
    strcpy(newnode->date, x);
    newnode->amount = y;
    strcpy(newnode->category, z);
    newnode->next = NULL;
    ptr->next = newnode;
  }
}

void deleterecord(struct node **ptr, const char *fileName)
{
  struct node *freeme = *ptr;
  struct node *holdme = NULL;

  while (freeme != NULL)
  {
    holdme = freeme->next;
    free(freeme);
    freeme = holdme;
  }

  
  *ptr = NULL;

  
  FILE *fpointer = fopen(fileName, "wb");
  if (fpointer != NULL)
  {
    fclose(fpointer);
  }
  else
  {
    setTextColor(4);
    printf("Error updating the file %s\n", fileName);
  }
}


struct node *readnext(struct node *ptr, FILE *fpointer)
{

  if (ptr == NULL)
  {
    ptr = (struct node *)malloc(sizeof(struct node));
    fread(ptr, sizeof(struct node), 1, fpointer);
    ptr->next = NULL;
  }
  else
  {
    struct node *ptr1 = ptr;
    struct node *ptr2 = (struct node *)malloc(sizeof(struct node));
    while (ptr1->next != NULL)
    {
      ptr1 = ptr1->next;
    }
    fread(ptr2, sizeof(struct node), 1, fpointer);
    ptr1->next = ptr2;
    ptr2->next = NULL;
  }
  return ptr;
}

struct node *readincome(struct node *ptr)
{
  FILE *fpointer;
  fpointer = fopen("myincome.bin", "rb");
  if (fpointer != NULL)
  {
  
    ptr = NULL;

    fseek(fpointer, 0, SEEK_END);
    long filesize = ftell(fpointer);
    rewind(fpointer);
    int entries = (int)(filesize / (sizeof(struct node)));
    for (int i = 0; i < entries; i++)
    {
      fseek(fpointer, (sizeof(struct node) * i), SEEK_SET);
      ptr = readnext(ptr, fpointer);
    }

    fclose(fpointer); 
  }
  else
  {
    setTextColor(4);
    printf("ERROR IN OPENINNG FILE\n");
  }
  return ptr;
}



void display(int a3)
{
  if (a3 == 3)                             
  {

    if (fopen("myincome.bin", "rb") == NULL) 

    {
      setTextColor(14);
      printf("NO RECORDS AVAILABLE\n\n");
      setTextColor(15);
      printf("________________________________________________________________________________________________________________\n\n");
    }
    else
    {
      // income=readincome(income);
      struct node *ptr2 = income;
      while (ptr2 != NULL)
      {
        setTextColor(15);
        printf("Date: %s\nAmount: %.2lf BDT\nCategory: %s\n\n", ptr2->date, ptr2->amount, ptr2->category);
        ptr2 = ptr2->next;
      }
      printf("________________________________________________________________________________________________________________\n\n");
    }
  }
  else if (a3 == 4) 
  {

    if (fopen("myexpense.bin", "rb") == NULL) 
    {
      setTextColor(14);
      printf("NO RECORDS AVAILABLE\n\n");
      setTextColor(15);
      printf("________________________________________________________________________________________________________________\n\n");
    }
    else
    {

      //   expense=readexpense(expense);
      struct node *ptr2 = expense;
      while (ptr2 != NULL)
      {
        printf("Date: %s\nAmount: %.2lf BDT\nCategory: %s\n\n", ptr2->date, ptr2->amount, ptr2->category);
        ptr2 = ptr2->next;
      }
      printf("________________________________________________________________________________________________________________\n\n");
    }
  }
}

void writeincome(struct node *ptr)
{
  FILE *fpointer;
  fpointer = fopen("myincome.bin", "wb");
  if (fpointer != NULL)
  {
    struct node *ptr1 = ptr;
    struct node *holdnext = NULL;
    while (ptr1 != NULL)
    {
      holdnext = ptr1->next;
      ptr1->next = NULL;
      fseek(fpointer, 0, SEEK_END);
      fwrite(ptr1, sizeof(struct node), 1, fpointer); /*everytime we write into file,it will overwrite the data whole data will be deleted and new data willl be written intofile*/
      ptr1->next = holdnext;
      holdnext = NULL;
      ptr1 = ptr1->next;
    }
    fclose(fpointer);
    fpointer = NULL;
    setTextColor(15);
    printf("\nINCOME SAVED SUCCESSFULLY!!!\n\n");
    setTextColor(15);
    printf("________________________________________________________________________________________________________________\n\n");
  }
  else
  {
    setTextColor(4);
    printf("\nCANNOT SAVE INCOME..TRY AGAIN\n");
    setTextColor(15);
    printf("________________________________________________________________________________________________________________\n\n");
  }
}

void writeexpense(struct node *ptr)
{
  FILE *fpointer;
  fpointer = fopen("myexpense.bin", "wb");
  if (fpointer != NULL)
  {
    struct node *ptr1 = ptr;
    struct node *holdnext = NULL;
    while (ptr1 != NULL)
    {
      holdnext = ptr1->next;
      ptr1->next = NULL;
      fseek(fpointer, 0, SEEK_END);
      fwrite(ptr1, sizeof(struct node), 1, fpointer); 
                                                              
      ptr1->next = holdnext;
      holdnext = NULL;
      ptr1 = ptr1->next;
    }
    fclose(fpointer);
    fpointer = NULL;
    printf("\nEXPENSE SAVED SUCCESSFULLY\n\n");
    printf("________________________________________________________________________________________________________________\n\n");
  }
  else
  {
    setTextColor(4);
    printf("\nCANNOT SAVE EXPENSE..TRY AGAIN\n\n");
    setTextColor(15);
    printf("________________________________________________________________________________________________________________\n\n");
  }
}

struct node *readexpense(struct node *ptr)
{
  FILE *fpointer;
  fpointer = fopen("myexpense.bin", "rb");
  if (fpointer != NULL)
  {
    ptr = NULL;

    fseek(fpointer, 0, SEEK_END);
    long filesize = ftell(fpointer);
    rewind(fpointer);
    int entries = (int)(filesize / (sizeof(struct node)));
    for (int i = 0; i < entries; i++)
    {
      fseek(fpointer, (sizeof(struct node) * i), SEEK_SET);
      ptr = readnext(ptr, fpointer);
    }

    fclose(fpointer); 
  }
  else
  {
    setTextColor(15);
    printf("Cannot open file\n");
  }
  return ptr;
}


void write(struct record *point)
{
  FILE *fpointer;
  fpointer = fopen("Record.bin", "wb");
  if (fpointer != NULL)
  {

    fseek(fpointer, 0, SEEK_END);
    fwrite(point, sizeof(struct record), 1, fpointer); 
                                                            
  }
  else
  {
    printf("FILEOPEN ERROR\n");
  }
  fclose(fpointer);
  fpointer = NULL;
}

struct record *readrecord()
{
  FILE *fpointer;
  fpointer = fopen("Record.bin", "rb");
  struct record *ptr = NULL;

  if (fpointer != NULL)
  {

    fseek(fpointer, 0, SEEK_SET);

    ptr = (struct record *)malloc(sizeof(struct record));
    fread(ptr, sizeof(struct record), 1, fpointer);
  }
  else
  {
    printf("CANNOT OPEN FILE\n");
  }
  return ptr;
}

void deleteIncome(struct node **head, double *currentIncome)
{
  if (*head == NULL)
  {
    printf("No income records to delete.\n");
    return;
  }

  struct node *temp = *head;
  *currentIncome -= temp->amount;
  *head = temp->next;
  free(temp);

  printf("Income record deleted successfully.\n");
}

void deleteExpense(struct node **head, double *currentExpense)
{
  if (*head == NULL)
  {
    printf("No expense records to delete.\n");
    return;
  }

  struct node *temp = *head;
  *currentExpense -= temp->amount;
  *head = temp->next;
  free(temp);

  printf("Expense record deleted successfully.\n");
}

void undoOperation(struct node **income, struct node **expense, double *currentIncome, double *currentExpense)
{
  
  if (*income == NULL && *expense == NULL)
  {
    printf("No operations to undo.\n");
    return;
  }

  
  if (*income != NULL)
  {
    *currentIncome -= (*income)->amount;

    
    struct node *temp = *income;
    *income = (*income)->next;
    temp->next = *expense;
    *expense = temp;

    printf("Last income operation undone.\n");
  }
  
  else if (*expense != NULL)
  {
    *currentExpense -= (*expense)->amount;

  
    struct node *temp = *expense;
    *expense = (*expense)->next;
    temp->next = *income;
    *income = temp;

    printf("Last expense operation undone.\n");
  }
}

void redoOperation(struct node **income, struct node **expense, double *currentIncome, double *currentExpense)
{
  
  if (*income == NULL && *expense == NULL)
  {
    printf("No operations to redo.\n");
    return;
  }

  
  if (*expense != NULL)
  {
    *currentIncome += (*expense)->amount;

    
    struct node *temp = *expense;
    *expense = (*expense)->next;
    temp->next = *income;
    *income = temp;

    printf("Last undone income operation redone.\n");
  }
  
  else if (*income != NULL)
  {
    *currentExpense += (*income)->amount;

    
    struct node *temp = *income;
    *income = (*income)->next;
    temp->next = *expense;
    *expense = temp;

    printf("Last undone expense operation redone.\n");
  }
}


void initReportQueue(struct reportQueue *queue)
{
  queue->front = NULL;
  queue->rear = NULL;
}


void enqueueReport(struct reportQueue *queue, char date[], double amount, char category[])
{
  struct reportNode *newNode = (struct reportNode *)malloc(sizeof(struct reportNode));
  strcpy(newNode->date, date);
  newNode->amount = amount;
  strcpy(newNode->category, category);
  newNode->next = NULL;

  if (queue->rear == NULL)
  {
    queue->front = newNode;
    queue->rear = newNode;
  }
  else
  {
    queue->rear->next = newNode;
    queue->rear = newNode;
  }
}


void dequeueReport(struct reportQueue *queue)
{
  if (queue->front == NULL)
  {
    return; 
  }

  struct reportNode *temp = queue->front;
  queue->front = temp->next;

  if (queue->front == NULL)
  {
    queue->rear = NULL; 
  }

  free(temp);
}


void generateReport(struct node *income, struct node *expense)
{
  printf("Generating and saving reports...\n");

  
  struct reportQueue reportQueue;
  initReportQueue(&reportQueue);

  
while (income != NULL)
{
  enqueueReport(&reportQueue, income->date, income->amount, income->category);
  income = income->next;
}

while (expense != NULL)
{
  
  enqueueReport(&reportQueue, expense->date, -expense->amount, expense->category);
  expense = expense->next;
}

  
  FILE *reportFile = fopen("reports.txt", "w");
  if (reportFile == NULL)
  {
    printf("Error opening file for saving reports.\n");
    return;
  }

  
  while (reportQueue.front != NULL)
  {
    fprintf(reportFile, "Type: %s\nDate: %s\nAmount: %.2lf BDT\nCategory: %s\n\n",
            (reportQueue.front->amount >= 0) ? "Income" : "Expense",
            reportQueue.front->date, fabs(reportQueue.front->amount), reportQueue.front->category);

    
    dequeueReport(&reportQueue);
  }

  
  fclose(reportFile);
  printf("Reports generated and saved to 'reports.txt'.\n");
}
