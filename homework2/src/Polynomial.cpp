#include<iostream>
#include<cmath>
using namespace std;

class Polynomial;

class Term{
    friend Polynomial;
    friend ostream& operator<<(ostream &output,const Polynomial &Poly);
    private:
    	int exp;
    	float coef;
};

class Polynomial{
private:
    Term *termArray;    // 陣列本體
    int capacity;       // 陣列大小
    int terms;          // 陣列內非零數字
public:
    Polynomial(): capacity(2), terms(0){
        termArray = new Term[capacity];
    }
    ~Polynomial(){ delete[] termArray; }

    Polynomial Add(Polynomial b);
    Polynomial Mult(Polynomial b);
    float Eval(float x);

    void newTerm(const float newcoef, const int newexp);

    friend istream& operator>>(istream &input, Polynomial &Poly);
    friend ostream& operator<<(ostream &output, const Polynomial &Poly);
};


istream& operator>>(istream& is, Polynomial& poly){
    float coef;
    int exp, n;
    is >> n;
    while (n--) {
        is >> coef >> exp;
        poly.newTerm(coef, exp);
    }
    return is;
}


ostream& operator<<(ostream& os, const Polynomial& poly){
    for(int i=0;i<poly.terms;++i)
    {
    	if(i>0)os<<"+";
        os << poly.termArray[i].coef;
        if(poly.termArray[i].exp!=0)
        cout<< "X^" << poly.termArray[i].exp;
    }
    return os;
}

void Polynomial::newTerm (const float theCoef, const int theExp) {
    if (theCoef == 0) return;
    if (terms == capacity) {
        capacity *= 2;
        Term *temp = new Term [capacity];
        copy (termArray, termArray + terms, temp);
        delete [] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoef;
    termArray [terms++].exp = theExp;
}


Polynomial Polynomial::Add(Polynomial b){
    Polynomial c;
    int aPos = 0, bPos = 0;
    while((aPos < terms) && (bPos < b.terms)){
        if(termArray[aPos].exp == b.termArray[bPos].exp){
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if(t) c.newTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if(termArray[aPos].exp < b.termArray[bPos].exp){
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else{
            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }

    for(;aPos < terms; aPos++)
        c.newTerm(termArray[aPos].coef, termArray[aPos].exp);

    for(;bPos < b.terms; bPos++)
        c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

    return c;
}
Polynomial Polynomial::Mult(Polynomial b)
{
    Polynomial c;
    for (int i = 0; i < terms; i++)
    {
        for (int j = 0; j < b.terms; j++)
        {
            float coef = termArray[i].coef * b.termArray[j].coef;
            int exp = termArray[i].exp + b.termArray[j].exp;
            bool found = false;
            for (int k = 0; k < c.terms; k++)
            {
                if (c.termArray[k].exp == exp)
                {
                    c.termArray[k].coef += coef;
                    found = true;
                    break;
                }
            }
            if(!found)
            c.newTerm(coef, exp);
        }
    }
    return c;
}
float Polynomial::Eval(float x)
{
    float n=0;
    for (int i = 0; i < terms; i++)
    {
        n += termArray[i].coef * pow(x, termArray[i].exp);
    }
    return n;
}
int main()
{
    //一次只能擇一模式選擇,不然會崩潰
	Polynomial a;
    Polynomial b;
    int mode,x;
    cin >> a >> b;
    cout << "選擇模式(1.Add,2.Muti):";
    cin >> mode;
    switch (mode)
    {
    case(1):
    {
        Polynomial c = a.Add(b);
        cout << c << endl;
        cout << "輸入X:";
        cin >> x;
        int sum = c.Eval(x);
        cout << sum << endl;
    }
    case(2):
    {
        Polynomial c = a.Mult(b);
        cout << c << endl;
        cin >> x;
        int sum = c.Eval(x);
        cout << sum << endl;
    }
    default:return 0;
    }
}
