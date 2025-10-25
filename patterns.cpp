#include <iostream>
#include <algorithm>
using namespace std;

void print_line(){ 
    cout << "--------------------" << endl;
}

void pattern1(int n){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            cout << " * ";
        }
        cout << endl;
    }
}
void pattern2(int n){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j <= i ; j++){
            cout << " * ";
        }
        cout << endl;
    }
}
void pattern3(int n){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j <= i ; j++){
            cout << " "<< j+1 << " ";
        }
        cout << endl;
    }
}
void pattern4(int n){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j <= i ; j++){
            cout << " "<< i+1 << " ";
        }
        cout << endl;
    }
}
void pattern5(int n){
    for(int i = 0 ; i < n ; i++){
        for(int j = n ; j > i ; j--){
            cout << " "<< "*" << " ";
        }
        cout << endl;
    }
}
void pattern6(int n){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0; j < n - i ; j++){
            cout << " " << j+1 << " ";
        }
        cout << endl;
    }
}
void pattern7(int n){
    for(int i = 0 ; i < n ; i++){
        for(int k = 0 ; k < n - i - 1; k++){
            cout << " ";
        }
        for(int j = 0; j < (2 * i) + 1 ; j++){
            cout << "*" ;
        }
        cout << endl;
    }
}
void pattern8(int n){
    for(int i = 0 ; i < n ; i++){
        for(int k = 0 ; k < i; k++){
            cout << " ";
        }
        for(int j = 0; j < (2 * n) - (2 * i + 1) ; j++){
            cout << "*";
        }
        cout << endl;
    }
}
void pattern9(int n){
    pattern7(n);
    pattern8(n);
}
void pattern10(int n){
    for(int i = 0; i < 2*n - 1; i++){
        int stars = 0;
        if(i < n){
            stars = i + 1;
        }else{
            stars = (2*n - 1) - i;
        }
        for(int j = 0; j < stars ; j++){
            cout << " * ";
        }
        cout << endl;
    }
}
void pattern11(int n){
    for(int i = 1; i <= n; i++){
        for(int j = 1 ; j <= i; j++){
            cout << " " << (i+j -1) %2<< " ";
        }
        cout << endl;
    }

    // for(int i = 0; i < n; i++){
    //     for(int j = 0 ; j <= i; j++){
    //         cout << " " << (i+j +1) %2<< " ";
    //     }
    //     cout << endl;
    // }
}
void pattern12(int n){
    for(int i = 0; i < n ; i++){
        for(int k = 0 ; k <=i ; k++){
            cout << k+1;
        }
        for(int j = 0 ; j < 2*n - 2*(i+1); j++){
            cout << " ";
        }
        for(int k = i ; k >=0 ; k--){
            cout << k+1;
        }
        cout << endl;
    }
}
void pattern13(int n){
    int count = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j <= i ; j++){
            cout << " " << count << " ";
            count++;
        }
        cout << endl;
    }
}
void pattern14(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j <= i ; j++){
            char c = 65;
            c += j;
            cout << " " << c  << " ";
        }
        cout<< endl; 
    }
}
void pattern15(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < n - i; j++){
            char c = 65;
            c += j;
            cout << " " << c  << " ";
        }
        cout<< endl; 
    }
}
void pattern16(int n){
    char c = 65;
    for(int i = 0; i < n; i++){
        
        for(int j = 0 ; j <= i ; j++){
            cout << " " << c << " ";
        }
        c++;
        cout<< endl; 
    }
}
void pattern17(int n){
    for(int i = 0 ; i < n ; i++){
        char ch = 'A';
        for(int k = 0 ; k < n - i -1 ; k++){
            cout << " ";
        }
        for(int j = 0 ; j < 2*i + 1 ; j++){
            if(j < i) cout << ch++;
            else cout << ch--;
        }
        for(int k = 0 ; k < n - i -1 ; k++){
            cout << " ";
        }
        cout << endl;
    }
}
void pattern18(int n){
    char ch = 'E';
    for(int i = 0; i < n ; i++){
        for(char j = ch - i; j <= ch ; j++ ){
            cout <<" " << j << " ";
        }
        cout << endl;
    }
}
void pattern19(int n){
    for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j < n - i; j++){
            cout << "*";
        }

        for(int k = 2*n; k > 2*n - 2*i; k--){
            cout << " ";
        }

        for(int j = 0 ; j < n - i ; j++){
            cout << "*";
        }
        cout << endl;
    }
    for(int i = 0; i < n ; i++){
        for(int j = n; j >= n - i ; j--){
            cout << "*";
        }

        for(int k = 0 ; k < 2*n - 2*(i+1) ; k++){
            cout << " ";
        }

        for(int j = n; j >= n - i ; j--){
            cout << "*";
        }
        cout << endl;
    }
}
void pattern20(int n){
    // stars= i,  1 to 5 , i.e while i < n
    //spaces
    //stars  1  
    //after if
    //stars = 2*n
    //
    int stars;
    int spaces;
    for(int i = 0; i < 2*n; i++){
        if(i < n){
            stars = i + 1;
            spaces = 2 * (n - i - 1);
        } else {
            stars = 2 * n - i;
            spaces = 2 * (i - n);
        }

        // Print left stars
        for(int j = 0; j < stars; j++){
            cout << "*";
        }

        // Print middle spaces
        for(int j = 0; j < spaces; j++){
            cout << " ";
        }

        // Print right stars
        for(int j = 0; j < stars; j++){
            cout << "*";
        }
        cout << endl;
    }
}
void pattern21(int n){
    for(int i = 0; i < n; i++){
        if(i == 0 || i == n -1){
            for(int j = 0; j < n; j++){
            cout << "*";
            }
        }else{
            cout << "*";
            for(int k = 0; k < n -2; k++){
                cout << " ";
            }
            cout << "*";
        }
        
        cout << endl;
    }
}
void pattern22(int n){

    // 1. Start the outer loop for the rows (i)
    //    It needs to run (2*n - 1) times.
    for(int i = 0; i < 2*n - 1; i++){

        // 2. Start the inner loop for the columns (j)
        //    It also needs to run (2*n - 1) times.
        for(int j = 0; j < 2*n - 1; j++){

            // 3. Find the 4 distances for the current cell (i, j)
            
            // Distance from top edge:
            int top = i;
            
            // Distance from left edge:
            int left = j;
            
            // Distance from bottom edge:
            // (The last index is (2*n - 2))
            int bottom = (2*n - 2) - i;
            
            // Distance from right edge:
            int right = (2*n - 2) - j;

            // 4. Find the smallest (the "minimum") of these 4 distances
            //    We can nest the `std::min` function.
            int min_dist = std::min( std::min(top, bottom) ,  std::min(left, right) );

            // 5. Print the final formula: n - (the smallest distance)
            cout << n - min_dist << " ";
        }

        // 6. After the inner loop finishes, go to the next line
        cout << endl;
    }
}

int main(){
    int n = 9;
    cin >> n;
    
    pattern1(n);
    print_line();
    pattern2(n);
    print_line();
    pattern3(n);
    print_line();
    pattern4(n);
    print_line();
    pattern5(n);
    print_line();
    pattern6(n);
    print_line();
    pattern7(n);
    print_line();
    pattern8(n);
    print_line();
    pattern9(n);
    print_line();
    pattern10(n);
    print_line();
    pattern11(n);
    print_line();
    pattern12(n);
    print_line();
    pattern13(n);
    print_line();
    pattern14(n);
    print_line();
    pattern15(n);
    print_line();
    pattern16(n);
    print_line();
    pattern17(n);
    print_line();
    pattern18(n);
    print_line();
    pattern19(n);
    print_line();
    pattern20(n);
    print_line();
    pattern21(n);
    print_line();
    pattern22(n);
    print_line();
    return 0;
}