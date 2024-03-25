#include "FTPClient.h"
#include "common.cpp"
#include <cstring>
#include <limits>

#define MAX_PATH_LENGTH 256
std::string filename = "./conf/conf.config";

/// @brief main
/// @return 
int main() 
{
    Config config = readConfigFile(filename);

    if (config.password.empty() || config.username.empty() || config.password.empty())
    {
        return 0;
    }
    // Thông tin máy chủ FTP
    const TCHAR* server = _T(config.server.c_str());
    const TCHAR* username = _T(config.username.c_str());
    const TCHAR* password = _T(config.password.c_str());

    FTPClient* ftpClient = new FTPClient(server, username, password);

    std::cout << "1. Upload file" << std::endl;
    std::cout << "2. Download file" << std::endl;
    std::cout << "3. Quit" << std::endl;

    while(1)
    {   
        std::cout << "Choose an option: ";
        char option;
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (option)
        {
        case '1':
        {
            TCHAR localPath[MAX_PATH_LENGTH];
            TCHAR remotePath[MAX_PATH_LENGTH];

            std::cout << "Enter local path: ";
            std::cin >> localPath;

            std::cout << "Enter remote path: ";
            std::cin >> remotePath;

            if (std::strlen(localPath) >= MAX_PATH_LENGTH || std::strlen(remotePath) >= MAX_PATH_LENGTH) 
            {
                std::cerr << "Path length exceeds the maximum allowed length of " << MAX_PATH_LENGTH << " characters." << std::endl;
                break;
            }

            if (fopen(localPath, "r")  == NULL) 
            {
                perror("Failed: ");
                continue;
            }

            if (ftpClient->UploadFile(localPath, remotePath)) 
            {
                std::cout << "File uploaded successfully\n";
            }
            else
            {
                std::cerr << "Failed to upload file\n";
            }
            break;
        }
        case '2':
        {
            TCHAR localPath[MAX_PATH_LENGTH];
            TCHAR remotePath[MAX_PATH_LENGTH];
            
            std::cout << "Enter remote path: ";
            std::cin >> remotePath;

            std::cout << "Enter local path: ";
            std::cin >> localPath;

            if (std::strlen(localPath) >= MAX_PATH_LENGTH || std::strlen(remotePath) >= MAX_PATH_LENGTH) 
            {
                std::cerr << "Path length exceeds the maximum allowed length of " << MAX_PATH_LENGTH << " characters." << std::endl;
                break;
            }
            
            if (ftpClient->DownloadFile(remotePath, localPath))
            {
                std::cout << "File downloaded successfully\n";
            }
            else
            {
                std::cerr << "Failed to download file\n";
            }
            break;
        }
        case '3':
        {
            delete ftpClient;
            return 0;
        }
        default:
        {
            std::cerr << "Invalid option\n";
            break;
        }
        }
    }

    return 0;
}
