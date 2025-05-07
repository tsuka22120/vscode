#include<iostream>

class Neko{
    private:
    std::string name;
    public:
    Neko(std::string s){
        name = s;
    }
    void naku(){
        std::cout << name << "がにゃーと鳴きました" << std::endl;
    }
};

int main(){
    Neko neko1("たま");
    std::cout << "あなたが名付けた猫がメモリ上に生成されました" << std::endl;
    std::cout << "猫が鳴きます" << std::endl;
    neko1.naku();
}