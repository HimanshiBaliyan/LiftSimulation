#include<iostream>
#include<iomanip>
#include<windows.h>
using namespace std;

class node{
public:
    int FNo;
    node *pre;
    node *next;

    node(int n)
    {
        FNo = n;
        pre = NULL;
        next = NULL;
    }
};

node *TraverseHead = NULL, *TraverseTail = NULL;
node *RequestHead = NULL, *RequestTail = NULL;

node * toGetTail(node *head);
void outerCall();
void innerCall();

class LinkedList{
public:
    void Create(node *&head,node *&tail, int x){
        node *current = new node(x);

        if(head == NULL){
            head = current;
        }else{
            tail->next = current;
            current->pre = tail;
        }
        tail = current;
    }
    void TraverseUp(node *head){
        if(head != NULL){
            node *temp = head;
            while(temp != NULL){
                cout<<temp->FNo<<" ";
                temp = temp->next;
            }
        }
    }
    void TraverseUp(node *UpTraversalHead,node *RHead){
        int call;
        node *traversalTemp = UpTraversalHead;
        node *temp = RHead;
        if(traversalTemp != NULL){
            while(traversalTemp !=NULL){
                if(GetAsyncKeyState(VK_ESCAPE)){
                    system("cls");
                    cout<<"\nPress 1 for Outer Call Request";
                    cout<<"\nPress 0 for Inner Call Request"<<endl;
                    cin>>call;
                    if(call)
                        outerCall();
                    else
                        innerCall();
                }
                system("cls");
                cout<<"\n Please Press 'ESC' for intermediate Request Calls \n";
                cout<<"Lift is on the floor :"<<setfill(' ')<<setw(3)<<traversalTemp->FNo;

                if(traversalTemp->FNo > temp->FNo && temp->next != NULL)
                    temp = temp->next;

                if(traversalTemp->FNo == temp->FNo){
                    Beep(850, 1000);
                    Sleep(800);
                    Deletion(RequestHead,RequestTail,temp->FNo);
                    if(temp->next != NULL)
                        temp = temp->next;
                }
                Sleep(1000);
                traversalTemp = traversalTemp->next;
            }
        }

    }
    
    void TraverseDown(node *DownTraversalTail,node *RTail){
        int call;
        node *traversalTemp = DownTraversalTail;
        node *temp = RTail;
        if(traversalTemp != NULL){
            while(traversalTemp !=NULL){
                if(GetAsyncKeyState(VK_ESCAPE)){
                    system("cls");
                    cout<<"\nPress 1 for Outer Call Request";
                    cout<<"\nPress 0 for Inner Call Request"<<endl;
                    cin>>call;
                    if(call)
                        outerCall();
                    else
                        innerCall();
                }
                system("cls");
                cout<<"\n Please Press 'ESC' for intermediate Request Calls \n";
                cout<<"Lift is on the floor :"<<setfill(' ')<<setw(3)<<traversalTemp->FNo;

                if(traversalTemp->FNo < temp->FNo && temp->next != NULL)
                    temp = temp->pre;

                if(traversalTemp->FNo == temp->FNo){
                    Beep(850, 1000);
                    Sleep(800);
                    Deletion(RequestHead,RequestTail,temp->FNo);
                    if(temp->pre != NULL)
                        temp = temp->pre;
                }
                Sleep(1000);
                traversalTemp = traversalTemp->pre;
            }
        }

    }

    int Deletion(node *&head,node *&tail,int x){
        node *temp = head;
        int num;
        if(head == NULL)
            return -1;
        else if(head->FNo == x || tail->FNo == x){
            if(head->FNo == x && tail->FNo == x){
                num = temp->FNo;
                head = tail = NULL;
                return num;
            }
            if(head->FNo == x){
                head->next->pre = NULL;
                head = head->next;
                num = temp->FNo;
                delete temp;
                return num;
            }
            if(tail->FNo == x){
                temp = tail;
                tail->pre->next = NULL;
                tail = tail->pre;
                num = temp->FNo;
                // if(head->next != NULL){
                //     head = head->next;
                // }
                delete temp;
                return num;
            }
        }
        else{
            while(temp!=NULL && temp->FNo<=x){
                if(temp->FNo == x){
                    temp->pre->next = temp->next;
                    temp->next->pre = temp->pre; 
                    num = temp->FNo;
                    delete temp;
                    return num;
                }
                temp=temp->next;
            }
        }
        return -1;
    }
};

class Lift:public LinkedList{
    public:
 
    // Function to merge two linked lists 
    node *merge(node *&first, node *&second) 
    { 
        // If first linked list is empty 
        if (!first) 
            return second; 
    
        // If second linked list is empty 
        if (!second) 
            return first; 
    
        // Pick the smaller value 
        if (first->FNo < second->FNo) 
        { 
            first->next = merge(first->next,second); 
            first->next->pre = first; 
            first->pre = NULL; 
            return first; 
        } 
        else
        { 
            second->next = merge(first,second->next); 
            second->next->pre = second; 
            second->pre = NULL; 
            return second; 
        } 
    } 
  
    // Function to do merge sort 
    node *mergeSort(node *&head) 
    { 
        if (!head || !head->next) 
            return head; 
        node *second = split(head); 
    
        // Recur for left and right halves 
        head = mergeSort(head); 
        second = mergeSort(second); 
    
        // Merge the two sorted halves 
        return merge(head,second); 
    }
    node *split(node *&head) 
    { 
        node *fast = head,*slow = head; 
        while (fast->next && fast->next->next) 
        { 
            fast = fast->next->next; 
            slow = slow->next; 
        } 
        node *temp = slow->next; 
        slow->next = NULL; 
        return temp; 
    }


    void Request(){
        int FloorRequest;
        char Repeat,g;
        node *ListHead = NULL,*ListTail = NULL;

        for(int i=0; i<=14; i++)
            Create(ListHead,ListTail,i);

        do{
            g:
            system("cls");
            cout<<"\nList of Floors In The Building";
            cout<<"\n------------------------------"<<endl;
            TraverseUp(ListHead);
            cout<<endl<<endl<<"Enter The Desired Floor : ";
            cin>>FloorRequest;
            if(FloorRequest>=0 && FloorRequest<=14)
            {
                int x = Deletion(ListHead,ListTail,FloorRequest);
                if(x != -1){
                    cout<<"-->"<<x<<" added to request"<<endl;
                    Create(RequestHead,RequestTail,x);
                }
                else{
                    cout<<"--> Given Request Already entered"<<endl;
                }
            }
            else
            {
                goto g;
            }

            cout<<endl<<"Do You Want To Enter More Request?"<<"\nPress 'Y' Else 'Any Other Key To Continue'"<<endl;
            cin>>Repeat;
            Repeat = toupper(Repeat);
        }while(Repeat == 'Y');
        RequestHead = mergeSort(RequestHead);
        RequestTail = toGetTail(RequestHead);
    }
};

void outerCall(){

    int OuterCall,g;
    node *temp = RequestHead;
    Lift l;
    g:
    system("cls");
    cout<<"\n'Outer Call Request for the LIFT'";
    cout<<"\n Please Enter your Current Floor no. : ";
    cin>>OuterCall;

    if(!(OuterCall>=0 && OuterCall<=14))
        goto g;

    cout<<"-->"<<OuterCall<<" added to request"<<endl;

    //Loop used to avoid duplicacy of request due to outside and inside Request call
    while(temp!=NULL)
    {
        if(OuterCall == temp->FNo)
            return;
        temp = temp->next;
    }
    
    l.Create(RequestHead,RequestTail,OuterCall);
    RequestHead = l.mergeSort(RequestHead);
    RequestTail = toGetTail(RequestHead);
}

void innerCall(){
    Lift l;
    cout<<"\n'Inner Call Request for the LIFT'\n";
    l.Request();
}

node * toGetTail(node *head){
    node *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    return temp;
}

int main(){
    system("cls");

    LinkedList ll;
    Lift L1;

    for(int i=0; i<=14; i++)
        ll.Create(TraverseHead,TraverseTail,i);
    int w;
    do{
        L1.Request();
        system("cls");
        cout<<endl<<"\n --> Entered Request List : ";
        ll.TraverseUp(RequestHead);
        Sleep(1500);
        ll.TraverseUp(TraverseHead,RequestHead);
        
        L1.Request();
        system("cls");
        cout<<endl<<"\n --> Entered Request List : ";
        ll.TraverseUp(RequestHead);
        Sleep(1500);
        ll.TraverseDown(TraverseTail,RequestTail);

        system("cls");
        cout<<"\n Do you want to exit the application ? \n Please Press enter 0 to exit ";
        cin>>w;
    }while(w != 0);
    return 0;
}
