#include <bits/stdc++.h>

using namespace std;

int numberOfVertices;

map<string, int> distinctRepresentations, circularlyDistinctRepresentations;

string stringRepresentationOfNumber(int number) {
    return string(1, 'a' + number);
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

void calculate_result(string current_string, vector<pair<int, int>> &edges, bool vertexAlreadyInCurrentVertexSet[]){
    if(current_string.length() == 2*numberOfVertices){
        distinctRepresentations[current_string]++;
        circularlyDistinctRepresentations[stringRepresentative(current_string)]++;
        //st_prufer[cur_string]++;
        //st_prufer_unique[calc_representative(cur_string)]++;
        return;
    }

    if(current_string == "") {
        for(pair<int, int> edge:edges){
            int u = edge.first;
            int v = edge.second;

            vertexAlreadyInCurrentVertexSet[u] = true;
            vertexAlreadyInCurrentVertexSet[v] = true;

            string next_string = stringRepresentationOfNumber(u) + stringRepresentationOfNumber(v) +
                                    stringRepresentationOfNumber(u) + stringRepresentationOfNumber(v);
            calculate_result(next_string, edges, vertexAlreadyInCurrentVertexSet);

            next_string = stringRepresentationOfNumber(v) + stringRepresentationOfNumber(u) +
                            stringRepresentationOfNumber(v) + stringRepresentationOfNumber(u);
            calculate_result(next_string, edges, vertexAlreadyInCurrentVertexSet);

            vertexAlreadyInCurrentVertexSet[u] = false;
            vertexAlreadyInCurrentVertexSet[v] = false;
        }
    } else {
        for(auto edge:edges){
            int u = edge.first;
            int v = edge.second;
            if(vertexAlreadyInCurrentVertexSet[u]^vertexAlreadyInCurrentVertexSet[v]){
                if(vertexAlreadyInCurrentVertexSet[v]){
                    swap(u, v);
                }
                vertexAlreadyInCurrentVertexSet[v] = true;

                size_t found_at_index = current_string.find(stringRepresentationOfNumber(u));
                string nextString = current_string.substr(0, found_at_index) +
                                        stringRepresentationOfNumber(v) +
                                        stringRepresentationOfNumber(u) +
                                        stringRepresentationOfNumber(v) +
                                            current_string.substr(found_at_index+1);

                calculate_result(nextString, edges, vertexAlreadyInCurrentVertexSet);

                found_at_index = current_string.find(stringRepresentationOfNumber(u), found_at_index+1);
                nextString = current_string.substr(0, found_at_index) +
                                stringRepresentationOfNumber(v) +
                                stringRepresentationOfNumber(u) +
                                stringRepresentationOfNumber(v) +
                                    current_string.substr(found_at_index+1);

                calculate_result(nextString, edges, vertexAlreadyInCurrentVertexSet);
                vertexAlreadyInCurrentVertexSet[v] = false;
            }
        }
    }
}

void create_tree_from_prufer_code(int prufer_code[], int number_of_vertices)
{
    int m = number_of_vertices - 2;
    int vertex_set[number_of_vertices];

    for (int i = 0; i < number_of_vertices; i++)
        vertex_set[i] = 0;

    // Number of occurrences of vertex in code
    for (int i = 0; i < m; i++)
        vertex_set[prufer_code[i]] += 1;

    vector<int> adj[number_of_vertices];
    vector<pair<int, int>> edges;

    int j = 0;
    for (int i = 0; i < m; i++)
    {
        for (j = 0; j < number_of_vertices; j++)
        {
            // If j+1 is not present in prufer set
            if (vertex_set[j] == 0)
            {
                // Remove from Prufer set and print edge.
                vertex_set[j] = -1;

                adj[j].push_back(prufer_code[i]);
                adj[prufer_code[i]].push_back(j);
                edges.push_back(make_pair(j, prufer_code[i]));

                vertex_set[prufer_code[i]]--;
                break;
            }
        }
    }

    j = 0;
    // For the last element
    int first_vertex;
    for (int i = 0; i < number_of_vertices; i++)
    {
        if (vertex_set[i] == 0 && j == 0)
        {
            first_vertex = i;
            j++;
        }
        else if (vertex_set[i] == 0 && j == 1){
            adj[first_vertex].push_back(i);
            adj[i].push_back(first_vertex);
            edges.push_back(make_pair(first_vertex, i));
        }
    }

    bool vertexAlreadyInCurrentVertexSet[number_of_vertices];
    memset(vertexAlreadyInCurrentVertexSet, false, sizeof vertexAlreadyInCurrentVertexSet);

    calculate_result("", edges, vertexAlreadyInCurrentVertexSet);
    //cout<<st_prufer.size()<<"\n";
    //cout<<st_prufer_unique.size()<<"\n";
    //st_prufer.clear();
    //st_prufer_unique.clear();
}

void generate_all_prufer_codes(int prufer_code[], int current_index, int numberOfVertices) {
    if(current_index == numberOfVertices-2) {
        create_tree_from_prufer_code(prufer_code, numberOfVertices);
        return;
    }
    for(int i=0;i<numberOfVertices;i++){
        prufer_code[current_index] = i;
        generate_all_prufer_codes(prufer_code, current_index+1, numberOfVertices);
    }
}

int main()
{
    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */
    cout<<"Enter the number of vertices in the tree\n";
    cin>>numberOfVertices;
    assert(numberOfVertices >= 3);
    assert(numberOfVertices <= 26);

    int prufer_code[numberOfVertices-2];
    generate_all_prufer_codes(prufer_code, 0, numberOfVertices);

    cout<<"Number of distinct representations:            "<<distinctRepresentations.size()<<"\n";
    cout<<"Number of circularly distinct representations: "<<circularlyDistinctRepresentations.size()<<"\n";

    return 0;
}
