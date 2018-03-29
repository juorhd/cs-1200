#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
using namespace std;

//extra credit part

int read_words_triangle(ifstream& fin, vector<string> &words, 
                        vector<int> &word_count, vector<int> &space_count){
    string word, _index;
    int width = 2;
    while ( fin >> word ){
        while ( word.size() > width ){                //when reading the word
            _index = word.substr(0,width-1) + '-';    //if words too long 
                                                      //split it with '-'
            words.push_back(_index); 
            word.erase(0, width-1);
            width += 2;
        }
        words.push_back(word); 
        width += 2;
    }

    int num_row = 1;
    int word_count_current_line;
    int w_count;

    for ( int i = 0; i < words.size(); ){
        word_count_current_line = num_row*2;
        w_count = 1;
        
        word_count_current_line -= words[i++].size();

        // when distributing the word if the word is too long
        // we split it into two lines depend on the current line width
        if ( word_count_current_line < 0 ){
            string left, right;
            --i;
            left = words[i].substr(0,num_row*2-1) + '-';   
            right = words[i].substr(num_row*2-1);
            words.erase(words.begin()+i);
            words.insert(words.begin()+i, right);
            words.insert(words.begin()+i, left);
            word_count.push_back(1);
            space_count.push_back(0);
            num_row++;++i;
            word_count_current_line = num_row*2-words[i++].size();
        }
        
        //count the word every line
        while ( word_count_current_line >= words[i].size()+1 && i < words.size() ){
            word_count_current_line -= words[i].size()+1;
            ++w_count;
            ++i; 
        }
        // store every line's word and space num
        word_count.push_back(w_count);
        space_count.push_back(word_count_current_line);
        
        num_row++;
    }
    //return the num of rows a triangle should have
    return num_row;
}

void flush_left_triangle( ofstream& fout, int num_row, vector<string> &words, 
                            vector<int> &word_count, vector<int> &space_count ){

    int word_index = 0;
    string line;
    fout << string(num_row,' ') + "/\\" << endl;

    for ( int i = 0; i < num_row-1; ++i ){
        line = words[word_index++];
        for ( int j = 1; j < word_count[i]; ++j ){
            line += ' '+words[word_index++];
        }
        //put all the space at the left hand side
        fout << string( num_row - i - 1, ' ' ) << "/" 
             << line << string( space_count[i], ' ' ) << "\\" << endl;
    }
    fout << '/' << string(num_row*2,'_') <<'\\'<<endl;
}

void flush_right_triangle( ofstream& fout, int num_row, vector<string> &words, 
                            vector<int> &word_count, vector<int> &space_count ){

    int word_index = 0;
    string line;
    fout << string(num_row,' ') + "/\\" << endl;

    for ( int i = 0; i < num_row-1; ++i ){
        line = words[word_index++];
        for ( int j = 1; j < word_count[i]; ++j ){
            line += ' '+words[word_index++];
        }
        //put all the space at the right hand side
        fout << string( num_row - i - 1, ' ' ) 
             << "/" << string( space_count[i], ' ' ) << line << "\\" << endl;
    }
    fout << '/' << string(num_row*2,'_') <<'\\'<<endl;
}

void full_justify_triangle( ofstream& fout, int num_row, vector<string> &words, 
                            vector<int> &word_count, vector<int> &space_count ){

    int word_index = 0;
    string line;
    fout << string(num_row,' ') + "/\\" << endl;

    for ( int i = 0; i < num_row-1; ++i ){
        line = words[word_index++];
        
        int space_between[word_count[i]+1];
        memset(space_between, 0, sizeof(space_between));
        int index = 1;

        if (word_count[i]>1){                // if this line has more than one word
            while ( space_count[i] > 0 ){    // if there is still more space left
                space_between[index]++;
                index++;
                if ( index == word_count[i] ){ index = 1; }
                space_count[i]--;
            }
            for ( int j = 1; j < word_count[i]; ++j ){
                line += string( space_between[j]+1, ' ') + words[word_index++];
            }
        }
        
        fout << string( num_row - i - 1, ' ' ) << "/" 
             << line << string(space_count[i], ' ')<< "\\" << endl;
    }
    fout << '/' << string(num_row*2,'_') <<'\\'<<endl;
}

//regular homework
int read_words_rectangle(ifstream& fin, int width, vector<string> &words){
    string word, _index; 
    int num_row = 0;
    while ( fin >> word ){   
        while ( word.size() > width ){           //when the words are superlong, split them;        
            _index = word.substr(0,width-1) + '-';

            words.push_back(_index); num_row++;
            word.erase(0, width-1);
        }
        words.push_back(word); num_row++; 
    }
    words.push_back("");
    
    //return the num_row needed for print
    return num_row;
}

void flush_left(ofstream& fout, int num, int length, vector<string> &words){
    int start=0;
    unsigned long total_length;
    
    //print the upper bound
    for (int k = 1; k <= length+4; k++) fout << '-';fout << endl;

    while ( start < num ){
        total_length=words[start++].size(); 
        if (start >= words.size()) break;
        fout << "| ";

        //justify how many words should be in the line.
        while ( total_length+words[start].size() < length && start < num){ 
            words[start-1] += ' ';
            fout << words[start-1];
            total_length += words[start++].size() + 1;
        }
        
        //add spare "space" at the right hand side
        while ( total_length < length ) {
            words[start-1] += ' ';
            total_length++;   
        }
        fout << words[start-1]<<" |"<<endl; 
    }
    for (int k = 1; k <= length+4; k++) fout << '-';fout << endl;
}

void flush_right(ofstream& fout, int num, int length, vector<string> &words){
    int start=0, point=0;
    unsigned long total_length;
    
    //print the upper bound
    for (int k = 1; k <= length+4; k++) fout << '-';fout << endl;
    
    while ( start < num ){
        //variable point to store the most left word's position
        point=start;                                     
        
        total_length=words[start++].size();
        if (start >= words.size()) break;
        fout << "| ";
        
        //justify how many words should be in the line.
        while ( total_length+words[start].size() < length && start < num) {
            words[start-1]+=' ';
            total_length+=words[start++].size()+1;
        }
        
        //add spare "space" at the left hand side
        while ( total_length < length ){
            words[point]=' '+words[point];
            total_length++;
        }

        for ( int i = point; i < start; i++ ) fout << words[i]; 
        fout << " |" << endl; 
    }
    for (int k = 1; k <= length+4; k++) fout << '-';fout << endl;
}

void full_justify(ofstream& fout, int num, int length, vector<string> &words){
    
    int start=0, point=0, index=0;
    unsigned long total_length;
    
    //print the upper bound
    for (int k = 1; k <= length+4; k++) fout << '-';fout << endl;
    
    while ( start < num )
    {
        index=point=start;
        total_length=words[start++].size();

        fout << "| ";
        
        //justify how many words should be in the line.
        while ( total_length+words[start].size() < length && start < num){
            words[start-1] += ' ';
            total_length += words[start++].size()+1;
        }

        if ( point != (start-1) && start < num ){
            while ( total_length < length ){
                //distribute the "space" along the line, from left to right,
                if ( index == (start-1) ) index=point;
                
                //if reach the last words, automatically return to the first one;      
                words[index++]+=' ';                   
                total_length++;
            }
        }
        
        else if ( start != num+1 ) {
            while ( total_length < length ) {
                words[start-1]+=' ';
                total_length++;
            }
        }
        
        for ( int i = point; i<start; i++ ) fout << words[i];
        fout << " |"<<endl; 
    }
    for (int k = 1; k <= length+4; k++) fout << '-';fout << endl;
}


int main(int argc,char* argv[]) {
    //open file and check
    ifstream fin(argv[1]);
    if(!fin.good()){
        cerr<<"Can't open "<<argv[1]<<" to read.\n";
        exit(1);
    } 
    //creat file to write
    ofstream fout(argv[2]);
    if(!fout.good()){
        cerr<<"Can't open "<<argv[2]<<" to read.\n";
    }
    
    //initiate the variables
    int text_width;
    string command;
    
    text_width = atoi(argv[3]);
    command = argv[4];
    vector<string> words;


    int num_row;
    
    //extra credit part
    if ( command.substr(0,8) == "triangle"){  
    
        vector<int> words_count;
        vector<int> space_count;
        num_row = read_words_triangle(fin, words, words_count, space_count); 
        if ( command == "triangle_flush_left") flush_left_triangle(fout, num_row, words, words_count, space_count);
        if ( command == "triangle_flush_right") flush_right_triangle(fout, num_row, words, words_count, space_count);
        if ( command == "triangle_full_justify") full_justify_triangle(fout, num_row, words, words_count, space_count);
    }    
    
    //regular part
    num_row = read_words_rectangle(fin, text_width, words);
    
    if ( command == "flush_left" ) flush_left(fout, num_row, text_width, words);
    if ( command == "flush_right" ) flush_right(fout, num_row, text_width, words);
    if ( command == "full_justify" ) full_justify(fout, num_row, text_width, words);

    
    return 0;
    
    
}
