#include <bits/stdc++.h>

using namespace std;

int numberOfVertices;

map<string, int> distinctRepresentations, circularlyDistinctRepresentations;

string stringRepresentationOfNumber(int number) {
    return string(1, 'a' + number);
}

int representationToNumber(char representation) {
    return representation - 'a';
}

string stringRepresentative(string representation) {
    int len = representation.length();
    char smallest_character = representation[0];
    for(int i=1;i<len;i++){
        smallest_character = min(smallest_character, representation[i]);
    }
    vector<string> representative_candidates;
    for(int i=0;i<len;i++){
        if(representation[i] == smallest_character){
            string candidate = representation.substr(i) + representation.substr(0, i);
            representative_candidates.push_back(candidate);
        }
    }
    sort(representative_candidates.begin(), representative_candidates.end());
    return representative_candidates[0];
}

bool isValidEdge(int i, int j, int numberOfVertices){
    return (j == (i+1)) || (i==0 && j==numberOfVertices-1);
}

bool isValidRepresentation(string &representation, int numberOfVertices){
    vector<int> occurences[numberOfVertices];
    for(int i=0;i<representation.length();i++){
        occurences[representationToNumber(representation[i])].push_back(i);
    }
    int numberOfValidEdges = 0;
    for(int i=0;i<numberOfVertices;i++){
        for(int j=i+1;j<numberOfVertices;j++){
            if((occurences[i][0]<occurences[j][0] && occurences[j][0]<occurences[i][1] && occurences[i][1]<occurences[j][1]) ||
               (occurences[j][0]<occurences[i][0] && occurences[i][0]<occurences[j][1] && occurences[j][1]<occurences[i][1])){
                   if(!isValidEdge(i, j, numberOfVertices)){
                        return false;
                   } else {
                       numberOfValidEdges++;
                   }
            }
        }
    }
    return numberOfValidEdges==numberOfVertices;
}

void calculate_result(int numberOfVertices){
    string representation = "";
    for(int i=0;i<numberOfVertices;i++){
        representation = representation +
                            stringRepresentationOfNumber(i) + stringRepresentationOfNumber(i);
    }
    do{
        if(isValidRepresentation(representation, numberOfVertices)){
            distinctRepresentations[representation]++;
            circularlyDistinctRepresentations[stringRepresentative(representation)]++;
        }
    } while(next_permutation(representation.begin(), representation.end()));
}

int main()
{
    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */
    cout<<"Enter the number of vertices in the cycle graph\n";
    cin>>numberOfVertices;
    assert(numberOfVertices >= 3);
    assert(numberOfVertices <= 26);

    calculate_result(numberOfVertices);

    cout<<"Number of distinct representations:            "<<distinctRepresentations.size()<<"\n";
    cout<<"Number of circularly distinct representations: "<<circularlyDistinctRepresentations.size()<<"\n";

    return 0;
}
