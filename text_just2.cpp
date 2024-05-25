#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int maxWidth =18;
void errors(int error  ) {
    switch (error ) {
    case -1:
        cout << "ERROR: word length exceeds";
        break;
    
    }
    exit(0);
}
int par_check(int &number_words, int &newenv, int &segment_sum) {
    int blanks;
      ((newenv - segment_sum) % (number_words - 1) == 0) ? 
        blanks = (newenv - segment_sum) / (number_words - 1)
    :  blanks = ((newenv - segment_sum) / (number_words - 1)) + 1;

    return blanks;
}
bool leng_check(vector<string>& words) {
    for (auto i = words.begin(); i != words.end(); ++i)
        if ((*i).size() > maxWidth) return false;
    return true;
}
void print(vector<string> ans) {
    for (int t = 0; t < ans.size(); t++)
        cout << ans[t];
}

void push_down(vector<string>& ans,vector<string>&words, int& pos, int& spaces_in_segment) {
    ans.push_back(words.at(pos));
    for (int temp = 0; temp < spaces_in_segment; temp++) {
        ans.push_back("-");
    }
}

int generat(vector<string>& ans, vector<string>& words, int& left, int& right, int& segment_sum, int& number_words) {
    int spaces_in_segment = maxWidth - segment_sum;
    if (number_words == 1)
    {
        push_down(ans, words, left, spaces_in_segment);
        ans.push_back("\n");
         left = right;
        return left;
       
    }
    int blanks = (spaces_in_segment / (number_words - 1));
    int temp, newenv = 0, temp2 = 0;
    for (int i = left; i < right; i++) {
        push_down(ans, words, i, blanks);
        number_words--;
        if (number_words == 1)
        {
            ans.push_back(words.at(i + 1));
            break;
        }
        segment_sum -= words.at(i).size();
        temp2 += words.at(i).size() + blanks;
        newenv = maxWidth - temp2;
        blanks = par_check(number_words, newenv, segment_sum);

    }
    ans.push_back("\n");
     left = right;
    return left;
}

int count_words(vector<string>& ans, vector<string>& words, int& left, int& right)   {
   int  number_words = 0, segment_sum=0;
  
    while (segment_sum < maxWidth && (number_words + segment_sum <  maxWidth)) {
       
        if (right >= words.size()) {     
            return generat(ans, words, left, right, segment_sum, number_words);
           }
        segment_sum += words.at(right).size();
        number_words++;
        right++;
    }
  
    right--; number_words--;

    if (number_words > 0) {
            if (right < words.size() )
                    segment_sum -= words.at(right).size();
    }
    return generat(ans, words, left, right, segment_sum, number_words);
    }



int main()
{
    
   // vector<string> words{ "this", "is", "an","jurisdiction" };
    vector<string> words{ "What","must","be","acknowledgment","shall","be" };
    // vector<string> words{ "This", "is", "an", "example", "of", "text", "justification." };
    vector<string> ans;

    if (!leng_check(words)) {
        errors(-1);
    }
    int  left = 0, right = 0  ;

    while ( left < words.size() ) {
       
        count_words(ans, words,left,right);
      
     }
    print(ans);
         

} 


