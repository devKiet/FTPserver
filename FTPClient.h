#ifndef FTPCLIENT_H
#define FTPCLIENT_H
#include <iostream>
#include <windows.h>
#include <wininet.h>
#include <tchar.h>
 
class FTPClient
{
public:
    /// @brief FTPClient
    /// @param server
    /// @param username
    /// @param password
    /// @return
    FTPClient(const TCHAR *server, const TCHAR *username, const TCHAR *password);

    /// @brief ~FTPClient
    /// @return
    ~FTPClient();

    /// @brief UploadFile
    /// @param localPath
    /// @param remotePath
    /// @return success
    bool UploadFile(const TCHAR *localPath, const TCHAR *remotePath);

    /// @brief DownloadFile
    /// @param remotePath
    /// @param localPath
    /// @return success
    bool DownloadFile(const TCHAR *remotePath, const TCHAR *localPath);

private:
    /// @brief OpenFTPConnection
    /// @return InternetConnect
    HINTERNET OpenFTPConnection();

    /// @brief PrintLastError
    /// @param result
    /// @param remotePath
    /// @param localPath
    /// @return
    void PrintLastError(bool result, const TCHAR *localPath, const TCHAR *remotePath);

private:
    /// @brief hInternet
    HINTERNET hInternet;

    /// @brief server
    LPCTSTR server;

    /// @brief username
    LPCTSTR username;

    /// @brief password
    LPCTSTR password;
};

#endif