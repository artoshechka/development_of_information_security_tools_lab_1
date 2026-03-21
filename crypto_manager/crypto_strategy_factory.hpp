/// @file
/// @brief Объявление фабрики криптографических стратегий.
/// @author Artemenko Anton
#ifndef GUID_6F34AE39_0BB3_4A98_83D7_C1945278D4A2
#define GUID_6F34AE39_0BB3_4A98_83D7_C1945278D4A2

#include <icrypto_strategy.hpp>

#include <memory>

namespace crypto_manager
{
/// @brief Тип доступной реализации криптографической стратегии.
enum class CryptoBackend
{
    OpenSsl,
};

/// @brief Создает криптографическую стратегию по выбранному backend'у.
/// @param[in] backend Идентификатор криптографического backend'а.
/// @return Уникальный указатель на стратегию или `nullptr`, если backend не поддерживается.
std::unique_ptr<ICryptoStrategy> CreateCryptoStrategy(CryptoBackend backend);

/// @brief Создает криптографическую стратегию с backend'ом по умолчанию.
/// @return Уникальный указатель на стратегию.
std::unique_ptr<ICryptoStrategy> CreateCryptoStrategy();

} // namespace crypto_manager

#endif // GUID_6F34AE39_0BB3_4A98_83D7_C1945278D4A2
