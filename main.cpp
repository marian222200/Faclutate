#include<fstream>
#include<iostream>
#include<cstdlib>
#define N 10000
#define P 10000
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");

struct nod
{
    int nr;
    nod *urm;
};
nod *l1[P];
nod *l2[P];

void citire(int v[],int &n);

void copiere(int *b,int *a,int lga);

int verif_sort(int v[],int n);

void bubble_sort(int v[],int n);

int pivotare(int s,int d);
void qs(int s,int d,int v[]);
void quick_sort(int v[],int n);

void interclasare(int *a,int *b,int *c,int lga,int lgb);
void merge_sort(int v[],int n);

void count_sort(int v[],int n);

void radix_sort(int v[],int n,int b);
void rs(int nrpasi,int b);
int maxim(int v[],int n);

void afisare_vector(int v[],int n);

int main(){
    int v[N];
    int cv[N];
    int n;

    citire(cv,n);
    copiere(v,cv,n);

    bubble_sort(v,n);
    fout<<verif_sort(v,n)<<"\n";
    copiere(v,cv,n);

    count_sort(v,n);
    fout<<verif_sort(v,n)<<"\n";
    copiere(v,cv,n);

    radix_sort(v,n,10);
    afisare_vector(v,n);
    fout<<verif_sort(v,n)<<"\n";
    copiere(v,cv,n);

    merge_sort(v,n);
    fout<<verif_sort(v,n)<<"\n";
    copiere(v,cv,n);

    quick_sort(v,n);
    fout<<verif_sort(v,n)<<"\n";

    return 0;
}
void afisare_vector(int v[],int n){
    int i;
    for(i=0;i<n;i++)fout<<v[i]<<" ";
    fout<<"\n";
}
void citire(int v[],int &n){
    int i;
    fin>>n;
    for(i=0;i<n;i++)fin>>v[i];
}
void radix_sort(int v[],int n,int b){
    int nrpasi=0,maxi=maxim(v,n),i,r,j=-1;
    nod *p;
    while(maxi!=0){
        maxi/=b;
        nrpasi++;
    }
    for(i=0;i<n;i++){
        p=new nod;
        p->nr=v[i];
        r=(p->nr)%b;
        p->urm=l1[r];
        l1[r]=p;
    }
    rs(nrpasi,b);
    if(nrpasi%2==0){
        for(i=0;i<b;i++){
            p=l2[i];
            while(p!=NULL){
                v[++j]=p->nr;
                p=p->urm;
            }
        }
    }
    else{
        for(i=0;i<b;i++){
            p=l1[i];
            while(p!=NULL){
                v[++j]=p->nr;
                p=p->urm;
            }
        }
    }
    fout<<j<<"\n";
}
int maxim(int v[],int n){
    int i,maxi=v[0];
    for(i=1;i<n;i++)
        if(v[i]>maxi)maxi=v[i];
    return maxi;
}
void rs(int nrpasi,int b){
    int i,pas=1,r,fac=b;
    nod *p,*q;
    while(pas<nrpasi){
        fac*=b;
        if(pas%2==1){
            for(i=0;i<b;i++){
                p=l1[i];
                while(p!=NULL){
                    q=new nod;
                    q->nr=p->nr;
                    r=(p->nr)%fac;
                    q->urm=l2[r];
                    l2[r]=q;
                    q=p;
                    p=p->urm;
                }
            }
            for(i=0;i<b;i++)l1[i]=0;
        }
        else{
            for(i=0;i<b;i++){
                p=l2[i];
                while(p!=NULL){
                    q=new nod;
                    q->nr=p->nr;
                    r=(p->nr)%fac;
                    q->urm=l1[r];
                    l1[r]=q;
                    q=p;
                    p=p->urm;
                }
            }
            for(i=0;i<b;i++)l2[i]=0;
        }
        pas++;
    }
}
void count_sort(int v[],int n){
    int f[N]={0},i,j,k=-1;
    for(i=0;i<n;i++)f[v[i]]++;
    for(i=0;i<N;i++)
        for(j=0;j<f[i];j++)v[++k]=i;
}
void quick_sort(int v[],int n){
    qs(0,n-1,v);
}
void copiere(int *b,int *a,int lga){
    int i;
    for(i=0;i<lga;i++)b[i]=a[i];
}
int verif_sort(int v[],int n){
    int i;
    for(i=0;i<n-1;i++)
        if(v[i]>v[i+1])return 0;
    return 1;
}
void bubble_sort(int v[],int n){
    int m=n,ok=0,aux,i;
    while(!ok){
        ok=1;
        for(i=0;i<m-1;i++)
            if(v[i]>v[i+1]){
                ok=0;
                aux=v[i];
                v[i]=v[i+1];
                v[i+1]=aux;
            }
        m--;
    }
}
int pivotare(int s,int d,int v[]){
    int i=s,j=d,pasi=0,pasj=1,aux;
    while(i<j){
        if(v[i]>v[j]){
            aux=v[i];
            v[i]=v[j];
            v[j]=aux;
            pasi=1-pasi;
            pasj=1-pasj;
        }
        i=i+pasi;
        j=j-pasj;
    }
    return i;
}
void qs(int s,int d,int v[]){
    if(s<d){
        int p=pivotare(s,d,v);
        qs(s,p-1,v);
        qs(p+1,d,v);
    }
}
int rest_imp_b_la_k(int nr,int b,int k){
    int fac=1;
    while(k>0){
        fac*=b;
        k--;
    }
    return nr%fac;
}
void interclasare(int *a,int *b,int *c,int lga,int lgb){
    int i=0,j=0,k=-1;
    while(i<lga&&j<lgb)
        if(a[i]<b[j])c[++k]=a[i++];
        else c[++k]=b[j++];
    while(i<lga)c[++k]=a[i++];
    while(j<lgb)c[++k]=b[j++];
}
void merge_sort(int v[],int n){
    if(n>1){
        int m,c[N];
        m=n/2;
        merge_sort(v,m);
        merge_sort(v+m,n-m);
        interclasare(v,v+m,c,m,n-m);
        copiere(v,c,n);
    }
}
