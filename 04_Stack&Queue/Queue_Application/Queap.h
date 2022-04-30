int& GET_MAX(int &e1, int &e2){ return e1 > e2 ? e1 : e2;}

//Stack类，不使用继承vector的方法，只赋予最基础的push，pop，top操作
class Stack
{
private:
    int *_elem;
    int _top;

public:
    Stack(int s, int head = 0){ //head 是哨兵元素
        _elem = new int[s + 1]; // 多出一个位置留个哨兵
        _elem[0] = head;
        _top = 0;
    }
    ~Stack(){
        if (_elem)
            delete[] _elem;
    }
    int size(){return _top;}
    bool Empty(){return !_top;}
    void push(int x){_elem[++_top] = x;}
    int pop(){return _elem[Empty() ? _top : _top--];} // _top若为0，则返回哨兵元素
    int &get_top(){return _elem[_top];} //查询栈顶元素
};


// Steap类，根据题目要求，只需实现取最大值getMax操作即可，通过两个Stack来实现目标
class Steap
{
private:
    Stack data, max;
public:
    // 根据题目要求，感染人数都是正整数，因此对于哨兵均使用default值为0即可，不会影响max的后续操作
    Steap(int s ) : data(s), max(s) {}
    ~Steap() {} //析构时会调用data和max的析构函数
    bool Empty(){return data.Empty();}
    int size(){
        return data.size();
    }
    void push(int x){
        data.push(x);
        max.push(GET_MAX(x, max.get_top())); //max进入的是栈顶和当前元素中的较大值
    }
    int pop(){ //两个栈都要pop，返回data栈顶元素
        max.pop();
        return data.pop();
    }
    int &get_Max(){
        return max.get_top(); //增加getMax操作
    }

};


//双栈当队，双Steap也能拼成一个Queap
class Queap
{
private:
    Steap in;
    Steap out;

public:
    Queap(int n) : in(n), out(n) {}
    ~Queap() {}
    void enqueue(const int &e){ in.push(e);} //入队操作
    int getsize(){return in.size() + out.size();}
    int dequeue(){ //出队操作
        if (out.Empty()){ 
            while (!in.Empty()){
                out.push(in.pop());
            }
        }
        return out.pop();
    }
    //两半最大值中的最大值就是整个队列的最大值
    int &pop_Max()
    {
        return GET_MAX(in.get_Max(), out.get_Max());
    }
};