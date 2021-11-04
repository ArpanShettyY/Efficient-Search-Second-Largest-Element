#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"assignment_2.h"

struct ele                              //data structure used for storing the elements and the match results
{
    int data;                           //element's value
    struct ele *next;                   //points to the next element
};

static void free_ele(struct ele* t)     //it just frees all the memory in the linked list
{                                       //starting with t and till the end
    struct ele *temp;                   //this ensures all unrequired elements are discarde and helps to reduce space complexity
    while(t!=NULL)
    {
        temp=t;
        t=t->next;
        free(temp);
    }
}


static void print_result(struct ele* t) //prints the element's value and the value of 
{                                       //all the elements it has won against in the required format
    while(t!=NULL)
    {
        printf("%d ",t->data);
        t=t->next;
    }
}

static struct ele* create_ele(int a)    //makes a new node for the element
{                                       //so that it can play matches and can be added to the tournament table
    struct ele *new=(struct ele *)malloc(sizeof(struct ele));
    new->data=a;
    new->next=NULL;
    return new;
}


static struct ele * find_result(struct ele* a, struct ele* b)  //Makes elements play matches and gives result back
{                                                              //takes the highest(winners) of both input lists and compares them(play match)
    if(a->data > b->data)                                      //the losing list's winner is appended to the winner's list
    {                                                          //and the winning list is returned
        free_ele(b->next);                                     
        b->next=a->next;
        a->next=b;
        return a;
    }
    else
    {
        free_ele(a->next);
        a->next=b->next;
        b->next=a;
        return b;
    }
}

void find_second_greatest(int *numbers, int length)             //uses other helper functions to demonstrate the matches
{                                                               //and find the second largest element
    int s=1+ceil(log2(length));                                 //computing tournament table size
    struct ele *blk[s];                                         //the tournament table, at each block of the table match will be played with winners from previous block. Every element starts at 0th block and has to make its way to top block to indicate its the highest
    for(int i=0;i<s;i++)                                        //initially no matches are playes so all null
    {
        blk[i]=NULL;
    }
    for(int i=0;i<length;i++)                                   //the for loop adds one element at a time into the tournament
    {                                                           //j holds the current block in which the element is in
        int key=1,j=0;                                          //key indicates when to come out of the while loop. The key is unset when the element has no one to play against at that level
        struct ele *new=create_ele(numbers[i]);                 // a node is created for the element
        while(key)                                              //the while loop makes the element to play matches and
        {                                                       //progress to further blocks on winning until no more contestants at the same level are left
            if(blk[j]==NULL)                                    //if no element to play against it will wait in that block
            {
                blk[j]=new;
                key=0;
            }
            else                                                //contestant found so a match will be played
            {
                print_result(blk[j]);                           //the match being played and its results are printed
                printf("X ");
                print_result(new);
                printf("= ");
                new=find_result(blk[j],new);
                blk[j]=NULL;                                     //removed from previous block once match is over
                j++;                                             // and advances to the next block
                print_result(new);
                printf("\n");
            }
        }
    }
    if(blk[s-1]==NULL)                                           //Once all the matches at same level are played but yet the winner is not decided then(no. of elements not power of 2 case)
    {
        int x=0;
        struct ele *push=blk[x];                                 //push finds the element at lowest block which has won but can't play matches at same level due to lack of contestants
        while(push==NULL)
        {
            push=blk[++x];
        }
        blk[x]= NULL;
        int n=x+1;
        while(n!=s-1)                                            //that element is pushed to higher blocks(wins by default)
        {
            if(blk[n]==NULL)                                     //if no contestant at the higher block ,then win by default again and go to next higher block                                     
            {
                n++;
            }
            else                                                 //if not play a match against the contestant and let the winner progress to the next higher block
            {
                print_result(blk[n]);
                printf("X ");
                print_result(push);
                printf("= ");
                push=find_result(blk[n],push);
                blk[n]=NULL;
                n++;
                print_result(push);
                printf("\n");
            }
        }
    blk[s-1]=push;                                                //finally after all possible matches ,the winner is found
    }                                                             //and placed in the highest block
    
    struct ele *p=blk[s-1]->next;                                 //The nodes after the winner ,are the set of all nodes which have  
    int sec=p->data;                                              //directly lost against the winner
    p=p->next;                                                    //so the second highest(winner) has to be among these
    while(p!=NULL)
    {
        if(p->data>sec)                                           //finding the highest in this list in (n-1) time complexity
            sec=p->data;
        p=p->next;
    }

    printf("\n%d\n",sec);                                           //finally the second highest is found and printed
}
