#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

// LRU implementation
int LRU(const vector<int>& pages, int numFrames) {
    unordered_map<int, int> pageLastUsed; 
    vector<int> frames; 
    int pageFaults = 0; 

    cout << "For LRU Algorithm:" << endl;

    
    for (int i = 0; i < pages.size(); ++i) {
        cout << "Step " << i + 1 << ": ";

        
        if (find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
            
            if (frames.size() < numFrames) {
                frames.push_back(pages[i]);
            }
            else {
                
                int leastRecentlyUsedPage = frames[0];
                for (int j = 1; j < numFrames; ++j) {
                    if (pageLastUsed[frames[j]] < pageLastUsed[leastRecentlyUsedPage]) {
                        leastRecentlyUsedPage = frames[j];
                    }
                }
                auto it = find(frames.begin(), frames.end(), leastRecentlyUsedPage);
                *it = pages[i];
            }
            
            pageFaults++;
            cout << "Page fault (" << pages[i] << ") - Page Table: {";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "}, Frames: [";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
        else {
            
            cout << "No page fault - Page Table: {";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "}, Frames: [";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
        
        pageLastUsed[pages[i]] = i;
    }

    cout << "Total Page Faults: " << pageFaults << endl << endl;
    return pageFaults;
}

//Optimal implementation
int Optimal(const vector<int>& pages, int numFrames) {
    unordered_map<int, int> nextPageIndex; 
    vector<int> frames; 
    int pageFaults = 0; 

    cout << "For Optimal Algorithm:" << endl;

    for (int i = 0; i < pages.size(); ++i) {
        cout << "Step " << i + 1 << ": ";

        if (find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
            
            if (frames.size() < numFrames) {
                frames.push_back(pages[i]);
            }
            else {
                int farthestNextUseIndex = -1;
                int pageToRemove;
                for (int j = 0; j < frames.size(); ++j) {
                    if (nextPageIndex.find(frames[j]) == nextPageIndex.end()) {
                        pageToRemove = frames[j];
                        break;
                    }
                    if (nextPageIndex[frames[j]] > farthestNextUseIndex) {
                        farthestNextUseIndex = nextPageIndex[frames[j]];
                        pageToRemove = frames[j];
                    }
                }
                auto it = find(frames.begin(), frames.end(), pageToRemove);
                *it = pages[i];
            }
            pageFaults++;
            cout << "Page fault (" << pages[i] << ") - Page Table: {";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "}, Frames: [";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
        else {
            cout << "No page fault - Page Table: {";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "}, Frames: [";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
        nextPageIndex[pages[i]] = i + 1;
    }

    cout << "Total Page Faults: " << pageFaults << endl << endl;
    return pageFaults;
}

//FIFO implementation
int FIFO(const vector<int>& pages, int numFrames) {
    queue<int> frame; 
    unordered_map<int, bool> inFrames; 
    int pageFaults = 0;

    cout << "For FIFO Algorithm:" << endl;

    for (int i = 0; i < pages.size(); ++i) {
        cout << "Step " << i + 1 << ": ";

        if (!inFrames[pages[i]]) {
            if (frame.size() == numFrames) {
                int old = frame.front();
                frame.pop();
                inFrames[old] = false;
            }
            frame.push(pages[i]);
            inFrames[pages[i]] = true;
            pageFaults++;
            cout << "Page fault (" << pages[i] << ") - Page Table: {";
            queue<int> temp = frame;
            while (!temp.empty()) {
                cout << temp.front();
                temp.pop();
                if (!temp.empty()) cout << ", ";
            }
            cout << "}, Frames: [";
            temp = frame;
            while (!temp.empty()) {
                cout << temp.front();
                temp.pop();
                if (!temp.empty()) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
        else {
            cout << "No page fault - Page Table: {";
            queue<int> temp = frame;
            while (!temp.empty()) {
                cout << temp.front();
                temp.pop();
                if (!temp.empty()) cout << ", ";
            }
            cout << "}, Frames: [";
            temp = frame;
            while (!temp.empty()) {
                cout << temp.front();
                temp.pop();
                if (!temp.empty()) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
    }

    cout << "Total Page Faults: " << pageFaults << endl << endl;
    return pageFaults;
}

int main() {
    vector<int> PageRef = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 };
    int Frames = 4;

    LRU(PageRef, Frames);

    Optimal(PageRef, Frames);

    FIFO(PageRef, Frames);

    return 0;
}