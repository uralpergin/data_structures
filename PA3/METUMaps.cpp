#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath)
{
    this -> potentialPathCount = potentialPathCount;
    map = Graph(mapFilePath);
    inJourney = false;
    int num = map.TotalVertexCount() * potentialPathCount;
    cachedPaths = KeyedHashTable(num);
    // TODO
}

void METUMaps::SetDestination(const std::string& name)
{
    if(inJourney) PrintUnableToChangeDestination();
    else destination = name;
    // TODO
}

void METUMaps::SetStartingLocation(const std::string& name)
{
    if(inJourney) PrintUnableToChangeStartingLoc();
    else startingLoc = name;
    // TODO
}

void METUMaps::StartJourney()
{   
    std::vector<std::vector<int> > path;
    std::string key;
    PrintCalculatingRoutes(startingLoc,destination);
    if(inJourney) PrintAlreadyInJourney();
    else if(destination == "" || startingLoc == "") PrintLocationNotFound();
    else{
        map.MultipleShortPaths(path,startingLoc,destination,potentialPathCount);
        std::vector<int> vec;
        for(int i = 0; i < path.size(); i++){
            vec = path[i];

            for(int j = 0; j < (path[i].size()-1) ; j++){
                
                key = GenerateKey(map.VertexName(vec[0]), destination);
                cachedPaths.Insert(key,vec);
                vec.erase(vec.begin());
            }
            //caching
        } 
        currentLoc = startingLoc;
        currentRoute = path[0];
        inJourney = true;
    }
    //cachedPaths.Print();
    // TODO
}

void METUMaps::EndJourney()
{
    if(!inJourney) PrintJourneyIsAlreadFinished();
    else{
        destination = "";
        startingLoc = "";
        currentLoc = "";
        inJourney = false;
        cachedPaths.ClearTable();
    }
    // TODO
}

void METUMaps::UpdateLocation(const std::string& name)
{
    if(name == destination) PrintJourneyCompleted();
    else if(!inJourney) PrintNotInJourney();
    else{
        std::vector<int> val;
        if(cachedPaths.Find(val, name+"/"+destination) == true){
            PrintCachedLocationFound(name, destination);
            currentRoute = val;
            currentLoc = name;
        }
        else{
            PrintCalculatingRoutes(name, destination);
            std::vector<std::vector<int> > path;
            map.MultipleShortPaths(path,name,destination,potentialPathCount);
            std::vector<int> vec;
            std::string key;
            for(int i = 0; i < path.size(); i++){
                vec = path[i];

                for(int j = 0; j < (path[i].size()-1) ; j++){
                
                    key = GenerateKey(map.VertexName(path[i][j]), destination);
                    cachedPaths.Insert(key,vec);
                    vec.erase(vec.begin());
                }
            }
            currentLoc = name;
            currentRoute = path[0];
        }
    } 
    // TODO
}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}