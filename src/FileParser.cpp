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
            
            switch ((int)type) {
                case HeaderType::PrimaryHeader: {
                    header.PrimaryHeader.RawData = tmp;
                    PrimaryRecord record;
                    memcpy(&record, tmp.data(), tmp.size());
                    record.Correct();
                    header.PrimaryHeader.Define(record);
                    maxLength = (uint32_t)record.HeaderLength;

                    cout << "PH FileTypeCode: " << (int)record.FileTypeCode << endl;
                    cout << "PH HeaderLength: " << (uint32_t)record.HeaderLength << endl;
                    cout << "PH DataLength: " << (uint64_t)record.DataLength << endl;
                    break;
                }
                case HeaderType::DCSFileNameRecord: {
                    header.DCSFilenameHeader.RawData = tmp;
                    DCSFilenameRecord record;
                    tmp.erase(tmp.begin(), tmp.begin()+3);
                    record.Filename = Tools.Binary2String(tmp);
                    header.DCSFilenameHeader.Define(record);

                    cout << "DCS Filename: " << (string)record.Filename << endl;
                    break;
                }
                case HeaderType::ImageStructureRecord: {
                    break;
                }
                case HeaderType::ImageNavigationRecord: {
                    break;
                }
                case HeaderType::ImageDataFunctionRecord: {
                    break;
                }
                case HeaderType::AnnotationRecord: {
                    header.AnnotationHeader.RawData = tmp;
                    AnnotationRecord record;
                    tmp.erase(tmp.begin(), tmp.begin()+3);
                    record.Filename = Tools.Binary2String(tmp);
                    header.AnnotationHeader.Define(record);

                    cout << "AR Filename: " << (string)record.Filename << endl;
                    break;
                }
                case HeaderType::TimestampRecord: {
                    header.TimestampHeader.RawData = tmp;
                    TimestampRecord record;
                    memcpy(&record, tmp.data(), tmp.size());
                    record.Correct();
                    header.TimestampHeader.Define(record);

                    cout << "TS Milissecods: " << (uint32_t)record.Milisseconds << endl;
                    cout << "TS Days: " << (uint16_t)record.Days << endl;
                    break;
                }
                case HeaderType::AncillaryTextRecord: {
                    break;
                }
                case HeaderType::KeyRecord: {
                    break;
                }
                case HeaderType::SegmentIdentificationRecord: {
                    break;
                }
                case HeaderType::NOAASpecificHeader: {
                    header.NOAASpecificHeader.RawData = tmp;
                    NOAASpecificRecord record;
                    memcpy(&record, tmp.data(), tmp.size());
                    record.Correct();
                    header.NOAASpecificHeader.Define(record);
                    
                    cout << "Signature: " << (string)record.Signature << endl;
                    cout << "Compression: " << (int)record.Compression << endl;
                    cout << "ProductID: " << (uint16_t)record.ProductID << endl;
                    break;
                }
                case HeaderType::HeaderStructuredRecord: {
                    break;
                }
                case HeaderType::RiceCompressionRecord: {
                    break;
                }
                default:
                    break;
            }
            
            cout << "OUT LOOP" << endl;
            c += size;
            data.erase(data.begin(), data.begin()+size);
        }
        return header;
    }
}