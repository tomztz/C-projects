//   list_string.c
//   David Gregg
//   January 2021

#include <stdio.h>

#include <assert.h>

#include <stdlib.h>

#include "list_string.h"


// create a new list string with the same value as a normal
// NULL-terminated C string
struct list_string * new_list_string(char * text) {
  struct list_string * my_string;				//create a new linked_string
  my_string = malloc(sizeof(struct list_string));		//allocate memory for the linked_string
  int str_length = 0;
  while (text[str_length] != 0) {				//get the number of characters of the input string
    str_length++;
  }

  for (int i = str_length - 1; i >= 0; i--) {		//this for loop creates a linkedlist same length of the string by
							//creating and inserting a new node before the head,update it's char c
							//correspondingly and then set the node to head.since we are inserting before
							//we need to set the first node to the last character of the string,the sencond to
							//the second last etc.
    struct ls_node * node;				//create a new node
    node = malloc(sizeof(struct ls_node));		//allocate memory
    node -> c = text[i];				//set the value of the node the corresponding value of the character of the input string

    node -> next = my_string -> head;			//node.next=head
    my_string -> head = node;				//head=node
  }

  return my_string;					//return my_string

}

// find the length of the list string
int list_string_length(struct list_string * this) {
  struct ls_node * p;					//create a temp pointer of type ls_node
  int count = 0;					//count=0
  for (p = this -> head; p != NULL; p = p -> next) {	//let p points to the head of the linedlist,as p is still pointing to a node in the linkedlist
							//then p points to the next node of the linkedlist

    count++;						//increment the counter by 1
  }

  return count;						//return count

}

// compare two strings; return -1 is s1 is lexicographically less that s2;
// return 0 if the strings are equal; return 1 if s1 is lexicographically
// larger than s2. E.g. "aB" is less than "ab" because 'B' has a smaller
// ASCII code than 'b'. Also "abc" is less that "abcd".
int list_string_compare(struct list_string * s1, struct list_string * s2) {
  struct ls_node * p1;                 //two temp pointers p1 and p2
  struct ls_node * p2;

  p1 = s1 -> head;			//p1 points to the head of s1
  p2 = s2 -> head;			//p2 points to the head of s2

  while (p1 != NULL) {			//while p1 is not pointing to null
    if ((p1 -> c) > (p2 -> c)) {	//if the ascii value of the char in the current node of s1 is greater than s2
      return 1;				//return 1 immediately(no need for more comparison)

    } else if ((p1 -> c) < (p2 -> c)) {	//if the ascii value of the char in the current node of s1 is less than s2

      return -1;			//return -1
    }

    if (p2 == NULL) {			//if p2 is pointing to NULL. hense s2 has less elements than s1, since we are inside the loop,
					//and also the elements before are equal otherwise it would have returned before
      return 1;				//we return 1 as s1>s2
    }
    p1 = p1 -> next;			//increment the pointer,point to the next node of s1
    p2 = p2 -> next;			//increment the pointer,point to the next node of s2

  }
  if (p2 != NULL) {			//if we exit the loop,by the condition of the while loop,p1 don't point to a node in s1
					//but if p2 is not null hense pointing to some node in s2, than that means s2 has more elements than s1 
    return -1;				//return -1
  } else {				//if they have the same length then there are equal
    return 0;				//return 0
  }
}

// return 1 if str is a substring of text; 0 otherwise
int list_string_substring(struct list_string * text, struct list_string * str) {
  struct ls_node * p1;                                       	//temp nodes p1,p2
  struct ls_node * p2;
  p2 = str -> head;						//p2 points to the head of substring
  int length_str = list_string_length(str);  			//get the length of the substring
  int same_chars = 0;						//number of same characters
  for (p1 = text -> head; p1 != NULL; p1 = p1 -> next) {	//iterate through the linkedlist string text as explained in previous function
    if ((p1 -> c) == (p2 -> c)) {				//if the character in the currrnt node of text is equal to the current node of str
      same_chars++;						//then we increament the number of the same characters
      if (same_chars == length_str) {				//if the number of same characters are equal to the length of the subtring
        return 1;						//then it means str is a substring of text
      }

      p2 = p2 -> next;						//increment the pointer
    } else {							//if the current character in the node text is not equal to str
								//we have to reset the same characters to 0,and the pointer pointing back																
      same_chars = 0;						//to the head of the substring,to make sure for example abc is a substring of
								//aabbcc happens

      p2 = str -> head;
    }

  }
  return 0;							//else not a substring
}
