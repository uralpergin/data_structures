#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName)
{   
    GraphVertex new_vertex;
    new_vertex.edgeCount = 0;
    new_vertex.name = vertexName;

    for(int i = 0; i < vertexList.size(); i++){
        if(vertexList[i].name == vertexName) throw DuplicateVertexNameException();
        else continue;
    }
    vertexList.push_back(new_vertex);
    // TODO
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{
    int from = -1; int to = -1;
    for(int i = 0; i < vertexList.size(); i++){
        if(vertexList[i].name == fromVertexName) from = i;
        if(vertexList[i].name == toVertexName) to = i;
    }
    if(from == -1 || to == -1) throw VertexNotFoundException();
    else if(from == to) return false;
    else if(vertexList[from].edgeCount == MAX_EDGE_PER_VERTEX || vertexList[to].edgeCount == MAX_EDGE_PER_VERTEX) throw TooManyEdgeOnVertexExecption();
    else{
        for(int j = 0; j < edgeList.size(); j++){
            if(edgeList[j].vertexId0 == from && edgeList[j].vertexId1 == to) return false;
            else continue;
        }
        GraphEdge new_edge;
        new_edge.vertexId0 = from;
        new_edge.vertexId1 = to;
        new_edge.weight = weight;
        new_edge.masked = false;

        edgeList.push_back(new_edge);

        vertexList[from].edgeCount +=1;
        vertexList[from].edgeIds[vertexList[from].edgeCount -1] = edgeList.size() -1;
        vertexList[to].edgeCount +=1;
        vertexList[to].edgeIds[vertexList[to].edgeCount -1] = edgeList.size() -1;

        return true;
    }

    
    // TODO
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{
    
    int fro = -1; int t = -1;
    for(int i = 0; i < vertexList.size(); i++){
        if(vertexList[i].name == from) fro = i;
        if(vertexList[i].name == to) t = i;
    }
    if(fro == -1 || t == -1) throw VertexNotFoundException();
    else{
        int *distance = new int[vertexList.size()];
        int *previous = new int[vertexList.size()];

        for(int k = 0; k < vertexList.size(); k++){
            distance[k] = LARGE_NUMBER;
            previous[k] = -1;
        }
        distance[fro] = 0;

        std::priority_queue<DistanceVertexIdPair> pq;
        for(int j = 0; j < vertexList.size(); j++){
            DistanceVertexIdPair d = DistanceVertexIdPair(j, distance[j]);
            pq.push(d); 
        }

        while(!pq.empty()){
            int v = pq.top().vId;
            pq.pop();

            for(int i = 0; i< edgeList.size(); i++){
                if(edgeList[i].masked != true && (edgeList[i].vertexId0 == v || edgeList[i].vertexId1 == v)){
                    int w;
                    if(edgeList[i].vertexId0 == v) w = edgeList[i].vertexId1;
                    else w = edgeList[i].vertexId0;
                    int new_dist = distance[v] + edgeList[i].weight;
                    if(new_dist < distance[w]){
                        distance[w] = new_dist;
                        previous[w] = v;
                        std::priority_queue<DistanceVertexIdPair> temp_pq;
                        for(int z = 0; z < vertexList.size(); z++){
                            if(pq.top().vId == w) pq.pop();
                            else{
                                temp_pq.push(pq.top());
                                pq.pop();
                            }
                        }
                        pq = temp_pq;
                        pq.push(DistanceVertexIdPair(w,new_dist));
                    }
                    continue;
                }
                else continue;
            }
        }
        
        std::vector<int> temp;
        int i = t;
        int finish = 0;
        while(!finish){
            if(i == -1){
                delete[] distance;
                delete[] previous;
                return false;
            }
            else if(i == fro){
                temp.push_back(fro);
                finish = 1;
                break;
            }
            else{
                temp.push_back(i);
                i = previous[i];
            }
        }
        int size = temp.size();
        for(int y = 0; y < size; y++){
            if(temp.back() == -1){
                delete[] previous;
                delete[] distance;
                return false;
            }
            else{
                orderedVertexIdList.push_back(temp.back());
                temp.pop_back();
            }
        }
        
        delete[] distance;
        delete[] previous;
        return true;
    }
    
    // TODO
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{   
    int find1 = -1; int find2 = -1;
    for(int c = 0; c < vertexList.size(); c++){
        if(vertexList[c].name == from) find1 = 1;
        else if(vertexList[c].name == to) find2 = 1;
    }
    if(find1 == -1 || find2 == -1) throw VertexNotFoundException(); 
    int num=-1;
    UnMaskAllEdges();
    std::vector<int> ordered;
    if(ShortestPath(ordered,from,to) == true){
        orderedVertexIdList.push_back(ordered);
        num=1;
    }
    else return 0;
    while(num != numberOfShortestPaths){
        int max = -1;
        
        for(int i = 0; i < ordered.size()-1; i++){
            for(int j = 0; j < edgeList.size(); j++){
                if(edgeList[j].vertexId0 == ordered[i] && edgeList[j].vertexId1 == ordered[i+1] && edgeList[j].weight > max){
                    max = edgeList[j].weight;
                    continue;
                }
                else continue;
            }    
        }
        for(int z = 0; z < edgeList.size(); z++){
            if(edgeList[z].weight == max) edgeList[z].masked = true;
        }
        ordered.clear();
        if(ShortestPath(ordered,from,to) == true){
            orderedVertexIdList.push_back(ordered);
            num++;
        }
        else break;
    }
    UnMaskAllEdges();
    return num; 
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{   
    int frst = -1; int scnd = -1;
    for(int i = 0; i < vertexNames.size(); i++){
        frst = -1;
        scnd = -1;
        for(int j = 0; j < vertexList.size(); j++){
            if(vertexNames[i].s0 == vertexList[j].name) frst = j;
            else if(vertexNames[i].s1 == vertexList[j].name) scnd = j;
            }
        if(frst == -1 || scnd == -1) throw VertexNotFoundException();
        else{
            for(int k = 0; k < edgeList.size(); k++){
                if((edgeList[k].vertexId0 == frst && edgeList[k].vertexId1 == scnd) || (edgeList[k].vertexId0 == scnd && edgeList[k].vertexId1 == frst)){
                    edgeList[k].masked = true;
                }
            }
        }
    }
    
    // TODO
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
   int frst = -1; int scnd = -1;
    for(int i = 0; i < vertexNames.size(); i++){
        frst = -1;
        scnd = -1;
        for(int j = 0; j < vertexList.size(); j++){
            if(vertexNames[i].s0 == vertexList[j].name) frst = j;
            else if(vertexNames[i].s1 == vertexList[j].name) scnd = j;
            }
        if(frst == -1 || scnd == -1) throw VertexNotFoundException();
        else{
            for(int k = 0; k < edgeList.size(); k++){
                if((edgeList[k].vertexId0 == frst && edgeList[k].vertexId1 == scnd) || (edgeList[k].vertexId0 == scnd && edgeList[k].vertexId1 == frst)){
                    edgeList[k].masked = false;
                }
            }
        }
    }
    // TODO
}

void Graph::UnMaskAllEdges()
{
    for(int i = 0; i < edgeList.size(); i++){
        edgeList[i].masked = false;
    }
    // TODO
}

void Graph::MaskVertexEdges(const std::string& name)
{   
    int ver_id = -1;
    for(int i = 0; i < vertexList.size(); i++){
        if(vertexList[i].name == name) ver_id = i; 
    }
    if(ver_id == -1) throw VertexNotFoundException();
    else{
        for(int j = 0; j < vertexList[ver_id].edgeCount; j++){
            edgeList[vertexList[ver_id].edgeIds[j]].masked = true; 
        }        
    }
    
    // TODO
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    int ver_id = -1;
    for(int i = 0; i < vertexList.size(); i++){
        if(vertexList[i].name == name) ver_id = i; 
    }
    if(ver_id == -1) throw VertexNotFoundException();
    else{
        for(int j = 0; j < vertexList[ver_id].edgeCount; j++){
            edgeList[vertexList[ver_id].edgeIds[j]].masked = false; 
        }        
    }
    
    // TODO
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    int from = -1; int to = -1;
    for(int i = 0; i < vertexList.size(); i++){
        if(vertexList[i].name == vName0) from = i;
        else if(vertexList[i].name == vName1) to = i;
    }
    if(from == -1 || to == -1) throw VertexNotFoundException();

    for(int j = 0; j < edgeList.size(); j++){
        if((edgeList[j].vertexId0 == from && edgeList[j].vertexId1 == to) || (edgeList[j].vertexId0 == to && edgeList[j].vertexId1 == from)){
            edgeList[j].weight = newWeight;
            break;
        }
        else continue;
    }
    // TODO
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    for(int i = 0; i < edgeList.size(); i++){
        if(edgeList[i].vertexId0 == vId0 && edgeList[i].vertexId1 == vId1){
            edgeList[i].weight = newWeight;
            break;
        }
        else continue;
    }
    // TODO
    
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    return vertexList.size();
    // TODO
}

int Graph::TotalEdgeCount() const
{
    return edgeList.size();
    // TODO
}

std::string Graph::VertexName(int vertexId) const
{
    if(vertexId >= vertexList.size()) return "";
    else return vertexList[vertexId].name;
    // TODO
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    int from = -1; int to = -1; int total_weight = 0;
    for(int i = 0; i < orderedVertexIdList.size() -1; i++){
        from = orderedVertexIdList[i];
        to = orderedVertexIdList[i+1];

        if(from >= vertexList.size() || to >= vertexList.size()) throw VertexNotFoundException();

        for(int j = 0; j < edgeList.size(); j++){
            if((edgeList[j].vertexId0 == from && edgeList[j].vertexId1 == to) || (edgeList[j].vertexId0 == to && edgeList[j].vertexId1 == from)) total_weight += edgeList[j].weight;
        }
    }
    if(total_weight != 0) return total_weight;
    else return -1;
    // TODO
}