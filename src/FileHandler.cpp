#include "FileHandler.h"

using namespace std;
namespace GOESDump {
    void FileHandler::HandleFile(string filename, XRITHeader fileHeader) {
        if (byCompressionTypeHandler.count((int)fileHeader.Compression())) {
            byCompressionTypeHandler[(int)fileHeader.Compression()].Define(filename, fileHeader);
        } else if (byProductIdHandler.count(fileHeader.Product().ID)) {
            byProductIdHandler[fileHeader.Product().ID].Define(filename, fileHeader);
        } else {
            DefaultHandler(filename, fileHeader);
        }
    }

    void FileHandler::DefaultHandler(string filename, XRITHeader fileHeader) {
        /*string dir = Path.GetDirectoryName(filename);
        string ofilename = fileHeader.Filename == null ? Path.GetFileName(filename) : fileHeader.Filename; 
        string f = PacketManager.FixFileFolder(dir, ofilename, fileHeader.Product, fileHeader.SubProduct);

        if (File.Exists(f)) {
            string timestamp = DateTime.Now.ToString("yyyyMMddHHmmssffff");
            string ext = Path.GetExtension(f);
            string append = String.Format("--dup-{0}{1}", timestamp, ext);
            f = f.Replace(String.Format("{0}", ext), append);
        }

        if (!String.Equals(Path.GetFileName(f), ofilename)) {
            if (fileHeader.SubProduct.Name != "Unknown") {
                UIConsole.GlobalConsole.Log(String.Format("New {0} - {1} ({2}) saved as {3}", fileHeader.Product.Name, fileHeader.SubProduct.Name, ofilename, Path.GetFileName(f)));
            } else {
                UIConsole.GlobalConsole.Log(String.Format("New {0} ({1}) saved as {2}", fileHeader.Product.Name, ofilename, Path.GetFileName(f)));
            }
        } else {
            if (fileHeader.SubProduct.Name != "Unknown") {
                UIConsole.GlobalConsole.Log(String.Format("New {0} - {1} ({2})", fileHeader.Product.Name, fileHeader.SubProduct.Name, ofilename));
            } else {
                UIConsole.GlobalConsole.Log(String.Format("New {0} ({1})", fileHeader.Product.Name, ofilename));
            }
        }

        try {
            File.Move((char)filename, f);
        } catch (IOException e) {
            UIConsole.GlobalConsole.Error(String.Format("Error moving file {0} to {1}: {2}", filename, f, e));
        }*/
    }
}
