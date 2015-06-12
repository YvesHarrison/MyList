#include<iostream>
using namespace std;

template<class T> class MyList; 
template<class T> ostream & operator<<(ostream &, const MyList<T> &); 

template<class T>
class MyList{

	friend ostream &operator<< <T>(ostream &os, const MyList<T> &obj);//���T�ǿ���ֱ��cout����Ļ�������int������Python����ĸ�ʽ���MyList�е�ÿһ��Ԫ�أ����磺
    // [1, 2, 5, 4, 1]
private:
	T *a;
	int size;
	int length;
	void double_space();//�����С������ʱ�������С�����Ĳ�����
public:
	MyList(){
		size = 100;
		length=0;
		a = new T [size];
	}
	MyList(int num, const T &item);//��item�ظ�num�����������С�
	MyList(const MyList &l);//�������һ��MyList��
    MyList(T* arr, int len);//��arr��ǰlen��Ԫ�ع�������

	void push(const T &item);//��item�����MyList���
	T pop();//��MyList�����һ��Ԫ��ɾ�������������ɾ����Ԫ�ء�
	void insert(int index, const T &item);//��item���뵽place����
	void clean();//������顣
	int get_size();//����MyList��Ԫ�ص�������
	void erase(int start, int end); //ɾ��MyList�е�start����endλ��Ԫ�أ��������ߡ�
	T get_item(int index);//���ص�index��Ԫ�ء�
	MyList get_item(int start, int end);//����MyList�е�start����endλ��Ԫ�أ��������ߡ��˴���Ҫ��pythonһ�����ܸ�������������Դ��롣
	int count(const T &item);//����MyList�к�item��ȵ�Ԫ�صĸ�����
	void remove(const T &item);//ɾ��MyList�е�һ����item��ȵ�Ԫ�ء�


	friend MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2) //�ϲ�����MyList
	{
		T *a;
		T len=l1.length+l2.length;
		a=new int[len];
		for(int i=0;i<l1.length;++i) a[i]=l1.a[i];
		for(int i=0;i<l2.length;++i) a[i+l1.length]=l2.a[i];
		MyList<T> MyList(a,len);
		delete [] a;
		return MyList;
	}    
	friend MyList<T> operator + (const MyList<T> &l1, const T &item) //ͬpush(T item)�������޸�l1������һ��������
	{
		MyList<T> l2(l1);
		l2.push(item);
		return l2;
	}
	MyList &operator = (const MyList &l);//��ֵ
	MyList &operator += (const T &item);//ͬpush(T item)
	MyList &operator += (const MyList &l);//��һ��MyList���뵽����MyList֮��
	T &operator [](int index);//���ص�index��Ԫ�ء�
	
	int divide1(int low,int high){
		T k=a[low];
	
		do {while(low<high&&a[high]<=k)--high;
			if(low<high){
				a[low]=a[high];++low;
		}
			while(low<high&&a[low]>=k)++low;
			if(low<high){
				a[high]=a[low];--high;
		}
		}while(low!=high);
		a[low]=k;
		return low;
		}
	int divide2(int low,int high){
		T k=a[low];
	
		do {while(low<high&&a[high]>=k)--high;
			if(low<high){
				a[low]=a[high];++low;
		}
			while(low<high&&a[low]<=k)++low;
			if(low<high){
				a[high]=a[low];--high;
		}
		}while(low!=high);
		a[low]=k;
		return low;
		}
	void quicksort1(int low,int high){
		int mid ;
		if(low>high) return;
		mid=divide1(low,high);
		quicksort1(low,mid-1);
		quicksort1(mid+1,high);
	} 
	void quicksort2(int low,int high){
		int mid ;
		if(low>high) return;
		mid=divide2(low,high);
		quicksort2(low,mid-1);
		quicksort2(mid+1,high);
	} 
	void sort(bool less=true);//ʵ��һ�����������鲢���򣬶�֧�ֱȽ��������>=<�������������
    // ��less=true�����մ�С�������У����򰴴Ӵ�С����
	void reverse();//��MyList��Ԫ�ص�������

	~MyList(){delete [] a; size=length=0;}
};

template<class T>
MyList<T>::MyList(int num,const T&item){
	size=num;
	length=num;
	a=new T[size];
	for(int i=0;i<length;++i) {
		a[i]=item;
	}
}

template<class T>
MyList<T>::MyList(const MyList &l){
	size=l.size;
	length=l.length;
	a=new T[size];
	for(int i=0;i<length;++i){
		a[i]=l.a[i];
	}
} 

template<class T>
MyList<T>:: MyList(T* arr, int len){
	length=len;
	size=len;
	a=new T[size];
	for(int i=0;i<len;++i) {
		a[i]=arr[i];
	}
} 

template<class T>
void MyList<T>::double_space(){
	T *b=a;
	size=2*size;
	a=new T[size];
	for (int i=0;i<length;++i){
		a[i]=b[i];
	}

	delete [] b;
}

template<class T>
void MyList<T>::push(const T &item){
	if(size==length){
		double_space();
	}
	else if(size==0){
		size=0;
		length=0;
		a=new T[size];
	}
	a[length]=item;
	length++;
	
} 

template<class T>
T MyList<T>::pop(){
	try{
		if(length==0) throw -1;
		else return a[--length];
	}
	catch (int){
		cout<<"The list is empty"<<endl;
	}
} 

template<class T>
void MyList<T>::insert(int index, const T &item){
	if(index<0) index=index+length;
	try{
		if(index>=length||index<0) throw -1;
		else{
			if(size==length){
			double_space();
		}
			for(int i=length;i>index;--i){
			a[i]=a[i-1];
		}
			a[index]=item;
			++length;
		}
	}
	catch(int){
		cout<<"Index out of range"<<endl;
	}
}

template<class T>
void MyList<T>::clean(){
	length=0;
	size=0;
	delete [] a;
	a=NULL;
}

template<class T>
int MyList<T>::get_size(){
	return length;
}

template<class T>
void MyList<T>::erase(int start, int end){
	if(start<0){
		start=start+length;
	}
	if(end<0){
		end=end+length;
	}
	try{
		if(start<length&&end<length&&start<=end){
			length=length-end+start-1;
			for(int i=start;i<length;++i){
				a[i]=a[i+end-start+1];
		}
	}
		else throw -1;	
	}
	catch(int){
		cout<<"Index is illegal"<<endl;
	}
}

template<class T>
T MyList<T>::get_item(int index){
	if(index<0){
		index=index+length;
	}
	try{
		if(index>=0&index<length){
			T b;
			b=a[index];
			return b;
	}
		else throw -1;
	}
	catch(int){
		cout<<"Index is illegal"<<endl;
	}
	
}

template<class T>
MyList<T> MyList<T>::get_item(int start, int end){
	MyList<T> tmp;
	if(start<0){
		start=length+start;
	}
	if(end<0){
		end=length+end;
	}
	try{
		if(start<0||end<0||start>length-1||end>length-1) throw -1;
		else{
			if(start>end)return tmp;
			else{
				tmp.size=tmp.length=end-start+1;
				tmp.a=new T[tmp.size];
				for(int i=start;i<=end;++i){
					tmp.a[i-start]=a[i];
				}
			return tmp;
		}
	}
	}
	catch(int){
		cout<<"Index is illegal"<<endl;
	}
} 
 
template<class T>
int MyList<T>::count(const T &item){
	int w=0;
	for(int i=0;i<length;++i){
		if(a[i]==item){
			w++;
		}
	}
	return w;
}

template<class T>
void MyList<T>::remove(const T &item){
	int w=0;
	for(int i=0;i<length;++i){
		if(a[i]==item){
			w=i;break;
		}
	}
	for(int i=w;i<length;++i){
		a[i]=a[i+1];
	}
	length--;
}

template<class T>
MyList<T> &MyList<T>:: operator = (const MyList<T> &l){
	if(this==&l)return *this;
	
	delete [] a;
	size=l.size;
	length=l.length;
	a=new T[l.size];
	for(int i=0;i<l.length;++i){
		a[i]=l.a[i];
	}
	return *this;
}

template<class T>
MyList<T> &MyList<T>:: operator += (const T &item){
	push(item);
	return *this;
}

template<class T>
MyList<T> &MyList<T>:: operator += (const MyList &l){
	while(length+l.length>size) double_space();
	
	for(int i=length;i<length+l.length;++i){
		a[i]=l.a[i-length];
	}
	length+=l.length;
	return *this;
}

template<class T>
T &MyList<T>:: operator [](int index){
	if(index<0){
		index=index+length;
	}
	try{
		if (index>length-1||index<0) throw -1;
		else{
		return a[index];
	}
	}
	catch(int){
		cout<<"Index is illegal"<<endl;
	}
	
}

template<class T>
ostream & operator<<(ostream &os, const MyList<T>&obj){
	os<<'[';
	if(obj.length){
		for(int i=0;i<obj.length-1;++i){
			cout<<obj.a[i]<<',';
		}
		cout<<obj.a[obj.length-1];
	}	
	os<<']';
	return os;
}

template<class T>
void MyList<T>::sort(bool less){
	if(less){
		quicksort2(0,length-1);
	}
	if(!less){
		quicksort1(0,length-1);
	}
}

template<class T>
void MyList<T>::reverse(){
	T tmp;
	for(int i=0;i<length/2;++i) {
		tmp=a[i];
		a[i]=a[length-1-i];
		a[length-1-i]=tmp;
	}
}

int main(){ 
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *��start > end�����ؿ�����
	b = a.get_item(3, -1); // b = [1, 0, 12]
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 1, 0, 12]
	b = a + a; // b = [15, 4, 1, 0, 12, 15, 4, 1, 0, 12]
	b.insert(3, 116); // b = [15, 4, 1, 116, 0, 12, 15, 4, 1, 0, 12]
	
	b.remove(4); // b = [15, 1, 116, 0, 12, 15, 4, 1, 0, 12]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;

}
