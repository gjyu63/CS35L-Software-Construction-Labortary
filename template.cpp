#include <iostream>
#include <ctime>
template <typename T>
struct Node{
    T num;
    Node<T>* next;
    Node(const T&);
    Node();
};
template <typename T>
Node<T>::Node(const T& n): num(n),next(0){}
template <typename T>
Node<T>::Node():next(0){}
template <typename T>
class List{
public:
    
    List();
    ~List();
    List(const List&); // copy constructor
    List& operator=(const List&); // copy assignment
    void insert_at_front(const T&);
    void print() const;
    void insert(T x,Node<T>*p);
    Node<T>* front;
private:
    Node<T>* node;
};
template<typename T>
List<T>::List(): front(0),node(0) {}

template<typename T>
List<T>::~List()
{
    Node<T>* i = front;
    while (i!=0)
    {
        Node<T>* j = i->next; // save next before deleting
        delete i;
        i=j;
    }
}

template <typename T>
void List<T>::insert_at_front(const T& things)
{
    Node<T>* node_to_insert=new Node<T>(things);
    node_to_insert->next = front;
    front = node_to_insert;
}

template <typename T>
void List<T>::insert(T x,Node<T>*p)
{
    node=new Node<T>();
    node->num=x;
    node->next=p->next;
    p->next=node;
}



template<typename T>
void List<T>::print() const
{
    for (Node<T>* i = front; i!=0; i = i->next)
    {
        std::cout << i->num << std::endl;
    }
}

int main()
{
    int N[100];
    for(int m=0; m<100; m++)
        N[m]=rand()%101;
    List<int> int_list;
    for(int i=0; i<100; i++)
    {
        if(i==0)
            int_list.insert_at_front(N[i]);
        else
            for(Node<int>* n = int_list.front; n!=0; n = n->next)
            {
                if(n->num<=N[i] && n->next==0)
                    int_list.insert( N[i],n);
                else if(n->num<=N[i] && n->next->num >= N[i])
                    int_list.insert( N[i],n);
            }
    }
    
    
    int_list.print();
    
    /*List<int> int_list;
    List<char> char_list;
    int_list.insert_at_front(3);
    int_list.insert_at_front(23);
    char_list.insert_at_front('W');
    int_list.print();
    char_list.print();*/
    
    
    return 0;
}
