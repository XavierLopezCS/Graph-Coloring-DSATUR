#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

//global variables; you can use them in your function with needing to pass them=
const int total_nodes = 26;
int graph[total_nodes][total_nodes] = {0};


//adds edges to graph
void populate_graph() {

    ifstream file("graph.txt");

    string line;
    vector<string> edge_list;

    while (getline(file, line,','))
    {
        edge_list.push_back(line);
    }

    for (size_t i = 0; i < edge_list.size(); i++) {
        cout << edge_list[i] << endl;
        for(size_t j = 0; j < edge_list[i].length();j++) {
            int index = (int)(edge_list[i].at(j)) - 97;
            graph[i][index] = 1;

        }
    }
}

void print_graph() {

    cout << "  ";
    for(int i = 0; i < 26; i++) {
        cout << (char)(i+97) << " ";
    }

    cout << endl;

    for(int i = 0; i < 26; i++) {
        cout << (char)(i+97) << " ";
        for(int j = 0; j < 26; j++) {
            cout << graph[i][j] << " ";
        }

        cout << endl;
    }
}


//Add your code here
void color_graph()
{
    int colors[total_nodes]; // Color assigned to each vertex
    bool used_colors[total_nodes][total_nodes] = {false}; // Tracks which neighbor uses which color
    int degree[total_nodes] = {0}; // Degree of each vertex

    // Initialize
    for (int i = 0; i < total_nodes; ++i) {
        colors[i] = -1; // -1 means uncolored
    }

    // Compute degrees
    for (int i = 0; i < total_nodes; ++i) {
        for (int j = 0; j < total_nodes; ++j) {
            if (graph[i][j] == 1)
                degree[i]++;
        }
    }

    // Choose the starting vertex (with highest degree)
    int start = 0;
    for (int i = 1; i < total_nodes; ++i) {
        if (degree[i] > degree[start]) {
            start = i;
        }
    }

    // Color the start vertex with color 0
    colors[start] = 0;
    for (int j = 0; j < total_nodes; ++j) {
        if (graph[start][j] == 1)
            used_colors[j][0] = true;
    }

    int colored = 1;

    while (colored < total_nodes) {
        int max_saturation = -1;
        int max_degree = -1;
        int selected = -1;

        // Select next vertex by highest saturation, then degree
        for (int v = 0; v < total_nodes; ++v) {
            if (colors[v] != -1) continue; // already colored

            // Counting saturation degree (number of unique neighbor colors)
            int sat = 0;
            for (int c = 0; c < total_nodes; ++c)
                if (used_colors[v][c]) sat++;

            if (sat > max_saturation || (sat == max_saturation && degree[v] > max_degree)) {
                max_saturation = sat;
                max_degree = degree[v];
                selected = v;
            }
        }

        if (selected == -1) break; // all colored

        // Finding the smallest color not used by neighbors
        int c = 0;
        while (used_colors[selected][c]) c++;

        colors[selected] = c;
        for (int j = 0; j < total_nodes; ++j) {
            if (graph[selected][j] == 1 && colors[j] == -1)
                used_colors[j][c] = true;
        }

        colored++;
    }

    // Printing the result
    cout << endl << "DSATUR Coloring Result:\n";
    for (int i = 0; i < total_nodes; ++i) {
        if (colors[i] != -1)
            cout << (char)(i + 97) << " -> Color " << colors[i] << endl;
    }
}


 
int main(int argc, char* argv[]) {

    populate_graph();

    print_graph();

    color_graph();

    return 0;
}

