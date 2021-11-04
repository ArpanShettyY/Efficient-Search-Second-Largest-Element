# Efficient-Search-Second-Largest-Element

Using Stepanov’s Binary counter to find the second largest element in an array of distinct/unique integers. 
Let n be the number of elements in the array (n>=2).  n may or may not be an exact power of 2.
The algorithm will have at most n + logn - 2 comparisons (however when n is not an exact power of 2, the number of comparisons can be little more).
It uses extra space proportional to (logn) ^ 2.

**To Compile Use:**
    gcc sanity_client.c A2_PES1UG19CS086.c -lm
This is because I have included math.h to use ceil and log2 funcations.

**Data Structure Used:**
        A varying column size table kind of structure is made using array of pointers.
        - Element Node:
            Each element is represented in the form of a structure "ele"(which is same as a singly linked list).
            It has 2 attributes:
            i)The Value: The number itself
            ii)Next pointer: If the current node is the head , then it points to a list which has elements against which this element has won or is greater than.
                             If the current node is not the head, then it just points to another node besides itself who has lost to the head of the list
        - Pointer Array: An array of pointer(pointing to the head of the list of above structure type) of approx (logn + 1) is used.
          They represent different level blocks of the tournament(block n tells the element its pointing to has won against n elements)
          So if an element wins in a block it can progress to the next block. If not it gets appended to next pointer list of the winner.
          So the final block will only have the winner(largest element) which has won all its matches .

    Now these two together forms a table where the column is the pointer array and the rows are the elements.
    Since an element can win against approx only logn other elements at max, we can be guarenteed that the list these pointer is pointing to will not exceed log(n)+1 nodes.
    Further there is a restriction that a block level can have only i nodes in it(where i is level of the block starting from 1)
    which on an average gives approx (logn + 1)/2 nodes per columns.
    so total number of nodes are approximately (log n + 1)*(log n + 1)/2.
    Therefore the space complexity is proportional to (log n)^2.

    Reasons for using this:    
        The reason for using a linked list implementation is to simplify the process of appending the loser element to the winner element list. This can be done in constant time.
        Further since this is dynamic , the unwanted nodes like the node which lost to the loser node can be immediately freed up.
        Also each block will never have more than i nodes, thus also implementing different no. of elemnets per column.
        So this implementation will take most minimal amount of space required at any point ,despite the existence of two seperate fields per element(which will just multiply and add a small constant factor). 


**Implementation:**

    Functions Used:
        static void free_ele(struct ele* t)
            takes the first pointer to the list and frees the space allocated to that list. Used to free space of all elements apart from the highest element and elements that lost to it.

        static void print_result(struct ele* t)
            prints the element and elements it has lost against in the required format.
        
        static struct ele* create_ele(int a)
            creates a node for the numbers in the input array
        
        static struct ele * find_result(struct ele* a, struct ele* b)
            compares two elements and appends the lesser element to the higher element's list of elements it has won aginst. then the higher element link is sent back
        
        void find_second_greatest(int *numbers, int length)
            This is the main function. Initially the pointer array is prepared.
            Then the elements are brought in one by one.
            Initially they go to the first block and if another element arrives at the first block, then they are compared and the lesser number is appended just after the higher number along with other numbers the higher element has won against. Then this list is moved to next block.
            This is repeated for all other blocks.

            At the end ,its checked if the no. of elements is a power of 2, if not then some elements get stuck at certain levels and can never progress.
            To overcome this the element of this kind in the lowest block is promoted to the next block and is compared with the element already there if present.
            This is done and the highest element of the whole is found.
            This totally took n-1 comparisons.
            Next to find second largest, the element list attached to the highest element is earched and th ehighest among them can be found in logn - 1 comparisons.
