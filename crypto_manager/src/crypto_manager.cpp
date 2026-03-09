/// @file
/// @brief Определение менеджера криптографических операций (Singleton).
/// @author Artemenko Anton

#include <src/crypto_manager.hpp>

#include <QByteArray>
#include <QCryptographicHash>
#include <QFile>
#include <QString>

#include <openssl/evp.h>
#include <openssl/rand.h>

using crypto_manager::OpenSSLCryptoManager;
namespace
{

/// Сигнатура зашифрованного файла
static const QByteArray FILE_MAGIC_SIGNATURE = "A5E2BDE2-21FD-4D6B-A905-78A326846E07";

/// @brief Генерация криптографического ключа из пароля.
/// @param[in] userPassword Пароль пользователя.
/// @return 32-байтовый ключ (SHA-256), подходящий для AES-256.
static QByteArray deriveKey(const QString &userPassword)
{
    return QCryptographicHash::hash(userPassword.toUtf8(), QCryptographicHash::Sha256);
}

} // namespace

OpenSSLCryptoManager &OpenSSLCryptoManager::Instance()
{
    static OpenSSLCryptoManager singletonInstance;
    return singletonInstance;
}

bool OpenSSLCryptoManager::EncryptFile(const QString &filePath, const QString &password)
{
    QFile inputFile(filePath);

    if (!inputFile.open(QIODevice::ReadOnly))
        return false;

    QByteArray fileContent = inputFile.readAll();
    inputFile.close();

    if (fileContent.startsWith(FILE_MAGIC_SIGNATURE))
        return false;

    QByteArray encryptionKey = deriveKey(password);

    unsigned char initializationVector[16];

    if (!RAND_bytes(initializationVector, sizeof(initializationVector)))
        return false;

    EVP_CIPHER_CTX *cipherContext = EVP_CIPHER_CTX_new();

    if (!cipherContext)
        return false;

    QByteArray encryptedData(fileContent.size() + 16, 0);

    int bytesProcessed = 0;
    int totalCiphertextLength = 0;

    if (!EVP_EncryptInit_ex(cipherContext, EVP_aes_256_cbc(), nullptr,
                            reinterpret_cast<const unsigned char *>(encryptionKey.data()), initializationVector))
    {
        EVP_CIPHER_CTX_free(cipherContext);
        return false;
    }

    if (!EVP_EncryptUpdate(cipherContext, reinterpret_cast<unsigned char *>(encryptedData.data()), &bytesProcessed,
                           reinterpret_cast<const unsigned char *>(fileContent.data()), fileContent.size()))
    {
        EVP_CIPHER_CTX_free(cipherContext);
        return false;
    }

    totalCiphertextLength = bytesProcessed;

    if (!EVP_EncryptFinal_ex(cipherContext, reinterpret_cast<unsigned char *>(encryptedData.data()) + bytesProcessed,
                             &bytesProcessed))
    {
        EVP_CIPHER_CTX_free(cipherContext);
        return false;
    }

    totalCiphertextLength += bytesProcessed;

    EVP_CIPHER_CTX_free(cipherContext);

    encryptedData.resize(totalCiphertextLength);

    QFile outputFile(filePath);

    if (!outputFile.open(QIODevice::WriteOnly))
        return false;

    outputFile.write(FILE_MAGIC_SIGNATURE);
    outputFile.write(reinterpret_cast<char *>(initializationVector), sizeof(initializationVector));
    outputFile.write(encryptedData);

    outputFile.close();

    return true;
}

bool OpenSSLCryptoManager::DecryptFile(const QString &filePath, const QString &password)
{
    QFile inputFile(filePath);

    if (!inputFile.open(QIODevice::ReadOnly))
        return false;

    QByteArray fileContent = inputFile.readAll();
    inputFile.close();

    if (!fileContent.startsWith(FILE_MAGIC_SIGNATURE))
        return false;

    QByteArray decryptionKey = deriveKey(password);

    QByteArray initializationVector = fileContent.mid(FILE_MAGIC_SIGNATURE.size(), 16);
    QByteArray encryptedData = fileContent.mid(FILE_MAGIC_SIGNATURE.size() + 16);

    EVP_CIPHER_CTX *cipherContext = EVP_CIPHER_CTX_new();

    if (!cipherContext)
        return false;

    QByteArray decryptedData(encryptedData.size(), 0);

    int bytesProcessed = 0;
    int totalPlaintextLength = 0;

    if (!EVP_DecryptInit_ex(cipherContext, EVP_aes_256_cbc(), nullptr,
                            reinterpret_cast<const unsigned char *>(decryptionKey.data()),
                            reinterpret_cast<const unsigned char *>(initializationVector.data())))
    {
        EVP_CIPHER_CTX_free(cipherContext);
        return false;
    }

    if (!EVP_DecryptUpdate(cipherContext, reinterpret_cast<unsigned char *>(decryptedData.data()), &bytesProcessed,
                           reinterpret_cast<const unsigned char *>(encryptedData.data()), encryptedData.size()))
    {
        EVP_CIPHER_CTX_free(cipherContext);
        return false;
    }

    totalPlaintextLength = bytesProcessed;

    if (!EVP_DecryptFinal_ex(cipherContext, reinterpret_cast<unsigned char *>(decryptedData.data()) + bytesProcessed,
                             &bytesProcessed))
    {
        EVP_CIPHER_CTX_free(cipherContext);
        return false;
    }

    totalPlaintextLength += bytesProcessed;

    EVP_CIPHER_CTX_free(cipherContext);

    decryptedData.resize(totalPlaintextLength);

    QFile outputFile(filePath);

    if (!outputFile.open(QIODevice::WriteOnly))
        return false;

    outputFile.write(decryptedData);

    outputFile.close();

    return true;
}