#include "PacketManager.h"

using namespace std;
namespace GOESDump {
    string PacketManager::FixFileFolder(string dir, string filename, NOAAProduct product, NOAASubproduct subProduct) {
        string filef = filename;
        string basedir = Tools.DirParentName(dir);

        if (product.ID != -1) {
            // New way
            string folderName = UnknownDataFolder;
            if (product.ID == (int)SCANNER_DATA_1 || product.ID == (int)SCANNER_DATA_2) {
                switch (subProduct.ID) {
                    case (int)INFRARED_AREA_OF_INTEREST:
                    case (int)VISIBLE_AREA_OF_INTEREST:
                    case (int)WATERVAPOUR_AREA_OF_INTEREST:
                        folderName = Tools.Combine(ImagesFolder, "Area of Interest");
                        break;
                    case (int)INFRARED_FULLDISK:
                    case (int)VISIBLE_FULLDISK:
                    case (int)WATERVAPOUR_FULLDISK:
                        folderName = Tools.Combine(ImagesFolder, "Full Disk");
                        break;
                    case (int)INFRARED_NORTHERN:
                    case (int)VISIBLE_NORTHERN:
                    case (int)WATERVAPOUR_NORTHERN:
                        folderName = Tools.Combine(ImagesFolder, "Northern Hemisphere");
                        break;
                    case (int)INFRARED_SOUTHERN:
                    case (int)VISIBLE_SOUTHERN:
                    case (int)WATERVAPOUR_SOUTHERN:
                        folderName = Tools.Combine(ImagesFolder, "Southern Hemisphere");
                        break;
                    case (int)INFRARED_UNITEDSTATES:
                    case (int)VISIBLE_UNITEDSTATES:
                    case (int)WATERVAPOUR_UNITEDSTATES:
                        folderName = Tools.Combine(ImagesFolder, "United States");
                        break;
                    default:
                        folderName = Tools.Combine(ImagesFolder, UnknownDataFolder);
                        break;
                }
            } else {
                switch (product.ID) {
                    case (int)DCS:
                        folderName = DCSFolder;
                        break;
                    case (int)EMWIN:
                        folderName = EMWINFolder;
                        break;
                    case (int)NOAA_TEXT:
                        folderName = TextFolder;
                        break;
                    case (int)OTHER_SATELLITES_1:
                    case (int)OTHER_SATELLITES_2:
                        folderName = OtherSatellitesFolder;
                        break;
                    case (int)WEATHER_DATA:
                        folderName = WeatherDataFolder;
                        break;
                    default:
                        folderName = UnknownDataFolder;
                        break;
                }
            }
             
            dir = Tools.Combine(basedir, folderName);

            if (!Tools.DirExists(dir)) {
                Tools.CreateDir(dir);
            }

            filef = Tools.Combine(dir, filename);

        } else {
            /*// Old way
            string folderName = UnknownDataFolder;
            if (dcsRegex.IsMatch(filename)) {
                folderName = DCSFolder;
            } else if (xxRegex.IsMatch(filename)) {
                folderName = Tools.Combine(ImagesFolder, "Area of Interest");
            } else if (fdRegex.IsMatch(filename)) { 
                folderName = Tools.Combine(ImagesFolder, "Full Disk");
            } else if (chartRegex.IsMatch(filename)) {
                folderName = WeatherDataFolder;
            } else if (gosRegex.IsMatch(filename)) {
                folderName = Tools.Combine(ImagesFolder, UnknownDataFolder);
            } else if (textRegex.IsMatch(filename)) {
                folderName = TextFolder;
            } else {
                folderName = UnknownDataFolder;
            }

            dir = Tools.Combine(basedir, folderName);

            if (!Tools.DirExists(dir)) {
                Tools.CreateDir(dir);
            }

            filef = Tools.Combine(dir, filename);*/
        }
        return filef;
    }

    /*void PacketManager::HandleWeatherData(string filename, XRITHeader header) {
        if (header.PrimaryHeader.FileType == FileTypeCode.IMAGE) {
            string basedir = new DirectoryInfo(Path.GetDirectoryName(filename)).Parent.FullName;
            if (header.Product.ID == (int)OTHER_SATELLITES_1 || header.Product.ID == (int)OTHER_SATELLITES_2) {
                basedir = Path.Combine(basedir, OtherSatellitesFolder);
            } else {
                basedir = Path.Combine(basedir, WeatherDataFolder);
            }

            try {
                UIConsole.GlobalConsole.Log(string.Format("New Weather Data - {0} - {1}", header.SubProduct.Name, header.Filename));
                ImageHandler.Handler.HandleFile(filename, basedir);
                File.Delete(filename);
            } catch (Exception e) {
                UIConsole.GlobalConsole.Warn(string.Format("Failed to parse Weather Data Image at {0}: {1}", filename, e));
            }
        } else {
            FileHandler.DefaultHandler(filename, header);
        }
    }

    void PacketManager::HandleTextData(string filename, XRITHeader header) {
        if (header.PrimaryHeader.FileType == FileTypeCode.TEXT) {
            string basedir = new DirectoryInfo(Path.GetDirectoryName(filename)).Parent.FullName;
            basedir = Path.Combine(basedir, TextFolder);

            try {
                UIConsole.GlobalConsole.Log(string.Format("New NOAA Text ({0})", header.Filename));
                TextHandler.Handler.HandleFile(filename, basedir);
                File.Delete(filename);
            } catch (Exception e) {
                UIConsole.GlobalConsole.Warn(string.Format("Failed to parse Weather Data Image at {0}: {1}", filename, e));
            }
        } else {
            FileHandler.DefaultHandler(filename, header);
        }
    }

    void PacketManager::DumpFile(string filename, XRITHeader fileHeader, string newExt) {
        string dir = Path.GetDirectoryName(filename);
        string f = FixFileFolder(dir, fileHeader.Filename, fileHeader.Product, fileHeader.SubProduct);
        f = f.Replace(".lrit", "." + newExt);

        if (File.Exists(f)) {
            string timestamp = DateTime.Now.ToString("yyyyMMddHHmmssffff");
            string ext = Path.GetExtension(f);
            string append = String.Format("--dup-{0}{1}", timestamp, ext);
            f = f.Replace(String.Format("{0}", ext), append);
        }

        if (!String.Equals(Path.GetFileName(f), fileHeader.Filename)) {
            if (fileHeader.SubProduct.Name != "Unknown") {
                UIConsole.GlobalConsole.Log(String.Format("New {0} - {1} ({2}) saved as {3}", fileHeader.Product.Name, fileHeader.SubProduct.Name, fileHeader.Filename, Path.GetFileName(f)));
            } else {
                UIConsole.GlobalConsole.Log(String.Format("New {0} ({1}) saved as {2}", fileHeader.Product.Name, fileHeader.Filename, Path.GetFileName(f)));
            }
        } else {
            if (fileHeader.SubProduct.Name != "Unknown") {
                UIConsole.GlobalConsole.Log(String.Format("New {0} - {1} ({2})", fileHeader.Product.Name, fileHeader.SubProduct.Name, fileHeader.Filename));
            } else {
                UIConsole.GlobalConsole.Log(String.Format("New {0} ({1})", fileHeader.Product.Name, fileHeader.Filename));
            }
        }

        //UIConsole.GlobalConsole.Log(String.Format("New JPEG file {0}", fileHeader.Filename));
        Console.WriteLine("Renaming {0} to {1}", filename, f);
        FileStream fs = File.OpenRead(filename);
        fs.Seek(fileHeader.PrimaryHeader.HeaderLength, SeekOrigin.Begin);
        FileStream os = File.OpenWrite(f);

        byte[] buffer = new Byte[1024];
        int bytesRead;

        while ((bytesRead = fs.Read(buffer, 0, 1024)) > 0) {
            os.Write(buffer, 0, bytesRead);
        }

        fs.Close();
        os.Close();

        // Keep the original lrit file
        File.Move(filename, f.Replace("." + newExt, ".lrit"));
    }

    string PacketManager::Decompressor(string filename, int pixels) {
        try {
            Process decompressor = new Process();
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;

            if (LLTools.IsLinux) {
                startInfo.FileName = "wine";
                startInfo.Arguments = String.Format("Decompress.exe {0} {1} a", pixels, filename);
                startInfo.EnvironmentVariables.Add("WINEDEBUG", "fixme-all,err-winediag");
            } else {
                startInfo.FileName = "Decompress.exe";
                startInfo.Arguments = String.Format("{0} {1} a", pixels, filename);
            }

            startInfo.RedirectStandardError = true;
            startInfo.RedirectStandardOutput = true;
            startInfo.CreateNoWindow = true;
            startInfo.UseShellExecute = false;

            decompressor.StartInfo = startInfo;

            UIConsole.GlobalConsole.Debug(String.Format("Calling {0}", startInfo.Arguments));
            decompressor.Start();
            decompressor.WaitForExit();

            if (decompressor.ExitCode != 0) {
                string stderr = decompressor.StandardError.ReadToEnd();
                UIConsole.GlobalConsole.Error(String.Format("Error Decompressing: {0}", stderr));
            } else {
                UIConsole.GlobalConsole.Debug(String.Format("Decompress sucessful to {0}", String.Format("{0}_decomp.lrit", filename)));
                try {
                    File.Delete(filename);
                } catch (Exception e) {
                    Console.WriteLine("Cannot delete file {0}: {1}", filename, e);
                }
            }

        } catch (Exception e) {
            UIConsole.GlobalConsole.Error(String.Format("Error running decompressor: {0}", e));
        }

        return String.Format("{0}_decomp.lrit", filename);
    }

    string PacketManager::Decompressor(string prefix, int pixels, int startnum, int endnum) {
        try {
            Process decompressor = new Process();
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            if (LLTools.IsLinux) {
                startInfo.FileName = "wine";
                startInfo.Arguments = String.Format("Decompress.exe {0} {1} {2} {3} a", prefix, pixels, startnum + 1, endnum);
                startInfo.EnvironmentVariables.Add("WINEDEBUG", "fixme-all,err-winediag");
            } else {
                startInfo.FileName = "Decompress.exe";
                startInfo.Arguments =  String.Format("{0} {1} {2} {3} a", prefix, pixels, startnum + 1, endnum);
            }

            startInfo.RedirectStandardError = true;
            startInfo.RedirectStandardOutput = true;
            startInfo.CreateNoWindow = true;
            startInfo.UseShellExecute = false;

            decompressor.StartInfo = startInfo;

            UIConsole.GlobalConsole.Debug(String.Format("Calling {0}", startInfo.Arguments));
            decompressor.Start();
            decompressor.WaitForExit();

            if (decompressor.ExitCode != 0) {
                string stderr = decompressor.StandardError.ReadToEnd();
                UIConsole.GlobalConsole.Error(String.Format("Error Decompressing: {0}", stderr));
            } else {
                UIConsole.GlobalConsole.Debug(String.Format("Decompress sucessful to {0}", String.Format("{0}_decomp{1}.lrit", prefix, startnum)));
                for (int i=startnum; i<endnum+1; i++) {
                    string f = string.Format("{0}{1}.lrit", prefix, i);
                    try {
                        File.Delete(f);
                    } catch (Exception e) {
                        Console.WriteLine("Error deleting file {0}: {1}", f, e);
                    }
                }
            }

        } catch (Exception e) {
            UIConsole.GlobalConsole.Error(String.Format("Error running decompressor: {0}", e));
        }

        return String.Format("{0}_decomp{1}.lrit", prefix, startnum);
    }*/
}