#include <iostream>

enum e_err{
    e_no_err = 0,
    e_no_on,
    e_no_off
};
class lamb1{
    public:
        e_err on_off(bool state)const {
            return e_no_err;
        }

    protected: 
        bool state = false;
        int ligth1 = 0;
};
class lamb2 : public lamb1{
    public:
        void changelight2(){
            ligth1 = 2;
        }
        bool getstate()const{
            std::cout<< "lamb2 ligth getstate:" << ligth1<< std::endl;
            return state;
        }
};
class lamb3 : public lamb2{
    public: 
        void changelight3(){
            ligth1 = 4;
        }
        void rgbb()const{
            std::cout<< "lamb3 ligth rgbb:" << ligth1<< std::endl;
        }
};

void func(const lamb1 &lamb){
    lamb.on_off(true);

}
int main(){
    lamb1 lm1;
    lamb2 lm2;
    lamb3 lm3;
    lm2.changelight2();
    lm3.changelight3();

    lm2.getstate();
    lm3.getstate();
    lm3.rgbb();
    func(lm3);
    return 0;
}