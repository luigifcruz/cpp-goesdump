#include "TextHandler.h"

using namespace std;
namespace GOESDump {
    void TextHandler::HandleFile(string filename, string outputFolder, XRITHeader header, WatchMan* wm) {
        vector<uint8_t> f = Tools.ReadAllBytes(filename);
        if ((int)f.at(0) == 0) {       
            f.erase(f.begin(), f.begin()+(int)header.PrimaryHeader.HeaderLength);
            ProcessFile(f, outputFolder, header, wm);
        } else {
            wm->Log("Expected header type 0 for first header. Got " + to_string((int)f.at(0)) + ".", 3);
        }
    }

    void TextHandler::ProcessFile(vector<uint8_t> file, string outputFolder, XRITHeader header, WatchMan* wm) {
        string outName = header.Filename();
        outName.replace(outName.find(".lrit"), 6,  ".txt");
        outName = Tools.Combine(outputFolder, outName);

        ofstream f(outName, ios::out | ios::binary);
        copy(file.begin(), file.end(), ostreambuf_iterator<char>(f));
        f.close();
    }
}
