#include <iostream>
using namespace std;

//Một câu tiếng việt cấu thành từ nhiều từ khác nhau. 
//Mỗi từ được lưu thành một node trong một danh sách liên kết đơn  

//1.khai bao ctruc dslk
struct WordNode{
    string tu;
    WordNode *next;
};
struct WordList{
    WordNode *head,*tail;
};
//khoi tao dsach
void listinit(WordList *l){
    l->head=nullptr;
    l->tail=nullptr;
}

//2. xac dinh tu xuat hien nhieu nhat trong cau
string findword(WordList *l){
    WordNode *p=l->head;
    WordNode *most=l->head;
    int maxcount=0;

    while(p){
        int count =1;   //dem so lan xuat hien cua p->tu
        WordNode *q=p->next;
        while(q){
            if(p->tu==q->tu){
                count++;               
            }
            q=q->next;
        }
        //cap nhat neu tim thay tu có so lan xuat hien nhieu hon
        if(count > maxcount){
            maxcount=count;
            most=p;
        }

        p=p->next;
    }
    return most ? most->tu: " " ;
}

//3. neu xuat hien tu lay thuc hien loai 1 tu
void BoLay(WordList *l){
    WordNode *p=l->head;    // q la con tro dang sau p
    WordNode *q=nullptr;    //neu de q chay trc p, q chay -> p khong chay => de sau
    while(p->next){
        if(p->tu==q->tu){
            WordNode *del=p;
            q->next=p->next;
            p=q->next;    //sao cho p trc q
            delete del;
        }
        q=p;
        p=p->next;
    }
}

//4. dem so tu vung xuat hien trong cau
int countWord(WordList *l){
    int count = 0;
    WordNode *p=l->head;
    while(p->next){
        count++;
        p=p->next;
    }
    return count;
}