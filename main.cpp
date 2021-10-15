#include <iostream>
#include <sstream>
#include <vector> 

void fillVector(std::string userInput, std::vector<int> &myVector){
    
    std::stringstream myStream(userInput); 
    int currentInteger = 0; 
    
    while (myStream >> currentInteger){
        myVector.push_back(currentInteger); 
    }
}

int main() {
    
    std::string userInput = ""; 
    std::vector<int> referenceString;
    std::vector<int> frameNumbers; 
    int numberInReferenceString = 0; 
    int numberOfFrames = 0;
    int pageFaults = 0; 
    
    std::cout << "Please enter the reference string separated by spaces: ";
    std::getline(std::cin, userInput);
    fillVector(userInput, referenceString);
    numberInReferenceString = referenceString.size(); 
    std::cout << "The reference string is: " << userInput << std::endl << std::endl;  
    
    std::cout << "Please enter the frame numbers: "; 
    std::getline(std::cin, userInput); 
    fillVector(userInput, frameNumbers); 
    numberOfFrames = frameNumbers.size();
    std::cout << "The frame numbers are: " << userInput << std::endl; 
    
    std::vector<int> storedValues(numberOfFrames, -1); 
    
    std::cout << "Assignment of the frames by LRU algorithm:" << std::endl << std::endl; 
    std::cout << "Frames:"; 
    for (int theCounter = 0; theCounter < numberOfFrames; theCounter++){
        std::cout << "\t" << frameNumbers.at(theCounter);
    }
    std::cout << "\n\n--------------------------------------\n"; 
    
    for (int theCounter = 0; theCounter < numberInReferenceString; theCounter++){
    
        if (theCounter == 0){ /* The first iteration will always cause a pauge fault as the frames are all empty. */ 
                storedValues.at(0) = referenceString.at(0); 
                pageFaults = pageFaults + 1; 
        } else { /* For all other iterations check if the value in referenceString is not already in storedValues. If it is continue over the next iteration. */
        
            bool alreadyStored = false; 

            for (int anotherCounter = 0; anotherCounter < numberOfFrames; anotherCounter++){
                
                if (storedValues.at(anotherCounter) == referenceString.at(theCounter)){
                    alreadyStored = true; 
                    break;
                }
            }
            
            if (!alreadyStored){ /* If it is not in the storedValues vector, then perform the following: */ 
                
                if (storedValues.at(numberOfFrames - 1) == -1){ /* If the last frame is empty, then it can be directly added without performing a swap operation. */ 
                    
                    for (int anotherCounter = 0; anotherCounter < numberOfFrames; anotherCounter++){
                        if (storedValues.at(anotherCounter) == -1){ /* Find the first empty location in the storedValues vector and store the value on it. */ 
                            storedValues.at(anotherCounter) = referenceString.at(theCounter); 
                            break; 
                        }
                    }
                    
                } else { /* If the last frame has been already occupied, then you need to find out which was the last recently used value stored and replace it. */ 
                
                    std::vector<int> recentValues(numberOfFrames - 1, -1);
                    int maxNumberOfRecentValues = recentValues.size(); 
                    recentValues.at(0) = referenceString.at(theCounter - 1); /* The value that was most recently used is the previous from the current one. */ 
                    
                    for (int anotherCounter = theCounter - 2; anotherCounter >= 0; anotherCounter--){
                        bool markedAsRecent = false; /* At first, all the values are NOT marked as being recent. */ 
                        for (int lastCounter = 0; lastCounter < maxNumberOfRecentValues; lastCounter++){
                            
                            if (referenceString.at(anotherCounter) == recentValues.at(lastCounter)){ /* If the value grabbed is inside recentValues, then stop checking recentValues. */ 
                                markedAsRecent = true;
                                break; 
                            }
                            
                            if (referenceString.at(anotherCounter) != recentValues.at(lastCounter) && recentValues.at(lastCounter) == -1){ /* If the value grabbed is NOT inside recentValues and there's an empty spot, then add it to recentValues. */ 
                                recentValues.at(lastCounter) = referenceString.at(anotherCounter); 
                            }
                            
                        }
                        if(markedAsRecent){
                            continue; 
                        }
                    }
                    
                    /* At this point, you have the recentValues stored inside the recentValues vector. 
                     * Now, you need to swap the value in the storedValues vector that is not inside recentValues. */ 
                     
                     for (int anotherCounter = 0; anotherCounter < numberOfFrames; anotherCounter++){
                         
                         bool mustSwap = false; 
                         
                         for (int lastCounter = 0; lastCounter < maxNumberOfRecentValues; lastCounter++){
                             
                             if (storedValues.at(anotherCounter) == recentValues.at(lastCounter)){ /* If the value at storedValues is found in recentValues move to the next item in storedValues. */ 
                                 break; 
                             }
                             
                             if (lastCounter == maxNumberOfRecentValues - 1){ /* If you got to the end of recentValues and didn't find a match, then mustSwap will be turned into true. */ 
                                 mustSwap = true; 
                             }
                             
                         }
                         
                         if (mustSwap){ /* If mustSwap was turned into true, then this is the index that you need to swap. */ 
                             storedValues.at(anotherCounter) = referenceString.at(theCounter);  
                         }
                         
                     }
    
                }
                
                pageFaults = pageFaults + 1; 
                
            } 

        }
        
        /******************************************
         * DISPLAYING THE STORED VALUES PER FRAME *
         ******************************************/
        for (int anotherCounter = 0; anotherCounter < numberOfFrames; anotherCounter++){
            std::cout << "\t" << storedValues.at(anotherCounter); 
        }
        std::cout << "\n"; 
    
    }
    
    std::cout << "--------------------------------------\n\n";
    std::cout << "Number of page faults: " << pageFaults << std::endl << std::endl <<std::endl; 
    std::cout << "Thanks for using this program, dear Memory Manager!";
    
    return 0; 
    
}