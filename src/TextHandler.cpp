#include "TextHandler.h"

using namespace std;
namespace GOESDump {
    void TextHandler::HandleFile(string filename, string outputFolder) {
        /*var f = File.Open(filename, FileMode.Open);
        var firstHeader = new byte[3];
        f.Read(firstHeader, 0, 3);
        if (firstHeader[0] == 0) {
            var tmp = firstHeader.Skip(1).Take(2).ToArray();
            if (BitConverter.IsLittleEndian) {
                Array.Reverse(tmp);
            }

            int size = BitConverter.ToUInt16(tmp, 0);
            firstHeader = new byte[size - 3];
            f.Seek(0, SeekOrigin.Begin);
            f.Read(firstHeader, 0, size - 3);

            PrimaryRecord fh = LLTools.ByteArrayToStruct<PrimaryRecord>(firstHeader);
            fh = LLTools.StructToSystemEndian(fh);

            f.Seek(0, SeekOrigin.Begin);
            tmp = new byte[fh.HeaderLength];
            f.Read(tmp, 0, (int)fh.HeaderLength);
            var header = FileParser.GetHeader(tmp);
            ProcessFile(f, header, outputFolder);
            f.Close();
        } else {
            cout << "Expected header type 0 for first header. Got " << (int)firstHeader[0] << "." << endl;
        }*/
    }

    void TextHandler::ProcessFile(string file, XRITHeader header, string outputFolder) {
        /*int bytesToRead = (int) (file.Length - header.PrimaryHeader.HeaderLength);

        var buffer = new byte[bytesToRead];
        file.Read(buffer, 0, bytesToRead);

        string outName = header.Filename.Replace(".lrit", ".txt");
        outName = Path.Combine(outputFolder, outName);

        var fo = File.OpenWrite(outName);
        fo.Write(buffer, 0, bytesToRead);
        fo.Close();*/
    }
}
