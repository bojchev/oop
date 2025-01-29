#include <iostream>
#include <math.h>

using namespace std;

class Complex
{

        float r;
        float im;
        
    public:
        

        Complex(float re=0.0, float i=0.0)
        {
            r=re;
            im=i;
        }


        Complex(const Complex& c)
        {
            r=c.r;
            im=c.im;
        }

        void print()
        {
            cout<<r;
            cout<<((im > 0) ? "+i" : "-i")<<abs(im);
        }
      
    
        Complex operator*(Complex c) 
        {
            Complex num;
            num.r = (r * c.r - im * c.im);
            num.im = (r * c.im + im * c.r);
            return num; 
        }
        Complex operator+(Complex c)
        {
            Complex num=*this;
            num.r+=c.r;
            num.im+=c.im;
            return num;
        }
        
        Complex operator~()
        {
            return Complex(r, -im);
        }
        Complex operator-()
        {
            return Complex(-r, -im);
        }
        Complex operator/(Complex c)
        {
            Complex num=*this;
            num.r/=c.r;
            num.im/=c.im;
            return num;
        }
        bool operator==(Complex c)
        {
            if(r==c.r && im==c.im)return 1;
            else return 0;
        }
        Complex operator=(Complex c)
        {
            r=c.r;
            im=c.im;
            return *this;
        }
        bool operator!=(Complex c)
        {
            if(r==c.r && im==c.im)return 0;
            else return 1;
        }
        float operator!()
        {
            return sqrt(r*r+im*im);
        }
        Complex operator-(Complex c)
        {
            Complex num=*this;
            num.r-=c.r;
            num.im-=c.im;
            return num;
        }
        
        
        Complex operator++(int)
        {
            Complex num = *this;
            im++;
            return num;
        }
        Complex operator--()
        {
            im--;
            return *this;   
        }
        Complex operator++()
        {
            Complex num = *this;
            r++;
            return num;
        }
};


int main()
{

    return 0;
}
