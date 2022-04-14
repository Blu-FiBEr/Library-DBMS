#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "libsys.h"

// Define the global variable of libsys
struct LibsysInfo repo_handle;
//--------------------------------create()---------------------------------
int libsys_create(char *repo_name1, char *repo_name2, char *repo_name3)
{

    // create booksys file pointer to open a file in 'wb' mode
    // handle file pointer error if value is NULL return appropriate error code referring to the error codes
    // close file pointer
    char repo_name_1[50];
    strcpy(repo_name_1, repo_name1);
    char extension1[] = ".dat";
    strcat(repo_name_1, extension1);
    FILE *fp_repo = fopen(repo_name_1, "wb");
    if (fp_repo == NULL)
        return LIB_FILE_ERROR;
    fclose(fp_repo);

    // Open the index file in "wb" mode
    // Initialize index file by store "0" to indicate there are zero entries in index file
    int i = 0;
    char name[100];
    while (repo_name_1[i] != '.')
    {
        i++;
    }
    strncpy(name, repo_name_1, i);
    name[i] = 0;
    char extension[] = ".ndx";
    strcat(name, extension);
    FILE *fp_ndx = fopen(name, "wb");
    if (fp_ndx == NULL)
        return LIB_FILE_ERROR;
    int index_entries = 0;
    size_t write_size = fwrite(&index_entries, sizeof(int), 1, fp_ndx);
    if (write_size != 1)
        return LIB_NDX_SAVE_FAILED;
    fclose(fp_ndx);

    // create studsys file pointer to open a file in 'wb' mode
    // handle file pointer error if value is NULL return appropriate error code referring to the error codes
    // close file pointer
    char repo_name_2[50];
    strcpy(repo_name_2, repo_name2);

    strcat(repo_name_2, extension1);
    FILE *fp_repo2 = fopen(repo_name_2, "wb");
    if (fp_repo2 == NULL)
        return LIB_FILE_ERROR;
    fclose(fp_repo2);

    // index for student
    int j = 0;
    char name_1[100];
    while (repo_name_2[j] != '.')
    {
        j++;
    }
    strncpy(name_1, repo_name_2, j);
    name_1[j] = 0;
    strcat(name_1, extension);
    fp_ndx = fopen(name_1, "wb");
    if (fp_ndx == NULL)
        return LIB_FILE_ERROR;
    index_entries = 0;
    write_size = fwrite(&index_entries, sizeof(int), 1, fp_ndx);
    if (write_size != 1)
        return LIB_NDX_SAVE_FAILED;
    fclose(fp_ndx);

    // create issuesys file pointer to open a file in 'wb' mode
    // handle file pointer error if value is NULL return appropriate error code referring to the error codes
    // close file pointer
    char repo_name_3[50];
    strcpy(repo_name_3, repo_name3);

    strcat(repo_name_3, extension1);
    FILE *fp_repo3 = fopen(repo_name_3, "wb");
    if (fp_repo3 == NULL)
        return LIB_FILE_ERROR;
    fclose(fp_repo3);

    // return success
    return LIB_SUCCESS;
}

//--------------------------------open()---------------------------------
int libsys_open(char *book_name, char *stud_name, char *issue_name)
{
    char repo_name[50];
    strcpy(repo_name, book_name);
    char extension1[] = ".dat";
    strcat(repo_name, extension1);
    int i = 0;
    char name[100];
    while (repo_name[i] != '.')
    {
        i++;
    }
    strncpy(name, repo_name, i);
    name[i] = 0;
    char extension[] = ".ndx";
    strcat(name, extension);
    FILE *fp_ndx = fopen(name, "rb+");
    if (fp_ndx == NULL)
        return LIB_FILE_ERROR;
    repo_handle.booksys_ndx_fp = fp_ndx;
    size_t read_size = fread(&repo_handle.book_index_count, sizeof(int), 1, repo_handle.booksys_ndx_fp);
    if (read_size != 1)
        return LIB_FILE_ERROR;
    read_size = fread(repo_handle.book_index_entries, sizeof(struct LIB_NdxInfo), repo_handle.book_index_count, repo_handle.booksys_ndx_fp);
    if (read_size != repo_handle.book_index_count)
        return LIB_FILE_ERROR;
    fclose(repo_handle.booksys_ndx_fp);

    // student index
    char stud_repo_name[50];
    strcpy(stud_repo_name, stud_name);
    strcat(stud_repo_name, extension1);
    int j = 0;
    char stud_name_1[100];
    while (stud_repo_name[j] != '.')
    {
        j++;
    }
    strncpy(stud_name_1, stud_repo_name, j);
    stud_name_1[j] = 0;
    strcat(stud_name_1, extension);
    fp_ndx = fopen(stud_name_1, "rb+");
    if (fp_ndx == NULL)
        return LIB_FILE_ERROR;
    repo_handle.studsys_ndx_fp = fp_ndx;
    read_size = fread(&repo_handle.stud_index_count, sizeof(int), 1, repo_handle.studsys_ndx_fp);
    if (read_size != 1)
        return LIB_FILE_ERROR;
    read_size = fread(repo_handle.stud_index_entries, sizeof(struct LIB_NdxInfo), repo_handle.stud_index_count, repo_handle.studsys_ndx_fp);
    if (read_size != repo_handle.stud_index_count)
        return LIB_FILE_ERROR;
    fclose(repo_handle.studsys_ndx_fp);

    int b_status = booksys_open(book_name);
    int s_status = studsys_open(stud_name);
    int i_status = issuesys_open(issue_name);
    if ((b_status || s_status || i_status) == 0)
        return LIB_SUCCESS;
    else
    {
        repo_handle.stud_repo_status = LIB_REPO_CLOSED;
        repo_handle.book_repo_status = LIB_REPO_CLOSED;
        repo_handle.issue_repo_status = LIB_REPO_CLOSED;
        return LIB_FILE_ERROR;
    }
}
// call booksys_open()
// call studsys_open()
// call issuesys_open()

// Open the index file in rb+ mode
// Read number of index entries from index file
// Load index_entries array by reading index entries from the index 	file
// Close only the index file

// check status of above functions
//  if all of them return success then return SUCCESS else return ERROR

int booksys_open(char *repo_name1)
{
    char repo_name[50];
    strcpy(repo_name, repo_name1);
    char extension1[] = ".dat";
    strcat(repo_name, extension1);
    if (repo_handle.book_repo_status == LIB_REPO_OPEN)
        return LIB_REPO_ALREADY_OPEN;
    FILE *fp_repo = fopen(repo_name, "rb+");
    if (fp_repo == NULL)
        return LIB_FILE_ERROR;
    repo_handle.booksys_data_fp = fp_repo;
    strcpy(repo_handle.booksys_name, repo_name);
    repo_handle.book_repo_status = LIB_REPO_OPEN;
    return LIB_SUCCESS;
}
// 1. assign repo handle a file pointer by opening file in 'rb+' mode
// 2. handle file pointer error if value is NULL return appropriate error code referring to the error codes in libsys.h
// 3. assign values (repo_name) to booksys_repo_handle
// 4. assign value to repo_handle.book_repo_status=LIB_REPO_OPEN;
// 5. return booksys_success

int issuesys_open(char *repo_name1)
{
    char repo_name[50];
    strcpy(repo_name, repo_name1);
    char extension1[] = ".dat";
    strcat(repo_name, extension1);
    if (repo_handle.issue_repo_status == LIB_REPO_OPEN)
        return LIB_REPO_ALREADY_OPEN;
    FILE *fp_repo = fopen(repo_name, "rb+");
    if (fp_repo == NULL)
        return LIB_FILE_ERROR;
    repo_handle.issuesys_data_fp = fp_repo;
    strcpy(repo_handle.issuesys_name, repo_name);
    repo_handle.issue_repo_status = LIB_REPO_OPEN;
    return LIB_SUCCESS;
}

// 1. assign repo handle a file pointer by opening file in 'rb+' mode
// 2. handle file pointer error if value is NULL return appropriate error code referring to the error codes in libsys.h
// 3. assign values (repo_name) to issuesys_repo_handle
// 4. assign value to repo_handle.issue_repo_status=LIB_REPO_OPEN;
// 5. return issuesys_success

int studsys_open(char *repo_name1)
{
    char repo_name[50];
    strcpy(repo_name, repo_name1);
    char extension1[] = ".dat";
    strcat(repo_name, extension1);
    if (repo_handle.stud_repo_status == LIB_REPO_OPEN)
        return LIB_REPO_ALREADY_OPEN;
    FILE *fp_repo = fopen(repo_name, "rb+");
    if (fp_repo == NULL)
        return LIB_FILE_ERROR;
    repo_handle.studsys_data_fp = fp_repo;
    strcpy(repo_handle.studsys_name, repo_name);
    repo_handle.stud_repo_status = LIB_REPO_OPEN;
    return LIB_SUCCESS;
}

// 1. assign repo handle a file pointer by opening file in 'rb+' mode
// 2. handle file pointer error if value is NULL return appropriate error code referring to the error codes
// 3. assign values (repo_name) to studsys_repo_handle
// 4. assign value to repo_handle.stud_repo_status=LIB_REPO_OPEN;
// 5. return studsys_success

//------------------------------book:NO change ----------------------------

int get_book_by_isbn(int key, struct Book *rec)
{
    if (repo_handle.book_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;

    int x = 0;
    int offset;

    for (int i = 0; i < repo_handle.book_index_count; i++)
    {
        if (repo_handle.book_index_entries[i].flag == RECORD_PRESENT && repo_handle.book_index_entries[i].key == key)
        {
            offset = repo_handle.book_index_entries[i].offset;
            x = 1;
            break;
        }
    }
    if (x == 0)
        return LIB_REC_NOT_FOUND;

    fseek(repo_handle.booksys_data_fp, offset, SEEK_SET);
    int temp;
    size_t read_size = fread(&temp, sizeof(int), 1, repo_handle.booksys_data_fp);

    if (temp != key || read_size != 1)
        return LIB_REC_NOT_FOUND;

    read_size = fread(rec, sizeof(struct Book), 1, repo_handle.booksys_data_fp);
    if (read_size != 1)
        return LIB_REC_NOT_FOUND;
    printf("Book Details are:-\nISBN:%d\nTitle:%s\nAuthor:%s\nPrice:%.2f\n", rec->isbn, rec->title, rec->author, rec->price);

    fseek(repo_handle.issuesys_data_fp, 0, SEEK_SET);
    struct Issue temp_issue;
    size_t readsize;
    int y = 0;
    int count = 0;
    struct Student student;
jump:
    readsize = fread(&temp_issue, sizeof(struct Issue), 1, repo_handle.issuesys_data_fp);
    if (readsize != 1)
        y = 1;

    // 4.2 check if isbn is equal to the isbn_to_read
    if (temp_issue.isbn == key && y != 1)
    {
        if (count == 0)
            printf("Book is Issued\nIssued by following students:\n");
        count++;

        get_student_by_rollno(temp_issue.rollno, &student);
        printf("Student %d:\nRollNo:%d\nName:%s\nAddress:%s\nCGPA:%.2f\n", count, student.rollno, student.name, student.address, student.cgpa);
    }
    // 4.3 if yes then read entire record of a book and return libsys_success
    // 4.4 else skip the record and read next isbn of the book
    else if (y == 0)
    {
        goto jump;
    }
    return BOOK_SUCCESS;
    // get_rec_by_key
    // check repo status
    // Search for index entry in index_entries array
    //-----use flag to read valid entries
    // Seek to the file location based on offset in index entry
    // Read the key at the current file location
    // Read the record after reading the key
}

int book_getter(int key, struct Book *rec)
{
    if (repo_handle.book_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;

    int x = 0;
    int offset;

    for (int i = 0; i < repo_handle.book_index_count; i++)
    {
        if (repo_handle.book_index_entries[i].flag == RECORD_PRESENT && repo_handle.book_index_entries[i].key == key)
        {
            offset = repo_handle.book_index_entries[i].offset;
            x = 1;
            break;
        }
    }
    if (x == 0)
        return LIB_REC_NOT_FOUND;

    fseek(repo_handle.booksys_data_fp, offset, SEEK_SET);
    int temp;
    size_t read_size = fread(&temp, sizeof(int), 1, repo_handle.booksys_data_fp);

    if (temp != key || read_size != 1)
        return LIB_REC_NOT_FOUND;

    read_size = fread(rec, sizeof(struct Book), 1, repo_handle.booksys_data_fp);
    if (read_size != 1)
        return LIB_REC_NOT_FOUND;
    return BOOK_SUCCESS;
    // get_rec_by_key
    // check repo status
    // Search for index entry in index_entries array
    //-----use flag to read valid entries
    // Seek to the file location based on offset in index entry
    // Read the key at the current file location
    // Read the record after reading the key
}

//-----check index file for key
//-----if key already present check for flag [flag=1 : entry is valid]
//-----if key is present but flag is 0 then just add entry at same index i.e update only offset and update flag; return status
//-----if key is present but flag is 1 return failure as data is already present
//-----if key is not prsent then proceed with following steps:

// Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to array using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
// return status

int put_book_by_isbn(int key, struct Book *rec)
{
    if (repo_handle.book_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;
    int x = -2;
    for (int i = 0; i < repo_handle.book_index_count; i++)
    {
        if (repo_handle.book_index_entries[i].key == key)
        {
            if (repo_handle.book_index_entries[i].flag == RECORD_PRESENT)
                x = -1;

            else
                x = i;

            break;
        }
    }
    fseek(repo_handle.booksys_data_fp, 0, SEEK_END);
    int current_pos = ftell(repo_handle.booksys_data_fp);

    if (x == -1)
        return BOOK_FAILURE;

    else if (x >= 0)
    {
        repo_handle.book_index_entries[x].flag = RECORD_PRESENT;
        repo_handle.book_index_entries[x].offset = current_pos;
    }

    else
    {
        struct LIB_NdxInfo temp;
        temp.key = key;
        temp.offset = current_pos;
        temp.flag = RECORD_PRESENT;
        strcpy(temp.second_key, rec->title);
        repo_handle.book_index_entries[repo_handle.book_index_count] = temp;
        repo_handle.book_index_count++;
    }

    // 4. write isbn_to_write
    size_t size1 = fwrite(&key, sizeof(int), 1, repo_handle.booksys_data_fp);

    // 5. write book record
    size_t size2 = fwrite(rec, sizeof(struct Book), 1, repo_handle.booksys_data_fp);

    if (size1 != 1 || size2 != 1)
        return LIB_ADD_FAILED;

    return BOOK_SUCCESS;
}

int delete_book_by_isbn(int key)
{
    if (repo_handle.book_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;

    struct Book temp1;
    if (book_getter(key, &temp1) != BOOK_SUCCESS)
        return LIB_REC_NOT_FOUND;
    else
    {
        fseek(repo_handle.issuesys_data_fp, 0, SEEK_SET);
        struct Issue temp;
        size_t readsize;
        int ans = 0, y = 0;

    jump:
        readsize = fread(&temp, sizeof(struct Issue), 1, repo_handle.issuesys_data_fp);
        if (readsize != 1)
            y = 1;

        // 4.2 check if isbn is equal to the isbn_to_read
        if (temp.isbn == key && y != 1)
        {
            ans = 1;
        }
        // 4.3 if yes then read entire record of a book and return libsys_success
        // 4.4 else skip the record and read next isbn of the book
        else if (y == 0)
        {
            goto jump;
        }
        if (ans == 1)
            return BOOK_FAILURE;

        for (int i = 0; i < repo_handle.book_index_count; i++)
        {
            if (repo_handle.book_index_entries[i].flag == RECORD_PRESENT && repo_handle.book_index_entries[i].key == key)
            {
                repo_handle.book_index_entries[i].flag = RECORD_DELETED;
            }
        }
    }
    return BOOK_SUCCESS;
    //-----delete_rec_by_key
    //-----check repo status
    //-----Search for index entry in index_entries array
    //-----if key matches and flag is 1 then reset flag
    //-----if key matches but flag is already reset return status
    //-----if key doesn't match then return status
}

//-----------------------------student: additional code---------------------------
int put_student_by_rollno(int rollno_to_write, struct Student *rec)
{ // 1. check if repo status is closed then return return appropriate error code referring to the error codes in libsys.h
    if (repo_handle.stud_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;
    int x = -2;
    for (int i = 0; i < repo_handle.stud_index_count; i++)
    {
        if (repo_handle.stud_index_entries[i].key == rollno_to_write)
        {
            if (repo_handle.stud_index_entries[i].flag == RECORD_PRESENT)
                x = -1;

            else
                x = i;

            break;
        }
    }
    fseek(repo_handle.studsys_data_fp, 0, SEEK_END);
    int current_pos = ftell(repo_handle.studsys_data_fp);

    if (x == -1)
        return BOOK_FAILURE;

    else if (x >= 0)
    {
        repo_handle.stud_index_entries[x].flag = RECORD_PRESENT;
        repo_handle.stud_index_entries[x].offset = current_pos;
    }

    else
    {
        struct LIB_NdxInfo temp;
        temp.key = rollno_to_write;
        temp.offset = current_pos;
        temp.flag = RECORD_PRESENT;
        strcpy(temp.second_key, rec->name);
        repo_handle.stud_index_entries[repo_handle.stud_index_count] = temp;
        repo_handle.stud_index_count++;
    }

    // 4. write isbn_to_write
    size_t size1 = fwrite(&rollno_to_write, sizeof(int), 1, repo_handle.studsys_data_fp);

    // 5. write book record
    size_t size2 = fwrite(rec, sizeof(struct Student), 1, repo_handle.studsys_data_fp);

    if (size1 != 1 || size2 != 1)
        return LIB_ADD_FAILED;

    return BOOK_SUCCESS;
}

// 1. check if repo status is closed then return return appropriate error code referring to the error codes
// 2. else continue with following action sequence
// 3. set the file pointer to end
// 4. write rollno_to_write
// 5. write Student record
// 6. if both actions are successful then return studsys_success
// 7. else return studsys_add_failed

int get_student_by_rollno(int rollno_to_read, struct Student *rec)
{ // 1. check if repo status is closed then  return appropriate error code referring to the error codes in libsys.h
    if (repo_handle.stud_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;
    // 2. else continue with following action sequence
    // 3. set the file pointer to end
    /**fseek(repo_handle.studsys_data_fp, 0, SEEK_SET);
    // 4.1 read isbn
    int temp_roll;
    size_t readsize;

jump:
    readsize = fread(&temp_roll, sizeof(int), 1, repo_handle.studsys_data_fp);
    if (readsize != 1)
        return LIB_REC_NOT_FOUND;
    // 4.2 check if isbn is equal to the isbn_to_read
    if (temp_roll == rollno_to_read)
    {
        fread(rec, sizeof(struct Student), 1, repo_handle.studsys_data_fp);

        return BOOK_SUCCESS;
    }
    // 4.3 if yes then read entire record of a book and return libsys_success
    // 4.4 else skip the record and read next isbn of the book
    else
    {
        fseek(repo_handle.studsys_data_fp, sizeof(struct Student), SEEK_CUR);

        goto jump;
    }
    // 5. Repeat step 4.1 to 4.4 till end of file
    // 6. Return record not found : appropriate error code referring to the error codes in libsys.h
    return LIB_REC_NOT_FOUND;**/

    int x = 0;
    int offset;

    for (int i = 0; i < repo_handle.stud_index_count; i++)
    {
        if (repo_handle.stud_index_entries[i].flag == RECORD_PRESENT && repo_handle.stud_index_entries[i].key == rollno_to_read)
        {
            offset = repo_handle.stud_index_entries[i].offset;
            x = 1;
            break;
        }
    }
    if (x == 0)
        return LIB_REC_NOT_FOUND;

    fseek(repo_handle.studsys_data_fp, offset, SEEK_SET);
    int temp;
    size_t read_size = fread(&temp, sizeof(int), 1, repo_handle.studsys_data_fp);

    if (temp != rollno_to_read || read_size != 1)
        return LIB_REC_NOT_FOUND;

    read_size = fread(rec, sizeof(struct Student), 1, repo_handle.studsys_data_fp);
    if (read_size != 1)
        return LIB_REC_NOT_FOUND;
    return BOOK_SUCCESS;
}

// 1. check if repo status is closed then  return appropriate error code referring to the error codes
// 2. else continue with following action sequence

// 3.1 read rollno
// 3.2 check if rollno is equal to the rollno_to_read
// 3.3 if yes then read entire record of a Student and return studsys_success
// 3.4 else skip the record and read next rollno of the Student
// 4. Repeat step 4.1 to 4.4 till end of file
// 5. Return record not found : appropriate error code referring to the error codes

int delete_student_by_rollno(int key)
{

    if (repo_handle.stud_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;

    struct Student temp1;
    if (get_student_by_rollno(key, &temp1) != BOOK_SUCCESS)
        return LIB_REC_NOT_FOUND;
    else
    {
        for (int i = 0; i < repo_handle.stud_index_count; i++)
        {
            if (repo_handle.stud_index_entries[i].flag == RECORD_PRESENT && repo_handle.stud_index_entries[i].key == key)
            {
                repo_handle.stud_index_entries[i].flag = RECORD_DELETED;
            }
        }
    }
    return BOOK_SUCCESS;
    //-----delete_rec_by_key
    //-----check repo status
    //-----Search for index entry in index_entries array
    //-----if key matches and flag is 1 then reset flag
    //-----if key matches but flag is already reset return status
    //-----if key doesn't match then return status
}
//--------------------------------issue()---------------------------------
int issue(int rollno, int isbn)
{

    // check if book repo status is closed then return return appropriate error code referring to the error codes
    // else continue with following action sequence
    if (repo_handle.book_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;
    // check if student repo status is closed then return return appropriate error code referring to the error codes
    // else continue with following action sequence
    if (repo_handle.stud_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;
    // check if issue repo status is closed then return return appropriate error code referring to the error codes
    // else continue with following action sequence
    if (repo_handle.issue_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;
    // declare student and book variables
    struct Book temp;
    struct Student temp1;
    // get book by isbn and store status in status1
    int status1 = book_getter(isbn, &temp);
    // get student by rollno and store status in status2
    int status2 = get_student_by_rollno(rollno, &temp1);
    // if status1 and status2 are successful then continue with following action sequence else return error
    if ((status1 || status2) != 0)
        return LIB_REC_NOT_FOUND;
    // create Issue object and assign rollno and isbn
    struct Issue issue_temp;
    issue_temp.rollno = rollno;
    issue_temp.isbn = isbn;

    // set the file pointer to end
    status1 = fseek(repo_handle.issuesys_data_fp, 0, SEEK_END);
    // write issue record
    size_t write_size = fwrite(&issue_temp, sizeof(struct Issue), 1, repo_handle.issuesys_data_fp);
    // if both actions are successful then return success
    if (status1 == 0 && write_size == 1)
        return BOOK_SUCCESS;
    // else return failed
    else
        return LIB_ADD_FAILED;
}
//----------------------------------close()---------------------------------
int libsys_close()
{

    // call booksys_close()
    // call studsys_close()
    // call issuesys_close()

    char name[100];
    int i = 0;
    while (repo_handle.booksys_name[i] != '.')
    {
        i++;
    }
    strncpy(name, repo_handle.booksys_name, i);
    name[i] = 0;
    char extension[] = ".ndx";
    strcat(name, extension);
    repo_handle.booksys_ndx_fp = fopen(name, "wb");
    if (repo_handle.booksys_ndx_fp == NULL)
        return LIB_FILE_ERROR;
    size_t write_size = fwrite(&repo_handle.book_index_count, sizeof(int), 1, repo_handle.booksys_ndx_fp);
    if (write_size != 1)
        return LIB_NDX_SAVE_FAILED;

    write_size = fwrite(repo_handle.book_index_entries, sizeof(struct LIB_NdxInfo), repo_handle.book_index_count, repo_handle.booksys_ndx_fp);
    if (write_size != repo_handle.book_index_count)
        return LIB_NDX_SAVE_FAILED;
    fclose(repo_handle.booksys_ndx_fp);

    // student index close
    char stud_name[100];
    int j = 0;
    while (repo_handle.studsys_name[j] != '.')
    {
        j++;
    }
    strncpy(stud_name, repo_handle.studsys_name, j);
    stud_name[j] = 0;

    strcat(stud_name, extension);
    repo_handle.studsys_ndx_fp = fopen(stud_name, "wb");
    if (repo_handle.studsys_ndx_fp == NULL)
        return LIB_FILE_ERROR;
    write_size = fwrite(&repo_handle.stud_index_count, sizeof(int), 1, repo_handle.studsys_ndx_fp);
    if (write_size != 1)
        return LIB_NDX_SAVE_FAILED;

    write_size = fwrite(repo_handle.stud_index_entries, sizeof(struct LIB_NdxInfo), repo_handle.stud_index_count, repo_handle.studsys_ndx_fp);
    if (write_size != repo_handle.stud_index_count)
        return LIB_NDX_SAVE_FAILED;
    fclose(repo_handle.studsys_ndx_fp);

    int b_status = booksys_close(repo_handle.booksys_name);
    int s_status = studsys_close(repo_handle.studsys_name);
    int i_status = issuesys_close(repo_handle.issuesys_name);
    if ((b_status || s_status || i_status) == 0)
        return LIB_SUCCESS;
    else
        return LIB_FILE_ERROR;
    // Open the index file in wb mode (write mode, not append mode)
    // Write number of index entries at the beginning of index file
    // Unload the index array into the index file (overwrite the entire index file)
    // Close the index file and data file

    // check status of above functions
    //  if all of them return success then return SUCCESS else return ERROR
}

int booksys_close()
{

    // 1. check if repo status is closed then  return appropriate error code referring to the error codes in libsys.h
    if (repo_handle.book_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;
    // 2. else continue with following action sequence
    // 3. close file pointer
    fclose(repo_handle.booksys_data_fp);
    // 4. set libsys_name as ""
    strcpy(repo_handle.booksys_name, "");
    // 5. set repo_status=LIB_REPO_CLOSED
    repo_handle.book_repo_status = LIB_REPO_CLOSED;
    // 6. return LIB_SUCCESS;
    return LIB_SUCCESS;
    // 1. check if repo status is closed then  return appropriate error code referring to the error codes in libsys.h
    // 2. else continue with following action sequence
    // 3. close file pointer
    // 4. set booksys_name as ""
    // 5. set book_repo_status=LIB_REPO_CLOSED
    // 6. return LIB_SUCCESS;
}

int studsys_close()
{ // 1. check if repo status is closed then  return appropriate error code referring to the error codes in libsys.h
    if (repo_handle.stud_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;
    // 2. else continue with following action sequence
    // 3. close file pointer
    fclose(repo_handle.studsys_data_fp);
    // 4. set libsys_name as ""
    strcpy(repo_handle.studsys_name, "");
    // 5. set repo_status=LIB_REPO_CLOSED
    repo_handle.stud_repo_status = LIB_REPO_CLOSED;
    // 6. return LIB_SUCCESS;
    return LIB_SUCCESS;
}

// 1. check if repo status is closed then  return appropriate error code referring to the error codes
// 2. else continue with following action sequence
// 3. close file pointer
// 4. set studsys_name as ""
// 5. set stud_repo_status=LIB_REPO_CLOSED
// 6. return LIB_SUCCESS;

int issuesys_close()
{
    // 1. check if repo status is closed then  return appropriate error code referring to the error codes in libsys.h
    if (repo_handle.issue_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;
    // 2. else continue with following action sequence
    // 3. close file pointer
    fclose(repo_handle.issuesys_data_fp);
    // 4. set libsys_name as ""
    strcpy(repo_handle.issuesys_name, "");
    // 5. set repo_status=LIB_REPO_CLOSED
    repo_handle.issue_repo_status = LIB_REPO_CLOSED;
    // 6. return LIB_SUCCESS;
    return LIB_SUCCESS;
}

int get_book_by_title(char *title, struct Book *rec)
{
    if (repo_handle.book_repo_status == LIB_REPO_CLOSED)
        return LIB_REPO_NOT_OPEN;

    int x = 0;
    int offset;

    for (int i = 0; i < repo_handle.book_index_count; i++)
    {
        if (repo_handle.book_index_entries[i].flag == RECORD_PRESENT && strcmp(repo_handle.book_index_entries[i].second_key, title) == 0)
        {
            offset = repo_handle.book_index_entries[i].offset;
            x = 1;
            break;
        }
    }
    if (x == 0)
        return LIB_REC_NOT_FOUND;

    fseek(repo_handle.booksys_data_fp, offset, SEEK_SET);
    int temp;
    size_t read_size = fread(&temp, sizeof(int), 1, repo_handle.booksys_data_fp);

    if (read_size != 1)
        return LIB_REC_NOT_FOUND;

    read_size = fread(rec, sizeof(struct Book), 1, repo_handle.booksys_data_fp);
    if (read_size != 1)
        return LIB_REC_NOT_FOUND;
    printf("Book Details are:-\nISBN:%d\nTitle:%s\nAuthor:%s\nPrice:%.2f\n", rec->isbn, rec->title, rec->author, rec->price);

    fseek(repo_handle.issuesys_data_fp, 0, SEEK_SET);
    struct Issue temp_issue;
    size_t readsize;
    int y = 0;
    int count = 0;
    struct Student student;
jump:
    readsize = fread(&temp_issue, sizeof(struct Issue), 1, repo_handle.issuesys_data_fp);
    if (readsize != 1)
        y = 1;

    // 4.2 check if isbn is equal to the isbn_to_read
    if (temp_issue.isbn == rec->isbn && y != 1)
    {
        if (count == 0)
            printf("Book is Issued\n Issued by following students:\n");
        count++;

        get_student_by_rollno(temp_issue.rollno, &student);
        printf("Student %d:\nRollNo:%d\nName:%s\nAddress:%s\nCGPA:%.2f\n", count, student.rollno, student.name, student.address, student.cgpa);
    }
    // 4.3 if yes then read entire record of a book and return libsys_success
    // 4.4 else skip the record and read next isbn of the book
    else if (y == 0)
    {
        goto jump;
    }
    return BOOK_SUCCESS;
}
int get_student_by_name(char *name, struct Student *rec)
{
    int x = 0;
    int offset;

    for (int i = 0; i < repo_handle.stud_index_count; i++)
    {
        if (repo_handle.stud_index_entries[i].flag == RECORD_PRESENT && strcmp(repo_handle.stud_index_entries[i].second_key, name) == 0)
        {
            offset = repo_handle.stud_index_entries[i].offset;
            x = 1;
            break;
        }
    }
    if (x == 0)
        return LIB_REC_NOT_FOUND;

    fseek(repo_handle.studsys_data_fp, offset, SEEK_SET);
    int temp;
    size_t read_size = fread(&temp, sizeof(int), 1, repo_handle.studsys_data_fp);

    if (read_size != 1)
        return LIB_REC_NOT_FOUND;

    read_size = fread(rec, sizeof(struct Student), 1, repo_handle.studsys_data_fp);
    if (read_size != 1)
        return LIB_REC_NOT_FOUND;
    return BOOK_SUCCESS;
}
// 1. check if repo status is closed then  return appropriate error code referring to the error codes
// 2. else continue with following action sequence
// 3. close file pointer
// 4. set issuesys_name as ""
// 5. set issue_repo_status=LIB_REPO_CLOSED
// 6. return LIB_SUCCESS;