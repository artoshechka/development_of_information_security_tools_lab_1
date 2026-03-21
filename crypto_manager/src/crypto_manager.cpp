/// @file
/// @brief Определение менеджера криптографических операций.
/// @author Artemenko Anton

#include <src/crypto_manager.hpp>

#include <logger_macros.hpp>

#include <stdexcept>

namespace crypto_manager
{
CryptoManager::CryptoManager(std::unique_ptr<ICryptoStrategy> cryptoStrategy,
                             const std::shared_ptr<logger::ILogger> &logger)
    : cryptoStrategy_(std::move(cryptoStrategy)), logger_(logger)
{
    if (!cryptoStrategy_)
    {
        if (logger_)
        {
            LogError(logger_) << "CryptoManager received null crypto strategy";
        }
        throw std::invalid_argument("crypto strategy must not be null");
    }
}

bool CryptoManager::EncryptFile(const QString &filePath, const QString &password)
{
    const bool result = cryptoStrategy_->EncryptFile(filePath, password);
    if (!result && logger_)
    {
        LogError(logger_) << "EncryptFile failed in strategy for file: " << filePath;
    }

    return result;
}

bool CryptoManager::DecryptFile(const QString &filePath, const QString &password)
{
    const bool result = cryptoStrategy_->DecryptFile(filePath, password);
    if (!result && logger_)
    {
        LogError(logger_) << "DecryptFile failed in strategy for file: " << filePath;
    }

    return result;
}

} // namespace crypto_manager
