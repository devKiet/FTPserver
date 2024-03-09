#include <iostream>
#include <windows.h>
#include <wininet.h>
#include <tchar.h>

class FTPClient {
public:
    FTPClient(const TCHAR* server, const TCHAR* username, const TCHAR* password)
        : server(server), username(username), password(password) {
        hInternet = InternetOpen(_T("FTP testing"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);;
        if (hInternet == NULL) {
            std::cerr << "InternetOpen failed, error " << GetLastError() << std::endl;
            exit(1);
        }
    }

    ~FTPClient() {
        InternetCloseHandle(hInternet);
    }

    bool UploadFile(const TCHAR* localPath, const TCHAR* remotePath) {
        HINTERNET hConnect = OpenFTPConnection();
        if (hConnect == NULL) {
            std::cerr << "Failed to open FTP connection. Error " << GetLastError() << std::endl;
            return false;
        }

        bool result = FtpPutFile(hConnect, localPath, remotePath, FTP_TRANSFER_TYPE_BINARY, 0) != 0;
        PrintLastError(result, localPath, remotePath);
        InternetCloseHandle(hConnect);
        return result;
    }

    bool DownloadFile(const TCHAR* remotePath, const TCHAR* localPath) {
        HINTERNET hConnect = OpenFTPConnection();
        if (hConnect == NULL) {
            std::cerr << "Failed to open FTP connection. Error " << GetLastError() << std::endl;
            return false;
        }

        bool result = FtpGetFile(hConnect, remotePath, localPath, FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY, 0) != 0;
        PrintLastError(result, localPath, remotePath);
        InternetCloseHandle(hConnect);
        return result;
    }

private:
    HINTERNET hInternet;
    LPCTSTR server;
    LPCTSTR username;
    LPCTSTR password;

    HINTERNET OpenFTPConnection() {
        return InternetConnect(hInternet, server, INTERNET_DEFAULT_FTP_PORT, username, password, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
    }

    void PrintLastError(bool result, const TCHAR* localPath, const TCHAR* remotePath)
    {
        if (!result) {
            DWORD error = GetLastError();
            std::cerr << "Failed to upload/download file. Error code: " << error << std::endl;
            std::cerr << "Local path: " << localPath << std::endl;
            std::cerr << "Remote path: " << remotePath << std::endl;
        }
    }
};

int main() {
    // Thông tin máy chủ FTP
    const TCHAR* server = _T("ftpupload.net");
    const TCHAR* username = _T("if0_36127269");
    const TCHAR* password =  _T("sPBoDy5X8X");

    FTPClient ftpClient(server, username, password);

    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Upload file" << std::endl;
    std::cout << "2. Download file" << std::endl;

    int option;
    std::cin >> option;

    if (option == 1) {
        // Upload file
        const TCHAR* localPath = _T("C:\\Users\\AD\\Downloads\\note.txt");
        const TCHAR* remotePath = _T("note.txt");

        if (fopen(localPath, "r")  == NULL)
        {
            perror("Failed: ");
            return 1;
        }
        if (ftpClient.UploadFile(localPath, remotePath)) {
            std::cout << "File uploaded successfully\n";
        } else {
            std::cerr << "Failed to upload file\n";
        }
    } else if (option == 2) {
        // Download file
        const TCHAR* remotePath = _T("note.txt");
        const TCHAR* localPath = _T("C:\\Users\\AD\\Downloads\\note.txt");
        if (ftpClient.DownloadFile(remotePath, localPath)) {
            std::cout << "File downloaded successfully\n";
        } else {
            std::cerr << "Failed to download file\n";
        }
    } else {
        std::cerr << "Invalid option\n";
    }

    return 0;
}
