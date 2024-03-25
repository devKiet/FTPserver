#include <FTPClient.h>

FTPClient::FTPClient(const TCHAR* server, const TCHAR* username, const TCHAR* password)
    : server(server), username(username), password(password) 
{
    hInternet = InternetOpen(_T("FTP testing"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);;
    if (hInternet == NULL) {
        std::cerr << "InternetOpen failed, error " << GetLastError() << std::endl;
        exit(1);
    }
}

FTPClient::~FTPClient()
{
    InternetCloseHandle(hInternet);
}

bool FTPClient::UploadFile(const TCHAR* localPath, const TCHAR* remotePath)
{
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

bool FTPClient::DownloadFile(const TCHAR* remotePath, const TCHAR* localPath) 
{
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

HINTERNET FTPClient::OpenFTPConnection()
{
    return InternetConnect(hInternet, server, INTERNET_DEFAULT_FTP_PORT, username, password, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
}

void FTPClient::PrintLastError(bool result, const TCHAR* localPath, const TCHAR* remotePath)
{
    if (!result) {
        DWORD error = GetLastError();
        std::cerr << "Failed to upload/download file. Error code: " << error << std::endl;
        std::cerr << "Local path: " << localPath << std::endl;
        std::cerr << "Remote path: " << remotePath << std::endl;
    }
}
