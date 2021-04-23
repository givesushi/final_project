#include <memory>
#include <string>
#include <iostream>

using namespace std;

int main(){
	shared_ptr<string> ptr = make_shared<string>("Lucy");
	string* ptr2 = ptr;
	cout << *ptr2 << endl;
}
