#include <iostream>
#include "FileParser.h"

using namespace std;
namespace GOESDump {
    XRITHeader FileParser::GetHeader(vector<uint8_t> data) {
        XRITHeader header;
        data.erase(data.begin(), data.begin()+10);
        int maxLength = data.size(); // Initial Guess
        int c = 0;

        cout << "maxLength: " << maxLength << "\n";

        while (c < maxLength) {
            uint8_t type = data.at(0);

            uint16_t size = ((uint16_t)data.at(2) << 8) | data.at(1);
            size = (size>>8) | (size<<8);

            vector<uint8_t> tmp;
            tmp.insert(tmp.end(), data.begin(), data.begin()+size);

            if (tmp.size() < size) {
                cout << "Not enough data for unpack header: Expected " << size << " got " << tmp.size() << "\n";
                break;
            }

            cout << "TYPE: " << (int)type << "\n";
            
            switch ((HeaderType)type) {
                case HeaderType::PrimaryHeader:
                    PrimaryRecord fh;
                    char* buffer = Tools.Vector2Byte(tmp);
                    header.PrimaryHeader.Define(fh);
                    header.PrimaryHeader.RawData = tmp;
                    maxLength = (int)fh.HeaderLength;
                    break;
                /*case HeaderType::DCSFileNameRecord:
                    DCSFilenameRecord record;
                    record.Filename = "MAKE THE UTF8 CONV";
                    header.DCSFilenameHeader.RawData = tmp;
                    header.DCSFilenameHeader.Define(record);
                    break;
                case (int)ImageStructureRecord:
                    ImageStructureRecord isr = LLTools.ByteArrayToStruct<ImageStructureRecord>(tmp);
                    isr = LLTools.StructToSystemEndian(isr);
                    h = new ImageStructureHeader(isr);
                    break;
                case (int)ImageNavigationRecord:
                    ImageNavigationRecord inr = LLTools.ByteArrayToStruct<ImageNavigationRecord>(tmp);
                    inr = LLTools.StructToSystemEndian(inr);
                    h = new ImageNavigationHeader(inr);
                    break;
                case (int)ImageDataFunctionRecord:
                    ImageDataFunctionRecord idfr = new ImageDataFunctionRecord();
                    idfr.Data = System.Text.Encoding.UTF8.GetString(tmp.Skip(3).ToArray());
                    h = new ImageDataFunctionHeader(idfr);
                    break;
                case (int)AnnotationRecord:
                    AnnotationRecord ar = new AnnotationRecord();
                    ar.Filename = System.Text.Encoding.UTF8.GetString(tmp.Skip(3).ToArray());
                    h = new AnnotationHeader(ar);
                    break;
                case (int)TimestampRecord:
                    TimestampRecord tr = LLTools.ByteArrayToStruct<TimestampRecord>(tmp);
                    tr = LLTools.StructToSystemEndian(tr);
                    h = new TimestampHeader(tr);
                    break;
                case (int)AncillaryTextRecord:
                    AncillaryText at = new AncillaryText();
                    at.Data = System.Text.Encoding.UTF8.GetString(tmp.Skip(3).ToArray());
                    h = new AncillaryHeader(at);
                    break;
                case (int)KeyRecord:
                    h = new XRITBaseHeader(HeaderType.KeyRecord, tmp);
                    break;
                case (int)SegmentIdentificationRecord:
                    SegmentIdentificationRecord sir = LLTools.ByteArrayToStruct<SegmentIdentificationRecord>(tmp);
                    sir = LLTools.StructToSystemEndian(sir);
                    h = new SegmentIdentificationHeader(sir);
                    break;
                case (int)NOAASpecificHeader:
                    NOAASpecificRecord nsr = LLTools.ByteArrayToStruct<NOAASpecificRecord>(tmp);
                    nsr = LLTools.StructToSystemEndian(nsr);
                    h = new NOAASpecificHeader(nsr);
                    break;
                case (int)HeaderStructuredRecord:
                    HeaderStructuredRecord hsr = new HeaderStructuredRecord();
                    hsr.Data = System.Text.Encoding.UTF8.GetString(tmp.Skip(3).ToArray());
                    h = new HeaderStructuredHeader(hsr);
                    break;
                case (int)RiceCompressionRecord:
                    RiceCompressionRecord rcr = LLTools.ByteArrayToStruct<RiceCompressionRecord>(tmp);
                    rcr = LLTools.StructToSystemEndian(rcr);
                    h = new RiceCompressionHeader(rcr);
                    break;
                default:
                    break;*/
            }
            cout << "OUT LOOP" << endl;
            c += size;
            data.erase(data.begin()+size, data.end());
        }
        return header;
    }
}