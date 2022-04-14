#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "libsys.h"

// Your code must support menu-driven functionality.
// Function calls rollno_libsys.h

int main()
{
	printf("============ Library Management System ============\n\n");

	printf("Operations - \n"

		   "1  - CREATE\n"
		   "2  - OPEN\n"
		   "3  - ADD_BOOK\n"
		   "4  - ADD_STUDENT {roll num}\n"
		   "5  - SEARCH_BOOK_ISBN {isbn}\n"
		   "6  - SEARCH_BOOK_TITLE {title}\n"
		   "7  - SEARCH_STUDENT_ROLLNUM {roll num}\n"
		   "8  - SEARCH_STUDENT_NAME {name}\n"
		   "9  - DELETE_BOOK {isbn}\n"
		   "10 - DELETE STUDENT {roll num}\n"
		   "11 - ISSUE {isbn} {roll num}\n"
		   "12 - CLOSE\n\n");

	printf("==================================================\n\n");

	int running = 1;
	int q, arg1, arg2;
	float arg;
	struct Book book;
	struct Student stud;
	struct Issue issu;

	while (running)
	{
		printf("Enter Operation: ");
		scanf("%d", &q);

		switch (q)
		{
		case 1:
			printf("CREATE --> Enter Book_filename, Stud_filename, Issue_filename: ");
			char charg1[50], charg2[50], charg3[50];
			scanf("%s %s %s", charg1, charg2, charg3);

			if (!libsys_create(charg1, charg2, charg3))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");
			break;
		case 2:
			printf("OPEN --> Enter Book_filename, Stud_filename, Issue_filename: ");
			char charg4[50], charg5[50], charg6[50];
			scanf("%s %s %s", charg4, charg5, charg6);
			if (!libsys_open(charg4, charg5, charg6))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");
			break;

		case 3:
			printf("PUT_BOOK_ISBN --> Enter ISBN: ");
			scanf("%d", &arg1);
			printf("PUT_BOOK_ISBN --> Enter TITLE: ");
			char charg7[50];
			scanf("%s", charg7);
			printf("PUT_BOOK_ISBN --> Enter AUTHOR: ");
			char charg8[50];
			scanf("%s", charg8);
			printf("PUT_BOOK_ISBN --> Enter PRICE: ");
			scanf("%f", &arg);
			book.isbn = arg1;
			strcpy(book.author, charg8);
			book.price = arg;
			strcpy(book.title, charg7);
			if (!put_book_by_isbn(arg1, &book))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");
			break;

		case 4:
			printf("PUT_STUD_ROLLNO --> Enter ROLLNO: ");
			scanf("%d", &arg1);
			printf("PUT_STUD_ROLLNO --> Enter NAME: ");
			char temp1[50];
			scanf("%s", temp1);

			printf("PUT_STUD_ROLLNO --> Enter ADDRESS: ");
			char temp2[50];
			scanf("%s", temp2);

			printf("PUT_STUD_ROLLNO --> Enter CGPA: ");
			scanf("%d", &arg2);
			stud.rollno = arg1;
			stud.cgpa = arg2;
			strcpy(stud.address, temp2);
			strcpy(stud.name, temp1);
			if (!put_student_by_rollno(arg1, &stud))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");
			break;

		case 5:
			printf("GET_BOOK_ISBN --> Enter ISBN: ");
			scanf("%d", &arg1);
			if (!get_book_by_isbn(arg1, &book))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");

			break;

		case 6:
			printf("GET_BOOK_TITLE --> Enter title: ");
			char temp3[50];
			scanf("%s", temp3);
			if (!get_book_by_title(temp3, &book))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");
			break;

		case 7:
			printf("GET_STUD_ROLLNUM --> Enter rollnum: ");
			scanf("%d", &arg1);
			if (!get_student_by_rollno(arg1, &stud))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");
			break;

		case 8:
			printf("GET_STUD_NAME --> Enter name: ");
			char temp4[50];
			scanf("%s", temp4);
			if (!get_student_by_name(temp3, &stud))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");
			break;

		case 9:
			printf("DELETE_BOOK --> Enter ISBN: ");
			scanf("%d", &arg1);
			if (!delete_book_by_isbn(arg1))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");
			break;

		case 10:
			printf("DELETE_STUD --> Enter rollnum: ");
			scanf("%d", &arg1);
			if (!delete_student_by_rollno(arg1))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");

			break;

		case 11:
			printf("ISSUE --> Enter ISBN and ROLLNUM: ");
			scanf("%d %d", &arg1, &arg2);
			if (!issue(arg1, arg2))
				printf("SUCCESS\n");
			else
				printf("FAILURE\n");
			break;

		case 12:
			if (!libsys_close())
			{
				printf("SUCCESS\n");
				running = 0;
			}
			else
				printf("FAILURE\n");
			break;
		}
	}

	printf("=============== EXITED ===============\n\n");
}
