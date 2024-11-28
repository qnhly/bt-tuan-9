#include <iostream>
using namespace std;

//dinh nghia mot cau tru dslk luu tru file trong 1 thu muc D>Document
//tren pc. cac file dc sx theo trat tu thoi gian.

//tren lop:
//Thiết kế giải thuật để sắp xếp các file trong thư mục lưu trữ theo thức tự tăng dần về dung lượng .

//1. khai bao cau truc dslk
struct FileNode{
    int size;               //kich thuoc file
    string addr;            //dia chi file
    string name;            //ten file
    int timestamp;          //thoi gian tao file
    FileNode *link;         //con tro den file ke tiep
};
struct FileList{
    FileNode *head, *tail;
};
//khoi tao dsach file
void initFileList(FileList *list){
    list->head=nullptr;
    list->tail=nullptr;
}

FileNode* insertionSort(FileNode *head){
    if(!head||!head->link)  return head;    //ktra dsach trong hoac co 1ptu
    FileNode *sorted=nullptr;
    FileNode *current=head;
    while (current)
    {
        FileNode *nextnode=current->link;
        if(sorted||current->size < sorted->size){      //chèn node vào sorted (t/h chen vao dau)
            current->link=sorted;                      //noi current voi ptu da sx
            sorted=current;                            //set lai con tro sorted(luon o vtri dau)       vd 123465
        }else{                  //truong hop tren vao giua hoac cuoi
            FileNode *temp = sorted;
            while (temp->link && temp->link->size < current->size){
                temp=temp->link;
            }
            current->link=temp->link;
            temp->link=current;     //chen current ngay sau temp
        }
        current=nextnode;
        return sorted;
    }
    
}
//2. copy paste file tu muc nay sang thu muc tren scho sx theo time

//khoi tao file can chuyen
FileNode* callFile(int size, string addr, string name, int timestamp){
    FileNode *p= new FileNode;
    p->size=size;
    p->addr=addr;
    p->name=name;
    p->timestamp=timestamp;
    p->link=NULL;
    return p;
}
//chuyen file vao thu muc
void addFile(FileList *l, FileNode *T){
    FileNode *p=l->head;
    if(l->head==0||T->timestamp<p->timestamp){
        T->link=l->head;
        l->head=T;
    }else{
        while(p){
            if(T->timestamp>=p->timestamp){
                T->link=p->link;
                p->link=T;
            }
            p=p->link;
        }
    }
    
}
//3. tinh toan kich thuoc cac file trong thu muc
int totalSize(FileList *l){
    FileNode *p= l->head;
    if(!p)  return;
    int sum=0;
    while(p){
        sum+=p->size;
        p=p->link;
    }
    return sum;
}

//4. sao luu vao o USB 32G. Xoa bo dan file co kich thuo nho nhat
void deleteFile(FileList *l,long sizeMax=32*1024*1024*1024){
    while(totalSize(l)>sizeMax){
        FileNode *FileMin=l->head;
        FileNode *p=l->head;
        if(!p)  return;
        FileNode *prevmin=nullptr;      //node truoc node co kich thuoc nho nhat
        FileNode *prevp=nullptr;
        //tim size nho nhat
        while(p->link){
            if(p->size<FileMin->size){
                FileMin=p;
                prevmin=prevp;      
            }
            prevp=p;
            p=p->link;
        }
        //xoa file co size nho nhat
        if(prevmin->link){
            prevmin->link=FileMin->link;        //moc noi lai dsach trc khi xoa
        }else{              //neu node min o ngay dau dsach
            l->head=l->head->link;      //cap nhat lai head
        }
        delete FileMin;
    }
}
