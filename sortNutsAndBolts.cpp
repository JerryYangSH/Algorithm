/**
 * class Comparator {
 *     public:
 *      int cmp(string a, string b);
 * };
 * You can use compare.cmp(a, b) to compare nuts "a" and bolts "b",
 * if "a" is bigger than "b", it will return 1, else if they are equal,
 * it will return 0, else if "a" is smaller than "b", it will return -1.
 * When "a" is not a nut or "b" is not a bolt, it will return 2, which is not valid.
*/
class Solution {
private: 
    void qsort(vector<string> &nuts, vector<string> &bolts, Comparator compare, int start, int end){
        if(start >= end){
            return;
        }
        int part_inx = partition(nuts, bolts[start], compare, start, end);
        partition(bolts, nuts[part_inx], compare, start, end);
        qsort(nuts, bolts, compare, start, part_inx-1);
        qsort(nuts, bolts, compare, part_inx+1, end);
    }
    int partition(vector<string> &str, string pivot, Comparator compare, int l, int u){

        int mid = l; // middle
        for (int i = l + 1; i <= u; i++) {
            if (compare.cmp(str[i], pivot) == -1 || 
                compare.cmp(pivot, str[i]) == 1) {
                // str[i] smaller than pivot
                mid++;
                swap(str, i, mid);
            } else if (compare.cmp(str[i], pivot) == 0 || 
                       compare.cmp(pivot, str[i]) == 0) {
                // swap nuts[l]/bolts[l] with pivot
				// l位置放pivot
                swap(str, i, l);
                i--;
            }
        }
        // move pivot to proper index
        swap(str, mid, l);

        return mid;
 
    }
    void swap(vector<string> &str, int p, int q){
        string tmp = str[p];
        str[p] = str[q];
        str[q] = tmp;
    }
public:
    /**
     * @param nuts: a vector of integers
     * @param bolts: a vector of integers
     * @param compare: a instance of Comparator
     * @return: nothing
     */
    void sortNutsAndBolts(vector<string> &nuts, vector<string> &bolts, Comparator compare) {
        // write your code here
        if(nuts.size() == 0 || nuts.size() != bolts.size()){
            return;
        }
        qsort(nuts, bolts, compare, 0, nuts.size()-1);
    }
};
