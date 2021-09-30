#include <bits/stdc++.h>

using namespace std;

int numberOfVertices;

map<string, int> distinctRepresentations, circularlyDistinctRepresentations;

vector<bool> vertexAlreadyInCurrentVertexSet;

set<pair<int, int>> edges;

string stringRepresentationOfNumber(int number) {
    return string(1, 'a' + number - 1);
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

void calculate_result(string currentString){
    if(currentString.length() == 2*numberOfVertices){
        distinctRepresentations[currentString]++;
        circularlyDistinctRepresentations[stringRepresentative(currentString)]++;
        return;
    }

    if(currentString == "")
    {
        for(pair<int, int> edge:edges){
            int u = edge.first;
            int v = edge.second;

            vertexAlreadyInCurrentVertexSet[u] = true;
            vertexAlreadyInCurrentVertexSet[v] = true;

            currentString = stringRepresentationOfNumber(u) + stringRepresentationOfNumber(v) +
                                stringRepresentationOfNumber(u) + stringRepresentationOfNumber(v);

            calculate_result(currentString);

            currentString = stringRepresentationOfNumber(v) + stringRepresentationOfNumber(u) +
                                stringRepresentationOfNumber(v) + stringRepresentationOfNumber(u);

            calculate_result(currentString);

            vertexAlreadyInCurrentVertexSet[u] = false;
            vertexAlreadyInCurrentVertexSet[v] = false;
        }
        return;

    }

    for(pair<int, int> edge:edges){
        int u = edge.first;
        int v = edge.second;
        if(vertexAlreadyInCurrentVertexSet[u]^vertexAlreadyInCurrentVertexSet[v]){
            if(vertexAlreadyInCurrentVertexSet[v]){
                swap(u, v);
            }

            vertexAlreadyInCurrentVertexSet[v] = true;

            size_t found_at_index = currentString.find(stringRepresentationOfNumber(u));
            string nextString = currentString.substr(0, found_at_index) +
                                    stringRepresentationOfNumber(v) +
                                    stringRepresentationOfNumber(u) +
                                    stringRepresentationOfNumber(v) +
                                        currentString.substr(found_at_index+1);

            calculate_result(nextString);

            found_at_index = currentString.find(stringRepresentationOfNumber(u), found_at_index+1);
            nextString = currentString.substr(0, found_at_index) +
                            stringRepresentationOfNumber(v) +
                            stringRepresentationOfNumber(u) +
                            stringRepresentationOfNumber(v) +
                                currentString.substr(found_at_index+1);

            calculate_result(nextString);
            vertexAlreadyInCurrentVertexSet[v] = false;

        }
    }

    return;

}

void initialize() {
    vertexAlreadyInCurrentVertexSet.assign(numberOfVertices+1, false);
}

int main()
{
    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */
    cout<<"Enter the number of vertices in the line graph\n";
    cin>>numberOfVertices;
    assert(numberOfVertices >= 2);
    assert(numberOfVertices <= 26);

    initialize();

    for(int current_vertex=1;current_vertex<numberOfVertices;current_vertex++){
        int next_vertex = current_vertex + 1;
        edges.insert(make_pair(current_vertex, next_vertex));
    }

    calculate_result("");

    cout<<"Number of distinct representations:            "<<distinctRepresentations.size()<<"\n";
    cout<<"Number of circularly distinct representations: "<<circularlyDistinctRepresentations.size()<<"\n";

    return 0;
}
